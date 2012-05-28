/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ByteArray
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 3.09.07 7:03 $
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
 $Log: /WinSteuerung2/dev/Zeus/src/zeusbase/System/ByteArray.hpp $
** 
** 6     3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
***************************************************************************/


#ifndef ByteArrayHPP
#define ByteArrayHPP

#include <zeusbase/System/Interfaces/IByteArray.hpp>
#include <zeusbase/System/ArrayList.hpp>

BEGIN_NAMESPACE_Zeus

/*****************************************************************************/
/*! This class extends the array list for byte arrays. The byte array is
    copied with the shallow mode
*/
/*****************************************************************************/
class TByteArray : public TArrayList<char>
{
  public:
    /*************************************************************************/
    /*! Constructor of byte array.
        \see TArrayList::TArrayList
    */
    /*************************************************************************/
    inline TByteArray(Int iSize = 20)
     : TArrayList<char>(iSize, etShallowCopy)
    {
    }

    /*************************************************************************/
    /*! Constructor of byte array.
        \see TArrayList::TArrayList
    */
    /*************************************************************************/
    inline TByteArray(const char* pArray, Int iSize, bool bAttachPointer = false)
     : TArrayList<char>(pArray, iSize, etShallowCopy, bAttachPointer)
    {
    }

    /*************************************************************************/
    /*! Constructor of byte array.
        \see TArrayList::TArrayList
    */
    /*************************************************************************/
    inline TByteArray(const char& rEmptyItem, Int iSize)
     : TArrayList<char>(rEmptyItem, iSize, etShallowCopy)
    {
    }

    /*************************************************************************/
    /*! Constructor of byte array.
        \param pList : Array to copy
    */
    /*************************************************************************/
    inline TByteArray(const IByteArray* pList)
     : TArrayList<char>(pList)
    {
    }

    /*************************************************************************/
    /*! Constructor of byte array.
        \param rList : Array to copy
    */
    /*************************************************************************/
    inline TByteArray(const IByteArray& rList)
     : TArrayList<char>(&rList)
    {
    }

    /*************************************************************************/
    /*! Constructor of byte array.
        \param rList : Array to copy
    */
    /*************************************************************************/
    inline TByteArray(const TByteArray& rList)
     : TArrayList<char>(rList)
    {
    }

    /*************************************************************************/
    /*! Destroys a byte array.
        \see TArrayList::~TArrayList
    */
    /*************************************************************************/
    inline virtual ~TByteArray()
    {
    }

    /*************************************************************************/
    /*! copy operator of byte array.
        \param rArray : Array to copy
    */
    /*************************************************************************/
    inline TByteArray& operator=(const IByteArray& rList)
    {
      rList.copyToList(*this);
      return *this;
    }

    /*************************************************************************/
    /*! copy operator of byte array.
        \param rArray : Array to copy
    */
    /*************************************************************************/
    inline TByteArray& operator=(const TByteArray& rList)
    {
      rList.copyToList(*this);
      return *this;
    }
};

END_NAMESPACE_Zeus
#endif
