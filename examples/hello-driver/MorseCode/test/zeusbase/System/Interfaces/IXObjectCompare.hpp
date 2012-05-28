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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXObjectCompare.hpp $
** 
** 13    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 12    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 11    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXObjectCompareHPP
#define IXObjectCompareHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IXSynchronAction.hpp>


#ifdef ENABLE_GUID_USAGE
  // {D151D700-4BBC-4d31-8996-EF879F98E8C6}
  #define INTERFACE_IXObjectCompare       TIID(0xd151d700, 0x4bbc, 0x4d31, 0x89, 0x96, 0xef, 0x87, 0x9f, 0x98, 0xe8, 0xc6)
#else
  #define INTERFACE_IXObjectCompare       0x00000011
#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface is used to check two xobjects 
*/
/***************************************************************************/
class IXObjectCompare : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXObjectCompare)    
  
  public:
    /***********************************************************************/
    /*! This method is called to check if two x objects are differnt and
        creates the corresponding action
        \param rTargetObject : Target object
        \param rpAction : Return parameter of an action
        \param bForce : If this flag is set, a change is requested by the
                        caller. The XObjectCompare-Object might still deny it
        \retval RET_NOERROR : Action generated
        \retval RET_REQUEST_FAILED : Could not generate an action
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createCompareAction(IXObject& rTargetObject, IXSynchronAction*& rpAction, bool bForce = false)=0;

    /***********************************************************************/
    /*! This method is called to create an action for removing a x-object
        \param rpAction : Return parameter of an action
        \retval RET_NOERROR : Action generated
        \retval RET_REQUEST_FAILED : Could not generate an action
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createRemoveAction(IXSynchronAction*& rpAction)=0;

    /***********************************************************************/
    /*! This method is called to create an action for adding a x-object
        \param rpAction : Return parameter of an action
        \retval RET_NOERROR : Action generated
        \retval RET_REQUEST_FAILED : Could not generate an action
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createAddAction(IXSynchronAction*& rpAction)=0;

    /***********************************************************************/
    /*! This method is called to create the root action of the
        synchronisation tree. If there is not valid return it will
        automatically create a TXSynchronAction Object
        \param rTargetObject : Target object
        \param rpAction : Return parameter of an action
        \retval RET_NOERROR : Action generated
        \retval RET_REQUEST_FAILED : Could not generate an action
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createRootAction(IXObject& rTargetObject, IXSynchronAction*& rpAction)=0;

    /***********************************************************************/
    /*! Notification of the synchronizing process. The process has been
        started at that moment
        \param bTarget : true if the object node is the target node
    */
    /***********************************************************************/
    virtual void MQUALIFIER onSynchronizeStarted(bool bTarget)=0;

    /***********************************************************************/
    /*! Notification of the synchronizing process. The process has been
        ended at that moment
        \param bTarget : true if the object node is the target node
    */
    /***********************************************************************/
    virtual void MQUALIFIER onSynchronizeEnded(bool bTarget)=0;

    /***********************************************************************/
    /*! Notification of the synchronizing process. The process has been
        finished for a given cyclye at that moment
        \param bTarget : true if the object node is the target node
        \param iActCycleIndex : Actual finished cycle
        \param bModified : This flag is set if the object has been modified
    */
    /***********************************************************************/
    virtual void MQUALIFIER onSynchronizeCylceFinished(bool bTraget, Int iActCycleIndex, bool bModified)=0;
};

END_NAMESPACE_Zeus

#endif

