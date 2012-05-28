/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : CriticalSection
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/CriticalSection.cpp $
** 
** 8     20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
***************************************************************************/

 
#include <zeusbase/System/CriticalSection.h>

#if defined(__GNUC__)
  #include <errno.h>
#else
  #include <windows.h>
#endif


USING_NAMESPACE_Zeus

/**************************************************************************/
/*! Creates a critical section object
*/
/**************************************************************************/
TCriticalSection::TCriticalSection(TLockType type /*= ltFast*/) : TZObject()
{
  #if defined(__GNUC__)
    ::pthread_mutexattr_init(&m_Attribute);
    
    switch(type)
    {
      case ltError : 
        ::pthread_mutexattr_settype(&m_Attribute, PTHREAD_MUTEX_ERRORCHECK_NP);
      break;
      
      case ltRecursive:
        ::pthread_mutexattr_settype(&m_Attribute, PTHREAD_MUTEX_RECURSIVE_NP);
      break;
      
      case ltFast :
      default:      //fall through
        ::pthread_mutexattr_settype(&m_Attribute, PTHREAD_MUTEX_FAST_NP);
      break;
    }
    ::pthread_mutex_init(&m_Mutex, &m_Attribute);
  #else
    switch(type)
    {
      case ltRecursive:
      case ltError ://fall through 
      case ltFast : //fall through
      default:      //fall through
        ::InitializeCriticalSection(&m_CriticalSection);
      break;
    }
  #endif

  m_iCount = 0;
}


/**************************************************************************/
/*! Destroys a critical section object
*/
/**************************************************************************/
TCriticalSection::~TCriticalSection()
{
  //Only checking if the mutex is unlocked
  #if defined(__GNUC__)
    ::pthread_mutexattr_destroy(&m_Attribute);
    ::pthread_mutex_destroy(&m_Mutex);
  #else
    ::DeleteCriticalSection(&m_CriticalSection);
  #endif
}

/**************************************************************************/
/*! Enters the lock
*/
/**************************************************************************/
void MQUALIFIER TCriticalSection::enter()
{
  #if defined(__GNUC__)
    ::pthread_mutex_lock(&m_Mutex);
  #else
    ::EnterCriticalSection(&m_CriticalSection);
  #endif

  m_iCount++;
  //TLogger::getLogger().printfln(m_iCount);
}


/**************************************************************************/
/*! Leaves the lock
*/
/**************************************************************************/
void MQUALIFIER TCriticalSection::leave()
{
  m_iCount--;
  //TLogger::getLogger().printfln(m_iCount);
  #if defined(__GNUC__)
    ::pthread_mutex_unlock(&m_Mutex);
  #else
    ::LeaveCriticalSection(&m_CriticalSection);
  #endif
}


/**************************************************************************/
/*! Checks if the lock is active.
    \retval true : active (an other thread is using the lock)
    \retval false : lock is free
*/
/**************************************************************************/
bool TCriticalSection::isLocked()
{
  #if defined(__GNUC__)
    bool bRetval = (::pthread_mutex_trylock(&m_Mutex) == EBUSY);
  #else
    #ifdef _MSC_VER
      bool bRetval = false;
    #else
      bool bRetval = TryEnterCriticalSection(&m_CriticalSection);
    #endif
  #endif

  return bRetval;
}


/**************************************************************************/
/*! Memory Management
*/
/**************************************************************************/
MEMORY_MANAGER_IMPL(TCriticalSection);
MEMORY_MANAGER_IMPL_END;

