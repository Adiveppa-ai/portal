//==============================================================================
//
// Copyright (c) 2004, 2024, Oracle and/or its affiliates. 
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

#ifndef BAS_DELETEABLEMEMORYBLOCK_HPP
  #include "BAS/DeleteableMemoryBlock.hpp"
#endif
#ifndef BAS_NONDELETEABLEMEMORYBLOCK_HPP
  #include "BAS/NonDeleteableMemoryBlock.hpp"
#endif

#ifndef _RWSTD_NEW_INCLUDED
  #include <new>
#endif
#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

//------------------------------------------------------------------------------

template <class T>
BAS::MemoryPool<T>::MemoryPool(unsigned int growSize,
                               bool supportDelete)
  : deleteableM(supportDelete),
    growSizeM(growSize),
    itemSizeM(sizeof(T))
{
  D_ENTER("BAS::MemoryPool<T>::MemoryPool(unsigned int growSize,"
          "bool supportDelete)");

  // Ensure items are aligned on proper boundry
  unsigned int itemSize= sizeof(T);
  unsigned int delta= itemSize % sizeof(T*);
  if (delta != 0)
  {
    itemSizeM= itemSize+(sizeof(T*)-delta);
  }
}

//------------------------------------------------------------------------------

template <class T>
BAS::MemoryPool<T>::~MemoryPool()
{
  D_ENTER("BAS::MemoryPool<T>::~MemoryPool()");
  threadMapM.clearAndDestroy();
}

//------------------------------------------------------------------------------

template <class T>
T*
BAS::MemoryPool<T>::doAllocateItem() noexcept(false) 
{
  D_ENTER("BAS::MemoryPool<T>::doAllocateItem() throw(std::bad_alloc)");

  // container to be later assigned.
  MemoryBlockContainer<T>* container=0;

  // If this is thread's first alloc, then add it to the thread/container map.
  if (!threadStorageM.isSet())
  {
    RWTWriteLockGuard<RWReadersWriterLock> writelock(lockM);
    unsigned long threadID= rwThreadId().hash();
    container= new MemoryBlockContainer<T>(*this);
    threadStorageM= container;
    threadMapM.insert(new unsigned long(threadID), container);
  }
  else
  {
    container= threadStorageM.getValue();
  }

  return  container->allocateItem();
}


//------------------------------------------------------------------------------

template <class T>
void
BAS::MemoryPool<T>::doFreeItem(void* item) noexcept(false) 
{
  D_ENTER("BAS::MemoryPool<T>::doFreeItem(void* item) throw (std::out_of_range)");

  // container to be later assigned.
  MemoryBlockContainer<T>* localStorageContainer=0;

  // success indicator
  bool success= false;

  // first attempt to delete in the current threads container
  if (threadStorageM.isSet())
  {
    localStorageContainer= threadStorageM.getValue();
    success= localStorageContainer->freeItem( (T*)item, true);
  }

  // if no success, then loop through all other thread containers
  if (!success)
  {
    // read lock required while iterating the thread/container map
    RWTReadLockGuard<RWReadersWriterLock> readlock(lockM);

    // get an mapIterator
    RWTPtrMapIterator<unsigned long, 
                          MemoryBlockContainer<T>,
                          std::less<unsigned long> > iter(threadMapM);

    // identify the container housing the item to delete
    while (iter())
    {
      BAS::MemoryBlockContainer<T>* container= iter.value();

      // don't bother re-checking in the current threads container
      // because we already did that above.
      if (container != localStorageContainer)
      {
        success= container->freeItem((T*)item, false);
        if (success)
        {
          break;
        }
      }
    }
  }

  // item not found in memory pool, throw exception
  if (!success)
  {
    throw std::out_of_range("Item is not a valid MemoryPool address.");
  }

}

//------------------------------------------------------------------------------
