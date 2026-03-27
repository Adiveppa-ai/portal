#ifndef LRP_ISCRIPTFUNCTIONS_HPP
#define LRP_ISCRIPTFUNCTIONS_HPP

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
//   iScript functions used by the LR(1) parser.
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
// $RCSfile: IScriptFunctions.hpp,v $
// $Revision: 1.13 $
// $Author: sd $
// $Date: 2001/04/24 14:13:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: IScriptFunctions.hpp,v $
// Revision 1.13  2001/04/24 14:13:14  sd
// - Long renamed to Integer
//
// Revision 1.12  2001/04/19 15:42:33  sd
// - Format updates
// - Useless iScript functions removed
//
// Revision 1.11  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.10  2001/04/03 08:15:30  sd
// - Full iScript support
//
// Revision 1.9  2001/03/22 09:30:07  sd
// - Value iterator improved?
//
// Revision 1.8  2001/03/20 09:03:35  sd
// - iScript extension renamed
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif

namespace SCR
{
class Interpreter;
class FctDescr;
class ParserStack;
}
namespace FRM
{
class InputMapping;
class OutputMapping;
}
namespace LRP
{
class IScriptInExt;
class IScriptOutExt;

/** <b><tt>FctLexerState</tt></b> is the function node for changing the
 *  state of the lexical analyser.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: IScriptFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.13 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/24 14:13:14 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class FctLexerState : public SCR::BoolNode
{
  public:
    /**@name FctLexerState constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~FctLexerState();

    //@}


    /**@name FctLexerState public methods */
    //@{

    /** Execute the lexerState() function
     *  @return The result of the function execution
     */
    virtual bool result();

    /** Factory for creation of the function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}

  protected:

    /* Constructor
     * @param extension Pointer to the iScript extension
     * @param lexerState Id of the new lexer state
     */
    FctLexerState( IScriptInExt* extension,
                       size_t            lexerState );

  private:
    // Hide copy constructor and assignment operator
    FctLexerState( const FctLexerState& );
    const FctLexerState operator=( const FctLexerState& );

    // Instance members
    IScriptInExt* extensionM;
    size_t            lexerStateM;
};


}
#endif // ISCRIPTFUNCTIONS_HPP
