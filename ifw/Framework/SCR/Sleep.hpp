#ifndef SCR_SLEEP_HPP
#define SCR_SLEEP_HPP

//==============================================================================
//
// Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
//      This material is the confidential property of Oracle Corporation. or its
//      subsidiaries or licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the iScript sleep() function.
//==============================================================================

#ifndef __rw_thread_thread_h__
  #include <rw/thread/thread.h>
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;

class Sleep : public VoidNode
{
  public:
    /**@name Sleep constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~Sleep();

    //@}

    /**@name Sleep public methods */
    //@{


    /** Sleeps for specified seconds 
     *  @return void
     */
    virtual void result();

    /** Sleep() 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     */
    static Node* factory( Interpreter&    interpreter,
                              ParserStack&    stack,
                              const FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param value Decimal node as input parameter
     */
    Sleep( LongNode* value ); 

    // instance members
    LongNode* valueM;
};
}
#endif // SLEEP_HPP
