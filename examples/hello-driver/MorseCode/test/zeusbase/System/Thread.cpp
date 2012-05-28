/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Thread
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 20.02.07 10:18 $
 * Ablage  : $File$
 * System  : Cell Computing Model
 ***************************************************************************
 * Licence:                                                                *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version             *
 *   2.1 of the License, or (at your option) any later version.            *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  *
 ***************************************************************************/

/***************************************************************************
 Changes :
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Thread.cpp $
** 
** 13    20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
**
** 9     28.11.06 16:31 bha
** Beheben von Compilerwarnungen
**
** 6     2.10.06 9:21 bha
** Killing and stopping of blocked threads on Linux and Win32
***************************************************************************/

#include <zeusbase/System/Thread.h>
#include <zeusbase/System/ThreadManager.h>
#include <zeusbase/System/ThreadMessageQueue.h>
#include <zeusbase/System/Time.h>
#include <zeusbase/System/CriticalSection.h>

#if defined(__GNUC__)
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/wait.h>
  #include <signal.h>
  #include <pthread.h>
  #include <linux/unistd.h>
#else
  #include <process.h>
  #include <windows.h>
#endif

USING_NAMESPACE_Zeus

//##########################################################################
// LINUX SPECIFIC FUNCTIONS

#if defined(__GNUC__)
/***************************************************************************/
/*! Handles the signal
*/
/***************************************************************************/
static void sigThreadHandler(int sig)
{
//  RootLogger.printfln(LOGMODE_DEBUG, "Signal received: %d", sig);
}

/***************************************************************************/
/*! Initializes the signal handler of the current thread object
*/
/***************************************************************************/
void initThreadSigHandler()
{
  sigset_t Mask;
  struct sigaction SigAction;
  
  sigemptyset(&Mask);
  SigAction.sa_handler = sigThreadHandler;
  SigAction.sa_mask = Mask;
  SigAction.sa_flags = 0;
  
  if (sigaction(SIGPIPE, &SigAction, NULL) < 0)
  {
//    RootLogger.printfln(LOGMODE_WARN, "Unable to init sig handler for SIGPIPE");
  }
}

/***************************************************************************/
/*! This is the run method of the thread
    \param life : the thread object 
    \return NULL;
*/
/***************************************************************************/
/*static*/ void* TThread::createThread(void* life)
{
  if (life != NULL)
  {
    TThread& rThread = *((TThread*)life);
    
//    RootLogger.printfln(LOGMODE_DEBUG, "Thread %d executed.",(int)life);
    initThreadSigHandler();
    
    //////////////////
    // Register thread at the ThreadManager
    // Note: Thread will wait until the thread ID is valid
    ThreadManager.addThread(rThread.getThreadID(), rThread.m_rQueue, false);
    //////////////////

    rThread.onStarted();
    rThread.execute();
    rThread.terminate_internal();
    rThread.onTerminated();
    
//    RootLogger.printfln(LOGMODE_DEBUG, "Thread %d terminated.",(int)life);
  }
  else
  {
//    RootLogger.printfln(LOGMODE_FATAL, "Invalid Thread object.");
  }
  return NULL;
}
//##########################################################################


//##########################################################################
// WINDOWS SPECIFIC FUNCTIONS
#else


/***************************************************************************/
/*! This is the run method of the thread
    \param life : the thread object 
    \return NULL;
*/
/***************************************************************************/
/*static*/ Uint32 __stdcall TThread::createThread(void* pLife)
{
  #ifdef WIN32
    //Initialize the COM for this thread. 
    CoInitialize(NULL); 
  #endif

  if (pLife != NULL)
  {
    TThread& rThread = *((TThread*)pLife);
    
//    RootLogger.printfln(LOGMODE_DEBUG, "Thread %d executed.",(Int)pLife);
    
    //////////////////
    // Register thread at the ThreadManager
    // Note: Thread will wait until the thread ID is valid
    ThreadManager.addThread(rThread.getThreadID(), rThread.m_rQueue, false);
    //////////////////
    
    rThread.onStarted();
    rThread.execute();
    rThread.terminate_internal();
    rThread.onTerminated();
    
//    RootLogger.printfln(LOGMODE_DEBUG, "Thread %d terminated.",(Int)pLife);
  }
  else
  {
//    RootLogger.printfln(LOGMODE_FATAL, "Invalid Thread object.");
  }
  return 0;
}
//##########################################################################


#if _WIN32_WINNT >= 0x0400
/***************************************************************************/
/*! User asynchron procedure call for win NT. This is used to wake the 
    thread from all waiting functions (SleepEx, WaitForMultibleObjectEx, 
    etc.). Make sure the thread is alertable all the time, otherwise this
    wont work.
*/
/***************************************************************************/
/*static*/ void CALLBACK TThread::doUserAPCProc(DWORD /*dwParam*/)
{
  // Do nothing here
}
#endif //_WIN32_WINNT >= 0x0400

#endif //not defined(__GNUC__)


/***************************************************************************/
/*! Creates a thread
    \param ePriority : Thread priority
*/
/***************************************************************************/
TThread::TThread(EPriority ePriority /*= etNormal*/)
 : TZObject(),
   m_rQueue(*new TThreadMessageQueue()),
   m_rDataLock(*new TCriticalSection(TCriticalSection::ltRecursive))
{
  m_ePriority = ePriority;
  m_uiThreadID = 0;
  m_bCreated = false;
  m_bSuspended = false;
  m_bInterrupted = true;
  m_pRunObj = NULL;

  #if defined(__GNUC__)
  #else
    m_hHandle = NULL;
  #endif

}

/***************************************************************************/
/*! Creates a thread using an external object as executing
    \param rObj : Object for execution
    \param ePriority : Thread priority
*/
/***************************************************************************/
TThread::TThread(IRunnable& rObj, EPriority ePriority /*= etNormal*/)
 : TZObject(),
   m_rQueue(*new TThreadMessageQueue()),
   m_rDataLock(*new TCriticalSection(TCriticalSection::ltRecursive))
{
  m_ePriority = ePriority;
  m_uiThreadID = 0;
  m_bCreated = false;
  m_bSuspended = false;
  m_bInterrupted = false;
  m_pRunObj = &rObj;
  m_pRunObj->addRef();

  #if defined(__GNUC__)
  #else
    m_hHandle = NULL;
  #endif
}


/***************************************************************************/
/*! Destroys the thread
*/
/***************************************************************************/
TThread::~TThread()
{
  //////////////////////////////////////
  // IMPORTANT:
  // Kill the thread. There is given no timeout. The thread will be killed 
  // imediately. This might cause ressource leaks. Use signalizeStop() 
  // before destroing the thread object.
  if (m_bCreated)
  {  
    this->kill();
  }
  //////////////////////////////////////
  
  if (m_pRunObj != NULL)
  {
    m_pRunObj->release();
    m_pRunObj = NULL;
  }
  
  m_rQueue.flush();
  m_rQueue.release();
  m_rDataLock.release();
}

/***************************************************************************/
/*! sets a new priority of the thread
    \param ePriority : new priority
*/
/***************************************************************************/
void TThread::setPriority(EPriority ePriority)
{
  m_ePriority = ePriority;

  #if defined(__GNUC__)
    if (m_bCreated)
    {
      struct sched_param Param;   // scheduling priority
      int iPolicy = SCHED_OTHER;  // regular scheduling policy

      Param.sched_priority = 0;

      switch(m_ePriority)
      {
        case etLow :
          Param.sched_priority = 15;
        break;

        case etHigh :
          Param.sched_priority = -15;
        break;

        case etLower :
          Param.sched_priority = 5;
        break;

        case etHigher :
          Param.sched_priority = -5;
        break;

        case etTimeCritical :
          Param.sched_priority = -20  ;
          iPolicy = SCHED_FIFO;
        break;

        case etNormal:
        default:
          //iPriority = 0;
        break;
      }

      if(pthread_setschedparam(Thread, iPolicy, &Param) != 0)
      {
 //       RootLogger.printfln(LOGMODE_ERROR, "Could not set the thread priority.");
      }
    }
  #else
    if (m_hHandle != NULL)
    {
      int iPriority = THREAD_PRIORITY_NORMAL;

      switch(m_ePriority)
      {
        case etLow :
          iPriority = THREAD_PRIORITY_LOWEST;
        break;

        case etHigh :
          iPriority = THREAD_PRIORITY_HIGHEST;
        break;

        case etLower :
          iPriority = THREAD_PRIORITY_BELOW_NORMAL;
        break;

        case etHigher :
          iPriority = THREAD_PRIORITY_ABOVE_NORMAL;
        break;

        case etTimeCritical :
          iPriority = THREAD_PRIORITY_TIME_CRITICAL  ;
        break;

        case etNormal: //fall through
        default:
          //iPriority = THREAD_PRIORITY_LOWEST;
        break;
      }

      if(!::SetThreadPriority(m_hHandle, iPriority))
      {
//        RootLogger.printfln(LOGMODE_ERROR, "Could not set the thread priority.");
      }
    }
  #endif
}


/***************************************************************************/
/*! Terminates the thread. If time out is not zero, this method will
    wait, until the thread terminats itself. If timeout occures, the
    thread will be forced to terminate. This might cause ressource leaks.
    \param dTimeOut : Time out
*/
/***************************************************************************/
void TThread::kill(Float64 dTimeOut /*= 0*/)
{
  signalizeStop(0);

  #if defined(__GNUC__)
    if (m_bCreated)
    {
      Float64 dTimeStamp = TTime::getTimeStamp();
      bool bThreadKilled= false;
      
      //wait to exit the tread
      while(!bThreadKilled && m_bCreated)
      {
        if(TTime::getTimeStamp()- dTimeStamp < dTimeOut)
        {
          TTime::sleep(0.1);
        }
        else
        {
          //CAUTION: 
          // Calling pthread_cancel() might produce resource leaks.
          // All data allocated in the execute()-method want be 
          // released (heap-allocations)
          pthread_cancel(Thread);
          bThreadKilled = true;
          m_bCreated = false;
        }
      } //while(!bThreadKilled && m_bCreated)
       
      pthread_join(Thread, NULL);
      ThreadManager.removeThread(this->getThreadID());
    }
  #else // #if not defined(__GNUC__)
    if (m_hHandle != NULL)
    {
      DWORD dwExitCode = 0;
      Float64 dTimeStamp = TTime::getTimeStamp();
      bool bThreadKilled= false;
  
      // wait to exit the tread
      // We have to wait for the exit code. If the exit code
      // is STILL_ACTIVE we have to wait as well.
      while(::GetExitCodeThread(m_hHandle, &dwExitCode) &&
              dwExitCode == STILL_ACTIVE &&
              !bThreadKilled)
      {
        if(TTime::getTimeStamp()- dTimeStamp < dTimeOut)
        {
          TTime::sleep(0.1);
        }
        else
        {
          //CAUTION: 
          // Calling ::TerminateThread() might produce resource leaks.
          // All data allocated in the execute()-method want be 
          // released (heap-allocations)
          ::TerminateThread(m_hHandle, 0);
          bThreadKilled = true;
          m_bCreated = false;
        }
      } // ::GetExitCodeThread(m_hHandle, &dwExitCode) && ...
  
      ::CloseHandle(m_hHandle);
      ThreadManager.removeThread(this->getThreadID());  
      m_hHandle = NULL;
    }
  #endif //#if not defined(__GNUC__)
  
  terminate_internal();
  m_uiThreadID = 0;
}

/***************************************************************************/
/*! Sets the interrupped signal. 
    \note the minimal time slice is about 0.1 sec.
*/
/***************************************************************************/
bool TThread::signalizeStop(Float64 dTimeOut /*=5.0*/)
{  
  bool bAbort = false;
  
  // Set the local interruption flag.
  m_bInterrupted = true;

  // Set the global interruption flag.
  // Note:  Any loops the thread is in, this flag shoul be checked
  //        otherwise the thread want terminate. 
  // Linux: Since we have no alertable functionality on
  //        Linux systems, we use non blocking API functions and loop 
  //        over it, checking the thread interruption flag.
  ThreadManager.setThreadState(this->getThreadID(), m_bInterrupted);
  
  //If the thread is suspended, we have to awake it, before terminating
  if (m_bSuspended)
  {
    this->resume();
  }


  //CALL the asynchron procedure call for win NT
  // This will wake the thread from waiting functions 
  // (SleepEx, WaitForMultibleObjectEx, etc) 
  #if _WIN32_WINNT >= 0x0400
    QueueUserAPC(doUserAPCProc, m_hHandle, 0);
  #endif

  
  // Here we wait for the termination. If the thread leaves its loop
  // it will set the m_bCreated flag to false 
  Float64 dTimeStamp = TTime::getTimeStamp();
  while(!bAbort && m_bCreated )
  {
    if(TTime::getTimeStamp()- dTimeStamp < dTimeOut)
    {
      TTime::sleep(0.1);
    }
    else
    {
      bAbort = true;
    }
  }
  return !bAbort;
}

/***************************************************************************/
/*! Starts the thread.
    \retval true: Thread created and successfully started
    \retval false: Could not start the thread (OS error)
*/
/***************************************************************************/
bool TThread::start()
{
  if (!m_bCreated)
  {
    m_bInterrupted = false;
    m_bCreated = true;
    
    ///////////////////////////////////////////////////////////////
    // DATA LOCK
    // Note: Its important to lock the access of m_uiThreadID
    // The thread will read this at the beginning to register
    // itself at the thread manager. Therefore it will need
    // a valid m_uiThreadID
    m_rDataLock.enter();
    
    #if defined(__GNUC__)
      int rc = ::pthread_create(&Thread, NULL,createThread, this);
      if (rc == 0)
      {
        m_bCreated = true;
        m_uiThreadID = Thread;

        //DO NOT DETACH THREAD.
        // Using the thread class inside Zeus-Framework, the thread it self
        // might access data form the Thread object (this). If the thread
        // is created detached, the object might be released by the
        // owner, without really termination the thread first. Therefor
        // the pthread_join is very important.
        //pthread_detach(Thread);
      }
      else
      {
        m_bCreated = false;
      }
    #else
      DWORD dwThreadId = 0;
      m_hHandle = ::CreateThread( NULL, 0, createThread, this, 0, &dwThreadId);

      if (m_hHandle != NULL)
      {
        m_bCreated = true;
        m_uiThreadID = dwThreadId;
      }
      else
      {
        m_bCreated = false;
      }
    #endif
    
    m_rDataLock.leave();
    // DATA LOCK END
    ///////////////////////////////////////////////////////////////

    setPriority(m_ePriority);
  }
  return m_bCreated;
}

/***************************************************************************/
/*! This stopps a thread. Using resume() the thread can be restarted
*/
/***************************************************************************/
void TThread::suspend()
{
  if (m_bCreated)
  {
    #if defined(__GNUC__)
    #else
      ::SuspendThread(m_hHandle);
      m_bSuspended = true;
    #endif
  }
}

/***************************************************************************/
/*! This starts a stopped thread.
*/
/***************************************************************************/
void TThread::resume()
{
  if (m_bCreated)
  {
    #if defined(__GNUC__)
    #else
      ::ResumeThread(m_hHandle);
      m_bSuspended= false;
    #endif
  }
}

/***************************************************************************/
/*! this method causes the OS to switch to an other thread (scheduling).
    \retval true : yield has been performed
    \retval false: could not yield thread
*/
/***************************************************************************/
bool TThread::yield()
{
  #if defined(__GNUC__)
    return (sched_yield() == 0);
  
  #elif _WIN32_WINNT >= 0x0400
    return ::SwitchToThread();
  
  #else 
    return false;
  
  #endif
}

/***************************************************************************/
/*! this sends a message to the queue of the thread
    \note This method could cause dead locks, if the thread is not started,
          but the bWaitForCompletion flag is set. Start the thread first
    \see IThreadManager::postObject
*/
/***************************************************************************/
Retval TThread::postObject(ISynchronizeObject& rObject,
                              bool bWaitForCompletion)
{
  Retval retValue = RET_REQUEST_FAILED;

  //////////////////////////////////////////
  // DATA LOCK
  m_rDataLock.enter();

  // Thread is running -> use thread manager
  if (m_bCreated)
  {
    retValue = ThreadManager.postObject(this->getThreadID(), rObject, bWaitForCompletion);
  }

  // thread is not running -> post the object directly into the message queue
  else
  {
    retValue = m_rQueue.postObject(rObject, bWaitForCompletion);
  }

  m_rDataLock.leave();
  //////////////////////////////////////////

  return retValue;
}


/***************************************************************************/
/*! This is the internal running method. Do not call this method directly
*/
/***************************************************************************/
void TThread::execute()
{
  if (m_pRunObj != NULL && m_bCreated == true)
  {
    m_pRunObj->execute();
  }
  else
  {
    //RootLogger.printfln(LOGMODE_WARN, "Method not implemented");
  }
}

/***************************************************************************/
/*! Internal clearance. All flag are reset.
*/
/***************************************************************************/
void TThread::terminate_internal()
{
  //////////////////////////////////////////
  // DATA LOCK
  m_rDataLock.enter();
  m_bCreated = false;
  m_rDataLock.leave();
  //////////////////////////////////////////
}


/***************************************************************************/
/*! \see IThread::getThreadID
*/
/***************************************************************************/
Uint MQUALIFIER TThread::getThreadID() const
{
  ///////////////////////////////////////////////////
  // DATA LOCK
  //Make sure the lock is available
  m_rDataLock.enter();
  Uint uiRetval = m_uiThreadID;
  m_rDataLock.leave();
  ///////////////////////////////////////////////////
  
  return uiRetval;
}

/**************************************************************************/
/*! Memory management
*/
/**************************************************************************/
MEMORY_MANAGER_IMPL(TThread);
  INTERFACE_CAST(IThread, INTERFACE_IThread);
MEMORY_MANAGER_IMPL_END;

