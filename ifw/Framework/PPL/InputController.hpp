#ifndef PPL_InputController_HPP
#define PPL_InputController_HPP

// @(#)%Portal Version: InputController.hpp:Pipeline7.3PatchInt:1:2006-Nov-22 04:18:33 %
//==============================================================================
//
// Copyright (c) 1996, 2016, Oracle and/or its affiliates. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PPL
//
//------------------------------------------------------------------------------
// Module Description:
//   Class implementation to handle an input file or stream pipeline
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: InputController.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: skattepu $
// $Date: 2016/10/04 00:44:27 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// Revision 1.13  2011/07/05 sumeemis
// Bug 11815646 - p-10434779 phase ii changes for pipeline parallel loading ecr
//
// Revision 1.12  2006/05/30 mliu
// PRSF00207396  Create probes for processing time
//
// Revision 1.11  2005/08/08 rtang
// PRSF00167707  Add api getRealtimeMutex() to access realtimeMutexM.
//
// Revision 1.10  2004/01/26 ammon
// PRSF00086760  Pass pcm context with flist for RTDP.
//
// Revision 1.9  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// Revision 1.8  2001/07/04 13:37:23  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.7  2001/06/21 07:11:15  mliebmann
// closeing transaction after waitfordata-timeout added
//
// Revision 1.6  2001/06/15 14:06:51  mliebmann
// TAMs isactive-method added
//
// Revision 1.5  2001/06/01 08:24:09  mliebmann
// workaround for the sequencer
//
// Revision 1.4  2001/05/28 10:31:45  mliebmann
// include of EDR::World.hpp deleted and the getIndex fixed
//
// Revision 1.3  2001/05/08 14:52:14  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.2  2001/05/04 09:17:37  bt
// Method writeToPipelineLog() changed.
//
// Revision 1.1  2001/05/03 16:31:07  bt
// FRM modules moved to PPL (Format renamed to Pipeline).
//
// Revision 1.13  2001/04/26 15:23:25  sd
// - EDR::ContainerIndex introduced
//
// Revision 1.12  2001/04/26 09:23:26  mliebmann
// GenericIO: TAM added
//
// Revision 1.11  2001/04/25 14:25:39  bt
// Transaction manager added.
//
// Revision 1.10  2001/04/23 15:24:50  sd
// - New class EDR::BlockIndex introduced
//
// Revision 1.9  2001/04/11 10:14:35  mliebmann
// Generic IO: little changes and documentation added
//
// Revision 1.8  2001/04/09 14:26:05  mliebmann
// Generic IO: changes
//
// Revision 1.5  2001/03/29 14:17:34  mliebmann
// Generic IO added
//
// Revision 1.4  2001/03/27 13:22:26  mliebmann
// Generic IO - only Backup
//
// Revision 1.3  2001/03/23 15:08:10  mliebmann
// GenericIO - only backup
//
// Revision 1.2  2001/03/21 15:24:45  mliebmann
// only for backup
//
//
//==============================================================================

#if !defined PPL_EXPORT
  #if defined(WINDOWS)
    #if !defined(PPL_INTERNAL)
      #define PPL_EXPORT __declspec(dllimport)
    #else
      #define PPL_EXPORT __declspec(dllexport)
    #endif
  #else
    #define PPL_EXPORT 
  #endif
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_REGISTRYENTRY_HPP
  #include "BAS/RegistryEntry.hpp"
#endif
#ifndef   PPL_THREADBASE_HPP
  #include "PPL/ThreadBase.hpp"
#endif
#ifndef   EDR_FACTORY_HPP
  #include "EDR/Factory.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   PLG_InputDevice_HPP
  #include "PLG/InputDevice.hpp"
#endif
#ifndef   PLI_InputInterface_HPP
  #include "PLI/InputInterface.hpp"
#endif
#ifndef   TAM_MANAGERIF_HPP
  #include "TAM/ManagerIf.hpp"
#endif
#ifndef   TAM_MODULEIF_HPP
  #include "TAM/ModuleIf.hpp"
#endif
#ifndef   PLG_CIRCULARBUFFER
  #include "PLG/CircularBuffer.hpp"
#endif

#ifndef   BAS_INSTRUMENTATION_PROBE_GROUP_H
  #include "BAS/InstrumentationProbeGroup.hpp"
#endif
#ifndef   BAS_INSTRUMENTATION_PROBE_TABLE_H
  #include "BAS/InstrumentationProbeTable.hpp"
#endif


namespace PPL
{
/** <tt><b>class InputController</b></tt><br>
    handles an input file or stream pipeline.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: InputController.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2016/10/04 00:44:27 $</font></td>
    <td><font size=-1>$Author: skattepu $</font></td>
    </tr>
    </table>                     

    <dl>
      <dt><b>Registry entries</b></dt>
      <dd>InputModule</dd>
      <dt><b>Messages send</b></dt>
      <dd>MSG_STREAM_START</dd>
      <dt><b>Messages receive</b></dt>
      <dd>none</dd>
      <dt><b>Request send</b></dt>
      <dd>none</dd>
      <dt><b>Request receive</b></dt>
      <dd>none</dd>
      <dt><b>Event send</b></dt>
      <dd>none</dd>
      <dt><b>Errors</b></dt>
      <dd>ERR_EDR_CREATE</dd>
      <dd>ERR_NO_EDRFACTORY</dd>
      <dd>ERR_NOT_USABLE</dd>
    </dl> 
*/
class InputController : public ThreadBase , public TAM::ModuleIf
{
  D_SINGLETHREADED

  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      InputController();

      /** Constructs an instance to handle an input file or stream pipeline.<br> 
        * @param objectName The string is used for the object registration. */
      InputController(const BAS::String& objectName,
                          STR::Queue<EDR::Container*>* queue,
                          TAM::ManagerIf* managerIf);

      /** Constructs an instance to handle an input file or stream pipeline.<br> 
        * @param objectName The string is used for the object registration.
        * @param nextPPLObject Pointer to the next pipeline object for processing
        */
      InputController(const BAS::String& objectName,
                                ThreadBase * nextPPLObject,
                                TAM::ManagerIf* managerIf);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~InputController();

    //@}

    /**@name Public Member Functions */
    //@{

      /// Excute-Thread.
      void execute();

     /** Initialize the device
      */

      bool init();

      virtual bool pushEdr(EDR::Container* edr);

     /** 
      * Open Transaction for  Realtime Implementation
      */
      bool openRealtimeTxn();

     /** 
      * process flist for Realtime Implementation
      * @parm flistpp Input flist
      * @parm ctxpi   Pcm context
      */
      bool processRealtimeFlist(pin_flist_t*& flistpp, pcm_context_t* ctxp);

     /** 
      * Close Transaction for  Realtime Implementation
      */
      bool closeRealtimeTxn();



      /** SetMaxTransaction.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      bool   setMaxTransaction(size_t maxT);

      /// GetMaxTransaction.
      size_t getMaxTransaction();

      /// Shows the moduleversion of the devicemodule.
      void writeModuleVersion() const;
    
      /** Returns active state.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      bool isActive();
      
      /** Start the processing.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      bool start(bool flagRegUpdate=false);
      
      /** Stop the processing.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      bool stop(bool flagRegUpdate=false);
      
      /// Stop the processing emmidiate without wait of end transaction.
      void requestAbort();
      
      /// Shutdown the process.
      bool shutdown();

	bool install();

	bool uninstall();

	bool startup();
    
      /** Shows the usability.
        * @return <tt>true</tt> usable,<br>
        *         <tt>false</tt> not usable. */
      bool isUsable();

      /** Has to be implemented, but is not used or called here!!!
        * @param EdrContainerList* EDRList of processable EDRs.
        * @return <tt>true </tt> True  on success.
        *         <tt>false</tt> False on failure.
        */
      virtual bool processEdrContainer(EdrContainerList* edrList);

	/** Create an internal container from the internal factory
	 */
	virtual EDR::Container* createInternalContainer();
    //@}

    /**@name Public TAM Functions */
    //@{

      /** Prepare to commit for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool prepareCommit(const TAM::TransId& id);

      /** Commit transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool commit(const TAM::TransId& id);

      /** Cancel transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool cancel(const TAM::TransId& id);

      /** Rollback transaction for the given transaction id.
        * @param id The transaction id.
        * @return <tt>true</tt> operation was successful,<br>
        *         <tt>false</tt> otherwise. */
      virtual bool rollback(const TAM::TransId& id);

      /** Shows if the controller is active.
        * @return <tt>true</tt> active,<br>
        *         <tt>false</tt> not active. */
      virtual bool activeState();

    //@}

	/** Get the transaction count. This is also the number of files that 
	 * have been processed if units per transaction is > 1
	 * @return size_t indicating the count
	 */
	size_t getTransactionCount() const;

	/** Get the realtime mutex lock. 
	 * @return RWMutexLock, the lock for realtime pipeline transaction
	 */

	RWMutexLock& getRealtimeMutex();

	/** 
	 * set isDeactiveM flag. 
	 */
	void deactivate(bool flag);

	/** check the status  
	 * @return isDeactiveM, true, pipeline is deactivated 
	 */
	bool isDeactive();

	/** 
	 * set isRegUpdateM flag. 
	 */
	void regUpdate(bool flag);

	/** check the status  
	 * @return isRegUpdateM
	 */
	bool isRegUpdate();

	/** Get the probes
	 */
	void getInstrumentationProbe(BAS::InstrumentationProbeList& probeList) const;

  private:

    bool readRegistry();
    bool setEDRContainerIndices();

    bool sendBeginTransactionContainer(const TAM::TransId* id);
    bool sendEndTransactionContainer(const TAM::TransId* id);
    bool sendBeginContainer();
    bool sendEndContainer();
    bool sendStartContainer(const BAS::String originatorName);
    bool sendStopContainer(const BAS::String originatorName);

    void writeToPipelineLog(const BAS::Status& s) const;

    /** Initialize the probes.
     * @return True on success; otherwise, False.
     */
    bool initInstrumentationProbe();

    // The following private attributes and functions are used internally.

    PLG::InputDevice           * inputDevicePlugInM;
    
    PLI::InputInterface          inputDeviceInterfaceM;

    // Use this to protect open/close realtime txn and start/stop/opcode execute   
    RWMutexLock                 realtimeMutexM;
    
    EDR::Factory               * edrFactoryM;
    u_int64               edrNumberM;
    
    TAM::ManagerIf             * managerIfM;
    EDR::Index                 streamTransIdIdxM;
    
  // Store TxnId for Realtime
	TAM::TransId*             realtimeTxnIdM;

    bool                      transactionM;
    size_t                    countTransactionM;
    int32                     maxTransactionM;
    
    bool                      shallGoInactiveM;
    bool                      shallGoActiveM;
    bool                      isRunningM;
    bool                      requestAbortM;

    // actual streamName
    BAS::String                streamNameM;
    
    EDR::Index                 seqCheckIdxM;
    EDR::Index                 streamNameIdxM;
    EDR::ContainerIndex        internalContainerIdxM;
    EDR::ContainerIndex        trailerContainerIdxM;

    BAS::RegisteredObject*     pipelineLogM;

    PPL_EXPORT static const BAS::String   registryPipelinesCM;
    PPL_EXPORT static const BAS::String   unitsPerTransactionCM;
    PPL_EXPORT static const BAS::String   noThreadCM;

    bool                      noThreadM;
    
    bool                      isValidM;
    
    // Used by NET::EM (CO167707),
    // set to true when NET::EM detects the pipeline instance was deactivated
    bool                      isDeactiveM;

    // isRegUpdateM will be set when registry update request is taken up
    bool                      isRegUpdateM;

    PPL_EXPORT static const u_int64 MaxBufEntriesCM;
  
    // ns timer
    BAS::NanoSecondTimer nsTimerM;

    // Circular buffer to hold last processing times
    PLG::CircularBuffer processingTimeBufM;

    /** Group/Table container for storing instrumentation probes
     *
     */
    BAS::InstrumentationProbeGroup* inputControllerInfoInstrM;	
    BAS::InstrumentationProbeTable* processingTimeBufInfoInstrM;

    BAS::String origStreamNameM;
    TAM::TransId* transIdM;
    EDR::Container* headerEdrM;
    int smallBatchNumM;
    int maxDetailsPerUnitM;
    int detailsPerUnitCountM;
};

//==============================================================================
//==============================================================================
inline bool InputController::isActive()
{
  D_ENTER("PPL::InputController::isActive()");
  RWPRECONDITION(inputDevicePlugInM);

  if (!isRunningM)
  {
    return false;
  }

  return inputDevicePlugInM->isActive();
}

//==============================================================================
//==============================================================================
inline bool InputController::shutdown()
{
  D_ENTER("PPL::InputController::shutdown()");
  RWPRECONDITION(inputDevicePlugInM);

  // tell the stream the request!
  return inputDevicePlugInM->shutdown();
}

inline bool InputController::install()
{
  D_ENTER("PPL::InputController::install()");
  RWPRECONDITION(inputDevicePlugInM);

  // tell the stream the request!
  return inputDevicePlugInM->install();
}

inline bool InputController::uninstall()
{
  D_ENTER("PPL::InputController::uninstall()");
  RWPRECONDITION(inputDevicePlugInM);

  // tell the stream the request!
  return inputDevicePlugInM->uninstall();
}

//==============================================================================
//==============================================================================
inline void InputController::requestAbort()
{
  D_ENTER("PPL::InputController::requestAbort()");
  RWPRECONDITION(inputDevicePlugInM);

  // tell the stream the request!
  inputDevicePlugInM->requestAbort();
  
  // stop myself!
  requestAbortM = true;
}

//==============================================================================
//==============================================================================
inline void InputController::writeModuleVersion() const
{
  D_ENTER("PPL::InputController::writeModuleVersion()");
  RWPRECONDITION(inputDevicePlugInM);

  inputDevicePlugInM->writeModuleVersion();
}

//==============================================================================
//==============================================================================
inline bool InputController::prepareCommit(const TAM::TransId& id)
{
  D_ENTER("PPL::InputController::prepareCommit(const TAM::TransId& id)");
  RWPRECONDITION(id.isValid());
  RWPRECONDITION(inputDevicePlugInM);

  return inputDevicePlugInM->prepareCommitIO(id);
}

//==============================================================================
//==============================================================================
inline bool InputController::commit(const TAM::TransId& id)
{
  D_ENTER("PPL::InputController::commit(const TAM::TransId& id)");
  RWPRECONDITION(id.isValid());
  RWPRECONDITION(inputDevicePlugInM);

  return inputDevicePlugInM->commitIO(id);
}

//==============================================================================
//==============================================================================
inline bool InputController::cancel(const TAM::TransId& id)
{
  D_ENTER("PPL::InputController::cancel(const TAM::TransId& id)");
  RWPRECONDITION(id.isValid());
  RWPRECONDITION(inputDevicePlugInM);

  return inputDevicePlugInM->cancelIO(id);
}

//==============================================================================
//==============================================================================
inline bool InputController::rollback(const TAM::TransId& id)
{
  D_ENTER("PPL::InputController::rollback(const TAM::TransId& id)");
  RWPRECONDITION(id.isValid());
  RWPRECONDITION(inputDevicePlugInM);

  return inputDevicePlugInM->rollbackIO(id);
}

//==============================================================================
//==============================================================================
inline bool InputController::activeState()
{
  return true;
}

//==============================================================================
//==============================================================================
inline bool 
InputController::processEdrContainer(EdrContainerList* /*edrList*/)
{
  return true;
}

inline EDR::Container*
InputController::createInternalContainer()
{
	EDR::Container* ptr = edrFactoryM->produceEDR(internalContainerIdxM);
	ptr->setCurrentPlugin(name());
	return ptr;
}

inline RWMutexLock& 
InputController::getRealtimeMutex()
{
	return realtimeMutexM;
}

inline bool 
InputController::isDeactive()
{
	return isDeactiveM;
}

inline void 
InputController::deactivate(bool flag)
{
	isDeactiveM = flag;
}

inline bool 
InputController::isRegUpdate()
{
	return isRegUpdateM;
}

inline void 
InputController::regUpdate(bool flag)
{
	isRegUpdateM = flag;
}

}
#endif // InputController_HPP

