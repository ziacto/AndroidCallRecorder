/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXSDNode
 * Package : System
 * Author  : Abbuehl Martin
 * Datum   : $Date: 20.08.08 11:20 $
 * Ablage  : $Archive: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IXSDNode.hpp $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IXSDNode.hpp $
** 
** 19    20.08.08 11:20 Mab
** Minor naming correction.
** 
** 18    11.08.08 16:55 Mab
** Base development.
** 
** 17    7.08.08 16:52 Mab
** Unbounded renamed.
** 
** 16    7.08.08 15:25 Mab
** New method getBase().
** 
** 15    29.07.08 16:11 Mab
** selectXSDNode() and selectXSDNodes() extended by flag
** bPrefixSchemaNamespace.
** 
** 14    21.07.08 12:59 Mab
** XSD base development.
** 
** 13    17.07.08 15:52 Mab
** getParentXSDNode() added.
** 
** 12    17.07.08 14:54 Mab
** createNewChildNode() extended by flag bPrefixSchemaNamespace.
** 
** 11    16.07.08 12:57 Mab
** createNewChildNode() added.
** 
** 10    7.07.08 12:05 Mab
** selectXSDNode/s moved to interface.
** 
** 9     15.05.08 15:46 Mab
** Limits implemented.
** 
** 8     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 7     27.03.08 15:43 Mab
***************************************************************************/
#ifndef IXSDNodeHPP
#define IXSDNodeHPP

#include <zeusbase/System/Interfaces/IXMLNode.hpp>


#ifdef ENABLE_GUID_USAGE
  // {7E3DD4F5-EBDA-4bd7-8E4B-6864E35F4486}
  #define INTERFACE_IXSDNode     TIID(0x7e3dd4f5, 0xebda, 0x4bd7, 0x8e, 0x4b, 0x68, 0x64, 0xe3, 0x5f, 0x44, 0x86)
#else
  #define INTERFACE_IXSDNode     0x00002007
#endif


#define UNBOUNDED   -1


BEGIN_NAMESPACE_Zeus


class IXSDNodes;
/******************************************************************************/
/*! Das Interface IXSDNode kapselt einen XML-Knoten eines XML-Schemas und
    erweitert IXMLNode.
*/
/******************************************************************************/
class IXSDNode : public IXMLNode
{
  public:
    /**************************************************************************/
    /*! Ist dieser Knoten ein complex type?
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isComplexType() const = 0;

    /**************************************************************************/
    /*! Ist dieser Knoten ein simple type?
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isSimpleType() const = 0;

    /**************************************************************************/
    /*! Ist dieser Knoten ein Element?
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isElement() const = 0;

    /**************************************************************************/
    /*! Ist dieser Knoten ein Attribut?
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isAttribute() const = 0;

    /**************************************************************************/
    /*! Ist dieser Knoten eine Annotation?
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isAnnotation() const = 0;

    /**************************************************************************/
    /*! Ist dieser Knoten eine Appinfo?
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isAppinfo() const = 0;

    /**************************************************************************/
    /*! Ist dieser Knoten eine Restriction?
    */
    /**************************************************************************/
    virtual bool MQUALIFIER isRestriction() const = 0;

    /**************************************************************************/
    /*! Den Namen eines Elements oder Attributs ermitteln.

        \param strName [OUT]: Name.

        \retval             : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getName(IString& strName) const = 0;

    /**************************************************************************/
    /*! Den Namen eines Elements oder Attributs setzen.

        \param strName [IN]: Name.

        \retval            : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setName(const IString& strName) = 0;

    /**************************************************************************/
    /*! Den Typ eines Elements oder Attributs ermitteln.

        \param strType [OUT]: Typ.

        \retval             : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getType(IString& strType) const = 0;

    /**************************************************************************/
    /*! Den Typ eines Elements oder Attributs setzen.

        \param strType [IN]: Typ.

        \retval            : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setType(const IString& strType) = 0;

    /**************************************************************************/
    /*! Die minimale Anzahl eines Elementknotens ermitteln.

        \param iMinOccurs [OUT]: Anzahl. UNBOUNDED_OCCURS möglich.

        \retval                : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getMinOccurs(Int& iMinOccurs) const = 0;

    /**************************************************************************/
    /*! Die minimale Anzahl eines Elementknotens setzen.

        \param iMinOccurs [IN]: Anzahl. UNBOUNDED_OCCURS möglich.

        \retval               : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setMinOccurs(Int iMinOccurs) = 0;

    /**************************************************************************/
    /*! Die maximale Anzahl eines Elementknotens ermitteln.

        \param iMaxOccurs [OUT]: Anzahl. UNBOUNDED_OCCURS möglich.

        \retval                : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getMaxOccurs(Int& iMaxOccurs) const = 0;

    /**************************************************************************/
    /*! Die maximale Anzahl eines Elementknotens setzen.

        \param iMaxOccurs [IN]: Anzahl. UNBOUNDED_OCCURS möglich.

        \retval               : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setMaxOccurs(Int iMaxOccurs) = 0;

    /**************************************************************************/
    /*! Den Default eines Attributs ermitteln.

        \param strDefault [OUT]: Default.

        \retval                : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getDefault(IString& strDefault) const = 0;

    /**************************************************************************/
    /*! Den Default eines Attributs setzen.

        \param strDefault [IN]: Default.

        \retval               : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setDefault(const IString& strDefault) = 0;

    /**************************************************************************/
    /*! Das value Attribut lesen.

        \param strValue [OUT]: Value.

        \retval              : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getValue(IString& strValue) const = 0;

    /**************************************************************************/
    /*! Das value Attribut setzen.

        \param strValue [IN]: Value.

        \retval             : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setValue(const IString& strValue) = 0;

    /**************************************************************************/
    /*! selectNode für IXSDNode.

        \param strQuery               [IN] : XML-Query.
        \param bPrefixSchemaNamespace [IN] : Das Namespaceprefix dem Query voranstellen.
        \param rpResult               [OUT]: Zeiger auf den selektierten Knoten.

        \retval                            : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER selectXSDNode(const IString& strQuery,
                                            bool bPrefixSchemaNamespace,
                                            IXSDNode*& rpResult) const = 0;

    /**************************************************************************/
    /*! selectNodes für IXSDNodes.

        \param strQuery               [IN] : XML-Query.
        \param bPrefixSchemaNamespace [IN] : Das Namespaceprefix dem Query voranstellen.
        \param rpResults              [OUT]: Die selektierten Knoten.

        \retval                            : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER selectXSDNodes(const IString& strQuery,
                                             bool bPrefixSchemaNamespace,
                                             IXSDNodes*& rpResults) const = 0;

    /**************************************************************************/
    /*! Get a list of all element sub nodes of this xsd complex type.
    
        \param rpElements [OUT]: Pointer to a collection of element nodes.

        \retval                : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getElements(IXSDNodes*& rpElements) = 0;

    /**************************************************************************/
    /*! Get one specific element sub node of this xsd complex type.

        \param strElementName [IN] : Name of the element.    
        \param rpElement      [OUT]: Pointer to the element node.

        \retval                    : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getElement(const IString& strElementName, IXSDNode*& rpElement) = 0;

    /**************************************************************************/
    /*! Get a list of all attribute sub nodes of this xsd complex or simple type.
    
        \param rpAttributes [OUT]: Pointer to a collection of attribute nodes.

        \retval                  : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributes(IXSDNodes*& rpAttributes) = 0;

    /**************************************************************************/
    /*! Get one specific attribute sub node of this xsd complex or simple type.

        \param strAttributeName [IN] : Name of the attribute.    
        \param rpAttribute      [OUT]: Pointer to the attribute node.

        \retval                      : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttribute(const IString& strAttributeName, IXSDNode*& rpAttribute) = 0;

    /**************************************************************************/
    /*! Get annotation.
    
        \param rpAnnotationNode [OUT]: Pointer to the annotation node.

        \retval                      : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAnnotation(IXSDNode*& rpAnnotationNode) = 0;

    /**************************************************************************/
    /*! Get appinfo.
    
        \param rpAppinfoNode [OUT]: Pointer to the appinfo node.

        \retval                   : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAppinfo(IXSDNode*& rpAppinfoNode) = 0;

    /**************************************************************************/
    /*! Get restriction.
    
        \param rpRestrictionNode [OUT]: Pointer to the restriction node.

        \retval                       : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getRestriction(IXSDNode*& rpRestrictionNode) = 0;

    /**************************************************************************/
    /*! Get the minInclusive node of a restriction node.
    
        \param rpMinInclusiveNode [OUT]: Pointer to the minInclusive node.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getMinInclusiveNode(IXSDNode*& rpMinInclusiveNode) = 0;

    /**************************************************************************/
    /*! Get the maxInclusive node of a restriction node.
    
        \param rpMaxInclusiveNode [OUT]: Pointer to the maxInclusive node.

        \retval                        : Error code.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getMaxInclusiveNode(IXSDNode*& rpMaxInclusiveNode) = 0;

    /**************************************************************************/
    /*! \See IXMLNode::getParentNode
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getParentXSDNode(IXSDNode*& rpParentNode) const = 0;

    /**************************************************************************/
    /*! Das base Attribut lesen.

        \param strBase [OUT]: Base ohne Schema-Namespace-Präfix.

        \retval             : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getBase(IString& strBase) const = 0;

    /**************************************************************************/
    /*! Das base Attribut setzen.

        \param strBase [IN]: Base ohne Schema-Namespace-Präfix.

        \retval            : Fehlercode.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setBase(const IString& strBase) = 0;

    /**************************************************************************/
    /*! Die interne IXMLNode-Instanz lesen. Es erfolgt kein addRef().         */
    /**************************************************************************/
    virtual IXMLNode& MQUALIFIER getXMLNodeInternal() = 0;

    /**************************************************************************/
    /*! Die interne IXMLNode-Instanz lesen. Es erfolgt kein addRef().
        Const Methode.                                                        */
    /**************************************************************************/
    virtual const IXMLNode& MQUALIFIER getXMLNodeInternalConst() const = 0;
};


END_NAMESPACE_Zeus


#endif
