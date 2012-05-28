/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : AutoPtr
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 11.08.08 11:26 $
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
 $Log: /Development_F/StuderWIN/usr/include/zeusbase/System/AutoPtr.hpp $
** 
** 7     11.08.08 11:26 Mab
** operator < implemented.
** 
** 6     4.04.08 19:04 Bha
** eliminated coding errors and warnings for VC2005 and C++Builder 2007
** 
** 5     14.01.08 14:31 Bha
** New methods to handle references added
** 
** 4     30.10.07 16:43 bha
** New method added to avoid icast macros
** 
** 3     4.10.07 7:10 bha
** const method implemented
** 
** 2     3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
** 
** 1     13.08.07 7:30 bha
** Created
***************************************************************************/

#ifndef AutoPtrHPP
#define AutoPtrHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>

BEGIN_NAMESPACE_Zeus


/**************************************************************************/
/*! This is the base class of all smart interface pointers
*/
/**************************************************************************/
template <class T> class TAutoPtrBase
{
  public:  
    /***********************************************************************/
    /*! Creates an Interface Smart pointer
    */
    /***********************************************************************/
    TAutoPtrBase()
    {
      m_pInterface = NULL;
    }

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param pIface : Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAutoPtrBase(const T* pIface, bool bAllocPointer = false)
    {
      m_pInterface = const_cast<T*>(pIface);

      if (bAllocPointer && m_pInterface != NULL)
      {
        m_pInterface->addRef();
      }
    }

    /***********************************************************************/
    /*! Creates an Interface Smart pointer
        \param rIface : Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAutoPtrBase(const T& rIface, bool bAllocPointer = false)
    {
      m_pInterface = const_cast<T*>(&rIface);
      if (bAllocPointer && m_pInterface != NULL)
      {
        m_pInterface->addRef();
      }
    }
  
    /***********************************************************************/
    /*! Destroys the smart pointer
    */
    /***********************************************************************/
    virtual ~TAutoPtrBase()
    {
      release();
    }
  
    /***********************************************************************/
    /*! assigns a new interface pointer to the auto pointer. This method
        will allocate a new pointer reference (using addRef())
        \param pInterface : Interface pointer to assign
    */
    /***********************************************************************/
    void assign(const T* pInterface)
    {
      release();
      m_pInterface = const_cast<T*>(pInterface);
      if (m_pInterface != NULL)
      {
        m_pInterface->addRef();
      }
    }

    /***********************************************************************/
    /*! assigns a new interface reference to the auto pointer. This method
        will allocate a new pointer reference (using addRef())
        \param rInterface : Interface reference to assign
    */
    /***********************************************************************/
    void assign(const T& rInterface)
    {
      release();
      m_pInterface = const_cast<T*>(&rInterface);
      if (m_pInterface != NULL)
      {
        m_pInterface->addRef();
      }
    }

    /***********************************************************************/
    /*! adopts a new interface pointer to the auto pointer. This method
        will not allocate a new pointer reference (no addRef())
        \param pInterface : pointer to attach
    */
    /***********************************************************************/
    void attach(const T* pInterface)
    {
      release();
      m_pInterface = const_cast<T*>(pInterface);
    }

    /***********************************************************************/
    /*! adopts a new interface reference to the auto pointer. This method
        will not allocate a new pointer reference (no addRef())
        \param rInterface : reference to attach
    */
    /***********************************************************************/
    void attach(const T& rInterface)
    {
      release();
      m_pInterface = const_cast<T*>(&rInterface);
    }

    /***********************************************************************/
    /*! Checks if two pointers are equal
        \param pInterface : pointer to check
    */
    /***********************************************************************/
    bool equals(const T* pInterface) const
    {
      return (m_pInterface == pInterface);
    }

    /***********************************************************************/
    /*! Checks if two pointers are equal
        \param rInterface : reference to check
    */
    /***********************************************************************/
    bool equals(const T& rInterface) const
    {
      return (m_pInterface == &rInterface);
    }

    /***********************************************************************/
    /*! returns the Reference of the pointer
    */
    /***********************************************************************/
    T*& getPointerReference()
    {
      return m_pInterface;
    }

    /***********************************************************************/
    /*! returns the Reference of the pointer
    */
    /***********************************************************************/
    const T*& getConstPointerReference() const
    {
#if defined(_MSC_VER)
      return (const T*&)(m_pInterface);
#else
      return m_pInterface;
#endif
    }

    /***********************************************************************/
    /*! returns the Reference of the interface pointer
    */
    /***********************************************************************/
    IZUnknown*& getInterfaceReference()
    {
      return (IZUnknown*&)(m_pInterface);
    }

    /***********************************************************************/
    /*! returns the Reference of the interface pointer
    */
    /***********************************************************************/
    const IZUnknown*& getInterfaceReferenceConst() const
    {
      return (const IZUnknown*&)(m_pInterface);
    }

    /***********************************************************************/
    /*! returns the the pointer
    */
    /***********************************************************************/
    T* getPointer()
    {
      return m_pInterface;
    }

    /***********************************************************************/
    /*! returns the the const_pointer
    */
    /***********************************************************************/
    const T* getConstPointer() const
    {
      return m_pInterface;
    }

    /***********************************************************************/
    /*! Removes the pointer from the wrapper without releasing it. After
        this call the internal member is set to NULL.
    */
    /***********************************************************************/
    T* detach()
    {
      T* pRetval = this->m_pInterface;
      this->m_pInterface = NULL;
      return pRetval;
    }

    /***********************************************************************/
    /*! Removes the pointer from the wrapper
    */
    /***********************************************************************/
    void release()
    {
      if (this->m_pInterface != NULL)
      {
        this->m_pInterface->release();
        this->m_pInterface = NULL;
      }
    }
  
  protected:
    //Interface pointer
    T* m_pInterface;

  private:
    /// Assign operator is hidden and not implemented
    TAutoPtrBase<T>& operator=(const TAutoPtrBase<T>& rWrapper);
    ///Copy constructor is hidden and not implemented
    TAutoPtrBase(const TAutoPtrBase& rWrapper);
};


/**************************************************************************/
/*! The auto pointer class helps to manage objects from heap classes.
    Normally its used if a heap class is created locally. If there are
    exceptions we will get memory leaks. Therfore we use the auto pointer
    to manage the objects inside a scope. Leaving the scope will also release
    the memory allocated with new.
*/
/**************************************************************************/
template <class T> class TAutoPtr : public TAutoPtrBase<T>
{
  public:
    
    /***********************************************************************/
    /*! Creates an auto pointer
    */
    /***********************************************************************/
    TAutoPtr() : TAutoPtrBase<T>()
    {}
    
    /***********************************************************************/
    /*! Creates an auto pointer
        \param pIface : Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAutoPtr(const T* pIface, bool bAllocPointer = false)
     : TAutoPtrBase<T>(pIface, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Creates an auto pointer
        \param rIface : Interface
        \param bAllocPointer : If this flag is true the pointer will be
                               allocated with addRef()
    */
    /***********************************************************************/
    TAutoPtr(const T& rIface, bool bAllocPointer = false)
     : TAutoPtrBase<T>(rIface, bAllocPointer)
    {}

    /***********************************************************************/
    /*! Copy constructor of auto pointer 
        \param wrapper : auto pointer to copy
    */
    /***********************************************************************/
    TAutoPtr(const TAutoPtr<T>& rWrapper)
     : TAutoPtrBase<T>(rWrapper.m_pInterface, true)
    {}
   
    /***********************************************************************/
    /*! Destroys the auto pointer
    */
    /***********************************************************************/
    virtual ~TAutoPtr()
    {}

    
    /***********************************************************************/
    /*! Assign operator 
        \param pIface : Interface
    */
    /***********************************************************************/
    TAutoPtr<T>& operator=(const T* pIface)
    {
      attach(pIface);
      return *this;
    }

    /***********************************************************************/
    /*! Assign operator
        \param iface : Interface
    */
    /***********************************************************************/
    TAutoPtr<T>& operator=(const T& rIface)
    {
      attach(&rIface);
      return *this;
    }

    /***********************************************************************/
    /*! Assign operator
        \param rWrapper : Interfacewrapper
    */
    /***********************************************************************/
    TAutoPtr<T>& operator=(const TAutoPtr<T>& rWrapper)
    {
      assign(rWrapper.m_pInterface);
      return *this;
    }
   
    /***********************************************************************/
    /*! Equals operator 
        \param rWrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator==(const TAutoPtr<T>& rWrapper) const
    {
      return equals(rWrapper.m_pInterface);
    }

    /***********************************************************************/
    /*! Equals operator
        \param wrapper : Interface wrapper
    */
    /***********************************************************************/
    bool operator!=(const TAutoPtr<T>& rWrapper) const
    {
      return !equals(rWrapper.m_pInterface);
    }
    
    /***********************************************************************/
    /*! Equals operator
        \param pIface : Interface
    */
    /***********************************************************************/
    bool operator==(const T* pIface) const
    {
      return equals(pIface);
    }

    /***********************************************************************/
    /*! Equals operator
        \param rIface : Interface
    */
    /***********************************************************************/
    bool operator==(const T& rIface) const
    {
      return equals(&rIface);
    }

    /***********************************************************************/
    /*! Equals operator
        \param pIface : Interface
    */
    /***********************************************************************/
    bool operator!=(const T* pIface) const
    {
      return !equals(pIface);
    }

    /***********************************************************************/
    /*! Equals operator
        \param rIface : Interface
    */
    /***********************************************************************/
    bool operator!=(const T& rIface) const
    {
      return !equals(&rIface);
    }

    /***********************************************************************/
    /*! Less than operator.

        Needed to resolve ambiguities in STL when using TAutoPtr as key of
        a set or map (ambiguity between operator T*() and operator T*&().).
        
        \param ptr [IN]: Auto pointer to be compared to this.              */
    /***********************************************************************/
    bool operator<(const TAutoPtr<T>& ptr) const
    {
      return this->m_pInterface < ptr.m_pInterface;
    }

    /***********************************************************************/
    /*! Operator is used to return the interface pointer and to access to
        all methods of this interface
        \return pointer to interface
    */
    /***********************************************************************/
    T* operator->() {return this->m_pInterface; }
    
    /***********************************************************************/
    /*! Operator is used to return the interface pointer and to access to
        all methods of this interface
        \return pointer to interface
    */
    /***********************************************************************/
    const T* operator->() const {return this->m_pInterface; }
    
    /***********************************************************************/
    /*! Returns the dereferenced pointer of an interface
        \return pointer to interface
    */
    /***********************************************************************/
    T& operator*() const {return *this->m_pInterface; }
    
    
    /***********************************************************************/
    /*! Implicit cast to T*
    */
    /***********************************************************************/
    operator T*() const {return (T*)this->m_pInterface; }

    /***********************************************************************/
    /*! Implicit cast to T*&
    */
    /***********************************************************************/
    operator T*&() {return (T*&)this->m_pInterface; }

};

END_NAMESPACE_Zeus

#endif

