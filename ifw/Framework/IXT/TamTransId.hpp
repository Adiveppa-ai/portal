#ifndef IXT_TAMTRANSID_HPP
#define IXT_TAMTRANSID_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of class TamTransId.
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
// $RCSfile: TamTransId.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2001/06/27 13:19:52 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TamTransId.hpp,v $
// Revision 1.2  2001/06/27 13:19:52  sd
// - New function String tamStreamName(Long)
//
// Revision 1.1  2001/06/27 12:31:14  sd
// - New iScript function tamTransId()
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{
class Integrate;

/** <b><tt>TamTransId</tt></b> is the iScript function node to access
 *  the current transaction id.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TamTransId.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/27 13:19:52 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class TamTransId : public SCR::DecimalNode
{
  public:
    /**@name TamTransId constructors and destructor */
    //@{

    /** Destructor
     */
    ~TamTransId();

    //@}


    /**@name TamTransId public methods */
    //@{

    /** Execute the tamTransId() function
     *  @return The current transaction id
     */
    virtual const BAS::Decimal& result();

    /** Factory method for the function node creation
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

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    TamTransId( Integrate* extension );

  private:
    // Hide the copy constructor and assignment operator
    TamTransId( const TamTransId& );
    const TamTransId& operator=( const TamTransId& );
   
    // Instance members
    Integrate* extensionM;
    BAS::Decimal    transIdM;
};
}
#endif // TAMTRANSID_HPP
