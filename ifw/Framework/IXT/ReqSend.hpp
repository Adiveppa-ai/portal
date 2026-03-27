#ifndef IXT_REQSEND_HPP
#define IXT_REQSEND_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class ReqSend.
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: 
//
//------------------------------------------------------------------------------
// 2002/06/18
//   Initial revision
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
class StringNode;
class ArrayNode;
}
namespace IXT
{
class Integrate;

/** <b><tt>ReqSend</tt></b> is the iScript function node for sending 
 *  requests to other plugins.
 */
class ReqSend : public SCR::BoolNode
{
  public:
    /**@name ReqSend constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~ReqSend();

    //@}


    /**@name ReqSend public methods */
    //@{

    /** Execute the iScript function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Create a sendMsg() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     *  @param string String to write to pipeline log
     */
    ReqSend( SCR::StringNode* receiverNode,
                 SCR::StringNode* requestNode,
                 SCR::ArrayNode*  inputArray,
                 SCR::ArrayNode*  outputArray
                );


    //@}

  private:
    // Hide copy constructor and assignment operator (not implemented)
    ReqSend();
    ReqSend( const ReqSend& other );
    const ReqSend& operator=( const ReqSend& other );

    // Instance members
    SCR::StringNode* receiverNodeM;
    SCR::StringNode* requestNodeM;
    SCR::ArrayNode*  inputArrayM;
    SCR::ArrayNode*  outputArrayM;
    Integrate*  extensionM;
};
}
#endif // REQSEND"_HPP
