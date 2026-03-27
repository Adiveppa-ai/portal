#ifndef DAT_PREFIXERROR_HPP
#define DAT_PREFIXERROR_HPP

//==============================================================================
//
//      @(#)%Portal Version: PrefixError.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:39:40 %
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: DAT::PrefixDesc
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class PrefixError. This is the iScript function 
//   node for the function prefixError().
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
// $RCSfile: PrefixError.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/09/19 10:50:32 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PrefixError.hpp,v $
// Revision 1.1  2000/09/19 10:50:32  sd
// - Initial revision of the iScript extension.
//
//==============================================================================

#include "SCR/Node.hpp"

// Forward declaration
namespace SCR {
  class FctDescr;
  class Interpreter;
  class ParserStack;
}

namespace DAT
{
namespace PrefixDesc
{

class PrefixIScriptExt;

/** <b><tt>PrefixError</tt></b> is the iScript function node for 
 *  getting the error messages from the prefix extension
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: PrefixError.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2000/09/19 10:50:32 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class PrefixError : public SCR::StringNode
{
  public:
    /**@name PrefixError constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~PrefixError();

    //@}

    /**@name PrefixError public methods */
    //@{

    /** Execute the prefixError() function
     */
    virtual const BAS::String& result();
    
    /** Create a prefixError() function 
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

    PrefixError( PrefixIScriptExt*  prefixExtension );

  private:
    // hide default and copy constructor
    PrefixError();
    PrefixError( const PrefixError& other );
    const PrefixError& operator=( const PrefixError& other );

    // instance members
    PrefixIScriptExt* prefixExtensionM;
};

} // namespace PrefixDesc
} // namespace DAT

#endif // DAT_PREFIXERROR_HPP
