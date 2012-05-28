/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 ***************************************************************************
 * Projekt : Zeus
 * Module  : GUIDWrapper
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : $Date: 21.04.08 16:54 $
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/GUIDWrapper.h $
** 
** 7     21.04.08 16:54 Bha
** linux binding implemented
** 
** 6     16.04.08 10:46 Mab
** Global != operator for TypGUID added.
** 
** 5     15.04.08 15:16 Bha
** global equal operator for GUID's
** 
** 4     14.04.08 17:48 Bha
** more operators and creation of GUID's
**
** 2     14.04.08 16:50 Bha
** toString method implemented
** 
** 1     7.04.08 19:06 Bha
** Usage of GUID for Interfaces
***************************************************************************/
//---------------------------------------------------------------------------

#ifndef GUIDWrapperH
#define GUIDWrapperH

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/String.h>
#include <string.h>

#if defined(ENABLE_WIN32_BINDING)

#ifdef USE_WINDOWS_H
  #include <windows.h>
#else
  #include <guiddef.h>
#endif 

#elif defined(ENABLE_LINUX_BINDING)
  #include <uuid/uuid.h>
#endif


BEGIN_NAMESPACE_Zeus

class TGUIDWrapper;

typedef TGUIDWrapper TIID;

/***************************************************************************/
/*! This class is used to wrapp a GUID
*/
/***************************************************************************/
zeusbase_class TGUIDWrapper
{
  public:
    TGUIDWrapper();
    TGUIDWrapper(const TypGUID& rGUID);

    /***********************************************************************/
    /*! Copy contructor
    */
    /***********************************************************************/
    inline TGUIDWrapper(const TGUIDWrapper& rGUIDWrapper)
    {
      m_GUID = rGUIDWrapper.m_GUID;
    }

    /***********************************************************************/
    /*! Creates a GUID out of the 128bit data
    */
    /***********************************************************************/
    inline TGUIDWrapper( Uint32 ulData1,
                         Uint16 usData2,
                         Uint16 usData3,
                         Uint8  ucData4_1,
                         Uint8  ucData4_2,
                         Uint8  ucData4_3,
                         Uint8  ucData4_4,
                         Uint8  ucData4_5,
                         Uint8  ucData4_6,
                         Uint8  ucData4_7,
                         Uint8  ucData4_8)
    {
      m_GUID.ulData1 = ulData1;
      m_GUID.usData2 = usData2;
      m_GUID.usData3 = usData3;
      m_GUID.aucData4[0] = ucData4_1;
      m_GUID.aucData4[1] = ucData4_2;
      m_GUID.aucData4[2] = ucData4_3;
      m_GUID.aucData4[3] = ucData4_4;
      m_GUID.aucData4[4] = ucData4_5;
      m_GUID.aucData4[5] = ucData4_6;
      m_GUID.aucData4[6] = ucData4_7;
      m_GUID.aucData4[7] = ucData4_8;
    }

    /***********************************************************************/
    /*! Destructor
    */
    /***********************************************************************/
    inline virtual ~TGUIDWrapper() {}

    //methods of GUIDWrapper
    TString toString() const;


    /**********************************************************************/
    /*! assigns a guid to the wrapper
    */
    /**********************************************************************/
    inline TGUIDWrapper& operator=(const TypGUID& rGuid)
    {
      m_GUID = rGuid;
      return *this;
    }

    /**********************************************************************/
    /*! assigns a guid wrapper object
    */
    /**********************************************************************/
    inline TGUIDWrapper& operator=(const TGUIDWrapper& rGuidWrapper)
    {
      m_GUID = rGuidWrapper.m_GUID;
      return *this;
    }

    /***********************************************************************/
    /*! Implicit returns the GUID structure
    */
    /***********************************************************************/
    inline operator const TypGUID& () const { return m_GUID; }

    /***********************************************************************/
    /*! Implicit returns the GUID structure pointer
    */
    /***********************************************************************/
    inline const TypGUID* operator &() const { return &m_GUID; }

    /***********************************************************************/
    /*! Implicit returns the GUID structure pointer
    */
    /***********************************************************************/
    inline TypGUID* operator &() { return &m_GUID; }


    //Static methods
    static TGUIDWrapper createGUID();

    /***********************************************************************/
    /*! Checks if two GUID are equal
    */
    /***********************************************************************/
    inline static bool isEqual(const TypGUID& rID1, const TypGUID& rID2)
    {
      #ifdef __BCPLUSPLUS__
        bool bRetval = (std::memcmp(&rID1, &rID2, sizeof(TypGUID)) == 0);
      #else
        bool bRetval = (memcmp(&rID1, &rID2, sizeof(TypGUID)) == 0);
      #endif
      return bRetval;
    }

    /***********************************************************************/
    /*! Checks if two GUID are equal
    */
    /***********************************************************************/
    inline static bool isEqualInterface(const InterfaceID& rID1, const InterfaceID& rID2)
    {
      #ifdef __BCPLUSPLUS__
        bool bRetval = (std::memcmp(&rID1, &rID2, sizeof(InterfaceID)) == 0);
      #else
        bool bRetval = (memcmp(&rID1, &rID2, sizeof(InterfaceID)) == 0);
      #endif
      return bRetval;
    }

    /***********************************************************************/
    /*! Checks if a GUID is equal to INTERFACE_IZUnknown
    */
    /***********************************************************************/
    inline static bool isIZUnknown(const InterfaceID& rID1)
    {
      #ifdef ENABLE_GUID_USAGE
        #ifdef __BCPLUSPLUS__
          bool bRetval =  (std::memcmp(&rID1, &INTERFACE_IZUnknown, sizeof(InterfaceID)) == 0);
        #else
          bool bRetval =  (memcmp(&rID1, &INTERFACE_IZUnknown, sizeof(InterfaceID)) == 0);
        #endif
      #else
        bool bRetval = (rID1 == INTERFACE_IZUnknown);
      #endif
      return bRetval;
    }

    /***********************************************************************/
    /*! Returns the interface ID as a string
    */
    /***********************************************************************/
    inline static TString toString(const InterfaceID& rID)
    {
      #ifdef ENABLE_GUID_USAGE
        return TGUIDWrapper(rID).toString();
      #else
        return TString(rID);
      #endif
    }


    //---------------------------------------------------------------------
    // WIN32 methods
    #ifdef ENABLE_WIN32_BINDING
      /*********************************************************************/
      /*! Creates a GUIDWrapper out of a win32 GUID
      */
      /*********************************************************************/
      inline TGUIDWrapper(const GUID& rGUID) { assign(rGUID); }

      void assign(const GUID& rGUID);

    #elif defined(ENABLE_LINUX_BINDING)
      /*********************************************************************/
      /*! Creates a GUIDWrapper out of a uuid structure
      */
      /*********************************************************************/
      inline TGUIDWrapper(const uuid_t Guid) { assign(Guid); }

      void assign(const uuid_t Guid);
    #endif

  private:
    ///GUID structure
    TypGUID m_GUID;
};


#ifdef ENABLE_GUID_USAGE
/***************************************************************************/
/*! Global comparison operators for 2 TypGUID objects.
*/
/***************************************************************************/
inline bool operator==(const TypGUID& rGUID1, const TypGUID& rGUID2)
{
  return TGUIDWrapper::isEqualInterface(rGUID1, rGUID2);
}

inline bool operator!=(const TypGUID& rGUID1, const TypGUID& rGUID2)
{
  return !(rGUID1 == rGUID2);
}

#endif

END_NAMESPACE_Zeus
#endif
