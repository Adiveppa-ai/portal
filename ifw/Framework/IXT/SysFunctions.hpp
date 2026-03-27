#ifndef IXT_SYSFUNCTIONS_HPP
#define IXT_SYSFUNCTIONS_HPP

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
//   Definition of the iScript integRate system functions.
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
// $RCSfile: SysFunctions.hpp,v $
// $Revision: 1.5 $
// $Author: sd $
// $Date: 2001/08/29 23:47:16 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: SysFunctions.hpp,v $
// Revision 1.6  2002/05/30 13:47:16  cdiab
// - added RegistryNodeName to retrieve the name of the actual registry node
//
// Revision 1.5  2001/08/29 23:47:16  sd
// - PETS #38204 - iScript compile errors have loglevel NORMAL
//
// Revision 1.4  2001/05/03 16:08:14  bt
// Format renamed to Pipeline.
//
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
class FctDescr;
class ParserStack;
}
namespace IXT
{
class Integrate;
/**<b><tt>SendEvent</tt></b> is used to send events to the event handler
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SysFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/29 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class SendEvent : public SCR::BoolNode
{
  public:
    /**@name SendEvent constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~SendEvent();

    //@}

    /**@name SendEvent public functions */
    //@{
    
    /** Execute the function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Set the event name
     *  @param eventName Name of the event to send
     */
    void eventName( SCR::StringNode* eventName );

    /** Add an event arguement to the node
     *  @param eventArg Argument node to add
     */
    void addArgument( SCR::StringNode* eventArg );

    /** Create a sendEvent() function 
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
     */
    SendEvent( Integrate* extension );

  private:
    // Hide default and copy constructor
    SendEvent();
    SendEvent( const SendEvent& other );
    const SendEvent& operator=( const SendEvent& other );

    // instance members
    Integrate*                      extensionM;
    SCR::StringNode*                     eventNameM;
    RWTPtrOrderedVector<SCR::StringNode> eventArgsM;
};

/**<b><tt>RegString</tt></b> is used to get string values from the
 * registry.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SysFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/29 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class RegString : public SCR::StringNode
{
  public:
    /**@name RegString constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~RegString();

    //@}

    /**@name SendEvent public functions */
    //@{
    
    /** Execute the function
     *  @return Registry string on success, empty string otherwise
     */
    virtual const BAS::String& result();

    /** Create a regString() function 
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
     *  @param registryName The registry name to get
     */
    RegString( Integrate*  extension,
                   SCR::StringNode* registryName );

  private:
    // Hide default and copy constructor
    RegString();
    RegString( const RegString& );
    const RegString& operator=( const RegString& );

    // instance members
    Integrate*  extensionM;
    SCR::StringNode* registryNameM;
    BAS::String      valueM;        
};

/**<b><tt>StopPipeline</tt></b> is the function node for the stopPipeline()
 * function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SysFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/29 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class StopPipeline : public SCR::VoidNode
{
  public:
    /**@name StopPipeline constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~StopPipeline();

    //@}

    /**@name StopPipeline public functions */
    //@{
    
    /** Execute the function
     */
    virtual void result();
    
    /** Create a stopPipeline() function node.
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
    StopPipeline( Integrate* extension );

  private:

    // instance members
    Integrate* extensionM;
};


/**<b><tt>PipelineName</tt></b> is the function node for the pipelineName()
 * function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SysFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/29 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class PipelineName : public SCR::StringNode
{
  public:
    /**@name PipelineName constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~PipelineName();

    //@}

    /**@name PipelineName public functions */
    //@{
    
    /** Execute the function
     */
    virtual const BAS::String& result();
    
    /** Create a pipelineName() function node.
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
     */
    PipelineName( Integrate* extension );

  private:
    // Hide copy and default constructor
    PipelineName();
    PipelineName( const PipelineName& );
    const PipelineName& operator=( const PipelineName& );

    // instance members
    Integrate* extensionM;
    BAS::String     pipelineNameM;
};

/**<b><tt>RegistryNodeName</tt></b> is the function node for the registryNodeName()
 * function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SysFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/05/30 13:47:16 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class RegistryNodeName : public SCR::StringNode
{
  public:
    /**@name RegistryNodeName constructor and destructors */
    //@{

    /** Destructor
     */
    virtual ~RegistryNodeName();

    //@}

    /**@name RegistryNodeName public functions */
    //@{
    
    /** Execute the function
     */
    virtual const BAS::String& result();
    
    /** Create a registryNodeName() function node.
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
     */
    RegistryNodeName( Integrate* extension );

  private:
    // Hide copy and default constructor
    RegistryNodeName();
    RegistryNodeName( const RegistryNodeName& );
    const RegistryNodeName& operator=( const RegistryNodeName& );

    // instance members
    Integrate* extensionM;
    BAS::String     registryNodeNameM;
};

/**<b><tt>NormalizeCli</tt></b> is the function node class for the
 * normalizeCli() function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SysFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/29 23:47:16 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class NormalizeCli : public SCR::StringNode
{
  public:
    /**@name NormalizeCli constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~NormalizeCli();
    
    //@}

    /**@name NormalizeCli public methods*/
    //@{

    /** Execute the normalizeCli() function
     *  @return result of NormalizeCli() function
     */
    virtual const BAS::String& result();

    /** Create a normalizeCli() function 
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}

  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     *  @param stringNode Cli number to normalize
     *  @param flagsNode Flags for normalization (can be 0)
     */
    NormalizeCli( Integrate*   extension,
                      SCR::StringNode*  stringNode,
                      SCR::LongNode*    flagsNode );

  private:
    // Hide default and copy constructor
    NormalizeCli();
    NormalizeCli( const NormalizeCli& );
    const NormalizeCli& operator=( const NormalizeCli& );
 
    // instance members
    Integrate*  extensionM;
    SCR::StringNode* stringNodeM;
    SCR::LongNode*   flagsNodeM;
    BAS::String      resultM;
};
}
#endif // SYSFUNCTIONS_HPP
