#ifndef SCR_FCTCALLNODE_HPP
#define SCR_FCTCALLNODE_HPP

//==============================================================================
//
// 1998, 1999, 2000                               (c) Copyright by SOLUTION42 AG
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
//   Data node for a function description
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
// $RCSfile: FctCallNode.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:01:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: FctCallNode.hpp,v $
// Revision 1.2  2001/08/29 16:46:14  sd
// - PETS #38712 - iScript functions without parenthesis stop integRate
//
// Revision 1.1  2000/08/23 15:50:12  sd
// - Initial revision.
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
namespace SCR
{

class FctDescr;

/** <b><tt>FctCallNode</tt></b> is used to push function descriptions on
 *  the data stack.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FctCallNode.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:01:48 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FctCallNode : public Node
{
  public:
    /**@name FctCallNode constructors and destructor */
    //@{

    /** Constructor
     */
    FctCallNode( const FctDescr* descr );

    /** Destructor
     */
    ~FctCallNode();
    
    //@}

    /**@name FctCallNode public methods */
    //@{

    /** Get the function description
     */
    const FctDescr* fctDescr() const;

    /** Execute the node 
     *  @return Node::EXEC_NORMAL     
     */
    virtual int execute();

    //@}

  private:
    const FctDescr* fctDescrM;
};

//==============================================================================
// Get the function description
//==============================================================================
inline const FctDescr* 
FctCallNode::fctDescr() const
{
  return fctDescrM;
}
}
#endif // FCTCALLNODE_HPP
