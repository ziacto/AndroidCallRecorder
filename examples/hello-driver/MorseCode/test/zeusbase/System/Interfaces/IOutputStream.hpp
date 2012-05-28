/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IOutputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 21.08.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IOutputStream.hpp $
** 
** 11    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 10    11.10.07 7:00 bha
** Commented the string reading and writing
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IOutputStreamHPP
#define IOutputStreamHPP


#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IByteArray.hpp>

#ifdef ENABLE_GUID_USAGE
  // {734E9B0B-DA13-4fde-81A7-9F1A340E6C4B}
  #define INTERFACE_IOutputStream     TIID(0x734e9b0b, 0xda13, 0x4fde, 0x81, 0xa7, 0x9f, 0x1a, 0x34, 0xe, 0x6c, 0x4b)
#else
  #define INTERFACE_IOutputStream     0x0000000B
#endif

BEGIN_NAMESPACE_Zeus


/**************************************************************************/
/*! Interface is defining a output stream
*/
/**************************************************************************/
class IOutputStream : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IOutputStream)
  
  public:    
    /**********************************************************************/
    /*! Writes to a stream out of a buffer
        \param pBuffer : Char Array
        \param iBufferSize : Size of the Array
        \retval RET_NOERROR : Writing was successful
        \retval RET_REQUEST_FAILED : Could not write to stream
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER write(const char* pBuffer, Int iBufferSize)=0;

    /**********************************************************************/
    /*! Writes a float64 value to a stream
        \param dData : float64 value
        \retval RET_NOERROR : Writing was successful
        \retval RET_REQUEST_FAILED : Could not write to stream
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER writeFloat64(Float64 dData)=0;
    
    /**********************************************************************/
    /*! Writes a int32 value to a stream
        \param lData : int32 value
        \retval RET_NOERROR : Writing was successful
        \retval RET_REQUEST_FAILED : Could not write to stream
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER writeInt32(Int32 lData)=0;

    /**********************************************************************/
    /*! Writes a int8 value to a stream
        \param cData : int8 value
        \retval RET_NOERROR : Writing was successful
        \retval RET_REQUEST_FAILED : Could not write to stream
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER writeInt8(Int8 cData)=0;

    /**********************************************************************/
    /*! Writes a long value to a stream
        \param bData : Long value
        \retval RET_NOERROR : Writing was successful
        \retval RET_REQUEST_FAILED : Could not write to stream
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER writeBool(bool bData)=0;

    /**********************************************************************/
    /*! Writes a byte array to a stream. This method uses some simple
        encoding. First 4 Byytes are used to write the array size, then the
        8Bit array will be written into the output stream.
        [4][3][2][1] = size, [0][1]..[size]. Use the readArray() method
        to read the array correctly from a stream.
        \param rData : Byte Array
        \retval RET_NOERROR : Writing was successful
        \retval RET_REQUEST_FAILED : Could not write to stream
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER writeArray(const IByteArray& rData)=0;

    /**********************************************************************/
    /*! Writes a string to a stream (16bit only). This method uses some
        simple encoding. First 4 Bytes are used to write the string size.
        Then the 16 bit string will be written into the output stream.
        [4][3][2][1] = size, [0_h][0_l][1_h][1_l]..[size_h][size_l].
        Use readString() method to read the correct string data.
        Note that this method is able to handle unicode.
        \param rData : String value
        \retval RET_NOERROR : Writing was successful
        \retval RET_REQUEST_FAILED : Could not write to stream
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER writeString(const IString& rData)=0;

    /**********************************************************************/
    /*! Closes the output stream
    */
    /**********************************************************************/
    virtual void MQUALIFIER close()=0;

    /**********************************************************************/
    /*! Flush the output stream. This will send the buffer to the
        destination.
    */
    /**********************************************************************/
    virtual void MQUALIFIER flush()=0;
};

END_NAMESPACE_Zeus

#endif
