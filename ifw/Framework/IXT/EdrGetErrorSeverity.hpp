#ifndef EXE_EDRGETERRORSEVERITY_HPP
#define EXE_EDRGETERRORSEVERITY_HPP

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
//   Declaration of the class EdrGetErrorSeverity. This class is the iScript 
//   function node for the function edrGetErrorSeverity().
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Mike Ammon
//------------------------------------------------------------------------------
//
// Revision 1.1  2003/06/03 15:27:56  ammon
// - CO 39102: Add function for getting severity of individual errors.
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

/** <b><tt>EdrGetErrorSeverity</tt></b> is the iScript function node class for the
 *  function Bool edrGetError(String).
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrGetErrorSeverity.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/25 12:57:56 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrGetErrorSeverity : public SCR::LongNode
{
  public:
    /**@name EXE_EdrGetErrorSeverity constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrGetErrorSeverity();

    //@}


    /**@name EXE_EdrGetErrorSeverity public methods */
    //@{

    /** Execute the edrGetErrorSeverity() function
     *  @return The error severity on success, -1 otherwise
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
     * @param indexNode Pointer to the first parameter node
     */
    EdrGetErrorSeverity( Integrate* extension,
                     SCR::LongNode*  indexNode );

  private:
    // Hide the copy constructor and assignment operator
    EdrGetErrorSeverity( const EdrGetErrorSeverity& );
    const EdrGetErrorSeverity& operator=( const EdrGetErrorSeverity& );

    // Instance members
    Integrate* extensionM;
    SCR::LongNode*  indexNodeM;
};
}
#endif // EXE_EDRGETERRORSEVERITY_HPP
