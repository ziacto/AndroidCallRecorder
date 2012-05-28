/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ISet
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 5.10.06
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/ISet.hpp $
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef ISetHPP
#define ISetHPP


#include <zeusbase/System/Interfaces/IList.hpp>

BEGIN_NAMESPACE_Zeus

/******************************************************************************/
/*! This class implements a set (using stl::set) for different types
*/
/******************************************************************************/
template <class T> class ISet : public IValueType
{
  HIDE_ASSIGNMENT_OPERATOR(ISet<T>)
  
  public:
    /**************************************************************************/
    /*! adds a new item to the set
        \param rItem : Item to add
        \retval true : Item added
        \retval false: Item is already added
    */
    /**************************************************************************/
    virtual bool MQUALIFIER addItem(const T& rItem) = 0;

    /**************************************************************************/
    /*! removes all items from the set
    */
    /**************************************************************************/
    virtual void MQUALIFIER clear() = 0;

    /**************************************************************************/
    /*! returns the number of items
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getCount() const = 0;

    /**************************************************************************/
    /*! Checks if an item is included
        \param rItem : Item to check
        \retval true : Item is included
        \retval false: Item is not included
    */
    /**************************************************************************/
    virtual bool MQUALIFIER hasItem(const T& rItem) const=0;

    /************************************************************************/
    /*! returns a set iterator. Release the iterator using releaseIterator()
        method
        \return new set iterator
    */
    /************************************************************************/
    virtual IListIterator<T>* MQUALIFIER getIterator() = 0;

    /************************************************************************/
    /*! returns a const set iterator. Release the iterator using
        releaseIterator() method
        \return new const set iterator
    */
    /************************************************************************/
    virtual const IListIterator<T>* MQUALIFIER getConstIterator() const = 0;

    /************************************************************************/
    /*! Checks if the set is empty
        \retval true : Set is empty
        \retval false: Set is not empty
    */
    /************************************************************************/
    virtual bool MQUALIFIER isEmpty() const = 0;

    /************************************************************************/
    /*! Releases an iterator.
        \param pIterator : Iterator instance
    */
    /************************************************************************/
    virtual void MQUALIFIER releaseIterator(const IListIterator<T>* pIterator) const =0;

    /************************************************************************/
    /*! removes one item from the set
        \param rItem : Item to remove
    */
    /************************************************************************/
    virtual bool MQUALIFIER removeItem(const T& rItem) = 0;

    /************************************************************************/
    /*! Copies a set into a list
        \param rList : Target list
    */
    /************************************************************************/
    virtual void MQUALIFIER copyToList(IList<T>& rList) const = 0;

    /************************************************************************/
    /*! Copies a set into a set
        \param rSet : Target set
    */
    /************************************************************************/
    virtual void MQUALIFIER copyToSet(ISet<T>& rSet) const = 0;

    /************************************************************************/
    /*! this method checks if two sets are equal
        \param rSet : set to check
        \retval true : Sets are equal
        \retval false: sets are not equal
    */
    /************************************************************************/
    virtual bool MQUALIFIER equals(const ISet<T>& rSet) const = 0;

    /************************************************************************/
    /*! Returns an item of the set. Use the iterator to iterate throu the
        set and traverse all items. This method will just return one and the
        same item of the set
        \return An item of the set
    */
    /************************************************************************/
    virtual T& MQUALIFIER getItem() = 0;

    /************************************************************************/
    /*! \see ISet::getItem
    */
    /************************************************************************/
    virtual const T& MQUALIFIER getItemConst() const = 0;
};


END_NAMESPACE_Zeus

#endif
