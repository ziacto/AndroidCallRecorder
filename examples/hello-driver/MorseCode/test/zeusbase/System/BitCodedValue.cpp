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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/BitCodedValue.cpp $
** 
** 10    17.04.08 8:08 Bha
** correction for int64 convertion defaults
** 
** 9     24.01.08 15:35 Bha
** New constructors for all int types
** 
** 8     24.01.08 14:43 Bha
** backward bit scan implemented
** 
** 7     24.01.08 13:55 Bha
** Warnings of Borland C++ removed
** 
** 6     24.01.08 13:51 Bha
** Max int constants renamed
** 
** 5     24.01.08 10:09 Bha
** Forward bit scan implemented
** 
** 4     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 3     26.02.07 9:00 bha
***************************************************************************/
//---------------------------------------------------------------------------

#include <zeusbase/System/BitCodedValue.h>
#include <zeusbase/System/Int.h>

//---------------------------------------------------------------------------
USING_NAMESPACE_Zeus


/****************************************************************************/
/* Map is used for bit scan with de Bruijn algorithm
*/
/****************************************************************************/
const int aDeBruijnMap[64] =
{
   63,  0, 58,  1, 59, 47, 53,  2,
   60, 39, 48, 27, 54, 33, 42,  3,
   61, 51, 37, 40, 49, 18, 28, 20,
   55, 30, 34, 11, 43, 14, 22,  4,
   62, 57, 46, 52, 38, 26, 32, 41,
   50, 36, 17, 19, 29, 10, 13, 21,
   56, 45, 25, 31, 35, 16,  9, 12,
   44, 24, 15,  8, 23,  7,  6,  5
};

/****************************************************************************/
/*! Creates an empty bit coded value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue()
{
  m_uldBitArray = 0;
  initMaxSize(64);
}

/****************************************************************************/
/*! Copy constructor of the bit coded value
    \param rValue : Value to copy
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(const TBitCodedValue& rValue)
{
  m_uldBitArray = rValue.m_uldBitArray;
  initMaxSize(rValue.m_iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an int value
    \param iValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(int iValue, Int iMaxSize /*= 64*/)
{
  m_uldBitArray = (Uint64)iValue;
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an unsigned int value
    \param uiValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(unsigned int uiValue, Int iMaxSize /*= 64*/)
{
  m_uldBitArray = (Uint64)uiValue;
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an signed int8 value
    \param cValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Int8 cValue, Int iMaxSize /*= 8*/)
{
  m_uldBitArray = static_cast<Uint64>(cValue);
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an signed int16 value
    \param sValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Int16 sValue, Int iMaxSize /*= 16*/)
{
  m_uldBitArray = static_cast<Uint64>(sValue);
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an signed int32 value
    \param lValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Int32 lValue, Int iMaxSize /*= 32*/)
{
  m_uldBitArray = static_cast<Uint64>(lValue);
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an signed int64 value
    \param ldValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Int64 ldValue, Int iMaxSize /*= 64*/)
{
  m_uldBitArray = static_cast<Uint64>(ldValue);
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an unsigned int8 value
    \param ucValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Uint8 ucValue, Int iMaxSize /*= 8*/)
{
  m_uldBitArray = static_cast<Uint64>(ucValue);
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an unsigned int16 value
    \param usValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Uint16 usValue, Int iMaxSize /*= 16*/)
{
  m_uldBitArray = static_cast<Uint64>(usValue);
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an unsigned int32 value
    \param ulValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Uint32 ulValue, Int iMaxSize /*= 32*/)
{
  m_uldBitArray = static_cast<Uint64>(ulValue);
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Creates a bit coded value out of an unsigned int64 value
    \param uldValue : Value to copy
    \param iMaxSize : Max bit code value
*/
/****************************************************************************/
TBitCodedValue::TBitCodedValue(Uint64 uldValue, Int iMaxSize /*= 64*/)
{
  m_uldBitArray = uldValue;
  initMaxSize(iMaxSize);
}

/****************************************************************************/
/*! Destroys the bit coded value
*/
/****************************************************************************/
TBitCodedValue::~TBitCodedValue()
{
}

/****************************************************************************/
/*! inits the max size
*/
/****************************************************************************/
void TBitCodedValue::initMaxSize(Int iMaxSize)
{
  m_iMaxSize = iMaxSize;
  if (m_iMaxSize > 64 || m_iMaxSize < 0)
  {
    m_iMaxSize = 64;
  }
}

/****************************************************************************/
/*! returns the state of a bit
    \param iIndex : Index of the bit (0 to 63)
    \param pError : Optional parameter to receive the error (wrong index)
    \retval true : Bit is set
    \retval false: Bit is not set
*/
/****************************************************************************/
bool TBitCodedValue::getBit(Int iIndex, bool* pError /*= NULL*/) const
{
  bool bRetval = false;
  if (iIndex < m_iMaxSize && iIndex >= 0)
  {
    Uint64 uldValue = (Uint64)1 << iIndex;
    bRetval = ((uldValue & m_uldBitArray) != 0);
  }
  else if (pError != NULL)
  {
    *pError = true;
  }
  return bRetval;
}

/****************************************************************************/
/*! Returns the first bit index of a bit set to 1. This method implements
    the de Bruijn algorithm
    (see http://supertech.csail.mit.edu/papers/debruijn.pdf).
    \retval >= 0 : Index of bit set
    \retval INVALID_INDEX : No bit is set
*/
/****************************************************************************/
Int TBitCodedValue::getFirstBitSet() const
{
  return getFirstBitSet(TInt::MaxUint64);
}

/****************************************************************************/
/*! Returns the first bit index of a bit set to 1. This method implements
    the de Bruijn algorithm
    (see http://supertech.csail.mit.edu/papers/debruijn.pdf).
    \param uldMask : Mask to mask out the interesting bits
    \retval >= 0 : Index of bit set
    \retval INVALID_INDEX : No bit is set
*/
/****************************************************************************/
Int TBitCodedValue::getFirstBitSet(Uint64 uldMask) const
{
  Int iRetval = INVALID_INDEX;
  Int64 ldVal = static_cast<Int64>(m_uldBitArray & uldMask);

  if (ldVal != 0)
  {
    #if defined(_MSC_VER)
      const Uint64 uldDebruijn64 = 0x07EDD5E59A4E28C2ui64;
    #else
      const Uint64 uldDebruijn64 = 0x07EDD5E59A4E28C2ULL;
    #endif

    Uint uiArrayIndex = static_cast<Uint>((static_cast<Uint64>(ldVal & -ldVal) * uldDebruijn64) >> 58);

    if (uiArrayIndex < 64)
    {
      iRetval = aDeBruijnMap[uiArrayIndex];
    }
  }
  return iRetval;
}


/****************************************************************************/
/*! Returns the last bit index of a bit set to 1 
    \retval >= 0 : Index of bit set
    \retval INVALID_INDEX : No bit is set
*/
/****************************************************************************/
Int TBitCodedValue::getLastBitSet() const
{
  return getLastBitSet(TInt::MaxUint64);
}

/****************************************************************************/
/*! Returns the last bit index of a bit set to 1
    \param uldMask : Mask to mask out the interesting bits
    \retval >= 0 : Index of bit set
    \retval INVALID_INDEX : No bit is set
*/
/****************************************************************************/
Int TBitCodedValue::getLastBitSet(Uint64 uldMask) const
{
  //TODO: Finding a faster way to compute it backwards
  Int iRetval = INVALID_INDEX;
  Int64 ldVal = static_cast<Int64>(m_uldBitArray & uldMask);

  while(ldVal != 0)
  {
    ldVal >>= 1;
    iRetval++;
  }
  return iRetval;
}


/***************************************************************************/
/*! inverts an indexed bit
    \param iIndex : Index of the bit
*/
/***************************************************************************/
bool TBitCodedValue::invertBit(Int iIndex)
{
  bool bRetval = false;
  if (iIndex < m_iMaxSize && iIndex >= 0)
  {
    Uint64 uldValue = (Uint64)1 << iIndex;
    m_uldBitArray ^= uldValue;
    bRetval = true;
  }
  return bRetval;
}


/****************************************************************************/
/*! sets the state of a bit
    \param iIndex : Index of the bit (0 to 63)
    \param bState : state of the bit
    \retval true : Bit state has been set
    \retval false: wrong index
*/
/****************************************************************************/
bool TBitCodedValue::setBit(Int iIndex, bool bState)
{
  bool bRetval = false;
  if (iIndex < m_iMaxSize && iIndex >= 0)
  {

    Uint64 uldValue = (Uint64)1 << iIndex;
    if (bState)
    {
      m_uldBitArray |= uldValue;
    }
    else
    {
      m_uldBitArray &= ~uldValue;
    }
    bRetval = true;
  } //(iIndex < sizeof(m_uldBitArray) && iIndex >= 0)
  return bRetval;
}

/***************************************************************************/
/*! sets a bit range from iFromIndex to iToIndex. If the range is too small
    for the given value not all bit can be set. The method returns false.
    The content of the bit coded value does not change, if this method returned
    false. If the force-flag is set this method will ignore if not all bits
    could be set.
    \param iFromIndex: from index
    \param iToIndex : to index
    \param ldValue : Value to set
    \param bForce : force setting range even bits are not completly set
    \param false : wrong index or bits can not be set (value unchanged)
    \param true : changes has been performed
*/
/***************************************************************************/
bool TBitCodedValue::setBitRange(Int iFromIndex, Int iToIndex, Uint64 uldValue, bool bForce /**= false*/)
{
  bool bRetval = false;
  if (iFromIndex < m_iMaxSize &&
      iFromIndex >= 0 &&
      iFromIndex <= iToIndex)
  {
    //creates a mask
    // a) f.e. setBitRange(0, 4, x) -> 11111111 11111111 11111111 11100000
    // b) f.e. setBitRange(5, 8, x) -> 11111111 11111111 11111110 00011111
    Uint64 uldMask = 0;
    for( Int i = 64-1; i >= 0; --i)
    {
      uldMask <<= (Uint64)1;
      if (i < iFromIndex || i > iToIndex)
      {
        uldMask |= 1;
      }
    }

    //check if the range is too small
    if (!bForce)
    {
      // 1st check: check if uldValue is too large
      Uint64 uldTempValue = uldValue << iFromIndex;
      Uint64 uldTempValue2 = uldTempValue >> iFromIndex;
      bRetval = (uldTempValue2 == uldValue);

      //2nd check: mask is big enough so no bits get lost
      bRetval &= (uldTempValue == (uldTempValue & ~uldMask));
    }


    // Do not check ranges
    if (bForce || bRetval)
    {
      // a) f.e. setBitRange(0, 4, 2):
      //    uldTempValue          00000000 00000000 00000000 00000010
      //    uiMask                11111111 11111111 11111111 11100000
      //    m_uldBitArray before  11010001 01001000 11011000 10010101
      //    m_uldBitArray after   11010001 01001000 11011000 10000010

      Uint64 uldTempValue = uldValue << iFromIndex;
      m_uldBitArray = (uldMask & m_uldBitArray) | (uldTempValue & ~uldMask);
      bRetval = true;
    } //(bForce || bRetval)
  }
  return bRetval;
}

/***************************************************************************/
/*! converts a bit coded value into a binary output
*/
/***************************************************************************/
/*static*/ TString TBitCodedValue::convertToBinary(Uint64 uldValue, Int iMaxSize, bool bTrimZeros /*= false*/)
{
  if (iMaxSize <= 0)
  {
    iMaxSize = 1;
  }
  wchar_t* pwcBuffer = new wchar_t[iMaxSize+1];
  pwcBuffer[iMaxSize] = 0x0000;

  for(Int i = iMaxSize-1; i >= 0; --i)
  {
    if ((uldValue & 1) == 1)
    {
      pwcBuffer[i] = L'1';
    }
    else
    {
      pwcBuffer[i] = L'0';
    }
    uldValue >>= 1;
  }

  TString strRetval(pwcBuffer);

  delete [] pwcBuffer;

  if (bTrimZeros)
  {
    strRetval = TString::trimExt(strRetval, TString(L"0"), true, false);
    if (strRetval.isEmpty())
    {
      strRetval = L"0";
    }
  }

  return TString(L"0b") + strRetval;
}

/***************************************************************************/
/*! converts a bit coded value into a hex output
*/
/***************************************************************************/
/*static*/ TString TBitCodedValue::convertToHex(Uint64 uldValue, Int iMaxSize, bool bTrimZeros /*= false*/)
{
  Int iMaxSizeEff = iMaxSize/4;
  if (iMaxSize <= 0 || iMaxSize%4 != 0)
  {
    iMaxSizeEff = 1;
  }

  wchar_t* pwcBuffer = new wchar_t[iMaxSizeEff+1];
  pwcBuffer[iMaxSizeEff] = 0x0000;

  for(Int i = iMaxSizeEff-1; i >= 0; --i)
  {
    switch(uldValue & 0xF)
    {
      case 0:
      default: //fall through
        pwcBuffer[i] = L'0';
      break;

      case 1:
        pwcBuffer[i] = L'1';
      break;

      case 2:
        pwcBuffer[i] = L'2';
      break;

      case 3:
        pwcBuffer[i] = L'3';
      break;

      case 4:
        pwcBuffer[i] = L'4';
      break;

      case 5:
        pwcBuffer[i] = L'5';
      break;

      case 6:
        pwcBuffer[i] = L'6';
      break;

      case 7:
        pwcBuffer[i] = L'7';
      break;

      case 8:
        pwcBuffer[i] = L'8';
      break;

      case 9:
        pwcBuffer[i] = L'9';
      break;

      case 10:
        pwcBuffer[i] = L'A';
      break;

      case 11:
        pwcBuffer[i] = L'B';
      break;

      case 12:
        pwcBuffer[i] = L'C';
      break;

      case 13:
        pwcBuffer[i] = L'D';
      break;

      case 14:
        pwcBuffer[i] = L'E';
      break;

      case 15:
        pwcBuffer[i] = L'F';
      break;
    }
    uldValue >>= 4;
  }

  TString strRetval(pwcBuffer);
  delete [] pwcBuffer;

  if (bTrimZeros)
  {
    strRetval = TString::trimExt(strRetval, TString(L"0"), true, false);
    if (strRetval.isEmpty())
    {
      strRetval = L"0";
    }
  }

  return TString(L"0x") + strRetval;
}


/**************************************************************************/
/*! converts a string in hex notation into a int64 value
    \param rString : string to convert
    \param rError : return value. True = Convertion was successfully
    \param iPredef : pre definition value to return if the string is not valid
    \return int64 value
*/
/**************************************************************************/
/*static*/ Int64 TBitCodedValue::convertHexToInt64(const TString& rString, bool& rError, Int64 ldPredef /*=0*/)
{
  Int64 ldValue = 0;
  rError = false;

  Int iSize = rString.getSize();
  if (iSize > 2) //TODO: Border for Int32 or Int64
  {
    for (Int i = 2; i < iSize && !rError; i++)
    {
      ldValue <<= 4;
      wchar_t wcChar = rString.getChar(i);
      if(wcChar >= L'1' && wcChar <= L'9')
      {
        ldValue += (wcChar - L'1'  + 1);
      }
      else if (wcChar >= L'A' && wcChar <= L'F')
      {
        ldValue += (wcChar - L'A' + 10);
      }
      else if (wcChar != L'0')
      {
        rError = true;
        ldValue = ldPredef;
      }
    }
  } //(iSize > 2)
  else
  {
    ldValue = ldPredef;
    rError = true;
  }

  return ldValue;
}


/**************************************************************************/
/*! converts a string in binary notation into a int64 value
    \param rString : string to convert
    \param rError : return value. True = Convertion was successfully
    \param iPredef : pre definition value to return if the string is not valid
    \return int64 value
*/
/**************************************************************************/
/*static*/ Int64 TBitCodedValue::convertBinaryToInt64(const TString& rString, bool& rError, Int64 ldPredef /*= 0*/)
{
  Int64 ldValue = 0;
  rError = false;

  Int iSize = rString.getSize();
  if (iSize > 2) //TODO: Border for Int32 or Int64
  {
    for (Int i = 2; i < iSize && !rError; i++)
    {
      ldValue <<= 1;
      wchar_t wcChar = rString.getChar(i);
      if(wcChar == L'1')
      {
        ldValue += 1;
      }
      else if (wcChar != L'0')
      {
        rError = true;
        ldValue = ldPredef;
      }
    }
  } //(iSize > 2)
  else
  {
    rError = true;
    ldValue = ldPredef;
  }
  return ldValue;
}
