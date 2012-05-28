/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IStack
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 17:21 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IStack.hpp $
** 
** 3     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 2     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 1     11.07.07 17:31 bha
** Created
***************************************************************************/

#ifndef IStackHPP
#define IStackHPP

#include <zeusbase/System/Interfaces/IList.hpp>
#include <zeusbase/System/Interfaces/IValueType.hpp>

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stddef.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


BEGIN_NAMESPACE_Zeus


/*****************************************************************************/
/*! This is the interface definition of a stack interface
*/
/*****************************************************************************/
template <class T> class IStack : public IValueType
{
  HIDE_ASSIGNMENT_OPERATOR(IStack<T>)

  public:

    /*************************************************************************/
    /*! Copies the content to the rStack object
        \param rStack : Target object
    */
    /*************************************************************************/
    virtual void MQUALIFIER copyToStack(IStack<T>& rStack) const = 0;

    /*************************************************************************/
    /*! Copies the content to the rList object
        \param rList : Target object
    */
    /*************************************************************************/
    virtual void MQUALIFIER copyToList(IList<T>& rList) const = 0;

    /*************************************************************************/
    /*! flushes the stack. All items will be removed
    */
    /*************************************************************************/
    virtual void MQUALIFIER flush() = 0;

    /*************************************************************************/
    /*! Returns the size of the stack
    */
    /*************************************************************************/
    virtual Int MQUALIFIER getCount() const = 0;

    /*************************************************************************/
    /*! Checks if the stack is empty
    */
    /*************************************************************************/
    virtual bool MQUALIFIER isEmpty() const = 0;

    /*************************************************************************/
    /*! Pushes a new item to the stack
    */
    /*************************************************************************/
    virtual void MQUALIFIER push(const T& rData) = 0;

    /*************************************************************************/
    /*! Removes the top element of the stack
    */
    /*************************************************************************/
    virtual T MQUALIFIER pop() = 0;

    /*************************************************************************/
    /*! returns the top element of the stack
    */
    /*************************************************************************/
    virtual T& MQUALIFIER peek() = 0;
};


END_NAMESPACE_Zeus

#endif

