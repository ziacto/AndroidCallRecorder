/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ISynchronizeObject
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 4.12.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/ISynchronizeObject.hpp $
** 
** 7     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 6     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 5     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
**
** 1     2.10.06 9:22 bha
** Thread management on Linux and Win32
***************************************************************************/

#ifndef ISynchronizeObjectHPP
#define ISynchronizeObjectHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {B24AA537-05C1-4086-8CBB-07DAC4C392E0}
  #define INTERFACE_ISynchronizeObject        TIID(0xb24aa537, 0x5c1, 0x4086, 0x8c, 0xbb, 0x7, 0xda, 0xc4, 0xc3, 0x92, 0xe0)
#else
  #define INTERFACE_ISynchronizeObject        0x00000018
#endif

/**************************************************************************/
/*! This interface defines a synchronize object. Its used to synchronize
    two threads
*/
/**************************************************************************/
class ISynchronizeObject : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ISynchronizeObject)
  
  public:
    /**********************************************************************/
    /*! Processes the synchronizing.
        This is called from the synchronized thread.
    */
    /**********************************************************************/
    virtual void MQUALIFIER process()=0;

    /**********************************************************************/
    /*! the waiting thread must call this method to wait for termination
        of the process method
    */
    /**********************************************************************/
    virtual bool MQUALIFIER waitForCompletion()=0;

    /**********************************************************************/
    /*! Notifies the waiting thread.
        This is called from the synchronized thread.
    */
    /**********************************************************************/
    virtual void MQUALIFIER notifyCompletion(bool bOK)=0;

    /**********************************************************************/
    /*! Checks if an error occured
    */
    /**********************************************************************/
    virtual bool MQUALIFIER hasError() const=0;
};

END_NAMESPACE_Zeus

#endif 
 
