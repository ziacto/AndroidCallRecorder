/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXMLNodeError
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/IXMLNodeError.hpp $
** 
** 6     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 5     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXMLNodeErrorHPP
#define IXMLNodeErrorHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IXMLNode.hpp>


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This is the error object returnd by the parser, if the validation fails.
*/
/***************************************************************************/
class IXMLNodeError : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXMLNodeError)
  
  public:
    /**************************************************************************/
    /*! Returns the message of the validation error
        \param rMessage : Return parameter of the error message
    */
    /**************************************************************************/
    virtual void MQUALIFIER getMessage(IString& rMessage) const=0;

    /**************************************************************************/
    /*! Returns the line number of the error
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getLine() const=0;

    /**************************************************************************/
    /*! Returns the line number of the error
    */
    /**************************************************************************/
    virtual Int MQUALIFIER getColumn() const=0;

    /**************************************************************************/
    /*! Returns the line number of the error
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNode(IXMLNode** ppNode)=0;
};

END_NAMESPACE_Zeus

#endif
