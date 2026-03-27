//==============================================================================
//
//      Copyright (c) 1996 - 2024 Oracle.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FCTPrefixDesc
//------------------------------------------------------------------------------
// Module Description:
//  This class is the FCT::PlugIn Implementation.
//  FCT::PlugIn is inherited from the PLG::FunctionPlugIn class.
//
//------------------------------------------------------------------------------
//
// Revision: 10005  6.7_FP2  03-May-2004  pramodk
// PRSF00108146: NT build problem: Modify build spec and LIBNAME to MAKE_STR2(LIBNAME)
//
// Revision: 10003  6.5_SP2  01-May-2003  keshav
// PRSF00039598: Changes due to registryUpdate interface change
//
// Revision 1.23  2001/10/23 13:44:14  dhatton
// PETS#40656 fix: DETAIL.B_NUMBER -> DETAIL.INTERN_B_NUMBER_ZONE.
//
// Revision 1.22  2001/08/29 12:07:03  dhatton
// Checked code review remarks.
//
// Revision 1.21  2001/08/15 09:20:55  jkeckst
// PETS 37618 Code Review
//
// Revision 1.20  2001/06/28 13:52:01  dhatton
// Additional status message.
//
// Revision 1.19  2001/06/21 09:34:25  dhatton
// Updated for v4-30-00
//
// Revision 1.18  2001/01/18 15:28:36  jkeckst
// return value for environment added
//
// Revision 1.17  2001/01/17 12:15:42  jkeckst
// API version
//
//
//==============================================================================
#include "BAS/Trace.hpp"
#include "FCT/PrefixDescPlugIn.hpp"
#include "PLI/DataCollection.hpp"
#include "PLI/DataInterface.hpp"
#include "DAT/PrefixDescPlugIn.hpp"
#include "PBC/WriteToPipelineLog.hpp"
#include "PBC/ModuleReference.hpp"

#include "EDR/Container.hpp" 
#include "EDR/Factory.hpp"


//==============================================================================

const BAS::String  FCT::PrefixDesc::PlugIn::registryDataPoolCM    ("DataPool");
const BAS::String  FCT::PrefixDesc::PlugIn::registryDataPlugInCM  ("PrefixDataModule");
const BAS::String  FCT::PrefixDesc::PlugIn::registryFormatCM      ("Format");

//==============================================================================

//-----------------------------------------------------------------------------
//Container field logical names.
//-----------------------------------------------------------------------------
const BAS::String
FCT::PrefixDesc::PlugIn::bNumberCM("B_NUMBER");
const BAS::String
FCT::PrefixDesc::PlugIn::descriptionCM("DESCRIPTION");

//-----------------------------------------------------------------------------
//Block logical names.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Container field default names.
//-----------------------------------------------------------------------------
const BAS::String
FCT::PrefixDesc::PlugIn::bNumberDefaultCM("DETAIL.INTERN_B_NUMBER_ZONE");
const BAS::String
FCT::PrefixDesc::PlugIn::descriptionDefaultCM("DETAIL.DESCRIPTION");

//-----------------------------------------------------------------------------
//Block default names.
//-----------------------------------------------------------------------------

//==============================================================================
FCT::PrefixDesc::PlugIn::PlugIn()
  : PLG::FunctionPlugIn()
  ,dataPlugInM(0)
  ,edrFactoryM(0)
{
  D_ENTER("FCT::PrefixDesc::PlugIn::PlugIn()");
}

//==============================================================================
//==============================================================================
FCT::PrefixDesc::PlugIn::PlugIn(const BAS::String& name, 
                                           const BAS::String& version)
  : PLG::FunctionPlugIn(name, version)
  ,dataPlugInM(0)
  ,edrFactoryM(0)
{
  D_ENTER("FCT::PrefixDesc::PlugIn::PlugIn(const BAS::String&)");

  // read all registry parameter  
  if(isRegistered() && isValid()) {
    isValid(readRegistry());
  }

  // set/get all environment variables  
  if(isValid()) {
    isValid(evalEnvironment());
  }
  
  // get all neccessary indices for all EDR container accesses
  if (isValid()) {
    isValid(setEDRContainerIndices());
  }
}

//==============================================================================
//==============================================================================
FCT::PrefixDesc::PlugIn::~PlugIn()
{
  D_ENTER("FCT::PrefixDesc::PlugIn::~PlugIn()");
  
  // Nothing to do here.
}

//==============================================================================
//==============================================================================
bool FCT::PrefixDesc::PlugIn::processEdrContainer(PLG::EdrContainerList& edrList)
{
  D_ENTER("FCT::PrefixDesc::PlugIn::processEdrContainer(EDR::ContainerVector *&)");

  // loop over all EDR container
  for (size_t listIdx=0; listIdx<edrList.length(); listIdx++) {
    // check if the EDR container is valid
    if(edrList(listIdx)->isValidDetail()) {
      // search in the data plugin the b-number
      if (dataPlugInM->search(edrList(listIdx)->getString(bNumberIdxM), 
                              descriptionM)) 
      {
        // if number found set the container field
        edrList(listIdx)->setString(destDescrIdxM, descriptionM);
      }
    }
  }
  
  return true;
}

//==============================================================================
//==============================================================================
bool FCT::PrefixDesc::PlugIn::evalEnvironment()
{
  D_ENTER("FCT::PrefixDesc::PlugIn::evalEnvironment()");
  
  // here you can set/get all neccesary data from other modules
  // or from the global environment.
  
  return true;
}

//==============================================================================
//==============================================================================
bool FCT::PrefixDesc::PlugIn::setEDRContainerIndices()
{
  D_ENTER("FCT::PrefixDesc::PlugIn::setEDRContainerIndices()");

  //---------------------------------------------------------------------------
  // Get the edr factory pointer.
  //---------------------------------------------------------------------------
  edrFactoryM = edrFactory();
  if( edrFactoryM == 0 )
  {
    D_PRINT("ERROR : failed to get the edr factory,");
    setStatus( "ERR_FACTORY_NOT_FOUND"
              ,BAS::Status::critical
              ,name() );
    return false;
  }
 
  
  try
  {
    // get the b-number to search for
    bNumberIdxM = 
      edrFactoryM->getIndex( MAKE_STR2(LIBNAME)
                            ,bNumberDefaultCM
                            ,bNumberCM
                            ,PBC::ModuleReference(dirName()) );
  
    // if something found, set the description in this field
    destDescrIdxM = 
      edrFactoryM->getIndex( MAKE_STR2(LIBNAME)
                            ,descriptionDefaultCM
                            ,descriptionCM
                            ,PBC::ModuleReference(dirName()) );
  }
  catch ( BAS::Status& status )
  {
    status.originatorName( PBC::ModuleReference(dirName()) );
    setStatus( status );
    PBC::writeToPipelineLog( *this, status );
    return false;
  }
  
  return true;
}

//==============================================================================
//==============================================================================
bool FCT::PrefixDesc::PlugIn::readRegistry() 
{
  D_ENTER("FCT::PrefixDesc::PlugIn::readRegistry()");

  const BAS::RegistryEntry* myEntry = registry();
  const BAS::RegistryEntry* subEntry(0);

  // check if I registered
  if (!myEntry) {
    D_PRINT("ERROR: registry subtree '" << name() << "' not found" << endl);
    setStatus("ERR_REG_SUBTREE_NOT_FOUND", BAS::Status::critical, name());
    return false;
  }

  //----------------------------------------------------------------------------
  // search for the registry entry "PrefixDataModule"
  //----------------------------------------------------------------------------
  subEntry = myEntry->find(registryDataPlugInCM);

  // found the entry
  if (subEntry) {
    BAS::String            plugInName;
    BAS::String            registryName;
    PLI::DataCollection*   dataColl(0);
    PLI::DataInterface *   plugInInt(0);
    
    // save the name of the data module
    plugInName = subEntry->value();

    // search the data pool (data module collection)
    registryName = rootName() + "." + registryDataPoolCM;
    dataColl = (PLI::DataCollection*)find( registryName );

    // if no data pool exists -> error
    if (!dataColl) {
      D_PRINT("ERROR: object '" << registryName << "' could not be found");
      setStatus("ERR_OBJ_NOT_FOUND", BAS::Status::critical, registryName );
      return false;
    }

    // check if the data pool is valid
    if ( dataColl->isRegistered() == false ) {
      D_PRINT("ERROR: object '" << registryName << "' is not registered");
      setStatus("ERR_REG_SUBTREE_NOT_FOUND", BAS::Status::critical, registryName );
      return false ;
    }

    // find the data module in the data pool
    plugInInt = (*dataColl)[plugInName];

    // found the data module?
    if (plugInInt) {
      // set the pointer to the data module
      dataPlugInM = dynamic_cast<DAT::PrefixDesc::PlugIn *> (plugInInt->plugIn());
    
      // check if the cast was valid
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
    BAS::String regName = name() + "." + registryDataPlugInCM;
    D_PRINT("ERROR: registry name '" << regName << "' not found" << endl);
    setStatus("ERR_REG_NAME_NOT_FOUND", BAS::Status::critical, regName);
    return false;
  }
  
  return true;
}

//==============================================================================
//==============================================================================
bool FCT::PrefixDesc::PlugIn::registryUpdate(const BAS::RegistryEntry* update,
					     BAS::ProtectedBool&       workedOn)
{
  D_ENTER ("FCT::PrefixDesc::PlugIn::registryUpdate(const BAS::RegistryEntry*, BAS::ProtectedBool& )");

  // call only the base class function
  return PLG::FunctionPlugIn::registryUpdate(update, workedOn);
  
  // here you must update all other registry entries
}

//==============================================================================
//==============================================================================
bool FCT::PrefixDesc::PlugIn::isUsable()
{
  D_ENTER("FCT::PrefixDesc::PrefixDescPlgIn::isUsable()");
  bool  retVal  = true;
  
  // check if the base class is usable
  if (!PLG::FunctionPlugIn::isUsable()) {
    BAS::Status  msg (name(), "ERR_NOT_USABLE", BAS::Status::critical, "FCT::PrefixDesc::PrefixDescPlgIn::PLG::FunctionPlugIn");
    writeToPipelineLog(msg);
    retVal = false;
  }

  // is there a data module?
  if (dataPlugInM) {
    //is the data module valid?
    if (!dataPlugInM->isUsable()) {
      BAS::Status  msg (name(), "ERR_NOT_USABLE", BAS::Status::critical, "FCT::PrefixDesc::PrefixDescPlgIn::dataPlugInM");
      writeToPipelineLog(msg);
      retVal = false;
    }
  } else {
   BAS::Status  msg (name(), "ERR_NOT_USABLE", BAS::Status::critical, "FCT::PrefixDesc::PrefixDescPlgIn::dataPlugInM is missing");
   writeToPipelineLog(msg);
   retVal = false;
  }
  
  // here comes all other check for the right using of this module
  
  
  return (retVal);
}

//==============================================================================
//==============================================================================
extern "C" FCT::PrefixDesc::PlugIn * MODULE_START (const BAS::String& name)
{
  D_ENTER_F("extern C FCT::PrefixDesc::PlugIn *ModuleStart(BAS::String& name)");

  return (new FCT::PrefixDesc::PlugIn(name, "10006"));
}

//==============================================================================
//==============================================================================
extern "C" FCT::PrefixDesc::PlugIn *ModuleStartNL()
{
  D_ENTER_F("extern C FCT::PrefixDesc::PlugIn *ModuleStartNL()");

  return (new FCT::PrefixDesc::PlugIn());
}
