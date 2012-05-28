/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : ThreadManager
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 7:04 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/ThreadManager.h $
** 
** 10    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 9     26.02.07 9:00 bha
**
** 1     2.10.06 9:21 bha
** Thread management on Linux and Win32
***************************************************************************/

#ifndef ThreadManagerH
#define ThreadManagerH

#include <zeusbase/System/Map.hpp>
#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/Interfaces/IThreadManager.hpp>
#include <zeusbase/System/SynchronizeObject.h>


BEGIN_NAMESPACE_Zeus

class TCriticalSection;
class IThreadMessageQueue;

#define ThreadManager TThreadManager::getInstance()

/***************************************************************************/
/*! This class implements the manager class for all threads
*/
/***************************************************************************/
zeusbase_class TThreadManager : public TZObject, public IThreadManager
{
  public:
    void setDelegationInterface(IThreadManager& rInstance);
    void releaseDelegationInterface();
    static TThreadManager& getInstance();

    //Methods of IThreadManager
    virtual void MQUALIFIER addThread(Uint uiID, IThreadMessageQueue& rQueue, bool bInterrupted);
    virtual Uint MQUALIFIER getCurrentThreadID() const;
    virtual Retval MQUALIFIER getMessageQueue(Uint uiThreadID, IThreadMessageQueue*& rpQueue);
    virtual bool MQUALIFIER isThreadInterrupted(Uint iID)const;
    virtual void MQUALIFIER removeThread(Uint uiID);
    virtual void MQUALIFIER setThreadState(Uint iID, bool bInterrupted);
    virtual Uint MQUALIFIER getMainThreadID() const;
    virtual Retval MQUALIFIER postObject(Uint uiThreadID,
                                         ISynchronizeObject& rObject,
                                         bool bWaitForCompletion);
    virtual Retval MQUALIFIER postObjectToMainThread(ISynchronizeObject& rObject,
                                                     bool bWaitForCompletion);
    virtual bool MQUALIFIER isCurrentThread(Uint uiThreadID) const;
    virtual bool MQUALIFIER isCurrentMainThread() const;

    //Methods of IZUnknown
    MEMORY_MANAGER_DECL
  
  protected:

    /////////////////////////////////////////////////
    //Compiler problem on older version from microsoft
    #ifdef _MSC_VER
      public:
    #endif
    /////////////////////////////////////////////////

    TThreadManager();
    virtual ~TThreadManager();

  private:
    ///Singleton instance
    static TAutoPtr<TThreadManager> m_ptrInstance;
    ///Delegation instance
    IThreadManager* m_pDelegation;
    ///Map of thread ids
    TMap<Uint, bool> m_mapThreads;
    ///Map of thread message queues
    TMap<Uint, IThreadMessageQueue*> m_mapQueues;
    ///lock for map
    TCriticalSection& m_rMapLock;
    ///lock for delecation pointer
    TCriticalSection& m_rDelegationLock;
    ///ID of the main thread
    Uint m_uiMainThreadID;

};


//INLINE METHODS
/****************************************************************************/
/*! \see IThreadManager::postObjectToMainThread
*/
/****************************************************************************/
inline Retval MQUALIFIER TThreadManager::postObjectToMainThread(ISynchronizeObject& rObject,
                                                            bool bWaitForCompletion)
{
  return postObject(getMainThreadID(), rObject, bWaitForCompletion);
}

/****************************************************************************/
/*! \see IThreadManager::isCurrentThread
*/
/****************************************************************************/
inline bool MQUALIFIER TThreadManager::isCurrentThread(Uint uiThreadID) const
{
  return (this->getCurrentThreadID() == uiThreadID);
}

/****************************************************************************/
/*! \see IThreadManager::isCurrentMainThread
*/
/****************************************************************************/
inline bool MQUALIFIER TThreadManager::isCurrentMainThread() const
{
  return (this->getCurrentThreadID() == this->getMainThreadID());
}

END_NAMESPACE_Zeus


//############################################################################
//MACROS OF SYNCHRONISATION
//----------------------------------------------------------------------------
#if defined(__GNUC__) || defined(_MSC_VER)
  #include <zeusbase/System/SynchronizeObject.h>
  #include <zeusbase/System/Platforms/SynchronizeObjectDelegater.hpp>

  /*************************************************************************/
  /*! \def SYNCHRONIZE_CLASS(clss, mMethod) : Defines a synchronisation
             class.
      \param clss : Classname of the method owner
      \param mMethod : Method to synchronize
  */
  /*************************************************************************/
  #define SYNCHRONIZE_CLASS(clss, mMethod)        \
      class TMethodCaller_##clss_##mMethod        \
         : public NAMESPACE_Zeus::TSynchronizeObject\
      {                                           \
        public:                                   \
          TMethodCaller_##clss_##mMethod(clss& rT)\
          {                                       \
            m_pT = &rT;                           \
          }                                       \
                                                  \
          void checkForError()                    \
          {                                       \
            m_rLock.enter();                      \
            if (this->hasError())                 \
            {                                     \
              m_pT = NULL;                        \
            }                                     \
            m_rLock.leave();                      \
          }                                       \
          virtual void MQUALIFIER process()       \
          {                                       \
            m_rLock.enter();                      \
            if (m_pT != NULL)                     \
            {                                     \
              m_pT->mMethod();                    \
            }                                     \
            m_rLock.leave();                      \
          }                                       \
                                                  \
        private:                                  \
          clss* m_pT;                             \
      };                                          \

  /*************************************************************************/
  /*! \def SYNCHRONIZE_METHOD(uiThreadID, clss, mMethod) :
            This macro is used to synchronize a method of an object
      \param uiThreadID : Id of the target thread
      \param clss : Classname of the method owner
      \param mMethod : Method to synchronize
  */
  /*************************************************************************/
  #define SYNCHRONIZE_METHOD(uiThreadID, clss, mMethod)   \
      {                                                   \
        SYNCHRONIZE_CLASS(clss, mMethod);                 \
                                                          \
        TAutoPtr<TMethodCaller_##clss_##mMethod> ptrObject = new TMethodCaller_##clss_##mMethod(*this); \
        ThreadManager.postObject(uiThreadID, *ptrObject, true); \
        ptrObject->checkForError();                         \
      }                                                   \
/*     { \
       TSynchronizeObjectDelegater<clss>* pObject = new TSynchronizeObjectDelegater<clss>(*this, mMethod); \
       ThreadManager.postObject(uiThreadID, *pObject, true); \
       pObject->checkForError(); \
       pObject->release(); \
     }
*/

  /*************************************************************************/
  /*! \def SYNCHRONIZE_MT_METHOD(clss, mMethod) :
            This macro is used to synchronize a method of an object with the
            main thread
      \param clss : Classname of the method owner
      \param mMethod : Method to synchronize
  */
  /*************************************************************************/
  #define SYNCHRONIZE_MT_METHOD(clss, mMethod)            \
      {                                                   \
        SYNCHRONIZE_CLASS(clss, mMethod);                 \
                                                          \
        TAutoPtr<TMethodCaller_##clss_##mMethod> ptrObject = new TMethodCaller_##clss_##mMethod(*this); \
        ThreadManager.postObjectToMainThread(*ptrObject, true); \
        ptrObject->checkForError();                         \
      }                                                   \
/*     { \
       TSynchronizeObjectDelegater<clss>* pObject = new TSynchronizeObjectDelegater<clss>(*this, mMethod); \
       ThreadManager.postObjectToMainThread(*pObject, true); \
       pObject->checkForError(); \
       pObject->release(); \
     }
*/

//----------------------------------------------------------------------------
// Borland bindings
#elif defined(__BCPLUSPLUS__)
  #include <zeusbase/System/Platforms/BorlandSynchronizeObject.hpp>

  /*************************************************************************/
  /*! \def SYNCHRONIZE_METHOD(uiThreadID, clss, mMethod) :
          This macro synchronizes the method call
      \param uiThreadID : Id of the target thread
      \param clss : Not used
      \param mMethod : Method to synchronize
  */
  /*************************************************************************/
  #define SYNCHRONIZE_METHOD(uiThreadID, clss, mMethod) \
     { \
       TAutoPtr<TBorlandSynchronizeObject> ptrObject = new TBorlandSynchronizeObject(&mMethod); \
       ThreadManager.postObject(uiThreadID, *ptrObject, true); \
       ptrObject->checkForError(); \
     }

  /*************************************************************************/
  /*! \def SYNCHRONIZE_MT_METHOD(clss, mMethod) :
            This macro is used to synchronize a method of an object with the
            main thread
      \param clss : Not used
      \param mMethod : Method to synchronize
  */
  /*************************************************************************/
  #define SYNCHRONIZE_MT_METHOD(clss, mMethod) \
     { \
       TAutoPtr<TBorlandSynchronizeObject> ptrObject = new TBorlandSynchronizeObject(&mMethod); \
       ThreadManager.postObjectToMainThread(*ptrObject, true); \
       ptrObject->checkForError(); \
     }


#endif


#endif
