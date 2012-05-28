/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IMapIterator
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IMapIterator.hpp $
** 
** 1     13.08.07 7:31 bha
** Created
***************************************************************************/

#ifndef IMapIteratorHPP
#define IMapIteratorHPP

#include <zeusbase/System/Interfaces/IListIterator.hpp>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! Special string map iterator to receive the keys instead of the values
*/
/*****************************************************************************/
template <class TKeyType, class TValueType> class IMapIterator : public IListIterator<TValueType>
{
  //causes errors of HIDE_ASSIGNMENT_OPERATOR(IMapIterator<TKeyType, TValueType>)
  typedef IMapIterator<TKeyType, TValueType> IMapIteratorTemplate;

  HIDE_ASSIGNMENT_OPERATOR(IMapIteratorTemplate)

  public:
    /*************************************************************************/
    /*! This method returns the key of an item instead of the value
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER getNextKey(TKeyType& rKey) =0;

    /*************************************************************************/
    /*! This method returns the key of an item instead of the value
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER getNextKeyConst(TKeyType& rKey) const=0;

    /*************************************************************************/
    /*! Gets the next Item and also returns the key value as a copy
    */
    /*************************************************************************/
    virtual TValueType& MQUALIFIER getNextItemWithKey(TKeyType& rKey) const=0;

    /*************************************************************************/
    /*! Gets the next Item and also returns the key value as a copy
    */
    /*************************************************************************/
    virtual const TValueType& MQUALIFIER getNextItemWithKeyConst(TKeyType& rKey) const=0;
};

END_NAMESPACE_Zeus

#endif

