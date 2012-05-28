/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : Transcoder
 * Package : System/Platforms
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 17:21 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Platforms/Transcoder.hpp $
** 
** 10    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 9     3.09.07 14:02 Mabbuehl
** VS6 warnings removed.
** 
** 8     20.02.07 10:19 bha
** Ueberarbeiten von ICAST's
** 
** 6     27.09.06 17:10 Mabbuehl
** 
** 5     25.09.06 17:22 Mabbuehl
** Unicode Migration
***************************************************************************/

 
#ifndef TranscoderHPP
#define TranscoderHPP

#include <zeusbase/System/String.h>

#ifdef _MSC_VER
  #pragma warning(push, 1) // Avoid Visual Studio 6.0 level 4 and 3 compiler warnings.
#endif

#include <stdlib.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

//#############################################################################
//STL Transforms
#ifdef USE_STL_BINDINGS
  
#ifdef _MSC_VER
  #pragma warning(push, 1) // Avoid Visual Studio 6.0 level 4 and 3 compiler warnings.
#endif

#include <string>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


#define _STD_STR(arg)   NAMESPACE_Zeus::TSTLTranscoder::transcodeStr(arg)
#define _STD_WSTR(arg)  NAMESPACE_Zeus::TSTLTranscoder::transcodeWStr(arg)

BEGIN_NAMESPACE_Zeus

/******************************************************************************/
/*! This transcoder is used to transform stl datatypes to the zeus-datatypes
*/
/******************************************************************************/
class TSTLTranscoder
{
  public:  
    /**************************************************************************/  
    /*! Transform a string to a zeus-string
        \param rValue : Input string
        \retval zeus-string
    */
    /**************************************************************************/  
    static TString transcodeStr(const std::string& rValue)
    {
      return TString(rValue.c_str());
    }
    
    /**************************************************************************/  
    /*! Transform a zeus-string to a stl-string
        \param rValue : Input string
        \retval stl-string
    */
    /**************************************************************************/  
    static std::string transcodeStr(const TString& rValue)
    {
      return std::string(rValue.c_str(NULL));
    }

    /**************************************************************************/  
    /*! Transform a wide-string to a zeus-string
        \param rValue : Input string
        \retval zeus-string
    */
    /**************************************************************************/  
    static TString transcodeWStr(const std::wstring& rValue)
    {
      return TString(rValue.c_str());
    }
    
    /**************************************************************************/  
     /*! Transform a zeus-string to a wide-string
        \param value : Input string
        \retval wide-string
    */
    /**************************************************************************/  
    static std::wstring transcodeWStr(const TString& rValue)
    {
      return std::wstring(rValue.c_bstr());
    }
};
END_NAMESPACE_Zeus
#endif

//#############################################################################
// QT Transforms
#ifdef USE_QT_BINDINGS

#define _QTWSTR(arg)  NAMESPACE_Zeus::TQTTranscoder::transcodeStr(arg)


#include <qstring.h>
BEGIN_NAMESPACE_Zeus
/******************************************************************************/
/*! This transcoder is used to transform QT datatypes to the zeus-datatypes
*/
/******************************************************************************/
class TQTTranscoder 
{
  public:

    /**************************************************************************/  
    /*! Transform a qstring to a zeus-string
        \param value : Input qstring
        \retval zeus-string
    */
    /**************************************************************************/  
    static TString transcodeStr(const QString& rValue)
    {
      return TString(rValue.ascii());
    }
    
    /**************************************************************************/  
     /*! Transform a zeus-string to a wide-string
        \param value : Input string
        \retval wide-string
    */
    /**************************************************************************/  
    static QString transcodeStr(const TString& rValue)
    {
      return QString::fromAscii(rValue.c_str(NULL));
    }
};
END_NAMESPACE_Zeus
 
#endif
     
//#############################################################################
// Borland Transforms
#ifdef USE_BCB_BINDINGS
#include <Classes.hpp>

#define _BCBSTR(arg)   NAMESPACE_Zeus::TBCBTranscoder::transcodeStr(arg)
#define _BCBWSTR(arg)  NAMESPACE_Zeus::TBCBTranscoder::transcodeWStr(arg)

BEGIN_NAMESPACE_Zeus

/******************************************************************************/
/*! This transcoder is used to transform borland datatypes to the zeus-datatypes
*/
/******************************************************************************/
class TBCBTranscoder 
{
  public:
    /**************************************************************************/  
    /*! 
    */
    /**************************************************************************/  
    static TString transcodeStr(const AnsiString& rValue) // AnsiString for Transcoder.
    {
      return TString(rValue.c_str());
    }
    
    /**************************************************************************/  
    /*! 
    */
    /**************************************************************************/  
    static TString transcodeWStr(const WideString& rValue) // WideString for Transcoder.
    {
      return TString(rValue.c_bstr());
    }
    
    /**************************************************************************/  
    /*! 
    */
    /**************************************************************************/  
    static AnsiString transcodeStr(const TString& rValue, BOOL_ERRORRETVAL(pError)) // AnsiString for Transcoder.
    {
      return AnsiString(rValue.c_str(pError)); // AnsiString for Transcoder.
    }
    
    /**************************************************************************/  
    /*! 
    */
    /**************************************************************************/  
    static WideString transcodeWStr(const TString& rValue) // WideString for Transcoder.
    {
      return WideString(rValue.c_bstr()); // WideString for Transcoder.
    }
};
END_NAMESPACE_Zeus

#endif


#endif
