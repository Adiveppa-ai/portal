#ifndef IXT_MSGFUNCTIONS_HPP
#define IXT_MSGFUNCTIONS_HPP

//==============================================================================
//
//             1998, 1999, 2000 (c) Copyright by SOLUTION42 AG
//                          Quickborn (Germany)
//
//                          ALL RIGHTS RESERVED
//
//            Reproduction for internal use only is permitted.
//      Disclosure to any third parties, in any form or circumstances
//                 whatsoever, is not permitted at all.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the classes for the iScript message functions
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
// $RCSfile: MsgFunctions.hpp,v $
// $Revision: 1.3 $
// $Author: sd $
// $Date: 2001/04/12 12:22:52 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: MsgFunctions.hpp,v $
// Revision 1.3  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.1  2000/12/04 08:21:07  sd
// - Module moved from IXT to iScript.
//
// Revision 1.1  2000/09/27 11:33:21  sd
// - IXT is a framework module again
//
// Revision 1.1  2000/09/26 13:33:35  sd
// - Initial revision for separate integRate iScript extension.
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

/**<b><tt>MsgName</tt></b> is the function node for the msgName() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MsgFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/12 12:22:52 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class MsgName : public SCR::StringNode
{
  public:

    /**@name MsgName constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~MsgName();

    //@

    /**@name MsgName public methods */
    //@{

    /** Get the name of the current message
     *  @return The value
     */
    virtual const BAS::String& result();

    /** Factory for creation of the msgName() function
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

    /* Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    MsgName( Integrate* extension );
    
  private:

    // Hide the default and copy constructor
    MsgName();
    MsgName( const MsgName& );
    const MsgName& operator=( const MsgName& );

    // instance members
    Integrate* extensionM;
};

/**<b><tt>MsgArg</tt></b> is the function node for the msgArg() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MsgFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/12 12:22:52 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class MsgArg : public SCR::StringNode
{
  public:

    /**@name MsgArg constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~MsgArg();

    //@

    /**@name MsgArg public methods */
    //@{

    /** Get the name of the current message
     *  @return The value
     */
    virtual const BAS::String& result();

    /** Factory for creation of the msgName() function
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
     *  @param argIndex Parameter node
     */
    MsgArg( Integrate* extension,
                SCR::LongNode*  argIndex );

  private:
    // Hide the default and copy constructor
    MsgArg();
    MsgArg( const MsgArg& );
    const MsgArg& operator=( const MsgArg& );

    // instance members
    Integrate* extensionM;
    SCR::LongNode*  argIndexM;
};

/**<b><tt>MsgNumArgs</tt></b> is the function node for the msgNumArgs() 
 * function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MsgFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/04/12 12:22:52 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class MsgNumArgs : public SCR::LongNode
{
  public:

    /**@name MsgNumArgs constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~MsgNumArgs();

    //@

    /**@name MsgNumArgs public methods */
    //@{

    /** Get the number of arguments of the current message
     *  @return Number of arguments
     */
    virtual int64 result();

    /** Factory for creation of the msgNumArgs() function
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

    /* Constructor
     * @param extension Pointer to the integRate iScript extension
     */
    MsgNumArgs( Integrate* extension );

  private:
    // Hide the default and copy constructor
    MsgNumArgs();
    MsgNumArgs( const MsgNumArgs& );
    const MsgNumArgs& operator=( const MsgNumArgs& );
    
    // instance members
    Integrate* extensionM;
};
}
#endif // MSGFUNCTIONS_HPP
