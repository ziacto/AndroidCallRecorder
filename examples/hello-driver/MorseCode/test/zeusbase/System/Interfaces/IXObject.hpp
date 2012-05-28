/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXObject
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 17.04.08 7:16 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXObject.hpp $
** 
** 29    17.04.08 7:16 Bha
** methods to read and write timeval attributes
** 
** 28    15.04.08 7:30 Ast
** Neuer Typ list
** 
** 27    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 26    4.04.08 9:47 Ast
** getExtXMLRefNode deleted
** 
** 25    2.04.08 14:14 Ast
** Method getExtXMLRefNode added
** 
** 24    14.01.08 14:28 Bha
** XMember interface defined
** 
** 23    7.01.08 9:20 Bha
** New methods to access X-Members
** 
** 22    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 21    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
**
** 16    20.10.06 10:23 bha
** Redesign of IXObject interface
***************************************************************************/

#ifndef IXObjectHPP
#define IXObjectHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IByteArray.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IStringList.hpp>
#include <zeusbase/System/Interfaces/ICriticalSection.hpp>
#include <zeusbase/System/Interfaces/IXMLNode.hpp>
#include <zeusbase/System/Interfaces/IXMLDocument.hpp>
#include <zeusbase/System/Interfaces/IXObjectImplHelper.hpp>

#ifdef ENABLE_GUID_USAGE
  // {A0F2EF68-C7E8-46cb-993A-B4CF5CBA5EA7}
  #define INTERFACE_IXObject      TIID(0xa0f2ef68, 0xc7e8, 0x46cb, 0x99, 0x3a, 0xb4, 0xcf, 0x5c, 0xba, 0x5e, 0xa7)
#else
  #define INTERFACE_IXObject      0x00000003
#endif


BEGIN_NAMESPACE_Zeus

class ISimpleCommand;
class IXObject;
class IZVariant;

//###########################################################################
//                     INTERFACE IXObjectCollection

/***************************************************************************/
/*! This interface defines a collection of XObjects. This may be used
    as a query result of getting objects out of a tree
*/
/***************************************************************************/
class IXObjectCollection : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXObjectCollection)
  
  public:
    /***********************************************************************/
    /*! This returns the number of objects inside this collection
        \return number of objects
    */
    /***********************************************************************/
    virtual Int MQUALIFIER getCount()const=0;

    /***********************************************************************/
    /*! This method returns an indexed object out of the collection
        \param iIndex : Index of the object
        \param rpObject : Return parameter
        \retval RET_NOERROR : Object returned
        \retval RET_REQUEST_FAILED : Could not find indexed object
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getObject(Int iIndex, IXObject*& rpObject) const = 0;

    /***********************************************************************/
    /*! This gets the next object using an internal iterator of the
        collection.
        \param rpObject : Return parameter
        \retval RET_NOERROR : Object returned
        \retval RET_REQUEST_FAILED : Could not find next object
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getNextObject(IXObject*& rpObject) const = 0;

    /***********************************************************************/
    /*! This gets the next object using an internal iterator of the
        collection. The object will be casted with the corresponding interface
        ID. If the cast fails, automatically the next matching object will be
        returned
        \param uiInterfaceID : ID of the interface
        \param rpObject : Return parameter
        \retval RET_NOERROR : Object returned
        \retval RET_REQUEST_FAILED : Could not find next object
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getNextCastedObject(const InterfaceID& rInterfaceID, IZUnknown*& rpObject) const = 0;

    /***********************************************************************/
    /*! Resets the internal iterator
    */
    /***********************************************************************/
    virtual void MQUALIFIER reset() const = 0;
};



//###########################################################################
//                       INTERFACE IXMemberVariable

/***************************************************************************/
/*! This interface defines a X-Object member
*/
/***************************************************************************/
class IXMemberVariable : public IZUnknown
{
  public:
    /************************************************************************/
    /*! Available member types
    */
    /************************************************************************/
    enum EVariableType
    {
      etXMLNode = 0,
      etInt = 1,
      etUint = 2,
      etFloat = 3,
      etBoolean = 4,
      etString = 5,
      etObjectRef = 6,
      etList = 7
    };

    /************************************************************************/
    /*! Returns the member type
    */
    /************************************************************************/
    virtual EVariableType MQUALIFIER getMemberType() const = 0;

    /************************************************************************/
    /*! Returns the name of the variable
        \param rName : return parameter
    */
    /************************************************************************/
    virtual void MQUALIFIER getName(IString& rName) const = 0;

    /************************************************************************/
    /*! returns the string value
        \param rValue : return parameter
        \retval RET_NOERROR : Value returned
        \retval RET_INVALID_TYPE: invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER getString(IString& rValue) const = 0;

    /************************************************************************/
    /*! returns the member value
        \param rValue : variant value to return
        \retval RET_NOERROR : Value returned
        \retval RET_INVALID_TYPE: Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER getValue(IZVariant& rValue) const = 0;

    /************************************************************************/
    /*! returns the XML node
        \param rpValue : return parameter
        \retval RET_NOERROR : XML node returned
        \retval RET_REQUEST_FAILED : not a XML value type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER getXMLNode(IXMLNode*& rpValue) const = 0;

    /************************************************************************/
    /*! Sets the string value
        \retval RET_NOERROR : Value set
        \retval RET_INVALID_TYPE: Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER setValue(const IZVariant& rValue) = 0;

    /************************************************************************/
    /*! sets the member value
        \param rValue : variant value to set
        \retval RET_NOERROR : Value set
        \retval RET_INVALID_TYPE: Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER setString(const IString& rValue) = 0;

    /************************************************************************/
    /*! Returns the items of list type as a IXPathResult
        \param rpValue : Item list
        \retval RET_NOERROR : List returned
        \retval RET_INVALID_TYPE: Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER getListItems(IXPathResults*& rpList) const = 0;

    /************************************************************************/
    /*! Returns the indexed item at position iIndex of list type
        \param iIndex : Index of requested item
        \param rpValue : Item at [iIndex]
        \retval RET_NOERROR : Item returned
        \retval RET_REQUEST_FAILED : Invalid item index
        \retval RET_INVALID_TYPE : Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER getListItem(const Int iIndex, IXMLNode*& rpItem) const = 0;

    /************************************************************************/
    /*! Adds an item to the list
        \param rpValue : Inserted item
        \retval RET_NOERROR : Item inserted
        \retval RET_REQUEST_FAILED : Wasn't able to add a new item
        \retval RET_INVALID_TYPE : Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER addListItem(IXMLNode*& rpItem) = 0;

    /************************************************************************/
    /*! Inserts an item into the list at position iIndex of list type
        \post if iIndex = 0, then the rItem is
              placed in the front (prepend); if the iIndex >= count or iIndex
              < 0 , the item is placed at the end (append); else the rItem is
              placed at position iIndex
        \param iIndex : Insert position
        \param rpValue : Item to insert
        \retval RET_NOERROR : Item inserted
        \retval RET_REQUEST_FAILED : Wasn't able to insert a new item
        \retval RET_INVALID_TYPE: Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER insertListItem(const Int iIndex, IXMLNode*& rpItem) = 0;

    /************************************************************************/
    /*! Removes an element out of the list
        \param iIndex : Index of the element to remove  
        \retval RET_NOERROR : Element removed
        \retval RET_INVALID_TYPE: Invalid variable type
    */
    /************************************************************************/
    virtual Retval MQUALIFIER deleteListItem(const Int iIndex) = 0;

};

//###########################################################################
//                          INTERFACE IXObject

/***************************************************************************/
/*! This interface defines a X-Object interface. An X-Object wrapps a XML
    node and can be created using automated factories. X-Objects are used
    to created object trees and for persistent object layers using xml.
*/
/***************************************************************************/
class IXObject : public IZUnknown
{
  public:
    //function definition for factory methods
    #ifdef _MSC_VER
      typedef Retval (MQUALIFIER *FCreateXObject)(IXMLNode* pMainNode, IXMLDocument* pDocu, IXObject*& rpObj);
    #else
      typedef Retval MQUALIFIER (*FCreateXObject)(IXMLNode* pMainNode, IXMLDocument* pDocu, IXObject*& rpObj);
    #endif

    /***********************************************************************/
    /*! This methods returns the name of the object
        \param rName : return parameter
    */
    /***********************************************************************/
    virtual void MQUALIFIER getName(IString& rName)const=0;

    /***********************************************************************/
    /*! This methods returns the classname of the object
        \param rName : return parameter
    */
    /***********************************************************************/
    virtual void MQUALIFIER getClassName(IString& rName)const=0;

    /***********************************************************************/
    /*! This methods returns the id of an object
        \return id of object
    */
    /***********************************************************************/
    virtual Uint MQUALIFIER getID()const=0;
    
    /***********************************************************************/
    /*! This methods adds an XObject as a child to this object
        \param rChild : child object to add
        \retval RET_NOERROR : Child object added
        \retval RET_REQUEST_FAILED : Could not add object
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER addChild(IXObject& rChild)=0;
    
    /***********************************************************************/
    /*! Deletes a child out of the list.
        \param iIndex : Index of child to Remove
        \param bDoFreeze : Do unfreeze child
        \retval RET_NOERROR : Child deleted
        \retval RET_REQUEST_FAILED : Could not delete child.
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER deleteChild(Int iIndex, bool bDoFreeze=false) = 0;

    /***********************************************************************/
    /*! This methods removes an XObject
        \param rChild : child object to remove
        \param bDoFreeze : Do unfreeze child
        \retval RET_NOERROR : Child object added
        \retval RET_REQUEST_FAILED : Could not remove object
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER removeChild(IXObject& rChild, bool bDoFreeze=false)=0;
    
    /***********************************************************************/
    /*! Get count of the children
        \return count
    */
    /***********************************************************************/
    virtual Int MQUALIFIER getChildCount()const=0;
    
    /***********************************************************************/
    /*! Get a child object by index
        \param iIndex : Index of the object
        \param rpChild : Return parameter of the found object
        \retval RET_NOERROR : Child object found
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getChild(Int iIndex, IXObject*& rpChild)=0;

    /***********************************************************************/
    /*! Get a child object by name
        \param rName : Name of the object
        \param rpChild : Return parameter of the found object
        \retval RET_NOERROR : Child object found
        \retval RET_INVALID_PARAMETER : Invalid parameter received
        \retval RET_REQUEST_FAILED : No child found
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getChildByName(const IString& rName, IXObject*& rpChild)=0;

    /***********************************************************************/
    /*! Get children objects by name. If the name is empty, all children of
        this object are returned.
        \param rName : Name of the objects
        \param rpObjects : Return parameter of the found objects
        \retval RET_NOERROR : Child objects found
        \retval RET_INVALID_PARAMETER : Invalid parameter received
        \retval RET_REQUEST_FAILED : No child found
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getChildrenByName(const IString& rName, IXObjectCollection*& rpObjects)=0;

    /***********************************************************************/
    /*! Get the parent object
        \param rpParent : Return parameter of the found object
        \retval RET_NOERROR : parent found
        \retval RET_REQUEST_FAILED : No parent found -> this is the root object
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getParent(IXObject*& rpParent)const=0;
    
    /***********************************************************************/
    /*! Get the xml node of the xobject
        \param rpNode : return parameter of the xml node
        \retval RET_NOERROR : node returned
        \retval RET_REQUEST_FAILED : Could not get the xml node
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getXMLNode(IXMLNode*& rpNode) const=0;

    /***********************************************************************/
    /*! Set the parent object. Only for internal use
        \param pParent : Parameter to set. If NULL is set, the object resets its parent
        \retval RET_NOERROR : parent set
        \retval RET_REQUEST_FAILED : Could not set the parent
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER setParent(IXObject* pParent)=0;

    /***********************************************************************/
    /*! This methods sets an XObject as a child of this object. Do not use
        this method. Its only used by the factory creating the tree. Therefor
        the xml structure wont be touched. For adding children, use the method
        addChild() instead. It will update the xml structure as well.
        \param child : child object to add
        \retval RET_NOERROR : Child object added
        \retval RET_INVALID_PARAMETER : Invalid parameter received
        \retval RET_REQUEST_FAILED : Could not add object
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER setChild(IXObject& child)=0;

    /***********************************************************************/
    /*! Returns the root object of the object tree.
        \param obj : Return parameter
        \retval RET_NOERROR : Root object returned
        \retval RET_INVALID_PARAMETER : Invalid parameter received;
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getRootObject(IXObject*& rpObj)=0;
    
    /***********************************************************************/
    /*! This method is used to get an object from the tree. Therefor a
        special Syntax is used. <BR>
        \param rPath : Objectpath
        \param rpObj : Return parameter of the object
        \retval RET_NOERROR : object found and returned
        \retval RET_REQUEST_FAILED : Could not find object
        \retval RET_INVALID_DATA : Invalid path
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getObject(const IString& rPath, IXObject*& rpObj)=0;

    /***********************************************************************/
    /*! This method is used to get a object list from the tree. Therefore a
        special Syntax is used. <BR>
        \param rPath : Objectpath
        \param rpObjects : Return parameter of the objects
        \retval RET_NOERROR : objects found and returned
        \retval RET_INVALID_PARAMETER : Invalid parameter received
        \retval RET_REQUEST_FAILED : Could not find any objects
        \retval RET_INVALID_DATA : Invalid path
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getObjects(const IString& rPath, IXObjectCollection*& rpObjects)=0;

    /***********************************************************************/
    /*! This methods checks if the children components can be created 
        \retval true : Able to create children
        \retval false : Do not create children
    */
    /***********************************************************************/
    virtual bool MQUALIFIER canCreateChildren()const=0;
    
    /**********************************************************************/
    /*! This method freezes a xobject. All external references has to be
        released at that point.
        \retval true : Freezing has been performed
        \retval false : Already frozen
    */
    /**********************************************************************/
    virtual bool MQUALIFIER freeze()=0;

    /**********************************************************************/
    /*! This method unfreezes a xobject. The external References begin to
        live and are accecible for others
        \retval true : Unfreezing has been performed
        \retval false : Already unfrozen
    */
    /**********************************************************************/
    virtual bool MQUALIFIER unfreeze()=0;

    /**********************************************************************/
    /*! Checks if a xobject is frozen
        \retval true : xobject is frozen
        \retval false : xobject is alive
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isFrozen()const=0;
    
    /**********************************************************************/
    /*! This method sets a lock for the whole XObject tree. This enables
        a secure multithreading access to the xobject tree
        \param pSection : Lock object
    */
    /**********************************************************************/
    virtual void MQUALIFIER setTreeLock(ICriticalSection* pSection)=0;
    
    /**********************************************************************/
    /*! This locks the xobject tree. Before using this method, set a
        lock object using setTreeLock()
    */
    /**********************************************************************/
    virtual void MQUALIFIER lockTree()=0;
    
    /**********************************************************************/
    /*! Unlocks the xobject tree
    */
    /**********************************************************************/
    virtual void MQUALIFIER unlockTree()=0;

    /**********************************************************************/
    /*! Executes a simple command. This can be used as a action method
        \param rCommand : Command witch has been executed
        \param uiMode : Mode of execution
        \retval RET_NOERROR : Command executed
        \retval RET_REQUEST_FAILED : Command has not been understand
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER onExecute(ISimpleCommand& rCommand, Uint uiMode)=0;

    /**********************************************************************/
    /*! Handles and sents a broad cast message to all its children.
        \param rMessage : Message to perform
    */
    /**********************************************************************/
    virtual void MQUALIFIER onBroadCast(ISimpleCommand& rMessage)=0;

    /**********************************************************************/
    /*! This method inserts a child to the parent object. The child will be
        added at the insert position. If the insert position is bigger
        than the child list, it will add the child at the end of the list.
        \param iIndex : Insert position of the child
        \param rChild : Child reference
        \retval RET_REQUEST_FAILED : Could not inset the child object
        \retval RET_NOERROR : Child inserted
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER insertChild(Int iIndex, IXObject& rChild)=0;

    /**********************************************************************/
    /*! This method returns the index of a child object
        \param rChild : Child reference
        \return index of the child. -1 is returned when the child does not
                  exists inside the list.
    */
    /**********************************************************************/
    virtual Int MQUALIFIER indexOfChild(IXObject& rChild)=0;

    /**********************************************************************/
    /*! creates a new child object
        \param rName : Object name
        \param rClassName : Name of the class
        \param rCodeModule: Codemodule
        \param rpChild : Return parameter of the child object
        \retval RET_NOERROR : Child created
        \retval RET_INVALID_DATA : Could not generate XML data
        \retval RET_REQUEST_FAILED : Could not create child
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER createChildObject(const IString& rName,
                                                const IString& rClassName,
                                                const IString& rCodeModule,
                                                IXObject*& rpChild)=0;

    /**********************************************************************/
    /*! creates a new child object
        \param rName : Object name
        \param rClassName : Name of the class
        \param rCodeModule: Codemodule
        \param rList : List of attribute - value pairs
        \param rpChild : Return parameter of the child object
        \retval RET_NOERROR : Child created
        \retval RET_INVALID_DATA : Could not generate XML data
        \retval RET_REQUEST_FAILED : Could not create child
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER createChildObjectCustom(const IString& rName,
                                                      const IString& rClassName,
                                                      const IString& rCodeModule,
                                                      const IStringList& rList,
                                                      IXObject*& rpChild)=0;

    /***********************************************************************/
    /*! This method is used to get an object from the tree. Therefor a
        special Syntax is used. The object will be casted to the required
        type. If the cast fails, this method will return the next object
        with the corresponding name and interface id
        \param rPath : Objectpath
        \param uiInterfaceID : ID of the interface
        \param rpObj : Return parameter of the object
        \retval RET_NOERROR : object found and returned
        \retval RET_REQUEST_FAILED : Could not find object
        \retval RET_INVALID_DATA : Invalid path
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getCastedObject(const IString& rPath, const InterfaceID& rInterfaceID, IZUnknown*& rpObj) = 0;

    //Persistent layer methods for attributes
    /***********************************************************************/
    /*! Returns an integer attribute of the object.
        \param rName : Name of the attribute
        \param rValue : Return value
        \param iDefault : Default value if the attribute can not be converted
        \retval RET_NOERROR : Attribute returned
        \retval RET_REQUEST_FAILED : No such attribute found
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER readIntAttribute(const IString& rName, Int& rValue, Int iDefault = 0) const = 0;

    /***********************************************************************/
    /*! Returns an unsigned integer attribute of the object.
        \param rName : Name of the attribute
        \param rValue : Return value
        \param uiDefault : Default value if the attribute can not be converted
        \retval RET_NOERROR : Attribute returned
        \retval RET_REQUEST_FAILED : No such attribute found
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER readUintAttribute(const IString& rName, Uint& rValue, Uint uiDefault = 0) const = 0;

    /***********************************************************************/
    /*! Returns a float attribute of the object.
        \param rName : Name of the attribute
        \param rValue : Return value
        \param fDefault : Default value if the attribute can not be converted
        \retval RET_NOERROR : Attribute returned
        \retval RET_REQUEST_FAILED : No such attribute found
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER readFloatAttribute(const IString& rName, Float& rValue, Float fDefault = 0) const = 0;

    /***********************************************************************/
    /*! Returns a string attribute of the object.
        \param rName : Name of the attribute
        \param rValue : Return value
        \retval RET_NOERROR : Attribute returned
        \retval RET_REQUEST_FAILED : No such attribute found
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER readStringAttribute(const IString& rName, IString& rValue) const = 0;

    /***********************************************************************/
    /*! Returns a timeval attribute of the object.
        \param rstrName : Name of the attribute
        \param rtmValue : Return value
        \param rtmDefault : Default value if the attribute can not be converted
        \retval RET_NOERROR : Attribute returned
        \retval RET_REQUEST_FAILED : No such attribute found
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER readTimevalAttribute(const IString& rstrName, Timeval& rtmValue, Timeval rtmDefault = 0) const = 0;

    /***********************************************************************/
    /*! Stores an integer attribute of the object.
        \param rName : Name of the attribute
        \param rValue : value to store
        \retval RET_NOERROR : Attribute stored
        \retval RET_REQUEST_FAILED : Storing attribute failed
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER storeIntAttribute(const IString& rName, const Int& rValue) = 0;

    /***********************************************************************/
    /*! Stores an unsigned integer attribute of the object.
        \param rName : Name of the attribute
        \param rValue : value to store
        \retval RET_NOERROR : Attribute stored
        \retval RET_REQUEST_FAILED : Storing attribute failed
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER storeUintAttribute(const IString& rName, const Uint& rValue) = 0;

    /***********************************************************************/
    /*! Stores a float attribute of the object.
        \param rName : Name of the attribute
        \param rValue : value to store
        \retval RET_NOERROR : Attribute stored
        \retval RET_REQUEST_FAILED : Storing attribute failed
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER storeFloatAttribute(const IString& rName, const Float& rValue) = 0;

    /***********************************************************************/
    /*! Stores a string attribute of the object.
        \param rName : Name of the attribute
        \param rValue : value to store
        \retval RET_NOERROR : Attribute stored
        \retval RET_REQUEST_FAILED : Storing attribute failed
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER storeStringAttribute(const IString& rName, const IString& rValue) = 0;

    /***********************************************************************/
    /*! Stores a timeval attribute of the object.
        \param rstrName : Name of the attribute
        \param rtmValue : value to store
        \retval RET_NOERROR : Attribute stored
        \retval RET_REQUEST_FAILED : Storing attribute failed
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER storeTimevalAttribute(const IString& rstrName, const Timeval& rtmValue) = 0;

    //Persistent layer methods for member values of the X-Object
    /***********************************************************************/
    /*! Gets the number of member variables
    */
    /***********************************************************************/
    virtual Int MQUALIFIER getMemberCount() const = 0;

    /***********************************************************************/
    /*! Returns the indexed member variable
        \param iIndex : Index of the member
        \param rpMember : Member description object
        \retval RET_NOERROR : Member returned
        \retval RET_REQUEST_FAILED : Could not find such a member
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getMemberVariable(Int iIndex, IXMemberVariable*& rpMember) const = 0;

    /***********************************************************************/
    /*! Returns the a member variable by name
        \param rName : Name of the member
        \param rpMember : Member description object
        \retval RET_NOERROR : Member returned
        \retval RET_REQUEST_FAILED : Could not find such a member
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getMemberVariableByName(const IString& rName, IXMemberVariable*& rpMember) const = 0;

    /***********************************************************************/
    /*! Adds a new member variable to the x-object class. This method
        is used to design a X-Object
        \param rName : Name of the member variable
        \param eType : Type of the member variable
        \retval RET_NOERROR : Member created and added
        \retval RET_REQUEST_FAILED : Invalid name
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER addNewMemberVariable(const IString& rName, IXMemberVariable::EVariableType eType) = 0;

    /***********************************************************************/
    /*! Removes a member variable from this X-Object. This method is used
        to design a X-Object
        \param rName : Name of the member variable
        \retval RET_NOERROR : Member created and added
        \retval RET_REQUEST_FAILED : Invalid name
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER removeMemberVariable(const IString& rName) = 0;

    /***********************************************************************/
    /*! Returns the object reference if the member value is of type 'ref'.
        The Reference attribute of the member node contains the X-Object path
        of the requested object. This method is not const since reading a
        X-Object can change the X-Object tree (see XLoaderObject).
        \param rName : Name of the member variable
        \param rpRef : Return value
        \retval RET_NOERROR : object found and returned
        \retval RET_INVALID_PARAMETER : no such member found. Name is invalid.
        \retval RET_INVALID_TYPE : Invalid type. Must be 'ref'.
        \retval RET_REQUEST_FAILED : No such object found.
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getMemberObjectReference(const IString& rName, IXObject*& rpRef) = 0;

    /***********************************************************************/
    /*! This returns the XML node of a requested member variable. The type of
        the variable must be 'xml'.
        \param rName  : Name of the member variable
        \param rpNode : Return value of the XMLNode
        \retval RET_NOERROR : XML Node returned
        \retval RET_INVALID_PARAMETER : no such member found. Name is invalid
        \retval RET_INVALID_TYPE : Type is not 'xml'
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getMemberXMLNode(const IString& rName, IXMLNode*& rpNode) const = 0;

    /***********************************************************************/
    /*! Returns an member variable of the object.
        \param rName : Name of the member variable
        \param rValue : Return value
        \retval RET_NOERROR : member returned
        \retval RET_INVALID_PARAMETER : no such member found. Name is invalid
        \retval RET_INVALID_TYPE : Invalid member type. Could not get value.
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER readMemberVariable(const IString& rName, IZVariant& rValue) const = 0;

    /***********************************************************************/
    /*! Stores an member variable of the object.
        \param rName : Name of the member variable
        \param rValue : value to store
        \retval RET_NOERROR : member stored
        \retval RET_INVALID_PARAMETER : no such member found. Name is invalid
        \retval RET_INVALID_TYPE : Invalid member type. Could not set value.
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER storeMemberVariable(const IString& rName, const IZVariant& rValue) = 0;

    /***********************************************************************/
    /*! Resets the list of member variables. This is nessecary if the
        XMember structure of the XML changes. This might happen during a
        synchronizing process of the XObjectTreeSynchronizing
    */
    /***********************************************************************/
    virtual void MQUALIFIER resetMemberVariables() = 0;
};


END_NAMESPACE_Zeus

#include <zeusbase/System/Interfaces/ISimpleCommand.hpp>

#endif

