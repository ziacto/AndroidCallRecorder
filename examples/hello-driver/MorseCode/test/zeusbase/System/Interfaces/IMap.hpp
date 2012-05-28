/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IMap
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IMap.hpp $
** 
** 11    7.01.08 9:21 Bha
** New method to copy maps defined
** 
** 10    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 9     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IMapHPP
#define IMapHPP

#include <zeusbase/System/Interfaces/IMapIterator.hpp>
#include <zeusbase/System/Interfaces/IValueType.hpp>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! This interface defines a map
*/
/*****************************************************************************/
template <class TKeyType, class TValueType> class IMap : public IValueType
{
  //causes errors of HIDE_ASSIGNMENT_OPERATOR(IMap<TKeyType, TValueType>
  typedef IMap<TKeyType, TValueType> IMapTemplate;

  HIDE_ASSIGNMENT_OPERATOR(IMapTemplate)

  public:
    /************************************************************************/
    /*! This copies the content of this map into an other map instance
        \param rMap : destrination map to copy the content to
    */
    /************************************************************************/
    virtual void MQUALIFIER copyToMap(IMap<TKeyType, TValueType>& rMap) const = 0;

    /************************************************************************/
    /*! Gets an item out of the map
        \param rKey : Key of the item
        \return item
    */
    /************************************************************************/
    virtual TValueType& MQUALIFIER getItem(const TKeyType& rKey)=0;

    /************************************************************************/
    /*! Gets a copy of an item out of the map
        \param rKey : Key of the item
        \return const item
    */
    /************************************************************************/
    virtual const TValueType& MQUALIFIER getItemConst(const TKeyType& rKey) const=0;

    /************************************************************************/
    /*! adds a new item to the map
        \param rKey : Key of the value
        \param rData : Data value
    */
    /************************************************************************/
    virtual void MQUALIFIER setItem(const TKeyType& rKey, const TValueType& rData)=0;

    /************************************************************************/
    /*! Checks if the map is empty
        \retval true : Map is empty
        \retval false : Map is not empty
    */
    /************************************************************************/
    virtual bool MQUALIFIER isEmpty() const=0;

    /************************************************************************/
    /*! Gets the number of elements
    */
    /************************************************************************/
    virtual Int MQUALIFIER getCount() const=0;

    /************************************************************************/
    /*! Deletes an item out of the map
        \param rKey : Key value
        \retval true : Item deleted
        \retval false: Could not delete item
    */
    /************************************************************************/
    virtual bool MQUALIFIER deleteItem(const TKeyType& rKey)=0;

    /************************************************************************/
    /*! Checks if an item is inside the map
        \param rKey : Key to check
        \retval true : Item is included
        \retval false: No such item found
    */
    /************************************************************************/
    virtual bool MQUALIFIER hasItem(const TKeyType& rKey) const=0;

    /************************************************************************/
    /*! Clears the map
    */
    /************************************************************************/
    virtual void MQUALIFIER clear()=0;

    /************************************************************************/
    /*! gets a map iterator
    */
    /************************************************************************/
    virtual IMapIterator<TKeyType, TValueType>* MQUALIFIER getIterator()=0;

    /************************************************************************/
    /*! releases a map iterator
    */
    /************************************************************************/
    virtual void MQUALIFIER releaseIterator(const IListIterator<TValueType>* pIterator) const=0;

    /************************************************************************/
    /*! gets a const map iterator
    */
    /************************************************************************/
    virtual const IMapIterator<TKeyType, TValueType>* MQUALIFIER getConstIterator() const=0;

    /************************************************************************/
    /*! Checks if two maps are equal
    */
    /************************************************************************/
    virtual bool MQUALIFIER equals(const IMap<TKeyType, TValueType>& rMap) const = 0;
};


END_NAMESPACE_Zeus

#endif
