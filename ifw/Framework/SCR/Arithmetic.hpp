#ifndef SCR_ARITHMETIC_HPP
#define SCR_ARITHMETIC_HPP 
/* @(#)%Portal Version: Arithmetic.hpp:PlatformR2Int:2:2006-Jul-16 15:28:50 % */
//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
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
// $RCSfile: Arithmetic.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:00:35 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Arithmetic.hpp,v $
// Revision 1.6  2000/10/06 08:23:31  sd
// - line number directive added.
// - Memory leaks in StringAdd removed
// - Constant variable map in MainExtension will be freed now
//
// Revision 1.5  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.4  2000/06/07 12:43:57  sd
// - Modulo operator for Long values added.
//
// Revision 1.3  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.2  2000/03/10 08:20:12  sd
// Changed the interface for the factory functions.
//
// Revision 1.1  2000/03/06 14:32:49  sd
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

/**<b><tt>LongArithmetic</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongArithmetic : public LongNode
{
  public:

    /**@name LongArithmetic constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongArithmetic();
    
    //@}

  protected:

    /** Constructor
     *  @param left Left operand
     *  @param right Left operand
     */
    LongArithmetic( LongNode* left,
                        LongNode* right );

    // instance members
    LongNode* leftM;
    LongNode* rightM;
};

/**<b><tt>LongAdd</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongAdd : public LongArithmetic
{
  public:

    /**@name LongAdd public methods */
    //@{

    /** Get the result
     *  @return The result
     */
    virtual int64 result();

    /** Create a longAdd() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    LongAdd( LongNode* left,
                 LongNode* right );
};

/**<b><tt>LongSub</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongSub : public LongArithmetic
{
  public:

    /**@name LongSub public methods */
    //@{

    /** Get the result
     *  @return The result
     */
    virtual int64 result();


    /** Create a longSub() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    LongSub( LongNode* left,
                 LongNode* right );

};

/**<b><tt>LongMul</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongMul : public LongArithmetic
{
  public:

    /**@name LongMul public methods */
    //@{

    /** Get the result
     *  @return The result
     */
    virtual int64 result();


    /** Create a longMul() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    LongMul( LongNode* left,
                 LongNode* right );
};

/**<b><tt>LongDiv</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongDiv : public LongArithmetic
{
  public:

    /**@name LongDiv public methods */
    //@{

    /** Get the result
     *  @return The result
     */
    virtual int64 result();


    /** Create a longDiv() function 
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
     *  @param interpreter Interpreter for the statement
     *  @param left Left operand
     *  @param right Left operand
     */
    LongDiv( Interpreter* interpreter,
                 LongNode*    left,
                 LongNode*    right );

    // instance members
    Interpreter* interpreterM;
};

/**<b><tt>LongMod</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongMod : public LongArithmetic
{
  public:

    /**@name LongMod public methods */
    //@{

    /** Get the result
     *  @return The result
     */
    virtual int64 result();


    /** Create a longMod() function 
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
     *  @param interpreter Interpreter for the statement
     *  @param left Left operand
     *  @param right Left operand
     */
    LongMod( Interpreter* interpreter,
                 LongNode*    left,
                 LongNode*    right );

    // instance members
    Interpreter* interpreterM;
};

/**<b><tt>DecimalArithmetic</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalArithmetic : public DecimalNode
{
  public:

    /**@name DecimalArithmetic constructors and destructor */
    //@{

    /** Constructor
     *  @param left Left operand
     *  @param right Left operand
     */
    DecimalArithmetic( DecimalNode* left,
                             DecimalNode* right );

    /** Destructor
     */
    ~DecimalArithmetic();

    //@}
    
  protected:

    DecimalNode*     leftM;
    DecimalNode*     rightM;
    BAS::Decimal            resultM;
};

/**<b><tt>DecimalAdd</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalAdd : public DecimalArithmetic
{
  public:

    /**@name DecimalArithmetic public methods */
    //@{

    /** Calculate the result
     *  @return The result
     */
    virtual const BAS::Decimal& result();

    /** Create a decimalAdd() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    DecimalAdd( DecimalNode* left,
                    DecimalNode* right );
};

/**<b><tt>DecimalSub</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalSub : public DecimalArithmetic
{
  public:

    /**@name DecimalArithmetic public methods */
    //@{

    /** Calculate the result
     *  @return The result
     */
    virtual const BAS::Decimal& result();

    /** Create a decimalSub() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    DecimalSub( DecimalNode* left,
                    DecimalNode* right );
};

/**<b><tt>DecimalMul</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalMul : public DecimalArithmetic
{
  public:

    /**@name DecimalArithmetic public methods */
    //@{

    /** Calculate the result
     *  @return The result
     */
    virtual const BAS::Decimal& result();

    /** Create a decimalMul() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    DecimalMul( DecimalNode* left,
                    DecimalNode* right );
};

/**<b><tt>DecimalDiv</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalDiv : public DecimalArithmetic
{
  public:

    /**@name DecimalArithmetic public methods */
    //@{

    /** Calculate the result
     *  @return The result
     */
    virtual const BAS::Decimal& result();

    /** Create a decimalDiv() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    DecimalDiv( Interpreter*   interpreter,
                      DecimalNode* left,
                      DecimalNode* right );

    // instance members
    Interpreter* interpreterM;
};

/**<b><tt>StringArithmetic</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringArithmetic : public StringNode
{
  public:

    /**@name StringArithmetic constructors and destructor */
    //@{

    /** Constructor
     *  @param left Left operand
     *  @param right Left operand
     *  @param op Arithmetic operation
     */
    StringArithmetic( StringNode* left,
                          StringNode* right );

    /** Destructor
     */
    ~StringArithmetic();

    //@}
    

  protected:
    StringNode*      leftM;
    StringNode*      rightM;
    BAS::String           resultM;
};

/**<b><tt>StringAdd</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringAdd : public StringArithmetic
{
  public:

    /**@name StringAdd public methods */
    //@{

    /** Calculate the result
     *  @return The result
     */
    virtual const BAS::String& result();

    /** Create a stringAdd() function 
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
     *  @param left Left operand
     *  @param right Left operand
     */
    StringAdd( StringNode* left,
                   StringNode* right );
    
};

/**<b><tt>LongNegation</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongNegation : public LongNode
{
  public:

    /**@name LongNegation constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongNegation();

    //@}

    /**@name LongNegation public methods */
    //@{

    /** Calculate the result
     *  @return The result
     */
    int64 result();

    /** Create a long negation function 
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
     *  @param node Node to negate
     */
    LongNegation( LongNode* node );

    // instance members
    LongNode* nodeM;
};

/**<b><tt>DecimalNegation</tt></b> 
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Arithmetic.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:35 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalNegation : public DecimalNode
{
  public:

    /**@name DecimalNegation constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DecimalNegation();

    //@}

    /**@name DecimalNegation public methods */
    //@{

    /** Calculate the result
     *  @return The result
     */
    virtual const BAS::Decimal& result();

    /** Create a decimal negation function 
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
     *  @param node Node to negate
     */
    DecimalNegation( DecimalNode* node );

    // instance members
    DecimalNode* nodeM;
    BAS::Decimal      resultM;
};
}

#endif // ARITHMETIC_HPP
