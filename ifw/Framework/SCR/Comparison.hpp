#ifndef SCR_COMPARISON_HPP
#define SCR_COMPARISON_HPP

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
//   Comparison operation nodes for the interpreter.
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
// $RCSfile: Comparison.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:04 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Comparison.hpp,v $
// Revision 1.4  2000/08/17 11:35:39  sd
// - first version with iScript extensions
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

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
namespace SCR
{
typedef enum
{
  OPERATOR_LESS,
  OPERATOR_GREATER,
  OPERATOR_EQUAL,
  OPERATOR_NOTEQUAL,
  OPERATOR_LESSEQUAL,
  OPERATOR_GREATEREQUAL
} CompOperatorType;

typedef RWTPtrOrderedVector<Node> IPConditionList;

/**<b><tt>Compare</tt></b> is the template for all comparison nodes.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Comparison.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:04 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
template<class T>
class Compare : public  BoolNode
{
  public:

    /**@name Compare constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Compare();

    //@}

    /** Evaluate the comparison
     *  @return Result of comparison
     */
    virtual bool result();

    /** Factory for creation of less comparison
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* lessFactory( Interpreter&    interpreter,
                                  ParserStack&    stack,
                                  const FctDescr& descr );

    /** Factory for creation of greater comparison
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* greaterFactory( Interpreter&    interpreter,
                                     ParserStack&    stack,
                                     const FctDescr& descr );

    /** Factory for creation of equal comparison
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* equalFactory( Interpreter&    interpreter,
                                   ParserStack&    stack,
                                   const FctDescr& descr );

    /** Factory for creation of not equal comparison
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* notequalFactory( Interpreter&    interpreter,
                                      ParserStack&    stack,
                                      const FctDescr& descr );

    /** Factory for creation of less or equal comparison
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* lessEqualFactory( Interpreter&    interpreter,
                                       ParserStack&    stack,
                                       const FctDescr& descr );

    /** Factory for creation of greater or equal comparison
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* greaterEqualFactory( Interpreter&    interpreter,
                                          ParserStack&    stack,
                                          const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param left Left side of comparison
     *  @param right Right side of comparison
     *  @param op Compare operator
     */
    Compare( T* left,
                 T* right,
                 CompOperatorType op );
    
    // instance members
    T*               leftM;
    T*               rightM;
    CompOperatorType compareOperatorM;
};
}
#ifdef INC_TEMPL_DEFS
#include "SCR/Comparison.cpp"
#endif

#endif // COMPARISON_HPP
