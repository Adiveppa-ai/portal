#ifndef LRP_STATE_HPP
#define LRP_STATE_HPP

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
//   Definition of the class State. This class is used to construct a DFA
//   for the LR(1)-Grammar.
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
// $RCSfile: State.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/11/21 12:50:37 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: State.hpp,v $
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef   LRP_ITEM_HPP
  #include "LRP/Item.hpp"
#endif

namespace LRP
{
typedef RWTValMap<int,int,less<int> >         TransitionMap;
typedef RWTValMapIterator<int,int,less<int> > TransitionMapIterator;

/** <b><tt>State</tt></b> is a state in the DFA constructed for the LR(1)-
 *  Parser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: State.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2000/11/21 12:50:37 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class State D_THREADINFO
{
  public:
    /**@name State constructors and destructor */
    //@{

    /** Default constructor (must be implemented because of RWTPtrSortedVector)
     */
    State();

    /** Constructor
     *  @param items The items for this parser state
     */
    State( const ItemSet& items );

    /** Destructor
     */
    ~State();

    //@}

    /**@name State public methods */
    //@{

    /** Get the id of the state
     *  @return The id
     */
    int stateId() const;

    /** Set the id of the state
     *  @param id The new state id
     */
    void stateId( int id );

    /** Get the items of the state
     *  @return Reference to item set
     */
    const ItemSet& items() const;

    /** Comparison operator for the RWTPtrMap
     *  @return <b>true</b> on left < right, <b>false</b> otherwise
     */
    bool operator()( const State& left, const State& right ) const;

    /** Add a new transition to the state
     *  @param symbol The symbol for the transition
     *  @param succState The successor state for the transition
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addTransition( int symbol, int succState );

    /** Get an iterator for the transitions
     *  @return The iterator
     */
    TransitionMapIterator transitions();

    //@}

#ifdef __aix
    bool operator==( const State& other ) const
    {
      return( this == &other );
    }
    bool operator<( const State& other ) const
    {
      return( this < &other );
    }
#endif

  private:

    // instance members
    int               stateIdM;
    ItemSet       itemsM;
    TransitionMap transMapM;
};

//==============================================================================
// Get the id of the state
//==============================================================================
inline int
State::stateId() const
{
  return stateIdM;
}

//==============================================================================
// Set the id of the state
//==============================================================================
inline void
State::stateId( int id )
{
  stateIdM = id;
}

//==============================================================================
// Get the items of the state
//==============================================================================
inline const ItemSet&
State::items() const
{
  return itemsM;
}

//==============================================================================
// Get an iterator for the transition map
//==============================================================================
inline TransitionMapIterator 
State::transitions() 
{
  return TransitionMapIterator( transMapM );
}
}

#endif // STATE_HPP
