/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IStringMap
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 17.07.06
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IStringMap.hpp $
** 
** 11    18.03.08 8:38 Mab
** Undo last change.
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IStringMapHPP
#define IStringMapHPP


#include <zeusbase/System/Interfaces/IMap.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>

BEGIN_NAMESPACE_Zeus


///
/***************************************************************************/
/*! Interface defines a map for string keys
*/
/***************************************************************************/
template <class T> class IStringMap : public IMap<IString,T>
{
  HIDE_ASSIGNMENT_OPERATOR(IStringMap<T>)
};

END_NAMESPACE_Zeus

#endif
