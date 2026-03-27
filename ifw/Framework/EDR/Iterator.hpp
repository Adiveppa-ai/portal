#ifndef EDR_ITERATOR_HPP
#define EDR_ITERATOR_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Iterator.
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
// $RCSfile: Iterator.hpp,v $
// $Revision: 1.12 $
// $Author: sd $
// $Date: 2002/01/15 09:28:23 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.12  2005/03/11  ammon
// PRSF00156493   Add access functions for array index.
//
// Revision 1.11  2002/01/15 09:28:23  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.10  2001/09/17 22:09:38  sd
// - PETS #39540 Iterator interface not sufficient for duplication
//
// Revision 1.9  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.8  2001/08/07 12:58:46  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.7  2001/06/12 12:00:55  sd
// - Pointer to factory added to container index
// - New method addIndex() added to iterator
//
// Revision 1.6  2001/06/11 12:12:15  sd
// - Special case for iterating with root block indices added
//
// Revision 1.5  2001/06/11 10:52:17  sd
// - New function duplicateDatablock() added
//
// Revision 1.4  2001/04/26 15:23:25  sd
// - ContainerIndex introduced
//
// Revision 1.3  2001/04/26 10:22:54  sd
// - Assignment operator is now private
//
// Revision 1.2  2001/04/23 14:53:16  sd
// - Index splitted to IndexBase, Index and BlockIndex
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.6  2001/03/19 12:13:55  sd
// - New function addDatablock() added to iterator
//
// Revision 1.5  2000/10/20 10:02:01  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_FACTORY_HPP
  #include "EDR/Factory.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif
#ifndef   EDR_ACCESSORIF_H
  #include "EDR/AccessorIf.hpp"
#endif

namespace EDR
{
/** <b><tt>Iterator</tt></b> is used to iterate over the tree structure
 *  of an EDR container.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Iterator.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.11 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/15 09:28:23 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>                
 */
class Iterator : public EDR::AccessorIf D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Iterator constructors and destructor */
    //@{

    /** Default constructor
     */
    Iterator();

    /** Constructor with index
     *  @param index Index for iteration
     */
    Iterator( const BlockIndex& index );

    /** Destructor
     */
    ~Iterator();

    //@}

    /**@name Iterator public methods */
    //@{

    /** Reset the iterator for the specified edr container
     *  @param edr The edr for which the iterator should be initialized
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool reset( Container* edr );

    /** Check whether the Iterator is valid or not
     *  @return <b>true</b> if iterator is valid, <b>false</b> otherwise
     */
    bool isValid() const;

    /** Advance to the first/next element
     *  @return <b>true</b> if iterator is valid, <b>false</b> otherwise
     */
    bool operator()();

    /** Advance to the first/next datablock specified by index
     *  @return <b>true</b> if iterator is valid, <b>false</b> otherwise
     */
    bool operator()( const BlockIndex& index );

    /** Get the current string value for the index
     *  @param index The index for the field to access
     *  @return Reference to string
     */
    const BAS::String& getString( const Index& index ) const;

    /** Set the current string value for the index
     *  @param index The index for the field to access
     *  @return Reference to string
     */
    bool setString( const Index& index, const BAS::String& value ) ;

    /** Get the current decimal value for the index
     *  @param index The index for the field to access
     *  @return Reference to decimal
     */
    const BAS::Decimal& getDecimal( const Index& index ) const;

    /** Set the current decimal value for the index
     *  @param index The index for the field to access
     *  @return Reference to decimal
     */
    bool setDecimal( const Index& index, const BAS::Decimal& value );

    /** Get the current date value for the index
     *  @param index The index for the field to access
     *  @return Reference to string
     */
    const BAS::DateTime& getDate( const Index& index ) const;

    /** Set the current datetime value for the index
     *  @param index The index for the field to access
     *  @return Reference to string
     */
    bool setDate( const Index& index, const BAS::DateTime& value ) ;

    /** Get the current long value for the index
     *  @param index The index for the field to access
     *  @return Reference to Long
     */
    int64 getLong( const Index& index ) const;

    /** Set the current long value for the index
     *  @param index The index for the field to access
     *  @return Reference to Long
     */
    bool setLong( const Index& index, int64 value );

   /** Get the current Poid value for the index
     *  @param index The index for the field to access
     *  @return Reference to the Object Id (Poid)
     */
    const EDR::CompactPoid&  getCompactPoid( const Index& index ) const;

    /** Set the current Poid value for the index
     *  @param index The index for the field to access
     *  @return Reference to the Object Id (Poid)
     */
    bool setCompactPoid( const Index& index, const EDR::CompactPoid& value );

    /** Set the edr index used by the iterator
     *  @param index The edr index to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setIndex( const BlockIndex& index );

    /** Add a new index to the iterator
     *  @param index The edr index to add
     *  @param failure Buffer for returning failure messages
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addIndex( const BlockIndex& index,
                   BAS::String&           failure );

    /** Add a new datablock to the edr container
     *  @param blockIndex The block index of the datablock to add
     *  @param newCurrentVector Return buffer for the new (duplicated) datablock's
     *                          current vector
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addDatablock( const BlockIndex& blockIndex,
                       CurrentVector& newCurrentVector = 
                         Container::nullCurrentVectorCM ) const;

    /** Add new datablock to the edr container and return pointer to it
     *  @param blockIndex The block index of the datablock to add
     *  @param newCurrentVector Return buffer for the new 
     *         datablock's current vector
     *  @return  pointer to new datablock
     */
    Datablock * addAndGetDatablock( const BlockIndex& blockIndex,
                       CurrentVector& newCurrentVector = 
                       Container::nullCurrentVectorCM ) const;

    /** Duplicate the current datablock
     *  @param blockIndex The block index of the datablock to duplicate
     *  @param newCurrentVector Return buffer for the new (duplicated) datablock's
     *                          current vector
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool duplicateDatablock( const BlockIndex& blockIndex,
                             CurrentVector& newCurrentVector = 
                               Container::nullCurrentVectorCM ) const;

    /** Get the relative position of a datablock in iteration
     *  @param blockIndex The block for which to access the position
     *  @return The position of the datablock
     */
    size_t relativePosition( const BlockIndex& blockIndex ) const;

    /** Get the iterator's current vector
     *  @return Reference to the used current vector
     */
    const CurrentVector& currentVector() const;

    /** Get the array index ID of a datablock
     *  @param index The block index for the datablock
     *  @return The array index ID of the datablock
     */
    int32 getArrayIndexId( const BlockIndex& index ) const;

    /** Set the array index ID of a datablock
     *  @param index The block index for the datablock
     *  @param currentVector Current values for the different levels
     *  @param value The larray index ID to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setArrayIndexId( const BlockIndex& index,
                          int32             value );

    //@}

  protected:

    /** Check if an index can be used with this iterator
     *  @param index The index to check
     *  @return <b>true</b> if index can be used, <b>false</b> otherwise
     */
    bool indexUsable( const Index& index ) const;

    /** Check if a block index can be used with this iterator
     *  @param index The index to check
     *  @return <b>true</b> if index can be used, <b>false</b> otherwise
     */
    bool blockIndexUsable( const BlockIndex& index ) const;

    /* Check if an block index can be used for an iteration step
     * @return <b>true</b> if index can be used, <b>false</b> otherwise
     */
    bool isIterationIndex( const BlockIndex& index ) const;

  private:

    enum InternalStateT
    {
      FIRST,
      ITERATING,
      FINISHED
    };

    // Hide copy constructor and assignment operator
    Iterator( const Iterator& other );
    const Iterator&  operator=( const Iterator& other );
    
    // instance members
    Container*                      currentEdrM;
    size_t                              startBlockTypeIdM;
    size_t                              depthM;
    size_t                              globalIterationLevelM;
    RWTValOrderedVector<InternalStateT> stateVectorM;
    RWTValOrderedVector<BlockIndex> indexVectorM;
    CurrentVector                   currentVectorM;
    RWTValOrderedVector<size_t>         numBlocksVectorM;

    InternalStateT                      rootBlockStateM;
};

//==============================================================================
// Check wheter the iterator is valid or not
//==============================================================================
inline bool
Iterator::isValid() const
{
  return( startBlockTypeIdM != Factory::illegalBlockTypeCM );
}


//==============================================================================
// Add a new datablock to the EDR container
//==============================================================================
inline bool
Iterator::addDatablock( const BlockIndex& blockIndex,
                            CurrentVector&    newCurrentVector) const
{
  RWPRECONDITION( currentEdrM != 0 );
  RWPRECONDITION( blockIndexUsable( blockIndex ) == true );
  return currentEdrM->addDatablock( blockIndex, 
                                    currentVectorM, 
                                    newCurrentVector );
}

//==============================================================================
// Duplicate the current datablock 
//==============================================================================
inline bool
Iterator::duplicateDatablock( const BlockIndex& blockIndex,
                                  CurrentVector&    newCurrentVector) const
{
  RWPRECONDITION( currentEdrM != 0 );
  RWPRECONDITION( blockIndexUsable( blockIndex ) == true );
  return currentEdrM->duplicateDatablock( blockIndex, 
                                          currentVectorM,
                                          newCurrentVector );
}

//==============================================================================
// Get the relative position of a datablock in iteration
//==============================================================================
inline size_t
Iterator::relativePosition( const BlockIndex& blockIndex ) const
{
  RWPRECONDITION( currentEdrM != 0 );
  RWPRECONDITION( blockIndexUsable( blockIndex ) == true );
  RWPRECONDITION( blockIndex.depth() > 0 );
  return currentVectorM( blockIndex.depth()-1 );
}

//==============================================================================
// Get the used current vector
//==============================================================================
inline const CurrentVector&
Iterator::currentVector() const
{
  return currentVectorM;
}
}
#endif // ITERATOR_HPP
