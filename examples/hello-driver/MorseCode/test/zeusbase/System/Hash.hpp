/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : Hash
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 24.01.08 13:51 $
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

 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Hash.hpp $
** 
** 2     24.01.08 13:51 Bha
** Max int constants renamed
** 
** 1     15.10.07 13:57 bha
** created
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef HashHPP
#define HashHPP

#include <zeusbase/System/Interfaces/IValueType.hpp>
#include <zeusbase/System/Int.h>

BEGIN_NAMESPACE_Zeus

/***************************************************************************/
/*! This class implements some basic functions for hashing data
*/
/***************************************************************************/
template <class T> class THash
{
  public:
    /***********************************************************************/
    /*! gets the hash of a char* buffer array of size iSize and returns the
        hash as a 64bit value
        \param pcBuffer : Buffer to hash
        \param iSize : Size of the buffer
        \param ldMax : max size of the hash table
    */
    /***********************************************************************/
    static Int64 getHash64(const T* pBuffer, Int iSize, Int64 ldMax = TInt::MaxInt64)
    {
      Int64 ldH = 0;
      Int64 ldA = 31415;
      Int64 ldB = 27183;
      Int i = 0;
      for(i = 0, ldH = 0; i < iSize; i++, pBuffer++, ldA = (ldA * ldB) % (ldMax - 1))
      {
        ldH = (ldA* ldH + *pBuffer) % ldMax;
      }
      return (ldH < 0) ? ( ldH + ldMax ) : ldH;
    }

    /***********************************************************************/
    /*! gets the hash of a char* buffer array of size iSize and returns the
        hash as a 32bit value
        \param pcBuffer : Buffer to hash
        \param iSize : Size of the buffer
        \param ldMax : max size of the hash table
    */
    /***********************************************************************/
    static Int32 getHash32(const T* pBuffer, Int iSize, Int32 lMax = TInt::MaxInt32)
    {
      Int32 lH = 0;
      Int32 lA = 31415;
      Int32 lB = 27183;
      Int i = 0;
      for(i = 0, lH = 0; i < iSize; i++, pBuffer++, lA = (lA * lB) % (lMax - 1))
      {
        lH = (lA* lH + *pBuffer) % lMax;
      }
      return (lH < 0) ? ( lH + lMax ) : lH;
    }

  private:
    THash(){}
    virtual ~THash(){}

};

END_NAMESPACE_Zeus

//---------------------------------------------------------------------------
#endif
