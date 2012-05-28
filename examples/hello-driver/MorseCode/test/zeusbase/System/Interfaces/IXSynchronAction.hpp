/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IXSynchronAction
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXSynchronAction.hpp $
** 
** 16    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 15    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 14    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
**
** 10    16.10.06 18:52 bha
** RootObjectNotification implemented
***************************************************************************/

#ifndef IXSynchronActionHPP
#define IXSynchronActionHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IXObject.hpp>

#ifdef ENABLE_GUID_USAGE
  // {847DFF5E-30D9-44a2-9DC3-C0AF867642A1}
  #define INTERFACE_IXSynchronAction     TIID(0x847dff5e, 0x30d9, 0x44a2, 0x9d, 0xc3, 0xc0, 0xaf, 0x86, 0x76, 0x42, 0xa1)
#else
  #define INTERFACE_IXSynchronAction     0x00000010
#endif

BEGIN_NAMESPACE_Zeus

class IXSynchronActionListener;

/*************************************************************************/
/*! This interface defines the access to synchronisation actions of
    a tree synchronisation. The synchronisation proceeds like follows:
    - mark the root of execution
    - execute action
      -# notify the target node of synchronizing state
      -# run onStartExecuting() method (pre processing)
      -# update the X-Object tree and the XML Nodes
      -# run onExecuted() method (in processing)
      -# descend to the leafes (execute action of all children)
      -# run onPostProcessing() method (post processing)
    .
    - finish the synchronizing
      -# descend to the leafes (finish the synch. of all children)
      -# notify the target node of finishing
    .
    - Unfreeze the target node of the root of execution action
      (Unfreeze falg must be set)
      -# Clean the target tree is requested (CleanTree flag must be set)
*/
/*************************************************************************/
class IXSynchronAction : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXSynchronAction)
  
  public:
    /*********************************************************************/
    /*! This type defines the type of the action. There are 3 types
        defined: etNodeChange, etNodeAdd, etNodeRemove.
    */
    /*********************************************************************/
    enum ENodeActionType
    {
      etNodeUnchanged = 0,    /*! < No changes to be made */
      etNodeChange = 1,       /*! < Node value changes to be made */
      etNodeAdd = 2,          /*! < Add the node */
      etNodeRemove = 3,       /*! < Remove the node */
      etNodeError = 4         /*! < Node has an error. The process will stop at this node*/
    };

    /*********************************************************************/
    /*! Adds a new child action to this action
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER addNewChild(IXObject* pNode1, IXObject* pNode2, IXSynchronAction::ENodeActionType eType, IXSynchronAction*& pChild)=0;

    /*********************************************************************/
    /*! Adds a child action to this instance
    */
    /*********************************************************************/
    virtual void MQUALIFIER add(IXSynchronAction& pChild)=0;

    /*********************************************************************/
    /*! This method is used to get the next action.

        \param rRefChild : The rRefChild Action is the previous sibling
                           of the requested child instance
        \param rpChild : Return parameter of the requested child
        \retval RET_NOERROR : Child returned
        \retval RET_REQUEST_FAILED : No next child found
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER getNextChildOfAction(IXSynchronAction& rRefChild, IXSynchronAction*& rpNextChild)=0;

    /*********************************************************************/
    /*! returns the number of child actions
    */
    /*********************************************************************/
    virtual Int MQUALIFIER getCount() const =0;

    /*********************************************************************/
    /*! returns the number of child actions
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER getChild(Int iIndex, IXSynchronAction*& rpAction) const =0;

    /*********************************************************************/
    /*! This method returns the type of the action
    */
    /*********************************************************************/
    virtual ENodeActionType MQUALIFIER getType() const =0;

    /*********************************************************************/
    /*! This returns the 1st node of the action (source)
        \param pNode : Return parameter of the node
        \retval RET_REQUEST_FAILED: could not return the node
        \retval RET_NOERROR: node returned
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER getNode1(IXObject*& rpNode) const =0;

    /*********************************************************************/
    /*! This returns the 1st node of the action (target)
        \param pNode : Return parameter of the node
        \retval RET_REQUEST_FAILED: could not return the node
        \retval RET_NOERROR: node returned
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER getNode2(IXObject*& rpNode) const =0;

    /*********************************************************************/
    /*! This returns the parent action node
        \param pParent : Return parameter of the parent
        \retval RET_REQUEST_FAILED: could not return the parent
        \retval RET_NOERROR: parent returned
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER getParent(IXSynchronAction*& rpParent) const =0;

    /*********************************************************************/
    /*! Adds a child action to this instance
        \param pParent : Parent instance
    */
    /*********************************************************************/
    virtual void MQUALIFIER setParent(IXSynchronAction& rParent)=0;

    /*********************************************************************/
    /*! Disabling an action is used to skip this action from execution.
        All its children will be disabled as well.
    */
    /*********************************************************************/
    virtual void MQUALIFIER disable()=0;

    /*********************************************************************/
    /*! If an action is enabled, it can be executed to transform the
        one tree node from tree 1 to tree 2
    */
    /*********************************************************************/
    virtual void MQUALIFIER enable()=0;

    /*********************************************************************/
    /*! Checks is an action is enabled.

        \retval true : Action is enabled
        \retval false: Action is disabled
    */
    /*********************************************************************/
    virtual bool MQUALIFIER isEnabled() const=0;

    /*********************************************************************/
    /*! This method synchronizes two tree nodes

        \param lCycleCount: Number of cycles for synchronizing. If zero is given
                            (default), it will simply run the X-Object
                            synchronisation. If lCycleCount > 0 then it will
                            repeat lCycleCount times the executeRecus() method.
        \param bUnfreeze  : Unfreeze synchronized tree
        \param bCleanTree : Remove all frozen objects after synchronizing and
                            unfreezing
        \param pListener : Listener interface to get callbacks of the actual
                           execution state
        \retval RET_NOERROR : No error occured transforming the nodes or
                              the action has been disabled
        \retval RET_REQUEST_FAILED : Could not transform the nodes
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER executeAction(Int iCycleCount=0, bool bUnfreeze = false, bool bCleanTree = false, IXSynchronActionListener* pListener = NULL)=0;

    /*********************************************************************/
    /*! Returns the caption of the action
    */
    /*********************************************************************/
    virtual void MQUALIFIER getCaption(IString& rCaption) const=0;

    /*********************************************************************/
    /*! Finds an action containing the rObject as left or right child
        \param rObject : Target or Source Object of the action
        \param rpAction : Return parameter of a found action
        \retval RET_NOERROR : Action found and returned
        \retval RET_REQUEST_FAILED : Could not find the action
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER findAction(IXObject& rObject, IXSynchronAction*& rpAction)= 0;

    /*********************************************************************/
    /*! This executes an action recursivly
        \param iActCylceIndex : ID of the cycle to run. Zero is the X-Object
                             synchronisation cycle. Every thing else is a
                             custom cycle
        \param pListener : Listener interface to get callbacks of the actual
                           execution state
        Do not call this method directly. Use executeAction()
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER executeRecurs(Int iActCylceIndex, IXSynchronActionListener* pListener = NULL)=0;

    /*********************************************************************/
    /*! This finishes an action recursivly
        Do not call this method directly. Use executeAction()
    */
    /*********************************************************************/
    virtual void MQUALIFIER finishRecurs() = 0;

    /*********************************************************************/
    /*! This method removes all objects witch are frozen at this moment.
        Do not call this method directly. Use executeAction()
    */
    /*********************************************************************/
    virtual void MQUALIFIER cleanTargetTree()=0;

    /*********************************************************************/
    /*! Returns the number of all cycle of this sub tree
    */
    /*********************************************************************/
    virtual Int MQUALIFIER getSubActionCount() const = 0;

    /*********************************************************************/
    /*! Returns an error code if the node has the state etNodeError.
        Otherwise it will return RET_NOERROR
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER getErrorCode() const = 0;

    /*********************************************************************/
    /*! Checks the pre conditions of the whole action tree. It will
        return the specific error code of the first failing action node.
        The method might continue recursivly after that, if the flag bForce
        is set. Otherwise it will terminate the precondition search.
        \param iCycleIndex : Check condition for that cycle
        \param bForce : Check children even the parent has an error
        \return error code. If everything is ok, RET_NOERROR will be returned

    */
    /*********************************************************************/
    virtual Retval MQUALIFIER checkPreConditions(Int iCycleIndex = 0, bool bForce = false) = 0;

    /*********************************************************************/
    /*! If this property is set, the root object of the X-Object tree
        will be notified of start and end synchronizing process events
        \param bFlag : Notify the root object 
    */
    /*********************************************************************/
    virtual void MQUALIFIER setRootObjectNotification(bool bFlag) = 0;

    /*********************************************************************/
    /*! returns the root of the action tree
    */
    /*********************************************************************/
    virtual Retval MQUALIFIER getRootAction(IXSynchronAction*& rpRoot) const=0;
};


END_NAMESPACE_Zeus

#endif
