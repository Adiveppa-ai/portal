#ifndef EXE_EDRHASERROR_HPP
#define EXE_EDRHASERROR_HPP

//==============================================================================
//
//   Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//   
//   This material is the confidential property of Oracle Corporation or its
//   licensors and may be used, reproduced, stored or transmitted only in
//   accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrHasError. This class is the iScript 
//   function node for the function edrHasError().
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
// $RCSfile: EdrHasError.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/09/25 12:57:56 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrHasError.hpp,v $
// Revision 1.1  2001/09/25 12:57:56  sd
// - PETS #39641 Missing set of functions to access edr errors
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

/** <b><tt>EdrHasError</tt></b> is the iScript function node class for the
 *  function Bool edrHasError(String).
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrHasError.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/25 12:57:56 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrHasError : public SCR::BoolNode
{
  public:
    /**@name EXE_EdrHasError constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrHasError();

    //@}


    /**@name EXE_EdrHasError public methods */
    //@{

    /** Execute the edrHasError() function
     *  @return <b>true</b> if operation was successful, <b>false</b> otherwise
     */
    virtual bool result();
     
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

    /* Constructor
     * @param extension Pointer to the integRate iScript extension
     * @param errorNode Pointer to the first parameter node
     */
    EdrHasError( Integrate*  extension,
                     SCR::StringNode* errorNode );

  private:
    // Hide the copy constructor and assignment operator
    EdrHasError( const EdrHasError& );
    const EdrHasError& operator=( const EdrHasError& );

    // Instance members
    Integrate*  extensionM;
    SCR::StringNode* errorNodeM;
};
}
#endif // EXE_EDRHASERROR_HPP
