#ifndef PLG_InputDevice_HPP
#define PLG_InputDevice_HPP 

//==============================================================================
//
// Copyright (c) 1996, 2016, Oracle and/or its affiliates. All rights reserved.
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
// $RCSfile: InputDevice.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: kmsantha $
// $Date: 2016/02/05 09:52:27 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.5  2004/01/26 ammon
// PRSF00086760 Pass pcm context with flist for RTDP.
//
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
// Revision 1.19  2001/07/12 10:23:58  mliebmann
// PETS #36926 handling of isUsable()-call fixed on all levels
//
// Revision 1.18  2001/06/05 14:36:17  mliebmann
// reject stream number return fixed
//
// Revision 1.17  2001/05/31 10:30:54  mliebmann
// INTERNAL.SEQ_CHECK is filled with default value 1 for sequence checking
//
// Revision 1.16  2001/05/29 13:05:34  mliebmann
// set recordNumber of each edr added
//
// Revision 1.15  2001/05/08 14:52:14  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.14  2001/05/03 16:03:49  bt
// Format renamed to Pipeline.
//
// Revision 1.13  2001/05/03 11:39:55  mliebmann
// GenericIO: Sequencer bug fixed and little changes
//
// Revision 1.12  2001/04/26 11:47:53  mliebmann
// GenericIO: little changes
//
// Revision 1.11  2001/04/26 09:26:59  mliebmann
// GenericIO: TAM added
//
// Revision 1.10  2001/04/11 10:15:13  mliebmann
// Generic IO: little changes and documentation added
//
// Revision 1.9  2001/04/10 10:01:32  mliebmann
// Generic IO: enumeration FILE_IO added
//
// Revision 1.8  2001/04/09 14:19:28  mliebmann
// FRM eliminated
//
// Revision 1.7  2001/04/04 10:21:54  sd
// - Include of PBC::EdrMsg.hpp removed
//
// Revision 1.6  2001/04/04 08:34:45  mliebmann
// Generic IO: default outputdevice added
//
// Revision 1.5  2001/04/03 14:22:12  mliebmann
// Generic IO: changes
//
// Revision 1.4  2001/03/28 09:52:32  mliebmann
// Generic IO - only Backup
//
// Revision 1.3  2001/03/27 13:23:37  mliebmann
// Generic IO - only Backup
//
// Revision 1.2  2001/03/23 15:10:09  mliebmann
// GenericIO - only backup
//
// Revision 1.1  2001/03/21 09:41:56  mliebmann
// only for Backup
//
//
//==============================================================================

#if !defined PLG_EXPORT
  #if defined(WINDOWS)
    #if !defined(PLG_INTERNAL)
      #define PLG_EXPORT __declspec(dllimport)
    #else
      #define PLG_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PLG_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TVHMAP_H
  #include <rw/tvhdict.h>
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
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
#ifndef   _PCM_H
  #include "pcm.h"
#endif

namespace PPL
{
class InputController;
}
namespace PLG
{
//------------------------------------------------------------------------------
// Forward declarations and typedefs.
//------------------------------------------------------------------------------

/** <tt><b>abstract class InputDevice</b></tt><br>
    <p>This module represents the first element of <em>integRate</em>.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: InputDevice.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2016/02/05 09:52:27 $</font></td>
    <td><font size=-1>$Author: kmsantha $</font></td>
    </tr>
    </table>                                                                          
  
    <dl>
      <dt><b>Registry entries</b></dt>
      <dd>DefaultOutput</dd>
      <dt><b>Messages send</b></dt>
      <dd>none</dd>
      <dt><b>Messages receive</b></dt>
      <dd>none</dd>
      <dt><b>Request send</b></dt>
      <dd>REQ_STREAM_NUMBER</dd>
      <dt><b>Request receive</b></dt>
      <dd>none</dd>
      <dt><b>Event send</b></dt>
      <dd>none</dd>
      <dt><b>Errors</b></dt>
      <dd>ERR_NO_DEFAULT_OUTPUT_STREAM</dd>
    </dl> 

*/

class InputDevice : public TransactionPlugIn
{
  public:

    /**@name InputDevice Constructors and Destructors */
    //@{
      /** Default constructor.<br>
        * Creates an unregistered OutputStreamPlugIn.
        * This Object cannot be used as an output stream. */
      InputDevice();

      /** Standard constructor.<br>
        * Creates an registered InputDevice. 
        * @param name    The name for the created object.
        * @param version The version for the created object. */
      InputDevice(const BAS::String& name,
                      const BAS::String& version);

      /// Destructor.
      virtual ~InputDevice();
    //@}

    /** Transaction-functions */
    //@{
      /** Send a begin transaction for the given transaction id.
        * @param id The transaction id.
        * @return true operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool beginTransactionIO(const TAM::TransId* id) = 0;

      /** Prepare to commit for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool prepareCommitIO(const TAM::TransId& id) = 0;

      /** Commit transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool commitIO(const TAM::TransId& id) = 0;
   
      /** Cancel transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancelIO(const TAM::TransId& id) = 0;
   
      /** Rollback transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollbackIO(const TAM::TransId& id) = 0;
    //@}

    /** Stream-access-functions */
    //@{
      /** WaitForData.
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT waitForData() = 0;
   
      /** Open device. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT open(BAS::String & streamName);

      /** Read realtime device. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT read(pin_flist_t*& flistpp, pcm_context_t* ctxp);
   
      /** Read from device. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT read() = 0;
   
      /** Close device. 
        * @return <tt>STR::IOResultT</tt> IO result. */
      virtual STR::IOResultT close() = 0;
    //@}

    /** Module control. */
    //@{
      /** IsActive. Show if the module is active or not.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool isActive();

      /// RequestAbort. Immediate kill of the process.
      virtual void requestAbort();

      /// Push the EDR contaienr into the input queue.
      bool pushEdr(EDR::Container* edr);

      /** Is modul usable.
        * @return <tt>true</tt> is usable,<br>
        *         <tt>false</tt> is not usable. */
      virtual bool isUsable();

	/** Request stop of processing; streams underneath receive a notification
	 */
	virtual bool stop();
    //@}

    bool setInputController(PPL::InputController * inputController);

	PPL::InputController* getInputController() const;
  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    InputDevice(InputDevice& right);
    const InputDevice& operator=(InputDevice& right);

    bool setTransId(const TAM::TransId * id);

    PPL::InputController * inputControllerM;
    
    // the default output stream for the edr data
    int64                    defaultOutputStreamNumberM;
    BAS::String              defaultOutputStreamNameM;

    int64                    recordNumberM;
    
    // Registry strings
    PLG_EXPORT static const BAS::String registryDefaultOutputCM;
    PLG_EXPORT static const BAS::String registryPipelinesCM;

    EDR::Index seqCheckIdxM;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------
inline bool 
InputDevice::isActive()
{
  return true;
}

inline void 
InputDevice::requestAbort()
{
}
}
#endif // InputDevice_HPP

