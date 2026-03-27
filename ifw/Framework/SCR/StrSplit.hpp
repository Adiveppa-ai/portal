#ifndef SCR_STRSPLIT_HPP
#define SCR_STRSPLIT_HPP
/* @(#)%Portal Version: StrSplit.hpp:PlatformR2Int:4:2006-Jul-16 15:25:27 % */
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
//   Declaration of an iScript function node for the splitting a string into an
//   array of strings 
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
// $RCSfile: StrSplit.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:04:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StrSplit.hpp,v $
// Revision 1.1  2001/11/12 16:01:18  cdiab
// PETS #41530 : create an iScript function strSplit(array, string, separator)
//
// Revision 1.0  2001/11/08 12:14:03  cdiab
// - Creation
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

/** <b><tt>StrSplit</tt></b> is the iScript function node for the 
 * splitting a string into an array of strings.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StrSplit.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrSplit : public LongNode
{
  public:
    /**@name StrSplit constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrSplit();

    //@}


    /**@name StrSplit public methods */
    //@{

    /** Splits a string into an array of strings.
     *  @return The number of elements in the resulting array
     */
    virtual int64 result();

    /** Create a StrSplit() function node
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
     * @param arrayNode node containing the Array to fill
     * @param stringNode node containing the String to split
     * @param separator the character to use as String separator
     */
    StrSplit(	ArrayNode*  arrayNode,
    			StringNode* stringNode,
    			StringNode*	separator);

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    StrSplit( const StrSplit& other );
    const StrSplit& operator=( const StrSplit& other );

    // instance members
    BAS::OnlyPointer<ArrayNode>  arrayNodeM;
    BAS::OnlyPointer<StringNode> stringNodeM;
    BAS::OnlyPointer<StringNode> separatorM;
    int64	    resultM;
};
}
#endif // STRSPLIT_HPP
