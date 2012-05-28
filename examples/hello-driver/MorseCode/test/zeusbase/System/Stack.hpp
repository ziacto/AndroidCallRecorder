/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Stack
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Stack.hpp $
** 
** 12    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 11    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 10    11.07.07 17:37 bha
** Implementing new interface IStack
** 
** 7     14.09.06 6:53 bha
** Anpassen von addRef und release auf const
***************************************************************************/


#ifndef StackH
#define StackH

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stddef.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


#include <string.h>
#include <zeusbase/System/Interfaces/IStack.hpp>

BEGIN_NAMESPACE_Zeus

/******************************************************************************/
/*! Implementation des Abstrakten DatenTyps Pushdown-Stack
*/
/******************************************************************************/
template <class T> class TStack : public IStack<T>
{
  public:
    ///Konstruktor
    TStack();
    TStack(const T& rEmptyObject);
    ///Destruktor
    ~TStack();

    //Methods of IStack
    virtual void MQUALIFIER copyToStack(IStack<T>& rStack) const;
    virtual void MQUALIFIER copyToList(IList<T>& rList) const;
    virtual void MQUALIFIER flush();
    virtual Int MQUALIFIER getCount() const;
    virtual bool MQUALIFIER isEmpty() const;
    virtual void MQUALIFIER push(const T& rData);
    virtual T MQUALIFIER pop();
    virtual T& MQUALIFIER peek();

    //operators
    TStack<T>& operator=(const TStack<T>& rStack);
    TStack<T>& operator=(const IStack<T>& rStack);

  protected:
    T getItem(Int iIndex) const;

  private:
    ///Containerklasse der Daten, die verlinked werden
    struct TBaseElement
    {
      TBaseElement(T data, TBaseElement* next)
      {
        Data = data;
        Next = next;
      }

      T Data;
      TBaseElement* Next;
    };

    /*********************************************************************/
    /* COMPILER PROBLEM:
       Change this if a compiler fails with : m_tEmpty(T()) (see constructors)

    #ifdef A_COMPILER_TYPE
    static const T& getDefaultEmpty()
    {
        static const T Empty; // is initialized by compiler
        return Empty;
    }
    #endif

    */

    ///Stack-Top
    TBaseElement* m_pElHead;
    ///Groesse des Stacks
    Int m_iSize;
    ///Das Leere Objekt
    T m_EmptyObject;
};


/******************************************************************************/
/*! Erstellen des Stacks
*/
/******************************************************************************/
template <class T> TStack<T>::TStack()
 /* COMPILER PROBLEM*/
 /*#ifdef A_COMPILER_TYPE
    : m_EmptyObject(getDefaultEmpty())
   #else
    : m_EmptyObject(T())
   #endif
*/
  : m_EmptyObject(T())
{
  m_pElHead = NULL;
  m_iSize = 0;

  // DO NOT USE MEMSET. This causes memory leaks on complex objects
  //memset(&m_EmptyObject,0, sizeof(T));
}

/******************************************************************************/
/*! Erstellen des Stacks
*/
/******************************************************************************/
template <class T> TStack<T>::TStack(const T& empty_object)
 : m_EmptyObject(empty_object)
{
  m_pElHead = NULL;
  m_iSize = 0;
}


/******************************************************************************/
/*! Zerstoeren des Stacks
*/
/******************************************************************************/
template <class T> TStack<T>::~TStack()
{
  flush();
  m_pElHead = NULL;
}


/******************************************************************************/
/*! This returns the indexed value of the queue. Used internaly for coping 
    stacks.
    \return Element: indexed value
*/
/******************************************************************************/
template <class T> T TStack<T>::getItem(Int iIndex) const
{
  T tRetval = m_EmptyObject;
  if (m_pElHead != NULL && iIndex >= 0 && iIndex < m_iSize)
  {
    TBaseElement* pActElement = m_pElHead;
    Int iCount = 0;
    while(iCount <= iIndex && pActElement != NULL)
    {
      pActElement = pActElement->pNext;
      ++iCount;
    }

    if (pActElement != NULL)
    {
      tRetval = pActElement->tData;
    }
  }
  return tRetval;
}

/******************************************************************************/
/*! \see IStack::flush
*/
/******************************************************************************/
template <class T> void MQUALIFIER TStack<T>::flush()
{
  while(m_pElHead != NULL)
  {
    TBaseElement* next = m_pElHead->Next;
    delete m_pElHead;
    m_pElHead = next;
  }
  m_iSize = 0;
}


/******************************************************************************/
/*! \see IStack::push
*/
/******************************************************************************/
template <class T> void MQUALIFIER TStack<T>::push(const T& data)
{
  m_pElHead = new TBaseElement(data, m_pElHead);
  m_iSize++;
}


/******************************************************************************/
/*! \see IStack::pop
*/
/******************************************************************************/
template <class T> T MQUALIFIER TStack<T>::pop()
{
  if (m_pElHead != NULL)
  {
    T retval = m_pElHead->Data;
    TBaseElement* del = m_pElHead;
    m_pElHead = m_pElHead->Next;
    delete del;
    m_iSize--;
    return retval;
  }
  else
  {
    return m_EmptyObject;
  }
}


/******************************************************************************/
/*! \see IStack::peek
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TStack<T>::peek()
{
  if (m_pElHead != NULL)
  {
    return m_pElHead->Data;
  }
  else
  {
    return m_EmptyObject;
  }
}

/******************************************************************************/
/*! \see IStack::getSize
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TStack<T>::getCount() const
{
  return m_iSize;
}


/******************************************************************************/
/*! \see IStack::isEmpty
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TStack<T>::isEmpty() const
{
  return (m_iSize == 0);
}


/******************************************************************************/
/*! \see IStack::copyToStack
*/
/******************************************************************************/
template <class T> void MQUALIFIER TStack<T>::copyToStack(IStack<T>& rStack) const
{
  TStack<T> stackTemp;

  TBaseElement* pActElement = m_pElHead;
  while(pActElement != NULL)
  {
    stackTemp.push(pActElement->Data);
    pActElement = pActElement->Next;
  }

  while(!stackTemp.isEmpty())
  {
    rStack.push(stackTemp.pop());
  }
}

/******************************************************************************/
/*! \see IStack::copyToList
*/
/******************************************************************************/
template <class T> void MQUALIFIER TStack<T>::copyToList(IList<T>& rList) const
{
  TBaseElement* pActElement = m_pElHead;
  while(pActElement != NULL)
  {
    rList.add(pActElement->Data);
    pActElement = pActElement->Next;
  }
}

/******************************************************************************/
/*! Copies a stack into an other stack
    \param rStack : Stack to copy from
*/
/******************************************************************************/
template <class T> TStack<T>& TStack<T>::operator=(const TStack<T>& rStack)
{
  rStack.copyToStack(*this);
  return *this;
}

/******************************************************************************/
/*! Copies a stack into an other stack
    \param rStack : Stack to copy from
*/
/******************************************************************************/
template <class T> TStack<T>& TStack<T>::operator=(const IStack<T>& rStack)
{
  rStack.copyToStack(*this);
  return *this;
}

END_NAMESPACE_Zeus

#endif
