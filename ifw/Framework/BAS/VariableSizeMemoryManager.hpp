#ifndef BAS_MEMORY_VARIABLESIZEMEMMGR_HPP
#define BAS_MEMORY_VARIABLESIZEMEMMGR_HPP
//==============================================================================
//
// Copyright (c) 2005, 2023, Oracle and/or its affiliates. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::VariableSizeMemoryManager
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::VariableSizeMemoryManager class
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Annama Ponnusamy
//
//==============================================================================
#ifndef BAS_LOCKPOOL_HPP
  #include "BAS/LockPool.hpp"
#endif
#ifndef BAS_THREAD_HPP
  #include <BAS/Thread.hpp>
#endif
#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef RW_TOOLS_TPSLIST_H
  #include <rw/tpslist.h>
#endif
#include <math.h>
#ifndef __rw_sync_RWFIFOMutexLock_h__
  #include <rw/sync/RWFIFOMutexLock.h>
#endif
#ifndef BAS_LOCKPOOLLOCKGUARD_HPP
  #include <BAS/LockPoolLockGuard.hpp>
#endif
#ifndef __rw_sync_RWSemaphore_h__
  #include <rw/sync/RWSemaphore.h>
#endif
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif
#ifndef BAS_MEMORYRANGEITEM_HPP
  #include "BAS/MemoryRangeItem.hpp"
#endif
#ifndef BAS_MEMORY_LRUOBJECTIF_HPP
  #include "BAS/LRUObjectIf.hpp"
#endif
#ifndef RW_TOOLS_TIDLIST_H
  #include <rw/tidlist.h>
#endif


namespace BAS
{
typedef LockPool<const void*, RWFIFOMutexLock> LockPoolObject;
}

namespace BAS
{

namespace Memory 
{

class Block;
typedef RWTIsvDlist<Block> MemBlkVector;

/** A VariableSizeMemoryManager owns the secondary cache.
 *  Owns the memory monitoring thread. Responsible for allocating memory in Blocks.     
 *  Acquires memory from buddy system memory pool
 */

class VariableSizeMemoryManager D_THREADINFO_M
{
public:

  VariableSizeMemoryManager( int objectsPerBlock, size_t totalSize, size_t growBySize );
  ~VariableSizeMemoryManager();

  /** Init
   *  @param startAdrs Starting address at which the memory has to be freed
      @param size the size of the memory to be freed
      @return void
   */
  void init(int objectsPerBlock, size_t totalSize, size_t growBySize);

  /** Accquiring new object from the block
   *  @param objectSize Memory is allocted according to object size
      @return void* The satrting location of the memory.
   */
  void* newObject(size_t objectSize) noexcept(false);

  /** Freeing the object in required block
   *  @param object The memory location at which the object started
   *  @objectSize The size of the object which has to be freed
      @return bool Status of freeing operation
   */
  bool  deleteObject( void* object, size_t objectSize );

  /** Accquiring memory from buddy system memory pool
   *  @param expoVal Depending upon the exponential value the memory is allocated
      @return void* The starting location of the memory allocated from buddy system memory pool
   */
  void* getBuddyBlock(size_t expoVal);

  /** To get the Exponential Value for the memory size
   *  @param initialSize The size for which the exponential to be found
   *  @param correctSize Retrieve the correct size
   *  @return unsigned int Return the exponent calculated for the intial size
   */
  static unsigned int expVal(int64 initialSize, size_t& correctSize);

  /** To Adjust the Object size according to the memory allocated
   *  @param objectsSize The size of the object
   *  @param correctSize the correct size
   *  @return unsigned int The adjusted object size.
   */
  unsigned int getAdjustedNumObjects(size_t objectsSize, size_t correctSize);

  /** Freeing memory in buddy System memory pool
   *  @param blockAddress The address at which the memory has to be freed
   *  @param expoVal Depending upon the exponential value the memory is freed
   *  @return int 
   */
  int freeBuddyBlock(void* blockAddress, size_t expoVal );

  /** Inserting free buddy system memory pool address in list
   *  @param blockAddress The free address to be stored
   *  @expoVal the exponential value to which the block address corresponds
   */
  void insertFreeAddress(char* blockAddress,unsigned int expoVal);

  /** Monitoring Memory usage and it's threshold
   *  @param void
   *  @return void
   */
  void monitoringMemory();

  /** The total object used in the memory
   *  @param void
   *  @return void
   */
  size_t totalUsedObjectSize();

  /** Increase the total object used in the memory
   *  @param void
   *  @return void
   */
  void incrTotalUsedObjectSize(size_t& objectSize);

  /** Decrease the total object used in the memory
   *  @param void
   *  @return void
   */
  void decrTotalUsedObjectSize(size_t& objectSize);

  /** To shut down the thread when process is shutting down
   *  @param void
   *  @return void
   */
  void shutDownThread();

  /** To Print the statistics of the memory
   *  @param ostream &
   *  @return void
   */
  void printStatistics(ostream &ostr);

  /** To Print the statistics of buddy system memory
   *  @param ostream &
   *  @return void
   */
  void printFreeExponentBlocks(ostream &ostr);


  /** To return start address of Memory manager
   *  @param void
   *  @return char*
   */
  char * startAdrs();


  //LockPool object
  static LockPoolObject* lockPoolObjectM;

  /** To activate recycle thread
   *  @param void
   */
  void activateThread();
  void markAsRecent(LRUObjectIf* object);

private:

  /** Find the buddy of the freeing memory
   *  @param blockAdrs The memory location for which the buddy is looked for
   *  @param expoVal The exponential value to which this block address belongs.
   */ 
  void* buddy(void* , unsigned int ); 


  BAS::Thread threadM;
  static int64 expValsCM[62][2];
  char *startAdrsM;
  char *startBuddyAdrsM;

  int objectsPerBlockM;
  unsigned int maxExpoValM;

  size_t totalSizeM;
  size_t freeSizeM;
  size_t totalUsedObjectSizeM;
  size_t growBySizeM;
  RWSemaphore freeMemSemaphoreM;
  bool exitM;
  static const int wordSizeM = 32;

  RWTPtrMap<size_t, MemBlkVector, std::less<size_t> > blocksMapM;
  
  RWTValMap<unsigned int, RWTPtrSlist<char>*, std::less<unsigned int> > freeBuddyBlocksMapM;
  RWTPtrMap<MemoryRangeItem, short, std::less<MemoryRangeItem> > memoryBlockTreeM; 

};

}// end namespace Memory

}// end namespace BAS

#endif // VARIABLESIZEMEMMGR_HPP

