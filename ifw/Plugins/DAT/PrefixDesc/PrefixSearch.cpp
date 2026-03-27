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
//   Implementation of the class DAT::PrefixSearch.
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
// $RCSfile: DAT::PrefixSearch.cpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2000/10/12 06:29:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DAT::PrefixSearch.cpp,v $
// Revision 1.2  2000/10/12 06:29:38  sd
// - Changes to support the IBM xlC compiler.
//
// Revision 1.1  2000/09/19 10:50:32  sd
// - Initial revision of the iScript extension.
//
//==============================================================================


#include "BAS/Trace.hpp"
#include "SCR/Data.hpp"
#include "SCR/FctDescr.hpp"
#include "SCR/ParserStack.hpp"
#include "SCR/Interpreter.hpp"
#include "DAT/PrefixSearch.hpp"
#include "DAT/PrefixIScriptExt.hpp"

//==============================================================================
// Constructor
//==============================================================================
DAT::PrefixDesc::PrefixSearch::PrefixSearch( DAT::PrefixDesc::PrefixIScriptExt* prefixExtension,
                                    SCR::StringNode*       cliNode,
                                    SCR::StringDataNode*   prefixDataNode,
                                    SCR::StringDataNode*   descriptionDataNode )
  : prefixExtensionM( prefixExtension ),
    cliNodeM( cliNode ),
    prefixDataNodeM( prefixDataNode ),
    descriptionDataNodeM( descriptionDataNode )
{
  D_ENTER( "DAT::PrefixDesc::PrefixSearch::PrefixSearch(DAT::PrefixDesc::PrefixIScriptExt*,"
           "SCR::StringNode*)" );
  RWPRECONDITION(prefixExtension != 0 );
  RWPRECONDITION(dynamic_cast<SCR::StringNode*>( cliNode ) != 0 );
  RWPRECONDITION(dynamic_cast<SCR::StringDataNode*>( prefixDataNode ) != 0 );
  RWPRECONDITION(dynamic_cast<SCR::StringDataNode*>( descriptionDataNode ) != 0);
}

//==============================================================================
// Destructor
//==============================================================================
DAT::PrefixDesc::PrefixSearch::~PrefixSearch()
{
  D_ENTER( "DAT::PrefixDesc::PrefixSearch::~PrefixSearch()" );

  if ( cliNodeM != 0 )
  {
    delete cliNodeM;
  }
  if ( prefixDataNodeM != 0 )
  {
    delete prefixDataNodeM;
  }
  if ( descriptionDataNodeM != 0 )
  {
    delete descriptionDataNodeM;
  }    
}

//==============================================================================
// Result function
//==============================================================================
bool
DAT::PrefixDesc::PrefixSearch::result()
{
  D_ENTER( "DAT::PrefixDesc::PrefixSearch::result()" );
  RWPRECONDITION( prefixExtensionM != 0 );

  if ( prefixExtensionM->prefixSearch( cliNodeM->result(),
                                       descriptionM,
                                       prefixM ) == true )
  {
    D_PRINT( "INFO: description found" );
    descriptionDataNodeM->set( descriptionM );
    prefixDataNodeM->set( prefixM );
    return true;
  }

  D_PRINT( "INFO: no description found" );
  return false;
}

//==============================================================================
// Factory for function creation
//==============================================================================
SCR::Node*
DAT::PrefixDesc::PrefixSearch::factory( SCR::Interpreter&    interpreter,
                           SCR::ParserStack&    stack,
                           const SCR::FctDescr& descr )
{
  D_ENTER_F( "DAT::PrefixDesc::PrefixSearch::factory(...)" );
  
  //----------------------------------------------------------------------------
  // Get the prefix iScript extension from interpreter
  //----------------------------------------------------------------------------
  DAT::PrefixDesc::PrefixIScriptExt* prefixExtension = 
    dynamic_cast<DAT::PrefixDesc::PrefixIScriptExt*>( 
      interpreter.extension( "DAT::PrefixDesc::PrefixDesc" ) );
  if ( prefixExtension == 0 )
  {
    interpreter.logError( "failed to get extension from interpreter" );
    return 0;
  }

  //----------------------------------------------------------------------------
  // Get the parameters from the data stack. 
  //----------------------------------------------------------------------------
  SCR::StringDataNode* prefixNode = (SCR::StringDataNode*) stack.popData();
  SCR::StringDataNode* descrNode  = (SCR::StringDataNode*) stack.popData();
  SCR::StringNode*     cliNode    = (SCR::StringNode*)     stack.popData(); 

  //----------------------------------------------------------------------------
  // Create new DAT::PrefixDesc::PrefixSearch node
  //----------------------------------------------------------------------------
  return new DAT::PrefixDesc::PrefixSearch( prefixExtension, cliNode, prefixNode, descrNode);
}
