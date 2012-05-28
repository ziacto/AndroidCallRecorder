/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : IObserver
 * Package : system
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 7.04.08 19:08 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/ISubject.hpp $
** 
** 10    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef ISubjectHPP
#define ISubjectHPP

#include <zeusbase/System/Interfaces/IObserver.hpp>

#ifdef ENABLE_GUID_USAGE
  // {407C915B-0FE0-410a-AFAC-4D6FC399540E}
  #define INTERFACE_ISubject       TIID(0x407c915b, 0xfe0, 0x410a, 0xaf, 0xac, 0x4d, 0x6f, 0xc3, 0x99, 0x54, 0xe)
#else
  #define INTERFACE_ISubject       0x00000007
#endif


BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! Definiert im Subject-Observer-Pattern das Subject. Dem Subject k�nen
    mehrere Observer registriert und dann wieder entfernt werden.
*/
/*****************************************************************************/
class ISubject : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ISubject)
  
  public:
    /*************************************************************************/
    /*! Ein Observer hinzufgen
        \param rObserver : Referenz auf den Observer
        \retval RET_NOERROR: Fehlerfreies hinzufgen des Observers
        \retval RET_REQUEST_FAILED : Observer kann nicht hinzugefgt werden
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER attach(IObserver& rObserver)=0;

    /*************************************************************************/
    /*! Ein Observer entfernen
        \param rObserver : Referenz auf den Observer
        \retval RET_NOERROR: Fehlerfreies entfernen des Observers
        \retval RET_REQUEST_FAILED : Observer kann nicht entfernt werden
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER detach(IObserver& rObserver)=0;

};


END_NAMESPACE_Zeus

#endif
