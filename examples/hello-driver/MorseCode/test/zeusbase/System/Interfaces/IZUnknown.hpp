/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IZUnknown
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 10.04.08 15:11 $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/Interfaces/IZUnknown.hpp $
** 
** 15    10.04.08 15:11 Tbu
** ID reset to IUnknown.
** 
** 13    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 12    11.10.07 13:24 Mabbuehl
** Comment concerning include order added.
** 
** 11    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 10    5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
** 
** 8     20.02.07 10:19 bha
** Ueberarbeiten von ICAST's
***************************************************************************/

#ifndef IZUnknownHPP
#define IZUnknownHPP

#include <zeusbase/Config/PlatformDefines.hpp>
#include <zeusbase/Config/InterfaceID.hpp> // Must be included BEFORE RetvalDefines.hpp.
#include <zeusbase/Config/RetvalDefines.hpp>
#include <zeusbase/System/Interfaces/IZUnknownImplHelper.hpp>

#ifdef ENABLE_GUID_USAGE
  // {0000000-0000-0000-C000-000000000046} Do not modify! Must be equal to IUnknown from COM.
  #define INTERFACE_IZUnknown  TIID(0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46)
#else
  #define INTERFACE_IZUnknown  0x00000000
#endif


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! The interface IZUnknown is used as the basic interface of the framework.
    It defines methods for memory management in C++. The concept is based
    on reference counters. Each call of addRef will increase the counter,
    each call of release() will decrease the counter. If the counter
    reaches zero, the object will be deleted automatically. When
    creating an new object, the reference counter is initalized with one and
    no addRef() must be called.
*/
/***************************************************************************/
class IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IZUnknown)
  HIDE_DESTRUCTOR(IZUnknown)

  public:

    /***********************************************************************/
    /*! This method is used to cast to different interface types. This is
        a secure way asking for other implemented interfaces, since C++
        does not reject invalid casts.
        \param uiInterfaceID : ID of the requested interface
        \param ppIface : return value of the interface. The pointer
                       contains the address of the requested interface
        \retval RET_NOERROR : Interface returned
        \retval RET_UNKNOWN_INTERFACE : Interface is not valid or not
                              implemented
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER askForInterface(const InterfaceID& rInterfaceID, IZUnknown*& rpIface)=0;

    /***********************************************************************/
    /*! This method increases the reference counter of this object.
        The call is const because it will not change the content of the
        object, since the reference counter is not an object data.
        This allows to handle const reference using addRef() and release().
    */
    /***********************************************************************/
    virtual void MQUALIFIER addRef() const=0;

    /***********************************************************************/
    /*! This method decreases the reference counter of this object.
        This call is const as well (like addRef()). The killing of an object
        is allowed by const method, because the content is not used any more.
    */
    /***********************************************************************/
    virtual void MQUALIFIER release() const=0;

};

END_NAMESPACE_Zeus

#endif
