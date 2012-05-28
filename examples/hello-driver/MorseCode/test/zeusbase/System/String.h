/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : String
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 17.04.08 8:08 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/String.h $
** 
** 70    17.04.08 8:08 Bha
** Timeval convertion implemented
** 
** 69    7.02.08 12:45 Bha
** Commenting fixed
** 
** 68    7.02.08 12:08 Mab
** operators for IString* added.
** 
** 67    6.02.08 15:06 Mab
** operators for boolean values added.
** 
** 66    6.02.08 14:56 Mab
** IString::toBool() IString::isBool() and TString constructor for bool
** added.
** 
** 65    4.02.08 7:22 Bha
** - new operators for unsigned int
** - stl bindings implemented for string and wstring
** 
** 64    23.01.08 11:12 Mab
** Overloaded methods for TString arguments added.
** 
** 63    21.01.08 10:52 Bha
** Error converting from Uint to int using the string. Fixed
** 
** 62    17.01.08 6:24 Bha
** Speedup string using internal member to store its size instead of
** reading each time using API function
** 
** 61    9.01.08 15:24 Bha
** renamed sprintf to format 
** 
** 60    9.01.08 13:30 Bha
** sprintf methods implemented for strings
** 
** 59    15.10.07 15:20 bha
** enquote corrected and hash-function added
** 
** 58    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 57    3.09.07 14:02 Mabbuehl
** VS6 warnings removed.
** 
** 56    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 55    2.07.07 7:26 bha
** toUint method and documentation
** 
** 54    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
**
** 44    9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
**
** 43    5.10.06 6:38 bha
** Stack types can hide addRef and release methods inside their interfaces
**
** 42    27.09.06 17:00 Mabbuehl
** Elimination Wide String
**
** 40    22.09.06 13:47 Mabbuehl
** Methoden terminated, enclosed und enquoted hinzugefgt.
**
** 36    20.09.06 17:43 bha
** format method implemented
**
** 34    20.09.06 15:39 bha
** static format float method
**
** 30    20.09.06 10:29 bha
** getSubString() mit lEndIndex -1: Alle Zeichen von lStartIndex bis Ende
** zurckgeben.
**
** 25    7.09.06 16:00 bha
** String mit compareTo erweitern
**
** 22    7.09.06 14:44 bha
** Erweitern des Strings
**
** 19    4.09.06 14:40 bha
** StringTool replaced. All methods are available in TString now.
**
** 17    4.09.06 12:09 Mabbuehl
** Impliziter cast-Operator fr wchar_t* implementiert.
***************************************************************************/


#ifndef StringH
#define StringH

#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/ByteArray.hpp>


#ifdef _MSC_VER
  #pragma warning(push, 1) // Avoid Visual Studio 6.0 level 4 and 3 compiler warnings.
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


#ifdef USE_BCB_BINDINGS
  #include <Classes.hpp>
#endif

#ifdef USE_STL_BINDINGS
  #ifdef _MSC_VER
    #pragma warning(push, 1) // Avoid Visual Studio 6.0 level 4 and 3 compiler warnings.
    #pragma warning(disable: 4701) // Previous pragma has no effect!
  #endif

  #include <string>

  #ifdef _MSC_VER
    #pragma warning(default: 4701)
    #pragma warning(pop)
  #endif
#endif


BEGIN_NAMESPACE_Zeus


/******************************************************************************/
/*! This is the implementation of the Zeus String. The Zeus String is a null
    terminated wide string array (16bit or 32bit depending on the platform).
    The last character of the string is the NULL-character witch is used to
    mark the end of the string.<BR>
    There are different methods for convertions such as number, float and 8bit
    array convertions.<BR>
    The string class is a stack type and implements the IString-interface. This
    interface is used to define other interface methods having string
    parameters.
*/
/******************************************************************************/
zeusbase_class TString : public IString
{
  public:
    //---------------------------------------------------------------------
    // constructors
    TString();
    TString(const wchar_t* data);
    TString(const char* data);
    TString(wchar_t wcChar, Uint uiCount=1);
    TString(char cChar, Uint uiCount=1);
    TString(const TString& strString);
    TString(const IString& strString);
    TString(const IString* pString);
    TString(Int32 lValue);
    TString(Int64 ldValue);
    TString(int iValue);
    TString(Uint32 ulValue);
    TString(Uint64 uldValue);
    TString(unsigned int uiValue);
    TString(Float fValue);
    TString(Float fValue, Uint uiDigits);
    TString(bool bValue);

  #ifdef USE_STL_BINDINGS
    TString(const std::wstring& rInstr);
    TString(const std::string& rInstr);
  #endif //USE_STL_BINDINGS

    /**********************************************************************/
    /*! Destroys the string and its arrays
    */
    /**********************************************************************/
    inline virtual ~TString()
    {
      clearBuffers();
    }

    //---------------------------------------------------------------------
    //static methods
    static TString formatFloat(Float fValue,
                               Float fRoundPrecision = 0,
                               Uint uiTailingZeros = 0,
                               Uint uiLeadingZeros = 1);
    static TString formatInt(  Int iValue,
                               Uint uiLeadingZeros);
    static TString format(const char* pcFormat, ...);
    static TString format(const wchar_t* pwcFormat, ...);
    static TString format(const IString& rFormat, ...);
    static TString formatV(const char* pcFormat, va_list Arg);
    static TString formatV(const wchar_t* pwcFormat, va_list Arg);
    static TString formatV(const IString& rFormat, va_list Arg);

    static TString transcode(const IByteArray& list);
    static TByteArray transcode(const TString& rValue, bool bAsWideChar);
    static TByteArray transcode(const IString& rValue, bool bAsWideChar);
    static TString trimExt(const IString& rSource,
                           const IString& rChars,
                           bool bLeft = true,
                           bool bRight = true);


    //---------------------------------------------------------------------
    //Operators
    TString& operator=(const TString& rInstr);
    TString& operator=(const IString& rInstr);
    TString& operator=(const IString* pInstr);
    TString& operator=(const wchar_t* pData);
    TString& operator=(const Int iData);
    TString& operator=(const int iData);
    TString& operator=(const Uint uiData);
    TString& operator=(const unsigned int uiData);
    TString& operator=(const Float fData);
    TString& operator=(const char* pData);
    TString& operator=(bool bData);
  #ifdef USE_STL_BINDINGS
    TString& operator=(const std::wstring& rInstr);
    TString& operator=(const std::string& rInstr);
  #endif
    bool operator==(const TString& rInstr) const;
    bool operator==(const IString& rInstr) const;
    bool operator==(const IString* pInstr) const;
    bool operator==(const wchar_t* pInbuffer) const;
    bool operator==(const char* pInbuffer) const;
    bool operator==(const Float fData) const;
    bool operator==(const Int iData) const;
    bool operator==(const int iData) const;
    bool operator==(const Uint uiData) const;
    bool operator==(const unsigned int uiData) const;
    bool operator==(bool bData) const;
  #ifdef USE_STL_BINDINGS
    bool operator==(const std::wstring& rInstr) const;
    bool operator==(const std::string& rInstr) const;
  #endif
    TString operator+ (const TString& rInstr) const;
    TString operator+ (const IString& rInstr) const;
    TString operator+ (const wchar_t* pInbuffer) const;
    TString operator+ (const char* pInbuffer) const;
    TString operator+ (const Int iInval) const;
    TString operator+ (const int iInval) const;
    TString operator+ (const Uint uiInval) const;
    TString operator+ (const unsigned int uiInval) const;
    TString operator+ (const Float fInval) const;
  #ifdef USE_STL_BINDINGS
    TString operator+ (const std::wstring& rInstr) const;
    TString operator+ (const std::string& rInstr) const;
  #endif
    bool operator!=(const TString& rInstr) const;
    bool operator!=(const IString& rInstr) const;
    bool operator!=(const IString* pInstr) const;
    bool operator!=(const wchar_t* pInbuffer)const;
    bool operator!=(const char* pInbuffer) const;
    bool operator!=(const Float fData) const;
    bool operator!=(const Int iData) const;
    bool operator!=(const int iData) const;
    bool operator!=(const Uint uiData) const;
    bool operator!=(const unsigned int uiData) const;
    bool operator!=(const bool bData) const;
  #ifdef USE_STL_BINDINGS
    bool operator!=(const std::wstring& rInstr) const;
    bool operator!=(const std::string& rInstr) const;
  #endif
    TString& operator+= (const TString& rInstr);
    TString& operator+= (const IString& rInstr);
    TString& operator+= (const wchar_t* pInbuffer);
    TString& operator+= (const char* pInbuffer);
    TString& operator+= (const Int iInval);
    TString& operator+= (const int iInval);
    TString& operator+= (const Uint uiInval);
    TString& operator+= (const unsigned int uiInval);
    TString& operator+= (const Float fInval);
  #ifdef USE_STL_BINDINGS
    TString& operator+= (const std::wstring& rInstr);
    TString& operator+= (const std::string& rInstr);
  #endif //USE_STL_BINDINGS

    wchar_t& operator[](Int iIndex);
    bool operator<  (const TString& rInStr) const;
    bool operator<= (const TString& rInStr) const;
    bool operator>  (const TString& rInStr) const;
    bool operator>= (const TString& rInStr) const;


    //---------------------------------------------------------------------
    // Substring-Manipulationen.
    bool containsChar(const wchar_t wcChar) const;
    bool containsCharOf(const wchar_t* wcChars) const;
    Int indexOf(wchar_t wcChar) const;
    TString deleteSubString(Int iStartIndex, Int iEndIndex = LONG_MAX) const;
    TString getSubString(Int iStartIndex, Int iEndIndex = LONG_MAX) const;
    TString getLeft(Int iCharCount) const;
    TString getRight(Int iCharCount) const;
    TString deleteLeft(Int iCharCount) const;
    TString deleteRight(Int iCharCount) const;
    Int getSubStringCount(const IString& rSubstring) const;
    TString insert(Int iIndex, const IString& rStrToInsert) const;
    TString insert(Int iIndex, const TString& rStrToInsert) const;
    TString remove(const IString& rToRemove, Int* pReplaces = NULL) const;
    TString remove(const TString& strToRemove, Int* pReplaces = NULL) const;
    TString removeFirst(const IString& rToRemove) const;
    TString removeFirst(const TString& rToRemove) const;
    TString replace(const IString& rToRemove, const IString& rReplace, Int* pReplaces = NULL) const;
    TString replace(const TString& rToRemove, const TString& rReplace, Int* pReplaces = NULL) const;
    TString replaceFirst(const IString& rToRemove, const IString& rReplace) const;
    TString replaceFirst(const TString& rToRemove, const TString& rReplace) const;
    TString toUpperCase() const;
    TString toLowerCase() const;
    TString trim() const;
    TString trimLeft() const;
    TString trimRight() const;
    TString terminated(const IString& rTermination) const;
    TString terminated(const TString& rTermination) const;
    TString enclosed(const IString& rEnclosure) const;
    TString enclosed(const TString& rEnclosure) const;
    TString enquoted() const;
    Int64 getHash() const;

    //---------------------------------------------------------------------
    //Methods of IString
    virtual const wchar_t* MQUALIFIER c_bstr() const;
    virtual const char* MQUALIFIER c_str(BOOL_ERRORRETVAL(pError)) const;
    virtual Float MQUALIFIER toFloat(Float fPredef = 0.0, bool* pbError = NULL) const;
    virtual Int   MQUALIFIER toInt(Int iPredef = 0, bool* pbError = NULL) const;
    virtual Uint  MQUALIFIER toUint(Uint uiPredef = 0, bool* pbError = NULL) const;
    virtual Timeval MQUALIFIER toTimeval(Timeval tmPredef = 0, bool* pbError = NULL) const;
    virtual bool MQUALIFIER toBool(bool bPredef = false, bool* pbError = NULL) const;
    virtual bool MQUALIFIER isFloat() const;
    virtual bool MQUALIFIER isInt() const;
    virtual bool MQUALIFIER isBool() const;
    virtual bool MQUALIFIER equals(const wchar_t* pInbuffer, bool bIgnoreCase = false) const;
    virtual bool MQUALIFIER equalsStr(const IString& rInstr, bool bIgnoreCase = false) const;
    virtual void MQUALIFIER concat(const wchar_t* pInbuffer);
    virtual void MQUALIFIER concatStr(const IString& rInstr);
    virtual void MQUALIFIER assign(const wchar_t* pInbuffer);
    virtual void MQUALIFIER assignStr(const IString& rInstr);
    virtual Int MQUALIFIER getSize() const;
    virtual wchar_t MQUALIFIER getChar(Int iIndex) const;
    virtual Int MQUALIFIER getFirstPos(const wchar_t* pSubBuffer) const;
    virtual Int MQUALIFIER getFirstPosStr(const IString& rSubString) const;
    virtual Int MQUALIFIER getLastPos(const wchar_t* pSubBuffer) const;
    virtual Int MQUALIFIER getLastPosStr(const IString& rSubString) const;
    virtual void MQUALIFIER clear();
    virtual bool MQUALIFIER isEmpty() const;
    virtual bool MQUALIFIER endsWith(const wchar_t* pString) const;
    virtual bool MQUALIFIER endsWithStr(const IString& rString) const;
    virtual bool MQUALIFIER startsWith(const wchar_t* pString) const;
    virtual bool MQUALIFIER startsWithStr(const IString& rString) const;
    virtual Int MQUALIFIER compareTo(const IString& rString) const;
    virtual bool MQUALIFIER contains(const wchar_t* pSubString) const;
    virtual bool MQUALIFIER containsStr(const IString& rSubString) const;

  protected:

    static TString convertDouble(const Float fValue, Int iDigit = 15);

  private:
    ///wchar_t Array Buffer
    wchar_t* m_pWBuffer;
    ///char array (temporary used to return the 8bit array). Only for efficiency, mutable.
    mutable char* m_pCBuffer;
    ///empty character
    static wchar_t m_wcEmpty;
    ///Size of the string. Only for efficiency, not for NULL chars, mutable.
    mutable Int m_iSize;

    //---------------------------------------------------------------------
    void clearBuffers();
    void clearWBuffer();
    void clearCBuffer() const;
    void updateSize() const;
    wchar_t* convToWStr(const char* pData);
    char* convToCStr(const wchar_t* pData, bool* pError) const;

    void create(const wchar_t* pData, bool bMyMemory = false);
    static void replace_internal(std::wstring& rData, Int iPos, Int iCharsToRemove, const std::wstring& rReplace);
    void assignInt32(Int32 lValue);
    void assignInt64(Int64 ldValue);
    void assignUint32(Uint32 ulValue);
    void assignUint64(Uint64 uldValue);
};



//##############################################################################
// INLINE
/**************************************************************************/
/*! Creates an empty string
*/
/**************************************************************************/
inline TString::TString()
{
  create(NULL);
}

/**************************************************************************/
/*! Creates a string out of a wide char array. The array must be NULL
    terminated
    \param pData : wide array containing the data
*/
/**************************************************************************/
inline TString::TString(const wchar_t* pData)
{
  create(pData);
}

/**************************************************************************/
/*! Creates a string out of an other string by interface.
    \param rString : string to copy
*/
/**************************************************************************/
inline TString::TString(const IString& rString)
{
  create(rString.c_bstr());
}

/**************************************************************************/
/*! Copy constructor
    \param rString : string to copy
*/
/**************************************************************************/
inline TString::TString(const TString& rString)
{
  create(rString.m_pWBuffer);
}

/**************************************************************************/
/*! Converts a string into a array of bytes
*/
/**************************************************************************/
inline /*static*/ TByteArray TString::transcode(const TString& rValue, bool bAsWideChar)
{
  return TString::transcode((const IString&)rValue, bAsWideChar);
}

/**************************************************************************/
/*! Checks if a char is contained by the string
    \param wcChar : Char to check
    \retval true : char found
    \retval false: No such char found
*/
/**************************************************************************/
inline bool TString::containsChar(const wchar_t wcChar) const
{
  return (this->indexOf(wcChar) >= 0);
}

/**************************************************************************/
/*! This method returns the left substring (begins at index 0 to index
    iCharCount -1
    \see TString::getSubString
 */
/**************************************************************************/
inline TString TString::getLeft(Int iCharCount) const
{
  return this->getSubString(0, iCharCount-1);
}

/**************************************************************************/
/*! This method returns the right substring (begins at index
    size- iCharCount to size-1
    \see TString::getSubString
 */
/**************************************************************************/
inline TString TString::getRight(Int iCharCount) const
{
  Int iSize = getSize();
  return this->getSubString(iSize - iCharCount, iSize-1);
}

/**************************************************************************/
/*! This method deletes the left substring (begins at index 0 to index
    iCharCount -1
    \see TString::deleteSubString
*/
/**************************************************************************/
inline TString TString::deleteLeft(Int iCharCount) const
{
  return this->deleteSubString(0, iCharCount-1);
}

/**************************************************************************/
/*! This method deletes the right substring (begins at index
    size - ulCharCount to size-1
    \see TString::deleteSubString
 */
/**************************************************************************/
inline TString TString::deleteRight(Int iCharCount) const
{
  Int iSize = getSize();
  return this->deleteSubString(iSize-iCharCount, iSize-1);
}

/**************************************************************************/
/*! inserts a string at the position index and returns the new string
    \param lIndex : position index to insert the string
    \param rStrToInsert : String to insert
    \return new string
*/
/**************************************************************************/
inline TString TString::insert(Int iIndex, const TString& rStrToInsert) const
{
  return this->insert(iIndex, (const IString&)rStrToInsert);
}

/******************************************************************************/
/*! This method removes all substrings from this string and returns the new
    string
    \param rToRemove : Substring to remove
    \param pReplaces : If pointer is valid, the number of replaces are returned
    \return new string
*/
/******************************************************************************/
inline TString TString::remove(const IString& rToRemove, Int* pReplaces /*= NULL*/) const
{
  return replace(rToRemove, (const IString&)TString(L""), pReplaces);
}

/******************************************************************************/
/*! This method removes all substrings from this string and returns the new
    string
    \param rToRemove : Substring to remove
    \param pReplaces : If pointer is valid, the number of replaces are returned
    \return new string
*/
/******************************************************************************/
inline TString TString::remove(const TString& rToRemove, Int* pReplaces /*= NULL*/) const
{
  return replace((const IString&)rToRemove, (const IString&)TString(L""), pReplaces);
}

/******************************************************************************/
/*! This method removes the first substrings found from this string and
    returns the new string
    \param rToRemove : Substring to remove
    \return new string
*/
/******************************************************************************/
inline TString TString::removeFirst(const IString& rToRemove) const
{
  return replaceFirst((const IString&)rToRemove, (const IString&)TString(L""));
}

/******************************************************************************/
/*! This method removes the first substrings found from this string and
    returns the new string
    \param rToRemove : Substring to remove
    \return new string
*/
/******************************************************************************/
inline TString TString::removeFirst(const TString& rToRemove) const
{
  return replaceFirst((const IString&)rToRemove, (const IString&)TString(L""));
}

/******************************************************************************/
/*! This method replaces the first substring with a new string. It might be used
    just for removing a substring by calling this method with an empty
    strReplace variable.
    \param rToRemove : Substring to remove
    \param rReplace : String for replaceing
    \return new string
*/
/******************************************************************************/
inline TString TString::replaceFirst(const TString& rToRemove, const TString& rReplace) const
{
  return replaceFirst((const IString&)rToRemove, (const IString&)rReplace);
}

/******************************************************************************/
/*! Overload the method terminated() for TString.
*/
/******************************************************************************/
inline TString TString::terminated(const TString& rTermination) const
{
  return terminated((const IString&) rTermination);
}

/******************************************************************************/
/*! Overload the method enclosed() for TString.
*/
/******************************************************************************/
inline TString TString::enclosed(const TString& rEnclosure) const
{
  return enclosed((const IString&) rEnclosure);
}

/******************************************************************************/
/*! This method works like replace() but it will
    replace all substrings inside this string.

    \param rToRemove : Substring to remove
    \param strReplace  : String for replacing
    \param pReplaces : If pointer is valid, the number of replaces are returned
    \return new string
*/
/******************************************************************************/
inline TString TString::replace(const TString& rToRemove, const TString& rReplace, Int* pReplaces /*= NULL*/) const
{
  return replace((const IString&)rToRemove, (const IString&)rReplace, pReplaces);
}

/**************************************************************************/
/*! This method trims the string. All leading or ending white spaces are
    removed.
    \return trimmed string
*/
/**************************************************************************/
inline TString TString::trim() const
{
  return TString::trimExt(*this, TString(L" \t\r\n"), true, true);
}

/**************************************************************************/
/*! This method trims the string. All leading white spaces are
    removed.
    \return trimmed string
*/
/**************************************************************************/
inline TString TString::trimLeft() const
{
  return TString::trimExt(*this, TString(L" \t\r\n"), true, false);
}

/**************************************************************************/
/*! This method trims the string. All ending white spaces are
    removed.
    \return trimmed string
*/
/**************************************************************************/
inline TString TString::trimRight() const
{
  return TString::trimExt(*this, TString(L" \t\r\n"), false, true);
}

/***************************************************************************/
/*! Returns a string terminated by strTermination, but does not add the
    termination if it already exists.
    \param rTermination : String must end with this substring
    \return new string
*/
/***************************************************************************/
inline TString TString::terminated(const IString& rTermination) const
{
  TString strReturn = *this;

  if (!strReturn.endsWithStr(rTermination))
  {
    strReturn += rTermination;
  } // !strReturn.endsWithStr(rTermination).

  return strReturn;
}


/***************************************************************************/
/*! Returns a string enclosed by rEnclosure, but does not add the
    enclosure wherever it already exists.
    \param rEnclosure : String must start and end with this substring
    \return new string
*/
/***************************************************************************/
inline TString TString::enclosed(const IString& rEnclosure) const
{
  TString strReturn = terminated(rEnclosure);

  if (!this->startsWithStr(rEnclosure))
  {
    strReturn = TString(rEnclosure) + strReturn;
  } // !this->startsWithStr(rEnclosure).

  return strReturn;
}


/***************************************************************************/
/*! Returns a string enquoted by ", but does not add the quotes wherever
    they already exist.
    \return new string
*/
/***************************************************************************/
inline TString TString::enquoted() const
{
  return enclosed(TString(L"\""));
}

/**************************************************************************/
/*! sets a formated string using the standard C formatting of string.
    See also std::sprintf and std::wsprintf
*/
/**************************************************************************/
inline /*static*/ TString TString::format(const char* pcFormat, ...)
{
  va_list Args;
  va_start(Args, pcFormat);
  TString strRetval = formatV(pcFormat, Args);
  va_end(Args);

  return strRetval;
}

/**************************************************************************/
/*! sets a formated string using the standard C formatting of string.
    See also std::sprintf and std::wsprintf
*/
/**************************************************************************/
inline /*static*/ TString TString::format(const wchar_t* pwcFormat, ...)
{
  va_list Args;
  va_start(Args, pwcFormat);
  TString strRetval = formatV(pwcFormat, Args);
  va_end(Args);

  return strRetval;
}

/**************************************************************************/
/*! sets a formated string using the standard C formatting of string.
    See also std::sprintf and std::wsprintf
*/
/**************************************************************************/
inline /*static*/ TString TString::format(const IString& rFormat, ...)
{
  va_list Args;
  va_start(Args, rFormat);
  TString strRetval = formatV(rFormat, Args);
  va_end(Args);

  return strRetval;
}


/**************************************************************************/
/*! \see IString::c_bstr
*/
/**************************************************************************/
inline const wchar_t* MQUALIFIER TString::c_bstr() const
{
  return m_pWBuffer;
}

/**************************************************************************/
/*! \see IString::c_str
*/
/**************************************************************************/
inline const char* MQUALIFIER TString::c_str(bool* pError) const
{
  return convToCStr(m_pWBuffer, pError);
}

/**************************************************************************/
/*! \see IString::isFloat
*/
/**************************************************************************/
inline bool MQUALIFIER TString::isFloat() const
{
  bool bError = false;
  toFloat(0, &bError);
  return !bError;
}


/**************************************************************************/
/*! \see IString::isInt
*/
/**************************************************************************/
inline bool MQUALIFIER TString::isInt() const
{
  bool bError = false;
  toInt(0, &bError);
  return !bError;
}


/**************************************************************************/
/*! \see IString::isBool
*/
/**************************************************************************/
inline bool MQUALIFIER TString::isBool() const
{
  bool bError = false;
  toBool(false, &bError);
  return !bError;
}


/**************************************************************************/
/*! \see IString::equalsStr
*/
/**************************************************************************/
inline bool MQUALIFIER TString::equalsStr(const IString& rInstr, bool bIgnoreCase /*= false*/) const
{
  return this->equals(rInstr.c_bstr(), bIgnoreCase);
}

/**************************************************************************/
/*! \see IString::concatStr
*/
/**************************************************************************/
inline void MQUALIFIER TString::concatStr(const IString& rInstr)
{
  concat(rInstr.c_bstr());
}

/**************************************************************************/
/*! \see IString::assignStr
*/
/**************************************************************************/
inline void MQUALIFIER TString::assignStr(const IString& rInstr)
{
  this->assign(rInstr.c_bstr());
}


/**************************************************************************/
/*! \see IString::getChar
*/
/**************************************************************************/
inline wchar_t MQUALIFIER TString::getChar(Int iIndex) const
{
  wchar_t wcRetval = 0x0000;
  Int iCounter = getSize();

  if (iIndex < iCounter && iIndex >= 0 && m_pWBuffer != NULL)
  {
    wcRetval = m_pWBuffer[iIndex];
  }
  return wcRetval;
}

/**************************************************************************/
/*! \see IString::getSize
*/
/**************************************************************************/
inline Int MQUALIFIER TString::getSize() const
{
  return m_iSize;
}


/**************************************************************************/
/*! \see IString::getFirstPosStr
*/
/**************************************************************************/
inline Int MQUALIFIER TString::getFirstPosStr(const IString& rSubString)const
{
  return getFirstPos(rSubString.c_bstr());
}

/**************************************************************************/
/*! \see IString::getLastPosStr
*/
/**************************************************************************/
inline Int MQUALIFIER TString::getLastPosStr(const IString& rSubString)const
{
  return getLastPos(rSubString.c_bstr());
}


/**************************************************************************/
/*! \see IString::clear
*/
/**************************************************************************/
inline void MQUALIFIER TString::clear()
{
  if (m_pWBuffer != NULL)
  {
    m_pWBuffer[0] = 0;
  } // m_pWBuffer != NULL.

  m_iSize = 0;
}


/**************************************************************************/
/*! \see IString::isEmpty
*/
/**************************************************************************/
inline bool MQUALIFIER TString::isEmpty()const
{
  return (getSize() == 0);
}

/**************************************************************************/
/*! \see IString::endsWith
*/
/**************************************************************************/
inline bool MQUALIFIER TString::endsWith(const wchar_t* pString)const
{
  return this->endsWithStr(TString(pString));
}

/**************************************************************************/
/*! \see IString::startsWith
*/
/**************************************************************************/
inline bool MQUALIFIER TString::startsWith(const wchar_t* pString)const
{
  return this->startsWithStr(TString(pString));
}

/**************************************************************************/
/*! \see IString::contains
*/
/**************************************************************************/
inline bool MQUALIFIER TString::contains(const wchar_t* pSubString) const
{
  return this->containsStr(TString(pSubString));
}

/**************************************************************************/
/*! \see IString::containsStr
*/
/**************************************************************************/
inline bool MQUALIFIER TString::containsStr(const IString& rSubString) const
{
  return (this->getFirstPosStr(rSubString) >= 0);
}


/**************************************************************************/
/*! Copy operator. An other string is copied into this string object
    \param rInstr : object to copy
*/
/**************************************************************************/
inline TString& TString::operator=(const TString& rInstr)
{
  assign(rInstr.m_pWBuffer);
  return *this;
}

/**************************************************************************/
/*! Copy operator. An other string is copied into this string object
    \param rInstr : object to copy
*/
/**************************************************************************/
inline TString& TString::operator=(const IString& rInstr)
{
  assign(rInstr.c_bstr());
  return *this;
}


/**************************************************************************/
/*! Assignment operator. Another string is copied into this string object
    \param pInstr : Pointer to object to assign
*/
/**************************************************************************/
inline TString& TString::operator=(const IString* pInstr)
{
  if (pInstr == NULL)
  {
    clear();
  } // pInstr == NULL.
  else
  {
    assignStr(*pInstr);
  } // pInstr != NULL.

  return *this;
}


/**************************************************************************/
/*! Copy operator. A wide array is copied into this string object
    \param pData : wide array to copy
*/
/**************************************************************************/
inline TString& TString::operator=(const wchar_t* pData)
{
  assign(pData);
  return *this;
}

/**************************************************************************/
/*! This assigns a int value to the string object
    \param iData : Value to assign
*/
/**************************************************************************/
inline TString& TString::operator=(const Int iData)
{
  #if defined(__ZEUS32__)
    this->assignInt32(iData);
  #elif defined(__ZEUS64__)
    this->assignInt64(iData);
  #else
    #error "TString::operator =(const Int iData): assign operator not implemented for this platform"
  #endif
  return *this;
}

/**************************************************************************/
/*! This assigns a int value to the string object
    \param iData : Value to assign
*/
/**************************************************************************/
inline TString& TString::operator=(const int iData)
{
  #if defined(__ZEUS32__)
    this->assignInt32(iData);
  #elif defined(__ZEUS64__)
    this->assignInt64(iData);
  #else
    #error "TString::operator =(const int iData): assign operator not implemented for this platform"
  #endif
  return *this;
}

/**************************************************************************/
/*! This assigns a unsigned int value to the string object
    \param uiData : Value to assign
*/
/**************************************************************************/
inline TString& TString::operator=(const Uint uiData)
{
  #if defined(__ZEUS32__)
    this->assignUint32(static_cast<Uint32>(uiData));
  #elif defined(__ZEUS64__)
    this->assignUint64(static_cast<Uint32>(uiData));
  #else
    #error "TString::operator =(const Uint uiData): assign operator not implemented for this platform"
  #endif
  return *this;
}

/**************************************************************************/
/*! This assigns a unsigned int value to the string object
    \param uiData : Value to assign
*/
/**************************************************************************/
inline TString& TString::operator=(const unsigned int uiData)
{
  #if defined(__ZEUS32__)
    this->assignUint32(static_cast<Uint32>(uiData));
  #elif defined(__ZEUS64__)
    this->assignUint64(static_cast<Uint32>(uiData));
  #else
    #error "TString::operator =(const unsigned int uiData): assign operator not implemented for this platform"
  #endif
  return *this;
}

/**************************************************************************/
/*! This assigns a float value to the string object
    \param fData : Value to assign
*/
/**************************************************************************/
inline TString& TString::operator=(const Float fData)
{
  TString strValue = convertDouble(fData);
  this->assign(strValue.m_pWBuffer);
  return *this;
}


/**************************************************************************/
/*! This assigns a 8bit array to the string object
    \param pData : array to assign
*/
/**************************************************************************/
inline TString& TString::operator=(const char* pData)
{
  m_pWBuffer = convToWStr(pData);
  return *this;
}


/**************************************************************************/
/*! This assigns a boolean value to the string object
    \param bData : boolean value to assign
*/
/**************************************************************************/
inline TString& TString::operator=(bool bData)
{
  assignInt32(bData);
  return *this;
}


#ifdef USE_STL_BINDINGS
/***************************************************************************/
/*! Assign operator for stl string class
*/
/***************************************************************************/
inline TString& TString::operator=(const std::wstring& rInstr)
{
  assign(rInstr.c_str());
  return *this;
}

/***************************************************************************/
/*! Assign operator for stl string class
*/
/***************************************************************************/
inline TString& TString::operator=(const std::string& rInstr)
{
  m_pWBuffer = convToWStr(rInstr.c_str());
  return *this;
}
#endif //USE_STL_BINDINGS

/**************************************************************************/
/*! Vergleichsoperator. Der wchar_t-Array wird mit dem des Objekts verglichen.
    \param rInstr : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator==(const TString& rInstr)const
{
  return equals(rInstr.m_pWBuffer);
}

/**************************************************************************/
/*! Vergleichsoperator. Der wchar_t-Array wird mit dem des Objekts verglichen.
    \param rInstr : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator==(const IString& rInstr)const
{
  return equals(rInstr.c_bstr());
}


/**************************************************************************/
/*! Vergleichsoperator f�r IString*.

    \param pInstr : Zeiger auf zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator==(const IString* pInstr) const
{
  return equals(pInstr == NULL ? NULL : pInstr->c_bstr());
}


/**************************************************************************/
/*! Vergleichsoperator. Der wchar_t-Array wird mit dem des Objekts verglichen.
    \param pInbuffer : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator==(const wchar_t* pInbuffer) const
{
  return equals(pInbuffer);
}

/**************************************************************************/
/*! Vergleichsoperator. Der char-Array wird mit dem des Objekts verglichen.
    \param inbuffer : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator==(const char* inbuffer)const
{
  TString str(inbuffer);
  return equals(str.m_pWBuffer);
}

/**************************************************************************/
/*! Vergleichsoperator: Der einen double Wert mit dem String vergleicht
    \param fData : Zuweisungsparameter
*/
/**************************************************************************/
inline bool TString::operator==(const Float fData) const
{
  TString strFormat = convertDouble(fData);
  return equals(strFormat.m_pWBuffer);
}

/**************************************************************************/
/*! equals operator check if the string is equal to an int
    \param iData : value to check
*/
/**************************************************************************/
inline bool TString::operator==(const Int iData) const
{
  TString strData(iData);
  return equalsStr(strData);
}

/**************************************************************************/
/*! equals operator check if the string is equal to an int
    \param iData : value to check
*/
/**************************************************************************/
inline bool TString::operator==(const int iData) const
{
  TString strData(iData);
  return equalsStr(strData);
}

/**************************************************************************/
/*! equals operator check if the string is equal to an unsigned int
    \param uiData : value to check
*/
/**************************************************************************/
inline bool TString::operator==(const Uint uiData) const
{
  TString strData(uiData);
  return equalsStr(strData);
}

/**************************************************************************/
/*! equals operator check if the string is equal to an unsigned int
    \param uiData : value to check
*/
/**************************************************************************/
inline bool TString::operator==(const unsigned int uiData) const
{
  TString strData(uiData);
  return equalsStr(strData);
}


/**************************************************************************/
/*! Check the equality to a boolean value.
    \param bData : boolean value for comparison.                          */
/**************************************************************************/
inline bool TString::operator==(bool bData) const
{
  TString strData(bData);
  return equalsStr(strData);
}


#ifdef USE_STL_BINDINGS
/***************************************************************************/
/*! Equals operator for stl string class
*/
/***************************************************************************/
inline bool TString::operator==(const std::wstring& rInstr)const
{
  TString str(rInstr.c_str());
  return equals(str.m_pWBuffer);
}

/***************************************************************************/
/*! Equals operator for stl string class
*/
/***************************************************************************/
inline bool TString::operator==(const std::string& rInstr)const
{
  TString str(rInstr.c_str());
  return equals(str.m_pWBuffer);
}
#endif // USE_STL_BINDINGS

/**************************************************************************/
/*! Hinzufuegen eines Strings
    \param rInstr : Stringobjekt
*/
/**************************************************************************/
inline TString TString::operator+ (const TString& rInstr) const
{
  TString str(this->m_pWBuffer);
  str.concat(rInstr.m_pWBuffer);
  return str;
}

/**************************************************************************/
/*! Hinzufuegen eines Strings
    \param rInstr : Stringobjekt
*/
/**************************************************************************/
inline TString TString::operator+ (const IString& rInstr) const
{
  TString str(this->m_pWBuffer);
  str.concat(rInstr.c_bstr());
  return str;
}

/**************************************************************************/
/*! Hinzufuegen eines wchar_t-Arrays
    \param pInbuffer : wchar_t Buffer welcher hinzugefuegt wird
*/
/**************************************************************************/
inline TString TString::operator+ (const wchar_t* pInbuffer) const
{
  TString str(this->m_pWBuffer);
  str.concat(pInbuffer);
  return str;
}

/**************************************************************************/
/*! Hinzufuegen eines char-Arrays
    \param pInbuffer : char Buffer welcher hinzugefuegt wird
*/
/**************************************************************************/
inline TString TString::operator+ (const char* pInbuffer) const
{
  TString str(this->m_pWBuffer);
  TString strC(pInbuffer);
  str.concat(strC.m_pWBuffer);
  return str;
}

/**************************************************************************/
/*! adds an int value to the string
    \param iInval : Value to add
*/
/**************************************************************************/
inline TString TString::operator+ (const Int iInval) const
{
  TString str(this->m_pWBuffer);
  TString strInval(iInval);
  str.concatStr(strInval);
  return str;
}

/**************************************************************************/
/*! adds an int value to the string
    \param iInval : Value to add
*/
/**************************************************************************/
inline TString TString::operator+ (const int iInval) const
{
  TString str(this->m_pWBuffer);
  TString strInval(iInval);
  str.concatStr(strInval);
  return str;
}

/**************************************************************************/
/*! adds an unsigned int value to the string
    \param uiInval : Value to add
*/
/**************************************************************************/
inline TString TString::operator+ (const Uint uiInval) const
{
  TString str(this->m_pWBuffer);
  TString strInval(uiInval);
  str.concatStr(strInval);
  return str;
}

/**************************************************************************/
/*! adds an unsigned int value to the string
    \param uiInval : Value to add
*/
/**************************************************************************/
inline TString TString::operator+ (const unsigned int uiInval) const
{
  TString str(this->m_pWBuffer);
  TString strInval(uiInval);
  str.concatStr(strInval);
  return str;
}

/**************************************************************************/
/*! Hinzufuegen eines float-Values
    \param fInval : float-Value
*/
/**************************************************************************/
inline TString TString::operator+ (const Float fInval) const
{
  TString strTmp(this->m_pWBuffer);
  TString strConv = convertDouble(fInval);
  strTmp.concatStr(strConv);
  return strTmp;
}

#ifdef USE_STL_BINDINGS

/***************************************************************************/
/*! Concat operator for stl string class
*/
/***************************************************************************/
inline TString TString::operator+ (const std::wstring& rInstr) const
{
  TString str(this->m_pWBuffer);
  TString strC(rInstr.c_str());
  str.concat(strC.m_pWBuffer);
  return str;
}

/***************************************************************************/
/*! Concat operator for stl string class
*/
/***************************************************************************/
inline TString TString::operator+ (const std::string& rInstr) const
{
  TString str(this->m_pWBuffer);
  TString strC(rInstr.c_str());
  str.concat(strC.m_pWBuffer);
  return str;
}
#endif //USE_STL_BINDINGS

/**************************************************************************/
/*! Vergleichsoperator. Der wchar_t-Array wird mit dem des Objekts verglichen.
    \param rInstr : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator!=(const TString& rInstr) const
{
  return !(equals(rInstr.m_pWBuffer));
}

/**************************************************************************/
/*! Vergleichsoperator. Der wchar_t-Array wird mit dem des Objekts verglichen.
    \param rInstr : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator!=(const IString& rInstr) const
{
  return !(equals(rInstr.c_bstr()));
}


/**************************************************************************/
/*! Vergleichsoperator f�r IString*.

    \param pInstr : Zeiger auf zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator!=(const IString* pInstr) const
{
  return !equals(pInstr == NULL ? NULL : pInstr->c_bstr());
}


/**************************************************************************/
/*! Vergleichsoperator. Der wchar_t-Array wird mit dem des Objekts verglichen.
    \param pInbuffer : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator!=(const wchar_t* pInbuffer)const
{
  return !(equals(pInbuffer));
}

/**************************************************************************/
/*! Vergleichsoperator. Der char-Array wird mit dem des Objekts verglichen.
    \param pInbuffer : zu vergleichendes Stringobjekt
*/
/**************************************************************************/
inline bool TString::operator!=(const char* pInbuffer) const
{
  TString str(pInbuffer);
  return !(equals(str.m_pWBuffer));
}

/**************************************************************************/
/*! Vergleichsoperator: Der einen float Wert mit dem String vergleicht
    \param fData : Zuweisungsparameter
*/
/**************************************************************************/
inline bool TString::operator!=(const Float fData) const
{
  TString str(fData);
  return !(equals(str.m_pWBuffer));
}

/**************************************************************************/
/*! Checks if the string is not equal to an int value
    \param iData : value to check
*/
/**************************************************************************/
inline bool TString::operator!=(const Int iData) const
{
  TString str(iData);
  return !(equals(str.m_pWBuffer));
}

/**************************************************************************/
/*! Checks if the string is not equal to an int value
    \param iData : value to check
*/
/**************************************************************************/
inline bool TString::operator!=(const int iData) const
{
  TString str(iData);
  return !(equals(str.m_pWBuffer));
}

/**************************************************************************/
/*! Checks if the string is not equal to an unsigned int value
    \param uiData : value to check
*/
/**************************************************************************/
inline bool TString::operator!=(const Uint uiData) const
{
  TString str(uiData);
  return !(equals(str.m_pWBuffer));
}

/**************************************************************************/
/*! Checks if the string is not equal to an unsigned int value
    \param uiData : value to check
*/
/**************************************************************************/
inline bool TString::operator!=(const unsigned int uiData) const
{
  TString str(uiData);
  return !(equals(str.m_pWBuffer));
}


/**************************************************************************/
/*! Negation of operator==.
/**************************************************************************/
inline bool TString::operator!=(bool bData) const
{
  TString str(bData);
  return !(equals(str.m_pWBuffer));
}


#ifdef USE_STL_BINDINGS
/***************************************************************************/
/*! Not Equal operator for stl string class
*/
/***************************************************************************/
inline bool TString::operator!=(const std::wstring& rInstr) const
{
  TString str(rInstr.c_str());
  return !equals(str.m_pWBuffer);
}

/***************************************************************************/
/*! Not Equal operator for stl string class
*/
/***************************************************************************/
inline bool TString::operator!=(const std::string& rInstr) const
{
  TString str(rInstr.c_str());
  return !equals(str.m_pWBuffer);
}
#endif //USE_STL_BINDINGS

/**************************************************************************/
/*! Concats a string with an other string
    \param rInstr : string to concatenate
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const TString& rInstr)
{
  this->concatStr(rInstr);
  return *this;
}

/**************************************************************************/
/*! Concats a string with an other string
    \param rInstr : string to concatenate
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const IString& rInstr)
{
  this->concatStr(rInstr);
  return *this;
}

/**************************************************************************/
/*! Concats a string with a wide char buffer
    \param pInbuffer : buffer
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const wchar_t* pInbuffer)
{
  this->concat(pInbuffer);
  return *this;
}

/**************************************************************************/
/*! Concats a string with a char buffer
    \param pInbuffer : buffer
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const char* pInbuffer)
{
  TString strInBuffer(pInbuffer);
  this->concatStr(strInBuffer);
  return *this;
}

/**************************************************************************/
/*! Concats a string with a int value
    \param iInval : value
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const Int iInval)
{
  TString strInVal(iInval);
  this->concatStr(strInVal);
  return *this;
}

/**************************************************************************/
/*! Concats a string with a int value
    \param iInval : value
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const int iInval)
{
  TString strInVal(iInval);
  this->concatStr(strInVal);
  return *this;
}

/**************************************************************************/
/*! Concats a string with a unsigned Int value
    \param iInval : value
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const Uint uiInval)
{
  TString strInVal(uiInval);
  this->concatStr(strInVal);
  return *this;
}

/**************************************************************************/
/*! Concats a string with a unsigned int value
    \param iInval : value
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const unsigned int uiInval)
{
  TString strInVal(uiInval);
  this->concatStr(strInVal);
  return *this;
}

/**************************************************************************/
/*! Concats a string with a float value
    \param fInval : value
    \return this
*/
/**************************************************************************/
inline TString& TString::operator+= (const Float fInval)
{
  TString strInVal(fInval);
  this->concatStr(strInVal);
  return *this;
}

#ifdef USE_STL_BINDINGS
/***************************************************************************/
/*! concats a string with a std::wstring
    \param rInstr : string value
*/
/***************************************************************************/
inline TString& TString::operator+= (const std::wstring& rInstr)
{
  TString strIn(rInstr.c_str());
  this->concatStr(strIn);
  return *this;
}

/***************************************************************************/
/*! concats a string with a std::string
    \param rInstr : string value
*/
/***************************************************************************/
inline TString& TString::operator+= (const std::string& rInstr)
{
  TString strIn(rInstr.c_str());
  this->concatStr(strIn);
  return *this;
}
#endif

/**************************************************************************/
/*! Klammeroperator: Zugriff auf ein bestimmtes Character im String
    \param index : Zuweisungsparameter
    \return character an dieser Position
*/
/**************************************************************************/
inline wchar_t& TString::operator[](Int iIndex)
{
  Int iCounter = getSize();
  if (iIndex < iCounter && iIndex >= 0 && m_pWBuffer != NULL)
  {
    return m_pWBuffer[iIndex]; //NOT POSSIBLE FOR ONE IN ONE OUT
  }
  else
  {
    m_wcEmpty = 0x0000;
    return m_wcEmpty;          //NOT POSSIBLE FOR ONE IN ONE OUT
  }
}

/**************************************************************************/
/*! compares lexicographically two strings and returns true if the this
    is smaller than the parameter rInStr.
    \param rInStr : String to compare
    \retval true : this is smaller
    \retval false : else
*/
/**************************************************************************/
inline bool TString::operator<(const TString& rInStr) const
{
  return (this->compareTo(rInStr) < 0);
}

/**************************************************************************/
/*! compares lexicographically two strings and returns true if the this
    is smaller than or equals the parameter rInStr.
    \param rInStr : String to compare
    \retval true : this is smaller or equal
    \retval false : else
*/
/**************************************************************************/
inline bool TString::operator<=(const TString& rInStr) const
{
  return (this->compareTo(rInStr) <= 0);
}

/**************************************************************************/
/*! compares lexicographically two strings and returns true if the this
    is bigger than the parameter rInStr.
    \param rInStr : String to compare
    \retval true : this is bigger
    \retval false : else
*/
/**************************************************************************/
inline bool TString::operator>(const TString& rInStr) const
{
  return (this->compareTo(rInStr) > 0);
}

/**************************************************************************/
/*! compares lexicographically two strings and returns true if the this
    is bigger than or equals the parameter rInStr.
    \param rInStr : String to compare
    \retval true : this is bigger or equal
    \retval false : else
*/
/**************************************************************************/
inline bool TString::operator>=(const TString& rInStr) const
{
  return (this->compareTo(rInStr) >= 0);
}


//-----------------------------------------------------------------
// GLOBAL OPERATORS
/***************************************************************************/
/*! Global assign operator for wchar_t* and TStrings
*/
/***************************************************************************/
inline TString operator+ (wchar_t* pIn, const TString& rIn2)
{
  return (TString(pIn) + rIn2);
}

/***************************************************************************/
/*! Global equals operator for wchar_t* and IString
*/
/***************************************************************************/
inline bool operator== (const IString& rInStr1, const wchar_t* pInStr2)
{
  return (TString(pInStr2) == rInStr1);
}

/***************************************************************************/
/*! Global equals operator for wchar_t* and IString
*/
/***************************************************************************/
inline bool operator== (const wchar_t* pInStr1, const IString& rInStr2)
{
  return (TString(pInStr1) == rInStr2);
}

/***************************************************************************/
/*! Global equals operator for char* and IString
*/
/***************************************************************************/
inline bool operator== (const IString& rInStr1, const char* pInStr2)
{
  return (TString(pInStr2) == rInStr1);
}

/***************************************************************************/
/*! Global equals operator for char* and IString
*/
/***************************************************************************/
inline bool operator== (const char* pInStr1, const IString& rInStr2)
{
  return (TString(pInStr1) == rInStr2);
}

/***************************************************************************/
/*! Global unequal operator for wchar_t* and IString
*/
/***************************************************************************/
inline bool operator!=(const IString& rInStr1, const wchar_t* pInStr2)
{
  return (TString(pInStr2) != rInStr1);
}

/***************************************************************************/
/*! Global unequal operator for wchar_t* and IString
*/
/***************************************************************************/
inline bool operator!=(const wchar_t* pInStr1, const IString& rInStr2)
{
  return (TString(pInStr1) != rInStr2);
}

/***************************************************************************/
/*! Global unequal operator for char* and IString
*/
/***************************************************************************/
inline bool operator!=(const IString& rInStr1, const char* pInStr2)
{
  return (TString(pInStr2) != rInStr1);
}

/***************************************************************************/
/*! Global unequal operator for char* and IString
*/
/***************************************************************************/
inline bool operator!=(const char* pInStr1, const IString& rInStr2)
{
  return (TString(pInStr1) != rInStr2);
}

#ifdef USE_STL_BINDINGS
/***************************************************************************/
/*! shift operator
*/
/***************************************************************************/
inline void operator<<(std::string& rOutstr, const TString& rInstr)
{
  rOutstr = rInstr.c_str(NULL);
}

/***************************************************************************/
/*! shift operator
*/
/***************************************************************************/
inline void operator<<(std::wstring& rOutstr, const TString& rInstr)
{
  rOutstr = rInstr.c_bstr();
}
#endif //USE_STL_BINDINGS


END_NAMESPACE_Zeus

#endif
