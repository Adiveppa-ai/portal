#ifndef SCR_ASSIGNMENT_HPP
#define SCR_ASSIGNMENT_HPP

//==========================================================================
//
//  @(#) %full_filespec: Assignment.hpp~20:csrc:1 %
//
// Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//
//	This material is the confidential property of Oracle Corporation.
//	or its subsidiaries or licensors and may be used, reproduced,
//	stored or transmitted only in accordance with a valid Oracle
//	license or sublicense agreement.
//
//==========================================================================


//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   The interpreter's assignment functions.
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
// $RCSfile: Assignment.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:00:53 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.7  2004/18/08 ammon
// PRSF00136596: Add PPoid support.
//
// Revision 1.6  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.5  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.4  2000/04/17 07:38:00  sd
// - BugFix in function getIdentifier()
// - Assignment for bool values added.
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
#ifndef SCR_DATA_HPP
  #include "SCR/Data.hpp"
#endif
#ifndef SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
namespace SCR 
{
/**<b><tt>LongAssignment</tt></b> is the assignment statement for long
 * values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Assignment.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:53 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongAssignment : public LongNode
{
  public:

    /**@name LongAssignment constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongAssignment();

    //@}

    /**@name LongAssignment public methods */
    //@{

    /** Execute the assignment
     *  @return left side value
     */
    virtual int64 result();

    /** Create the assignement
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:
    /** Constructor
     *  @param leftData Value to assign to
     *  @param rightData Value to assign
     */
    LongAssignment( LongDataNode* leftData,
                        LongNode*     rightData );

    LongDataNode* leftDataM;
    LongNode*     rightDataM;
};

/**<b><tt>AdtAssignment</tt></b> is the assignment statement for adt
 * values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Assignment.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:53 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class AdtAssignment : public AdtNode
{
  public:

    /**@name AdtAssignment constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~AdtAssignment();

    //@}

    /**@name AdtAssignment public methods */
    //@{

    /** Execute the assignment
     *  @return left side value
     */
    virtual int64 result();

    /** Create the assignement
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    /** Return the ADT subtype string
     *  @return <b>BAS::String&</b>
     */
    const BAS::String& subType() const;
    //@}

  private:
    /** Constructor
     *  @param leftData Value to assign to
     *  @param rightData Value to assign
     */
    AdtAssignment( AdtDataNode* leftData,
                        AdtNode*     rightData );

    AdtDataNode*		leftDataM;
    AdtNode*     		rightDataM;
    static const BAS::String	subTypeCM;
};


/**<b><tt>DecimalAssignment</tt></b> is the assignment statement for 
 * decimal values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Assignment.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:53 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalAssignment : public DecimalNode
{
  public:

    /**@name DecimalAssignment constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DecimalAssignment();

    //@}

    /**@name DecimalAssignment public methods */
    //@{

    /** Execute the assignment
     *  @return left side value
     */
    virtual const BAS::Decimal& result();

    /** Create the assignement
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Constructor
     *  @param leftData Value to assign to
     *  @param rightData Value to assign
     */
    DecimalAssignment( DecimalDataNode* leftData,
                           DecimalNode*     rightData );

    // instance members
    DecimalDataNode* leftDataM;
    DecimalNode*     rightDataM;
};

/**<b><tt>StringAssignment</tt></b> is the assignment statement for 
 * string values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Assignment.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:53 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringAssignment : public StringNode
{
  public:

    /**@name StringAssignment constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StringAssignment();

    //@}

    /**@name StringAssignment public methods */
    //@{

    /** Execute the assignment
     *  @return left side value
     */
    virtual const BAS::String& result();

    /** Create the assignement
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );


    //@}

  private:

    /** Constructor
     *  @param leftData Value to assign to
     *  @param rightData Value to assign
     */
    StringAssignment( StringDataNode* leftData,
                          StringNode*     rightData );

    // instance members
    StringDataNode* leftDataM;
    StringNode*     rightDataM;
};

/**<b><tt>DateAssignment</tt></b> is the assignment statement for 
 * date values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Assignment.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:53 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateAssignment : public DateNode
{
  public:

    /**@name DateAssignment constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DateAssignment();

    //@}

    /**@name DateAssignment public methods */
    //@{

    /** Execute the assignment
     *  @return left side value
     */
    virtual const BAS::DateTime& result();
    
    /** Create the assignement
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:
    /** Constructor
     *  @param leftData Value to assign to
     *  @param rightData Value to assign
     */
    DateAssignment( DateDataNode* leftData,
                        DateNode*     rightData );

    // instance members
    DateDataNode* leftDataM;
    DateNode*     rightDataM;
};

/**<b><tt>BoolAssignment</tt></b> is the assignment statement for 
 * bool values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Assignment.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Bool: 2000/03/16 10:15:56 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolAssignment : public BoolNode
{
  public:

    /**@name BoolAssignment constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~BoolAssignment();

    //@}

    /**@name BoolAssignment public methods */
    //@{

    /** Execute the assignment
     *  @return left side value
     */
    virtual bool result();
    
    /** Create the assignement
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  private:

    /** Constructor
     *  @param leftData Value to assign to
     *  @param rightData Value to assign
     */
    BoolAssignment( BoolDataNode* leftData,
                        BoolNode*     rightData );

    // instance members
    BoolDataNode* leftDataM;
    BoolNode*     rightDataM;
};

/**<b><tt>PPoidAssignment</tt></b> is the assignment statement for
 * PPoid values.
 */
class PPoidAssignment : public PPoidNode
{
  public:

    /**@name PPoidAssignment constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~PPoidAssignment();

    //@}

    /**@name PPoidAssignment public methods */
    //@{

    /** Execute the assignment
     *  @return left side value
     */
    virtual const BAS::Identifier& result();

    /** Create the assignement
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                          ParserStack&    stack,
                          const FctDescr& descr );

    //@}

  private:
    /** Constructor
     *  @param leftData Value to assign to
     *  @param rightData Value to assign
     */
    PPoidAssignment( PPoidDataNode* leftData,
                     PPoidNode*     rightData );

    // instance members
    PPoidDataNode* leftDataM;
    PPoidNode*     rightDataM;
};
}
#endif // ASSIGNMENT_HPP
