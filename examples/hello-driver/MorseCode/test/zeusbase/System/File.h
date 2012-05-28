/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : File
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 22.01.08 8:06 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/File.h $
** 
** 20    22.01.08 8:06 Bha
** file information implemented
** 
** 19    21.01.08 18:24 Bha
** File version implemented for win32
** 
** 18    18.06.07 7:22 bha
** Deleting files with force flag
**
** 11    4.09.06 14:40 bha
** StringTool replaced. All methods are available in TString now.
***************************************************************************/

#ifndef FileH
#define FileH

#include <zeusbase/System/String.h>
#include <zeusbase/System/ZObject.h>
#include <sys/stat.h>

BEGIN_NAMESPACE_Zeus

class TDirectoryItem;

/***************************************************************************/
/*! The directory class implements methods to access the system directory
*/
/***************************************************************************/
zeusbase_class TFile : public TZObject
{
  public:
    TFile(const IString& rAbsName);
    TFile(const TDirectoryItem& rItem);
    TFile(TString strAbsName);
    TFile(const IString& rFileRootPath, const IString& rFileName);
    TFile(const TFile& rFile);
    virtual ~TFile();

    TString getAbsoluteName() const;
    TString extractFileName() const;
    TString extractFileExt() const;
    TString extractFileNameBase() const;
    TString extractFilePath() const;
    bool deleteFile(bool bForce = false);
    bool canWrite() const;
    bool canRead() const;
    bool exists() const;
    bool equals(const TFile& rFile) const;
    bool equals(const IString& rFileName) const;
    Int64 getSize() const;
    Timeval getCreationTime() const;
    Timeval getLastAccessTime() const;
    Timeval getModificationTime() const;
    bool copyTo(const IString& rTargetName) const;
    bool setReadOnly(bool bValue);
    void createBackupFiles(Uint uiBackupNum);
    bool refresh();
    void splitPath(IString& rDrive, IString& rDirectory, IString& rFileName, IString& rExtension);

    //Resource and information related methods
    TString getFileVersion() const;
    TString getFileInformation(const IString& rEntryName) const;

    //Methods of TZObject
    TString toString() const;

    //opeators
    TFile& operator=(const TFile& rFile);
    bool operator==(const TFile& rFile) const;
    bool operator==(const TString& rFile) const;
    bool operator!=(const TFile& rFile) const;
    bool operator!=(const TString& rFile) const;

    //static methods
    static bool isFile(const IString& rDirectoryItem);
    static bool isDirectory(const IString& rDirectoryItem);
    static bool isHidden(const IString& rDirectoryItem);
    static TString createAbsoluteFileNamePath(const IString& rFileName, const IString& rPathToComplete);

  protected:
    ///Absolute name
    TString m_strAbsName;

  private:
    ///Buffer of the file status
    #if defined(__GNUC__)
      struct stat m_StatBuffer;
    #else
      struct _stat m_StatBuffer;
    #endif

    //Flag if status has been read
    bool m_bStatusRead;

    static Int findLastPos(const TString& strItem, wchar_t wcChar);
};


//Inline methods
/***************************************************************************/
/*! \see TZObject::toString
*/
/***************************************************************************/
inline TString TFile::toString() const
{
  return m_strAbsName;
}

/***************************************************************************/
/*! Returns the absolute name of the directory
*/
/***************************************************************************/
inline TString TFile::getAbsoluteName() const
{
  return m_strAbsName;
}

/***************************************************************************/
/*! Checks if two files are equal
*/
/***************************************************************************/
inline bool TFile::operator==(const TFile& rFile) const
{
  return this->equals(rFile);
}

/***************************************************************************/
/*! Checks if two files are equal
*/
/***************************************************************************/
inline bool TFile::operator==(const TString& rFile) const
{
  return this->equals(rFile);
}

/***************************************************************************/
/*! Checks if two files are equal
*/
/***************************************************************************/
inline bool TFile::operator!=(const TFile& rFile) const
{
  return !this->equals(rFile);
}

/***************************************************************************/
/*! Checks if two files are equal
*/
/***************************************************************************/
inline bool TFile::operator!=(const TString& rFile) const
{
  return !this->equals(rFile);
}

/***************************************************************************/
/*! Returns the version of the file. This works only for win32 platforms
    or platforms supporting resource data of files
*/
/***************************************************************************/
inline TString TFile::getFileVersion() const
{
  return getFileInformation(TString(L"FileVersion"));
}


/****************************************************************************/
/*! Checks if a directory item is a file
    \param rDirectoryItem : Name of the directory item
*/
/****************************************************************************/
inline /*static*/ bool TFile::isFile(const IString& rDirectoryItem)
{
  return !TFile::isDirectory(rDirectoryItem);
}

END_NAMESPACE_Zeus

#endif
