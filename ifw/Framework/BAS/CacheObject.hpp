#ifndef BAS_MEMORY_CACHEOBJECT_HPP
#define BAS_MEMORY_CACHEOBJECT_HPP
//==============================================================================
//
// Copyright (c) 2005, 2023, Oracle and/or its affiliates. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::CacheObject
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::CacheObject class
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
#ifndef __rw_sync_RWMutexLock_h__
  #include <rw/sync/RWMutexLock.h>
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

/** Acts as Base class for all the shadow objects. Overloads the new & delete operator 
 *  so that the request to allocate memory for the Shadow object will be routed to Block.
 */

class CacheObject D_THREADINFO
{
public:

  /** overloaded new operator
   *  @param size The Object size
   *  @return void*
   */
  void* operator new(size_t size, size_t dummySize, VariableSizeMemoryManager* memMgr) noexcept(false);

  /** Overload the delete operator
   *  @param ptr 
   *  @param size
   *  @return void
   */
  void operator delete( void *ptr, size_t size, VariableSizeMemoryManager* memMgr);
 
private:

  /** overloaded new operator
   *  @param size The Object size
   *  @return void*
   */
  void* operator new(size_t size) noexcept(false);

  /** Overload the delete operator
   *  @param ptr 
   *  @param size
   *  @return void
   */
  void operator delete( void *ptr, size_t size);

};

} // end namespace Memory

} // end namespace BAS

#endif // CACHEOBJECT_HPP
