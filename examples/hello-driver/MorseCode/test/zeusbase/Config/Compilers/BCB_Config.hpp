/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : BCB_Config
 * Package : Config
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 21.04.08 16:53 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/Config/Compilers/BCB_Config.hpp $
** 
** 3     21.04.08 16:53 Bha
** usage of windows.h defined
** 
** 2     4.02.08 6:41 Bha
** check the compiler option -b for enums
** 
** 1     11.06.07 14:45 bha
***************************************************************************/

#ifndef __BCB_Config_22934542321
#define __BCB_Config_22934542321

//Use bindings standard library
#define USE_STL_BINDINGS

//uses windows.h include
#define USE_WINDOWS_H

//IPV6 not available on borland C++ builder 6.x because winsock2.h is not
// included by windows.h
#ifdef __BCPLUSPLUS__ <= 0x0560
  #undef ENABLE_IPV6_BINDING
#else
  #define ENABLE_IPV6_BINDING
#endif




//The compiler option -b must be set for BCB projects otherwise enum's are not
// handled properly passing as interface method parameters. Specially for VC
// projects the problem is known, since they handle enums as int.
#pragma defineonoption ENUM_AS_INT -b

#ifndef ENUM_AS_INT
  #error Compiler does not handle enums as int (Option -b not set). BCB projects are incompatible with VC projects.
#endif

#endif

