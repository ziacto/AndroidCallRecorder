/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : BorlandSynchronizeObject
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 20.02.07 10:19 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Platforms/BorlandSynchronizeObject.hpp $
** 
** 4     20.02.07 10:19 bha
** Ueberarbeiten von ICAST's
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef BorlandSynchronizeObjectH
#define BorlandSynchronizeObjectH
//---------------------------------------------------------------------------

#if defined(__BCPLUSPLUS__)

#include <zeusbase/System/CriticalSection.h>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This is a platform specific helper class for thread synchronizing on
    Borland C++ Builder
*/
/***************************************************************************/
class TBorlandSynchronizeObject : public TSynchronizeObject
{
  public:
    ///Definition of a call back Method
    typedef void __fastcall (__closure *TSynchEvent)(void);

    /************************************************************************/
    /*! Creates a synchronize object
        \param pEvent : Call back method
    */
    /************************************************************************/
    TBorlandSynchronizeObject(TSynchEvent pEvent)
    {
      m_pEvent = pEvent;
    }

    /************************************************************************/
    /*! This method is used to check for errors and reset the call back
         method
    */
    /************************************************************************/
    void checkForError()
    {
      ///////////////////////////////////////////////////////////////////////
      m_rLock.enter();
      if (this->hasError())
      {
        m_pEvent = NULL;
      }
      m_rLock.leave();
      ///////////////////////////////////////////////////////////////////////
    }

    /************************************************************************/
    /*! \see ISynchronizeObject::process
    */
    /************************************************************************/
    virtual void MQUALIFIER process()
    {
      ///////////////////////////////////////////////////////////////////////
      m_rLock.enter();
      if (m_pEvent != NULL)
      {
        m_pEvent();
      }
      m_rLock.leave();
      ///////////////////////////////////////////////////////////////////////
    }

  protected:
    /************************************************************************/
    /*! Destructs a synchronize object
    */
    /************************************************************************/
    virtual ~TBorlandSynchronizeObject()
    {}

  private:
    ///call back Method
    TSynchEvent m_pEvent;
};

END_NAMESPACE_Zeus

#endif //defined(__BCPLUSPLUS__)

#endif