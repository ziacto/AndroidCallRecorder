/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXMLDocument
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 25.10.06
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IXMLDocument.hpp $
** 
** 18    21.07.08 12:59 Mab
** XSD base development.
** 
** 17    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 16    4.02.08 11:37 Ast
** method for namespace usage
** 
** 15    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 14    21.06.07 6:25 bha
** Keeping the file name on saveAs() method
** 
** 13    4.06.07 15:42 bha
** 
** 12    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXMLDocumentHPP 
#define IXMLDocumentHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IXMLNode.hpp>
#include <zeusbase/System/Interfaces/IXMLErrorReporter.hpp>

#ifdef ENABLE_GUID_USAGE
  // {997DBBE8-12F8-4c56-A6B6-2E734970EFDE}
  #define INTERFACE_IXMLDocument     TIID(0x997dbbe8, 0x12f8, 0x4c56, 0xa6, 0xb6, 0x2e, 0x73, 0x49, 0x70, 0xef, 0xde)
#else
  #define INTERFACE_IXMLDocument     0x00002003
#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! Das IXMLParser Interface definiert einen XML Parser
*/
/***************************************************************************/
class IXMLDocument : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXMLDocument)    
  
  public:
    
    /**************************************************************************/
    /*! Returns the main node of the xml dom tree
        \param rpMainNode : return parameter of the main node
        \retval RET_NOERROR : main node returned.
        \retval RET_REQUEST_FAILED : Could not return the main node
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getMainNode(IXMLNode*& rpMainNode) = 0;
    
    /**************************************************************************/
    /*! Returns the DOM buffer as a stream.
        \param stream : return parameter of a stream of data
        \retval RET_NOERROR : Stream returned
        \retval RET_REQUEST_FAILED : Could return stream
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getStream(IString& rStream)const=0;
    
    /**************************************************************************/
    /*! Saves the document. This method will fail, if a stream has been loaded
        previously. 
        \retval RET_NOERROR : File saved
        \retval RET_REQUEST_FAILED : Could not save file
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER save() = 0;
    
    /**************************************************************************/
    /*! Saves the document using a new file name. This method will fail, 
        if a stream has been loaded previously. 
        \param rFilename : Name of the new file
        \param bKeepOrginalFileName : Keeps the original file name stored. This
                                      flag is needed to store a copy
        \retval RET_NOERROR : File saved
        \retval RET_REQUEST_FAILED : Could not save file
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER saveAs(const IString& rFilename, bool bKeepOrginalFileName = false) = 0;

    /**************************************************************************/
    /*! Creates a new xml DOM node. The node will be returned to the caller and
        can be inserted or added using the IXMLNode method insert() or append().
        \param uiNodeType : Type of the node (see defines)
        \param rName : Name of the node
        \param rUri : Ressource identifier (not used for all types
                      -> see XML spec. of xercesc
        \param rpNode : return parameter of the created node.
        \retval RET_NOERROR : Node created.
        \retval RET_REQUEST_FAILED : Could not create the node
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER createNewNode(Uint uiNodeType,
                                            const IString& rName,
                                            const IString& rUri,
                                            IXMLNode*& rpNode) = 0;

    /**************************************************************************/
    /*! Validates the xml document. Te errors will be returned by the
        the error handler registered
        \param pReporter : reporter instance
        \retval RET_NOERROR : XML is ok
        \retval RET_INVALID_DATA : XML is not valid.
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER validate(IXMLErrorReporter* pReporter = NULL) = 0;

    /**************************************************************************/
    /*! Returns the complete node list of the xml dom tree
        \param rpList : return parameter of the list
        \retval RET_NOERROR : list returned.
        \retval RET_REQUEST_FAILED : Could not return the list
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER getNodeList(IXMLNodeList*& rpList) = 0;

    /**************************************************************************/
    /*! Returns the file name of the XML document. If the file name is
        empty, the document was built out of a stream.
    */
    /**************************************************************************/
    virtual void MQUALIFIER getFileName(IString& rFileName) const = 0;

    /**************************************************************************/
    /*! Sets the prefix for a specific name space. Use this method before
        querying data with X-Path.
        \param rPrefix : Prefix to use
        \param rNameSpace : Name space 
    */
    /**************************************************************************/
    virtual void MQUALIFIER useNamespace(const IString& rPrefix, const IString& rNameSpace) = 0;

    /**************************************************************************/
    /*! Removes a specific name space.

        \param rPrefix : Prefix to remove.                                    */
    /**************************************************************************/
    virtual void MQUALIFIER removeNamespace(const IString& rPrefix) = 0;
};

END_NAMESPACE_Zeus

#endif 
