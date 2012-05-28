/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IPropertyAccess
 * Package : system
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IPropertyAccess.hpp $
** 
** 12    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 11    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 10    21.06.07 12:32 bha
** New method to receive all properties from a namespace
** 
** 9     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IPropertyAccessHPP
#define IPropertyAccessHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IStringList.hpp>


#ifdef ENABLE_GUID_USAGE
  // {16B02AF6-FA7F-4ece-8D4D-E3DFBFD97582}
  #define INTERFACE_IPropertyAccess    TIID(0x16b02af6, 0xfa7f, 0x4ece, 0x8d, 0x4d, 0xe3, 0xdf, 0xbf, 0xd9, 0x75, 0x82)
#else
  #define INTERFACE_IPropertyAccess    0x00000006
#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines the access to a property collection (file)
*/
/***************************************************************************/
class IPropertyAccess : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IPropertyAccess)
  
  public:
    /**********************************************************************/
    /*! adds a property value
        \param rName : Name of the property
        \param rValue : Property value
        \retval RET_NOERROR : value set
        \retval RET_REQUEST_FAILED : Invalid name
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER addProperty(const IString& rName, const IString& rValue)=0;
    
    /**********************************************************************/
    /*! Checks if a property exists
        \param rName : Name of the property
        \retval false : Property does not exist
        \retval true : Property exists
    */
    /**********************************************************************/
    virtual bool MQUALIFIER existsProperty(const IString& rName)const =0;
    
    /**********************************************************************/
    /*! Returns all property names of this set
        \param rList : Return parameter
    */
    /**********************************************************************/
    virtual void MQUALIFIER getPropertyNames(IStringList& rList)const =0;

    /**********************************************************************/
    /*! This Method will collect all properties matching a name space
        \param rNameSpace : name space of the property
        \param rList : List of property name
    */
    /**********************************************************************/
    virtual void MQUALIFIER getPropertyNamesByNameSpace(const IString& rNameSpace, IStringList& rList) const = 0;

    /**********************************************************************/
    /*! Returns a property value
        \param rName : Name of the property
        \param rValue : Property value
        \retval RET_NOERROR : value returned
        \retval RET_REQUEST_FAILED : Invalid name
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER getPropertyValue(const IString& rName, IString& rValue)const =0;

    /**********************************************************************/
    /*! Sets a property value
        \param rName : Name of the property
        \param rValue : Property value
        \retval RET_NOERROR : value set
        \retval RET_REQUEST_FAILED : Invalid name
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER setPropertyValue(const IString& rName, const IString& rValue)=0;

    /**********************************************************************/
    /*! Returns a property path value. This converts any path variables
        into the normal absolute path
        \param rName : Name of the property
        \param rValue : Property path value
        \retval RET_NOERROR : value returned
        \retval RET_REQUEST_FAILED : Invalid name
        \retval RET_INVALID_PARAMETER : name or value is not valid
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER getPropertyPathValue(const IString& rName, IString& rValue)const =0;

    /**********************************************************************/
    /*! Returns a property file value. This converts any path variables
        into the normal absolute file path
        \param rName : Name of the property
        \param rValue : Property path value
        \retval RET_NOERROR : value returned
        \retval RET_REQUEST_FAILED : Invalid name
        \retval RET_INVALID_PARAMETER : name or value is not valid
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER getPropertyFileValue(const IString& rName, IString& rValue)const =0;
};

END_NAMESPACE_Zeus

#endif
