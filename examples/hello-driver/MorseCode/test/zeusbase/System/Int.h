/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Int
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 24.01.08 13:51 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Int.h $
** 
** 15    24.01.08 13:51 Bha
** Max int constants renamed
** 
** 14    7.01.08 9:02 Bha
** getFactorial() method implemented
** 
** 13    1.11.07 6:36 bha
** fast logarithm for base 2 implemented
** 
** 12    11.10.07 6:59 bha
** Implemented prime check and factorization
** 
** 11    26.02.07 9:00 bha
**
** 2     20.09.06 17:43 bha
** format method implemented
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef IntH
#define IntH
//---------------------------------------------------------------------------

#include <zeusbase/System/ZValueType.hpp>
#include <zeusbase/System/BitCodedValue.h>
#include <zeusbase/System/Time.h>
#include <zeusbase/System/Interfaces/IMap.hpp>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This class implements a wrapper for int-values
*/
/***************************************************************************/
zeusbase_class TInt : public TZValueType<Int>
{
  public:
    TInt();
    TInt(Int iValue);
    TInt(const TInt& rIn);
    virtual ~TInt();

    void factorize(IMap<Int, Int>& rFactors) const;
    TString format(Uint uiLeadingZeros) const;
    Int getDigitCount(Uint uiNumBase = 10) const;
    Int64 getFactorial() const;
    bool isPrime() const;
    TString toBinary(bool bTrimZeros = false) const;
    TString toHex(bool bTrimZeros = false) const;


    static void factorize(Int iValue, IMap<Int, Int>& rFactors);
    static Int getDigitCount(Int iValue, Uint uiNumBase);
    static Int64 getFactorial(Int iVal);
    static bool isPrime(Int iValue);
    static Int log2(Int iValue);

    static Int randomInt(Int iFrom, Int iTo);
    static Int8 randomInt8();
    static Int16 randomInt16();
    static Int32 randomInt32();
    static Int64 randomInt64();
    static Int64 randomInt64(Int64 ldFrom, Int64 ldTo);

    //constants
    static const Int8   MaxInt8;
    static const Int8   MinInt8;
    static const Int16  MaxInt16;
    static const Int16  MinInt16;
    static const Int32  MaxInt32;
    static const Int32  MinInt32;
    static const Int64  MaxInt64;
    static const Int64  MinInt64;
    static const Uint8  MaxUint8;
    static const Uint16 MaxUint16;
    static const Uint32 MaxUint32;
    static const Uint64 MaxUint64;

  protected:

};

//Inline methods
/***************************************************************************/
/*! Returns the number of digits representing this number.
*/
/***************************************************************************/
inline Int TInt::getDigitCount(Uint uiNumBase /*= 10*/) const
{
  return TInt::getDigitCount(this->m_tValue, uiNumBase);
}

/***************************************************************************/
/*! Returns the factorial of a number such as 7! = 1*2*3 ..*7
*/
/***************************************************************************/
inline Int64 TInt::getFactorial() const
{
  return TInt::getFactorial(this->m_tValue);
}

/***************************************************************************/
/*! factorizes the number and returns a map containing the factor (key) and
    its potential (value).
*/
/***************************************************************************/
inline void TInt::factorize(IMap<Int, Int>& rFactors) const
{
  TInt::factorize(this->m_tValue, rFactors);
}

/***************************************************************************/
/*! Checks if a number is prime
*/
/***************************************************************************/
inline bool TInt::isPrime() const
{
  return TInt::isPrime(this->m_tValue);
}

/***************************************************************************/
/*! Returns a random integer number, witch is between iFrom and iTo
    \param iFrom : lower limit
    \param iTo  :upper limit
    \return random number
*/
/***************************************************************************/
inline /*static*/ Int TInt::randomInt(Int iFrom, Int iTo)
{
  return TTime::randomInt(iFrom, iTo);
}

/***************************************************************************/
/*! returns a random number of int8 values
*/
/***************************************************************************/
inline /*static*/ Int8 TInt::randomInt8()
{
  return static_cast<Int8>(TTime::randomInt(TInt::MinInt8, TInt::MaxInt8));
}

/***************************************************************************/
/*! returns a random number of int16 values
*/
/***************************************************************************/
inline /*static*/ Int16 TInt::randomInt16()
{
  return static_cast<Int16>(TTime::randomInt(TInt::MinInt16, TInt::MaxInt16));
}

/***************************************************************************/
/*! returns a random number of int32 values
*/
/***************************************************************************/
inline /*static*/ Int32 TInt::randomInt32()
{
  return static_cast<Int32>(TTime::randomInt(TInt::MinInt32, TInt::MaxInt32));
}

/***************************************************************************/
/*! returns a random number of int64 values
*/
/***************************************************************************/
inline /*static*/ Int64 TInt::randomInt64()
{
  Int iRandMax = RAND_MAX/2;
  Float dValue = TTime::random(-iRandMax, iRandMax)/(double)iRandMax;
  Int64 ldValue = static_cast<Int64>(dValue * TInt::MaxInt64);
  return ldValue;
}

/***************************************************************************/
/*! Returns a random 64 bit integer number, witch is between ldFrom and ldTo
    \param ldFrom : lower limit
    \param ldTo  :upper limit
    \return random number
*/
/***************************************************************************/
inline /*static*/ Int64 TInt::randomInt64(Int64 ldFrom, Int64 ldTo)
{
  Int iRandMax = RAND_MAX;
  Float dValue = TTime::random(0, iRandMax)/(double)iRandMax;
  Int64 ldValue = static_cast<Int64>(dValue * ldTo);
  return ldFrom + ldValue;
}

/***************************************************************************/
/*! This converts the int-value into the binary notation.
    \param bTrimZeros : if this flag is set it will trim all leading zeros
                        0x000011010 -> 0x11010
*/
/***************************************************************************/
inline TString TInt::toBinary(bool bTrimZeros /*= false*/) const
{
  return TBitCodedValue::convertToBinary(this->m_tValue, 32, bTrimZeros);
}

/***************************************************************************/
/*! This converts the int-value into the hex notation.
    \param bTrimZeros : if this flag is set it will trim all leading zeros
                        0x0000FFA2 -> 0xFFA2
*/
/***************************************************************************/
inline TString TInt::toHex(bool bTrimZeros /*= false*/) const
{
  return TBitCodedValue::convertToHex(this->m_tValue, 32, bTrimZeros);
}

END_NAMESPACE_Zeus

#endif
