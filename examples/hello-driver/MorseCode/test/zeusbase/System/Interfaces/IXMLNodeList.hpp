/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXMLNodeList
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXMLNodeList.hpp $
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

#ifndef IXMLNodeListHPP
#define IXMLNodeListHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IXMLNode.hpp>

#ifdef ENABLE_GUID_USAGE
  // {69D51A6C-0720-41b2-BCD5-F932C8A3FA52}
  #define INTERFACE_IXMLNodeList       TIID(0x69d51a6c, 0x720, 0x41b2, 0xbc, 0xd5, 0xf9, 0x32, 0xc8, 0xa3, 0xfa, 0x52)
#else
  #define INTERFACE_IXMLNodeList       0x00002001
#endif

BEGIN_NAMESPACE_Zeus

class IXMLNode;

/******************************************************************************/
/*! Das IXMLNodeList definiert eine Schnittstelle zu der XMLNodeList eines
    DOM Trees. Hier sind alle Nodes eines Parentnodes enthalten
*/
/******************************************************************************/
class IXMLNodeList : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXMLNodeList)    
  
  public :
    /**************************************************************************/
    /*! Mit dieser Funktion laest es sich bestimmen wieviele SubNodes im der
        Liste vorhanden sind.
        \return Groesse der Liste
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getListCount() const= 0;

    /**************************************************************************/
    /*! Diese Funktion gibt einen indexierten SubNode in der Liste zurck.
        \param iIndex : Wahl des Nodes
        \param ppNode : Rckgabeparameter
        \retval RET_NOERROR : Fehlerfreie Rckgabe
        \retval RET_REQUEST_FAILED : Der Knoten kann nicht zurckgegeben werden
        \retval RET_INVALID_PARAMETER: Fehlerhafter Rckgabeparameter
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNode(Int iIndex, IXMLNode** ppNode) const= 0;
};

END_NAMESPACE_Zeus

#endif
