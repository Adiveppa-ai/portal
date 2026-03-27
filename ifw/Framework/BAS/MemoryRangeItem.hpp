#ifndef BAS_MEMORYRANGEITEM_HPP
#define BAS_MEMORYRANGEITEM_HPP

//==============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//  This material is the confidential property of Oracle Corporation. or its
//  subsidiaries or licensors and may be used, reproduced, stored or transmitted
//  only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::MemoryRangeItem
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of BAS::MemoryRangeItem class
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
#ifndef _RWSTD_IOSTREAM_INCLUDED
  #include <iostream>
#endif

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_MEMORYBLOCK_HPP
  #include "BAS/MemoryBlock.hpp"
#endif
namespace BAS {

class MemoryBlock;

//------------------------------------------------------------------------------

/** <b><tt>BAS::MemoryRangeItem</tt></b> Used to identify the starting and 
 * ending address for a particular MemoryBlock. Also used as search key for 
 * locating a particular MemoryBlock in a MemoryBlockContainer.
*/
class MemoryRangeItem D_THREADINFO
{

D_NONTHREADSAFE

public:
  /**
   * constructor used to create a MemoryRangeItem.
   * @param blockAlias the real block associated with this MemoryRangeItem.
   * @param floor the low range Memory address for the block
   * @param ceiling the high range Memory address for the block
   */
  MemoryRangeItem(void* blockAlias,
                  MemoryAddress floor,
                  MemoryAddress ceiling);

  /**
   * equivalence operator for comparing MemoryRangeItems.
   * @param the rhs of the compare operation.
   */
  bool operator< (const MemoryRangeItem& item) const;

  /**
   * sets the state of MemoryBlock for issuing a find command. 
   * @param the pointer used in searching for a target MemoryBlock.
   */
  void set(void* item) throw();

  /**
   * gets the MemoryBlock associated with this MemoryRangeItem.
   * @return associated MemoryBlock
   */
  void* getBlock() const throw();

private:
  // off limits
  MemoryRangeItem();
  MemoryRangeItem(const MemoryRangeItem&);
  MemoryRangeItem& operator=(const MemoryRangeItem&);

private:
  void* floorM;
  void* ceilingM;
  void* memoryBlockAliasM;
};


//------------------------------------------------------------------------------
inline
MemoryRangeItem::MemoryRangeItem(void* blockAlias, 
                                 MemoryAddress floor,
                                 MemoryAddress ceiling)
  : floorM((void*)floor),
    ceilingM((void*)ceiling),
    memoryBlockAliasM(blockAlias)
{
  D_ENTER("BAS::MemoryRangeItem::MemoryRangeItem(void* blockAlias," 
          "MemoryAddress floor, MemoryAddress ceiling)");

}

//------------------------------------------------------------------------------

inline bool 
MemoryRangeItem::operator< (const MemoryRangeItem& rhs) const
{
  D_ENTER("BAS::operator< (const MemoryRangeItem& rhs) const");
  return (rhs.floorM > ceilingM);
}

//------------------------------------------------------------------------------

inline void 
MemoryRangeItem::set(void* item) throw()
{
  D_ENTER("BAS::MemoryRangeItem::set(void* item) throw()");

  floorM= item;
  ceilingM= item;
}

//------------------------------------------------------------------------------

inline void* 
MemoryRangeItem::getBlock() const throw()
{
  D_ENTER("BAS::MemoryRangeItem::getBlock() const throw()");

  return memoryBlockAliasM;
}

//------------------------------------------------------------------------------

} // end namespace

#endif
