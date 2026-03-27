#ifndef LRP_EDRREJECT_HPP
#define LRP_EDRREJECT_HPP

//==============================================================================
//
//   Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//   
//   This material is the confidential property of Oracle Corporation or its
//   licensors and may be used, reproduced, stored or transmitted only in
//   accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the function node for the iScript function edrReject().
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
// $RCSfile: EdrReject.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/07/09 13:52:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrReject.hpp,v $
// Revision 1.1  2001/07/09 13:52:24  sd
// - PETS #36769 need possibility to reject an EDR from iScript on output
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
}
namespace LRP
{
class IScriptOutExt;

/** <b><tt>EdrReject</tt></b> is the function node for rejecting
 *  edr containers in the output plugin.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrReject.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/07/09 13:52:24 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrReject : public SCR::VoidNode
{
  public:
    /**@name EdrReject constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrReject();

    //@}


    /**@name EdrReject public methods */
    //@{

    /** Execute the edrReject() function
     *  @return The result of the function execution
     */
    virtual void result();

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
     */
    EdrReject( IScriptOutExt* outExtension );
    
  private:
    // Hide copy constructor and assignment operator
    EdrReject( const EdrReject& );
    const EdrReject operator=( const EdrReject& );

    // Instance members
    IScriptOutExt* outExtensionM;
};
}
#endif // EDRREJECT_HPP
