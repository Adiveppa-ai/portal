#ifndef IXT_LOGPIPELINE_HPP
#define IXT_LOGPIPELINE_HPP

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
//   Declaration of the class LogPipeline
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
// $RCSfile: LogPipeline.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/08/29 23:47:16 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: LogPipeline.hpp,v $
// Revision 1.1  2001/08/29 23:47:16  sd
// - PETS #38204 - iScript compile errors have loglevel NORMAL
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

namespace SCR
{
class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{
class Integrate;

/** <b><tt>LogPipeline</tt></b> is the iScript function node for writting
 *  messages to the pipeline log.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: LogPipeline.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/29 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class LogPipeline : public SCR::VoidNode
{
  public:
    /**@name LogPipeline constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~LogPipeline();

    //@}

    /**@name LogPipeline public functions */
    //@{
    
    /** Execute the function
     */
    virtual void result();
    
    /** Create a logPipeline() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     *  @param string String to write to pipeline log
     */
    LogPipeline( Integrate*  extension,
                     SCR::StringNode* stringNode,
                     SCR::LongNode*   severityNode);


  private:
    // Hide default and copy constructor
    LogPipeline();
    LogPipeline( const LogPipeline& other );
    const LogPipeline& operator=( const LogPipeline& other );

    // instance members
    Integrate*  extensionM;
    SCR::StringNode* stringNodeM;
    SCR::LongNode*   severityNodeM;
};
}
#endif // LOGPIPELINE_HPP
