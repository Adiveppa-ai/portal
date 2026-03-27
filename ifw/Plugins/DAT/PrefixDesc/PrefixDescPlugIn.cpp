//==============================================================================
//
// Copyright (c) 1996, 2023, Oracle and/or its affiliates. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Module Description:
//  PlugIn class implementation.
//
//  This class is the DAT::PlugIn Implementations.
//  DAT::PlugIn is inherited from the PLG::DataPlugIn class.
//
//------------------------------------------------------------------------------
// Revision: 10011  7.4_PS8  15-Nov-2010  Nishant Kumar
// BUG10243069: Unnecessary destroy method call is removed during reload operation.
//
// Revision: 10010  7.4      25-Oct-2010 Nishant Kumar
// Bug 10220978: Module changed to conform to the parallel loading architecture in pipeline.
// Changed defaultConnection to openConnection.
//
// Revision: 10007  6.7_FP2  04-Oct-2004  Meera Sundaram
// PRSF00132353: Make DAT_PrefixDesc const correct (part of quality fest)
//
// Revision: 10006  6.7_FP2  14-May-2004  pramodk
// PRSF00107376: NT Build Problem: Modify build spec and LIBNAME to MAKE_STR2(LIBNAME)
//
// Revision: 10005  6.7_FP2  19-Mar-2004  brajan
// PRSF00086920: [Pipeline] Code Cleanup: Remove Remains from DB Version Check
//
// Revision: 10003  6.5_SP2  01-May-2003  keshav
// PRSF00039598: Changes due to registryUpdate interface change
//
// Revision 1.31  2001/06/21 13:54:47  dhatton
// Minor correction.
//
// Revision 1.30  2001/01/17 12:13:50  jkeckst
// API version with comments
//
//==============================================================================

#include "BAS/Trace.hpp"
#include "DAT/PrefixDescPlugIn.hpp"
#include "EDR/Container.hpp"
#include "STR/FileIoTurbo.hpp"
#include "DBC/DatabasePlugIn.hpp"
#include "BAS/Decimal.hpp"


const BAS::String DAT::PrefixDesc::PlugIn::registryPrefixDescCM     ("PrefixDesc");
const BAS::String DAT::PrefixDesc::PlugIn::registryReuseOnFailureCM ("ReuseOnFailure");
const BAS::String DAT::PrefixDesc::PlugIn::registrySourceCM         ("Source");
const BAS::String DAT::PrefixDesc::PlugIn::registryDataPoolCM       ("DataPool");
const BAS::String DAT::PrefixDesc::PlugIn::registryDataConnectionCM ("DataConnection");
const BAS::String DAT::PrefixDesc::PlugIn::dbTableNameCM            ("ifw_destindesc");
const BAS::String DAT::PrefixDesc::PlugIn::registryReloadCM         ("Reload");
const BAS::String DAT::PrefixDesc::PlugIn::registryCLIBaseCM        ("CLIBase");

//==============================================================================
//==============================================================================
DAT::PrefixDesc::PlugIn::PlugIn()
  : reuseOnFailureM(false)
  , dataPlugInM(0)
{
  D_ENTER("DAT::PrefixDesc::PlugIn::PlugIn()");
}

//==============================================================================
//==============================================================================
DAT::PrefixDesc::PlugIn::PlugIn(const BAS::String& name, 
                                           const BAS::String& version) 
  : PLG::DataPlugIn(name, version)
  , reuseOnFailureM(false)
  , dataPlugInM(0)
{
  D_ENTER("DAT::PrefixDesc::PlugIn::PlugIn(BAS::String& name)");

  if(isRegistered() && isValid()) {
    isValid(readRegistry());
    
    if (isValid()) {
      isValid(evalEnvironment());
    }
  }
}

//==============================================================================
//==============================================================================
DAT::PrefixDesc::PlugIn::~PlugIn()
{
  D_ENTER("DAT::PrefixDesc::PlugIn::~PlugIn()");
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::evalEnvironment()
{
  D_ENTER("DAT::PrefixDesc::PlugIn::evalEnvironment()");

  // get the name of the event handler
  BAS::Message requestName(name(), rootName(), "REQ_EVENTHANDLER_NAME");
  if (sendRequest(requestName)  && requestName.arguments().entries() == 1) {
    eventHandlerNameM = requestName.arguments()(0);
  }

  return true;
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::loadDataFromFile()
{
  D_ENTER("DAT::PrefixDesc::PlugIn::loadDataFromFile()");
  
  // loop over all input file names
  for (size_t i=0; i<inputFileListM.entries(); i++) {
    D_PRINT ("add file " << inputFileListM(i));
    // insert data in the tree
    if (!buildTreeFromFile(inputFileListM(i), prefixDescTreeM.get())) {
      setStatus("ERR_BUILD_DESC_TREE", BAS::Status::critical, inputFileListM(i));
      return false;
    }
  }      

  return true;
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::loadDataFromDB()
{
  D_ENTER("DAT::PrefixDesc::PlugIn::loadDataFromDB()");

  if (!buildTreeFromDB(dbTableNameCM, prefixDescTreeM.get())) {
    return false;
  }
  
  return true;
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::init()
{
  D_ENTER("DAT::PrefixDesc::PlugIn::init()");

  bool retValue = true;

  // the variable can be only set to read from file or read from DB
  switch (valueSourceM) {
    case FILE:
      prefixDescTreeM = new PrefixDescTree( valueCLIBaseM );
      retValue = loadDataFromFile();
      break;
    case DATABASE:
      prefixDescTreeM = new PrefixDescTree( valueCLIBaseM );
      retValue = loadDataFromDB();
      break;
    default:
      retValue = false;
      break;
  }

  // save the state from init function
  usableM.setFlag("LOAD_DATA", retValue);
  return retValue;
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::readRegistry ()
{
  D_ENTER ("DAT::PrefixDesc::PlugIn::readRegistry()");
  
  const BAS::RegistryEntry *myEntry = registry();
  const BAS::RegistryEntry *regNode = 0;

  if (!myEntry) {
    D_PRINT("ERROR: registry subtree '" << name() << "' not found");
    setStatus("ERR_REG_SUBTREE_NOT_FOUND", BAS::Status::critical, name());
    return false;
  }

  //----------------------------------------------------------------------------
  // Entry "CLIBase"
  //----------------------------------------------------------------------------
  regNode = (*myEntry)[registryCLIBaseCM];

    if (regNode != 0) {
      BAS::String valueCLIBase = regNode->value();
      if (valueCLIBase == "10") {
        valueCLIBaseM = 10;
      } else if(valueCLIBase == "16") {
        valueCLIBaseM = 16;
      } else {
       // Invalid CLI Base Value.
       BAS::StringList errList;
       BAS::String regName = name() + "." + registryCLIBaseCM;

       errList.append( valueCLIBase );
       errList.append( regName );

       D_PRINT("ERROR: Invalid registry value '" << valueCLIBase << "' for " << regName << endl);

       setStatus("ERR_INVALID_REG_VALUE", BAS::Status::critical, errList);
       return false;
    }
  } else {
    BAS::String regName = name() + "." + registryCLIBaseCM;

    D_PRINT("ERROR: registry name '" << regName << "' not found" << endl);

    setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::critical, regName);
    return false;
  }
 
  //----------------------------------------------------------------------------
  // Entry "Source"
  //----------------------------------------------------------------------------
  regNode = (*myEntry)[registrySourceCM];

  if (regNode != 0) {
     BAS::String valueSource = regNode->value();
     valueSource.toUpper();

     if (valueSource == "DATABASE") {
       valueSourceM = DATABASE;
     } else if (valueSource == "FILE") {
       valueSourceM = FILE;
     } else {
       // Invalid Source Value.
       BAS::StringList errList;
       BAS::String regName = name() + "." + registrySourceCM;

       errList.append( valueSource );
       errList.append( regName );

       D_PRINT("ERROR: Invalid registry value '" << valueSource << "' for " << regName << endl);

       setStatus("ERR_INVALID_REG_VALUE", BAS::Status::critical, errList);
       return false;
    }
  } else {
    BAS::String regName = name() + "." + registrySourceCM;

    D_PRINT("ERROR: registry name '" << regName << "' not found" << endl);

    setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::critical, regName);
    return false;
  }

  //----------------------------------------------------------------------------
  // Entry "ReuseOnFailure"
  //----------------------------------------------------------------------------
  if (!setBoolFlag(myEntry, registryReuseOnFailureCM, reuseOnFailureM)) {
    return false;
  }

  switch (valueSourceM) {
  //----------------------------------------------------------------------------
  // Get all file names from the registry
  //----------------------------------------------------------------------------
    case FILE:
      regNode = (*myEntry)[registryPrefixDescCM];
      if (!regNode) {
        BAS::String regName = name() + "." + registryPrefixDescCM;
        D_PRINT("ERROR: registry name '" << regName << "' not found");
        setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::major, regName);
        return false;
      } else {
        setInputList(regNode);
      }
      break;
  //----------------------------------------------------------------------------
  // Get the data base entry point
  //----------------------------------------------------------------------------
    case DATABASE:
    
      regNode =  (*myEntry)[registryDataConnectionCM];

      if(regNode) {
        BAS::String            plugInName;
        BAS::String            registryName;
        PLI::DataCollection*   dataColl(0);
        PLI::DataInterface *   plugInInt(0);

        plugInName = regNode->value();

        registryName = rootName() + "." + registryDataPoolCM;
        // find the data collection in the registry
        dataColl = (PLI::DataCollection*)find(registryName);

        if (!dataColl) {
          D_PRINT("ERROR: object '" << registryName << "' could not be found");
          setStatus("ERR_OBJ_NOT_FOUND", BAS::Status::critical, registryName );
          return false;
        }

        // check if the data collection is valid
        if (dataColl->isRegistered() == false) {
          D_PRINT("ERROR: object '" << registryName << "' is not registered");
          setStatus("ERR_REG_SUBTREE_NOT_FOUND", BAS::Status::critical, registryName );
          return false ;
        }

        plugInInt = (*dataColl)[plugInName];        
        if (plugInInt) {
          // set the data pointer to the data collection plug in
          dataPlugInM = dynamic_cast<DBC::DatabasePlugIn *> (plugInInt->plugIn());

          // test if the cast is realy done
          if (!dataPlugInM) {
            D_PRINT("ERROR: registry name '" << plugInName << "' is no valid PlugIn" << endl);
            setStatus("ERR_PLUGIN_NOT_VALID", BAS::Status::critical, plugInName);
            return false;
          }
        } else {
          D_PRINT("ERROR: registry name '" << plugInName << "' not found" << endl);
          setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::critical, plugInName);
          return false;
        }
      } else {
        BAS::String regName = name() + "." + registryDataConnectionCM;
        D_PRINT("ERROR: registry name '" << regName << "' not found" << endl);
        setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::critical, regName);
        return false;
      }     
    
    
      break;
    default:
      return false;
      break;
  }
  
  return true;
}

//==============================================================================
//==============================================================================
bool
DAT::PrefixDesc::PlugIn::registryUpdate(const BAS::RegistryEntry* update,
					BAS::ProtectedBool&       workedOn)
{
  D_ENTER ("DAT::PrefixDesc::PlugIn::registryUpdate (const BAS::RegistryEntry*, BAS::ProtectedBool& workedOn)");

  RWPRECONDITION(update);
  
  BAS::RegistryEntry         *myEntry = registry();
  //----------------------------------------------------------------------------
  // Entry "ReuseOnFailure"
  //----------------------------------------------------------------------------
  if (!updateBoolFlag(update, 
                      myEntry, 
                      registryReuseOnFailureCM, 
                      reuseOnFailureM, 
                      "DAT PREFIX DESCRIPTION",
		      workedOn)) {
    usableM.setFalseFlag("registryReuseOnFailureCM");
    return false;
  } else {
    usableM.setTrueFlag("registryReuseOnFailureCM");
  }

  const BAS::RegistryEntry  *subEntry = 0;
  BAS::RegistryEntry        *sysEntry = 0;
  BAS::String               updateCLIBase;
 
   if ((subEntry = update->find(registryCLIBaseCM)))
   {
     workedOn = true;
 
     updateCLIBase = subEntry->value();
     sysEntry = myEntry->find(registryCLIBaseCM);
    
     if(sysEntry)
     {
       sysEntry->value(updateCLIBase);
     }
   }
  
  // reload all data
  switch (valueSourceM) {
    case FILE:
      sysEntry = (*myEntry) [registryPrefixDescCM];
      subEntry = (*update)[registryPrefixDescCM];

      if (!subEntry) {
        return true;
      }
      workedOn = true;

      setInputList(subEntry);

      if (!updateInfos()) {
        usableM.setFalseFlag("UPDATE_PREFIX_FILE");
      } else {
        usableM.setTrueFlag("UPDATE_PREFIX_FILE");
      }

      // save all infos to the registry
      if(sysEntry) {
        sysEntry->clear();
      } else {
        myEntry->addEntry(registryPrefixDescCM, "");
        sysEntry = (*myEntry)[registryPrefixDescCM];
      }

      *sysEntry = *subEntry;
      
      break;
    case DATABASE:
      subEntry = (*update)[registryReloadCM];
      if (!subEntry) {
        return true;
      }    
      workedOn = true;
      if (!updateInfos()) {
        usableM.setFalseFlag("UPDATE_PREFIX_DB");
      } else {
        usableM.setTrueFlag("UPDATE_PREFIX_DB");
      }
      
      break;
    default:
      break;
  }

  return true;  
}

//==============================================================================
//==============================================================================
void DAT::PrefixDesc::PlugIn::setInputList(const BAS::RegistryEntry * subEntry)
{
  D_ENTER("DAT::PrefixDesc::PlugIn::setInputList(const BAS::RegistryEntry *)");
  
  // clear the old list
  inputFileListM.clear();

  // collect all names from the registry with the name File
  for (size_t i=0; i < (*subEntry).entries(); i++) {
    if ((*subEntry)[i]->name() == "File") {
      inputFileListM.append((*subEntry)[i]->value());
    }      
  }
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::updateInfos()
{
  D_ENTER("DAT::PrefixDesc::PlugIn::updateInfos()");

  bool retValue = true;
  BAS::OnlyPointer<PrefixDescTree>   orgTree;

  // should we safe the old datas?
  if ((prefixDescTreeM != 0) && (reuseOnFailureM))  {
    orgTree = prefixDescTreeM;
  } 

  // create a new description tree
  prefixDescTreeM = new PrefixDescTree( valueCLIBaseM );
  
  switch (valueSourceM) {
    case FILE:
      retValue = loadDataFromFile();
      break;
    case DATABASE:
      retValue = loadDataFromDB();
      break;
    default:
      retValue = false;
      break;
  }

  // if we have an error, we must delete teh tree or reuse the old tree
  if(!retValue) {
    BAS::Message evt(name(), eventHandlerNameM, "EVT::RELOAD_FAILED");
    sendMessage(evt);
    
    if (reuseOnFailureM) {
      prefixDescTreeM = orgTree;
    } else {
      // remove all nodes
      prefixDescTreeM = 0;
    }
  } else {
    BAS::Message evt(name(), eventHandlerNameM, "EVT::RELOAD_SUCCESSFUL");
    sendMessage(evt);
  }

  usableM.setFlag("UPDATE_DATA", retValue);
  return retValue;
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::buildTreeFromFile(const BAS::String & prefixFile,
                                                          PrefixDescTree * tree)
{
  D_ENTER("DAT::PrefixDesc::PlugIn::buildTree(const BAS::String &, PrefixDescTree *)");

  STR::FileIoTurbo prefixFileStream;
  int64            lineCount = 0;
  int             ret;
  BAS::String     line, dummy;
  BAS::StringList argList, lineValues;
  PrefixItemT     newPrefixItem;

  prefixFileStream.openFile(prefixFile, ios::in);

  if (prefixFileStream.fail()) {
    setStatus("INF_PREFIX_DATA_NOT_LOADED", BAS::Status::warning, prefixFile);
    return false;
  } 
  setStatus("INF_START_LOADING_DATA", BAS::Status::normal, prefixFile);
  
  // read all line from file
  while (!prefixFileStream.eof()) {
    prefixFileStream.readLine(line);
    lineCount++;

    // is something in the line
    if (!line.isNull()) {
      lineValues = line.split(';');
      // could I understand the line
      if (lineValues.entries() == 2) {
        newPrefixItem.prefix = lineValues(0).strip(BAS::String::both);
        newPrefixItem.description = lineValues(1).strip(BAS::String::both);
        
        // insert new entry in the tree
        if ((ret = tree->insert(newPrefixItem.prefix, newPrefixItem)) < 0) {
          D_PRINT("Error while inserting line " << lineCount);
          argList.clear();
          dummy.convert(lineCount);
          argList.append(dummy);
          argList.append(prefixFile);
          setStatus("ERR_DAT_PREFDESC_INS_TREE_FILE", BAS::Status::major, argList);
          return false;
        }
      } else {
        dummy.convert(lineCount);
        setStatus("ERR_PREFIX_DATA_NO_DELIM", BAS::Status::major, dummy);
        return false;
      }
    }
  }
  prefixFileStream.closeFile();

  // give us a litte information
  dummy.convert(lineCount);
  setStatus("INF_NUM_LINES_READ", BAS::Status::normal, dummy);
  setStatus("INF_FINISHED_LOADING_DATA", BAS::Status::normal, prefixFile);

  D_PRINT (" lineCount " << lineCount);
  D_PRINT (" Treennodes " << tree->treeNodeCount());

  return true ;
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::buildTreeFromDB(const BAS::String & tableName,
                                                        PrefixDescTree * tree)
{
  D_ENTER("DAT::PrefixDesc::PlugIn::buildTreeFromDB(BAS::String &, PrefixDescTree * tree)");

  RWPRECONDITION(tree);
  
  setStatus("INF_START_LOADING_DBDATA", BAS::Status::normal, tableName);
  
  RWDBConnection conn = dataPlugInM -> openConnection();
  RWDBTable int_DestDesc = conn.database().table(tableName);
  
  if (!int_DestDesc.isValid()) {
    setStatus("ERR_DB_CONNECTION_NOT_VALID", BAS::Status::critical);
    return false;
  }
  
  RWDBSelector select = conn.database().selector();    
  select << int_DestDesc["areacode"]
         << int_DestDesc["type"]
         << int_DestDesc["name"];

  BAS::String        type;
  BAS::String        dummy;
  BAS::StringList    argList;
  int64              lineCount = 0;
  PrefixItemT       newPrefixItem;
  RWDBReader rdr = select.reader(conn);

  if(!rdr.status().isValid()) {
    // generate error status.
    setStatus("ERR_DATABASE",
               BAS::Status::critical,
               dataPlugInM->errorMessage(rdr.status()) );

    return false;
  }

  // read every row from the table
  while(rdr()) {
    rdr >> newPrefixItem.prefix 
        >> type 
        >> newPrefixItem.description;

    if(!rdr.status().isValid()) { 
     
      // generate error status.
      setStatus("ERR_DATABASE",
               BAS::Status::critical,
               dataPlugInM->errorMessage(rdr.status()));
      // delete all data
      return false;
    } else {

      if (tree->insert(newPrefixItem.prefix, newPrefixItem) < 0) {
        D_PRINT("Error while inserting line " << lineCount);
        argList.clear();
        dummy.convert(lineCount);
        argList.append(dummy);
        argList.append(dbTableNameCM);
        setStatus("ERR_DAT_PREFDESC_INS_TREE_DB", BAS::Status::major, argList);
        return false;
      }
      lineCount++;
    }
  }

  // give us a litte information
  dummy.convert(lineCount);
  setStatus("INF_NUM_LINES_READ", BAS::Status::normal, dummy);

  setStatus("INF_FINISHED_LOADING_DBDATA", BAS::Status::normal, tableName);
  return true;
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::search(const BAS::String & number, 
                                  BAS::String & decription ) const
{
  D_ENTER("DAT::PrefixDesc::PlugIn::search( const BAS::String&, BAS::String&)");

  if (isValid()) {
    PrefixItemT   prefixItem;
    
    // search the number in the tree
    if (prefixDescTreeM->search (number, prefixItem, false)) {
      decription = prefixItem.description;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::search(const BAS::String & number, 
                                  BAS::String & description,
                                  BAS::String & prefix)const
{
  D_ENTER("DAT::PrefixDesc::PlugIn::search( const BAS::String&, BAS::String&, BAS::String &)");

  if (isValid()) {
    PrefixItemT   prefixItem;
    
    // search the number in the tree
    if (prefixDescTreeM->search (number, prefixItem, false)) {
      description = prefixItem.description;
      prefix      = prefixItem.prefix;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

//==============================================================================
//==============================================================================
bool DAT::PrefixDesc::PlugIn::isUsable()
{
  D_ENTER("DAT::PrefixDesc::PlugIn::isUsable()");
  bool retVal = true;
  
  if (!PLG::DataPlugIn::isUsable()) {
    setStatus("ERR_NOT_USABLE", BAS::Status::major, "DAT::PrefixDesc::PlugIn::PLG::DataPlugIn");
    retVal = false;
  }

  if (dataPlugInM != 0) {
    if (!dataPlugInM->isUsable()) {
      setStatus("ERR_NOT_USABLE", BAS::Status::major, "DAT::PrefixDesc::PlugIn::dataPlugInM");
      retVal = false;
    }
  }
  
  if(!prefixDescTreeM.get()) {
    setStatus("ERR_NOT_USABLE", BAS::Status::major, "DAT::PrefixDesc::PlugIn::prefixDescTree");
    retVal = false;
  }

  if (!usableM.summary()) {
    retVal = false;
    BAS::Status msg(name(), "ERR_IN_SECTION", BAS::Status::major);
  
    PBC::Usable::UsableHashType::const_iterator itr;
    
    itr = usableM.usableHash().begin();
    
    while(itr != usableM.usableHash().end()) {
      if (!(*itr).second) {
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
extern "C" DAT::PrefixDesc::PlugIn* MODULE_START (const BAS::String& name)
{
  D_ENTER_F("extern C DAT::PrefixDesc::PlugIn *ModuleStart(BAS::String& name)");

  return (new DAT::PrefixDesc::PlugIn(name, "10012"));
}
