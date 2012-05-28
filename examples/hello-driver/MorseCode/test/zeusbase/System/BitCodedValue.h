/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : BitCodedValue
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 17.04.08 8:08 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/BitCodedValue.h $
** 
** 7     17.04.08 8:08 Bha
** correction for int64 convertion defaults
** 
** 6     24.01.08 15:35 Bha
** New constructors for all int types
** 
** 5     24.01.08 13:51 Bha
** Max int constants renamed
** 
** 4     24.01.08 10:09 Bha
** Forward bit scan implemented
** 
** 3     26.02.07 9:00 bha
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef BitCodedValueH
#define BitCodedValueH

#include <zeusbase/System/ZObject.h>

BEGIN_NAMESPACE_Zeus


/***************************************************************************/
/*! This class implements a bit coded value as a stack type. The bit coded
    value is used as helper class for setting bits or event bytes inside a
    64 bit array.
    \todo: We might extend this class for larger bit arrays than 64 bits.
*/
/***************************************************************************/
zeusbase_class TBitCodedValue 
{
  public:
    //Constructors
    TBitCodedValue();
    TBitCodedValue(const TBitCodedValue& rValue);
    TBitCodedValue(int iValue, Int iMaxSize = 64);
    TBitCodedValue(unsigned int uiValue, Int iMaxSize = 64);

    //signed values
    TBitCodedValue(Int8 cValue, Int iMaxSize = 8);
    TBitCodedValue(Int16 sValue, Int iMaxSize = 16);
    TBitCodedValue(Int32 lValue, Int iMaxSize = 32);
    TBitCodedValue(Int64 ldValue, Int iMaxSize = 64);

    //unsigned values
    TBitCodedValue(Uint8 ucValue, Int iMaxSize = 8);
    TBitCodedValue(Uint16 usValue, Int iMaxSize = 16);
    TBitCodedValue(Uint32 ulValue, Int iMaxSize = 32);
    TBitCodedValue(Uint64 uldValue, Int iMaxSize = 64);

    //destructor
    virtual ~TBitCodedValue();

    TString toBinary(bool bTrimZeros = false) const;
    TString toHex(bool bTrimZeros = false) const;

    Int8 getInt8() const;
    Int16 getInt16() const;
    Int32 getInt32() const;
    Int64 getInt64() const;

    Uint8 getUint8() const;
    Uint16 getUint16() const;
    Uint32 getUint32() const;
    Uint64 getUint64() const;

    bool getBit(Int iIndex, bool* pError = NULL) const;
    Int getFirstBitSet() const;
    Int getFirstBitSet(Uint64 uldMask) const;
    Int getLastBitSet() const;
    Int getLastBitSet(Uint64 uldMask) const;

    void invertAll();
    bool invertBit(Int iIndex);

    bool setBit(Int iIndex, bool bState);
    bool setBitRange(Int iFromIndex, Int iToIndex, Uint64 uldValue, bool bForce = false);
    bool setBitRange(Int iFromIndex, Int iToIndex, Int64 ldValue, bool bForce = false);
    bool setBitRange(Int iFromIndex, Int iToIndex, int iValue, bool bForce = false);
    bool setBitRange(Int iFromIndex, Int iToIndex, unsigned int uiValue, bool bForce = false);

    //operators
    bool operator== (Int64 ldValue) const;
    bool operator== (Uint64 uldValue) const;
    bool operator== (const TBitCodedValue& rValue) const;
    bool operator== (int iValue) const;
    bool operator== (unsigned int uiValue) const;

    bool operator!= (Int64 ldValue) const;
    bool operator!= (Uint64 uldValue) const;
    bool operator!= (const TBitCodedValue& rValue) const;
    bool operator!= (int iValue) const;
    bool operator!= (unsigned int uiValue) const;

    TBitCodedValue& operator= (Int64 ldValue);
    TBitCodedValue& operator= (Uint64 uldValue);
    TBitCodedValue& operator= (const TBitCodedValue& rValue);
    TBitCodedValue& operator= (int iValue);
    TBitCodedValue& operator= (unsigned int uiValue);

    bool operator[](Int iIndex) const;

    static TString convertToBinary(const TBitCodedValue& rValue, bool bTrimZeros = false);
    static TString convertToBinary(Uint64 uldValue, Int iMaxSize, bool bTrimZeros = false);
    static TString convertToHex(const TBitCodedValue& rValue, bool bTrimZeros = false);
    static TString convertToHex(Uint64 uldValue, Int iMaxSize, bool bTrimZeros = false);

    static Int64 convertHexToInt64(const TString& rString, bool& rError, Int64 ldPredef = 0);
    static Int64 convertBinaryToInt64(const TString& rString, bool& rError, Int64 ldPredef = 0);

  protected:

    ///Bit coded value
    Uint64 m_uldBitArray;
    ///Max bit code size
    Int m_iMaxSize;

  private:
    void initMaxSize(Int iMaxSize);
};

//INLINE METHODS
/***************************************************************************/
/*! Returns a int8 value
*/
/***************************************************************************/
inline Int8 TBitCodedValue::getInt8() const
{
  return (Int8)m_uldBitArray;
}

/***************************************************************************/
/*! Returns a int16 value
*/
/***************************************************************************/
inline Int16 TBitCodedValue::getInt16() const
{
  return (Int16)m_uldBitArray;
}

/***************************************************************************/
/*! Returns a int32 value
*/
/***************************************************************************/
inline Int32 TBitCodedValue::getInt32() const
{
  return (Int32)m_uldBitArray;
}

/***************************************************************************/
/*! Returns a int64 value
*/
/***************************************************************************/
inline Int64 TBitCodedValue::getInt64() const
{
  return (Int64)m_uldBitArray;
}

/***************************************************************************/
/*! Returns a Uint8 value
*/
/***************************************************************************/
inline Uint8 TBitCodedValue::getUint8() const
{
  return (Uint8)m_uldBitArray;
}

/***************************************************************************/
/*! Returns a Uint16 value
*/
/***************************************************************************/
inline Uint16 TBitCodedValue::getUint16() const
{
  return (Uint16)m_uldBitArray;
}

/***************************************************************************/
/*! Returns a Uint32 value
*/
/***************************************************************************/
inline Uint32 TBitCodedValue::getUint32() const
{
  return (Uint32)m_uldBitArray;
}

/***************************************************************************/
/*! Returns a Uint64 value
*/
/***************************************************************************/
inline Uint64 TBitCodedValue::getUint64() const
{
  return (Uint64)m_uldBitArray;
}

/***************************************************************************/
/*! sets a bit range from iFromIndex to iToIndex.
    \see TBitCodedValue::setBitRange
*/
/***************************************************************************/
inline bool TBitCodedValue::setBitRange(Int iFromIndex, Int iToIndex, Int64 ldValue, bool bForce /**= false*/)
{
  return setBitRange(iFromIndex, iToIndex, (Uint64)ldValue, bForce);
}

/***************************************************************************/
/*! sets a bit range from iFromIndex to iToIndex.
    \see TBitCodedValue::setBitRange
*/
/***************************************************************************/
inline bool TBitCodedValue::setBitRange(Int iFromIndex, Int iToIndex, int iValue, bool bForce /**= false*/)
{
  return setBitRange(iFromIndex, iToIndex, (Uint64)iValue, bForce);
}

/***************************************************************************/
/*! sets a bit range from iFromIndex to iToIndex.
    \see TBitCodedValue::setBitRange
*/
/***************************************************************************/
inline bool TBitCodedValue::setBitRange(Int iFromIndex, Int iToIndex, unsigned int uiValue, bool bForce /**= false*/)
{
  return setBitRange(iFromIndex, iToIndex, (Uint64)uiValue, bForce);
}

/***************************************************************************/
/*! converts the bit coded value into a binary output
*/
/***************************************************************************/
inline TString TBitCodedValue::toBinary(bool bTrimZeros /*= false*/) const
{
  return convertToBinary(m_uldBitArray, m_iMaxSize, bTrimZeros);
}

/***************************************************************************/
/*! converts the bit coded value into a hexadecimal output
*/
/***************************************************************************/
inline TString TBitCodedValue::toHex(bool bTrimZeros /*= false*/) const
{
  return convertToHex(m_uldBitArray, m_iMaxSize, bTrimZeros);
}

/***************************************************************************/
/*! converts a bit coded value into a binary output
*/
/***************************************************************************/
inline /*static*/ TString TBitCodedValue::convertToBinary(const TBitCodedValue& rValue, bool bTrimZeros /*= false*/)
{
  return convertToBinary(rValue.m_uldBitArray, rValue.m_iMaxSize, bTrimZeros);
}

/***************************************************************************/
/*! converts a bit coded value into a hexadecimal output
*/
/***************************************************************************/
inline /*static*/ TString TBitCodedValue::convertToHex(const TBitCodedValue& rValue, bool bTrimZeros /*= false*/)
{
  return convertToHex(rValue.m_uldBitArray, rValue.m_iMaxSize, bTrimZeros);
}

/***************************************************************************/
/*! inverts all bits
*/
/***************************************************************************/
inline void TBitCodedValue::invertAll()
{
  m_uldBitArray = ~m_uldBitArray;
}

//--------------------------------------------------------------------------
//         OPERATOR ==
/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator== (Int64 ldValue) const
{
  return (m_uldBitArray == (Uint64)ldValue);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator== (Uint64 uldValue) const
{
  return (m_uldBitArray == uldValue);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator== (const TBitCodedValue& rValue) const
{
  return (m_uldBitArray == rValue.m_uldBitArray);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator== (int iValue) const
{
  return (m_uldBitArray == (Uint64)iValue);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator== (unsigned int uiValue) const
{
  return (m_uldBitArray == (Uint64)uiValue);
}



//--------------------------------------------------------------------------
//         OPERATOR !=
/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator!= (Int64 ldValue) const
{
  return (m_uldBitArray != (Uint64)ldValue);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator!= (Uint64 uldValue) const
{
  return (m_uldBitArray != uldValue);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator!= (const TBitCodedValue& rValue) const
{
  return (m_uldBitArray != rValue.m_uldBitArray);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator!= (int iValue) const
{
  return (m_uldBitArray != (Uint64)iValue);
}

/***************************************************************************/
/*! compares a value with the bit coded value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator!= (unsigned int uiValue) const
{
  return (m_uldBitArray != (Uint64)uiValue);
}



//--------------------------------------------------------------------------
//         OPERATOR =
/***************************************************************************/
/*! assigns a new bit coded value
*/
/***************************************************************************/
inline TBitCodedValue& TBitCodedValue::operator= (Int64 ldValue)
{
  m_uldBitArray = (Uint64)ldValue;
  return *this;
}

/***************************************************************************/
/*! assigns a new bit coded value
*/
/***************************************************************************/
inline TBitCodedValue& TBitCodedValue::operator= (Uint64 uldValue)
{
  m_uldBitArray = uldValue;
  return *this;
}

/***************************************************************************/
/*! assigns a new bit coded value
*/
/***************************************************************************/
inline TBitCodedValue& TBitCodedValue::operator= (const TBitCodedValue& rValue)
{
  m_uldBitArray = rValue.m_uldBitArray;
  return *this;
}

/***************************************************************************/
/*! assigns a new bit coded value
*/
/***************************************************************************/
inline TBitCodedValue& TBitCodedValue::operator= (int iValue)
{
  m_uldBitArray = (Uint64)iValue;
  return *this;
}


/***************************************************************************/
/*! assigns a new bit coded value
*/
/***************************************************************************/
inline TBitCodedValue& TBitCodedValue::operator= (unsigned int uiValue)
{
  m_uldBitArray = (Uint64)uiValue;
  return *this;
}

/***************************************************************************/
/*! returns an indexed value
*/
/***************************************************************************/
inline bool TBitCodedValue::operator[](Int iIndex) const
{
  return this->getBit(iIndex);
}


END_NAMESPACE_Zeus

//---------------------------------------------------------------------------
#endif
