/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : StringContainer
 * Package : System
 * Author  : Andreas Steiner
 * Datum   : $Date: 18.03.08 7:36 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IStringContainer.hpp $
** 
** 2     18.03.08 7:36 Ast
** Kommentar korrigiert
** 
** 1     17.03.08 14:07 Ast
** erstellt
***************************************************************************/

#ifndef IStringContainerHPP
#define IStringContainerHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines a container for a Zeus string with memory managment
    functions.
*/
/***************************************************************************/
class IStringContainer : public IZUnknown
{
  public:

    /**************************************************************************/
    /*! Returns the assigned string from the container.
        \return : assigned string
    */
    /**************************************************************************/
    virtual IString& getData() = 0;

    /**************************************************************************/
    /*! Assigns a string to the container.
        \param rString : string to assign
    */
    /**************************************************************************/
    virtual void setData(IString& rString) = 0;

};

END_NAMESPACE_Zeus


#endif

