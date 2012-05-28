/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ILogger
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 6.03.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/ILogger.hpp $
** 
** 9     7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 8     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 7     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

 
#ifndef ILoggerHPP
#define ILoggerHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IPropertyAccess.hpp>

#ifdef ENABLE_GUID_USAGE
  // {4496EA5C-BBE7-4dc1-9906-274BCB34D006}
  #define INTERFACE_ILogger      TIID(0x4496ea5c, 0xbbe7, 0x4dc1, 0x99, 0x6, 0x27, 0x4b, 0xcb, 0x34, 0xd0, 0x6)
#else
  #define INTERFACE_ILogger      0x0000000E
#endif

BEGIN_NAMESPACE_Zeus

/**************************************************************************/
/*! This interface defines the logging mechanisme.
*/
/**************************************************************************/
class ILogger : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ILogger)
  
  public:
  
    /**********************************************************************/
    /*! Returns a new logger interface. If the name is NULL or empty, the
        root logger will be returned.
        \param rName : Name of the logger
        \param rpLogger : Return parameter of the logger
        \retval RET_NOERROR : Logger returned
        \retval RET_ERR_REQUEST_FAILED : Could not return the logger
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER getLogger(const IString& rName, ILogger*& rpLogger)=0;
    
    /**********************************************************************/
    /*! prints a debug message to the logger
        \param rMessage : Message to print
    */
    /**********************************************************************/
    virtual void MQUALIFIER printDebug(const IString& rMessage)=0;

    /**********************************************************************/
    /*! prints a error message to the logger
        \param rMessage : Message to print
    */
    /**********************************************************************/
    virtual void MQUALIFIER printError(const IString& rMessage)=0;

    /**********************************************************************/
    /*! prints a fatal error message to the logger
        \param rMessage : Message to print
    */
    /**********************************************************************/
    virtual void MQUALIFIER printFatal(const IString& rMessage)=0;

    /**********************************************************************/
    /*! prints a info message to the logger
        \param rMessage : Message to print
    */
    /**********************************************************************/
    virtual void MQUALIFIER printInfo(const IString& rMessage)=0;

    /**********************************************************************/
    /*! prints a warning to the logger
        \param rMessage : Message to print
    */
    /**********************************************************************/
    virtual void MQUALIFIER printWarn(const IString& rMessage)=0;

    /**********************************************************************/
    /*! Checks if the debug output is enabled
        \retval true : enabled
        \retval false: disabled
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isDebugEnabled()=0;

    /**********************************************************************/
    /*! Checks if the error output is enabled
        \retval true : enabled
        \retval false: disabled
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isErrorEnabled()=0;

    /**********************************************************************/
    /*! Checks if the fatal error output is enabled
        \retval true : enabled
        \retval false: disabled
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isFatalEnabled()=0;

    /**********************************************************************/
    /*! Checks if the info output is enabled
        \retval true : enabled
        \retval false: disabled
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isInfoEnabled()=0;

    /**********************************************************************/
    /*! Checks if the warning output is enabled
        \retval true : enabled
        \retval false: disabled
    */
    /**********************************************************************/
    virtual bool MQUALIFIER isWarnEnabled()=0;
    
    /**********************************************************************/
    /*! Loads the settings from a file
        \param rFileName : Name and path of file to load
        \retval RET_NOERROR : File found and settings loaded
        \retval RET_REQUEST_FAILED : Could not load settings
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER loadConfiguration(const IString& rFileName)=0;

    /**********************************************************************/
    /*! Loads the settings directly from the properties
        \param rProp : Properties instance
        \retval RET_NOERROR : Settings loaded
        \retval RET_REQUEST_FAILED : Could not load settings
    */
    /**********************************************************************/
    virtual Retval MQUALIFIER loadProperties(IPropertyAccess& rProp)=0;

  
};

END_NAMESPACE_Zeus

#endif

