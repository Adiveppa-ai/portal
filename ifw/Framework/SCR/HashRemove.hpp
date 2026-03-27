#ifndef SCR_HASHREMOVE_HPP
#define SCR_HASHREMOVE_HPP

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
//   Definition of the class HashRemove.
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
// $RCSfile: HashRemove.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:21 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: HashRemove.hpp,v $
// Revision 1.1  2001/09/25 11:30:02  sd
// - PETS #39831 Missing iScript function hashRemove()
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

/** <b><tt>HashRemove</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashRemove.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:21 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashRemove : public BoolNode
{
  public:
    /**@name HashRemove constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~HashRemove();

    //@}


    /**@name HashRemove public methods */
    //@{

    /** Try to remove the hash element
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create the function node
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
     *  @param hashNode Node for accessing the hash to clear
     *  @param keyNode The key to check
     */
    HashRemove( HashNode*   hashNode,
                    StringNode* keyNode );

  private:

    // Hide default and copy constructor
    HashRemove();
    HashRemove( const HashRemove& other );
    const HashRemove& operator=( const HashRemove& other );

    // Instance members
    HashNode*   hashNodeM;
    StringNode* keyNodeM;
};
}
#endif // HASHREMOVE_HPP
