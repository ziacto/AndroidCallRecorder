/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXObjectImplHelper
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 15.10.07 15:20 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IXObjectImplHelper.hpp $
** 
** 9     15.10.07 15:20 bha
** Macros for object exports added
***************************************************************************/

#ifndef IXObjectImplHelperHPP
#define IXObjectImplHelperHPP 

//###########################################################################
// EXTERNAL REGISTER MACROS (LIBRARY EXPORTS)
/***************************************************************************/
/*! \def MExportXRootObjectFactory Defines a factory method to create
                XRootObjects witch will be exported by the library
*/
/***************************************************************************/
#define MExportXRootObjectFactory(classid)\
MODULE_EXPORT_PRE Retval MODULE_EXPORT MQUALIFIER create##classid(NAMESPACE_Zeus::IXMLNode* pMainNode, NAMESPACE_Zeus::IXMLDocument* pDocu, NAMESPACE_Zeus::IXObject*& rpObj) \
{ \
  Retval retValue = RET_INTERNAL_ERROR; \
  if (pMainNode != NULL && pDocu != NULL) \
  { \
    rpObj = new classid(*pMainNode, *pDocu); \
    retValue = RET_NOERROR; \
  } \
  return retValue; \
} \

/***************************************************************************/
/*! \def MExportXRootObjectFactory Defines a factory method to create
                XRootObjects using a special namespace,
                witch will be exported by the library
*/
/***************************************************************************/
#define MExportXRootObjectFactoryNS(__namespace, classid)\
MODULE_EXPORT_PRE Retval MODULE_EXPORT MQUALIFIER create##classid(NAMESPACE_Zeus::IXMLNode* pMainNode, NAMESPACE_Zeus::IXMLDocument* pDocu, NAMESPACE_Zeus::IXObject*& rpObj) \
{ \
  Retval retValue = RET_INTERNAL_ERROR; \
  if (pMainNode != NULL && pDocu != NULL) \
  { \
    rpObj = new __namespace::classid(*pMainNode, *pDocu); \
    retValue = RET_NOERROR; \
  } \
  return retValue; \
} \


/***************************************************************************/
/*! \def MExportXObjectFactory Defines a factory method to create
                XObjects witch will be exported by the library
*/
/***************************************************************************/
#define MExportXObjectFactory(classid)\
MODULE_EXPORT_PRE Retval MODULE_EXPORT MQUALIFIER create##classid(NAMESPACE_Zeus::IXMLNode* pMainNode, NAMESPACE_Zeus::IXMLDocument*, NAMESPACE_Zeus::IXObject*& rpObj) \
{ \
  Retval retValue = RET_INTERNAL_ERROR; \
  if (pMainNode != NULL) \
  { \
    rpObj = new classid(*pMainNode); \
    retValue = RET_NOERROR; \
  } \
  return retValue; \
} \

/***************************************************************************/
/*! \def MExportXObjectFactoryNS Defines a factory method to create
                 XObjects using special namespace,
                 witch will be exported by the library
*/
/***************************************************************************/
#define MExportXObjectFactoryNS(__namespace, classid)\
MODULE_EXPORT_PRE Retval MODULE_EXPORT MQUALIFIER create##__namespace(NAMESPACE_Zeus::IXMLNode* pMainNode, NAMESPACE_Zeus::IXMLDocument*, NAMESPACE_Zeus::IXObject*& rpObj) \
{ \
  Retval retValue = RET_INTERNAL_ERROR; \
  \
  if (pMainNode != NULL) \
  { \
    rpObj = new __namespace::classid(*pMainNode); \
    retValue = RET_NOERROR; \
  } \
  \
  return retValue; \
} \


//###########################################################################
// INTERNAL REGISTER MACROS
/**************************************************************************/
/*! Declaration of autoregistration and factory method to create a 
    XRootObject using the XObjectFactory.
    \param classid : ID of the class to be registered
*/
/**************************************************************************/
#define REG_ROOT_BEGIN(classid) \
  protected: \
    static Retval MQUALIFIER createXRootObject(IXMLNode* pMainNode, IXMLDocument* pDocu, IXObject*& rpObj) \
    { \
      Retval retValue = RET_REQUEST_FAILED; \
      if (pMainNode != NULL && pDocu != NULL) \
      { \
        rpObj = new classid(*pMainNode, *pDocu); \
        retValue = RET_NOERROR; \
      } \
      else \
      { \
        retValue = RET_INTERNAL_ERROR; \
      } \
      return retValue; \
    } \
  public: \
    static bool autoregRoot(bool reg) \
    { \
      TString strClassName;\
      
/**************************************************************************/
/*! Entry of autoregistration. This will be added to the database of the
    XObjectFactory. 
    \param classid : ID of the class
    \param classname: String value representing the class name
*/
/**************************************************************************/
#define REG_ROOT_ADD(classid, classname) \
      strClassName = classname; \
      static Uint classid##Handle = 0;\
      if (reg)\
      {\
        classid##Handle = TXObjectFactory::getInstance().registerXClass(strClassName, createXRootObject); \
      }\
      else\
      {\
        TXObjectFactory::getInstance().unregisterXClass(classid##Handle, strClassName); \
      }

/**************************************************************************/
/*! End of registration.
*/
/**************************************************************************/
#define REG_ROOT_END \
      return true;\
    }
      
/**************************************************************************/
/*! Declaration of autoregistration and factory method to create a 
    XObject using the XObjectFactory. Those Objects are sub objects of a 
    XRootObject.
    \param classid : ID of the class to be registered
*/
/**************************************************************************/
#define REG_SUB_BEGIN(classid) \
  protected: \
    static Retval MQUALIFIER createXObject(IXMLNode* pMainNode, IXMLDocument* /*docu*/, IXObject*& rpObj) \
    { \
      Retval retVal = RET_REQUEST_FAILED; \
      if (pMainNode != NULL) \
      { \
        rpObj = new classid(*pMainNode); \
        retVal = RET_NOERROR; \
      } \
      else \
      { \
        retVal = RET_INTERNAL_ERROR; \
      } \
      return retVal; \
    } \
  public: \
    static bool autoregSub(bool reg) \
    { \
      TString strClassName;\

/**************************************************************************/
/*! Entry of autoregistration. This will be added to the database of the
    XObjectFactory. 
    \param classid : ID of the class
    \param classname: String value representing the class name
*/
/**************************************************************************/
#define REG_SUB_ADD(classid, classname) \
      strClassName = classname; \
      static Uint classid##Handle = 0;\
      if (reg)\
      {\
        classid##Handle = TXObjectFactory::getInstance().registerXClass(strClassName, createXObject); \
      }\
      else\
      {\
        TXObjectFactory::getInstance().unregisterXClass(classid##Handle, strClassName); \
      }

/**************************************************************************/
/*! End of registration, same as REG_ROOT_END
*/
/**************************************************************************/
#define REG_SUB_END \
      REG_ROOT_END
              

/**************************************************************************/
/*! Implementation of the registration. This will registrate the class 
    explicitly.
*/
/**************************************************************************/
#define XOBJECTFACTORY_REGISTER_ROOT(classid) \
classid::autoregRoot(true);

/**************************************************************************/
/*! Implementation of the unregistration. This will unregistrate the class 
    explicitly.
*/
/**************************************************************************/
#define XOBJECTFACTORY_UNREGISTER_ROOT(classid) \
classid::autoregRoot(false);
    
/**************************************************************************/
/*! Implementation of the registration. This will registrate the class 
    explicitly.
*/
/**************************************************************************/
#define XOBJECTFACTORY_REGISTER_SUB(classid) \
classid::autoregSub(true);

/**************************************************************************/
/*! Implementation of the unregistration. This will unregistrate the class 
    explicitly.
*/
/**************************************************************************/
#define XOBJECTFACTORY_UNREGISTER_SUB(classid) \
classid::autoregSub(false);



#endif
