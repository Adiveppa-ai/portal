#ifndef BAS_MEMORYBLOCKCONTAINER_HPP
#define BAS_MEMORYBLOCKCONTAINER_HPP

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

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef RW_TOOLS_TIDLIST_H
  #include <rw/tidlist.h>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_MEMORYRANGEITEM_HPP
  #include "BAS/MemoryRangeItem.hpp"
#endif

namespace BAS {

// forward decl
template <class T>
class MemoryPool;


//------------------------------------------------------------------------------

/** <b><tt>BAS::MemoryBlockContainer</tt></b> class used to house all the
 * MemoryBlocks associated with a threadID
*/
template <class T>
class MemoryBlockContainer  D_THREADINFO
{
 D_THREADSAFE

 public:

   /**
    * constructor for a MemoryBlockContainer
    * @param memoryPool backpointer to the MemoryPool
    */
    MemoryBlockContainer(const MemoryPool<T>& memoryPool);

   /**
    * destructor for the MemoryBlockContainer
    */
    ~MemoryBlockContainer();
    
    /**
     * used to allocate an item in the container
     * @return address of the allocated item
     * @exception std::bad_alloc if unable to allocate the item
     */
    T* allocateItem() noexcept(false);

    /**
     * used to free an item in the container
     * @param item address of item to free
     * @param isAllocatingThread the thread requesting the free is the same
     *                           thread that originally allocated.
     * @return boolean if item is a member of the container and
     * was successfully freed
     * @exception std::out_of_range if unable to free the item because of
     *            bad address.
     */
    bool freeItem(T* item, bool isAllocatingThread) noexcept(false);

 private:

    /**
     * indicates if a particular address is contained in this container
     * @param item address of the item to seek for
     * @return boolean indicating if the address is in the container
     */
    bool containsItem(const T* item) const;

    /**
     * used to force the container to increase its number of MemoryBlocks by one.
     * @exception std::bad_alloc if unable to calloc a new MemoryBlock
     */
    void grow() noexcept(false);

 private:
    // off limits
    MemoryBlockContainer();
    MemoryBlockContainer(const MemoryBlockContainer&);
    MemoryBlockContainer& operator=(const MemoryBlockContainer&);

 private:
    MemoryBlock* lastBlockAliasM;
    const MemoryPool<T>& memoryPoolM;
    MemoryRangeItem rangeItemM;
    RWTPtrMap<MemoryRangeItem, short, std::less<MemoryRangeItem> > memoryBlockTreeM;
    RWTIsvDlist<MemoryBlock> memoryBlockListM;
    RWMutexLock lockM;
    bool lockAcquiredM;
};

} // end namespace

#ifdef INC_TEMPL_DEFS
#include "MemoryBlockContainer.cpp"
#endif

#endif


