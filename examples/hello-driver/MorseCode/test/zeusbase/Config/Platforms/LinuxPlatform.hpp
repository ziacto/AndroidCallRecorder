/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : LinuxPlatform
 * Package : Config
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 7.01.08 9:21 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/Config/Platforms/LinuxPlatform.hpp $
** 
** 3     7.01.08 9:21 Bha
** Double precision mode defined
** 
** 2     18.06.07 7:34 bha
** Correction for Linux platform
***************************************************************************/


#ifndef __LinuxPlatformHPP_128345873243
#define __LinuxPlatformHPP_128345873243


#define ZEUS_PLATFORM "linux"


//enables all linux bindings
#define ENABLE_LINUX_BINDING

//enables the posix threads
#define ENABLE_PTHREAD_BINDING


//TODO: Detect 64 bit systems
#define __ZEUS32__
//#define __ZEUS64__


//module export defines
#define MQUALIFIER
#define MODULE_EXPORT
#define MODULE_IMPORT
#define MODULE_EXPORT_PRE       extern "C"

#define FLOAT_PRECISION         0.0000000001

/***********************************************************************/
/*! \def ENABLE_DOUBLE_PRECISION
  This puts the X86 FPU in 64-bit precision mode.  The default
  under Linux is to use 80-bit mode, which produces subtle
  differences from FreeBSD and other systems, eg,
  (int)(1000*atof("0.3")) is 300 in 64-bit mode, 299 in 80-bit
  mode.
*/
/***********************************************************************/
#define ENABLE_DOUBLE_PRECISION

///Use QT bindings
//#define USE_QT_BINDINGS


#endif

