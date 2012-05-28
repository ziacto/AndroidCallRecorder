/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXRootObject
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXRootObject.hpp $
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

#ifndef IXRootObjectHPP
#define IXRootObjectHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {0ABB659E-6761-40c3-A5DC-2844BA418972}
  #define INTERFACE_IXRootObject     TIID(0xabb659e, 0x6761, 0x40c3, 0xa5, 0xdc, 0x28, 0x44, 0xba, 0x41, 0x89, 0x72)
#else
  #define INTERFACE_IXRootObject     0x00000014
#endif


/***************************************************************************/
/*! Interface of the root object of an X-Object tree
*/
/***************************************************************************/
class IXRootObject : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXRootObject)
  
  public:

    /***********************************************************************/
    /*! Stores the data tree of XObjects back into a file.
        \return See IXMLDocument for error codes
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER save() =0;

    /***********************************************************************/
    /*! Stores the data tree of XObjects back into a file.
        \param rFileName : Name of the file
        \return See IXMLDocument for error codes
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER saveAs(const IString& rFileName) =0;
};

END_NAMESPACE_Zeus

#endif
