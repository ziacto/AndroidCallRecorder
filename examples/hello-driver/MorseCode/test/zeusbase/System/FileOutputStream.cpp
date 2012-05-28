/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : FileOutputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 15.10.07 15:01 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/FileOutputStream.cpp $
** 
** 11    15.10.07 15:01 Mabbuehl
** Comment concerning Unicode Migration added.
** 
** 10    20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
** 
** 8     28.11.06 16:31 bha
** Beheben von Compilerwarnungen
***************************************************************************/

#include <zeusbase/System/FileOutputStream.h>
 
BEGIN_NAMESPACE_Zeus 

 
/***************************************************************************/
/*! UNICODE PROBLEMs of this class:

    - The constructor of ifstream which takes a file name uses char*.
    - This could not be solved by using a constructor which takes a
      file descriptor (file handle, integer number). In this case, the file
      would be opened manually before constructor the ifstream object.
      However, constructing ifstream by giving a file descriptor always
      resulted in an opening failure (ifstream::is_open() returned false). */
/***************************************************************************/

  
/***************************************************************************/
/* Help function to return the mode
*/
/***************************************************************************/
std::ios_base::openmode getOpenMode(bool bAppend)
{
  std::ios_base::openmode iMode = std::ios::out | std::ios::binary;
  //std::_Ios_Openmode iMode = std::ios::out;
  if (bAppend)
  {
    iMode = std::ios::app | std::ios::binary;
  }
  return iMode;
}


/***************************************************************************/
/*! Creates an output file stream
    \param rFilename : Name of the file to open
    \param bAppend : if set the data will be appended to the existing 
                     content of the file
*/
/***************************************************************************/
TFileOutputStream::TFileOutputStream(const IString& rFilename, bool bAppend /*=true*/)
 : TAbstractOutputStream(),
   m_rFile(*new TFile(rFilename)),
   m_rStream(*new std::ofstream(rFilename.c_str(NULL), getOpenMode(bAppend))) // UNICODE PROBLEM
{
  m_bAppend = bAppend;
  
  m_bAvailable = !m_rStream.fail();
  m_bOpen = m_rStream.is_open();
}

/***************************************************************************/
/*! Creates an output file stream
    \param rFile : File object
    \param bAppend : if set the data will be appended to the existing 
                     content of the file
*/
/***************************************************************************/
TFileOutputStream::TFileOutputStream(TFile& rFile, bool bAppend /*=true*/)
 : TAbstractOutputStream(),
   m_rFile(*new TFile(rFile.getAbsoluteName())),
  
   #if defined(_MSC_VER)
     m_rStream(*new std::ofstream())
   #else
     m_rStream(*new std::ofstream(rFile.getAbsoluteName().c_str(NULL), getOpenMode(bAppend))) // UNICODE PROBLEM
   #endif 
{
  
  #if defined(_MSC_VER)
    m_rStream.open(rFile.getAbsoluteName().c_str(NULL), getOpenMode(bAppend)); // UNICODE PROBLEM
  #endif

  m_bAppend = bAppend;  
  m_bAvailable = !m_rStream.fail();
  m_bOpen = m_rStream.is_open();
}

/***************************************************************************/
/*! Destroys the output file stream
*/
/***************************************************************************/
TFileOutputStream::~TFileOutputStream()
{
  close();
  m_rFile.release();
  delete (&m_rStream);
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
Retval MQUALIFIER TFileOutputStream::write(const char* pBuffer, Int iBufferSize)
{
  Retval retVal = RET_INVALID_DATA;
  if (pBuffer == NULL)
  {
    retVal = RET_INVALID_PARAMETER;
  }
  else if (iBufferSize > 0)
  {
    if (m_bAvailable && m_bOpen)
    {
      m_rStream.write(pBuffer, iBufferSize);
      retVal = RET_NOERROR;
    }
    else
    {
      retVal = RET_REQUEST_FAILED;
    }  
  }
  return retVal;
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
Retval MQUALIFIER TFileOutputStream::writeInt8(Int8 cData)
{
  Retval retVal = RET_REQUEST_FAILED;
  if (m_bAvailable && m_bOpen)
  {
    m_rStream.put(cData);
    retVal =  RET_NOERROR;
  }
  return retVal;
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
void MQUALIFIER TFileOutputStream::close()
{
  if (m_bOpen)
  {
    m_rStream.close();
  }
}

/***************************************************************************/
/*! See IOutputStream
*/
/***************************************************************************/
void MQUALIFIER TFileOutputStream::flush()
{
  m_rStream.flush();
}


END_NAMESPACE_Zeus

