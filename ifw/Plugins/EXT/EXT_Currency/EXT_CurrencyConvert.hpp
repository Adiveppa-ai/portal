#ifndef EXT_CURRENCYCONVERT_HPP
#define EXT_CURRENCYCONVERT_HPP

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
// Block: API/samples/EXE_Currency
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the function node for the iScript function currencyConvert()
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
// $RCSfile: EXT_CurrencyConvert.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/01/17 13:21:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_CurrencyConvert.hpp,v $
// Revision 1.1  2001/01/17 13:21:06  sd
// - Initial revision
//
//==============================================================================

#include "SCR_Node.hpp"
#include "SCR_FctDescr.hpp"
#include "SCR_ParserStack.hpp"
#include "SCR_Interpreter.hpp"

class EXT_Currency;

/** <b><tt>EXT_CurrencyConvert</tt></b> is the function node for the iScript
 *  function currencyConvert().
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EXT_CurrencyConvert.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/01/17 13:21:06 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EXT_CurrencyConvert : public SCR_DecimalNode
{
  public:
    /**@name EXT_CurrencyConvert constructors and destructor */
    //@{
    
    // we do not need a public constructor!

    /** Destructor
     */
    virtual ~EXT_CurrencyConvert();

    //@}

    /**@name EXT_CurrencyConvert public methods */
    //@{

    /** Execute the function
     *  @return Result of the currency conversion
     */
    virtual const BAS_Decimal& result();

    /** Factory for creating a new EXT_CurrencyConvert function node
     *  @param interpreter The current interpreter
     *  @param stack The compiler's data stack
     *  @param descr The function description registered at the extension
     *  @return Pointer to new node on success, 0 otherwise
     */
    static SCR_Node* factory( SCR_Interpreter&    interpreter,
                              SCR_ParserStack&    stack,
                              const SCR_FctDescr& descr );

    //@}

  protected:
    /* Constructor
     * @param currencyExt Pointer to assciated currency extension
     * @param conversionString Conversion string parameter node
     * @param sourceValue Function node for the value to convert
     */
    EXT_CurrencyConvert( EXT_Currency*    currencyExt,
                         SCR_StringNode*  conversionString,
                         SCR_DecimalNode* sourceValue );

  private:
    // Hide the default and copy constructor (not implemented)
    EXT_CurrencyConvert();
    EXT_CurrencyConvert( const EXT_CurrencyConvert& other );
    
    // instance members
    EXT_Currency*    currencyExtM;
    SCR_StringNode*  conversionStringM;
    SCR_DecimalNode* sourceValueM;
    BAS_Decimal      resultM;
};

#endif // EXT_CURRENCYCONVERT_HPP
