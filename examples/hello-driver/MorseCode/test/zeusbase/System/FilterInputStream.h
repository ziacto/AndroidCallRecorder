/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : FilterInputStream
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/FilterInputStream.h $
** 
** 7     16.01.08 10:10 Bha
** stream end reached redefined
** 
** 6     11.10.07 6:58 bha
** Optimized filter streams reading/writing block data
** 
** 5     26.02.07 9:00 bha
***************************************************************************/

#ifndef FilterInputStreamH
#define FilterInputStreamH


#include <zeusbase/System/AbstractInputStream.h>
#include <zeusbase/System/ZObject.h>

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! The filter input stream is used to filter streams before reading them.
    To implement any filter you must simply overwrite the read method
    and filter the incomming buffer of the parent stream
*/
/**************************************************************************/
zeusbase_class TFilterInputStream : public TAbstractInputStream
{
  public:
    TFilterInputStream(IInputStream& rParentStream);

    //Methods of IInputStream
    virtual bool MQUALIFIER available() const;
    virtual bool MQUALIFIER isEndReached() const;
    virtual Retval MQUALIFIER read(char* pBuffer, Int iBufferSize, Int& rValidSize) const;
    virtual Int8 MQUALIFIER readInt8() const;
    virtual void MQUALIFIER close();
    virtual void MQUALIFIER reset();
    virtual bool MQUALIFIER skip(Int iBytes = 1);

  protected:
    TFilterInputStream(IInputStream& rParentStream, bool bDirectCreated);
    virtual ~TFilterInputStream();

    virtual Retval delegateReadBlockToReadInt8(char* pBuffer, Int iBufferSize, Int& rValidSize) const;

  private:
    ///Parent stream (source of data)
    IInputStream& m_rParentStream;
};

//Inline methods
/****************************************************************************/
/*! \see IInputStream::isEndReached
*/
/****************************************************************************/
inline bool MQUALIFIER TFilterInputStream::isEndReached() const
{
  return m_rParentStream.isEndReached();
}

/****************************************************************************/
/*! \see IInputStream::read
*/
/****************************************************************************/
inline Retval MQUALIFIER TFilterInputStream::read(char* pBuffer, Int iBufferSize, Int& rValidSize) const
{
  return m_rParentStream.read(pBuffer, iBufferSize, rValidSize);
}

/****************************************************************************/
/*! \see IInputStream::readInt8
*/
/****************************************************************************/
inline Int8 MQUALIFIER TFilterInputStream::readInt8() const
{
  return m_rParentStream.readInt8();
}

/****************************************************************************/
/*! \see IInputStream::close
*/
/****************************************************************************/
inline void MQUALIFIER TFilterInputStream::close()
{
  m_rParentStream.close();
}

/****************************************************************************/
/*! \see IInputStream::reset
*/
/****************************************************************************/
inline void MQUALIFIER TFilterInputStream::reset()
{
  m_rParentStream.reset();
}

/****************************************************************************/
/*! \see IInputStream::available
*/
/****************************************************************************/
inline bool MQUALIFIER TFilterInputStream::available() const
{
  return m_rParentStream.available();
}



END_NAMESPACE_Zeus

#endif
