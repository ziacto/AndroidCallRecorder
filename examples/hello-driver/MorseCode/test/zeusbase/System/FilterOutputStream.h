/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : FilterOutputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 11.10.07 6:58 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/FilterOutputStream.h $
** 
** 6     11.10.07 6:58 bha
** Optimized filter streams reading/writing block data
** 
** 5     26.02.07 9:00 bha
***************************************************************************/

#ifndef FilterOutputStreamH
#define FilterOutputStreamH

#include <zeusbase/System/AbstractOutputStream.h>
#include <zeusbase/System/ZObject.h>

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! The filter output stream is used to filter streams before writing them.
    To implement any filter you must simply overwrite the write method
    and filter the outgoing buffer to the parent stream
*/
/**************************************************************************/
zeusbase_class TFilterOutputStream : public TAbstractOutputStream
{
  public:
    TFilterOutputStream(IOutputStream& rParentStream);

    //Methods of IOutputStream
    virtual Retval MQUALIFIER write(const char* pBuffer, Int iBufferSize);
    virtual Retval MQUALIFIER writeInt8(Int8 cData);
    virtual void MQUALIFIER close();
    virtual void MQUALIFIER flush();

  protected:
    TFilterOutputStream(IOutputStream& rParentStream, bool bDirectCreated);
    virtual ~TFilterOutputStream();

    virtual Retval delegateWriteBlockToWriteInt8(const char* pBuffer, Int iBufferSize);
    
  private:
    ///Parent stream (target of data)
    IOutputStream& m_rParentStream;

};

//Inline methods
/****************************************************************************/
/*! \see IOutputStream::write
*/
/****************************************************************************/
inline Retval MQUALIFIER TFilterOutputStream::write(const char* pBuffer, Int iBufferSize)
{
  return m_rParentStream.write(pBuffer, iBufferSize);
}

/****************************************************************************/
/*! \see IOutputStream::
*/
/****************************************************************************/
inline Retval MQUALIFIER TFilterOutputStream::writeInt8(Int8 cData)
{
  return m_rParentStream.writeInt8(cData);
}

/****************************************************************************/
/*! \see IOutputStream::close
*/
/****************************************************************************/
inline void MQUALIFIER TFilterOutputStream::close()
{
  flush();
  m_rParentStream.close();
}

/****************************************************************************/
/*! \see IOutputStream::flush
*/
/****************************************************************************/
inline void MQUALIFIER TFilterOutputStream::flush()
{
}


END_NAMESPACE_Zeus

#endif


