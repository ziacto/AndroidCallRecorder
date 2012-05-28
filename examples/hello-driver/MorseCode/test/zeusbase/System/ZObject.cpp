/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : ZObject
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 7.04.08 19:08 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/ZObject.cpp $
** 
** 11    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 10    4.02.08 7:33 Bha
** - changed to inline methods
** - C++ casting
** 
** 9     20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
***************************************************************************/

#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/String.h>

USING_NAMESPACE_Zeus


/***************************************************************************/
/*! Creates an anonymous object
*/
/***************************************************************************/
TZObject::TZObject()
{
  m_uiID = reinterpret_cast<Uint>(this);
  m_iRefCounter = 1;
}
  
/***************************************************************************/
/*! Creates an object with a name
    \param strName : Name of the object
*/
/***************************************************************************/
TZObject::TZObject(TString strName)
{
  m_uiID = reinterpret_cast<Uint>(this);
  m_iRefCounter = 1;
  m_strName = strName;
}

/***************************************************************************/
/*! Copy constructor of the ZObject
*/
/***************************************************************************/
TZObject::TZObject(const TZObject& rObject)
{
  m_uiID = rObject.m_uiID;
  m_strName = rObject.m_strName;
}

/***************************************************************************/
/*! Copy operator
*/
/***************************************************************************/
TZObject& TZObject::operator=(const TZObject& rObject)
{
  m_uiID = rObject.m_uiID;
  m_strName = rObject.m_strName;
  return *this;
}
/***************************************************************************/
/*! returns a string representing this object
*/
/***************************************************************************/
TString TZObject::toString() const
{
  TString strRetval(L"ZObject: Name=");
  strRetval += m_strName;
  strRetval += L" , Hash=";
  strRetval += (Int)getHash();
  return strRetval;
}

/***************************************************************************/
/*! Siehe IZUnknown
*/
/***************************************************************************/
Retval MQUALIFIER TZObject::askForInterface(const InterfaceID& rInterfaceID, IZUnknown*& rpIface)
{
  Retval retVal = RET_UNKNOWN_INTERFACE;

  if (TIID::isIZUnknown(rInterfaceID))
  {
    rpIface = this;
    this->addRef();
    retVal = RET_NOERROR;
  }

  return retVal;
}

/***************************************************************************/
/*! \see IZUnknown::addRef
*/
/***************************************************************************/
void MQUALIFIER TZObject::addRef() const
{
  TZObject* pThis = const_cast<TZObject*>(this);
  ++pThis->m_iRefCounter;
}

/***************************************************************************/
/*! \see IZUnknown::release
*/
/***************************************************************************/
void MQUALIFIER TZObject::release() const
{
  TZObject* pThis = const_cast<TZObject*>(this);
  --pThis->m_iRefCounter;
  if (m_iRefCounter <= 0)
  {
    delete pThis;
  }
}

