//==============================================================================
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
//  DAT::SamplePlugIn class implementation.
//
//  This class is the DAT::SamplePlugIn Implementations.
//  DAT::SamplePlugIn is inherited from the PLG::DataPlugIn class.
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
// $RCSfile: DAT::SamplePlugIn.cpp,v $
// $Revision: 1.7 $
// $Author: mliebmann $
// $Date: 2001/09/17 09:25:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DAT::SamplePlugIn.cpp,v $
// Revision 1.7  2001/09/17 09:25:21  mliebmann
// listener events updated
//
// Revision 1.6  2001/09/17 07:56:18  mliebmann
// documentation updated
//
// Revision 1.5  2001/09/17 07:23:32  mliebmann
// Listener concept updated
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
#include "BAS/String.hpp"
#include "BAS/Trace.hpp"
#include "EDR/Container.hpp"
#include "STR/FileIoTurbo.hpp"
#include "DBC/DatabasePlugIn.hpp"
#include "BAS/Decimal.hpp"
#include "BAS/ProtectedBool.hpp"
#include "SamplePlugIn.hpp"

static const char* rcsid()
{
  return "$Id: SamplePlugIn.cpp,v 1.7 2001/09/17 09:25:21 mliebmann Exp $";
};

const BAS::String DAT::SamplePlugIn::registryReuseOnFailureCM ("ReuseOnFailure");
const BAS::String DAT::SamplePlugIn::registryDataPoolCM       ("DataPool");
const BAS::String DAT::SamplePlugIn::registryDataConnectionCM ("DataConnection");
const BAS::String DAT::SamplePlugIn::registryReloadCM         ("Reload");

/*****************************************************
 * Hardcoded tablename defintion
 *****************************************************/
const BAS::String DAT::SamplePlugIn::dbTableNameCM            ("ifw_exchange_rate");

// Listener configuration
const BAS::String DAT::SamplePlugIn::registryListenerCM       ("Listener");
//Update event types.
const BAS::String DAT::SamplePlugIn::ADD_CM                   ("ADD");
const BAS::String DAT::SamplePlugIn::CHANGE_CM                ("CHANGE");
const BAS::String DAT::SamplePlugIn::REMOVE_CM                ("REMOVE");
//Naming contants.
const BAS::String DAT::SamplePlugIn::LST_ACCOUNT_UPDATE_CM    ("LST_ACCOUNT_UPDATE");

//==============================================================================
//==============================================================================
DAT::SamplePlugIn::SamplePlugIn()
  : SampleListM( 0 )
  , dataPlugInM(0)
  , reuseOnFailureM(false)
{
  D_ENTER("DAT::SamplePlugIn::SamplePlugIn()");
}

//==============================================================================
//==============================================================================
DAT::SamplePlugIn::SamplePlugIn(const BAS::String& name, 
                                               const BAS::String& version) 
  : PLG::DataPlugIn(name, version)
  , SampleListM( 0 )
  , dataPlugInM(0)
  , reuseOnFailureM(false)
{
  D_ENTER("DAT::SamplePlugIn::SamplePlugIn(BAS::String& name)");

  // Look up if this plugin is a registered object and if it is valid
  // after the base-class initialisation PLG::DataPlugIn.
  if(isRegistered() && isValid()) 
  {
    // Read registry entries from registry-file.
    // isValid is set for showing if the contructor has everything done OK!
    // Because the contructor could not give any return-value!
    isValid(readRegistry());
    
    if (isValid()) 
    {
      // Initialise other enviroment variables for calculating
      // isValid is set for showing if the contructor has everything done OK!
      // Because the contructor could not give any return-value!
      isValid(evalEnvironment());
    }
  }
}

//==============================================================================
//==============================================================================
DAT::SamplePlugIn::~SamplePlugIn()
{
  D_ENTER("DAT::SamplePlugIn::~SamplePlugIn()");
  
  /*****************************************************
   * The dataPlugInM has not to be deleted here, because 
   * it is generated in an other class and only referenced
   * here for use only! So do not delete this plugIn here!
   *****************************************************/

  /*****************************************************
   * If a hashmap is loaded into the memory it has to be 
   * deleted manualy at this destructor. This pointer is 
   * generated in this Sample-class.
   *****************************************************/
  if (SampleListM != 0)
  {
    delete SampleListM;
    // variable set to 0 as safty measure
    SampleListM = 0; 
  }
}

//==============================================================================
//==============================================================================
bool 
DAT::SamplePlugIn::evalEnvironment()
{
  D_ENTER("DAT::SamplePlugIn::evalEnvironment()");

  // Getting some enviroment variables.
  // Here, the eventhandler is looked with a request over the base-class
  // BAS::RegisteredObject with the call of sendRequest(..).
  BAS::Message requestName(name(), rootName(), "REQ_EVENTHANDLER_NAME");
  if(sendRequest(requestName) == true && requestName.arguments().entries() == 1)
  {
    eventHandlerNameM = requestName.arguments()(0);
  }

  return true;
}

//==============================================================================
//==============================================================================
bool 
DAT::SamplePlugIn::init()
{
  D_ENTER("DAT::SamplePlugIn::init()");

  bool retValue = true;

  /*****************************************************
   * New generation of an empty hashmap.
   *****************************************************/
  SampleListM = new SampleList();
  
  /*****************************************************
   * Fill this empty hashmap with value from the database.
   *****************************************************/
  retValue = buildListFromDB();
  if (!retValue)
  {
    D_PRINT("Error loading data from database!");
  }

  /*****************************************************
   * Show listener that everything is finished and it can
   * be started to send messages with the update()-method
   * of these class (update() is inherited from 
   * BAS::RegisteredObject).
   *****************************************************/
  if( listenerM != 0 )
  {
    BAS::Message ready(name(), listenerM->name(), "LST_INIT_FINISHED");
    sendMessage(ready);
  }

  usableM.setFlag("LOAD_DATA", retValue);
  return retValue;
}

//==============================================================================
//==============================================================================
bool 
DAT::SamplePlugIn::readRegistry ()
{
  D_ENTER ("DAT::SamplePlugIn::readRegistry()");
  
  /*****************************************************
   * Get the registry-string for the actual modul/plugin!
   *****************************************************/
  const BAS::RegistryEntry *myEntry = registry();
  const BAS::RegistryEntry *regNode = 0;

  if (!myEntry) 
  {
    D_PRINT("ERROR: registry subtree '" << name() << "' not found");
    setStatus("ERR_REG_SUBTREE_NOT_FOUND", BAS::Status::critical, name());
    return false;
  }

  //----------------------------------------------------------------------------
  // Entry "ReuseOnFailure"
  //----------------------------------------------------------------------------
  // TRUE: Reuse on failure is the meaning to reuse the previous loaded data
  // stored in memory, if the loading from the new data from the database
  // did not work.
  //----------------------------------------------------------------------------
  // FALSE: by this the SampleListM is only set to zero, if the loading
  // of data from the database failed and the plugin is unusable 
  // -> isUsable() returns false!
  //----------------------------------------------------------------------------
  if (!setBoolFlag(myEntry, registryReuseOnFailureCM, reuseOnFailureM)) 
  {
    return false;
  }

  //----------------------------------------------------------------------------
  // Entry "DataConnection"
  //----------------------------------------------------------------------------
  // Databasedefintion from datapool of the registry!
  // Set of the dataPlugInM for use of the databaseconnection.
  //----------------------------------------------------------------------------
  regNode =  (*myEntry)[registryDataConnectionCM];

  if(regNode) 
  {
    BAS::String            plugInName;
    BAS::String            registryName;
    PLI::DataCollection*   dataColl(0);
    PLI::DataInterface *   plugInInt(0);

    plugInName = regNode->value();

    registryName = rootName() + "." + registryDataPoolCM;
    dataColl = (PLI::DataCollection*)find(registryName);
	
    if (!dataColl) 
    {
      D_PRINT("ERROR: object '" << registryName << "' could not be found");
      setStatus("ERR_OBJ_NOT_FOUND", BAS::Status::critical, registryName );
      return false;
    }

    if (dataColl->isRegistered() == false) 
    {
      D_PRINT("ERROR: object '" << registryName << "' is not registered");
      setStatus("ERR_REG_SUBTREE_NOT_FOUND", BAS::Status::critical, registryName );
      return false ;
    }

    plugInInt = (*dataColl)[plugInName];
    if (plugInInt) 
    {
      dataPlugInM = dynamic_cast<DBC::DatabasePlugIn *> (plugInInt->plugIn());

      if (!dataPlugInM) 
      {
        D_PRINT("ERROR: registry name '" << plugInName << "' is no valid PlugIn" << endl);
        setStatus("ERR_PLUGIN_NOT_VALID", BAS::Status::critical, plugInName);
        return false;
      }
    } else 
    {
      D_PRINT("ERROR: registry name '" << plugInName << "' not found" << endl);
      setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::critical, plugInName);
      return false;
    }
  } else 
  {
    BAS::String regName = name() + "." + registryDataConnectionCM;
    D_PRINT("ERROR: registry name '" << regName << "' not found" << endl);
    setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::critical, regName);
    return false;
  }     
    
  // -------------------------------------------------------------------
  // registry item Listener
  // -------------------------------------------------------------------
  const BAS::RegistryEntry* subEntry = (*myEntry)[registryListenerCM];
 
  if(subEntry) 
  {
    listenerM = find( subEntry->value() + ".Module" );
    if (!listenerM) 
    {
      D_PRINT("ERROR: Listener not found " << subEntry->value());
      setStatus("ERR_LISTENER_NOT_FOUND", BAS::Status::major, subEntry->value());
      return false;
    }
    listenerM->attach(this);
  } 
  else 
  {
    D_PRINT("INFO: No listener specified");
    setStatus("MSG_NO_LISTENER", BAS::Status::warning);
  }

  return true;
}

//==============================================================================
//==============================================================================
bool 
DAT::SamplePlugIn::registryUpdate (const BAS::RegistryEntry * update)
{
  D_ENTER ("DAT::SamplePlugIn::registryUpdate (const BAS::RegistryEntry * )");

  RWPRECONDITION(update);
  
  BAS::RegistryEntry         *myEntry = registry();

  //----------------------------------------------------------------------------
  // Entry "ReuseOnFailure"
  //----------------------------------------------------------------------------
  // TRUE: Reuse on failure is the meaning to reuse the previous loaded data
  // stored in memory, if the loading from the new data from the database
  // did not work.
  //----------------------------------------------------------------------------
  // FALSE: by this the SampleListM is only set to zero, if the loading
  // of data from the database failed and the plugin is unusable 
  // -> isUsable() returns false!
  //----------------------------------------------------------------------------
  BAS::ProtectedBool workedOn;
  if (!updateBoolFlag(update, myEntry, registryReuseOnFailureCM, reuseOnFailureM, "DAT SAMPLE", workedOn))
  {
    usableM.setFalseFlag("registryReuseOnFailureCM");
    return false;
  } else 
  {
    usableM.setTrueFlag("registryReuseOnFailureCM");
  }

  const BAS::RegistryEntry  *subEntry = 0;
  
  //----------------------------------------------------------------------------
  // Entry "Reload"
  //----------------------------------------------------------------------------
  // Check if reload of the data is ask by the registry-semaphore.
  // TRUE: Relaod data
  //----------------------------------------------------------------------------
  // FALSE: No data relaoded but return with true - everythings OK!
  //----------------------------------------------------------------------------
  subEntry = (*update)[registryReloadCM];
  if (!subEntry) 
  {
    return true;
  }    
  
  /*****************************************************
   + Update the in-memory storage of the database data.
   *****************************************************/
  if (!updateInfos()) 
  {
    usableM.setFalseFlag("UPDATE_SAMPLE_DB");
  } else 
  {
    usableM.setTrueFlag("UPDATE_SAMPLE_DB");
  }
      
  return true;  
}

//==============================================================================
//==============================================================================
bool 
DAT::SamplePlugIn::updateInfos()
{
  D_ENTER("DAT::SamplePlugIn::updateInfos()");

  bool retValue = true;

  /*****************************************************
   + Empty definition to store the original hashmap.
   *****************************************************/
  SampleList* orgList = 0;

  /*****************************************************
   + If the reuseOnFailure is activated store the old
   * hashmap.
   *****************************************************/
  if ((SampleListM != 0) && (reuseOnFailureM)) 
  {
    orgList = SampleListM;
  } 

  /*****************************************************
   + Generate a new hashmap to load the new data from the
   * database.
   *****************************************************/
  SampleListM = new SampleList();
  
  /*****************************************************
   * Fill the empty hashmap with value from the database.
   *****************************************************/
  retValue = buildListFromDB();

  /*****************************************************
   * On failure of the database-access the event 
   + EVT_RELOAD_FAILED is send to the eventhandler and 
   * on reuseOnFailure the origList is restored to
   * the SampleListM.
   *****************************************************
   * On success of the database-access the event
   * EVT_RELOAD_SUCCESSFUL is send to the eventhandler and
   * on reuseOnFailure the old hashmap is deleted.
   *****************************************************/
  if(!retValue) 
  {
    BAS::Message evt(name(), eventHandlerNameM, "EVT::RELOAD_FAILED");
    sendMessage(evt);
    
    if (reuseOnFailureM) 
    {
      delete SampleListM;
      SampleListM = orgList;
    } else 
    {
      // remove all nodes
      delete SampleListM;
      SampleListM = 0;
    }
  } else 
  {
    BAS::Message evt(name(), eventHandlerNameM, "EVT_RELOAD_SUCCESSFUL");
    sendMessage(evt);
  }

  /*****************************************************
   * Show the PBC-class that the update of data was successfull
   * or not.
   *****************************************************/
  usableM.setFlag("UPDATE_DATA", retValue);
  return retValue;
}

//==============================================================================
//==============================================================================
bool 
DAT::SamplePlugIn::buildListFromDB()
{
  D_ENTER("DAT::SamplePlugIn::buildlistFromDB()");
  
  setStatus("INF_START_LOADING_DBDATA", BAS::Status::normal, dbTableNameCM);

  RWDBDatabase dbase = dataPlugInM->defaultConnection("LIBNAME").database();
  RWDBTable table_sample  = dbase.table(dbTableNameCM);
  
  /*****************************************************
   * Check, if the tablenames exist in the specified
   * database.
   *****************************************************/
  if (!table_sample.isValid()) 
  {
    setStatus("ERR_DB_CONNECTION_NOT_VALID", BAS::Status::critical);
    return false;
  }
  
  RWDBSelector select = dbase.selector();
  /*****************************************************
   * Select statement for database access
   * Example:
   *****************************************************/
  select << table_sample ["from_currency"]
         << table_sample ["to_currency"]
         << rwdbCast(table_sample["valid_from"], "CHAR", "YYYYMMDD");

  /*****************************************************
   * Where statement.
   * RogueWave documentation part:

      RWDBSelector&
      where(const RWDBCriterion& criterion);

      Specifies criterion as self's SQL WHERE clause. If self already has a WHERE clause, this method replaces it. Returns a reference to self.

   * Example:       
   *                "DD-MMM-YYYY"
   *****************************************************/
  BAS::String date = "15-MAY-2006";
  select.where(table_sample["valid_from"] == date);
  /*****************************************************
   * OrderedBy statement.
   * RogueWave documentation part:
   
      RWDBSelector&
      orderBy(const RWDBColumn& column);

          Specifies column as an ORDER BY column for self. A select statement may have multiple ORDER BY columns; successive calls to
          orderBy() add ORDER BY columns to self. The order of orderBy() calls is retained. Returns a reference to self.

      RWDBSelector&
      orderBy(int columnNumber);

          Specifies columnNumber as an ORDER BY column for self. A select statement may have multiple ORDER BY columns; successive calls to
          orderBy() add ORDER BY columns to self. The order of orderBy() calls is retained. Returns a reference to self.

      RWDBSelector&
      orderByClear();

          Clears self's ORDER BY clause. Returns a reference to self.

      RWDBSelector&
      orderByDescending(const RWDBColumn& column);
      
          Specifies column as an ORDER BY DESCENDING column for self. A select statement may have multiple ORDER BY columns; successive
          calls to orderBy() add ORDER BY columns to self. The order of orderBy() calls is retained. Returns a reference to self.

      RWDBSelector&
      orderByDescending(int columnNumber);

          Specifies columnNumber as an ORDER BY DESCENDING column for self. A select statement may have multiple ORDER BY columns;
          successive calls to orderBy() add ORDER BY columns to self. The order of orderBy() calls is retained. Returns a reference to self.

   * Example:       
   *****************************************************/
  RWDBColumn column = table_sample.column("valid_from");
  select.orderBy(column);

    
  BAS::String            lineCountDummy;// used for tempcalculation
  int64                  lineCount = 0; // counted line recieved from the database
  SampleItemT           newSampleItem; // item which is inserted into the hashlist
  RWDBReader            rdr = select.reader(dataPlugInM->defaultConnection("LIBNAME"));

  if(!rdr.status().isValid()) 
  {
    // generate error status.
    setStatus("ERR_DATABASE",
               BAS::Status::critical,
               dataPlugInM->errorMessage(rdr.status()) );
    return false;
  }

  /*****************************************************
   * Definition of local variables for the database data
   * Example:  

  BAS::String value1;
  BAS::String value2;
  BAS::String name1;
  BAS::String name2;
   *****************************************************/
  /*****************************************************
   * And key-value for the hashmap
   *****************************************************/
  BAS::String validfrom;
  /*****************************************************/

  while(rdr()) 
  {
    /*****************************************************
     * Mapping of the database reader into the local variables
     * Example:
    rdr >> value1
  //      >> value2
  //      >> name1
        >> name2
        >> validfrom;
     *****************************************************/

    /*****************************************************
     * Mapping of the local variables into the datastructur
     * Example:

     ***************
     * decimal-value:
    newSampleItem.value1.fromString(value);
    newSampleItem.value2.fromString(value2);

     ***************
     * string-value
    newSampleItem.name1 = name1;
    newSampleItem.name2 = name2;
     *****************************************************/

    if(!rdr.status().isValid()) 
    {
      D_PRINT("ERROR: Database");
      // generate error status.
      setStatus("ERR_DATABASE",
               BAS::Status::critical,
               dataPlugInM->errorMessage(rdr.status()));
      // delete all data
      return false;
    } else 
    {
      /*****************************************************
       * Insert SampleItem in the hashmap
       *****************************************************/
      if (!SampleListM->insert(validfrom, newSampleItem))
      {
        D_PRINT("Error while inserting SampleItemField from line " << lineCount);
        BAS::StringList argList;
        lineCountDummy.convert(lineCount);
        argList.append(lineCountDummy);
        argList.append(dbTableNameCM);
        setStatus("ERR_DAT_SAMPLE_INS_LIST_DB", BAS::Status::major, argList);
        return false;
      }

      D_PRINT("Insert the new CurrencyField!");

    }
    lineCount++;
  }

  lineCountDummy.convert(lineCount);
  setStatus("INF_NUM_LINES_READ", BAS::Status::normal, lineCountDummy);

  BAS::StringList argList;
  argList.append(dbTableNameCM);
  setStatus("INF_FINISHED_LOADING_DBDATA", BAS::Status::normal, argList);
  return true;
}

//==============================================================================
//==============================================================================
/*****************************************************
 * This function-call has to be modified with special 
 * search-string and return parameters.
 *****************************************************/
bool 
DAT::SamplePlugIn::search( const BAS::String  & searchDate, 
                                BAS::Decimal & sampleValue1, 
                                BAS::Decimal & sampleValue2, 
                                BAS::String  & sampleName1, 
                                BAS::String  & sampleName2 )
{
  D_ENTER("DAT::SamplePlugIn::search( const BAS::Date & searchdate, BAS::Decimal & sampleValue)");
  D_ARG(searchDate);

  if (isValid()) 
  {
    /*****************************************************
     * Find-value of the specific string
     * Example:
     
    SampleItemT tempSample;
    if (SampleListM->findValue(searchDate.asString(),tempSample))
    {
     ***************
     * Mapping of the found value into the return parameter
     
      sampleValue1 = tempSample.value1;
      sampleValue2 = tempSample.value2;

      sampleName1 = tempSample.name1;
      sampleName2 = tempSample.name2;

      return true;
    }
     *****************************************************/
    
  }
  
  return false;
}

//==============================================================================
//==============================================================================
bool 
DAT::SamplePlugIn::isUsable()
{
  D_ENTER("DAT::SamplePlugIn::isUsable()");
  bool retVal = true;
  
  /*****************************************************
   * Call to the base-class for it's usability!
   *****************************************************/
  if (!PLG::DataPlugIn::isUsable()) 
  {
    setStatus("ERR_NOT_USABLE", BAS::Status::major, "DAT::SamplePlugIn::PLG::DataPlugIn");
    retVal = false;
  }

  /*****************************************************
   * Check the database modul pointer of usability.
   *****************************************************/
  if (dataPlugInM != 0) 
  {
    if (!dataPlugInM->isUsable()) 
    {
      setStatus("ERR_NOT_USABLE", BAS::Status::major, "DAT::SamplePlugIn::dataPlugInM");
      retVal = false;
    }
  }
  
  /*****************************************************
   * Check the modul hashmap pointer of usability.
   *****************************************************/
  if(SampleListM == 0) 
  {
    setStatus("ERR_NOT_USABLE", BAS::Status::major, "DAT::SamplePlugIn::SampleList");
    retVal = false;
  }

  /*****************************************************
   * Check the usable flags.
   *****************************************************/
  if (!usableM.summary()) 
  {
    retVal = false;
    BAS::Status msg(name(), "ERR_IN_SECTION", BAS::Status::major);
  
    PBC::Usable::UsableHashType::const_iterator itr;
    
    itr = usableM.usableHash().begin();
    
    while(itr != usableM.usableHash().end()) 
    {
      if (!(*itr).second) 
      {
        msg.argument((*itr).first);
        setStatus(msg);
      }
      itr++;
    }
  }    
  
  return (retVal);
}

//==============================================================================
//==============================================================================
/*****************************************************
 * Respond to a listener update message.
 *****************************************************/
bool 
DAT::SamplePlugIn::update(const BAS::Status& status)
{
  D_ENTER("DAT::SamplePlugIn::update(const BAS::Status& status)");
  
  if (status.messageName() != LST_ACCOUNT_UPDATE_CM) {
    D_PRINT("ERROR: invalid message name");
    return false;
  }
  
  if (status.arguments().length() < 5) {
    D_PRINT("ERROR: to less arguments");
    return false;
  }

  /*****************************************************
   * Extract the message data from the status.
     Example: 
     
  BAS::String ObjDB   = status.arguments()(0);
  BAS::String ObjID0  = status.arguments()(1);
  BAS::String ObjType = status.arguments()(2);
  BAS::String ObjRev  = status.arguments()(3);
   *****************************************************/

  //The event type. INSERT, UPDATE, REMOVE 
  BAS::String eventType      = status.arguments()(4);

  if( eventType == ADD_CM )
  {
    D_PRINT("INFO : Insert message received.");
    /*****************************************************
     * Here has to be implemented the reaction to the insert.
     *****************************************************/
    return true;
  }
  else if( eventType == CHANGE_CM )
  { 
    D_PRINT("INFO : Update message received.");
    /*****************************************************
     * Here has to be implemented the reaction to the update.
     *****************************************************/
    return true;
  }
  else if( eventType == REMOVE_CM )
  { 
    D_PRINT("INFO : Remove message received.");
    /*****************************************************
     * Here has to be implemented the reaction to the remove.
     *****************************************************/
    return true;
  }

  D_PRINT("ERROR: Invalid event type " << eventType );
  setStatus("ERR_INVALID_EVENT_TYPE"
            ,BAS::Status::critical
            ,eventType );
  return false;
}

//==============================================================================
//==============================================================================
extern "C" DAT::SamplePlugIn* MODULE_START (const BAS::String& name)
{
  D_ENTER("extern C DAT::SamplePlugIn *ModuleStart(BAS::String& name)");

  return (new DAT::SamplePlugIn(name, "$Name:  $"));
}

//==============================================================================
//==============================================================================
extern "C" DAT::SamplePlugIn* ModuleStartNL()
{
  D_ENTER("extern C DAT::SamplePlugIn *ModuleStartNL()");

  return (new DAT::SamplePlugIn());
}
