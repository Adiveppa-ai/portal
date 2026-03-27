#ifndef BAS_MEMORY_CACHEOBJECTREF_HPP
#define BAS_MEMORY_CACHEOBJECTREF_HPP

//==============================================================================
//
//      Copyright (c) 2005 - 2023 Oracle.
//
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::CacheObjectRef
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::CacheObjectRef class
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

#ifndef BAS_MEMORY_CACHEOBJECT_HPP
  #include "BAS/CacheObject.hpp"
#endif

namespace BAS
{

namespace Memory
{

/** Manages the Reference count if the Shadow obects are shared.
 *  Filters the delete request till the Reference count becomes zero.
 */

class CacheObjectRef D_THREADINFO
{
public:

  
  virtual ~CacheObjectRef();

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
 void operator delete(void *ptr);

  /** To Increment the Reference count
   *  @param void
   *  @return void
   */
  void addRef();

  /** To decrement the Reference count
   *  @param void
   *  @return int 
   */
  int releaseRef();

private:

  CacheObjectRef();
  size_t refCntM;

};

}// end namespace Memory

}// end namespace BAS

#endif // CACHEOBJECTREF_HPP
