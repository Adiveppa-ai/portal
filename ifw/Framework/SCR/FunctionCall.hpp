#ifndef SCR_FUNCTIONCALL_HPP
#define SCR_FUNCTIONCALL_HPP
/* @(#)%Portal Version: FunctionCall.hpp:PlatformR2Int:2:2006-Jul-16 15:27:25 % */

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
//   Declaration of the base class for all function nodes used to call iScript
//   functions coded in 
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// $RCSfile: FunctionCall.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
//------------------------------------------------------------------------------
// Revision 1.2  2004/18/08 ammon
// PRSF00136596:  Add PPoid support.
//
// Revision 1.1  2001/04/10 10:50:35  sd
// - Full function support (inclusive return values)
//
//==============================================================================

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
namespace SCR
{

typedef RWTPtrOrderedVector<Node> ParameterList;

class Function;

/** <b><tt>FunctionCall</tt></b> is the base class for all iScript function
 *  nodes used to call functions coded in iScript.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class FunctionCall D_THREADINFO
{
  public:
    /**@name FunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    FunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~FunctionCall();

    //@}

    /**@name FunctionCall public methods */
    //@{

    /** Initialize the pointer to the function to execute
     *  @param fct Pointer to the function to execute
     */
    void function( Function* fct );

    //@}

  protected:
    // Instance members
    ParameterList parametersM;
    Function*     functionM;
};

/** <b><tt>VoidFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type void.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class VoidFunctionCall : public FunctionCall, public VoidNode
{
  public:
    /**@name VoidFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    VoidFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~VoidFunctionCall();

    //@}


    /**@name VoidFunctionCall public methods */
    //@{

    /** Execute the function
     */
    virtual void result();

    //@}
};

/** <b><tt>StringFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type String.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class StringFunctionCall : public FunctionCall, public StringNode
{
  public:
    /**@name StringFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    StringFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~StringFunctionCall();

    //@}


    /**@name StringFunctionCall public methods */
    //@{

    /** Execute the function and return the result
     *  @return The function result
     */
    virtual const BAS::String& result();

    //@}
};

/** <b><tt>LongFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type Long.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class LongFunctionCall : public FunctionCall, public LongNode
{
  public:
    /**@name LongFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    LongFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~LongFunctionCall();

    //@}


    /**@name LongFunctionCall public methods */
    //@{

    /** Execute the function and return the result
     *  @return The function result
     */
    virtual int64 result();

    //@}
};


/** <b><tt>AdtFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type Adt.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  </tr>
 *  </table>
 */
class AdtFunctionCall : public FunctionCall, public LongNode
{
  public:
    /**@name AdtFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    AdtFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~AdtFunctionCall();

    //@}


    /**@name AdtFunctionCall public methods */
    //@{

    /** Execute the function and return the result
     *  @return The function result
     */
    virtual int64 result();

    //@}
};

/** <b><tt>DecimalFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type Decimal.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalFunctionCall : public FunctionCall, public DecimalNode
{
  public:
    /**@name DecimalFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    DecimalFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~DecimalFunctionCall();

    //@}


    /**@name DecimalFunctionCall public methods */
    //@{

    /** Execute the function and return the result
     *  @return The function result
     */
    virtual const BAS::Decimal& result();

    //@}
};

/** <b><tt>DateFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type Date.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class DateFunctionCall : public FunctionCall, public DateNode
{
  public:
    /**@name DateFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    DateFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~DateFunctionCall();

    //@}


    /**@name DateFunctionCall public methods */
    //@{

    /** Execute the function and return the result
     *  @return The function result
     */
    virtual const BAS::DateTime& result();

    //@}
};

/** <b><tt>BoolFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type Bool.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FunctionCall.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:06 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class BoolFunctionCall : public FunctionCall, public BoolNode
{
  public:
    /**@name BoolFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    BoolFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~BoolFunctionCall();

    //@}


    /**@name BoolFunctionCall public methods */
    //@{

    /** Execute the function and return the result
     *  @return The function result
     */
    virtual bool result();

    //@}
};

/** <b><tt>PPoidFunctionCall</tt></b> is the iScript function node used to
 *  call functions coded in iScript with a return value of type PPoid.
 */
class PPoidFunctionCall : public FunctionCall, public PPoidNode
{
  public:
    /**@name PPoidFunctionCall constructors and destructor */
    //@{

    /** Constructor
     *  @param parameters List with all function call parameters
     */
    PPoidFunctionCall( const ParameterList& parameters );

    /** Destructor
     */
    virtual ~PPoidFunctionCall();

    //@}


    /**@name PPoidFunctionCall public methods */
    //@{

    /** Execute the function and return the result
     *  @return The function result
     */
    virtual const BAS::Identifier& result();

    //@}
};
}
#endif // FUNCTIONCALL_HPP
