/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXLoaderObject
 * Package : system
 * Author  : Benjamin Hadorn
 * Datum   : 8.05.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXLoaderObject.hpp $
** 
** 16    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 15    4.04.08 10:00 Ast
** Beschreibung korrigiert
** 
** 14    4.04.08 9:47 Ast
** getExtXMLRefNode added
** 
** 12    2.04.08 14:16 Ast
** Method  getExtXMLRefNode added
** 
** 11    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 10    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXLoaderObjectHPP
#define IXLoaderObjectHPP
 
#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IXMLDocument.hpp>


#ifdef ENABLE_GUID_USAGE
  // {6969BD24-A96C-4d09-B09B-D0B3E62DD211}
  #define INTERFACE_IXLoaderObject    TIID(0x6969bd24, 0xa96c, 0x4d09, 0xb0, 0x9b, 0xd0, 0xb3, 0xe6, 0x2d, 0xd2, 0x11)
#else
  #define INTERFACE_IXLoaderObject    0x00000004
#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines a loadable object node, witch can load and unload the
    children objects (load and unload a ressource library)
*/
/***************************************************************************/
class IXLoaderObject : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IXLoaderObject)  

  public:
    /***********************************************************************/
    /*! Load the ressource DLL
        \retval RET_NOERROR : Resource loaded
        \retval RET_INTERNAL_ERROR : An internal unknown error occured 
                                     loading the resource
        \retval RET_REQUEST_FAILED : Could not load the resource (file 
                                     not available)
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER load()=0;
    
    /***********************************************************************/
    /*! Unload the resource
        \retval RET_NOERROR : Resource unloaded
        \retval RET_INTERNAL_ERROR : An internal unknown error occured 
                                     unloading the resource
        \retval RET_REQUEST_FAILED : Could not unload the resource
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER unload()=0;

    /***********************************************************************/
    /*! Check if the resource is loaded
        \retval true : Resource is loaded
        \retval false : Resource is not loaded
    */
    /***********************************************************************/
    virtual bool MQUALIFIER isLoaded()=0;

    /***********************************************************************/
    /*! Get the xml node of the xobject
        \param rpNode : return parameter of the xml node
        \param bResolveExtXMLRef : return the xml node of the external XML
                                   reference document, if exists
        \retval RET_NOERROR : node returned
        \retval RET_REQUEST_FAILED : Could not get the xml node
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getExtXMLRefNode(IXMLNode*& rpExtRefNode) const=0;

    /***********************************************************************/
    /*! This sets a external XML Reference as a XMLDocument. Only one xml 
        document can be loaded externaly.
        \param rDoc : Loaded document
        \param rMainRef : Main node of the document
        \retval RET_NOERROR : Ext reference added
        \retval RET_REQUEST_FAILED : Could not add document, because one 
                                     is loaded already
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER setExtXMLRef(IXMLDocument& rDoc, IXMLNode& rMainRef)=0;

    /***********************************************************************/
    /*! Returns the filename of the external xml file.
        \param rFileName : Return parameter of the filename
    */
    /***********************************************************************/
    virtual void MQUALIFIER getXMLFileName(IString& rFileName) const=0;

    /***********************************************************************/
    /*! Reloads the document
        \param pFileNameToCopy : Copy data form a file first
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER reload(const IString* pFileNameToCopy = NULL) = 0;


};

END_NAMESPACE_Zeus

#endif
