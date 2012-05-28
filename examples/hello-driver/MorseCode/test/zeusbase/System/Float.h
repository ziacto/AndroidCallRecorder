/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Float
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 4.08.08 7:31 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Float.h $
** 
** 19    4.08.08 7:31 Bha
** new methods to compare float values
** 
** 18    27.05.08 7:43 Bha
** Method delegation to math class
** 
** 17    8.01.08 6:53 Bha
** Qualification of numbers extended
** 
** 16    7.01.08 9:03 Bha
** new methods to handle floats implemented
** 
** 15    30.10.07 16:43 bha
** log-method for any base implemented
** 
** 14    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 13    3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
** 
** 12    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
**
** 5     5.10.06 6:36 bha
** New operators for Int and int
**
** 2     20.09.06 17:43 bha
** format method implemented
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef FloatH
#define FloatH

#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/ZValueType.hpp>
#include <zeusbase/System/Time.h>
#include <zeusbase/Math/Math.hpp>

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! This class implements usefull methods to modify float values
    \todo: Redesign this class for Float typedef. Select the correct
           API functions according the Float type (32, 64 or 80 bits)
*/
/**************************************************************************/
zeusbase_class TFloat : public TZValueType<Float>
{
  public:
    TFloat();
    TFloat(const TFloat& rValue);
    TFloat(Float fValue);
    TFloat(const IString& rValue);
    virtual ~TFloat();

    bool equals(Float fValue, Float fPrecision) const;

    //Delegated methods of Math.hpp
    inline Float round() const { return TMath::round(m_tValue); }
    inline Float roundEx(Float fPrecision) const { return TMath::roundEx(m_tValue, fPrecision); }
    inline Float ceil() const  { return TMath::ceil(m_tValue); }
    inline Float floor() const { return TMath::floor(m_tValue); }
    inline Int roundInt() const { return TMath::roundInt(m_tValue); }
    inline Int ceilInt() const  { return TMath::ceilInt(m_tValue); }
    inline Int floorInt() const { return TMath::floorInt(m_tValue); }

    TString format(Float fRoundPrecision = 0,
                   Uint uiTailingZeros = 0,
                   Uint uiLeadingZeros = 1) const;
    bool isZero() const;
    bool isNonZero() const;
    bool isInfinity() const;
    bool isPosInfinity() const;
    bool isNegInfinity() const;
    bool isNaN() const;
    Float getFactorial() const;


    //Operators
    bool operator ==(const TFloat& rValue)const;
    bool operator ==(const Float fValue)const;
    bool operator !=(const TFloat& rValue)const;
    bool operator !=(const Float fValue)const;

    //static methods
    static bool equalsFloat(Float fValue1, Float fValue2, Float fPrecision = FLOAT_PRECISION);
    static bool isZero(const Float& fValue, Float fPrecision = FLOAT_PRECISION);
    static bool isNonPositive(const Float& f, Float fPrecision = FLOAT_PRECISION);
    static bool isNonNegative(const Float& f, Float fPrecision = FLOAT_PRECISION);
    inline static bool isNonZero(const Float& fValue, Float fPrecision = FLOAT_PRECISION)      { return !isZero(fValue, fPrecision); }
    inline static bool isPositive(const Float& fValue, Float fPrecision = FLOAT_PRECISION)     { return !isNonPositive(fValue, fPrecision); }
    inline static bool isNegative(const Float& fValue, Float fPrecision = FLOAT_PRECISION)     { return !isNonNegative(fValue, fPrecision); }
    inline static bool isGreater(const Float& rfValue1, const Float& rfValue2, const Float& rfPrecision = FLOAT_PRECISION)      { return isNegative(rfValue2- rfValue1, rfPrecision); }
    inline static bool isGreaterEqual(const Float& rfValue1, const Float& rfValue2, const Float& rfPrecision = FLOAT_PRECISION) { return isNonPositive(rfValue2- rfValue1, rfPrecision); }
    inline static bool isLower(const Float& rfValue1, const Float& rfValue2, const Float& rfPrecision = FLOAT_PRECISION)        { return isPositive(rfValue2- rfValue1, rfPrecision); }
    inline static bool isLowerEqual(const Float& rfValue1, const Float& rfValue2, const Float& rfPrecision = FLOAT_PRECISION)   { return isNonNegative(rfValue2- rfValue1, rfPrecision); }

    static bool isInfinity(Float fValue);
    static bool isNaN(Float fValue);

    static Float getFactorial(Float fVal);

    static Float randomFloat(Float fFrom, Float fTo);
    static Float32 randomFloat32();
    static Float64 randomFloat64();

    //constants
    static const Float NaN;
    static const Float Infinity;
    static const Float NegInfinity;
    static const Float MaxValue;
    static const Float MinValue;
    static const Float MaxValue32bit;
    static const Float MinValue32bit;

  protected:
    static Float m_fStaticPrecision;
};


/**************************************************************************/
/*! Destroys the float value
*/
/**************************************************************************/
inline TFloat::~TFloat()
{}

/**************************************************************************/
/*! Checks if the float object is infinity (positive or negative)
    \retval true : floating number is infinity
    \retval false: not infinity
*/
/**************************************************************************/
inline bool TFloat::isInfinity() const
{
  return TFloat::isInfinity(m_tValue);
}

/**************************************************************************/
/*! returns true if the value is positive and infinity
*/
/**************************************************************************/
inline bool TFloat::isPosInfinity() const
{
  return (isInfinity() && m_tValue > 0);
}

/**************************************************************************/
/*! returns true if the value is negative and infinity
*/
/**************************************************************************/
inline bool TFloat::isNegInfinity() const
{
  return (isInfinity() && m_tValue < 0);
}

/**************************************************************************/
/*! Checks if the float object is not a number
    \retval true : not a number
    \retval false: a number
*/
/**************************************************************************/
inline bool TFloat::isNaN() const
{
  return TFloat::isNaN(m_tValue);
}

/**************************************************************************/
/*! This factorial method uses the
    Stirling's approximation (Formula from wikipedia)
*/
/**************************************************************************/
inline Float TFloat::getFactorial() const
{
  return TFloat::getFactorial(m_tValue);
}


/**************************************************************************/
/*! equals operator to check if two floats are the same
*/
/**************************************************************************/
inline bool TFloat::operator ==(const TFloat& rValue)const
{
  return TFloat::equalsFloat(m_tValue, rValue.m_tValue, m_fStaticPrecision);
}

/**************************************************************************/
/*! equals operator to check if two floats are the same
*/
/**************************************************************************/
inline bool TFloat::operator ==(const Float fValue)const
{
  return TFloat::equalsFloat(m_tValue, fValue, m_fStaticPrecision);
}

/**************************************************************************/
/*! not-equals operator to check if two floats are not the same
*/
/**************************************************************************/
inline bool TFloat::operator !=(const TFloat& rValue)const
{
  return !TFloat::equalsFloat(m_tValue, rValue.m_tValue, m_fStaticPrecision);
}

/**************************************************************************/
/*! not-equals operator to check if two floats are not the same
*/
/**************************************************************************/
inline bool TFloat::operator !=(const Float fValue)const
{
  return !TFloat::equalsFloat(m_tValue, fValue, m_fStaticPrecision);
}

/**************************************************************************/
/*! this method checks if a float value is equal to this float object
    \param fValue : Value to check
    \param fPrecision : How precise the check will be
    \retval true : double values are equal within the precision
    \retval false: Values are not equal
*/
/**************************************************************************/
inline bool TFloat::equals(Float fValue, Float fPrecision) const
{
  return TFloat::equalsFloat(m_tValue, fValue, fPrecision);
}

/**************************************************************************/
/*! Checks if the float number is zero using a precision value
    \param fPrecision : precision value
    \retval true : value is zero within the given precision
    \retval false: value is not zero
*/
/**************************************************************************/
inline bool TFloat::isZero() const
{
  return TFloat::equalsFloat(m_tValue, 0, FLOAT_PRECISION);
}

/**************************************************************************/
/*! Checks if the float number is non zero using a precision value
    \param fPrecision : precision value
    \retval true : value is non zero within the given precision
    \retval false: value is zero
*/
/**************************************************************************/
inline bool TFloat::isNonZero() const
{
  return TFloat::isNonZero(m_tValue, FLOAT_PRECISION);
}


/**************************************************************************/
/*! Checks if two float values are the same
    \param fValue1 : Value to check
    \param fValue2 : Value to check
    \param fPrecision : How precise the check will be
    \retval true : double values are equal within the precision
    \retval false: Values are not equal
*/
/**************************************************************************/
inline /*static*/ bool TFloat::equalsFloat(Float fValue1, Float fValue2, Float fPrecision)
{
  return (::fabs(fValue1 - fValue2) < fPrecision);
}

/**************************************************************************/
/*! Checks if a float number is zero using a precision value
    \param fValue : Value to check
    \param fPrecision : precision value
    \retval true : value is zero within the given precision
    \retval false: value is not zero
*/
/**************************************************************************/
inline /*static*/ bool TFloat::isZero(const Float& fValue, Float fPrecision /*= FLOAT_PRECISION*/)
{
  return (::fabs(fValue) < fPrecision);
}

/******************************************************************************/
/*! positivity of a float value.

    \param f          [IN]: Float value.
    \param fPrecision [IN]: Numerical tolerance.

    \retval true : f is numerically positive or zero.
    \retval false : f is numerically negative.
*/
/******************************************************************************/
inline /*static*/ bool TFloat::isNonNegative(const Float& f, Float fPrecision /*= FLOAT_PRECISION*/)
{
  return (f > -fPrecision);
}

/******************************************************************************/
/*! negativity of a float value.

    \param f          [IN]: Float value.
    \param fPrecision [IN]: Numerical tolerance.

    \retval true : f is numerically negative or zero.
    \retval false : f is numerically positive.
*/
/******************************************************************************/
inline /*static*/ bool TFloat::isNonPositive(const Float& f, Float fPrecision /*= FLOAT_PRECISION*/)
{
  return (f < fPrecision);
}

/***************************************************************************/
/*! Returns a random float number, witch is between from and to
    \param fFrom : lower limit
    \param fTo  :upper limit
    \return random number
*/
/***************************************************************************/
inline /*static*/ Float TFloat::randomFloat(Float fFrom, Float fTo)
{
  return TTime::randomFloat(fFrom, fTo);
}

/***************************************************************************/
/*! returns a random number of float32 values
*/
/***************************************************************************/
inline /*static*/ Float32 TFloat::randomFloat32()
{
  return (Float32) TTime::randomFloat(TFloat::MinValue32bit, TFloat::MaxValue32bit);
}

/***************************************************************************/
/*! returns a random number of float64 values
*/
/***************************************************************************/
inline /*static*/ Float64 TFloat::randomFloat64()
{
  return TTime::randomFloat(TFloat::MinValue, TFloat::MaxValue);
}


END_NAMESPACE_Zeus

//---------------------------------------------------------------------------
#endif
