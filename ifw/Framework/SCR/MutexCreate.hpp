#ifndef SCR_MUTEXCREATE_HPP
#define SCR_MUTEXCREATE_HPP
/* @(#)%Portal Version: MutexCreate.hpp:PlatformR2Int:2:2006-Jul-16 15:26:26 % */
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
//   Declaration of the iScript function node for mutexCreate.
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

/** <b><tt>MutexCreate</tt></b>
 */
class MutexCreate : public LongNode
{
  public:
    /**@name MutexCreate constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~MutexCreate();

    //@}


    /**@name MutexCreate public methods */
    //@{

    /** Execute the function
     *  @return Handle for the muxtex on success (>0), <0 otherwise
     */
    virtual int64 result();

    /** Create a mutexCreate() function node
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
    MutexCreate( MainExtension* mainExtension );

  private:
    // Instance members
    MainExtension* mainExtensionM;
};
}
#endif // MUTEXCREATE_HPP
