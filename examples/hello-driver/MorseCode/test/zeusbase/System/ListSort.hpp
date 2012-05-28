/***************************************************************************
 * Copyright (C) 2008 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ListSort
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date$
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
 $Log$
***************************************************************************/

#ifndef ListSortHPP
#define ListSortHPP

#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/ArrayList.hpp>
#include <zeusbase/System/SingleLinkedList.hpp>


BEGIN_NAMESPACE_Zeus

/****************************************************************************/
/*! This class is used to sort single linked lists and array lists
*/
/****************************************************************************/
template <class T> class TListSort : public TZObject
{
  public:
    static void sort(TSingleLinkedList<T>& rList);
    static void sort(TArrayList<T>& rList);
    static Int insertSorted(TSingleLinkedList<T>& rList, const T& rItem);
    static Int insertSorted(TArrayList<T>& rList, const T& rItem);

  protected:
    inline TListSort() {}
    inline virtual ~TListSort() {}

};

/****************************************************************************/
/*! sorts a single linked list
*/
/****************************************************************************/
/*static*/ template <class T> void TListSort<T>::sort(TSingleLinkedList<T>& rList)
{
  bool bChanged = true;

  while(bChanged)
  {
    bChanged = false;

    typename TSingleLinkedList<T>::TSingleLinkedListElement* pElement1 = rList.getHeadElement();
    while(pElement1 != NULL)
    {
      typename TSingleLinkedList<T>::TSingleLinkedListElement* pElement2 = pElement1->pNext;

      if (pElement2 != NULL)
      {
        //Swap elements
        if (pElement1->tData > pElement2->tData)
        {
          T tTemp = pElement1->tData;
          pElement1->tData = pElement2->tData;
          pElement2->tData = tTemp;
          bChanged = true;
        }

        pElement1 = pElement2;
      }
      else
      {
        pElement1 = NULL;
      }
    }
  }
}

/****************************************************************************/
/*! sorts an array list
*/
/****************************************************************************/
/*static*/ template <class T> void TListSort<T>::sort(TArrayList<T>& rList)
{
  bool bChanged = true;
  Int iCount = rList.getCount();

  while(bChanged)
  {
    bChanged = false;
    Int iIndex1 = 0;
    Int iIndex2 = 1;
    while(iIndex1 < iCount && iIndex2 < iCount)
    {
      if (rList[iIndex1] > rList[iIndex2])
      {
        T tTemp = rList[iIndex1];
        rList[iIndex1] = rList[iIndex2];
        rList[iIndex2] = tTemp;
        bChanged = true;
      }
      iIndex1++;
      iIndex2++;
    }
  }
}

/****************************************************************************/
/*! inserts an item into a list regarding the sorting
*/
/****************************************************************************/
/*static*/ template <class T> Int TListSort<T>::insertSorted(TSingleLinkedList<T>& rList, const T& rItem)
{
  Int iInsertPos = -1;
  TIterator<T> It = rList.getIterator();
  bool bAdded = false;
  while(!bAdded && It.hasNextItem())
  {
    iInsertPos++;
    if (rItem < It.getNextItem())
    {
      bAdded = true;
      iInsertPos = rList.insert(iInsertPos, rItem);
    }
  }

  if (!bAdded)
  {
    iInsertPos = rList.add(rItem);
  }

  return iInsertPos;
}

/****************************************************************************/
/*! inserts an item into a list regarding the sorting
*/
/****************************************************************************/
/*static*/ template <class T> Int TListSort<T>::insertSorted(TArrayList<T>& rList, const T& rItem)
{
  Int iInsertPos = -1;
  Int iCount = rList.getCount();

  bool bAdded = false;
  while(!bAdded && iInsertPos < iCount)
  {
    iInsertPos++;
    if (rItem < rList[iInsertPos])
    {
      bAdded = true;
      iInsertPos = rList.insert(iInsertPos, rItem);
    }
  }

  if (!bAdded)
  {
    iInsertPos = rList.add(rItem);
  }

  return iInsertPos;
}


END_NAMESPACE_Zeus


#endif
