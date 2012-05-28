/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXObjectFactory
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 1.08.08 11:31 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXObjectFactory.hpp $
** 
** 17    1.08.08 11:31 Bha
** new method added to create objects out of any Xml node
** 
** 16    8.04.08 14:19 Bha
** Usage of GUID for Interfaces
** 
** 15    8.04.08 14:03 Ast
** Dokumentation nachgeführt
** 
** 14    7.04.08 10:39 Ast
** createChildObjectBySchema added
** 
** 13    7.01.08 8:44 Bha
** Method to use Error-X-Object
** 
** 12    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 11    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXObjectFactoryHPP
#define IXObjectFactoryHPP

#include <zeusbase/System/Interfaces/IXObject.hpp>
#include <zeusbase/System/Interfaces/IXMLNode.hpp>
#include <zeusbase/System/Interfaces/IXMLDocument.hpp>

#ifdef ENABLE_GUID_USAGE
  // {CC4A6C6F-E41A-4127-9E70-320D551BED4A}
  #define INTERFACE_IXObjectFactory     TIID(0xcc4a6c6f, 0xe41a, 0x4127, 0x9e, 0x70, 0x32, 0xd, 0x55, 0x1b, 0xed, 0x4a)
#else
  #define INTERFACE_IXObjectFactory     0x00000005
#endif

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines the x object factory. It can create a x object
    tree out of a xml stream or xml file. 
*/
/***************************************************************************/
class IXObjectFactory : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXObjectFactory)
  
  public:  

    /***********************************************************************/
    /*! This creates a xrootobject out of a xml stream.
        \param rStream : Stream data (xml format)
        \param rpObj : Return parameter of created xrootobject
        \param bOnlyRoot : Creates only the root object
        \param bDoUnfreeze : If this flag is set, the object tree will be
            unfrozen after creation
        \retval RET_UNREGISTERED_CLASS : Class is not registered
        \retval RET_REQUEST_FAILED : No valid XML
        \retval RET_INTERNAL_ERROR : Internal Error occured
        \retval RET_NOERROR : Object created
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createObjectFromStream(const IString& rStream,
                                                     IXObject*& rpObj,
                                                     bool bOnlyRoot = true,
                                                     bool bDoUnfreeze = true) = 0;
    
    /***********************************************************************/
    /*! This creates only a xrootobject out of a xml stream.
        \param rFileName : File name
        \param rpObj : Return parameter of created xrootobject
        \param bOnlyRoot : Creates only the root object
        \param bDoUnfreeze : If this flag is set, the object tree will be
            unfrozen after creation
        \retval RET_UNREGISTERED_CLASS : Class is not registered
        \retval RET_REQUEST_FAILED : No valid XML
        \retval RET_INTERNAL_ERROR : Internal Error occured
        \retval RET_NOERROR : Object created
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createObjectFromFile(const IString& rFileName,
                                                   IXObject*& rpObj,
                                                   bool bOnlyRoot = true,
                                                   bool bDoUnfreeze = true)=0;
    
    /***********************************************************************/
    /*! This creates all child objects of a existing parent object. This 
        method can been called to create all children to a later point of 
        time.
        \param rParentNode : Parent XML Node
        \param rParent : Parent Object
        \param bDoUnfreeze : If this flag is set, the child object will be
            unfrozen after creation
        \retval RET_INTERNAL_ERROR : Internal Error occured
        \retval RET_NOERROR : Object created
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createChildObjects(IXMLNode& rParentNode,
                                                 IXObject& rParent,
                                                 bool bDoUnfreeze = true)=0;
        
    /***********************************************************************/
    /*! This creates all child objects of a new XML node and add them to the
        parent
        \param rNewNode : New XML Node
        \param rParent : Parent Object
        \param rpChild : return of the child object
        \param bDoUnfreeze : If this flag is set, the child object will be
            unfrozen after creation
        \param pRightSibling : If this parameter is a valid child object
                               of the parent, the new child object will be
                               added before this object
        \retval RET_INTERNAL_ERROR : Internal Error occured
        \retval RET_NOERROR : Object created
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER addNewChildObjects(IXMLNode& rNewNode,
                                                 IXObject& rParent,
                                                 IXObject*& rpChild,
                                                 bool bDoUnfreeze = true,
                                                 IXObject* pRightSibling = NULL)=0;
    
    /***********************************************************************/
    /*! This method registeres a factory method to create a specific xobject
        named by classname
        \param rClassName : Name of class
        \param pFunct : Function to call
        \return Handle. If the handle is = 0xFFFFFFFF the registration failed
    */
    /***********************************************************************/
    virtual Uint32 MQUALIFIER registerXClass(const IString& rClassName, IXObject::FCreateXObject pFunct)=0;
    
    /***********************************************************************/
    /*! This method unregisteres a factory method 
        \param uiHandle : Handle of the registration
        \param rClassName : Name of class
        \retval true : Class unregistered
        \retval false : Could not unregister class
    */
    /***********************************************************************/
    virtual bool MQUALIFIER unregisterXClass(Uint uiHandle, const IString& rClassName)=0;
    
    /***********************************************************************/
    /*! This creates a xrootobject out of a xml document.
        \param rDocument : XML Document
        \param rpObj : Return parameter of created xrootobject
        \param bOnlyRoot : Creates only the root object
        \param bDoUnfreeze : If this flag is set, the object tree will be
            unfrozen after creation
        \retval RET_UNREGISTERED_CLASS : Class is not registered
        \retval RET_REQUEST_FAILED : No valid XML
        \retval RET_INTERNAL_ERROR : Internal Error occured
        \retval RET_INVALID_DATA : Not a valid XML Format
        \retval RET_NOERROR : Object created
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createObjectFromDocument(IXMLDocument& rDocument,
                                                       IXObject*& rpObj,
                                                       bool bOnlyRoot = true,
                                                       bool bDoUnfreeze = true) = 0;

    /***********************************************************************/
    /*! This property must be set to expand the x-object tree with all
        possible x-object node, even they can not be created with the
        correct object classes. Therefore the error object will be created.
        This property is set to false as default, meaning the objects are
        not created and put to the tree if the correct class can not be
        found.
        \param bValue : property flag
    */
    /***********************************************************************/
    virtual void MQUALIFIER setErrorObjectExpandProperty(bool bValue) = 0;

    /***********************************************************************/
    /*! This creates a child object of a XSD schema template and add them to
        the parent.
        \param rName : Name of the XObject
        \param rParent : Parent Object
        \param rSchemaNode : XSD-Schema node with the definition of the XObject
                             (xsd:complexType).
        \param rpChildObj : Return of the child object
        \param bDoUnfreeze : If this flag is set, the child object will be
            unfrozen after creation
        \retval RET_NOERROR : Object created
        \retval RET_INTERNAL_ERROR : Internal Error occured
        \retval RET_INVALID_PARAMETER : Parameter rSchemaNode is not a valid
                                        XSD node
        \retval RET_INVALID_TYPE : Type definition not found
        \retval RET_ABORT : Maximum count of XObject of this parent reached
        \retval RET_REQUEST_FAILED : No valid XML
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createChildObjectBySchema(const IString& rName,
                                                        IXObject& rParent,
                                                        IXMLNode&  rSchemaNode,
                                                        IXObject*& rpChildObj,
                                                        bool bDoUnfreeze = true) = 0;

    /***********************************************************************/
    /*! This method creates an object tree out of an Xml node
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createObjectByXMLNode(IXMLNode& rMainNode,
                                                    NAMESPACE_Zeus::IXMLDocument* pDocu,
                                                    IXObject*& rpObj,
                                                    bool bDoUnfreeze = true) = 0;

};

END_NAMESPACE_Zeus

#endif
