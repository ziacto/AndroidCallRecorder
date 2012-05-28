/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXMLNode
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 16.04.08 15:48 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXMLNode.hpp $
** 
** 29    16.04.08 15:48 Bha
** extending sibling to filter element nodes
** 
** 28    8.04.08 14:19 Bha
** Usage of GUID for Interfaces
** 
** 27    8.04.08 14:03 Ast
** Dokumentation nachgeführt
** 
** 26    7.04.08 10:06 Ast
** createElementChildNodeBySchema erweitert
** 
** 25    3.04.08 13:16 Ast
** Method getNextSibling added
** 
** 24    1.04.08 13:30 Ast
**  createElementChildNodeBySchema hinzugefügt.
** 
** 23    7.02.08 8:57 Mab
** getAttributeValueUint hinzugefügt.
** 
** 22    6.02.08 15:57 Mab
** Lesen von Attributen als bool, Int, Float hinzugefügt.
** 
** 21    2.10.07 14:18 dle
** get and set methods for text sub nodes
** 
** 20    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 19    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
** 
** 16    20.10.06 17:14 Mabbuehl
** Interface IXMLNode: Pointers to references.
** 
** 14    29.09.06 11:24 Mabbuehl
** Automatisierte Ersetzung von Framework 1 durch Framework 2 Definitionen
** und Klassen.
***************************************************************************/

#ifndef IXMLNodeHPP
#define IXMLNodeHPP

#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IXMLNodeList.hpp>
#include <zeusbase/System/Interfaces/IXPathResults.hpp>

#define TYPE_NODE_CDATA_SECTION                   1
#define TYPE_NODE_COMMENT                         2
#define TYPE_NODE_DOCUMENT                        3
#define TYPE_NODE_DOCUMENT_FRAGMENT               4
#define TYPE_NODE_TEXT                            5
#define TYPE_NODE_DOCUMENT_TYPE                   6
#define TYPE_NODE_ELEMENT                         7
#define TYPE_NODE_ENTITY                          8
#define TYPE_NODE_ENTITY_REFERENCE                9
#define TYPE_NODE_NOTATION                        10
#define TYPE_NODE_PROCESSING_INSTRUCTION          11
#define TYPE_NODE_ATTRIBUTE                       12
#define TYPE_NODE_DECL                            13


#define IMPCLASSNAME_XERCESC                      0
#define IMPCLASSNAME_MSXML                        1

#ifdef ENABLE_GUID_USAGE
  // {9ADBE736-BB3B-4c78-BE1A-C73ACE5D3A1A}
  #define INTERFACE_IXMLNode     TIID(0x9adbe736, 0xbb3b, 0x4c78, 0xbe, 0x1a, 0xc7, 0x3a, 0xce, 0x5d, 0x3a, 0x1a)
#else
  #define INTERFACE_IXMLNode     0x00002000
#endif


BEGIN_NAMESPACE_Zeus

class IXMLNodeList;

/******************************************************************************/
/*! Das Interface IXMLNode definiert die Schnittstelle zu einem Node des
    DOM Trees
*/
/******************************************************************************/
class IXMLNode : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXMLNode)
  
  public :

    /**************************************************************************/
    /*! Den Namen des Nodes ermitteln
        \param rName : Rckgabeparameter des Nodenamens
        \retval RET_NOERROR : Fehlerfreie Rckgabe
        \retval RET_REQUEST_FAILED : Fehler beim Zurckgeben aufgetreten
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNodeName(IString& rName) const = 0;

    /**************************************************************************/
    /*! Den Typ des Nodes ermitteln. Der Typ wird Implementationsunabhï¿½gig
        zurckgegeben (Define).
        \retval TYPE_NODE_CDATA_SECTION                   1
        \retval TYPE_NODE_COMMENT                         2
        \retval TYPE_NODE_DOCUMENT                        3
        \retval TYPE_NODE_DOCUMENT_FRAGMENT               4
        \retval TYPE_NODE_TEXT                            5
        \retval TYPE_NODE_DOCUMENT_TYPE                   6
        \retval TYPE_NODE_ELEMENT                         7
        \retval TYPE_NODE_ENTITY                          8
        \retval TYPE_NODE_ENTITY_REFERENCE                9
        \retval TYPE_NODE_NOTATION                        10
        \retval TYPE_NODE_PROCESSING_INSTRUCTION          11
        \retval TYPE_NODE_ATTRIBUTE                       12
        \retval TYPE_NODE_DECL                            13
    */
    /**************************************************************************/
    virtual Uint MQUALIFIER getNodeType() const = 0;

    /**************************************************************************/
    /*! Den Nodewert ermitteln.
        \param rValue : Rckgabeparameter des Nodewerts
        \retval RET_NOERROR : Fehlerfreie Rckgabe
        \retval RET_REQUEST_FAILED : Fehler beim Zurckgeben aufgetreten
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNodeValue(IString& rValue) const = 0;

    /**************************************************************************/
    /*! Mit dieser Methode kann einfach der Wert eines Attributs des Nodes
        abgefragt werden.
        \param rName : Name des Attributs
        \param rValue : Rueckgabewert des Attributs
        \retval RET_NOERROR : Fehlerfreie Rckgabe
        \retval RET_REQUEST_FAILED : Fehler beim Zurckgeben aufgetreten
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributeValue(const IString& rName, IString& rValue) const= 0;

    /**************************************************************************/
    /*! Ein Attribut als Int lesen.

        \param rName  [IN] : Name des Attributs.
        \param rValue [OUT]: Gelesener Wert.
        
        \retval            : Fehlercode.                                      */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributeValueInt(const IString& rName, Int& rValue) const = 0;

    /**************************************************************************/
    /*! Ein Attribut als Uint lesen.

        \param rName  [IN] : Name des Attributs.
        \param rValue [OUT]: Gelesener Wert.
        
        \retval            : Fehlercode.                                      */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributeValueUint(const IString& rName, Uint& rValue) const = 0;

    /**************************************************************************/
    /*! Ein Attribut als bool lesen.

        \param rName  [IN] : Name des Attributs.
        \param rValue [OUT]: Gelesener Wert.
        
        \retval            : Fehlercode.                                      */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributeValueBool(const IString& rName, bool& rValue) const = 0;

    /**************************************************************************/
    /*! Ein Attribut als Float lesen.

        \param rName  [IN] : Name des Attributs.
        \param rValue [OUT]: Gelesener Wert.
        
        \retval            : Fehlercode.                                      */
    /**************************************************************************/
    virtual Retval MQUALIFIER getAttributeValueFloat(const IString& rName, Float& rValue) const = 0;

    /**************************************************************************/
    /*! Diese Methode gibt alle SubNodes eines Nodes in einer IXMLNodeList
        zurck.
        \param rpList : Rckgabeparameter der Nodeliste
        \retval RET_NOERROR : Fehlerfreie Rckgabe
        \retval RET_REQUEST_FAILED : Fehler beim Zurckgeben aufgetreten
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNodeList(IXMLNodeList*& rpList) const = 0;

    /**************************************************************************/
    /*! Diese Funktion erlaubt es nach einem gestimmten NodeNamen in der
        NodeListe eines Nodes zu suchen.<BR>
        Wird im Parameter NodeNamen ein leerer String bergeben wird einfach der
        erste Node der Liste zurckgegeben.
        \param pName : Name des Nodes nach dem gesucht werden soll
    */
    /**************************************************************************/
    virtual void MQUALIFIER resetNodeIterator(const IString* pName = NULL) const = 0;

    /**************************************************************************/
    /*! Diese Funktion sollte erst aufgerufen werden, wenn zuvor einmal die <BR>
        Funktion getFirstNode aufgerufen wurde. Denn diese Funktion gibt den <BR>
        nï¿½hsten Node der dem Namen des Parameters NodeName entspricht. <BR>
        Diese Funktion kann nun mehrmals hintereinander aufgerufen werden, bis
        kein entsprechender Node mehr gefunden wird.
        \param rpNode : Rckgabeparameter des XMLNodes
        \retval RET_NOERROR : Fehlerfreie Rckgabe
        \retval RET_REQUEST_FAILED : Fehler beim Zurckgeben aufgetreten
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNextNode(IXMLNode*& rpNode) const = 0;

    /**************************************************************************/
    /*! Mit dieser Methode kann einfach ermittelt werden, ob ein Node noch
        SubNodes besitzt.
        \retval true : ja der Node besitzt noch SubNodes
        \retval false: nein der Node besitzt keine SubNodes
    */
    /**************************************************************************/
    virtual bool MQUALIFIER hasChildren() const = 0;

    /**************************************************************************/
    /*! Mit dieser Funtkion kann ein neuer SubNode hinzugefgt werden.
        \param rNewNode : Zeiger auf ein IXMLNode Interface
        \retval RET_NOERROR : Node erfolgreich hinzugefgt
        \retval RET_REQUEST_FAILED : Node kann nicht hinzugefgt werden
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER appendNode(IXMLNode& rNewNode) = 0;

    /**************************************************************************/
    /*! Mit dieser Funktion wird ein neuer SubNode erzeugt. Dieser Node ist auch
        automatisch in der NodeList aufgenommen.
        \param uiType  : bestimmt die Art des Nodes
        \param rName : Namen des neuen Nodes
        \param pUri  : namespaceURI parameter der als prefix fr den <BR>
                          Nodenamen dient. Wird ein leerer String bergeben,<BR>
                          wird der Default namespaceURI verwendet.
        \param rpNode : Rueckgabeparameter des XMLNodes
        \retval RET_NOERROR : Fehlerfreie Rueckgabe
        \retval RET_REQUEST_FAILED : Fehler beim Zurueckgeben aufgetreten
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER createNewChildNode(Uint uiType,
                                                 const IString& rName,
                                                 const IString* pUri,
                                                 IXMLNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Mit dieser Funktion wird ein neuer SubNode erzeugt. Dieser Node ist auch
        automatisch in der NodeList aufgenommen.
        \param rName : Namen des neuen Nodes
        \param rSchemaNode: Node, der die Schemainformationen (xsd:complexType) für den zu
                            erstellenden Knoten beinhaltet.
        \param rpNode : Rueckgabeparameter des XMLNodes
        \param ppRightSibling : XML-Node rechts vom eingefügten Knoten
        \retval RET_NOERROR : Fehlerfreie Rueckgabe
        \retval RET_INVALID_PARAMETER : rSchemaNode ist nicht ein gültiger
                                        XSD-Node
        \retval RET_INVALID_TYPE : Typdefinition wurde nicht vorhanden
        \retval RET_ABORT : Knoten kann nicht eingefügt werden, da die maximale
                            Anzahl erreicht wurde
        \retval RET_REQUEST_FAILED : Fehler beim Zurueckgeben aufgetreten
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER createElementChildNodeBySchema(const IString& rName,
                                                             IXMLNode&  rSchemaNode,
                                                             IXMLNode*& rpNode,
                                                             IXMLNode** ppRightSibling = NULL) = 0;

    /**************************************************************************/
    /*! Setzen eines neuen Nodewerts
        \param rData : neuer Wert des Nodes
        \retval RET_NOERROR : Wert wurde geï¿½dert
        \retval RET_REQUEST_FAILED : Wert konnte nicht geï¿½dert werden
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setNodeValue(const IString& rData) = 0;

    /**************************************************************************/
    /*! Setzen eines Attributwerts
        \param rName  : Name des Attributes
        \param rValue : neuer Wert fr das Attribute
        \retval RET_NOERROR : Wert wurde geï¿½dert
        \retval RET_REQUEST_FAILED : Wert kann nicht verï¿½dert werden
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setAttributeValue(const IString& rName,
                                                const IString& rValue) = 0;

    /**************************************************************************/
    /*! Entfernt den Node aus der XMLNodeList des ParentNodes
        \retval RET_NOERROR : Knoten wurde entfernt
        \retval RET_REQUEST_FAILED : Knoten konnte nicht entfernt werden
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER removeMe() = 0;

    /**************************************************************************/
    /*! Mit dieser Methode kann ermittelt werden, welche Parserimplementation
        fr das Interface verwendet wurde.
        \retval IMPCLASSNAME_STDOMNODE_XERCESC
    */
    /**************************************************************************/
    virtual Uint MQUALIFIER getImplClass() const = 0;


    /**************************************************************************/
    /*! This methods resets the attribute iterator. The next call of 
        getNextAttribute() will return the first attribute
    */
    /**************************************************************************/
    virtual void MQUALIFIER resetAttributeIterator() const= 0;


    /**************************************************************************/
    /*! Mit dieser Methode wird das naechste Attribut zurueckgegben
        \param rName : Referenz auf den Attributnamen
        \param rValue : Referenz auf den Wert des Attributs
        \retval RET_NOERROR : Attribut gefunden
        \retval RET_REQUEST_FAILED : kein Attribut gefunden
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNextAttribute(IString& rName,
                                               IString& rValue) const = 0;

    /**************************************************************************/
    /*! Ermittelt den Parent des DOMNodes
        \param rpParent : Parentknoten
        \retval RET_NOERROR : Parent zurckgegeben
        \retval RET_REQUEST_FAILED : kein Parent gefunden
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getParentNode(IXMLNode*& rpParent) const = 0;

    /**************************************************************************/
    /*! Ermittelt den rechten Sibling des DOMNodes
        \param rpParent : Siblingknoten
        \param bOnlyElements : Is this flag set, only ElementNodes are
                               considered
        \retval RET_NOERROR : Sibling zurckgegeben
        \retval RET_REQUEST_FAILED : kein Sibling gefunden
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNextSibling(IXMLNode*& rpParent, bool bOnlyElements = true) const = 0;

    /**************************************************************************/
    /*! Suchen einer Menge von Knoten nach dem XPfad-Query
        \param rQuery : XPfad des gesuchten Knoten
        \param rpResults : Rckgabeparameter des Knotenmenge
        \retval RET_REQUEST_FAILED : Keine Knoten gefunden
        \retval RET_NOERROR : Fehlerfreie ï¿½ergabe
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER selectNodes(const IString& rQuery,
                                          IXPathResults*& rpResults) const = 0;

    /**************************************************************************/
    /*! Ein Knoten klonen. Es entsteht ein extaktes Abbild des Knotens
        \param bRecurs : Rekursives Klonen
        \param rpNode : Rckgabeparameter des Knotens
        \retval RET_REQUEST_FAILED : Kann Knoten nicht klonen
        \retval RET_NOERROR : Fehlerfreie ï¿½ergabe
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER clone(bool bRecurs, IXMLNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Ein Child-Knoten einfgen.
        \param rNode : Knoten welcher eingefgt werden soll
        \param pBeforeNode : Vor diesem Knoten einfgen
        \retval RET_REQUEST_FAILED : Kann Knoten nicht eingefgt werden
        \retval RET_NOERROR : Fehlerfreies Einfgen
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER insertNode(IXMLNode& rNode, IXMLNode* pBeforeNode) = 0;

    /**************************************************************************/
    /*! serializes the node
        \param rStream : Return parameter of the stream
        \retval RET_REQUEST_FAILED : Could not serialize the node
        \retval RET_NOERROR : Serializing was successful
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER serializeNode(IString& rStream) const = 0;

    /**************************************************************************/
    /*! This method returns the implementation pointer of a concrete xml
        node. Do not use this method outside of the XML_Service module
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getImplPtr(void** pImpl) const = 0;
    
    /**************************************************************************/
    /*! This method sets the implementation pointer of a concrete xml
        node. Do not use this method outside of the XML_Service module
    */
    /**************************************************************************/
    virtual void MQUALIFIER setImplPtr(void* pImpl) = 0;

    /**************************************************************************/
    /*! Suchen einer Menge von Knoten nach dem XPfad-Query
        \param rQuery : XPfad des gesuchten Knoten
        \param rpResults : Rckgabeparameter des Knotenmenge
        \retval RET_REQUEST_FAILED : Keine Knoten gefunden
        \retval RET_NOERROR : Fehlerfreie ï¿½ergabe
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER selectNode(const IString& rQuery,
                                         IXMLNode*& rpResult) const = 0;

    /**************************************************************************/
    /*! Suchen des ersten Child-Knotens mit entsprechendem Namen
        \param rName : Namen des gesuchten Knoten
        \param rpChildNode : Rckgabeparameter des Child-Knotens
        \retval RET_REQUEST_FAILED : Kein Knoten gefunden
        \retval RET_INVALID_DATA : Name ist ein Leernamen. 
        \retval RET_NOERROR : Fehlerfreie Rckgabe
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getChildNode(const IString& rName, IXMLNode*& rpChildNode) const= 0;

    /**************************************************************************/
    /*! This method removes an attribute from this node.

        \param rName : Name of the attribute

        \retval RET_NOERROR : Attribute removed
        \retval RET_REQUEST_FAILED : Could not find such an attribute
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER removeAttribute(const IString& rName) = 0;

    /**************************************************************************/
    /*! returns the text child node. If the node is not an element this
        method will fail.
        \param rText : return parameter
        \retval RET_NOERROR : text returned
        \retval RET_REQUEST_FAILED : node is not an element
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getText(IString& rText) const= 0;

    /**************************************************************************/
    /*! sets the text child node. If the node is not an element this
        method will fail. If there exists a text node already, this will simply
        overwrite its content.
        \param rText : Text to set
        \retval RET_NOERROR : text set
        \retval RET_REQUEST_FAILED : node is not an element
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setText(const IString& rText)= 0;
};


END_NAMESPACE_Zeus


#endif
