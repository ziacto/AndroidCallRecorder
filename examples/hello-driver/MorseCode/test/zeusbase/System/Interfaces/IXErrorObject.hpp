/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IXErrorObject
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXErrorObject.hpp $
** 
** 2     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 1     7.01.08 8:01 Bha
** Created
***************************************************************************/


#ifndef IXErrorObjectHPP
#define IXErrorObjectHPP

#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IZUnknown.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {1CA87CC8-3C1B-459d-BCD6-57CA750955AF}
  #define INTERFACE_IXErrorObject     TIID(0x1ca87cc8, 0x3c1b, 0x459d, 0xbc, 0xd6, 0x57, 0xca, 0x75, 0x9, 0x55, 0xaf)
#else
  #define INTERFACE_IXErrorObject     0x0000001A
#endif

/***************************************************************************/
/*! Error object interface
*/
/***************************************************************************/
class IXErrorObject : public IZUnknown
{
  public:
    /***********************************************************************/
    /*! Returns the error text of the object
        \param rText : Return parameter
    */
    /***********************************************************************/
    virtual void MQUALIFIER getErrorText(IString& rText) const = 0;

};

END_NAMESPACE_Zeus

#endif
