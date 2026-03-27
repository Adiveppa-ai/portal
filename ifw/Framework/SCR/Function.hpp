#ifndef SCR_FUNCTION_HPP
#define SCR_FUNCTION_HPP

//==============================================================================
//
// Copyright (c) 1998, 2023, Oracle and/or its affiliates.
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Function.
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
// $RCSfile: Function.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:01 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Function.hpp,v $
// Revision 1.11  2001/06/14 11:05:30  sd
// - Transaction support changed
//
// Revision 1.10  2001/06/14 09:58:35  sd
// - iScript now supports transactions
//
// Revision 1.9  2001/04/10 10:50:35  sd
// - Full function support (inclusive return values)
//
// Revision 1.8  2001/04/09 08:20:03  sd
// - Initial revision
//
//==============================================================================

#if !defined SCR_EXPORT
    #define SCR_EXPORT 
#endif

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef SCR_STATEMENT_HPP
  #include "SCR/Statement.hpp"
#endif
namespace SCR
{

class Variable;

/** <b><tt>Function</tt></b> is the class for self-defined iScript
 *  functions.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Function.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:01 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 */
class Function : public StatementList
{
  public:
    /**@name Function constructors and destructor */
    //@{

    /** Constructor
     */
    Function();

    /** Destructor
     */
    virtual ~Function();

    //@}


    /**@name Function public methods */
    //@{
    
    /** Add a new identifier to the function
     *  @param identifier Identifier of this value
     *  @param value Variable to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addIdentifier( const BAS::String& identifier,
                                Variable*     value );

    /** Get the string list with parameter variables
     *  @return Reference to the parameter name list
     */
    const BAS::StringList& parameters() const;

    /** Get a pointer to the return value variable
     *  @return Pointer to the variable
     */
    Variable* returnValue() const;

    /** Change the internal state to parameters (return value init finished)
     */
    void returnValueInitFinished();

    /** Change the internal state to initialized (parameter init finished)
     */
    void parameterInitFinished();

    /** Get the return type of the function
     */
    int returnType() const;

    //@}

  protected:

    enum InitStateT
    {
      INIT_RETVAL,
      INIT_PARAMETERS,
      INITIALIZED
    };

  private:
    // Instance members
    Variable*  returnValueM;
    BAS::StringList parametersM;
    InitStateT     stateM;

  public:
    // Class members
    SCR_EXPORT static const BAS::String retValNameCM;
};

typedef RWTPtrMap<BAS::String,Function,less<BAS::String> > FunctionMap;

//==============================================================================
// Get the list with function parameters
//==============================================================================
inline const BAS::StringList&
Function::parameters() const 
{
  return parametersM;
}

//==============================================================================
// Get a pointer to the return value
//==============================================================================
inline Variable*
Function::returnValue() const
{
  // Only void functions have no return value and for these this function should
  // never be called.
  RWPRECONDITION( returnValueM != 0 );
  return returnValueM;
}

//==============================================================================
// Change the internal state
//==============================================================================
inline void
Function::returnValueInitFinished()
{
  stateM = INIT_PARAMETERS;
}

//==============================================================================
// Change the internal state
//==============================================================================
inline void
Function::parameterInitFinished()
{
  stateM = INITIALIZED;
}

//==============================================================================
// Get the return type of the function
//==============================================================================
inline int
Function::returnType() const
{
  if ( returnValueM != 0 )
  {
    return Node::baseType( returnValueM->dataType() );
  }
  else
  {
    return Node::VOID_TYPE;
  }
}

}
#endif // FUNCTION_HPP

