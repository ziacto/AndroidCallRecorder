/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : Math
 * Package : Math
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 27.05.08 10:42 $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/Math/Math.hpp $
** 
** 12    27.05.08 10:42 Bha
** header define conflicts with borland header of math class
** 
** 11    27.05.08 7:41 Bha
** new math methods added for float and int signatures
** 
** 10    14.01.08 14:37 Bha
** gcd methods added
** 
** 9     3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
**
** 5     20.09.06 17:43 bha
** format method implemented
***************************************************************************/

#ifndef Zeus__MathHPP
#define Zeus__MathHPP

#include <zeusbase/Config/PlatformDefines.hpp>
#include <math.h>

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! This class contains generous mathematical functions
*/
/**************************************************************************/
class TMath
{
  public:
    /**************************************************************************/
    /*! rounds this value up
    */
    /**************************************************************************/
    inline static Float ceil(const Float& rfValue)
    {
      #if defined(__GNUC__)
        return ::ceil(rfValue);
      #elif defined(_MSC_VER)
        return ::ceil(rfValue);
      #else
        return std::ceil(rfValue);
      #endif
    }

    /**************************************************************************/
    /*! rounds this value up
    */
    /**************************************************************************/
    inline static Int ceilInt(const Float& rfValue)
    {
      return static_cast<Int>(TMath::ceil(rfValue));
    }

    /**************************************************************************/
    /*! returns the e^x
    */
    /**************************************************************************/
    inline static Float exp(const Float& rfX)
    {
      return ::exp(rfX);
    }

    /**************************************************************************/
    /*! returns the e^x as an integer
    */
    /**************************************************************************/
    inline static Int expInt(const Float& rfX)
    {
      return roundInt(TMath::exp(rfX));
    }

    /**************************************************************************/
    /*! rounds this value down
    */
    /**************************************************************************/
    inline static Float floor(const Float& rfValue)
    {
      #if defined(__GNUC__)
        return ::floor(rfValue);
      #elif defined(_MSC_VER)
        return ::floor(rfValue);
      #else
        return std::floor(rfValue);
      #endif
    }

    /**************************************************************************/
    /*! rounds this value down
    */
    /**************************************************************************/
    inline static Int floorInt(const Float& rfValue)
    {
      return static_cast<Int>(TMath::floor(rfValue));
    }

    /************************************************************************/
    /*! Returns the logarithm naturalis of rfValue
    */
    /************************************************************************/
    inline static Float ln(const Float& rfValue)
    {
      return ::log(rfValue);
    }

    /************************************************************************/
    /*! Returns the logarithm naturalis of rfValue as an integer
    */
    /************************************************************************/
    inline static Int lnInt(const Float& rfValue)
    {
      return roundInt(TMath::ln(rfValue));
    }

    /************************************************************************/
    /*! Returns the log(x,y)
    */
    /************************************************************************/
    inline static Float log(const Float& rfValue, const Float& rfBase)
    {
      return (::log(rfValue) / ::log(rfBase));
    }

    /************************************************************************/
    /*! Returns the log(x,y)
    */
    /************************************************************************/
    inline static Int logInt(const Float& rfValue, const Float& rfBase)
    {
      return static_cast<Int>(TMath::log(rfValue, rfBase));
    }

    /**********************************************************************/
    /*! Gets the maximum of two float values
        \param fD1 : value 1
        \param fD2 : value 2
        \return max(value 1, value 2)
    */
    /**********************************************************************/
    static Float maxFloat(Float fD1, Float fD2)
    {
      Float fRetval = fD1;
      if (fD1 < fD2)
      {
        fRetval = fD2;
      }
      return fRetval;
    }

    /**********************************************************************/
    /*! Gets the minimum of two float values
        \param d1 : value 1
        \param d2 : value 2
        \return min(value 1, value 2)
    */
    /**********************************************************************/
    static Float minFloat(Float fD1, Float fD2)
    {
      Float fRetval = fD1;
      if (fD1 > fD2)
      {
        fRetval = fD2;
      }
      return fRetval;
    }

    /**********************************************************************/
    /*! Gets the maximum of two int values
        \param iD1 : value 1
        \param iD2 : value 2
        \return max(value 1, value 2)
    */
    /**********************************************************************/
    static Int maxInt(Int iD1, Int iD2)
    {
      Int iRetval = iD1;
      if (iD1 < iD2)
      {
        iRetval = iD2;
      }
      return iRetval;
    }

    /**********************************************************************/
    /*! Gets the minimum of two int values
        \param iD1 : value 1
        \param iD2 : value 2
        \return min(value 1, value 2)
    */
    /**********************************************************************/
    static Int minInt(Int iD1, Int iD2)
    {
      Int iRetval = iD1;
      if (iD1 > iD2)
      {
        iRetval = iD2;
      }
      return iRetval;
    }

    /**********************************************************************/
    /*! calculates the power of base by exponent
        \param rfBase : Base
        \param rfExp : Exponent
        \return rfBase ^ rfExp
    */
    /**********************************************************************/
    inline static Float pow(const Float& rfBase, const Float& rfExp)
    {
      return ::pow(rfBase, rfExp);
    }

    /**********************************************************************/
    /*! calculates the power of base by exponent
        \param rfBase : Base
        \param rfExp : Exponent
        \return rfBase ^ rfExp
    */
    /**********************************************************************/
    inline static Int powInt(const Float& rfBase, const Float& rfExp)
    {
      return static_cast<Int>(::pow(rfBase, rfExp));
    }

    /**********************************************************************/
    /*! rounds a float value to an other float value
        \param fValue : value to round
        \param fPrecision : default is 1.0. Using 0.1 it will round to tenth
        \return round(dValue)
    */
    /**********************************************************************/
    static Float roundEx(Float fValue, Float fPrecision)
    {
      Float fRetval = fValue;
      if (fPrecision != 0.0)
      {
        Float fX = fValue/fPrecision;
        Float dXTest = fX - floor(fX);

        if (dXTest < 0.5)
        {
          fRetval = floor(fX)*fPrecision;
        }
        else
        {
          fRetval = ceil(fX)*fPrecision;
        }
      }
      return fRetval;
    }

    /**********************************************************************/
    /*! rounds a double value to a integer number
        \param rfValue : value to round
        \return round(rfValue)
    */
    /**********************************************************************/
    inline static Float round(const Float& rfValue)
    {
      return roundEx(rfValue, 1.0);
    }

    /**********************************************************************/
    /*! rounds a double value to a integer
        \param rfValue : value to round
        \return round(rfValue)
    */
    /**********************************************************************/
    inline static Int roundInt(const Float& rfValue)
    {
      return static_cast<Int>(roundEx(rfValue, 1.0));
    }

    /**********************************************************************/
    /*! returns the square root of a value
    */
    /**********************************************************************/
    inline static Float sqrt(const Float& rfValue)
    {
      return ::sqrt(rfValue);
    }

    /**********************************************************************/
    /*! returns the square root of a value as an integer
    */
    /**********************************************************************/
    inline static Int sqrtInt(const Float& rfValue)
    {
      return roundInt(TMath::sqrt(rfValue));
    }

    /**********************************************************************/
    /*! Returns the greatest common divisor of two numbers.
        The algorithm has been taken from
        http://en.wikipedia.org/wiki/Euclidean_algorithm
        \param iA : Number A
        \param iB : Number B
        \return greatest common divisor
    */
    /**********************************************************************/
    static Int gcd(Int iA, Int iB)
    {
      while (iB != 0)
      {
        Int iTemp = iB;
        iB = iA % iB;
        iA = iTemp;
      }
      return iA;
    }

    /**********************************************************************/
    /*! Returns the greatest common divisor of two numbers.
        This method implements the extended version, witch also returns
        the X and Y components, such that ax + by = gcd(a,b).
        The algorithm has been taken from
        http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
        \param iA : Number A
        \param iB : Number B
        \param rX : Return parameter of X component
        \param rY : Return parameter of Y component
        \return greatest common divisor
    */
    /**********************************************************************/
    static Int gcd(Int iA, Int iB, Int& rX, Int& rY)
    {
      rX = 1;
      rY = 0;
      Int iX1 = 0;
      Int iY1 = 1;
      while (iB != 0)
      {
        Int iTemp = iB;
        Int iQuotient = iA / iB; //integer div
        iB = iA % iB;
        iA = iTemp;

        iTemp = iX1;
        iX1 = rX - iQuotient * iX1;
        rX = iTemp;

        iTemp = iY1;
        iY1 = rY - iQuotient * iY1;
        rY = iTemp;
      }
      return iA;
    }

  protected:
    inline TMath() {}
    inline virtual ~TMath() {}
};

END_NAMESPACE_Zeus

#endif

