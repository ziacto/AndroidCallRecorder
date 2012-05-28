/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : ISerializableImplHelper
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 25.09.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/ISerializableImplHelper.hpp $
** 
** 14    7.01.08 8:43 Bha
** Serializing types for unsigned integer implemented
** 
** 13    26.02.07 9:00 bha
***************************************************************************/



#ifndef ISerializableImplHelperHPP
#define ISerializableImplHelperHPP

/***************************************************************************/
/*! Macro to register the serializable class at the object factory.
    \param classid : ID of the serializable class
*/
/***************************************************************************/
#define OBJECTFACTORY_REGISTER_CLASS(classid) \
  classid::autoreg(true);

/***************************************************************************/
/*! Implementation of some methods and the serializing constructor
    \param classid : ID of the serializable class
*/
/***************************************************************************/
#define SERIAL_CONSTRUCTOR_START(classid) \
Retval MQUALIFIER classid::createObject(Uint uiObjectID, IInputStream* pStream, IZUnknown*& rpObj) \
{ \
  Retval retValue = RET_REQUEST_FAILED;\
  if (pStream != NULL)\
  { \
    classid* pNewObject = NULL; \
    bool bError = false; \
    try \
    { \
      pNewObject = new classid(uiObjectID, *pStream, bError);\
    } \
    catch(...) \
    { \
      bError = true;\
    } \
    if (bError && pNewObject != NULL) \
    { \
      pNewObject->release(); \
      pNewObject = NULL; \
    } \
    rpObj = (ISerializable*)pNewObject; \
    if (rpObj != NULL) \
    { \
      retValue = RET_NOERROR;\
    } \
    else \
    { \
      retValue = RET_REQUEST_FAILED; \
    } \
  } \
  else if (pStream == NULL) \
  { \
    rpObj = (ISerializable*)new classid();\
    retValue = RET_NOERROR;\
  } \
  return retValue;\
} \
\
classid::classid(Uint uiObjectID, IInputStream& rStream, bool& rError) : TZObject()


/***************************************************************************/
/*! Termination of the serializing constructor. Between the beginning and
    this end, you may place your own code to initialize the object.
*/
/***************************************************************************/
#define SERIAL_CONSTRUCTOR_INIT   rError = (doSerialize(uiObjectID, &rStream, this, NULL, NULL) != RET_NOERROR);

/***************************************************************************/
/*! Standard constructor for serializing
    \param classid : ID of the serializable class
*/
/***************************************************************************/
#define SERIAL_CONSTRUCTOR(classid) \
  SERIAL_CONSTRUCTOR_START(classid) \
  { \
    SERIAL_CONSTRUCTOR_INIT; \
  }

/***************************************************************************/
/*! Starts the serializing part of your class.
    \param classid : ID of the serializable class
    \param classname : Name of the serializable class
*/
/***************************************************************************/
#define SERIAL_START(classid, classname) \
  public : \
    classid(Uint uiObjectID, IInputStream& rStream, bool& rError);\
    static Retval MQUALIFIER createObject(Uint uiObjectID, IInputStream* pStream, IZUnknown*& rpObj); \
    \
    static void autoreg(bool bReg)\
    { \
      static Uint classid##Handle = 0;\
      TString strClassName(classname); \
      if (bReg) \
      { \
        classid##Handle = ZObjectFactory.registerClass(strClassName, createObject); \
      } \
      else \
      { \
        ZObjectFactory.unregisterClass(strClassName, classid##Handle); \
      } \
    } \
    \
    virtual Retval MQUALIFIER serialize(IByteArray& rStream) const \
    { \
      TByteArrayOutputStream* pStream = new TByteArrayOutputStream();\
      Retval retValue = doSerialize(0, NULL, NULL, pStream, this); \
      pStream->popData(rStream);\
      pStream->release();\
      return retValue; \
    } \
    \
    virtual Uint MQUALIFIER getObjectID() const \
    { return m_uiID; } \
    \
    \
    static Retval doSerialize(Uint obj_id_in, \
                                     IInputStream* stream_in, \
                                     classid* obj_new, \
                                     IOutputStream* stream_out, \
                                     const classid* obj_old) \
    { \
      Retval retValue = RET_REQUEST_FAILED; \
      Int32 lMode = 0; \
      if (stream_in != NULL && obj_new != NULL) \
      { \
        lMode = 1; \
        obj_new->m_uiID = obj_id_in; \
      } \
      else if (stream_out != NULL && obj_old != NULL) \
      { \
        lMode = 2; \
        stream_out->writeInt32(SERIALOBJECT_HEADER);\
        stream_out->writeInt32(obj_old->m_uiID);\
        TString strClassName(classname);\
        stream_out->writeString(strClassName);\
      } \
      \
      if (lMode > 0) \
      { \
        retValue = RET_NOERROR;


/***************************************************************************/
/*! Serializing a string attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_STRING(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeString(*stream_out, obj_old->attrib); \
          } \
          else \
          { \
            retValue = TSerializer::deserializeString(*stream_in, obj_new->attrib); \
          } \
        }

/***************************************************************************/
/*! Serializing a string attribute using getter and setter method to receive
    the string value.
    \param setmethod : Method to set the string value
    \param getmethod : Method to get the string value
*/
/***************************************************************************/
#define SERIAL_STRING_SET_GET(setmethod, getmethod) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TString strValue = obj_old->getmethod(); \
            TSerializer::serializeString(*stream_out, strValue); \
          } \
          else \
          { \
            TString strValue; \
            retValue = TSerializer::deserializeString(*stream_in, strValue); \
            obj_new->setmethod(strValue);\
          } \
        }

/***************************************************************************/
/*! Serializing a byte array attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_BYTEARRAY(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeByteArray(*stream_out, obj_old->attrib); \
          } \
          else \
          { \
            retValue = TSerializer::deserializeByteArray(*stream_in, obj_new->attrib); \
          } \
        }

/***************************************************************************/
/*! Serializing a byte array pointer attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_BYTEARRAY_PTR(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (obj_old->attrib != NULL)\
          { \
            if (lMode == 2) \
            { \
              TSerializer::serializeByteArray(*stream_out, *obj_old->attrib); \
            } \
            else \
            { \
              retValue = TSerializer::deserializeByteArray(*stream_in, *obj_new->attrib); \
            } \
          } \
          else \
          { \
            retValue = RET_REQUEST_FAILED; \
          } \
        }

/***************************************************************************/
/*! Serializing a list of float64.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_FLOAT64LIST(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeFloat64List(*stream_out, obj_old->attrib); \
          } \
          else \
          { \
            retValue = TSerializer::deserializeFloat64List(*stream_in, obj_new->attrib); \
          } \
        }

/***************************************************************************/
/*! Serializing a int8 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_INT8(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeInt8(*stream_out, (Int8)obj_old->attrib); \
          } \
          else \
          { \
            Int8 cValue = 0;\
            retValue = TSerializer::deserializeInt8(*stream_in, cValue); \
            obj_new->attrib = (Int8)cValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a uint8 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_UINT8(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeUint8(*stream_out, (Uint8)obj_old->attrib); \
          } \
          else \
          { \
            Uint8 ucValue = 0;\
            retValue = TSerializer::deserializeUint8(*stream_in, ucValue); \
            obj_new->attrib = (Uint8)ucValue;\
          } \
        }


/***************************************************************************/
/*! Serializing a int16 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_INT16(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeInt16(*stream_out, (Int16)obj_old->attrib); \
          } \
          else \
          { \
            Int16 sValue = 0;\
            retValue = TSerializer::deserializeInt16(*stream_in, sValue); \
            obj_new->attrib = (Int16)sValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a uint16 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_UINT16(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeUint16(*stream_out, (Uint16)obj_old->attrib); \
          } \
          else \
          { \
            Uint16 usValue = 0;\
            retValue = TSerializer::deserializeUint16(*stream_in, usValue); \
            obj_new->attrib = (Uint16)usValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a Int32 attribute using a convertion. This is needed for
    Enumerations
    \param attrib : Signature of the attribute
    \param convert_type : type to convert
*/
/***************************************************************************/
#define SERIAL_INT32_CONVERT(attrib, convert_type) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeInt32(*stream_out, (Int32)obj_old->attrib); \
          } \
          else \
          { \
            Int32 lValue = 0;\
            retValue = TSerializer::deserializeInt32(*stream_in, lValue); \
            obj_new->attrib = (convert_type)lValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a Int32 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_INT32(attrib) \
          SERIAL_INT32_CONVERT(attrib, Int32)


/***************************************************************************/
/*! Serializing a uint32 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_UINT32(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeUint32(*stream_out, (Uint32)obj_old->attrib); \
          } \
          else \
          { \
            Uint32 ulValue = 0;\
            retValue = TSerializer::deserializeUint32(*stream_in, ulValue); \
            obj_new->attrib = (Uint32)ulValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a int64 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_INT64(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeInt64(*stream_out, (Int64)obj_old->attrib); \
          } \
          else \
          { \
            Int64 ldValue = 0;\
            retValue = TSerializer::deserializeInt64(*stream_in, ldValue); \
            obj_new->attrib = (Int64)ldValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a uint64 attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_UINT64(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeUint64(*stream_out, (Uint64)obj_old->attrib); \
          } \
          else \
          { \
            Uint64 uldValue = 0;\
            retValue = TSerializer::deserializeUint64(*stream_in, uldValue); \
            obj_new->attrib = (Uint64)uldValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a double attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_FLOAT32(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeFloat32(*stream_out, (Float32)obj_old->attrib); \
          } \
          else\
          { \
            Float32 fValue = 0;\
            retValue = TSerializer::deserializeFloat32(*stream_in, fValue); \
            obj_new->attrib = (Float32)fValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a double attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_FLOAT64(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeFloat64(*stream_out, (Float64)obj_old->attrib); \
          } \
          else\
          { \
            Float64 dValue = 0;\
            retValue = TSerializer::deserializeFloat64(*stream_in, dValue); \
            obj_new->attrib = (Float64)dValue;\
          } \
        }

/***************************************************************************/
/*! Serializing a bool attribute.
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_BOOL(attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeBool(*stream_out, (bool)obj_old->attrib); \
          } \
          else \
          { \
            bool bValue = false;\
            retValue = TSerializer::deserializeBool(*stream_in, bValue); \
            obj_new->attrib = (bool)bValue;\
          } \
        }


/***************************************************************************/
/*! Serializing a sub object of this object. The sub object must inhire also
    the ISerializable Interface.
    \param interface_id : interface id of this object. Needed for up casts
    \param attrib : Signature of the attribute
*/
/***************************************************************************/
#define SERIAL_OBJECT(interface_id, attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeObject(*stream_out, obj_old->attrib); \
          } \
          else \
          { \
            retValue = TSerializer::deserializeObject(*stream_in, interface_id, ICAST(obj_new->attrib)); \
            if (retValue != RET_NOERROR) \
            { \
              obj_new->attrib = NULL; \
              retValue = RET_NOERROR;\
            } \
          } \
        } \
        else \
        { \
          if (lMode == 1)\
          { \
            obj_new->attrib = NULL; \
          } \
        } \

/***************************************************************************/
/*! Serializing an object list
    \param interface_id : interface id of this object. Needed for up casts
    \param subclass : interface of this object. Needed for up casts
    \param attrib : Signature of the attribute list
*/
/***************************************************************************/
#define SERIAL_OBJECTLIST(interface_id, subclass, attrib) \
        if (retValue == RET_NOERROR) \
        { \
          if (lMode == 2) \
          { \
            TSerializer::serializeObjectList(*stream_out, (obj_old->attrib).getCount()); \
            const IListIterator<subclass*>* pIt = (obj_old->attrib).getConstIterator(); \
            while(pIt->hasNextItem()) \
            { \
              TSerializer::serializeObjectFromList(*stream_out, pIt->getNextItemConst()); \
            } \
            (obj_old->attrib).releaseIterator(pIt); \
          } \
          else \
          { \
            Int iCount = 0; \
            retValue = TSerializer::deserializeObjectList(*stream_in, iCount); \
            if (retValue == RET_NOERROR) \
            { \
              for(Int i = 0; i < iCount; i++) \
              { \
                subclass* pObject = NULL;\
                if (TSerializer::deserializeObjectFromList(*stream_in, interface_id, ICAST(pObject)) == RET_NOERROR)\
                { \
                  obj_new->attrib.add((subclass*)pObject);\
                } \
                else \
                { \
                  obj_new->attrib.add(NULL); \
                } \
              } \
            } \
          } \
        }

/***************************************************************************/
/*! This starts the customized serializing of data.
*/
/***************************************************************************/
#define SERIAL_CUSTOM_START \
        if (retValue == RET_NOERROR) \
        { \

/***************************************************************************/
/*! This ends the customized serializing of data.
*/
/***************************************************************************/
#define SERIAL_CUSTOM_END \
        }

/***************************************************************************/
/*! End of the serializing part.
*/
/***************************************************************************/
#define SERIAL_END \
      } \
      return retValue; \
    }

#endif
