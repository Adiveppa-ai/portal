#ifndef DAT_SAMPLE_HPP
#define DAT_SAMPLE_HPP
//==============================================================================
//
//      @(#)%Portal Version: SamplePlugIn.hpp:Pipeline7.3.1Int:1:2007-Oct-08 01:38:20 %
//      
//      Copyright (c) 1996 - 2007 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: DAT::Sample
//------------------------------------------------------------------------------
// Module Description:
//  SamplePlugIn class implementation.
//
//  This class is the SamplePlugIn Implementation.
//  This PlugIn is inherited from PLG::DataPlugIn class.
//
//  This class should show how a plugIn should be developed. For this some
//  method have to be implemented in the right way to work with the framework.
//
//  Basic methods are:
//    - readRegistry() - read registry values from the registry-file
//    - registryUpdate() - is called if a semaphore is set for the framework
//                         to update database data or other setting of the
//                         registry-file.
//    - isUsable() - show the controller is this plugIn is usable.
//                   Test of internal variables or database-connections.
//    - init() - is called after all DAT-plugIns are loaded to set specific
//               variables or loading data from database.
//    - search() - is called by any other plugIn or IScript-extension to get
//                 access to the stored data. (Parameter list is specific to 
//                 the stored in-memory data!)
//    - update() - is called by the base-class BAS::RegistrereObject, if the
//                 class itself is attach to the obeserver from the base-class.
//    - MODULE_START() - is called to create an object of this class by the
//                       dlopen-method of the system!
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: marco liebmann
//
// $RCSfile: SamplePlugIn.hpp,v $
// $Revision: 1.7 $
// $Author: mliebmann $
// $Date: 2001/09/17 09:25:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: SamplePlugIn.hpp,v $
// Revision 1.7  2001/09/17 09:25:21  mliebmann
// listener events updated
//
// Revision 1.6  2001/09/17 08:21:37  mliebmann
// documentation updated
//
// Revision 1.5  2001/09/17 07:56:18  mliebmann
// documentation updated
//
// Revision 1.4  2001/09/17 06:38:11  mliebmann
// Listener concept updated
//
// Revision 1.3  2001/09/17 06:24:25  mliebmann
// Listener concept added
//
// Revision 1.2  2001/09/11 12:27:32  mliebmann
// Documentation updated
//
// Revision 1.1  2001/09/05 12:39:54  mliebmann
// initial version of a simple sample
//
//
//==============================================================================

// roguewave includes
#include <rw/tvsrtvec.h>
#include <rw/tvdlist.h> 
#include <rw/tvhdict.h> 

// portal includes
#include "BAS/OnlyPointer.hpp"
#include "BAS/Date.hpp"
#include "PLG/DataPlugIn.hpp"
#include "PBC/Usable.hpp"
#include "PLI/DataCollection.hpp"

class DatabasePlugIn;
//------------------------------------------------------------------------------

/** <tt><b>SamplePlugIn</b></tt> implements the integRate 
    sample template.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: SamplePlugIn.hpp,v $</font></td>
    <td><font size=-1>$Revision: 1.7 $</font></td>
    <td><font size=-1>$Date: 2001/09/17 09:25:21 $</font></td>
    <td><font size=-1>$Author: mliebmann $</font></td>
    </tr>
    </table>

    <b>Registry entries</b>
         <dd>ReuseOnFailure</dd>
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

    struct SampleItemT
    {
      /*****************************************************
       * Definition of the table coloums for in-memory storage
       * Example:

      BAS::String value1;
      BAS::String value2;
      BAS::String name1;
      BAS::String name2;
       *****************************************************/

#ifdef AIX
      inline int operator==(const SampleItemT& rVal) const
      {
        return true;
      }

      inline int operator<(const SampleItemT& rVal) const
      {
        return true;
      }
#endif
    };

    /*****************************************************
     * Typedefinition of the list, where the data is stored
     * Example with simple hash-functionality:
     * Here is a RogueWave SourcePro template-definition
     * used to define a hashmap with key-value BAS::String,
     * a return-value SampleItemT and with it's basic BAS::StringHash-
     * method and less-operator.
     *****************************************************/
    typedef RWTValHashMap < BAS::String, SampleItemT, BAS::StringHash, less<BAS::String> > SampleList;
    /*****************************************************
     * This typedef is later used for variable-definition
     *****************************************************/
namespace DAT
{
class SamplePlugIn : public PLG::DataPlugIn
{
  public :
    /**@name Constructors and destructors. */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    SamplePlugIn();

    /** Standard constructor.<br>
        Creates an registered object.
        @param name    Name of the object.
        @param version Version of the object.
    */
    SamplePlugIn(const BAS::String& name, const BAS::String& version);

    /** Destructor */
    virtual ~SamplePlugIn();
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
    bool search( const BAS::String  & searchDate, 
                       BAS::Decimal & sampleValue1, 
                       BAS::Decimal & sampleValue2, 
                       BAS::String  & sampleName1, 
                       BAS::String  & sampleName2 );
    
    /** Called from the observer (in this module the AccountListener-PlugIn)
        @param status Message from observer
	@return true - on success
	        false - on failure
    */
    bool update(const BAS::Status& status);

    ///
    bool registryUpdate (const BAS::RegistryEntry * update);
    ///
    virtual bool isUsable();
    //@}

  private:
    // Default, copy constructor and assign operator are not implemented. 
    // They are private to prevent unintentionally use.
    SamplePlugIn(SamplePlugIn& right);
    const SamplePlugIn& operator=(SamplePlugIn& right);

    bool readRegistry ();

    bool evalEnvironment();
    
    bool buildListFromDB();
    
    bool updateInfos();
    
    SampleList            *SampleListM;

    static const BAS::String   registryReuseOnFailureCM;
    static const BAS::String   registryDataPoolCM;
    static const BAS::String   registryDataConnectionCM;
    static const BAS::String   dbTableNameCM;
    static const BAS::String   dbTableName2CM;
    static const BAS::String   registryReloadCM;
    
    DBC::DatabasePlugIn        *dataPlugInM;
    bool                      reuseOnFailureM;
    PBC::Usable                usableM;
    
    BAS::String                eventHandlerNameM;

    /*****************************************************
     * Listener definition (Corba-connection to infranet!)
     * For the use of this listener in the registry has to
     * defined a AccountListener-plugin with the real
     * corba connection.
     *****************************************************/
    //Pointer to the listener base class.
    BAS::RegisteredObject* listenerM;
    static const BAS::String   registryListenerCM;

    //Update event types.
    static const BAS::String ADD_CM;
    static const BAS::String CHANGE_CM;
    static const BAS::String REMOVE_CM;
    
    //Naming contants.
    static const BAS::String LST_ACCOUNT_UPDATE_CM;
};
} //namespace DAT

#endif // DAT_SAMPLE_HPP
