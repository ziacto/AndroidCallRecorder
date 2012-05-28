/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IValueType
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 3.11.06
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
 $Log: /WinSteuerung2/usr/include/zeusbase/System/Interfaces/IValueType.hpp $
** 
** 3     11.10.07 13:25 Mabbuehl
** Include order corrected for customized ZEUS_ERRORLEVEL to be active.
** 
** 2     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
***************************************************************************/

#ifndef IValueTypeHPP
#define IValueTypeHPP

#include <zeusbase/Config/InterfaceID.hpp> // Must be included BEFORE RetvalDefines.hpp.
#include <zeusbase/Config/RetvalDefines.hpp>
#include <zeusbase/System/Interfaces/IZUnknownImplHelper.hpp>
#include <zeusbase/Config/PlatformDefines.hpp>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines a value type. The value types are non shared
    interfaces, such as strings, lists etc. For shared types you must use
    IZUnknown interface.
*/
/***************************************************************************/
class IValueType
{
  HIDE_ASSIGNMENT_OPERATOR(IValueType)
  HIDE_DESTRUCTOR(IValueType)
};

END_NAMESPACE_Zeus


#endif

