/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : FileOutputStream
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 17:21 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/FileOutputStream.h $
** 
** 11    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 10    26.02.07 9:00 bha
***************************************************************************/

#ifndef FileOutputStreamH
#define FileOutputStreamH

#include <zeusbase/System/AbstractOutputStream.h>
#include <zeusbase/System/String.h>
#include <zeusbase/System/File.h>

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

/***************************************************************************/
/*! Implements an output stream to write into a file
*/
/***************************************************************************/
zeusbase_class TFileOutputStream : public TAbstractOutputStream
{
  public:
    TFileOutputStream(const IString& rFilename, bool bAppend);
    TFileOutputStream(TFile& rFile, bool bAppend=true);

    //Methods of IOutputStream
    virtual Retval MQUALIFIER write(const char* pBuffer, Int iBufferSize);
    virtual Retval MQUALIFIER writeInt8(Int8 cData);
    virtual void MQUALIFIER close();
    virtual void MQUALIFIER flush();

  protected:
    virtual ~TFileOutputStream();

  private:
    ///File instance
    TFile& m_rFile;
    ///Input File stream object
    std::ofstream& m_rStream;
    ///flag for appending data
    bool m_bAppend;
};


END_NAMESPACE_Zeus

#endif

