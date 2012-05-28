/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus                                                          
 * Module  : DirectoryItem
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/DirectoryItem.cpp $
** 
** 10    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 9     20.02.07 10:18 bha
** Ueberarbeiten von ICAST's
***************************************************************************/
//---------------------------------------------------------------------------

#include <zeusbase/System/DirectoryItem.h>
#include <zeusbase/System/File.h>
//---------------------------------------------------------------------------

#ifdef _MSC_VER
  #pragma warning(push, 1)
#endif

#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#if defined(__GNUC__)
  #include <dirent.h>
  #include <unistd.h>
#else

  //Visual studio
  #ifdef _MSC_VER
    #include <direct.h>

  //Borland C++ Builder
  #else
    #include <dir.h>
  #endif

  #ifdef _MSC_VER
    #pragma warning(push, 1)
  #endif
  #include <io.h>

  #ifdef _MSC_VER
    #pragma warning(pop)
  #endif

  #include <fcntl.h>
#endif

USING_NAMESPACE_Zeus

#if defined(__GNUC__)
/***************************************************************************/
/*! Creates an directory item
*/
/***************************************************************************/
TDirectoryItem::TDirectoryItem(const TString& rDirName,struct dirent& rFileBlock)
{
  m_strDirName = rDirName;
  m_strName = rFileBlock.d_name;
  
  #ifdef _DIRENT_HAVE_D_TYPE
    m_uiFileAttributes = rFileBlock.d_type;
  #else
    m_uiFileAttributes = 0;
  #endif
  
  TFile File(m_strDirName + m_strName);
  m_ldSize = File.getSize();
  m_tmModificationTime = File.getModificationTime();
}

#elif defined(_MSC_VER)

/***************************************************************************/
/*! Creates an directory item
*/
/***************************************************************************/
TDirectoryItem::TDirectoryItem(const TString& rDirName, struct _wfinddata_t& rFileBlock)
{
  m_strDirName = rDirName;
  m_strName = rFileBlock.name;
  m_uiFileAttributes = rFileBlock.attrib;
  m_ldSize  = rFileBlock.size;
  m_tmModificationTime = rFileBlock.time_write;
}

#else
/***************************************************************************/
/*! Creates an directory item
*/
/***************************************************************************/
TDirectoryItem::TDirectoryItem(const TString& rDirName, struct std::_wffblk& rFileBlock)
{
  m_strDirName = rDirName;
  m_strName = rFileBlock.ff_name;
  m_uiFileAttributes = rFileBlock.ff_attrib;
  m_ldSize  = rFileBlock.ff_fsize;
  m_tmModificationTime = rFileBlock.ff_ftime;
}
#endif


/***************************************************************************/
/*! Destroy the directory item
*/
/***************************************************************************/
TDirectoryItem::~TDirectoryItem()
{
}

/***************************************************************************/
/*! Checks if the item is a directory
    \todo This method is not unicode compatible for Unix systems
*/
/***************************************************************************/
bool TDirectoryItem::isDirectory() const
{
  #if defined(__GNUC__)
  
    bool bRetval = false;
    
    /////////////////////////////////////////////////////////////  
    // The system devices the D_Type of the dirent structure
    #ifdef _DIRENT_HAVE_D_TYPE
    if (m_uiFileAttributes != DT_UNKNOWN)
    {
      bRetval = (m_uiFileAttributes == DT_DIR);
    }
    //else we have to get the state-structiure to read the mode of the file
    else
    {
    #endif
    /////////////////////////////////////////////////////////////  
      
      TString strFileNamePath(m_strDirName);
      strFileNamePath += m_strName;
      
      struct stat Buffer;
      if (::stat(strFileNamePath.c_str(NULL), &Buffer) == 0)
      {
        bRetval = S_ISDIR(Buffer.st_mode);
      }
      
    /////////////////////////////////////////////////////////////  
    #ifdef _DIRENT_HAVE_D_TYPE
    }
    #endif
    /////////////////////////////////////////////////////////////
      
    return bRetval;

  #elif _MSC_VER
    return !!(m_uiFileAttributes & _A_SUBDIR);
  #else
    return (m_uiFileAttributes & FA_DIREC);
  #endif
}

/***************************************************************************/
/*! Checks if the file is hidden
*/
/***************************************************************************/
bool TDirectoryItem::isHidden() const
{
  #if defined(__GNUC__)
    return false;
  #elif _MSC_VER
    return !!(m_uiFileAttributes & _A_HIDDEN);
  #else
    return (m_uiFileAttributes & FA_HIDDEN);
  #endif
}

/***************************************************************************/
/*! Checks if the file is a system file
*/
/***************************************************************************/
bool TDirectoryItem::isSystem() const
{
  #if defined(__GNUC__)
    return false;
  #elif _MSC_VER
    return !!(m_uiFileAttributes & _A_SYSTEM);
  #else
    return (m_uiFileAttributes & FA_SYSTEM);
  #endif
}

