/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 *************************************************************************** 
 * Projekt : ZeusBase
 * Module  : ISingletonManager
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 20.09.06
 * Ablage  : $File$
 * System  : Zeus-Framework
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/ISingletonManager.hpp $
** 
** 9     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 8     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 7     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef ISingletonManagerHPP
#define ISingletonManagerHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {B5525864-71F9-49fe-A3E0-2CA08B5A49B6}
  #define INTERFACE_ISingletonManager    TIID(0xb5525864, 0x71f9, 0x49fe, 0xa3, 0xe0, 0x2c, 0xa0, 0x8b, 0x5a, 0x49, 0xb6)
#else
  #define INTERFACE_ISingletonManager    0x0000001B
#endif

/***************************************************************************/
/*! This interface is used to define the singleton manager. Each loaded
    module will receive such an interface, to access the singletons of the
    system
*/
/***************************************************************************/
class ISingletonManager : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ISingletonManager)
  
  public:
    /***********************************************************************/
    /*! adds a singleton to the registry. A singleton can be added only 
        once using the name. 
        \param rName : Name of the singleton object
        \param rIface : Reference to the singleton object
        \retval RET_NOERROR : Singleton added
        \retval RET_REQUEST_FAILED : Could not add singleton
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER addSingleton(const IString& rName, IZUnknown& rIface)=0;


    /***********************************************************************/
    /*! Gets a singleton object referenced by the name of the object.
        \param rName : Name of the singleton object
        \param rpIface : Return parameter. Reference to the singleton object
        \retval RET_NOERROR : Singleton returned
        \retval RET_REQUEST_FAILED : Could not find singleton with this name
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getSingleton(const IString& rName, IZUnknown*& rpIface)=0;
    
    /***********************************************************************/
    /*! Removes a singleton. If an added singleton is not removed manually, 
        the manager will remove it when the application terminates. For 
        singletons provided in code modules (shared libraries) its 
        important, that the user (programmer) removes it manually before 
        the code module has been unloaded.
        \param rName : Name of the object to be removed
        \retval RET_NOERROR : Singleton removed
        \retval RET_REQUEST_FAILED : Could not find singleton with this name
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER removeSingleton(const IString& rName)=0;
};

END_NAMESPACE_Zeus

#endif

