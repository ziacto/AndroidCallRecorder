/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IArray
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 11.09.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IArray.hpp $
** 
** 11    7.01.08 9:33 Bha
** New Zeus-Framework version 0.6 created
** 
** 10    12.09.07 17:09 bha
** Noted special case of coping arrays for interface types
** 
** 9     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/


#ifndef IArrayHPP
#define IArrayHPP

#include <zeusbase/System/Interfaces/IList.hpp>

BEGIN_NAMESPACE_Zeus

/***********************************************************************/
/*! Copy mode of an array
*/
/***********************************************************************/
enum EArrayCopyMode
{
  etShallowCopy = 0,
  etDeepCopy = 1
};


/***************************************************************************/
/*! This interface defines an array, witch also inherites the behavoir of
    a list.
*/
/***************************************************************************/
template <class T> class IArray : public IList<T>
{
  HIDE_ASSIGNMENT_OPERATOR(IArray<T>)
  
  public:

    /***********************************************************************/
    /*! Returns the array of the data
        \return array
    */
    /***********************************************************************/
    virtual T* MQUALIFIER getArray() const = 0;

    /***********************************************************************/
    /*! Returns the const array of the data
        \return array
    */
    /***********************************************************************/
    virtual const T* MQUALIFIER getArrayConst() const = 0;

    /***********************************************************************/
    /*! Returns the size of the valid array data
        \return size
    */
    /***********************************************************************/
    virtual Int MQUALIFIER getArraySize() const = 0;
    
    /***********************************************************************/
    /*! Sets a new array of data. The array will be copied into the 
        member of the arraylist. Adopting the pointer can only be used
        for shallow copy arrays, because objects might live on a
        different heap (local heap)
        \param pArray : pointer to the array of data
        \param iSize : Size of the array
        \param bAttachPointer : if this flag is set the array pointer will be
                                attached
        \retval RET_NOERROR : Array copied
        \retval RET_REQUEST_FAILED : Could not copy this array
        \retval RET_INVALID_PARAMETER : Invalid parameter received (=NULL)
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER setArray(const T* pArray, Int iSize, bool bAttachPointer = false)=0;
    
    /***********************************************************************/
    /*! This appends an array to the current array.
        \param pArray : Array of Data
        \param iSize : Size of the array
        \retval RET_NOERROR : Data appended
        \retval RET_REQUEST_FAILED: Could not append data.
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER appendArray(const T* pArray, Int iSize)=0;
    
    /***********************************************************************/
    /*! Copies a subsequence of this array into the destination
        \param rDest : Destination array
        \param iStart : Start index of the first element
        \param iEnd : End index of the last element
        \retval RET_NOERROR : Array copied
        \retval RET_REQUEST_FAILED : Could not copy array
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER copyToArray(IArray<T>& rDest, Int iStart, Int iEnd) const =0;

    /***********************************************************************/
    /*! returns the copy mode of an array
    */
    /***********************************************************************/
    virtual EArrayCopyMode MQUALIFIER getCopyMode() const = 0;
};

END_NAMESPACE_Zeus

#endif
