/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IPriorityQueue
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 13.08.07 7:31 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IPriorityQueue.hpp $
** 
** 1     13.08.07 7:31 bha
** Created
***************************************************************************/


#ifndef IPriorityQueueHPP
#define IPriorityQueueHPP

#include <zeusbase/System/Interfaces/IQueue.hpp>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! This interface describes a FIFO list (queue) with priority sort. The sort
    will be done with the key type. 
*/
/*****************************************************************************/
template <class TKeyType, class TValueType> class IPriorityQueue : public IQueue<TValueType>
{
  //causes errors of HIDE_ASSIGNMENT_OPERATOR(IPriorityQueue<TKeyType, TValueType>)
  typedef IPriorityQueue<TKeyType, TValueType> IPriorityQueueTemplate;
  HIDE_ASSIGNMENT_OPERATOR(IPriorityQueueTemplate)

  public:

    /*************************************************************************/
    /*! adds an object to the priority queue
        \param rKey : Priority key
        \param tData : Data object
    */
    /*************************************************************************/
    virtual void MQUALIFIER appendPriorityItem(const TKeyType& rKey, const TValueType& tData) = 0;
    
    /*************************************************************************/
    /*! Copies the content to the rQueue object
        \param rQueue : Target object
    */
    /*************************************************************************/
    virtual void MQUALIFIER copyToPriorityQueue(IPriorityQueue<TKeyType, TValueType>& rQueue) const = 0;

    /*************************************************************************/
    /*! returns the priority of the front element without removing it from the
        queue
        \return priority of the front element
    */
    /*************************************************************************/
    virtual const TKeyType& MQUALIFIER peekPriority() const = 0;
};


END_NAMESPACE_Zeus

#endif


