/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IXSLProcessor
 * Package : System
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IXSLProcessor.hpp $
** 
** 8     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
**
** 7     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 6     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IXSLProcessorHPP
#define IXSLProcessorHPP


#include <zeusbase/System/Interfaces/IPostProcessor.hpp>

#ifdef ENABLE_GUID_USAGE
  // {5764593C-6537-4958-A4F7-482B21665AC8}
  #define INTERFACE_IXSLProcessor   TIID(0x5764593c, 0x6537, 0x4958, 0xa4, 0xf7, 0x48, 0x2b, 0x21, 0x66, 0x5a, 0xc8)
#else
  #define INTERFACE_IXSLProcessor   0x00002005
#endif

BEGIN_NAMESPACE_Zeus

/******************************************************************************/
/*! This interfaces defines a post processor using xslt stylesheets
*/
/******************************************************************************/
class IXSLProcessor : public IPostProcessor
{
  HIDE_ASSIGNMENT_OPERATOR(IXSLProcessor)
  
  public:
};

END_NAMESPACE_Zeus

#endif
