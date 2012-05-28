/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Time
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 4.02.08 7:32 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Time.h $
** 
** 14    4.02.08 7:32 Bha
** changed to inline methods
** 
** 13    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 12    26.02.07 9:00 bha
**
** 7     14.09.06 14:58 bha
** definieren von portablen primitiven Datentypen
***************************************************************************/

#ifndef TimeH
#define TimeH

#include <zeusbase/System/ZObject.h>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! Wrapper class to access time and random fnctions
*/
/***************************************************************************/
zeusbase_class TTime : public TZObject
{
  public:
    //static methods
    static Uint64 getTickCount();
    static void usleep(Uint64 dwell);

    static Float64 getTimeStamp();
    static void sleep(Float64 dDwell);

    static Uint32 random(Uint32 ulFrom, Uint32 ulTo);
    static Float randomFloat(Float dFrom, Float dTo);
    static Int randomInt(Int iFrom, Int iTo);
    static void initRandom();

  protected:
    inline TTime() {}
    inline virtual ~TTime() {}

  private:
};

END_NAMESPACE_Zeus

#endif

