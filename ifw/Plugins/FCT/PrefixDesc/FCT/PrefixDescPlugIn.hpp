#ifndef FCT_PREFIXDESC_HPP
#define FCT_PREFIXDESC_HPP 1
//==============================================================================
//
//      @(#)%Portal Version: PrefixDescPlugIn.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:39:24 %
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FCT::PrefixDesc
//------------------------------------------------------------------------------
// Module Description:
//   This class is the PlugIn implementation.
//   This PlugIn is inherited from FuncPlugIn class.
//
//------------------------------------------------------------------------------
//
// Revision: 10003  6.5_SP2  01-May-2003  keshav
// PRSF00039598: Changes due to registryUpdate interface change
//
// Revision 1.18  2001/08/29 12:07:03  dhatton
// Checked code review remarks.
//
// Revision 1.17  2001/08/15 09:20:55  jkeckst
// PETS 37618 Code Review
//
// Revision 1.16  2001/06/21 09:34:25  dhatton
// Updated for v4-30-00
//
// Revision 1.15  2001/01/17 12:15:42  jkeckst
// API version
//
// Revision 1.14  2000/02/29 13:23:34  jkeckst
//
//==============================================================================
#include <unistd.h>
#include <rw/locale.h>
#include "PLG/FunctionPlugIn.hpp"
#include "EDR/Index.hpp"      

// Forward declaration
namespace DAT {
  namespace PrefixDesc{
    class PlugIn;
  }
}

// Forward declaration
namespace EDR {
  class Container;
  class Factory;
}

namespace FCT
{
namespace PrefixDesc
{

/** <tt><b>PlugIn</b></tt> Implements the integRate prefix
description search.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: PrefixDescPlugIn.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.18 $</font></td>
    <td><font size=-1>$Date: 2001/08/29 12:07:03 $</font></td>
    <td><font size=-1>$Author: dhatton $</font></td>
    </tr>
    </table>

    <p>This class try to search in his data tree the B-Number and
    set the description for this number.
    
    <dl>
    <dt><b>Registry entries</b></dt>
        <dd>PrefixDataModule</dd>
        <dd>Active</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Requests send</b></dt>
         <dd>none</dd>
    <dt><b>Messages received</b></dt>
         <dd>none</dd>
    <dt><b>Errors</b></dt>
        <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
        <dd>ERR_PLUGIN_NOT_VALID</dd>
        <dd>ERR_REG_NAME_NOT_FOUND</dd>
        <dd>ERR_OBJ_NOT_FOUND</dd>
        <dd>ERR_INDEX_NOT_CREATED</dd>
    <dt><b>Aliases</b></dt>
      <dd>DETAIL_B_NUMBER</dd>
      <dd>DETAIL_B_NUMBER_DESTINATION_DECRIPTION</dd>
    </dl>
*/
class PlugIn : public PLG::FunctionPlugIn
{
  public:

    /**@name Constructors and destructor. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    PlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the registered object.
        @param version Version of the registered object.
    */
    PlugIn(const BAS::String& name, const BAS::String& version);

    /** Destructor. */
    virtual ~PlugIn();

    //@}

    /**@name special Functions. */
    //@{
    /** Set the description for the B-Number.
    */
    bool processEdrContainer(PLG::EdrContainerList& edrList);

    /** Read all useful registry entries.
    */
    bool readRegistry();

    /** Get all environment nesseccary variables.
    */
    bool evalEnvironment();

    /** Update all useful registry entries.
        @param updateRegistry The new registry with all update infos.
        @param workedOn  reference to set to true if anything was changed.
    */
    bool registryUpdate(const BAS::RegistryEntry* updateRegistry,
			BAS::ProtectedBool&       workedOn);

    /** Check if the module is usable.
    */
    bool isUsable();
    //@}

  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    PlugIn(PlugIn& right);
    const PlugIn& operator=(PlugIn& right);

    // Get all container indices.
    bool setEDRContainerIndices();

    // Registry values.

    // Registry strings.
    static const BAS::String   registryDataPoolCM;
    static const BAS::String   registryDataPlugInCM;
    static const BAS::String   registryFormatCM;

    // Pointer to the data module.
    DAT::PrefixDesc::PlugIn* dataPlugInM;
    
    // For better performance use this not as smallest scope.
    BAS::String descriptionM;

    //The edr factory.
    EDR::Factory* edrFactoryM;

    //Edr field logical names.
    static const BAS::String bNumberCM;
    static const BAS::String descriptionCM;

    //Edr field default names.
    static const BAS::String bNumberDefaultCM;
    static const BAS::String descriptionDefaultCM;
    
    // The indices for accessing the EDR container. 
    EDR::Index  bNumberIdxM;
    EDR::Index  destDescrIdxM;
};

} // namespace PrefixDesc
} // namespace FCT

#endif // FCT_PREFIXDESC_HPP          
