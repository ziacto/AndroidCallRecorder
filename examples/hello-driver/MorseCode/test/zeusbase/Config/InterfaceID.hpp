/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : InterfaceID
 * Package : Config
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 10.04.08 14:41 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/Config/InterfaceID.hpp $
** 
** 10    10.04.08 14:41 Tbu
** Reset
** 
** 8     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 7     20.05.06 19:46 bha
***************************************************************************/

#ifndef InterfaceIDHPP
#define InterfaceIDHPP

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stddef.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

/******************************************************************************/
/* Globally registration
   ----------------------
   All interface ID must be registered by b_hadorn@bluewin.ch


   Locally registration
   --------------------
   For local projects the interface ID can be registered by the project team.
   Use interface ID's 0xFF000000 to 0xFFFFFFFF for localy projects

*/
/******************************************************************************/

#include <zeusbase/Config/CustomGlobalDefines.hpp>



//#define INTERFACE_IAttributeMessage              31
//#define INTERFACE_IListMessage                   36
//#define INTERFACE_ITextMessage                   37
//#define INTERFACE_IModuleManager                 51
//#define INTERFACE_ICellRegistry                  200
//#define INTERFACE_ICellMonitor                   400

//Broadcast types
//#define BC_TEST                                  0


#endif
