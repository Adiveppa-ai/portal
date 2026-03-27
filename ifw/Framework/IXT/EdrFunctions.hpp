#ifndef IXT_EDRFUNCTIONS_HPP
#define IXT_EDRFUNCTIONS_HPP
/* @(#)%Portal Version: EdrFunctions.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:50:30 % */

//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the classes for the edr container access.
//
// Open Points:
//   <open points>
//
// Review Status:
//   <in-work>
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: EdrFunctions.hpp,v $
// $Revision: 1.7 $
// $Author: sd $
// $Date: 2002/01/07 10:47:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.8  2005/03/22  pborah
// PRSF00161970:  "iScript function "clearErrors()" missing in 6.7FP1"
//
// Revision 1.7  2004/10/19  ammon
// PRSF00136835:  Add functions for timed out flag
//
// Revision 1.6  2003/11/19  ammon
// PRSF00068378:  Add functions for EDR to XML serialization
//
// Revision 1.5  2002/01/07 10:47:57  sd
// - PETS #42574 - LERG enhancements
//
// Revision 1.4  2001/04/23 15:10:49  sd
// - IXT adjusted to EDR::BlockIndex.
//
// Revision 1.3  2001/04/12 12:22:52  sd
// - Moved from EXT_iScrpt to IXT
//
// Revision 1.4  2001/04/03 07:30:59  sd
// - Initial revision
//
// Revision 1.3  2001/03/22 15:21:35  sd
// - Adjusted to new EDR container
//
// Revision 1.2  2001/03/13 10:58:28  sd
// - First update for the new EDR container.
//
// Revision 1.1  2000/12/04 08:21:07  sd
// - Module moved from IXT to iScript.
//
// Revision 1.1  2000/09/27 11:33:21  sd
// - IXT is a framework module again
//
// Revision 1.1  2000/09/26 13:33:34  sd
// - Initial revision for separate integRate iScript extension.
//
// Revision 1.17  2000/09/25 12:43:13  sd
// - New function edrDatablockIsValid() added. This function has to be used
//   in all loops for datablocks.
//
// Revision 1.16  2000/08/30 07:52:49  sd
// - new functions Bool edrIsValidDetail() and Void edrSetIsValidDetail(Bool)
//   added
//
// Revision 1.15  2000/08/25 12:20:48  sd
// - new function Bool edrSetContentType(Long) added
// - BugFix for PR2404
//
// Revision 1.14  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.13  2000/05/23 12:52:11  sd
// - new functions Long edrNumMultiFields(EdrAlias,Long) and
//                 Long edrNumDatablocks(EdrAlias) added.
//
// Revision 1.12  2000/05/09 15:08:12  sd
// - go back to v3-99-10
//
// Revision 1.10  2000/05/05 08:37:09  sd
// - Function edrMaxSeverity() added.
//
// Revision 1.9  2000/04/20 10:37:10  sd
// - new functions edrDuplicate() and edrSetCurrent() added.
// - support for edr duplication added (not yet working)
//
// Revision 1.8  2000/03/22 13:00:02  sd
// - edr access functions changed to support up to 3 parameters (edralias,
//   block number and multi field number ).
//
// Revision 1.7  2000/03/16 12:13:08  sd
// - New function Bool edrSetStream(String) added.
//
// Revision 1.6  2000/03/16 10:15:56  sd
// - new function addEdrError( String, Long, ... )
// - interface for factory functions changed to references instead of
//   pointers.
//
// Revision 1.5  2000/03/14 11:05:07  sd
// - New function edrIndex() added to SCR::StringEdr.
//
// Revision 1.4  2000/03/13 12:38:53  sd
// - Function edrAddDataBlock() added to descriptions.
//
// Revision 1.3  2000/03/10 11:36:49  sd
// - isLeftValue() function removed.
//
// Revision 1.2  2000/03/10 08:20:12  sd
// - Changed the interface for the factory functions.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   SCR_DATA_HPP
  #include "SCR/Data.hpp"
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
/** <b><tt>EdrSetStream</tt></b> is the function for setting the output
 *  stream for the edr.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrSetStream : public SCR::BoolNode
{
  public:
    /**@name EdrSetStream constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrSetStream();

    //@}

    /**@name EdrSetStream public methods */
    //@{

    /** Check if the object is valid
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

    /** Execute the function.
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Factory for creation of function node
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

    /** Constructor for const strings
     *  @param extension Pointer to the integRate iScript extension
     *  @param streamName name of the output stream
     */
    EdrSetStream( Integrate*    extension,
                      const BAS::String& streamName );

    /** Constructor for NON const strings
     *  @param extension Pointer to the integRate iScript extension
     *  @param stringNode String node with name of the output stream
     */
    EdrSetStream( Integrate*  extension,
                      SCR::StringNode* streamName );

  private:

    // Hide copy and default constructor
    EdrSetStream();
    EdrSetStream( const EdrSetStream& );
    const EdrSetStream& operator=( const EdrSetStream& );

    // instance members    
    Integrate*  extensionM;
    int64            streamNumberM;
    SCR::StringNode* streamNameM;
};

/** <b><tt>EdrAddError</tt></b> is the function class for adding errors
 *  to an edr container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrAddError : public SCR::BoolNode
{
  public:
    /**@name EdrAddError constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrAddError();

    //@}

    /**@name EdrAddError public methods */
    //@{

    /** Execute the function.
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Factory for creation of function node
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

    /** Set the error node
     */
    void errorNode( SCR::StringNode* errorNode );

    /** Set the severity node
     */
    void severityNode( SCR::LongNode* severityNode );

    /** Add an argument for the error message
     */
    void addArgument( SCR::StringNode* stringNode );

    /** Constructor 
     *  @param extension Pointer to the integRate iScript extension
     *  @param error Error message to add to the edr container
     */
    EdrAddError( Integrate* extension );

  private:
    // Hide default and copy constructor
    EdrAddError();
    EdrAddError( const EdrAddError& other );
    const EdrAddError& operator=( const EdrAddError& other );
    
    // instance members
    Integrate*                      extensionM;
    SCR::StringNode*                     errorNodeM;
    SCR::LongNode*                       severityNodeM;
    RWTPtrOrderedVector<SCR::StringNode> argumentListM;
};

/**<b><tt>EdrDuplicate</tt></b> is the funtion node for the edrDuplicate()
 * function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrDuplicate : public SCR::LongNode
{
  public:
    /**@name EdrDuplicate constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrDuplicate();

    //@

    /**@name EdrDuplicate public methods */
    //@{

    /** Execute the edrDuplicate() function
     *  @return The index of the new edr container on success, -1 otherwise
     */
    virtual int64 result();

    /** Factory for creation of edr field
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
    EdrDuplicate( Integrate* interpreter );

  private:
    // disallow use of copy and default constructor
    EdrDuplicate();
    EdrDuplicate( const EdrDuplicate& );
    const EdrDuplicate& operator=( const EdrDuplicate& );

    // instance members
    Integrate* extensionM;
};

/**<b><tt>EdrSetCurrent</tt></b> is the funtion node for the edrSetCurrent()
 * function.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrSetCurrent : public SCR::BoolNode
{
  public:
    /**@name EdrSetCurrent constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrSetCurrent();

    //@

    /**@name EdrSetCurrent public methods */
    //@{

    /** Execute the edrSetCurrent() function
     *  @return The index of the new edr container on success, -1 otherwise
     */
    virtual bool result();

    /** Factory for creation of edr field
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
     *  @param indexNode Function node specifying the edr container index
     */
    EdrSetCurrent( Integrate* extension, 
                       SCR::LongNode*  indexNode );

  private:

    // disallow use of copy and default constructor
    EdrSetCurrent();
    EdrSetCurrent( const EdrSetCurrent& );
    const EdrSetCurrent& operator=( const EdrSetCurrent& );

    // instance members
    Integrate* extensionM;
    SCR::LongNode*  indexNodeM;
};

/** <b><tt>EdrMaxServerity</tt></b> is the function node for evaluating
 *  the maximum serverity of the current edr container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrMaxSeverity : public SCR::LongNode
{
  public:
    /**@name EdrMaxSeverity constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrMaxSeverity();

    //@}

    /**@name EdrMaxSeverity public methods */
    //@{

    /** Get the max severity of the current edr container
     *  @return The max severity (>= 0) on success, -1 otherwise
     */
    virtual int64 result();

    /** Factory for creation of function node
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
     *  @param extension Pointer to the integRate iScript extensioni
     *  @param error Error message to add to the edr container
     */
    EdrMaxSeverity( Integrate* extension );

  private:
    // Hide copy and default constructor
    EdrMaxSeverity();
    EdrMaxSeverity( const EdrMaxSeverity& );
    const EdrMaxSeverity& operator=( const EdrMaxSeverity& );

    // instance members
    Integrate* extensionM;
};

/** <b><tt>EdrSetContentType</tt></b> is the function for setting the 
 *  content type of the current edr.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrSetContentType : public SCR::BoolNode
{
  public:
    /**@name EdrSetContentType constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrSetContentType();

    //@}

    /**@name EdrSetContentType public methods */
    //@{

    /** Execute the function.
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool result();

    /** Factory for creation of function node
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

    /** Constructor for const strings
     *  @param extension Pointer to the integRate iScript extension
     *  @param streamName name of the output stream
     */
    EdrSetContentType( Integrate* extension,
                           SCR::LongNode*  contentNode );

  private:
    // Hide default and copy constructor
    EdrSetContentType();
    EdrSetContentType( const EdrSetContentType& other );
    const EdrSetContentType& operator=(const EdrSetContentType& other );

    // instance members    
    Integrate* extensionM;
    SCR::LongNode*  contentNodeM;
};

/**<b><tt>EdrIsValidDetail</tt></b> is the function node to check if a edr
 * container is a valid detail container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrIsValidDetail : public SCR::BoolNode
{
  public:

    /**@name EdrIsValidDetail constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrIsValidDetail();

    //@}

    /**@name EdrIsValidDetail public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual bool result();

    /** Create a edrIsValidDetail() function 
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
     *  @param extension Pointer to the integrate iScript extension
     */
    EdrIsValidDetail( Integrate* extension );

  private:
    // Hide default and copy constructor
    EdrIsValidDetail();
    EdrIsValidDetail( const EdrIsValidDetail& );
    const EdrIsValidDetail& operator=( const EdrIsValidDetail& );

    // instance members
    Integrate* extensionM;
};

/**<b><tt>EdrSetIsValidDetail</tt></b> is the function node to set the 
 * isValidDetail flag for the current EDR container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrSetIsValidDetail : public SCR::VoidNode
{
  public:

    /**@name EdrSetIsValidDetail constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrSetIsValidDetail();

    //@}

    /**@name EdrSetIsValidDetail public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual void result();

    /** Create a edrIsValidDetail() function 
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
     *  @param extension Pointer to the integrate iScript extension
     *  @param flagNode The parameter node for the function
     */
    EdrSetIsValidDetail( Integrate* extension,
                             SCR::BoolNode*  flagNode );

  private:
    // Hide copy and default constructor
    EdrSetIsValidDetail();
    EdrSetIsValidDetail( const EdrSetIsValidDetail& );
    const EdrSetIsValidDetail& operator=( const EdrSetIsValidDetail& );

    // instance members 
    Integrate* extensionM;
    SCR::BoolNode*  flagNodeM;
};

/** <b><tt>EdrXml</tt></b> is the function node to get the
 *  XML representation of the current edr.
 */
class EdrXml : public SCR::StringNode
{
  public:
    /**@name EdrXml constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrXml();

    //@}

    /**@name EdrXml public methods */
    //@{

    /** Execute the getEdrXml() function
     *  @return The XML representation of the current edr on success,
     *  BAS::NULL_STRING otherwise
     */
    virtual const BAS::String& result();

    /** Factory for creation of the function node
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
    /* Constructor
     * @param extension  Pointer to the integRate iScript extension
     * @param multiline  Produce multi-line "pretty" format XML.
     *                   Multiline must be false to use XML with input grammar
     */
    EdrXml( Integrate* extension, bool multiline );

  private:
    // Hide the copy constructor and assignment operator
    EdrXml( const EdrXml& );
    const EdrXml& operator=( const EdrXml& );

    // Instance members
    Integrate*  extensionM;
    bool        multilineM;
    BAS::String resultM;
};

/**<b><tt>EdrTimedOut</tt></b> is the function node to check if
 * the timed out flag is set for the current EDR container.
 */
class EdrTimedOut : public SCR::BoolNode
{
  public:

    /**@name EdrTimedOut constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrTimedOut();

    //@}

    /**@name EdrTimedOut public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual bool result();

    /** Create a edrTimedOut() function
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
     *  @param extension Pointer to the integrate iScript extension
     */
    EdrTimedOut( Integrate* extension );

  private:
    // Hide default and copy constructor
    EdrTimedOut();
    EdrTimedOut( const EdrTimedOut& );
    const EdrTimedOut& operator=( const EdrTimedOut& );

    // instance members
    Integrate*  extensionM;
};

/**<b><tt>EdrSetTimedOut</tt></b> is the function node to set the
 * timed out flag for the current EDR container.
 */
class EdrSetTimedOut : public SCR::VoidNode
{
  public:

    /**@name EdrSetTimedOut constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrSetTimedOut();

    //@}

    /**@name EdrSetTimedOut public methods */
    //@{

    /** Calculate the result value
     *  @return The result value
     */
    virtual void result();

    /** Create a edrTimedOut() function
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
     *  @param extension Pointer to the integrate iScript extension
     *  @param flagNode The parameter node for the function
     */
    EdrSetTimedOut( Integrate*      extension,
                    SCR::BoolNode*  flagNode );

  private:
    // Hide copy and default constructor
    EdrSetTimedOut();
    EdrSetTimedOut( const EdrSetTimedOut& );
    const EdrSetTimedOut& operator=( const EdrSetTimedOut& );

    // instance members
    Integrate*                      extensionM;
    BAS::OnlyPointer<SCR::BoolNode> flagNodeM;
};
/** <b><tt>EdrClearErrors</tt></b> is the function node for 
 *  Clearing the error list in the Edr container
 */
class EdrClearErrors : public SCR::VoidNode
{
  public:
    /**@name EdrClearErrors constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrClearErrors();

    //@}

    /**@name EdrClearErrors public methods */
    //@{

    /** Clear the error list of the current edr container
     *  @return void
     */
    virtual void result();

    /** Factory for creation of function node
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
     *  @param error Error message to add to the edr container
     */
    EdrClearErrors( Integrate* extension );

  private:
    // Hide default constructor
    EdrClearErrors();

    // instance members
    Integrate* extensionM;
};
}
#endif // EDRFUNCTIONS_HPP
