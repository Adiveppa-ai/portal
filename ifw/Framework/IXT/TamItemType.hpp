#ifndef IXT_TAMITEMTYPE_HPP
#define IXT_TAMITEMTYPE_HPP

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
//   Declaration of class TamItemType.
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
// $RCSfile: TamItemType.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/06/28 06:38:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TamItemType.hpp,v $
// Revision 1.1  2001/06/28 06:38:14  sd
// - Initial revision
//
// Revision 1.1  2001/06/27 13:25:43  sd
// - New function String tamItemType(Long)
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

/** <b><tt>TamItemType</tt></b> is the iScript function node to 
 *  access the stream extensions of the current transaction.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TamItemType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/28 06:38:14 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class TamItemType : public SCR::LongNode
{
  public:
    /**@name TamItemType constructors and destructor */
    //@{

    /** Destructor
     */
    ~TamItemType();

    //@}


    /**@name TamItemType public methods */
    //@{

    /** Execute the tamItemType() function
     *  @return The specified item' stream name
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
     *  @param indexNode Pointer to the item index node
     */
    TamItemType( Integrate* extension,
                     SCR::LongNode*  indexNode );

  private:
    // Hide the copy constructor and assignment operator
    TamItemType( const TamItemType& );
    const TamItemType& operator=( const TamItemType& );
   
    // Instance members
    Integrate* extensionM;
    SCR::LongNode*  indexNodeM;
};
}
#endif // TAMITEMTYPE_HPP
