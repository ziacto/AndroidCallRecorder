/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IString
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 3.11.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IString.hpp $
** 
** 30    17.04.08 8:08 Bha
** Timeval convertion implemented
** 
** 29    7.02.08 12:08 Mab
** Method clear() added.
** 
** 28    6.02.08 14:56 Mab
** IString::toBool() IString::isBool() and TString constructor for bool
** added.
** 
** 27    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 26    2.07.07 7:25 bha
** documentation of interface
** 
** 22    26.02.07 9:00 bha
** 17    9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
**
** 16    5.10.06 6:38 bha
** Stack types can hide addRef and release methods inside their interfaces
**
** 15    27.09.06 17:00 Mabbuehl
** Elimination Wide String
**
** 12    7.09.06 16:00 bha
** String mit compareTo erweitern
**
** 10    4.09.06 14:40 bha
** StringTool replaced. All methods are available in TString now.
**
** 8     28.08.06 12:01 Mabbuehl
** Conversion to char* redesigned. Retval is not a multi byte string any
** more, but a single byte string.
***************************************************************************/

#ifndef IStringHPP
#define IStringHPP

#include <zeusbase/System/Interfaces/IValueType.hpp>
#include <zeusbase/Config/PlatformDefines.hpp>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines a wide string for C++. It is used to wrapp a
    unicode string. There are converter methods for regular 8bit strings,
    numbers and float values.
    The string is NULL terminated, witch means the last character is a
    NULL-character to mark the end of the string
*/
/***************************************************************************/
class IString : public IValueType
{
  HIDE_ASSIGNMENT_OPERATOR(IString)
  
  public:
    /***********************************************************************/
    /*! returns the wide array as wchar_t-array
        \return wide array
    */
    /***********************************************************************/
    virtual const wchar_t* MQUALIFIER c_bstr() const = 0;

    /***********************************************************************/
    /*! Returns the 8bit array. This array must be converted from the 16bit.
        If the converting fails (for wide characters) this will place a '?'
        at the failure position. There  is a optional bool to capture the
        convertion error.

        \param pError [OUT]: Returns if any character could not be converted
                             without loss of information. For example, real
                             Chinese characters can not be converted to single
                             byte Ansi characters.

        \return            : 8bit array
    */
    /***********************************************************************/
    virtual const char* MQUALIFIER c_str( BOOL_ERRORRETVAL(pError) ) const = 0;

    /**************************************************************************/
    /*! this method converts a string into a float value

        \param dPreDef  [IN] : Default value
        \param pbError [OUT]:  Optional bool to capture convertion errors

        \return value
    */
    /**************************************************************************/
    virtual Float64 MQUALIFIER toFloat(Float64 dPreDef = 0.0, bool* pbError = NULL) const = 0;

    /**************************************************************************/
    /*! This method converts a string into a int value

        \param lPreDef  [IN] : Default value
        \param pbError [OUT]:  Optional bool to capture convertion errors

        \return value
    */
    /**************************************************************************/
    virtual Int32 MQUALIFIER toInt(Int32 lPreDef = 0, bool* pbError = NULL) const = 0;

    /**************************************************************************/
    /*! this method converts a string into a unsigned int value

        \param ulPredef  [IN] : Default value
        \param pbError [OUT]: Optional bool to capture convertion errors

        \return value
    */
    /**************************************************************************/
    virtual Uint MQUALIFIER toUint(Uint uiPredef = 0, bool* pbError = NULL) const = 0;

    /**************************************************************************/
    /*! this method converts a string into a time value, witch is preset to
        be 64bit

        \param tmPredef  [IN] : Default value
        \param pbError [OUT]: Optional bool to capture convertion errors

        \return value
    */
    /**************************************************************************/
    virtual Timeval MQUALIFIER toTimeval(Timeval tmPredef = 0, bool* pbError = NULL) const = 0;

    /**************************************************************************/
    /*! This method converts a string into a boolean value

        \param bPredef [IN] : Default value
        \param pbError [OUT]: Optional bool to capture conversion errors

        \return value
    */
    /**************************************************************************/
    virtual bool MQUALIFIER toBool(bool bPredef = false, bool* pbError = NULL) const = 0;

    /**************************************************************************/
    /*! Checks if the string can be converted into a float value
        \retval true : content is a float
        \retval false: content is not a float
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isFloat() const = 0;

    /**************************************************************************/
    /*! Checks if the string can be converted into a int value (o unsigned int)
        \retval true : content is a int (or unsigned int)
        \retval false: content is not a number
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isInt() const = 0;

    /**************************************************************************/
    /*! Checks if the string can be converted into a boolean value
        \retval true : content is a boolean
        \retval false: content is not a boolean
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isBool() const = 0;

    /**************************************************************************/
    /*! Checks if the string content is equal with a wide character array.
        \param pInbuffer : array to check
        \param bIgnoreCase : If this falg is set the case will be ignored
        \retval true : Content is equal
        \retval false: Inhalte is different
    */
    /**************************************************************************/
    virtual bool MQUALIFIER equals(const wchar_t* pInbuffer, bool bIgnoreCase = false) const = 0;

    /**************************************************************************/
    /*! Checks if the string content is equal with an other string object
        \param rInstr : String to check
        \param bIgnoreCase : If this falg is set the case will be ignored
        \retval true : Content is equal
        \retval false: Inhalte is different
    */
    /**************************************************************************/
    virtual bool MQUALIFIER equalsStr(const IString& rInstr, bool bIgnoreCase = false) const = 0;

    /**************************************************************************/
    /*! Concats a wide array at the end of the string
        \param pInbuffer : Wide array to add
    */
    /**************************************************************************/
    virtual void MQUALIFIER concat(const wchar_t* pInbuffer) = 0;

    /**************************************************************************/
    /*! concats an other string object at the end of the string
        \param rInstr : String to add
    */
    /**************************************************************************/
    virtual void MQUALIFIER concatStr(const IString& rInstr) = 0;

    /**************************************************************************/
    /*! assigns a wide array into the string. The old string buffer will
        be overwritten using this method.
        \param pInbuffer : wide array to assign
    */
    /**************************************************************************/
    virtual void MQUALIFIER assign(const wchar_t* pInbuffer)=0;

    /**************************************************************************/
    /*! assigns a string content to this string.
        \param rInstr : String to assign
    */
    /**************************************************************************/
    virtual void MQUALIFIER assignStr(const IString& rInstr)=0;

    /**************************************************************************/
    /*! returns the string size (without the NULL-character).
        \return string size
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getSize() const = 0;

    /**************************************************************************/
    /*! Returns an indexed wide character of the string. If the index is
        out of the array bound, this will return a NULL character
        \param iIndex : Index of the character
        \return Indexed character
    */
    /**************************************************************************/
    virtual wchar_t MQUALIFIER getChar(Int iIndex) const = 0;


    /**************************************************************************/
    /*! returns the index of the first substring found in the string
        \param pSubBuffer : wide character array as substring
        \retval -1 : Substring not found
        \retval >= 0 : Index of substring
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getFirstPos(const wchar_t* pSubBuffer)const = 0;

    /**************************************************************************/
    /*! returns the index of the first substring found in the string
        \param rSubString : substring
        \retval -1 : Substring not found
        \retval >= 0 : Index of substring
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getFirstPosStr(const IString& rSubString)const = 0;

    /**************************************************************************/
    /*! returns the index of the last substring found in the string
        \param pSubBuffer : wide character array as substring
        \retval -1 : Substring not found
        \retval >= 0 : Index of substring
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getLastPos(const wchar_t* pSubBuffer)const = 0;

    /**************************************************************************/
    /*! returns the index of the last substring found in the string
        \param rSubString : substring
        \retval -1 : Substring not found
        \retval >= 0 : Index of substring
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getLastPosStr(const IString& rSubString)const = 0;

    /**************************************************************************/
    /*! Empties / clears a string.
    */
    /**************************************************************************/
    virtual void MQUALIFIER clear() = 0;

    /**************************************************************************/
    /*! Checks if a string is empty
        \retval true : String is empty (same as strData->equals(L"") but
                       faster.
        \retval false : String contains data
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isEmpty() const = 0;

    /**************************************************************************/
    /*! Checks if the string ends with the substring pString
        \param pString : String to check
        \retval true : String ends with this sub string
        \retval false: String does not end with this substring
    */
    /**************************************************************************/
    virtual bool MQUALIFIER endsWith(const wchar_t* pString) const = 0;

    /**************************************************************************/
    /*! Checks if the string ends with the substring rString
        \param rString : String to check
        \retval true : String ends with this sub string
        \retval false: String does not end with this substring
    */
    /**************************************************************************/
    virtual bool MQUALIFIER endsWithStr(const IString& rString) const = 0;

    /**************************************************************************/
    /*! Checks if the string starts with the substring pString
        \param pString : String to check
        \retval true : String starts with this sub string
        \retval false: String does not start with this substring
    */
    /**************************************************************************/
    virtual bool MQUALIFIER startsWith(const wchar_t* pString) const = 0;

    /**************************************************************************/
    /*! Checks if the string starts with the substring rString
        \param rString : String to check
        \retval true : String starts with this sub string
        \retval false: String does not start with this substring
    */
    /**************************************************************************/
    virtual bool MQUALIFIER startsWithStr(const IString& rString) const = 0;

    /**************************************************************************/
    /*! Compares two strings lexicographically. The lexicographically
        compare depends on the locale. This takes the default locale
        \param rString : String to compare with
        \retval 0 : Strings are equal
        \retval -1: this string is smaller than the rString
        \retval 1 : this string is bigger than the rString
    */
    /**************************************************************************/
    virtual Int MQUALIFIER compareTo(const IString& rString) const=0;

    /**************************************************************************/
    /*! Returns true if the string contains a substring
        \param pSubString : Substring to check
        \retval true : Substring is contained
        \retval false:  no such substring found
    */
    /**************************************************************************/
    virtual bool MQUALIFIER contains(const wchar_t* pSubString) const=0;

    /**************************************************************************/
    /*! Returns true if the string contains a substring
        \param rSubString : Substring to check
        \retval true : Substring is contained
        \retval false:  no such substring found
    */
    /**************************************************************************/
    virtual bool MQUALIFIER containsStr(const IString& rSubString) const=0;

    //Friend classes: DO NOT CHANGE
    friend class TStringList;
    friend class TZVariant;
};

END_NAMESPACE_Zeus


#endif

