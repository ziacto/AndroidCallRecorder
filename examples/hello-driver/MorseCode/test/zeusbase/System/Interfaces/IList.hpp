/***************************************************************************
 * Copyright (C) 2008 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IList
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IList.hpp $
** 
** 16    27.05.08 7:44 Bha
** handing multible items on lists
** 
** 15    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 14    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 13    11.07.07 17:35 bha
** New methods getting first and last items
** 
** 12    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/


#ifndef IListHPP
#define IListHPP

#include <zeusbase/System/Interfaces/IValueType.hpp>
#include <zeusbase/System/Interfaces/IListIterator.hpp>

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stddef.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! Abstakter Datentyp Liste. Das Interface IStList beschreibt das
    Verhalten der Liste.
*/
/*****************************************************************************/
template <class T> class IList : public IValueType
{
  HIDE_ASSIGNMENT_OPERATOR(IList<T>)
  
  public:

    /**************************************************************************/
    /*! Adds an element to the list.
        \pre no precondition
        \post newSize = oldSize + 1 and element rItem on the place [Length-1]<BR>
                       Before:  e0, e1, e2 ... en                            <BR>
                       After:   e0, e1, e2 ... en, rItem

        \param rItem : Item to add
        \return Position of the added item
    */
    /**************************************************************************/
    virtual Int MQUALIFIER add(const T& rItem)=0;

    /**************************************************************************/
    /*! Adds a list of items to this list. The order is given by the iterator
        of the given list.
        \param rlstItems : Item list to add
        \return Position of the last item added
    */
    /**************************************************************************/
    virtual Int MQUALIFIER addAll(const IList<T>& rlstItems) = 0;

    /**************************************************************************/
    /*! Adds an empty item to the list
        \return Position of the last item added
    */
    /**************************************************************************/
    virtual Int MQUALIFIER addEmptyItem() = 0;

    /**************************************************************************/
    /*! This method assigns a new list of items to this list. The old list will
        be replaced
        \param rList : list to assign
    */
    /**************************************************************************/
    virtual void MQUALIFIER copyToList(IList<T>& rList) const =0;
    
    /**************************************************************************/
    /*! Clears the list. All elements are removed from the list
        \pre no preconditions
        \post getSize() = 0
    */
    /**************************************************************************/
    virtual void MQUALIFIER clear()=0;

    /**************************************************************************/
    /*! Removes an element out of the list
        \pre iIndex >= 0 and iIndex < Size
        \post newSize = oldSize - 1 and the Element[iIndex] was before at the
              place lIndex + 1                                              <BR>
              Before:  e0, e1, ... iIndex, iIndex+1 ... en                  <BR>
              After:   e0, e1, ... iIndex+1, iIndex+2 ... en

        \param iIndex : Index of the element to remove
        \retval RET_NOERROR : Element removed
        \retval RET_REQUEST_FAILED: Could not remove element
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER deleteItem(Int iIndex)=0;

    /**************************************************************************/
    /*! Removes the element rItem out of the list.
        \pre no precondition
        \post see deleteItem()
        \param rItem : Element to remove
        \retval RET_NOERROR : Element removed
        \retval RET_REQUEST_FAILED: Could not remove element
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER remove(const T& rItem)=0;

    /**************************************************************************/
    /*! Removes all items of the given list.
        \param rlstItems : Items to remove
        \retval RET_NOERROR : Items removed (at least one has been removed)
        \retval RET_REQUEST_FAILED: Could not remove any item
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER removeAll(const IList<T>& rlstItems)=0;

    /**************************************************************************/
    /*! Returns the number of items
        \return number of items
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getCount() const =0;

    /**************************************************************************/
    /*! Returns the indexed item at position iIndex
        \pre  iIndex >= 0 und iIndex < Size
        \post no changes on the list

        \param iIndex : Index of requested item
        \retval Empty element : Could not find the item at iIndex
        \retval Element[iIndex] : item at [iIndex]
    */
    /**************************************************************************/
    virtual T& MQUALIFIER getItem(Int iIndex)=0;

    /**************************************************************************/
    /*! Returns the indexed item at position iIndex. The return value is
        const.
        \see IList::getItem
    */
    /**************************************************************************/
    virtual const T& MQUALIFIER getItemConst(Int iIndex) const=0;

    /**************************************************************************/
    /*! returns the index of an item.
        \param rItem : Item to check
        \retval INVALID_INDEX : Item is not inserted in this list
        \retval >= 0: Index of the item
    */
    /**************************************************************************/
    virtual Int MQUALIFIER indexOf(const T& rItem) const=0;

    /**************************************************************************/
    /*! Inserts an item into the list at position iIndex.
        \pre iIndex must be valid (>= 0).
        \post if iIndex = 0, then the rItem is
              placed in the front (prepend); if the iIndex == count, the item is
              placed at the end (append); else the rItem is placed at position
              iIndex:
        \param rItem : Item to insert
        \param iIndex : insert position
        \retval INVALID_INDEX : Could not insert the element
                               (invalid insert position)
        \retval >= 0: Item inserted. The return value is the insert position
    */
    /**************************************************************************/
    virtual Int MQUALIFIER insert(Int iIndex, const T& rItem)=0;

    /**************************************************************************/
    /*! This method checks if an item is equal to an item inside this list
        \param lIndex : Index of the item to be checked
        \param rItem : Item to check
        \retval true : Item is equal
        \retval false: Item is not equal
    */
    /**************************************************************************/
    virtual bool MQUALIFIER equalsItem(Int iIndex, const T& rItem) const =0;

    /**************************************************************************/
    /*! This method checks if two lists has the same content
        \param list : list to check
        \retval true : list is equal
        \retval false: list is not equal
    */
    /**************************************************************************/
    virtual bool MQUALIFIER equals(const IList<T>& rList) const =0;
        
    /**************************************************************************/
    /*! Returns the iterator of this list object. This iterator is used to 
        traverse the list. The iterator will be allocated inside this method and
        must be released through the method releaseIterator(). Its possible 
        to use the method as nested calls. The order of the releasing doesn't has
        to mach the getIterator() calls.
        \return pointer to a allocated iterator.
    */
    /**************************************************************************/
    virtual IListIterator<T>* MQUALIFIER getIterator() const=0;
    
    /**************************************************************************/
    /*! Returns the const iterator of this list object. This iterator is used to
        traverse the list. The iterator will be allocated inside this method and
        must be released through the method releaseIterator(). Its possible 
        to use the method as nested calls. The order of the releasing doesn't has
        to mach the getIterator() calls.
        \return pointer to a allocated iterator.
    */
    /**************************************************************************/
    virtual const IListIterator<T>* MQUALIFIER getConstIterator() const=0;

    /**************************************************************************/
    /*! This method releases a iterator object. This must be called after a
        call of getIterator(), otherwise it will cause a memory leak.
        \param pIterator : Iterator to release.
    */
    /**************************************************************************/
    virtual void MQUALIFIER releaseIterator(const IListIterator<T>* pIterator) const=0;
    
    /**************************************************************************/
    /*! Checks if the list is empty
        \retval true : List is empty
        \retval false : List is not empty
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isEmpty() const =0;
    

    /**************************************************************************/
    /*! returns the first item of the list
        \return first item
    */
    /**************************************************************************/
    virtual T& MQUALIFIER getFirstItem()=0;

    /**************************************************************************/
    /*! returns the first item of the list. The return value is
        const.
        \see IList::getFirstItem
    */
    /**************************************************************************/
    virtual const T& MQUALIFIER getFirstItemConst() const=0;

    /**************************************************************************/
    /*! returns the last item of the list
        \return last item
    */
    /**************************************************************************/
    virtual T& MQUALIFIER getLastItem()=0;

    /**************************************************************************/
    /*! returns the last item of the list. The return value is
        const.
        \see IList::getLastItem
    */
    /**************************************************************************/
    virtual const T& MQUALIFIER getLastItemConst() const=0;

    /**************************************************************************/
    /*! checks if the list contains an item
        \param rItem: item to check
        \retval true : item is included by the list
        \retval false: item is not included by the list
    */
    /**************************************************************************/
    virtual bool MQUALIFIER hasItem(const T& rItem) const = 0;

    /**************************************************************************/
    /*! checks if the list contains all items of the given list
        \param rlstItems: list of items to check
        \retval true : all items are included by the list
        \retval false: at least one item is not not included by the list
    */
    /**************************************************************************/
    virtual bool MQUALIFIER hasAllItems(const IList<T>& rlstItems) const = 0;

    //Friend classes: DO NOT CHANGE
    friend class TZVariant;
};


END_NAMESPACE_Zeus

#endif
