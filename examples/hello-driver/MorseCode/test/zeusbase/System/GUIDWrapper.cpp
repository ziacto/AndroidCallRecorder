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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/GUIDWrapper.cpp $
** 
** 4     21.04.08 16:54 Bha
** linux binding implemented
** 
** 3     14.04.08 17:48 Bha
** more operators and creation of GUID's
** 
** 2     14.04.08 16:50 Bha
** toString method implemented
** 
** 1     7.04.08 19:06 Bha
** Usage of GUID for Interfaces
***************************************************************************/
//---------------------------------------------------------------------------

#include <zeusbase/System/GUIDWrapper.h>
#include <zeusbase/System/BitCodedValue.h>


#if defined(ENABLE_WIN32_BINDING)
  #include <windows.h>
#endif

//---------------------------------------------------------------------------
USING_NAMESPACE_Zeus

/****************************************************************************/
/*! Creates an empty GUID
*/
/****************************************************************************/
TGUIDWrapper::TGUIDWrapper()
{
  #ifdef __BCPLUSPLUS__
    std::memset(reinterpret_cast<void*>(&m_GUID), 0, sizeof(m_GUID));
  #else
    memset(reinterpret_cast<void*>(&m_GUID), 0, sizeof(m_GUID));
  #endif
}


/****************************************************************************/
/*! Creates a GUIDWrapper out of a GUID structure
*/
/****************************************************************************/
TGUIDWrapper::TGUIDWrapper(const TypGUID& rGUID)
{
  m_GUID = rGUID;
}


#if defined(ENABLE_WIN32_BINDING)

/****************************************************************************/
/*! assigns a win32 GUI structure
*/
/****************************************************************************/
void TGUIDWrapper::assign(const GUID& rGUID)
{
  m_GUID.ulData1 = rGUID.Data1;
  m_GUID.usData2 = rGUID.Data2;
  m_GUID.usData3 = rGUID.Data3;
  m_GUID.aucData4[0] = rGUID.Data4[0];
  m_GUID.aucData4[1] = rGUID.Data4[1];
  m_GUID.aucData4[2] = rGUID.Data4[2];
  m_GUID.aucData4[3] = rGUID.Data4[3];
  m_GUID.aucData4[4] = rGUID.Data4[4];
  m_GUID.aucData4[5] = rGUID.Data4[5];
  m_GUID.aucData4[6] = rGUID.Data4[6];
  m_GUID.aucData4[7] = rGUID.Data4[7];
}

#elif defined(ENABLE_LINUX_BINDING)

/****************************************************************************/
/*! assigns an uuid structure
*/
/****************************************************************************/
void TGUIDWrapper::assign(const uuid_t Guid)
{
  memcpy(reinterpret_cast<void*>(&m_GUID), reinterpret_cast<const void*>(Guid), sizeof(TypGUID));
}

#endif

/****************************************************************************/
/*! Returns the String of the GUID
*/
/****************************************************************************/
TString TGUIDWrapper::toString() const
{
  TBitCodedValue B1(m_GUID.ulData1);
  TBitCodedValue B2(m_GUID.usData2);
  TBitCodedValue B3(m_GUID.usData3);
  TBitCodedValue B4(m_GUID.aucData4[0]);
  TBitCodedValue B5(m_GUID.aucData4[1]);
  TBitCodedValue B6(m_GUID.aucData4[2]);
  TBitCodedValue B7(m_GUID.aucData4[3]);
  TBitCodedValue B8(m_GUID.aucData4[4]);
  TBitCodedValue B9(m_GUID.aucData4[5]);
  TBitCodedValue B10(m_GUID.aucData4[6]);
  TBitCodedValue B11(m_GUID.aucData4[7]);

  TString strRetval(L"{");
  strRetval += B1.toHex();
  strRetval += L", ";
  strRetval += B2.toHex();
  strRetval += L", ";
  strRetval += B3.toHex();
  strRetval += L", ";
  strRetval += B4.toHex();
  strRetval += L", ";
  strRetval += B5.toHex();
  strRetval += L", ";
  strRetval += B6.toHex();
  strRetval += L", ";
  strRetval += B7.toHex();
  strRetval += L", ";
  strRetval += B8.toHex();
  strRetval += L", ";
  strRetval += B9.toHex();
  strRetval += L", ";
  strRetval += B10.toHex();
  strRetval += L", ";
  strRetval += B11.toHex();
  strRetval += L"}";

  return strRetval;
}


/****************************************************************************/
/*! Creates a new GUID calling the API function
*/
/****************************************************************************/
/*static*/ TGUIDWrapper TGUIDWrapper::createGUID()
{
  #if defined(ENABLE_WIN32_BINDING)
    GUID Guid;

    CoCreateGuid(&Guid);

    return TGUIDWrapper(Guid);

  #elif defined(ENABLE_LINUX_BINDING)
    uuid_t Guid;
    uuid_generate(Guid);

    return TGUIDWrapper(Guid);
  #else
    #error Platform not defined to create GUID
  #endif
}
