#ifndef PPL_PIPELINECOLLECTION_HPP
#define PPL_PIPELINECOLLECTION_HPP
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
//   PipelineCollection class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: bt
//
// $RCSfile: PipelineCollection.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $ 
// $Author: skattepu $ 
// $Date: 2016/10/04 00:44:28 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: PipelineCollection.hpp,v $
// Revision 1.17  2011/03/24 21:41:39 sm
// Progapagation of Phase - II changes for pipeline parallel loading ECR.
//
// Revision 1.2  2001/05/04 09:17:03  bt
// CMD_WRITE_LOG entry removed.
//
// Revision 1.16 2010/07/09 Santanu
// Bug9871778 Added the function invalidateActivities
// Revision 1.1  2001/05/03 16:31:07  bt
// FRM modules moved to PPL (Format renamed to Pipeline).
//
// Revision 1.15  2000/09/29 10:11:17  aro
// Tried to fix doc++ comments.
//
// Revision 1.14  2000/05/02 13:19:02  bt
// PR number 1811 fixed. Synchronize starting and stopping pipelines.
//
// Revision 1.13  2000/03/14 13:28:26  aro
// Removed double variable declaratiion; includes fixed.
//
// Revision 1.12  2000/02/14 16:23:55  bt
// Function Control Interface Collection and method init() added.
//
// Revision 1.11  1999/09/08 12:28:22  bt
// Implementation changed to support the egcs release 1.1.2 compiler.
// Class STR::InputFile modified to synchronize start() and inactiveLoop().
// If start() is called prior to inactiveLoop(), inactiveLoop() will hang.
//
// Revision 1.10  1999/08/16 15:37:39  bt
// Function writeQueueStatus() added (PR integrate/519).
// Function writeModuleVersion() added (PR integrate/520).
//
// Revision 1.8  1999/05/18 09:29:02  bt
// Registry entries changed.
//
// Revision 1.7  1999/05/06 17:28:22  aro
// CVS Recovery.
//
// Revision 1.1  1999/04/12 11:43:15  bt
// Initial version.
//
//==============================================================================

#ifndef   RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef   COLLECTION_HPP
  #include "BAS/Collection.hpp"
#endif
#ifndef   BAS_CONTROLLERIF_H
  #include "BAS/ControllerIf.hpp"
#endif
#ifndef   PPL_PIPELINE_HPP
  #include "PPL/Pipeline.hpp"
#endif

#include "PLI/ParallelLoadManager.hpp"

//------------------------------------------------------------------------------
// Explicit instantiation of base class BAS::OnlyPointer
//------------------------------------------------------------------------------

#ifndef INC_TEMPL_DEFS
namespace BAS
{
  template class OnlyPointer<PPL::Pipeline>;
}
#endif
namespace PPL
{

/** This class represents a collection of input pipelines.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: PipelineCollection.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2016/10/04 00:44:28 $</font></td>
    <td><font size=-1>$Author: skattepu $</font></td>
    </tr>
    </table>                     

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>Pipelines</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>INF_START_PIPELINE_WAIT</dd>
    <dd>INF_STOP_PIPELINE_WAIT</dd>
    <dd>INF_INPUT_BUFFER_STATUS</dd>
    <dd>INF_OUTPUT_BUFFER_STATUS</dd>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_INVALID_REG_BASE_NAME</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
</dl> 
*/
typedef RWTValMap<BAS::String, size_t, less<BAS::String> >   PipelineInstancesMap;

typedef RWTValSlist<BAS::String> RegistryNameList;

typedef RWTValMap<BAS::String, RegistryNameList*, less<BAS::String> >  PipelineRegistryMap;

typedef RWTValSlist<BAS::String> PipelineNameList;

class PipelineCollection : public BAS::Collection<Pipeline>,
							   public BAS::ControllerIf
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      PipelineCollection();

      /** Constructs a collection of input pipelines.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      PipelineCollection(const BAS::String& objectName);

     /** Constructs a collection of input pipelines.<br>
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it.
        * @param baseParallelLoadMgr Parallel load manager pointer passed
        * from Base. */
      PipelineCollection(const BAS::String& objectName,PLI::ParallelLoadManager *baseParallelLoadMgr);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~PipelineCollection();

    //@}

	/**@name ControllerIf Functions
	 */
	//@{
	/**  Start all input pipelines.
	 * This starts up the threads associated with the pipelines, and then calls
	 * the start function which actually makes them 'go'. 
	 */
	virtual bool startup();
	
	/** Install
	 */
	virtual bool install();

	/** Uninstall
	 */
	virtual bool uninstall();

	/** Shutdown
	 */
	virtual bool shutdown();

	//@}

    /**@name Public Member Functions */
    //@{

	/** Start the pipelines.
	 * This is different from 'startup' which is an intialization method
	 * designed to create the intial startup state. Start itself just makes
	 * the pipelines "go" and is the converse to "stop"
	 */
	virtual bool start(bool flag=false);

      /// Init function which will be called to initialize all input pipelines.
      virtual bool init();

      ///  Stop all input pipelines.
      virtual bool stop(bool flag=false);

      /// Deactivate all input pipelines.
      virtual void deactivate();

      /// Returns the state of all pipeline interfaces.
      virtual bool interfacesValid();

      /// Write the version of all pipeline modules.
      virtual void writeModuleVersion() const;

      /// Write the status of EDR queues into the pipeline log.
      virtual void writeQueueStatus() const;

      /// Immediate shut down of all input pipelines.
      virtual void immediateShutdown();

      /// set restart pipeline state for every pipeline 
      virtual void restartPipelines(const bool val);

      /// Invalidating activities.
      void invalidateActivities();

      /** Adding pipeline initialization batch to
          Parallel load manager
      */ 
      void addPipelineInitBatch();

      /** Adding pipeline construction batch to
          Parallel load manager
      */
      void addPipelineConstructionBatch();

    //@}

  private:

    // The following private attributes and functions are used internally.

    /**a special internal class to support parallel pipeline construction
    */

    class PipelineConstructor : public PLI::CommonLoadInterface
    {
        public:
          PipelineConstructor();
          PipelineConstructor(const BAS::String& objectName);

          /** Common Init
           */

          virtual bool commonInit();

          virtual bool validity();

          void pipelineName(const BAS::String & pipelineName);
          void pipelineCollection ( PipelineCollection * );
          const BAS::String & pipelineName();


        private:
           BAS::String pipelineNameM;
           PipelineCollection * pPipelineColM;
    };

    // Stop the input pipelines.

      void stopPipelines(bool flagRegUpdate=false);

    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      PipelineCollection(PipelineCollection& right);

      const PipelineCollection& operator=(PipelineCollection& right);
	
	/** State variable to determine if the pipelines have already started.
	 * So we don't start twice!
	 */
	bool hasStartedM;

    /** Map of pipeline name to number of instances 
     */
    PipelineInstancesMap   pipelineInstancesMapM;

    /** List of pipeline names in 'Pipelines' section of registry file
     */
    PipelineNameList       pipelineNameListM;

    /** Map of pipeline name to instance specific registry name list 
     */
    PipelineRegistryMap    pipelineRegistryMapM; 

    /** Flag of multi-instance support for given pipeline
     */
    bool hasInstancesM;

    /** Populate data into pipelineInstancesMap and pipelineRegistryMap
     */
    bool readInstancesInfo(const BAS::RegistryEntry* regEntry);   

    /** Create registry sub-tree for a given instance
     */ 
    void createInstanceRegistry(const BAS::RegistryEntry* registry, size_t instanceId);    

    /** Add the pipeline into pipeline collection
     */
    bool addPipeline(const BAS::String& regName, PPL::Pipeline* pipelinePtr);

    /** Creating pipeline individual objects
    */
    void createPipeline(const BAS::String& objectName);

    /** Common functionality for the public constructors
    */
    void commonConstructionFunc();

    /** Check if parallel loading is enabled
    */
    bool isParallelLoadingEnabled();

    /** Holds a list of all invalid pipelines
     */

    RWTValMap<int, int, less<int> > invalidPipelinesListM; 

    static const BAS::String registryFunctionsCM;

    /** Container to temporarily hold all the pipeline construction
        objects during parallel construction
    */

    RWTPtrOrderedVector<PipelineConstructor> pipelineCtorCollectionM;

   /** Mutex to guard addition of Pipeline objects during
       parallel construction
   */
    RWMutexLock collectionLockerM;

   /** Pointer to hold the parallel load manager pointer
   */
   PLI::ParallelLoadManager * pBaseParallelLoadMgrM;

   friend class PipelineConstructor;

};
}
#endif // PIPELINECOLLECTION_HPP

