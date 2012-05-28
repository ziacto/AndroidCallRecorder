/***************************************************************************
 * Copyright (C) 2008 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : ArrayList
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 27.05.08 7:41 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/ArrayList.hpp $
** 
** 29    27.05.08 7:41 Bha
** Methods for handing multible items added
** 
** 28    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 27    8.02.08 12:59 Bha
** Commenting
** 
** 26    21.01.08 18:23 Bha
** Copy method added for arrays
** 
** 25    7.01.08 9:03 Bha
** const method to get the array implemented
** 
** 24    12.09.07 17:22 bha
** Error coping data from different heap objects. No pointer adoption
** allowed
**
** 23    3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
**
** 22    11.07.07 17:36 bha
** New methods getting first and last items
**
** 21    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
**
** 17    5.10.06 6:38 bha
** Stack types can hide addRef and release methods inside their interfaces
**
** 16    18.09.06 12:40 Mabbuehl
** Bereinigung von Borland-Release-Warnungen, wo es m�lich und
** effizienter ist.
**
** 10    7.09.06 14:44 bha
** Erweitern des Strings
***************************************************************************/

#ifndef ArrayListH
#define ArrayListH

#include <zeusbase/System/Interfaces/IArray.hpp>
#include <zeusbase/System/Iterators.hpp>

#include <string.h>
#include <assert.h>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! This template class implements an array based list of a type T. The
    array list uses two methods to copy arrays: the shallow copy is used
    to copy primitive data types. A memory copy function is used. The deep copy
    method uses the copy constructor of the class T.
    The array list is faster using the [] operator than other list
    implementations.
*/
/*****************************************************************************/
template <class T> class TArrayList : public IArray<T>
{
  public:

    TArrayList(Int iSize = 20, EArrayCopyMode eCopyMode = etDeepCopy);
    TArrayList(const T* pArray, Int iSize, EArrayCopyMode eCopyMode, bool bAttachPointer = false);
    TArrayList(const T& rEmptyItem, Int iSize, EArrayCopyMode eCopyMode);

    virtual ~TArrayList();

    ///Copy constructors
    TArrayList(const TArrayList<T>& rList);
    TArrayList(const IArray<T>* pList);

    //Methods of IArray
    virtual T* MQUALIFIER getArray() const;
    virtual const T* MQUALIFIER getArrayConst() const;
    virtual Int MQUALIFIER getArraySize() const;
    virtual Retval MQUALIFIER setArray(const T* pArray, Int iSize, bool bAttachPointer = false);
    virtual Retval MQUALIFIER appendArray(const T* pArray, Int iSize);
    virtual Retval MQUALIFIER copyToArray(IArray<T>& rDest, Int iStart, Int iEnd) const;
    virtual EArrayCopyMode MQUALIFIER getCopyMode() const;

    //Methods of IList
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
    T& operator[](Int iIndex);
    TArrayList<T>& operator=(const IList<T>& rList);
    TArrayList<T>& operator=(const IList<T>* pList);
    TArrayList<T>& operator=(const TArrayList<T>& rList);
    TArrayList<T>& operator=(const TArrayList<T>* pList);
    bool operator==(const TArrayList<T>& rList) const;
    bool operator!=(const TArrayList<T>& rList) const;
    T& getEmptyItem();

    //Copy methods
    Retval copyToArray(TArrayList<T>& rDest,
                       Int iStart = 0,
                       Int iEnd = INVALID_INDEX) const;
    Retval copyToArray(T* pBuffer,
                       Int iBufferSize,
                       Int& rCopiedSize,
                       Int iStart = 0,
                       Int iEnd = INVALID_INDEX) const;

    Retval setArray2(const T* pArray, Int iSize, bool bAttachPointer = false);

  protected:

  private:

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

    /*********************************************************************/
    /*! Iterator der Liste
    */
    /*********************************************************************/
    class TArrayListIterator : public IListIterator<T>
    {
      public:
        /*****************************************************************/
        /*! Creates the ArrayList iterator
            \param parent : Parameter list
        */
        /*****************************************************************/
        TArrayListIterator(TArrayList& rParent)
        {
          m_iRefCounter = 1;
          m_pParent = &rParent;
          m_pNextIterator = NULL;
          m_iActElement = 0;
          m_tEmpty = m_pParent->getEmptyItem();
        }

        /*****************************************************************/
        /*! Creates the ArrayList const iterator
            \param parent : Parameter list
        */
        /*****************************************************************/
        TArrayListIterator(const TArrayList& rParent)
        {
          m_iRefCounter = 1;
          m_pParent = const_cast<TArrayList<T>*>(&rParent);
          m_pNextIterator = NULL;
          m_iActElement = 0;
          m_tEmpty = m_pParent->getEmptyItem();
        }

        /*****************************************************************/
        /*! Destroys the iterator
        */
        /*****************************************************************/
        virtual ~TArrayListIterator()
        {}

        /*****************************************************************/
        /*! \see IListIterator::reset
        */
        /*****************************************************************/
        virtual void MQUALIFIER reset() const
        {
          m_iActElement = 0;
        }

        /*****************************************************************/
        /*! \see IListIterator::getNextItem
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItem() const
        {
          if (this->hasNextItem())
          {
            m_iActElement++;
            return m_pParent->getItem(m_iActElement-1);
          }
          else
          {
            return m_tEmpty;
          }
        }

        /*****************************************************************/
        /*! \see IListIterator::getNextItemConst
        */
        /*****************************************************************/
        virtual const T& MQUALIFIER getNextItemConst() const
        {
          return const_cast<const T&>(this->getNextItem());
        }

        /*****************************************************************/
        /*! \see IListIterator::hasNextItem
        */
        /*****************************************************************/
        virtual bool MQUALIFIER hasNextItem() const
        {
          return (m_pParent != NULL && m_iActElement < m_pParent->getCount());
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
        TArrayListIterator* getNextIterator() const
        {
          return m_pNextIterator;
        }

        /*****************************************************************/
        /*! Setzen des n�hsten Iterator Pointers
        */
        /*****************************************************************/
        void setNextIterator(TArrayListIterator* pIt)
        {
          m_pNextIterator = pIt;
        }

        /*****************************************************************/
        /*! Lesen der aktueller Elementposition
        */
        /*****************************************************************/
        Int getActElement()
        {
          return m_iActElement;
        }

        /*****************************************************************/
        /*! Setzen der aktueller Elementposition
        */
        /*****************************************************************/
        void setActElement(Int iElement)
        {
          m_iActElement = iElement;
        }

        /*****************************************************************/
        /*! Sets the parent to NULL
        */
        /*****************************************************************/
        void clearParent()
        {
          m_pParent = NULL;
        }

      private:
        mutable TArrayList* m_pParent;
        mutable TArrayListIterator* m_pNextIterator;
        mutable Int m_iActElement;
        mutable T m_tEmpty;
        ///Reference counter
        mutable Int m_iRefCounter;
    };

    ///Data array
    T* m_pDataArray;
    ///Iterator pointer
    mutable TArrayListIterator* m_pIterator;
    ///Counts the list elements
    Int m_iCounter;
    ///Size of the array
    Int m_iSize;
    ///Initialized array size (original size)
    Int m_iOrigSize;
    ///empty object
    T m_tEmpty;
    ///Copy mode
    EArrayCopyMode m_eCopyMode;

    void resize(Int iNewSize);
};




/******************************************************************************/
/*! Creates an array list.
    \param iSize : Size of the array
    \param eCopyMode : Copy mode of the array. Deep copy uses the copy
                       constructor of the objects, shallow copy uses the
                       memory copy function
*/
/******************************************************************************/
template <class T> TArrayList<T>::TArrayList(Int iSize, EArrayCopyMode eCopyMode /*= etDeepCopy*/)
 /* COMPILER PROBLEM*/
 /*#ifdef A_COMPILER_TYPE
    : m_Empty(getDefaultEmpty())
   #else
    : m_tEmpty(T())
   #endif
 */
 : m_tEmpty(T())
{
  m_eCopyMode = eCopyMode;
  m_iSize = iSize;
  m_iOrigSize = iSize;
  m_iCounter = 0;
  m_pIterator = NULL;
  m_pDataArray = new T[m_iSize];

  // DO NOT USE MEMSET. This causes memory leaks on complex objects
  //  memset(&m_tEmpty, 0, sizeof(T));
  assert(m_pDataArray != NULL);
}

/******************************************************************************/
/*! Creates an array list
    \param pArray : Array to be wrapped
    \param iSize : Size of the array
    \param eCopyMode : Copy mode of the array. Deep copy uses the copy
                       constructor of the objects, shallow copy uses the
                       memory copy function
    \param bAttachPointer : if this flag is set the pointer of the array will
                           be attached (managed by the array class).
*/
/******************************************************************************/
template <class T> TArrayList<T>::TArrayList(const T* pArray, Int iSize,
                                             EArrayCopyMode eCopyMode,
                                             bool bAttachPointer)
 /* COMPILER PROBLEM*/
 /*#ifdef A_COMPILER_TYPE
    : m_Empty(getDefaultEmpty())
   #else
    : m_tEmpty(T())
   #endif
 */
 : m_tEmpty(T())
{
  m_eCopyMode = eCopyMode;
  m_iSize = iSize;
  m_iOrigSize = iSize;
  m_pIterator = NULL;
  m_pDataArray = NULL;
  m_iCounter = 0;

  if (!bAttachPointer)
  {
    setArray2(pArray, iSize);
  } //(!bAttachPointer)

  else
  {
    m_pDataArray = const_cast<T*>(pArray);
    m_iCounter = iSize;
  } //(bAttachPointer)

  assert(m_pDataArray != NULL);
}

/******************************************************************************/
/*! Creates an array list. Using this constructor the empty item can be set.
    The empty element is returned if there is an index error
    \param rEmptyItem : Empty element.
    \param iSize : Size of the array list
    \param eCopyMode : Copy mode of the array. Deep copy uses the copy
                       constructor of the objects, shallow copy uses the
                       memory copy function
*/
/******************************************************************************/
template <class T> TArrayList<T>::TArrayList(const T& rEmptyItem,
                                             Int iSize,
                                             EArrayCopyMode eCopyMode)
 : m_tEmpty(rEmptyItem)
{
  m_eCopyMode = eCopyMode;
  m_iSize = iSize;
  m_iOrigSize = iSize;
  m_iCounter = 0;
  m_pIterator = NULL;
  m_pDataArray =  new T[m_iSize];

  assert(m_pDataArray != NULL);
}

/******************************************************************************/
/*! Copy constructor
    \param rList : ArrayList to copy
*/
/******************************************************************************/
template <class T> TArrayList<T>::TArrayList(const TArrayList<T>& rList)
 /* COMPILER PROBLEM*/
 /*#ifdef A_COMPILER_TYPE
    : m_Empty(getDefaultEmpty())
   #else
    : m_tEmpty(T())
   #endif
 */
 : m_tEmpty(T())
{
  m_eCopyMode = rList.getCopyMode();
  m_iSize = rList.getArraySize();
  m_iOrigSize = m_iSize;
  m_iCounter = 0;
  m_pIterator = NULL;
  m_pDataArray = NULL;

  // DO NOT USE MEMSET. This causes memory leaks on complex objects
  //memset(&m_tEmpty, 0, sizeof(T));

  this->setArray2(rList.getArray(), rList.getCount());

  assert(m_pDataArray != NULL);
}

/******************************************************************************/
/*! Copy constructor
    \param pList : ArrayList to copy
*/
/******************************************************************************/
template <class T> TArrayList<T>::TArrayList(const IArray<T>* pList)
 /* COMPILER PROBLEM*/
 /*#ifdef A_COMPILER_TYPE
    : m_Empty(getDefaultEmpty())
   #else
    : m_tEmpty(T())
   #endif
 */
 : m_tEmpty(T())
{
  m_eCopyMode = etDeepCopy;
  m_iCounter = 0;
  m_pIterator = NULL;
  m_pDataArray = NULL;

  // DO NOT USE MEMSET. This causes memory leaks on complex objects
  // memset(&m_tEmpty, 0, sizeof(T));
  if (pList != NULL)
  {
    m_iSize = pList->getArraySize();
    m_iOrigSize = m_iSize;
    m_eCopyMode = pList->getCopyMode();
    this->setArray(pList->getArray(), pList->getCount());
  }
  else
  {
    m_iSize = 20;
    m_iOrigSize = 20;
    m_pDataArray =  new T[m_iSize];
  }

  assert(m_pDataArray != NULL);
}


/******************************************************************************/
/*! Destroys the array list
*/
/******************************************************************************/
template <class T> TArrayList<T>::~TArrayList()
{
  //Reseten aller Iteratoren
  TArrayListIterator* pIt = m_pIterator;
  while (pIt != NULL)
  {
    pIt->clearParent();
    pIt = pIt->getNextIterator();
  }
  delete [] m_pDataArray;
}


/******************************************************************************/
/*! This returns the allocated size of the array. The difference between the
    getCount() method and getArraySize() is, that getCount() returns the
    count of items in an array, and getArraySize() returns the size of the
    array, witch is normaly bigger or equal to the count.
    \return array size:
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TArrayList<T>::getArraySize() const
{
  return m_iSize;
}


/******************************************************************************/
/*! \see IArray::getArray
*/
/******************************************************************************/
template <class T> T* MQUALIFIER TArrayList<T>::getArray() const
{
  return m_pDataArray;
}

/******************************************************************************/
/*! \see IArray::getArrayConst
*/
/******************************************************************************/
template <class T> const T* MQUALIFIER TArrayList<T>::getArrayConst() const
{
  return m_pDataArray;
}

/******************************************************************************/
/*! \see IArray::setArray
*/
/******************************************************************************/
template <class T> Retval MQUALIFIER TArrayList<T>::setArray(const T* pArray, Int iSize, bool bAttachPointer /*= false*/)
{
  Retval retVal = RET_INVALID_DATA;

  if (!bAttachPointer || this->getCopyMode() != etDeepCopy)
  {
    retVal = setArray2(pArray, iSize, bAttachPointer);
  }

  return retVal;
}

/******************************************************************************/
/*! sets an array
    \param bAttachPointer : Adopts the pointer given
    \see IArray::setArray
*/
/******************************************************************************/
template <class T> Retval TArrayList<T>::setArray2(const T* pArray, Int iSize, bool bAttachPointer /*= false*/)
{
  Retval retVal = RET_INVALID_PARAMETER;

  if (!bAttachPointer)
  {
    //Speciality: Sets the original size to the new size required and call clear, witch will
    // free the actual array and allocate the array with original size
    m_iOrigSize = iSize+2;
    this->clear();
    ///////////////

    if (pArray != NULL)
    {
      //Copy the array
      switch(m_eCopyMode)
      {
        case etShallowCopy:
          ::memcpy(m_pDataArray, pArray, sizeof(T)*iSize);
        break;

        case etDeepCopy :  //fall though
        default:
          for(Int i = 0; i < iSize; i++)
          {
            m_pDataArray[i] = pArray[i];
          }
        break;
      }
      m_iCounter = iSize;
      retVal = RET_NOERROR;
    }
  } //(!bAttachPointer)
  else
  {
    if (m_pDataArray != NULL)
    {
      delete [] m_pDataArray;
    }
    m_pDataArray = const_cast<T*>(pArray);
    m_iOrigSize = iSize;
    m_iCounter = iSize;
    m_iSize = iSize;

    //Reseten aller Iteratoren
    TArrayListIterator* pIt = m_pIterator;
    while (pIt != NULL)
    {
      pIt->reset();
      pIt = pIt->getNextIterator();
    }
  } //(bAttachPointer)

  return retVal;
}

/******************************************************************************/
/*! \see IArray::appendArray
*/
/******************************************************************************/
template <class T> Retval MQUALIFIER TArrayList<T>::appendArray(const T* pArray, Int iSize)
{
  Retval retVal = RET_INVALID_PARAMETER;
  if (pArray != NULL)
  {
    if (m_iCounter + iSize >= m_iSize)
    {
      resize(m_iSize + iSize);
    }

    //append the array
    switch(m_eCopyMode)
    {
      case etShallowCopy:
        ::memcpy(&m_pDataArray[m_iCounter], pArray, sizeof(T)*iSize);
      break;

      case etDeepCopy :  //fall though
      default:
        for(Int i = 0; i < iSize; i++)
        {
          m_pDataArray[i + m_iCounter] = pArray[i];
        }
      break;
    }
    m_iCounter += iSize;
    retVal = RET_NOERROR;
  }
  return retVal;
}


/******************************************************************************/
/*! \see IArray::copyToArray
*/
/******************************************************************************/
template <class T> Retval MQUALIFIER TArrayList<T>::copyToArray(IArray<T>& rDest, Int iStart, Int iEnd) const
{
  Retval retVal = RET_INVALID_PARAMETER;

  //Not supported for interfaces. For interfaces IArray<Iface> you
  // MUST use shallow copy
  if (rDest.getCopyMode() == etDeepCopy)
  {
    retVal = RET_INVALID_DATA;
    assert(false);
  }
  else if (iStart <= iEnd)
  {
    if (iStart < 0 || iEnd >= m_iCounter)
    {
      retVal = RET_REQUEST_FAILED;
    }
    else
    {
      Int iArraySize = iEnd - iStart + 1;
      T* pArr = new T[iArraySize];
      ::memcpy(pArr, &(m_pDataArray[iStart]), sizeof(T)*iArraySize);
      rDest.setArray(pArr, iArraySize, false);
      retVal = RET_NOERROR;
      delete [] pArr;
    }
  }

  return retVal;
}

/******************************************************************************/
/*! copies the data to an array list
    \param rDest : Destination
    \param iStart : Start index to copy from (default = 0)
    \param iEnd : End index (default = INVALID_INDEX, copies to the end)
    \retval RET_INVALID_PARAMETER : Invalid index iStart > iEnd
    \retval RET_REQUEST_FAILED : indices are out of bounds
    \retval RET_NOERROR : Array copied
*/
/******************************************************************************/
template <class T> Retval TArrayList<T>::copyToArray(TArrayList<T>& rDest,
                                                     Int iStart /*= 0*/,
                                                     Int iEnd /*= INVALID_INDEX*/) const
{
  Retval retVal = RET_INVALID_PARAMETER;
  if (iEnd == INVALID_INDEX)
  {
    iEnd = m_iCounter -1;
  }

  if (iStart <= iEnd)
  {
    if (iStart < 0 || iEnd >= m_iCounter)
    {
      retVal = RET_REQUEST_FAILED;
    }
    else
    {
      Int iArraySize = iEnd - iStart + 1;
      T* pArr = new T[iArraySize];

      //copy the array
      switch(m_eCopyMode)
      {
        case etShallowCopy:
          ::memcpy(pArr, &(m_pDataArray[iStart]), sizeof(T)*iArraySize);
        break;

        case etDeepCopy :  //fall though
        default:
          for(Int i = 0; i < iArraySize; ++i)
          {
            pArr[i] = m_pDataArray[i + iStart];
          }
        break;
      }

      rDest.setArray2(pArr, iArraySize, true);
      retVal = RET_NOERROR;
    }
  }
  return retVal;
}

/******************************************************************************/
/*! copies the data to an array or buffer
    \param pBuffer : Destination Buffer
    \param iBufferSize : Size of the buffer
    \param iStart : Start index to copy from (default = 0)
    \param iEnd : End index (default = INVALID_INDEX, copies to the end)
    \retval RET_INVALID_PARAMETER : Invalid index iStart > iEnd
    \retval RET_REQUEST_FAILED : indices are out of bounds
    \retval RET_NOERROR : Array copied
*/
/******************************************************************************/
template <class T> Retval TArrayList<T>::copyToArray(T* pBuffer,
                                                     Int iBufferSize,
                                                     Int& rCopiedSize,
                                                     Int iStart /*= 0*/,
                                                     Int iEnd /*= INVALID_INDEX*/) const
{
  Retval retVal = RET_INVALID_PARAMETER;
  if (iEnd == INVALID_INDEX)
  {
    iEnd = m_iCounter -1;
  }

  if (iStart <= iEnd)
  {
    Int iArraySize = iEnd - iStart + 1;
    if (iStart < 0 ||
        iEnd >= m_iCounter ||
        iArraySize > iBufferSize)
    {
      retVal = RET_REQUEST_FAILED;
    }
    else
    {
      //copy the array
      switch(m_eCopyMode)
      {
        case etShallowCopy:
          ::memcpy(pBuffer, &(m_pDataArray[iStart]), sizeof(T)*iArraySize);
        break;

        case etDeepCopy :  //fall though
        default:
          for(Int i = 0; i < iArraySize; ++i)
          {
            pBuffer[i] = m_pDataArray[i + iStart];
          }
        break;
      }

      rCopiedSize = iArraySize;
      retVal = RET_NOERROR;
    }
  }
  return retVal;
}


/******************************************************************************/
/*! \see IArray::getCopyMode
*/
/******************************************************************************/
template <class T> EArrayCopyMode MQUALIFIER TArrayList<T>::getCopyMode() const
{
  return m_eCopyMode;
}


/******************************************************************************/
/*!  Resizes the array
     \param iNewSize : New size of the array list
*/
/******************************************************************************/
template <class T> void TArrayList<T>::resize(Int iNewSize)
{
  assert(m_pDataArray != NULL);

  m_iSize = iNewSize;
  T* pNewArray = new T[m_iSize];
  for(int i = 0; i < m_iCounter; i++)
  {
    pNewArray[i] = m_pDataArray[i];
  }
  delete [] m_pDataArray;
  m_pDataArray = pNewArray;
}


/******************************************************************************/
/*! \see IList::add
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TArrayList<T>::add(const T& rItem)
{

  //Vergroessern des Arrays
  if (m_iCounter >= m_iSize)
  {
    resize((Int)(m_iSize*1.5));
  }

  m_pDataArray[m_iCounter] = rItem;
  m_iCounter++;

  return m_iCounter-1;
}

/******************************************************************************/
/*! \see IList::addAll
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TArrayList<T>::addAll(const IList<T>& rlstItems)
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
template <class T> Int MQUALIFIER TArrayList<T>::addEmptyItem()
{
  return this->add(m_tEmpty);
}

/******************************************************************************/
/*! \see IList::copyToList
*/
/******************************************************************************/
template <class T> void MQUALIFIER TArrayList<T>::copyToList(IList<T>& rList) const
{
  rList.clear();

  Int iCounter = 0;
  while (iCounter < m_iCounter)
  {
    rList.add(m_pDataArray[iCounter]);
    iCounter++;
  }
}


/******************************************************************************/
/*! \see IList::clear
*/
/******************************************************************************/
template <class T> void MQUALIFIER TArrayList<T>::clear()
{
  if (m_pDataArray != NULL)
  {
    delete [] m_pDataArray;
  }
  m_pDataArray = new T[m_iOrigSize];
  m_iSize = m_iOrigSize;

  //Zuruecksetzen der Liste
  m_iCounter = 0;

  //Reseten aller Iteratoren
  TArrayListIterator* pIt = m_pIterator;
  while (pIt != NULL)
  {
    pIt->reset();
    pIt = pIt->getNextIterator();
  }
}


/******************************************************************************/
/*! \see IList::deleteItem
*/
/******************************************************************************/
template <class T> Retval MQUALIFIER TArrayList<T>::deleteItem(Int iIndex)
{
  Retval retVal = RET_REQUEST_FAILED;

  if (iIndex >= 0 && iIndex < m_iCounter)
  {
    for(int i = iIndex; i < m_iCounter-1; i++)
    {
      m_pDataArray[i] = m_pDataArray[i+1];
    }
    m_iCounter--;

    //Anpassen aller Iteratoren die den aktuellen Index bereits ueberstiegen
    //haben
    TArrayListIterator* it = m_pIterator;
    while (it != NULL)
    {
      //Alle Iteratoren welche das aktuelle Element groesser als Index haben
      if (it->getActElement() > iIndex)
      {
        it->setActElement(it->getActElement()-1);
      }
      it = it->getNextIterator();
    }
    retVal = RET_NOERROR;
  }
  return retVal;
}


/******************************************************************************/
/*! \see IList::indexOf
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TArrayList<T>::indexOf(const T& rItem) const
{
  Int iCounter = 0;
  while (iCounter < m_iCounter)
  {
    if (m_pDataArray[iCounter] == rItem)
    {
      return iCounter;
    }
    iCounter++;
  }
  return INVALID_INDEX;
}

/******************************************************************************/
/*! \see IList::insert
*/
/******************************************************************************/
template <class T> Int MQUALIFIER TArrayList<T>::insert(Int iIndex, const T& rItem)
{
  Int iRetval = INVALID_INDEX;

  if (iIndex >= 0)
  {

    //Vergroessern des Arrays
    if (m_iCounter >= m_iSize)
    {
      resize((Int)(m_iSize*1.5));
    }

    //Anfuegen eines Items
    if (iIndex == m_iCounter)
    {
      m_pDataArray[m_iCounter] = rItem;
      m_iCounter++;
      iRetval = m_iCounter-1;
    }

    //Einfuegen
    else if (iIndex < m_iCounter)
    {
      for(int i = m_iCounter-1; i >= iIndex; i--)
      {
        m_pDataArray[i+1] = m_pDataArray[i];
      }
      m_pDataArray[iIndex] = rItem;
      m_iCounter++;
      iRetval = iIndex;
    }

    //Anpassen aller Iteratoren die den aktuellen Index bereits ueberstiegen
    //haben
    TArrayListIterator* it = m_pIterator;
    while (it != NULL)
    {
      //Alle Iteratoren welche das aktuelle Element groesser als Index haben
      if (it->getActElement() >= iIndex)
      {
        it->setActElement(it->getActElement()+1);
      }
      it = it->getNextIterator();
    }
  }
  return iRetval;
}


/******************************************************************************/
/*! \see IList::remove
*/
/******************************************************************************/
template <class T> Retval MQUALIFIER TArrayList<T>::remove(const T& rItem)
{
  return deleteItem(indexOf(rItem));
}

/***************************************************************************/
/*! \see IList::removeAll
*/
/***************************************************************************/
template <class T> Retval MQUALIFIER TArrayList<T>::removeAll(const IList<T>& rlstItems)
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
template <class T> Int MQUALIFIER TArrayList<T>::getCount() const
{
  return  m_iCounter;
}

/******************************************************************************/
/*! \see IList::getItem
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TArrayList<T>::getItem(Int iIndex)
{
  if (iIndex >= 0 && iIndex < m_iCounter)
  {
    return m_pDataArray[iIndex];
  }
  else
  {
    return m_tEmpty;
  }
}

/***************************************************************************/
/*! \see IList::getItemConst
*/
/***************************************************************************/
template <class T> const T& MQUALIFIER TArrayList<T>::getItemConst(Int iIndex) const
{
  if (iIndex >= 0 && iIndex < m_iCounter)
  {
    return m_pDataArray[iIndex];
  }
  else
  {
    return m_tEmpty;
  }
}


/******************************************************************************/
/*! \see IList::equalsItem
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TArrayList<T>::equalsItem(Int iIndex, const T& rItem) const
{
  return (iIndex >= 0 && iIndex < m_iCounter && getItemConst(iIndex) == rItem);
}

/******************************************************************************/
/*! \see IList::equals
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TArrayList<T>::equals(const IList<T>& rList) const
{
  bool bRetval = (rList.getCount() == m_iCounter);

  if (bRetval)
  {
    for (int i = 0; i < m_iCounter && bRetval; ++i)
    {
      bRetval &= rList.equalsItem(i, m_pDataArray[i]);
    }
  }

  return bRetval;
}


/******************************************************************************/
/*! \see IList::getIterator
*/
/******************************************************************************/
template <class T> IListIterator<T>* MQUALIFIER TArrayList<T>::getIterator() const
{
  TArrayListIterator* pIterator = new TArrayListIterator(*this);
  pIterator->setNextIterator(m_pIterator);
  m_pIterator = pIterator;
  return m_pIterator;
}

/******************************************************************************/
/*! \see IList::getConstIterator
*/
/******************************************************************************/
template <class T> const IListIterator<T>* MQUALIFIER TArrayList<T>::getConstIterator() const
{
  TArrayListIterator* pIterator = new TArrayListIterator(*this);
  pIterator->setNextIterator(m_pIterator);
  m_pIterator = pIterator;
  return m_pIterator;
}


/******************************************************************************/
/*! \see IList::releaseIterator
*/
/******************************************************************************/
template <class T> void MQUALIFIER TArrayList<T>::releaseIterator(const IListIterator<T>* pIterator) const
{
  TArrayListIterator* pIt = m_pIterator;
  TArrayListIterator* pItPrev = NULL;
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
template <class T> bool MQUALIFIER TArrayList<T>::isEmpty() const
{
  return (m_iCounter == 0);
}

/******************************************************************************/
/*! \see IList::getFirstItem
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TArrayList<T>::getFirstItem()
{
  return this->getItem(0);
}

/******************************************************************************/
/*! \see IList::getFirstItemConst
*/
/******************************************************************************/
template <class T> const T& MQUALIFIER TArrayList<T>::getFirstItemConst() const
{
  return this->getItemConst(0);
}

/******************************************************************************/
/*! \see IList::getLastItem
*/
/******************************************************************************/
template <class T> T& MQUALIFIER TArrayList<T>::getLastItem()
{
  return this->getItem(m_iCounter-1);
}

/******************************************************************************/
/*! \see IList::getLastItemConst
*/
/******************************************************************************/
template <class T> const T& MQUALIFIER TArrayList<T>::getLastItemConst() const
{
  return this->getItemConst(m_iCounter-1);
}

/******************************************************************************/
/*! \see IList::hasItem
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TArrayList<T>::hasItem(const T& rItem) const
{
  return (this->indexOf(rItem) != INVALID_INDEX);
}

/******************************************************************************/
/*! \see IList::hasAllItems
*/
/******************************************************************************/
template <class T> bool MQUALIFIER TArrayList<T>::hasAllItems(const IList<T>& rlstItems) const
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
/*! Operator to index an item of the array
    \param iIndex : Index of the requested item
    \return returns the item at index
*/
/******************************************************************************/
template <class T> T& TArrayList<T>::operator[](Int iIndex)
{
  return getItem(iIndex);
}

/******************************************************************************/
/*! operator copies a list into this list object
    \param rList : source
    \return this list (target)
*/
/******************************************************************************/
template <class T> TArrayList<T>& TArrayList<T>::operator= (const TArrayList<T>& rList)
{
  rList.copyToArray(*this, 0, rList.getCount()-1);
  return *this;
}

/******************************************************************************/
/*! operator copies a list into this list object
    \param pList : source
    \return this list (target)
*/
/******************************************************************************/
template <class T> TArrayList<T>& TArrayList<T>::operator= (const TArrayList<T>* pList)
{
  if (pList != NULL)
  {
    pList->copyToArray(*this, 0, pList->getCount()-1);
  }
  return *this;
}

/******************************************************************************/
/*! operator copies a list into this list object
    \param rList : source
    \return this list (target)
*/
/******************************************************************************/
template <class T> TArrayList<T>& TArrayList<T>::operator= (const IList<T>& rList)
{
  rList.copyToList(*this);
  return *this;
}

/******************************************************************************/
/*! operator copies a list into this list object
    \param pList : source
    \return this list (target)
*/
/******************************************************************************/
template <class T> TArrayList<T>& TArrayList<T>::operator= (const IList<T>* pList)
{
  if (pList != NULL)
  {
    pList->copyToList(*this);
  }
  return *this;
}


/******************************************************************************/
/*! Operator to check equality of two lists
    \param rList : list to check
    \retval true : Equal
    \retval false : not equal
*/
/******************************************************************************/
template <class T> bool  TArrayList<T>::operator==(const TArrayList<T>& rList) const
{
  return this->equals(rList);
}

/******************************************************************************/
/*! Checks if two list are not equal
    \param rList : list to check
*/
/******************************************************************************/
template <class T> bool  TArrayList<T>::operator!=(const TArrayList<T>& rList) const
{
  return !this->equals(rList);
}

/***************************************************************************/
/*! Returns the empty data element
*/
/***************************************************************************/
template <class T> T& TArrayList<T>::getEmptyItem()
{
  return m_tEmpty;
}

END_NAMESPACE_Zeus

#endif

