/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXPathResults
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 7:04 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IXPathResults.hpp $
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/
#ifndef IXPathResultsHPP
#define IXPathResultsHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>


BEGIN_NAMESPACE_Zeus

class IXMLNode;

/******************************************************************************/
/*! This interface wrapps a xpath result. The result is a list of nodes
    applying to a given x path.
*/
/******************************************************************************/
class IXPathResults : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXPathResults)    
  
  public :
    /**************************************************************************/
    /*! Resets the node iterator
    */
    /**************************************************************************/
    virtual void MQUALIFIER reset()=0;

    /**************************************************************************/
    /*! returns the next node from the internal iterator
        \param rpNode : return parameter
        \retval RET_NOERROR : Node returned
        \retval RET_REQUEST_FAILED : no next node found
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNextNode(IXMLNode*& rpNode)=0;

    /**************************************************************************/
    /*! Checks if a next node is available
        \retval true : Next node available
        \retval false: End of list reached
    */
    /**************************************************************************/
    virtual bool MQUALIFIER hasNextItem() const=0;

    /**************************************************************************/
    /*! Returns the number of nodes found
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getCount() const=0;

    /**************************************************************************/
    /*! Returns an indexed node
        \param iIndex : Index of node
        \param rpNode : Return parameter
        \retval RET_NOERROR : Node returned
        \retval RET_REQUEST_FAILED : no node found
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNode(Int iIndex, IXMLNode*& rpNode) const=0;

};

END_NAMESPACE_Zeus

#endif

