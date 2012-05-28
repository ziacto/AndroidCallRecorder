/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : ThreadMessageQueue
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/ThreadMessageQueue.h $
** 
** 6     3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 5     26.02.07 9:00 bha
**
** 1     2.10.06 9:21 bha
** Thread management on Linux and Win32
***************************************************************************/

#ifndef ThreadMessageQueueH
#define ThreadMessageQueueH

#include <zeusbase/System/Interfaces/IThreadMessageQueue.hpp>
#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/Queue.hpp>
#include <zeusbase/System/Event.h>

BEGIN_NAMESPACE_Zeus

class TCriticalSection;

/**************************************************************************/
/*! This implements the message queue of a thread. The message queue
    is used to synchronize threads
*/
/**************************************************************************/
zeusbase_class TThreadMessageQueue : public TZObject, public IThreadMessageQueue
{
  public:
    TThreadMessageQueue();

    //Methods of IThreadMessageQueue
    virtual void MQUALIFIER flush();
    virtual Retval MQUALIFIER processObject();
    virtual Retval MQUALIFIER postObject(ISynchronizeObject& rObject, bool bWaitForCompletion);
    virtual void MQUALIFIER lock();
    virtual void MQUALIFIER unlock();
    virtual bool MQUALIFIER isLocked() const;
    virtual bool MQUALIFIER isEmpty() const;

    //Methods of IZUnknown
    MEMORY_MANAGER_DECL

  protected:
    virtual ~TThreadMessageQueue();

    /**********************************************************************/
    /*! Method for to receive the post event
    */
    /**********************************************************************/
    virtual void onItemPosted(ISynchronizeObject& /* rObject */, bool /* bWaitForCompletion */)
    {}


  private:

    /************************************************************************/
    /*! This is the container class
    */
    /************************************************************************/
    class TItemContainer  : public TZObject
    {
      public:
        /********************************************************************/
        /*! Creates a container
        */
        /********************************************************************/
        TItemContainer(ISynchronizeObject& rObject, bool bWaitForCompletion)
         : TZObject(),
           m_rObject(rObject)
        {
          m_rObject.addRef();
          m_bWaitForCompletion = bWaitForCompletion;
        }

        /********************************************************************/
        /*! Destroys a container
        */
        /********************************************************************/
        virtual ~TItemContainer()
        {
          m_rObject.release();
        }

        /********************************************************************/
        /*! returns the synchronzing object
        */
        /********************************************************************/
        ISynchronizeObject& getObject()
        {
          return m_rObject;
        }

        /********************************************************************/
        /*! returns the synchronzing object
        */
        /********************************************************************/
        const ISynchronizeObject& getObject() const
        {
          return m_rObject;
        }

        /********************************************************************/
        /*! returns the wait for completion flag
        */
        /********************************************************************/
        bool isWaitForCompletionSet()
        {
          return m_bWaitForCompletion;
        }

      private:
        ///Synchronizing object
        ISynchronizeObject& m_rObject;
        ///Flag to wait for completion
        bool m_bWaitForCompletion;

    };

    ///Object queue
    TQueue<TItemContainer*> m_lstQueue;
    ///Locked flag
    bool m_bLocked;
    ///Lock of the queue
    TCriticalSection& m_rLock;


};


/**************************************************************************/
/*! \see IThreadMessageQueue::lock
*/
/**************************************************************************/
inline bool MQUALIFIER TThreadMessageQueue::isLocked() const
{
  return m_bLocked;
}

END_NAMESPACE_Zeus


#endif
