#ifndef DAT_PREFIXISCRIPTEXT_HPP
#define DAT_PREFIXISCRIPTEXT_HPP

//==============================================================================
//
//      @(#)%Portal Version: PrefixIScriptExt.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:39:35 %
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
//   The PrefixDescr iScript extension.
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
// $RCSfile: PrefixIScriptExt.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2000/09/27 08:30:50 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PrefixIScriptExt.hpp,v $
// Revision 1.2  2000/09/27 08:30:50  sd
// - Changes in iScript extension due to modifications in SCR.
//
// Revision 1.1  2000/09/19 10:50:32  sd
// - Initial revision of the iScript extension.
//
//==============================================================================

#include "SCR/Variable.hpp"
#include "SCR/Extension.hpp"

namespace DAT
{
namespace PrefixDesc
{

class PlugIn;

/** <b><tt>PrefixIScriptExt</tt></b> is the iScript extension class for
 *  the PrefixDescr data plugin.
 *
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: PrefixIScriptExt.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2000/09/27 08:30:50 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class PrefixIScriptExt : public SCR::Extension
{
  public:
    /**@name PrefixIScriptExt constructors and destructor */
    //@{

    /** Constructor
     */
    PrefixIScriptExt();

    /** Destructor
     */
    virtual ~PrefixIScriptExt();

    //@}


    /**@name PrefixIScriptExt public methods */
    //@{

    /** Get the name of the extension
     *  @return reference to the extension name
     */
    virtual const BAS::String& extensionName() const;

    /** Get a variable from the extension
     *  @param name The name of the variable
     *  @return Pointer to the variable on success, 0 otherwise
     */
    virtual SCR::Variable* variable( const BAS::String& name );

    //@}

    /**@name PrefixIScriptExt special methods */
    //@{

    /** Connect the extension to a PrefixDescPlugIn 
     *  @param name The registry name of the plugin
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool prefixDataModule( const BAS::String& name );

    /** Search for the prefix description
     *  @param number Number for which to search the prefix
     *  @param description Return buffer for the description
     *  @param prefix Return buffer for the searched prefix
     *  @return <b>true</b> if prefix was found, <b>false</b> otherwise
     */
    bool prefixSearch( const BAS::String& number,
                       BAS::String&       description,
                       BAS::String&       prefix );

    /** Get the failure string, describing the last error
     *  @return Reference to failure string
     */
    const BAS::String& failure() const;

    //@}

  private:

    // instance members
    PlugIn*       prefixDescrPlugInM;
    BAS::String   failureM;

    // class members
    static SCR::VariableMap  constantsCM;
};

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
PrefixIScriptExt::failure() const
{
  return failureM;
}

} // namespace PrefixDesc
} // namespace DAT

#endif // DAT_PREFIXISCRIPTEXT_HPP
