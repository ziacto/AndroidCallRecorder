/***************************************************************************
 * Copyright (C) 2008 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : StringList
 * Package : system
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/StringList.h $
** 
** 17    27.05.08 7:44 Bha
** handing multible items on lists
** 
** 16    7.01.08 9:00 Bha
** Is not an ZObject anymore
** 
** 15    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 14    11.07.07 17:36 bha
** New methods getting first and last items
** 
** 13    26.02.07 9:00 bha
**
** 9     5.10.06 6:38 bha
** Stack types can hide addRef and release methods inside their interfaces
***************************************************************************/


#ifndef StringListH
#define StringListH

#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/SingleLinkedList.hpp>
#include <zeusbase/System/Interfaces/IStringList.hpp>


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This class implements a string based list.
*/
/***************************************************************************/
zeusbase_class TStringList : public IStringList
{
  public:
    TStringList();
    virtual ~TStringList();

    //Methods of IStringList
    virtual Int MQUALIFIER add(const IString& rItem);
    virtual Int MQUALIFIER addAll(const IStringList& rlstItems);
    virtual Int MQUALIFIER addEmptyItem();
    virtual void MQUALIFIER copyToList(IStringList& rList) const;
    virtual void MQUALIFIER clear();
    virtual Retval MQUALIFIER deleteItem(Int iIndex);
    virtual Retval MQUALIFIER remove(const IString& rItem);
    virtual Retval MQUALIFIER removeAll(const IStringList& rlstItems);
    virtual Int MQUALIFIER getCount()const;
    virtual IString& MQUALIFIER getItem(Int iIndex);
    virtual const IString& MQUALIFIER getItemConst(Int iIndex) const;
    virtual bool MQUALIFIER equalsItem(Int iIndex, const IString& rItem) const;
    virtual bool MQUALIFIER equals(const IStringList& rList) const;
    virtual Int MQUALIFIER indexOf(const IString& rItem) const;
    virtual Int MQUALIFIER insert(Int iIndex, const IString& rItem);
    virtual IStringListIterator* MQUALIFIER getIterator() const;
    virtual const IStringListIterator* MQUALIFIER getConstIterator() const;
    virtual void MQUALIFIER releaseIterator(const IStringListIterator* pIterator) const;
    virtual bool MQUALIFIER isEmpty() const;
    virtual IString& MQUALIFIER getFirstItem();
    virtual const IString& MQUALIFIER getFirstItemConst() const;
    virtual IString& MQUALIFIER getLastItem();
    virtual const IString& MQUALIFIER getLastItemConst() const;
    virtual bool MQUALIFIER hasItem(const IString& rItem) const;
    virtual bool MQUALIFIER hasAllItems(const IStringList& rlstItems) const;

    //Additional methods for easy accessing the list
    Int add(TString strItem);
    Retval remove(TString strItem);
    bool equalsItem(Int iIndex, TString strItem) const;
    Int indexOf(TString strItem) const;

    //Operators
    IString& operator[] (Int iIndex);
    TStringList& operator = (const TStringList& rList);
    bool operator == (const TStringList& rList);

  private:
    ///List of strings
    TSingleLinkedList<TString> m_lstStrings;

};


//Inline methods
/***************************************************************************/
/*! \see IList::add
*/
/***************************************************************************/
inline Int MQUALIFIER TStringList::add(const IString& rItem)
{
  return m_lstStrings.add(TString(rItem));
}

/******************************************************************************/
/*! \see IList::add
*/
/******************************************************************************/
inline Int TStringList::add(TString strItem)
{
  return m_lstStrings.add(strItem);
}

/******************************************************************************/
/*! \see IList::addEmptyItem
*/
/******************************************************************************/
inline Int MQUALIFIER TStringList::addEmptyItem()
{
  return m_lstStrings.addEmptyItem();
}

/***************************************************************************/
/*! \see IList::clear
*/
/***************************************************************************/
inline void MQUALIFIER TStringList::clear()
{
  m_lstStrings.clear();
}

/***************************************************************************/
/*! \see IList::deleteItem
*/
/***************************************************************************/
inline Retval MQUALIFIER TStringList::deleteItem(Int iIndex)
{
  return m_lstStrings.deleteItem(iIndex);
}

/***************************************************************************/
/*! \see IList::remove
*/
/***************************************************************************/
inline Retval MQUALIFIER TStringList::remove(const IString& rItem)
{
  return deleteItem(indexOf(rItem));
}

/******************************************************************************/
/*! \see IList::remove
*/
/******************************************************************************/
inline Retval TStringList::remove(TString strItem)
{
  return deleteItem(indexOf(strItem));
}

/***************************************************************************/
/*! \see IList::getCount
*/
/***************************************************************************/
inline Int MQUALIFIER TStringList::getCount() const
{
  return m_lstStrings.getCount();
}

/***************************************************************************/
/*! \see IList::getItem
*/
/***************************************************************************/
inline IString& MQUALIFIER TStringList::getItem(Int iIndex)
{
  return m_lstStrings.getItem(iIndex);
}

/***************************************************************************/
/*! \see IList::getItemConst
*/
/***************************************************************************/
inline const IString& MQUALIFIER TStringList::getItemConst(Int iIndex) const
{
  return m_lstStrings.getItemConst(iIndex);
}

/***************************************************************************/
/*! \see IList::equalsItem
*/
/***************************************************************************/
inline bool MQUALIFIER TStringList::equalsItem(Int iIndex, const IString& rItem) const
{
  return getItemConst(iIndex).equalsStr(rItem);
}

/******************************************************************************/
/*! \see IList::equalsItem
*/
/******************************************************************************/
inline bool TStringList::equalsItem(Int iIndex, TString strItem) const
{
  return getItemConst(iIndex).equalsStr(strItem);
}

/***************************************************************************/
/*! \see IList::insert
*/
/***************************************************************************/
inline Int MQUALIFIER TStringList::insert(Int iIndex, const IString& rItem)
{
  return m_lstStrings.insert(iIndex, rItem);
}

/******************************************************************************/
/*! \see IList::indexOf
*/
/******************************************************************************/
inline Int TStringList::indexOf(TString strItem) const
{
  return indexOf((IString&)strItem);
}

/******************************************************************************/
/*!  \see IList::isEmpty
*/
/******************************************************************************/
inline bool MQUALIFIER TStringList::isEmpty() const
{
  return m_lstStrings.isEmpty();
}

/******************************************************************************/
/*! \see IList::getFirstItem
*/
/******************************************************************************/
inline IString& MQUALIFIER TStringList::getFirstItem()
{
  return this->getItem(0);
}

/******************************************************************************/
/*! \see IList::getFirstItemConst
*/
/******************************************************************************/
inline const IString& MQUALIFIER TStringList::getFirstItemConst() const
{
  return this->getItemConst(0);
}

/******************************************************************************/
/*! \see IList::getLastItem
*/
/******************************************************************************/
inline IString& MQUALIFIER TStringList::getLastItem()
{
  return this->getItem(m_lstStrings.getCount()-1);
}

/******************************************************************************/
/*! \see IList::getLastItemConst
*/
/******************************************************************************/
inline const IString& MQUALIFIER TStringList::getLastItemConst() const
{
  return this->getItemConst(m_lstStrings.getCount()-1);
}

/******************************************************************************/
/*! \see IList::hasItem
*/
/******************************************************************************/
inline bool MQUALIFIER TStringList::hasItem(const IString& rItem) const
{
  return m_lstStrings.hasItem(TString(rItem));
}


/******************************************************************************/
/*! Operator zur fr das einfache Zugreifen auf den Elementinhalt
    \param iIndex : Index auf ein Element der Liste
    \return gibt den Dateninhalt eines Elements der Liste zurck
*/
/******************************************************************************/
inline IString& TStringList::operator[](Int iIndex)
{
  return getItem(iIndex);
}

END_NAMESPACE_Zeus

#endif
