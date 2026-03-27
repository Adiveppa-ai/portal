#ifndef SCR_SYSTEM_HPP
#define SCR_SYSTEM_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
// only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class System.
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
class StringDataNode;

/** <b><tt>System</tt></b> is the iScript function node to execute
 *  system commands.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: System.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:29 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class System : public LongNode
{
  public:
    /**@name System constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~System();

    //@}

    /**@name System public methods */
    //@{

    /** Execute the system command
     *  @return The the exit code
     */
    virtual int64 result();

    /** Create a system() function node
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
     *  @param commandNode The command to execute
     *  @param outputBufferNode The optional buffer for the output
     */
    System( StringNode*     commandNode,
            StringDataNode* outputBufferNode );

    // instance members
    StringNode*     commandNodeM;
    StringDataNode* outputBufferNodeM;
};
}
#endif // SCR_SYSTEM_HPP
