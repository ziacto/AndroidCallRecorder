/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ICriticalSection
 * Package : System
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/Interfaces/ICriticalSection.hpp $
** 
** 7     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 6     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef ICriticalSectionHPP 
#define ICriticalSectionHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>


BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This interface defines a scritical section or a lock object
*/
/***************************************************************************/
class ICriticalSection : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ICriticalSection)
  
  public:
    
    /***********************************************************************/
    /*! Locks the section
    */
    /***********************************************************************/
    virtual void MQUALIFIER enter()=0;
  
    /***********************************************************************/
    /*! Unlocks the section
    */
    /***********************************************************************/
    virtual void MQUALIFIER leave()=0;
};

END_NAMESPACE_Zeus

#endif
