/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus                                                          
 * Module  : IThread
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 2.10.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IThread.hpp $
** 
** 6     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 5     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 4     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
**
** 1     2.10.06 9:22 bha
** Thread management on Linux and Win32
***************************************************************************/
 

#ifndef IThreadHPP
#define IThreadHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {393FF413-51B8-4a9d-99A5-E956E4608D99}
  #define INTERFACE_IThread      TIID(0x393ff413, 0x51b8, 0x4a9d, 0x99, 0xa5, 0xe9, 0x56, 0xe4, 0x60, 0x8d, 0x99)
#else
  #define INTERFACE_IThread      0x00000016
#endif

/***************************************************************************/
/*! This interface is used internally for thread manager and event classes.
*/
/***************************************************************************/
class IThread : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IThread)
  
  public:
    /***********************************************************************/
    /*! Returns the platorm specific thread ID (handle)
    */
    /***********************************************************************/
    virtual Uint MQUALIFIER getThreadID() const = 0;
    
    /***********************************************************************/
    /*! Checks if the thread is interrupted. This flag must be asked 
        inside the execute method, to abort the process.
        \retval true : Interrupt flag is set
        \retval false : Interrupt flag is not set
    */
    /***********************************************************************/
    virtual bool MQUALIFIER isInterrupted() const = 0; 
};

END_NAMESPACE_Zeus

#endif
