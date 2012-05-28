/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : SynchronizeObject
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/SynchronizeObject.h $
** 
** 5     26.02.07 9:00 bha
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef SynchronizeObjectH
#define SynchronizeObjectH


#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/Interfaces/ISynchronizeObject.hpp>

BEGIN_NAMESPACE_Zeus

class TEvent;
class TCriticalSection;

//---------------------------------------------------------------------------
/****************************************************************************/
/*! This is the implementation of a simple synchronizing object
*/
/****************************************************************************/
zeusbase_class TSynchronizeObject : public TZObject, public ISynchronizeObject
{
  public:
    TSynchronizeObject();

    //Methods of ISynchronizeObject
    virtual void MQUALIFIER process()=0;
    virtual bool MQUALIFIER waitForCompletion();
    virtual void MQUALIFIER notifyCompletion(bool bOK);
    virtual bool MQUALIFIER hasError() const;

    //Methods of IZUnknown
    MEMORY_MANAGER_DECL

  protected:
    virtual ~TSynchronizeObject();

    ///Lock of the synch obj
    TCriticalSection& m_rLock;

  private:
    ///Event
    TEvent& m_rEvent;
    ///Error flag
    bool m_bError;

};

//INLINE METHODS
/****************************************************************************/
/*! \see ISynchronizeObject::hasError
*/
/****************************************************************************/
inline bool MQUALIFIER TSynchronizeObject::hasError() const
{
  return m_bError;
}

END_NAMESPACE_Zeus

#endif
