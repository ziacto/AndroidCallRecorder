/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : StringList
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/StringList.cpp $
** 
** 11    27.05.08 7:44 Bha
** handing multible items on lists
** 
** 10    7.01.08 9:00 Bha
** Is not an ZObject anymore
** 
** 9     20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
** 
** 6     9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
** 
** 5     18.09.06 12:40 Mabbuehl
** Bereinigung von Borland-Release-Warnungen, wo es möglich und
** effizienter ist.
***************************************************************************/

#include <zeusbase/System/StringList.h> 

USING_NAMESPACE_Zeus

/***************************************************************************/
/*! Creates a new StringList object
*/
/***************************************************************************/
TStringList::TStringList()
{}

/***************************************************************************/
/*! Destroys the StringList object
*/
/***************************************************************************/
TStringList::~TStringList()
{
  clear();
}

/***************************************************************************/
/*! \see IList::addAll
*/
/***************************************************************************/
Int MQUALIFIER TStringList::addAll(const IStringList& rlstItems)
{
  TConstIterator<IString> It = rlstItems.getConstIterator();
  while(It.hasNextItem())
  {
    this->add(It.getNextItemConst());
  }

  return m_lstStrings.getCount()-1;
}

/***************************************************************************/
/*! \see IList::copyToList
*/
/***************************************************************************/
void MQUALIFIER TStringList::copyToList(IStringList& rList) const
{
  rList.clear();
  Int iCount = m_lstStrings.getCount();
  for(Int i = 0; i < iCount; i++)
  {
    rList.add(m_lstStrings.getItemConst(i));
  }
}

/***************************************************************************/
/*! \see IList::removeAll
*/
/***************************************************************************/
Retval MQUALIFIER TStringList::removeAll(const IStringList& rlstItems)
{
  Retval retValue = RET_REQUEST_FAILED;
  bool bOK = false;
  TConstIterator<IString> It = rlstItems.getConstIterator();
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

/***************************************************************************/
/*! \see IList::rItem
*/
/***************************************************************************/
Int MQUALIFIER TStringList::indexOf(const IString& rItem) const
{
  Int iCount = this->getCount();
  Int iIndex = INVALID_INDEX;
  
  for(Int i = 0; i < iCount; i++)
  {
    if (m_lstStrings.getItemConst(i).equalsStr(rItem))
    {
      iIndex = i;
      break;
    }
  }
  return iIndex;
}

/***************************************************************************/
/*! \see IList::equals
*/
/***************************************************************************/
bool MQUALIFIER TStringList::equals(const IStringList& rList) const
{
  Int iCount = getCount();
  bool bRetval = (iCount == rList.getCount());

  if (bRetval)
  {
    for(Int i = 0; i < iCount && bRetval; i++)
    {
      bRetval &= (this->getItemConst(i).equalsStr(rList.getItemConst(i)));
    }
  }
  return bRetval;
}

/***************************************************************************/
/*! \see IList::getIterator
*/
/***************************************************************************/
IStringListIterator* MQUALIFIER TStringList::getIterator() const
{
  return (IStringListIterator*)m_lstStrings.getIterator();
}

/***************************************************************************/
/*! \see IList::getConstIterator
*/
/***************************************************************************/
const IStringListIterator* MQUALIFIER TStringList::getConstIterator() const
{
  return (const IStringListIterator*)m_lstStrings.getConstIterator();
}

/***************************************************************************/
/*! \see IList::releaseIterator
*/
/***************************************************************************/
void MQUALIFIER TStringList::releaseIterator(const IStringListIterator* pIterator) const
{
  m_lstStrings.releaseIterator((IListIterator<TString>*)pIterator);
}

/***************************************************************************/
/*! \see IList::hasAllItems
*/
/***************************************************************************/
bool MQUALIFIER TStringList::hasAllItems(const IStringList& rlstItems) const
{
  bool bRetval = true;
  TConstIterator<IString> It = rlstItems.getConstIterator();
  while(bRetval && It.hasNextItem())
  {
    bRetval &= this->hasItem(It.getNextItemConst());
  }

  return bRetval;
}

/******************************************************************************/
/*! Operator zum kopieren einer Liste
    \param list : Ausgangsliste
    \return neu kopierte Liste
*/
/******************************************************************************/
TStringList& TStringList::operator=(const TStringList& rList)
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
bool TStringList::operator==(const TStringList& rList)
{
  return this->equals(rList);
}

 
