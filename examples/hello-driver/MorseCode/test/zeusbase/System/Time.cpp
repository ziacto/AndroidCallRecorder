/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus                                                          
 * Module  : Time
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 4.04.08 19:04 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Time.cpp $
** 
** 22    4.04.08 19:04 Bha
** eliminated coding errors and warnings for VC2005 and C++Builder 2007
** 
** 21    14.03.08 11:21 Bha
** Bugfix for C++Builder 2007
** 
** 20    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 19    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
** 
** 10    18.09.06 12:40 Mabbuehl
** Bereinigung von Borland-Release-Warnungen, wo es m�lich und
** effizienter ist.
** 
** 9     14.09.06 14:58 bha
** definieren von portablen primitiven Datentypen
** 
** 8     11.09.06 15:51 Mabbuehl
** Uninitialized Pointers.
***************************************************************************/

#if defined(__GNUC__)
  #include <stddef.h>
  #include <unistd.h>
  #include <sys/time.h>
  #include <stdlib.h>
  #include <stdio.h>
#else
  #include <windows.h>

  #ifdef _MSC_VER
    #pragma warning(push, 1)
  #endif

  #include <stdlib.h>
  #include <stdio.h>
  #include <errno.h>

  #ifdef _MSC_VER
    #pragma warning(pop)
  #endif

  #include <time.h>
#endif

#include <zeusbase/System/Time.h>

#include <math.h>

USING_NAMESPACE_Zeus

#ifdef WIN32
/***************************************************************************/
/*! This code is a implementation of the gettimeofday-function from linux.
    Code from http://www.tcpdump.org/lists/workers/2005/12/msg00003.html

    Number of micro-seconds between the beginning of the Windows epoch
    (Jan. 1, 1601) and the Unix epoch (Jan. 1, 1970).

    This assumes all Win32 compilers have 64-bit support.
*/
/***************************************************************************/
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS) || defined(__WATCOMC__)
  #define DELTA_EPOCH_IN_USEC  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_USEC  11644473600000000ULL
#endif

static Uint64 filetime_to_unix_epoch(const FILETIME *ft)
{
  Uint64 uldRes = (Uint64) ft->dwHighDateTime << 32;

  uldRes |= ft->dwLowDateTime;
  uldRes /= 10;                   /* from 100 nano-sec periods to usec */
  uldRes -= DELTA_EPOCH_IN_USEC;  /* from Win epoch to Unix epoch */
  return (uldRes);
}

int gettimeofday (struct timeval* tv, void* /*tz*/)
{
  FILETIME  ft;
  Uint64 uldTim;

  if (!tv)
  {
    errno = EINVAL;
    return (-1);
  }
  GetSystemTimeAsFileTime (&ft);
  uldTim = filetime_to_unix_epoch (&ft);
  tv->tv_sec  = (Int32) (uldTim / 1000000L);
  tv->tv_usec = (Int32) (uldTim % 1000000L);
  return (0);
}
#endif


/***************************************************************************/
/*! Returns a random number, witch is between from and to
    \param uldFrom : lower limit
    \param uldTo : upper limit
    \return random number
*/
/***************************************************************************/
/*static*/ Uint32 TTime::random(Uint32 uldFrom, Uint32 uldTo)
{
  #if (__BCPLUSPLUS__ >= 0x0570)
    Uint32 uldDiff = ::abs((int) (Float)(uldTo - uldFrom))+1;
  #else
    Uint32 uldDiff = abs((Int) (Float)(uldTo - uldFrom))+1;
  #endif

  #if defined(__GNUC__)
    Uint64 uldTimeStamp = ::rand();
  
  #elif defined(_MSC_VER)
    Float fValue = (::rand()/(Float)RAND_MAX);
    Uint64 uldTimeStamp = (Uint64) fValue * LONG_MAX;
  
  #else 
    Uint64 uldTimeStamp = ::_lrand();
  #endif
  
  Uint32 uldRes = (Uint32)(uldTimeStamp % uldDiff);
  return uldFrom + uldRes;
}


/***************************************************************************/
/*! Returns a random float number, witch is between from and to
    \param dFrom : lower limit
    \param dTo  :upper limit
    \return random number
*/
/***************************************************************************/
/*static*/ Float TTime::randomFloat(Float fFrom, Float fTo)
{
  Float fDiff = fabs(fTo - fFrom);
  Float fValue = random(0, RAND_MAX)/(Float)RAND_MAX;
  Float fRes = fDiff * fValue;
  return fFrom + fRes;
}

/***************************************************************************/
/*! Returns a random integer number, witch is between from and to
    \param iFrom : lower limit
    \param iTo  :upper limit
    \return random number
*/
/***************************************************************************/
/*static*/ Int TTime::randomInt(Int iFrom, Int iTo)
{
  #if (__BCPLUSPLUS__ >= 0x0570)
    Int iDiff = ::abs(static_cast<int>(iFrom - iTo));
  #else
    Int iDiff = abs(iFrom - iTo);
  #endif

  Int iRes = random(0, iDiff);
  return iFrom + iRes;
}

/***************************************************************************/
/*! Initializes the random function
*/
/***************************************************************************/
/*static*/ void TTime::initRandom()
{
  #if defined(__GNUC__)
    ::srandom(getTickCount() % RAND_MAX);
  #elif _MSC_VER
    ::srand(((Uint) getTickCount()) % RAND_MAX);
  #else  
    ::randomize();
  #endif
}

/***************************************************************************/
/*! Returns the time in micro seconds
*/
/***************************************************************************/
/*static*/ Uint64 TTime::getTickCount()
{
  timeval rTime;
  gettimeofday(&rTime, NULL);
  Uint64 uldSec = rTime.tv_sec *1000000 +  rTime.tv_usec;

  return uldSec;
}


/***************************************************************************/
/*! Returns the time in seconds
*/
/***************************************************************************/
/*static*/ Float64 TTime::getTimeStamp()
{
  timeval rTime;
  gettimeofday(&rTime, NULL);
  Uint64 uldSec = rTime.tv_sec *1000000+  rTime.tv_usec;
  #if defined(_MSC_VER)
    return ((Int64)uldSec)/(Float64)1000000.0;
  #else
    return uldSec/(Float64)1000000.0;
  #endif
}

/***************************************************************************/
/*! Dwells for a time in micro seconds
*/
/***************************************************************************/
/*static*/ void TTime::usleep(Uint64 uldDwell)
{
  #if defined(__GNUC__)
    ::usleep(uldDwell);
  #else
    ::SleepEx((Int32)(uldDwell/1000), true);
  #endif
}

/***************************************************************************/
/*! Dwells for a time in seconds
*/
/***************************************************************************/
/*static*/ void TTime::sleep(Float64 dDwell)
{
  #if defined(__GNUC__)
    ::usleep((unsigned int)(1000000*dDwell));
  #else
    unsigned int uiValue = (unsigned int) (1000.0*dDwell);
/*    if (uiValue <= 0)
    {
      uiValue = 1;
    }  */
    ::SleepEx(uiValue, true);
  #endif
}

