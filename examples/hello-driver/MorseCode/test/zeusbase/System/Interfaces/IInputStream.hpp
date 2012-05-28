/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IInputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 8.11.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IInputStream.hpp $
** 
** 15    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 14    16.01.08 10:10 Bha
** stream end reached redefined
** skip method defined
** 
** 13    11.10.07 7:00 bha
** Commented the string reading and writing
** 
** 12    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 11    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IInputStreamHPP
#define IInputStreamHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IByteArray.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>

#ifdef ENABLE_GUID_USAGE
  // {20A223D8-5EF0-444c-A412-7B35FB93B2B3}
  #define INTERFACE_IInputStream       TIID(0x20a223d8, 0x5ef0, 0x444c, 0xa4, 0x12, 0x7b, 0x35, 0xfb, 0x93, 0xb2, 0xb3)
#else
  #define INTERFACE_IInputStream       0x0000000A
#endif

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! Interface is defining a input stream
*/
/**************************************************************************/
class IInputStream : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IInputStream)
  
  public:
    /**********************************************************************/
    /*! Returns if the input stream is available (valid). 
        \retval true : stream is ok
        \retval false : invalid stream
    */
    /**********************************************************************/
    virtual bool MQUALIFIER available() const=0;
    
    /**********************************************************************/
    /*! This method checks if the stream is at the end. If a stream is
        at the end the methods readDouble(), readLong(), readByte()
        and readBool() should not called anymore. They will return zero.
        You must call this method before getting data from the stream.
        \retval true : Stream is at the end
        \retval false : Stream is not at the end
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isEndReached() const=0;
    
    /**********************************************************************/
    /*! Reads from a stream into a buffer
        \param pBuffer : Char Array
        \param lBufferSize : Size of the Array
        \param rValidSize : Length of the read buffer (return parameter)
        \retval RET_NOERROR : Reading was successful
        \retval RET_REQUEST_FAILED : Could not read from Socket
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER read(char* pBuffer, Int iBufferSize, Int& rValidSize) const=0;
    
    /**********************************************************************/
    /*! Reads a float value from a stream
        \param pError : Error return flag. If *pError = true an error has
                        been occured reading from the stream
        \return float value
    */
    /**********************************************************************/
    virtual Float64 MQUALIFIER readFloat64(BOOL_ERRORRETVAL(pError)) const=0;
    
    /**********************************************************************/
    /*! Reads a int32 value from a stream
        \param pError : Error return flag. If *pError = true an error has
                        been occured reading from the stream
        \return int32 value
    */
    /**********************************************************************/
    virtual Int32 MQUALIFIER readInt32(BOOL_ERRORRETVAL(pError)) const=0;
    
    /**********************************************************************/
    /*! Reads a int8 value from a stream
        \return int8 value
    */
    /**********************************************************************/
    virtual Int8 MQUALIFIER readInt8() const=0;
    
    /**********************************************************************/
    /*! Reads a bool value from a stream
        \return bool value 
    */
    /**********************************************************************/
    virtual bool MQUALIFIER readBool() const=0;
    
    /**********************************************************************/
    /*! Reads an array of bytes from a stream. This method uses special
        notation of the buffer and can only be used if the stream has
        written using writeArray() method. First 4 Bytes read gives the size
        of the following byte array to read. [4][3][2][1] = size,
        [0][1]..[size].
        \param rData : Return parameter
        \retval RET_NOERROR : Bytes readed
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER readArray(IByteArray& rData) const=0;
        
    /**********************************************************************/
    /*! Reads a string (16bit based) from the stream. This method uses
        spaecial notation of the buffer and can only be used if the stream
        has been written using writeString() method. First 4 bytes represent
        the size of the string. [4][3][2][1] = size,
        [0_h][0_l][1_h][1_l]..[size_h][size_l].
        Note that this method is able to handle unicode.
        \param rData : Return parameter
        \retval RET_NOERROR : String readed
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER readString(IString& rData) const=0;
    
    /**********************************************************************/
    /*! Closes the input stream
    */
    /**********************************************************************/
    virtual void MQUALIFIER close()=0;

    /**********************************************************************/
    /*! Sets the stream position back to the beginning
    */
    /**********************************************************************/
    virtual void MQUALIFIER reset()=0;

    /**********************************************************************/
    /*! This method is used to skip a number of bytes
        \param iBytes : Number of bytes to skip (default = 1)
        \retval true : Byte skipped
        \retval false: Error or end of stream reached
    */
    /**********************************************************************/
    virtual bool MQUALIFIER skip(Int iBytes = 1) = 0;
};

END_NAMESPACE_Zeus

#endif 
