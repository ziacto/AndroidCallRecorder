/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : AbstractOutputStream
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/AbstractOutputStream.h $
** 
** 4     26.02.07 9:00 bha
***************************************************************************/

#ifndef AbstractOutputStreamH
#define AbstractOutputStreamH

#include <zeusbase/System/Interfaces/IOutputStream.hpp>
#include <zeusbase/System/ZObject.h>

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! This class implements an abstract output stream class
*/
/**************************************************************************/
zeusbase_class TAbstractOutputStream : public TZObject, public IOutputStream
{
  public:
    TAbstractOutputStream();

    bool MQUALIFIER available() const;

    //Abstract Methods of IOutputStream
    virtual Retval MQUALIFIER write(const char* pBuffer, Int iBufferSize)=0;
    virtual Retval MQUALIFIER writeInt8(char cData)=0;
    virtual void MQUALIFIER close()=0;
    virtual void MQUALIFIER flush()=0;

    //Methods of IOutputStream
    virtual Retval MQUALIFIER writeFloat64(Float64 dData);
    virtual Retval MQUALIFIER writeInt32(Int32 lData);
    virtual Retval MQUALIFIER writeBool(bool bData);
    virtual Retval MQUALIFIER writeArray(const IByteArray& rData);
    virtual Retval MQUALIFIER writeString(const IString& rData);

    //Methods of IZUnknown
    MEMORY_MANAGER_DECL

  protected:
    virtual ~TAbstractOutputStream();

    ///flag to check if stream is open
    bool m_bOpen;
    ///flag to check if stream is valid
    bool m_bAvailable;

  private:

};

//Inline methods
/***************************************************************************/
/*! See IInputStream
*/
/***************************************************************************/
inline bool MQUALIFIER TAbstractOutputStream::available() const
{ return m_bAvailable; }


END_NAMESPACE_Zeus

#endif
