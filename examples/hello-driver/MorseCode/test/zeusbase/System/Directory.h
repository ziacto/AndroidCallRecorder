/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Directory
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 20.03.08 10:54 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Directory.h $
** 
** 17    20.03.08 10:54 Mab
** getWorkingDirectory and setWorkingDirectory added.
** 
** 16    26.02.07 9:00 bha
**
** 10    24.07.06 6:40 bha
** Listing files with TDirectoryItem is supported now.
***************************************************************************/

#ifndef DirectoryH
#define DirectoryH

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IList.hpp>
#include <zeusbase/System/DirectoryItem.h>
#include <zeusbase/System/String.h>
#include <zeusbase/System/ZObject.h>


#if defined(__GNUC__)
  #define PATH_DELIMITER        L'/'
#else
  #define PATH_DELIMITER        L'\\'
#endif

#define USERPATH_DELIMITER        L'~'

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! The directory class implements methods to access the system directory
*/
/***************************************************************************/
zeusbase_class TDirectory : public TZObject
{
  public:
    /***********************************************************************/
    /*! Enumeration type for folder locations
    */
    /***********************************************************************/
    enum EFolderType
    {
      etCommonAdminTools,             /*! < only for windows (CSIDL_COMMON_ADMINTOOLS) */
      etCommonAltStartup,             /*! < only for windows (CSIDL_COMMON_ALTSTARTUP) */
      etCommonApplicationData,        /*! < linux: [/etc]; windows (CSIDL_COMMON_APPDATA)*/
      etCommonDesktop,                /*! < only for windows (CSIDL_COMMON_DESKTOPDIRECTORY) */
      etCommonDocuments,              /*! < only for windows (CSIDL_COMMON_DOCUMENTS) */
      etCommonFavorits,               /*! < only for windows (CSIDL_COMMON_FAVORITES) */
      etCommonPrograms,               /*! < linux: [/usr/bin]; windows (CSIDL_COMMON_PROGRAMS) */
      etCommonStartMenu,              /*! < only for windows (CSIDL_COMMON_STARTMENU) */
      etCommonStartup,                /*! < only for windows (CSIDL_COMMON_STARTUP) */
      etCommonTemplates,              /*! < only for windows (CSIDL_COMMON_TEMPLATES) */
      etControls,                     /*! < only for windows (CSIDL_CONTROLS) */
      etCookies,                      /*! < only for windows (CSIDL_COOKIES) */
      etDesktop,                      /*! < only for windows (CSIDL_DESKTOPDIRECTORY) */
      etDrives,                       /*! < only for windows (CSIDL_DRIVES) */
      etFonts,                        /*! < only for windows (CSIDL_FONTS) */
      etHistory,                      /*! < only for windows (CSIDL_HISTORY) */
      etInternet,                     /*! < only for windows (CSIDL_INTERNET) */
      etInternetCache,                /*! < only for windows (CSIDL_INTERNET_CACHE) */
      etLibraries,                    /*! < linux: [/usr/local/lib]; windows (CSIDL_SYSTEM) */
      etLocalApplicationData,         /*! < linux: [/usr/local/etc]; windows (CSIDL_LOCAL_APPDATA); Variable = $(LOCALAPPLICATIONDATA) */
      etMyMusic,                      /*! < only for windows (CSIDL_MYMUSIC) */
      etMyPictures,                   /*! < only for windows (CSIDL_MYPICTURES) */
      etNetHood,                      /*! < only for windows (CSIDL_NETHOOD) */
      etNetwork,                      /*! < only for windows (CSIDL_NETWORK) */
      etPrinters,                     /*! < only for windows (CSIDL_PRINTERS) */
      etPrintHood,                    /*! < only for windows (CSIDL_PRINTHOOD) */
      etProfile,                      /*! < linux: [/home/USER]; windows (CSIDL_PROFILE) */
      etProgramFiles,                 /*! < linux: [/usr/local/bin]; windows (CSIDL_PROGRAM_FILES) Variable = $(PROGRAMFILES) */
      etProgramFilesCommon,           /*! < linux: [/usr/local/share]; windows (CSIDL_PROGRAM_FILES_COMMON) */
      etRecent,                       /*! < only for windows (CSIDL_RECENT) */
      etSendTo,                       /*! < only for windows (CSIDL_SENDTO) */
      etSystem,                       /*! < linux: [/proc]; windows (CSIDL_WINDOWS)*/
      etTrashBin,                     /*! < linux: [/home/USER/Desktop/trash]; windows (CSIDL_BITBUCKET) */
      etUserAdminTools,               /*! < only for windows (CSIDL_ADMINTOOLS) */
      etUserAltStartup,               /*! < only for windows (CSIDL_ALTSTARTUP) */
      etUserApplicationData,          /*! < linux: [/home/USER]; windows (CSIDL_APPDATA) */
      etUserDesktop,                  /*! < linux: [/home/USER/Desktop]; windows (CSIDL_DESKTOP) */
      etUserDocuments,                /*! < inux: [/home/USER/Documents]; windows (CSIDL_PERSONAL) */
      etUserFavorits,                 /*! < only for windows (CSIDL_FAVORITES)*/
      etUserHome,                     /*! < linux: [/home/USER]; windows (CSIDL_PROFILE) */
      etUserPrograms,                 /*! < linux: [/home/USER/bin]; windows (CSIDL_PROGRAMS) */
      etUserStartmenu,                /*! < only for windows (CSIDL_STARTMENU)*/
      etUserStartup,                  /*! < only for windows (CSIDL_STARTUP) */
      etUserTemplates,                /*! < only for windows (CSIDL_TEMPLATES) */
      etMedia                         /*! < only for linux [/media] */
    };

    TDirectory();
    TDirectory(const TString& strDirName);
    TDirectory(const TDirectoryItem& rItem);
    TDirectory(const TDirectory& rDirectory);
    virtual ~TDirectory();

    const TString& getDirName() const;
    Retval makeAbsolute(const TString& strBasePath, bool bMustExists);
    bool makeDirectory(bool bCreateDeep=false);
    bool removeDirectory();
    bool rename(const TString& strNewName);
    bool isAbsolute() const;
    bool exists() const;
    bool equals(const TDirectory& rDirectory) const;
    bool equals(const IString& rDirectoryName) const;
    Retval getDirectoryContent(IList<TDirectoryItem*>& rList) const;

    //operators
    TDirectory& operator=(const TDirectory& rDirectory);
    bool operator==(const TDirectory& rDirectory) const;
    bool operator==(const TString& rDirectory) const;
    bool operator!=(const TDirectory& rDirectory) const;
    bool operator!=(const TString& rDirectory) const;

    //Methods of TZObject
    TString toString() const;

    //Static methods
    static inline TDirectory getCurrentDirectory(bool& rError) { return getWorkingDirectory(rError); }
    static inline Retval setCurrentDirectory(const IString& strDirectory) { return setWorkingDirectory(strDirectory); }
    static TDirectory getWorkingDirectory(bool& rError);
    static Retval setWorkingDirectory(const IString& strDirectory);
    
    static TDirectory getUserDirectory(bool& rError);
    static TDirectory getTempDirectory(bool& rError);
    static TDirectory getSystemDirectory(EFolderType eFolder, bool& rError);
    static Retval getSystemDirName(EFolderType eFolder, TString& rDirName);

  private:
    ///Directory name
    TString m_strDirName;

    static TString completePath(TString path);

};


//Inline methods comes here
/***************************************************************************/
/*! Checks if the directory is a absolute or a relative path
    \retval true: path is absolute
    \retval false: path is relative
*/
/***************************************************************************/
inline bool TDirectory::isAbsolute() const
{
  bool bRetval = false;
  #if defined(__GNUC__)
    if (m_strDirName.getChar(0) == L'/')
    {
      bRetval = true;
    }
  #else
    if (m_strDirName.getFirstPos(L":") >= 0)
    {
      bRetval = true;
    }
  #endif
  return bRetval;
}

/***************************************************************************/
/*! Returns the absolute name of the directory
*/
/***************************************************************************/
inline const TString& TDirectory::getDirName() const
{
  return m_strDirName;
}

/***************************************************************************/
/*! \see TZObject::toString
*/
/***************************************************************************/
inline TString TDirectory::toString() const
{
  return m_strDirName;
}

/***************************************************************************/
/*! Checks if two directories are equal
*/
/***************************************************************************/
inline bool TDirectory::operator==(const TDirectory& rDirectory) const
{
  return this->equals(rDirectory);
}

/***************************************************************************/
/*! Checks if two directories are equal
*/
/***************************************************************************/
inline bool TDirectory::operator==(const TString& rDirectory) const
{
  return this->equals(rDirectory);
}

/***************************************************************************/
/*! Checks if two directories are equal
*/
/***************************************************************************/
inline bool TDirectory::operator!=(const TDirectory& rDirectory) const
{
  return !this->equals(rDirectory);
}

/***************************************************************************/
/*! Checks if two directories are equal
*/
/***************************************************************************/
inline bool TDirectory::operator!=(const TString& rDirectory) const
{
  return !this->equals(rDirectory);
}


END_NAMESPACE_Zeus

#endif
