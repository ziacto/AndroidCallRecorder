/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : SynchronizeObjectDelegater
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Platforms/SynchronizeObjectDelegater.hpp $
** 
** 4     20.02.07 10:19 bha
** Ueberarbeiten von ICAST's
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef SynchronizeObjectDelegaterHPP
#define SynchronizeObjectDelegaterHPP

#include <zeusbase/System/SynchronizeObject.h>
#include <zeusbase/System/CriticalSection.h>

BEGIN_NAMESPACE_Zeus

/****************************************************************************/
/*! This class is used to synchronize a method of a class
*/
/****************************************************************************/
template <class T> class TSynchronizeObjectDelegater : public TSynchronizeObject
{
  public:
    typedef void (MQUALIFIER T::*ProcessMethod)();

    /************************************************************************/
    /*! Creates a delagtion object to synchronize an object method
    */
    /************************************************************************/
    TSynchronizeObjectDelegater(T& rThis, ProcessMethod pMethod)
     : TSynchronizeObject()
    {
      m_pThis = &rThis;
      m_pMethod = pMethod;
    }

    /************************************************************************/
    /*! This method is used to check for errors and clears the delegation
    */
    /************************************************************************/
    void checkForError()
    {
      m_rLock.enter();
      if (this->hasError())
      {
        m_pThis = NULL;
      }
      m_rLock.leave();
    }

    /************************************************************************/
    /*! \see IsynchronizeObject::process
    */
    /************************************************************************/
    virtual void MQUALIFIER process()
    {
      m_rLock.enter();
      if (m_pThis != NULL)
      {
        (*m_pThis.*(m_pMethod))();
      }
      m_rLock.leave();
    }
  protected:

  private:
    //This pointer of the delegation
    T * m_pThis;
    //Method pointer of the delegation
    ProcessMethod  m_pMethod;
};

END_NAMESPACE_Zeus

#endif

