/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : String
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 17.04.08 8:16 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/String.cpp $
** 
** 73    17.04.08 8:16 Bha
** warning eliminated
** 
** 72    17.04.08 8:08 Bha
** Timeval convertion implemented
** 
** 71    14.04.08 16:52 Bha
** Bugfix for linux using errno
** 
** 70    9.04.08 14:20 Bha
** Corrected toBool method
** 
** 69    9.04.08 10:40 Mab
** Bugs corrected concering std::wstring::find returning 0 instead of npos
** in case the search string is empty.
** 
** 68    28.02.08 8:30 Mab
** Beweis in der Beschreibung von replace() verbessert.
** 
** 67    7.02.08 12:08 Mab
** operators for IString* added.
** 
** 66    6.02.08 14:56 Mab
** IString::toBool() IString::isBool() and TString constructor for bool
** added.
** 
** 65    4.02.08 7:22 Bha
** - new operators for unsigned int
** - stl bindings implemented for string and wstring
** 
** 64    29.01.08 10:53 Bha
** Compiling error of gnu compiler fixed
** 
** 63    21.01.08 11:15 Bha
** 64Bit platform supported for toInt() and toUint()
** 
** 62    21.01.08 10:52 Bha
** Error converting from Uint to int using the string. Fixed
** 
** 61    17.01.08 6:24 Bha
** Speedup string using internal member to store its size instead of
** reading each time using API function
** 
** 60    14.01.08 14:38 Bha
** Revision 0.6.0.1 of Zeus-Framework
** 
** 59    10.01.08 11:00 Mab
** formatV() implemented.
** 
** 58    9.01.08 15:24 Bha
** renamed sprintf to format 
** 
** 57    9.01.08 13:30 Bha
** sprintf methods implemented for strings
** 
** 56    15.10.07 15:20 bha
** enquote corrected and hash-function added
** 
** 55    15.10.07 13:59 Mabbuehl
** Unicode Migration.
** 
** 54    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 53    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 52    2.07.07 7:26 bha
** toUint method and documentation
** 
** 51    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
**
** 44    28.11.06 16:31 bha
** Beheben von Compilerwarnungen
**
** 41    9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
**
** 40    5.10.06 6:38 bha
** Stack types can hide addRef and release methods inside their interfaces
**
** 33    20.09.06 17:43 bha
** format method implemented
**
** 31    20.09.06 10:29 bha
** getSubString() mit iEndIndex -1: Alle Zeichen von iStartIndex bis Ende
** zurckgeben.
**
** 30    18.09.06 12:40 Mabbuehl
** Bereinigung von Borland-Release-Warnungen, wo es mï¿½lich und
** effizienter ist.
**
** 27    14.09.06 14:58 bha
** definieren von portablen primitiven Datentypen
**
** 24    7.09.06 16:00 bha
** String mit compareTo erweitern
**
** 22    7.09.06 14:44 bha
** Erweitern des Strings
**
** 19    4.09.06 14:40 bha
** StringTool replaced. All methods are available in TString now.
**
** 18    4.09.06 12:09 Mabbuehl
** Impliziter cast-Operator fr wchar_t* implementiert.
**
** 16    28.08.06 12:01 Mabbuehl
** Conversion to char* redesigned. Retval is not a multi byte string any
** more, but a single byte string.
**
** 13    20.07.06 8:28 bha
** convertDouble produces a memory overrun for values like 0.1E-99 and
** smaler -> problem solved
***************************************************************************/

#include <string.h>
#include <wchar.h>
#include <math.h>
#include <stdio.h>

#include <zeusbase/System/String.h>
#include <zeusbase/System/BitCodedValue.h>
#include <zeusbase/System/Float.h>
#include <zeusbase/System/Int.h>
#include <zeusbase/System/Hash.hpp>

#if defined(__GNUC__)
  #include <wctype.h>
  #include <errno.h>
#elif defined(ENABLE_WIN32_BINDING)
//  #include <shlwapi.h>

#endif

USING_NAMESPACE_Zeus


wchar_t TString::m_wcEmpty = 0x0000;

/**************************************************************************/
/*! Creates a wide array for the Tstring object
    \param pData : Data to assign to wide array
    \param bMyMemory : If flag is set the pData is adopted, else it will
                       copy the pData content into the wide array
*/
/**************************************************************************/
void TString::create(const wchar_t* pData, bool bMyMemory/*=false*/)
{
  m_iSize = 0;
  m_pWBuffer = NULL;
  m_pCBuffer = NULL;

  if (pData == NULL)
  {
    m_pWBuffer = new wchar_t[1];
    if (m_pWBuffer != NULL)
    {
      m_pWBuffer[0] = 0x0000;
    }
  }
  else
  {
    if (bMyMemory)
    {
      m_pWBuffer = (wchar_t*)pData;
    }
    else
    {
      assign(pData);
    }
  }
  updateSize();
}


/**************************************************************************/
/*! Creates a string out of a regular char array. The array must be NULL
    terminated
    \param pData : char array containing the data
*/
/**************************************************************************/
TString::TString(const char* pData)
{
  m_iSize = 0;
  m_pWBuffer = NULL;
  m_pCBuffer = NULL;
  create(convToWStr(pData), true);
}

/**************************************************************************/
/*! Creates a string with n-wide characters
    \param wcChar : wide character
    \param uiCount : number of repetitions
*/
/**************************************************************************/
TString::TString(wchar_t wcChar, Uint uiCount/*=1*/)
{
  wchar_t* pBuffer = new wchar_t[uiCount+1];

  for (Uint ui = 0; ui < uiCount; ++ui)
  {
    pBuffer[ui] = wcChar;
  }
  pBuffer[uiCount] = 0x0000;

  create(pBuffer, true);
}

/**************************************************************************/
/*! Creates a string with n-characters
    \param cChar : Character
    \param uiCount : number of repetitions
*/
/**************************************************************************/
TString::TString(char cChar, Uint uiCount /*=1*/)
{
  m_iSize = 0;
  m_pWBuffer = NULL;
  m_pCBuffer = NULL;
  char* pBuffer = new char[uiCount+1];

  for (Uint ui = 0; ui < uiCount; ++ui)
  {
    pBuffer[ui] = cChar;
  }
  pBuffer[uiCount] = 0x0000;

  create(convToWStr(pBuffer), true);
  delete [] pBuffer;
}

/**************************************************************************/
/*! Konstruktor.
    \param pString : String Objekt. Die Daten werden in das neue Objekt
                    kopiert.
*/
/**************************************************************************/
TString::TString(const IString* pString)
{
  if (pString == NULL)
  {
    create(NULL);
  }
  else
  {
    create(pString->c_bstr());
  }
}

/**************************************************************************/
/*! Creates a new string out of a int32 value.
    \param lValue : int32 value
*/
/**************************************************************************/
TString::TString(Int32 lValue)
{
  TString strData;
  strData.assignInt32(lValue);
  create(strData.m_pWBuffer);
}

/**************************************************************************/
/*! Creates a new string out of a int64 value.
    \param lValue : int32 value
*/
/**************************************************************************/
TString::TString(Int64 ldValue)
{
  TString strData;
  strData.assignInt64(ldValue);
  create(strData.m_pWBuffer);
}

/**************************************************************************/
/*! Creates a new string out of a int value.
    \param iValue : int value
*/
/**************************************************************************/
TString::TString(int iValue)
{
  TString strData;
  #if defined(__ZEUS32__)
    strData.assignInt32((Int32)iValue);
  #elif defined(__ZEUS64__)
    strData.assignInt64((Int64)iValue);
  #else
    #error "TString::TString(int iValue): constructor not implemented for this platform"
  #endif
  create(strData.m_pWBuffer);
}

/**************************************************************************/
/*! Creates a new string out of a unsigned int32 value.
    \param ulValue : Uint32 value
*/
/**************************************************************************/
TString::TString(Uint32 ulValue)
{
  TString strData;
  strData.assignUint32(ulValue);
  create(strData.m_pWBuffer);
}

/**************************************************************************/
/*! Creates a new string out of a unsigned long 64 value.
    \param uldValue : unsigned long 64 value
*/
/**************************************************************************/
TString::TString(Uint64 uldValue)
{
  TString strData;
  strData.assignUint64(uldValue);
  create(strData.m_pWBuffer);
}

/**************************************************************************/
/*! Creates a new string out of a unsigned int value.
    \param uiValue : unsigned int value
*/
/**************************************************************************/
TString::TString(unsigned int uiValue)
{
  TString strData;

  #if defined(__ZEUS32__)
    strData.assignUint32((Uint32)uiValue);
  #elif defined(__ZEUS64__)
    strData.assignUint64((Uint64)uiValue);
  #else
    #error "TString::TString(unsigned int uiValue): constructor not implemented for this platform"
  #endif

  create(strData.m_pWBuffer);
}

/**************************************************************************/
/*! Konstruktor.
    \param fValue : float value
*/
/**************************************************************************/
TString::TString(Float fValue)
{
  TString str = convertDouble(fValue);
  create(str.m_pWBuffer);
}


/**************************************************************************/
/*! Konstruktor.
    \param bValue : boolean value
*/
/**************************************************************************/
TString::TString(bool bValue)
{
  TString strData;
  strData.assignInt32(bValue);
  create(strData.m_pWBuffer);
}


/**************************************************************************/
/*! Konstruktor.
    \param fValue : double value
    \param uiDigits : Digits to convert
*/
/**************************************************************************/
TString::TString(Float fValue, Uint uiDigits)
{
  TString str = convertDouble(fValue, uiDigits);
  create(str.m_pWBuffer);
}

#ifdef USE_STL_BINDINGS
/***************************************************************************/
/*! contructor to take the wstring of stl
    \param rInstr : Input string
*/
/***************************************************************************/
TString::TString(const std::wstring& rInstr)
{
  create(rInstr.c_str());
}

/***************************************************************************/
/*! contructor to take the string of stl
    \param rInstr : Input string
*/
/***************************************************************************/
TString::TString(const std::string& rInstr)
{
  m_iSize = 0;
  m_pWBuffer = NULL;
  m_pCBuffer = NULL;
  create(convToWStr(rInstr.c_str()), true);
}
#endif


/**************************************************************************/
/*! \see IString::toFloat
*/
/**************************************************************************/
Float MQUALIFIER TString::toFloat( Float fPredef /* = 0.0*/,
                                   bool* pbError /* = NULL */) const
{
  Float fRetval = fPredef;
  bool bError    = true;

  if (m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000)
  {
    wchar_t* pEndptr = NULL;
    Float fResult = ::wcstod(m_pWBuffer, &pEndptr);

    if (pEndptr != NULL && *pEndptr != 0x0000)
    {
      fRetval = fPredef;
    } // pEndptr != NULL && *pEndptr != 0x0000: The conversion aborted at a specific character.
    else
    {
      fRetval = fResult;
      bError  = false;
    } // pEndptr == NULL || *pEndptr == 0x0000: The conversion did not abort at a specific character.
  } // m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000.

  if (pbError != NULL)
  {
    *pbError = bError;
  } // pbError != NULL.

  return fRetval;
}


/**************************************************************************/
/*! \see IString::toInt
*/
/**************************************************************************/
Int MQUALIFIER TString::toInt( Int iPredef /* = 0*/,
                               bool* pbError /* = NULL */) const
{
  Int iRetval = iPredef;
  bool bError  = true;

  if (m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000)
  {
    //----------------------------------------------------------------------
    //hex notation
    if (m_pWBuffer[0] == L'0' && m_pWBuffer[1] == L'x')
    {
      iRetval = static_cast<Int>(TBitCodedValue::convertHexToInt64(*this, bError, iPredef));
    }

    //----------------------------------------------------------------------
    //binary notation
    else if(m_pWBuffer[0] == L'0' && m_pWBuffer[1] == L'b')
    {
      iRetval = static_cast<Int>(TBitCodedValue::convertBinaryToInt64(*this, bError, iPredef));
    }

    //----------------------------------------------------------------------
    //regular notation
    else
    {
      wchar_t* pEndptr = NULL;
      #if defined(__ZEUS32__)
        Int iResult = ::wcstol(m_pWBuffer, &pEndptr, 10);
      #elif defined(__ZEUS64__)
        Int iResult = ::wcstoll(m_pWBuffer, &pEndptr, 10);
      #else
        #error "Unknown platform bit size for TString::toInt"
      #endif

      if (pEndptr != NULL && *pEndptr != 0x0000)
      {
        iRetval = iPredef;
      } // pEndptr != NULL && *pEndptr != 0x0000: The conversion aborted at a specific character.
      else
      {
        iRetval = iResult;

        //Overflow has happened. The return value has been saturated to LONG_MAX or LONG_MIN
        bError = (errno == ERANGE);
      } // pEndptr == NULL || *pEndptr == 0x0000: The conversion did not abort at a specific character.


      ////////////////////////////////////////////////////////////////////////////////
      //Had some problems on linux system, that this value has not been
      // reset once it has received ERANGE, even I called the wcstol function again
      // with proper data
      #if defined(ENABLE_LINUX_BINDING)
        errno = 0;
      #endif
      ////////////////////////////////////////////////////////////////////////////////

    }
  } // m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000.

  if (pbError != NULL)
  {
    *pbError = bError;
  } // pbError != NULL.

  return iRetval;
}

/**************************************************************************/
/*! \see IString::toUint
*/
/**************************************************************************/
Uint MQUALIFIER TString::toUint(Uint uiPredef /*= 0*/, bool* pbError /*= NULL*/) const
{
  Uint uiRetval = uiPredef;
  bool bError  = true;

  if (m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000)
  {
    //----------------------------------------------------------------------
    //hex notation
    if (m_pWBuffer[0] == L'0' && m_pWBuffer[1] == L'x')
    {
      uiRetval = static_cast<Uint>(TBitCodedValue::convertHexToInt64(*this, bError, uiPredef));
    }

    //----------------------------------------------------------------------
    //binary notation
    else if(m_pWBuffer[0] == L'0' && m_pWBuffer[1] == L'b')
    {
      uiRetval = static_cast<Uint>(TBitCodedValue::convertBinaryToInt64(*this, bError, uiPredef));
    }

    //----------------------------------------------------------------------
    //regular notation
    else
    {
      wchar_t* pEndptr = NULL;
      #if defined(__ZEUS32__)
        Uint uiResult = ::wcstoul(m_pWBuffer, &pEndptr, 10);
      #elif defined(__ZEUS64__)
        Uint uiResult = ::wcstoull(m_pWBuffer, &pEndptr, 10);
      #else
        #error "Unknown platform bit size for TString::toUint"
      #endif

      if (pEndptr != NULL && *pEndptr != 0x0000)
      {
        uiRetval = uiPredef;
      } // pEndptr != NULL && *pEndptr != 0x0000: The conversion aborted at a specific character.
      else
      {
        uiRetval = uiResult;

        //Overflow has happened. The return value has been saturated to ULONG_MAX or ULONG_MIN
        bError = (errno == ERANGE);
      } // pEndptr == NULL || *pEndptr == 0x0000: The conversion did not abort at a specific character.

      ////////////////////////////////////////////////////////////////////////////////
      //Had some problems on linux system, that this value has not been
      // reset once it has received ERANGE, even I called the wcstol function again
      // with proper data
      #if defined(ENABLE_LINUX_BINDING)
        errno = 0;
      #endif
      ////////////////////////////////////////////////////////////////////////////////

    }
  } // m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000.

  if (pbError != NULL)
  {
    *pbError = bError;
  } // pbError != NULL.

  return uiRetval;
}

/**************************************************************************/
/*! \see IString::toTimeval
*/
/**************************************************************************/
Timeval MQUALIFIER TString::toTimeval(Timeval tmPredef /* = 0*/,
                                      bool* pbError /* = NULL */) const
{
  Timeval tmRetval = tmPredef;
  bool bError  = true;

  if (m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000)
  {
    //----------------------------------------------------------------------
    //hex notation
    if (m_pWBuffer[0] == L'0' && m_pWBuffer[1] == L'x')
    {
      tmRetval = static_cast<Timeval>(TBitCodedValue::convertHexToInt64(*this, bError, tmPredef));
    }

    //----------------------------------------------------------------------
    //binary notation
    else if(m_pWBuffer[0] == L'0' && m_pWBuffer[1] == L'b')
    {
      tmRetval = static_cast<Timeval>(TBitCodedValue::convertBinaryToInt64(*this, bError, tmPredef));
    }

    //----------------------------------------------------------------------
    //regular notation
    else
    {
      #if defined (ENABLE_WIN32_BINDING)

        //There is no way to detect errors if the string can not be converted
        tmRetval =  static_cast<Timeval>(::_wtoi64(m_pWBuffer));
        bError = false;

      #else //not defined (ENABLE_WIN32_BINDING)

        wchar_t* pEndptr = NULL;
        Int tmResult = static_cast<Timeval>(::wcstoll(m_pWBuffer, &pEndptr, 10));

        if (pEndptr != NULL && *pEndptr != 0x0000)
        {
          tmRetval = tmPredef;
        } // pEndptr != NULL && *pEndptr != 0x0000: The conversion aborted at a specific character.
        else
        {
          tmRetval = tmResult;

          //Overflow has happened. The return value has been saturated to LONG_MAX or LONG_MIN
          bError = (errno == ERANGE);
        } // pEndptr == NULL || *pEndptr == 0x0000: The conversion did not abort at a specific character.


        ////////////////////////////////////////////////////////////////////////////////
        //Had some problems on linux system, that this value has not been
        // reset once it has received ERANGE, even I called the wcstol function again
        // with proper data
        #if defined(ENABLE_LINUX_BINDING)
          errno = 0;
        #endif
        ////////////////////////////////////////////////////////////////////////////////

      #endif //not defined (ENABLE_WIN32_BINDING)
    }
  } // m_pWBuffer != NULL && m_pWBuffer[0] != 0x0000.

  if (pbError != NULL)
  {
    *pbError = bError;
  } // pbError != NULL.

  return tmRetval;
}

/**************************************************************************/
/*! \see IString::toBool
*/
/**************************************************************************/
bool MQUALIFIER TString::toBool(bool bPredef /* = false */, bool* pbError /* = NULL */) const
{
  bool bError = false;  
  bool bRetval = (toInt(bPredef, &bError) != 0);

  if (bError)
  {
    const TString strLower = toLowerCase();

    if (strLower == L"true")
    {
      bError = false;
      bRetval = true;
    } // strLower == L"true".
    else if (strLower == L"false")
    {
      bError = false;
      bRetval = false;
    } // strLower == L"false".
  } // bError.

  if (pbError != NULL)
  {
    *pbError = bError;
  } // pbError != NULL.
  return bRetval;
}


/**************************************************************************/
/*! \see IString::equals
*/
/**************************************************************************/
bool MQUALIFIER TString::equals(const wchar_t* pInbuffer, bool bIgnoreCase /*= false*/) const
{
  bool bRetval = false;

  if (m_pWBuffer == pInbuffer)
  {
    bRetval = true;
  }
  else if (pInbuffer == NULL)
  {
    bRetval = isEmpty();
  }
  else if (m_pWBuffer != NULL)
  {
    if(bIgnoreCase)
    {
      #if defined(__GNUC__)
        bRetval = (::wcscasecmp(m_pWBuffer, pInbuffer) == 0);
      #else
        bRetval  = (::_wcsicmp(m_pWBuffer, pInbuffer) == 0);
      #endif
    }
    else
    {
      bRetval = (wcscmp(m_pWBuffer, pInbuffer)==0);
    }
  }
  return bRetval;
}

/**************************************************************************/
/*! \see IString::concat
*/
/**************************************************************************/
void MQUALIFIER TString::concat(const wchar_t* pInbuffer)
{
  if (pInbuffer != NULL)
  {
    //Erstellen des neuen Buffers
    size_t size1 = 0;
    if (m_pWBuffer != NULL)
    {
      size1 = wcslen(m_pWBuffer);
    }

    size_t size2 = wcslen(pInbuffer)+1;
    wchar_t* pNewbuffer = new wchar_t[size1+size2];
    if (pNewbuffer != NULL)
    {
      if (m_pWBuffer != NULL)
      {
        wcscpy(pNewbuffer,m_pWBuffer);
      }
      else
      {
        wcscpy(pNewbuffer,L"");
      }

      wcscat(pNewbuffer,pInbuffer);
      this->assign(pNewbuffer);
      delete [] pNewbuffer;
    }
  }
}

/**************************************************************************/
/*! \see IString::assign
*/
/**************************************************************************/
void MQUALIFIER TString::assign(const wchar_t* pInbuffer)
{
  if (pInbuffer != m_pWBuffer)
  {
    this->clearBuffers();
    if (pInbuffer != NULL)
    {
      size_t size = wcslen(pInbuffer)+1;
      if (size > 0)
      {
        m_pWBuffer = new wchar_t[size];
        if (m_pWBuffer != NULL)
        {
          wcscpy(m_pWBuffer,pInbuffer);
        }
      }
      else
      {
        m_pWBuffer = new wchar_t[1];
        if (m_pWBuffer != NULL)
        {
          m_pWBuffer[0] = 0x0000;
        }
      }
    }
    else
    {
      m_pWBuffer = new wchar_t[1];
      if (m_pWBuffer != NULL)
      {
        m_pWBuffer[0] = 0x0000;
      }
    }
  }
  updateSize();
}

/******************************************************************************/
/*! Die Suche nach dem SubString wurde nach dem Knuth-Morris-Pratt
    Verfahren implementiert. In einem Preprocessing-Verfahren wird
    aus dem gesuchten SubString eine Sprungtabelle erstellt. Je nach dem,
    wieviele Zeichen bei der Suche uebereinstimmten, kann direkt eine
    bestimmte Distanz gesprungen werden, falls das darauffolgende Zeichen
    nicht uebereinstimmt.                                               <BR>
                                                                        <BR>
    Preprocessing Algorithmus:                                          <BR>
    Initialisiere die Tabelle mit Sprungweite 1                         <BR>
    Initialisiere die Vergleichsvariable k mit 0                        <BR>
    Wiederhole solange bis Ende des SubStrings erreicht
      - Falls das Zeichen[i] ungleich Zeichen[k] ist dann
        Setze die Sprungweite[i+1] = i+1
      - Sonst setze Sprungweite[i+1] = Sprungweite[i] und wenn
        i groesser als 0 ist dann inkrementiere k um eins               <BR>
                                                                        <BR>
    \see IString::getFirstPos
*/
/******************************************************************************/
Int MQUALIFIER TString::getFirstPos(const wchar_t* pSubBuffer)const
{
  if (pSubBuffer != NULL && m_pWBuffer != NULL)
  {
    Int i;
    Int iBaseCount = getSize();
    Int iSubCount = wcslen(pSubBuffer);

    //long iSubCount = rSubString.getSize();
    //wchar_t* pSubBuffer = rSubString.c_bstr();

    if (iSubCount == 0)
    {
      return -1;
    }


    //--------------------------------------------------------------------
    //Preprozessing nach Knuth-Morris-Pratt Verfahren
    Int* pJumpArray = new Int[iSubCount];
    Int k = 0;
    pJumpArray[0] = 1; //Initialisieren des Grundspringens

    for(i = 0; i < iSubCount-1; i++)
    {
      if (pSubBuffer[i] != pSubBuffer[k])
      {
        pJumpArray[i+1] = i+1;    //Setzen der Sprungweite
        k = 0;                    //Zuruecksetzen der Pruefposition
      }

      //Anpassen der Sprungweite, weil Pruefposition gleich dem Char. ist
      else
      {
        if (i >0)
        {
          k++;
        }
        pJumpArray[i+1] = pJumpArray[i];
      }
    }


    //--------------------------------------------------------------------
    //Nach SubString suchen
    for (i = 0; i <= iBaseCount-iSubCount;)
    {
      Int iPos = i;
      while(iPos-i < iSubCount && pSubBuffer[iPos-i] == m_pWBuffer[iPos])
      {
        iPos++;
        if (pSubBuffer[iPos-1-i] == m_pWBuffer[iPos-1] && iPos-i == iSubCount)
        {
          delete [] pJumpArray;
          return i;
        }
      }
      i += pJumpArray[iPos-i];  //Optimierung: Sprung nach vorne
    }

    delete [] pJumpArray;
  }
  return -1;
}


/**************************************************************************/
/*! \see IString::getLastPos
*/
/**************************************************************************/
Int MQUALIFIER TString::getLastPos(const wchar_t* pSubBuffer)const
{
  Int iRetval = -1;
  if (pSubBuffer != NULL && m_pWBuffer != NULL)
  {
    Int iBaseCount = getSize();
    Int iSubCount = wcslen(pSubBuffer);
    if (iSubCount != 0 && iBaseCount != 0 && iBaseCount >= iSubCount)
    {
      // iCompareIndex : Start index (right of the string)
      // wcStartChar : right start character of the substring
      // bFound : Flag if the substring has been found
      Int iCompareIndex = iBaseCount-1;
      wchar_t wcStartChar = pSubBuffer[iSubCount-1];
      bool bFound = false;


      // Loop as long as the substring has not been found and the
      // iCompareIndex is larger than the Substring index
      while (!bFound && iCompareIndex  >= iSubCount-1)
      {

        //The maximum of the backward jump
        Int iMaxJump = 0;
        bool bJumpIndexFixed = false;


        //Loop as long as the characters are the same and the index is
        // smaller than the number of characters of the substring
        Int iIndex = -1;
        do
        {
          ++iIndex;

          //make sure iIndex is not zero
          if(iIndex < iSubCount &&
             iIndex > 0 &&
             m_pWBuffer[iCompareIndex-iIndex] == wcStartChar &&
             !bJumpIndexFixed)
          {
            iMaxJump = iIndex;
            bJumpIndexFixed = true;
          }
          else
          {
            ++iMaxJump;
          }
        }
        while(iIndex < iSubCount &&
              m_pWBuffer[iCompareIndex-iIndex] == pSubBuffer[iSubCount-1 - iIndex]);

        // if the index reached the end -> substring found at position
        // iCompareIndex - iSubCount
        bFound = (iIndex == iSubCount);

        // if not found, jump to the next search position
        if (!bFound)
        {
          iCompareIndex -= iMaxJump;
        }
        else
        {
          iRetval = iCompareIndex - iSubCount + 1;
        }
      } //(!bFound && iCompareIndex  >= 0)
    } //(iSubCount != 0)
  }
  return iRetval;
}

/**************************************************************************/
/*! \see IString::endsWithStr
*/
/**************************************************************************/
bool MQUALIFIER TString::endsWithStr(const IString& rString) const
{
  Int iEndPos = this->getSize()-1;
  Int iStartPos = iEndPos - rString.getSize()+1;
  return (getSubString(iStartPos, iEndPos) == rString);
}

/**************************************************************************/
/*! \see IString::startsWithStr
*/
/**************************************************************************/
bool MQUALIFIER TString::startsWithStr(const IString& rString) const
{
  Int iEndPos = rString.getSize()-1;
  Int iStartPos = 0;
  return (getSubString(iStartPos, iEndPos) == rString);
}

/**************************************************************************/
/*! \see IString::compareTo
*/
/**************************************************************************/
Int MQUALIFIER TString::compareTo(const IString& rString) const
{
  return wcscmp(m_pWBuffer, rString.c_bstr());
}

/**************************************************************************/
/*! Checks if a char of an array of chars is contained by the string.
    Special case is handled if the set of chars is empty. The empty set is
    always a part of each set.
    \param wcChars : array of chars to check (null terminated)
    \retval true : char found
    \retval false: No such char found
*/
/**************************************************************************/
bool TString::containsCharOf(const wchar_t* wcChars) const
{
  bool bRetval = false;
  Int iSubSize = TString(wcChars).getSize();
  if (iSubSize > 0)
  {
    for(Int i = 0; i < iSubSize && !bRetval; i++)
    {
      bRetval = this->containsChar(wcChars[i]);
    }
  }
  else
  {
    bRetval = true;
  }
  return bRetval;
}

/**************************************************************************/
/*! Returns the position index of a character inside the string
*/
/**************************************************************************/
Int TString::indexOf(wchar_t wcChar) const
{
  Int iRetval = -1;
  Int iSize = this->getSize();
  for(Int i = 0; i < iSize && iRetval < 0; i++)
  {
    if (this->m_pWBuffer[i] == wcChar)
    {
      iRetval = i;
    }
  }
  return iRetval;
}

/**************************************************************************/
/*! Ermitteln des Substring
    \param iStartIndex : Start index
    \param iEndIndex : end index
    \return substring
*/
/**************************************************************************/
TString TString::getSubString(Int iStartIndex, Int iEndIndex /*= LONG_MAX*/) const
{
  TString strRetval;

  Int iSize = getSize();
  if (iEndIndex >= iSize)
  {
    iEndIndex = iSize-1;
  }

  if (iStartIndex < 0)
  {
    iStartIndex = 0;
  }

  if (iStartIndex <= iEndIndex && m_pWBuffer != NULL)
  {
    Int iCount = iEndIndex - iStartIndex + 1;
    wchar_t* wBuffer = new wchar_t[iCount+1];
    if (wBuffer != NULL)
    {
      ::wmemcpy(wBuffer, m_pWBuffer+iStartIndex, iCount);
      wBuffer[iCount] = L'\0';
      strRetval = wBuffer;
      delete [] wBuffer;
    }
  }
  return strRetval;
}

/**************************************************************************/
/*! returns the result of a substring remove.
    \param iStartIndex : Start index
    \param iEndIndex : end index
    \return new string
*/
/**************************************************************************/
TString TString::deleteSubString(Int iStartIndex, Int iEndIndex /*= LONG_MAX*/) const
{
  TString strRetval;
  if (iStartIndex <= iEndIndex && m_pWBuffer != NULL)
  {
    //get starting string
    if (iStartIndex > 0)
    {
      strRetval = getSubString(0,iStartIndex-1);
    }

    //get ending string
    Int iLastIndex = this->getSize()-1;
    if (iEndIndex < iLastIndex)
    {
      strRetval += getSubString(iEndIndex+1, iLastIndex);
    }
  }
  else
  {
    strRetval = this;
  }
  return strRetval;
}

/******************************************************************************/
/*! Converts the string content to upper case letters
    \return converted string
*/
/******************************************************************************/
TString TString::toUpperCase() const
{
  #if defined(__GNUC__)
    const wchar_t* pBuffer = this->c_bstr();
    Int iSize = this->getSize();
    wchar_t* pNewBuffer = new wchar_t[iSize+1];

    for(Int i = 0; i < iSize+1; i++)
    {
      pNewBuffer[i] = ::towupper(pBuffer[i]);
    }
    pNewBuffer[iSize] = L'\0';
    TString strRet(pNewBuffer);
    delete [] pNewBuffer;

    return strRet;
  #else
    return ::_wcsupr(TString(this).m_pWBuffer);
  #endif
}

/******************************************************************************/
/*! Converts the string content to lower case letters
    \return converted string
*/
/******************************************************************************/
TString TString::toLowerCase() const
{
  #if defined(__GNUC__)
    const wchar_t* pBuffer = this->c_bstr();
    Int iSize = this->getSize();
    wchar_t* pNewBuffer = new wchar_t[iSize+1];

    for(Int i = 0; i < iSize+1; i++)
    {
      pNewBuffer[i] = ::towlower(pBuffer[i]);
    }
    pNewBuffer[iSize] = L'\0';
    TString strRet(pNewBuffer);
    delete [] pNewBuffer;

    return strRet;
  #else
    return ::_wcslwr(TString(this).m_pWBuffer);
  #endif
}


/******************************************************************************/
/*! This method counts the substrings of this string
    \param strSubstring : Substring
    \return number of times this substring occures in this string
*/
/******************************************************************************/
Int TString::getSubStringCount(const IString& rSubstring) const
{
  Int iCount = 0;

  if (!rSubstring.isEmpty()) // Important: std::wstring::find returns 0 for an empty sub string, not npos.
  {                          //            Otherwise the while below won't end.
    Int iStartPos = 0;
    std::wstring strData(this->c_bstr());
    std::wstring strSub(rSubstring.c_bstr());

    Int iFindPos  = strData.find(strSub, iStartPos);

    while (iFindPos != (Int) std::wstring::npos)
    {
      ++iCount;
      iStartPos = iFindPos + strSub.length();
      iFindPos  = strData.find(strSub, iStartPos);
    } // while (iFindPos != (Int) std::wstring::npos).
  } // !rSubstring.isEmpty().

  return iCount;
}


/**************************************************************************/
/*! inserts a string at the position index and returns the new string
    \param iIndex : position index to insert the string
    \param rStrToInsert : String to insert
    \return new string
*/
/**************************************************************************/
TString TString::insert(Int iIndex, const IString& rStrToInsert) const
{
  TString strRetval;
  Int iSize = this->getSize();
  if (iIndex >= 0 && iIndex <= iSize)
  {
    strRetval = getSubString(0, iIndex-1);
    strRetval += rStrToInsert;

    if (iIndex < iSize)
    {
      strRetval += getSubString(iIndex);
    }
  }
  else
  {
    strRetval = this;
  }
  return strRetval;
}


/******************************************************************************/
/*! This is the internal helper method for replacing a substring inside
    this string. A sequence at position iPos of lCharsToRemove bytes will be
    removed first and then the strReplace will be inserted.
*/
/******************************************************************************/
/*static*/ void TString::replace_internal(std::wstring& rData,
                                          Int iPos,
                                          Int iCharsToRemove,
                                          const std::wstring& rReplace)
{
  rData.erase(iPos, iCharsToRemove);

  if (!rReplace.empty())
  {
    rData.insert(iPos, rReplace);
  }
}

/******************************************************************************/
/*! This method replaces a substring with a new string. It can also be used
    just for removing a substring by calling this method with an empty
    strReplace variable.
    \param rToRemove : Substring to remove
    \param rReplace : String for replaceing
    \return new string
*/
/******************************************************************************/
TString TString::replaceFirst(const IString& rToRemove, const IString& rReplace) const
{
  TString strRetval;

 // Important to check !rToRemove.isEmpty(): std::wstring::find returns 0 for an empty sub string, not npos.
 // Otherwise rReplace will be inserted at the beginning, which is incorrect.
  if (!isEmpty() && !rToRemove.isEmpty() && !rToRemove.equalsStr(rReplace))
  {
    std::wstring strWholeString(c_bstr());
    std::wstring strRem(rToRemove.c_bstr());
    std::wstring strRep(rReplace.c_bstr());

    Int iPos = strWholeString.find(strRem);
    if (iPos != (Int) std::wstring::npos)
    {
      replace_internal(strWholeString, iPos, strRem.length(), strRep);
      strRetval = strWholeString.c_str();
    }
    else
    {
      strRetval = c_bstr();
    }
  }
  else
  {
    strRetval = c_bstr();
  }
  return strRetval;
}


/*****************************************************************************/
/*! This method works like replace() but it will
    replace all substrings inside this string.

    \param rToRemove : Substring to remove
    \param rReplace  : String for replacing
    \param pReplaces : If pointer is valid, the number of replaces are returned
    \return new string
*/
/*****************************************************************************/
/*

    Aufruf                            | Wirkung
    ---------------------------------------------------------------
    BBA mit replaceAll(BA, A)         | BBA (Pos=1) => BA (Pos=0) => A
                                      |
    AAB mit replaceAll(AB, BA)        | AAB (Pos=1) => ABA (Pos=0) => BAA
                                      |
    AAB mit replaceAll(AB, BAA)       | AAB (Pos=1) => ABAA (Pos=0) => BAAAA
                                      |
    4 Spaces mit                      |
      replaceAll(1 Space, 2 Spaces)   | 8 Spaces
                                      |
    4 Spaces mit                      |
      replaceAll(2 Spaces, 1 Space)   | 1 Space


    Algorithmus
    -----------
    Falls strToRemove in strReplace enthalten ist, wuerde bei wiederholtem
    Ersetzen ein Loop ad infinitum entstehen. Beispiel:

    A, A, AB: A => AB => ABB => ABBB => ABBBB ...

    In obigen Beispielen ist dies nur beim vierten der Fall. Hier muss immer
    erst hinter dem Ersatzstring weitergesucht werden.

    Bei den anderen Beispielen jedoch muss immer wieder von Anfang an gesucht
    werden (insbesondere: erstes bis drittes Beispiel.)

    Beweis fuer:
    strToRemove ist nicht in strReplace enthalten => kein unendlicher Loop:

    Fall 1: strToRemove ist laenger als strReplace:
            => Ersetzung ist kuerzend => Bearbeitung ist endlich

    Fall 2: strToRemove ist gleich lang wie oder kuerzer als strReplace.
            Setze a := |rToRemove|,  b := |rReplace|,  s := |*this|
            
            Betrachte den kleinstmoeglichen Matchindex (unter der Bedingung,
            dass strToRemove nicht in strReplace enthalten ist):
            1. Ersetzung: 0
            2. Ersetzung: b – a + 1 (ueberlege an Beispiel mit b = 5, a = 3)
            n. Ersetzung: Index_Match(n):=(n-1)*(b-a+1)

            Betrachte die Stringlaenge nach n Ersetzungen: s(n) = s + n(b-a)

            s(n) waechst weniger stark als Index_Match(n). Damit wird
            Index_Match(n) s(n) ueberholen, so dass keine weitere Ersetzung
            mehr moeglich ist. Damit ist der Beweis eigentlich abgeschlossen.
            Doch wann genau bricht die Rekursion spaetestens ab?

            Genau wenn Index_Match(n+1) >= s(n) ist: Index_Match(n+1)=n*(b-a+1)

            Vergleich: n*(b-a+1) >= s+n(b-a)   <=>   n >= s

            also nach spaetestens s Ersetzungen, q.e.d.                      */
/*****************************************************************************/
TString TString::replace(const IString& rToRemove, const IString& rReplace, Int* pReplaces/* = NULL*/) const
{
  TString strRetval;
  TString strTmpToRemove(rToRemove);
  long iReplaces = 0;
  
  // Important to check !rToRemove.isEmpty(): std::wstring::find returns 0 for an empty sub string, not npos.
  // Otherwise the while below won't end.
  if (!isEmpty() && !rToRemove.isEmpty() && !strTmpToRemove.equalsStr(rReplace))
  {
    std::wstring strWholeString(c_bstr());
    std::wstring strRem(rToRemove.c_bstr());
    std::wstring strRep(rReplace.c_bstr());

    bool bInfiniteRecursion = (TString(rReplace).getSubStringCount(strTmpToRemove) > 0);

    Int iPos = strWholeString.find(strRem);

    while (iPos != (Int) std::wstring::npos)
    {
      replace_internal(strWholeString,iPos,strRem.length(), strRep);

      ++iReplaces;

      if (bInfiniteRecursion)
      {
        iPos = strWholeString.find(strRem, iPos + strRep.length());
      } // bInfiniteRecursion.
      else
      {
        iPos = strWholeString.find(strRem);
      } // !bInfiniteRecursion.
    } // while (iPos != string::npos).

    strRetval = strWholeString.c_str();
  } // !isEmpty() && !rToRemove.isEmpty() && !strTmpToRemove.equalsStr(rReplace).
  else
  {
    strRetval = c_bstr();
  } // isEmpty() || rToRemove.isEmpty() || strTmpToRemove.equalsStr(rReplace).

  if (pReplaces != NULL)
  {
    *pReplaces = iReplaces;
  } // pReplaces != NULL.

  return strRetval;
}

/**************************************************************************/
/*! This method returns the hash of the unicode string
*/
/**************************************************************************/
Int64 TString::getHash() const
{
  return THash<wchar_t>::getHash64(m_pWBuffer, this->getSize());
}



/**************************************************************************/
/*! sets a formated string using the standard C formatting of string.
    See also std::vsprintf and std::vwsprintf
*/
/**************************************************************************/
/*static*/ TString TString::formatV(const char* pcFormat, va_list Arg)
{
  char cBuffer[1025];
  
  #ifdef _MSC_VER
    Int iChars = _vsnprintf(cBuffer, 1024, pcFormat, Arg);
  #else
    Int iChars = vsnprintf(cBuffer, 1024, pcFormat, Arg);
  #endif

  if (iChars < 0)
  {
    iChars = 0;
  }
  cBuffer[iChars] = 0x00;
  return TString(cBuffer);
}

/**************************************************************************/
/*! sets a formated string using the standard C formatting of string.
    See also std::vsprintf and std::vwsprintf
*/
/**************************************************************************/
/*static*/ TString TString::formatV(const wchar_t* pwcFormat, va_list Arg)
{
  wchar_t wcBuffer[1025];

  #ifdef _MSC_VER
    Int iChars = _vsnwprintf(wcBuffer, 1024, pwcFormat, Arg);
  #elif defined(ENABLE_LINUX_BINDING)
    Int iChars = vswprintf(wcBuffer, 1024, pwcFormat, Arg);
  #else
    Int iChars = vsnwprintf(wcBuffer, 1024, pwcFormat, Arg);
  #endif

  if (iChars < 0)
  {
    iChars = 0;
  }
  wcBuffer[iChars] = 0x0000;
  return TString(wcBuffer);
}

/**************************************************************************/
/*! sets a formated string using the standard C formatting of string.
    See also std::vsprintf and std::vwsprintf
*/
/**************************************************************************/
/*static*/ TString TString::formatV(const IString& rFormat, va_list Arg)
{
  wchar_t wcBuffer[1025];
  #ifdef _MSC_VER
    Int iChars = _vsnwprintf(wcBuffer, 1024, rFormat.c_bstr(), Arg);
  #elif defined(ENABLE_LINUX_BINDING)
    Int iChars = vswprintf(wcBuffer, 1024, rFormat.c_bstr(), Arg);
  #else
    Int iChars = vsnwprintf(wcBuffer, 1024, rFormat.c_bstr(), Arg);
  #endif

  if (iChars < 0)
  {
    iChars = 0;
  }
  wcBuffer[iChars] = 0x0000;
  return TString(wcBuffer);
}

/**************************************************************************/
/*! Converts a float value into a string value using a special format
    \see TFloat::format
*/
/**************************************************************************/
/*static*/ TString TString::formatFloat( Float fValue,
                                         Float fRoundPrecision /*= 0*/,
                                         Uint uiTailingZeros /*= 0*/,
                                         Uint uiLeadingZeros /*= 1*/)
{
  return TFloat(fValue).format(fRoundPrecision, uiTailingZeros, uiLeadingZeros);
}

/**************************************************************************/
/*! Converts a int value into a string value using a special format
    \see TFloat::format
*/
/**************************************************************************/
/*static*/ TString TString::formatInt(    Int iValue,
                                          Uint uiLeadingZeros)
{
  return TInt(iValue).format(uiLeadingZeros);
}


/**************************************************************************/
/*! Converts a array of bytes to a string
    \param rList : Byte array to convert into a string
    \return Converted string data
    \note The byte array might contain simple character data or
          16bit UNICODE data. If UNICODE data is stored the header 0xFFFE
          is needed (1st and 2nd byte).
*/
/**************************************************************************/
/*static*/ TString TString::transcode(const IByteArray& rList)
{
  TString strRetval;
  Int iCount = rList.getCount();
  if (iCount > 0)
  {
    //--------------------------------------------------------------------
    // transcode from wide character based array (16bit)
    if ((Uint8)rList.getItemConst(0) == 0xFF &&
        (Uint8)rList.getItemConst(1) == 0xFE)
    {
      iCount /= 2;
      Uint16* pusBuffer = new Uint16[iCount+1];
      memset(pusBuffer, 0, sizeof(Uint16) * (iCount+1));
      memcpy(pusBuffer, rList.getArray() + 2, sizeof(Uint16) * iCount);
      Int iWideSize = sizeof(wchar_t);

      //--------------------------------------------------
      //If wide size if bigger than 2 bytes -> copy manually
      if (iWideSize > 2)
      {
        wchar_t* pwcBuffer = new wchar_t[iCount+1];
        for(Int i = 0; i < iCount; i++)
        {
          pwcBuffer[i] = pusBuffer[i];
        }
        strRetval = pwcBuffer;
        delete [] pwcBuffer;
      }

      //--------------------------------------------------
      //Uint16 size equals wchar_t size -> cast and assign
      else
      {
        strRetval = (wchar_t*)pusBuffer;
      }
      delete [] pusBuffer;
    }

    //--------------------------------------------------------------------
    // transcode from character based array
    else
    {
      char* pBuffer = new char[iCount+1];
      memset(pBuffer, 0, sizeof(char)*(iCount+1));
      memcpy(pBuffer, rList.getArray(), sizeof(char)*iCount);
      strRetval = pBuffer;
      delete [] pBuffer;
    }
  }
  return strRetval;
}

/**************************************************************************/
/*! Converts a string into a array of bytes
    \param rValue : String value to convert into a byte array
    \param bAsWideChar : Flag if the byte array will represent the ISO
                         or UNICODE data of the string. True means UNICODE.
    \return Byte array
    \note The TString::transcode() method does only support the 2 Byte
          data of UNICODE.
          This will convert the wchar_t-Data if the sizeof(wchar_t) is
          bigger than 2 Bytes.
*/
/**************************************************************************/
/*static*/ TByteArray TString::transcode(const IString& rValue, bool bAsWideChar)
{
  Int iCount = rValue.getSize() + 1; // + 1 for ending with NULL
  
  if (bAsWideChar)
  {
    ++iCount;    // for autodetect 0xFFFE (little endian)
    iCount *= 2;
  } // bAsWideChar.

  TByteArray array(iCount);

  if (bAsWideChar)
  {
    Int iWideSize = sizeof(wchar_t);

    //Add header
    array.add(static_cast<unsigned char>(0xFF));
    array.add(static_cast<unsigned char>(0xFE));

    //-----------------------------------------
    // wide characters are bigger than 2 bytes
    if (iWideSize > 2)
    {
      Int iStringSize = rValue.getSize();
      Uint16* pusBuffer = new Uint16[iStringSize+1];
      
      for(Int i = 0; i < iStringSize; i++)
      {
        pusBuffer[i] = rValue.getChar(i);
      }

      array.appendArray((char*)pusBuffer, (iStringSize+1)*sizeof(Uint16));
      delete [] pusBuffer;
    } // iWideSize > 2.

    //-----------------------------------------
    // wide character size is two byte
    else
    {
      array.appendArray((char*)rValue.c_bstr(), iCount - 2);
    } // iWideSize <= 2.

    //Ending of the data
    array[iCount - 1] = 0x00;
    array[iCount - 2] = 0x00;
  } // bAsWideChar.
  else
  {
    array.setArray(rValue.c_str(NULL), iCount);
    array[iCount - 1] = 0x00;
  } // !bAsWideChar.
  
  return array;
}

/**************************************************************************/
/*! This method trims the string. All leading or ending characters listed
    in parameter rChars are removed
    \param rSource : Source string
    \param rChars : List of characters to remove
    \param bLeft : Flag if the left side must be trimmed
    \param bRight : Flag if the right side must be trimmed

    \return trimmed string
*/
/**************************************************************************/
/*static*/ TString TString::trimExt(const IString& rSource,
                                    const IString& rChars,
                                    bool bLeft /*= true*/,
                                    bool bRight /*= true*/)
{
  TString strTest(rSource);
  wchar_t* pBuffer = strTest.m_pWBuffer;
  const wchar_t* pSkipChars = rChars.c_bstr();

  Int iSize = rSource.getSize();
  Int iSkipSize = rChars.getSize();
  Int iIndex = 0;

  //trim left
  if(bLeft)
  {
    bool bBreak = false;
    while (!bBreak && iIndex < iSize)
    {
      Int iSkipIndex = 0;
      bool bFound = false;
      while(!bFound && iSkipIndex < iSkipSize)
      {
        bFound = (pSkipChars[iSkipIndex] == pBuffer[iIndex]);
        iSkipIndex++;
      }
      if (bFound)
      {
        iIndex++;
      }
      else
      {
        bBreak = true; //Stop searching for skip characters, if none has been found
      }
    }

    //Has any skipped?
    pBuffer += iIndex;
    iSize -= iIndex;
  }

  //trim right
  if(bRight)
  {
    bool bBreak = false;
    iIndex = iSize-1;
    while (!bBreak && iIndex >= 0)
    {
      Int iSkipIndex = 0;
      bool bFound = false;
      while(!bFound && iSkipIndex < iSkipSize)
      {
        bFound = (pSkipChars[iSkipIndex] == pBuffer[iIndex]);
        iSkipIndex++;
      }
      if (bFound)
      {
        iIndex--;
      }
      else
      {
        bBreak = true; //Stop searching for skip characters, if none has been found
      }
    }

    //Has any skipped?
    if (iIndex < iSize-1)
    {
      pBuffer[iIndex+1] = 0x0000; //Mark the following character as NULL
    }
  }

  return TString(pBuffer);
}

/**************************************************************************/
/*! Loeschen aller Buffer Objekte
*/
/**************************************************************************/
void TString::clearBuffers()
{
  clearCBuffer();
  clearWBuffer();
}

/**************************************************************************/
/*! Loeschen des char-Buffers
*/
/**************************************************************************/
void TString::clearCBuffer() const
{
  if (m_pCBuffer != NULL)
  {
    delete [] m_pCBuffer;
    m_pCBuffer = NULL;
  }
}

/**************************************************************************/
/*! Loeschen des wchar_t-Buffers
*/
/**************************************************************************/
void TString::clearWBuffer()
{
  if (m_pWBuffer != NULL)
  {
    delete [] m_pWBuffer;
    m_pWBuffer = NULL;
  }
  m_iSize = 0;
}


/**************************************************************************/
/*! Konvertieren eines char_Array in ein WChar_Array
    \param pData : Char_Array
*/
/**************************************************************************/
wchar_t* TString::convToWStr(const char* pData)
{
  this->clearWBuffer();
  if (pData != NULL)
  {
    size_t size1 = strlen(pData)+1;
    m_pWBuffer = new wchar_t[size1];
    if (m_pWBuffer != NULL)
    {
      mbstowcs( m_pWBuffer, pData, size1);
    }
  }
  else
  {
    m_pWBuffer = new wchar_t[1];
    if (m_pWBuffer != NULL)
    {
      m_pWBuffer[0] = 0x0000;
    }
  }
  updateSize();
  return m_pWBuffer;
}

/**************************************************************************/
/*! Konvertieren eines wchar_Array in ein char_Array

    \param pData   [IN] : wchar_Array
    \param pError [OUT]: Return error code

    \retval            : char_Array                                       */
/**************************************************************************/
char* TString::convToCStr(const wchar_t* pData, bool* pError) const
{
  bool bError = true;

  clearCBuffer();

  if (pData != NULL)
  {
    size_t size = ::wcslen(pData) + 1;
    m_pCBuffer = new char[size];

    if (m_pCBuffer != NULL)
    {
      ::memset(m_pCBuffer, 0, size);

      bError = false; // New default.

      for (unsigned int uiWideCharIndex = 0; uiWideCharIndex < size - 1; ++uiWideCharIndex)
      {
        wchar_t wc = pData[uiWideCharIndex];

        char c1 = (char) (wc & 0x00FF); // Note: By using these hex masks, the code is independent
                                        //       from little and big endian memory encoding.

        if ((wc & 0xFF00) == 0)
        {
          m_pCBuffer[uiWideCharIndex] = c1;
        } // (wc & 0xFF00) == 0.
        else
        {
          bError = true;
          m_pCBuffer[uiWideCharIndex] = '?';
        } // (wc & 0xFF00) != 0.
      } // Loop over all wide characters of the data array.
    } // m_pCBuffer != NULL.
  } // data != NULL.

  if (pError != NULL)
  {
    *pError = bError;
  } // pError != NULL.

  return m_pCBuffer;
}

/*****************************************************************************/
/*! Konvertieren eines Doublewerts in einen StString
    \param fValue : double Wert
    \param iDigit : Number of digits
    \return Formatierter String
*/
/*****************************************************************************/
/*static*/ TString TString::convertDouble(const Float fValue, Int iDigit /*=15*/)
{
  TString str;
  int iSign = 0;
  int iDecimal = 0;
  int ndig = iDigit;
  Float64 dTemp = ::fabs(fValue);

  char* pFromBuffer = new char[100];
  /*char* pToBuffer = new char[100];*/

  if (pFromBuffer != NULL)
  {
    pFromBuffer = ::strcpy(pFromBuffer, ecvt(dTemp, ndig, &iDecimal, &iSign));

    ///////////////
    //Creates the target array according to the iDecimal point position
    Int iToBufferSize = 100;
    if (abs(iDecimal) > iToBufferSize)
    {
      iToBufferSize = abs(iDecimal)+100;
    }
    char* pToBuffer = new char[iToBufferSize];
    ::memset(pToBuffer,'0',iToBufferSize * sizeof(char));
    ///////////////

    if (fValue < 0.0)
    {
      iSign = 1;
    }
    else
    {
      iSign = 0;
    }

    const Int iFromLength = strlen(pFromBuffer);
    Int iFromIndex = iFromLength - 1;
    Int iToLength = strlen(pFromBuffer);
    bool bHasDecimal = false;

    //Dezimalpunkt wird gesetzt
    if (iDecimal < iFromLength)
    {
      //Trimmen der Laenge
      long lTrimIndex = iFromLength-1;
      while(pFromBuffer[lTrimIndex] == '0' && lTrimIndex > 0 && lTrimIndex >= iDecimal)
      {
        --lTrimIndex;
      }
      if (lTrimIndex == iDecimal-1)
      {
        iToLength = lTrimIndex+1;
        iFromIndex = lTrimIndex;
      }
      else if (iDecimal <= 0)  //Dezimal punkt muss gesetzt werden
      {
        iToLength = lTrimIndex - iDecimal + 3; //Dezimalpunkt und eine Null
        iFromIndex = lTrimIndex;
        bHasDecimal = true;
        iDecimal = 1;
      }
      else
      {
        iToLength = lTrimIndex + 2; //String wird um Dezimalpunkt lï¿½ger
        iFromIndex = lTrimIndex;
        bHasDecimal = true;
      }
    }

    if (iSign == 1)
    {
      ++iToLength;
      ++iDecimal;
    }

    //Initialisieren der Indexes
    Int iToIndex = iToLength - 1;

    while (iFromIndex >= 0)
    {
      //Dezimal punkt ueberspringen
      if(iDecimal == iToIndex && bHasDecimal)
      {
        iToIndex--;
      }
      else
      {
        pToBuffer[iToIndex] = pFromBuffer[iFromIndex];
        iToIndex--;
        iFromIndex--;
      }
    }

    //Setzen des Signs
    if (iSign == 1)
    {
      pToBuffer[0] = '-';
    }

    //Setzen des Dezimalpunkts
    if(bHasDecimal)
    {
      pToBuffer[iDecimal] = '.';
    }


    pToBuffer[iToLength] = '\0';

    str = pToBuffer;
    //free(pFromBuffer);
    //free(pToBuffer);
    delete [] pFromBuffer;
    delete [] pToBuffer;
  }
  return str;
}


/***************************************************************************/
/*! Assigns a int32 value to the string
    \param lValue : Int32 value to assign
*/
/***************************************************************************/
void TString::assignInt32(Int32 lValue)
{
  char* pNewBuffer = new char[100];
  if (pNewBuffer != NULL)
  {
    #if defined(__GNUC__)
      Int iNDig = 15;
      pNewBuffer = gcvt(lValue, iNDig, pNewBuffer);
    #else
      pNewBuffer = ltoa(lValue, pNewBuffer, 10);
    #endif
    TString str(pNewBuffer);
    assign(str.c_bstr());
    delete [] pNewBuffer;
  }
}

/***************************************************************************/
/*! Assigns a int64 value to the string
    \param ldValue : Int64 value to assign
*/
/***************************************************************************/
void TString::assignInt64(Int64 ldValue)
{
  char* pNewBuffer = new char[100];
  if (pNewBuffer != NULL)
  {
    #if defined(__GNUC__)
      Int iNDig = 15;
      pNewBuffer = gcvt(ldValue, iNDig, pNewBuffer);
    #else
      pNewBuffer = _i64toa(ldValue, pNewBuffer, 10);
    #endif
    TString str(pNewBuffer);
    assign(str.c_bstr());
    delete [] pNewBuffer;
  }
}

/***************************************************************************/
/*! Assigns an unsigned int32 value to the string
    \param ulValue : Uint32 value to assign
*/
/***************************************************************************/
void TString::assignUint32(Uint32 ulValue)
{
  char* pNewBuffer = new char[100];
  if (pNewBuffer != NULL)
  {
    #if defined(__GNUC__)
      Int iNDig = 15;
      pNewBuffer = gcvt(ulValue, iNDig, pNewBuffer);
    #else
      pNewBuffer = ultoa(ulValue, pNewBuffer, 10);
    #endif
    TString str(pNewBuffer);
    assign(str.c_bstr());
    delete [] pNewBuffer;
  }
}

/***************************************************************************/
/*! Assigns an unsigned int64 value to the string
    \param uldValue : Uint64 value to assign
*/
/***************************************************************************/
void TString::assignUint64(Uint64 uldValue)
{
  char* pNewBuffer = new char[100];
  if (pNewBuffer != NULL)
  {
    #if defined(__GNUC__)
      Int iNDig = 15;
      pNewBuffer = gcvt(uldValue, iNDig, pNewBuffer);
    #else
      pNewBuffer = _ui64toa(uldValue, pNewBuffer, 10);
    #endif
    TString str(pNewBuffer);
    assign(str.c_bstr());
    delete [] pNewBuffer;
  }
}

/******************************************************************************/
/*! Determines the internal size of the string and sets the m_iSize member.
    This method must be called each time we change the size of the string,
    since getSize() only returns the member m_iSize.
*/
/******************************************************************************/
void TString::updateSize() const
{
  if (m_pWBuffer == NULL)
  {
    m_iSize = 0;
  } // m_pWBuffer == NULL.
  else
  {
    m_iSize = wcslen(m_pWBuffer);
  } // m_pWBuffer != NULL.
}



