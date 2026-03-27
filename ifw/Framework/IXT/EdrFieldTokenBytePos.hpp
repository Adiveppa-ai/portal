#ifndef IXT_EDRFIELDTOKENBYTEPOS_HPP
#define IXT_EDRFIELDTOKENBYTEPOS_HPP

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
//   
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
// $RCSfile: EdrFieldTokenBytePos.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2002/03/13 08:51:02 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrFieldTokenBytePos.hpp,v $
// Revision 1.1  2002/03/13 08:51:02  sd
// - ClearCase Transition checkin
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   IXT_EDRVALUEACCESS_HPP
  #include "IXT/EdrValueAccess.hpp"
#endif

namespace IXT
{

class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{
class Integrate;

/** <b><tt>EdrFieldTokenBytePos</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFieldTokenBytePos.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2002/03/13 08:51:02 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrFieldTokenBytePos : public SCR::LongNode, public EdrValueAccess
{
  public:
    /**@name EdrFieldTokenBytePos constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrFieldTokenBytePos();

    //@}

    /**@name EdrFieldTokenBytePos public methods */
    //@{

    /** Execute the function
     *  @return The byte position (>=0) of the associated token on success
     *          < 0 otherwise
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
     */
    EdrFieldTokenBytePos( Integrate* extension );

  private:
};
}
#endif // EDRFIELDTOKENBYTEPOS_HPP
