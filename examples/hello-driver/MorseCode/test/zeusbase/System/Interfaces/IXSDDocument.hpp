/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXSDDocument
 * Package : System
 * Author  : Abbuehl Martin
 * Datum   : $Date: 13.08.08 10:08 $
 * Ablage  : $File: $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IXSDDocument.hpp $
** 
** 14    13.08.08 10:08 Mab
** 
** 13    12.08.08 15:57 Mab
** getIncludeFileMainNode() added.
** 
** 12    11.08.08 16:55 Mab
** Base development.
** 
** 11    21.07.08 12:59 Mab
** XSD base development.
** 
** 10    21.05.08 12:05 Mab
** Recursive elements selection added.
** 
** 9     29.04.08 10:29 Mab
** getSpecificNodes, getComplexTypes and getSimpleTypes added.
** 
** 8     24.04.08 17:22 Mab
** IXSDDocument::getElement added.
** 
** 7     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 2     25.03.08 15:50 Mab
** Derivation IXMLDocument implemented.
***************************************************************************/
#ifndef IXSDDocumentHPP
#define IXSDDocumentHPP

#include <zeusbase/System/Interfaces/IXMLDocument.hpp>
#include <zeusbase/System/Interfaces/IXSDNodes.hpp>
#include <zeusbase/System/Interfaces/IXSDNode.hpp>


#ifdef ENABLE_GUID_USAGE
  // {C0CA9961-70B4-4b7a-BE10-D3143773F2C5}
  #define INTERFACE_IXSDDocument      TIID(0xc0ca9961, 0x70b4, 0x4b7a, 0xbe, 0x10, 0xd3, 0x14, 0x37, 0x73, 0xf2, 0xc5)
#else
  #define INTERFACE_IXSDDocument      0x00002006
#endif


BEGIN_NAMESPACE_Zeus


/***************************************************************************/
/*! The IXSDDocument extends the IXMLDocument, but does not derive
    IXMLDocument directly to avoid multiple inheritance in the implementation class.
*/
/***************************************************************************/
class IXSDDocument : public IXMLDocument
{
  public:
    /**************************************************************************/
    /*! Save the container document.
    
        \param strFileName [IN] : File name.

        \retval                 : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER saveContainerDocument(const IString& strFileName) const = 0;
    
    /**************************************************************************/
    /*! Get a specific named node.

        \param strXSDQualifier [IN] : XSD qualifier like 'element' or 'complexType'.
        \param strName         [IN] : The name used within the desired node.
        \param rpNode          [OUT]: Pointer to an IXSDNode.

        \retval                     : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNamedNode(const IString& strXSDQualifier,
                                           const IString& strName,
                                           IXSDNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Get a collection of specific nodes.

        \param strXSDQualifier [IN] : XSD qualifier like 'element' or 'complexType'.
        \param rpNodes         [OUT]: Pointer to a collection of IXSDNodes.

        \retval                     : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getSpecificNodes(const IString& strXSDQualifier,
                                               IXSDNodes*& rpNodes) = 0;

    /**************************************************************************/
    /*! Get an element node.
    
        \param strElementName [IN] : The element's name.
        \param rpNode         [OUT]: Pointer to an IXSDNode.

        \retval                    : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getElement(const IString& strElementName,
                                         IXSDNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Get a simple type node.
    
        \param strSimpleTypeName [IN] : Name of the simple type.
        \param rpNode            [OUT]: Pointer to an IXSDNode.

        \retval                       : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getSimpleType(const IString& strSimpleTypeName,
                                            IXSDNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Get a complex type node.
    
        \param strComplexTypeName [IN] : Name of the complex type.
        \param rpNode             [OUT]: Pointer to an IXSDNode.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getComplexType(const IString& strComplexTypeName,
                                             IXSDNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Get a list of all element sub nodes of a given xsd complex type.
    
        \param strComplexTypeName [IN] : Name of the complex type.
        \param rpElements         [OUT]: Pointer to a collection of element nodes.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getElementsOfComplexType(const IString& strComplexTypeName,
                                                       IXSDNodes*& rpElements) = 0;

    /**************************************************************************/
    /*! Get one specific element sub node of a given xsd complex type.
    
        \param strComplexTypeName [IN] : Name of the complex type.
        \param strElementName     [IN] : Name of the element.    
        \param rpElement          [OUT]: Pointer to the element node.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getElementOfComplexType(const IString& strComplexTypeName,
                                                      const IString& strElementName,
                                                      IXSDNode*& rpElement) = 0;

    /**************************************************************************/
    /*! Get a list of all attribute sub nodes of a given xsd complex type.
    
        \param strComplexTypeName [IN] : Name of the complex type.
        \param rpAttributes       [OUT]: Pointer to a collection of attribute nodes.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributesOfComplexType(const IString& strComplexTypeName,
                                                         IXSDNodes*& rpAttributes) = 0;

    /**************************************************************************/
    /*! Get one specific attribute sub node of a given xsd complex type.
    
        \param strComplexTypeName [IN] : Name of the complex type.
        \param strAttributeName   [IN] : Name of the attribute.    
        \param rpAttribute        [OUT]: Pointer to the attribute node.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributeOfComplexType(const IString& strComplexTypeName,
                                                        const IString& strAttributeName,
                                                        IXSDNode*& rpAttribute) = 0;

    /**************************************************************************/
    /*! Get a list of all complex types.
    
        \param rpComplexTypes [OUT]: Pointer to a collection of complex type nodes.

        \retval                    : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getComplexTypes(IXSDNodes*& rpComplexTypes) = 0;

    /**************************************************************************/
    /*! Get a list of all simple types.
    
        \param rpSimpleTypes [OUT]: Pointer to a collection of simple type nodes.

        \retval                    : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getSimpleTypes(IXSDNodes*& rpSimpleTypes) = 0;

    /**************************************************************************/
    /*! Get a list of all element nodes in the entire schema of a given
        xsd complex type.
    
        \param strComplexTypeName [IN] : Name of the complex type.
        \param rpElements         [OUT]: Pointer to a collection of element nodes.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAllElementsOfComplexType(const IString& strComplexTypeName,
                                                          IXSDNodes*& rpElements) = 0;

    /**************************************************************************/
    /*! \See IXMLNode::createNewChildNode

        \param rParentNode            [IN]: The parent node.
        
        \param bPrefixSchemaNamespace [IN]: Prefix the schema namespace at the
                                            beginning of strName.             */
    /**************************************************************************/
    virtual Retval MQUALIFIER createNewXSDChildNode(IXSDNode& rParentNode,
                                                    const IString& strName,
                                                    bool bPrefixSchemaNamespace,
                                                    IXSDNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Is an XSD node in a specific include file?

        \param rNode       [IN]: The XSD node.
        \param strFilePath [IN]: Absolute file path of the include file.

        \retval                : rNode is included in strFilePath.            */
    /**************************************************************************/
    virtual bool MQUALIFIER isXSDNodeIncludedInFile(const IXSDNode& rNode,
                                                    const IString& strFilePath) const = 0;

    /**************************************************************************/
    /*! Get the main node of a given include file.

        \param strIncludeFile [IN] : Absolute file path of the include file.
        \param rpNode         [OUT]: The main node.

        \retval                    : Error code.                              */
    /**************************************************************************/
    virtual Retval MQUALIFIER getIncludeFileMainNode(const IString& strIncludeFile,
                                                     IXSDNode*& rpNode) = 0;
};


END_NAMESPACE_Zeus

#endif

