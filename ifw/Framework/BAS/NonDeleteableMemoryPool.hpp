#ifndef BAS_NONDELETEABLEMEMORYPOOL_HPP
#define BAS_NONDELETEABLEMEMORYPOOL_HPP

//==============================================================================
//
// Copyright (c) 2004, 2023, Oracle and/or its affiliates.
//  This material is the confidential property of Oracle Corporation. or its
//  subsidiaries or licensors and may be used, reproduced, stored or transmitted
//  only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::MemoryPool
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of BAS::NonDeleteableMemoryPool class
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Author: Louis Piro
//
//==============================================================================

#include <stdlib.h>
#ifndef _RWSTD_NEW_INCLUDED
  #include <new>
#endif
#ifndef _RWSTD_STDEXCEPT_INCLUDED
  #include <stdexcept>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_MEMORYPOOL_HPP
  #include "BAS/MemoryPool.hpp"
#endif
#ifndef BAS_NONDELETEABLEMEMORYBLOCK_HPP
  #include "BAS/NonDeleteableMemoryBlock.hpp"
#endif

namespace BAS {

// forward decl
class MemoryBlock;

//------------------------------------------------------------------------------

/** <b><tt>BAS::NonDeleteableMemoryPool</tt></b> A NonDeleteableMemoryPool for the 
 * batch creation of objects of the templatized type.  Class is thread-safe and
 * is used to improve both memory and performance of heavily created objects.
 * Objects in this pool cannot be cleared, re-assigned or deleted.
*/
template <class T>
class NonDeleteableMemoryPool : private MemoryPool<T>
{
 public:

   /**
    * Constructs a NonDeleteableMemoryPool for objects of the templatized type.
    * @param growSize      specifies the increments in which the pool will 
    *                      automatically grow.
    */
   NonDeleteableMemoryPool(unsigned int growSize);

   /**
    * used to return a pointer to a single allocated pool item.  
    * @return pointer to the allocated item
    * @exception std::bad_alloc if pool unable to allocate an item.
    */
   T* allocateItem() noexcept(false); 

   /**
    * used to create a NonDeleteableMemoryPool during a pool auto-grow
    * operation.
    * @return the pointer to the newly created block which is now
    *         owned by the caller.
    */
   virtual MemoryBlock* handleCreateMemoryBlock(unsigned int growSize) const;

 private:
  // off limits
  NonDeleteableMemoryPool();
  NonDeleteableMemoryPool(const NonDeleteableMemoryPool&);
  NonDeleteableMemoryPool& operator=(const NonDeleteableMemoryPool&);
};

//------------------------------------------------------------------------------

template <class T>
BAS::NonDeleteableMemoryPool<T>::NonDeleteableMemoryPool(unsigned int growSize)
  : BAS::MemoryPool<T>(growSize, false)
{
  D_ENTER("BAS::NonDeleteableMemoryPool<T>::NonDeleteableMemoryPool("
          "unsigned int growSize)");
}

//------------------------------------------------------------------------------

template <class T>
inline
BAS::MemoryBlock* 
BAS::NonDeleteableMemoryPool<T>::handleCreateMemoryBlock(unsigned int growSize) const
{
  D_ENTER("BAS::NonDeleteableMemoryPool<T>::handleCreateMemoryBlock("
          "unsigned int growSize) const");

  return (new BAS::NonDeleteableMemoryBlock(growSize, MemoryPool<T>::itemSize()));
}

//------------------------------------------------------------------------------

template <class T>
inline
T* 
BAS::NonDeleteableMemoryPool<T>::allocateItem() noexcept(false) 
{
  D_ENTER("BAS::NonDeleteableMemoryPool<T>::allocateItem() throw (std::bad_alloc)");

  return MemoryPool<T>::doAllocateItem();
}

//------------------------------------------------------------------------------

} // end namespace

#endif

