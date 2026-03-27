#ifndef SCR_HASHFUNCTIONS_HPP
#define SCR_HASHFUNCTIONS_HPP
/* @(#)%Portal Version: HashFunctions.hpp:PlatformR2Int:2:2006-Jul-16 15:27:13 % */
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
//   Definition of some function nodes for accessing and changing hashes.
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
// $RCSfile: HashFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:17 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: HashFunctions.hpp,v $
// Revision 1.3  2001/04/10 15:05:12  sd
// - New function hashKeys() to retrieve the key values of a hash
//
// Revision 1.2  2000/10/09 10:16:43  sd
// - New function hashContains() added
//
// Revision 1.1  2000/10/09 10:00:47  sd
// - Initial revision
//
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_FCTDESCR_HPP
  #include "SCR/FctDescr.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
#ifndef SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif
namespace SCR
{

/** <b><tt>HashClear</tt></b> is the function node for clearing hashes.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashClear : public VoidNode
{
  public:
    /**@name HashClear constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~HashClear();

    //@}


    /**@name HashClear public methods */
    //@{

    /** Clear the hash
     */
    virtual void result();

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
     */
    HashClear( HashNode* hashNode );

  private:

    // Hide default and copy constructor
    HashClear();
    HashClear( const HashClear& other );
    const HashClear& operator=( const HashClear& other );

    // instance members
    HashNode* hashNodeM;
};

/** <b><tt>HashContains</tt></b> is the function node for checking if a
 *  hash contains an element.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashContains : public BoolNode
{
  public:
    /**@name HashContains constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~HashContains();

    //@}


    /**@name HashContains public methods */
    //@{

    /** Check if the hash contains the element
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
    HashContains( HashNode*   hashNode,
                      StringNode* keyNode );

  private:

    // Hide default and copy constructor
    HashContains();
    HashContains( const HashContains& other );
    const HashContains& operator=( const HashContains& other );

    // instance members
    HashNode*   hashNodeM;
    StringNode* keyNodeM;
};

/** <b><tt>HashKeys</tt></b> is the function node for getting
 *  all keys used in an associative array.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: HashFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:17 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashKeys : public LongNode
{
  public:
    /**@name HashKeys constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~HashKeys();

    //@}


    /**@name HashKeys public methods */
    //@{

    /** Get all keys from the hash
     *  @return The number of keys
     */
    virtual int64 result();

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
     *  @param keyArrayNode Node for accessing the array to fill with the keys
     */
    HashKeys( HashNode*  hashNode,
                  ArrayNode* keyArrayNode );

  private:

    // Hide default and copy constructor
    HashKeys();
    HashKeys( const HashKeys& other );
    const HashKeys& operator=( const HashKeys& other );

    // instance members
    HashNode*  hashNodeM;
    ArrayNode* keyArrayNodeM;
};
}
#endif // HASHFUNCTIONS_HPP
