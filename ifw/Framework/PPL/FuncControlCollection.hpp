#ifndef PPL_FUNCCONTROLCOLLECTION_HPP
#define PPL_FUNCCONTROLCOLLECTION_HPP
//==============================================================================
//
// Copyright (c) 1996, 2011, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: INT
//
//------------------------------------------------------------------------------
// Module Description:
//   Function Control Interface Collection class implementation.
//
// Open Points:
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Marco Liebmann
//
// $RCSfile: FuncControlCollection.hpp $
// $Revision: /cgbubrm_main.pipeline/1 $
// $Author: sumeemis $
// $Date: 2011/08/10 01:09:12 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// $Log: FuncControlCollection.hpp,v $
// Revision 1.1  2001/11/21 10:36:49  mliebmann
// PETS #41918 new base class for single-thread pipeline and necessary modifiations
//
// 22-Mar-2011 Sumeet Mishra     Bug 11815646 - P-10434779 PHASE II CHANGES FOR PIPELINE PARALLEL LOADING ECR
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
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
#ifndef   PPL_FUNCTION_CONTROL_CONTROLLER_HPP
  #include "PPL/FunctionController.hpp"
#endif

#include "PLI/ParallelLoadManager.hpp"

namespace PPL
{
/** This class represents a collection of function control interfaces.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: FuncControlCollection.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_main.pipeline/1 $</font></td>
    <td><font size=-1>$Date: 2011/08/10 01:09:12 $</font></td>
    <td><font size=-1>$Author: sumeemis $</font></td>
    </tr>
    </table>          

<dl>
    <dt><b>Registry entries</b></dt>
    <dd>Functions</dd>
    <dd>BufferXX</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_INVALID_REG_BASE_NAME</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_CREATE_OBJECT_FAILED</dd>
    <dd>ERR_INVALID_FCI_COLL_ORDER</dd>
    <dd>ERR_INVALID_FCI_COLL_ENTRIES</dd>
</dl> 
*/
class FuncControlCollection : public BAS::Object
{
  public:

    /**@name Public Constructors */
    //@{

      /// Constructs a default instance.
      FuncControlCollection();

      /** Constructs a collection of function control interfaces.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      FuncControlCollection(const BAS::String& objectName,
                         STR::Queue<EDR::Container*>* inputQueue,
                         STR::Queue<EDR::Container*>* outputQueue);

      /** Constructs a collection of function control interfaces.<br> 
        * @param objectName The string is used for the object registration.
        * Also the registry entries are searched with it. */
      FuncControlCollection(const BAS::String& objectName,
                         STR::Queue<EDR::Container*>* inputQueue,
                         STR::Queue<EDR::Container*>* outputQueue,
                         PLI::ParallelLoadManager *baseParallelLoadMgr);

      /** Constructs a collection of function control interfaces.<br> 
        * @param objectName The string is used for the object registration.
        * @param nextPPLObject Pointer to the next pipeline object for processing
        * @param firstFuncController Pointer to the first function-
        *                            controller (back parameter)
        * Also the registry entries are searched with it. */
      FuncControlCollection(const BAS::String& objectName,
                                ThreadBase * nextPPLObject,
                                ThreadBase*& firstFuncController);

      /** Constructs a collection of function control interfaces.<br> 
        * @param objectName The string is used for the object registration.
        * @param nextPPLObject Pointer to the next pipeline object for processing
        * @param firstFuncController Pointer to the first function-
        *                            controller (back parameter)
        * Also the registry entries are searched with it. */
      FuncControlCollection(const BAS::String& objectName,
                                ThreadBase * nextPPLObject,
                                ThreadBase*& firstFuncController,
                                PLI::ParallelLoadManager *baseParallelLoadMgr);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~FuncControlCollection();

    //@}

    /**@name Public Member Functions */
    //@{

      /** Init function which will be called
        * to initialize all function control interfaces. */
      virtual bool init();

      /** Shutdown function which will be called
        * to shutdown all function control interfaces. */
      virtual bool shutdown();

	bool install();

	bool startup();

	bool uninstall();
	
      /// Check the usability of all function control interfaces.
      virtual bool isUsable();

      /// Abort requested, stop the queues immediately.
      virtual void requestAbort();

      /// Write version information.
      virtual void writeModuleVersion() const;

      /// Write the status of EDR queues into the pipeline log.
      virtual void writeQueueStatus(const BAS::String& pipelineName,
                                    const BAS::String& longPipelineName,
                                    BAS::RegisteredObject* pipelineLog) const;

     RWTValOrderedVector<BAS::String> getRegisteredPluginNames();

     /** Add function batch to parallel load manager
     */
     void addFunctionInitBatch();

    //@}

  private:

    // The following private attributes and functions are used internally.

      BAS::StringList queueRegListM;

      BAS::StringList interfaceRegListM;

      RWTPtrOrderedVector< FunctionController > functionControllerPtrVectorM;

      RWTPtrOrderedVector< STR::Queue<EDR::Container*> > queuePtrVectorM;

    // Read the configuration values out of the registry.

      virtual bool readRegistry();

    // Create the queues.

      virtual bool createQueues();

    // Create the function control interfaces.
    // Multithreaded with queues

      virtual bool createInterfaces(STR::Queue<EDR::Container*>* inputQueue,
                                    STR::Queue<EDR::Container*>* outputQueue);

    // Create the function control interfaces.
    // SingleThreaded with pointer to the next pipelineobject
    
      virtual bool createInterfaces(ThreadBase * nextPPLObject,
                                    ThreadBase*& firstFuncController);
                                    
    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      FuncControlCollection(FuncControlCollection& right);

      const FuncControlCollection& operator=(FuncControlCollection& right);

      void commonConstructionFunc();

      /** Pointer to hold the parallel load manager pointer
      */
      PLI::ParallelLoadManager * pBaseParallelLoadMgrM;

      static const BAS::String registryDataPoolCM;
      static const BAS::String registryPipelinesCM;
};
}
#endif // FUNCCONTROLCOLLECTION_HPP
