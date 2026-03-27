#ifndef SCR_LONGTOHEXSTR_HPP
#define SCR_LONGTOHEXSTR_HPP

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
//   Declaration of an iScript function node for the conversion from integer
//   to a hexadecimal string.
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
// $RCSfile: LongToHexStr.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: LongToHexStr.hpp,v $
// Revision 1.3  2001/05/29 12:14:03  sd
// - New function `Long decimalToLong(Decimal)'
//
// Revision 1.2  2001/05/29 08:46:02  sd
// - Initial revision
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

/** <b><tt>LongToHexStr</tt></b> is the iScript function node for the 
 *  conversion from integer values to hexadecimal strings.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LongToHexStr.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:48 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongToHexStr : public StringNode
{
  public:
    /**@name LongToHexStr constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongToHexStr();

    //@}


    /**@name LongToHexStr public methods */
    //@{

    /** Convert a long value to a hexadecimal string
     *  @return The result string
     */
    virtual const BAS::String& result();

    /** Create a longToHexStr() function node
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
     * @param longNode Pointer to the parameter function node
     */
    LongToHexStr( LongNode* longNode );

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    LongToHexStr( const LongToHexStr& other );
    const LongToHexStr& operator=( const LongToHexStr& other );

    // instance members
    LongNode* longNodeM;
    BAS::String    resultM;
};
}
#endif // LONGTOHEXSTR_HPP
