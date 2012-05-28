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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Int.cpp $
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
** 2     20.09.06 17:43 bha
** format method implemented
***************************************************************************/
//---------------------------------------------------------------------------

#include <zeusbase/System/Int.h>

USING_NAMESPACE_Zeus

const Int8   TInt::MaxInt8    = CHAR_MAX;
const Int8   TInt::MinInt8    = CHAR_MIN;
const Int16  TInt::MaxInt16   = SHRT_MAX;
const Int16  TInt::MinInt16   = SHRT_MIN;
const Int32  TInt::MaxInt32   = LONG_MAX;
const Int32  TInt::MinInt32   = LONG_MIN;
const Uint8  TInt::MaxUint8   = UCHAR_MAX;
const Uint16 TInt::MaxUint16  = USHRT_MAX;
const Uint32 TInt::MaxUint32  = ULONG_MAX;

#if defined(__GNUC__) 
  const Int64  TInt::MaxInt64  = 9223372036854775807LL;
  const Int64  TInt::MinInt64  = (-TInt::MaxInt64 - 1LL);
  const Uint64 TInt::MaxUint64 = 0xFFFFFFFFFFFFFFFFULL;
#else
  const Int64  TInt::MaxInt64  = _I64_MAX;
  const Int64  TInt::MinInt64  = _I64_MIN;
  const Uint64 TInt::MaxUint64 = _UI64_MAX;
#endif

/***************************************************************************/
/*! Creates an empty Int-Object
*/
/***************************************************************************/
TInt::TInt() : TZValueType<Int>()
{}

/***************************************************************************/
/*! Creates a Int-Object
    \param iValue : Initial value
*/
/***************************************************************************/
TInt::TInt(Int iValue) : TZValueType<Int>(iValue)
{}

/***************************************************************************/
/*! copy constructor
*/
/***************************************************************************/
TInt::TInt(const TInt& rIn) : TZValueType<Int>(rIn)
{}


/***************************************************************************/
/*! Destroys the int object
*/
/***************************************************************************/
TInt::~TInt()
{
}

/***************************************************************************/
/*! This converts the int value into a string
    \param uiLeadingZeros : How many leading zeros the formated output
                            must have
    \return return of the formated output
*/
/***************************************************************************/
TString TInt::format(Uint uiLeadingZeros) const
{
  TString strRetval(m_tValue);

  if (uiLeadingZeros > 0)
  {
    Int iEndPos = strRetval.getSize();

    //inserts at i the leading zeros
    // i = 0 if no '-' has been found
    // else i = pos('-') + 1
    Int iInsertPos = strRetval.getFirstPos(L"-");
    ++iInsertPos;

    Int iDigitsToAdd = uiLeadingZeros - (iEndPos - iInsertPos);
    if (iDigitsToAdd > 0)
    {
      strRetval = strRetval.insert(iInsertPos, TString(L'0', iDigitsToAdd));
    }
  }
  return strRetval;
}

/***************************************************************************/
/*! returns the number of digits to show the number in a specific base of
    numbers (such as decimal, binary etc.). Note that this method will not
    return any digit (space) used for signs. This method returns the digits
    in a mathematical way (not space needed).
    \param iValue : Number to check
    \param iNumBase : Base of number system
    \return number of digits
*/
/***************************************************************************/
/*static*/ Int TInt::getDigitCount(Int iValue, Uint uiNumBase)
{
  Int iRetval = 1;

  if (iValue < 0)
  {
    iValue *= -1;
  }

  while(iValue >= (Int)uiNumBase)
  {
    iRetval++;
    iValue /= (Int)uiNumBase;
  }
  return iRetval;
}

/***************************************************************************/
/*! Returns the factorial of a number. Note that this function can only
    handle n up to 20
    \param iVal : number n
    \return n!
*/
/***************************************************************************/
/*static*/ Int64 TInt::getFactorial(Int iVal)
{
  Int64 iRetval = 1;
  if (iVal > 0)
  {
    for(Int i = 2; i <= iVal; i++)
    {
      iRetval *= i;
    }
  }
  return iRetval;
}


/***************************************************************************/
/*! factorizes the number and returns a map containing the factor (key) and
    its potential (value).
    \param iValue : Number to factorize
    \param rFactors : return value. Map contains the factors (key) and the
    potentials (value of map)
*/
/***************************************************************************/
/*static*/ void TInt::factorize(Int iValue, IMap<Int, Int>& rFactors)
{
  rFactors.clear();
  bool bNegNumber = (iValue < 0);
  if (bNegNumber)
  {
    iValue *= -1;
  }

  //factorizing loop
  Int iEnd = iValue/2;
  for(Int i = 2; i < iEnd; i++)
  {
    Int iCount = 0;
    while (iValue % i == 0)
    {
      iValue = iValue/i;
      ++iCount;
    }
    if (iCount > 0)
    {
      rFactors.setItem(i, iCount);
    }
  }

  //prime number
  if (rFactors.isEmpty())
  {
    rFactors.setItem(iValue, 1);
  }

  //no factorization -> prime number
  if (bNegNumber)
  {
    rFactors.setItem(-1, 1);
  }
}


/***************************************************************************/
/*! checks if a number is prime
    \param iValue : Number to check. Note that all negative value are rejected
                    by this method. If iValue equals 0 or 1
                    the method will return false.
    \retval true : Number is prime
    \retval false: Number is not prime
*/
/***************************************************************************/
/*static*/ bool TInt::isPrime(Int iValue)
{
  bool bRetval = (iValue > 1);
  if (bRetval)
  {
    Int iEnd = iValue/2;

    for (Int i = 2; (i <= iEnd && bRetval); i++)
    {
      bRetval &= (iValue % i != 0);
    }
  }
  return bRetval;
}

/***************************************************************************/
/*! A fast way to get the logarithm to the base of 2
*/
/***************************************************************************/
/*static*/ Int TInt::log2(Int iValue)
{
  Int k;
  for ( k = 1; (iValue = iValue / 2) != 1; k++)
  {
  }
  return k;
}

