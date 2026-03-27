#ifndef EXT_SETEXCHANGERATES_HPP
#define EXT_SETEXCHANGERATES_HPP

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
//   Declaration of the function node for the iScript function 
//   setExchangeRates()
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
// $RCSfile: EXT_SetExchangeRates.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/01/17 13:21:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_SetExchangeRates.hpp,v $
// Revision 1.1  2001/01/17 13:21:06  sd
// - Initial revision
//
//==============================================================================

#include "SCR_Node.hpp"
#include "SCR_FctDescr.hpp"
#include "SCR_ParserStack.hpp"
#include "SCR_Interpreter.hpp"

class EXT_Currency;

/** <b><tt>EXT_SetExchangeRates</tt></b> is the function node class for the
 *  iScript function setExchangeRates().
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EXT_SetExchangeRates.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/01/17 13:21:06 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EXT_SetExchangeRates : public SCR_VoidNode
{
  public:
    /**@name EXT_SetExchangeRates constructors and destructor */
    //@{

    // we do not need a public constructor!
    
    /** Destructor
     */
    virtual ~EXT_SetExchangeRates();

    //@}
    
    /**@name EXT_SetExchangeRates public methods */
    //@{

    /** Execute the function node
     */
    virtual void result();
    
    /** Factory for creating a new EXT_SetExchangeRates function node
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
     * @param currencyExt Pointer to the currency extension
     */
    EXT_SetExchangeRates( EXT_Currency* currencyExt );
    
    /* Add new parameters to the function node
     * @param conversionString Pointer to the conversion string parameter
     * @param factor Pointer to the factor parameter node
     */
    void addConversion( SCR_StringNode*  conversionString,
                        SCR_DecimalNode* factor );
    
  private:
    // Hide the default and copy constructor (not implemented)
    EXT_SetExchangeRates();
    EXT_SetExchangeRates( const EXT_SetExchangeRates& other );
    
    // instance members
    EXT_Currency*                        currencyExtM;
    RWTPtrOrderedVector<SCR_StringNode>  conversionsM;
    RWTPtrOrderedVector<SCR_DecimalNode> factorsM;
};

#endif // EXT_SETEXCHANGERATES_HPP
