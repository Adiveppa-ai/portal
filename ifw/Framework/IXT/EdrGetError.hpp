#ifndef EXE_EDRGETERROR_HPP
#define EXE_EDRGETERROR_HPP

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
//   Declaration of the class EdrGetError. This class is the iScript 
//   function node for the function edrGetError().
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
// $RCSfile: EdrGetError.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/09/25 12:57:56 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrGetError.hpp,v $
// Revision 1.1  2001/09/25 12:57:56  sd
// - PETS #39641 Missing set of functions to access edr errors
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
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

/** <b><tt>EdrGetError</tt></b> is the iScript function node class for the
 *  function Bool edrGetError(String).
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrGetError.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/25 12:57:56 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrGetError : public SCR::StringNode
{
  public:
    /**@name EXE_EdrGetError constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrGetError();

    //@}


    /**@name EXE_EdrGetError public methods */
    //@{

    /** Execute the edrGetError() function
     *  @return The error name on success, empty string otherwise
     */
    virtual const BAS::String& result();
     
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
     * @param indexNode Pointer to the first parameter node
     */
    EdrGetError( Integrate* extension,
                     SCR::LongNode*  indexNode );

  private:
    // Hide the copy constructor and assignment operator
    EdrGetError( const EdrGetError& );
    const EdrGetError& operator=( const EdrGetError& );

    // Instance members
    Integrate* extensionM;
    SCR::LongNode*  indexNodeM;
};
}
#endif // EXE_EDRGETERROR_HPP
