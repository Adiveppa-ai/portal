#ifndef BAS_NONDELETEABLEMEMORYBLOCK_HPP
#define BAS_NONDELETEABLEMEMORYBLOCK_HPP

//==============================================================================
//
// Copyright (c) 2004, 2023, Oracle and/or its affiliates. 
//  This material is the confidential property of Oracle Corporation. or its
//  subsidiaries or licensors and may be used, reproduced, stored or transmitted
//  only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::NonDeleteableMemoryBlock
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of BAS::NonDeleteableMemoryBlock class
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
#ifndef _RWSTD_STDEXCEPT_INCLUDED
  #include <stdexcept>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_MEMORYBLOCK_HPP
  #include "BAS/MemoryBlock.hpp"
#endif

namespace BAS {

//------------------------------------------------------------------------------

/** <b><tt>BAS::NonDeleteableMemoryBlock</tt></b> Used to identify a block of
 * memory allocated during a MemoryPool auto-grow operation. Items in this
 * block can never be deleted, and will remain until the exe is no longer 
 * running.
*/
class NonDeleteableMemoryBlock : public MemoryBlock
{
 public:
    /**
     * constructs a NonDeleteableMemoryBlock capable of allocating items in bulk on the
     * process heap.
     * @param capacity number of items to allocate on the process heap
     * @param itemSize size of each item allocated
     */
    NonDeleteableMemoryBlock(unsigned int capacity, unsigned int itemSize);

    /**
     * destructs a NonDeleteableMemoryBlock. Called by the MemoryBlockContainer
     * when the exe is shutting down.
     */
    virtual ~NonDeleteableMemoryBlock();

    /**
     * gets the number of currently allocated items in this block which are
     * in use.
     * @return number of items currently allocated and assigned in this block.
     */
    virtual unsigned int entries() const throw();

    /**
     * gets one item from the block and returns its pointer to the caller.
     * @return pointer to an item in the block
     * @exception std::bad_alloc if all allocated items have been requested.
     */
    virtual void* allocateItem() noexcept(false);

    /**
     * does nothing because NonDeleteableMemoryBlock items cannot be freed and
     * reassigned.
     * @param pointer to the item in the block that should be available again
     * @exception std::out_of_range if user attempts to delete item in a 
     *            NonDeleteableMemoryBlock.
     */
    virtual void deleteItem(void*) noexcept(false);
    
 private:
    // off limits
    NonDeleteableMemoryBlock();
    NonDeleteableMemoryBlock(const NonDeleteableMemoryBlock&);
    NonDeleteableMemoryBlock& operator=(const NonDeleteableMemoryBlock&);

 private:
    unsigned int numEntriesM;

};

//------------------------------------------------------------------------------

inline unsigned int
NonDeleteableMemoryBlock::entries() const throw()
{
  D_ENTER("BAS::NonDeleteableMemoryBlock::entries() const throw()");

  return numEntriesM;
}

//------------------------------------------------------------------------------

} // end namespace

#endif

