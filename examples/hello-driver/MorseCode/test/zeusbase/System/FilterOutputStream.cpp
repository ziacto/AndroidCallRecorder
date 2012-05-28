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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/FilterOutputStream.cpp $
** 
** 5     11.10.07 6:58 bha
** Optimized filter streams reading/writing block data
***************************************************************************/
#include <zeusbase/System/FilterOutputStream.h>

USING_NAMESPACE_Zeus 
 
/**************************************************************************/
/*! Creates a filter input stream
    \param rParentStream : Parent stream (target)
*/
/**************************************************************************/
TFilterOutputStream::TFilterOutputStream(IOutputStream& rParentStream)
 : TAbstractOutputStream(),
   m_rParentStream(rParentStream)
{
  m_rParentStream.addRef();
}
  
/**************************************************************************/
/*! Creates a filter input stream
    \param rParentStream : Parent stream (source)
    \param bDirectCreated : Dummy, is used to avoid an addref on the input
           stream
*/
/**************************************************************************/
TFilterOutputStream::TFilterOutputStream(IOutputStream& rParentStream, bool /*bDirectCreated*/)
 : TAbstractOutputStream(),
   m_rParentStream(rParentStream)
{
}

/**************************************************************************/
/*! Destroys the filter input stream
*/
/**************************************************************************/
TFilterOutputStream::~TFilterOutputStream()
{
  m_rParentStream.release();
}

/**************************************************************************/
/*! This method dispatches the write-Block method to the writeInt8 method
*/
/**************************************************************************/
Retval TFilterOutputStream::delegateWriteBlockToWriteInt8(const char* pBuffer, Int iBufferSize)
{
  for (Int i = 0; i < iBufferSize; i++)
  {
    writeInt8(pBuffer[i]);
  }
  
  return RET_NOERROR;
}

