/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : String
 * Package : SystemTokenizer
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 20.02.07 10:18 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/StringTokenizer.cpp $
** 
** 17    20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
** 
** 13    13.11.06 16:51 Mabbuehl
** 
** 8     30.10.06 11:36 Mabbuehl
** Constuctor overloaded in order to pass const wchar_t* as delimiter.
** 
** 4     18.09.06 12:40 Mabbuehl
** Bereinigung von Borland-Release-Warnungen, wo es möglich und
** effizienter ist.
***************************************************************************/

#include <zeusbase/System/StringTokenizer.h>

USING_NAMESPACE_Zeus


/**************************************************************************/
/*! Creates a new tokenizer.

    \param rData             : Data to tokenize
    \param rDelimiter        : delimiter
    \param bRemoveEmptyTokens: Remove all empty token if this flag is set */
/**************************************************************************/
TStringTokenizer::TStringTokenizer(const IString& rData, const IString& rDelimiter,
                                   bool bRemoveEmptyTokens /* = false */)
{
  constructorInit(rData, rDelimiter, bRemoveEmptyTokens);
}


/**************************************************************************/
/*! Creates a new tokenizer.

    \param rData             : Data to tokenize
    \param pwcDelimiter      : delimiter
    \param bRemoveEmptyTokens: Remove all empty token if this flag is set */
/**************************************************************************/
TStringTokenizer::TStringTokenizer(const IString& rData, const wchar_t* pwcDelimiter,
                                   bool bRemoveEmptyTokens /* = false */)
{
  constructorInit(rData, TString(pwcDelimiter), bRemoveEmptyTokens);
}


/**************************************************************************/
/*! Method to encapsulate alls constructor initializations.

    \param rData             : Data to tokenize
    \param rDelimiter        : delimiter
    \param bRemoveEmptyTokens: Remove all empty token if this flag is set */
/**************************************************************************/
void TStringTokenizer::constructorInit(const IString& rData, const IString& rDelimiter,
                                       bool bRemoveEmptyTokens)
{
  m_pListIterator = m_lstTokens.getIterator();
  m_strDelimiter  = rDelimiter;
  tokenize(rData);
  
  if (bRemoveEmptyTokens)
  {
    removeEmptyTokens();
  } // bRemoveEmptyTokens.
}

    
/**************************************************************************/
/*! Destroys the tokenizer
*/
/**************************************************************************/
TStringTokenizer::~TStringTokenizer()
{
  m_lstTokens.releaseIterator(m_pListIterator);
  m_pListIterator = NULL;
}


/**************************************************************************/
/*! Remove all empty token
*/
/**************************************************************************/
void TStringTokenizer::removeEmptyTokens()
{
  Int iIndex = 0;
  IStringListIterator* pIt = m_lstTokens.getIterator();
  while(pIt->hasNextItem())
  {
    if (pIt->getNextItem().isEmpty())
    {
      m_lstTokens.deleteItem(iIndex);
    }
    else //if deleteitem has been performed -> do not increase lIndex
    {
      iIndex++;
    }
  }
  m_lstTokens.releaseIterator(pIt);
}

/**************************************************************************/
/*! internal method to tokenize the data
    \param rData : Data to tokenize
*/
/**************************************************************************/
void TStringTokenizer::tokenize(const IString& rData)
{
  TString strData(rData);
  Int iIndex = 0; // Causes unavoidable warning W8004 when compiling Borland release.

  //-----------------------------------------------------------------------
  // This code is easier to read, but does more reallocations of memory
  do
  {
    iIndex = strData.getFirstPosStr(m_strDelimiter);

    if (iIndex >= 0)
    {
      m_lstTokens.add(strData.getSubString(0, iIndex-1));

      //reallocation
      strData = strData.deleteSubString(0, iIndex+m_strDelimiter.getSize()-1);
    }
    else
    {
      m_lstTokens.add(strData);
    }
  } while(iIndex >= 0);
}

/**************************************************************************/
/*! Returns a list of tokens. The list is a copy of the internal
    token list. Use set tokens to set a new token list
    \param rList : Return parameter
*/
/**************************************************************************/
void TStringTokenizer::getTokens(IStringList& rList) const
{
  m_lstTokens.copyToList(rList);
}


/**************************************************************************/
/*! internal method to build a string out of tokens and a delimiter
*/
/**************************************************************************/
TString TStringTokenizer::toString_internal(const IString& rDelimiter) const
{
  TString strRetval;
  const IStringListIterator* pIt = m_lstTokens.getConstIterator();

  while(pIt->hasNextItem())
  {
    strRetval += pIt->getNextItem();
    if (pIt->hasNextItem())
    {
      strRetval += rDelimiter;
    }
  }
  m_lstTokens.releaseIterator(pIt);

  return strRetval;
}

/**************************************************************************/
/*! sets tokens to the internal token list
    \param rList : New tokens
*/
/**************************************************************************/
void TStringTokenizer::setTokens(const IStringList& rList)
{
  rList.copyToList(m_lstTokens);
}


/**************************************************************************/
/*! Remove tokens given by a range of indexes.

    \param iFirstIndex [IN]: First index of this range.
    \param iLastIndex  [IN]: Last  index of this range.

    \retval                 : Error code.                                 */
/**************************************************************************/
Retval TStringTokenizer::removeTokens(Int iFirstIndex, Int iLastIndex)
{
  Retval retVal = RET_INVALID_PARAMETER;

  if (iFirstIndex <= iLastIndex    &&
      iFirstIndex < getTokenCount() &&
      iLastIndex  < getTokenCount())
  {
    retVal = RET_NOERROR;

    Int iCount = iLastIndex - iFirstIndex + 1;

    for (Int iRemoved = 0; iRemoved < iCount; ++iRemoved)
    {
      m_lstTokens.deleteItem(iFirstIndex);
    } // Loop over uiCount items to be deleted.
  } // Parameters are valid.
  
  return retVal;
}


/**************************************************************************/
/*! Remove a token given by index.

    \param iIndex [IN]: Index of the token to be removed.

    \retval            : Error code.                                      */
/**************************************************************************/
Retval TStringTokenizer::removeToken(Int iIndex)
{
  Retval retVal = RET_INVALID_PARAMETER;

  if (iIndex < getTokenCount())
  {
    retVal = m_lstTokens.deleteItem(iIndex);
  } // uiIndex < getTokenCount().
  
  return retVal;
}


/**************************************************************************/
/*! Remove the first token.

    \retval: Error code.                                                  */
/**************************************************************************/
Retval TStringTokenizer::removeFirstToken()
{
  return removeToken(0);
}


/**************************************************************************/
/*! Remove the last token.

    \retval: Error code.                                                  */
/**************************************************************************/
Retval TStringTokenizer::removeLastToken()
{
  return removeToken(getTokenCount() - 1);
}


/**************************************************************************/
/*! Get the first token.                                                  */
/**************************************************************************/
TString TStringTokenizer::getFirstToken() const
{
  return getToken(0);
}


/**************************************************************************/
/*! Get the last token.                                                  */
/**************************************************************************/
TString TStringTokenizer::getLastToken() const
{
  return getToken(getTokenCount() - 1);
}


/**************************************************************************/
/*! Get the index of a given token.

    \param strToken      [IN] : The token to be searched for.
    \param uiIndex       [OUT]: Index of the first appearance of strToken.

    \param bExactNotLike [IN] : true:  strToken has to match one of the
                                       tokens stored in this tokenizer.

                                false: strToken only has to be contained at
                                       the beginning of one of the tokens of
                                       this tokenizer.

    \retval                   : Error code.                               */
/**************************************************************************/
Retval TStringTokenizer::getTokenIndex(const IString& strToken, Int& iIndex,
                                       bool bExactNotLike /* = true */)
{
  Retval retVal = RET_REQUEST_FAILED;

  resetIterator();
  Int iLocalIndex = 0;

  while (retVal != RET_NOERROR && hasNextToken())
  {
    if (bExactNotLike)
    {
      if (getNextToken() == strToken)
      {
        retVal = RET_NOERROR;
      } // getNextToken() == strToken.
    } // bExactNotLike.
    else
    {
      if (getNextToken().startsWith(strToken.c_bstr()))
      {
        retVal = RET_NOERROR;
      } // getNextToken().startsWith(strToken.c_bstr()).
    } // !bExactNotLike.

    if (retVal == RET_NOERROR)
    {
      iIndex = iLocalIndex;
    } // retval == RET_NOERROR.
    else
    {
      ++iLocalIndex;
    } // retval != RET_NOERROR.
  } // while (retval != RET_NOERROR && hasNextToken()).
    
  return retVal;
}

