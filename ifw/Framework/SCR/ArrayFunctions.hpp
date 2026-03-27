#ifndef SCR_ARRAYFUNCTIONS_HPP
#define SCR_ARRAYFUNCTIONS_HPP

/* @(#)%Portal Version: ArrayFunctions.hpp:PlatformR2Int:2:2006-Jul-16 15:28:35 % */
//==============================================================================
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
//   Function nodes for arrays.
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
// $RCSfile: ArrayFunctions.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:00:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: ArrayFunctions.hpp,v $
// Revision 1.1  2000/10/06 15:11:21  sd
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
/** <b><tt>ArraySize</tt></b> is the function node to determine the size
 *  of an array.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:48 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ArraySize : public LongNode
{
  public:
    /**@name ArraySize constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~ArraySize();

    //@}


    /**@name ArraySize public methods */
    //@{

    /** Get the size of an array
     *  @return The array size
     */
    virtual int64 result();

    /** Create a function node
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
     *  @param array The array for which to determine the size
     */
    ArraySize( ArrayNode* array );

  private:

    // Hide default and copy constructor
    ArraySize();
    ArraySize( const ArraySize& other );
    const ArraySize& operator=( const ArraySize& other );

    // instance members
    ArrayNode* arrayNodeM;
};

/** <b><tt>ArrayClear</tt></b> is the function node for clearing arrays.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: ArrayFunctions.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:00:48 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class ArrayClear : public VoidNode
{
  public:
    /**@name ArrayClear constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~ArrayClear();

    //@}


    /**@name ArrayClear public methods */
    //@{

    /** Clear the array
     *  @return The array size
     */
    virtual void result();

    /** Create a function node
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
     *  @param array The array to clear
     */
    ArrayClear( ArrayNode* array );

  private:

    // Hide default and copy constructor
    ArrayClear();
    ArrayClear( const ArrayClear& other );
    const ArrayClear& operator=( const ArrayClear& other );

    // instance members
    ArrayNode* arrayNodeM;
};
}
#endif // ARRAYFUNCTIONS_HPP
