#ifndef BAS_MEMORY_LRUOBJECT_HPP
#define BAS_MEMORY_LRUOBJECT_HPP

//==============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::LRUObject
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::LRUObject class
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

#ifndef BAS_MEMORY_LRUOBJECTIF_HPP
  #include "BAS/LRUObjectIf.hpp"
#endif
#ifndef BAS_MEMORY_LRUCACHE_HPP
  #include "BAS/LRUCache.hpp"
#endif

namespace BAS
{

namespace Memory
{

/** Maintains the reference of the CacheObject to ensure that the removal of 
 *  LRUObject will remove the CacheObject from the memory.
 */

class LRUObject : public LRUObjectIf D_THREADINFO
{
public:
  LRUObject();
 
  ~LRUObject();

  /** Reset the flag to false which does not push object to the vector
   *  @param void
   *  @return void  
   */
  void resetDeletableFlag();
  
private:
  bool deletableM;
   
public:
  static LRUCache& getLRUCache ();
};

}// end namespace Memory

}// end namespace BAS

#endif // LRUOBJECT_HPP
