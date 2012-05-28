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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/StringMap.hpp $
** 
** 26    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 25    7.01.08 9:01 Bha
** copy method implemented
** 
** 24    3.09.07 17:21 Mabbuehl
** VS6 warnings removed.
** 
** 23    3.09.07 14:02 Mabbuehl
** VS6 warnings removed.
** 
** 22    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 21    11.06.07 10:29 bha
** Anpassungen an Zeus-Framework 0.4.2
** 
** 15    9.10.06 8:29 bha
** IString-Methoden mit Referenz statt Pointer
**
** 14    7.09.06 14:44 bha
** Erweitern des Strings
***************************************************************************/

#ifndef StringMapH
#define StringMapH

#include <zeusbase/System/String.h>
#include <zeusbase/System/ZObject.h>
#include <zeusbase/System/Interfaces/IStringMap.hpp>
#include <zeusbase/System/Iterators.hpp>

#if defined(__GNUC__)
  #include <string.h>
  #include <string>
  #include <map>
#else
  #include <string.h>

  #ifdef _MSC_VER
    #pragma warning(push, 1) // Avoid Visual Studio 6.0 level 4 and 3 compiler warnings.
  #endif

  #include <string>
  #include <map>

  #ifdef _MSC_VER
    #pragma warning(pop)
  #endif
#endif

BEGIN_NAMESPACE_Zeus
using namespace std;

/*****************************************************************************/
/*! The String map wrapps a std::map class using a string as key
*/
/*****************************************************************************/
template <class T> class TStringMap : public IStringMap<T>
{
  typedef std::map<std::wstring, T>  TStrMap;
  public:
    /************************************************************************/
    /*! Creates a empty map
    */
    /************************************************************************/
    TStringMap()
     : m_tEmpty(T())
    {
      m_pIterator = NULL;

      // DO NOT USE MEMSET. This causes memory leaks on complex objects
      //memset(&m_tEmpty, 0, sizeof(T));
    }
    
    /************************************************************************/
    /*! Creates a empty map, defining an empty item
        \param emptyitem : Empty item
    */
    /************************************************************************/
    TStringMap(const T& rEmptyItem)
     : m_tEmpty(rEmptyItem)
    {
      m_pIterator = NULL;
    }
    
    /*********************************************************************/
    /*! Copy constructor
        \param rMap : Map to copy
    */
    /*********************************************************************/
    TStringMap(const TStringMap<T>& rMap)
     : m_Map(rMap.m_Map),
       m_tEmpty(rMap.m_tEmpty)
    {
      m_pIterator = NULL;
    }

    /************************************************************************/
    /*! Destroys the map
    */
    /************************************************************************/
    virtual ~TStringMap()
    {
      clear();
      
      //resets all iterators
      TAbstractMapIterator* pIt = m_pIterator;
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
    virtual void MQUALIFIER copyToMap(IMap<IString, T>& rMap) const
    {
      TConstMapIterator<IString, T> It = this->getConstIterator();
      while(It.hasNextItem())
      {
        TString strKey;
        const T& rItem = It.getNextItemWithKeyConst(strKey);
        rMap.setItem(strKey, rItem);
      }
    }

    /************************************************************************/
    /*! \see IMap::getItem
    */
    /************************************************************************/
    inline T& getItem(const TString& rKey)
    {
      return getItem((const IString&)rKey);
    }

    /************************************************************************/
    /*! \see IMap::setItem
    */
    /************************************************************************/
    inline void setItem(const wchar_t* pKey, const T& rData)
    {
      setItem(TString(pKey), rData);
    }

    /************************************************************************/
    /*! \see IMap::deleteItem
    */
    /************************************************************************/
    inline bool deleteItem(const TString& rKey)
    {
      return deleteItem((const IString&)rKey);
    }

    /************************************************************************/
    /*! Checks if an item is inside the map
    */
    /************************************************************************/
    inline bool hasItem(const TString& rKey) const
    {
      return hasItem((const IString&)rKey);
    }

    /************************************************************************/
    /*! \see IMap::getItem
    */
    /************************************************************************/
    virtual T& MQUALIFIER getItem(const IString& rKey)
    {
      // CATUTION:
      // Do not use the direct statement
      //  strKey = rKey.c_bstr();
      // for some reasons this causes errors
      std::wstring strKey = TString(&rKey).c_bstr();
      typename TStrMap::iterator it = m_Map.find(strKey);
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
    virtual const T& MQUALIFIER getItemConst(const IString& rKey) const
    {
      // CATUTION:
      // Do not use the direct statement
      //  strKey = rKey.c_bstr();
      // for some reasons this causes errors
      std::wstring strKey = TString(&rKey).c_bstr();
      typename TStrMap::const_iterator it = m_Map.find(strKey);
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
    virtual void MQUALIFIER setItem(const IString& rKey, const T& rData)
    {
      // CATUTION:
      // Do not use the direct statement
      //  strKey = rKey.c_bstr();
      // for some reasons this causes errors
      std::wstring strKey = TString(&rKey).c_bstr();
      m_Map[strKey] = rData;
    }

    /************************************************************************/
    /*! \see IMap::isEmpty
    */
    /************************************************************************/
    virtual bool MQUALIFIER isEmpty() const
    {
      return m_Map.empty();
    }
    
    /************************************************************************/
    /*! \see IMap::getCount
    */
    /************************************************************************/
    virtual Int MQUALIFIER getCount() const
    {
      return m_Map.size();
    }

    /************************************************************************/
    /*! \see IMap::deleteItem
    */
    /************************************************************************/
    virtual bool MQUALIFIER deleteItem(const IString& rKey)
    {
      // CATUTION:
      // Do not use the direct statement
      //  strKey = rKey.c_bstr();
      // for some reasons this causes errors
      std::wstring strKey = TString(&rKey).c_bstr();
      return (m_Map.erase(strKey) == 1);
    }

    /************************************************************************/
    /*! \see IMap::hasItem
    */
    /************************************************************************/
    virtual bool MQUALIFIER hasItem(const IString& rKey) const
    {
      bool bRetval = false;

      // CATUTION:
      // Do not use the direct statement
      //  strKey = rKey.c_bstr();
      // for some reasons this causes errors
      std::wstring strKey = TString(&rKey).c_bstr();

      typename TStrMap::const_iterator it;
      it = m_Map.find(strKey);
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
    virtual void MQUALIFIER clear()
    {
      m_Map.clear();
    }
    
    /************************************************************************/
    /*! \see IMap::getIterator
    */
    /************************************************************************/
    virtual IMapIterator<IString,T>* MQUALIFIER getIterator()
    {
      TStringMapIterator* pIterator = new TStringMapIterator(*this, m_Map, m_tEmpty);
      pIterator->setNextIterator(m_pIterator);
      m_pIterator = pIterator;
      return m_pIterator;
    }

    /************************************************************************/
    /*! \see IMap::getConstIterator
    */
    /************************************************************************/
    virtual const IMapIterator<IString, T>* MQUALIFIER getConstIterator() const
    {
      TConstStringMapIterator* pIterator = new TConstStringMapIterator(*this, m_Map, m_tEmpty);
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
      TAbstractMapIterator* pIt = m_pIterator;
      TAbstractMapIterator* pItPrev = NULL;
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
    virtual bool MQUALIFIER equals(const IMap<IString, T>& rMap) const
    {
      bool bRetval = (this->getCount() == rMap.getCount());

      const IMapIterator<IString, T>* pIt1 = getConstIterator();
      const IMapIterator<IString, T>* pIt2 = rMap.getConstIterator();

      while(bRetval && pIt1->hasNextItem() && pIt2->hasNextItem())
      {
        TString strKey1;
        TString strKey2;
        bRetval = (pIt1->getNextItemWithKeyConst(strKey1) == pIt2->getNextItemWithKeyConst(strKey2));

        bRetval &= (strKey1 == strKey2);
      }
      pIt1->release();
      pIt2->release();
      return bRetval;
    }

    /************************************************************************/
    /*! \see IMap::equals
    */
    /************************************************************************/
    virtual bool equals(const TStringMap<T>& rMap) const
    {
      return (this->getCount() == rMap.getCount() &&
              m_Map == rMap.m_Map);
    }

    /*********************************************************************/
    /*! assign operator
    */
    /*********************************************************************/
    TStringMap<T>& operator=(const TStringMap<T>& rInPar)
    {
      m_Map = rInPar.m_Map;
      m_tEmpty = rInPar.m_tEmpty;
      return *this;
    }

    /*********************************************************************/
    /*! equals operator
    */
    /*********************************************************************/
    bool operator==(const TStringMap<T>& rMap) const
    {
      return equals(rMap);
    }

    /*********************************************************************/
    /*! equals operator
    */
    /*********************************************************************/
    bool operator==(const IStringMap<T>& rMap) const
    {
      return equals(rMap);
    }

    /*********************************************************************/
    /*! not equals operator
    */
    /*********************************************************************/
    bool operator!=(const TStringMap<T>& rMap) const
    {
      return !equals(rMap);
    }

    /*********************************************************************/
    /*! not equals operator
    */
    /*********************************************************************/
    bool operator!=(const IStringMap<T>& rMap) const
    {
      return !equals(rMap);
    }

  private:
    ///Empty item
    T m_tEmpty;
    ///Binary search
    TStrMap m_Map;

    /*********************************************************************/
    /*! abstract iterator of the map
    */
    /*********************************************************************/
    class TAbstractMapIterator : public IMapIterator<IString, T>
    {
      public:
        /*****************************************************************/
        /*! Creates the iterator
        */
        /*****************************************************************/
        TAbstractMapIterator(const TStringMap<T>& rParent)
        {
          m_iRefCounter = 1;
          m_pNextIterator = NULL;
          m_pParent = const_cast<TStringMap<T>*>(&rParent);
        }
        
        /*****************************************************************/
        /*! Destroys the iterator
        */
        /*****************************************************************/
        virtual ~TAbstractMapIterator()
        {}

        /*****************************************************************/
        /*! gets the next iterator
        */
        /*****************************************************************/
        TAbstractMapIterator* getNextIterator()
        { return m_pNextIterator; }

        /*****************************************************************/
        /*! sets the next iterator
        */
        /*****************************************************************/
        void setNextIterator(TAbstractMapIterator* pIt)
        { m_pNextIterator = pIt; }

        /*****************************************************************/
        /*! \see IZUnknown::askForInterface
        */
        /*****************************************************************/
        Retval MQUALIFIER askForInterface(const InterfaceID& /*rInterfaceID*/, IZUnknown*& /*rpIface*/)
        {
          return RET_UNKNOWN_INTERFACE;
        }

        /***************************************************************************/
        /*! \see IZUnknown::addRef
        */
        /***************************************************************************/
        void MQUALIFIER addRef() const
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
        void clearParent()
        {
          m_pParent = NULL;
        }
      
      protected:
        ///Next iterator
        mutable TAbstractMapIterator* m_pNextIterator;
        ///Parent instance
        mutable TStringMap<T>* m_pParent;

      private:
        ///Reference counter
        mutable Int m_iRefCounter;
    };

    /*********************************************************************/
    /*! Iterator of the map
    */
    /*********************************************************************/
    class TStringMapIterator : public TAbstractMapIterator
    {
      public:
        /*****************************************************************/
        /*! Creates the iterator
        */
        /*****************************************************************/
        TStringMapIterator(const TStringMap<T>& rParent,
                           TStrMap& rMap, 
                           T& rEmptyElement)
         : TAbstractMapIterator(rParent),
           m_rMap(rMap),
           m_Iterator(rMap.begin()),
           m_tEmpty(rEmptyElement)
        {
        }
        /*****************************************************************/
        /*! Destroys the iterator
        */
        /*****************************************************************/
        virtual ~TStringMapIterator()
        {}

        /*****************************************************************/
        /*! \see IMapIterator::getNextKey
        */
        /*****************************************************************/
        virtual Retval MQUALIFIER getNextKey(IString& rKey)
        {
          return getNextKeyConst(rKey);
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextKeyConst
        */
        /*****************************************************************/
        virtual Retval MQUALIFIER getNextKeyConst(IString& rKey) const
        {
          Retval retValue = RET_REQUEST_FAILED;
          if (this->hasNextItem())
          {
            retValue = RET_NOERROR;
            rKey.assign((*m_Iterator).first.c_str());
            m_Iterator++;
          }
          return retValue;
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextItemWithKey
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItemWithKey(IString& rKey) const
        {
          if (this->hasNextItem())
          {
            rKey.assign((*m_Iterator).first.c_str());
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
        virtual const T& MQUALIFIER getNextItemWithKeyConst(IString& rKey) const
        {
          return const_cast<const T&>(getNextItemWithKey(rKey));
        }

        /*****************************************************************/
        /*! \see IListIterator::reset
        */
        /*****************************************************************/
        virtual void MQUALIFIER reset() const
        {
          m_Iterator = m_rMap.begin();
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
        virtual const T& MQUALIFIER getNextItemConst() const
        {
          return const_cast<const T&>(this->getNextItem());
        }

        /*****************************************************************/
        /*! \see IListIterator::hasNextItem
        */
        /*****************************************************************/
        virtual bool MQUALIFIER hasNextItem() const
        {
          return (m_rMap.end() != m_Iterator);
        }

      private:
        ///Binary search
        TStrMap& m_rMap;
        ///Empty item
        T m_tEmpty;
        ///Iterator of the map
        mutable typename TStrMap::iterator m_Iterator;
    };


    /*********************************************************************/
    /*! Const iterator of the map
    */
    /*********************************************************************/
    class TConstStringMapIterator : public TAbstractMapIterator
    {
      public:
        /*****************************************************************/
        /*! Creates the const iterator
        */
        /*****************************************************************/
        TConstStringMapIterator(const TStringMap<T>& rParent,
                                const TStrMap& rMap, 
                                const T& rEmptyElement)
         : TAbstractMapIterator(rParent),
           m_rMap(rMap),
           m_tEmpty(rEmptyElement),
           m_tRetval(rEmptyElement),
           m_Iterator(rMap.begin())
        {
        }

        /*****************************************************************/
        /*! Destroys the iterator
        */
        /*****************************************************************/
        virtual ~TConstStringMapIterator()
        {}

        /*****************************************************************/
        /*! \see IMapIterator::getNextKey
        */
        /*****************************************************************/
        virtual Retval MQUALIFIER getNextKey(IString& rKey)
        {
          return getNextKeyConst(rKey);
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextKeyConst
        */
        /*****************************************************************/
        virtual Retval MQUALIFIER getNextKeyConst(IString& rKey) const
        {
          Retval retValue = RET_REQUEST_FAILED;
          if (this->hasNextItem())
          {
            retValue = RET_NOERROR;
            rKey.assign((*m_Iterator).first.c_str());
            m_Iterator++;
          }
          return retValue;
        }

        /*****************************************************************/
        /*! \see IMapIterator::getNextItemWithKey
        */
        /*****************************************************************/
        virtual T& MQUALIFIER getNextItemWithKey(IString& rKey) const
        {
          if (this->hasNextItem())
          {
            rKey.assign((*m_Iterator).first.c_str());
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
        /*! \see IMapIterator::getNextItemWithKeyConst
        */
        /*****************************************************************/
        virtual const T& MQUALIFIER getNextItemWithKeyConst(IString& rKey) const
        {
          if (this->hasNextItem())
          {
            rKey.assign((*m_Iterator).first.c_str());
            const T& rRetval = (*m_Iterator).second;
            m_Iterator++;
            return rRetval;
          }
          else
          {
            return const_cast<const T&>(m_tEmpty);
          }
        }

        /*****************************************************************/
        /*! \see IListIterator::reset
        */
        /*****************************************************************/
        virtual void MQUALIFIER reset() const
        {
          m_Iterator = m_rMap.begin();
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
          return const_cast<T&>(m_tRetval);
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
        virtual bool MQUALIFIER hasNextItem() const
        {
          return (m_rMap.end() != m_Iterator);
        }

      private:
        ///Binary search
        const TStrMap& m_rMap;
        ///Empty item
        T m_tEmpty;
        ///Return copy value
        mutable T m_tRetval;
        ///Iterator of the map
        mutable typename TStrMap::const_iterator m_Iterator;
    };

    ///Iterator Zeiger
    mutable TAbstractMapIterator* m_pIterator;
};

END_NAMESPACE_Zeus

#endif

