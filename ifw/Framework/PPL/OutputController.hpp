#ifndef PPL_OutputController_HPP
#define PPL_OutputController_HPP

// @(#)$Id: OutputController.hpp /cgbubrm_7.5.0.pipeline/2 2012/06/21 03:56:34 sknanda Exp $ 
//==============================================================================
//
// Copyright (c) 1996, 2023, Oracle and/or its affiliates. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PPL
//------------------------------------------------------------------------------
// Module Description:
//   Class implementation to handle an input file or stream pipeline
//
//------------------------------------------------------------------------------
// Revision 1.21 2012/05/14 Santanu 
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER  
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.20  2002/03/13 10:53:59  mliebmann
// PETS #39719 sequencer mod for Rap/Tap: backup for ClearCase migration
//
// Revision 1.19  2001/12/20 09:26:21  mliebmann
// PETS #41864 Recycle Plugin: Parameter RecycleTest, output Controller get no status
//
// Revision 1.18.2.1  2001/11/28 11:12:22  mliebmann
// PETS #41864 Recycle Plugin: Parameter RecycleTest, outputcontroller gets not status
//
// Revision 1.18  2001/11/27 11:23:50  mliebmann
// PETS #41918 missing include file - not compileable
//
// Revision 1.17  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// Revision 1.16  2001/09/26 10:28:00  sd
// - PETS #39870 EDR::Statistic should not be part of module EDR
//
// Revision 1.15  2001/09/26 09:20:02  mliebmann
// PETS #39834 IFW_EDRSEQLOG.RECYCLING is now set to the TAM::RECYCLE field of the corresponding streamname
//
// Revision 1.14  2001/07/09 11:17:13  mliebmann
// PETS #36697 check of the edr-container is fixed, if an endTransaction-container follow directly on a beginTransaction-container
//
// Revision 1.13  2001/06/27 06:35:45  mliebmann
// releaseEdr(..) moved and some additional changes based on the first!
//
// Revision 1.12  2001/06/15 14:06:51  mliebmann
// TAMs isactive-method added
//
// Revision 1.11  2001/06/01 08:24:09  mliebmann
// workaround for the sequencer
//
// Revision 1.10  2001/05/29 13:04:57  mliebmann
// streamlog-file generation fixed
//
// Revision 1.9  2001/05/18 13:05:34  mliebmann
// LogError(EDR::Container *) moved into PLG::OutputDevice / bug fixed in destructor -> streamLogM was not initialized by default with 0
//
// Revision 1.8  2001/05/15 15:22:05  mliebmann
// registry switch SequenceGeneration changed perFile/perTransaction to Unit/Transaction
//
// Revision 1.7  2001/05/14 10:05:41  mliebmann
// registry parameter AppendSeqeunceNumber deleted
//
// Revision 1.6  2001/05/11 12:19:22  mliebmann
// error handling fixed
//
// Revision 1.5  2001/05/11 09:09:19  mliebmann
// error messages added/corrected
//
// Revision 1.4  2001/05/09 14:47:53  mliebmann
// fixed multiple input-streams to one output-stream / parameter SequenceGeneration added
//
// Revision 1.3  2001/05/08 14:52:15  mliebmann
// new TAM::TransItem added or TAM::TransType eliminated
//
// Revision 1.2  2001/05/04 09:17:37  bt
// Method writeToPipelineLog() changed.
//
// Revision 1.1  2001/05/03 16:31:07  bt
// FRM modules moved to PPL (Format renamed to Pipeline).
//
// Revision 1.11  2001/05/02 10:49:18  sd
// - Input stream plugin no longer needed in v4-30
//
// Revision 1.10  2001/04/26 09:23:26  mliebmann
// GenericIO: TAM added
//
// Revision 1.9  2001/04/25 14:25:39  bt
// Transaction manager added.
//
// Revision 1.8  2001/04/11 10:14:35  mliebmann
// Generic IO: little changes and documentation added
//
// Revision 1.7  2001/04/09 14:26:05  mliebmann
// Generic IO: changes
//
// Revision 1.6  2001/04/05 15:12:18  mliebmann
// Generic IO: updated
//
// Revision 1.3  2001/03/29 14:17:34  mliebmann
// Generic IO added
//
// Revision 1.2  2001/03/23 15:08:10  mliebmann
// GenericIO - only backup
//
// Revision 1.1  2001/03/21 09:39:11  mliebmann
// only for backup
//
//
//==============================================================================

#ifndef   EDR_FACTORY_HPP
  #include "EDR/Factory.hpp"
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
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   PLI_THREADINTERFACE_HPP
  #include "PLI/ThreadInterface.hpp"
#endif
#ifndef   PPL_OutputCollection_HPP
  #include "PPL/OutputCollection.hpp"
#endif
#ifndef   LOG_STREAMDATE_HPP
  #include "LOG/StreamDate.hpp"
#endif
#ifndef   TAM_MANAGERIF_HPP
  #include "TAM/ManagerIf.hpp"
#endif
#ifndef   TAM_MODULEIF_HPP
  #include "TAM/ModuleIf.hpp"
#endif
#ifndef   TAM_TRANSID_HPP
  #include "TAM/TransId.hpp"
#endif
#ifndef   PLG_STATISTIC_HPP
  #include "PLG/Statistic.hpp"
#endif
#ifndef   PPL_PIPELINE_HPP
  #include "PPL/Pipeline.hpp"
#endif
#ifndef  PPL_EDRTRACE_HPP
  #include "PPL/EdrTrace.hpp"
#endif

#include <rw/bitvec.h>

namespace PPL
{
/** <tt><b>class OutputController</b></tt><br>
    handles an input file or stream pipeline.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: OutputController.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/2 $</font></td>
    <td><font size=-1>$Date: 2012/06/21 03:56:34 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    <td><font size=-1>$RCSfile: OutputController.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/2 $</font></td>
    <td><font size=-1>$Date: 2012/06/21 03:56:34 $</font></td>
    <td><font size=-1>$Author: sknanda $</font></td>
    </tr>
    </table>                     

    <dl>
      <dt><b>Registry entries</b></dt>
      <dd>MaxErrorRates</dd>
      <dd>OutputCollection</dd>
      <dd>OutputLog</dd>
      <dd>Sequencer (optional)</dd>
      <dt><b>Messages send</b></dt>
      <dd>CMD_STOP</dd>
      <dd>MSG_STREAM_STOP</dd>
      <dt><b>Messages receive</b></dt>
      <dd>none</dd>
      <dt><b>Request send</b></dt>
      <dd>none</dd>
      <dt><b>Request receive</b></dt>
      <dd>none</dd>
      <dt><b>Event send</b></dt>
      <dd>none</dd>
      <dt><b>Errors</b></dt>
      <dd>ERR_CANNOT_INIT_OUTPUT_COLLECTION</dd>
      <dd>ERR_ILLEGAL_STREAM_NUM</dd>
      <dd>ERR_INVALID_STATE</dd>
      <dd>ERR_NOT_USABLE</dd>
      <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
      <dd>ERR_UNKNOWN_CONTAINER_TYPE</dd>
      <dd>ERR_UNKNOWN_CONTENT_TYPE</dd>
      <dd>WRN_NO_ENDTRANSACTION</dd>
      <dd>INF_PIPELINE_NOT_MULTITHREADED</dd>
      <dd>ERR_REG_NAME_NOT_FOUND_SETTING_DEFAULT</dd>
      <dd>ERR_CONVERSION_INT</dd>
      <dd>ERR_CREATE_THREAD_FAILED</dd>
      <dd>ERR_NO_EDRFACTORY</dd>
      <dd>ERR_EDR_FACTORY_CREATION_FAILED</dd>
    </dl> 
*/
class OutputController : public ThreadBase , public TAM::ModuleIf
{
  D_SINGLETHREADED

  public:

    /** State enumeration.
    */
    enum State
    {
      STARTED = 0,
      TRANSSTARTED,
      BEGINNING,
      PROCESSING,
      ENDED,
      TRANSENDED,
      STOPPED 
    };

    //========================================= 
    //Status indicating the flow of EDR(s)
    //from the main OutputController thread
    //to the worker threads, when multithreading
    //feature is enabled.
    //==========================================
    enum EdrFlowStatus
    {
      FLOW_STARTED = 0,
      FLOW_ENDED,
      FLOW_COMPLETED
    };

    //========================================= 
    //Structure used by worker threads
    //when multithreading feature is enabled.
    //==========================================
    struct WorkerThreadInfo
    {
       EDR::Factory * factoryM;
       size_t curWorkItemIndexM;
       RWMutexLock workerThreadInfoLockM;
       
       WorkerThreadInfo(): factoryM(0), curWorkItemIndexM(0) {}
            
       ~WorkerThreadInfo()
       {
         delete factoryM;
       }
    };

    //=============================================
    //Structure encapsulating an EDR along with
    //some additional information used by worker
    //threads when multithreading feature is 
    //enabled.
    //=============================================
    struct WorkItem 
    {
       //Constructor and Desctructor
       WorkItem(const size_t outputCollectionSize,EDR::Container* edr);
       ~WorkItem();

       //Data funtions
       void reset(EDR::Container* edr);
       void cacheSucc(WorkItem * item);
       WorkItem * cacheSucc()const;

       //Data Members
       EDR::Container *  edrM;
       RWMutexLock  accessLockM;
       RWMutexLock duplicateLockM;
       RWCondition duplicateCondM;
       size_t duplicatesReqdM;
       bool finishedM;
       RWBitVec * streamProgressIndM; //Bit map for the streams to be written for this item
       WorkItem * cacheSuccM;
    };

    //=========================================
    //Cache of WorkItem(s).
    //=========================================
    class WorkItemCache
    {

       public:

         //Constructor and Destructor
         WorkItemCache(const size_t);
         ~WorkItemCache();

         WorkItem * getItem(EDR::Container* edr);
         void insertItem( WorkItem* item);

       private:

         WorkItem * inCacheM; 
         WorkItem * outCacheM;
         const size_t totalStreamCountM;
    };

    //========================================= 
    //Structure used by worker and writer threads
    //when multithreading feature is enabled.
    //==========================================
    struct WriterThreadInfo
    {
      RWMutexLock writeLockM;
      RWCondition writeCondM;
      RWTValOrderedVector <size_t> itemIndexListM; 
      STR::Queue<EDR::Container*> * writerThreadQueueM;
      int edrsQueuedM;
      int edrsWrittenM;

      WriterThreadInfo();
      ~WriterThreadInfo();
      
      void resetEdrCounters();
   };   

    
    
    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      OutputController();

      /** Constructs an instance to handle an input file or stream pipeline.<br> 
        * @param objectName The string is used for the object registration. */
      OutputController(const BAS::String& objectName,
                           STR::Queue<EDR::Container*> * queue,
                           TAM::ManagerIf * managerIf);

      OutputController(const BAS::String& objectName,
                           TAM::ManagerIf * managerIf);
    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~OutputController();

    //@}

    /**@name Public Member Functions */
    //@{
      /** Excute-Thread.
        * Executed if queues are used.
        * See: ThreadBase.
        */
      void execute();
      
      /** Executes a list of edr to the output-Devices.
        * Is executed with one thread for the whole pipeline.
        * See: ThreadBase.
        * @param EdrContainerList* EDRList of processable EDRs.
        * @return <tt>true</tt> usable,<br>
        *         <tt>false</tt> not usable.
        */
      bool processEdrContainer(EdrContainerList* edrList);

      /** Shows the usability.
        * @return <tt>true</tt> usable,<br>
        *         <tt>false</tt> not usable. */
      virtual bool isUsable();

      /// Shows the moduleversion of the Modules in the collection.
      virtual void writeModuleVersion() const;
      
      /// Shows the system shutdown.
      virtual bool shutdown();

	virtual bool install();

	virtual bool uninstall();

	virtual bool startup();
      
      /** Show the emmidiate abort of the system without wait of 
        * the endtransaction. */
      virtual void requestAbort();
      
      /// Update the statistic about the written/released EDRs
      virtual void countEdr(EDR::Container * edr);

      /** Return the number of records processed without errors
        * @return the number of records processed without errors
        */
      int64 getNumberOfRecordsOut() const;

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

      /** Checks if multithreaded options is enabled.
        * @return <tt>true</tt> enabled,<br>
        *         <tt>false</tt> disabled. */
      bool isMultiThreaded();

     //*}
    
  protected:
  
    virtual void writeToStreamLog(const BAS::Status& s) const;

    /** 
    */
    virtual bool checkState(const State stat) const;

    /** 
    */
    virtual State state() const;

    /** 
    */
    virtual void state(const State newState);

    /** 
    */
    virtual void writeEdrTraceLog(EDR::Container* edr);

  private:

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
    OutputController(OutputController& right);
    const OutputController& operator=(OutputController& right);

	bool isStreamLogDisabled() const;

    void initInternal(); // not virtual, should never be overwritten! Contructor-help!
    
    virtual bool readRegistry();
    bool readMultiThreadingBlock(BAS::RegistryEntry* myEntry);
    virtual bool registryUpdate(const BAS::RegistryEntry* updateRegistry,
                                BAS::ProtectedBool&       workedOn);
    virtual bool evalEnvironment();
    virtual bool setEDRContainerIndices();
    virtual void receiveRequest(BAS::Message& msg);

    virtual bool checkForSystemError(const EDR::Container * edr);

    virtual void edrToStream(EDR::Container* edr);
    virtual bool processServiceContainer(EDR::Container* edr);
    virtual void processDataContainer(EDR::Container* edr);
    virtual void processHeaderContainer(EDR::Container* edr);
    virtual void processDetailContainer(EDR::Container* edr);
    virtual void processTrailerContainer(EDR::Container* edr);
    virtual void processBeginTransactionContainer(EDR::Container* edr);
    virtual void processEndTransactionContainer(EDR::Container* edr);
    virtual bool processBeginContainer(EDR::Container* edr);
    virtual bool processEndContainer(EDR::Container* edr);
    virtual void processStartContainer(EDR::Container* edr);
    virtual void processStopContainer(EDR::Container* edr);

    // Construction methods.
    virtual bool createOutputCollection();
    virtual bool createLog();
    virtual bool createEdrTrace();
    virtual void notifyEdrTraceModeChange();

    virtual int64 rejectStream();
    
    void waitForWorkersToFinish();
    void signalWorkerDone();

    void waitForProcessingToFinish();
    void signalProcessingStart();

    void workerThreadExecute();
    void writerThreadExecute(const int queueIndex);
  
    WorkerThreadInfo * getWorkerThreadInfo();
    
    void insertIntoWorkingCache(WorkItem * itemToWrite);
    void cleanUp();

    WorkItem * getNewItem(EDR::Container * edr);
    void removeProcessedItems(const size_t maxIndexToCheck);

    size_t minWorkItemIndex();
    void resetThreadIndexes();

    void doPreProcessing();
    void doPostProcessing();
    
    void putEdrToWriterQueue( WorkerThreadInfo * curThreadStruct, EDR::Container * edr );
    STR::Queue<EDR::Container*> * getQueueForWriterThread(const int queueIndex);

    void waitForStreamToBeFree(WorkerThreadInfo * curThreadStruct, size_t stream);
    void logThreadInfo(const char * suffix, const bool);
    BAS::RegisteredObject* getPipelineRegObj();
    void createMultiThreadingEngine();
   
    TAM::ManagerIf*                              managerIfM;

    TAM::TransId*                                curTransIdM;
    
    // The following private attributes and functions are used internally.
    bool validM;
    
    OutputCollection *                      outputCollectionM;

    // Statistic counter object.
    PLG::Statistic                               counterM;

    EDR::Factory*                                edrFactoryM;

    // number of defined output streams
    size_t                                      numberOfOutputDevicesM;
    size_t edrCountM;

    // Stream logger object.
    LOG::StreamDate *                            streamLogM;
    PPL::EdrTrace*                               edrTraceM;
    bool                                         edrTraceEnabledM;

    // Object state indicator.
    State                                       stateM;

    // The actual streamName.
    BAS::String                                 curStreamNameM;

    // the actual checkKey, if sequencer is used!
    BAS::String                                 curCheckKeyM;

    bool                                        edrSequenceGenerationPerUnitM;
    bool                                        firstHeaderProcessedM;
    bool                                        firstBeginProcessedM;
	bool                                        disableStreamLogM;
    EDR::Container                             * lastTrailerContainerM;
    EDR::Container                             * lastEndContainerM;
        
	PPL_EXPORT static const BAS::String         streamLogDisabledCM;
    PPL_EXPORT static const BAS::String         outputCollectionCM;
    PPL_EXPORT static const BAS::String         streamLogCM;
    PPL_EXPORT static const BAS::String         maxErrorRatesCM;
    PPL_EXPORT static const BAS::String         systemErrorCM;
    PPL_EXPORT static const BAS::String         registryPipelinesCM;
    PPL_EXPORT static const BAS::String         registrySequenceGenerationCM;
    PPL_EXPORT static const BAS::String         registrySequenceHandlerCM;
    PPL_EXPORT static const BAS::String         registrySequencerPoolCM;
    PPL_EXPORT static const BAS::String         edrTraceCM;
    PPL_EXPORT static const BAS::String         edrTraceEnabledCM;
    PPL_EXPORT static const BAS::String         totalDuplicateThreadsCM;
    PPL_EXPORT static const BAS::String         multiThreadedCM;
    PPL_EXPORT static const BAS::String         enableMultiThreadedCM;
    PPL_EXPORT static const BAS::String         noOfThreadsCM;
    PPL_EXPORT static const BAS::String         bufferSizeCM;

    
    bool                                        requestAbortM;

    EDR::Index                                  streamTransIdIdxM;
    EDR::Index                                  streamNameIdxM;
    EDR::Index                                  headerOriginSequenceNumberIdxM;
    EDR::Index                                  seqCheckIdxM;
    EDR::Index                                  seqCheckKeyIdxM;
    EDR::Index                                  seqGenIdxM ;
    EDR::Index                                  offsetGenIdxM;
    EDR::Index                                  processStatusIdxM;
    
    int64                                        rejectStreamM;

    // Sequence Handler object.
    PLG::Sequencer *      sequencerM;

    // indicates if the sequencer object is needed or not
    bool                 sequencerNeededM;

   // Process Status indicates whether Recycling is on or not

    typedef TAM::TransItem ProcessStatus;

    /** Enumeration process status.
      * <ul>
      * <li> NORMAL        = 0
      * <li> RECYCLE       = 1
      * <li> RECYCLE_TEST  = 2
      * </ul> */
    typedef ProcessStatus::ItemTypeT processStatusT;

    processStatusT processStatusM; 

    //======================================
    //The following variables are used when
    //multithreading is enabled.
    //======================================
    EdrFlowStatus edrFlowStatusM;
    RWMutexLock edrFlowStatusLockM;
    RWCondition edrFlowStartedCondM;

    size_t workerThreadsDoneCountM;
    RWMutexLock workerThreadsDoneLockM;
    RWCondition workerThreadsDoneCondM;

    WriterThreadInfo * writerThreadInfoListM;
    RWTPtrOrderedVector<BAS::Thread> writerThreadPoolM;    

    RWTPtrOrderedVector<WorkerThreadInfo> workerThreadInfoListM;
    RWTPtrOrderedVector<BAS::Thread> workerThreadPoolM;
    
    WorkItemCache * workItemCacheM;
    
    RWTPtrOrderedVector<WorkItem> workingCacheM; //Intermediary Vector

    size_t lastRemovedItemIndexM;
    bool shutdownM;
    bool pipelineMultiThreadedM;

    //The following members are read from registry
    bool multiThreadedWriteM;
    size_t totalWorkerThreadsM;
    bool batchModeEnabledM;
    size_t batchSizeM;

    //TODO:: Remove the following two after testing.
    time_t txtStTime;
    time_t txnEndTime;
};

//------------------------------------------------------------------------------
// Inlines
//------------------------------------------------------------------------------

inline bool 
OutputController::checkState(const State stat) const
{
  D_ENTER("PPL::OutputController::checkState(const State stat) const");
  return (stateM == stat);
}

//------------------------------------------------------------------------------

inline void
OutputController::state(const State stat)
{
  D_ENTER("PPL::OutputController::state(const State stat)");

  stateM = stat;
}

//------------------------------------------------------------------------------

inline OutputController::State
OutputController::state() const
{
  D_ENTER("PPL::OutputController::state()");
  return stateM;
}

//------------------------------------------------------------------------------

inline void 
OutputController::writeToStreamLog(const BAS::Status& s) const
{
	D_ENTER("PPL::OutputController::writeToStreamLog(const BAS::Status& s)");
	if (!isStreamLogDisabled())
	{
		streamLogM->write(s);
	}
}

//------------------------------------------------------------------------------

inline void OutputController::writeModuleVersion() const
{
  D_ENTER("PPL::OutputController::writeModuleVersion()");
  RWPRECONDITION(outputCollectionM);

  outputCollectionM->writeModuleVersion();
}

//------------------------------------------------------------------------------

inline bool OutputController::shutdown()
{
  D_ENTER("PPL::OutputController::shutdown()");
  RWPRECONDITION(outputCollectionM);
  
  // tell the stream the request!
  if (outputCollectionM->shutdown() == false)
  {
    setStatus(outputCollectionM->status());
    isValid(false);
  }

  D_RETURN(isValid());
  return isValid();
}

inline bool OutputController::install()
{
  D_ENTER("PPL::OutputController::install()");
  RWPRECONDITION(outputCollectionM);
  
  if (outputCollectionM->install() == false)
  {
    setStatus(outputCollectionM->status());
    isValid(false);
  }

  D_RETURN(isValid());
  return isValid();
}

inline bool OutputController::uninstall()
{
  D_ENTER("PPL::OutputController::uninstall()");
  RWPRECONDITION(outputCollectionM);
  
  // tell the stream the request!
  if (outputCollectionM->uninstall() == false)
  {
    setStatus(outputCollectionM->status());
    isValid(false);
  }

  D_RETURN(isValid());
  return isValid();
}

//------------------------------------------------------------------------------

inline void OutputController::requestAbort()
{
  D_ENTER("PPL::OutputController::requestAbort()");
  // stop myself!
  requestAbortM = true;
}

inline bool OutputController::activeState()
{
  return true;
}

inline int64
OutputController::getNumberOfRecordsOut() const
{
  D_ENTER("PPL::OutputController::getNumberOfRecordsOut()");
  return (counterM.edrDetCount() - counterM.edrErrCount());
}

inline bool
OutputController::isStreamLogDisabled() const
{
	return disableStreamLogM;
}

inline bool
OutputController::isMultiThreaded()
{
  return multiThreadedWriteM;
}
}

#endif // OutputController_HPP

