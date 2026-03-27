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
//   Implementation of the class EXT_SetExchangeRates.
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
// $RCSfile: EXT_SetExchangeRates.cpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/01/17 13:21:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_SetExchangeRates.cpp,v $
// Revision 1.1  2001/01/17 13:21:06  sd
// - Initial revision
//
//==============================================================================

static const char* rcsid()
{
  return "$Id: EXT_SetExchangeRates.cpp,v 1.1 2001/01/17 13:21:06 sd Exp $";
};

#include "BAS_Trace.hpp"
#include "SCR_ParserFunctions.hpp"
#include "EXT_Currency.hpp"
#include "EXT_SetExchangeRates.hpp"

//==============================================================================
// Constructor
//==============================================================================
EXT_SetExchangeRates::EXT_SetExchangeRates( EXT_Currency* currencyExt )
  : currencyExtM( currencyExt )
{
  D_ENTER( "EXT_SetExchangeRates::EXT_SetExchangeRates(EXT_Currency*)" );
  RWPRECONDITION( currencyExtM != 0 );
}

//==============================================================================
// Destructor
//==============================================================================
EXT_SetExchangeRates::~EXT_SetExchangeRates()
{
  D_ENTER( "EXT_SetExchangeRates::~EXT_SetExchangeRates()" );
  
  conversionsM.clearAndDestroy();
  factorsM.clearAndDestroy();
}

//==============================================================================
// Add new parameters to the function node
//==============================================================================
void EXT_SetExchangeRates::addConversion( SCR_StringNode*  conversion, 
                                          SCR_DecimalNode* factor )
{
  D_ENTER( "EXT_SetExchangeRates::addConversion(SCR_StringNode*,"
           "SCR_DecimalNode*)" );
  RWPRECONDITION( dynamic_cast<SCR_StringNode*>( conversion ) != 0 );
  RWPRECONDITION( dynamic_cast<SCR_DecimalNode*>( factor ) != 0 );
  
  conversionsM.append( conversion );
  factorsM.append( factor );
}

//==============================================================================
// Execute the function
//==============================================================================
void EXT_SetExchangeRates::result()
{
  RWPRECONDITION( conversionsM.length() == factorsM.length() );

  for ( size_t i = 0; i < conversionsM.length(); i++ )
  {
    currencyExtM->setExchangeRate( conversionsM(i)->result(), 
                                   factorsM(i)->result() );
  }
}

//==============================================================================
// Factory for creating function nodes
//==============================================================================
SCR_Node* EXT_SetExchangeRates::factory( SCR_Interpreter&    interpreter,
                                         SCR_ParserStack&    stack,
                                         const SCR_FctDescr& descr )
{
  D_ENTER( "EXT_SetExchangeRates::factory(SCR_Interpreter&,SCR_ParserStack&,"
           "const SCR_FctDescr&)" );
  
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
  
  // we need an even number of arguments
  if ( stack.topNumParams() % 2 != 0 )
  {
    SCR_YaccError( "expected an even number of arguments in call to `" + 
                   descr.signature() + "'" );
          return 0;
  }
  
  // check the types
  for ( size_t i = 0; i < stack.topNumParams(); i += 2 )
  {
    // check type of factor parameter
    if ( descr.checkType( SCR_Node::DECIMAL_TYPE, stack.popType() ) == false )
    {
      // error message is written by the checkType function
      return 0;
    }
    
    // check type of conversion parameter
    if ( descr.checkType( SCR_Node::STRING_TYPE,stack.popType() ) == false )
    {
      // error message is written by the checkType function
      return 0;
    }
  }
  
  // create the function node
  EXT_SetExchangeRates* setExchRates = new EXT_SetExchangeRates( extension );
  
  // add the parameters
  for ( size_t j = 0; j < stack.topNumParams(); j += 2 )
  {
    // parameters are check, so simply use a type cast
    SCR_DecimalNode* factor     = (SCR_DecimalNode*) stack.popData();
    SCR_StringNode*  conversion = (SCR_StringNode*) stack.popData();
    
    setExchRates->addConversion( conversion, factor );
  }
  
  return setExchRates;
}
