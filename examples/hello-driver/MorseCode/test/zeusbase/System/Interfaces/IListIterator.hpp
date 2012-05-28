/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IListIterator
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 19.09.06
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
 $Log: /WinSteuerung2/usr/include/zeusbase/System/Interfaces/IListIterator.hpp $
** 
** 7     5.09.07 10:02 Releasebuilder
** Compilationsfehler im Release behoben.
** 
** 6     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 5     11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
***************************************************************************/


#ifndef IListIteratorHPP
#define IListIteratorHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! Defines the iterator interface. It is used to iterate through
    list and sets. 
*/
/*****************************************************************************/
template <class T> class IListIterator : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IListIterator<T>)
  
  public:
    /*************************************************************************/
    /*! Resets the iterator
    */
    /*************************************************************************/
    virtual void MQUALIFIER reset() const=0;

    /*************************************************************************/
    /*! Gets the next Item
    */
    /*************************************************************************/
    virtual T& MQUALIFIER getNextItem() const=0;

    /*************************************************************************/
    /*! Gets the next Item
    */
    /*************************************************************************/
    virtual const T& MQUALIFIER getNextItemConst() const=0;

    /*************************************************************************/
    /*! Checks if there is a next item
        \retval true : Has next item
        \retval false : No next item
    */
    /*************************************************************************/
    virtual bool MQUALIFIER hasNextItem() const=0;
};

END_NAMESPACE_Zeus

#endif

