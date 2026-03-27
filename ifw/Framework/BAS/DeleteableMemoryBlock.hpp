#ifndef BAS_DELETEABLEMEMORYBLOCK_HPP
#define BAS_DELETEABLEMEMORYBLOCK_HPP

//==============================================================================
//
// Copyright (c) 2004, 2023, Oracle and/or its affiliates. 
//  This material is the confidential property of Oracle Corporation. or its
//  subsidiaries or licensors and may be used, reproduced, stored or transmitted
//  only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::DeleteableMemoryBlock
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of BAS::DeleteableMemoryBlock class
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
#ifndef RW_TOOLS_BITVEC_H
  #include <rw/bitvec.h>
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_MEMORYBLOCK_HPP
  #include "BAS/MemoryBlock.hpp"
#endif

//------------------------------------------------------------------------------

namespace BAS {

/** <b><tt>BAS::DeleteableMemoryBlock</tt></b> Used to identify a block of
 * memory allocated during a MemoryPool auto-grow operation. Items in this
 * block can be freed and re-used.
*/
class DeleteableMemoryBlock : public MemoryBlock
{
 public:

   /**
    * constructs a DeleteableMemoryBlock capable of allocating items in bulk 
    * on the process heap.
    * @param capacity number of items to allocate on the process heap
    * @param itemSize size of each item allocated
    */
    DeleteableMemoryBlock(unsigned int capacity, unsigned int itemSize);

    /**
     * destructs the DeleteableMemoryBlock object. Called by the 
     * MemoryBlockContainer when the exe is shutting down.
     */
    virtual ~DeleteableMemoryBlock();

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
     * unassigns one item from the block and returns it to available status.
     * @param pointer to the item in the block that should be available again
     * @exception std::out_of_range if bad address given.
     */
    virtual void deleteItem(void*) noexcept(false);
    
 private:
    // off limits
    DeleteableMemoryBlock();
    DeleteableMemoryBlock(const DeleteableMemoryBlock&);
    DeleteableMemoryBlock& operator=(const DeleteableMemoryBlock&);

 private:
    RWBitVec     bitVecM;
    unsigned int entriesM;

};

//------------------------------------------------------------------------------

inline unsigned int
DeleteableMemoryBlock::entries() const throw()
{
  D_ENTER("BAS::DeleteableMemoryBlock::entries() const throw()");

  return entriesM;
}

//------------------------------------------------------------------------------

} // end namespace

#endif
