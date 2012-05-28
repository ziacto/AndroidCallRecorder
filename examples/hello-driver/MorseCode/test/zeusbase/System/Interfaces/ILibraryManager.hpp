/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ILibraryManager
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 20.09.06
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/ILibraryManager.hpp $
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef ILibraryManagerHPP
#define ILibraryManagerHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! System Library manager
*/
/***************************************************************************/
class ILibraryManager : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ILibraryManager)
  
  public:
    /***********************************************************************/
    /*! This method creates an object out of the codemodule
        \param rCodeModule : Module name
        \param rClassName : Name of the class
        \param rpIface : Reference to return
        \retval RET_NOERROR : Object created
        \retval RET_REQUEST_FAILED : Class not exported
        \retval RET_INTERNAL_ERROR : Internal error occured
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER createObject(const IString& rCodeModule, const IString& rClassName, IZUnknown*& rpIface)=0;

    /***********************************************************************/
    /*! Registers a x Factory function and returns the handle of this function
        \param rCodeModule : Module name
        \param rClassName : Name of the class
        \param rHandle : Return parameter of the function handle
        \retval RET_NOERROR : Function found
        \retval RET_REQUEST_FAILED : Class not exported
        \retval RET_INTERNAL_ERROR : Internal error occured
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER registerXClass(const IString& rCodeModule, const IString& rClassName, Uint& rHandle)=0;
};

END_NAMESPACE_Zeus

#endif 
