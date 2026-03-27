#ifndef EXE_EDRNUMERRORS_HPP
#define EXE_EDRNUMERRORS_HPP

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
//   Declaration of the class EdrNumErrors. This class is the iScript 
//   function node for the function edrNumErrors().
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
// $RCSfile: EdrNumErrors.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/09/25 12:57:56 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrNumErrors.hpp,v $
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

/** <b><tt>EdrNumErrors</tt></b> is the iScript function node class for the
 *  function edrNumErrors().
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrNumErrors.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/25 12:57:56 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrNumErrors : public SCR::LongNode
{
  public:
    /**@name EXE_EdrNumErrors constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrNumErrors();

    //@}


    /**@name EXE_EdrNumErrors public methods */
    //@{

    /** Execute the edrNumErrors() function
     *  @return The number of errors
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

    /* Constructor
     * @param extension Pointer to the integRate iScript extension
     */
    EdrNumErrors( Integrate*  extension );

  private:
    // Hide the copy constructor and assignment operator
    EdrNumErrors( const EdrNumErrors& );
    const EdrNumErrors& operator=( const EdrNumErrors& );

    // Instance members
    Integrate*  extensionM;
};
}
#endif // EXE_EDRNUMERRORS_HPP
