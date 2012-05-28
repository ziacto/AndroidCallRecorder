/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : String
 * Package : SystemTokenizer
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 26.02.07 9:00 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/StringTokenizer.h $
** 
** 16    26.02.07 9:00 bha
**
** 7     30.10.06 11:36 Mabbuehl
** Constuctor overloaded in order to pass const wchar_t* as delimiter.
**
** 4     22.09.06 11:00 Mabbuehl
** getToken(Int iTokenIndex) eingefügt.
***************************************************************************/

#ifndef SystemTokenizerH
#define SystemTokenizerH

#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/StringList.h>

BEGIN_NAMESPACE_Zeus


/**************************************************************************/
/*! This class implements a tokenizer for strings                         */
/**************************************************************************/
zeusbase_class TStringTokenizer : public TZObject
{
  public:
    TStringTokenizer(const IString& rData, const IString& rDelimiter  , bool bRemoveEmptyTokens = false);
    TStringTokenizer(const IString& rData, const wchar_t* pwcDelimiter, bool bRemoveEmptyTokens = false);

    virtual ~TStringTokenizer();

    TString getNextToken() const;
    TString getToken(Int iTokenIndex) const;
    TString getFirstToken() const;
    TString getLastToken() const;
    void getTokens(IStringList& rList) const;
    Int getTokenCount() const;
    bool hasNextToken() const;
    void removeEmptyTokens();
    void resetIterator();
    void setTokens(const IStringList& rList);
    TString toString() const;
    TString toString(TString strNewDelimiter) const;
    Retval removeTokens(Int iFirstIndex, Int iLastIndex);
    Retval removeToken(Int uiIndex);
    Retval removeFirstToken();
    Retval removeLastToken();

    Retval getTokenIndex(const IString& strToken, Int& iIndex, bool bExactNotLike = true);

  private:
    void constructorInit(const IString& rData, const IString& rDelimiter, bool bRemoveEmptyTokens);

    void tokenize(const IString& rData);
    TString toString_internal(const IString& rDelimiter) const;

  private:
    ///list of all tokens
    TStringList m_lstTokens;

    ///List iterator
    const IStringListIterator* m_pListIterator;

    ///Delimiter
    TString m_strDelimiter;
};

//inline methods
/**************************************************************************/
/*! returns the next token
*/
/**************************************************************************/
inline TString TStringTokenizer::getNextToken() const
{
  return m_pListIterator->getNextItem();
}


/**************************************************************************/
/*! returns a token by index.                                             */
/**************************************************************************/
inline TString TStringTokenizer::getToken(Int iTokenIndex) const
{
  TString strReturn;

  if (iTokenIndex < getTokenCount())
  {
    strReturn = m_lstTokens.getItemConst(iTokenIndex);
  } // ulTokenIndex < getTokenCount().

  return strReturn;
}


/**************************************************************************/
/*! returns the number of the tokens
*/
/**************************************************************************/
inline Int TStringTokenizer::getTokenCount() const
{
  return m_lstTokens.getCount();
}

/**************************************************************************/
/*! checks if there are more tokens
*/
/**************************************************************************/
inline bool TStringTokenizer::hasNextToken() const
{
  return m_pListIterator->hasNextItem();
}

/**************************************************************************/
/*! resets the token iterator
*/
/**************************************************************************/
inline void TStringTokenizer::resetIterator()
{
  m_pListIterator->reset();
}

/**************************************************************************/
/*! This method returns the string builded from the tockens
    \return build string out of tokens
*/
/**************************************************************************/
inline TString TStringTokenizer::toString() const
{
  return toString_internal(m_strDelimiter);
}

/**************************************************************************/
/*! This method returns the string builded from the tockens and a delimiter
    \return build string out of tokens
*/
/**************************************************************************/
inline TString TStringTokenizer::toString(TString strNewDelimiter) const
{
  return toString_internal(strNewDelimiter);
}

END_NAMESPACE_Zeus

#endif

