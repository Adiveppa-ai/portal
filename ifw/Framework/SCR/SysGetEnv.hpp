#ifndef SCR_SYSGETENV_HPP
#define SCR_SYSGETENV_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//               This material is the confidential property of
//       Oracle Corporation or its subsidiaries or licensors
//    and may be used, reproduced, stored or transmitted only in accordance
//            with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class SysGetEnv.
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
// $RCSfile: SysGetEnv.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:04:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: SysGetEnv.hpp,v $
// Revision 1.1  2002/03/06 13:34:31  sd
// - PETS #43775 request for iScript-function to execute external commands
//               and to read and set EnvVariables
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;

/** <b><tt>SysGetEnv</tt></b> is the iScript function node to access
 *  environment variables.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SysGetEnv.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:24 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class SysGetEnv : public StringNode
{
  public:
    /**@name SysGetEnv constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~SysGetEnv();

    //@}

    /**@name SysGetEnv public methods */
    //@{

    /** Execute the command
     *  @return The contents of the environment variable
     */
    virtual const BAS::String& result();

    /** Create a sysGetEnv() function node
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
     */
    SysGetEnv( StringNode* variableNode );

    // instance members
    StringNode* variableNodeM;
    BAS::String      resultM;
};
}

#endif // SYSGETENV_HPP
