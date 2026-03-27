#ifndef SCR_DECIMALFUNCTIONS_HPP
#define SCR_DECIMALFUNCTIONS_HPP

//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation. or its
// subsidiaries or licensors and may be used, reproduced, stored or transmitted
// only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   The functions for decimal values.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: DecimalFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:30 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.6  2004/07/30 ammon
// PRSF00123976 Added support for other rounding types
//
// Revision 1.5  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.4  2000/04/27 12:50:34  sd
// - function longToDecimal() added.
//
// Revision 1.3  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.2  2000/03/10 08:20:12  sd
// Changed the interface for the factory functions.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// Initial revision.
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
namespace SCR
{

class Interpreter;

/**<b><tt>DecimalAbs</tt></b> implements the abs() function for 
 * decimal values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DecimalFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:30 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalAbs : public DecimalNode
{
  public:
    /**@name DecimalAbs constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DecimalAbs();

    //@}

    /**@name DecimalAbs public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::Decimal& result();

    /** Create a decimalAbs function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:
    /** Constructor
     *  @param value Decimal node as input parameter
     */
    DecimalAbs( DecimalNode* value );

    // instance members
    DecimalNode* valueM;
    BAS::Decimal        resultM;
};

/**<b><tt>StrToDecimal</tt></b> implements the strToDecimal() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DecimalFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:30 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrToDecimal : public DecimalNode
{
  public:
    /**@name StrToDecimal constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrToDecimal();

    //@}

    /**@name StrToDecimal public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::Decimal& result();

    /** Create a strToDecimal() function on datastack
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     *  @param string Value to convert
     */
    StrToDecimal( StringNode* string );

    // instance members
    StringNode* stringM;
    BAS::Decimal       resultM;
};

/**<b><tt>Round</tt></b> implements the round() function for 
 * decimal values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DecimalFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:30 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Round : public DecimalNode
{
  public:
    /**@name Round constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Round();

    //@}

    /**@name Round public methods */
    //@{

    /** Set the round method
     *  @param The rounding method
     */
    void setRoundMethod( RWDecimalBase::RoundingMethod method );

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::Decimal& result();

    /** Create a round() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    /** Create a trunc() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* truncFactory( Interpreter&    interpreter,
                                   ParserStack&    stack,
                                   const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     *  @param value Decimal node as input parameter
     *  @param places Decimal places for rounding (can be 0)
     *  @param method Rounding method (default - PLAIN, 1 - UP,
     *                2 - DOWN, 3 - BANKERS)
     */
    Round( DecimalNode* value, 
               LongNode*    places,
               LongNode*    method );

    // instance members
    DecimalNode*            valueM;
    LongNode*               placesM;
    BAS::OnlyPointer<LongNode>     methodM;
    BAS::Decimal                   resultM;
    RWDecimalBase::RoundingMethod roundingMethodM;
};

/**<b><tt>LongToDecimal</tt></b> implements the longToDecimal() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DecimalFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:30 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongToDecimal : public DecimalNode
{
  public:
    /**@name LongToDecimal constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongToDecimal();

    //@}

    /**@name LongToDecimal public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual const BAS::Decimal& result();

    /** Create a longToDecimal() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );
    
    //@}

  protected:

    /** Constructor
     *  @param longnode Value to convert
     */
    LongToDecimal( LongNode* longnode );

    // instance members
    LongNode*    longM;
    BAS::Decimal      resultM;
};
}
#endif // DECIMALFUNCTIONS_HPP
