/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : SynchronizeObject
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/SynchronizeObject.cpp $
** 
** 3     20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
***************************************************************************/

//---------------------------------------------------------------------------



#include <zeusbase/System/SynchronizeObject.h>
#include <zeusbase/System/CriticalSection.h>
#include <zeusbase/System/Event.h>

//---------------------------------------------------------------------------
USING_NAMESPACE_Zeus

/****************************************************************************/
/*! Creates a simple synchronizing object
*/
/****************************************************************************/
TSynchronizeObject::TSynchronizeObject()
 : TZObject(),
   m_rLock(*new TCriticalSection()),
   m_rEvent(*new TEvent())
{
  m_bError = false;
}

/****************************************************************************/
/*! Destroys the simple synchronizing object
*/
/****************************************************************************/
TSynchronizeObject::~TSynchronizeObject()
{
  m_rEvent.release();
  m_rLock.release();
}

/****************************************************************************/
/*! \see ISynchronizeObject::waitForCompletion
*/
/****************************************************************************/
bool MQUALIFIER TSynchronizeObject::waitForCompletion()
{
  bool bRetval = m_rEvent.waitInfinite();

  ////////////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  m_bError |= !bRetval;  //if an error has been set before -> keep information
  m_rLock.leave();
  ////////////////////////////////////////////////////////////////////////////

  return !m_bError;
}

/****************************************************************************/
/*! \see ISynchronizeObject::notifyCompletion
*/
/****************************************************************************/
void MQUALIFIER TSynchronizeObject::notifyCompletion(bool bOK)
{
  ////////////////////////////////////////////////////////////////////////////
  m_rLock.enter();
  m_bError |= !bOK;  //if an error has been set before -> keep information
  m_rLock.leave();
  ////////////////////////////////////////////////////////////////////////////

  m_rEvent.set();
}

/****************************************************************************/
/*! Memory management
*/
/****************************************************************************/
MEMORY_MANAGER_IMPL_LOCK(TSynchronizeObject, &m_rLock)
  INTERFACE_CAST(ISynchronizeObject, INTERFACE_ISynchronizeObject);
MEMORY_MANAGER_IMPL_END;

