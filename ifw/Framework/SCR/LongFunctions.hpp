#ifndef SCR_LONGFUNCTIONS_HPP
#define SCR_LONGFUNCTIONS_HPP

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
//   Declaration of the interpreter's long functions.
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
// $RCSfile: LongFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:43 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: LongFunctions.hpp,v $
// Revision 1.5  2001/01/18 09:23:37  sd
// - New function Long strHexToString(String) added.
//
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

#ifndef RW_TOOLS_TVMAP_H
  #include <rw/tvmap.h>
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_PARSERSTACK_HPP
  #include "SCR/ParserStack.hpp"
#endif
namespace SCR
{

class Interpreter;

/**<b><tt>Length</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LongFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:43 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Length : public LongNode
{
  public:
    /**@name Length constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Length();
    
    //@}

    /**@name Length public methods*/
    //@{

    /** Get the length of the string
     *  @return Length of the input string
     */
    virtual int64 result();

    /** Create a length function 
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
     */
    Length( StringNode* stringNode );

    StringNode* stringNodeM;
};

/**<b><tt>LongAbs</tt></b> implements the abs() function for long values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LongFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:43 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongAbs : public LongNode
{
  public:
    /**@name LongAbs constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongAbs();

    //@}

    /**@name LongAbs public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual int64 result();

    /** Create a longAbs function 
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
    LongNode* valueM;

    /** Constructor
     *  @param value Long node as input parameter
     */
    LongAbs( LongNode* value );
};

/**<b><tt>StrToLong</tt></b> implements the strToLong() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LongFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:43 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrToLong : public LongNode
{
  public:
    /**@name StrToLong constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrToLong();

    //@}

    /**@name StrToLong public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual int64 result();

    /** Create a strToLong() function on datastack
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
     *  @param string Value to convert
     */
    StrToLong( StringNode* string );

    // instance members
    StringNode* stringM;
};

/**<b><tt>StrHexToLong</tt></b> implements the strHexToLong() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LongFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:43 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StrHexToLong : public LongNode
{
  public:
    /**@name StrHexToLong constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~StrHexToLong();

    //@}

    /**@name StrHexToLong public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual int64 result();

    /** Create a strHexToLong() function on datastack
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
     *  @param string Value to convert
     */
    StrHexToLong( StringNode* string );

    // instance members
    StringNode* stringM;
};

/**<b><tt>LongDecode</tt></b> implements the longDecode() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LongFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:43 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongDecode : public LongNode
{
  public:
    /**@name LongDecode constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~LongDecode();

    //@}

    /**@name LongDecode public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual int64 result();

    /** Create a longDecode() function on datastack
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    /** Add a new map entry to the map
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addMapEntry( int64 source, int64 dest );

    /** Set the source node
     *  @param The decode node
     */
    void decodeNode( LongNode* decodeNode );

    /** Set the default value
     *  @param The default value
     */
    void defaultValue( int64 defValue );
    
    //@}

  protected:
    /** Constructor
     */
    LongDecode();

    RWTValMap< int64,int64,less<int64> > mapM;
    LongNode*                     decodeNodeM;
    int64                         defaultValueM;
};
}
#endif // LONGFUNCTIONS_HPP
