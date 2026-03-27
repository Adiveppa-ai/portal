#ifndef PBC_MODULEREFERENCE_HPP
#define PBC_MODULEREFERENCE_HPP
//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PBC
//------------------------------------------------------------------------------
// Module Description:
//   Defintion of a macro for extracting the IFW_ALIAS_MAP reference out of
//   module name.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Peter Engelbrecht
//
// $RCSfile: ModuleReference.hpp,v $
// $Revision: 1.1 $
// $Author: pengelbr $
// $Date: 2001/05/16 08:44:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ModuleReference.hpp,v $
// Revision 1.1  2001/05/16 08:44:06  pengelbr
// Added global function ModuleReference().
//
//==============================================================================

// Framework includes
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
namespace PBC
{
/** <tt><b>ModuleReference</b></tt> extracts the registry name of a module
    out of BAS::RegisteredObject::dirName().

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: ModuleReference.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.1 $</font></td>
    <td><font size=-1>$Date: 2001/05/16 08:44:06 $</font></td>
    <td><font size=-1>$Author: pengelbr $</font></td>
    </tr>
    </table>

    <p>This global function can be used to obtain the registry name of a module.
    EDR::Factory::getIndex() or EDR::Factory::getBlockIndex() may need this as
    value for the reference parameter.
*/
extern const BAS::String ModuleReference( const BAS::String& name );
}
#endif // MODULEREFERENCE_HPP
