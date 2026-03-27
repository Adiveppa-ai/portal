#ifndef PLG_InputStreamDevice_HPP
#define PLG_InputStreamDevice_HPP

// @(#)%Portal Version: InputStreamDevice.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:47:54 %
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLG
//------------------------------------------------------------------------------
// Module Description:
//  OutputStreamPlugIn class implementation.
//
//  This class is the base class for all output stream PlugIn's. 
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: InputStreamDevice.hpp,v $
// $Revision: 1.4 $
// $Author: mliebmann $
// $Date: 2001/11/21 10:36:49 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: InputStreamDevice.hpp,v $
// Revision 1.4  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// Revision 1.3  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.2  2001/09/03 08:58:09  mliebmann
// CR-08.2001 some includes never used in v4-30
//
// Revision 1.1  2001/08/10 12:35:10  mliebmann
// PETS #36559 SourcePro AIX port
//
// Revision 1.3  2001/07/12 10:23:58  mliebmann
// PETS #36926 handling of isUsable()-call fixed on all levels
//
// Revision 1.2  2001/05/08 14:52:14  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.1  2001/04/26 09:26:59  mliebmann
// GenericIO: TAM added
//
//==============================================================================

#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>
#endif
#ifndef   LOG_STREAMDATE_HPP
  #include "LOG/StreamDate.hpp"
#endif
#ifndef   PLI_InputManagerInterface_HPP
  #include "PLI/InputManagerInterface.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   STR_InStreamManager_HPP
  #include "STR/InStreamManager.hpp"
#endif
#ifndef   PLG_InputDevice_HPP
  #include "PLG/InputDevice.hpp"
#endif
namespace PLG
{
//------------------------------------------------------------------------------
// Forward declarations and typedefs.
//------------------------------------------------------------------------------

/** <tt><b>abstract class InputDevice</b></tt><br>
    <p>This module represents the first element of <em>integRate</em>
    and it uses a stream-module to access to physical devices.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: InputStreamDevice.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.4 $</font></td>
    <td><font size=-1>$Date: 2001/11/21 10:36:49 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>                                                                          
  
    <dl>
      <dt><b>Registry entries</b></dt>
      <dd>InputStream</dd>
      <dt><b>Messages send</b></dt>
      <dd>none</dd>
      <dt><b>Messages receive</b></dt>
      <dd>none</dd>
      <dt><b>Request send</b></dt>
      <dd>none</dd>
      <dt><b>Request receive</b></dt>
      <dd>none</dd>
      <dt><b>Event send</b></dt>
      <dd>none</dd>
      <dt><b>Errors</b></dt>
      <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    </dl> 

*/
class InputStreamDevice : public InputDevice
{
  public:

    /**@name InputStreamDevice Constructors and Destructors */
    //@{
    /** Default constructor.<br>
        Creates an unregistered OutputStreamPlugIn.
        This Object cannot be used as an output stream. */
    InputStreamDevice();

    /** Standard constructor.<br>
        Creates an registered InputDevice. 
        @param name    The name for the created object.
        @param version The version for the created object. */
    InputStreamDevice(const BAS::String& name,
                          const BAS::String& version);

    /// Destructor.
    virtual ~InputStreamDevice();
    //@}

    /** Transaction-functions */
    //@{
      /** Send a begin transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool beginTransactionIO(const TAM::TransId* id);

      /** Prepare to commit for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool prepareCommitIO(const TAM::TransId& id);

      /** Commit transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool commitIO(const TAM::TransId& id);
   
      /** Cancel transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancelIO(const TAM::TransId& id);
   
      /** Rollback transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollbackIO(const TAM::TransId& id);
    //@}

    /** Stream-access-functions */
    //@{
      /** WaitForData. */
      virtual STR::IOResultT waitForData();
   
      /** Open device. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT open(BAS::String & streamName);
   
      /** Read from device. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT read() = 0;
   
      /** Close device. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT close();
    //@}

    /** Module control. */
    //@{
      /** IsActive. Show if the module is active or not.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool isActive();

      /** RequestAbort. Immediate kill of the process. */
      virtual void requestAbort();

      /** Shutdown. Show the stream that the system shutdown. */
      virtual bool shutdown();


	bool install();
	bool uninstall();
	bool startup();
	bool stop();

      /** Get the stream module. */
      virtual STR::InStreamManager* inStreamManagerPlugIn();
    
      /** Write version of the module. */
      void writeModuleVersion() const;

      /** Is modul usable.
        * @return <tt>true</tt> is usable,<br>
        *         <tt>false</tt> is not usable. */
      virtual bool isUsable();
    //@}

  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    InputStreamDevice(InputStreamDevice& right);
    const InputStreamDevice& operator=(InputStreamDevice& right);
    STR::InStreamManager* inStreamManagerPlugInM;

    PLI::InputManagerInterface* inStreamManagerInterfaceM;
    
    // the default output stream for the edr data
    int64                    defaultOutputStreamNumberM;
    BAS::String              defaultOutputStreamNameM;
    
    // Registry strings
    PLG_EXPORT static const BAS::String inputStreamManagerCM;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
inline void InputStreamDevice::requestAbort()
{
  D_ENTER("PLG::InputStreamDevice::requestAbort()");
  RWPRECONDITION(inStreamManagerPlugInM);
  
  // tell the stream the request!
  inStreamManagerPlugInM->requestAbort();
}

inline STR::InStreamManager* InputStreamDevice::inStreamManagerPlugIn()
{
  D_ENTER("PLG::InputStreamDevice::inStreamManagerPlugIn()");
  return inStreamManagerPlugInM;
}

inline bool InputStreamDevice::isActive()
{
  D_ENTER("PLG::InputStreamDevice::isActive()");
  RWPRECONDITION(inStreamManagerPlugInM);
  
  return inStreamManagerPlugInM->isActive();
}
}
#endif // InputStreamDevice_HPP
