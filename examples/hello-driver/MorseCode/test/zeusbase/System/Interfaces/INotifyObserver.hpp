/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : INotifyObserver
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 5.04.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/INotifyObserver.hpp $
** 
** 7     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 6     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 5     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/


#ifndef INotifyObserverHPP
#define INotifyObserverHPP

#include <zeusbase/System/Interfaces/IObserver.hpp>

BEGIN_NAMESPACE_Zeus

#ifdef ENABLE_GUID_USAGE
  // {F8B4CFCA-4170-4f98-B0E4-696A89C9B939}
  #define INTERFACE_INotifyObserver   TIID(0xf8b4cfca, 0x4170, 0x4f98, 0xb0, 0xe4, 0x69, 0x6a, 0x89, 0xc9, 0xb9, 0x39)
#else
  #define INTERFACE_INotifyObserver   0x00000012
#endif

/****************************************************************************/
/*! The notification observer interface defines an observer for simply
    notification. The information has to be read from the subject.
*/
/****************************************************************************/
class INotifyObserver : public IObserver
{
  HIDE_ASSIGNMENT_OPERATOR(INotifyObserver)    
  
  public:
    /*************************************************************************/
    /*! This method is called for notification of an observer.
    */
    /*************************************************************************/
    virtual void MQUALIFIER notify()=0;

};


END_NAMESPACE_Zeus

#endif

