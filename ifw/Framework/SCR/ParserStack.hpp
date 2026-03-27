#ifndef SCR_PARSERSTACK_HPP
#define SCR_PARSERSTACK_HPP

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
//   Stack for the parser.
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
// $RCSfile: ParserStack.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:03:33 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ParserStack.hpp,v $
// Revision 1.10  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.9  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.8  2000/08/17 11:35:40  sd
// - first version with iScript extensions
//
// Revision 1.7  2000/03/14 14:32:38  sd
// Return type for operator=() added to avoid warnings under HPUX.
//
// Revision 1.6  2000/03/13 12:38:53  sd
// Function edrAddDataBlock() added to descriptions.
//
// Revision 1.5  2000/03/10 12:22:13  sd
// - stringDecode() function added.
// - number of arguments check modified.
// - unlimited number of arguments supported.
//
// Revision 1.4  2000/03/08 08:18:27  sd
// Doc++ comments added.
// Function pushType() removed.
// Copy constructor and assignment operator declared private.
//
// Revision 1.3  2000/03/07 17:00:34  sd
// Left hand value flag for datatypes introduced.
// Comments (C and C++ style) added to Lexer.
//
// Revision 1.2  2000/03/06 16:48:16  sd
// Implementation changed to support the SUN CC compiler.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// Initial revision.
//
//==============================================================================

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_FCTDESCR_HPP
  #include "SCR/FctDescr.hpp"
#endif

namespace SCR
{
/**<b><tt>ParserStack</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ParserStack.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:33 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ParserStack D_THREADINFO
{
  public:
    /**@name ParserStack constructor and destructor */
    //@{

    /** Constrcutor
     */
    ParserStack();

    /** Destructor 
     */
    virtual ~ParserStack();

    //@}

    /**@name ParserStack public methods */
    //@{

    /** Clear the entire stack
     */
    void clear();

    /** Push a new data node on the stack
     *  @param node The data node
     *  @param type The type of the data node
     */
    void pushData( Node* node, int type );

    /** Pop the top data node from stack.
     *  @return Pointer to top data node, 0 on stack underflow
     */
    Node* popData();

    /** Push a value on the number of parameters stack
     *  @param params Number of parameters
     */
    void pushNumParams( int params );

    /** Pop the top value from number of parameters stack
     *  @return The number of parameters on the stack
     */
    int popNumParams();

    /** Get the top value on number of parameters stack without changing the
     *  stack
     *  @return The top stack value
     */
    int topNumParams();

    /** Increase the top value on number of parameters stack
     *  @return The decreased top value
     */
    int incTopNumParams();

    /** Push a function description on the function stack
     *  @param descr The function description
     */
    void pushFunction( const FctDescr* descr);

    /** Pop the top function description from function stack
     *  @return Function description pointer
     */
    FctDescr* popFunction();

    /** Get the top function description on stack (without changing stack)
     *  @return Function description pointer
     */
    FctDescr* topFunction() const;

    /** Get the size of the function stack
     */
    size_t numFunctions() const;

    /** Pop the top type from type stack
     *  @return The top type on stack
     */
    int popType();

    /** Get the top type on stack without changing the stack
     *  @return The top type on stack
     */
    int topType();

	/** Get the supertype of all the types on the stack. This changes
	 * the stack so that all of the types are the same (if the promotion is 
	 * allowed)
	 * @return the super type of the stack
	 */
	int superType();

	/** Replace the data stack with the parameter passed
	 */
	void appendDataStack(RWTPtrOrderedVector<Node>& stack);

    /** Print the stack
     *  @param stream Stream for output
     */
    void print( std::ostream& stream );
      
    //@}

  private:

    // Hide copy constructor and assignment operator
    ParserStack( const ParserStack& );
    const ParserStack& operator=( const ParserStack& );

    RWTPtrOrderedVector<Node>     dataStackM;
    RWTValOrderedVector<int>          typeStackM;
    RWTPtrOrderedVector<FctDescr> functionStackM;
    RWTValOrderedVector<int>         numParamStackM;
};
}
#endif // PARSERSTACK_HPP
