#ifndef LRP_DESCRPARSER_HPP
#define LRP_DESCRPARSER_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the helper class used by the Yacc parser that parses the
//   configuration files. This class was only created because the SUN CC 
//   compile had problems with the templates database. To fix this problem
//   I had to move all the actions from the Yacc source code to member 
//   functions of this class.
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
// $RCSfile: DescrParser.hpp,v $
// $Revision: 1.11 $
// $Author: sd $
// $Date: 2001/06/21 10:17:38 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: DescrParser.hpp,v $
// Revision 1.11  2001/06/21 10:17:38  sd
// - FRM::FileDescr renamed to FRM::StreamDescr
//
// Revision 1.10  2001/05/17 08:16:21  sd
// - BugFix in method declaration
//
// Revision 1.9  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.8  2001/04/02 09:13:22  sd
// - BlockDescr renamed to FRM::RecordDescr
//
// Revision 1.7  2001/03/21 08:34:57  sd
// - Now multiple file and mapping descriptions are supported.
//
// Revision 1.6  2001/03/19 16:12:31  sd
// - Backup version
//
// Revision 1.5  2001/03/19 11:16:55  sd
// - Backup version
//
// Revision 1.4  2001/03/16 16:03:13  sd
// - ASN blocks added
//
// Revision 1.3  2001/03/13 13:45:35  sd
// - Backup version
//
// Revision 1.2  2001/03/07 15:02:39  sd
// - Backup
//
// Revision 1.1  2001/03/07 14:01:08  sd
// - New class DescrParser introduced
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_PARAMETER_HPP
  #include "EDR/Parameter.hpp"
#endif

namespace FRM
{
class DataDescr;
class StreamDescr;
class RecordDescr;
class InputMapping;
class OutputMapping;
}
namespace EDR
{
class FieldDescr;
}
namespace LRP
{
class Grammar;

//==============================================================================
// Types
//==============================================================================
typedef struct RuleDescription
{
    BAS::String     leftSideM;
    BAS::StringList rightSideM;
    int            lineNumberM;

#ifdef __aix
    bool operator==( const RuleDescription& other ) const
    {
      return( this == &other );
    }
    bool operator<( const RuleDescription& other ) const
    {
      return( this < &other );
    }
#endif
} RuleDescription;

typedef struct ActionDescription
{
    BAS::String     leftSideM;
    BAS::String     actionM;

#ifdef __aix
    bool operator==( const ActionDescription& other ) const
    {
      return( this == &other );
    }
    bool operator<( const ActionDescription& other ) const
    {
      return( this < &other );
    }
#endif
} ActionDescription;

typedef enum
{
  IN_MAPPING,
  OUT_MAPPING
} MappingModeT;


/** <b><tt>DescrParser</tt></b> is used by the Yacc parser that parses
 *  the input files like grammar description etc. This class was introduced
 *  because of some problems with the Solaris templates database when this
 *  functions were directly inserted in the Yacc source code.
 */
class DescrParser : public LRP_FlexLexer D_THREADINFO_M
{
  public:
    /**@name DescrParser constructors and destructor */
    //@{

    /** Constructor
     */
    DescrParser();

    /** Destructor
     */
    ~DescrParser();

    //@}


    /**@name DescrParser public methods */
    //@{

    /** Set the failure description
     *  @param msg New failure description
     */
    void failure( const BAS::String& msg );

    /** Get the failure description
     *  @return Reference to failure string
     */
    const BAS::String& failure();

    /** Push a parameter to the parameter stack
     *  @param parameter The parameter to push on the stack
     */
    void pushParameter( const EDR::Parameter& parameter );

    /** Append new iScript source code
     *  @param source The source code to append
     */
    void appendIScriptSource( const BAS::String& source );

    /** Get the number of non-terminal symbols
     *  @return number of non-terminal symbols
     */
    size_t numNonTerminals();

    /** Add a new non-terminal symbol
     *  @param name The name of the symbol
     */
    void addNonTerminal( const BAS::String& name );

    /** Get a non-terminal symbol name
     *  @param idx The index of the symbol
     *  @return Reference to symbol name
     */
    const BAS::String& nonTerminal( size_t idx );
    
    /** Set the start symbol name
     *  @param name The name of the symbol
     */
    void startSymbol( const BAS::String& name );

    /** Get the start symbol name
     *  @return Reference to start symbol name
     */
    const BAS::String& startSymbol();

    /** Add a new rule
     *  @param rule The new rule description
     */
    void newRule( const RuleDescription& rule );

    /** Get the current rule
     *  @return Reference to the current rule
     */
    RuleDescription& curRule();

    /** Append a new action description
     *  @param action The action to append
     */
    void appendAction( const ActionDescription& action );

    /** Initialize the grammar
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool initGrammar();

    /** Parse the grammar
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool parseGrammar( Grammar*      grammar,
                              const BAS::String& grammarFileName,
                              const BAS::String& grammarText );

    /** Increment the action number
     */
    void incActionNum();

    /** Get the current action number
     *  @return The current action number
     */
    int actionNum();

	int parse(void *);
	
	int yylex(BAS::String*);
    
    //@}

  private:
	void switchToIScriptMode(bool flag);
	void initGrammarLexer(const BAS::String& fileName, 
						  std::stringstream* str);

    // class members
    BAS::String                                 failureM;
    BAS::String                                 startSymbolM;
    BAS::StringList                             nonTerminalsM;
    RWTValOrderedVector<RuleDescription>   rulesM;
    RWTValOrderedVector<ActionDescription> actionsM;
    RWTValOrderedVector<EDR::Parameter>         parameterStackM;
    Grammar*                               curGrammarM;
    BAS::String                                 iScriptSourceM;
    int                                        actionNumM;

	std::stringstream strM;
	int         lineNumberM;
	BAS::String  fileNameM;
	BAS::String  parse_bufferM;
	bool        switchToIScriptModeM;
	BAS::String  iScriptBufferM;
	int         braceLevelM;
};

//==============================================================================
// Get the failure description
//==============================================================================
inline const BAS::String&
DescrParser::failure()
{
  return failureM;
}

//==============================================================================
// Append new iScript source
//==============================================================================
inline void
DescrParser::appendIScriptSource( const BAS::String& source )
{
  iScriptSourceM.append( source );
}

//==============================================================================
// Get the number of non-terminal symbols
//==============================================================================
inline size_t
DescrParser::numNonTerminals()
{
  return nonTerminalsM.entries();
}

//==============================================================================
// Add a new non-terminal symbol
//==============================================================================
inline void
DescrParser::addNonTerminal( const BAS::String& name )
{
  nonTerminalsM.append( name );
}

//==============================================================================
// Get a non-terminal symbol name
//==============================================================================
inline const BAS::String&
DescrParser::nonTerminal( size_t idx )
{
  return nonTerminalsM(idx);
}

//==============================================================================
// Set the start symbol
//==============================================================================
inline void
DescrParser::startSymbol( const BAS::String& name )
{
  startSymbolM = name;
}

//==============================================================================
// Get the start symbol name
//==============================================================================
inline const BAS::String&
DescrParser::startSymbol()
{
  return startSymbolM;
}

//==============================================================================
// Add a new rule
//==============================================================================
inline void
DescrParser::newRule( const RuleDescription& rule )
{
  rulesM.append( rule );
}

//==============================================================================
// Get the current rule
//==============================================================================
inline RuleDescription&
DescrParser::curRule()
{
  return rulesM( rulesM.entries()-1 );
}

//==============================================================================
// Append a new action
//==============================================================================
inline void
DescrParser::appendAction( const ActionDescription& action )
{
  actionsM.append( action );
}

//==============================================================================
// Increment the action number
//==============================================================================
inline void
DescrParser::incActionNum()
{
  actionNumM++;
}

//==============================================================================
// Get the action number
//==============================================================================
inline int
DescrParser::actionNum()
{
  return actionNumM;
}

inline void 
DescrParser::initGrammarLexer(const BAS::String& fileName,
							  std::stringstream* str)
{
	fileNameM = fileName;
	yyrestart(str);
}
inline void 
DescrParser::switchToIScriptMode( bool flag )
{
	D_ENTER( "LRP_Lexer::switchToIScriptMode(bool)" );
	switchToIScriptModeM = flag;
}

}
inline int LRP_FlexLexer::yylex(YYARG)
{
	return 0;
}

#endif // DESCRPARSER_HPP
