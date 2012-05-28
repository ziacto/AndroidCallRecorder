/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IZObjectFactory
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 7.04.08 19:08 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IZObjectFactory.hpp $
** 
** 17    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 16    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 15    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

 
#ifndef IZObjectFactoryHPP
#define IZObjectFactoryHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IByteArray.hpp>
#include <zeusbase/System/Interfaces/IInputStream.hpp>
#include <zeusbase/System/Interfaces/IOutputStream.hpp>

#ifdef ENABLE_GUID_USAGE
  // {7D68F304-D382-44e6-90E5-0E6B7237E722}
  #define INTERFACE_IZObjectFactory     TIID(0x7d68f304, 0xd382, 0x44e6, 0x90, 0xe5, 0xe, 0x6b, 0x72, 0x37, 0xe7, 0x22)
#else
  #define INTERFACE_IZObjectFactory     0x00000009
#endif


BEGIN_NAMESPACE_Zeus


/***************************************************************************/
/*! The IZObjectFactory Interface defines the factory to create serializable
    objects by class name and streaming information 
*/
/***************************************************************************/
class IZObjectFactory : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IZObjectFactory)
  
  public:
    //function definition for factory methods
    #ifdef _MSC_VER
      typedef Retval (MQUALIFIER *FCreateZObject)(Uint uiObjectID, IInputStream* pStream, IZUnknown*& rpObj);
    #else
      typedef Retval MQUALIFIER (*FCreateZObject)(Uint uiObjectID, IInputStream* pStream, IZUnknown*& rpObj);
    #endif
    /***********************************************************************/
    /*! Factory method to create a registered serializable object out of a 
        byte stream.
        \param rStream : Byte stream
        \param rInterfaceID : Interface to cast
        \param rpObj : Return value of created object
        \retval RET_NOERROR : Object created
        \retval RET_REQUEST_FAILED : Invalid stream or Object could not be 
                   created. Eventually not a registered class
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createObjectFromStream(const IByteArray& rStream, const InterfaceID& rInterfaceID, IZUnknown*& rpObj)=0;
    
    /***********************************************************************/
    /*! Factory method to create a registered serializable object 
        according to the classname. This will return a empty object created
        with the standard constructor
        \param rClassName : Name of the class
        \param rCodeModule : Code module
        \param rpObj : Return value of created object
        \retval RET_NOERROR : Object created
        \retval RET_REQUEST_FAILED : not a registered class
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createObjectByClassName(const IString& rClassName, const IString& rCodeModule, IZUnknown*& rpObj)=0;

    /***********************************************************************/
    /*! Register a class
        \param rName : Name of the class
        \param pFunction : Factory function to call for creating an object
                          of this class
        \return Handle of the creation. If handle is NULL (0) the
                          registration failed
    */
    /***********************************************************************/
    virtual Uint MQUALIFIER registerClass(const IString& rName, IZObjectFactory::FCreateZObject pFunction)=0;

    /***********************************************************************/
    /*! Unregsiter a registered class
        \param rName : Name of the class
        \param uiHandle : Handle received by the registration
        \retval RET_NOERROR : Class unregistered
        \retval RET_REQUEST_FAILED : Invalid handle or class not registered
        \retval RET_INVALID_PARAMETER : Invalid parameter received.
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER unregisterClass(const IString& rName, Uint uiHandle)=0;


};


END_NAMESPACE_Zeus

#endif
