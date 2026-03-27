#ifndef SCR_NODE_HPP
#define SCR_NODE_HPP
/* @(#)%Portal Version: Node.hpp:PlatformR2Int:2:2006-Jul-16 15:26:13 % */

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates. 
// 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Base class for all datatypes used in the interpreter.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// $RCSfile: Node.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
//------------------------------------------------------------------------------
// Revision 1.13  2004/18/08 ammon
// PRSF00136596:  Add PPoid support.
//
// Revision 1.12  2001/04/10 13:48:22  sd
// - return statement improved
//
// Revision 1.11  2001/04/10 10:50:35  sd
// - Full function support (inclusive return values)
//
// Revision 1.10  2001/04/06 11:47:08  sd
// - Backup version
//
// Revision 1.9  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.8  2000/09/29 11:24:23  sd
// - Doc++ bugs fixed
//
// Revision 1.7  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.6  2000/06/16 15:03:29  sd
// - Implementation changed to support the IBM AIX xlC compiler.
//
// Revision 1.5  2000/03/23 11:25:36  sd
// - support for file variables added.
// - new class FileVariable
//
// Revision 1.4  2000/03/10 12:22:13  sd
// - stringDecode() function added.
// - number of arguments check modified.
// - unlimited number of arguments supported.
//
// Revision 1.3  2000/03/07 17:00:34  sd
// - Left hand value flag for datatypes introduced.
// - Comments (C and C++ style) added to Lexer.
//
// Revision 1.2  2000/03/06 16:30:10  sd
// - Constants converted to enumeration.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// - Initial revision.
//
//==============================================================================

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif
#ifndef BAS_IDENTIFIER_H
  #include "BAS/Identifier.hpp"
#endif

namespace SCR
{
class Hash;
class Array;
class Variable;

/**<b><tt>Node</tt></b> is the base class for all nodes used in
 * integRate´s interpreter for processing conditions and results from the
 * generic rules.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Node D_THREADINFO
{
  public:
    
    enum
    {
      LEFT_FLAG          = 0x04000,
      CONST_FLAG         = 0x08000,

      BASE_TYPE_MASK     = ~(LEFT_FLAG | CONST_FLAG),

      UNKNOWN_TYPE       = 0,
      EDRALIAS_TYPE      = 1,

      VOID_TYPE          = 10,
      STRING_TYPE        = 11,
      BOOL_TYPE          = 12,
      DECIMAL_TYPE       = 13,
      LONG_TYPE          = 14,
      DATE_TYPE          = 15,
      FILE_TYPE          = 16,
      FCT_DESCR_TYPE     = 17,
      ARRAY_TYPE         = 18,
      HASH_TYPE          = 19,
      ADT_TYPE           = 20,
      PPOID_TYPE         = 21,

      CONST_STRING_TYPE  = STRING_TYPE  | CONST_FLAG,
      CONST_BOOL_TYPE    = BOOL_TYPE    | CONST_FLAG,
      CONST_DECIMAL_TYPE = DECIMAL_TYPE | CONST_FLAG,
      CONST_LONG_TYPE    = LONG_TYPE    | CONST_FLAG,
      CONST_ADT_TYPE     = ADT_TYPE     | CONST_FLAG,
      CONST_DATE_TYPE    = DATE_TYPE    | CONST_FLAG,
      CONST_PPOID_TYPE   = PPOID_TYPE   | CONST_FLAG,

      LEFT_STRING_TYPE   = STRING_TYPE  | LEFT_FLAG,
      LEFT_BOOL_TYPE     = BOOL_TYPE    | LEFT_FLAG,
      LEFT_DECIMAL_TYPE  = DECIMAL_TYPE | LEFT_FLAG,
      LEFT_LONG_TYPE     = LONG_TYPE    | LEFT_FLAG,
      LEFT_ADT_TYPE      = ADT_TYPE     | LEFT_FLAG,
      LEFT_DATE_TYPE     = DATE_TYPE    | LEFT_FLAG,
      LEFT_PPOID_TYPE    = PPOID_TYPE   | LEFT_FLAG
    };

    enum ExecuteResultT
    {
      EXEC_NORMAL   =  0,
      EXEC_RETURN   = -1,
      EXEC_CONTINUE = -2,
      EXEC_BREAK    = -3,
      EXEC_EXIT     = -4
    };

    /**@name Node constructors and destructor */
    //@{

    /** Constructor
     */
    Node();

    /** Destructor
     */
    virtual ~Node();

    //@}

    /**@name Node public methods */
    //@{

    /** Execute the node's function
     *  @return The result of the function execution
     */
    virtual int execute();

    /** Add a new substatement
     *  @param statement Statement to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addStatement( Node* statement );

    /** Add a new identifier to the statement list
     *  @param identifier Identifier of this value
     *  @param value Variable to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addIdentifier( const BAS::String& identifier,
                                Variable*     value );

    /** Get an identifer from the statement list´s identifiers
     *  @param identifier The identifier to get
     */
    virtual Variable* getIdentifier( const BAS::String& identifier );

	/** Perform a type promotion
	 * @param type the type to promote to
	 * @return Node* pointer to the new node with the promoted type in it
	 */
	virtual Node* promote(int type) const;

    /** Check whether the node returns a result or not. This function is used
     *  by the interpreter to analyze the code of functions to check if they
     *  always return a result.
     *  @return <b>true</b> if result is returned, <b>false</b> otherwise
     */
    virtual bool returnsResult() const;

    /** Return the datatype as string
     *  @param type Type for which to return the datatype as string
     *  @return The datatype name as string
     */
    static BAS::String datatypeAsString( int type );

    /** Return the typeid for a datatype given as string
     *  @param name The name of the datatype
     *  @return The typeid for that typename
     */
    static int typeIdForName( const BAS::String& name );

    /** Get the base type for a type value, this means remove const etc.
     *  @param type The type for which to return the basetype
     *  @return The basetype
     */
    static int baseType( int type );

    /** Check if a datatype is a left value
     *  @return <b>true</b> if left value, <b>false</b> otherwise
     */
    static bool isLeft( int type );

    /** Check if a datatype is a const value
     *  @return <b>true</b> if const value, <b>false</b> otherwise
     */
    static bool isConst( int type );

    /** Check if a datatype is an array value
     *  @return <b>true</b> if array value, <b>false</b> otherwise
     */
    static bool isArray( int type );

    /** Check if a datatype is a hash value
     *  @return <b>true</b> if hash value, <b>false</b> otherwise
     */
    static bool isHash( int type );

    /** Check if a datatype is a reference type
     *  @return <b>true</b> if reference value, <b>false</b> otherwise
     */
    static bool isReference( int type );

	/** Find the supertype (the type that both can be promoted to) of the
	 * left and right hand arguments. Returns UNKNOWN_TYPE if conversion is
	 * impossible
	 * @param lhs left hand type
	 * @param rhs right hand type
	 * @return supertype
	 */
	static int SuperType(int lhs, int rhs);


    //@}

};

/**<b><tt>LongNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongNode : public Node
{
  public:

    /**@name LongNode public methods */
    //@{

    /** Execute the long node's function
     */
    virtual int execute();

    /** Get a long value
     *  @return the value
     */
    virtual int64 result() = 0;

    //@}
};


/**<b><tt>AdtNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class AdtNode : public Node
{
  public:

    /**@name AdtNode public methods */
    //@{

    /** Execute the Adt node's function
     */
    virtual int execute();

    /** Get a Adt value
     *  @return the value
     */
    virtual int64 result() = 0;

    /** Get a AdtNode subType. 
     */
    virtual const BAS::String& subType() const = 0;
    //@}
};

/**<b><tt>DecimalNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalNode : public Node
{
  public:

    /**@name DecimalNode public methods*/
    //@{

    /** Execute the decimal node's function
     */
    virtual int execute();

    /** Get the decimal value
     *  @return The decimal value
     */
    virtual const BAS::Decimal& result() = 0;
    
    //@}
};

/**<b><tt>DateNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateNode : public Node
{
  public:

    /**@name DateNode public methods */
    //@{

    /** Execute the date node's function
     */
    virtual int execute();

    /** Get the date value
     *  @return The date value
     */
    virtual const BAS::DateTime& result() = 0;

    //@}
};

/**<b><tt>BoolNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolNode : public Node
{
  public:
    /**@name BoolNode public methods */
    //@{

    /** Execute the bool node's function
     */
    virtual int execute();

    /** Get the bool value
     *  @return The bool value
     */
    virtual bool result() = 0;

    //@}

};

/**<b><tt>StringNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringNode : public Node
{
  public:

    /**@name StringNode public methods */
    //@{

    /** Execute the string node's function
     */
    virtual int execute();

    /** Get the string value
     *  @return The string value
     */
    virtual const BAS::String& result() = 0;

    //@}
};

/**<b><tt>VoidNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class VoidNode : public Node
{
  public:

    /**@name VoidNode public methods */
    //@{

    /** Execute the void node's function
     */
    virtual int execute();

    /** Execute the node 
     */
    virtual void result() = 0;

    //@}
};

/**<b><tt>ArrayNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ArrayNode : public Node
{
  public:

    /**@name VoidNode public methods */
    //@{

    /** Execute the array node's function
     */
    virtual int execute();

    /** Execute the node 
     *  @return Pointer to the resulting array
     */
    virtual Array* result() = 0;

    /** Get the container type
     */
    virtual int containerType() const = 0;

    /** Get the default variable
     *  @return Pointer to the default variable
     */
    virtual const Variable* defaultValue() const = 0;

    //@}
};

/**<b><tt>HashNode</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Node.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:03:22 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class HashNode : public Node
{
  public:

    /**@name VoidNode public methods */
    //@{

    /** Execute the hash node's function
     */
    virtual int execute();

    /** Execute the node 
     *  @return Pointer to the resulting array
     */
    virtual Hash* result() = 0;

    /** Get the container type
     */
    virtual int containerType() const = 0;

    /** Get the default variable
     *  @return Pointer to the default variable
     */
    virtual const Variable* defaultValue() const = 0;

    //@}
};

/**<b><tt>PPoidNode</tt></b>
 */
class PPoidNode : public Node
{
  public:

    /**@name PPoidNode public methods */
    //@{

    /** Execute the date node's function
     */
    virtual int execute();

    /** Get the date value
     *  @return The date value
     */
    virtual const BAS::Identifier& result() = 0;

    //@}
};
}
#endif // NODE_HPP
