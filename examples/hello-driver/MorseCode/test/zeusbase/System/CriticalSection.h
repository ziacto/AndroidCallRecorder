/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : CriticalSection
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/CriticalSection.h $
** 
** 9     23.04.08 16:24 Bha
** windows includes depending on the usage flag
** 
** 8     26.02.07 9:00 bha
***************************************************************************/

#ifndef CriticalSectionH
#define CriticalSectionH

#include <zeusbase/System/Interfaces/ICriticalSection.hpp>
#include <zeusbase/System/ZObject.h>

#if defined(__GNUC__)
  #include <pthread.h>
#else

  #if defined(USE_WINDOWS_H)
    #include <windows.h>
  #endif

#endif

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This class implements a critical section (mutex) for multithreading
*/
/***************************************************************************/
zeusbase_class TCriticalSection : public TZObject, public ICriticalSection
{
  public:
    enum TLockType {ltFast, ltRecursive, ltError};
    TCriticalSection(TLockType type = ltFast);

    bool isLocked();

    //Methods of ICriticalSection
    virtual void MQUALIFIER enter();
    virtual void MQUALIFIER leave();

    //Methods of IZUnknown
    MEMORY_MANAGER_DECL

  protected:
    virtual ~TCriticalSection();

  private:
    ///Counter
    Int m_iCount;

    #if defined(__GNUC__)
      ///Mutex
      pthread_mutex_t m_Mutex;
      ///Mutex attribute
      pthread_mutexattr_t m_Attribute;
    #else
      CRITICAL_SECTION m_CriticalSection;
    #endif
};

END_NAMESPACE_Zeus

#endif
