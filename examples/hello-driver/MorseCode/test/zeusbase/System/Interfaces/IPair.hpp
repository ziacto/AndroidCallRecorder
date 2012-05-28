/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IPair
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 7:04 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IPair.hpp $
** 
** 2     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 1     2.07.07 7:18 bha
** Pair interface created
***************************************************************************/


#ifndef IPairHPP
#define IPairHPP

#include <zeusbase/System/Interfaces/IValueType.hpp>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! Defines a stack interface for pair types. A pair is an object containing
    a first argument and a second argument
*/
/***************************************************************************/
template <class T1, class T2> class IPair : public IValueType
{
  //causes errors of HIDE_ASSIGNMENT_OPERATOR(IMap<T1, T2>)
  typedef IPair<T1, T2> IPairTemplate;
  HIDE_ASSIGNMENT_OPERATOR(IPairTemplate)

  public:
    /***********************************************************************/
    /*! Assigns a new value object
        \param rPair : Pair object to assign
    */
    /***********************************************************************/
    virtual void MQUALIFIER assign(const IPair<T1, T2>& rPair) = 0;

    /***********************************************************************/
    /*! checks if two pair objects are equal
        \param rPair : Pair object to check
        \retval true : Object content is equal
        \retval false: Object content is different
    */
    /***********************************************************************/
    virtual bool MQUALIFIER equals(const IPair<T1, T2>& rPair) const= 0;

    /***********************************************************************/
    /*! checks if the first value equals to the rInPar
        \param rInPar : value to check
        \retval true : first value is equal
        \retval false: first value is different
    */
    /***********************************************************************/
    virtual bool MQUALIFIER equalsFirst(const T1& rInPar) const= 0;

    /***********************************************************************/
    /*! checks if the second value equals to the rInPar
        \param rInPar : value to check
        \retval true : second value is equal
        \retval false: second value is different
    */
    /***********************************************************************/
    virtual bool MQUALIFIER equalsSecond(const T2& rInPar) const= 0;

    /***********************************************************************/
    /*! Returns the first value of the pair. This method is also needed to
        change the content of the first value, there fore this method is not
        const. Use getFirstConst() for reading access.
    */
    /***********************************************************************/
    virtual T1& MQUALIFIER getFirst() = 0;

    /***********************************************************************/
    /*! Returns the first value of the pair.
    */
    /***********************************************************************/
    virtual const T1& MQUALIFIER getFirstConst() const = 0;

    /***********************************************************************/
    /*! Returns the second value of the pair. This method is also needed to
        change the content of the second value, there fore this method is not
        const. Use getSecondConst() for reading access.
    */
    /***********************************************************************/
    virtual T2& MQUALIFIER getSecond() = 0;

    /***********************************************************************/
    /*! Returns the second value of the pair.
    */
    /***********************************************************************/
    virtual const T2& MQUALIFIER getSecondConst() const = 0;

    /***********************************************************************/
    /*! Sets the first value of the pair.
        \param rInPar : value to set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setFirst(const T1& rInPar) = 0;

    /***********************************************************************/
    /*! Sets the second value of the pair.
        \param rInPar : value to set
    */
    /***********************************************************************/
    virtual void MQUALIFIER setSecond(const T2& rInPar) = 0;

    /***********************************************************************/
    /*! Sets a new pair of values to this pair object
        \param rInPar1 : first value
        \param rInPar2 : second value
    */
    /***********************************************************************/
    virtual void MQUALIFIER setPair(const T1& rInPar1, const T2& rInPar2) = 0;
};

END_NAMESPACE_Zeus

#endif
