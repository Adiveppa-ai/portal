#ifndef SCR_RETURNSTATEMENT_HPP
#define SCR_RETURNSTATEMENT_HPP

//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//  This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
//   only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the function node class for the iScript return statement.
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
// $RCSfile: ReturnStatement.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:03:44 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ReturnStatement.hpp,v $
// Revision 1.1  2001/04/10 10:50:35  sd
// - Full function support (inclusive return values)
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
/** <b><tt>ReturnStatement</tt></b> is the iScript function node for the
 *  return statement.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ReturnStatement.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:44 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ReturnStatement : public Node
{
  public:
    /**@name ReturnStatement constructors and destructor */
    //@{

    /** Constructor
     */
    ReturnStatement( Node* assignment );

    /** Destructor
     */
    virtual ~ReturnStatement();

    //@}


    /**@name ReturnStatement public methods */
    //@{

    /** Execute the return statement
     *  @return Node::EXEC_RETURN
     */
    virtual int execute();

    /** Check whether the statement returns a result or not
     *  @return <b>true</b>
     */
    virtual bool returnsResult() const;

    //@}

  private:
    // Instance members
    Node* assignmentStatementM;
};
}
#endif // RETURNSTATEMENT_HPP
