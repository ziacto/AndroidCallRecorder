/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IRunnable
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IRunnable.hpp $
** 
** 9     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 8     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 7     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IRunnableHPP
#define IRunnableHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>


#ifdef ENABLE_GUID_USAGE
  // {995CE998-4920-4eff-B7BA-ABFD3357A994}
  #define INTERFACE_IRunnable  TIID(0x995ce998, 0x4920, 0x4eff, 0xb7, 0xba, 0xab, 0xfd, 0x33, 0x57, 0xa9, 0x94)
#else
  #define INTERFACE_IRunnable  0x00000002
#endif

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! Das Runable Interface definiert Methoden zum Ausfuehren eines Objekts
    in einem Thread Objekt
*/
/***************************************************************************/
class IRunnable : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IRunnable)
  
  public:

    /***********************************************************************/
    /*! Diese Methode wird vom Thread ausgefuehrt
    */
    /***********************************************************************/
    virtual void MQUALIFIER execute()=0;
};

END_NAMESPACE_Zeus

#endif

