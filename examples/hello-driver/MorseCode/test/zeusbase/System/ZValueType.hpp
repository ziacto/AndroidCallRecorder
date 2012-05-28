/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ZValueType
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 16.04.08 15:48 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/ZValueType.hpp $
** 
** 2     16.04.08 15:48 Bha
** recursive call corrected
** 
** 1     25.09.06 7:17 bha
***************************************************************************/

#ifndef ZValueTypeH
#define ZValueTypeH

#include <zeusbase/System/ZObject.h>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! Template class for value objects, such as TFloat and TInt
*/
/*****************************************************************************/
template <class T> class TZValueType : public TZObject
{
  public:
    TZValueType();
    TZValueType(const TZValueType<T>& rValue);
    TZValueType(T tValue);
    virtual ~TZValueType();

    T& getValue();
    const T& getValue() const;

    //Operators
    TZValueType<T>& operator =(const TZValueType<T>& rInVal);
    TZValueType<T>& operator =(const T tValue);
    bool operator ==(const TZValueType<T>& rValue)const;
    bool operator ==(const T tValue)const;
    bool operator !=(const TZValueType<T>& rValue)const;
    bool operator !=(const T tValue)const;
    T operator+ (const TZValueType<T>& rValue) const;
    T operator+ (const T tValue) const;
    T operator- (const TZValueType<T>& rValue) const;
    T operator- (const T tValue) const;
    T operator* (const TZValueType<T>& rValue) const;
    T operator* (const T tValue) const;
    T operator/ (const TZValueType<T>& rValue) const;
    T operator/ (const T tValue) const;
    T& operator+= (const TZValueType<T>& rValue);
    T& operator+= (const T tValue);
    T& operator-= (const TZValueType<T>& rValue);
    T& operator-= (const T tValue);
    T& operator*= (const TZValueType<T>& rValue);
    T& operator*= (const T tValue);
    T& operator/= (const TZValueType<T>& rValue);
    T& operator/= (const T tValue);
    T& operator * ();
    const T& operator * () const;

  protected:
    ///internal value
    T m_tValue;
};


/****************************************************************************/
/*! Creates an empty value object
*/
/****************************************************************************/
template <class T> TZValueType<T>::TZValueType()
 : TZObject(),
   m_tValue(T())
{}

/**************************************************************************/
/*! Creates a value object out of an other value object
*/
/**************************************************************************/
template <class T> TZValueType<T>::TZValueType(const TZValueType<T>& rValue)
 : TZObject(),
   m_tValue(rValue.m_tValue)
{}

/**************************************************************************/
/*! Creates a value object out of a value value
*/
/**************************************************************************/
template <class T> TZValueType<T>::TZValueType(T tValue)
 : TZObject(),
   m_tValue(tValue)
{
}

/**************************************************************************/
/*! Destroys the value object
*/
/**************************************************************************/
template <class T> TZValueType<T>::~TZValueType()
{}

/**************************************************************************/
/*! gets the value of the value object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::getValue()
{
  return m_tValue;
}

/**************************************************************************/
/*! gets the value of the value object
*/
/**************************************************************************/
template <class T> const T& TZValueType<T>::getValue() const
{
  return m_tValue;
}

/**************************************************************************/
/*! assigns a value to this object
*/
/**************************************************************************/
template <class T> TZValueType<T>& TZValueType<T>::operator =(const TZValueType<T>& rInVal)
{
  m_tValue = rInVal.m_tValue;
  return *this;
}

/**************************************************************************/
/*! assigns a value to this double object
*/
/**************************************************************************/
template <class T> TZValueType<T>& TZValueType<T>::operator =(const T tValue)
{
  m_tValue = tValue;
  return *this;
}

/**************************************************************************/
/*! equals operator to check if two floats are the same
*/
/**************************************************************************/
template <class T> bool TZValueType<T>::operator ==(const TZValueType<T>& rValue)const
{
  return (m_tValue == rValue.m_tValue);
}

/**************************************************************************/
/*! equals operator to check if two floats are the same
*/
/**************************************************************************/
template <class T> bool TZValueType<T>::operator ==(const T tValue)const
{
  return (m_tValue == tValue);
}

/**************************************************************************/
/*! not-equals operator to check if two floats are not the same
*/
/**************************************************************************/
template <class T> bool TZValueType<T>::operator !=(const TZValueType<T>& rValue)const
{
  return (m_tValue != rValue.m_tValue);
}

/**************************************************************************/
/*! not-equals operator to check if two floats are not the same
*/
/**************************************************************************/
template <class T> bool TZValueType<T>::operator !=(const T tValue)const
{
  return !(m_tValue != tValue);
}

/**************************************************************************/
/*! adds a value to this value and returns a new
    object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator+ (const TZValueType<T>& rValue) const
{
  return m_tValue + rValue.m_tValue;
}

/**************************************************************************/
/*! adds a value to this value and returns a new
    object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator+ (const T tValue) const
{
  return m_tValue + tValue;
}

/**************************************************************************/
/*! subtracts a value to this value and returns a new object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator- (const TZValueType<T>& rValue) const
{
  return m_tValue - rValue.m_tValue;
}

/**************************************************************************/
/*! subtracts a value to this value and returns a new object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator- (const T tValue) const
{
  return m_tValue - tValue;
}

/**************************************************************************/
/*! multiplies a value to this value and returns a new object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator* (const TZValueType<T>& rValue) const
{
  return m_tValue * rValue.m_tValue;
}

/**************************************************************************/
/*! multiplies a value to this value and returns a new object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator* (const T tValue) const
{
  return m_tValue * tValue;
}

/**************************************************************************/
/*! devides a value to this value and returns a new object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator/ (const TZValueType<T>& rValue) const
{
  return m_tValue / rValue.m_tValue;
}

/**************************************************************************/
/*! devides a value to this value and returns a new object
*/
/**************************************************************************/
template <class T> T TZValueType<T>::operator/ (const T tValue) const
{
  return m_tValue / tValue;
}

/**************************************************************************/
/*! adds a value to this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator+= (const TZValueType<T>& rValue)
{
  m_tValue += rValue.m_tValue;
  return m_tValue;
}

/**************************************************************************/
/*! adds a value to this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator+= (const T tValue)
 {
  m_tValue += tValue;
  return m_tValue;
}

/**************************************************************************/
/*! subtracts a value from this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator-= (const TZValueType<T>& rValue)
{
  m_tValue -= rValue.m_tValue;
  return m_tValue;
}

/**************************************************************************/
/*! subtracts a value from this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator-= (const T tValue)
{
  m_tValue -= tValue;
  return m_tValue;
}

/**************************************************************************/
/*! multiblies a value with this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator*= (const TZValueType<T>& rValue)
{
  m_tValue *= rValue.m_tValue;
  return m_tValue;
}

/**************************************************************************/
/*! multiblies a value with this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator*= (const T tValue)
{
  m_tValue *= tValue;
  return m_tValue;
}

/**************************************************************************/
/*! dividide a value with this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator/= (const TZValueType<T>& rValue)
{
  m_tValue /= rValue.m_tValue;
  return m_tValue;
}

/**************************************************************************/
/*! dividide a value with this object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator/= (const T tValue)
{
  m_tValue /= tValue;
  return m_tValue;
}

/**************************************************************************/
/*! gets the value of the object
*/
/**************************************************************************/
template <class T> T& TZValueType<T>::operator * ()
{
  return getValue();
}

/**************************************************************************/
/*! gets the value of the object
*/
/**************************************************************************/
template <class T> const T& TZValueType<T>::operator * () const
{
  return getValue();
}


END_NAMESPACE_Zeus

#endif

