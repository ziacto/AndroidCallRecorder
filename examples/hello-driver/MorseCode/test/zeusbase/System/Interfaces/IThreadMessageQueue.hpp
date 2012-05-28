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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IThreadMessageQueue.hpp $
** 
** 7     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 6     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 5     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IThreadMessageQueueHPP
#define IThreadMessageQueueHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/ISynchronizeObject.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {41D6B912-BB9C-4cc7-9A20-99C61504AD59}
  #define INTERFACE_IThreadMessageQueue        TIID(0x41d6b912, 0xbb9c, 0x4cc7, 0x9a, 0x20, 0x99, 0xc6, 0x15, 0x4, 0xad, 0x59)
#else
  #define INTERFACE_IThreadMessageQueue        0x00000019
#endif

/**************************************************************************/
/*! This interface defines the thread message queue. The queue is used
    to send messages to the thread for synchronizing
*/
/**************************************************************************/
class IThreadMessageQueue : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IThreadMessageQueue)    
  
  public:
    /**********************************************************************/
    /*! Clears the queue
    */
    /**********************************************************************/
    virtual void MQUALIFIER flush()=0;
    
    /**********************************************************************/
    /*! proceses the first object of the queue and removes it from the queue
        \retval RET_NOERROR : Object processed
        \retval RET_REQUEST_FAILED : No object found for processing
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER processObject()=0;
    
    /**********************************************************************/
    /*! puts a object into the message queue
        \param rObject : Synchronizing object
        \param bWaitForCompletion : caller waits for completion 
        \retval RET_NOERROR : Object posted
        \retval RET_REQUEST_FAILED : Could not post object or
                waiting was aborted
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER postObject(ISynchronizeObject& rObject, bool bWaitForCompletion)=0;

    /**********************************************************************/
    /*! locks the queue. All post calls will return an error
    */
    /**********************************************************************/
    virtual void MQUALIFIER lock()=0;

    /**********************************************************************/
    /*! unlocks the queue. The queue is ready to receive objects
    */
    /**********************************************************************/
    virtual void MQUALIFIER unlock()=0;

    /**********************************************************************/
    /*! checks if the queue is locked
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isLocked() const=0;

    /**********************************************************************/
    /*! checks if the queue is empty
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isEmpty() const=0;
};

END_NAMESPACE_Zeus

#endif 
 
