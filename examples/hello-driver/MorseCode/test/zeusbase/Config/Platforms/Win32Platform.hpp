/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Win32Platform
 * Package : Config
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 12.03.08 14:20 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/Config/Platforms/Win32Platform.hpp $
** 
** 3     12.03.08 14:20 Bha
** added define to disable multi processor useage
** 
** 2     7.01.08 9:33 Bha
** New Zeus-Framework version 0.6 created
***************************************************************************/

#ifndef __Win32PlatformHPP_845673493922
#define __Win32PlatformHPP_845673493922

#define ZEUS_PLATFORM "win32"


//Enables all win32 bindings
#define ENABLE_WIN32_BINDING

//enables the win32 API for threads
#define ENABLE_WIN32_THREAD_BINDING

//disables the multi processor use for the process
#define DISABLE_MULTI_PROCESSOR

//win32 is allways 32bit platform
#define __ZEUS32__

//module export defines
#define MQUALIFIER              __stdcall
#define MODULE_EXPORT           __declspec(dllexport)
#define MODULE_IMPORT           __declspec(dllimport)
#define MODULE_EXPORT_PRE       extern "C"

#define FLOAT_PRECISION         0.0000000001

#endif
