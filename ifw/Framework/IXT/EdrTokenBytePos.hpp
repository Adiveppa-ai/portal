#ifndef IXT_EDRTOKENBYTEPOS_HPP
#define IXT_EDRTOKENBYTEPOS_HPP

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
//   Definition of the class EdrTokenBytePos.
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
// $RCSfile: EdrTokenBytePos.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2002/03/13 08:51:02 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrTokenBytePos.hpp,v $
// Revision 1.1  2002/03/13 08:51:02  sd
// - ClearCase Transition checkin
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

/** <b><tt>EdrTokenBytePos</tt></b> is the iScript function for 
 *  edrTokenBytePos().
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrTokenBytePos.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2002/03/13 08:51:02 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrTokenBytePos : public SCR::LongNode
{
  public:
    /**@name EdrTokenBytePos constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrTokenBytePos();

    //@}


    /**@name EdrTokenBytePos public methods */
    //@{

    /** Execute the function..
     */
    virtual int64 result();

    /** Factory for creation of the function node
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
     *  @param tokenIndexNode Parameter node for the token index
     */
    EdrTokenBytePos( Integrate* extension,
                        SCR::LongNode*  tokenIndexNode );

  private:
    // Hide the copy constructor and assignment operator
    EdrTokenBytePos( const EdrTokenBytePos& );
    const EdrTokenBytePos& operator=( const EdrTokenBytePos& );

    // Instance members
    Integrate* extensionM;
    SCR::LongNode*  tokenIndexNodeM;
};
}
#endif // EDRTOKENBYTEPOS_HPP
