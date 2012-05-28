/***************************************************************************
 * Copyright (C) 2005 by Benjamin Hadorn (bhadorn@swissinfo.org)           *
 *************************************************************************** 
 * Projekt : Zeus
 * Module  : IPostProcessor
 * Package : System
 * Author  : Benjamin Hadorn
 * Datum   : 21.08.06
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
 $Log: /Development_F/StuderWIN/dev/Zeus/src/zeusbase/System/Interfaces/IPostProcessor.hpp $
** 
** 11    7.04.08 19:08 Bha
** Usage of GUID for Interfaces
** 
** 10    3.09.07 7:04 bha
** New Framework using auto pointer and improved lists
** 
** 9     27.06.07 12:24 bha
** Setting parameters for post processors
** 
** 8     5.03.07 7:18 bha
** Stack und Heap Schnittstellen definiert.
***************************************************************************/

#ifndef IPostProcessorHPP
#define IPostProcessorHPP

#include <zeusbase/System/Interfaces/IZUnknown.hpp>
#include <zeusbase/System/Interfaces/IString.hpp>
#include <zeusbase/System/Interfaces/IByteArray.hpp>

#ifdef ENABLE_GUID_USAGE
  // {38DB699C-E04B-4dc8-A3FF-7820475A869B}
  #define INTERFACE_IPostProcessor     TIID(0x38db699c, 0xe04b, 0x4dc8, 0xa3, 0xff, 0x78, 0x20, 0x47, 0x5a, 0x86, 0x9b)
#else
  #define INTERFACE_IPostProcessor     0x0000000F
#endif


BEGIN_NAMESPACE_Zeus

/******************************************************************************/
/*! This interfaces defines a post processor for transforming data into an other
    data format.
*/
/******************************************************************************/
class IPostProcessor : public IZUnknown
{
  HIDE_ASSIGNMENT_OPERATOR(IPostProcessor)
  
  public:
  
    /*************************************************************************/
    /*! This transforms data of a file into a buffer. If available a file
        with rules can be given (optional)
        \param rFileName : Name of the source data file
        \param rRuleFile : Name of the file containing rules (optional)
        \param rOutput : Return buffer
        \retval RET_NOERROR : Data transformed
        \retval RET_REQUEST_FAILED : Could not transform data. Wrong input.
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER transformFile(const IString& rFileName,
                                            const IString& rRuleFile,
                                            IByteArray& rOutput)=0;

    /*************************************************************************/
    /*! This method transforms the data from a buffer to an output buffer.
        with rules can be given (optional)
        \param rBuffer : source data buffer
        \param rRuleFile : Name of the file containing rules (optional)
        \param rOutput : Return buffer
        \retval RET_NOERROR : Data transformed
        \retval RET_REQUEST_FAILED : Could not transform data. Wrong input.
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER transformBuffer(const IString& rBuffer,
                                              const IString& rRuleFile,
                                              IByteArray& rOutput)=0;

    /*************************************************************************/
    /*! This method transforms the data from a buffer to an output buffer.
        with rules can be given (optional)
        \param rBuffer : source data buffer
        \param rRuleBuffer : buffer containing rules
        \param rOutput : Return buffer
        \retval RET_NOERROR : Data transformed
        \retval RET_REQUEST_FAILED : Could not transform data. Wrong input.
    */
    /*************************************************************************/
    virtual Retval MQUALIFIER transformBuffer2(const IString& rBuffer,
                                               const IString& rRuleBuffer,
                                               IByteArray& rOutput) = 0;

    /*************************************************************************/
    /*! clears all transforming. After the transformation all parameters
        are removed automatically. However it might be a good idea also
        to call this method before setting parameters if the transformer is
        a shared object.
    */
    /*************************************************************************/
    virtual void MQUALIFIER clearParameter() = 0;

    /*************************************************************************/
    /*! Sets transforming parameters
    */
    /*************************************************************************/
    virtual void MQUALIFIER setParameter(const IString& rName, const IString& rValue)=0;
};

END_NAMESPACE_Zeus

#endif
