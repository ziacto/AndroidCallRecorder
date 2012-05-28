/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ThreadMessageQueue
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 7:04 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/ThreadMessageQueue.cpp $
** 
** 7     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 6     11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
** 
** 1     2.10.06 9:21 bha
** Thread management on Linux and Win32
***************************************************************************/

#include <zeusbase/System/ThreadMessageQueue.h>
#include <zeusbase/System/CriticalSection.h>

USING_NAMESPACE_Zeus 

/**************************************************************************/
/*! Creates a message queue
*/
/**************************************************************************/
TThreadMessageQueue::TThreadMessageQueue()
 : TZObject(),
   m_rLock(*new TCriticalSection(TCriticalSection::ltRecursive))
{
  m_bLocked = false;
}


/**************************************************************************/
/*! Destroys the message queue
*/
/**************************************************************************/
TThreadMessageQueue::~TThreadMessageQueue()
{
  m_bLocked = true;
  flush();
  m_rLock.release();
}


/**************************************************************************/
/*! \see IThreadMessageQueue::flush
*/
/**************************************************************************/
void MQUALIFIER TThreadMessageQueue::flush()
{
  ///////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  while(!m_lstQueue.isEmpty())
  {
    TItemContainer* pItem = m_lstQueue.removeItem();

    //Error because not synchronized
    ISynchronizeObject& rObject = pItem->getObject();
    rObject.notifyCompletion(false);

    pItem->release();
  }
  m_lstQueue.flush();
  m_rLock.leave();
  ///////////////////////////////////////////////////////////////////////
}

/**************************************************************************/
/*! \see IThreadMessageQueue::processObject
    This method is called by the owner thread.
*/
/**************************************************************************/
Retval MQUALIFIER TThreadMessageQueue::processObject()
{
  Retval retValue = RET_REQUEST_FAILED;
  ///////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  TItemContainer* pItem = m_lstQueue.removeItem();
  m_rLock.leave();
  ///////////////////////////////////////////////////////////////////////


  if (pItem != NULL)
  {
    ISynchronizeObject& rObject = pItem->getObject();
    rObject.process();
    rObject.notifyCompletion(true);
    pItem->release();
    retValue = RET_NOERROR;
  }
  return retValue;
}

/**************************************************************************/
/*! \see IThreadMessageQueue::postObject
*/
/**************************************************************************/
Retval MQUALIFIER TThreadMessageQueue::postObject(ISynchronizeObject& rObject, bool bWaitForCompletion)
{
  Retval retValue = RET_NOERROR;

  ///////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  if (!m_bLocked)
  {
    //event method for sub classes
    onItemPosted(rObject, bWaitForCompletion);

    TItemContainer* pItem = new TItemContainer(rObject, bWaitForCompletion);
    m_lstQueue.appendItem(pItem);
    m_rLock.leave();
    ///////////////////////////////////////////////////////////////////////

    if (bWaitForCompletion)
    {
      if (!rObject.waitForCompletion())
      {
        retValue = RET_REQUEST_FAILED;
      }
    }
  }
  else
  {
    m_rLock.leave();
    ///////////////////////////////////////////////////////////////////////

    retValue = RET_REQUEST_FAILED;
  }
  return retValue;
}

/**************************************************************************/
/*! \see IThreadMessageQueue::lock
*/
/**************************************************************************/
void MQUALIFIER TThreadMessageQueue::lock()
{
  ///////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  m_bLocked = true;
  m_rLock.leave();
  ///////////////////////////////////////////////////////////////////////
}

/**************************************************************************/
/*! \see IThreadMessageQueue::lock
*/
/**************************************************************************/
void MQUALIFIER TThreadMessageQueue::unlock()
{
  ///////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  m_bLocked = false;
  m_rLock.leave();
  ///////////////////////////////////////////////////////////////////////
}

/**************************************************************************/
/*! \see IThreadMessageQueue::lock
*/
/**************************************************************************/
bool MQUALIFIER TThreadMessageQueue::isEmpty() const
{
  ///////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  bool bRetval = m_lstQueue.isEmpty();
  m_rLock.leave();
  ///////////////////////////////////////////////////////////////////////

  return bRetval;
}

/**************************************************************************/
/*! Memory management
*/
/**************************************************************************/
MEMORY_MANAGER_IMPL_LOCK(TThreadMessageQueue, &m_rLock);
  INTERFACE_CAST(IThreadMessageQueue, INTERFACE_IThreadMessageQueue);
MEMORY_MANAGER_IMPL_END;


