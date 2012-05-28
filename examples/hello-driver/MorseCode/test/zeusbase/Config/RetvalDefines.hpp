/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : RetvalDefines
 * Package : Config
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 5.05.08 18:21 $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/Config/RetvalDefines.hpp $
** 
** 11    5.05.08 18:21 Bha
** new retval for ressource handling
** 
** 10    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 9     12.03.08 12:57 Tbu
** RET_OPTION_NOT_SET in RET_FEATURE_UNAVAILABLE geändert
** 
** 8     12.03.08 11:27 Tbu
** RET_OPTION_NOT_SET eingefügt
** 
** 7     7.01.08 9:22 Bha
** error for invalid types defined
** 
** 6     6.09.07 13:56 Mabbuehl
** Implementation Inch.
***************************************************************************/

#ifndef RetvalDefinesHPP
#define RetvalDefinesHPP

//The following error messages are compatible with the error codes of COM
//Error messages

//S_OK
#define RET_NOERROR                              0x00000000L

//--------------------------------------------------
#if defined(_WIN32) && !defined(_MAC)

  //E_NOTIMPL
  #define RET_METHOD_NOT_IMPL                    0x80004001L
  //E_INVALIDARG
  #define RET_INVALID_PARAMETER                  0x80070057L
  //E_NOINTERFACE
  #define RET_UNKNOWN_INTERFACE                  0x80004002L
  //E_HANDLE
  #define RET_INVALID_DATA                       0x80070006L
  //E_ABORT
  #define RET_ABORT                              0x80004004L
  //E_FAIL
  #define RET_REQUEST_FAILED                     0x80004005L
  //E_ACCESSDENIED
  #define RET_ACCESS_DENIED                      0x80070005L

#else // !defined(_WIN32) || defined(_MAC)

  //E_NOTIMPL
  #define RET_METHOD_NOT_IMPL                    0x80000001L
  //E_INVALIDARG
  #define RET_INVALID_PARAMETER                  0x80000003L
  //E_NOINTERFACE
  #define RET_UNKNOWN_INTERFACE                  0x80000004L
  //E_HANDLE
  #define RET_INVALID_DATA                       0x80000006L
  //E_ABORT
  #define RET_ABORT                              0x80000007L
  //E_FAIL
  #define RET_REQUEST_FAILED                     0x80000008L
  //E_ACCESSDENIED
  #define RET_ACCESS_DENIED                      0x80000009L


#endif // !defined(_WIN32) || defined(_MAC)
//--------------------------------------------------


//E_UNEXPECTED
#define RET_INTERNAL_ERROR                       0x8000FFFFL

//OTHER ERRORS
#define RET_REMOTECALL_ERROR                     0x8000A006L
#define RET_UNREGISTERED_CLASS                   0x8000A008L
#define RET_NOT_READY                            0x8000A009L
#define RET_REMOTEPROTOCOL_ERROR                 0x8000A00BL
#define RET_NETWORK_ERROR                        0x8000A00CL
#define RET_TIMEOUT                              0x8000A00DL
#define RET_INCORRECT_UNITSYSTEM                 0x8000A00FL
#define RET_INVALID_TYPE                         0x8000A010L
#define RET_FEATURE_UNAVAILABLE                  0x8000A011L
#define RET_RESOURCE_NOT_ACCESSIBLE              0x8000A012L
#define RET_RESOURCE_NOT_AVAILABLE               0x8000A013L



#define RET_OK                                   0x0000A014L
#define RET_CANCEL                               0x0000A015L
#define RET_YES                                  0x0000A016L
#define RET_NO                                   0x0000A017L


//Specific error return macros for methods supporting the Error Levels
#if ZEUS_ERRORLEVEL > 0
  #define BOOL_ERRORRETVAL(c)                    bool* c
  #define ULONG_ERRORRETVAL(c)                   unsigned long* c
#else
  #define BOOL_ERRORRETVAL(c)                    bool* c = NULL
  #define ULONG_ERRORRETVAL(c)                   unsigned long* c = NULL
#endif

#endif
