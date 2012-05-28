/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Object
 * Package : Config
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 27.05.08 7:41 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/Config/PlatformDefines.hpp $
** 
** 40    27.05.08 7:41 Bha
** Zeus-Framework 0.6.3
** 
** 39    23.04.08 16:24 Bha
** windows includes depending on the usage flag
** 
** 38    16.04.08 15:53 Bha
** changed timeval to int64 
** 
** 37    11.04.08 13:20 Bha
** GUID activated
** 
** 36    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 35    14.03.08 11:19 Bha
** new version 0.6.1
** 
** 34    29.01.08 10:53 Bha
** Compiling error of gnu compiler fixed
** 
** 33    7.01.08 9:33 Bha
** New Zeus-Framework version 0.6 created
** 
** 32    3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
**
** 28    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
** 
** 27    24.04.07 18:22 Mabbuehl
** Prozessordefines des VS für i386 und Alpha eingefügt.
** 
** 17    14.09.06 14:58 bha
** definieren von portablen primitiven Datentypen
***************************************************************************/

#ifndef __PlatformDefinesHPP__1735294829467
#define __PlatformDefinesHPP__1735294829467


///Version of the zeus framework
#define ZEUS_VERSION            "0.6.4"

//---------------------------------------------------------------------------
//Standard Error Level
// 0 = low error level. Catching any errors of methods is optional.
// 1 = medium error level. All function who might fail must receive the error
//     return value
#ifndef ZEUS_ERRORLEVEL
  #define ZEUS_ERRORLEVEL         1
#endif


//---------------------------------------------------------------------------
// Unicode defines
#ifndef DISABLE_UNICODE
  #ifndef _UNICODE
    #define _UNICODE
  #endif

  #ifndef UNICODE
    #define UNICODE
  #endif
#endif


//---------------------------------------------------------------------------
// Enables GUID for interface id's
// This option must be set to be COM compatible.
// Supported by Win32 and Linux systems
#define ENABLE_GUID_USAGE


//---------------------------------------------------------------------------
// Debug defines
#if defined(DEBUG) || defined(_DEBUG)
  #define ZEUS_DEBUG
#endif


//--------------------------------------------------------------------------
//Namespace of Zeus
#define NAMESPACE_Zeus          Zeus

#define BEGIN_NAMESPACE_Zeus    namespace NAMESPACE_Zeus {
#define END_NAMESPACE_Zeus      }
#define USING_NAMESPACE_Zeus    using namespace NAMESPACE_Zeus;


//--------------------------------------------------------------------------
// Endian defines
// code has been taken from boost/detail/limits.hpp
#if defined(__sparc) || defined(__sparc__) || defined(__powerpc__) || defined(__ppc__) || defined(__hppa) || defined(_MIPSEB) || defined(_POWER)
  #define ZEUS_BIG_ENDIAN
#elif defined(__i386__) || defined(__alpha__) || defined(__ia64) || defined(__ia64__) || defined(_M_IX86) || defined(_M_ALPHA)
  #define ZEUS_LITTLE_ENDIAN
#else
  #error "The file zeusbase/config/PlatformDefines.hpp needs to be set up for your CPU type."
#endif


//---------------------------------------------------------------------------
//Platform selection
#if defined(linux) || defined(__linux) || defined(__linux__)
  //linux
  #define ZEUS_PLATFORM_CONFIG "zeusbase/Config/Platforms/LinuxPlatform.hpp"

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
  //win32
  #define ZEUS_PLATFORM_CONFIG "zeusbase/Config/Platforms/Win32Platform.hpp"
#else
  #error "The file zeusbase/config/PlatformDefines.hpp needs to be set for this platform."
#endif

#include ZEUS_PLATFORM_CONFIG


//---------------------------------------------------------------------------
//Compiler selection
#if defined(__GNUC__)
  //GNU Compiler
  #define ZEUS_COMPILER_CONFIG "zeusbase/Config/Compilers/GCC_Config.hpp"

#elif defined(__BCPLUSPLUS__)
  //Borland C++ Compiler
  #define ZEUS_COMPILER_CONFIG "zeusbase/Config/Compilers/BCB_Config.hpp"

#elif defined(_MSC_VER)
  //Microsoft C++ Compiler
  #define ZEUS_COMPILER_CONFIG "zeusbase/Config/Compilers/MSC_Config.hpp"

#else
  #error "The file zeusbase/config/PlatformDefines.hpp needs to be set for this compiler."
#endif

#include ZEUS_COMPILER_CONFIG


//--------------------------------------------------------------------------
//class declarations for ZeusBase Library
#ifdef ZEUSBASE_EXPORT
  #define zeusbase_class        class MODULE_EXPORT
#else
  #define zeusbase_class        class MODULE_IMPORT
#endif

#define remote_interface        class


BEGIN_NAMESPACE_Zeus

//--------------------------------------------------------------------------
// TYPE DEFINITION
// The type definition is split into two sections
//  1. The physical definition declares all data types for Zeus-Frameworks
//     according to the memory size
//  2. The logical definition declares the logical types such as return values
//     numbers, floats etc.

// 1. Physical types


typedef char               Int8;
typedef unsigned char      Uint8;
typedef short              Int16;
typedef unsigned short     Uint16;
typedef long               Int32;
typedef unsigned long      Uint32;

#ifdef _MSC_VER
typedef __int64            Int64;
typedef unsigned __int64   Uint64;
#else
typedef long long          Int64;
typedef unsigned long long Uint64;
#endif

typedef float              Float32;
typedef double             Float64;


// 2. Logical types

#if defined(__ZEUS32__)
typedef Int32              Int;
typedef Uint32             Uint;
typedef Float64            Float;
typedef Uint               Retval;
typedef Int64              Timeval;

#elif defined(__ZEUS64__)
typedef Int64              Int;
typedef Uint64             Uint;
typedef Float64            Float;
typedef Uint               Retval;
typedef Int64              Timeval;

#else
  #error "Unknown platform bit size"
#endif

//--------------------------------------------------------------------------
// GLOBAL STRUCTURE DEFINITION
/***************************************************************************/
/*! This structure represents the GUID
*/
/***************************************************************************/
struct TypGUID
{
  Uint32 ulData1;
  Uint16 usData2;
  Uint16 usData3;
  Uint8 aucData4[8];
};

#ifdef ENABLE_GUID_USAGE
  typedef TypGUID InterfaceID;
#else
  typedef Uint InterfaceID;
#endif

//--------------------------------------------------------------------------
// Constant number definitions
// 
#define CONST_UINT32(a)      a##UL
#define CONST_INT32(a)       a##L

#ifdef _MSC_VER
  #define CONST_UINT64(a)    a##ui64
  #define CONST_INT64(a)     a##i64

#else
  #define CONST_UINT64(a)    a##ULL
  #define CONST_INT64(a)     a##LL

#endif

//--------------------------------------------------------------------------


///Invalid index of the list
#define INVALID_INDEX     -1

END_NAMESPACE_Zeus


#endif

