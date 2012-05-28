/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : STLBindings
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Platforms/STLBindings.hpp $
** 
** 7     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 6     20.02.07 10:19 bha
** Ueberarbeiten von ICAST's
***************************************************************************/

#ifndef STLBindingsHPP
#define STLBindingsHPP 

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <istream>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#include <zeusbase/System/String.h>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This class does the bindings to classes of the standard library and
    implements some usefull functions
*/
/***************************************************************************/
class TSTLBindings
{
  public:
    /***********************************************************************/
    /*! Read a double out of a input stream
        \param rStream : Stream class
        \return double value
    */
    /***********************************************************************/
    static Float64 readFloat64(std::istream& rStream)
    {
      Float64 dRetval = 0.0;
      Int iSize = sizeof(Float64);
      char* pBuffer = new char[iSize];
      ::memset(pBuffer, 0, sizeof(char)*iSize);
      
      rStream.read(pBuffer, iSize);
      dRetval = *((Float64*)pBuffer);
      
      delete [] pBuffer;
      return dRetval;
    }

    /***********************************************************************/
    /*! Read a int32 out of a input stream
        \param rStream : Stream class
        \return int32 value
    */
    /***********************************************************************/
    static Int32 readInt32(std::istream& rStream)
    {
      Int32 lRetval = 0;
      Int iSize = sizeof(Int32);
      char* pBuffer = new char[iSize];
      ::memset(pBuffer, 0, sizeof(char)*iSize);
    
      rStream.read(pBuffer, iSize);
      lRetval = *((Int32*)pBuffer);
    
      delete [] pBuffer;
      return lRetval;
    }
    
    /***********************************************************************/
    /*! Read an array of bytes out of a input stream
        \param rStream : Stream class
        \param rData : Return parameter of the array
        \retval RET_NOERROR : Array read
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /***********************************************************************/
    static Retval readArray(std::istream& rStream, IByteArray& rData)
    {
      Int iSize = TSTLBindings::readInt32(rStream);
      if (iSize > 0)
      {
        char* pBuffer = new char[iSize];
        ::memset(pBuffer, 0, sizeof(char)*iSize);
        
        rStream.read(pBuffer, iSize);
        
        rData.setArray(pBuffer, iSize);
        delete [] pBuffer;    
      }
      return RET_NOERROR;
    }
    
    /***********************************************************************/
    /*! Read a string of bytes out of a input stream
        \param stream : Stream class
        \param data : Return parameter of the string
        \retval RET_NOERROR : string read
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /***********************************************************************/
    static Retval readString(std::istream& rStream, IString& rData)
    {
      TString strRetval;
      Int iStringSize = TSTLBindings::readInt32(rStream);
      if (iStringSize > 0)
      {
        char* pBuffer = new char[iStringSize];
        ::memset(pBuffer, 0, sizeof(char)*iStringSize);
        
        rStream.read(pBuffer, iStringSize);
        
        strRetval = pBuffer;
        delete [] pBuffer;
      }
      rData.assignStr(&strRetval);
      return RET_NOERROR;
    }
};

END_NAMESPACE_Zeus

#endif
