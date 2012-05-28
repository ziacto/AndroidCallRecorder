/***************************************************************************
 * Copyright (C) 2008 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : SingleLinkedList
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 27.05.08 7:44 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/SingleLinkedList.hpp $
** 
** 21    27.05.08 7:44 Bha
** handing multible items on lists
** 
** 20    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 19    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 18    11.07.07 17:36 bha
** New methods getting first and last items
** 
** 17    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
** 
** 13    5.10.06 6:38 bha
** Stack types can hide addRef and release methods inside their interfaces
** 
** 12    18.09.06 12:40 Mabbuehl
** Bereinigung von Borland-Release-Warnungen, wo es m�lich und
** effizienter ist.
** 
** 7     7.09.06 14:44 bha
** Erweitern des Strings
***************************************************************************/


#ifndef SingleLinkedListH
#define SingleLinkedListH

#include <zeusbase/System/Interfaces/IList.hpp>
#include <zeusbase/System/Iterators.hpp>
#include <string.h>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! Template Klasse fuer Listen. Sie verwendet den abstrakten Datentypen
    IList. Die Listen sind als Single Linked List implementiert und
    verwalten einen Datentyp T.
*/
/*****************************************************************************/
template <class T> class TSingleLinkedList : public IList<T>
{
  public:
    //typename TSingleLinkedListElement;
    struct TSingleLinkedListElement;
    
    TSingleLinkedList();
    TSingleLinkedList(const T& rEmptyItem);
    TSingleLinkedList(const TSingleLinkedList<T>& rList);
    virtual ~TSingleLinkedList();

    //Interface IList
    virtual Int MQUALIFIER add(const T& rItem);
    virtual Int MQUALIFIER addAll(const IList<T>& rlstItems);
    virtual Int MQUALIFIER addEmptyItem();
    virtual void MQUALIFIER copyToList(IList<T>& rList) const;
    virtual void MQUALIFIER clear();
    virtual Retval MQUALIFIER deleteItem(Int iIndex);
    virtual Retval MQUALIFIER remove(const T& rItem);
    virtual Retval MQUALIFIER removeAll(const IList<T>& rlstItems);
    virtual Int MQUALIFIER getCount() const;
    virtual T& MQUALIFIER getItem(Int iIndex);
    virtual const T& MQUALIFIER getItemConst(Int iIndex) const;
    virtual bool MQUALIFIER equalsItem(Int iIndex, const T& rItem) const;
    virtual bool MQUALIFIER equals(const IList<T>& rList) const;
    virtual Int MQUALIFIER indexOf(const T& rItem) const;
    virtual Int MQUALIFIER insert(Int iIndex, const T& rItem);
    virtual IListIterator<T>* MQUALIFIER getIterator() const;
    virtual const IListIterator<T>* MQUALIFIER getConstIterator() const;
    virtual void MQUALIFIER releaseIterator(const IListIterator<T>* pIterator) const;
    virtual bool MQUALIFIER isEmpty() const;
    virtual T& MQUALIFIER getFirstItem();
    virtual const T& MQUALIFIER getFirstItemConst() const;
    virtual T& MQUALIFIER getLastItem();
    virtual const T& MQUALIFIER getLastItemConst() const;
    virtual bool MQUALIFIER hasItem(const T& rItem) const;
    virtual bool MQUALIFIER hasAllItems(const IList<T>& rlstItems) const;

    //Operators
    T& operator[] (Int iIndex);
    TSingleLinkedList<T>& operator= (const TSingleLinkedList<T>& rList);
    bool operator== (const TSingleLinkedList<T>& rList) const;
    bool operator!= (const TSingleLinkedList<T>& rList) const;
    TSingleLinkedListElement* getHeadElement() const;
    T& getEmptyElement();

  ////////////////////////////////////////////////////////////////////////
  // Container class must be public, because the class is needed by 
  // public methods
  public :

    /*********************************************************************/
    /*! Die Struktur TBaseElement ist die Speicherstruktur der SL-List
    */
    /*********************************************************************/
    struct TSingleLinkedListElement
    {
      /*****************************************************************/
      /*! Creates a container object
          \param data: Data Element
      */
      /*****************************************************************/
      TSingleLinkedListElement(const T& rData)
       : tData(const_cast<T&>(rData))
      {
        pNext = NULL;
      }

      /*****************************************************************/
      /*! Creates a container Object, witch points to a next element
      */
      /*****************************************************************/
      TSingleLinkedListElement(const T& rData, TSingleLinkedListElement* pNextPtr)
       : tData(const_cast<T&>(rData))
      {
        pNext = pNextPtr;
      }

      /// Objekt der Datenklasse T wird hier gespeichert
      T tData;
      /// Zeiger auf das naechste Objekt (Verkettung)
      TSingleLinkedListElement* pNext;
    };
  //public
  ////////////////////////////////////////////////////////////////////////

  protected:
    void resetAllIterators();

    /*********************************************************************/
    /*! Iterator der Liste
    */
    /*********************************************************************/
    class TSingleListIterator : public IListIterator<T>
    {
      public:
        /*****************************************************************/
        /*! Creates the ListIterator
            \param head : Head element
            \retval empty : Empty element
        */
        /*****************************************************************/
        TSingleListIterator(TSingleLinkedList& rParent)
        {
          m_iRefCounter = 1;
          m_pParent = &rParent;
          m_pNextIterator = NULL;
          m_pActElement = m_pParent->getHeadElement();
        }

        /*****************************************************************/
        /*! Creates the ListIterator
            \param head : Head element
            \retval empty : Empty element
        */
        /*****************************************************************/
        TSingleListIterator(const TSingleLinkedList& rParent)
        {
          m_iRefCounter = 1;
          m_pParent = const_cast<TSingleLinkedList<T>*>(&rParent);
          m_pNextIterator = NULL;
          m_pActElement = m_pParent->getHeadElement();
        }

        /*****************************************************************/
        /*! Destroys the ListIterator
        */
        /*****************************************************************/
        virtual ~TSingleListIterator(){}
        
        /*****************************************************************/
        /*! \see IListIterator::reset
        */
        /*****************************************************************/
        virtual void MQUALIFIER reset() const
        {
          m_pActElement = m_pParent->getHeadElement();
        }

        /*****************************************************************/
        /*! \see IListIterator::getNextItem
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItem() const
        {
          if (this->hasNextItem())
          {
            TSingleLinkedListElement* pTemp = m_pActElement;
            m_pActElement = m_pActElement->pNext;
            return pTemp->tData;
          }
          else
          {
            return m_pParent->getEmptyElement();
          }
        }


        /*****************************************************************/
        /*! \see IListIterator::getNextItemConst
        */
        /*****************************************************************/
        virtual const T& MQUALIFIER getNextItemConst() const
        {
          return (const T&)this->getNextItem();
        }
        
        /*****************************************************************/
        /*! s\see IListIterator::hasNextItem
        */
        /*****************************************************************/
        virtual bool MQUALIFIER hasNextItem() const
        {
          return (m_pActElement != NULL);
        }


        /*****************************************************************/
        /*! \see IZUnknown::askForInterface
        */
        /*****************************************************************/
        Retval MQUALIFIER askForInterface(const InterfaceID& /*rInterfaceID*/, IZUnknown*& /*rpIface*/)
        {
          return RET_UNKNOWN_INTERFACE;
        }

        /***************************************************************************/
        /*! \see IZUnknown::addRef
        */
        /***************************************************************************/
        void MQUALIFIER addRef() const
        {
          ++m_iRefCounter;
        }

        /***************************************************************************/
        /*! \see IZUnknown::release
        */
        /***************************************************************************/
        void MQUALIFIER release() const
        {
          --m_iRefCounter;
          if (m_iRefCounter <= 0)
          {
            if (m_pParent != NULL)
            {
              m_pParent->releaseIterator(this);
            }
            else
            {
              delete this;
            }
          }
        }

        /*****************************************************************/
        /*! Ermitteln des n�hsten Iterator Pointers
        */
        /*****************************************************************/
        TSingleListIterator* getNextIterator() const
        {
          return m_pNextIterator;
        }

        /*****************************************************************/
        /*! Setzen des n�hsten Iterator Pointers
        */
        /*****************************************************************/
        void setNextIterator(TSingleListIterator* pIt)
        {
          m_pNextIterator = pIt;
        }

        /*****************************************************************/
        /*! Ermitteln des aktuellen Elements
        */
        /*****************************************************************/
        TSingleLinkedListElement* getActElement() const
        {
          return m_pActElement;
        }

        /*****************************************************************/
        /*! Setzen des aktuellen Elements
        */
        /*****************************************************************/
        void setActElement(TSingleLinkedListElement* pActElement)
        {
          m_pActElement = pActElement;
        }
        
        /*****************************************************************/
        /*! clears the parent instance
        */
        /*****************************************************************/
        void clearParent()
        {
          m_pParent = NULL;
        }

      private:
        ///Parent object
        mutable TSingleLinkedList* m_pParent;
        ///Next iterator
        mutable TSingleListIterator* m_pNextIterator;
        ///Actual element of the iterator
        mutable TSingleLinkedListElement* m_pActElement;
        ///Reference counter
        mutable Int m_iRefCounter;
    };

  private:

    ///Reference counter
    Int m_iRefCounter;
    ///Zeiger auf den Kopf der Liste
    TSingleLinkedListElement* m_pHead;
    ///Zeiger auf das Ende der Liste
    TSingleLinkedListElement* m_pTail;
    ///Iterator Zeiger
    mutable TSingleListIterator* m_pIterator;
    ///Zaehler der Listenelemente
    Int m_iCounter;

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

  protected:
    ///Leeres Objekt bei Fehler
    T m_tEmpty;
};

/******************************************************************************/
/*! Konstruktor der SingleLinked List
*/
/******************************************************************************/
template <class T> TSingleLinkedList<T>::TSingleLinkedList()
 /* COMPILER PROBLEM*/
 /*#ifdef A_COMPILER_TYPE
    : m_Empty(getDefaultEmpty())
   #else
    : m_tEmpty(T())
   #endif
 */
 : m_tEmpty(T())
{
  m_iRefCounter = 1;
  m_iCounter = 0;
  m_pIterator = NULL;
  m_pTail = NULL;
  m_pHead = NULL;

  // DO NOT USE MEMSET. This causes memory leaks on complex objects
  //memset(&m_tEmpty, 0, sizeof(T));
}


/******************************************************************************/
/*! Bei diesem Konstruktor kann der Rckgabetyp gesetzt werden,
    wenn ein Indexfehler auftritt.
    \param rEmptyItem : Leeres Element welches beim Fehlerfall zurueckgegeben
                       wird.
*/
/******************************************************************************/
template <class T> TSingleLinkedList<T>::TSingleLinkedList(const T& rEmptyItem)
 : m_tEmpty(rEmptyItem)
{
  m_iRefCounter = 1;
  m_iCounter = 0;
  m_pIterator = NULL;
  m_pTail = NULL;
  m_pHead = NULL;
}

/******************************************************************************/
/*! Copy constructor
    \param rList : List to copy
*/
/******************************************************************************/
template <class T> TSingleLinkedList<T>::TSingleLinkedList(const TSingleLinkedList<T>& rList)
{
  m_iRefCounter = 1;
  m_iCounter = 0;
  m_pIterator = NULL;
  m_pTail = NULL;
  m_pHead = NULL;
  *this = rList;
}


/******************************************************************************/
/*! Destruktor der Liste. Die Liste wird geloescht
*/
/******************************************************************************/
template <class T> TSingleLinkedList<T>::~TSingleLinkedList()
{
  clear();
  
  //Reseten aller Iteratoren
  TSingleListIterator* pIt = m_pIterator;
  while (pIt != NULL)
  {
    pIt->clearParent();
    pIt = pIt->getNextIterator();
  }
}

/******************************************************************************/
/*! Gets the Headelement of the list
*/
/******************************************************************************/
template <class T> typename TSingleLinkedList<T>::TSingleLinkedListElement* TSingleLinkedList<T>::getHeadElement() const
{
  return m_pHead;
}

/******************************************************************************/
/*! Gets the Empty data element
*/
/******************************************************************************/
template <class T> T& TSingleLinkedList<T>::getEmptyElement()
{
  return m_tEmpty;
}



/******************************************************************************/
/*! \see IList::add
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TSingleLinkedList<T>::add(const T& rItem)
{
  //Noch kein Item in der Liste
  if (m_pHead == NULL)
  {
    m_pHead = new TSingleLinkedListElement(rItem);
    m_pTail = m_pHead;

    //notification of the new head element
    resetAllIterators();
  }

  //Anfuegen des Items
  else
  {
    TSingleLinkedListElement* pNewItem = new TSingleLinkedListElement(rItem);
    m_pTail->pNext = pNewItem;
    m_pTail = pNewItem;  //Neuer Tail
  }
  m_iCounter++;
  return m_iCounter-1;
}

/******************************************************************************/
/*! \see IList::addAll
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TSingleLinkedList<T>::addAll(const IList<T>& rlstItems)
{
  TConstIterator<T> It = rlstItems.getConstIterator();
  while(It.hasNextItem())
  {
    this->add(It.getNextItemConst());
  }

  return m_iCounter-1;
}

/******************************************************************************/
/*! \see IList::addEmptyItem
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TSingleLinkedList<T>::addEmptyItem()
{
  return this->add(m_tEmpty);
}

/******************************************************************************/
/*! \see IList::copyToList
*/
/******************************************************************************/
template <class T> void MQUALIFIER TSingleLinkedList<T>::copyToList(IList<T>& rList) const
{
  rList.clear();

  //Copy of the data
  TSingleLinkedListElement* pItem = m_pHead;
  while (pItem != NULL)
  {
    rList.add(pItem->tData);
    pItem = pItem->pNext;
  }
}


/******************************************************************************/
/*! \see IList::clear
*/
/******************************************************************************/
template <class T> void MQUALIFIER TSingleLinkedList<T>::clear()
{
  while (m_pHead != NULL)
  {
    TSingleLinkedListElement* pNextItem = m_pHead->pNext;
    delete m_pHead;
    m_pHead = pNextItem;
    m_iCounter--;
  }

  //Zuruecksetzen der Liste
  m_pHead = NULL;
  m_pTail = NULL;
  m_iCounter = 0;

  //Loeschen des Iteratorreferenzen
  resetAllIterators();
}


/******************************************************************************/
/*! \see IList::deleteItem
*/
/******************************************************************************/
template <class T> Retval MQUALIFIER TSingleLinkedList<T>::deleteItem(Int iIndex)
{
  Retval retVal = RET_REQUEST_FAILED;
  if (m_pHead != NULL && iIndex >= 0 && iIndex < m_iCounter)
  {
    TSingleLinkedListElement* pItem = m_pHead;
    TSingleLinkedListElement* pPrevItem = NULL;
    Int iCounter =0;

    while (pItem != NULL && iCounter < iIndex)
    {
      pPrevItem = pItem;
      pItem = pItem->pNext;
      iCounter++;
    }

    //------------------------------------------------------------------------
    //Fall 1: Item[0] (Head) soll geloescht werden.
    if(pItem == m_pHead)
    {
      //Anpassen der neuen Headers der Iteratoren
      TSingleListIterator* it = m_pIterator;
      while (it != NULL)
      {
        if (it->getActElement() == m_pHead)
        {
          it->setActElement(m_pHead->pNext);
        }
        it = it->getNextIterator();
      }

      pItem = m_pHead->pNext;
      delete m_pHead;
      m_pHead = pItem;
      m_iCounter--;

      //Falls Nur ein Element existierte
      if (m_pHead == NULL)
      {
        m_pTail = NULL;
      }
      retVal = RET_NOERROR;
    }

    //------------------------------------------------------------------------
    //Fall 2: Letzes rItem wird geloescht
    else if (pItem == m_pTail)
    {
      //Anpassen des aktuellen Items der Iteratoren, wenn das Item das
      //geloeschte ist.
      TSingleListIterator* it = m_pIterator;
      while (it != NULL)
      {
        if (it->getActElement() == m_pTail)
        {
          it->setActElement(NULL);
        }
        it = it->getNextIterator();
      }

      //Loeschen des Letzten Items
      delete m_pTail;
      m_pTail = pPrevItem;
      pPrevItem->pNext = NULL;
      m_iCounter--;
      retVal = RET_NOERROR;
    }

    //------------------------------------------------------------------------
    //Fall 3 : Loeschen eines Item in der Mitte der Liste
    else if (pItem != NULL)
    {
      TSingleLinkedListElement* pNextItem = pItem->pNext;

      //Anpassen des aktuellen Items der Iteratoren, wenn das Item das
      //geloeschte ist.
      TSingleListIterator* it = m_pIterator;
      while (it != NULL)
      {
        if (it->getActElement() == pItem)
        {
          it->setActElement(pNextItem);
        }
        it = it->getNextIterator();
      }

      delete pItem;
      pPrevItem->pNext = pNextItem;
      m_iCounter--;
      retVal = RET_NOERROR;
    }
  }
  return retVal;
}


/******************************************************************************/
/*! \see IList::indexOf
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TSingleLinkedList<T>::indexOf(const T& rItem) const
{
  TSingleLinkedListElement* pItem = m_pHead;
  Int iCounter = INVALID_INDEX;
  while (pItem != NULL)
  {
    iCounter++;
    if (pItem->tData == rItem)
    {
      return iCounter;
    }
    pItem = pItem->pNext;
  }

  return INVALID_INDEX;
}

/******************************************************************************/
/*! \see IList::insert
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TSingleLinkedList<T>::insert(Int iIndex, const T& rItem)
{
  if (iIndex >= 0)
  {
    Int iCounter = 0;
    TSingleLinkedListElement* pItem = m_pHead;  //Vor diesem Item Einfuegen
    TSingleLinkedListElement* pPrevItem = NULL; //Nach diesem Item Einfuegen

    while(pItem != NULL && iCounter < iIndex)
    {
      pPrevItem = pItem;
      pItem = pItem->pNext;
      iCounter++;
    }

    //Fall 1: Ein Element in der Mitte der Liste einfuegen
    if (pItem != NULL)
    {
      //Als HeadElement einfuegen
      if (pPrevItem == NULL)
      {
        m_pHead = new TSingleLinkedListElement(rItem, pItem);
      }
      else
      {
        pPrevItem->pNext = new TSingleLinkedListElement(rItem, pItem);
      }
      m_iCounter++;
      return iCounter;
    }

    //Am Ende der Liste Anfuegen
    else if (pItem == NULL && iIndex == iCounter)
    {
      //List was empty
      if (pPrevItem == NULL)
      {
        m_pHead = new TSingleLinkedListElement(rItem);
        m_pTail = m_pHead;

        //notification of the new head element
        resetAllIterators();
      }

      else
      {
        m_pTail = new TSingleLinkedListElement(rItem);
        pPrevItem->pNext = m_pTail;
      }
      m_iCounter++;
      return iCounter;
    }
    else
    {
      return INVALID_INDEX;
    }
  }
  else
  {
    return INVALID_INDEX;
  }
}


/******************************************************************************/
/*! \see IList::remove
*/
/******************************************************************************/
template <class T> Retval MQUALIFIER TSingleLinkedList<T>::remove(const T& rItem)
{
  return deleteItem(indexOf(rItem));
}

/***************************************************************************/
/*! \see IList::removeAll
*/
/***************************************************************************/
template <class T> Retval MQUALIFIER TSingleLinkedList<T>::removeAll(const IList<T>& rlstItems)
{
  Retval retValue = RET_REQUEST_FAILED;
  bool bOK = false;
  TConstIterator<T> It = rlstItems.getConstIterator();
  while(It.hasNextItem())
  {
    bOK |= (this->remove(It.getNextItemConst()) == RET_NOERROR);
  }

  if (bOK)
  {
    retValue = RET_NOERROR;
  }
  return retValue;
}


/******************************************************************************/
/*! \see IList::getCount
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TSingleLinkedList<T>::getCount() const
{
  return  m_iCounter;
}


/******************************************************************************/
/*!  Siehe ADT IList
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TSingleLinkedList<T>::getItem(Int iIndex)
{
  Int iCounter = 0;
  TSingleLinkedListElement* pItem = m_pHead;  //Start

  while(pItem != NULL && iCounter < iIndex)
  {
    pItem = pItem->pNext;
    iCounter++;
  }

  if (pItem != NULL && iIndex >= 0)
  {
    return pItem->tData;
  }
  else
  {
    return m_tEmpty;
  }
}

/******************************************************************************/
/*!  Siehe ADT IList
*/
/******************************************************************************/
template <class T> const T& MQUALIFIER TSingleLinkedList<T>::getItemConst(Int iIndex) const
{
  Int iCounter = 0;
  TSingleLinkedListElement* pItem = m_pHead;  //Start

  while(pItem != NULL && iCounter < iIndex)
  {
    pItem = pItem->pNext;
    iCounter++;
  }

  if (pItem != NULL && iIndex >= 0)
  {
    return pItem->tData;
  }
  else
  {
    return m_tEmpty;
  }
}

/******************************************************************************/
/*!  Siehe ADT IList
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TSingleLinkedList<T>::equalsItem(Int iIndex, const T& rItem) const
{
  return (getItemConst(iIndex) == rItem);
}

/******************************************************************************/
/*! \see IList::equals
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TSingleLinkedList<T>::equals(const IList<T>& rList) const
{
  bool bRetval = (rList.getCount() == m_iCounter);
  
  if (bRetval)
  {
    TSingleLinkedListElement* pItem = m_pHead;  //Start
    Int iCounter = 0;
    
    while (pItem != NULL && bRetval)
    {
      bRetval &= rList.equalsItem(iCounter, pItem->tData);
      pItem = pItem->pNext;
      ++iCounter;
    }
  }
  
  return bRetval;
}

/******************************************************************************/
/*!  Siehe ADT IList
*/
/******************************************************************************/
template <class T> IListIterator<T>* MQUALIFIER TSingleLinkedList<T>::getIterator() const
{
  TSingleListIterator* pIterator = new TSingleListIterator(*this);
  pIterator->setNextIterator(m_pIterator);
  m_pIterator = pIterator;
  return m_pIterator;
}

/******************************************************************************/
/*!  Siehe ADT IList
*/
/******************************************************************************/
template <class T> const IListIterator<T>* MQUALIFIER TSingleLinkedList<T>::getConstIterator() const
{
  TSingleListIterator* pIterator = new TSingleListIterator(*this);
  pIterator->setNextIterator(m_pIterator);
  m_pIterator = pIterator;
  return m_pIterator;
}

/******************************************************************************/
/*!  Siehe ADT IList
*/
/******************************************************************************/
template <class T> void MQUALIFIER TSingleLinkedList<T>::releaseIterator(const IListIterator<T>* pIterator) const
{
  TSingleListIterator* pIt = m_pIterator;
  TSingleListIterator* pItPrev = NULL;
  while (pIt != NULL)
  {
    if (pIt == pIterator)
    {
      //Erster Iterator loeschen
      if (pItPrev == NULL)
      {
        m_pIterator = pIt->getNextIterator();
        delete pIt;
      }
      else
      {
        pItPrev->setNextIterator(pIt->getNextIterator());
        delete pIt;
      }
      break;
    }
    pItPrev = pIt;
    pIt = pIt->getNextIterator();
  }
}

/******************************************************************************/
/*! \see IList::isEmpty
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TSingleLinkedList<T>::isEmpty() const
{
  return (m_iCounter == 0);
}

/******************************************************************************/
/*! \see IList::getFirstItem
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TSingleLinkedList<T>::getFirstItem()
{
  return this->getItem(0);
}

/******************************************************************************/
/*! \see IList::getFirstItemConst
*/
/******************************************************************************/
template <class T> const T& MQUALIFIER TSingleLinkedList<T>::getFirstItemConst() const
{
  return this->getItemConst(0);
}

/******************************************************************************/
/*! \see IList::getLastItem
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TSingleLinkedList<T>::getLastItem()
{
  return this->getItem(m_iCounter-1);
}

/******************************************************************************/
/*! \see IList::getLastItemConst
*/
/******************************************************************************/
template <class T> const T& MQUALIFIER TSingleLinkedList<T>::getLastItemConst() const
{
  return this->getItemConst(m_iCounter-1);
}

/******************************************************************************/
/*! \see IList::hasItem
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TSingleLinkedList<T>::hasItem(const T& rItem) const
{
  return (this->indexOf(rItem) != INVALID_INDEX);
}

/******************************************************************************/
/*! \see IList::hasAllItems
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TSingleLinkedList<T>::hasAllItems(const IList<T>& rlstItems) const
{
  bool bRetval = true;

  TConstIterator<T> It = rlstItems.getConstIterator();
  while(bRetval && It.hasNextItem())
  {
    bRetval &= this->hasItem(It.getNextItemConst());
  }
  return bRetval;
}

/******************************************************************************/
/*! Operator for selection an indexed item
    \param iIndex : Index of the item
    \return indexed item
*/
/******************************************************************************/
template <class T> T& TSingleLinkedList<T>::operator[](Int iIndex)
{
  return getItem(iIndex);
}


/******************************************************************************/
/*! Operator zum kopieren einer Liste
    \param list : Ausgangsliste
    \return neu kopierte Liste
*/
/******************************************************************************/
template <class T> TSingleLinkedList<T>& TSingleLinkedList<T>::operator=(const TSingleLinkedList<T>& rList)
{
  rList.copyToList(*this);
  return *this;
}

/******************************************************************************/
/*! Operator to check equality of two lists
    \param list : list to check
    \retval true : Equal
    \retval false : not equal
*/
/******************************************************************************/
template <class T> bool  TSingleLinkedList<T>::operator==(const TSingleLinkedList<T>& rList) const
{
  return this->equals(rList);
}

/******************************************************************************/
/*! Checks if two list are not equal
    \param rList : list to check
*/
/******************************************************************************/
template <class T> bool  TSingleLinkedList<T>::operator!=(const TSingleLinkedList<T>& rList) const
{
  return !this->equals(rList);
}

/******************************************************************************/
/*! Resets all iterators
*/
/******************************************************************************/
template <class T> void TSingleLinkedList<T>::resetAllIterators()
{
  TSingleListIterator* pIt = m_pIterator;
  while (pIt != NULL)
  {
    pIt->reset();
    pIt = pIt->getNextIterator();
  }
}

END_NAMESPACE_Zeus

#endif

