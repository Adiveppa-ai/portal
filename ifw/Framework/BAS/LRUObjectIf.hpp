#ifndef BAS_MEMORY_LRUOBJECTIF_HPP
#define BAS_MEMORY_LRUOBJECTIF_HPP

//==============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: BAS::Memory::LRUObjectIf
//------------------------------------------------------------------------------
// Module Description
//   Implementation of BAS::Memory::LRUObjectIf class
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

namespace BAS
{

namespace Memory
{

class LRUObjectIf 
{
public:
  LRUObjectIf() {};
  virtual ~LRUObjectIf() {};

  /** Reset the flag to false which does not push object to the vector
   *  @param void
   *  @return void  
   */
  virtual void resetDeletableFlag() = 0;
};
 
}// end namespace Memory

}// end namespace BAS
#endif // LRUOBJECTIF_HPP
