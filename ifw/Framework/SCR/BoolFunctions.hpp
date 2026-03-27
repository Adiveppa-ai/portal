#ifndef SCR_BOOLFUNCTIONS_HPP
#define SCR_BOOLFUNCTIONS_HPP

//==============================================================================
//
// 1998,1999 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Bool functions for the interpreter.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: BoolFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:00:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: BoolFunctions.hpp,v $
// Revision 1.3  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.2  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.1  2000/03/10 08:19:24  sd
// Moved from Comparison to this file.
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
namespace SCR
{
/**<b><tt>BoolAND</tt></b> is the function node for the boolean AND
 * operation
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: BoolFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolAND : public BoolNode
{
  public:

    /**@name BoolAND constructors and destructor */
    //@{
    
    /** Destructor
     */
    virtual ~BoolAND();

    //@}

    /**@name BoolAND public methods */
    //@{
    
    /** Evaluate the boolean operation
     *  @return result of the boolean operation
     */
    virtual bool result();

    /** Create a boolean AND function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param left Left operand
     *  @param right Right operand
     */
    BoolAND( BoolNode* left,
                 BoolNode* right );
    
    // instance members
    BoolNode* leftM;
    BoolNode* rightM;
};

/**<b><tt>BoolOR</tt></b> is the function node for the boolean OR operation.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: BoolFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:57 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolOR : public BoolNode
{
  public:

    /**@name BoolOR constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~BoolOR();

    //@}
    
    /**@name BoolOR public methods */
    //@{

    /** Evaluate the boolean operation
     *  @return result of the boolean operation
     */
    virtual bool result();
    
    /** Create a boolean OR function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}
    

  protected:

    /** Constructor
     *  @param left Left operand
     *  @param right Right operand
     */
    BoolOR( BoolNode* left,
                BoolNode* right );

    // instance members
    BoolNode* leftM;
    BoolNode* rightM;
};
}
#endif // BOOLFUNCTIONS_HPP
