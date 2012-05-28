/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : AbstractInputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 15.10.07 14:02 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/AbstractInputStream.cpp $
** 
** 12    15.10.07 14:02 Mabbuehl
** Unicode Migration.
** 
** 11    11.10.07 7:58 bha
** Warning eliminated
** 
** 10    11.10.07 6:56 bha
** Stores and writes UNICODE-Strings
** 
** 9     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 8     20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
**
** 4     9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
** 
** 3     18.09.06 12:40 Mabbuehl
** Bereinigung von Borland-Release-Warnungen, wo es m�glich und
** effizienter ist.
***************************************************************************/

#include <zeusbase/System/AbstractInputStream.h>

USING_NAMESPACE_Zeus


/***************************************************************************/
/*! Creates an abstract input stream 
*/
/***************************************************************************/
TAbstractInputStream::TAbstractInputStream()
 : TZObject()
{
  m_bAvailable = true;
  m_bOpen = true;
}

/***************************************************************************/
/*! Destroys the abstract stream
*/
/***************************************************************************/
TAbstractInputStream::~TAbstractInputStream()
{}

/***************************************************************************/
/*! \see IInputStream::readFloat64
*/
/***************************************************************************/
Float64 MQUALIFIER TAbstractInputStream::readFloat64(bool* pError) const
{
  Int iSize = sizeof(Float64);
  Int iValidSize = 0;
  char* pBuffer = new char[iSize];
  ::memset(pBuffer, 0, sizeof(char)*iSize);

  Retval retError = this->read(pBuffer, iSize, iValidSize);
  Float64 dRetval = 0;
  if (retError == RET_NOERROR)
  {
    dRetval = *((Float64*)pBuffer);
  }
  delete [] pBuffer;

  //Error return
  if (pError != NULL)
  {
    *pError = (retError != RET_NOERROR);
  }

  return dRetval;
}

/***************************************************************************/
/*! \see IInputStream::readInt32
*/
/***************************************************************************/
Int32 MQUALIFIER TAbstractInputStream::readInt32(bool* pError) const
{
  Int iSize = sizeof(Int32);
  Int iValidSize = 0;
  char* pBuffer = new char[iSize];
  ::memset(pBuffer, 0, sizeof(char)*iSize);

  Retval retError = this->read(pBuffer, iSize, iValidSize);
  Int32 lRetval = 0;
  if (retError == RET_NOERROR)
  {
    lRetval = *((Int32*)pBuffer);
  }
  delete [] pBuffer;

  //Error return
  if (pError != NULL)
  {
    *pError = (retError != RET_NOERROR);
  }

  return lRetval;
}

/***************************************************************************/
/*! \see IInputStream::readBool
*/
/***************************************************************************/
bool MQUALIFIER TAbstractInputStream::readBool() const
{
  #ifdef _MSC_VER
    return !!readInt8();
  #else
    return readInt8();
  #endif
}

/***************************************************************************/
/*! \see IInputStream::readArray
*/
/***************************************************************************/
Retval MQUALIFIER TAbstractInputStream::readArray(IByteArray& rData) const
{
  Retval retValue = RET_NOERROR;
  bool bError = false;
  Int iSize = readInt32(&bError);
  Int iValidSize = 0;
  if (bError)
  {
    retValue = RET_REQUEST_FAILED;
  }
  else if (iSize > 0)
  {
    char* pBuffer = new char[iSize];
    ::memset(pBuffer, 0, sizeof(char)*iSize);
    
    retValue = this->read(pBuffer, iSize, iValidSize);
    
    rData.setArray(pBuffer, iSize);
    delete [] pBuffer;    
  }
  return retValue;
}

/***************************************************************************/
/*! \see IInputStream::readString
*/
/***************************************************************************/
Retval MQUALIFIER TAbstractInputStream::readString(IString& rData) const
{  
  Retval retValue = RET_NOERROR;
  TString strRetval;
  bool bError = false;
  Int iStringSize = readInt32(&bError);
  Int iValidSize = 0;
  if (bError)
  {
    retValue = RET_REQUEST_FAILED;
  }
  else if (iStringSize > 0)
  {
    char* pBuffer = new char[iStringSize]; // UNICODE PROBLEM
    ::memset(pBuffer, 0, sizeof(char)*iStringSize);

    retValue = this->read(pBuffer, iStringSize, iValidSize);

    //The strng transfer is done over wchar_t
    //strRetval = (wchar_t*)pBuffer;
    strRetval = pBuffer;
    delete [] pBuffer;
  }
  rData.assignStr(strRetval);
  return retValue;
/*

  Retval retValue = RET_NOERROR;
  TString strRetval;
  bool bError = false;
  Int iBufferSize = readInt32(&bError);
  if (bError)
  {
    retValue = RET_REQUEST_FAILED;
  }
  else if (iBufferSize > 0)
  {
    Int iStringSize = (iBufferSize + 1) / 2;
    strRetval = TString(L'.', iStringSize);

    char* pBuffer = new char[iBufferSize];
    ::memset(pBuffer, 0, sizeof(char)*iBufferSize);

    Int iValidSize = 0;
    retValue = this->read(pBuffer, iBufferSize, iValidSize);

    if (iValidSize == iBufferSize)
    {
      for(Int i = 0, j = 0; i < iValidSize-1; i += 2, j++)
      {
        char c1 = pBuffer[i];
        char c2 = pBuffer[i+1];
        wchar_t wc1 = (wchar_t)(c1 | (c2 << 8));
        strRetval[j] = wc1;
      }
    }
    delete [] pBuffer;
  }
  rData.assignStr(strRetval);
  return retValue;
*/
}

/**************************************************************************/
/*! Memory Management
*/
/**************************************************************************/
MEMORY_MANAGER_IMPL(TAbstractInputStream);
  INTERFACE_CAST(IInputStream, INTERFACE_IInputStream);
MEMORY_MANAGER_IMPL_END;

 
