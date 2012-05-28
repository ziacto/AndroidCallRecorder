/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXMLErrorReporter
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 6.03.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXMLErrorReporter.hpp $
** 
** 10    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXMLErrorReporterHPP
#define IXMLErrorReporterHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IXMLNodeError.hpp>

#ifdef ENABLE_GUID_USAGE
  // {96A45563-9E87-4f23-A5CB-25A52DD17FB8}
  #define INTERFACE_IXMLErrorReporter    TIID(0x96a45563, 0x9e87, 0x4f23, 0xa5, 0xcb, 0x25, 0xa5, 0x2d, 0xd1, 0x7f, 0xb8)
#else
  #define INTERFACE_IXMLErrorReporter    0x00002004
#endif


BEGIN_NAMESPACE_Zeus


/***************************************************************************/
/*! The XML error reporter is used to return the errors while parsing or
    validating an xml document
*/
/***************************************************************************/
class IXMLErrorReporter : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXMLErrorReporter)
  
  public:
    /***********************************************************************/
    /*! Type of the message
    */
    /***********************************************************************/
    enum EXMLErrorType
    {
      etXMLWarning = 0,
      etXMLError = 1,
      etXMLFatal = 2,
      etXMLNo = 3
    };

    /**************************************************************************/
    /*! This is the generous method to return errors occured parsing a file.
        It will provide an error type, a message and position attributes
        of the error occured.
        \param eType : Type of the message
        \param rMessage: Message itself
        \param iLine : Line of the message
        \param iColumn : Column of the message
    */
    /**************************************************************************/
    virtual void MQUALIFIER onMessage(EXMLErrorType eType, const IString& rMessage, Int iLine, Int iColumn)=0;

    /**************************************************************************/
    /*! This provides an error return if the document is parsed and validated.
        The returned object contains all information of the error, including
        the node reference.
        \param pErrorObj : Object of the error
    */
    /**************************************************************************/
    virtual void MQUALIFIER onNodeError(IXMLNodeError* pErrorObj)=0;

    /**************************************************************************/
    /*! This method must reset the error reporter. All messages must be reset.
    */
    /**************************************************************************/
    virtual void MQUALIFIER reset()=0;
};

END_NAMESPACE_Zeus

#endif

