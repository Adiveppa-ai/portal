#ifndef EDR_DATABLOCKVALUE_HPP
#define EDR_DATABLOCKVALUE_HPP

//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: 
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class DatablockValue.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: DatablockValue.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:42 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DatablockValue.hpp,v $
// Revision 1.6  2012/11/11 Santanu 
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
//
// Revision 1.5  2002/01/15 09:28:23  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.4  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.3  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.2  2001/03/30 12:49:44  sd
// - Changes to support duplication of EDR containers
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   EDR_VALUE_HPP
  #include "EDR/Value.hpp"
#endif
namespace EDR
{
class Factory;
class Datablock;

/** <b><tt>DatablockValue</tt></b> is the value class for datablocks.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DatablockValue.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:42 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>                
 */
class DatablockValue  D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name DatablockValue constructors and destructor */
    //@{

    /** Default constructor
     *  @param blockTypeId The block type id of the contained datablock
     */
    DatablockValue( size_t blockTypeId );

    /** Destructor
     */
    ~DatablockValue();

    //@}

    /**@name DatablockValue public methods */
    //@{

    /** Clone the datablock value
     *  @return Pointer to the cloned datablock value
     */
    DatablockValue* clone() const;

    /** Clear the value
     */
    void clear();

    /** Get the current datablock of the value
     *  @return Pointer to the current datablock if existent, 0 otherwise
     */
    Datablock* currentDatablock() const;

    /** Get the n-th datablock
     *  @param n The number of the datablock
     *  @return Pointer to the datablock if existent, 0 otherwise
     */
    Datablock* datablock( size_t n ) const;

    /** Add a new datablock to the value
     *  @param block The new datablock to add
     */
    void addDatablock( Datablock* block );

    /** Get the number of datablocks
     *  @return The number of datablocks
     */
    size_t numDatablocks() const;

    /** Get the block type id
     *  @return The blocktype id
     */
    size_t blockTypeId() const;

    /** Copy the data from another Datablock value. This function
     *  is only used when datablocks will be duplicated by the Factory and
     *  should be used carefully!
     *  @param other The other datablock value to copy
     */
    void copyData( const DatablockValue* other );

    /** Copy the data from another Datablock value. This function
     *  is only used when datablocks will be duplicated by the Factory and
     *  should be used carefully!
     *  The multi-threaded-multi-factory version
     *  @param other The other datablock value to copy
     */
    void variantFactoryCopyData( const DatablockValue* other );

    /** Serialize the datablock value
     *  @param out Output stream for serialization
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool serialize( std::ostream& out ) const;

    /** Restore the serialized datablock value
     *  @param in The input stream
     *  @param factory EDR factory for creating the datablocks
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool restore( std::istream& in, Factory* factory );

    /** Remove the n-th datablock
     *  @param n The number of the datablock
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool removeDatablock( size_t dataBlockNumber );

    /** Get the current block number
     *  @return The currentBlockM value
     */

    size_t getCurrentBlockNum() const;

    /** Set the factory object
     *  @param factory The pointer to the factory object
     */
    void setFactory(EDR::Factory * factory);

    //@}

  protected:

    /* Resize the datablock value to the specified capacity
     * @param newCapacity The new capacity
     */
    void resize( size_t newCapacity );

  private:

    // Hide default and copy constructor
    DatablockValue();
    DatablockValue( const DatablockValue& other );
    const DatablockValue& operator=( const DatablockValue& other );

    // instance members
    size_t          currentBlockM;
    size_t          blockTypeIdM;
    size_t          numBlocksM;
    size_t          capacityM;
    Datablock** blocksM;
    Factory * factoryM;
};

//==============================================================================
// Get the number of datablocks
//==============================================================================
inline size_t
DatablockValue::numDatablocks() const
{
  return numBlocksM;
}

//==============================================================================
// Get the blocktype id
//==============================================================================
inline size_t
DatablockValue::blockTypeId() const
{
  return blockTypeIdM;
}

//==============================================================================
// Clear the datablock value
//==============================================================================
inline void
DatablockValue::clear()
{
  currentBlockM = 0;
  numBlocksM    = 0;
}

//==============================================================================
// Get the n-th datablock
//==============================================================================
inline Datablock*
DatablockValue::datablock( size_t n ) const
{
  D_ENTER( "DatablockValue::datablock(size_t)" );

  if ( n < numBlocksM )
  {
    return blocksM[ n ];
  }
  else
  {
    return 0;
  }
}
//==============================================================================
// Get the current datablock number
//==============================================================================
inline size_t
DatablockValue::getCurrentBlockNum() const
{
  return currentBlockM;
}


}

#endif // DATABLOCKVALUE_HPP
