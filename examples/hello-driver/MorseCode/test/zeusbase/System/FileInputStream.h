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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/FileInputStream.h $
** 
** 13    16.01.08 10:11 Bha
** stream end reached redefined
** skip method implemented
** error in reset() fixed
** 
** 12    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 11    26.02.07 9:00 bha
***************************************************************************/

#ifndef FileInputStreamH
#define FileInputStreamH

#include <zeusbase/System/AbstractInputStream.h>
#include <zeusbase/System/String.h>

#ifdef _MSC_VER
  #pragma warning(push, 1)
  #pragma warning(disable: 4701 4702) // Previous pragma has no effect!
#endif

#include <fstream>
#include <stdio.h>

#ifdef _MSC_VER
  #pragma warning(default: 4701 4702)
  #pragma warning(pop)
#endif


BEGIN_NAMESPACE_Zeus

class TFile;

/***************************************************************************/
/*! Implements a input stream to read out of a file
*/
/***************************************************************************/
zeusbase_class TFileInputStream : public TAbstractInputStream
{
  public:
    TFileInputStream(const IString& strFilename);
    TFileInputStream(TFile& rFile);

    //Methods of IInputStream
    virtual bool MQUALIFIER isEndReached() const;
    virtual Retval MQUALIFIER read(char* pBuffer, Int iBufferSize, Int& rValidSize) const;
    virtual Int8 MQUALIFIER readInt8() const;
    virtual void MQUALIFIER close();
    virtual void MQUALIFIER reset();
    virtual bool MQUALIFIER skip(Int iBytes = 1);

  protected:
    virtual ~TFileInputStream();

  private:
    ///File instance
    TFile& m_rFile;
    ///Input File stream object
    std::ifstream& m_rStream;
};


END_NAMESPACE_Zeus

#endif
