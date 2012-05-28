/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus                                                          
 * Module  : Event
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 17:21 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Event.cpp $
** 
** 16    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 15    20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
** 
** 12    2.10.06 9:20 bha
** Implementation for Linux
** 
** 11    14.09.06 14:58 bha
** definieren von portablen primitiven Datentypen
***************************************************************************/

#include <zeusbase/System/Event.h>
#include <zeusbase/System/Time.h>
#include <zeusbase/System/ThreadManager.h>

#if defined(__GNUC__)
  #include <stdio.h>
  #include <errno.h>
  #include <sys/time.h>
#elif defined(__BCPLUSPLUS__)

#endif

USING_NAMESPACE_Zeus

/***************************************************************************/
/*! Creates a new event
*/
/***************************************************************************/
TEvent::TEvent(EWaitType eType /*= etBlocked*/)
 : TZObject()
{
  m_eType = eType;

  #if defined(__GNUC__)
    pthread_mutex_init(&m_Mutex, NULL);
    pthread_cond_init(&m_CondVar, NULL);
    m_bSet = false;
  #else
    m_hHandle = ::CreateEvent(NULL, true, false, NULL);
  #endif
}

/***************************************************************************/
/*! Destroys the event
*/
/***************************************************************************/
TEvent::~TEvent()
{
  #if defined(__GNUC__)
    pthread_cond_destroy(&m_CondVar);
    pthread_mutex_destroy(&m_Mutex);
  #else
    ::CloseHandle(m_hHandle);
  #endif
}

/***************************************************************************/
/*! set signal
*/
/***************************************************************************/
void TEvent::set()
{
  #if defined(__GNUC__)
    pthread_mutex_lock(&m_Mutex);
    m_bSet = true;
    
    // signal all threads to wake up
    pthread_cond_broadcast(&m_CondVar);
    pthread_mutex_unlock(&m_Mutex);
  #else
    ::SetEvent(m_hHandle);
  #endif
}

/***************************************************************************/
/*! reset the event
*/
/***************************************************************************/
void TEvent::reset()
{
  #if defined(__GNUC__)
    m_bSet = false;
  #else
    ::ResetEvent(m_hHandle);
  #endif
}



/***************************************************************************/
/*! Wait for a signalification
    \param dSeconds : time to wait.
*/
/***************************************************************************/
bool TEvent::wait(Float64 dSeconds)
{
  bool bRetval = false;

  #if defined(__GNUC__)  
  
    Uint uiThreadID = ThreadManager.getCurrentThreadID();

    /////////////////////////////////
    //set clean up routine
    // The clean up is needed to release lock of the event
    pthread_cleanup_push(TEvent::cleanup, this);
    pthread_mutex_lock(&m_Mutex);    
    
    Float64 dTimeStamp = TTime::getTimeStamp();
    Float64 dTimeStamp2 = TTime::getTimeStamp();
    bool bNotified = m_bSet;
    while(!bNotified && 
          !ThreadManager.isThreadInterrupted(uiThreadID) &&
          dTimeStamp2 - dTimeStamp < dSeconds)
    {
      bNotified = wait_internal();
      dTimeStamp2 = TTime::getTimeStamp();
    }
    
    bRetval = bNotified;

    pthread_mutex_unlock(&m_Mutex);
    pthread_cleanup_pop(0);   //do not execute handler
    /////////////////////////////////
  

  #else
    if (m_eType == etBlocked)
    {
      DWORD dwRet = ::WaitForSingleObjectEx(m_hHandle, (Uint32)(dSeconds*1000), true);
      bRetval = (dwRet == WAIT_OBJECT_0);
    }
    else if (m_eType == etActive)
    {
      bRetval = waitForActiveObject((unsigned long) (dSeconds*1000));
    }
  #endif

  return bRetval;
}


/***************************************************************************/
/*! Wait for a signalification. The time out if infinite
*/
/***************************************************************************/
bool TEvent::waitInfinite()
{
  bool bRetval = false;

  #if defined(__GNUC__)
    
    Uint uiThreadID = ThreadManager.getCurrentThreadID();

    /////////////////////////////////
    //set clean up routine
    // The clean up is needed to release lock of the event
    pthread_cleanup_push(TEvent::cleanup, this);
    pthread_mutex_lock(&m_Mutex);
    
    bool bNotified = m_bSet;
    while(!bNotified &&
          !ThreadManager.isThreadInterrupted(uiThreadID))
    {
      bNotified = wait_internal();
    }
    bRetval = bNotified;

    pthread_mutex_unlock(&m_Mutex);
    
    pthread_cleanup_pop(0);   //do not execute handler
    /////////////////////////////////
  
  #else
    if (m_eType == etBlocked)
    {
      DWORD dwRet = ::WaitForSingleObjectEx(m_hHandle, INFINITE, true);
      bRetval = (dwRet == WAIT_OBJECT_0);
    }
    else if (m_eType == etActive)
    {
      bRetval = waitForActiveObject(INFINITE);
    }
  #endif

  return bRetval;
}

//##########################################################################
// PLATFORM DEPENDED METHDOS

#if defined(__GNUC__)
/***************************************************************************/
/*! clean up if the thread must be canceled or terminated
*/
/***************************************************************************/
/*static*/ void TEvent::cleanup(void* pPtr)
{
  if (pPtr != NULL)
  {
    TEvent& rEvent = *((TEvent*)pPtr);
    pthread_mutex_unlock(&rEvent.m_Mutex);
  }
}

/***************************************************************************/
/*! Internal waiting method. This waits 0.01 seconds and returns true
    if the signal has been set
*/
/***************************************************************************/
bool TEvent::wait_internal()
{
  struct timespec TimeOut;
  struct timeval Now;
  gettimeofday(&Now, NULL);
  TimeOut.tv_sec = Now.tv_sec + 0;
  TimeOut.tv_nsec = Now.tv_usec * 1000 + 10000000;
  
  int iRet = pthread_cond_timedwait(&m_CondVar, &m_Mutex, &TimeOut);

  ///////////////////////////////////////
  //Test of return value
  /*
  if (iRet == EINTR)
  {
    printf("Cont wait returned [EINTR]\n");
  }
  else if (iRet == ETIMEDOUT)
  {
    printf("Cont wait returned [ETIMEDOUT]\n");
  }
  */
  ///////////////////////////////////////

  return (iRet != ETIMEDOUT);
}


#endif

#ifdef WIN32
/***************************************************************************/
/*! internal method for waiting for an event handle. This method
    implements an active waiting
*/
/***************************************************************************/
bool TEvent::waitForActiveObject(Uint uiTimeOut)
{
  Int iState = 0;
  Uint64 udlTimeStampMilli = TTime::getTickCount()/1000;
  Uint64 udlTime = 0;
  while (iState == 0 && udlTime < uiTimeOut)
  {
    DWORD dwRet = ::MsgWaitForMultipleObjectsEx(1, &m_hHandle, uiTimeOut, QS_ALLINPUT, MWMO_ALERTABLE);
    switch(dwRet)
    {
      case WAIT_OBJECT_0 :
        iState = 1;
      break;

      case WAIT_OBJECT_0+1 :
      {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
          // If it's a quit message, we're out of here.
          if (msg.message == WM_QUIT)
          {
            iState = 2;
          }
          else
          {
            // Otherwise, dispatch the message.
            ::DispatchMessage(&msg);
          }
        } // End of PeekMessage while loop.
      }
      break;

      default:
        iState = 2;
      break;
    }
    TTime::sleep(0.001);
    udlTime = TTime::getTickCount()/1000 - udlTimeStampMilli;
  }

  return (iState == 1);
}
#endif

