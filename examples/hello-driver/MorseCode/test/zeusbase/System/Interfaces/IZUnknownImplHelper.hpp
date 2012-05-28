/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IZUnknownImplHelper
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 22.04.08 10:44 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IZUnknownImplHelper.hpp $
** 
** 18    22.04.08 10:44 Mab
** Elimination using ns zeus in Headerfiles.
** 
** 17    21.04.08 15:06 Mab
** Elimination using ns zeus aus Headerfiles.
** 
** 16    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 15    15.10.07 15:20 bha
** Macros for object exports added
** 
** 14    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 13    25.04.07 16:22 Mabbuehl
** Visual Studio 6.0 level 4 warnings reduced.
** 
** 12    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
** 
** 10    20.02.07 10:19 bha
** Ueberarbeiten von ICAST's
**
** 7     5.10.06 6:38 bha
** Stack types can hide addRef and release methods inside their interfaces
***************************************************************************/

#ifndef IZUnknownImplHelperHPP
#define IZUnknownImplHelperHPP

#include <zeusbase/Config/PlatformDefines.hpp>

//###########################################################################
// MACROS FOR MEMORY MANAGAGER
/**************************************************************************/
/*! \def MEMORY_MANAGER_DECL
    This macro defines the declaration part of the memory management.
*/
/**************************************************************************/
#define MEMORY_MANAGER_DECL \
    virtual NAMESPACE_Zeus::Retval MQUALIFIER askForInterface(const NAMESPACE_Zeus::InterfaceID& rInterfaceID, NAMESPACE_Zeus::IZUnknown*& rpIface);\
    virtual void MQUALIFIER addRef() const;\
    virtual void MQUALIFIER release() const;




//--------------------------------------------------------------------------
// Defines the start of the askForInterface Method. Do not use directly
#ifdef ENABLE_GUID_USAGE

#define INTERFACE_CAST_START(classid) \
  NAMESPACE_Zeus::Retval MQUALIFIER classid::askForInterface(const NAMESPACE_Zeus::InterfaceID& rInterfaceID, NAMESPACE_Zeus::IZUnknown*& rpIface)\
  {

#else //ndef ENABLE_GUID_USAGE

#define INTERFACE_CAST_START(classid) \
  NAMESPACE_Zeus::Retval MQUALIFIER classid::askForInterface(const NAMESPACE_Zeus::InterfaceID& rInterfaceID, NAMESPACE_Zeus::IZUnknown*& rpIface)\
  { \
    NAMESPACE_Zeus::Retval retVal; \
    switch(rInterfaceID) \
    {

#endif //ENABLE_GUID_USAGE
//--------------------------------------------------------------------------




//--------------------------------------------------------------------------
// Defines the start of the askForInterface Method. Do not use directly
#ifdef ENABLE_GUID_USAGE

#define INLINE_INTERFACE_CAST_START \
  NAMESPACE_Zeus::Retval MQUALIFIER askForInterface(const NAMESPACE_Zeus::InterfaceID& rInterfaceID, NAMESPACE_Zeus::IZUnknown*& rpIface)\
  {

#else //ndef ENABLE_GUID_USAGE

#define INLINE_INTERFACE_CAST_START \
  NAMESPACE_Zeus::Retval MQUALIFIER askForInterface(const NAMESPACE_Zeus::InterfaceID& rInterfaceID, NAMESPACE_Zeus::IZUnknown*& rpIface)\
  { \
    NAMESPACE_Zeus::Retval retVal; \
    switch(rInterfaceID) \
    {

#endif //ENABLE_GUID_USAGE
//--------------------------------------------------------------------------


/**************************************************************************/
/*! \def MEMORY_MANAGER_IMPL_PARENT
    Implementation of the memory management. This part of the memory
    management delegates it to a parent class.
    \param classid : ID of the class
    \param parent : ID of the parent class
*/
/**************************************************************************/
#define MEMORY_MANAGER_IMPL_PARENT(classid, parent) \
  typedef parent TempParent;\
  void MQUALIFIER classid::addRef() const\
  { \
    TempParent::addRef(); \
  } \
  void MQUALIFIER classid::release() const\
  { \
    TempParent::release(); \
  } \
  INTERFACE_CAST_START(classid)


/**************************************************************************/
/*! \def MEMORY_MANAGER_INLINEIMPL_PARENT
    Inline implementation of the memory management. This part of the memory
    management delegates it to a parent class.
    \param classid : ID of the class
    \param parent : ID of the parent class
*/
/**************************************************************************/
#define MEMORY_MANAGER_INLINEIMPL_PARENT(parent) \
  typedef parent TempParent;\
  void MQUALIFIER addRef() const\
  { \
    TempParent::addRef(); \
  } \
  void MQUALIFIER release() const\
  { \
    TempParent::release(); \
  } \
  INLINE_INTERFACE_CAST_START


/**************************************************************************/
/*! \def MEMORY_MANAGER_IMPL
    This macro is similar to the MEMORY_MANAGER_IMPL_PARENT macro. It uses
    the TZObject as parent class.
    \param classid : ID of the class
*/
/**************************************************************************/
#define MEMORY_MANAGER_IMPL(classid) \
  MEMORY_MANAGER_IMPL_PARENT(classid, NAMESPACE_Zeus::TZObject)

/**************************************************************************/
/*! \def MEMORY_MANAGER_IMPL
    This macro is similar to the MEMORY_MANAGER_IMPL_PARENT macro. It uses
    the TZObject as parent class.
    \param classid : ID of the class
*/
/**************************************************************************/
#define MEMORY_MANAGER_INLINEIMPL() \
  MEMORY_MANAGER_INLINEIMPL_PARENT(NAMESPACE_Zeus::TZObject)


/**************************************************************************/
/*! Implementation of memorymanagement using a lock object. It uses the
    TZObject as a parent class. if the lock object is NULL, it works like
    the macro MEMORY_MANAGER_IMPL
    \param classid : ID of the class
    \param lock : Lock object
*/
/**************************************************************************/
#define MEMORY_MANAGER_IMPL_LOCK(classid, lock) \
  void MQUALIFIER classid::addRef() const\
  { \
    NAMESPACE_Zeus::TCriticalSection* pSection = (NAMESPACE_Zeus::TCriticalSection*)lock;\
    if (pSection != NULL)\
    { \
      pSection->enter();\
    } \
    typedef NAMESPACE_Zeus::TZObject TempTZObject;\
    TempTZObject::addRef(); \
    if (pSection != NULL)\
    { \
      pSection->leave();\
    }\
  } \
  void MQUALIFIER classid::release() const\
  { \
    NAMESPACE_Zeus::TCriticalSection* pSection = (NAMESPACE_Zeus::TCriticalSection*)lock;\
    if (pSection != NULL)\
    { \
      pSection->enter();\
    }\
    typedef NAMESPACE_Zeus::TZObject TempTZObject;\
    if (getRefCounter() == 1)\
    {\
      if (pSection != NULL)\
      { \
        pSection->leave();\
      }\
      TempTZObject::release(); \
    }\
    else\
    {\
      TempTZObject::release(); \
      if (pSection != NULL)\
      { \
        pSection->leave();\
      }\
    }\
  } \
  INTERFACE_CAST_START(classid)

/**************************************************************************/
/*! \def INTERFACE_CAST
    This macro is used to cast the object according the interface_id. The
    casting class must be specified and inherited.
    \param interface_type : Class id of the interface
    \param interface_id : Nummeric value representing an interface
*/
/**************************************************************************/
#define INTERFACE_CAST(interface_type, interface_id) \
  INTERFACE_CAST_VAR(interface_type, interface_id, this)

//--------------------------------------------------------------------------
#ifdef ENABLE_GUID_USAGE

/**************************************************************************/
/*! \def INTERFACE_CAST_VAR
    This macro is used to cast the object according the interface_id. The
    casting class must be specified and inherited.
    \param interface_type : Class id of the interface
    \param interface_id : Nummeric value representing an interface
    \param variable_ : variable to cast. normally its the this ptr
*/
/**************************************************************************/
#define INTERFACE_CAST_VAR(interface_type, interface_id, variable_) \
      typedef NAMESPACE_Zeus::TGUIDWrapper TempTGUIDWrapper;\
      if (TempTGUIDWrapper::isEqual(rInterfaceID, interface_id)) \
      {\
        rpIface = (interface_type*)variable_; \
        variable_->addRef(); \
        return RET_NOERROR; \
      }\

#else //ndef ENABLE_GUID_USAGE

/**************************************************************************/
/*! \def INTERFACE_CAST
    This macro is used to cast the object according the interface_id. The
    casting class must be specified and inherited.
    \param interface_type : Class id of the interface
    \param interface_id : Nummeric value representing an interface
    \param variable_ : variable to cast. normally its the this ptr
*/
/**************************************************************************/
#define INTERFACE_CAST_VAR(interface_type, interface_id, variable_) \
      case interface_id : \
        rpIface = (interface_type*)variable_; \
        variable_->addRef(); \
        retVal = RET_NOERROR; \
      break;\

#endif //ndef ENABLE_GUID_USAGE
//--------------------------------------------------------------------------




//--------------------------------------------------------------------------
#ifdef ENABLE_GUID_USAGE

/**************************************************************************/
/* \def MEMORY_MANAGER_IMPL_PARENT_END
   End of memory management implementation.
   \param parent : Class id of the parent class
*/
/**************************************************************************/
#define MEMORY_MANAGER_IMPL_PARENT_END(parent) \
    typedef parent TempParent;\
    return TempParent::askForInterface(rInterfaceID, rpIface); \
  }\

#else //ndef ENABLE_GUID_USAGE

/**************************************************************************/
/* \def MEMORY_MANAGER_IMPL_PARENT_END
   End of memory management implementation.
   \param parent : Class id of the parent class
*/
/**************************************************************************/
#define MEMORY_MANAGER_IMPL_PARENT_END(parent) \
      default: \
        typedef parent TempParent;\
        retVal = TempParent::askForInterface(rInterfaceID, rpIface); \
      break; \
    } \
    return retVal; \
  }\

#endif //ndef ENABLE_GUID_USAGE
//--------------------------------------------------------------------------




/**************************************************************************/
/* \def MEMORY_MANAGER_IMPL_END
   End of memory management implementation. Same as macro
   MEMORY_MANAGER_IMPL_PARENT_END. The parent will be TZObject.
*/
/**************************************************************************/
#define MEMORY_MANAGER_IMPL_END \
  MEMORY_MANAGER_IMPL_PARENT_END(NAMESPACE_Zeus::TZObject)


/**************************************************************************/
/*! \def ICAST : This macro is used to call askForInterface without
                 writing casts directly in your code.
                 askForInterface(INTERFACE_ISerializable, ICAST(pSerialObj)).
    \param variable : Variable to cast
*/
/**************************************************************************/
#define ICAST(variable) (NAMESPACE_Zeus::IZUnknown*&)variable


/**************************************************************************/
/*! \def HIDE_MEMORY_MANAGER_DEF
    This macro hides the declaration part of the memory management for
    stack objects
*/
/**************************************************************************/
#define HIDE_MEMORY_MANAGER_DEF \
  protected: \
    virtual NAMESPACE_Zeus::Retval MQUALIFIER askForInterface(const NAMESPACE_Zeus::InterfaceID& rInterfaceID, NAMESPACE_Zeus::IZUnknown*& rpIface)=0;\
    virtual void MQUALIFIER addRef() const=0;\
    virtual void MQUALIFIER release() const=0;


//###########################################################################
// EXPORT FUNCTION MACROS for regular interfaces
/***************************************************************************/
/*! \def MExportObjectFactory Defines a factory method witch will be
                             exported by the library and creates a new
                             Object from ClassName
*/
/***************************************************************************/
#define MExportObjectFactory(InterFace, ClassName)\
MODULE_EXPORT_PRE NAMESPACE_Zeus::Retval MODULE_EXPORT MQUALIFIER create##InterFace(NAMESPACE_Zeus::IZUnknown*& rpIface)\
{\
  rpIface = (InterFace*)new ClassName();\
  return RET_NOERROR;\
}\

/***************************************************************************/
/*! \def MExportSingletonObject Defines a method witch will be
                             exported by the library to access singleton
                             objects by other modules
*/
/***************************************************************************/
#define MExportSingletonObject(InterFace, SingletonObj)\
MODULE_EXPORT_PRE NAMESPACE_Zeus::Retval MODULE_EXPORT MQUALIFIER create##InterFace(NAMESPACE_Zeus::IZUnknown*& rpIface)\
{\
  rpIface = (InterFace*)&SingletonObj;\
  SingletonObj.addRef(); \
  return RET_NOERROR;\
}\

//###########################################################################
// HIDDING OF METHDOS
/**************************************************************************/
/*! \def HIDE_ASSIGNMENT_OPERATOR

    This macro hides the assignment operator of a class given an
    object of the same class.

    \param class_type: Class type.
*/
/**************************************************************************/
#ifdef ZEUS_DEBUG
  #define HIDE_ASSIGNMENT_OPERATOR(class_type)             \
    private:                                             \
      inline void operator=(const class_type& /* Object */) { }
#else
  #define HIDE_ASSIGNMENT_OPERATOR(class_type)
#endif

/**************************************************************************/
/*! \def HIDE_DESTRUCTOR

    This macro hides the destructor of a class given an
    object of the same class.

    \param class_type: Class type.
*/
/**************************************************************************/
#ifdef ZEUS_DEBUG
  #define HIDE_DESTRUCTOR(class_type)
/*  #define HIDE_DESTRUCTOR(class_type)             \
    protected:                                             \
      inline virtual ~class_type() {}
*/
#else
  #define HIDE_DESTRUCTOR(class_type)
#endif


#endif

