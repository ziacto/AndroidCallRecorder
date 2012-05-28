/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : SettingsManager
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/ISettingsManager.hpp $
** 
** 3     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 2     18.06.07 7:33 bha
** Observer notification
** 
** 1     11.06.07 10:16 bha
***************************************************************************/

#ifndef ISettingsManagerHPP
#define ISettingsManagerHPP

#include <zeusbase/System/Interfaces/IPropertyAccess.hpp>

BEGIN_NAMESPACE_Zeus

class IXMLDocument;
class INotifyObserver;

/*****************************************************************************/
/*! Interface for settings manager access and singleton delegation
*/
/*****************************************************************************/
class ISettingsManager : public IPropertyAccess
{
  HIDE_ASSIGNMENT_OPERATOR(ISettingsManager)

  public:
    /*************************************************************************/
    /*! Returns the document of the base singleton object
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER getUserDocument(NAMESPACE_Zeus::IXMLDocument*& rpDocument) const = 0;

    /**************************************************************************/
    /*! Notifies all observer instances
    */
    /**************************************************************************/
    virtual void MQUALIFIER notifyObservers()=0;

    /**************************************************************************/
    /*! attaches an observer to the user settings
    */
    /**************************************************************************/
    virtual void MQUALIFIER attach(INotifyObserver& rObserver)=0;

    /**************************************************************************/
    /*! detaches an observer to the user settings
    */
    /**************************************************************************/
    virtual void MQUALIFIER detach(INotifyObserver& rObserver)=0;
};

END_NAMESPACE_Zeus

#endif
