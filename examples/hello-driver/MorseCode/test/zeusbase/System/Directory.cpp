/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : Directory
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 9.04.08 14:28 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Directory.cpp $
** 
** 32    9.04.08 14:28 Bha
** set working directory for linux implemented
** 
** 31    20.03.08 11:21 Mab
** Minor bug corrected.
** 
** 30    20.03.08 10:54 Mab
** getWorkingDirectory and setWorkingDirectory added.
** 
** 29    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 28    20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
** 
** 23    9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
**
** 21    11.09.06 15:51 Mabbuehl
** Uninitialized Pointers.
**
** 16    24.07.06 6:40 bha
** Listing files with TDirectoryItem is supported now.
***************************************************************************/

#include <zeusbase/System/Directory.h> 

#if defined(__GNUC__)
  #include <unistd.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <dirent.h>
#else

  //Visual studio
  #ifdef _MSC_VER
    #include <direct.h>
    #include "Shlobj.h"
    #include <commctrl.h>
    #include "Shlwapi.h"

    #include <IMAGEHLP.H>
    #pragma comment(lib, "imageHLP.lib")
    #pragma comment (lib, "shlwapi.lib") // Uses lib path $(BCB)\lib\Psdk.

  //Borland C++ Builder
  #else
    #include "Shlwapi.h"
    #include "Shlobj.h"
    #include <dir.h>
    #include <Dbghelp.h>
    #pragma link "shlwapi.lib" // Uses lib path $(BCB)\lib\Psdk.
  #endif

  #ifdef _MSC_VER
    #pragma warning(push, 1)
  #endif

  #include <stdlib.h>
  #include <stdio.h>
  #include <io.h>

  #ifdef _MSC_VER
    #pragma warning(pop)
  #endif

  #include <errno.h>
  #include <sys/types.h>
#endif


USING_NAMESPACE_Zeus

/***************************************************************************/
/*! Creates an Directory wrapper object
*/
/***************************************************************************/
TDirectory::TDirectory()
{
  m_strDirName = completePath(L"");
}
/***************************************************************************/
/*! Creates an new Directory wrapper object
    \param strDirName : Name of the directory
*/
/***************************************************************************/
TDirectory::TDirectory(const TString& strDirName) : TZObject()
{
  m_strDirName = completePath(strDirName);
}

/***************************************************************************/
/*! Creates an new Directory wrapper object out of the directory item
    \param rItem : Item containing the path information
*/
/***************************************************************************/
TDirectory::TDirectory(const TDirectoryItem& rItem)
{
  m_strDirName = completePath(rItem.getAbsoluteName());
}

/***************************************************************************/
/*! Copy constructor
    \param rDirectory : Directory to copy
*/
/***************************************************************************/
TDirectory::TDirectory(const TDirectory& rDirectory) : TZObject(rDirectory)
{
  m_strDirName = rDirectory.m_strDirName;
}


/***************************************************************************/
/*! Destroys the Directory wrapper object
*/
/***************************************************************************/
TDirectory::~TDirectory()
{}

/***************************************************************************/
/*! Copy operator
    \param rDirectory : Directory to copy
*/
/***************************************************************************/
TDirectory& TDirectory::operator=(const TDirectory& rDirectory)
{
  TZObject::operator=(rDirectory);
  m_strDirName = rDirectory.m_strDirName;
  return *this;
}


/***************************************************************************/
/*! This builds an abolute path if a path is not absolute yet. The
    base path will be assembled with this path.
    \param strBasePath : base path (must be absolute)
    \param bMustExists : if the assembled path does not exists, the method
        will return an error.
*/
/***************************************************************************/
Retval TDirectory::makeAbsolute(const TString& strBasePath, bool bMustExists)
{
  Retval retValue = RET_REQUEST_FAILED;
  if (!this->isAbsolute())
  {
    TString strMyDirName;
    if (this->m_strDirName.getChar(0) == L'.' &&
        this->m_strDirName.getChar(1) == PATH_DELIMITER)
    {
      strMyDirName = this->m_strDirName.getSubString(2, this->m_strDirName.getSize()-1);
    }
    else
    {
      strMyDirName = this->m_strDirName;
    }

    TDirectory BaseDir(completePath(strBasePath) + strMyDirName);
    if ((bMustExists && BaseDir.exists()) || !bMustExists)
    {
      this->m_strDirName = BaseDir.getDirName();
      retValue = RET_NOERROR;
    }
  }
  else
  {
    retValue = RET_NOERROR;
  }
  return retValue;
}


/***************************************************************************/
/*! If a directory does not exists this method will create a new directory.
    If the directory exists it will simply return true.
    \param bCreateDeep : Creates non existing parent directories if flag is set 
    \retval true : Directory created
    \retval false : could not create directory
    \todo This method is not unsicode compatible for Unix systems
*/
/***************************************************************************/
bool TDirectory::makeDirectory(bool bCreateDeep /*=false*/)
{
  bool bRetval = true;
  if (!this->exists())
  {
    #if defined(__GNUC__)
      bRetval = (mkdir(this->m_strDirName.c_str(NULL), S_IRWXU | S_IRWXG) == 0);
    #else
      if (bCreateDeep)
      {
        bRetval = (::MakeSureDirectoryPathExists(this->m_strDirName.c_str(NULL)) == TRUE);
      }
      else
      {
        bRetval = (_wmkdir(this->m_strDirName.c_bstr()) == 0);
      }
    #endif
  }
  return bRetval;
}

/***************************************************************************/
/*! If a directory exists this method will remove it.
    If the directory doesnt exists it will simply return true.
    \retval true : Directory created
    \retval false : could not create directory
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TDirectory::removeDirectory()
{
  bool bRetval = true;
  if (this->exists())
  {
    #if defined(__GNUC__)
      bRetval = (rmdir(this->m_strDirName.c_str(NULL))== 0);
    #else
      bRetval = (_wrmdir(this->m_strDirName.c_bstr())== 0);
    #endif
  }
  return bRetval;
}

/***************************************************************************/
/*! This method renames a directory. It will fail if the new directory
    exists or if the name is already given to this directory or this
    does not exists.
    \retval true : Directory renamed
    \retval false : could not rename directory
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TDirectory::rename(const TString& strNewName)
{
  bool bRetval = false;
  TDirectory NewDir(strNewName);
  if (this->exists() && !NewDir.exists())
  {
    #if defined(__GNUC__)
      bRetval = (::rename(this->m_strDirName.c_str(NULL), NewDir.getDirName().c_str(NULL)) == 0);
    #else
      bRetval = (::_wrename(this->m_strDirName.c_bstr(), NewDir.getDirName().c_bstr()) == 0);
    #endif

    if (bRetval)
    {
      this->m_strDirName = NewDir.getDirName();
    }
  }
  return bRetval;
}


/***************************************************************************/
/*! Checks if the file exists
    \retval true : File exists
    \retval false : File doesnt exist
*/
/***************************************************************************/
bool TDirectory::exists() const
{
  #if defined(__GNUC__)
    return (::access(m_strDirName.c_str(NULL), 0x00) == 0);
  #else
    return (::_waccess(m_strDirName.c_bstr(), 0x00) == 0);
  #endif
}

/***************************************************************************/
/*! This checks if a directory equals an other directory object. Only the
    names and not the content are compared.
    \param rDirectory : Object to check
    \retval true : Object is equal
    \retval false: Object is not equal
*/
/***************************************************************************/
bool TDirectory::equals(const TDirectory& rDirectory) const
{
  return this->equals(rDirectory.m_strDirName);
}

/***************************************************************************/
/*! This checks if a directory equals an other directory object.
    \see TDirectory::equals
*/
/***************************************************************************/
bool TDirectory::equals(const IString& rDirectoryName) const
{
  #if defined(__GNUC__)
    return (m_strDirName == rDirectoryName);
  #else
    //Ignore case on Windows systems
    return m_strDirName.equalsStr(rDirectoryName, true);
  #endif
}


/***************************************************************************/
/*! Returns a list of directory items from this directory
    \param rList : List of items to return. Each item of this list must be
                   released by the caller
    \retval RET_NOERROR : List returned
    \retval RET_REQUEST_FAILED : Could not read this directory
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
Retval TDirectory::getDirectoryContent(IList<TDirectoryItem*>& rList) const
{
  Retval retValue = RET_REQUEST_FAILED;
  if (this->exists())
  {
  #if defined(__GNUC__)
    struct dirent** ppNameList = NULL;
    int iRet = scandir(m_strDirName.c_str(NULL), &ppNameList, 0, alphasort);
    if (iRet >= 0)
    {
      while(iRet--)
      {
        // do not add the this and the parent directory
        // on recursions of the TDirectoryItem structure this
        // could cause problems
        if (strcmp(ppNameList[iRet]->d_name, ".") != 0 &&
            strcmp(ppNameList[iRet]->d_name, "..") != 0)
        {
          rList.add(new TDirectoryItem(m_strDirName, *ppNameList[iRet]));
        }
        free(ppNameList[iRet]);
      }
      free(ppNameList);
    }
    retValue = RET_NOERROR;


  #elif defined(_MSC_VER)
    struct _wfinddata_t FileBlock;
    TString strPath(m_strDirName);
    strPath += L"*.*";
    int iRet = _wfindfirst((wchar_t*)strPath.c_bstr(), &FileBlock);
    if (iRet >= 0)
    {
      //loop unitil the findnext will return -1
      do
      {
        // do not add the this and the parent directory
        // on recursions of the TDirectoryItem structure this
        // could cause problems
        if (wcscmp(FileBlock.name, L".") != 0 &&
            wcscmp(FileBlock.name, L"..") != 0)
        {
          rList.add(new TDirectoryItem(m_strDirName, FileBlock));
        }
      }
      while(_wfindnext(iRet, &FileBlock) == 0);
    }
    retValue = RET_NOERROR;

  #else
    struct _wffblk FileBlock;
    TString strPath(m_strDirName);
    strPath += L"*.*";
    int iRet = ::_wfindfirst(strPath.c_bstr(), &FileBlock, 0x17); /*FA_RDONLY |
                                                                   FA_HIDDEN |
                                                                   FA_SYSTEM |
                                                                   FA_LABEL  |
                                                                   FA_DIREC  |
                                                                   FA_ARCH);   */
    if (iRet == 0)
    {
      //loop unitil the findnext will return -1
      do
      {
        // do not add the this and the parent directory
        // on recursions of the TDirectoryItem structure this
        // could cause problems
        if (wcscmp(FileBlock.ff_name, L".") != 0 &&
            wcscmp(FileBlock.ff_name, L"..") != 0)
        {
          rList.add(new TDirectoryItem(m_strDirName, FileBlock));
        }
      }
      while(::_wfindnext(&FileBlock) == 0);
    }
    retValue = RET_NOERROR;
  #endif
  }
  return retValue;
}


/***************************************************************************/
/*! Static method to receive the current working directory
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
/* static */ TDirectory TDirectory::getWorkingDirectory(bool& rError)
{
  rError = true;

  TString strWorkingDirectory;

  #ifdef ENABLE_WIN32_BINDING
    wchar_t pBuffer[MAX_PATH + 1];
    ::memset(pBuffer, 0, sizeof(pBuffer)); // Static array. sizeof ok.
  
    if (::GetCurrentDirectory(MAX_PATH + 1, pBuffer))
    {
      rError = false;
      strWorkingDirectory = pBuffer;
    } // ::GetCurrentDirectory(MAX_PATH + 1, pBuffer).
  #else
    //Try to get directory name
    char* cBuffer = NULL;
    size_t lSize = 200;
    bool bBreak = false;
    while(!bBreak)
    {
      cBuffer = new char[lSize];
      if (getcwd(cBuffer, lSize) == cBuffer)
      {
        bBreak = true;
      }
      else
      {
        delete [] cBuffer;
        cBuffer = NULL;
        if (errno == ERANGE)
        {
          bBreak = true;
        }
        else
        {
          lSize *= 3;
        }
      }
    }

    if (cBuffer != NULL) // Check if Name is valid
    {
      strWorkingDirectory = TDirectory::completePath(cBuffer);
      delete [] cBuffer;
      rError = false;
    }
  #endif 

  return TDirectory(strWorkingDirectory);
}


/***************************************************************************/
/*! Static method to set the current working directory.

    \todo This method is not implemented for Unix systems
*/
/***************************************************************************/
/* static */ Retval TDirectory::setWorkingDirectory(const IString& strDirectory)
{
  Retval retval = RET_REQUEST_FAILED;

  #ifdef ENABLE_WIN32_BINDING
    if (::SetCurrentDirectory(strDirectory.c_bstr()))
    {
      retval = RET_NOERROR;
    } // ::SetCurrentDirectory(strDirectory.c_bstr()).
  #else
    if (chdir(strDirectory.c_str(NULL)) == 0) //UNICODE PROBLEM
    {
      retval = RET_NOERROR;
    }
  #endif

  return retval;
}

/***************************************************************************/
/*! This method returns the home directory of a user. For Unix systems it
    will simply return the '~'. For windows systems the absolute home
    directory of the current user will be returned
    \param rError : returns true if an error occured
    \return user directory
*/
/***************************************************************************/
TDirectory TDirectory::getUserDirectory(bool& rError)
{
  rError = false;
  return TDirectory(L"~");
}

/***************************************************************************/
/*! This method returns the temporary file directory of a system
    \param rError : returns true if an error occured
    \return temp directory
*/
/***************************************************************************/
TDirectory TDirectory::getTempDirectory(bool& rError)
{

  #if defined(__GNUC__)
    rError = false;
    return TDirectory(P_tmpdir);
  #else
    Uint uiSize = 500;
    wchar_t* pStr = new wchar_t[uiSize];
    Uint uiSizeRet = ::GetTempPath(uiSize, pStr);
    if (uiSizeRet > 0 && uiSizeRet < uiSize)
    {
      pStr[uiSizeRet] = L'\0';
      rError = false;
    }
    else
    {
      pStr[0] = L'\0';
      rError = true;
    }
    TString strData(pStr);
    delete [] pStr;
    return TDirectory(strData);
  #endif
}

/***************************************************************************/
/*! This method completes a file path. The file path must end with the
    PATH_DELIMITER.
*/
/***************************************************************************/
TString TDirectory::completePath(TString path)
{
  
  if (path[0] == L'$' && path[1] == L'(')
  {
    TString strVar = path.getSubString(0, path.getFirstPos(L")"));
    TString strRest = path.getSubString(path.getFirstPos(L")")+1);
    
    // remove the path delimiter
    if (strRest[0] == PATH_DELIMITER) 
    {
      strRest = strRest.getSubString(1);
    }
    
    if (strVar == L"$(LOCALAPPLICATIONDATA)")
    {
      TString strPath;
      if (getSystemDirName(etLocalApplicationData, strPath) == RET_NOERROR)
      {
        path = strPath;
        path += strRest;
      }
    }
    else if (strVar == L"$(PROGRAMFILES)")
    {
      TString strPath;
      if (getSystemDirName(etProgramFiles, strPath) == RET_NOERROR)
      {
        path = strPath;
        path += strRest;
      }
    }
  }
  
  // Its a user path -> read active user directory
  // examples: ~ becomes /home/userxy
  //           ~/dir2 becomes /home/userxy/dir2
  //           ~dir2 stays ~dir2
  if ((path.getSize() == 1 && path.getChar(0) == USERPATH_DELIMITER) ||
      (path.getChar(0) == USERPATH_DELIMITER && path.getChar(1) == PATH_DELIMITER))
  {
    path = path.getSubString(1,path.getSize()-1);
    TString strHomePath;
    getSystemDirName(etUserHome, strHomePath);
    if (strHomePath[strHomePath.getSize()-1] == PATH_DELIMITER)
    {
      strHomePath = strHomePath.getSubString(0,strHomePath.getSize()-2);
    }
    path = strHomePath + path;
  }
  if (path == L"")
  {
    wchar_t cBuffer[3] = {L'.',PATH_DELIMITER, L'\0'};
    path.concat(cBuffer);
  }
  else if (path.getChar(path.getSize()-1) != PATH_DELIMITER)
  {
    wchar_t cBuffer[2] = {PATH_DELIMITER, L'\0'};
    path.concat(cBuffer);
  }
  
  return path;
}

/***************************************************************************/
/*! This method returns the name of a system directory.
    \param eFolder : Folder type (see enumeration)
    \param rDirName : Return parameter of the system directory
    \retval RET_NOERROR : System directory name returned
    \retval RET_REQUEST_FAILED : Could not find system directory
*/
/***************************************************************************/
/*static*/ Retval TDirectory::getSystemDirName(EFolderType eFolder, TString& rDirName)
{
  Retval retValue = RET_NOERROR;

  #if defined(__GNUC__)
    switch(eFolder)
    {      
      case etCommonApplicationData:
        rDirName = L"/etc/";
      break;
      
      case etCommonPrograms :
        rDirName = L"/usr/bin/";
      break;
      
      case etLibraries:
        rDirName = L"/usr/local/lib/";
      break;
            
      case etLocalApplicationData: 
        rDirName = L"/usr/local/etc/";
      break;
      
      case etMedia :
        rDirName = L"/media/";
      break;
      
      case etProgramFiles :
        rDirName = L"/usr/local/bin/";
      break;
      
      case etProgramFilesCommon:
        rDirName = L"/usr/local/share/";
      break;
      
      case etSystem :
        rDirName = L"/proc/";
      break;
        
      case etProfile:            
      case etTrashBin:            //fall through
      case etUserApplicationData: //fall through
      case etUserDesktop:         //fall through 
      case etUserDocuments:       //fall through    
      case etUserHome :           //fall through
      case etUserPrograms :       //fall through
      {  
        TDirectory dDir(getenv("HOME"));
        rDirName = dDir.getDirName();
        
        switch(eFolder)
        {
          case etTrashBin:
            rDirName.concat(L"Desktop/Trash/");
          break;
          
          case etUserDesktop:
            rDirName.concat(L"Desktop/");
          break;
          
          case etUserDocuments:
            rDirName.concat(L"Documents/");
          break;
          
          case etUserPrograms:
            rDirName.concat(L"bin/");
          break;
                    
          default:
          break;
          
        }
        
      }
      break;
      
      default :
        retValue = RET_REQUEST_FAILED;
      break;
    };

  #else
    Int32 lFolder = CSIDL_PERSONAL;

    switch(eFolder)
    {

      #if defined(__BORLANDC__) || (_WIN32_IE >= 0x0500) //(_MSC_VER > 1200)
        case etCommonAdminTools :
          lFolder = CSIDL_COMMON_ADMINTOOLS;
        break;

        case etCommonApplicationData :
          lFolder = CSIDL_COMMON_APPDATA;
        break;

        case etCommonDocuments :
          lFolder = CSIDL_COMMON_DOCUMENTS;
        break;

        case etCommonTemplates :
          lFolder = CSIDL_COMMON_TEMPLATES;
        break;

        case etLibraries :
          lFolder = CSIDL_SYSTEM;
        break;

        case etLocalApplicationData : 
          lFolder = CSIDL_LOCAL_APPDATA;
        break;

        case etMyMusic :
          lFolder = CSIDL_MYMUSIC;
        break;

        case etMyPictures :
          lFolder = CSIDL_MYPICTURES;
        break;

        case etProfile :
          lFolder = CSIDL_PROFILE;
        break;

        case etProgramFiles :
          lFolder = CSIDL_PROGRAM_FILES;
        break;

        case etProgramFilesCommon :
          lFolder = CSIDL_PROGRAM_FILES_COMMON;
        break;

        case etSystem :
          lFolder = CSIDL_WINDOWS;
        break;

        case etUserAdminTools :
          lFolder = CSIDL_ADMINTOOLS;
        break;
      
        case etUserHome :
          lFolder = CSIDL_PROFILE;
        break;

      #endif

      case etCommonAltStartup :
        lFolder = CSIDL_COMMON_ALTSTARTUP;
      break;

      case etCommonDesktop :
        lFolder = CSIDL_COMMON_DESKTOPDIRECTORY;
      break;

      case etCommonFavorits :
        lFolder = CSIDL_COMMON_FAVORITES;
      break;

      case etCommonPrograms :
        lFolder = CSIDL_COMMON_PROGRAMS;
      break;

      case etCommonStartMenu :
        lFolder = CSIDL_COMMON_STARTMENU;
      break;

      case etCommonStartup :
        lFolder = CSIDL_COMMON_STARTUP;
      break;

      case etControls :
        lFolder = CSIDL_CONTROLS;
      break;

      case etCookies :
        lFolder = CSIDL_COOKIES;
      break;

      case etDesktop :
        lFolder = CSIDL_DESKTOPDIRECTORY;
      break;

      case etDrives :
        lFolder = CSIDL_DRIVES;
      break;

      case etFonts :
        lFolder = CSIDL_FONTS;
      break;

      case etHistory :
        lFolder = CSIDL_HISTORY;
      break;

      case etInternet :
        lFolder = CSIDL_INTERNET;
      break;

      case etInternetCache :
        lFolder = CSIDL_INTERNET_CACHE;
      break;

      case etNetHood :
        lFolder = CSIDL_NETHOOD;
      break;

      case etNetwork :
        lFolder = CSIDL_NETWORK;
      break;

      case etPrinters :
        lFolder = CSIDL_PRINTERS;
      break;

      case etPrintHood :
        lFolder = CSIDL_PRINTHOOD;
      break;

      case etRecent :
        lFolder = CSIDL_RECENT;
      break;

      case etSendTo :
        lFolder = CSIDL_SENDTO;
      break;

      case etTrashBin :
        lFolder = CSIDL_BITBUCKET;
      break;

      case etUserAltStartup :
        lFolder = CSIDL_ALTSTARTUP;
      break;

      case etUserApplicationData :
        lFolder = CSIDL_APPDATA;
      break;

      case etUserDesktop :
        lFolder = CSIDL_DESKTOP;
      break;

      case etUserDocuments:
        lFolder = CSIDL_PERSONAL;
      break;

      case etUserFavorits :
        lFolder = CSIDL_FAVORITES;
      break;

      case etUserPrograms :
        lFolder = CSIDL_PROGRAMS;
      break;

      case etUserStartmenu :
        lFolder = CSIDL_STARTMENU;
      break;

      case etUserStartup :
        lFolder = CSIDL_STARTUP;
      break;

      case etUserTemplates :
        lFolder = CSIDL_TEMPLATES;
      break;

      //not supported paths
      case etMedia : //fall through
      default :
        retValue = RET_REQUEST_FAILED;
      break;
    };
    if (retValue == RET_NOERROR)
    {
      LPITEMIDLIST pIDList = NULL;

      if (::SHGetSpecialFolderLocation(NULL, lFolder, &pIDList) == NOERROR)
      {
        wchar_t cFolder[MAX_PATH + 1];

        if (::SHGetPathFromIDList(pIDList, cFolder))
        {
          rDirName = cFolder;

          // Release Memory
          LPMALLOC pMalloc = NULL;
          ::SHGetMalloc(&pMalloc);
          pMalloc->Free(pIDList);
          pMalloc->Release();
        }
        else
        {
          retValue = RET_INTERNAL_ERROR;
          rDirName = L"";
        }
      }
      else
      {
        retValue = RET_INTERNAL_ERROR;
        rDirName = L"";
      }
    }
  #endif

  //Check if Path delimiter has been added to the end of the system path
  if (retValue == RET_NOERROR &&
      rDirName.getChar(rDirName.getSize()-1) != PATH_DELIMITER)
  {
    wchar_t cBuffer[2] = {PATH_DELIMITER, L'\0'};
    rDirName.concat(cBuffer);
  }
  return retValue;
}

/***************************************************************************/
/*! This method returns the directory instance of a system directory.
    \param eFolder : Folder type (see enumeration)
    \param rError : returns true if an error occured
    \return system directory
*/
/***************************************************************************/
/*static*/ TDirectory TDirectory::getSystemDirectory(EFolderType eFolder, bool& rError)
{
  TString strDirName;
  Retval retValue = getSystemDirName(eFolder, strDirName);
  rError = (retValue != RET_NOERROR);
  return TDirectory(strDirName);
}



