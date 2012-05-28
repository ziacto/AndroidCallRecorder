/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Event
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 26.02.07 9:00 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Event.h $
** 
** 13    26.02.07 9:00 bha
**
** 9     2.10.06 9:20 bha
** Implementation for Linux
***************************************************************************/


#ifndef EventH
#define EventH

#include <zeusbase/System/ZObject.h>

#if defined(__GNUC__)
  #include <pthread.h>
#else
  #include <windows.h>
#endif

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This class implements a event to signal a thread
*/
/***************************************************************************/
zeusbase_class TEvent : public TZObject
{
  public:
    enum EWaitType
    {
      etBlocked = 0,
      etActive = 1
    };


    TEvent(EWaitType eType = etBlocked);
    virtual ~TEvent();

    void set();
    void reset();
    bool wait(Float64 dSeconds = 10.0);
    bool waitInfinite();

  private :
    //Type of the event
    EWaitType m_eType;

  #if defined(__GNUC__)
    //Mutex
    pthread_mutex_t m_Mutex;
    //condition (event)
    pthread_cond_t m_CondVar;
    //Flag if the event is set
    bool m_bSet;

    bool wait_internal();
    static void cleanup(void* pPtr);

  #else
    ///Handle of event
    HANDLE m_hHandle;
    bool waitForActiveObject(Uint uiTimeOut);
  #endif
};

END_NAMESPACE_Zeus

#endif
