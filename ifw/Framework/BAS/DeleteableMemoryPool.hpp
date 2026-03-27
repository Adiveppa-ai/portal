#ifndef BAS_DELETEABLEMEMORYPOOL_HPP
#define BAS_DELETEABLEMEMORYPOOL_HPP

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
//   Implementation of BAS::DeleteableMemoryPool class
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
#ifndef BAS_DELETEABLEMEMORYBLOCK_HPP
  #include "BAS/DeleteableMemoryBlock.hpp"
#endif

namespace BAS {

// forward decl
class MemoryBlock;

//------------------------------------------------------------------------------

/** <b><tt>BAS::DeleteableMemoryPool</tt></b> A DeleteableMemoryPool for the 
 * batch creation of objects of the templatized type.  Class is thread-safe and
 * is used to improve both memory and performance of heavily created objects.
 * Objects in this pool can be cleared and re-assigned.
*/
template <class T>
class DeleteableMemoryPool : private MemoryPool<T>
{
 public:

   /**
    * Constructs a DeleteableMemoryPool for objects of the templatized type.
    * @param growSize      specifies the increments in which the pool will 
    *                      automatically grow.
    */
   DeleteableMemoryPool(unsigned int growSize);

   /**
    * used to return a pointer to a single allocated pool item.  
    * @return pointer to the allocated item
    * @exception std::bad_alloc if pool unable to allocate an item.
    */
   T* allocateItem() noexcept(false); 

   /**
    * used to free a pointer to a single allocated pool item.  
    * @exception std::out_of_range if pool unable to free an item
    */
   void freeItem(void* item) noexcept(false); 

   /**
    * used to create a DeleteableMemoryBlock during a pool auto-grow
    * operation.
    * @return the pointer to the newly created block which is now
    *         owned by the caller.
    */
   virtual MemoryBlock* handleCreateMemoryBlock(unsigned int growSize) const;

 private:
  // off limits
  DeleteableMemoryPool();
  DeleteableMemoryPool(const DeleteableMemoryPool&);
  DeleteableMemoryPool& operator=(const DeleteableMemoryPool&);
};

//------------------------------------------------------------------------------

template <class T>
BAS::DeleteableMemoryPool<T>::DeleteableMemoryPool(unsigned int growSize)
  : BAS::MemoryPool<T>(growSize, true)
{
  D_ENTER("BAS::DeleteableMemoryPool<T>::DeleteableMemoryPool("
          "unsigned int growSize)");
}

//------------------------------------------------------------------------------

template <class T>
inline
BAS::MemoryBlock* 
BAS::DeleteableMemoryPool<T>::handleCreateMemoryBlock(unsigned int growSize) const
{
  D_ENTER("BAS::DeleteableMemoryPool<T>::handleCreateMemoryBlock("
          "unsigned int growSize) const");

  return (new BAS::DeleteableMemoryBlock(growSize, MemoryPool<T>::itemSize()));
}

//------------------------------------------------------------------------------

template <class T>
inline
T* 
BAS::DeleteableMemoryPool<T>::allocateItem() noexcept(false) 
{
  D_ENTER("BAS::DeleteableMemoryPool<T>::allocateItem() throw (std::bad_alloc)");

  return MemoryPool<T>::doAllocateItem();
}

//------------------------------------------------------------------------------

template <class T>
inline
void 
BAS::DeleteableMemoryPool<T>::freeItem(void* item) noexcept(false) 
{
  D_ENTER("BAS::DeleteableMemoryPool<T>::freeItem(void* item)"
          " throw (std::out_of_range)");

  MemoryPool<T>::doFreeItem(item);
}

//------------------------------------------------------------------------------

} // end namespace

#endif

