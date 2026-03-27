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
//   Implementation of the class DAT::PrefixError.
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
// $RCSfile: DAT::PrefixError.cpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2000/10/12 06:29:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DAT::PrefixError.cpp,v $
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
#include "DAT/PrefixError.hpp"
#include "DAT/PrefixIScriptExt.hpp"

//==============================================================================
// Constructor
//==============================================================================
DAT::PrefixDesc::PrefixError::PrefixError( DAT::PrefixDesc::PrefixIScriptExt* prefixExtension )
  : prefixExtensionM( prefixExtension )
{
  D_ENTER( "DAT::PrefixDesc::PrefixError::PrefixError(DAT::PrefixDesc::PrefixIScriptExt*)" );
  RWPRECONDITION( prefixExtension != 0 );
}

//==============================================================================
// Destructor
//==============================================================================
DAT::PrefixDesc::PrefixError::~PrefixError()
{
  D_ENTER( "DAT::PrefixDesc::PrefixError::~PrefixError()" );
}

//==============================================================================
// Result function
//==============================================================================
const BAS::String&
DAT::PrefixDesc::PrefixError::result()
{
  D_ENTER( "DAT::PrefixDesc::PrefixError::result()" );
  RWPRECONDITION( prefixExtensionM != 0 );

  return prefixExtensionM->failure();
}

//==============================================================================
// Factory for function creation
//==============================================================================
SCR::Node*
DAT::PrefixDesc::PrefixError::factory( SCR::Interpreter&    interpreter,
                          SCR::ParserStack&    stack,
                          const SCR::FctDescr& descr )
{
  D_ENTER_F( "DAT::PrefixDesc::PrefixError::factory(...)" );
  
  //----------------------------------------------------------------------------
  // Get the prefixomer iScript extension from interpreter
  //----------------------------------------------------------------------------
  DAT::PrefixDesc::PrefixIScriptExt* prefixExtension = 
    dynamic_cast<DAT::PrefixDesc::PrefixIScriptExt*>( 
      interpreter.extension( "DAT::PrefixDesc::PrefixDesc" ) );
  if ( prefixExtension == 0 )
  {
    interpreter.logError( "failed to get extension from interpreter" );
    return 0;
  }

  return new DAT::PrefixDesc::PrefixError( prefixExtension );
}
