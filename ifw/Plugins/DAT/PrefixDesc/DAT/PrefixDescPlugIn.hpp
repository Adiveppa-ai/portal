#ifndef DAT_PREFIXDESC_HPP
#define DAT_PREFIXDESC_HPP
//==============================================================================
//
//      @(#)%Portal Version: PrefixDescPlugIn.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:39:46 %
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Module Description:
//  PlugIn class implementation.
//
//  This class is the PrefixDescPlugIn Implementation.
//  This PlugIn is inherited from PLG::DataPlugIn class.
//
//------------------------------------------------------------------------------
//
// Revision: 10003  6.5_SP2  01-May-2003  keshav
// PRSF00039598: Changes due to registryUpdate interface change
//
// Revision 1.19  2001/01/17 12:13:50  jkeckst
// API version with comments
//
//==============================================================================

#include "BAS/OnlyPointer.hpp"
#include "PLG/DataPlugIn.hpp"
#include "PBC/Usable.hpp"
#include "PBC/ValTree.hpp"
#include "PLI/DataCollection.hpp"

// Forward declaration
namespace DBC {
  class DatabasePlugIn;
}

namespace DAT
{
namespace PrefixDesc
{

//------------------------------------------------------------------------------

/** <tt><b>PlugIn</b></tt> implements the integRate 
    prefix description tree.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: PrefixDescPlugIn.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.19 $</font></td>
    <td><font size=-1>$Date: 2001/01/17 12:13:50 $</font></td>
    <td><font size=-1>$Author: jkeckst $</font></td>
    </tr>
    </table>

    <b>Registry entries</b>
         <dd>PrefixDescFile</dd>
         <dd>ReuseOnFailure</dd>
         <dd>Source</dd>
         <dd>DataConnection</dd>
    <b>Messages send</b>
         none
    <b>Messages receive</b>
         none
    <b>Errors</b>
         <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
         <dd>ERR_BUILD_DESC_TREE</dd>
         <dd>ERR_REG_NAME_NOT_FOUND</dd>
*/


class PlugIn : public PLG::DataPlugIn
{
  public :
    /** Source type enumeration.
        Values:
        <ul>
        <li>DATABASE
        <li>FILE
        </ul>
    */
    enum sourceTypeT
    {
      DATABASE = 1,
      FILE
    };

    /**@name Constructors and destructors. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    PlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the object.
        @param version Version of the object.
    */
    PlugIn(const BAS::String& name, const BAS::String& version);

    /** Destructor */
    virtual ~PlugIn();
    //@}

    /**@name Additional Methods. */
    //@{

    /** Initializer.<br>
        Must be used for loading the PlugIn Data.
    */
    bool init();
    /** Find a description for the number.
        @param number - the number to search for a description.
        @param description - the founded description. It were only set
        when something founded.
        @return true - found a description.
                false - found no description.
    */
    bool search(const BAS::String & number, BAS::String & description)const;
    
    /** Find a description for the number.
        @param number - the number to search for a description.
        @param description - the founded description. It were only set
        when something founded.
        @param prefix - the founded prefix that matched. It were only set
        when something founded.
        @return true - found a description.
                false - found no description.
    */
    bool search(const BAS::String & number, 
                BAS::String & description,
                BAS::String & prefix)const;
    
    /// Update all registry items.
    bool registryUpdate(const BAS::RegistryEntry* update,
			BAS::ProtectedBool&       workedOn);

    /// Check if the object is usable.
    virtual bool isUsable();
    //@}

  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    PlugIn(PlugIn& right);
    const PlugIn& operator=(PlugIn& right);

    ///
    bool readRegistry ();
    ///
    bool evalEnvironment();
    
    // A data pair. Every prefix has one description.
    struct PrefixItemT
    {
      BAS::String  prefix;
      BAS::String  description;
    };

    // The data tree of all pairs.
    typedef PBC::ValTree<PrefixItemT> PrefixDescTree;
  
    bool buildTreeFromFile(const BAS::String & prefixFile, 
                   PrefixDescTree * tree);
    bool buildTreeFromDB(const BAS::String & tableName, 
                   PrefixDescTree * tree);
    bool updateInfos();
    
    bool loadDataFromFile();
    bool loadDataFromDB();
    
    void setInputList(const BAS::RegistryEntry * subEntry);

    // all constants for the registry items    
    static const BAS::String   registryCLIBaseCM;
    static const BAS::String   registryPrefixDescCM;
    static const BAS::String   registryReuseOnFailureCM;
    static const BAS::String   registrySourceCM;
    static const BAS::String   registryDataPoolCM;
    static const BAS::String   registryDataConnectionCM;
    static const BAS::String   dbTableNameCM;
    static const BAS::String   registryReloadCM;
    
    // pointer to the data module
    DBC::DatabasePlugIn  *dataPlugInM;
    // store the registry value for CLI Base
    int                 valueCLIBaseM;
    // store the registry value for Source
    sourceTypeT         valueSourceM;
    // store the registry value for reuseOnFailure
    bool                reuseOnFailureM;
    // Collect all stati for correct running
    PBC::Usable          usableM;
    // The data tree
    BAS::OnlyPointer<PrefixDescTree> prefixDescTreeM;
    // store all file names from the registry
    BAS::StringList  inputFileListM;
    // store the name of the event handler
    BAS::String      eventHandlerNameM;
};

} // namespace PrefixDesc
} // namespace DAT

#endif
