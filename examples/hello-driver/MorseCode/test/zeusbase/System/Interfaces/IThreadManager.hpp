/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus                                                          
 * Module  : IThreadManager
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 5.12.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IThreadManager.hpp $
** 
** 9     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 8     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 7     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/
 

#ifndef IThreadManagerHPP
#define IThreadManagerHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {ECA36038-829C-4110-B81E-0BA95EDEFD88}
  #define INTERFACE_IThreadManager      TIID(0xeca36038, 0x829c, 0x4110, 0xb8, 0x1e, 0xb, 0xa9, 0x5e, 0xde, 0xfd, 0x88)
#else
  #define INTERFACE_IThreadManager      0x00000017
#endif

class IThreadMessageQueue;
class ISynchronizeObject;

/***************************************************************************/
/*! This interface defines the methods of the thread manager
*/
/***************************************************************************/
class IThreadManager : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IThreadManager)    
  
  public:
  
    /***********************************************************************/
    /*! adds a thread to the manager and registers the thread message 
        queue
        \param uiID : Thread ID
        \param rQueue : Thread message queue
        \param bInterrupted : interrupted flag
    */
    /***********************************************************************/
    virtual void MQUALIFIER addThread(Uint uiID, IThreadMessageQueue& rQueue, bool bInterrupted) = 0;
    
    /***********************************************************************/
    /*! Returns the current thread ID (calling thread)
        \return Thread ID 
    */
    /***********************************************************************/
    virtual Uint MQUALIFIER getCurrentThreadID() const = 0;

    /***********************************************************************/
    /*! Returns the thread message queue 
        \param uiThreadID : ID of the queue owner thread
        \param rpQueue : Return parameter
        \retval RET_NOERROR : Queue returned
        \retval RET_REQUEST_FAILED : Could not find a queue
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getMessageQueue(Uint uiThreadID, IThreadMessageQueue*& rpQueue) = 0;
        
    /***********************************************************************/
    /*! Checks if a thread is interrupted
        \param uiID : Thread ID
        \retval true : Thread is interrupted
        \retval false: Thread is running
    */
    /***********************************************************************/
    virtual bool MQUALIFIER isThreadInterrupted(Uint uiID)const=0;
    
    /***********************************************************************/
    /*! Removes a thread from the list
        \param uiID : Thread ID
    */
    /***********************************************************************/
    virtual void MQUALIFIER removeThread(Uint uiID)=0;
    
    /***********************************************************************/
    /*! Sets a new thread state
        \param uiID : Thread ID
        \param bInterrupted : interrupted flag
    */
    /***********************************************************************/
    virtual void MQUALIFIER setThreadState(Uint uiID, bool bInterrupted)=0;

    /***********************************************************************/
    /*! Returns the ID of the main thread
    */
    /***********************************************************************/
    virtual Uint MQUALIFIER getMainThreadID() const=0;

    /***********************************************************************/
    /*! posts an object to a thread message queue
        \param uiThreadID : ID of the queue
        \param rObject : Object to post
        \param bWaitForCompletion : flag if the calling thread must wait for
                                    process completion
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER postObject(Uint uiThreadID,
                                         ISynchronizeObject& rObject,
                                         bool bWaitForCompletion)=0;

    /***********************************************************************/
    /*! posts an object to the main thread message queue
        \param rObject : Object to post
        \param bWaitForCompletion : flag if the calling thread must wait for
                                    process completion
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER postObjectToMainThread(ISynchronizeObject& rObject,
                                                     bool bWaitForCompletion)=0;

    /***********************************************************************/
    /*! Checks if the current thread is the thread with ID uiThreadID.
    */
    /***********************************************************************/
    virtual bool MQUALIFIER isCurrentThread(Uint uiThreadID) const=0;

    /***********************************************************************/
    /*! Checks if the current thread is the main thread
    */
    /***********************************************************************/
    virtual bool MQUALIFIER isCurrentMainThread() const=0;
};

END_NAMESPACE_Zeus

#endif
 
