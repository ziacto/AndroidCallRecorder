/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : ZObject
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/ZObject.h $
** 
** 17    23.04.08 16:24 Bha
** windows includes depending on the usage flag
** 
** 16    21.04.08 16:55 Bha
** usage of windows.h
** 
** 15    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 14    4.02.08 7:33 Bha
** - changed to inline methods
** - C++ casting
** 
** 13    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 12    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 11    26.02.07 9:00 bha
***************************************************************************/

#ifndef ZObjectH
#define ZObjectH

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/AutoPtr.hpp>
#include <zeusbase/System/String.h>
#include <zeusbase/System/GUIDWrapper.h>


#if defined(__GNUC__)

#else

  #ifdef USE_WINDOWS_H
    #include <windows.h>
  #endif

#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! Die Klasse Object ist ist die Basisklasse des Frameworks
*/
/***************************************************************************/
zeusbase_class TZObject : protected IZUnknown
{
  public:
    TZObject();
    TZObject(TString strName);

    Uint getHash() const;
    TString toString() const;

    virtual TString getObjName() const;
    virtual void setObjName(const TString& name);

    //Methoden des IZUnknown
    MEMORY_MANAGER_DECL

  protected:
    //these method are protected and must be redeclared public
    // for stack objects
    virtual ~TZObject();
    
    TZObject(const TZObject& rObject);
    TZObject& operator=(const TZObject& rObject);

    Int getRefCounter() const;
    Uint m_uiID;

  private:
    ///Reference counter
    Int m_iRefCounter;
    ///Name of the object
    TString m_strName;
};

//Inline methods
/***************************************************************************/
/*! Destroyes the Object
*/
/***************************************************************************/
inline TZObject::~TZObject()
{}

/***************************************************************************/
/*! Get hash infomation about the object
*/
/***************************************************************************/
inline Uint TZObject::getHash() const
{
  return (Uint)this;
}

/***************************************************************************/
/*! Returns the name of the object
*/
/***************************************************************************/
inline TString TZObject::getObjName() const
{
  return m_strName;
}

/***************************************************************************/
/*! Sets the name of the object
*/
/***************************************************************************/
inline void TZObject::setObjName(const TString& name)
{
  m_strName = name;
}

/***************************************************************************/
/*! Returns the reference counter of this object
*/
/***************************************************************************/
inline Int TZObject::getRefCounter() const
{
  return m_iRefCounter;
}


END_NAMESPACE_Zeus
#endif
