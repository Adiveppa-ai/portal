#ifndef LRP_TRANSITION_HPP
#define LRP_TRANSITION_HPP

//==============================================================================
//
//             1998, 1999, 2000 (c) Copyright by SOLUTION42 AG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: LRP 
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Transition.
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
// $RCSfile: Transition.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2001/04/06 11:36:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Transition.hpp,v $
// Revision 1.2  2001/04/06 11:36:57  sd
// - Parser adjusted to support new iScript function interface
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

namespace SCR 
{
class Function;
}
namespace LRP
{

/** <b><tt>Transition</tt></b> is used to handle all transitions between
 *  states.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Transition.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/06 11:36:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class Transition D_THREADINFO
{
  public:

    typedef enum
    {
      GOTO,
      SHIFT,
      REDUCE
    } TransitionType;

    //**@name Transition contructors and destructor */
    //@{

    /** Constructor for a GOTO or a SHIFT transition
     *  @param transType The transition type
     *  @param succState The successort state
     *  @param function The statement to execute
     */
    Transition( TransitionType transType,
                    size_t         succState,
                    SCR::Function*  function );

    /** Constructor for a REDUCE transition
     *  @param transType The transition type (must be REDUCE)
     *  @param numPops The number of symbols to pop from the stack
     *  @param newSymbol The new symbol to push on the stack
     *  @param function The statement to execute
     */
    Transition( TransitionType transType,
                    size_t         numPops,
                    size_t         pushSymbol,
                    SCR::Function*  function );

    /** Destructor
     */
    ~Transition();

    //@}

    /**@name Transition public methods */
    //@{

    /** Get the transition type
     *  @return The transition type
     */
    TransitionType transitionType() const;

    /** Get the symbol to push for the transition
     *  @return The new symbol to push on the stack
     */
    size_t pushSymbol() const;

    /** Get the successor state for the transition
     *  @return The successor state
     */
    size_t succState() const;

    /** Get the number of symbols to pop
     *  @return The number of symbols to pop from the stack
     */
    size_t numPops() const;

    /** Get the function to execute
     *  @return Pointer to statement to execute (can be 0)
     */
    SCR::Function* function() const;

    //@}

  private:
    TransitionType transTypeM;
    size_t         pushSymbolM;
    size_t         numPopsM;
    size_t         succStateM;
    SCR::Function*  functionM;
};

//==============================================================================
// Get the transition type
//==============================================================================
inline Transition::TransitionType
Transition::transitionType() const
{
  return transTypeM;
}

//==============================================================================
// Get the symbol to push
//==============================================================================
inline size_t
Transition::pushSymbol() const
{
  return pushSymbolM;
}

//==============================================================================
// Get the number of symbols to pop from stack
//==============================================================================
inline size_t
Transition::numPops() const
{
  return numPopsM;
}

//==============================================================================
// Get the successor state
//==============================================================================
inline size_t
Transition::succState() const
{
  return succStateM;
}

//==============================================================================
// Get the function to execute
//==============================================================================
inline SCR::Function*
Transition::function() const
{
  return functionM;
}
}
#endif // TRANSITION_HPP
