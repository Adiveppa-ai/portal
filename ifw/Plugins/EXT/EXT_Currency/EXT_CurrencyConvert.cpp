//==============================================================================
//
//             1998, 1999, 2000 (c) Copyright by SOLUTION42 AG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: API/samples/EXT_Currency
//------------------------------------------------------------------------------
// Module Description:
//   Implementation of the class EXT_CurrencyConvert.
//
// Open Points:
//   none
//
// Review Status:
//   finished
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: EXT_CurrencyConvert.cpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/01/17 13:21:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_CurrencyConvert.cpp,v $
// Revision 1.1  2001/01/17 13:21:06  sd
// - Initial revision
//
//==============================================================================

static const char* rcsid()
{
  return "$Id: EXT_CurrencyConvert.cpp,v 1.1 2001/01/17 13:21:06 sd Exp $";
};

#include "BAS_Trace.hpp"
#include "SCR_ParserFunctions.hpp"
#include "EXT_Currency.hpp"
#include "EXT_CurrencyConvert.hpp"

//==============================================================================
// Constructor
//==============================================================================
EXT_CurrencyConvert::EXT_CurrencyConvert( EXT_Currency*    currencyExt,
                                          SCR_StringNode*  conversionString,
                                          SCR_DecimalNode* sourceValue )
  : currencyExtM( currencyExt ),
    conversionStringM( conversionString ),
    sourceValueM( sourceValue )
{
  D_ENTER( "EXT_CurrencyConvert::EXT_CurrencyConvert(EXT_Currency*,SCR_StringNode*,SCR_DecimalNode*" );
  RWPRECONDITION( currencyExt != 0 );
  RWPRECONDITION( dynamic_cast<SCR_StringNode*>(conversionString) != 0 );
  RWPRECONDITION( dynamic_cast<SCR_DecimalNode*>(sourceValue) != 0 );
}

//==============================================================================
// Destructor
//==============================================================================
EXT_CurrencyConvert::~EXT_CurrencyConvert()
{
  D_ENTER( "EXT_CurrencyConvert::~EXT_CurrencyConvert()" );
  delete conversionStringM;
  delete sourceValueM;
}

//==============================================================================
// Execute the function
//==============================================================================
const BAS_Decimal& EXT_CurrencyConvert::result()
{
  D_ENTER( "EXT_CurrencyConvert::result()" );
  
  // get the conversion string from parameter one (call subnodes result() function)
  const BAS_String& conversion = conversionStringM->result();
  
  // retrieve the conversion factor from the extension (is 0.0 on error)
  BAS_Decimal conversionFactor = currencyExtM->conversionFactor( conversion );
  
  // calculate the result
  resultM = sourceValueM->result() * conversionFactor;
  
  return resultM;
}

//==============================================================================
// Factory for function node creation
//==============================================================================
SCR_Node* EXT_CurrencyConvert::factory( SCR_Interpreter&    interpreter,
                                        SCR_ParserStack&    stack,
                                        const SCR_FctDescr& descr )
{
  D_ENTER( "EXT_CurrencyConvert::factory(SCR_Interpreter&,SCR_ParserStack&,"
           "const SCR_FctDescr&)");

  // get the extension pointer from the interpreter
  EXT_Currency* extension = dynamic_cast<EXT_Currency*>( 
    interpreter.extension( EXT_Currency::extensionNameCM ) );
  if ( extension == 0 )
  {
    // this normaly can not happen, but ...
    SCR_YaccError( "failed to get extension `" + EXT_Currency::extensionNameCM +
                   "' from interpreter" );
    return 0;
  }
  
  // type checking is done by the compiler for fixed argument functions so we can simple pop the parameters
  // (if our function description is right!)
  
  // pop the second argument first
  SCR_DecimalNode* source = (SCR_DecimalNode*) stack.popData();
  
  // now pop the first argument from stack
  SCR_StringNode*  conversion = (SCR_StringNode*) stack.popData();
  
  // create the new function node
  return new EXT_CurrencyConvert( extension, conversion, source );
}
