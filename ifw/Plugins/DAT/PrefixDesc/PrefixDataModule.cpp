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
//   Implementation of the class DAT::PrefixDataModule.
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
// $RCSfile: DAT::PrefixDataModule.cpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2000/10/12 06:29:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DAT::PrefixDataModule.cpp,v $
// Revision 1.2  2000/10/12 06:29:38  sd
// - Changes to support the IBM xlC compiler.
//
// Revision 1.1  2000/09/19 10:50:32  sd
// - Initial revision of the iScript extension.
//
//==============================================================================


#include "BAS/Trace.hpp"
#include "SCR/FctDescr.hpp"
#include "SCR/ParserStack.hpp"
#include "SCR/Interpreter.hpp"
#include "DAT/PrefixIScriptExt.hpp"
#include "DAT/PrefixDataModule.hpp"

//==============================================================================
// Constructor
//==============================================================================
DAT::PrefixDesc::PrefixDataModule::PrefixDataModule( DAT::PrefixDesc::PrefixIScriptExt* prefixExtension,
                                            SCR::StringNode*       prefixModuleNode )
  : prefixExtensionM( prefixExtension ),
    prefixModuleNodeM( prefixModuleNode )
{
  D_ENTER( "DAT::PrefixDesc::PrefixDataModule::PrefixDataModule(DAT::PrefixDesc::PrefixIScriptExt*,"
           "SCR::StringNode*)" );
  RWPRECONDITION( prefixExtension != 0 );
  RWPRECONDITION( dynamic_cast<SCR::StringNode*>(prefixModuleNode) != 0 );
}

//==============================================================================
// Destructor
//==============================================================================
DAT::PrefixDesc::PrefixDataModule::~PrefixDataModule()
{
  D_ENTER( "DAT::PrefixDesc::PrefixDataModule::~PrefixDataModule()" );
  delete prefixModuleNodeM;
}

//==============================================================================
// Result function
//==============================================================================
bool
DAT::PrefixDesc::PrefixDataModule::result()
{
  D_ENTER( "DAT::PrefixDesc::PrefixDataModule::result()" );
  RWPRECONDITION( prefixExtensionM != 0 );

  return prefixExtensionM->prefixDataModule( prefixModuleNodeM->result() );
}

//==============================================================================
// Factory for function creation
//==============================================================================
SCR::Node*
DAT::PrefixDesc::PrefixDataModule::factory( SCR::Interpreter&    interpreter,
                               SCR::ParserStack&    stack,
                               const SCR::FctDescr& descr )
{
  D_ENTER_F( "DAT::PrefixDesc::PrefixDataModule::factory(...)" );
  
  //----------------------------------------------------------------------------
  // Get the first parameter from data stack
  //----------------------------------------------------------------------------
  SCR::StringNode* prefixDataModule = (SCR::StringNode*) stack.popData();

  //----------------------------------------------------------------------------
  // Get the prefixomer iScript extension from interpreter
  //----------------------------------------------------------------------------
  DAT::PrefixDesc::PrefixIScriptExt* prefixExtension = 
    dynamic_cast<DAT::PrefixDesc::PrefixIScriptExt*>( interpreter.extension( "DAT::PrefixDesc::PrefixDesc" ) );
  if ( prefixExtension == 0 )
  {
    interpreter.logError( "failed to get extension from interpreter" );
    delete prefixDataModule;
    return 0;
  }

  return new DAT::PrefixDesc::PrefixDataModule( prefixExtension, prefixDataModule );
}


