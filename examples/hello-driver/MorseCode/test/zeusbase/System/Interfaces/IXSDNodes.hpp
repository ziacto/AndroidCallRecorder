/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXSDNodes
 * Package : System
 * Author  : Abbuehl Martin
 * Datum   : $Date: 26.03.08 11:11 $
 * Ablage  : $Archive: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IXSDNodes.hpp $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IXSDNodes.hpp $
** 
** 1     26.03.08 11:11 Mab
***************************************************************************/
#ifndef IXSDNodesHPP
#define IXSDNodesHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>


BEGIN_NAMESPACE_Zeus

class IXSDNode;
/******************************************************************************/
/*! This interface wrapps a collection of IXSDNodes.
*/
/******************************************************************************/
class IXSDNodes : public IZUnknown
{
  public:
    /**************************************************************************/
    /*! Resets the node iterator
    */
    /**************************************************************************/
    virtual void MQUALIFIER reset() = 0;

    /**************************************************************************/
    /*! returns the next node from the internal iterator
        \param rpNode : return parameter
        \retval RET_NOERROR : Node returned
        \retval RET_REQUEST_FAILED : no next node found
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNextNode(IXSDNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Checks if a next node is available
        \retval true : Next node available
        \retval false: End of list reached
    */
    /**************************************************************************/
    virtual bool MQUALIFIER hasNextItem() const = 0;

    /**************************************************************************/
    /*! Returns the number of nodes found
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getCount() const = 0;

    /**************************************************************************/
    /*! Returns an indexed node
    
        \param iIndex : Index of node
        \param rpNode : Return parameter
        \retval RET_NOERROR : Node returned
        \retval RET_REQUEST_FAILED : no node found
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNode(Int iIndex, IXSDNode*& rpNode) const = 0;
};

END_NAMESPACE_Zeus

#endif

