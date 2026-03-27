#ifndef SCR_MUTEXACQUIRE_HPP
#define SCR_MUTEXACQUIRE_HPP

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
//   Declaration of the iScript function node for mutexAcquire.
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
//------------------------------------------------------------------------------
// 2002/06/19
//   Initial revision
//==============================================================================

#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
namespace SCR
{

class Interpreter;
class ParserStack;
class FctDescr;
class MainExtension;

/** <b><tt>MutexAcquire</tt></b>
 */
class MutexAcquire : public BoolNode
{
  public:
    /**@name MutexAcquire constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~MutexAcquire();

    //@}


    /**@name MutexAcquire public methods */
    //@{

    /** Execute the function
     *  @return true on success, false otherwise
     */
    virtual bool result();

    /** Create a mutexAcquire() function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:
    /** Constructor
     *  @param mainExtension Pointer to the integRate pointer 
     */
    MutexAcquire( MainExtension* mainExtension,
                      LongNode*      mutexHandleNode );

  private:
    // Instance members
    MainExtension* mainExtensionM;
    LongNode*      mutexHandleNodeM;
};
}
#endif // MUTEXACQUIRE_HPP
