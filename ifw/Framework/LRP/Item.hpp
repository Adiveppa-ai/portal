#ifndef LRP_ITEM_HPP
#define LRP_ITEM_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Definition of a LR(1) grammar item.
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
// $RCSfile: Item.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2001/09/15 22:10:58 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Item.hpp,v $
// Revision 1.2  2001/09/15 22:10:58  sd
// - PETS 37618 Warnings removed
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   RW_TOOLS_TVSRTVEC_H
  #include <rw/tvsrtvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   LRP_PRODUCTION_HPP
  #include "LRP/Production.hpp"
#endif

namespace LRP
{
typedef RWTValSortedVector<int,less<int> > ItemSet;
typedef RWTValOrderedVector<int>           RuleVector;

/** <b><tt>Item</tt></b> is the class for the items of a LR(1) grammar.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Item.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/15 22:10:58 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class Item D_THREADINFO
{
  public:

    /**@name Item constructors and destructor */
    //@{

    /** Default constructor (only implemented because the Rogue Wave
     *  SortedVector needs a default constructor
     */
    Item();

    /** Constructor
     *  @param leftSide Id of the left side symbol of the production rule
     */
    Item( int leftSide );

    /** Constructor for initialization from production
     *  @param production The production to initialize from
     */
    Item( const Production& production );

    /** Destructor
     */
    ~Item();

    //@}

    /**@name Item public methods */
    //@{

    /** Get the id of the item's left side
     *  @return The id of the left side symbol
     */
    int leftSide() const;

    /** Get the id of a symbol on the right side
     *  @param idx The index of the symbol
     *  @return The symbols id
     */
    int rightSide( size_t idx ) const;
   
    /** Get the lookahead symbol at index
     *  @param idx The index of the symbol
     *  @return The symbols id
     */
    int lookahead( size_t idx ) const;

    /** Get the number of symbols on the right side
     *  @return The number of symbols
     */
    int numRightSideSymbols() const;

    /** Get the number of lookahead symbols
     *  @return The number of symbols
     */
    int numLookaheadSymbols() const;

    /** Get the id of the item's current symbol 
     *  @return The id of the current symbol, -1 if no current symbol
     */
    int currentSymbol() const;

    /** Get the current position
     *  @return The current position
     */
    int currentPosition() const;

    /** Set the current position
     *  @param The new current position
     */
    void currentPosition( size_t idx );

    /** Append a rightside symbol to the item
     *  @param symbolId The symbols id
     */
    void append( int symbolId );

    /** Add a look ahead symbol to the item
     *  @param symbolId Look ahead symbol to add
     */
    void addLookahead( int symbolId );

    /** Set the look ahead symbol of the item
     *  @param symbolId Look ahead symbol to set
     */
    void setLookahead( int symbolId );

    /** Set the item id
     *  @param id The id to set
     */
    void itemId( int id );

    /** Get the item id
     *  @return The item's id
     */
    int itemId() const;

    /** Comparison operator for the RWTPtrMap
     *  @return <b>true</b> on left < right, <b>false</b> otherwise
     */
    bool operator()( const Item& left, const Item& right ) const;

    /** Get the string + lookahead behind the current symbol
     *  @return The string
     */
    String getStringAndLookaheadBehindCurrentSymbol() const;

    /** Get the successor item for the item
     *  @return The successor item if existent, otherwise a copy of self
     */
    Item successorItem() const;

    /** Get the production id
     *  @return The id
     */
    int productionId() const;

    //@}

#ifdef __aix
    bool operator==( const Item& other ) const
    {
      return( this == &other );
    }
    bool operator<( const Item& other ) const
    {
      return( this < &other );
    }
#endif

  private:

    // instance members
    int            itemIdM;
    int            productionIdM;
    int            succItemIdM;
    int            positionM;
    int            leftSideM;
    String     rightSideM;
    String     lookAheadM;
};

typedef RWTValSortedVector<int,less<int> > ItemSet;

//==============================================================================
// Get the left side symbol of the item
//==============================================================================
inline int
Item::leftSide() const
{
  return leftSideM;
}

//==============================================================================
// Get the current symbol of the item
//==============================================================================
inline int
Item::currentSymbol() const
{
  if ( positionM < (int) rightSideM.entries() )
  {
    return rightSideM( positionM );
  }
  else
  {
    return -1;
  }
}

//==============================================================================
// Add a lookahead symbol to the item
//==============================================================================
inline void
Item::addLookahead( int symbolId )
{
  lookAheadM.append( symbolId );
}

//==============================================================================
// Set the lookahead symbol of the item
//==============================================================================
inline void
Item::setLookahead( int symbolId )
{
  lookAheadM.clear();
  lookAheadM.append( symbolId );
}

//==============================================================================
// Set the item's id
//==============================================================================
inline void
Item::itemId( int id )
{
  itemIdM = id;
}

//==============================================================================
// Get the item's id
//==============================================================================
inline int
Item::itemId() const
{
  return itemIdM;
}

//==============================================================================
// Get the current position
//==============================================================================
inline int
Item::currentPosition() const
{
  return positionM;
}

//==============================================================================
// Set the current position
//==============================================================================
inline void
Item::currentPosition( size_t idx )
{
  if ( idx <= rightSideM.entries() )
  {
    positionM = idx;
  }
}

//==============================================================================
// Get the number of symbols on the right side
//==============================================================================
inline int
Item::numRightSideSymbols() const
{
  return rightSideM.entries();
}

//==============================================================================
// Get a symbol on the right side
//==============================================================================
inline int
Item::rightSide( size_t idx ) const
{
  return rightSideM( idx );
}

//==============================================================================
// Get the number of lookahead symbols
//==============================================================================
inline int
Item::numLookaheadSymbols() const
{
  return lookAheadM.entries();
}

//==============================================================================
// Get a lookahead symbol
//==============================================================================
inline int
Item::lookahead( size_t idx ) const
{
  return lookAheadM( idx );
}

//==============================================================================
// Get the production id
//==============================================================================
inline int
Item::productionId() const
{
  return productionIdM;
}
}

#endif // ITEM_HPP
