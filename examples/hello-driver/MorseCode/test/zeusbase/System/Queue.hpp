/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Queue
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Queue.hpp $
** 
** 13    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 12    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 11    11.07.07 17:36 bha
** Operatoer added
** 
** 10    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
** 
** 7     14.09.06 6:53 bha
** Anpassen von addRef und release auf const
***************************************************************************/

#ifndef QueueH
#define QueueH

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stddef.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#include <string.h>
#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/Interfaces/IQueue.hpp>

BEGIN_NAMESPACE_Zeus

/******************************************************************************/
/*! This class implements the abstract data type FIFO queue
*/
/******************************************************************************/
template <class T> class TQueue : public IQueue<T>
{
  public:
    TQueue();
    TQueue(IQueue<T>& rQueue);
    TQueue(const T& rEmptyObject);
    virtual ~TQueue();

    //Methods of IQueue
    virtual void MQUALIFIER appendItem(const T& tData);
    virtual void MQUALIFIER copyToQueue(IQueue<T>& rQueue) const;
    virtual void MQUALIFIER copyToList(IList<T>& rList) const;
    virtual T MQUALIFIER removeItem();
    virtual Int MQUALIFIER getCount() const;
    virtual void MQUALIFIER flush();
    virtual bool MQUALIFIER isEmpty() const;
    virtual T& MQUALIFIER peekItem() ;
    virtual const T& MQUALIFIER peekItemConst() const;

    //operators
    TQueue<T>& operator=(const TQueue<T>& rQueue);
    TQueue<T>& operator=(const IQueue<T>& rQueue);

    
  protected:
    T getItem(Int iIndex) const;

  private:
    /***************************************************************/
    /*! Container to store the data. Used as to link the queue
    */
    /***************************************************************/
    struct TBaseElement
    {
      /*************************************************************/
      /*! Creates the container element
      */
      /*************************************************************/
      TBaseElement(T tData1, TBaseElement* pNext1)
      {
        tData = tData1;
        pNext = pNext1;
      }

      ///Data object
      T tData;
      ///Next element inside the queue
      TBaseElement* pNext;
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

    ///Beginning of the queue
    TBaseElement* m_pElHead;
    ///Ending of the queue
    TBaseElement* m_pElTail;
    ///Queue size
    Int m_iCount;
    ///Empty object. Used to return if the queue is empty
    T m_EmptyObject;

};


/******************************************************************************/
/*! Creates a queue
*/
/******************************************************************************/
template <class T> TQueue<T>::TQueue()
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
  m_pElTail = NULL;
  m_iCount = 0;

  // DO NOT USE MEMSET. This causes memory leaks on complex objects
  //memset(&m_EmptyObject,0, sizeof(T));
}

/******************************************************************************/
/*! Copy constructor
*/
/******************************************************************************/
template <class T> TQueue<T>::TQueue(IQueue<T>& rQueue)
 : m_EmptyObject(rQueue.m_EmptyObject)
{
  m_pElHead = NULL;
  m_pElTail = NULL;
  m_iCount = 0;
  rQueue.copyToQueue(*this);
}

/******************************************************************************/
/*! Creates a queue using a special empty object
*/
/******************************************************************************/
template <class T> TQueue<T>::TQueue(const T& rEmptyObject)
 : m_EmptyObject(rEmptyObject)
{
  m_pElHead = NULL;
  m_pElTail = NULL;
  m_iCount = 0;
}


/******************************************************************************/
/*! Destroys the queue
*/
/******************************************************************************/
template <class T> TQueue<T>::~TQueue()
{
  flush();
  m_pElHead = NULL;
  m_pElTail = NULL;
}

/******************************************************************************/
/*! This returns the indexed value of the queue. Used internaly for coping 
    queues. Note that index is used backwards on queues
    \return Element: indexed value
*/
/******************************************************************************/
template <class T> T TQueue<T>::getItem(Int iIndex) const
{
  T Retval = m_EmptyObject;
  if (m_pElHead != NULL && iIndex >= 0 && iIndex < m_iCount)
  {
    TBaseElement* pActElement = m_pElHead;
    while(iIndex > 0 && pActElement != NULL)
    {
      pActElement = pActElement->pNext;
      iIndex--;
    }
    
    if (pActElement != NULL)
    {
      Retval = pActElement->tData;
    }
  }
  return Retval;
}

/******************************************************************************/
/*! \see IQueue::appendItem
*/
/******************************************************************************/
template <class T> void MQUALIFIER TQueue<T>::appendItem(const T& tData)
{
  if (m_pElTail == NULL)
  {
    m_pElTail = new TBaseElement(tData, NULL);
    m_pElHead = m_pElTail;
  }
  else
  {
    m_pElTail->pNext = new TBaseElement(tData, NULL);
    m_pElTail = m_pElTail->pNext;
  }
  m_iCount++;
}

/******************************************************************************/
/*! \see IQueue::copyToQueue
*/
/******************************************************************************/
template <class T> void MQUALIFIER TQueue<T>::copyToQueue(IQueue<T>& rQueue) const
{
  TBaseElement* pActElement = m_pElHead;
  while(pActElement != NULL)
  {
    rQueue.appendItem(pActElement->tData);
    pActElement = pActElement->pNext;
  }

  /* NOT SO EFFICIENT O(n^2)
  for(int i = 0; i < m_iCount; i++)
  {
    rQueue.appendItem(this->getItem(i));
  }*/
}

/******************************************************************************/
/*! \see IQueue::copyToList
*/
/******************************************************************************/
template <class T> void MQUALIFIER TQueue<T>::copyToList(IList<T>& rList) const
{
  TBaseElement* pActElement = m_pElHead;
  while(pActElement != NULL)
  {
    rList.add(pActElement->tData);
    pActElement = pActElement->pNext;
  }

  /* NOT SO EFFICIENT O(n^2)
  for(int i = 0; i < m_iCount; i++)
  {
    rList.add(this->getItem(i));
  }*/
}

/******************************************************************************/
/*! \see IQueue::removeItem
*/
/******************************************************************************/
template <class T> T MQUALIFIER TQueue<T>::removeItem()
{
  if (m_pElHead != NULL)
  {
    T tRetval = m_pElHead->tData;
    TBaseElement* pDel = m_pElHead;
    m_pElHead = m_pElHead->pNext;
    delete pDel;
    m_iCount--;
    
    if (m_pElHead == NULL)
    {
      m_pElTail = NULL;
    }
    return tRetval;
  }
  else
  {
    return m_EmptyObject;
  }
}

/******************************************************************************/
/*! \see IQueue::getCount
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TQueue<T>::getCount() const
{
  return m_iCount;
}


/******************************************************************************/
/*! \see IQueue::flush
*/
/******************************************************************************/
template <class T> void MQUALIFIER TQueue<T>::flush()
{
  while(m_pElHead != NULL)
  {
    TBaseElement* pNext = m_pElHead->pNext;
    delete m_pElHead;
    m_pElHead = pNext;
  }
  m_iCount = 0;
  m_pElTail = NULL;
}

/******************************************************************************/
/*! \see IQueue::isEmpty
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TQueue<T>::isEmpty() const
{
  return (m_iCount == 0);
}

/******************************************************************************/
/*! \see IQueue::peekItem
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TQueue<T>::peekItem()
{
  if (m_pElHead != NULL)
  {
    return m_pElHead->tData;
  }
  else
  {
    return m_EmptyObject;
  }
}

/******************************************************************************/
/*! \see IQueue::peekItemConst
*/
/******************************************************************************/
template <class T> const T& MQUALIFIER TQueue<T>::peekItemConst() const
{
  if (m_pElHead != NULL)
  {
    return m_pElHead->tData;
  }
  else
  {
    return m_EmptyObject;
  }
}



/******************************************************************************/
/*! Copies a queue into an other queue
    \param rQueue: Queue to copy from
*/
/******************************************************************************/
template <class T> TQueue<T>& TQueue<T>::operator=(const TQueue<T>& rQueue)
{
  rQueue.copyToQueue(*this);
  return *this;
}

/******************************************************************************/
/*! Copies a queue into an other queue
    \param rQueue: Queue to copy from
*/
/******************************************************************************/
template <class T> TQueue<T>& TQueue<T>::operator=(const IQueue<T>& rQueue)
{
  rQueue.copyToQueue(*this);
  return *this;
}

END_NAMESPACE_Zeus


#endif
