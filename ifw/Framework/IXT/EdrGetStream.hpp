#ifndef IXT_EDR_GET_STREAM_HPP
#define IXT_EDR_GET_STREAM_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrGetStream.
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

#if !defined IXT_EXPORT
  #if defined(WINDOWS)
    #if !defined(IXT_INTERNAL)
      #define IXT_EXPORT __declspec(dllimport)
    #else
      #define IXT_EXPORT __declspec(dllexport)
    #endif
  #else
    #define IXT_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
class StringNode;
}
namespace IXT
{

class Integrate;
/** <b><tt>EdrGetStream</tt></b> is the iScript function node for sending 
 *  requests to other plugins.
 */
class EdrGetStream : public SCR::StringNode
{
  public:
    /**@name EdrGetStream constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrGetStream();

    //@}


    /**@name EdrGetStream public methods */
    //@{

    /** Execute the iScript function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual const BAS::String & result();

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
    EdrGetStream(Integrate * extension);

    //@}

  private:
    // Hide copy constructor and assignment operator (not implemented)
    EdrGetStream();
    EdrGetStream( const EdrGetStream& other );
    const EdrGetStream& operator=( const EdrGetStream& other );

    void collectAllStreamNames(Integrate * extension);
    RWTValOrderedVector<BAS::String> streamNameM;

    // Instance members
    Integrate*  extensionM;
    BAS::String      emptyResultM;

    IXT_EXPORT static const BAS::String outputModuleCM;
};
}
#endif
