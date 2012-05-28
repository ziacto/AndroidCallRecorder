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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXSynchronActionListener.hpp $
** 
** 7     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 6     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 5     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXSynchronActionListenerHPP
#define IXSynchronActionListenerHPP

#include <zeusbase/System/Interfaces/IXSynchronAction.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {472EC55C-7B14-490b-8810-341AC11E2837}
  #define INTERFACE_IXSynchronActionListener     TIID(0x472ec55c, 0x7b14, 0x490b, 0x88, 0x10, 0x34, 0x1a, 0xc1, 0x1e, 0x28, 0x37)
#else
  #define INTERFACE_IXSynchronActionListener     0x00000013
#endif

/***************************************************************************/
/*! This interface defines the listener for xobject synchronisation. It
    defines callback methods to receive actual  informations
    about the synchronisation process.
*/
/***************************************************************************/
class IXSynchronActionListener : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXSynchronActionListener)
  
  public:
    /***********************************************************************/
    /*! call back if an action is been executed
        \param rSender : Action reference
        \param iActCycleIndex : Actual cycle
    */
    /***********************************************************************/
    virtual void MQUALIFIER onExecuteAction(IXSynchronAction& rSender, Int iActCycleIndex) = 0;

};

END_NAMESPACE_Zeus

#endif
