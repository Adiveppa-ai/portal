#ifndef LRP_PARSER_HPP
#define LRP_PARSER_HPP

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
//   Definition of the LR(1)-Parser class.
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
// $RCSfile: Parser.hpp,v $
// $Revision: 1.15 $
// $Author: cdiab $
// $Date: 2001/11/21 11:56:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Parser.hpp,v $
// Revision 1.16  2002/05/28 15:56:48  cdiab
// Added a callback to the grammar for onRollback processing
//
// Revision 1.15  2001/11/21 11:56:48  cdiab
// PETS #41920 : add a callback to the grammar for error processing
// Added a callback from the input parser to the input grammar through a
// function named onParseError(), providing the following variables:
// ERROR_TOKEN_ASC, ERROR_TOKEN_HEX, ERROR_TOKEN_HEXARRAY, ERROR_TOKEN_BYTEPOS
//
// Revision 1.14  2001/09/26 06:58:52  sd
// - PETS #38714 EXT_OutFileManager: empty outputfile not deleted
//
// Revision 1.13  2001/09/15 22:10:58  sd
// - PETS 37618 Warnings removed
//
// Revision 1.12  2001/06/27 06:56:55  sd
// - New interface for the output device.
//
// Revision 1.11  2001/04/12 12:21:47  sd
// - Update for splitting LRP/FRM::Base
//
// Revision 1.10  2001/04/03 08:15:30  sd
// - Full iScript support
//
// Revision 1.9  2001/03/19 16:12:31  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#if !defined LRP_EXPORT
  #if defined(WINDOWS)
    #if !defined(LRP_INTERNAL)
      #define LRP_EXPORT __declspec(dllimport)
    #else
      #define LRP_EXPORT __declspec(dllexport)
    #endif
  #else
    #define LRP_EXPORT 
  #endif
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   SCR_LOG_HPP
  #include "SCR/Log.hpp"
#endif
#ifndef   SCR_INTERPRETER_HPP
  #include "SCR/Interpreter.hpp"
#endif
#ifndef   LRP_TRANSITION_HPP
  #include "LRP/Transition.hpp"
#endif
#ifndef   IXT_INTERPRETER_HPP
  #include "IXT/Interpreter.hpp"
#endif

namespace EDR
{
class Factory;
}
namespace LRP
{
class FileBuffer;
class Grammar;

/** <b><tt>Parser</tt></b> is the LR(1)-Parser class.
 */
class Parser D_THREADINFO
{
  D_SINGLETHREADED

  public:
    
    typedef enum
    {
      GOON,
      ACCEPT,
      ERROR,
      INTERNAL_ERROR
    } ParserResult;

    /**@name Parser constructors and destructor */
    //@{

    /** Constructor
     *  @param interpreterName The registry name of the iScript interpreter
     */
    Parser( const BAS::String& interpreterName );

    /** Destructor
     */
    virtual ~Parser();

    //@}

    /**@name Parser public methods */
    //@{

    /** Get the failure string
     *  @return Reference to the internal failure string
     */
    const BAS::String& failure() const;

    /** Reset the parser to it's state after construction
     */
    void reset();
    
    /** Get the isValid flag
     *  @return The isValid flag
     */
    bool isValid() const;

    /** Get the divideByTwo flag
     *  @return The divideByTwo flag
     */
    bool divideByTwo() const;

    /** Get the reference to the interpreter used in the parser
     *  @return Reference to interpreter
     */
    IXT::Interpreter& interpreter();

    /** Give back the hand to the grammar for in case of Rollback.
     *  @return <b>false</b> if onRollback() is programmed on the grammar but
     *                       did not execute correctly
     *          <b>true</b>  otherwise
     */
    bool onRollbackCallback(const TAM::TransId*       transId,
                            const TAM::TransItemList* transItemList);

     bool readRegistry();

    //@}

  protected:

    /** Set the isValid flag
     *  @param flag The new isValid flag
     */
    void isValid( bool flag );

    /** Set the divideByTwo flag
     *  @param flag The new divideByTwo flag
     */
    void divideByTwo( bool flag );

    /** Set the failure string
     *  @param msg The new failure string
     */
    void failure( const BAS::String& msg );

    /** Set the failure string for a conflict
     *  @param newTransition The old transition
     *  @param oldTransition The conflicting new transition
     *  @param state State where the conflict occured
     *  @param symbol Symbol for which the conflict occured
     */
    void conflict( Transition::TransitionType newTransition,
                   Transition::TransitionType oldTransition,
                   size_t                         state,
                   size_t                         symbol );

    /** Set the failure string for an unexpected symbol
     *  @param symbol Symbol The unexpected symbol
     */
    void unexpectedSymbol( size_t symbol );

    /** Initialize the parser with data from the grammar
     *  @param startSymbol The start symbol for the parser stack
     *  @param eofSymbol The eof symbol for the parser stack
     *  @param acceptState The accept state for the parser
     *  @param numSymbols Number of symbols
     *  @param numStates Number of parser states
     *  @param iScriptSource The iScript source code with actions to execute
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( size_t                     startSymbol,
               size_t                     eofSymbol,
               size_t                     acceptState,
               size_t                     numSymbols,
               size_t                     numStates,
               const BAS::StringList&      symbolNames,
               const BAS::String&          iScriptSource );
    

    /** Get the End-Of-File symbol
     *  @return The End-Of-File symbol
     */
    size_t eofSymbol() const;

    /** Process a symbol
     *  @param symbol The symbol to process
     */
    ParserResult processSymbol( size_t symbol );

    /** Give back the hand to the grammar for Error handeling.
     *  @return <b>true</b>  if error handeling is programmed on the grammar
     *          <b>false</b> otherwise
     */
    bool onParseErrorCallback( );

	/** Function to be called when the parsing is finished
	 */
	void onParseEnd( );


  protected:
    /* Add a GOTO transition to the parser
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addGoto( size_t state,
                  size_t symbol,
                  size_t succState );

    /* Add a SHIFT transition to the parser
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addShift( size_t state,
                   size_t symbol,
                   size_t succState );

    /* Add a REDUCE transition to the parser
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addReduce( size_t            state,
                    size_t            symbol,
                    size_t            numPops,
                    size_t            pushSymbol,
                    const BAS::String& action );

    /* Get a transition by state and symbol
     * @param state
     * @param symbol
     * @return Pointer to transition
     */
    Transition* transition( size_t state,
                                size_t symbol ) const;

    /* Set a transition
     * @param state The state for the transition
     * @param symbol The symbol for the transition
     * @param transition The transition to set
     */
    void transition( size_t          state,
                     size_t          symbol,
                     Transition* transition );

    /* Push a symbol and a state on the stack
     * @param symbol The symbol to push onto the stack
     */
    bool push( size_t symbol, size_t state );

    /* Pop a number of symbols from the state and symbol stack
     * @param numSymbols The number of symbols to pop from the stack
     */
    bool pop( size_t numSymbols );

    /* Get the top of the state stack
     * @return The state stacks top state
     */
    size_t topState() const;

    /* Get the top of the symbol stack
     * @return The symbol stacks top symbol id
     */
    size_t topSymbol() const;

    /* Push a symbol on the stack
     */
    bool pushSymbol( size_t symbol );

    /* Push a state on the stack
     */
    bool pushState( size_t state );

    /* Print the contents of all stacks (for debug output)
     */
    void printStacks();

  private:

    // hide the copy constructor
    Parser( const Parser& other );
    const Parser& operator=( const Parser& other );


    LRP_EXPORT static const BAS::String  regParserDivideByTwoCM;

    bool divideByTwoM;
    
  protected:
    // instance members
    bool                 isValidM;
    bool                 isInitializedM;
    IXT::Interpreter      interpreterM;
    size_t               numSymbolsM;
    size_t               numStatesM;
    Transition**     transitionTableM;
    BAS::String           failureM;
    size_t               stackSizeM;
    size_t               symbolTopM;
    size_t*              symbolStackM;
    size_t               stateTopM;
    size_t*              stateStackM;
    size_t               startSymbolM;
    size_t               eofSymbolM;
    size_t               acceptStateM;
    BAS::StringList       symbolNamesM;
    
    RWMutexLock          mutexM;

    SCR::Function*        onParseStartFctM;
    SCR::Function*        onParseErrorFctM;
    SCR::Function*        onRollbackFctM;
    SCR::Function*        onParseEndFctM;

    friend class Grammar;

    // class members
    LRP_EXPORT static const BAS::String onParseStartNameCM;
    LRP_EXPORT static const BAS::String onParseErrorNameCM;
    LRP_EXPORT static const BAS::String onRollbackNameCM;
    LRP_EXPORT static const BAS::String onParseEndNameCM;
};

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
Parser::failure() const
{
  return failureM;
}

//==============================================================================
// Get a transition by state and  symbol
//==============================================================================
inline Transition* 
Parser::transition( size_t state, size_t symbol ) const
{
  RWPRECONDITION( state <= numStatesM );
  RWPRECONDITION( symbol < numSymbolsM );
  RWPRECONDITION( transitionTableM != 0 );
  return transitionTableM[ state*numSymbolsM + symbol ];
}

//==============================================================================
// Set a transition for state and symbol
//==============================================================================
inline void
Parser::transition( size_t state, size_t symbol, Transition* transition)
{
  RWPRECONDITION( state < numStatesM );
  RWPRECONDITION( symbol < numSymbolsM );
  RWPRECONDITION( transitionTableM != 0 );
  transitionTableM[ state*numSymbolsM + symbol ] = transition;
}

//==============================================================================
// Push a symbol and a state on the stack
//==============================================================================
inline bool
Parser::push( size_t symbol, size_t state )
{
  if ( symbolTopM < stackSizeM && stateTopM < stackSizeM )
  {
    stateStackM[stateTopM++]   = state;
    symbolStackM[symbolTopM++] = symbol;
    return true;
  }
  else
  {
    failureM = "stack overflow";
    return false;
  }
}

//==============================================================================
// Push a symbol on the stack
//==============================================================================
inline bool
Parser::pushSymbol( size_t symbol )
{
  if ( symbolTopM < stackSizeM )
  {
    symbolStackM[symbolTopM++] = symbol;
    return true;
  }
  else
  {
    failureM = "stack overflow";
    return false;
  }
}

//==============================================================================
// Push a state on the stack
//==============================================================================
inline bool
Parser::pushState( size_t state )
{
  if ( stateTopM < stackSizeM )
  {
    stateStackM[stateTopM++] = state;
    return true;
  }
  else
  {
    failureM = "stack overflow";
    return false;
  }
}

//==============================================================================
// Pop a number of symbols from the stack
//==============================================================================
inline bool
Parser::pop( size_t numPops )
{
  if ( symbolTopM >= numPops && stateTopM >= numPops )
  {
    symbolTopM -= numPops;
    stateTopM  -= numPops;
    return true;
  }
  else
  {
    failureM = "stack underflow";
    return false;
  }
}

//==============================================================================
// Get the top state
//==============================================================================
inline size_t
Parser::topState() const
{
  RWPRECONDITION( stateTopM > 0 );
  return stateStackM[stateTopM-1];
}

//==============================================================================
// Get the top symbol
//==============================================================================
inline size_t
Parser::topSymbol() const
{
  RWPRECONDITION( symbolTopM > 0 );
  return symbolStackM[symbolTopM-1];
}

//==============================================================================
// Get the End-Of-File symbol
//==============================================================================
inline size_t
Parser::eofSymbol() const
{
  return eofSymbolM;
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
Parser::failure( const BAS::String& msg )
{
  failureM = msg;
}

//==============================================================================
// Set the divideByTwo flag
//==============================================================================
inline void
Parser::divideByTwo( bool flag )
{
  divideByTwoM = flag;
}

//==============================================================================
// Get the divideByTwo flag
//==============================================================================
inline bool
Parser::divideByTwo() const
{
  return divideByTwoM;
}

//==============================================================================
// Set the isValid flag
//==============================================================================
inline void
Parser::isValid( bool flag )
{
  isValidM = flag;
}

//==============================================================================
// Get the isValid flag
//==============================================================================
inline bool
Parser::isValid() const
{
  return isValidM;
}

//==============================================================================
// Get the interpreter
//==============================================================================
inline IXT::Interpreter&
Parser::interpreter()
{
  return interpreterM;
}
}

#endif // PARSER_HPP
