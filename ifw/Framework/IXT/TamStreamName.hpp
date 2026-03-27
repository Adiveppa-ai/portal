#ifndef IXT_TAMSTREAMNAME_HPP
#define IXT_TAMSTREAMNAME_HPP

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
//   Declaration of class TamStreamName.
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
// $RCSfile: TamStreamName.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/06/28 06:38:14 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TamStreamName.hpp,v $
// Revision 1.1  2001/06/28 06:38:14  sd
// - Initial revision
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

/** <b><tt>TamStreamName</tt></b> is the iScript function node to access
 *  the stream names of the current transaction.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TamStreamName.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/06/28 06:38:14 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class TamStreamName : public SCR::StringNode
{
  public:
    /**@name TamStreamName constructors and destructor */
    //@{

    /** Destructor
     */
    ~TamStreamName();

    //@}


    /**@name TamStreamName public methods */
    //@{

    /** Execute the tamStreamName() function
     *  @return The specified item' stream name
     */
    virtual const BAS::String& result();

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
    TamStreamName( Integrate* extension,
                       SCR::LongNode*  indexNode );

  private:
    // Hide the copy constructor and assignment operator
    TamStreamName( const TamStreamName& );
    const TamStreamName& operator=( const TamStreamName& );
   
    // Instance members
    Integrate* extensionM;
    SCR::LongNode*  indexNodeM;
};
}
#endif // TAMSTREAMNAME_HPP
