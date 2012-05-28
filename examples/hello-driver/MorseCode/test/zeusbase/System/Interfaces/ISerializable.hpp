/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ISerializable
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 5.09.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/ISerializable.hpp $
** 
** 12    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 11    7.01.08 8:43 Bha
** Serializing types for unsigned integer implemented
** 
** 10    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 9     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef ISerializableHPP
#define ISerializableHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IInputStream.hpp>
#include <zeusbase/System/Interfaces/IOutputStream.hpp>


#ifdef ENABLE_GUID_USAGE
  // {1F0A291E-F491-4d94-B122-41AAF00578BD}
  #define INTERFACE_ISerializable      TIID(0x1f0a291e, 0xf491, 0x4d94, 0xb1, 0x22, 0x41, 0xaa, 0xf0, 0x5, 0x78, 0xbd)

#else
  #define INTERFACE_ISerializable      0x00000001
#endif


///Header bytes (4 bytes) to specify the stream as a object stream.
#define SERIALOBJECT_HEADER   0xF5E4D3C2
 
#define SERIAL_INT32_ID                 0x10
#define SERIAL_FLOAT64_ID               0x11
#define SERIAL_BOOL_ID                  0x12
#define SERIAL_INT8_ID                  0x14
#define SERIAL_INT16_ID                 0x15
#define SERIAL_INT64_ID                 0x16
#define SERIAL_FLOAT32_ID               0x17
#define SERIAL_UINT8_ID                 0x18
#define SERIAL_UINT16_ID                0x19
#define SERIAL_UINT32_ID                0x1A
#define SERIAL_UINT64_ID                0x1B
#define SERIAL_STRING_ID                0x20
#define SERIAL_ARRAY_ID                 0x21
#define SERIAL_OBJECT_ID                0x22
#define SERIAL_OBJECTLIST_ID            0x24
#define SERIAL_FLOAT64LIST_ID           0x30


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines a serializable Object interface
*/
/***************************************************************************/
class ISerializable : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ISerializable)
  
  public:  
    /*************************************************************************/
    /*! This method serializes an object and returns the byte array
        \param rStream : Return parameter of the serialized object
        \retval RET_NOERROR : Serialzing was ok
        \retval RET_ERR_REQUEST_FAILED : Error occured serializing the object
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER serialize(IByteArray& rStream) const =0;

    /*************************************************************************/
    /*! This methods returns the ID of the object. Normaly this ID is equal to
        the address of the object. However it may be usefull to change this 
        to implement other behavours.
        \return Object ID
    */
    /*************************************************************************/
    virtual Uint MQUALIFIER getObjectID() const = 0;

};

END_NAMESPACE_Zeus

#endif
