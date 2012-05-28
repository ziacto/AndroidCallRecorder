/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : TextInputStream
 * Package : System
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/TextInputStream.h $
** 
** 5     26.02.07 9:00 bha
**
** 2     28.11.06 16:31 bha
** Beheben von Compilerwarnungen
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef TextInputStreamH
#define TextInputStreamH

#include <zeusbase/System/FilterInputStream.h>

BEGIN_NAMESPACE_Zeus


/*****************************************************************************/
/*! This is a special input stream filter to read text informations. The
    text can be read from any input stream or directly from a file.
    Following encodings are valid:
    \li ISO-8859-1: ISO Latin Alphabet No. 1
    \li UTF-16 : Sixteen-bit UCS Transformation Format,
                byte order identified by an optional byte-order mark
    \li AUTO : Autodetect.
*/
/*****************************************************************************/
zeusbase_class TTextInputStream : public TFilterInputStream
{
  public:
    /*************************************************************************/
    /*! Text encoding type
    */
    /*************************************************************************/
    enum EEncodingType
    {
      etAutoDetect = 0,
      etISO_8859_1 = 1,
      etUTF_16 = 2
    };

    /*************************************************************************/
    /*! Text endian type
    */
    /*************************************************************************/
    enum EEndianType
    {
      etLittleEndian = 0,
      etBigEndian = 1
    };

    TTextInputStream(IInputStream& rParentStream,
                     EEncodingType eEncoding = etAutoDetect,
                     EEndianType eEndian = etLittleEndian);
    TTextInputStream(const IString& rFileName,
                     EEncodingType eEncoding = etAutoDetect,
                     EEndianType eEndian = etLittleEndian);

    Retval readLine(IString& rLine) const;
    EEndianType getEndianType() const;
    EEncodingType getEncodingType() const;

  protected:
    virtual ~TTextInputStream();

    //Methods of IInputStream
    virtual Float64 MQUALIFIER readFloat64(BOOL_ERRORRETVAL(pError)) const;
    virtual Int32 MQUALIFIER readInt32(BOOL_ERRORRETVAL(pError)) const;
    virtual bool MQUALIFIER readBool() const;
    virtual Retval MQUALIFIER readArray(IByteArray& rData) const;
    virtual Retval MQUALIFIER readString(IString& rData) const;
    virtual Retval MQUALIFIER read(char* pBuffer, Int iBufferSize, Int& rValidSize) const;
    virtual Int8 MQUALIFIER readInt8() const;

  private:
    //Encoding of a text file
    EEncodingType m_eEncoding;
    ///Endian type
    EEndianType m_eEndian;

    void autoDetectEncoding();
    void strReadUTF16Line(IString& rData) const;
    void strReadISO8859_1Line(IString& rData) const;

};

//Inline
/*****************************************************************************/
/*! returns the endian type
*/
/*****************************************************************************/
inline TTextInputStream::EEndianType TTextInputStream::getEndianType() const
{
  return m_eEndian;
}

/*****************************************************************************/
/*! returns the encoding type
*/
/*****************************************************************************/
inline TTextInputStream::EEncodingType TTextInputStream::getEncodingType() const
{
  return m_eEncoding;
}

/*****************************************************************************/
/*! Can not be used to read from text data
*/
/*****************************************************************************/
inline Float64 MQUALIFIER TTextInputStream::readFloat64(bool* pError) const
{
  if (pError != NULL)
  {
    *pError = true;
  }
  return 0;
}

/*****************************************************************************/
/*! Can not be used to read from text data
*/
/*****************************************************************************/
inline Int32 MQUALIFIER TTextInputStream::readInt32(bool* pError) const
{
  if (pError != NULL)
  {
    *pError = true;
  }
  return 0;
}

/*****************************************************************************/
/*! Can not be used to read from text data
*/
/*****************************************************************************/
inline bool MQUALIFIER TTextInputStream::readBool() const
{
  return false;
}

/*****************************************************************************/
/*! Can not be used to read from text data
*/
/*****************************************************************************/
inline Retval MQUALIFIER TTextInputStream::readArray(IByteArray& /*rData*/) const
{
  return RET_REQUEST_FAILED;
}

/*****************************************************************************/
/*! Can not be used to read from text data
*/
/*****************************************************************************/
inline Retval MQUALIFIER TTextInputStream::readString(IString& /*rData*/) const
{
  return RET_REQUEST_FAILED;
}

/*****************************************************************************/
/*! \see IInputStream::read
*/
/*****************************************************************************/
inline Retval MQUALIFIER TTextInputStream::read(char* pBuffer, Int iBufferSize, Int& rValidSize) const
{
  return TFilterInputStream::read(pBuffer, iBufferSize, rValidSize);
}

/*****************************************************************************/
/*! \see IInputStream::readInt8
*/
/*****************************************************************************/
inline char MQUALIFIER TTextInputStream::readInt8() const
{
  return TFilterInputStream::readInt8();
}


END_NAMESPACE_Zeus

//---------------------------------------------------------------------------
#endif
