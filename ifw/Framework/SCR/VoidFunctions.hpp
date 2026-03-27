#ifndef SCR_VOIDFUNCTIONS_HPP
#define SCR_VOIDFUNCTIONS_HPP

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
//   Declaration of the functions returning void.
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
// $RCSfile: VoidFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:04:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: VoidFunctions.hpp,v $
// Revision 1.11  2000/09/26 13:33:04  sd
// - Module SCR is now only dependent from BAS
//
// Revision 1.10  2000/09/08 15:35:06  sd
// - new functions String formatName() and
//                 Void   scriptUsable(Bool) added.
//
// Revision 1.9  2000/09/08 15:04:32  sd
// - Function scriptUsable() added.
//
// Revision 1.8  2000/08/17 11:35:40  sd
// - first version with iScript extensions
//
// Revision 1.7  2000/04/18 08:12:58  sd
// - new Function Void stopFormat(Void) added.
//
// Revision 1.6  2000/03/31 12:27:13  sd
// - New function `String regString(String)' added to interpreter.
//
// Revision 1.5  2000/03/17 09:29:42  sd
// - Support for sending events added.
// - New function Bool sendEvent(String) added to script language.
//
// Revision 1.4  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.3  2000/03/14 13:04:36  sd
// - Basic function support added.
// - At startup the function BEGIN and at destuction the function END is
//   called automatically.
//
// Revision 1.2  2000/03/10 08:20:12  sd
// Changed the interface for the factory functions.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// Initial revision.
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif

namespace SCR
{
class Interpreter;

/**<b><tt>ScriptUsable</tt></b> is the function node for the 
 * Void scriptUsable(Bool) function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: VoidFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:38 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ScriptUsable : public VoidNode
{
  public:
    /**@name ScriptUsable constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~ScriptUsable();

    //@}

    /**@name ScriptUsable public functions */
    //@{
    
    /** Execute the function
     */
    virtual void result();
    
    /** Create a scriptUsable() function node.
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
     *  @param interpreter The interpreter for execution
     *  @param usableNode The usable flag node
     */
    ScriptUsable( Interpreter* interpreter,
                      BoolNode*    usableNode );

    // instance members
    Interpreter* interpreterM;
    BoolNode*    usableNodeM;
};

/**<b><tt>IXT_LogStdout</tt></b> is the function node for the logStdout()
 * function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: VoidFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:38 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LogStdout : public VoidNode
{
  public:
    /**@name LogStdout constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~LogStdout();

    //@}

    /**@name LogStdout public functions */
    //@{
    
    /** Execute the function
     */
    virtual void result();
    
    /** Create a logFormat() function 
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
     *  @param string String to write to format log
     */
    LogStdout( StringNode* string );


  private:
    // Hide default and copy constructor
    LogStdout();
    LogStdout( const LogStdout& other );
    const LogStdout& operator=( const LogStdout& other );

    // instance members
    StringNode* stringM;
};
}

#endif // VOIDFUNCTIONS_HPP
