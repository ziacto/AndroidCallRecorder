/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : BorlandMainThreadMessageQueue
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 20.02.07 10:19 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Platforms/BorlandMainThreadMessageQueue.hpp $
** 
** 3     20.02.07 10:19 bha
** Ueberarbeiten von ICAST's
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef BorlandMainThreadMessageQueueH
#define BorlandMainThreadMessageQueueH
//---------------------------------------------------------------------------

#if defined(__BCPLUSPLUS__)


#include <zeusbase/System/ThreadMessageQueue.h>
#include <Forms.hpp>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This is a platform specific helper class for thread message queue on
    Borland C++ Builder
*/
/***************************************************************************/
class TBorlandMainThreadMessageQueue : public TThreadMessageQueue
{
  public:

    /************************************************************************/
    /*! Creates a main thread queue
        \param pEvent : Call back method
    */
    /************************************************************************/
    TBorlandMainThreadMessageQueue() : TThreadMessageQueue()
    {}

  protected:
    /************************************************************************/
    /*! Destructs the main thread queue
    */
    /************************************************************************/
    virtual ~TBorlandMainThreadMessageQueue()
    {}

    /**********************************************************************/
    /*! \see TThreadMessageQueue::onItemPosted
    */
    /**********************************************************************/
    virtual void onItemPosted(ISynchronizeObject& /*rObject*/, bool /*bWaitForCompletion*/)
    {
      if (::PostMessage(Application->Handle, WM_USER+0, 0, 0))
      {
      }
    }

  private:
};

END_NAMESPACE_Zeus

#endif //defined(__BCPLUSPLUS__)


#endif
