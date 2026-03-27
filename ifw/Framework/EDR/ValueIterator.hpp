#ifndef EDR_VALUEITERATOR_HPP
#define EDR_VALUEITERATOR_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Iterator for Values. This class is only used by the input and output
//   mapping to access the single Values in a much faster way than single
//   access.
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
// $RCSfile: ValueIterator.hpp,v $
// $Revision: 1.5 $
// $Author: sd $
// $Date: 2001/09/15 17:49:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ValueIterator.hpp,v $
// Revision 1.5  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.4  2001/08/07 12:58:46  mwriedt
// - PETS #37618: Code Review.
//
// Revision 1.3  2001/04/23 15:05:49  sd
// - Include for "BlockIndex.hpp" added
//
// Revision 1.2  2001/04/23 14:53:16  sd
// - Index splitted to IndexBase, Index and BlockIndex
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.9  2001/03/22 09:30:07  sd
// - Value iterator improved?
//
// Revision 1.7  2001/03/13 13:45:35  sd
// - Backup version
//
// Revision 1.5  2001/03/12 15:19:20  sd
// - output processing corrected
//
// Revision 1.3  2001/03/09 14:08:12  sd
// - Performance test
//
// Revision 1.1  2001/03/09 12:30:40  sd
// - ValueIterator added.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   EDR_DATABLOCK_HPP
  #include "EDR/Datablock.hpp"
#endif

namespace EDR
{
typedef RWTValOrderedVector<size_t> CurrentVector;
class Container;
class Value;

/** <b><tt>ValueIterator</tt></b> is a class that is only used by the 
 *  input and the output mapping to access the Values in a very fast
 *  manner.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ValueIterator.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 17:49:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class ValueIterator D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name ValueIterator constructors and destructor */
    //@{

    /** Constructor
     */
    ValueIterator();

    /** Destructor
     */
    ~ValueIterator();

    //@}


    /**@name ValueIterator public methods */
    //@{

    /** Get the failure string
     *  @return Reference for the failure string
     */
    const BAS::String& failure() const;

    /** Add a new value index to the Iterator
     *  @param index The edr container index to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addIndex( const Index& index );

    /** Reset the iterator
     *  @param edr EDR container to iterate
     */
    bool reset( const Container* edr );

    /** Reset the iterator using a current vector
     *  @param edr EDR container to iterate
     *  @param currentVector The current vector for the different levels
     */
    bool reset( const Container*     edr,
                const CurrentVector& currentVector );

    /** Get the next Value from the iterator. This is the secure version,
     *  if you want faster access and you know the number of values inside the
     *  iterator use unsecureNext() for faster access
     *  @return Pointer to the next value or 0
     */
    Value* next();

    /** Get the next Value this is the fast but unsecure version. You
     *  have to know that the iterator contains more values!
     *  @return Pointer to the next value
     */
    Value* unsecureNext();

    //@}

  protected:

    /* Class for storing information about the iteration values. The class
     * stores the local index of the datablock to use and the index of the
     * value inside this datablock
     */
    class ValueData
    {
      public:
        /* Default constructor */
        ValueData() 
          : blockNumberM( 0 ),
            valueNumberM( 0 )
        {
        }

        /* Constructor for direct initialization */
        ValueData( size_t          blockNumber,
                       size_t          valueNumber )
          : blockNumberM( blockNumber ),
            valueNumberM( valueNumber )
        {
        }

        size_t blockNumberM;
        size_t valueNumberM;
    };

    /* Class for storing information about the datablocks used in iteration.
     * The class stores the index for the datablock to use and a pointer to
     * the datablock. This pointer is intialized in the reset() function.
     */
    class BlockData
    {
      public:
        /* Default constructor */
        BlockData()
          : datablockM(0)
        {
        }

        /* Constructor for direct initialization */
        BlockData( Datablock*        datablock, 
                       const BlockIndex& blockIndex )
          : datablockM( datablock ),
            blockIndexM( blockIndex )
        {
        }

        Datablock* datablockM;
        BlockIndex blockIndexM;
    };

    /* Set the failure string
     * @param msg The failure message
     */
    void failure( const BAS::String& msg );

    /* Add a new block to the internal array
     * @param blockData The block data to append
     */
    void addBlockData( const BlockData& blockData );

    /* Add new value data to the internal array
     * @param valueData The value data to append
     */
    void addValueData( const ValueData& valueData );

  private:

    /** Copy constructor (not implemented)
     */
    ValueIterator( const ValueIterator& other );


    // instance members
    ValueData*                     valueDataM;
    size_t                             valueDataCapacityM;
    BlockData*                     blockDataM;
    size_t                             blockDataCapacityM;
    Value**                        valueM;
    size_t                             numValuesM;
    size_t                             numBlocksM;
    BAS::String                         failureM;
    Value**                        currentPtrM;
    Value**                        endPtrM;
};

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
ValueIterator::failure() const
{
  return failureM;
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
ValueIterator::failure( const BAS::String& msg )
{
  failureM = msg;
}

//==============================================================================
// Get the next value
//==============================================================================
inline Value*
ValueIterator::unsecureNext()
{
  RWPRECONDITION( currentPtrM != endPtrM );

  return *currentPtrM++;
}

//==============================================================================
// Get the next value
//==============================================================================
inline Value*
ValueIterator::next()
{
  if ( currentPtrM == endPtrM )
  {
    return 0;
  }

  return unsecureNext();
}
}
#endif // VALUEITERATOR_HPP
