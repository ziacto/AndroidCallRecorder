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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/FilterInputStream.cpp $
** 
** 6     16.01.08 10:10 Bha
** stream end reached redefined
** 
** 5     11.10.07 6:58 bha
** Optimized filter streams reading/writing block data
***************************************************************************/
#include <zeusbase/System/FilterInputStream.h>

USING_NAMESPACE_Zeus 
 
/**************************************************************************/
/*! Creates a filter input stream
    \param rParentStream : Parent stream (source)
*/
/**************************************************************************/
TFilterInputStream::TFilterInputStream(IInputStream& rParentStream)
 : TAbstractInputStream(),
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
TFilterInputStream::TFilterInputStream(IInputStream& rParentStream, bool /*bDirectCreated*/)
 : TAbstractInputStream(),
   m_rParentStream(rParentStream)
{
}


/**************************************************************************/
/*! Destroys the filter input stream
*/
/**************************************************************************/
TFilterInputStream::~TFilterInputStream()
{
  m_rParentStream.release();
}

/**************************************************************************/
/*! This method dispatches the read-Block method to the readInt8 method
*/
/**************************************************************************/
Retval TFilterInputStream::delegateReadBlockToReadInt8(char* pBuffer, Int iBufferSize, Int& rValidSize) const
{
  Retval retVal = RET_REQUEST_FAILED;
  rValidSize = 0;
  for(int i = 0; i < iBufferSize && !isEndReached(); i++)
  {
    pBuffer[i] = readInt8();
    rValidSize++;
  }
  if (rValidSize > 0)
  {
    retVal = RET_NOERROR;
  }
  return retVal;
}


/****************************************************************************/
/*! The skip method needs to read bytes, since we don't know about the
    encoding and filter implementation. Therefore the skipping of one byte
    might be skipping of multible bytes on the origin source stream.
    \see IInputStream::skip
*/
/****************************************************************************/
bool MQUALIFIER TFilterInputStream::skip(Int iBytes /*= 1*/)
{
  bool bRetval = false;
  if (iBytes > 0)
  {
    char* pcBuffer = new char[iBytes];
    Int iValidSize = 0;
    if (this->delegateReadBlockToReadInt8(pcBuffer, iBytes, iValidSize) == RET_NOERROR)
    {
      bRetval = true;
    }
    delete [] pcBuffer;
  }
  return bRetval;
}

