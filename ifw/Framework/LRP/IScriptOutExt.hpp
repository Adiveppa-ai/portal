#ifndef LRP_ISCRIPTOUTEXT_HPP
#define LRP_ISCRIPTOUTEXT_HPP

//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class IScriptOutExt.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: IScriptOutExt.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:50 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: IScriptOutExt.hpp,v $
// Revision 1.11 2012/05/14 Santanu 
// bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
//
// Revision 1.10  2001/06/27 06:56:55  sd
// - New interface for the output device.
//
// Revision 1.9  2001/06/26 13:42:07  sd
// - Reject handling changed
//
// Revision 1.8  2001/06/26 10:57:01  sd
// - IScript functions renamed
// - Error handling improved
//
// Revision 1.7  2001/05/21 12:16:29  sd
// - Releasing the EDRs via PLG::OutputDevice::releaseEdr()
//
// Revision 1.6  2001/05/18 12:52:59  sd
// - Error handling added
//
// Revision 1.5  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.4  2001/04/11 07:37:38  sd
// - The extension now releases the EDR containers.
//
// Revision 1.3  2001/04/04 11:54:14  sd
// - Old stream interfaces replaced by new stream managers.
//
// Revision 1.2  2001/03/12 15:19:20  sd
// - output processing corrected
//
// Revision 1.1  2001/03/07 11:00:55  sd
// - Initial revision
//
//==============================================================================

#if !defined LRP_EXPORT
  #if defined(WINDOWS)
    #if !defined(LRP_INTERNAL)
      #define LRP_EXPORT __declspec(dllimport)
    #else
      #define LRP_EXPORT __declspec(dllexport)
    #endif
  #else
    #define LRP_EXPORT 
  #endif
#endif

#ifndef   __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif
#ifndef   SCR_EXTENSION_HPP
  #include "SCR/Extension.hpp"
#endif
#ifndef   SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   EDR_FACTORY_HPP
  #include "EDR/Factory.hpp"
#endif
#ifndef   PLG_OutputDevice_HPP
  #include "PLG/OutputDevice.hpp"
#endif
#ifndef   PLG_OutputStreamDevice_HPP
  #include "PLG/OutputStreamDevice.hpp"
#endif
#ifndef   PPL_OutputCollection_HPP
  #include "PPL/OutputCollection.hpp"
#endif

namespace FRM
{
class DataDescr;
}
namespace LRP
{

/** <b><tt>IScriptOutExt</tt></b> is the iScript extension used in the
 *  output parser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: IScriptOutExt.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:50 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>
 */
class IScriptOutExt : public SCR::Extension
{
  public:
    // Class members
    LRP_EXPORT static const BAS::String extensionNameCM;

    /**@name IScriptOutExt constructors and destructor */
    //@{

    /** Constructor
     *  @param dataDescr Pointer to the file data description
     *  @param outputStreamDevice Pointer to the output stream device
     */
    IScriptOutExt( const BAS::String&       interpreterName,
                   FRM::DataDescr*          dataDescr,
                   PLG::OutputStreamDevice* outputStreamDevice );

    /** Destructor
     */
    virtual ~IScriptOutExt();

    //@}

    /**@name IScriptOutExt public methods */
    //@{

    /** Get the name of the extension
     *  @return Reference to the string with the name of the extension
     */
    virtual const BAS::String& extensionName() const;

    /** Get a variable by it's name
     *  @param name The name of the variable
     *  @return Pointer to the variable on success, 0 otherwise
     */
    virtual SCR::Variable* variable( const BAS::String& name );

    /** Get a pointer to the file data description
     *  @return Pointer to the file data description
     */
    FRM::DataDescr* dataDescr() const;
    
    /** Get a pointer to the current EDR container
     *  @return Pointer to the EDR container
     */
    EDR::Container* currentEdr();

    /** Set the pointer to the current EDR container
     *  @param edr Pointer to the current edr container
     */
    void nextEdr( EDR::Container* edr );

    /** Get a pointer to the output stream
     *  @return Pointer to the output stream
     */
    STR::OutStreamManager* outputStream();

    /** Set the reject current edr flag
     *  @param flag The new flag value
     */
    void rejectCurrent( bool flag );

    /** Get the EDR to reject
     *  @return Pointer to the EDR to reject
     */
    EDR::Container* rejectedEdr();

    /** Add a new identifier to the actual statement list 
     *  @param identifier Identifier of this value
     *  @param value Variable to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addIdentifier( const BAS::String& identifier,
                        SCR::Variable*     value );

    /** Get the interpreter name
     *  @return the interpreter name
     */
    const BAS::String& interpreterName() const;

    /* Check if the multithreaded option is enabled
     * for the output controller
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool isMultiThreadedWrite() const;


    //@}

  private:
    // Hide the copy constructor etc.
    IScriptOutExt( const IScriptOutExt& rhs );
    const IScriptOutExt& operator=( const IScriptOutExt& rhs );
    
    // Instance members
    EDR::Container*           currentEdrM;
    bool                     rejectCurrentM;
    EDR::Container*           lookAheadEdrM;
    FRM::DataDescr*           dataDescrM;
    PLG::OutputStreamDevice*  outputStreamDeviceM;
    BAS::String               interpreterNameM;
    
    SCR::VariableMap	     variablesM;

    // Class members
    LRP_EXPORT static SCR::VariableMap  constantsCM;
    LRP_EXPORT static RWMutexLock      mutexCM;
    LRP_EXPORT static int              instancesCM;
};

//==============================================================================
// Get a pointer to the data description
//==============================================================================
inline FRM::DataDescr*
IScriptOutExt::dataDescr() const
{
  return dataDescrM;
}

//==============================================================================
// Get a pointer to the current EDR container
//==============================================================================
inline EDR::Container*
IScriptOutExt::currentEdr() 
{
  return currentEdrM;
}

//==============================================================================
// Set the pointer to the current EDR container
//==============================================================================
inline void
IScriptOutExt::nextEdr( EDR::Container* edr ) 
{
  if ( currentEdrM != 0 )
  {
    // The current EDR can be released
    outputStreamDeviceM->outputCollection()->releaseEdr( currentEdrM );
  }
  currentEdrM   = lookAheadEdrM;
  lookAheadEdrM = edr;
}

//==============================================================================
// Get a pointer to the output stream
//==============================================================================
inline STR::OutStreamManager*
IScriptOutExt::outputStream()
{
  RWPRECONDITION( outputStreamDeviceM->outStreamManagerPlugIn() != 0 );
  return outputStreamDeviceM->outStreamManagerPlugIn();
}

//==============================================================================
// Set the reject current flag
//==============================================================================
inline void
IScriptOutExt::rejectCurrent( bool flag )
{
  rejectCurrentM = flag;
}

//==============================================================================
// Get the rejected EDR container
//==============================================================================
inline EDR::Container*
IScriptOutExt::rejectedEdr()
{
  if ( rejectCurrentM == true )
  {
    EDR::Container* edr = currentEdrM;
    rejectCurrentM = false;
    currentEdrM = 0;
    return edr;
  }
  else
  {
    return 0;
  }
}
}
#endif // ISCRIPTOUTEXT_HPP
