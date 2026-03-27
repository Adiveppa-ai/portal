#ifndef SCR_STRPAD_HPP
#define SCR_STRPAD_HPP

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
//   Declaration of an iScript function node for the padding (and eventually
//   trunking) of a string to a specific length.
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
// $RCSfile: StrPad.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:04:02 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StrPad.hpp,v $
// Revision 1.0  2002/07/19 12:14:03  cdiab
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

/** <b><tt>StrPad</tt></b> is the iScript function node for the padding
 * (and eventually trunking) of a string to a specific length.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StrPad.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:04:02 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrPad : public StringNode
{
  public:
    /**@name StrPad constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrPad();

    //@}

    /**@name StrPad public methods */
    //@{

    /** padds the given string to the required length.
     *  @return The padded string
     */
    virtual const BAS::String& result();

    /** Create a StrPad() function node
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

    /** Constructor
     *  @param baseStringNode the source string
     *  @param padCharNode the character to be used for padding
     *  @param lenNode the desired length of the result string
     *  @param isLeftJustifiedNode a flag to indicate it is to de Left justified
     */
    StrPad( StringNode* baseStringNode,
                StringNode* padCharNode,
                LongNode*   lenNode,
                BoolNode*   isLeftJustifiedNode );

  private:

    // Hide the copy constructor and assignment operator (not implemented)
    StrPad( const StrPad& other );
    const StrPad& operator=( const StrPad& other );

    // instance members
    StringNode* baseStringNodeM;
    StringNode* padCharNodeM;
    LongNode*   lenNodeM;
    BoolNode*   isLeftJustifiedNodeM;
    BAS::String      resultM;
};
}
#endif // STRPAD_HPP
