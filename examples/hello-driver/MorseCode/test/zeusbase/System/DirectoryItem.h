/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : DirectoryItem
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/DirectoryItem.h $
** 
** 9     26.02.07 9:00 bha
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef DirectoryItemH
#define DirectoryItemH
//---------------------------------------------------------------------------

#include <zeusbase/System/String.h>
#include <zeusbase/System/ZObject.h>


#if defined(__GNUC__)
struct dirent;
//#include <dirent.h>

#elif defined(_MSC_VER)
  struct _wfinddata_t;
#else
  namespace std
  {
    struct _wffblk;
  };
#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! The directory item represents an item
*/
/***************************************************************************/
zeusbase_class TDirectoryItem : public TZObject
{
  public:
    #if defined(__GNUC__)
      TDirectoryItem(const TString& rDirName,struct dirent& rFileBlock);
    #elif defined(_MSC_VER)
      TDirectoryItem(const TString& rDirName, struct _wfinddata_t& rFileBlock);
    #else
      TDirectoryItem(const TString& rDirName, struct std::_wffblk& rFileBlock);
    #endif

    TString getName() const;
    TString getAbsoluteName() const;
    Timeval getModificationTime() const;
    Int64 getSize() const;
    Uint64 getFileStamp() const;
    bool isDirectory() const;
    bool isFile() const;
    bool isHidden() const;
    bool isSystem() const;

  protected:
    virtual ~TDirectoryItem();

    ///Name of the directory item
    TString m_strName;
    ///Name of the base directory
    TString m_strDirName;

  private:
    //File attributes
    Uint m_uiFileAttributes;
    ///Size of the file
    Int64 m_ldSize;
    ///Time of the last change
    Timeval m_tmModificationTime;
};

//inline methods
/***************************************************************************/
/*! Returns the name of the item
*/
/***************************************************************************/
inline TString TDirectoryItem::getName() const
{
  return m_strName;
}

/***************************************************************************/
/*! Returns the complete path of the item
*/
/***************************************************************************/
inline TString TDirectoryItem::getAbsoluteName() const
{
  return TString(m_strDirName + m_strName);
}


/***************************************************************************/
/*! Returns the time of the last change
*/
/***************************************************************************/
inline Timeval TDirectoryItem::getModificationTime() const
{
  return m_tmModificationTime;
}

/***************************************************************************/
/*! Returns the item size
*/
/***************************************************************************/
inline Int64 TDirectoryItem::getSize() const
{
  return m_ldSize;
}

/***************************************************************************/
/*! Returns the stamp of file
*/
/***************************************************************************/
inline Uint64 TDirectoryItem::getFileStamp() const
{
  Uint64 uldFileAttr = m_uiFileAttributes;
  return (uldFileAttr << 32) | m_tmModificationTime;
}


/***************************************************************************/
/*! Checks if the item is a file
*/
/***************************************************************************/
inline bool TDirectoryItem::isFile() const
{
  return !isDirectory();
}

END_NAMESPACE_Zeus

#endif
