/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Float
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 27.05.08 7:43 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Float.cpp $
** 
** 14    27.05.08 7:43 Bha
** Method delegation to math class
** 
** 13    7.01.08 9:03 Bha
** new methods to handle floats implemented
** 
** 12    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
**
** 2     20.09.06 17:43 bha
** format method implemented
***************************************************************************/
//---------------------------------------------------------------------------

#include <zeusbase/System/Float.h>
#include <zeusbase/System/Int.h>
#include <float.h>
#include <math.h>
//---------------------------------------------------------------------------

USING_NAMESPACE_Zeus

#ifndef M_PI
  #define M_PI        3.14159265358979323846 // Extracted from Borland <math.h>. Not provided by VS 6.0.
#endif


//initialisation of static members
#if defined(__GNUC__)
  const Float TFloat::NaN = NAN;
  const Float TFloat::Infinity = INFINITY;
  const Float TFloat::NegInfinity = -INFINITY;
#else
  #if defined(_MSC_VER)
    #include <limits>
    const Float TFloat::NaN = std::numeric_limits<double>::quiet_NaN();
    const Float TFloat::Infinity = std::numeric_limits<double>::infinity();
    const Float TFloat::NegInfinity = -std::numeric_limits<double>::infinity();
  #else
    const Float TFloat::NaN = 0.0 / 0.0;
    const Float TFloat::Infinity = 1.0 / 0.0;
    const Float TFloat::NegInfinity = -1.0/0.0;
  #endif
#endif

const Float TFloat::MaxValue = DBL_MAX;
const Float TFloat::MinValue = DBL_MIN;
const Float TFloat::MaxValue32bit = FLT_MAX;
const Float TFloat::MinValue32bit = FLT_MIN;

/*static*/ Float TFloat::m_fStaticPrecision = FLOAT_PRECISION;


/**************************************************************************/
/*! Creates an empty float object
*/
/**************************************************************************/
TFloat::TFloat() : TZValueType<Float>()
{}

/**************************************************************************/
/*! Creates a float object out of an other float object
*/
/**************************************************************************/
TFloat::TFloat(const TFloat& rValue) : TZValueType<Float>(rValue)
{}

/**************************************************************************/
/*! Creates a float object out of an float
*/
/**************************************************************************/
TFloat::TFloat(Float fValue) : TZValueType<Float>(fValue)
{}

/**************************************************************************/
/*! Creates a float object out of a string value
*/
/**************************************************************************/
TFloat::TFloat(const IString& rValue) : TZValueType<Float>()
{
  m_tValue = rValue.toFloat(0.0);
}

/**************************************************************************/
/*! Formats the float object and returns the string. The format is specified
    by three parameters: <BR>
    \param dRoundPrecision : Rounding precision. 0 means no rounding (default)
                          see TMath::roundEx for more informations.
    \param ulTailingZeros : Tailing zeros (from decimal point). Default is 0.
    \param ulLeadingZeros : Leading zeros (from decimal point). Default is 1
    \return formated string output
*/
/**************************************************************************/
TString TFloat::format(Float fRoundPrecision /*= 0*/,
                       Uint uiTailingZeros /*= 0*/,
                       Uint uiLeadingZeros /*= 1*/) const
{
  TString strRetval(TMath::roundEx(m_tValue, fRoundPrecision));

  Int iDecimalPos = strRetval.getFirstPos(L".");
  if (uiTailingZeros > 0)
  {
    Int iDigitsToAdd = uiTailingZeros;
    if (iDecimalPos == -1)
    {
      strRetval += L".";
      iDecimalPos = strRetval.getSize() - 1;
    }
    else
    {
      iDigitsToAdd = uiTailingZeros - (strRetval.getSize() - iDecimalPos - 1);
    }

    if (iDigitsToAdd > 0)
    {
      strRetval += TString(L'0', iDigitsToAdd);
    }
  }

  if (uiLeadingZeros > 0)
  {
    if (iDecimalPos == -1)
    {
      iDecimalPos = strRetval.getSize();
    }

    //inserts at i the leading zeros
    // i = 0 if no '-' has been found
    // else i = pos('-') + 1
    Int iInsertPos = strRetval.getFirstPos(L"-");
    ++iInsertPos;

    Int iDigitsToAdd = uiLeadingZeros - (iDecimalPos - iInsertPos);
    if (iDigitsToAdd > 0)
    {
      strRetval = strRetval.insert(iInsertPos, TString(L'0', iDigitsToAdd));
    }
  }
  return strRetval;
}

/**************************************************************************/
/*! Checks if the float is infinity (positive or negative)
    \retval true : floating number is infinity
    \retval false: not infinity
*/
/**************************************************************************/
/*static*/ bool TFloat::isInfinity(Float fValue)
{
  #if defined(__GNUC__)
    int iClass = fpclassify(fValue);
    return (iClass == FP_INFINITE);
  #else

    // CAUTION:
    // DO NOT USE _fpclass OR _fpclassl
    // These two functions causes problem on Windows API. For example:
    // - The multiplication of two double-Values produces large inaccuracy
    //
    // int iClass = _fpclassl(dValue);
    // return (iClass == _FPCLASS_NINF || iClass == _FPCLASS_PINF);

    return (!_finite(fValue) && !TFloat::isNaN(fValue));
  #endif
}

/**************************************************************************/
/*! Checks if the float is not a number
    \retval true : not a number
    \retval false: a number
*/
/**************************************************************************/
/*static*/ bool TFloat::isNaN(Float fValue)
{
  #if defined(__GNUC__)
    return isnan(fValue);
  #else
    return (_isnan(fValue) != 0);
  #endif
}

/**************************************************************************/
/*! This factorial method uses the
    Srinivasa Ramanujan's approximation (Formula from wikipedia)
*/
/**************************************************************************/
/*static*/ Float TFloat::getFactorial(Float fVal)
{
  Float fRetval = 1;
  Int iVal = TFloat(fVal).roundInt();

  //For integer use the exact calculation
  if (equalsFloat(fVal, iVal))
  {
    fRetval = static_cast<Float>(TInt::getFactorial(iVal));
  }

  //for real numbers use the approximation
  else
  {
    //Srinivasa Ramanujan's approximation
    fRetval = exp( fVal * ::log(fVal) - fVal + (::log(fVal*(1+4*fVal*(1+2*fVal)))/6) + ::log(M_PI)/2 );

    //Stirling's approximation
    //fRetval = ::sqrt(2* M_PI * fVal)* pow((fVal / ::exp(1)), fVal);
  }
  return fRetval;

}


