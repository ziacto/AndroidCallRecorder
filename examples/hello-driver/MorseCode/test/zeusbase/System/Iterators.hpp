/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : Iterators
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Iterators.hpp $
** 
** 3     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 2     3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
** 
** 1     13.08.07 7:30 bha
** Created
***************************************************************************/

#ifndef IteratorsHPP
#define IteratorsHPP

#include <zeusbase/System/Interfaces/IListIterator.hpp>
#include <zeusbase/System/Interfaces/IMapIterator.hpp>
#include <zeusbase/System/AutoPtr.hpp>
#include <assert.h>

BEGIN_NAMESPACE_Zeus

/****************************************************************************/
/*! Abstract implementation of the list iterator wrapper
    all non const methods are defined protected. The inheriting classes
    such as TConstIterator and TIterator are implementing these methods
    as private or public.
*/
/****************************************************************************/
template <class T> class TAbstractIterator : public TAutoPtrBase<IListIterator<T> >, private IListIterator<T>
{
  public:

    /***********************************************************************/
    /*! \see IListIterator::reset
    */
    /***********************************************************************/
    virtual void MQUALIFIER reset() const
    {
      if (this->m_pInterface != NULL)
      {
        this->m_pInterface->reset();
      }
    }

    /***********************************************************************/
    /*! \see IListIterator::getNextItemConst
    */
    /***********************************************************************/
    virtual const T& MQUALIFIER getNextItemConst() const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItemConst();
    }

    /***********************************************************************/
    /*! \see IListIterator::hasNextItem
    */
    /***********************************************************************/
    virtual bool MQUALIFIER hasNextItem() const
    {
      bool bRetval = false;
      if (this->m_pInterface != NULL)
      {
        bRetval = this->m_pInterface->hasNextItem();
      }
      return bRetval;
    }
  
  protected:
    /***********************************************************************/
    /*! Standard constructor
    */
    /***********************************************************************/
    TAbstractIterator()
     : TAutoPtrBase<IListIterator<T> >()
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAbstractIterator(const IListIterator<T>* pIt, bool bAllocPointer = false)
     : TAutoPtrBase<IListIterator<T> >(pIt, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAbstractIterator(IListIterator<T>* pIt, bool bAllocPointer = false)
     : TAutoPtrBase<IListIterator<T> >(pIt, bAllocPointer)
    {}

    /***********************************************************************/
    /*! \see IListIterator::getNextItem
    */
    /***********************************************************************/
    virtual T& MQUALIFIER getNextItem() const = 0;

  private:
    /***********************************************************************/
    /*! \see IZUnknown::askForInterface
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER askForInterface(const InterfaceID& /*rInterfaceID*/, IZUnknown*& /*rpIface*/) 
    {
      return RET_METHOD_NOT_IMPL;
    }

    /***********************************************************************/
    /*! \see IZUnknown::addRef
    */
    /***********************************************************************/
    virtual void MQUALIFIER addRef() const {}

    /***********************************************************************/
    /*! \see TAutoPtrBase::release
    */
    /***********************************************************************/
    virtual void MQUALIFIER release() const
    {}

    ///Hidden copy constructor
    TAbstractIterator(const TAbstractIterator<T>& rIt);
    ///Hidden copy operator
    TAbstractIterator<T>& operator=(const TAbstractIterator<T>& rIt);
};

//############################################################################
//                                    LIST ITERATORS
/****************************************************************************/
/*! Implementation of the list iterator wrapper for non const iterations
*/
/****************************************************************************/
template <class T> class TIterator : public TAbstractIterator<T>
{
  public:
    /***********************************************************************/
    /*! Standard constructor
    */
    /***********************************************************************/
    TIterator()
     : TAbstractIterator<T>()
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TIterator(IListIterator<T>* pIt, bool bAllocPointer = false)
     : TAbstractIterator<T>(pIt, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Copy constructor
    */
    /***********************************************************************/
    TIterator(const TIterator<T>& rIt)
     : TAbstractIterator<T>(rIt.m_pInterface, true)
    {}

    /***********************************************************************/
    /*! Copy operator
    */
    /***********************************************************************/
    TIterator<T>& operator=(const TIterator<T>& rIt)
    {
      assign(rIt.m_pInterface);
      return *this;
    }

    /***********************************************************************/
    /*! Assign operator
        \param iface : Interface
    */
    /***********************************************************************/
    TIterator<T>& operator=(IListIterator<T>* pIt)
    {
      attach(pIt);
      return *this;
    }

    /***********************************************************************/
    /*! Equals operator 
        \param rWrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator==(const TIterator<T>& rWrapper) const
    {
      return equals(rWrapper.m_pInterface);
    }

    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator==(const IListIterator<T>* pIt) const
    {
      return equals(pIt);
    }
    
    /***********************************************************************/
    /*! Equals operator
        \param wrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator!=(const TIterator<T>& rWrapper) const
    {
      return !equals(rWrapper.m_pInterface);
    }
    
    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator!=(const IListIterator<T>* pIt) const
    {
      return !equals(pIt);
    }
    
    /***********************************************************************/
    /*! \see IListIterator::getNextItem
    */
    /***********************************************************************/
    virtual T& MQUALIFIER getNextItem() const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItem();
    }

  private:
};

/****************************************************************************/
/*! Implementation of the list iterator wrapper for const iterations
*/
/****************************************************************************/
template <class T> class TConstIterator : public TAbstractIterator<T>
{
  public:
    /***********************************************************************/
    /*! Standard constructor
    */
    /***********************************************************************/
    TConstIterator()
     : TAbstractIterator<T>()
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TConstIterator(const IListIterator<T>* pIt, bool bAllocPointer = false)
     : TAbstractIterator<T>(pIt, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Copy constructor
    */
    /***********************************************************************/
    TConstIterator(const TConstIterator<T>& rIt)
     : TAbstractIterator<T>(rIt.m_pInterface, true)
    {}

    /***********************************************************************/
    /*! Copy operator
    */
    /***********************************************************************/
    TConstIterator<T>& operator=(const TConstIterator<T>& rIt)
    {
      assign(rIt.m_pInterface);
      return *this;
    }

    /***********************************************************************/
    /*! Assign operator
        \param iface : Interface
    */
    /***********************************************************************/
    TConstIterator<T>& operator=(const IListIterator<T>* pIt)
    {
      attach(pIt);
      return *this;
    }

    /***********************************************************************/
    /*! Equals operator 
        \param rWrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator==(const TConstIterator<T>& rWrapper) const
    {
      return equals(rWrapper.m_pInterface);
    }

    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator==(const IListIterator<T>* pIt) const
    {
      return equals(pIt);
    }
    
    /***********************************************************************/
    /*! Equals operator
        \param wrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator!=(const TConstIterator<T>& rWrapper) const
    {
      return !equals(rWrapper.m_pInterface);
    }
  
    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator!=(const IListIterator<T>* pIt) const
    {
      return !equals(pIt);
    }
  
  private:
    /***********************************************************************/
    /*! \see IListIterator::getNextItem
    */
    /***********************************************************************/
    virtual T& MQUALIFIER getNextItem() const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItem();
    }
};

//############################################################################
//                                    MAP ITERATORS
/****************************************************************************/
/*! Abstract implementation of the map iterator wrapper.
*/
/****************************************************************************/
template <class TKeyType, class T> class TAbstractMapIterator
  : public TAutoPtrBase<IMapIterator<TKeyType, T> >,
    private IMapIterator<TKeyType, T>
{
  public:
    /***********************************************************************/
    /*! \see IListIterator::reset
    */
    /***********************************************************************/
    virtual void MQUALIFIER reset() const
    {
      if (this->m_pInterface != NULL)
      {
        this->m_pInterface->reset();
      }
    }

    /***********************************************************************/
    /*! \see IListIterator::getNextItemConst
    */
    /***********************************************************************/
    virtual const T& MQUALIFIER getNextItemConst() const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItemConst();
    }

    /***********************************************************************/
    /*! \see IListIterator::hasNextItem
    */
    /***********************************************************************/
    virtual bool MQUALIFIER hasNextItem() const
    {
      bool bRetval = false;
      if (this->m_pInterface != NULL)
      {
        bRetval = this->m_pInterface->hasNextItem();
      }
      return bRetval;
    }

    /*************************************************************************/
    /*! \see IMapIterator::getNextKeyConst
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER getNextKeyConst(TKeyType& rKey) const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextKeyConst(rKey);
    }

    /*************************************************************************/
    /*! \see IMapIterator::getNextItemWithKeyConst
    */
    /*************************************************************************/
    virtual const T& MQUALIFIER getNextItemWithKeyConst(TKeyType& rKey) const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItemWithKeyConst(rKey);
    }
  
  protected:
    /***********************************************************************/
    /*! Standard constructor
    */
    /***********************************************************************/
    TAbstractMapIterator()
     : TAutoPtrBase<IMapIterator<TKeyType, T> >()
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAbstractMapIterator(const IMapIterator<TKeyType, T>* pIt, bool bAllocPointer = false)
     : TAutoPtrBase<IMapIterator<TKeyType, T> >(pIt, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAbstractMapIterator(IMapIterator<TKeyType, T>* pIt, bool bAllocPointer = false)
     : TAutoPtrBase<IMapIterator<TKeyType, T> >(pIt, bAllocPointer)
    {}

    virtual T& MQUALIFIER getNextItem() const = 0;
    virtual Retval MQUALIFIER getNextKey(TKeyType& rKey) =0;
    virtual T& MQUALIFIER getNextItemWithKey(TKeyType& rKey) const = 0;
  
  
  private:
    /***********************************************************************/
    /*! \see IZUnknown::askForInterface
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER askForInterface(const InterfaceID& /*rInterfaceID*/, IZUnknown*& /*rpIface*/)
    {
      return RET_METHOD_NOT_IMPL;
    }

    /***********************************************************************/
    /*! \see IZUnknown::addRef
    */
    /***********************************************************************/
    virtual void MQUALIFIER addRef() const {}

    /***********************************************************************/
    /*! \see TAutoPtrBase::release
    */
    /***********************************************************************/
    virtual void MQUALIFIER release() const
    {}
    
    ///Hidden copy constructor
    TAbstractMapIterator(const TAbstractMapIterator<TKeyType, T>& rIt);
    ///Hidden copy operator
    TAbstractMapIterator<TKeyType, T>& operator=(const TAbstractMapIterator<TKeyType, T>& rIt);
};


/****************************************************************************/
/*! Implementation of the map iterator wrapper for non const iterations
*/
/****************************************************************************/
template <class TKeyType, class T> class TMapIterator : public TAbstractMapIterator<TKeyType, T>
{
  public:
    /***********************************************************************/
    /*! Standard constructor
    */
    /***********************************************************************/
    TMapIterator()
     : TAbstractMapIterator<TKeyType, T>()
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TMapIterator(IMapIterator<TKeyType, T>* pIt, bool bAllocPointer = false)
     : TAbstractMapIterator<TKeyType, T>(pIt, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Copy constructor
    */
    /***********************************************************************/
    TMapIterator(const TMapIterator<TKeyType, T>& rIt)
     : TAbstractMapIterator<TKeyType, T>(rIt.m_pInterface, true)
    {}

    /***********************************************************************/
    /*! Copy operator
    */
    /***********************************************************************/
    TMapIterator<TKeyType, T>& operator=(const TMapIterator<TKeyType, T>& rIt)
    {
      assign(rIt.m_pInterface);
      return *this;
    }

    /***********************************************************************/
    /*! Assign operator
        \param iface : Interface
    */
    /***********************************************************************/
    TMapIterator<TKeyType, T>& operator=(IMapIterator<TKeyType, T>* pIt)
    {
      attach(pIt);
      return *this;
    }

    /***********************************************************************/
    /*! Equals operator 
        \param rWrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator==(const TMapIterator<TKeyType, T>& rWrapper) const
    {
      return equals(rWrapper.m_pInterface);
    }

    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator==(const IMapIterator<TKeyType, T>* pIt) const
    {
      return equals(pIt);
    }
    
    /***********************************************************************/
    /*! Equals operator
        \param wrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator!=(const TMapIterator<TKeyType, T>& rWrapper) const
    {
      return !equals(rWrapper.m_pInterface);
    }
    
    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator!=(const IMapIterator<TKeyType, T>* pIt) const
    {
      return !equals(pIt);
    }
    
    /***********************************************************************/
    /*! \see IListIterator::getNextItem
    */
    /***********************************************************************/
    virtual T& MQUALIFIER getNextItem() const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItem();
    }

    /***********************************************************************/
    /*! \see IMapIterator::getNextKey
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getNextKey(TKeyType& rKey)
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextKey(rKey);
    }

    /***********************************************************************/
    /*! \see IMapIterator::getNextItemWithKey
    */
    /***********************************************************************/
    virtual T& MQUALIFIER getNextItemWithKey(TKeyType& rKey) const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItemWithKey(rKey);
    }

  private:
};


/****************************************************************************/
/*! Implementation of the map iterator wrapper for const iterations
*/
/****************************************************************************/
template <class TKeyType, class T> class TConstMapIterator : public TAbstractMapIterator<TKeyType, T>
{
  public:
    /***********************************************************************/
    /*! Standard constructor
    */
    /***********************************************************************/
    TConstMapIterator()
     : TAbstractMapIterator<TKeyType, T>()
    {}

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIt : Iterator Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TConstMapIterator(const IMapIterator<TKeyType, T>* pIt, bool bAllocPointer = false)
     : TAbstractMapIterator<TKeyType, T>(pIt, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Copy constructor
    */
    /***********************************************************************/
    TConstMapIterator(const TConstMapIterator<TKeyType, T>& rIt)
     : TAbstractMapIterator<TKeyType, T>(rIt.m_pInterface, true)
    {}

    /***********************************************************************/
    /*! Copy operator
    */
    /***********************************************************************/
    TConstMapIterator<TKeyType, T>& operator=(const TConstMapIterator<TKeyType, T>& rIt)
    {
      assign(rIt.m_pInterface);
      return *this;
    }

    /***********************************************************************/
    /*! Assign operator
        \param iface : Interface
    */
    /***********************************************************************/
    TConstMapIterator<TKeyType, T>& operator=(const IMapIterator<TKeyType, T>* pIt)
    {
      attach(pIt);
      return *this;
    }

    /***********************************************************************/
    /*! Equals operator 
        \param rWrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator==(const TConstMapIterator<TKeyType, T>& rWrapper) const
    {
      return equals(rWrapper.m_pInterface);
    }

    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator==(const IMapIterator<TKeyType, T>* pIt) const
    {
      return equals(pIt);
    }
    
    /***********************************************************************/
    /*! Equals operator
        \param wrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator!=(const TConstMapIterator<TKeyType, T>& rWrapper) const
    {
      return !equals(rWrapper.m_pInterface);
    }
  
    /***********************************************************************/
    /*! Equals operator 
        \param pIt : Interface
    */
    /***********************************************************************/
    bool operator!=(const IMapIterator<TKeyType, T>* pIt) const
    {
      return !equals(pIt);
    }
  
  private:
    /***********************************************************************/
    /*! \see IListIterator::getNextItem
    */
    /***********************************************************************/
    virtual T& MQUALIFIER getNextItem() const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItem();
    }

    /***********************************************************************/
    /*! \see IMapIterator::getNextKey
    */
    /***********************************************************************/
    virtual Retval MQUALIFIER getNextKey(TKeyType& rKey)
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextKey(rKey);
    }

    /***********************************************************************/
    /*! \see IMapIterator::getNextItemWithKey
    */
    /***********************************************************************/
    virtual T& MQUALIFIER getNextItemWithKey(TKeyType& rKey) const
    {
      assert(this->m_pInterface != NULL);
      return this->m_pInterface->getNextItemWithKey(rKey);
    }
};

END_NAMESPACE_Zeus

#endif


