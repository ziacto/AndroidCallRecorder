/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : STLBindings
 * Package : System/Platforms
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 6.03.06 6:49 $
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
** 3     6.03.06 6:49 bha
***************************************************************************/

#ifndef STLBindingsHPP
#define STLBindingsHPP 

#include <zeusbase/System/Interfaces/IInputStream.hpp>
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
    inline static double readDouble(IInputStream& rStream)
    {
      double dRetval = 0.0;
      long lSize = sizeof(double);
      long lValidSize = 0;
      char* pBuffer = new char[lSize];
      ::memset(pBuffer, 0, sizeof(char)*lSize);
      
      rStream.read(*pBuffer, lSize, lValidSize);
      dRetval = *((double*)pBuffer);
      
      delete [] pBuffer;
      return dRetval;
    }

    /***********************************************************************/
    /*! Read a long out of a input stream
        \param rStream : Stream class
        \return long value
    */
    /***********************************************************************/
    inline static long readLong(IInputStream& rStream)
    {
      long lRetval = 0;
      long lSize = sizeof(long);
      long lValidSize = 0;
      char* pBuffer = new char[lSize];
      ::memset(pBuffer, 0, sizeof(char)*lSize);
    
      rStream.read(*pBuffer, lSize, lValidSize);
      lRetval = *((long*)pBuffer);
    
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
    inline static unsigned long readArray(IInputStream& rStream, IByteArray& rData)
    {
      long lSize = TSTLBindings::readLong(rStream);
      long lValidSize = 0;
      if (lSize > 0)
      {
        char* pBuffer = new char[lSize];
        ::memset(pBuffer, 0, sizeof(char)*lSize);
        
        rStream.read(*pBuffer, lSize, lValidSize);
        
        rData.setArray(pBuffer, lSize);
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
    inline static unsigned long readString(IInputStream& rStream, IString& rData)
    {
      TString strRetval;
      long lStringSize = TSTLBindings::readLong(rStream);
      long lValidSize = 0;
      if (lStringSize > 0)
      {
        char* pBuffer = new char[lStringSize];
        ::memset(pBuffer, 0, sizeof(char)*lStringSize);
        
        rStream.read(*pBuffer, lStringSize, lValidSize);
        
        strRetval = pBuffer;
        delete [] pBuffer;
      }
      rData.assignStr(&strRetval);
      return RET_NOERROR;
    }
};

END_NAMESPACE_Zeus

#endif
