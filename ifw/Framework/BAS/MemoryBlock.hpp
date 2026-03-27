#ifndef BAS_MEMORYBLOCK_HPP
#define BAS_MEMORYBLOCK_HPP

//==============================================================================
//
// Copyright (c) 2004, 2023, Oracle and/or its affiliates. 
//  This material is the confidential property of Oracle Corporation. or its
//  subsidiaries or licensors and may be used, reproduced, stored or transmitted
//  only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::MemoryBlock
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of BAS::MemoryBlock class
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
#ifndef _RWSTD_NEW_INCLUDED
  #include <new>
#endif

#ifndef RW_TOOLS_TISLIST_H
  #include <rw/tislist.h>
#endif
#ifndef RW_TOOLS_IDLIST_H
  #include <rw/idlist.h>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif

typedef u_int64 MemoryAddress;

namespace BAS {

class MemoryRangeItem;

//------------------------------------------------------------------------------

/** <b><tt>BAS::MemoryBlock</tt></b> Abstract base class used to define
 * MemoryBlock behavior.
*/
class MemoryBlock : public RWIsvDlink  D_THREADINFO_M
{

 D_NONTHREADSAFE

 public:

   /**
    * constructor for a MemoryBlock base.
    * @param capacity number of items to allocate on the process heap
    * @param itemSize size of each item allocated
    */
    MemoryBlock(unsigned int capacity,  unsigned int itemSize);

   /**
    * destructor for MemoryBlock base.
    */
    virtual ~MemoryBlock();

    /**
     * used to explicitly initialize a MemoryBlock
     * @exception std::bad_alloc 
     */
    void initialize() noexcept(false);

    /**
     * indicates whether this items in the MemoryBlock have all been assigned to 
     * callers via the allocateItem() function.
     * @return boolean indicated full state of the block.
     */
    bool isFull() const throw();

    /**
     * indicated whether block items are completely unassigned.
     * @return boolean representing the allocation state of the items in the block
     */
    bool isEmpty() const throw();

    /**
     * indicates if the block houses a particular memory address.
     * @return true if the address is present in the block
     */
    bool contains(void*) throw();

    /**
     * creates a MemoryRangeItem for this MemoryBlock.  Caller now owns storage of 
     * this rangeItem.
     * @return memoryRangeItem for this block.
     */
    MemoryRangeItem* createMemoryRangeItem();

    /**
     * pure virtual for returning the number of unclaimed items in the block
     * @return number of unclaimed items in the block.
     */
    virtual unsigned int entries() const throw()=0;

    /**
     * pure virtual to claim a block item
     * @return a pointer to the claimed block item
     * @exception std::bad_alloc 
     */
    virtual void* allocateItem() noexcept(false)=0;

    /**
     * pure virtual to unclaim a block item
     * @exception std::out_of_range 
     */
    virtual void deleteItem(void*) noexcept(false)=0;

 protected: 
   unsigned int  getCapacity() const throw();
   void*         getBlockAddress() const throw();
   MemoryAddress getBlockAddressLong() const throw();
   unsigned int  itemSize() const throw();

 private:
  void mallocBlock() noexcept(false);
  void freeBlock()   throw();
    
 private:
    // off limits
    MemoryBlock();
    MemoryBlock(const MemoryBlock&);
    MemoryBlock& operator=(const MemoryBlock&);

 private:
      unsigned int capacityM;
      unsigned int itemSizeM;
      void*        blockAddressM;
};


//------------------------------------------------------------------------------

inline bool 
MemoryBlock::contains(void* address) throw()
{
  D_ENTER("BAS::MemoryBlock::contains(void* address) const throw()");

  // will assert if initialize() failed or wasn't called
  RWASSERT(blockAddressM != 0);
 
  // test supplied address to see if it's in this block.
  MemoryAddress blockEnd= ((MemoryAddress)blockAddressM) + (itemSizeM*capacityM); 
  return ( (address >= blockAddressM) && 
           (address <= (void*)blockEnd) );
}

//------------------------------------------------------------------------------

inline bool
MemoryBlock::isFull() const throw()
{
  D_ENTER("BAS::isFull() const throw()");
  return (capacityM == this->entries());
}

//------------------------------------------------------------------------------

inline bool
MemoryBlock::isEmpty() const throw()
{
  D_ENTER("BAS::::isEmpty() const throw()");
  return (this->entries() == 0);
}

//------------------------------------------------------------------------------

inline unsigned int
MemoryBlock::getCapacity() const throw()
{
  D_ENTER("BAS::getCapacity() const throw()");
  return capacityM;
}

//------------------------------------------------------------------------------

inline unsigned int
MemoryBlock::itemSize() const throw()
{
  D_ENTER("BAS::itemSize() const throw ()");
  return itemSizeM;
}

//------------------------------------------------------------------------------

inline void*
MemoryBlock::getBlockAddress() const throw()
{
  D_ENTER("BAS::getBlockAddress() const throw()");
  return blockAddressM;
}

//------------------------------------------------------------------------------

inline MemoryAddress
MemoryBlock::getBlockAddressLong() const throw()
{
  D_ENTER("BAS::getBlockAddressLong() const throw()");
  return (MemoryAddress)blockAddressM;
}

//------------------------------------------------------------------------------

} // end namespace

#endif

