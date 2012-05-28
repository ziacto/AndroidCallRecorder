/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IObserver
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IObserver.hpp $
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

#ifndef IObserverHPP
#define IObserverHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>

#ifdef ENABLE_GUID_USAGE
  // {EBEC72CC-E7D6-4978-A220-55EBCBC1EB0B}
  #define INTERFACE_IObserver        TIID(0xebec72cc, 0xe7d6, 0x4978, 0xa2, 0x20, 0x55, 0xeb, 0xcb, 0xc1, 0xeb, 0xb)
#else
  #define INTERFACE_IObserver        0x00000008
#endif


BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! Der ISTObserver dient als Observerschnittstelle welche standard Methoden
    eines Observers definiert.
*/
/*****************************************************************************/
class IObserver : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IObserver)
  
  public:

    /*************************************************************************/
    /*! Diese Methode gibt den Observer frei. Ein Enable kann dadurch erfolgen.
        Speziell beim Anmelden wird diese Methode aufgerufen
    */
    /*************************************************************************/
    virtual void MQUALIFIER unlockObserver()=0;


    /*************************************************************************/
    /*! Diese Methode sperrt den Observer. Ein Disable kann dadurch erfolgen.
        Speziell beim Abmelden wird diese Methode aufgerufen
    */
    /*************************************************************************/
    virtual void MQUALIFIER lockObserver()=0;

    /*************************************************************************/
    /*! Den Parent loeschen. Diese Methode sollte nur vom Besitzer des
        Observer aufgerufen werden.
    */
    /*************************************************************************/
    virtual void MQUALIFIER clearParent()=0;

};

END_NAMESPACE_Zeus

#endif


