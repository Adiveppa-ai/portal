#ifndef IXT_TAMNUMTRANSITEMS_HPP_HPP
#define IXT_TAMNUMTRANSITEMS_HPP_HPP

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
//   Declaration of class TamNumTransItems.
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
// $RCSfile: TamNumTransItems.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/06/27 12:44:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TamNumTransItems.hpp,v $
// Revision 1.1  2001/06/27 12:44:38  sd
// - New iScript function Long tamNumTransItems()
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

/** <b><tt>TamNumTransItems</tt></b> is the iScript function node to 
 *  access the number of trans items for the current transaction.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TamNumTransItems.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/27 12:44:38 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class TamNumTransItems : public SCR::LongNode
{
  public:
    /**@name TamNumTransItems constructors and destructor */
    //@{

    /** Destructor
     */
    ~TamNumTransItems();

    //@}


    /**@name TamNumTransItems public methods */
    //@{

    /** Execute the tamNumTransItems() function
     *  @return The current transaction id
     */
    virtual int64 result();

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
    TamNumTransItems( Integrate* extension );

  private:
    // Hide the copy constructor and assignment operator
    TamNumTransItems( const TamNumTransItems& );
    const TamNumTransItems& operator=( const TamNumTransItems& );
   
    // Instance members
    Integrate* extensionM;
};
}
#endif // TAMNUMTRANSITEMS_HPP_HPP
