/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IZVariant
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 7.04.08 19:08 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IZVariant.hpp $
** 
** 15    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 14    7.01.08 8:43 Bha
** Serializing types for unsigned integer implemented
** 
** 13    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 12    4.04.07 6:50 bha
***************************************************************************/

#ifndef IZVariantHPP
#define IZVariantHPP
 

#include <zeusbase/System/Interfaces/ISerializable.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IList.hpp>

#ifdef ENABLE_GUID_USAGE
  // {95C94F60-BFA6-43b4-B579-5F78118FE9EC}
  #define INTERFACE_IZVariant    TIID(0x95c94f60, 0xbfa6, 0x43b4, 0xb5, 0x79, 0x5f, 0x78, 0x11, 0x8f, 0xe9, 0xec)
#else
  #define INTERFACE_IZVariant    0x0000000C
#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines a variant datatype. This datatype is designed
    to wrap regular primitive datatypes and complex serializabl;e objects.
    Its used for serializing and deserializing data over the network
*/
/***************************************************************************/
class IZVariant : public ISerializable
{
  HIDE_ASSIGNMENT_OPERATOR(IZVariant)
  
  public:
    
    /***************************************************************************/
    /*! Datatypes of a variant 
    */
    /***************************************************************************/
    enum EZVariantType 
    {
      etEmpty      = 0,    /*!< Unknown or Empty data */
      etInt8       = 1,    /*!< a int8 value */
      etInt16      = 2,    /*!< a int16 value */
      etInt32      = 3,    /*!< a int32 value */
      etInt64      = 4,    /*!< a int64 value */
      etFloat32    = 5,    /*!< a float32 value */
      etFloat64    = 6,    /*!< a float64 value */
      etString     = 7,    /*!< a wide char based string */
      etByteArray  = 8,    /*!< a byte array (stream) */
      etObject     = 9,    /*!< a object */
      etObjectList = 10,   /*!< list of objects */
      etUint8      = 11,   /*!< a unsigned int8 value */
      etUint16     = 12,   /*!< a unsigned int16 value */
      etUint32     = 13,   /*!< a unsigned int32 value */
      etUint64     = 14,   /*!< a unsigned int64 value */
    };
    
    /***********************************************************************/
    /*! Returns the datatype of the variant
        \return datatype (see TZVariantType)
    */
    /***********************************************************************/
    virtual EZVariantType MQUALIFIER getType() const=0;
    
    /***********************************************************************/
    /*! Returns the name of the variant type
        \param rName : return parameter of the name
    */
    /***********************************************************************/
    virtual void MQUALIFIER getVariantName(IString& rName) const=0;
    
    /***********************************************************************/
    /*! Returns the variant data as an int8 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getInt8(Int8& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an int16 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getInt16(Int16& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an int32 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getInt32(Int32& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an int64 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getInt64(Int64& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an unsigned int8 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getUint8(Uint8& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an unsigned int16 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getUint16(Uint16& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an unsigned int32 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getUint32(Uint32& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an unsigneds int64 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getUint64(Uint64& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as a float 32 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getFloat32(Float32& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as a float 64 value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getFloat64(Float64& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as a return value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getRetval(Retval& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as a time value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getTimeval(Timeval& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as a string value
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getString(IString& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as a byte array
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getByteArray(IByteArray& rRet) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an object
        \param rpRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getObject(ISerializable*& rpRret) const=0;

    /***********************************************************************/
    /*! Returns the variant data as an object list
        \param rRet : Return value
        \retval RET_NOERROR : Value returned
        \retval RET_REQUEST_FAILED : Could not return the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getObjectList(IList<ISerializable*>& rRet) const=0;

    /***********************************************************************/
    /*! Sets the name of the variant type
        \param rName : Name of the variant
    */
    /***********************************************************************/
    virtual void MQUALIFIER setVariantName(const IString& rName)=0;

    /***********************************************************************/
    /*! Sets an int8 value to the variant
        \param cVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setInt8(Int8 cVal)=0;

    /***********************************************************************/
    /*! Sets an int16 value to the variant
        \param sVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setInt16(Int16 sVal)=0;

    /***********************************************************************/
    /*! Sets an int32 value to the variant
        \param lVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setInt32(Int32 lVal)=0;

    /***********************************************************************/
    /*! Sets an int64 value to the variant
        \param ldVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setInt64(Int64 ldVal)=0;

    /***********************************************************************/
    /*! Sets an unsigned int8 value to the variant
        \param ucVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setUint8(Uint8 ucVal)=0;

    /***********************************************************************/
    /*! Sets an unsigned int16 value to the variant
        \param usVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setUint16(Uint16 usVal)=0;

    /***********************************************************************/
    /*! Sets an unsigned int32 value to the variant
        \param ulVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setUint32(Uint32 ulVal)=0;

    /***********************************************************************/
    /*! Sets an unsigned int64 value to the variant
        \param uldVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setUint64(Uint64 uldVal)=0;

    /***********************************************************************/
    /*! Sets a float64 value to the variant
        \param fVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setFloat32(Float32 fVal)=0;

    /***********************************************************************/
    /*! Sets a float64 value to the variant
        \param dVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setFloat64(Float64 dVal)=0;

    /***********************************************************************/
    /*! Sets a return value to the variant
        \param retVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setRetval(Retval retVal)=0;

    /***********************************************************************/
    /*! Sets a time value to the variant
        \param tmVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setTimeval(Timeval tmVal)=0;

    /***********************************************************************/
    /*! Sets a string value to the variant
        \param rVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setString(const IString& rVal)=0;

    /***********************************************************************/
    /*! Sets an array to the variant
        \param rVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setByteArray(const IByteArray& rVal)=0;

    /***********************************************************************/
    /*! Sets an object to the variant
        \param rVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setObject(const ISerializable& rVal)=0;

    /***********************************************************************/
    /*! Sets an aobject list to the variant
        \param rVal : value to be set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setObjectList(const IList<ISerializable*>& rVal)=0;

    /***********************************************************************/
    /*! assigns a variant to this variant
        \param rInpar : Variant object to set
        \retval RET_NOERROR : Values set
        \retval RET_REQUEST_FAILED : Could not set the requested type
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER assign(const IZVariant& rInpar)=0;

    /***********************************************************************/
    /*! Checks if two variants are equal
        \param rInpar : Variant to check
        \retval true : Variants are equal
        \retval false : Variants are not equal
    */
    /***********************************************************************/
    virtual bool MQUALIFIER equals(const IZVariant& rInpar) const=0;

    /**************************************************************************/
    /*! Compares two variants. If the variant contains values, it compares
        based on > < or == operators. If the variant contains strings, it
        will compare lexicographically.
        \param rInpar : Variant to compare with
        \retval 0 : Variants are equal (or can not be compared)
        \retval -1: this variant is smaller than the rInpar
        \retval 1 : this variant is bigger than the rInpar
    */
    /**************************************************************************/
    virtual Int MQUALIFIER compareTo(const IZVariant& rInpar) const = 0;

    /**************************************************************************/
    /*! Converts the variant to an int value
    */
    /**************************************************************************/
    virtual Int MQUALIFIER toInt(Int iDefault = 0) const = 0;

    /**************************************************************************/
    /*! Converts the variant to an unsigned int value
    */
    /**************************************************************************/
    virtual Uint MQUALIFIER toUint(Uint uiDefault = 0) const = 0;

    /**************************************************************************/
    /*! Converts the variant to a float value
    */
    /**************************************************************************/
    virtual Float MQUALIFIER toFloat(Float fDefault = 0) const = 0;

    /**************************************************************************/
    /*! Converts the variant to a string value
    */
    /**************************************************************************/
    virtual void MQUALIFIER toString(IString& rValue) const = 0;

};

END_NAMESPACE_Zeus

#endif
