/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IFileSystemFileObserver
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 27.09.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IFileSystemWatcherObserver.hpp $
** 
** 6     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 5     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 4     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IFileSystemWatcherObserverHPP
#define IFileSystemWatcherObserverHPP


#include <zeusbase/System/Interfaces/IObserver.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>


BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {BF77E8DA-F24F-4060-A186-45C7FF7497FD}
  #define INTERFACE_IFileSystemWatcherObserver    TIID(0xbf77e8da, 0xf24f, 0x4060, 0xa1, 0x86, 0x45, 0xc7, 0xff, 0x74, 0x97, 0xfd)
#else
  #define INTERFACE_IFileSystemWatcherObserver    0x00000015
#endif

/**************************************************************************/
/*! This observer interface defines call backs for FileSystemWatcher class
*/
/**************************************************************************/
class IFileSystemWatcherObserver : public IObserver
{
  HIDE_ASSIGNMENT_OPERATOR(IFileSystemWatcherObserver)
  
  public:
    /****************************************************************************/
    /*! Callback if a file has been created
        \param rFileName : Name of the file
    */
    /****************************************************************************/
    virtual void MQUALIFIER onFileCreated(const IString& rFileName)=0;

    /****************************************************************************/
    /*! Callback if a file has been deleted
        \param rFileName : Name of the file
    */
    /****************************************************************************/
    virtual void MQUALIFIER onFileRemoved(const IString& rFileName)=0;

    /****************************************************************************/
    /*! Callback if a file has been changed
        \param rFileName : Name of the file
    */
    /****************************************************************************/
    virtual void MQUALIFIER onFileChanged(const IString& rFileName)=0;

    /****************************************************************************/
    /*! Callback if a file has been renamed
        \param rOldFileName : old file name
        \param rNewFileName : new file name
    */
    /****************************************************************************/
    virtual void MQUALIFIER onFileRenamed(const IString& rOldFileName, const IString& rNewFileName)=0;

    /****************************************************************************/
    /*! Unknown action on file
        \param rFileName : Name of the file
    */
    /****************************************************************************/
    virtual void MQUALIFIER onUnknownAction(const IString& rFileName)=0;

};

END_NAMESPACE_Zeus

#endif
