/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : MSC_Config
 * Package : Config
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 22.04.08 10:36 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/Config/Compilers/MSC_Config.hpp $
** 
** 9     22.04.08 10:36 Mab
** Elimination using ns zeus in Headerfiles.
** 
** 8     21.04.08 16:53 Bha
** usage of windows.h defined
** 
** 7     16.04.08 15:53 Bha
** Correction of the warnings for VC2005
** 
** 6     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 5     3.09.07 14:02 Mabbuehl
** VS6 warnings removed.
**
** 3     3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
** 
** 2     18.06.07 8:53 bha
** Anpassen an VC++
***************************************************************************/

#ifndef __MSC_Config_22934542321
#define __MSC_Config_22934542321


//Use bindings standard library
#define USE_STL_BINDINGS

//enables the IPV6
#if(_WIN32_WINNT >= 0x0400)
  #define ENABLE_IPV6_BINDING
#endif


#pragma warning(disable: 4065) // Switch with default, but without case labels.
#pragma warning(disable: 4097) // Incorrect warning caused by typedefs used in IZUnknownImplHelper.hpp only for VS.
#pragma warning(disable: 4238) // Non standard use of an r value as l value.
#pragma warning(disable: 4251) // Class, but not one of its members is declared as export class.
#pragma warning(disable: 4275) // Class, but not its base class is declared as export class.
#pragma warning(disable: 4505) // Non referenced local function was removed.
#pragma warning(disable: 4511) // Copy constructor can not be generated. Useless. If needed, compilation will fail.
#pragma warning(disable: 4512) // Assignment operator can not be generated. Useless. If needed, compilation will fail.
#pragma warning(disable: 4514) // Unreferenced inline method was removed by linker.
#pragma warning(disable: 4663) // Non standard C++ template syntax.
#pragma warning(disable: 4710) // Function was not inlined by compiler.
#pragma warning(disable: 4786) // Symbolic informations in Debug get restricted to 255 chars.
#pragma warning(disable: 4996) // xxx is a deprecated function

#ifdef _MANAGED
  #pragma warning(disable: 4793) // system owed code for xxx generated
#endif

//Use bindings for migrossoft visual studio
//#define USE_VC_BINDINGS


//This must be set if the includes of zeus are used in managed context of vc2005
// there is a problem with windows.h
#ifndef _MANAGED
  #define USE_WINDOWS_H
#else
  #undef USE_WINDOWS_H
#endif


//-----------------------------------------------------
/* MSC_VER defines for other visual studio environments

Visual C++ 1.1        MSC_VER=800
Visual C++ 2.x        MSC_VER=900
Visual C++ 4.x        MSC_VER=1000
Visual C++ 5          MSC_VER=1100
Visual C++ 6          MSC_VER=1200
Visual C++ .NET       MSC_VER=1300
Visual C++ .NET 2003  MSC_VER=1310
Visual C++ 2005       MSC_VER=1400
*/
//-----------------------------------------------------



#endif
