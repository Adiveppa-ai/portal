//==============================================================================
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
//   Implementation of the class DAT::PrefixIScriptExt.
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
// $RCSfile: DAT::PrefixIScriptExt.cpp,v $
// $Revision: 1.3 $
// $Author: sd $
// $Date: 2006/07/31 08:30:50 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DAT::PrefixIScriptExt.cpp,v $
// Revision 1.3  2006/07/31 08:30:50  amadhuka
// - PRSF00225698 : SCM_TAP3_Beppi DAT_PrefixDesc iscript extension does not work any more
//
// Revision 1.2  2000/09/27 08:30:50  sd
// - Changes in iScript extension due to modifications in SCR.
//
// Revision 1.1  2000/09/19 10:50:32  sd
// - Initial revision of the iScript extension.
//
//==============================================================================


#include "BAS/Trace.hpp"
#include "SCR/FctDescr.hpp"
#include "DAT/PrefixDataModule.hpp"
#include "DAT/PrefixSearch.hpp"
#include "DAT/PrefixError.hpp"
#include "DAT/PrefixDescPlugIn.hpp"
#include "DAT/PrefixIScriptExt.hpp"

//==============================================================================
// Global values
//==============================================================================
SCR::VariableMap DAT::PrefixDesc::PrefixIScriptExt::constantsCM;

//==============================================================================
// Constructor
//==============================================================================
DAT::PrefixDesc::PrefixIScriptExt::PrefixIScriptExt()
  : prefixDescrPlugInM( 0 )
{
  D_ENTER( "DAT::PrefixDesc::PrefixIScriptExt::PrefixIScriptExt()" );
}

//==============================================================================
// Destructor
//==============================================================================
DAT::PrefixDesc::PrefixIScriptExt::~PrefixIScriptExt()
{
  D_ENTER( "DAT::PrefixDesc::PrefixIScriptExt::~PrefixIScriptExt()" );
}

//==============================================================================
// Get the name of the extension
//==============================================================================
const BAS::String&
DAT::PrefixDesc::PrefixIScriptExt::extensionName() const
{
  D_ENTER( "DAT::PrefixDesc::PrefixIScriptExt::extensionName() const" );

  static const BAS::String extensionName = "DAT::PrefixDesc::PrefixDesc";

  return extensionName;
}

//==============================================================================
// Set the prefix data module
//==============================================================================
bool
DAT::PrefixDesc::PrefixIScriptExt::prefixDataModule( const BAS::String& name )
{
  D_ENTER( "DAT::PrefixDesc::PrefixIScriptExt::prefixDataModule(const BAS::String&)" );

  //----------------------------------------------------------------------------
  // Search for the registered object
  //----------------------------------------------------------------------------
  BAS::RegisteredObject* registeredObject = 
    BAS::RegisteredObject::find( name );
  if ( registeredObject == 0 )
  {
    D_PRINT( "ERROR: no such object " << name );
    failureM = "no such object `" + name + "'";
    return false;
  }

  //----------------------------------------------------------------------------
  // Check if object is a DAT::PrefixDesc::CustomerPlugIn
  //----------------------------------------------------------------------------
  prefixDescrPlugInM = dynamic_cast<DAT::PrefixDesc::PlugIn*>( registeredObject );
  if ( prefixDescrPlugInM == 0 )
  {
    D_PRINT( "ERROR: " << name << " is no DAT::PrefixDesc::PlugIn" );
    failureM = name + " is no DAT::PrefixDesc::PlugIn";
    return false;
  }
    
  return true;
}

//==============================================================================
// Search the for the prefix description
//==============================================================================
bool
DAT::PrefixDesc::PrefixIScriptExt::prefixSearch( const BAS::String& number,
                                    BAS::String&       description,
                                    BAS::String&       prefix )
{
  D_ENTER( "DAT::PrefixDesc::PrefixIScriptExt::prefixSearch(const BAS::String&,...)" );

  D_PRINT( "INFO: searching " << number );

  //----------------------------------------------------------------------------
  // Check if extension is connected to a data module
  //----------------------------------------------------------------------------
  if ( prefixDescrPlugInM == 0 )
  {
    D_PRINT( "INFO: no connection to a prefix data module" );
    failureM = "no connection to a prefix description data module";
    return false;
  }

  //----------------------------------------------------------------------------
  // Search for the description
  //----------------------------------------------------------------------------
  return prefixDescrPlugInM->search( number, description, prefix );
}

//==============================================================================
// Get a variable from the DAT::PrefixDesc::PrefixDesc extension
//==============================================================================
SCR::Variable*
DAT::PrefixDesc::PrefixIScriptExt::variable( const BAS::String& name )
{
  D_ENTER( "DAT::PrefixDesc::PrefixIScriptExt::variable(const BAS::Stringg&)" );

  //----------------------------------------------------------------------------
  // Check if function description table is already initialized
  //----------------------------------------------------------------------------
  if ( constantsCM.isEmpty() )
  {
    //--------------------------------------------------------------------------
    // Bool prefixDataModule(String)
    //--------------------------------------------------------------------------
    SCR::FctDescr* fctDescr =
      new SCR::FctDescr(
        "prefixDataModule",           // name
        SCR::Node::BOOL_TYPE,          // return type
        1,                            // minimum number of arguments
        1,                            // maximum number of arguments
        DAT::PrefixDesc::PrefixDataModule::factory,// factory for creation
        SCR::Node::STRING_TYPE         // type of first argument
        );
    constantsCM.insert( new BAS::String( fctDescr->name() ), fctDescr );

    //--------------------------------------------------------------------------
    // String prefixError()
    //--------------------------------------------------------------------------
    fctDescr =
      new SCR::FctDescr(
        "prefixError",               // name
        SCR::Node::STRING_TYPE,       // return type
        0,                           // minimum number of arguments
        0,                           // maximum number of arguments
        DAT::PrefixDesc::PrefixError::factory     // factory for creation
        );
    constantsCM.insert( new BAS::String( fctDescr->name() ), fctDescr );

    //--------------------------------------------------------------------------
    // Bool prefixSearch(String,LeftString,LeftString)
    //--------------------------------------------------------------------------
    fctDescr =
      new SCR::FctDescr(
        "prefixSearch",              // name
        SCR::Node::BOOL_TYPE,         // return type
        3,                           // minimum number of arguments
        3,                           // maximum number of arguments
        DAT::PrefixDesc::PrefixSearch::factory,   // factory for creation
        SCR::Node::STRING_TYPE,
        SCR::Node::LEFT_STRING_TYPE,
        SCR::Node::LEFT_STRING_TYPE
        );
    constantsCM.insert( new BAS::String( fctDescr->name() ), fctDescr );
  }

  return constantsCM.findValue( &name );
}

//==============================================================================
// Generator function for the iScript extension
//==============================================================================
extern "C" DAT::PrefixDesc::PrefixIScriptExt* DAT_PrefixDesc_IScriptExtension() 
{
  D_ENTER_F( "DAT::PrefixDesc::PrefixIScriptExt* DAT::PrefixDesc::PrefixDesc_IScriptExtension()" );

  return new DAT::PrefixDesc::PrefixIScriptExt();
}
