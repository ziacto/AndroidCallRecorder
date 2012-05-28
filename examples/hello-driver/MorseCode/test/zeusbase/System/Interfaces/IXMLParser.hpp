/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXMLParser
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 14.05.08 12:51 $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IXMLParser.hpp $
** 
** 14    14.05.08 12:51 Mab
** Error handling improved.
** 
** 13    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 12    31.03.08 10:34 Mab
** Namespace handling improved.
** 
** 11    19.03.08 13:38 Mab
** XSD Document introduced.
** 
** 10    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 9     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXMLParserHPP 
#define IXMLParserHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IXMLDocument.hpp>
#include <zeusbase/System/Interfaces/IXSDDocument.hpp>
#include <zeusbase/System/Interfaces/IXMLErrorReporter.hpp>


//Sets the validation (dtd and schema support)
#define SETTING_PARSER_VALIDATION                    L"XMLParser.Validation"

//Sets the full schema checking
// ATTENTION: this property is very time consuming
#define SETTING_PARSER_FULLSCHEMA_SUPPORT            L"XMLParser.FullSchemaSupport"

//More infomration for editing and debugging xml source files
#define SETTING_PARSER_ADDITIONAL_INFOS              L"XMLParser.AdditionalInfos"


#ifdef ENABLE_GUID_USAGE
  // {EF0B7A7B-3BD9-4bb9-94D8-EC2DEF170C8E}
  #define INTERFACE_IXMLParser     TIID(0xef0b7a7b, 0x3bd9, 0x4bb9, 0x94, 0xd8, 0xec, 0x2d, 0xef, 0x17, 0xc, 0x8e)
#else
  #define INTERFACE_IXMLParser     0x00002002
#endif

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! Das IXMLParser Interface definiert einen XML Parser
*/
/***************************************************************************/
class IXMLParser : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXMLParser)    
  
  public:
    /**************************************************************************/
    /*! This method loads a xml file into the buffer using a dom parser.
        \param rFileName : name of the file (path)
        \param ppDocu : Return parameter of the parsed document
        \retval RET_NOERROR : File loaded.
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER loadFromFile(const IString& rFileName, IXMLDocument*& rpDocu)=0;

    /**************************************************************************/
    /*! This method loads an xsd file.
    
        \param rFileName                [IN] : Name and path of the file.
        \param rpDocu                   [OUT]: Return parameter of the parsed document
        \param strErrors                [OUT]: Error descriptions.
        
        \param strSchemaNamespacePrefix [IN] : Optional: Namespace prefix of the
                                               schema namespace. Defaults to xsd.
                                               Give this parameter if you with to
                                               use xs or other prefixes.
        
        \retval                              : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER loadXSDFromFile(const IString& rFileName,
                                              IXSDDocument*& rpDocu,
                                              IString& strErrors,
                                              const char* strSchemaNamespacePrefix = "xsd") = 0;

    /**************************************************************************/
    /*! This method loads a xml from a stream (string) into the buffer
        using a dom parser.
        \param rStream : stream of data
        \param ppDocu : Return parameter of the parsed document
        \retval RET_NOERROR : Stream loaded.
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER parseStream(const IString& rStream, IXMLDocument*& rpDocu)=0;

    /**************************************************************************/
    /*! Adds a error reporter to the parser. Throu this reporter, all
        errors during parsing the xml will be posted.
        \param rReporter : Reference of the reporter
    */
    /**************************************************************************/
    virtual void MQUALIFIER addErrorReporter(IXMLErrorReporter& rReporter)=0;

    /**************************************************************************/
    /*! Removes a error reporter of the parser.
        \param rReporter : Reference of the reporter
        \retval RET_NOERROR : Reporter removed
        \retval RET_REQUEST_FAILED : No such reporter was added
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER removeErrorReporter(IXMLErrorReporter& rReporter)=0;

    /**************************************************************************/
    /*! Gets a named parser property. Check the property defines for the parser
        to lookup different possibilities.
        \param rName : Name of the property
        \return value of the property
    */
    /**************************************************************************/
    virtual bool MQUALIFIER getProperty(const IString& rName)const=0;

    /**************************************************************************/
    /*! Sets the parser properties. Check the property defines for the parser
        to lookup different possibilities.
        \param rName : Name of the property
        \param bValue : Parser property
    */
    /**************************************************************************/
    virtual void MQUALIFIER setProperty(const IString& rName, bool bValue)=0;

};

END_NAMESPACE_Zeus

#endif
