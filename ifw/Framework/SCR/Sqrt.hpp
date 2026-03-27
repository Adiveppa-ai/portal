#ifndef SCR_SQRT_HPP
#define SCR_SQRT_HPP

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
//   Declaration of the iScript sqrt() function.
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
// $RCSfile: Sqrt.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:03:53 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Sqrt.hpp,v $
// Revision 1.1  2001/12/18 15:26:21  sd
// - PETS #42574 Enhancements for LERG support
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

/** <b><tt>Sqrt</tt></b> is the iScript square root function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Sqrt.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:53 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Sqrt : public DecimalNode
{
  public:
    /**@name Sqrt constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Sqrt();

    //@}

    /**@name Sqrt public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::Decimal& result();

    /** Create a sqrt() 
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
     *  @param value Decimal node as input parameter
     */
    Sqrt( DecimalNode* value ); 

    // instance members
    DecimalNode* valueM;
    BAS::Decimal      resultM;
};
}
#endif // SQRT_HPP
