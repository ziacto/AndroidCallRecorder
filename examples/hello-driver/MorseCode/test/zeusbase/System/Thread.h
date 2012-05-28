/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Thread
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 23.04.08 16:24 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Thread.h $
** 
** 15    23.04.08 16:24 Bha
** windows includes depending on the usage flag
** 
** 14    26.02.07 9:00 bha
**
** 8     2.10.06 9:21 bha
** Killing and stopping of blocked threads on Linux and Win32
***************************************************************************/

#ifndef ThreadH
#define ThreadH

#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/Interfaces/IRunnable.hpp>
#include <zeusbase/System/Interfaces/IThread.hpp>

#if defined(__GNUC__)
  #include <pthread.h>
#else
  #if defined(USE_WINDOWS_H)
    #include <windows.h>
  #endif
#endif


BEGIN_NAMESPACE_Zeus

class TThreadMessageQueue;
class TCriticalSection;
class ISynchronizeObject;

/***************************************************************************/
/*! Diese Klasse kapselt einen Thread. Der Thread wird in der Methode
    execute() taetig
*/
/***************************************************************************/
zeusbase_class TThread : public TZObject, public IThread
{
  public:
    /***********************************************************************/
    /*! Thread priority
    */
    /***********************************************************************/
    enum EPriority
    {
      etNormal = 0,
      etLow = 1,
      etHigh = 2,
      etLower = 3,
      etHigher = 4,
      etTimeCritical = 5
    };

    TThread(EPriority ePriority = etNormal);
    TThread(IRunnable& rObj, EPriority ePriority = etNormal);


    EPriority getPriority() const;
    void setPriority(EPriority ePriority);

    virtual void kill(Float64 dTimeOut=0);
    virtual bool isDead() const;
    virtual void resume();
    virtual bool signalizeStop(Float64 dTimeOut=5.0);
    virtual bool start();
    virtual void suspend();
    virtual bool yield();
    virtual Retval postObject(ISynchronizeObject& rObject,
                              bool bWaitForCompletion);

    //Methods of IThread
    virtual bool MQUALIFIER isInterrupted() const;
    virtual Uint MQUALIFIER getThreadID() const;

    //Methods of IZUnknown
    MEMORY_MANAGER_DECL

  protected:
    ///Abbruchflag fuer Thread
    bool m_bInterrupted;
    ///Message queue of the thread
    TThreadMessageQueue& m_rQueue;

    virtual ~TThread();
    virtual void execute();
    virtual void onTerminated() {}
    virtual void onStarted() {}

  private:
    void terminate_internal();
    ///Flag gibt an ob der Thread erstellt wurde
    bool m_bCreated;
    ///suspended flag
    bool m_bSuspended;
    ///Runable Interface
    IRunnable* m_pRunObj;
    ///Priority
    EPriority m_ePriority;
    ///Thread ID
    Uint m_uiThreadID;
    //Lock for ThreadID
    TCriticalSection& m_rDataLock;


    #if defined(__GNUC__)
      ///Thread
      pthread_t Thread;

      static void* createThread(void* life);
    #else
      //Thread handle
      HANDLE m_hHandle;
      static Uint32 __stdcall createThread(void* pLife);

      #if _WIN32_WINNT >= 0x0400
        static void CALLBACK doUserAPCProc(DWORD dwParam);
      #endif
    #endif
};

//INLINE

/***************************************************************************/
/*! Pruefen ob der Thread noch existiert
    \retval true : Der Thread existiert nicht mehr
    \retval false : Der Thread existiert noch
*/
/***************************************************************************/
inline bool TThread::isDead() const
{
  return !m_bCreated;
}

/***************************************************************************/
/*! \see IThread::isInterrupted
*/
/***************************************************************************/
inline bool MQUALIFIER TThread::isInterrupted() const
{
  return m_bInterrupted;
}

/***************************************************************************/
/*! returns the priority of the thread
*/
/***************************************************************************/
inline TThread::EPriority TThread::getPriority() const
{
  return m_ePriority;
}



END_NAMESPACE_Zeus

#endif
