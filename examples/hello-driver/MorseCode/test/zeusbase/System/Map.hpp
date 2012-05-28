/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : StringMap
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Map.hpp $
** 
** 18    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 17    4.02.08 7:37 Bha
** - changed to inline methods
** - stl bindings for map
** 
** 16    7.01.08 9:01 Bha
** copy method implemented
** 
** 15    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 14    3.09.07 14:02 Mabbuehl
** VS6 warnings removed.
** 
** 13    3.09.07 7:03 bha
** New Framework using auto pointer and improved lists
** 
** 12    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
** 
** 6     14.09.06 6:53 bha
** Anpassen von addRef und release auf const
** 
** 5     7.09.06 14:44 bha
** Erweitern des Strings
***************************************************************************/

#ifndef __MapHPP__1246139532
#define __MapHPP__1246139532

#include <zeusbase/System/Interfaces/IMap.hpp>
#include <zeusbase/System/Iterators.hpp>
#include <zeusbase/System/ZObject.h>
#include <string.h>

#ifdef _MSC_VER
  #pragma warning(push, 1) // Avoid Visual Studio 6.0 level 4 and 3 compiler warnings.
#endif

#include <map>
#include <string>

#ifdef _MSC_VER
  #pragma warning(pop)
#endif


BEGIN_NAMESPACE_Zeus

using namespace std;

/******************************************************************************/
/*! This class implements a map (using std::map) for different types for
    keys and values
*/
/******************************************************************************/
template <class TKeyType, class T> class TMap : public IMap<TKeyType,T>
{
  public:
    /************************************************************************/
    /*! Creates a empty map
    */
    /************************************************************************/
    inline TMap()
     /* COMPILER PROBLEM*/
     /*#ifdef A_COMPILER_TYPE
        : m_tEmpty(getDefaultEmpty())
       #else
        : m_tEmpty(T())
       #endif
     */
     : m_tEmpty(T())
    {
      m_pIterator = NULL;

      // DO NOT USE MEMSET. This causes memory leaks on complex objects
      //memset(&m_tEmpty, 0, sizeof(T));
    }
    
    /************************************************************************/
    /*! Creates a empty map, defining an empty item
        \param rEmptyItem : Empty item
    */
    /************************************************************************/
    inline TMap(const T& rEmptyItem)
     : m_tEmpty(rEmptyItem)
    {
      m_pIterator = NULL;
    }
    
  #ifdef USE_STL_BINDINGS
    /*********************************************************************/
    /*! Creates a map out of a stl::map
        \param rMap : Map to copy
    */
    /*********************************************************************/
    inline TMap(const std::map<TKeyType, T>& rMap)
     : m_Map(rMap),
       m_tEmpty(T())
    {
      m_pIterator = NULL;
    }
  #endif

    /*********************************************************************/
    /*! Copy constructor
        \param rMap : Map to copy
    */
    /*********************************************************************/
    inline TMap(const TMap<TKeyType, T>& rMap)
     : m_Map(rMap.m_Map),
       m_tEmpty(rMap.m_tEmpty)
    {
      m_pIterator = NULL;
    }

    /************************************************************************/
    /*! Destroys the map
    */
    /************************************************************************/
    virtual ~TMap()
    {
      clear();
      
      //resets all iterators
      TInternalAbstractMapIterator* pIt = m_pIterator;
      while (pIt != NULL)
      {
        pIt->clearParent();
        pIt = pIt->getNextIterator();
      }
    }

    /************************************************************************/
    /*! \see IMap::copyToMap
    */
    /************************************************************************/
    virtual void MQUALIFIER copyToMap(IMap<TKeyType, T>& rMap) const
    {
      TConstMapIterator<TKeyType, T> It = this->getConstIterator();
      while(It.hasNextItem())
      {
        TKeyType Key;
        const T& rItem = It.getNextItemWithKeyConst(Key);
        rMap.setItem(Key, rItem);
      }
    }

    /************************************************************************/
    /*! \see IMap::getItem
    */
    /************************************************************************/
    virtual T& MQUALIFIER getItem(const TKeyType& rKey)
    {
      typename std::map<TKeyType, T>::iterator it = m_Map.find(rKey);
      if (it != m_Map.end())
      {
        return (*it).second;
      }
      return m_tEmpty;
    }
    
    /************************************************************************/
    /*! \see IMap::getItemConst
    */
    /************************************************************************/
    virtual const T& MQUALIFIER getItemConst(const TKeyType& rKey) const
    {
      typename std::map<TKeyType, T>::const_iterator it = m_Map.find(rKey);
      if (it != m_Map.end())
      {
        return (*it).second;
      }
      return m_tEmpty;
    }
    
    /************************************************************************/
    /*! \see IMap::setItem
    */
    /************************************************************************/
    inline virtual void MQUALIFIER setItem(const TKeyType& rKey, const T& rData)
    {
      m_Map[rKey] = rData;
    }
    
    /************************************************************************/
    /*! \see IMap::isEmpty
    */
    /************************************************************************/
    inline virtual bool MQUALIFIER isEmpty() const
    {
      return m_Map.empty();
    }
    
    /************************************************************************/
    /*! \see IMap::getCount
    */
    /************************************************************************/
    inline virtual Int MQUALIFIER getCount() const
    {
      return m_Map.size();
    }

    /************************************************************************/
    /*! \see IMap::deleteItem
    */
    /************************************************************************/
    inline virtual bool MQUALIFIER deleteItem(const TKeyType& rKey)
    {
      return (m_Map.erase(rKey) == 1);
    }

    /************************************************************************/
    /*! \see IMap::hasItem
    */
    /************************************************************************/
    virtual bool MQUALIFIER hasItem(const TKeyType& rKey) const
    {
      bool bRetval = false;
      typename std::map<TKeyType, T>::const_iterator it;
      it = m_Map.find(rKey);
      if (it != m_Map.end())
      {
        bRetval = true;
      }
      return bRetval;
    }
        
    /************************************************************************/
    /*! \see IMap::clear
    */
    /************************************************************************/
    inline virtual void MQUALIFIER clear()
    {
      m_Map.clear();
    }
    
    /************************************************************************/
    /*! \see IMap::getIterator
    */
    /************************************************************************/
    inline virtual IMapIterator<TKeyType, T>* MQUALIFIER getIterator()
    {
      TInternalMapIterator* pIterator = new TInternalMapIterator(*this, m_Map, m_tEmpty);
      pIterator->setNextIterator(m_pIterator);
      m_pIterator = pIterator;
      return m_pIterator;
    }
    
    /************************************************************************/
    /*! \see IMap::getConstIterator
    */
    /************************************************************************/
    inline virtual const IMapIterator<TKeyType, T>* MQUALIFIER getConstIterator() const
    {
      TInternalConstMapIterator* pIterator = new TInternalConstMapIterator(*this, m_Map, m_tEmpty);
      pIterator->setNextIterator(m_pIterator);
      m_pIterator = pIterator;
      return m_pIterator;
    }


    /************************************************************************/
    /*! \see IMap::releaseIterator
    */
    /************************************************************************/
    virtual void MQUALIFIER releaseIterator(const IListIterator<T>* pIterator) const
    {
      TInternalAbstractMapIterator* pIt = m_pIterator;
      TInternalAbstractMapIterator* pItPrev = NULL;
      while (pIt != NULL)
      {
        if (pIt == pIterator)
        {
          //Erster Iterator loeschen
          if (pItPrev == NULL)
          {
            m_pIterator = pIt->getNextIterator();
            delete pIt;
          }
          else
          {
            pItPrev->setNextIterator(pIt->getNextIterator());
            delete pIt;
          }
          break;
        }
        pItPrev = pIt;
        pIt = pIt->getNextIterator();
      }
    }

    /************************************************************************/
    /*! \see IMap::equals
    */
    /************************************************************************/
    virtual bool MQUALIFIER equals(const IMap<TKeyType, T>& rMap) const
    {
      bool bRetval = (this->getCount() == rMap.getCount());

      const IMapIterator<TKeyType, T>* pIt1 = getConstIterator();
      const IMapIterator<TKeyType, T>* pIt2 = rMap.getConstIterator();

      while(bRetval && pIt1->hasNextItem() && pIt2->hasNextItem())
      {
        TKeyType Key1;
        TKeyType Key2;
        bRetval = (pIt1->getNextItemWithKeyConst(Key1) == pIt2->getNextItemWithKeyConst(Key2));

        bRetval &= (Key1 == Key2);
      }
      pIt1->release();
      pIt2->release();
      return bRetval;
    }

    /************************************************************************/
    /*! \see IMap::equals
    */
    /************************************************************************/
    inline virtual bool equals(const TMap<TKeyType, T>& rMap) const
    {
      return (this->getCount() == rMap.getCount() &&
              m_Map == rMap.m_Map);
    }

    /*********************************************************************/
    /*! Assigns the data of a map to this object
        \param rInPar : map to assign
        \return this;
    */
    /*********************************************************************/
    inline TMap<TKeyType, T>& operator= (const TMap<TKeyType, T>& rInPar)
    {
      m_Map = rInPar.m_Map;
      m_tEmpty = rInPar.m_tEmpty;
      return *this;
    }

  #ifdef USE_STL_BINDINGS
    /*********************************************************************/
    /*! Assigns the data of a map to this object
        \param rInPar : map to assign
        \return this;
    */
    /*********************************************************************/
    inline TMap<TKeyType, T>& operator= (const std::map<TKeyType, T>& rInPar)
    {
      m_Map = m_Map;
      return *this;
    }
  #endif

    /*********************************************************************/
    /*! checks if two maps are equal
        \param rMap : Map to check
        \retval true : Map are equal
        \retval false: Map are not equal
    */
    /*********************************************************************/
    inline bool operator== (const TMap<TKeyType, T>& rMap) const
    {
      return equals(rMap);
    }

    /*********************************************************************/
    /*! checks if two maps are equal
        \param rMap : Map to check
        \retval true : Map are equal
        \retval false: Map are not equal
    */
    /*********************************************************************/
    inline bool operator== (const IMap<TKeyType, T>& rMap) const
    {
      return equals(rMap);
    }

    /*********************************************************************/
    /*! not equals operator
    */
    /*********************************************************************/
    inline bool operator!= (const TMap<TKeyType, T>& rMap) const
    {
      return !equals(rMap);
    }

    /*********************************************************************/
    /*! not equals operator
    */
    /*********************************************************************/
    inline bool operator!= (const IMap<TKeyType, T>& rMap) const
    {
      return !equals(rMap);
    }

  protected:

  private:
    ///Empty item
    T m_tEmpty;
    ///Binary search 
    std::map<TKeyType, T> m_Map;
    
    /*********************************************************************/
    /* COMPILER PROBLEM:
       Change this if a compiler fails with : m_tEmpty(T()) (see constructors)

    #ifdef A_COMPILER_TYPE
    static const T& getDefaultEmpty()
    {
        static const T Empty; // is initialized by compiler
        return Empty;
    }
    #endif

    */

    /*********************************************************************/
    /*! abstract iterator of the map
    */
    /*********************************************************************/
    class TInternalAbstractMapIterator : public IMapIterator<TKeyType, T>
    {
      public:
        /*****************************************************************/
        /*! Creates the iterator
        */
        /*****************************************************************/
        inline TInternalAbstractMapIterator(const TMap<TKeyType, T>& rParent)
        {
          m_iRefCounter = 1;
          m_pNextIterator = NULL;
          m_pParent = (TMap<TKeyType, T>*) &rParent;
        }

        /*****************************************************************/
        /*! Destroys the iterator
        */
        /*****************************************************************/
        inline virtual ~TInternalAbstractMapIterator()
        {}

        /*****************************************************************/
        /*! gets the next iterator
        */
        /*****************************************************************/
        inline TInternalAbstractMapIterator* getNextIterator()
        { return m_pNextIterator; }

        /*****************************************************************/
        /*! sets the next iterator
        */
        /*****************************************************************/
        inline void setNextIterator(TInternalAbstractMapIterator* pIt)
        { m_pNextIterator = pIt; }


        /*****************************************************************/
        /*! \see IZUnknown::askForInterface
        */
        /*****************************************************************/
        inline Retval MQUALIFIER askForInterface(const InterfaceID& /*rInterfaceID*/, IZUnknown*& /*rpIface*/)
        {
          return RET_UNKNOWN_INTERFACE;
        }

        /***************************************************************************/
        /*! \see IZUnknown::addRef
        */
        /***************************************************************************/
        inline void MQUALIFIER addRef() const
        {
          ++m_iRefCounter;
        }

        /***************************************************************************/
        /*! \see IZUnknown::release
        */
        /***************************************************************************/
        void MQUALIFIER release() const
        {
          --m_iRefCounter;
          if (m_iRefCounter <= 0)
          {
            if (m_pParent != NULL)
            {
              m_pParent->releaseIterator(this);
            }
            else
            {
              delete this;
            }
          }
        }

        /*****************************************************************/
        /*! Sets the parent to NULL
        */
        /*****************************************************************/
        inline void clearParent()
        {
          m_pParent = NULL;
        }
      
      protected:
        ///Next iterator
        mutable TInternalAbstractMapIterator* m_pNextIterator;
        ///Parent instance
        mutable TMap<TKeyType, T>* m_pParent;

      private:
        ///Reference counter
        mutable Int m_iRefCounter;
        
    };

    /*********************************************************************/
    /*! Iterator of the map
    */
    /*********************************************************************/
    class TInternalMapIterator : public TInternalAbstractMapIterator
    {
      public:
        /*****************************************************************/
        /*! Creates the iterator
        */
        /*****************************************************************/
        inline TInternalMapIterator(const TMap<TKeyType, T>& rParent,
                     std::map<TKeyType, T>& tMap, 
                     T& tEmptyItem)
         : TInternalAbstractMapIterator(rParent),
           m_Map(tMap),
           m_tEmpty(tEmptyItem),
           m_Iterator(tMap.begin())
        {
        }
        
        /*****************************************************************/
        /*! Destroys the iterator
        */
        /*****************************************************************/
        inline virtual ~TInternalMapIterator()
        {}

        /*****************************************************************/
        /*! \see IMapIterator::getNextKey
        */
        /*****************************************************************/
        virtual Retval MQUALIFIER getNextKey(TKeyType& rKey)
        {
          return getNextKeyConst(rKey);
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextKeyConst
        */
        /*****************************************************************/
        inline virtual Retval MQUALIFIER getNextKeyConst(TKeyType& rKey) const
        {
          Retval retValue = RET_REQUEST_FAILED;
          if (this->hasNextItem())
          {
            retValue = RET_NOERROR;
            rKey = (*m_Iterator).first;
            m_Iterator++;
          }
          return retValue;
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextItemWithKey
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItemWithKey(TKeyType& rKey) const
        {
          if (this->hasNextItem())
          {
            rKey = (*m_Iterator).first;
            T& rRetval = (*m_Iterator).second;
            m_Iterator++;

            return rRetval;
          }
          else
          {
            return const_cast<T&>(m_tEmpty);
          }
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextItemWithKeyConst
        */
        /*****************************************************************/
        inline virtual const T& MQUALIFIER getNextItemWithKeyConst(TKeyType& rKey) const
        {
          return const_cast<const T&>(getNextItemWithKey(rKey));
        }

        /*****************************************************************/
        /*! \see IListIterator::reset
        */
        /*****************************************************************/
        inline virtual void MQUALIFIER reset() const
        {
          m_Iterator = m_Map.begin();
        }

        /*****************************************************************/
        /*! \see IListIterator::getNextItem
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItem() const
        {
          if (this->hasNextItem())
          {
            T& tRetval = (*m_Iterator).second;
            m_Iterator++;
            return tRetval;
          }
          else
          {
            return const_cast<T&>(m_tEmpty);
          }
        }

        /*****************************************************************/
        /*! \see IListIterator::getNextItemConst
        */
        /*****************************************************************/
        inline virtual const T& MQUALIFIER getNextItemConst() const
        {
          return const_cast<const T&>(this->getNextItem());
        }

        /*****************************************************************/
        /*! \see IListIterator::hasNextItem
        */
        /*****************************************************************/
        inline virtual bool MQUALIFIER hasNextItem() const
        {
          return (m_Map.end() != m_Iterator);
        }

      private:
        ///Binary search
        std::map<TKeyType, T>& m_Map;
        ///Empty item
        T m_tEmpty;
        ///Iterator of the map
        mutable typename std::map<TKeyType, T>::iterator m_Iterator;
    };

    /*********************************************************************/
    /*! Iterator of the map
    */
    /*********************************************************************/
    class TInternalConstMapIterator : public TInternalAbstractMapIterator
    {
      public:
        /*****************************************************************/
        /*! Creates the iterator
        */
        /*****************************************************************/
        inline TInternalConstMapIterator(const TMap<TKeyType, T>& rParent,
                          const std::map<TKeyType, T>& tMap, 
                          const T& tEmptyItem)
         : TInternalAbstractMapIterator(rParent),
           m_Map(tMap),
           m_tEmpty(tEmptyItem),
           m_tRetval(tEmptyItem),
           m_Iterator(tMap.begin())
        {
        }

        /*****************************************************************/
        /*! Destroys the iterator
        */
        /*****************************************************************/
        inline virtual ~TInternalConstMapIterator()
        {}

        /*****************************************************************/
        /*! \see IMapIterator::getNextKey
        */
        /*****************************************************************/
        inline virtual Retval MQUALIFIER getNextKey(TKeyType& rKey)
        {
          return getNextKeyConst(rKey);
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextKeyConst
        */
        /*****************************************************************/
        virtual Retval MQUALIFIER getNextKeyConst(TKeyType& rKey) const
        {
          Retval retValue = RET_REQUEST_FAILED;
          if (this->hasNextItem())
          {
            retValue = RET_NOERROR;
            rKey = (*m_Iterator).first;
            m_Iterator++;
          }
          return retValue;
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextItemWithKey
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItemWithKey(TKeyType& rKey) const
        {
          if (this->hasNextItem())
          {
            rKey = (*m_Iterator).first;
            m_tRetval = const_cast<T&>((*m_Iterator).second);
            m_Iterator++;
          }
          else
          {
            m_tRetval = m_tEmpty;
          }
          return m_tRetval;
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextItemWithKeyConst
        */
        /*****************************************************************/
        virtual const T& MQUALIFIER getNextItemWithKeyConst(TKeyType& rKey) const
        {
          if (this->hasNextItem())
          {
            rKey = (*m_Iterator).first;
            const T& rRetval = (*m_Iterator).second;
            m_Iterator++;

            return rRetval;
          }
          else
          {
            return m_tEmpty;
          }
        }

        /*****************************************************************/
        /*! \see IListIterator::reset
        */
        /*****************************************************************/
        inline virtual void MQUALIFIER reset() const
        {
          m_Iterator = m_Map.begin();
        }

        /*****************************************************************/
        /*! \see IListIterator::getNextItem
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItem() const
        {
          if (this->hasNextItem())
          {
            m_tRetval = (*m_Iterator).second;
            m_Iterator++;
          }
          else
          {
            m_tRetval = m_tEmpty;
          }
          return m_tRetval;
        }

        /*****************************************************************/
        /*! \see IListIterator::getNextItemConst
        */
        /*****************************************************************/
        virtual const T& MQUALIFIER getNextItemConst() const
        {
          if (this->hasNextItem())
          {
            const T& rRetval = (*m_Iterator).second;
            m_Iterator++;
            return rRetval;
          }
          else
          {
            return m_tEmpty;
          }
        }

        /*****************************************************************/
        /*! \see IListIterator::hasNextItem
        */
        /*****************************************************************/
        inline virtual bool MQUALIFIER hasNextItem() const
        {
          return (m_Map.end() != m_Iterator);
        }

      private:
        ///Binary search
        const std::map<TKeyType, T>& m_Map;
        ///Empty item
        T m_tEmpty;
        ///item to return (copy only)
        mutable T m_tRetval;
        ///Iterator of the map
        mutable typename std::map<TKeyType, T>::const_iterator m_Iterator;
    };

    ///Iterator Zeiger
    mutable TInternalAbstractMapIterator* m_pIterator;
};


END_NAMESPACE_Zeus

#endif

