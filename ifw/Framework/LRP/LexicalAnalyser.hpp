#ifndef LRP_LEXICALANALYSER_HPP
#define LRP_LEXICALANALYSER_HPP
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
//   Declaration of the class LexicalAnalyser
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
// $RCSfile: LexicalAnalyser.hpp,v $
// $Revision: 1.11 $
// $Author: sd $
// $Date: 2001/07/03 11:49:58 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: LexicalAnalyser.hpp,v $
// Revision 1.11  2001/07/03 11:49:58  sd
// - PETS #36641 - ASN.1 enhancements for Swisscom
//
// Revision 1.10  2001/06/21 14:37:14  sd
// - new function writeOnReject()
//
// Revision 1.9  2001/06/21 10:17:38  sd
// - FRM::FileDescr renamed to FRM::StreamDescr
//
// Revision 1.8  2001/04/12 11:15:46  sd
// - Parts of LRP moved to FRM::Base
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif

#ifndef   LRP_ENDOFSYMBOLINFO_HPP
  #include "LRP/EndOfSymbolInfo.hpp"
#endif
#ifndef   LRP_LEXERSTATE_HPP
  #include "LRP/LexerState.hpp"
#endif

namespace EDR
{
class Token;
}
namespace FRM
{
class DataDescr;
}
namespace LRP
{
class FileBuffer;

/** <b><tt>LexicalAnalyser</tt></b> is the lexical analyser for the
 *  recognition of the different record types inside a cdr file.
 */
class LexicalAnalyser D_THREADINFO
{
  D_SINGLETHREADED

  public:
    /**@name LexicalAnalyser constructors and destructor */
    //@{

    /** Constructor
     *  @param dataDescr Pointer to the file data description
     */
    LexicalAnalyser( FRM::DataDescr* dataDescr );

    /** Destructor
     */
    ~LexicalAnalyser();

    //@}

    /**@name LexicalAnalyser public methods */
    //@{

    /** Check whether the analyser is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    bool isValid() const;

    /** Set the current lexer state
     *  @param id The id of the new current lexer state
     */
    void currentLexerState( size_t id );

    /** Process the data read from file buffer
     *  @param fileBuffer The file buffer to read from
     *  @param toke Reference to token pointer for returning the result
     *  @return <b>true</b> if there are some more tokens, <b>false</b> on EOF
     */
    bool process( FileBuffer& fileBuffer,
                  EDR::Token*&     token );

    /** Reset the lexical analyser to the initial state
     */
    void reset();

    /** Get the id for a lexer state name
     *  @param name The name of the lexer state
     *  @return Id >= on success, < 0 otherwise
     */
    int idForLexerState( const BAS::String& name ) const;

    /** Get the pointer to the data description
     *  @return Pointer to the data description
     */
    FRM::DataDescr* dataDescr() const;

    /** Get the failure string in case of error
     *  @return Reference to the failure string
     */
    const BAS::String& failure() const;

    /** Set the writeOnReject flag for the tokens read by the parser
     *  @param flag The new write on reject flag
     */
    void writeOnReject( bool flag );

    //@}

  protected:
    
    /* Set the failure string (is only used by the parser)
     * @param failure The new failure string
     */
    void failure( const BAS::String& failure );

    /* Initialize the lexical analyser
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init();

    /* Push a state on the state stack
     * @param state The state to push
     */
    void pushState( LexerState* state );

    /* Pop a state from the state stack
     * @return Pointer to popped state on success, 0 otherwise
     */
    LexerState* popState();

    /* Do a state transition
     * @param transition The transition to execute
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool stateTransition( const FRM::StateTransition* transition );

  private:

    // instance members
    bool                                     isValidM;
    BAS::String                               failureM;
    FRM::DataDescr*                           dataDescrM;
    LexerState*                          currentLexerStateM;
    size_t                                   currentPositionM;
    RWTPtrOrderedVector<LexerState>      lexerStatesM;
    RWTPtrOrderedVector<LexerState>      stateStackM;
    RWTValOrderedVector<EndOfSymbolInfo> endOfSymbolStackM;
    bool                                     writeOnRejectM;
};

//==============================================================================
// Set the current lexer state
//==============================================================================
inline void
LexicalAnalyser::currentLexerState( size_t id )
{
  RWPRECONDITION( id < lexerStatesM.entries() );
  currentLexerStateM = lexerStatesM(id);
}

//==============================================================================
// Check whether the analyser is valid or not
//==============================================================================
inline bool
LexicalAnalyser::isValid() const
{
  return isValidM;
}

//==============================================================================
// Get the pointer to the data description
//==============================================================================
inline FRM::DataDescr*
LexicalAnalyser::dataDescr() const
{
  return dataDescrM;
}

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
LexicalAnalyser::failure() const
{
  return failureM; 
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
LexicalAnalyser::failure( const BAS::String& failure )
{
  failureM = failure; 
}

//==============================================================================
// Set the write on reject flag 
//==============================================================================
inline void
LexicalAnalyser::writeOnReject( bool flag )
{
  writeOnRejectM = flag;
}

//==============================================================================
// Push a state on the stack
//==============================================================================
inline void
LexicalAnalyser::pushState( LexerState* state )
{
  stateStackM.append( state );
}

//==============================================================================
// Pop a state for the stack
//==============================================================================
inline LexerState*
LexicalAnalyser::popState() 
{
  if ( stateStackM.entries() > 0 )
  {
    return stateStackM.removeLast();
  }
  else
  {
    return 0;
  }
}
}
#endif // LEXICANALYSER_HPP
