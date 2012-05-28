/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : File
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 4.04.08 19:04 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/File.cpp $
** 
** 35    4.04.08 19:04 Bha
** eliminated coding errors and warnings for VC2005 and C++Builder 2007
** 
** 34    24.01.08 10:01 Mab
** VS6 warnings fixed.
** 
** 33    22.01.08 8:06 Bha
** file information implemented
** 
** 32    21.01.08 18:42 Bha
** Problem with resource reading fixed. Delimiter inserted 
** 
** 31    21.01.08 18:24 Bha
** File version implemented for win32
** 
** 30    16.01.08 11:35 Bha
** Remove also the original file
** 
** 29    16.01.08 10:35 Bha
** Deletes the old backup files first
** 
** 28    15.10.07 14:50 Mabbuehl
** Unicode Migration.
** 
** 27    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 26    3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
** 
** 25    18.06.07 7:22 bha
** Deleting files with force flag
** 
** 24    14.06.07 12:07 bha
** 
** 16    9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
** 
** 13    4.09.06 14:40 bha
** StringTool replaced. All methods are available in TString now.
***************************************************************************/

#include <zeusbase/System/File.h>
#include <zeusbase/System/BitCodedValue.h>
#include <zeusbase/System/Directory.h>
#include <zeusbase/System/DirectoryItem.h>
#include <zeusbase/System/FileInputStream.h>
#include <zeusbase/System/FileOutputStream.h>

#include <string.h>

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stdlib.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#include <errno.h>

#if defined(__GNUC__)
  #include <wchar.h>
  #include <unistd.h>
  #include <sys/types.h>
#else

  #if defined(__BCPLUSPLUS__)
    #include <dir.h>
  #endif

  #include <sys/types.h>
  #include <fcntl.h>

  #ifdef _MSC_VER
    #pragma warning(push, 1)
  #endif

  #include <stdio.h>
  #include <io.h>

  #ifdef _MSC_VER
    #pragma warning(pop)
  #endif
  
  #define W_OK      02
  #define R_OK      04
#endif

USING_NAMESPACE_Zeus

/***************************************************************************/
/*! Creates an new file wrapper object
    \param rAbsName : Name of the file
*/
/***************************************************************************/
TFile::TFile(const IString& rAbsName) : TZObject()
{
  m_strAbsName = rAbsName;
  m_bStatusRead = false;
}

/***************************************************************************/
/*! Creates a file wrapper out of a directory item
    \param rItem : Item containing the informations
*/
/***************************************************************************/
TFile::TFile(const TDirectoryItem& rItem)
{
  m_strAbsName = rItem.getAbsoluteName();
  m_bStatusRead = false;
}

/***************************************************************************/
/*! Creates an new file wrapper object
    \param strAbsName : Name of the file
*/
/***************************************************************************/
TFile::TFile(TString strAbsName) : TZObject()
{
  m_strAbsName = strAbsName;
  m_bStatusRead = false;
}

/***************************************************************************/
/*! Creates a file wrapper out of a root directory and a file name (path)
    \param rFileRootPath : Root directory. Note that the path should end 
           with '/' or '\' separator
    \param rFileName : File name (path). Leading '/' or '\' will be ignored
*/
/***************************************************************************/
TFile::TFile(const IString& rFileRootPath, const IString& rFileName) : TZObject()
{
  m_strAbsName = rFileRootPath;
    
  if (rFileName.getChar(0) == L'/' || rFileName.getChar(0) == L'\\')
  {
    TString strFileName(rFileName);
    m_strAbsName += strFileName.getSubString(1, strFileName.getSize()-1);
  }
  else
  {
    m_strAbsName += rFileName;
  }
  m_bStatusRead = false;
}

/***************************************************************************/
/*! Copy constructor
*/
/***************************************************************************/
TFile::TFile(const TFile& rFile) : TZObject(rFile)
{
  m_strAbsName = rFile.m_strAbsName;
  m_bStatusRead = false;
}

/***************************************************************************/
/*! Destroys the Directory wrapper object
*/
/***************************************************************************/
TFile::~TFile()
{}

/***************************************************************************/
/*! Refreshes the status of the file object
    \retval true : Status read
    \retval false : Could not read status
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TFile::refresh()
{
  m_bStatusRead = false;
  if (exists())
  {
  #if defined(__GNUC__)
    if (::stat(m_strAbsName.c_str(NULL), &m_StatBuffer) == 0) // UNICODE PROBLEM under __GNUC__.
    {
      m_bStatusRead = true;
    }
  #else
    if (::_wstat(m_strAbsName.c_bstr(), &m_StatBuffer) == 0)
    {
      m_bStatusRead = true;
    }
  #endif
  }
  return m_bStatusRead;
}

/***************************************************************************/
/*! Copy operator
    \param rFile : File to copy
*/
/***************************************************************************/
TFile& TFile::operator=(const TFile& rFile)
{
  TZObject::operator=(rFile);

  m_strAbsName = rFile.m_strAbsName;
  return *this;
}


/***************************************************************************/
/*! Checks if the file exists
    \retval true : File exists
    \retval false : File doesnt exist
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TFile::exists() const
{
  #if defined(__GNUC__)
    return (::access(m_strAbsName.c_str(NULL), 0x00) == 0); // UNICODE PROBLEM under __GNUC__.
  #else
    return (::_waccess(m_strAbsName.c_bstr(), 0x00) == 0);
  #endif
}

/***************************************************************************/
/*! Checks if the two files are equal. This method does only a path check
    and not a content check.
    \param rFile : Path to check
    \retval true : Path is equal
    \retval false: Path is not equal
*/
/***************************************************************************/
bool TFile::equals(const TFile& rFile) const
{
  return equals(rFile.m_strAbsName);
}

/***************************************************************************/
/*! Checks if the two files are equal
    \see TFile::equals
*/
/***************************************************************************/
bool TFile::equals(const IString& rFileName) const
{
  #if defined(__GNUC__)
    return (m_strAbsName == rFileName);
  #else
    //Ignore case on Windows systems
    return m_strAbsName.equalsStr(rFileName, true);
  #endif
}

/***************************************************************************/
/*! This method is used to extract the filename out of the whole path
*/
/***************************************************************************/
TString TFile::extractFileName() const
{
  TString strRetval = m_strAbsName;
  Int iPos = findLastPos(m_strAbsName, L'/');
  if(iPos == -1)
  {
    iPos = findLastPos(m_strAbsName, L'\\');
  }
  if (iPos > -1)
  {
    strRetval = m_strAbsName.getSubString(iPos+1, m_strAbsName.getSize()-1);
  }
  return strRetval;
}


/***************************************************************************/
/*! This method is used to extract the file extentsion out of the whole path
*/
/***************************************************************************/
TString TFile::extractFileExt() const
{
  TString strRetval;
  TString strFileName = this->extractFileName();
  Int iPos = this->findLastPos(strFileName, L'.');
  if (iPos != -1)
  {
    strRetval = strFileName.getSubString(iPos+1, strFileName.getSize()-1);
  }
  return strRetval;
}

/***************************************************************************/
/*! This method is used to extract the path of the file
*/
/***************************************************************************/
TString TFile::extractFilePath() const
{
  TString strRetval = L"";
  Int iPos = findLastPos(m_strAbsName, L'/');
  if(iPos == -1)
  {
    iPos = findLastPos(m_strAbsName, L'\\');
  }
  if (iPos > -1)
  {
    strRetval = m_strAbsName.getSubString(0,iPos);
  }
  return strRetval;
}

/***************************************************************************/
/*! This method is used to extract the file base name out of the whole path
*/
/***************************************************************************/
TString TFile::extractFileNameBase() const
{
  TString strRetval = this->extractFileName();
  Int iPos = this->findLastPos(strRetval, L'.');
  if (iPos != -1)
  {
    strRetval = strRetval.getSubString(0,iPos-1);
  }
  return strRetval;
}


/***************************************************************************/
/*! Search the last position of a specific character in the filename
    \param str : base string
    \param chr : Character to find
    \retval > -1 : Position of the character
    \retval -1 : Character not found
*/
/***************************************************************************/
/*static*/ Int TFile::findLastPos(const TString& strItem, wchar_t wcChar)
{
  Int iRetval = -1;
  const wchar_t* pBase = strItem.c_bstr();
  const wchar_t* pPos = wcsrchr(pBase, wcChar);
  if (pPos != NULL)
  {
    iRetval = (pPos - pBase);
  }
  return iRetval;
}

/***************************************************************************/
/*! Deletes the file
    \retval true : File deleted
    \retval false: could not delete file
*/
/***************************************************************************/
bool TFile::deleteFile(bool bForce /*= false*/)
{
  bool bRetval = false;

  if (bForce)
  {
    // Remove write protection
    setReadOnly(false);
  } // bForce.

  // Remove the file from the file system:
  if (canWrite())
  {
    #if defined(__GNUC__)
    if (::unlink(m_strAbsName.c_str(NULL)) == 0) // UNICODE PROBLEM under __GNUC__.
    {
      bRetval = true;
    } // ::unlink(m_strAbsName.c_str(NULL)) == 0.
    #else
    if (::_wunlink(m_strAbsName.c_bstr()) == 0)
    {
      bRetval = true;
    } // ::wunlink(m_strAbsName.c_bstr()) == 0.
    #endif
  } // canWrite().
  
  return bRetval;
}

/***************************************************************************/
/*! Copies the file and renames it
    \param rTargetName : Name of the copied file
    \retval true : File deleted
    \retval false: could not delete file
*/
/***************************************************************************/
bool TFile::copyTo(const IString& rTargetName) const
{
  #if defined(__GNUC__)
    bool bRetval = false;

    TAutoPtr<TFileInputStream> ptrFileInput = new TFileInputStream((TFile&)*this);
    TAutoPtr<TFileOutputStream> ptrFileOutput = new TFileOutputStream(rTargetName, false);

    Int iBufferSize= this->getSize()+1;
    Int iRetSize = 0;
    char* pBuffer = new char[iBufferSize];

    if (ptrFileInput->read(pBuffer, iBufferSize, iRetSize) == RET_NOERROR)
    {
      bRetval = (ptrFileOutput->write(pBuffer, iRetSize) == RET_NOERROR);
    }

    delete [] pBuffer;

    return bRetval;
  #else
    return (::CopyFileW(m_strAbsName.c_bstr(), rTargetName.c_bstr(), false) != 0);
  #endif

}


/***************************************************************************/
/*! Checks if the file can be written
    \retval true : Able to write file
    \retval false: Unable to write file
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TFile::canWrite() const
{
  #if defined(__GNUC__)
    return (::access(m_strAbsName.c_str(NULL), W_OK) == 0); // UNICODE PROBLEM under __GNUC__.
  #else
    return (::_waccess(m_strAbsName.c_bstr(), W_OK) == 0);
  #endif
}

/***************************************************************************/
/*! Checks if the file can be read
    \retval true : Able to read file
    \retval false: Unable to read file
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TFile::canRead() const
{
  #if defined(__GNUC__)
    return (::access(m_strAbsName.c_str(NULL), R_OK) == 0); // UNICODE PROBLEM under __GNUC__.
  #else
    return (::_waccess(m_strAbsName.c_bstr(), R_OK) == 0);
  #endif
}

/***************************************************************************/
/*! Reads the size of the file
    \return File size in bytes
*/
/***************************************************************************/
Int64 TFile::getSize() const
{
  Int64 ldRetval = 0;

  TFile& rFile = (TFile&)*this; //To avoid the mutable on refreshing members
  if (m_bStatusRead || rFile.refresh())
  {
    ldRetval = m_StatBuffer.st_size;
  }
  return ldRetval;
}

/***************************************************************************/
/*! Returns the time of the file creation
    \return time
*/
/***************************************************************************/
Timeval TFile::getCreationTime() const
{
  Timeval tmRetval = 0;

  TFile& rFile = (TFile&)*this; //To avoid the mutable on refreshing members
  if (m_bStatusRead || rFile.refresh())
  {
    tmRetval = m_StatBuffer.st_ctime;
  }
  return tmRetval;
}

/***************************************************************************/
/*! Returns the time of the last access
    \return time
*/
/***************************************************************************/
Timeval TFile::getLastAccessTime() const
{
  Timeval tmRetval = 0;

  TFile& rFile = (TFile&)*this; //To avoid the mutable on refreshing members
  if (m_bStatusRead || rFile.refresh())
  {
    tmRetval = m_StatBuffer.st_atime;
  }
  return tmRetval;
}

/***************************************************************************/
/*! Returns the time of the last change
    \return time
*/
/***************************************************************************/
Timeval TFile::getModificationTime() const
{
  Timeval tmRetval = 0;

  TFile& rFile = (TFile&)*this; //To avoid the mutable on refreshing members
  if (m_bStatusRead || rFile.refresh())
  {
    tmRetval = m_StatBuffer.st_mtime;
  }
  return tmRetval;
}

/***************************************************************************/
/*! sets or clears the readonly mode
    \param bValue : true = set to readonly; false= set to writable
    \retval true : Mode successfully set
    \retval false: Setting mode failed
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TFile::setReadOnly(bool bValue)
{
  bool bRetval = false;

  #if defined(__GNUC__)
    struct stat Buffer;

    if (::stat(m_strAbsName.c_str(NULL), &Buffer) == 0) // UNICODE PROBLEM under __GNUC__.
    {
      int iAMode = S_IREAD;
      if (!bValue)
      {
        iAMode |= S_IWRITE;
      }

      if (::chmod(m_strAbsName.c_str(NULL), iAMode) == 0) // UNICODE PROBLEM under __GNUC__.
      {
        bRetval = true;
      }
    }
  #else
    struct _stat Buffer;

    if (::_wstat(m_strAbsName.c_bstr(), &Buffer) == 0)
    {
      int iAMode = S_IREAD;
      if (!bValue)
      {
        iAMode |= S_IWRITE;
      }
      if (::_wchmod(m_strAbsName.c_bstr(), iAMode) == 0)
      {
        bRetval = true;
      }
    }
  #endif
  return bRetval;
}

/****************************************************************************/
/*! Creates the backup
    \param uiBackupNum : Max number of backups. The first backup will be called
                        <name>~1.<ext>.
*/
/****************************************************************************/
void TFile::createBackupFiles(Uint uiBackupNum)
{
  if (this->exists())
  {
    TString strSourceFile;
    Uint uiCount = uiBackupNum;

    if (uiBackupNum > 1)
    {
      uiCount--;
    }

    //Backups of the backups
    while (uiCount > 0)
    {
      strSourceFile = this->extractFilePath();
      strSourceFile += this->extractFileNameBase();
      strSourceFile += L"~";
      strSourceFile += (Int)uiCount;
      strSourceFile += L".";
      strSourceFile += this->extractFileExt();

      TFile SourceFile(strSourceFile);

      if (SourceFile.exists() && uiBackupNum != uiCount)
      {
        TString strTargetName(this->extractFilePath());
        strTargetName += this->extractFileNameBase();
        strTargetName += L"~";
        strTargetName += (Int)(uiCount+1);
        strTargetName += L".";
        strTargetName += this->extractFileExt();

        TFile TargetFile(strTargetName);
        if (TargetFile.exists())
        {
          TargetFile.deleteFile(true);
        }
        SourceFile.copyTo(strTargetName);
      }
      uiCount--;
    }

    this->copyTo(strSourceFile);

    //Remove also the original file
    if (this->exists())
    {
      this->deleteFile(true);
    }
  }
}

/****************************************************************************/
/*! This method splits into a drive (windows only), directory name, file name
    and file extension
    \todo This method is not unicode compatible for Unix systems
*/
/****************************************************************************/
void TFile::splitPath(IString& rDrive, IString& rDirectory, IString& rFileName, IString& rExtension)
{
  #if defined(__GNUC__)
    TString strPath = extractFilePath();
    TString strName = extractFileName();
    TString strExt = extractFileExt();
    rDirectory.assignStr(strPath);
    rFileName.assignStr(strName);
    rExtension.assignStr(strExt);
  #else
    wchar_t wcDrive    [_MAX_DRIVE];
    wchar_t wcDirectory[_MAX_DIR];
    wchar_t wcFileName [_MAX_FNAME];
    wchar_t wcExtension[_MAX_EXT];
    ::_wsplitpath(m_strAbsName.c_bstr(), wcDrive, wcDirectory, wcFileName, wcExtension);

    rDrive.assign(wcDrive);
    rDirectory.assign(wcDirectory);
    rFileName.assign(wcFileName);
    rExtension.assign(wcExtension);
  #endif
}

/****************************************************************************/
/*! Returns a resource data of the file depending on the EntryName
    This works only for win32 platforms
    or platforms supporting resource data of files.
    \param rEntryName : Name of the resource data
    \return Data
*/
/****************************************************************************/
TString TFile::getFileInformation(const IString& rEntryName) const
{
  TString strRetval;

  #if defined(ENABLE_WIN32_BINDING)
    TString strFileName(m_strAbsName);

    DWORD dwHandle = 0;
    DWORD dwSize = ::GetFileVersionInfoSize(const_cast<wchar_t*>(strFileName.c_bstr()), &dwHandle);
    if(dwSize != 0)
    {
      wchar_t* pwcBuffer = new wchar_t[dwSize];
      bool bStatus = (::GetFileVersionInfo(const_cast<wchar_t*>(strFileName.c_bstr()), 0, dwSize, pwcBuffer) != 0);

      TString strLanguage;
      if (bStatus)
      {
        // Extract the language ID
        UINT uiDataSize = 0;
        Uint16* pusTranslation = NULL;

        bStatus = (::VerQueryValue( pwcBuffer,
                                    L"\\VarFileInfo\\Translation",
                                    reinterpret_cast<void**>(&pusTranslation),
                                    &uiDataSize) != 0);

        if (bStatus && uiDataSize >= 2)
        {
          strLanguage += TBitCodedValue(pusTranslation[0], 16).toHex().getSubString(2);
          strLanguage += TBitCodedValue(pusTranslation[1], 16).toHex().getSubString(2);
        }

      }

      if (bStatus)
      {
        // Here we create a prefix string that is the same for all the keys.
        TString strKey(L"\\StringFileInfo\\");
        strKey += strLanguage;
        strKey += L"\\";
        strKey += rEntryName;

        wchar_t* pwcData = NULL;
        UINT uiDataSize = 0;
        bStatus = (::VerQueryValue( pwcBuffer,
                                    const_cast<wchar_t*>(strKey.c_bstr()),
                                    reinterpret_cast<void**>(&pwcData),
                                    &uiDataSize) != 0);

        strRetval = pwcData;

      } //(bStatus)

      delete [] pwcBuffer;

    } //(dwSize != 0)
  #endif

  return strRetval;
}


/****************************************************************************/
/*! Checks if a directory item is a directory
    \param rDirectoryItem : Name of the directory item
*/
/****************************************************************************/
/*static*/ bool TFile::isDirectory(const IString& rDirectoryItem)
{
  #if defined(__GNUC__)
    bool bRetval = false;
    struct stat Buffer;
    
    if (::stat(rDirectoryItem.c_str(NULL), &Buffer) == 0) // UNICODE PROBLEM under __GNUC__.
    {
      bRetval = S_ISDIR(Buffer.st_mode);
    }
    return bRetval;

//Not needed
//  #elif defined(__BCPLUSPLUS__)
//    return (_wrtl_chmod(rDirectoryItem.c_bstr(), 0) & FA_DIREC);
  #else
    return ((::GetFileAttributes(rDirectoryItem.c_bstr()) & FILE_ATTRIBUTE_DIRECTORY) != 0);
  #endif
}

/****************************************************************************/
/*! Checks if a directory item is hidden
    \param rDirectoryItem : Name of the directory item
*/
/****************************************************************************/
/*static*/ bool TFile::isHidden(const IString& rDirectoryItem)
{
  #if defined(__GNUC__)
    return false; //Never hidden on UNIX

//Not needed
//  #elif defined(__BCPLUSPLUS__)
//    return (_wrtl_chmod(rDirectoryItem.c_bstr(), 0) & FA_HIDDEN);
  #else
    return ((::GetFileAttributes(rDirectoryItem.c_bstr()) & FILE_ATTRIBUTE_HIDDEN) != 0);
  #endif
}

/****************************************************************************/
/*! creates a complete file name (absolute path)
*/
/****************************************************************************/
/*static*/ TString TFile::createAbsoluteFileNamePath(const IString& rFileName, const IString& rPathToComplete)
{
  TFile fFile(rFileName);
  TDirectory dDir = fFile.extractFilePath();
  dDir.makeAbsolute(rPathToComplete, false);
  
  return dDir.getDirName() + fFile.extractFileName();  
}
