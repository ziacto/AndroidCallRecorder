/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : ISimpleCommand
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/ISimpleCommand.hpp $
** 
** 10    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 9     14.01.08 7:32 Bha
** Changed from pointer to references
** 
** 8     3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 7     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef ISimpleCommandHPP
#define ISimpleCommandHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>

#ifdef ENABLE_GUID_USAGE
  // {F0D110AA-61BA-472f-A805-792EF91247BA}
  #define INTERFACE_ISimpleCommand       TIID(0xf0d110aa, 0x61ba, 0x472f, 0xa8, 0x5, 0x79, 0x2e, 0xf9, 0x12, 0x47, 0xba)
#else
  #define INTERFACE_ISimpleCommand       0x0000000D
#endif



BEGIN_NAMESPACE_Zeus

class IXObject;

/******************************************************************************/
/*! The simple command interface is used  to
    define and execute commands for the framework. This commands are the base
    architecture for actions of the framework
*/
/******************************************************************************/
class ISimpleCommand : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(ISimpleCommand)
  
  public:
    /**************************************************************************/
    /*! Returns the name of a target object. This name tells for witch xobject
        this command must be used
        \param rName : return parameter of the target object name
    */
    /**************************************************************************/
    virtual void MQUALIFIER getTargetObjectName(IString& rName)const =0;

    /**************************************************************************/
    /*! Returns the main data item of the command
        \param rData : return parameter for main data
    */
    /**************************************************************************/
    virtual void MQUALIFIER getMainData(IString& rData)const =0;

    /**************************************************************************/
    /*! returns the additional data item of the command
        \param rData : return parameter for additional data
    */
    /**************************************************************************/
    virtual void MQUALIFIER getAddData(IString& rData)const =0;

    /**************************************************************************/
    /*! Returns the special data stream of a command. The stream may represent a
        unparsed xml document or just a text document such as ini, txt etc.
        \param rData : return parameter for the document
    */
    /**************************************************************************/
    virtual void MQUALIFIER getStream(IString& rData) const=0;

    /**************************************************************************/
    /*! Returns the mode of the command to execute. This tells the meaning of
        the data items.
        \return mode of the command
    */
    /**************************************************************************/
    virtual Uint MQUALIFIER getMode() const=0;

    /**************************************************************************/
    /*! Returns the security level for this command
        \return security level
    */
    /**************************************************************************/
    virtual Uint MQUALIFIER getSecurity() const=0;

    /**************************************************************************/
    /*! Sets the name of the target object
        \param rName : name of the target object
    */
    /**************************************************************************/
    virtual void MQUALIFIER setTargetObjectName(const IString& rName)=0;

    /**************************************************************************/
    /*! Sets the main data stream
        \param rData : main data object
    */
    /**************************************************************************/
    virtual void MQUALIFIER setMainData(const IString& rData)=0;

    /**************************************************************************/
    /*! Sets the additional data item
        \param rData: additional data
    */
    /**************************************************************************/
    virtual void MQUALIFIER setAddData(const IString& rData)=0;

    /**************************************************************************/
    /*! Sets the special data stream object, (document)
        \param rData : data stream
    */
    /**************************************************************************/
    virtual void MQUALIFIER setStream(const IString& rData)=0;

    /**************************************************************************/
    /*! Sets the mode of the simple command
        \param uiMode : new mode
    */
    /**************************************************************************/
    virtual void MQUALIFIER setMode(Uint uiMode)=0;

    /**************************************************************************/
    /*! Sets the security level of the command
        \param uiValue : security value
    */
    /**************************************************************************/
    virtual void MQUALIFIER setSecurity(Uint uiValue)=0;

    /**************************************************************************/
    /*! Executes the command. The command it self can have a command listener
        interface. The listener will receive the command if this method is
        called.
        \param uiMode : mode of execution
    */
    /**************************************************************************/
    virtual void MQUALIFIER execute(Uint uiMode)=0;

    /**************************************************************************/
    /*! This method can enable or disable the execution with a specific mode
        \param bEnable : true = enabled, false = block
        \param uiMode : execution mode (see execute())
    */
    /**************************************************************************/
    virtual void MQUALIFIER enableExecuteMode(bool bEnable, Uint uiMode)=0;

    /**************************************************************************/
    /*! Sets the listener interface. Only one listener can be registered.
        \param pListener : Listener interface
        \retval RET_NOERROR : Listener registered
        \retval RET_INVALID_PARAMETER : Invalid parameter received
    */
    /**************************************************************************/
    virtual Retval MQUALIFIER setListener(IXObject* pListener)=0;
};

END_NAMESPACE_Zeus

#include <zeusbase/System/Interfaces/IXObject.hpp>

#endif
