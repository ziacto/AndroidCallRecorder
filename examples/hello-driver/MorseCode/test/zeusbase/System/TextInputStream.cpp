/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : TextInputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 16.01.08 10:10 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/TextInputStream.cpp $
** 
** 6     16.01.08 10:10 Bha
** stream end reached redefined
** 
** 5     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 4     20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
** 
** 2     28.11.06 16:31 bha
** Beheben von Compilerwarnungen
***************************************************************************/
//---------------------------------------------------------------------------

#include <zeusbase/System/TextInputStream.h>
#include <zeusbase/System/FileInputStream.h>
#include <zeusbase/System/ByteArray.hpp>

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stdio.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


USING_NAMESPACE_Zeus

/*****************************************************************************/
/*! Creates a TextInputStream filter using any input stream as source
    \param rParentStream : Source stream
    \param strEncoding : Encoding
*/
/*****************************************************************************/
TTextInputStream::TTextInputStream(IInputStream& rParentStream,
                                   EEncodingType eEncoding /*= etAutoDetect*/,
                                   EEndianType eEndian /*= etLittleEndian*/)
 : TFilterInputStream(rParentStream)
{
  m_eEncoding = eEncoding;
  m_eEndian = eEndian;

  if (m_eEncoding == etAutoDetect)
  {
    autoDetectEncoding();
  }
}

/*****************************************************************************/
/*! Creates a TextInputStream filter, using a file as source
*/
/*****************************************************************************/
TTextInputStream::TTextInputStream(const IString& rFileName,
                                   EEncodingType eEncoding /*= etAutoDetect*/,
                                   EEndianType eEndian /*= etLittleEndian*/)
 : TFilterInputStream(*new TFileInputStream(rFileName), true)
{
  m_eEncoding = eEncoding;
  m_eEndian = eEndian;

  if (m_eEncoding == etAutoDetect)
  {
    autoDetectEncoding();
  }
}


/*****************************************************************************/
/*! Destroys the TextInputStream filter
*/
/*****************************************************************************/
TTextInputStream::~TTextInputStream()
{

}

/*****************************************************************************/
/*! Detects the encoding of the stream
*/
/*****************************************************************************/
void TTextInputStream::autoDetectEncoding()
{
  if (this->available())
  {
    unsigned char ucByte1 = this->readInt8();
    unsigned char ucByte2 = this->readInt8();
    bool bSet = false;

    //UTF-8
    if (ucByte1 == 0xEF && ucByte2 == 0xBB )
    {
      unsigned char ucByte3 = this->readInt8();
      if (ucByte3 == 0xBF)
      {
        //TODO: Not supported yet
      }
    }
    //UTF-16/UCS-2, big-endian
    else if (ucByte1 == 0xFE && ucByte2 == 0xFF )
    {
      m_eEncoding = etUTF_16;
      m_eEndian = etBigEndian;
      bSet = true;
    }
    //UTF-16/UCS-2, little-endian
    else if (ucByte1 == 0xFF && ucByte2 == 0xFE )
    {
      m_eEncoding = etUTF_16;
      m_eEndian = etLittleEndian;
      bSet = true;
    }

    //UTF-32
    else if (ucByte1 == 0x00 && ucByte2 == 0x00)
    {
      //TODO: Not supported yet
    }

    //To set
    if (!bSet)
    {
      reset();
      m_eEncoding = etISO_8859_1;
      m_eEndian = etLittleEndian;
    }
  }
}

/*****************************************************************************/
/*! read a line from a UTF16 stream
*/
/*****************************************************************************/
void TTextInputStream::strReadUTF16Line(IString& rData) const
{
  TByteArray aData(2000);
  bool bLineEndReached = false;
  bool b32Bit = (sizeof(wchar_t) == 4);

  while(!bLineEndReached && !this->isEndReached())
  {
    Int8 cByte1 = TFilterInputStream::readInt8();
    Int8 cByte2 = TFilterInputStream::readInt8();

    if (cByte1 != '\n' && cByte2 != '\n')
    {
      if (cByte1 != '\r' && cByte2 != '\r' &&
          cByte1 != -1 && cByte2 != -1)
      {
        if (m_eEndian == etBigEndian)
        {
          aData.add(cByte2);
          aData.add(cByte1);
  
          //printf("%d.%d.", cByte2, cByte1);
        }
        else
        {
          aData.add(cByte1);
          aData.add(cByte2);
        
          //printf("%d.%d.", cByte1, cByte2);
        }
        
        //////////////////////////////
        //for 32bit wchar_t's
        if (b32Bit)
        {
          aData.add(0x00);
          aData.add(0x00);
        }
        //////////////////////////////
      }
    }
    else
    {
      bLineEndReached = true;
    }
  }
  aData.add(0x00);
  aData.add(0x00);
  
  //////////////////////////////
  //for 32bit wchar_t's
  if (b32Bit)
  {
    aData.add(0x00);
    aData.add(0x00);
  }
  //////////////////////////////

  wchar_t* pwcData = (wchar_t*)aData.getArray();
  rData.assign(pwcData);
  
//  printf("size of wchar_t=%d\n", sizeof(wchar_t));
}

/*****************************************************************************/
/*! read a line from a Ansi stream
*/
/*****************************************************************************/
void TTextInputStream::strReadISO8859_1Line(IString& rData) const
{
  TByteArray aData(2000);
  bool bLineEndReached = false;
  while(!bLineEndReached && !this->isEndReached())
  {
    Int8 cByte1 = TFilterInputStream::readInt8();

    if (cByte1 != '\n')
    {
      if (cByte1 != '\r' && cByte1 != -1)
      {
        aData.add(cByte1);
      }
    }
    else
    {
      bLineEndReached = true;
    }
  }
  aData.add(0x00);

  TString strData(aData.getArray());
  rData.assignStr(strData);
}



/*****************************************************************************/
/*! Reads a text line into the string buffer
*/
/*****************************************************************************/
Retval TTextInputStream::readLine(IString& rLine) const
{
  Retval retValue = RET_REQUEST_FAILED;

  if (this->available() && !this->isEndReached())
  {
    switch(m_eEncoding)
    {
      case etUTF_16 :
        strReadUTF16Line(rLine);
      break;

      case etISO_8859_1:
      default: //fall through
        strReadISO8859_1Line(rLine);
      break;
    }
    retValue = RET_NOERROR;
  }
  return retValue;
}

