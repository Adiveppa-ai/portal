#ifndef SCR_SWITCHCASE_HPP
#define SCR_SWITCHCASE_HPP

//==============================================================================
//
// Copyright (c) 1995, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//
//	This material is the confidential property of Oracle Corporation.
//	or its subsidiaries or licensors and may be used, reproduced,
//	stored or transmitted only in accordance with a valid Oracle
//	license or sublicense agreement
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the iScript switch-case statement classes.
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
// $RCSfile: SwitchCase.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:04:20 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: SwitchCase.hpp,v $
// Revision 1.8  2001/04/10 10:50:35  sd
// - Full function support (inclusive return values)
//
// Revision 1.7  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.6  2000/11/02 11:37:12  sd
// - New regExprSwitch(), a switch/case for regular expressions.
//
// Revision 1.5  2000/10/12 15:24:33  sd
// - Implicit break removed again.
//
// Revision 1.3  2000/10/12 08:48:18  sd
// - Error messages improved.
//
// Revision 1.2  2000/10/12 07:38:09  sd
// - Compilation errors under HPUX removed.
//
// Revision 1.1  2000/10/12 07:24:25  sd
// - Initial revision.
//
//==============================================================================

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef FSM_ENGINE_HPP
  #include "FSM/Engine.hpp"
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class ParserStack;

/** <b><tt>SwitchCase</tt></b> is the baseclass for all switch-case
 *  statements used in iScript.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SwitchCase.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:20 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class SwitchCase : public Node
{
  public:
    /**@name SwitchCase constructors and destructor */
    //@{

    /** Constructor
     *  @param switchNode The switch criterion
     */
    SwitchCase();
    
    /** Destructor
     */
    ~SwitchCase();

    //@}

    /**@name SwitchCase public methods */
    //@{

    /** Add the statement to the switch-case
     *  @param statement The statement to add to list
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addStatement( Node* statement );

    /** Add a new case to the switch-case statement
     *  @param stack The compiler's datastack
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool nextCase( ParserStack& stack) = 0;

    /** Add a default to the switch-case statement
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addDefault();

    /** Add a break to the switch-case statement
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addBreak();

    //@}
    
  protected:

    // Internal states used for adding statements and case-labels
    typedef enum
    {
      INITIAL_STATE,
      CASE_STATE,
      STATEMENT_STATE
    } CreateStateT;

    // instance members
    CreateStateT                  createStateM;
    Node*                     curStatementM;
    Node*                     defaultStatementM;
    RWTPtrOrderedVector<Node> statementsToDeleteM;

  private:
    // Hide copy constructor etc.
    SwitchCase( const SwitchCase& other );
    const SwitchCase& operator=( const SwitchCase& other );
};

/** <b><tt>LongSwitchCase</tt></b> is the iScript switch case statement
 *  for long values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SwitchCase.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:20 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongSwitchCase : public SwitchCase
{
  public:
    /**@name LongSwitchCase constructors and destructor */
    //@{

    /** Constructor
     *  @param switchNode The switch criterion
     */
    LongSwitchCase( LongNode* switchNode );
    
    /** Destructor
     */
    ~LongSwitchCase();

    //@}


    /**@name LongSwitchCase public methods */
    //@{

    /** Execute the statement
     */
    virtual int execute();

    /** Add a new case to the switch-case statement
     *  @param stack The compiler's datastack
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool nextCase( ParserStack& stack);

    /** Check whether the switch-case statement always returns a result or not
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    //@}

  private:
    
    // hide default and copy constructor
    LongSwitchCase();
    LongSwitchCase( const LongSwitchCase& other );
    const LongSwitchCase& operator=( const LongSwitchCase& other );

    // instance members
    LongNode*                         switchNodeM;
    RWTValMap<int64,Node*,less<int64> > caseMapM;
};

/** <b><tt>StringSwitchCase</tt></b> is the iScript switch case statement
 *  for string values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SwitchCase.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:20 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringSwitchCase : public SwitchCase
{
  public:
    /**@name StringSwitchCase constructors and destructor */
    //@{

    /** Constructor
     *  @param switchNode The switch criterion
     */
    StringSwitchCase( StringNode* switchNode );
    
    /** Destructor
     */
    ~StringSwitchCase();

    //@}


    /**@name StringSwitchCase public methods */
    //@{

    /** Execute the statement
     */
    virtual int execute();

    /** Add a new case to the switch-case statement
     *  @param stack The compiler's datastack
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool nextCase( ParserStack& stack);

    /** Check whether the switch-case statement always returns a result or not
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    //@}

  private:
    
    // hide default and copy constructor
    StringSwitchCase();
    StringSwitchCase( const StringSwitchCase& other );
    const StringSwitchCase& operator=( const StringSwitchCase& other );

    // instance members
    StringNode*                                   switchNodeM;
    RWTValMap<BAS::String,Node*,less<BAS::String> > caseMapM;
};

/** <b><tt>RegExprSwitchCase</tt></b> is the iScript switch case statement
 *  for regular expressions.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SwitchCase.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:20 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class RegExprSwitchCase : public SwitchCase
{
  public:
    /**@name RegExprSwitchCase constructors and destructor */
    //@{

    /** Constructor
     *  @param switchNode The switch criterion
     */
    RegExprSwitchCase( StringNode* switchNode );
    
    /** Destructor
     */
    ~RegExprSwitchCase();

    //@}


    /**@name RegExprSwitchCase public methods */
    //@{

    /** Execute the statement
     */
    virtual int execute();

    /** Add a new case to the switch-case statement
     *  @param stack The compiler's datastack
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool nextCase( ParserStack& stack);

    /** Do the final setup for the finite state machine 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool finalSetup();

    /** Check whether the switch-case statement always returns a result or not
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    //@}

  private:
    
    // hide default and copy constructor
    RegExprSwitchCase();
    RegExprSwitchCase( const RegExprSwitchCase& other );
    const RegExprSwitchCase& operator=( const RegExprSwitchCase& other );

    // instance members
    StringNode*               switchNodeM;
    FSM::Engine                    fsmM;
    RWTPtrOrderedVector<Node> statementsM;
};
}

#endif // SWITCHCASE_HPP
