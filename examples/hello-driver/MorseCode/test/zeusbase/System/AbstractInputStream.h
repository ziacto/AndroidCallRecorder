/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : AbstractInputStream
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/AbstractInputStream.h $
** 
** 8     16.01.08 10:10 Bha
** stream end reached redefined
** 
** 7     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 6     26.02.07 9:00 bha
***************************************************************************/

#ifndef AbstractInputStreamH
#define AbstractInputStreamH

#include <zeusbase/System/Interfaces/IInputStream.hpp>
#include <zeusbase/System/ZObject.h>

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! This class implements an abstract input stream class
*/
/**************************************************************************/
zeusbase_class TAbstractInputStream : public TZObject, public IInputStream
{
  public:
    TAbstractInputStream();

    //Abstract Methods of IInputStream
    virtual Retval MQUALIFIER read(char* pBuffer, Int iBufferSize, Int& rValidSize) const=0;
    virtual Int8 MQUALIFIER readInt8() const=0;
    virtual bool MQUALIFIER isEndReached() const=0;
    virtual void MQUALIFIER close()=0;
    virtual void MQUALIFIER reset()=0;
    virtual bool MQUALIFIER skip(Int iBytes = 1) = 0;

    //Methods of IInputStream
    virtual bool MQUALIFIER available() const;
    virtual Float64 MQUALIFIER readFloat64(BOOL_ERRORRETVAL(pError)) const;
    virtual Int32 MQUALIFIER readInt32(BOOL_ERRORRETVAL(pError)) const;
    virtual bool MQUALIFIER readBool() const;
    virtual Retval MQUALIFIER readArray(IByteArray& rData) const;
    virtual Retval MQUALIFIER readString(IString& rData) const;

    //Methods of IZUnknown
    MEMORY_MANAGER_DECL

  protected:
    virtual ~TAbstractInputStream();

    ///flag to check if stream is open
    bool m_bOpen;
    ///flag to check if stream is valid
    bool m_bAvailable;

  private:

};

//Inline methods
/***************************************************************************/
/*! \see IInputStream::available
*/
/***************************************************************************/
inline bool MQUALIFIER TAbstractInputStream::available() const
{ return m_bAvailable; }


END_NAMESPACE_Zeus

#endif
