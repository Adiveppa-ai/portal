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
// Block: API/Samples/EXT_Currency
//------------------------------------------------------------------------------
// Module Description:
//  Implementation of sample iScript extension class EXT_Currency.
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
// $RCSfile: EXT_Currency.cpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/01/17 13:21:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_Currency.cpp,v $
// Revision 1.1  2001/01/17 13:21:06  sd
// - Initial revision
//
//==============================================================================

static const char* rcsid()
{
  return "$Id: EXT_Currency.cpp,v 1.1 2001/01/17 13:21:06 sd Exp $";
};

#include "BAS_Trace.hpp"
#include "EXT_SetExchangeRates.hpp"
#include "EXT_CurrencyConvert.hpp"
#include "EXT_Currency.hpp"

// static class members of EXT_Currency class
RWMutexLock      EXT_Currency::mutexCM;
int              EXT_Currency::instancesCM     = 0;
SCR_VariableMap  EXT_Currency::constantsCM;
const BAS_String EXT_Currency::extensionNameCM = "EXT_Currency";

//==============================================================================
// Constructor
//==============================================================================
EXT_Currency::EXT_Currency()
{
  D_ENTER( "EXT_Currency::EXT_Currency()" );
  
  // make initialization thread-safe
  RWLockGuard<RWMutexLock> mutex(mutexCM);

  instancesCM++;
  if ( instancesCM == 1 )
  {
    // insert string constant containing extension version
    SCR_StringVariable* version = new SCR_StringVariable( "v1-00-00", 
                                                          true /* is const */ );
    constantsCM.insert( new BAS_String( "EXT_VERSION" ), version );

    // insert function description
    SCR_FctDescr* fctDescr =
      new SCR_FctDescr( "currencyConvert",            // the name of the function
                        SCR_Node::DECIMAL_TYPE,       // the return type of the function
                        2,                            // minimum number of arguments
                        2,                            // maximum number of arguments
                        EXT_CurrencyConvert::factory, // the factory method for function node creation
                        SCR_Node::STRING_TYPE,        // type of first parameter
                        SCR_Node::DECIMAL_TYPE );     // type of second parameter
    constantsCM.insert( new BAS_String( fctDescr->name() ), fctDescr );
    
    // insert function description
    fctDescr =
      new SCR_FctDescr( "setExchangeRates",           // the name of the function
                        SCR_Node::DECIMAL_TYPE,       // the return type of the function
                        2,                            // minimum number of arguments
                        SCR_FctDescr::UNLIMITED_ARGS, // maximum number of arguments is unlimited
                        EXT_SetExchangeRates::factory,// the factory method for function node creation
                        SCR_Node::STRING_TYPE,        // type of first parameter
                        SCR_Node::DECIMAL_TYPE );     // type of second parameter
    constantsCM.insert( new BAS_String( fctDescr->name() ), fctDescr );

  }
}

//==============================================================================
// Destructor
//==============================================================================
EXT_Currency::~EXT_Currency()
{
  D_ENTER( "EXT_Currency::~EXT_Currency()" );
  
  // make destruction thread-safe
  RWLockGuard<RWMutexLock> mutex(mutexCM);
  
  instancesCM--;
  if ( instancesCM == 0 )
  {
    // last instance removed => cleanup
    constantsCM.clearAndDestroy();
  }
}

//==============================================================================
// Get the name of the extension
//==============================================================================
const BAS_String& EXT_Currency::extensionName() const
{
  D_ENTER( "EXT_Currency::extensionName() const" );
  return EXT_Currency::extensionNameCM;
}

//==============================================================================
// Search for a variable
//==============================================================================
SCR_Variable* EXT_Currency::variable( const BAS_String& name )
{
  D_ENTER( "EXT_Currency::variable(const BAS_String&)" );
  
  return constantsCM.findValue( &name );
}

//==============================================================================
// Insert/replace a exchange rate in the conversion table
//==============================================================================
void EXT_Currency::setExchangeRate( const BAS_String&  conversion, 
                                    const BAS_Decimal& factor )
{
  D_ENTER( "EXT_Currency::setExchangeRate(const BAS_String&,const BAS_Decimal&)");
  
  if ( conversionTableM.contains( conversion ) == true )
  {
    // remove old entry if existent
    conversionTableM.remove( conversion );
  }
  
  conversionTableM.insert( conversion, factor );
}


//==============================================================================
// Get a conversion factor from the exchange rate table
//==============================================================================
BAS_Decimal EXT_Currency::conversionFactor( const BAS_String& conversion ) const
{
  D_ENTER( "EXT_Currency::conversionFactor(const BAS_String&)" );
  
  BAS_Decimal retValue(0);
  
  // retValue will stay 0.0 if no entry was found
  conversionTableM.findValue( conversion, retValue );
  
  return retValue;
}

//==============================================================================
// Generator function used by the iScript interpreter
//==============================================================================
extern "C" EXT_Currency* EXT_Currency_IScriptExtension()
{
  D_ENTER( "EXT_Currency* EXT_Currency_IScriptExtension()" );
  
  return new EXT_Currency();
}
