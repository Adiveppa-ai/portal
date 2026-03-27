#ifndef SCR_DECIMALTOLONG_HPP
#define SCR_DECIMALTOLONG_HPP
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the function node for the function decimalToLong().
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
// $RCSfile: DecimalToLong.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:39 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DecimalToLong.hpp,v $
// Revision 1.1  2001/05/29 12:14:46  sd
// - New function `Long decimalToLong(Decimal)'
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

/** <b><tt>DecimalToLong</tt></b> is the function node for the iScript 
 *  function decimalToLong().
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DecimalToLong.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:39 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalToLong : public LongNode
{
  public:
    /**@name DecimalToLong constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DecimalToLong();

    //@}


    /**@name DecimalToLong public methods */
    //@{

    /** Convert a decimal value to a long value
     *  @return The result value
     */
    virtual int64 result();

    /** Create a decimalToLong() function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> to function node on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:
    
    /* Constructor
     */
    DecimalToLong( DecimalNode* decimalNode );

  private:
    // Hide the copy constructor and assignment operator (not implemented)
    DecimalToLong( const DecimalToLong& other );
    const DecimalToLong& operator=( const DecimalToLong& other );

    // instance members
    DecimalNode* decimalNodeM;
};
}
#endif // DECIMALTOLONG_HPP
