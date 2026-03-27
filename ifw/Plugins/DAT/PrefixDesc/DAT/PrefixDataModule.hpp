#ifndef DAT_PREFIXDATAMODULE_HPP
#define DAT_PREFIXDATAMODULE_HPP

//==============================================================================
//
//	@(#)%Portal Version: PrefixDataModule.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:39:51 %
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
//   Definition of the function node for the function prefixDataModule().
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
// $RCSfile: PrefixDataModule.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/09/19 10:50:32 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PrefixDataModule.hpp,v $
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

// Forward declaration
class PrefixIScriptExt;

/** <b><tt>PrefixDataModule</tt></b> is the iScript function node for 
 *  connecting the iScript extension to a Prefix data plugin.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: PrefixDataModule.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2000/09/19 10:50:32 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class PrefixDataModule : public SCR::BoolNode
{
  public:
    /**@name PrefixDataModule constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~PrefixDataModule();

    //@}

    /**@name PrefixDataModule public methods */
    //@{

    /** Execute the prefixDataModule(String) function
     */
    virtual bool result();
    
    /** Create a prefixDataModule(String) function 
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
    PrefixDataModule( PrefixIScriptExt* prefixExtension,
                          SCR::StringNode*       prefixModuleNode );

  private:
    // hide default and copy constructor
    PrefixDataModule();
    PrefixDataModule( const PrefixDataModule& other );
    const PrefixDataModule& operator=( const PrefixDataModule& other );

    // instance members
    PrefixIScriptExt* prefixExtensionM;
    SCR::StringNode*  prefixModuleNodeM;
};

} // namespace PrefixDesc
} // namespace DAT

#endif // DAT_PREFIXDATAMODULE_HPP
