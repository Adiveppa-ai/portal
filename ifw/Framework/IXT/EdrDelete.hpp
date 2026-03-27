#ifndef EXE_EDRDELETE_HPP
#define EXE_EDRDELETE_HPP

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
//   Declaration of the class EXE_EdrDelete. This class is the iScript function
//   node for the function edrDelete().
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
// $RCSfile: EdrDelete.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/04/12 12:22:52 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrDelete.hpp,v $
// Revision 1.1  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.1  2001/04/11 07:37:11  sd
// - New function Bool edrDelete().
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

/** <b><tt>EdrDelete</tt></b> is the iScript function node class for the
 *  function edrDelete().
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrDelete.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/12 12:22:52 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrDelete : public SCR::BoolNode
{
  public:
    /**@name EXE_EdrDelete constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrDelete();

    //@}


    /**@name EXE_EdrDelete public methods */
    //@{

    /** Execute the edrDelete() function
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
     */
    EdrDelete( Integrate* extension );

  private:
    // Hide the copy constructor and assignment operator
    EdrDelete( const EdrDelete& );
    const EdrDelete& operator=( const EdrDelete& );

    // Instance members
    Integrate* extensionM;
};
}
#endif // EXE_EDRDELETE_HPP
