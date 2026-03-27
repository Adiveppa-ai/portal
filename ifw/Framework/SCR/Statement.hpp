#ifndef SCR_STATEMENT_HPP
#define SCR_STATEMENT_HPP 

//==============================================================================
//
// 1998,1999 (c) Copyright by solution42 - IT systems & consulting GmbH & Co. KG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Definiton of the base class for all interpreter statements.
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
// $RCSfile: Statement.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:03:58 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Statement.hpp,v $
// Revision 1.10  2001/09/16 21:11:59  sd
// - PETS #37618 Compiler warnings removed
//
// Revision 1.9  2001/04/10 10:50:35  sd
// - Full function support (inclusive return values)
//
// Revision 1.8  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.7  2000/08/17 11:35:40  sd
// - first version with iScript extensions
//
// Revision 1.6  2000/06/16 15:03:29  sd
// - Implementation changed to support the IBM AIX xlC compiler.
//
// Revision 1.5  2000/04/27 11:52:01  sd
// - for loop added to iScript.
//
// Revision 1.4  2000/03/15 08:26:57  sd
// - New files ParserFunctions.?pp added.
//
// Revision 1.3  2000/03/14 14:34:34  sd
// - BAS::Trace.hpp added to include files.
//
// Revision 1.2  2000/03/14 13:04:36  sd
// - Basic function support added.
// - At startup the function BEGIN and at destuction the function END is
//   called automatically.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// - Initial revision.
//
//==============================================================================

#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_DATA_HPP
  #include "SCR/Data.hpp"
#endif
#ifndef SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
namespace SCR
{

/**<b><tt>StatementList</tt></b> is the statement class for a block.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Statement.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:58 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StatementList : public Node
{
  public:

    /**@name StatementList constructors and destructor */
    //@{

    /** Constructor
     */
    StatementList();

    /** Destructor
     */
    virtual ~StatementList();

    //@}

    /**@name StatementList public methods */
    //@{

    /** Execute the statement
     *  @return The result of the execution
     */
    virtual int execute();

    /** Add a new statement to list
     *  @param statement The statement to add to list
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addStatement( Node* statement );

    /** Add a new identifier to the statement list
     *  @param identifier Identifier of this value
     *  @param value Variable to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addIdentifier( const BAS::String& identifier,
                                Variable*   value );

    /** Get an identifer from the statement list´s identifiers
     *  @param identifier The identifier to get
     */
    virtual Variable* getIdentifier( const BAS::String& identifier );

    /** Check whether the statement list returns a result or not. This function
     *  is used by the interpreter to analyze the code of functions to check if
     *  they always return a result.
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    //@}

  protected:
    RWTPtrOrderedVector<Node> statementsM;
    VariableMap               identifiersM;
};

/**<b><tt>WhileStatement</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Statement.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:58 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class WhileStatement : public Node
{
  public:

    /**@name WhileStatement constructors and destructor */
    //@{

    /** Constructor
     *  @param condition The condition for the while loop
     */
    WhileStatement( BoolNode* condition );

    /** Destructor
     */
    virtual ~WhileStatement();

    //@}

    /**@name WhileStatement public methods */
    //@{

    /** Execute the statement
     */
    virtual int execute();

    /** Add the statement to the while loop
     *  @param statement The statement to add to list
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addStatement( Node* statement );


    /** Check whether the while statement returns a result or not. This function
     *  is used by the interpreter to analyze the code of functions to check if
     *  they always return a result.
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    //@}

  protected:
    // Instance members
    BoolNode*  conditionM;
    Node*      statementM;
};

/**<b><tt>DoStatement</tt></b> is the iScript statement for the
 * do-while loop.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Statement.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:58 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DoStatement : public Node
{
  public:

    /**@name DoStatement constructors and destructor */
    //@{

    /** Constructor
     *  @param condition The condition for the while loop
     */
    DoStatement();

    /** Destructor
     */
    virtual ~DoStatement();

    //@}

    /**@name DoStatement public methods */
    //@{

    /** Execute the statement
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual int execute();

    /** Add the statement to the do loop
     *  @param statement The statement to add to list
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addStatement( Node* statement );

    /** Check whether the do-while statement returns a result or not. This
     *  function is used by the interpreter to analyze the code of functions
     *  to check if they always return a result.
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    /** Set the condition for the do statement
     *  @param condition The condition for the do statement
     */
    void condition( BoolNode* condition );

    //@}

  protected:
    // Instance members
    BoolNode* conditionM;
    Node*     statementM;
};

/**<b><tt>IFStatement</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Statement.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:58 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class IfStatement : public Node
{
  public:

    /**@name IfStatement constructors and destructor */
    //@{

    /** Constructor
     */
    IfStatement( BoolNode* condition );

    /** Destructor
     */
    virtual ~IfStatement();

    //@}

    /**@name IfStatement public methods */
    //@{

    /** Execute the statement
     */
    virtual int execute();

    /** Add a new statement to the if statement
     *  @param statement The statement to add to list
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addStatement( Node* statement );

    /** Check whether the if statement returns a result or not. This
     *  function is used by the interpreter to analyze the code of functions
     *  to check if they always return a result.
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    //@}

  protected:
    BoolNode*  conditionM;
    Node* ifStatementM;
    Node* elseStatementM;
};

/**<b><tt>ForLoop</tt></b> is the iScript statement for the
 * for-loop.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Statement.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:58 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ForLoop : public Node
{
  public:

    /**@name ForLoop constructors and destructor */
    //@{

    /** Constructor
     *  @param condition The condition for the while loop
     */
    ForLoop();

    /** Destructor
     */
    virtual ~ForLoop();

    //@}

    /**@name ForLoop public methods */
    //@{

    /** Execute the for loop
     */
    virtual int execute();

    /** Add the statement to the for loop
     *  @param statement The statement to add to list
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addStatement( Node* statement );

    /** Add the condition to the for loop
     *  @param condition The condition node to add
     */
    void condition( BoolNode* condNode );

    /** Check whether the for-loop returns a result or not. This
     *  function is used by the interpreter to analyze the code of functions
     *  to check if they always return a result.
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    //@}

  protected:
    // Instance members
    Node*      startStatementM;
    BoolNode*  conditionM;
    Node*      stepStatementM;
    Node*      loopStatementM;
};
}
#endif // STATEMENT_HPP
