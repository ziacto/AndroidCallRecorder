/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IQueue
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IQueue.hpp $
** 
** 4     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 3     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 2     11.07.07 17:37 bha
** 
** 1     11.06.07 10:16 bha
***************************************************************************/


#ifndef IQueueHPP
#define IQueueHPP

#include <zeusbase/System/Interfaces/IValueType.hpp>
#include <zeusbase/System/Interfaces/IList.hpp>

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stddef.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! This interface describes a FIFO list (queue).
*/
/*****************************************************************************/
template <class T> class IQueue : public IValueType
{
  HIDE_ASSIGNMENT_OPERATOR(IQueue<T>)

  public:

    /*************************************************************************/
    /*! adds an object to the queue
        \param tData : Data object
    */
    /*************************************************************************/
    virtual void MQUALIFIER appendItem(const T& tData) = 0;
    
    /*************************************************************************/
    /*! Copies the content to the rQueue object
        \param rQueue : Target object
    */
    /*************************************************************************/
    virtual void MQUALIFIER copyToQueue(IQueue<T>& rQueue) const = 0;

    /*************************************************************************/
    /*! Copies the content to the rList object
        \param rList : Target object
    */
    /*************************************************************************/
    virtual void MQUALIFIER copyToList(IList<T>& rList) const = 0;

    /*************************************************************************/
    /*! returns the front element of the queue and removes it
        \return front element
    */
    /*************************************************************************/
    virtual T MQUALIFIER removeItem() = 0;
    
    /*************************************************************************/
    /*! Returns the number of items inside the queue
        \return Size of Queue
    */
    /*************************************************************************/
    virtual Int MQUALIFIER getCount() const = 0;
    
    /*************************************************************************/
    /*! flushes the queue. All items will be removed
    */
    /*************************************************************************/
    virtual void MQUALIFIER flush() = 0;
    
    /*************************************************************************/
    /*! Checks if the queue is empty
        \retval true : queue is empty
        \retval false : queue is not empty
    */
    /*************************************************************************/
    virtual bool MQUALIFIER isEmpty() const = 0;

    /*************************************************************************/
    /*! returns the front element of the queue without removing it
        \return front element
    */
    /*************************************************************************/
    virtual T& MQUALIFIER peekItem() = 0;

    /*************************************************************************/
    /*! returns the front element of the queue without removing it
        \return front element
    */
    /*************************************************************************/
    virtual const T& MQUALIFIER peekItemConst() const = 0;
};


END_NAMESPACE_Zeus

#endif
 
