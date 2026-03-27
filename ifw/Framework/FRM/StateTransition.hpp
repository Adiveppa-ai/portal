#ifndef FRM_STATETRANSITION_HPP
#define FRM_STATETRANSITION_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FRM
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class StateTransition
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: StateTransition.hpp,v $
// $Revision: 1.2 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StateTransition.hpp,v $
// Revision 1.2  2001/09/27 12:01:18  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.1  2001/07/04 07:17:43  sd
// - Initial revision
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace FRM
{
/** <b><tt>StateTransition</tt></b> stores the state transition information
 *  for the different records.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StateTransition.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:18 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class StateTransition D_THREADINFO
{
  public:

    enum StateTransitionT
    {
      TRANS_SUCC_STATE,
      TRANS_PUSH_STATE,
      TRANS_POP_STATE
    };

    /**@name StateTransition constructors and destructor */
    //@{

// CodeReview  - 08.2001 - cdiab - I - 05.02 one parameter too much
    /** Constructor
     *  @param transitionType The type of the transition (SUCC,PUSH,POP)
     *  @param succStateName The name of the successor state
     *  @param succStateId The id of the successor state
     */
    StateTransition( StateTransitionT  transitionType,
                         const BAS::String& succStateName );

    /** Destructor
     */
    ~StateTransition();

    //@}

    /**@name StateTransition public methods */
    //@{

    /** Get the transition type (SUCC, PUSH, POP)
     *  @return The transition type
     */
    StateTransitionT transitionType() const;

    /** Get the successor state name
     *  @return Reference to the successor name string
     */
    const BAS::String& succStateName() const;

    /** Get the successor state id
     *  @return The successor state id
     */
    int succStateId() const;

    /** Set the successor state id
     *  @param id The new successor state id
     */
    void succStateId( int id );

    //@}

  private:
    // Instance members
    StateTransitionT transitionTypeM;
    BAS::String       succStateNameM;
    int              succStateIdM;
};

//==============================================================================
// Get the transition type
//==============================================================================
inline StateTransition::StateTransitionT
StateTransition::transitionType() const
{
  return transitionTypeM;
}

//==============================================================================
// Get the successor name
//==============================================================================
inline const BAS::String&
StateTransition::succStateName() const
{
  return succStateNameM;
}

//==============================================================================
// Get the successor state id
//==============================================================================
inline int 
StateTransition::succStateId() const
{
  return succStateIdM;
}

//==============================================================================
// Set the successor state id
//==============================================================================
inline void
StateTransition::succStateId( int id )
{
  succStateIdM = id;
}
}
#endif // STATETRANSITION_HPP
