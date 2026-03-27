#ifndef PLI_PARALLEL_LOAD_MANAGER_HPP
#define PLI_PARALLEL_LOAD_MANAGER_HPP
//==============================================================================
//
// @(#)%Portal Version: .hpp:Pipeline7.3ModularInt:3:2007-Mar-27 13:13:17 %
//
// Copyright (c) 1998, 2011, Oracle and/or its affiliates. 
// All rights reserved. 
//
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLI
//------------------------------------------------------------------------------
// Module Description:
//   integrate control class implementation.
//
//------------------------------------------------------------------------------
// Change Log
//------------------------------------------------------------------------------
// Responsible: pc
//
// $RCSfile: ParallelLoadManager.hpp $
// $Revision: /cgbubrm_main.pipeline/1 $
// $Author: sumeemis $
// $Date: 2011/08/10 01:09:11 $
// $Locker:  $
//
//------------------------------------------------------------------------------
// Revision 1.2  2011/03/22 01:45:14  sm
// Bug 11815646 - P-10434779 PHASE II CHANGES FOR PIPELINE PARALLEL LOADING ECR
// Bug 11838319 - P-11825308 PLM: AUTO MODE RANK ISSUE
//
// Revision 1.1  2010/11/09 16:12:12  pc
// Initial version of base class LoadManager.
//
//==============================================================================


#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_REGISTRYENTRY_HPP
  #include "BAS/RegistryEntry.hpp"
#endif
#ifndef   BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif

#include "PLI/CommonLoadInterface.hpp"
#include "BAS/Thread.hpp"

namespace PLI
{
/** This class represents parallel load manager (PLM)
*/

class ParallelLoadManager: public BAS::RegisteredObject
{
  public:

      /** RunMode in which PLM is currently running

       A batch-set comprises of a set of batches with the same rank -
       that is, the items they encompass can be loaded in parallel.

       BATCH_SET_TRIGGER = all the PLM threads waits once a batch-set is
                           complete. A trigger sould be given by the caller to continue.
                           Once the trigger arrives, next batch-set is taken up
                           before waiting again and so on.

                           All PLM threads die after the last batch-set is 
                           completed.

                           This mode is useful in cases when, the caller has some
                           work to do, after one-or-more batches in a batchset.

       AUTO              = all the batches in various batch-sets are executed
                           one-by-one, till all are completed; no breaks here. 
                           All PLM threads die after completion.

                           This mode is useful in cases when, all the jobs
                           in a group have to be done without breaks.
      */
      enum RunMode
      {
        BATCH_SET_TRIGGER = 0, //Set comprises of one or more batches
        AUTO
      };

      /** Group consists of one or more batches, belonging to different batch-sets

         SINGLE_GROUP = In this mode, PLM needs to execute items in just one group.

         MULTI_GROUP  = In this mode, the PLM waits after one group is done, for the
                        caller to dynamically add another group for processing

      */

      enum WorkMode
      {
        SINGLE_GROUP = 0,
        MULTI_GROUP
      };


      //have to make the below enum/struct public for blasted archaic compilers

      /** Status of each item/batch executed by the PLM
      */

      enum LoadStatus
      {
        LOAD_NOT_STARTED = 0,
        LOADING,
        LOADED,
        LOAD_FAILED
      };

      /** Unit of Operation in PLM
      */

      struct LoadItem
      {
        //item handle
        PLI::CommonLoadInterface* loadItem;

        //status of the item;
        LoadStatus loadStatus;

        //stored dependency on other items in the batch
        RWTValOrderedVector<LoadItem*> dependencyList; 

        //lock to manipulate the item
        RWReadersWriterLock itemLock;
        
	//the thread-id of the thread which has 'won'
	//the contest among other threads to load the item
	RWThreadId threadIdToLoad;

	//rank of the item - level in the dependency grap
	int itemRank;

	int getRank() { return itemRank;  }

      };

      /** Default constructor */

      ParallelLoadManager();

      /** Main Constructor */
      ParallelLoadManager(const BAS::String& objectName);

      /** Destructor */
      ~ParallelLoadManager();

      /** Overriden readRegistry */
      virtual bool readRegistry();

      /** Method to start the PLM threads */
      void startParallelInit(const BAS::String & caller);
	
      /** Checking whether a batch set is completed */
     bool isABatchSetComplete();

      /** Is PLM enabled? */
      bool enabled() const;

      /** Has the work of PLM completed */
      void waitForComplete();

      /** Retrigger the execution of next batch set -
         used if mode is BATCH_SET_TRIGGER
      */
      void processNextBatchSet();

      /** Retrigger the execution of next group -
         used if work-mode is MULTI_GROUP
      */
      void processNextGroup();
    
      /** Setting the mode */
      void runMode ( RunMode m );

      /** Getting the mode */
      RunMode runMode();

      /** Setting the mode */
      void workMode ( WorkMode m );

      /** Getting the mode */
      WorkMode workMode();
     
      /**Adding batch to the PLM queue*/
      bool addBatchToQueue(const BAS::String & batchName,
                           const RWTValOrderedVector<PLI::CommonLoadInterface*> &itemList,
                           const BAS::StringList & batchDepencencies);

      /** Print status of PLM*/
      void printStatus(const BAS::String & caller);

      /** Indicate that no more groups are to be loaded - in MULTI_GROUP mode */
      void stop();

      /**Set current group name*/
      void setGroupName ( const BAS::String & );

      /**Get current group name*/
      const BAS::String & getGroupName ();

  private:

      /** Structure to capture the Batch details.
          A batch-set is a collection of batches sharing
          the same rank.
      */
      struct Batch
      {
        //batch name
        BAS::String batchName;

        //rank of the batch in the dependency graph
        int rank;

        //status of batch
        LoadStatus batchStatus;

        //is any more PLM threads reqd to work on this batch?
        bool noMoreLoadThreadsReqd;

        //batches THIS batche is dependent on
        RWTValOrderedVector<Batch*> batchDependencyList;

        //items within this batch
        RWTValOrderedVector<LoadItem*> loadItemList;

        //lock to access this batch's members
        RWReadersWriterLock batchLock;

        //max no of threads reqd to handle this batch
        //this is calculated based on the dependencies
        //by the calculateSpan method
        int span;

        //the number of threads allocated to this batch
        int allocatedThreads;
        int getRank() { return rank;  }
      };

      //useful typedefs
      typedef RWReadersWriterLock::ReadLockGuard  ReadGuard;
      typedef RWReadersWriterLock::WriteLockGuard WriteGuard;

      //locks to guard shared variables
      //RWReadersWriterLock getTriggerLockM;


      RWReadersWriterLock currentRankLockM;
      //RWReadersWriterLock groupCompletedLockM;
      RWReadersWriterLock stopLockM;
      RWMutexLock groupCompletedLockM;
      RWMutexLock groupLockerM;
      RWMutexLock statusLockM;
      RWMutexLock restartLockM;
      RWReadersWriterLock threadIncrementLockM;
      RWReadersWriterLock deadThreadIncrementLockM;

      //condition variables
      RWCondition batchClearedCondM;
      RWCondition groupCompletedCondM;
      RWCondition restartThreadsCondM;

      bool groupClearedM;
      bool stopM;
      bool nextGroupInitDoneM;

      //Collection of all batches
      RWTValOrderedVector<Batch*> batchCollectionM;

      //is PLM active?
      bool parallelLoadEnabledM;

      //boolean indicating whether threads are
      //waiting for re-trigger of next batch-set
      //from the caller
      bool waitingForReTriggerM;

      //have all batches been loaded?
      bool groupLoadCompletedM;

      //number of threads configured
      int  numberOfLoadThreadsM;

      //pool holding the threads
      RWTValOrderedVector<BAS::Thread*> threadPoolM;

      //run-mode currently the PLM is running in
      RunMode runModeM; 

      //work-mode currently the PLM is running in 
      WorkMode workModeM;
 
      //rank (level) of the batches whose items are
      //currently being loaded by PLM threads
      int currentRankM;

      //threads waiting for re-trigger from caller
      //used in BATCH-SET-TRIGGER run-mode and MULTI_GROUP work mode
      unsigned int waitingThreadCountM;

      //a count of threads that have already died 
      unsigned int deadThreadCountM;

      //maximum rank among the batches
      int maxRankM;

      //current group name - in case of workMode = MULTI_GROUP
      BAS::String curGroupNameM;

      //has the 'hidden' RunMode parameter been configured in
      //the registry?
      bool regModeSetM;

      //count of groups in MULTI_GROUP work mode
      unsigned groupCountM;

      //Registry paramters
      static const BAS::String numThreadsCM;
      static const BAS::String enableParallelLoadingCM;
      static const BAS::String parallelLoadManagerCM;
      static const BAS::String modeCM;

     /** The main 'run' method executed by the PLM threads */
      void run();

      /** The method used to load individual items*/
      bool loadItems( Batch * );



      /**Calculate spans for the batches in the current group*/

      void computeGroupSpans();

      bool isLastThreadToWait();

      void prepareNextGroup();

      bool isAllGroupsDone();

      void signalGroupLoadCompleted();

      void waitForRestartSignal();

      void setThreadsWaitIndicator();

      void incrementWaitThreadCount();

      void signalStopWaiting();

      void incrementDeadThreadCount();

      bool isLastThreadToDie();

};

inline bool 
PLI::ParallelLoadManager::isABatchSetComplete()
{
  if ( runModeM == BATCH_SET_TRIGGER )
  {
    return isLastThreadToWait();
  }
  else
  {
    return true;
  }
}

inline bool
PLI::ParallelLoadManager::isLastThreadToWait()
{
  ReadGuard readGuard (threadIncrementLockM);
  return (waitingThreadCountM >= threadPoolM.entries());
}

inline void
PLI::ParallelLoadManager::processNextBatchSet()
{
  if ( runModeM == BATCH_SET_TRIGGER )
  {
    signalStopWaiting();
  }
}

inline void
PLI::ParallelLoadManager::setGroupName(const BAS::String & groupName)
{
  curGroupNameM = groupName;
}

inline const BAS::String&
PLI::ParallelLoadManager::getGroupName()
{
  return curGroupNameM;
}

inline void
PLI::ParallelLoadManager::processNextGroup()
{
  if ( workModeM == MULTI_GROUP )
  {
    RWLockGuard<RWMutexLock> groupCompletedGuard (groupCompletedLockM);

    groupLoadCompletedM = false;

    signalStopWaiting();
  }
}

inline void
PLI::ParallelLoadManager::signalGroupLoadCompleted()
{
  RWLockGuard<RWMutexLock> groupCompletedGuard (groupCompletedLockM);

  if(groupLoadCompletedM == false)
  {
    groupLoadCompletedM = true; //indicate completeness of the group

    groupCompletedCondM.signal(); //signalling the caller
  }
}

inline void
PLI::ParallelLoadManager::setThreadsWaitIndicator()
{
  if ( waitingForReTriggerM == false )
  {
    RWLockGuard<RWMutexLock> restartGuard (restartLockM);

    if ( waitingForReTriggerM == false )
    {
      waitingForReTriggerM = true;
    }
  }
}

inline void
PLI::ParallelLoadManager::incrementWaitThreadCount()
{
  WriteGuard writeGuard (threadIncrementLockM);

  waitingThreadCountM++ ;
}

inline void
PLI::ParallelLoadManager::incrementDeadThreadCount()
{
  WriteGuard writeGuard (deadThreadIncrementLockM);
  deadThreadCountM++ ;
}

inline bool
PLI::ParallelLoadManager::isLastThreadToDie()
{
  ReadGuard readGuard (deadThreadIncrementLockM);
  return (deadThreadCountM >= threadPoolM.entries());
}

inline bool
PLI::ParallelLoadManager::isAllGroupsDone()
{
  ReadGuard readGuard (stopLockM);
  return (stopM == true);
}

inline void
PLI::ParallelLoadManager::stop()
{
  {
    WriteGuard writeGuard (stopLockM);
    stopM = true;
  }
  signalStopWaiting();
}

inline PLI::ParallelLoadManager::RunMode
PLI::ParallelLoadManager:: runMode()
{
 return runModeM;
}

inline PLI::ParallelLoadManager::WorkMode
PLI::ParallelLoadManager::workMode()
{
 return workModeM;
}

inline void
PLI::ParallelLoadManager::workMode( WorkMode m )
{
  workModeM = m;
}


/** A generic method to calculate span of a graph.
    Span = the maximum number of items on a level (i.e.
           sharing the same rank) in a graph.
*/

template < class T>
bool calculateSpan ( const T & rankHolder , 
                     int & span , 
                     int & rankWithMaxSpan)
{
  //Maximum 'depth' supported in a graph
  const unsigned MaxHierarchyLevelsSupportedC = 10;

  //array to hold the items having 'i' rank
  //index represents the rank - the value represents the count
  int rankCount[MaxHierarchyLevelsSupportedC] = {0};

  unsigned m ;

  span = 0;

  //rank having the max span
  rankWithMaxSpan = 0;

  for (m = 0; m < rankHolder.entries() ; m++)
  {
    if ( (unsigned) rankHolder[m]->getRank() < MaxHierarchyLevelsSupportedC )
    {
       rankCount[rankHolder[m]->getRank()]++;
    }
    else
    {
       return false;
    }
  }

  span = rankCount[0];

  //get the max rank now
  for (m = 1; m < MaxHierarchyLevelsSupportedC ; m++)
  {
    if (rankCount[m] > span)
    {
      span = rankCount[m];
      rankWithMaxSpan = m;
    }
  }

  return true;
}

}
#endif // PARALLEL_LOAD_MANAGER_HPP
