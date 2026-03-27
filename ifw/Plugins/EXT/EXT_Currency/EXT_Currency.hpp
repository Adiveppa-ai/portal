#ifndef EXT_CURRENCY_HPP
#define EXT_CURRENCY_HPP

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
//   Declaration of sample iScript extension class EXT_Currency.
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
// $RCSfile: EXT_Currency.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/01/17 13:21:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_Currency.hpp,v $
// Revision 1.1  2001/01/17 13:21:06  sd
// - Initial revision
//
//==============================================================================

#include <rw/tvmap.h>
#include <rw/thr/mutex.h>
#include "BAS_String.hpp"
#include "BAS_Decimal.hpp"
#include "SCR_Variable.hpp"
#include "SCR_Extension.hpp"

class EXT_Currency : public SCR_Extension
{
  public:

    /**@name EXT_Currency constructors and destructor */
    //@{
    
    /** Constructor
     */
    EXT_Currency();

    /** Destructor
     */
    virtual ~EXT_Currency();

    //@}

    /**@name EXT_Currency public methods */
    //@{

    /** Get the name of the extension
     *  @return Reference to the name of the extension
     */
    virtual const BAS_String& extensionName() const;

    /** Search for a variable in the extension
     *  @param name The name of the variable to seach
     *  @return Pointer to variable on success, 0 otherwise
     */
    virtual SCR_Variable* variable( const BAS_String& name );

    /** Insert/replace an exchange rate
     *  @param conversion Name of the conversion
     *  @param factor Factor for the conversion
     */
    void setExchangeRate( const BAS_String&  conversion, 
                          const BAS_Decimal& factor );

    /** Get a conversion factor from the extension
     *  @param name The name of the conversion
     *  @return Conversion factor on success, 0.0 otherwise
     */
    BAS_Decimal conversionFactor( const BAS_String& name ) const;

    //@}

  protected:

  private:
    // Hide copy constructor (not implemented)
    EXT_Currency( const EXT_Currency& other );

    // instance members
    RWTValMap<BAS_String,BAS_Decimal,less<BAS_String> > conversionTableM;

    // class members
    static RWMutexLock      mutexCM;
    static int              instancesCM;
    static SCR_VariableMap  constantsCM;

  public:
    static const BAS_String extensionNameCM;
};

#endif // EXT_CURRENCY_HPP
