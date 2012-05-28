/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : ILibraryImplHelper
 * Package : Help Implementations
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 15.10.07 13:56 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/ILibraryImplHelper.hpp $
** 
** 1     15.10.07 13:56 bha
** created
***************************************************************************/

#ifndef ILibraryImplHelperHPP
#define ILibraryImplHelperHPP

//defines all X-Object exports
#include <zeusbase/System/Interfaces/IXObjectImplHelper.hpp>
//defines all regular Object exports
#include <zeusbase/System/Interfaces/IZUnknownImplHelper.hpp>

//for register functions
#include <zeusbase/System/Interfaces/ISingletonManager.hpp>
#include <zeusbase/System/ZObjectFactory.h>
#include <zeusbase/System/LibraryManager.h>
#include <zeusbase/System/LoggerManager.h>
#include <zeusbase/System/SettingsManager.h>
#include <zeusbase/System/ThreadManager.h>
#include <zeusbase/System/XObjectFactory.h>
#include <zeusbase/Security/SecurityManager.h>

/***************************************************************************/
/*! The MregisterLibrary_Start starts the register of object factories,
    library loader interface and other common singletons of the framework
    \param codemodulename : Name of the codemodule (string)
*/
/***************************************************************************/
#define MregisterLibrary_Start(codemodulename)\
MODULE_EXPORT_PRE Retval MODULE_EXPORT MQUALIFIER registerLibrary(NAMESPACE_Zeus::ISingletonManager& manager)\
{\
  TString strCodeModule(codemodulename); \
  TString strName = L"IXObjectFactory"; \
  TAutoPtr<IXObjectFactory> ptrFactory;\
  if (manager.getSingleton(strName, ICAST(ptrFactory.getPointerReference())) == RET_NOERROR)\
  { \
    TXObjectFactory::getInstance().setDelegationInterface(*ptrFactory);\
  } \
  \
  TAutoPtr<ILibraryManager> ptrLibManager; \
  strName = L"ILibraryManager"; \
  if (manager.getSingleton(strName, ICAST(ptrLibManager.getPointerReference())) == RET_NOERROR)\
  { \
    TLibraryManager::getInstance().setDelegationInterface(*ptrLibManager);\
  } \
  TAutoPtr<IThreadManager> ptrThreadManager; \
  strName = L"IThreadManager"; \
  if (manager.getSingleton(strName, ICAST(ptrThreadManager.getPointerReference())) == RET_NOERROR)\
  { \
    TThreadManager::getInstance().setDelegationInterface(*ptrThreadManager);\
  } \
  TAutoPtr<ISettingsManager> ptrSettingsManager; \
  strName = L"ISettingsManager"; \
  if (manager.getSingleton(strName, ICAST(ptrSettingsManager.getPointerReference())) == RET_NOERROR)\
  { \
    SettingsManager.setDelegationInterface(*ptrSettingsManager);\
  } \
  TAutoPtr<ILogger> ptrSystemRootLogger;\
  strName = L"ILogger";\
  if (manager.getSingleton(strName, ICAST(ptrSystemRootLogger.getPointerReference())) == RET_NOERROR)\
  { \
    if (!RootLogger.equals(ptrSystemRootLogger))\
    { \
      TAutoPtr<ILogger> ptrMyLogger; \
      if (ptrSystemRootLogger->getLogger(strCodeModule, ptrMyLogger) == RET_NOERROR) \
      { \
        LoggerManager.setRootLogger(ptrMyLogger);\
      } \
      else \
      { \
        LoggerManager.setRootLogger(ptrSystemRootLogger);\
      } \
    } \
  } \
  \
  strName = L"IZObjectFactory"; \
  TAutoPtr<IZObjectFactory> ptrZFactory;\
  if (manager.getSingleton(strName, ICAST(ptrZFactory.getPointerReference())) == RET_NOERROR)\
  { \
    TZObjectFactory::getInstance().setDelegationInterface(*ptrZFactory);\
  } \
  strName = L"ISecurityManager"; \
  TAutoPtr<ISecurityManager> ptrSecManager;\
  if (manager.getSingleton(strName, ICAST(ptrSecManager.getPointerReference())) == RET_NOERROR)\
  { \
    TSecurityManager::getInstance().setDelegationInterface(*ptrSecManager);\
  } \
  LoggerManager.getLogger(codemodulename).printfln(LOGMODE_INFO, "Code module [%s] has been registered.", strCodeModule.c_str(NULL)); \

/***************************************************************************/
/*! End of the register function
*/
/***************************************************************************/
#define MregisterLibrary_End\
  return RET_NOERROR;\
}\

/***************************************************************************/
/*! Complete register function for simple modules
    \param codemodulename : Name of the codemodule (string)
*/
/***************************************************************************/
#define MregisterLibrary(codemodulename)\
MregisterLibrary_Start(codemodulename); \
MregisterLibrary_End;

/***************************************************************************/
/*! Start of the unregister function, witch releases all delegation
    interfaces of the common framework singletons
*/
/***************************************************************************/
#define MunregisterLibrary_Start()\
MODULE_EXPORT_PRE Retval MODULE_EXPORT MQUALIFIER unregisterLibrary(NAMESPACE_Zeus::ISingletonManager& )\
{\
  NAMESPACE_Zeus::TXObjectFactory::getInstance().releaseDelegationInterface();\
  NAMESPACE_Zeus::TZObjectFactory::getInstance().releaseDelegationInterface();\
  NAMESPACE_Zeus::TLibraryManager::getInstance().releaseDelegationInterface();\
  NAMESPACE_Zeus::TSettingsManager::getInstance().releaseDelegationInterface();\
  NAMESPACE_Zeus::TSecurityManager::getInstance().releaseDelegationInterface();\

/***************************************************************************/
/*! End of the unregister function
*/
/***************************************************************************/
#define MunregisterLibrary_End\
  return RET_NOERROR;\
}\

/***************************************************************************/
/*! Complete unregister function for simple modules, witch releases
    all delegation interfaces of the common framework singletons
*/
/***************************************************************************/
#define MunregisterLibrary()\
  MunregisterLibrary_Start() \
  MunregisterLibrary_End; \

#endif
