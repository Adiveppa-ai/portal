#ifndef SCR_INTERPRETER_HPP
#define SCR_INTERPRETER_HPP 

//==============================================================================
//
// Copyright (c) 1995, 2023, Oracle and/or its affiliates.
// All rights reserved. 
//
//	This material is the confidential property of Oracle Corporation.
//	or its subsidiaries or licensors and may be used, reproduced,
//	stored or transmitted only in accordance with a valid Oracle
//	license or sublicense agreement
//
//------------------------------------------------------------------------------
// Block: FCT
//------------------------------------------------------------------------------
// Module Description:
//   Integrate´s interpreter to evaluate conditions and process programms.
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
// $RCSfile: Interpreter.hpp $
// $Revision: /cgbubrm_7.5.0.portalbase/1 $
// $Author: nishahan $
// $Date: 2015/11/27 05:02:32 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Interpreter.hpp,v $
// Revision 1.36  2001/09/16 21:11:59  sd
// - PETS #37618 Compiler warnings removed
//
// Revision 1.35  2001/05/23 10:47:39  sd
// - Changes for the new iRules extensions.
//
// Revision 1.34  2001/05/04 09:16:42  bt
// CMD_WRITE_LOG entry removed.
//
// Revision 1.33  2001/04/10 13:48:22  sd
// - return statement improved
//
// Revision 1.32  2001/04/06 11:17:28  sd
// - Support for functions (currently without return values)
//
// Revision 1.31  2000/09/27 08:19:00  sd
// - Include for EDR::Container.hpp removed.
//
// Revision 1.30  2000/09/27 07:08:01  sd
// - New interface for compilation of compare patters introduced.
//
// Revision 1.29  2000/09/26 13:33:04  sd
// - Module SCR is now only dependent from BAS
//
// Revision 1.28  2000/09/25 12:43:13  sd
// - New function edrDatablockIsValid() added. This function has to be used
//   in all loops for datablocks.
//
// Revision 1.27  2000/09/08 15:35:06  sd
// - new functions String formatName() and
//                 Void   scriptUsable(Bool) added.
//
// Revision 1.26  2000/09/08 15:04:32  sd
// - Function scriptUsable() added.
//
// Revision 1.25  2000/08/23 15:49:11  sd
// - Hash and array values introduced.
//
// Revision 1.24  2000/08/17 11:35:39  sd
// - first version with iScript extensions
//
// Revision 1.23  2000/05/09 15:08:12  sd
// - go back to v3-99-10
//
// Revision 1.21  2000/04/25 08:15:20  sd
// - Support for EDR container duplication added.
//
// Revision 1.20  2000/04/20 10:37:10  sd
// - new functions edrDuplicate() and edrSetCurrent() added.
// - support for edr duplication added (not yet working)
//
// Revision 1.19  2000/04/18 08:12:58  sd
// - new Function Void stopFormat(Void) added.
//
// Revision 1.18  2000/04/17 13:15:00  sd
// - Support for message processing added.
//
// Revision 1.17  2000/04/11 11:41:54  sd
// - General constants like MAX_DATE and MIN_DATE added.
//
// Revision 1.16  2000/03/31 12:27:13  sd
// - New function `String regString(String)' added to interpreter.
//
// Revision 1.15  2000/03/31 11:09:51  sd
// - Global constant now can be passed to the interpreter.
//
// Revision 1.14  2000/03/23 12:49:13  sd
// - new function callEdrSpecificFunctions().
//
// Revision 1.13  2000/03/23 12:36:15  sd
// - Support for edr specific functions added.
// - Functions can have a return type now (just Syntax!)
//
// Revision 1.12  2000/03/22 13:00:02  sd
// - edr access functions changed to support up to 3 parameters (edralias,
//   block number and multi field number ).
//
// Revision 1.11  2000/03/17 09:29:42  sd
// - Support for sending events added.
// - New function Bool sendEvent(String) added to script language.
//
// Revision 1.10  2000/03/16 14:49:25  sd
// - new function numConditions() added.
//
// Revision 1.9  2000/03/16 12:13:08  sd
// - New function Bool edrSetStream(String) added.
//
// Revision 1.8  2000/03/14 15:20:22  sd
// - Check for actual edr container != 0 added to make the script language
//   more robust.
//
// Revision 1.7  2000/03/14 14:32:38  sd
// - Return type for operator=() added to avoid warnings under HPUX.
//
// Revision 1.6  2000/03/14 13:03:35  sd
// - New function pushFunction() added.
//
// Revision 1.5  2000/03/13 12:38:53  sd
// - Function edrAddDataBlock() added to descriptions.
//
// Revision 1.4  2000/03/10 08:20:12  sd
// - Changed the interface for the factory functions.
//
// Revision 1.3  2000/03/08 08:19:31  sd
// - Copy constructor, assignement operator declared private.
//
// Revision 1.2  2000/03/07 17:00:33  sd
// - Left hand value flag for datatypes introduced.
// - Comments (C and C++ style) added to Lexer.
//
// Revision 1.1  2000/03/06 14:32:50  sd
// - Initial revision.
//
//==============================================================================

#if !defined SCR_EXPORT
    #define SCR_EXPORT 
#endif

#ifndef RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef BAS_REGISTEREDOBJECT_HPP
  #include "BAS/RegisteredObject.hpp"
#endif
#ifndef NORM_NUMBER_HPP
  #include "BAS/NormNumber.hpp"
#endif
#ifndef SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef SCR_STATEMENT_HPP
  #include "SCR/Statement.hpp"
#endif
#ifndef SCR_FUNCTION_HPP
  #include "SCR/Function.hpp"
#endif
#ifndef SCR_VARIABLE_HPP
  #include "SCR/Variable.hpp"
#endif
#ifndef SCR_EXTENSION_HPP
  #include "SCR/Extension.hpp"
#endif
namespace SCR
{

class Log;
class CompareInterface;
class ParserStack;
class FctDescr;

/**<b><tt>Interpreter</tt></b> is the iScript interpreter.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Interpreter.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.portalbase/1 $</font></td>
 *  <td><font size=-1>$Date: 2015/11/27 05:02:32 $</font></td>
 *  <td><font size=-1>$Author: nishahan $</font></td>
 *  </tr>
 *  </table>
 *
 *  <dl>
 *  <dt><b>Registry entries</b></dt>
 *      <dd>none</dd>
 *  <dt><b>Messages send</b></dt>
 *      <dd>none</dd>
 *  <dt><b>Requests send</b></dt>
 *      <dd>none</dd>
 *  <dt><b>Information</b></dt>
 *      <dd>none</dd>
 *  <dt><b>Errors</b></dt>
 *      <dd>none</dd>
 *  </dl>
 */
class Interpreter D_THREADINFO
{
  public:
    /**@name Interpreter constructors and destructor */
    //@{
    
    /** Constructor
     */
    Interpreter( Log* log );

    /** Destructor
     */
    ~Interpreter();

    //@}

    /**@name Interpreter public methods */
    //@{

    /** Compile the programm specified in parameter string
     *  @param program Programcode to compile
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool compile( const BAS::String& program );

    /** Execute the programm.
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool execute();

    /** Get the isValid falg
     *  @return The isValid flag
     */
    bool isValid() const;

    /** Get the script is usable flag
     *  @return The script is usable flag
     */
    bool scriptUsable() const;

    /** Compile the conditions specified in parameter string
     *  @param condition Conditions to compile
     *  @param interface Interface class for returning the pattern conditions
     */
    bool compileConditions( const BAS::String&     conditions,
                            CompareInterface& var_interface );
    
    /** Compile the where clause for an iSQL query
     *  @param clause The condition for the where clause
     *  @return Pointer to the root node of the clause's parse tree
     */
    BoolNode* compileQuery( const BAS::String& clause );
					   
    /** Get pointer to the actual statement
     *  @return pointer to actual statement if existent, 0 otherwise
     */
    Node* topStatement();

    /** Push a new function to the interpreter
     *  @param functionName Name of the function
     *  @param function Statement list for the function
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool pushFunction( const BAS::String&  functionName,
                       Function*      function );

    /** Add a new statement to the interpreter´s stack
     *  @param list The new statementlist to add
     */
    bool pushStatement( Node* statement );

    /** Pop a statement from the interpreter´s stack
     *  @param list The new statementlist to add
     */
    bool popStatement();

    /** Add a new statement to the actual statement list
     *  @param statement Statement to add to interpreter
     */
    bool addStatement( Node* statement );

    /** Add a new identifier to the actual statement list 
     *  @param identifier Identifier of this value
     *  @param value Variable to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addIdentifier( const BAS::String& identifier,
                        Variable*     value );

    /** Add a new global constant to the interpreter. These constants can be
     *  overwritten be script variables 
     *  @param identifier Identifier of this value
     *  @param value String value to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addGlobalConstant( const BAS::String& identifier,
                            const BAS::String& value );

    /** Get a defined IScript function from the interpreter
     *  @param name The function name
     *  @return Pointer to the statementlist if existent, 0 otherwise
     */
    Function* getFunction( const BAS::String& name );

    /** Get a variable from the interpreter
     *  @param identifier Identifier to get
     *  @return Pointer to variable if existent, 0 otherwise
     */
    Variable* getVariable( const BAS::String& module,
                               const BAS::String& identifier );

    /** Write a compile error to the format log. 
     *  @param string String to write to the format log
     */
    void logError( const BAS::String& string );

    /** Set the number of lines compiled
     */
    void linesCompiled( int64 numLines );

    /** Get the number of lines compiled
     */
    int64 linesCompiled() const;

    /** Insert a new iScript extension in the interpreter
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool insertExtension( Extension* extension );

    /** Get an iScript extenions by name 
     *  @param name The name of the desired extension 
     *  @return Pointer to the iScript extension on success, 0 otherwise
     */
    Extension* extension( const BAS::String& name );

    //@}

  protected:

    /** Clear the old program
     */
    void clear();

    /* Set the isValid flag
     * @param flag The new flag
     */
    void isValid( bool flag );

    /* Set the script is usable flag
     * @param flag The new script is usable value
     */
    void scriptUsable( bool flag );
    

  private:

    // Hide copy constructor and operator=
    Interpreter( const Interpreter& );
    const Interpreter& operator=( const Interpreter& );

    // member variables
    Log*                          logM;
    RWTPtrOrderedVector<Node>     statementStackM;
    VariableMap                   globalConstantsM;
    Function*                     mainFunctionM;
    FunctionMap                   functionsM;
    ExtensionVector               extensionsM;
    int64                              linesCompiledM;
    bool                              scriptUsableM;
    bool                              isValidM;

    // friends
    friend class ScriptUsable;

    // class members
    SCR_EXPORT static const BAS::String functionBeginCM;
    SCR_EXPORT static const BAS::String functionEndCM;
};

//==============================================================================
// Set the number of lines compiled
//==============================================================================
inline void
Interpreter::linesCompiled( int64 linesCompiled )
{
  linesCompiledM = linesCompiled;
}

//==============================================================================
// Get the number of lines compiled
//==============================================================================
inline int64
Interpreter::linesCompiled() const
{
  return linesCompiledM;
}

//==============================================================================
// Set the script is usable flag
//==============================================================================
inline void
Interpreter::scriptUsable( bool flag )
{
  scriptUsableM = flag;
}

//==============================================================================
// Check if the script is usable
//==============================================================================
inline bool
Interpreter::scriptUsable() const
{
  return scriptUsableM;
}
}
#endif // INTERPRETER_HPP
