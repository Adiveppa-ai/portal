#ifndef SCR_DATEADD_HPP
#define SCR_DATEADD_HPP

//==============================================================================
//
// Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//               This material is the confidential property of
//       Oracle Corporation or its subsidiaries or licensors
//    and may be used, reproduced, stored or transmitted only in accordance
//            with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class DateAdd
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
// $RCSfile: DateAdd.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DateAdd.hpp,v $
// Revision 1.1  2001/09/13 22:11:46  sd
// - PETS #39365 iScript does not allow date manipulations
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;

/** iScript function node for the function dateAdd().
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: DateAdd.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:21 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateAdd : public DateNode
{
  public:
    /**@name DateAdd constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~DateAdd();

    //@}

    /**@name DateAdd public methods */
    //@{

    /** Execute the function
     */
    virtual const BAS::DateTime& result();

    /** Create a dateAdd() function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> to function node on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:
    /* Constructor
     * @param sourceDateNode The source date parameter
     * @param yearNode The years parameter
     * @param monthNode The months to add
     * @param dayNode The days to add
     * @param hourNode The hours to add
     * @param minuteNode The minutes to add
     * @param secondNode The seconds to add
     */
    DateAdd( DateNode* sourceDateNode,
                 LongNode* yearNode,
                 LongNode* monthNode,
                 LongNode* dayNode,
                 LongNode* hourNode,
                 LongNode* minuteNode,
                 LongNode* secondNode );

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    DateAdd( const DateAdd& other );
    const DateAdd& operator=( const DateAdd& other );

    // instance members
    DateNode* sourceDateNodeM;
    LongNode* yearNodeM;
    LongNode* monthNodeM;
    LongNode* dayNodeM;
    LongNode* hourNodeM;
    LongNode* minuteNodeM;
    LongNode* secondNodeM;
    BAS::DateTime  resultM;
};
}
#endif // DATEADD_HPP
