#ifndef BAS_MEMORY_LRUCACHE_HPP
#define BAS_MEMORY_LRUCACHE_HPP

//==============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::LRUCache
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::LRUCache class
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

#ifndef BAS_MEMORY_VARIABLESIZEMEMMGR_HPP
  #include "BAS/VariableSizeMemoryManager.hpp"
#endif
#ifndef BAS_MEMORY_LRUOBJECTIF_HPP
  #include "BAS/LRUObjectIf.hpp"
#endif
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif
#ifndef RW_TOOLS_TPDEQUE_H
  #include <rw/tpdeque.h>
#endif
#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif

namespace BAS
{

namespace Memory
{

/** Owns ths LRU Cache
 *  Provides functionality to find the LRU Objects
 */
class LRUCache D_THREADINFO
{
public:
  LRUCache();

  ~LRUCache();
 
  /** Add the object at the end of the deque
   *  @object Pust the object
   *  @return void
   */
  void add(LRUObjectIf *object);

  /** Remove object at the specific position in the dequeue
   *  @object Remove the object
   *  @return void
   */
  void remove(LRUObjectIf *object);
  
  /** Get teh object at the front of the dequeue
   *  @return LRUObjectIf The object from the front
   */
  LRUObjectIf *getLRUObject();

  /** To check LRU object is deleted or not
   *  @param LRUObjectIf* The LRU object
   *  @return bool TRUE = deleted FALSE = not deleted
   */
  bool isLruObjectDeleted(LRUObjectIf* lru);

  /** To add deleted object in vector
   *  @param LRUObjectIf* The LRU object
   */
  void addDeletedObjInVec(LRUObjectIf* lru);

  /** To remove object from the vector
   *  @param LRUObjectIf* The LRU object
   *  @return bool TRUE = deleted FALSE = not deleted
   */
  void removeDeletedObjInVec(LRUObjectIf* lru);

  /** Print the deque data
   *  @return void
   */
  void print(ostream &ostr);
  
  /** To mark the object in vector as reused
   *  @param LRUObjectIf* The LRU object
   */
  void markAsRecent(LRUObjectIf* object);

private:
  RWTPtrDeque<LRUObjectIf> lruCacheM;
  RWTValOrderedVector<int64> deletedObjVecM;

};

}// end namespace Memory

}// end namespace BAS

#endif // LRUCACHE_HPP
