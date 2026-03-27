#ifndef BAS_MEMORYPOOL_HPP
#define BAS_MEMORYPOOL_HPP

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
//   Implementation of BAS::MemoryPool class
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

#ifndef __rw_sync_RWReadersWriterLock_h__
  #include <rw/sync/RWReadersWriterLock.h>
#endif
#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef __rw_thread_RWTThreadLocal_h__
  #include <rw/thread/RWTThreadLocal.h> 
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_MEMORYBLOCKCONTAINER_HPP
  #include "BAS/MemoryBlockContainer.hpp"
#endif

namespace BAS {

// forward decl
class MemoryBlock;

//------------------------------------------------------------------------------

/** <b><tt>BAS::MemoryPool</tt></b> A MemoryPool for the batch creation of
 * objects of the templatized type.  Class is thread-safe and is used to improve
 * both memory and performance of heavily created objects.
*/
template <class T>
class MemoryPool D_THREADINFO
{

 D_THREADSAFE

 public:

   /**
    * Constructs a MemoryPool for objects of the templatized type.
    * @param growSize      specifies the increments in which the pool will automatically grow.
    * @param supportDelete specifies if the objects in the pool will be deleted, or if they remain in
    *                      permanent memory for the life of the exe.
    */
   MemoryPool(unsigned int growSize, bool supportDelete);

   /**
    * destructs the MemoryPool
    */
   ~MemoryPool();

   /**
    * specifies whether this MemoryPool has free capability.
    * @return bool indicating if pool will free allocated items.
    */
   bool         deleteable() const throw();
   /**
    * specifies the number of items the pool will batch allocated during an
    * auto grow operation.
    * @return bool indicating the pools delete policy
    */
   unsigned int growSize() const throw();
   /**
    * specifies the size in bytes of each item in the pool.
    * @return size in bytes of each item in the pool.
    */
   unsigned int itemSize() const throw();

   /**
    * pure virtual used to create the proper memory block during a 
    * pool auto-grow operation.
    * @return the pointer to the newly created block which is now
    *         owned by the caller.
    */
   virtual MemoryBlock* handleCreateMemoryBlock(unsigned int growSize) const=0;

 protected:
   /**
    * used to return a pointer to a single allocated pool item.  
    * @return pointer to the allocated item
    * @exception std::bad_alloc if pool unable to allocate an item.
    */
   T* doAllocateItem() noexcept(false); 

   /**
    * used to free a pointer to a single allocated pool item.  
    * @exception std::out_of_range if pool unable to free an item
    */
   void doFreeItem(void* item) noexcept(false); 

 private:
   bool deleteableM;
   unsigned int growSizeM;
   unsigned int itemSizeM;
   RWTPtrMap<unsigned long, MemoryBlockContainer<T>,
                            std::less<unsigned long> > threadMapM;
   RWReadersWriterLock lockM;
   RWTThreadLocal< MemoryBlockContainer<T>* > threadStorageM;


 private:
  // off limits
  MemoryPool();
  MemoryPool(const MemoryPool&);
  MemoryPool& operator=(const MemoryPool&);
};

//------------------------------------------------------------------------------

template <class T>
inline
bool 
MemoryPool<T>::deleteable() const throw()
{
  D_ENTER("BAS::MemoryPool<T>::deleteable() const throw()");

  return deleteableM;
}

//------------------------------------------------------------------------------

template <class T>
inline
unsigned int 
MemoryPool<T>::growSize() const throw()
{
  D_ENTER("BAS::MemoryPool<T>::growSize() const throw()");

  return growSizeM;
}

//------------------------------------------------------------------------------

template <class T>
inline
unsigned int 
MemoryPool<T>::itemSize() const throw()
{
  D_ENTER("BAS::MemoryPool<T>::itemSize() const throw()");

  return itemSizeM;
}

//------------------------------------------------------------------------------

} // end namespace

#ifdef INC_TEMPL_DEFS
#include "MemoryPool.cpp"
#endif

#endif

