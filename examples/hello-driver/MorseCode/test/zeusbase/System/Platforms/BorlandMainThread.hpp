/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : BorlandMainThread
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Platforms/BorlandMainThread.hpp $
** 
** 6     26.02.07 9:00 bha
***************************************************************************/


#ifndef BorlandMainThreadHPP
#define BorlandMainThreadHPP
//---------------------------------------------------------------------------

#if defined(__BCPLUSPLUS__)

#include <zeusbase/System/AbstractMainThread.h>
#include <zeusbase/System/Platforms/BorlandMainThreadMessageQueue.hpp>
#include <Forms.hpp>

BEGIN_NAMESPACE_Zeus

#define BorlandMainThread   TBorlandMainThread::getInstance()

/****************************************************************************/
/*! This class implements the main thread for borland environment
*/
/****************************************************************************/
zeusbase_class TBorlandMainThread : public TAbstractMainThread
{
  public:
    /*************************************************************************/
    /*! returns the instance of the borland main thread
    */
    /*************************************************************************/
    static TBorlandMainThread& getInstance()
    {
      return m_Instance;
    }

    /*************************************************************************/
    /*! \see TAbstractMainThread::registerThread
    */
    /*************************************************************************/
    inline virtual void registerThread(TThreadManager& rManager, bool bUseInternalDispatcher)
    {
      TAbstractMainThread::registerThread(rManager, bUseInternalDispatcher);
      if (bUseInternalDispatcher)
      {
        Application->OnMessage = performAppMessage;
      }
    }

    /*************************************************************************/
    /*! \see TAbstractMainThread::unregisterThread
    */
    /*************************************************************************/
    virtual void unregisterThread(TThreadManager& rManager)
    {
      TAbstractMainThread::unregisterThread(rManager);
      if (m_bUseInternalDispatcher)
      {
        Application->OnMessage = NULL;
      }
    }

    /*************************************************************************/
    /*! Method to receive the messages
    */
    /*************************************************************************/
    void __fastcall performAppMessage(tagMSG& /*rMsg*/, bool& bHandled)
    {
      while (!m_bInterrupted && m_rQueue.processObject() == RET_NOERROR)
      {
        //process next object
      }
    }

  protected:
    /*************************************************************************/
    /*! Creates the main thread of a borland application
    */
    /*************************************************************************/
    TBorlandMainThread() : TAbstractMainThread(*new TBorlandMainThreadMessageQueue())
    {
      m_ulHandle = ::GetCurrentThread();
    }

    /*************************************************************************/
    /*! Destroys the main thread
    */
    /*************************************************************************/
    virtual ~TBorlandMainThread()
    {}

  private:
    static TBorlandMainThread m_Instance;
    ///Handle of the main thread
    HANDLE m_ulHandle;
};

//This line must be included inside a cpp module
//TBorlandMainThread TBorlandMainThread::m_Instance;

END_NAMESPACE_Zeus


#endif

#endif

