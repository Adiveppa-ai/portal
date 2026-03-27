#ifndef PPL_PIPELINE_HPP
#define PPL_PIPELINE_HPP

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
//------------------------------------------------------------------------------
// Module Description:
//   Class implementation to handle an input file or stream pipeline
//
//------------------------------------------------------------------------------

// Revision: 10005  7.5      14-May-2012  Santanu 
// bug14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER
//
// Revision: 10004  7.4      23-Mar-2011  sumeemis
// Bug 11815646 - P-10434779 PHASE II CHANGES FOR PIPELINE PARALLEL LOADING ECR.

// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.2  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// Revision 1.1  2001/05/03 16:31:07  bt
// FRM modules moved to PPL (Format renamed to Pipeline).
//
// Revision 1.40  2001/04/25 14:25:39  bt
// Transaction manager added.
//
// Revision 1.39  2001/04/12 12:44:27  sd
// - Update for the new modules EDR::Base, FRM::Base and IXT
//
// Revision 1.38  2001/04/04 12:00:54  sd
// - Old stream interfaces removed
//
// Revision 1.37  2001/03/29 14:17:34  mliebmann
// Generic IO added
//
// Revision 1.36  2001/02/22 11:25:22  sd
// - Backup version
//
// Revision 1.35  2001/01/11 13:03:41  sd
// - First v4-30 check-in.
//
// Revision 1.34  2000/11/29 10:41:11  jkeckst
// add new registry item NetworkDestinationCode
//
// Revision 1.33  2000/09/29 10:11:17  aro
// Tried to fix doc++ comments.
//
// Revision 1.32  2000/09/26 12:43:59  bt
// EDR::Recycling added.
//
// Revision 1.31  2000/06/16 14:01:10  clohmann
// Changes for AIX compiler.
//
// Revision 1.30  2000/05/02 13:19:02  bt
// PR number 1811 fixed. Synchronize starting and stopping pipelines.
//
// Revision 1.29  2000/03/14 13:28:25  aro
// Removed double variable declaratiion; includes fixed.
//
// Revision 1.28  2000/03/08 14:30:24  clohmann
// Shutdown function added.
//
// Revision 1.27  2000/02/14 16:23:55  bt
// Function Control Interface Collection and method init() added.
//
// Revision 1.26  2000/01/18 07:55:02  jkeckst
// the newest changes for v4.0 (the new EDR-Container)
//
// Revision 1.25  1999/12/17 08:04:57  clohmann
// Events added.
//
// Revision 1.24  1999/11/10 13:02:47  clohmann
// CodeReview - 10.1999 - clohmann
//
// Revision 1.23  1999/10/20 14:54:16  bt
// Usability check added (method isUsable()).
//
// Revision 1.22  1999/08/17 07:49:52  bt
// Command CMD_DEACTIVATE added.
//
// Revision 1.21  1999/08/16 15:35:19  bt
// Function writeModuleVersion() added (PR integrate/520).
//
// Revision 1.17  1999/05/27 10:14:58  bt
// New registry entries and receiveRequest() method added.
//
// Revision 1.16  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.15  1999/05/06 17:28:20  aro
// CVS Recovery.
//
// Revision 1.1  1999/04/08 16:14:10  bt
// Initial version.
//
//==============================================================================


#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_REGISTRYENTRY_HPP
  #include "BAS/RegistryEntry.hpp"
#endif
#ifndef   BAS_OBJECT_H
  #include "BAS/Object.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   TAM_MANAGER_HPP
  #include "TAM/Manager.hpp"
#endif
#ifndef   PPL_FUNCCONTROLCOLLECTION_HPP
  #include "PPL/FuncControlCollection.hpp"
#endif
#ifndef   PLI_THREADINTERFACE_HPP
  #include "PLI/ThreadInterface.hpp"
#endif
#ifndef   PPL_OutputController_HPP
  #include "PPL/OutputController.hpp"
#endif
#ifndef   PPL_InputController_HPP
  #include "PPL/InputController.hpp"
#endif

#include "PLI/CommonLoadInterface.hpp"

namespace EDR
{
class Factory;
}
namespace FRM
{
class DataDescr;
}
namespace PPL
{

/** This class handles an input file or stream pipeline.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: Pipeline.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/2 $</font></td>
    <td><font size=-1>$Date: 2016/10/04 00:44:28 $</font></td>
    <td><font size=-1>$Author: skattepu $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/2 $</font></td>
    <td><font size=-1>$Date: 2016/10/04 00:44:28 $</font></td>
    <td><font size=-1>$Author: skattepu $</font></td>
    </tr>
    </table>

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>Active</dd>
    <dd>CountryCode</dd>
    <dd>MobileCountryCode</dd>
    <dd>NationalAccessCode</dd>
    <dd>InternationalAccessCode</dd>
    <dd>InternationalAccessCodeSign</dd>
    <dd>RejectStream</dd>
    <dd>InputBuffer</dd>
    <dd>OutputBuffer</dd>
    <dd>PipelineLog</dd>
    <dd>Output</dd>
    <dd>Functions</dd>
    <dd>Input</dd>
    <dt><b>Messages send</b></dt>
    <dd>CMD_WRITE_REGISTRY_FILE</dd>
    <dt><b>Messages receive</b></dt>
    <dd>MSG_STREAM_START</dd>
    <dd>MSG_STREAM_STOP</dd>
    <dd>CMD_WRITE_LOG</dd>
    <dd>CMD_START</dd>
    <dd>CMD_STOP</dd>
    <dd>CMD_DEACTIVATE</dd>
    <dt><b>Request send</b></dt>
    <dd>none</dd>
    <dt><b>Request receive</b></dt>
    <dd>REQ_CC</dd>
    <dd>REQ_MCC</dd>
    <dd>REQ_NAC</dd>
    <dd>REQ_NDC</dd>
    <dd>REQ_IAC</dd>
    <dd>REQ_IAC_SIGN</dd>
    <dd>REQ_REJECT_STREAM</dd>
    <dd>REQ_REJECT_STREAM_NAME</dd>
    <dt><b>Event send</b></dt>
    <dd>EVT_PIPELINE_START</dd>
    <dd>EVT_PIPELINE_STOP</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_REG_NAME_NOT_FOUND</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_REG_UPDATE_FAILED</dd>
    <dd>INF_ABORT_REQUESTED</dd>
    <dd>INF_PIPELINE_START</dd>
    <dd>INF_PIPELINE_STOP</dd>
</dl>
*/
class Pipeline : public BAS::Object, public PLI::CommonLoadInterface
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      Pipeline();

      /** Constructs an instance to handle an input file or stream pipeline.<br>
        * @param objectName The string is used for the object registration. */
      Pipeline(const BAS::String& objectName);

      /** Constructs an instance to handle an input file or stream pipeline.<br>
        * @param objectName The string is used for the object registration.
        * @param baseParallelLoadMgr Parallel load manager pointer passed from base.*/
      Pipeline(const BAS::String& objectName,PLI::ParallelLoadManager *baseParallelLoadMgr);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~Pipeline();

    //@}

    /**@name Public Member Functions */
    //@{

      /** Init function which will be called
        * to initialize the pipeline interfaces. */
      virtual bool init();

      /** Shutdown function which will be called
        * to shutdown the pipeline interfaces. */
      virtual bool shutdown();

  bool install();

  bool uninstall();

  bool startup();

    /** Returns the status of isReadyM flag
     *  that is set once pipleline->start() is called
     *  and unset once pipeline->stop is called. */
    bool isReady();

   /** Returns the status of restartPipelineM flag
     *  that is set to false when pipeline server shutting down */
    bool isRestartable();

      /// Start the input pipeline.
      virtual void start(bool flagRegUpdate=false);

      /// Stop the input pipeline.
      virtual void stop(bool flagRegUpdate=false);

      /// Deactivate the input pipeline.
      virtual void deactivate();

      /// Returns the state of the input pipeline.
      virtual bool isActive();

      /// Returns true when pipeline is deactivated.
      virtual bool isDeactive();

      /// Check the usability of the pipeline modules.
      virtual bool isUsable();

      /// Returns the state of the pipeline interfaces.
      virtual bool interfacesValid();

      /// Request an abort to perform the next shut down immediately.
      virtual void requestAbort();

      /// Write the version of the pipeline modules.
      virtual void writeModuleVersion() const;

      /// Write the status of EDR queues into the pipeline log.
      virtual void writeQueueStatus() const;

      /** Routine to process incoming messages.
        * @param msg The incoming message. */
      virtual void receiveMessage(const BAS::Message& msg);

      /** Routine to process incoming requests.
        * When the request can not be served,
        * all argument list items will be removed.
        * @param msg The request message (in/out parameter). */
      virtual void receiveRequest(BAS::Message& msg);

      /** Routine to update the state of the input pipeline.
        * @param updateRegistry The registry tree with values to be updated.
  * @param workedOn reference to set to true if anything was changed.
  */
      virtual bool registryUpdate(const BAS::RegistryEntry* updateRegistry,
                                  BAS::ProtectedBool&       workedOn);

     /** Get a pointer to the edr container factory */
     EDR::Factory* edrFactory();

     /** Set the restartPipelineM flag.
       * @param val if false pipeline is shutting down. */
     virtual void restartPipeline(const bool val);
     /** Cancel all the transactions
       */
     bool cancelAllTransactions();

     /** Common functionality between public constructors
       */
     void commonConstructionFunc();

     /** Common Init
     */

     virtual bool commonInit();

     virtual bool validity();

     /** Loading FCI Collection batch to parallel load manager
     */

     void addFCIColInitBatch();
     /** Create a local edr factory
      * @param edrFactory The reference to the edr factory created
      * @return @return <b>true</b> on success, <b>false</b>
      */
     bool createEdrFactory(EDR::Factory *& edrFactory ,  const BAS::String &); 

     /** Add an entry in the registry for EDR factory
      *  @edrFactoryName The name of the EDR factory
      *  @return <b>true</b> on success, <b>false</b>
      */
     bool makeEdrFactoryRegEntry(BAS::String &edrFactoryName);

#ifdef __aix
      // operator for AIX
      bool operator==(const Pipeline& right) const { return true; }
      bool operator<(const Pipeline& right) const { return true; }
#endif


       RWTValOrderedVector<BAS::String> getRegisteredPluginNames();

    //@}

  private:

    // The following private attributes and functions are used internally.

      STR::Queue<EDR::Container*>* inputQueueM;

      STR::Queue<EDR::Container*>* outputQueueM;

      BAS::RegisteredObject* pipelineLogM;

      EDR::Factory* edrFactoryM;

      FRM::DataDescr* dataDescrM;

      PLI::ThreadInterface* logInterfaceM;

      TAM::Manager* transactionManagerM;

      OutputController* outputDeviceInterfaceM;

      FuncControlCollection* fciCollectionM;

      InputController* inputDeviceInterfaceM;

      const BAS::RegistryEntry* registrySubTreeM;

      bool isStreamActiveM;

      RWMutexLock isStreamActiveLockerM;

      bool isActiveM;

      RWMutexLock isActiveLockerM;

      bool startInProgressM;

      bool stopInProgressM;

      RWMutexLock startStopLockerM;

      BAS::String countryCodeM;

      BAS::String mobCountryCodeM;

      BAS::String natAccessCodeM;

      BAS::String intAccessCodeM;

      BAS::String intAccessCodeSignM;

      BAS::String netDestCodeM;

      BAS::String rejectStreamNameM;

      BAS::String rejectStreamNumberM;

      BAS::String eventHandlerNameM;

      // This is to reflect the state of pipeline
      // isReadyM is true only at the end of pipeline->start()
      bool isReadyM;

      // Flag to distinguish a pipeline start event after a registry update and otherwise
      bool setRegUpdateFalseM;

      RWMutexLock isReadyLockerM;

      // restartPipelineM is set to false when pipeline server shutting down
      bool restartPipelineM;

      RWMutexLock restartLockerM;

    // Read the configuration values out of the registry.

      virtual bool readRegistry();

    // Read the configuration values from other objects.

      virtual bool evalEnvironment();

    // Write the not usable error message to the pipeline log.

      void logNotUsableMessage(const BAS::String& objectName);

    // Create the pipeline log object.

      bool createPipelineLog();

    // Create the input queue object.

      bool createInputQueue();

    // Create the output queue object.

      bool createOutputQueue();

    // Create the transaction manager object.

      bool createTransactionManager();

    // Create the output stream interface object.

      bool createOutputDeviceInterface();

    // Create the function control interface collection.

      bool createFciCollection(ThreadBase *& firstFunctionController,PLI::ParallelLoadManager *baseParallelLoadMgr);

    // Create the input stream interface object.

      bool createInputDeviceInterface(ThreadBase * firstFunctionController);

    // Configuration for the use of the pipeline in one or multi-threadmode (Registry-key)
      PPL_EXPORT static const BAS::String registryMultiThreadedCM;

    // Configuration for the use of the pipeline in one or multi-threadmode
      bool multiThreadedM;

    // Configuration for the use of the pipeline in one or multi-threadmode (Registry-key)
      PPL_EXPORT static const BAS::String registryNoOutputUsedCM;

    // Configuration for the use of the pipeline in one or multi-threadmode
      bool noOutputUsedM;

    // Configuration for the use of the pipeline in one or multi-threadmode (Registry-key)
      PPL_EXPORT static const BAS::String edrFactoryNameCM;

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.
      Pipeline(Pipeline& right);
      const Pipeline& operator=(Pipeline& right);

};

//------------------------------------------------------------------------------
// Returns a pointer to the edr container factory
//------------------------------------------------------------------------------

inline EDR::Factory*
Pipeline::edrFactory()
{
  return edrFactoryM;
}
}
#endif // PIPELINE_HPP

