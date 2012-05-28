/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : ThreadManager
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 14.03.08 11:21 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/ThreadManager.cpp $
** 
** 9     14.03.08 11:21 Bha
** Set CPU affinity mask (just CPU0) if requested by define
** 
** 8     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 2     28.11.06 16:31 bha
** Beheben von Compilerwarnungen
** 
** 1     2.10.06 9:21 bha
** Thread management on Linux and Win32
***************************************************************************/

#include <zeusbase/System/ThreadManager.h>
#include <zeusbase/System/Interfaces/IThreadMessageQueue.hpp>
#include <zeusbase/System/CriticalSection.h>

#if defined(__GNUC__)
  #include <pthread.h>
#else
  #include <windows.h>
#endif

 
USING_NAMESPACE_Zeus

#if defined(ENABLE_WIN32_BINDING)
  //Initialisation of the singleton object
  TAutoPtr<TThreadManager> TThreadManager::m_ptrInstance = NULL;
#else
  TAutoPtr<TThreadManager> TThreadManager::m_ptrInstance = new TThreadManager();
#endif

/**************************************************************************/
/*! Returns the singleton object
*/
/**************************************************************************/
/*static*/ TThreadManager& TThreadManager::getInstance()
{
  #if defined(ENABLE_WIN32_BINDING)
    if (m_ptrInstance == NULL)
    {
      m_ptrInstance = new TThreadManager();
    }
  #endif
  return *m_ptrInstance;
}

/**************************************************************************/
/*! Creates the singleton object
*/
/**************************************************************************/
TThreadManager::TThreadManager() 
 : TZObject(),
   m_rMapLock(*new TCriticalSection()),
   m_rDelegationLock(*new TCriticalSection(TCriticalSection::ltRecursive))
{
  #if defined(ENABLE_WIN32_BINDING) && defined(DISABLE_MULTI_PROCESSOR)
    //Set CPU affinity mask (just CPU0)
    unsigned long ulCPUAffinityMask = 1;
    ::SetProcessAffinityMask(::GetCurrentProcess(), ulCPUAffinityMask);
  #endif

  m_pDelegation = NULL;
  //current thread is not interrupted
  m_uiMainThreadID = getCurrentThreadID();
  this->setThreadState(m_uiMainThreadID, false);
}

/**************************************************************************/
/*! Destroys the singleton object
*/
/**************************************************************************/
TThreadManager::~TThreadManager()
{
  releaseDelegationInterface();
  
  ////////////////////////////////////////////////////////////////
  // MAP LOCK ENTER
  m_rMapLock.enter();
  TIterator<IThreadMessageQueue*> It = m_mapQueues.getIterator();
  while(It.hasNextItem())
  {
    It.getNextItem()->release();
  }
  It = NULL;
  m_mapQueues.clear();
  m_rMapLock.leave();
  // MAP LOCK LEAVE
  ////////////////////////////////////////////////////////////////

  m_rMapLock.release();
  m_rDelegationLock.release();
}

/**************************************************************************/
/*! sets a delegation interface
*/
/**************************************************************************/
void TThreadManager::setDelegationInterface(IThreadManager& rInstance)
{
  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();

  releaseDelegationInterface();  //needs a recursive lock
  if (&rInstance != this)
  {
    m_pDelegation = &rInstance;
    m_pDelegation->addRef();
  }

  m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////
}


/**************************************************************************/
/*! Releases the delegation
*/
/**************************************************************************/
void TThreadManager::releaseDelegationInterface()
{
  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    m_pDelegation->release();
    m_pDelegation = NULL;
  }
  m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////
}

/**************************************************************************/
/*! \see IThreadManager::addThread
*/
/**************************************************************************/
void MQUALIFIER TThreadManager::addThread(Uint uiID, IThreadMessageQueue& rQueue, bool bInterrupted)
{
  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    m_pDelegation->addThread(uiID, rQueue, bInterrupted);
    m_rDelegationLock.leave();
  }
  else 
  {
    m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////

    if (m_mapQueues.hasItem(uiID))
    {
      removeThread(uiID);
    }
    
    ////////////////////////////////////////////////////////////////
    // MAP LOCK ENTER
    m_rMapLock.enter();
    m_mapQueues.setItem(uiID, &rQueue);
    rQueue.addRef();
    m_mapThreads.setItem(uiID, bInterrupted);
    m_rMapLock.leave();
    // MAP LOCK LEAVE
    ////////////////////////////////////////////////////////////////
  }
}

/**************************************************************************/
/*! \see IThreadManager::getCurrentThreadID
*/
/**************************************************************************/
Uint MQUALIFIER TThreadManager::getCurrentThreadID() const
{
  Uint uiRetval = 0;

  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    uiRetval = m_pDelegation->getCurrentThreadID();
    m_rDelegationLock.leave();
  }
  else
  {
    m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////


  #if defined(__GNUC__)
    uiRetval = pthread_self();
  #else
    uiRetval = ::GetCurrentThreadId();
  #endif
  
  }
  return uiRetval;
}


/**************************************************************************/
/*! \see IThreadManager::getMessageQueue
*/
/**************************************************************************/
Retval MQUALIFIER TThreadManager::getMessageQueue(Uint uiThreadID, IThreadMessageQueue*& rpQueue)
{
  Retval retValue = RET_REQUEST_FAILED;

  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    retValue = m_pDelegation->getMessageQueue(uiThreadID, rpQueue);
    m_rDelegationLock.leave();
  }
  else
  {
    m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////
    // MAP LOCK ENTER
    m_rMapLock.enter();
    rpQueue = m_mapQueues.getItem(uiThreadID);
    if (rpQueue != NULL)
    {
      rpQueue->addRef();
      retValue = RET_NOERROR;
    }
    m_rMapLock.leave();
    // MAP LOCK LEAVE
    ////////////////////////////////////////////////////////////////
  }
  
  return retValue;
}


/**************************************************************************/
/*! \see IThreadManager::getCurrentThreadID
*/
/**************************************************************************/
bool MQUALIFIER TThreadManager::isThreadInterrupted(Uint uiID)const
{
  bool bRetval = true;

  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    bRetval = m_pDelegation->isThreadInterrupted(uiID);
    m_rDelegationLock.leave();
  }
  else
  {
    m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////

    if (uiID != 0)
    {
      ////////////////////////////////////////////////////////////////
      // MAP LOCK ENTER
      m_rMapLock.enter();
      bRetval = m_mapThreads.getItemConst(uiID);
      m_rMapLock.leave();
      // MAP LOCK LEAVE
      ////////////////////////////////////////////////////////////////
    }
  } 
  return bRetval;
}

/**************************************************************************/
/*! \see IThreadManager::removeThread
*/
/**************************************************************************/
void MQUALIFIER TThreadManager::removeThread(Uint uiID)
{
  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    m_pDelegation->removeThread(uiID);
    m_rDelegationLock.leave();
  }
  else
  {
    m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    // MAP LOCK ENTER
    m_rMapLock.enter();
    IThreadMessageQueue* pItem = m_mapQueues.getItem(uiID);
    if (pItem != NULL)
    {
      pItem->release();
    }
    m_mapQueues.deleteItem(uiID);
    
    m_mapThreads.deleteItem(uiID);
    m_rMapLock.leave();
    // MAP LOCK LEAVE
    ////////////////////////////////////////////////////////////////
  }
}

/**************************************************************************/
/*! \see IThreadManager::getCurrentThreadID
*/
/**************************************************************************/
void MQUALIFIER TThreadManager::setThreadState(Uint uiID, bool bInterrupted)
{
  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    m_pDelegation->setThreadState(uiID, bInterrupted);
    m_rDelegationLock.leave();
  }
  else
  {
    m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    // MAP LOCK ENTER
    m_rMapLock.enter();
    if(m_mapThreads.hasItem(uiID))
    {
      m_mapThreads.setItem(uiID, bInterrupted);
    }
    m_rMapLock.leave();
    // MAP LOCK LEAVE
    ////////////////////////////////////////////////////////////////
  }
}

/****************************************************************************/
/*! \see IThreadManager::getMainThreadID
*/
/****************************************************************************/
Uint MQUALIFIER TThreadManager::getMainThreadID() const
{
  Uint uiRetval = m_uiMainThreadID;

  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    uiRetval = m_pDelegation->getMainThreadID();
  }
  m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////

  return uiRetval;
}


/**************************************************************************/
/*! \see IThreadManager::postObject
*/
/**************************************************************************/
Retval MQUALIFIER TThreadManager::postObject(Uint uiThreadID,
                                                    ISynchronizeObject& rObject,
                                                    bool bWaitForCompletion)
{
  Retval retValue = RET_REQUEST_FAILED;

  ////////////////////////////////////////////////////////////////
  // DELEGATION LOCK ENTER
  m_rDelegationLock.enter();
  if (m_pDelegation != NULL)
  {
    retValue = m_pDelegation->postObject(uiThreadID, rObject, bWaitForCompletion);
    m_rDelegationLock.leave();
  }
  else
  {
    m_rDelegationLock.leave();
  // DELEGATION LOCK LEAVE
  ////////////////////////////////////////////////////////////////

    //If the the target thread is the current thread and wait for
    //completion is set
    //  -> run the synch process directly
    if (this->isCurrentThread(uiThreadID) &&  bWaitForCompletion)
    {
      rObject.process();
      rObject.notifyCompletion(true);
    }

    //The target thread is not the calling thread or the wait for completion
    //is not set
    // -> post the message object to the queue of the target thread
    else
    {
      TAutoPtr<IThreadMessageQueue> ptrMessageQueue = NULL;
      if (this->getMessageQueue(uiThreadID, ptrMessageQueue) == RET_NOERROR)
      {
        retValue = ptrMessageQueue->postObject(rObject, bWaitForCompletion);
      }
    }
  }
  return retValue;
}

/**************************************************************************/
/*! Memory management
*/
/**************************************************************************/
MEMORY_MANAGER_IMPL_LOCK(TThreadManager, &m_rDelegationLock);
  INTERFACE_CAST(IThreadManager, INTERFACE_IThreadManager);
MEMORY_MANAGER_IMPL_END;

