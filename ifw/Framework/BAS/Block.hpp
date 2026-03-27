#ifndef BAS_MEMORY_BLK_HPP
#define BAS_MEMORY_BLK_HPP

//==============================================================================
//
// Copyright (c) 2005, 2023, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::Block
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::Block class
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Annama Ponnusamy
//
//==============================================================================
#ifndef BAS_MEMORY_VARIABLESIZEMEMMGR_HPP
  #include "BAS/VariableSizeMemoryManager.hpp"
#endif
#ifndef BAS_MEMORYRANGEITEM_HPP
  #include "BAS/MemoryRangeItem.hpp"
#endif
#ifndef RW_TOOLS_TIDLIST_H
  #include <rw/tidlist.h>
#endif

typedef u_int64 MemoryAddress;

namespace BAS
{

class MemoryRangeItem;

}
/** Block is responsible for maintaining the Block of memory , 
 *  serves the request to new/delete memory for shadow object.
 *  Interacts with VariableSizeMemoryManager to get a block of memory when needed. 
 */
namespace BAS
{

namespace Memory
{

class Block : public RWIsvDlink D_THREADINFO
{
  public:
    Block( int32 objectSize, int32 numObjects, BAS::Memory::VariableSizeMemoryManager* memMgr);
    ~Block();

    /** Free the object from the block
      *  @param objectSize Free the object accoring to object size
      *  @return void
      */
    void cleanup(size_t objectSize);

    /** Try to retrieve the free object from the block
      *  @param objectSize look for free object depending on the object size
      *  @return void* The address of the free object
      */
    void* getFreeObject(size_t objectSize);

    /** Try to Free the object
      *  @param object The object address which is to be freed
      *  @param objectSize The size of the object
      */
    bool freeObject( void* object, size_t objectSize );

    /** To check the validity of the Block new operation
      *  @return bool The status of the Block creation
      */
    bool  isValid();

    /** To check the block weather full or not
      *  @return bool The satus of block weather full or not
      */
    bool  isFull();

    /** To check the block weather Free or not
      *  @return bool The satus of block weather Free or not
      */
    bool  isFree();

    /** To lock Memory at block level with starting address as key.
      *  @return const char* the starting address as key
      */
    const char* getBlockId(); 

    /** To Print the statistics for the particular block
      *  @param ostream& 
      */
    void printStatistics(ostream &ostr); 

    /** To get the memory block information
      *  @param int&
      *  @return char*
      */
    char* getMemBlockInfo(int& numTotal, size_t& blkSize); 

    /**
     * creates a MemoryRangeItem for this MemoryBlock.  Caller now owns storage of
     * this rangeItem.
     * @return memoryRangeItem for this block.
     */
    MemoryRangeItem* createMemoryRangeItem(int32 objectSize);


  protected:
    MemoryAddress getBlockAddressLong() const throw();

  private:
      
    u_int32        objectIsFree( u_int32 object );
    void* useObject( u_int32 object, size_t objectSize );

    int32            numUsedM;
    int32            numTotalM;
    int32            nextM;
    char*            memoryBlockM;
    u_int32*         freeVectorM;
    static const int32 wordSizeM = 32;
};

inline MemoryAddress
Block::getBlockAddressLong() const throw()
{
  D_ENTER("BAS::Memory::Block::getBlockAddressLong() const throw()");
  return (MemoryAddress)memoryBlockM;
}

}//end of namespace Memory

}//end of namespace BAS
#endif // BLK_HPP
