//==============================================================================
//
// Copyright (c) 2004, 2023, Oracle and/or its affiliates. 
//  This material is the confidential property of Oracle Corporation. or its
//  subsidiaries or licensors and may be used, reproduced, stored or transmitted
//  only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::MemoryBlockContainer
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of BAS::MemoryBlockContainer class
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

//------------------------------------------------------------------------------

template <class T>
BAS::MemoryBlockContainer<T>::MemoryBlockContainer(const BAS::MemoryPool<T>& memoryPool)
    :lastBlockAliasM(0),
     memoryPoolM(memoryPool),
     rangeItemM(0,0,0),
     lockAcquiredM(false)
{
  D_ENTER("BAS::MemoryBlockContainer<T>::MemoryBlockContainer("
          "const BAS::MemoryPool<T>& memoryPool)");

  grow();
}

//------------------------------------------------------------------------------

template <class T>
BAS::MemoryBlockContainer<T>::~MemoryBlockContainer()
{
  D_ENTER("BAS::MemoryBlockContainer<T>::~MemoryBlockContainer()");
  memoryBlockListM.clearAndDestroy();
  memoryBlockTreeM.clearAndDestroy();
}

//------------------------------------------------------------------------------

template <class T>
bool
BAS::MemoryBlockContainer<T>::containsItem(const T* item) const
{
  rangeItemM.set(item);
  return memoryBlockTreeM.contains(&rangeItemM);
}

//------------------------------------------------------------------------------

template <class T>
T*
BAS::MemoryBlockContainer<T>::allocateItem() noexcept(false) 
{
  D_ENTER("BAS::MemoryBlockContainer<T>::allocateItem() throw (std::bad_alloc)");

  // This function is guarenteed to be only executed by a single owning thread; 

  // result to be later assigned
  T* result=0;

  // Handle NON_DELETABLE situation
  if ( !memoryPoolM.deleteable() ) 
  {
     if (lastBlockAliasM->isFull())
     {
       grow();
     }
     result= reinterpret_cast<T*>(lastBlockAliasM->allocateItem());
  }
  // Handle DELETABLE situation
  else 
  {
    // must serialize freeItem() and allocateItem() operations if pool
    // supports DELETE operation because a different thread may be simutaneouly
    // deleting an object in this container.
    RWTWriteLockGuard<RWMutexLock> writeGuard(lockM);

    if (memoryBlockListM.last()->isFull())
    {
      // move the full block to the head of the list
      MemoryBlock* fullBlock= memoryBlockListM.removeLast();
      memoryBlockListM.prepend(fullBlock);

      // set the new last block.
      lastBlockAliasM= memoryBlockListM.last();

      // if the previous block is also full then grow
      if ( memoryBlockListM.last()->isFull() )
      {
        grow();
      }
    }
    result= reinterpret_cast<T*>(lastBlockAliasM->allocateItem());
  }

  // return the  actual memory location
  return result;

}

//------------------------------------------------------------------------------

template <class T>
bool
BAS::MemoryBlockContainer<T>::freeItem(T* item, bool isAllocatingThread) 
 noexcept(false) 
{
  D_ENTER("BAS::MemoryBlockContainer<T>::freeItem(T* item, "
          "bool isAllocatingThread) throw (std::out_of_range)");

  // freed result
  bool itemFreed= false;

  // must serialize freeItem() and allocateItem() operation if freeing
  // thread differs from allocating thread.
  if (!isAllocatingThread)
  {
    lockM.acquire();
    lockAcquiredM=true;
  }

  try
  {
    // Does this container house this items address
    rangeItemM.set(item);
    const MemoryRangeItem* rangeItem= memoryBlockTreeM.find(&rangeItemM);
    // if we found a rangeItem then let's begin the free operation
    if (rangeItem)
    {
       BAS::MemoryBlock* block= (BAS::MemoryBlock*)rangeItem->getBlock();
       block->deleteItem(item);
       itemFreed= true;
  
       // if block is now empty then delete it. 
       // Although, never delete the last block.
       if (block->isEmpty() && (memoryBlockListM.entries() > 1))
       {
         memoryBlockListM.removeReference(block);
         delete memoryBlockTreeM.remove(rangeItem);
         delete block;
       }
       else if (memoryBlockListM.last() != block)
       {
         // since this block now has vacancies, move it to the tail of the list
         // if necessary.
         memoryBlockListM.removeReference(block);
         memoryBlockListM.append(block);
       }
    }
  }
  catch (...)
  {
    // conditional release lock
    if (lockAcquiredM)
    {
       lockAcquiredM= false;
       lockM.release();
    }
    throw;
  }

  // conditional release lock
  if (lockAcquiredM)
  {
     lockAcquiredM= false;
     lockM.release();
  }

  return itemFreed;
}

//------------------------------------------------------------------------------

template <class T>
void
BAS::MemoryBlockContainer<T>::grow() noexcept(false) 
{
  D_ENTER("BAS::MemoryBlockContainer<T>::grow() throw (std::bad_alloc)");

  // create and initialize a new block.
  lastBlockAliasM= memoryPoolM.handleCreateMemoryBlock(memoryPoolM.growSize());
  lastBlockAliasM->initialize();

  // Special stuff if DELETEABLE memory pool
  if (memoryPoolM.deleteable())
  {
    memoryBlockListM.append(lastBlockAliasM);
    memoryBlockTreeM.insert(lastBlockAliasM->createMemoryRangeItem(),0);
  }
}

//------------------------------------------------------------------------------

