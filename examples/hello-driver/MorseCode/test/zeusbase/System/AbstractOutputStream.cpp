/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : AbstractOutputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 11.10.07 6:56 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/AbstractOutputStream.cpp $
** 
** 6     11.10.07 6:56 bha
** Stores and writes UNICODE-Strings
***************************************************************************/

#include <zeusbase/System/AbstractOutputStream.h>

USING_NAMESPACE_Zeus 


/***************************************************************************/
/*! Creates an abstract output stream
*/
/***************************************************************************/
TAbstractOutputStream::TAbstractOutputStream()
 : TZObject()
{  
  m_bAvailable = true;
  m_bOpen = true;
}

/***************************************************************************/
/*! Destroys the output stream
*/
/***************************************************************************/
TAbstractOutputStream::~TAbstractOutputStream()
{}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
Retval MQUALIFIER TAbstractOutputStream::writeFloat64(Float64 dData)
{
  Retval retValue = RET_REQUEST_FAILED;
  if (m_bAvailable && m_bOpen)
  {
    char* pBuffer = (char*)&dData;
    this->write(pBuffer, sizeof(Float64));
    retValue =  RET_NOERROR;
  }
  return retValue;
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
Retval MQUALIFIER TAbstractOutputStream::writeInt32(Int32 lData)
{
  Retval retValue = RET_REQUEST_FAILED;
  if (m_bAvailable && m_bOpen)
  {
    char* pBuffer = (char*)&lData;
    this->write(pBuffer, sizeof(Int32));
    retValue =  RET_NOERROR;
  }
  return retValue;
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
Retval MQUALIFIER TAbstractOutputStream::writeBool(bool bData)
{
  Retval retValue = RET_REQUEST_FAILED;
  if (m_bAvailable && m_bOpen)
  {
    retValue = writeInt8(bData);
  }
  return retValue;
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
Retval MQUALIFIER TAbstractOutputStream::writeArray(const IByteArray& rData)
{
  Retval retValue = RET_REQUEST_FAILED;
  if (m_bAvailable && m_bOpen)
  {
    this->writeInt32(rData.getCount()); //Size of the array
    this->write(rData.getArray(), rData.getCount());
    retValue = RET_NOERROR;
  }
  
  return retValue;
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
Retval MQUALIFIER TAbstractOutputStream::writeString(const IString& rData)
{
  Retval retValue = RET_REQUEST_FAILED;
  if (m_bAvailable && m_bOpen)
  {
    Int iBufferSize = rData.getSize()+1;
    this->writeInt32(iBufferSize); //Size of the characters
    this->write(rData.c_str(NULL), iBufferSize); //Size of the characters // UNICODE PROBLEM
    retValue =  RET_NOERROR;
  }

  return retValue;
/*
  Retval retValue = RET_REQUEST_FAILED;
  if (m_bAvailable && m_bOpen)
  {
    Int iStringSize = rData.getSize()+1;
    Int iBufferSize = iStringSize * 2;
    this->writeInt32(iBufferSize); //Size of the characters

    char* pcData = new char[iBufferSize];
    for (Int i = 0, j = 0; i < iBufferSize; i += 2, j++)
    {
      wchar_t wcC1 = rData.getChar(j);

      pcData[i] = static_cast<char>(0x00FF & wcC1);
      pcData[i+1] = static_cast<char>(0x00FF & (wcC1 >> 8));
    }
    this->write(pcData, iBufferSize); //Size of the characters

    delete [] pcData;

    retValue =  RET_NOERROR;
  }
  return retValue;*/
}

/**************************************************************************/
/*! Memory Management
*/
/**************************************************************************/
MEMORY_MANAGER_IMPL(TAbstractOutputStream);
  INTERFACE_CAST(IOutputStream, INTERFACE_IOutputStream);
MEMORY_MANAGER_IMPL_END;
 
