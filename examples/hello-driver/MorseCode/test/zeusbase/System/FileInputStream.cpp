/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : FileInputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 16.01.08 10:11 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/FileInputStream.cpp $
** 
** 12    16.01.08 10:11 Bha
** stream end reached redefined
** skip method implemented
** error in reset() fixed
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

#include <zeusbase/System/FileInputStream.h>
#include <zeusbase/System/File.h>


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
/*! Creates an input stream opening a file 
    \param strFilename : Name of the file
*/
/***************************************************************************/
TFileInputStream::TFileInputStream(const IString& strFilename)
 : TAbstractInputStream(),
   m_rFile(*new TFile(strFilename)),
   m_rStream(*new std::ifstream(strFilename.c_str(NULL), std::ios::in | std::ios::binary)) // UNICODE PROBLEM
{
  m_bAvailable = m_rFile.exists();
  m_bOpen = m_rStream.is_open();
}


/***************************************************************************/
/*! Creates an input stream opening a file 
    \param rFile : File object
*/
/***************************************************************************/
TFileInputStream::TFileInputStream(TFile& rFile)
 : TAbstractInputStream(),
   m_rFile(*new TFile(rFile.getAbsoluteName())),

   #if defined(_MSC_VER)
     m_rStream(*new std::ifstream())
   #else
     m_rStream(*new std::ifstream(rFile.getAbsoluteName().c_str(NULL), std::ios::in | std::ios::binary)) // UNICODE PROBLEM
   #endif
   
{
  #if defined(_MSC_VER)
    m_rStream.open(rFile.getAbsoluteName().c_str(NULL), std::ios::in | std::ios::binary); // UNICODE PROBLEM
  #endif
  
  m_bAvailable = m_rFile.exists();
  m_bOpen = m_rStream.is_open();
}

/***************************************************************************/
/*! Destroys the file stream
*/
/***************************************************************************/
TFileInputStream::~TFileInputStream()
{
  close();
  
  m_rFile.release();
  delete (&m_rStream);
}

/***************************************************************************/
/*! \see IInputStream::isEndReached
*/
/***************************************************************************/
bool MQUALIFIER TFileInputStream::isEndReached() const
{
  return (m_rStream.eof() || m_rStream.peek() == EOF);
}

/***************************************************************************/
/*! \see IInputStream::read
*/
/***************************************************************************/
Retval MQUALIFIER TFileInputStream::read(char* pBuffer, Int iBufferSize, Int& rValidSize) const
{
  Retval retVal = RET_INVALID_DATA;
  if (pBuffer == NULL)
  {
    retVal = RET_INVALID_PARAMETER;
  }
  else if (iBufferSize > 0)
  {
    if (m_bAvailable && m_bOpen && !isEndReached())
    {
      m_rStream.read(pBuffer, iBufferSize);
      rValidSize = m_rStream.gcount();
      if (rValidSize > 0)
      {
        retVal = RET_NOERROR;
      }
      else
      {
        retVal = RET_REQUEST_FAILED;
      }
    }
  }
  return retVal;
}

/***************************************************************************/
/*! \see IInputStream::readInt8
*/
/***************************************************************************/
Int8 MQUALIFIER TFileInputStream::readInt8() const
{
  return (Int8)m_rStream.get();
}

/***************************************************************************/
/*! \see IInputStream::close
*/
/***************************************************************************/
void MQUALIFIER TFileInputStream::close()
{
  if (m_bOpen)
  {
    m_rStream.close();
  }
}

/***************************************************************************/
/*! \see IInputStream::reset
*/
/***************************************************************************/
void MQUALIFIER TFileInputStream::reset()
{
  if (m_bOpen)
  {
    m_rStream.clear(); //clear all error bits
    m_rStream.seekg(0, std::ios_base::beg);
  }
}

/***************************************************************************/
/*! \see IInputStream::skip
*/
/***************************************************************************/
bool MQUALIFIER TFileInputStream::skip(Int iBytes /*= 1*/)
{
  bool bError = true;
  if (m_bOpen)
  {
    m_rStream.clear(); //clear all error bits

    Int iPos1 = m_rStream.tellg();
    m_rStream.seekg(iBytes, std::ios_base::cur);

    bError = (m_rStream.fail() || m_rStream.bad());

    Int iPos2 = m_rStream.tellg();
    bError |= ((iPos1 + iBytes) != iPos2);
  }

  return !bError;
}


END_NAMESPACE_Zeus

