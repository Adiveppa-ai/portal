#ifndef LRP_GRAMMAR_HPP
#define LRP_GRAMMAR_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2023 Oracle. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Grammar contains all rules and symbols of a grammar.
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
// $RCSfile: Grammar.hpp,v $
// $Revision: 1.10 $
// $Author: sd $
// $Date: 2001/10/12 15:07:22 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Grammar.hpp,v $
// Revision 1.10  2001/10/12 15:07:22  sd
// - PETS #36559 SourcePro AIX port (bug removed)
//
// Revision 1.9  2001/08/10 12:35:09  mliebmann
// PETS #36559 SourcePro AIX port
//
// Revision 1.8  2001/04/05 09:28:24  sd
// - Backup version
//
// Revision 1.7  2001/03/07 14:01:08  sd
// - New class DescrParser introduced
//
// Revision 1.6  2001/02/26 15:07:12  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef   RW_TOOLS_TVSRTVEC_H
  #include <rw/tvsrtvec.h>
#endif
#ifndef   RW_TOOLS_TPSRTVEC_H
  #include <rw/tpsrtvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   QUEUE_HPP
  #include "STR/Queue.hpp"
#endif
#ifndef   LRP_SYMBOL_HPP
  #include "LRP/Symbol.hpp"
#endif
#ifndef   LRP_PRODUCTION_HPP
  #include "LRP/Production.hpp"
#endif
#ifndef   LRP_ITEM_HPP
  #include "LRP/Item.hpp"
#endif
#ifndef   LRP_STATE_HPP
  #include "LRP/State.hpp"
#endif

#ifndef LRP_DESCRPARSER_HPP
#define YYSTYPE BAS::String
#define YYARG YYSTYPE* lvalp

#undef yyFlexLexer
#define yyFlexLexer LRP_FlexLexer
#include "FlexLexer.h"
#include "DescrParser.hpp"
#endif


namespace EDR
{
class Container;
}
namespace LRP
{
class Parser;

//==============================================================================
// These typedefs are made for better understanding of the algorithms
//==============================================================================
typedef RWTValSortedVector<int,less<int> > FirstSet;
typedef RWTValSortedVector<int,less<int> > FollowSet;


/** <b><tt>Grammar</tt></b> contains all symboles and rules of the grammar
 *  and is able to create a Parser object for this grammar.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Grammar.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.10 $</font></td>
 *  <td><font size=-1>$Date: 2001/10/12 15:07:22 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class Grammar D_THREADINFO
{
  public:
    /**@name Grammar constructors and destructor */
    //@{

    /** Constructor
     *  @param terminals List with all terminal symbols
     *  @param grammarDescrFileName File name for the grammar description file
     *  @param debugFile The name of the grammar debug file
     */
    Grammar( const BAS::StringList& terminals,
                 const BAS::String&     grammarDescrFileName,
                 const BAS::String&     debugFile );

    /** Constructor
     *  @param terminals List with all terminal symbols
     *  @param grammarDescrFileName File name for the grammar description file
     *  @param grammarDescrText Contents of the grammar description
     *  @param debugFile The name of the grammar debug file
     */
    Grammar( const BAS::StringList& terminals,
                 const BAS::String& grammarDescrFileName,
                 const BAS::String& grammarDescrText,
                 const BAS::String& debugFile );

    /** Destructor
     */
    virtual ~Grammar();

    //@}

    /**@name Grammar public methods */
    //@{

    /** Check if the grammar is valid
     *  @return <b>true</b> if the grammar is valid, <b>false</b> otherwise
     */
    bool isValid() const;

    /** Check if the grammar is alread initialized
     *  @return <b>true</b> if grammar is initialized, <b>false</b> otherwise
     */
    bool isInitialized() const;

    /** Add a new production to the grammar 
     *  @param leftSide The left side symbol of the production rule
     *  @param rightSide The right side symbols of the production rule
     *  @param reduceAction The action to execute on reduce
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addProduction( const BAS::String&     leftSide,
                        const BAS::StringList& rightSide,
                        const BAS::String&     reduceAction );

    /** Get the id for a symbol
     *  @param name The name of the symbol
     *  @return id for symbol (>= 0) on success, -1 otherwise
     */
    int symbolId( const BAS::String& name ) const;

    /** Get the id for an unqualified symbol
     *  @param name The name of the symbol
     *  @param numPossibleSymbols Return buffer for the number of possible 
     *         symbols
     *  @return id for symbol (>= 0) on success, -1 otherwise
     */
    int unqualifiedSymbolId( const BAS::String& name,
                             size_t&           numPossibleSymbols ) const;

    /** Get the failure string
     *  @return Reference to the failure string
     */
    const BAS::String& failure() const;

    /* Get the name for a symbol id
     * @param id The id of the symbol
     */
    const BAS::String& symbolName( int id ) const; 

    //@}

  protected:

    /* Initialize the grammar with value from the description files
     * @param startSymbol Name of the start symbol
     * @param nonTerminals Vector with non-terminal symbols
     * @param iScriptActions iScript source with actions to execute
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const BAS::String&     startSymbol,
               const BAS::StringList& nonTerminals,
               const BAS::String&     iScriptActions );

    /* Initialize a parser
     * @param parser The parser to initialize
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool initParser( Parser* parser );

    /* Prepare the initialization of the parser
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool prepareForParserGeneration();

    /* Set the isValid flag of the grammar
     * @param flag The new isValid flag
     */
    void isValid( bool flag );

    /* Set the failure string
     * @param failure The new failure string
     */
    void failure( const BAS::String& failure );

    /* Check if the symbol id is a terminal symbol id 
     * @return <b>true</b> if terminal id, <b>false</b> otherwise
     */
    bool isTerminalId( int id ) const;

    /* Check if the symbol id is a non-terminal symbol id 
     * @return <b>true</b> if non-terminal id, <b>false</b> otherwise
     */
    bool isNonTerminalId( int id ) const;

    /* Create the first sets for the different symbols
     */
    void createSymbolFirstSets();

    /* Calcultate the derives sentence flag for all the symbols
     */
    void calculateDerivesSentence();

    /* Calculate the is reachable flag for all the symbols
     */
    void calculateIsReachable();

    /* Create the parser states
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool createParserStates();

    /* Get all productions with specified non-terminal symbol on left side
     * @param symbolId The id of the non-terminal symbol on left side of rule
     * @return A vector with all rules for this symbol
     */
    ProductionVector productionsForSymbol( int symbolId ) const;

    /* Get all possible successor symbols for a state
     * @param state The state for which to calculate the possible successors
     * @return The possible successor symbols
     */
    SymbolSet possibleSuccSymbolsForState( const State& state ) const;

    /* Calculate the closure for a set of items
     * @param inputSet The set for which to calculate the closure
     * @return A set of item ids
     */
    ItemSet closure( const ItemSet& inputSet );

    /* Calculate the first set for a string
     * @param string The string for which to calculate the first set
     * @return The first set for the string
     */
    FirstSet first( const String& string );

    /* Calculate the follow set for a non-terminal symbol
     * @param nonTerminalId Symbol for which to calculate the follow set
     * @return The follow set for the non-terminal symbol
     */
    FollowSet follow( int nonTerminalId );

    /* Calculate the goto set for a symbol and an item set
     * @param symbolId The input symbol
     * @param itemSet The input item set
     * @return The calculated goto-set of items
     */
    ItemSet gotoset( int symbolId, const ItemSet& itemSet );

    /* Get a string for a set of symbol ids 
     * @return String with symbol names
     */
    BAS::String symbolSetString( 
      const RWTValSortedVector<int,less<int> >& set ) const;

    /* Get a item by it's id
     * @param id The id of the item
     * @return Pointer to item on success, 0 otherwise
     */
    Item* getItemById( int id ) const;

    /* Get a id for the item. If the item does not already exist, it will
     * be inserted in the itemMap automatically
     * @param item The item for which to get the id
     * @return The id of the item
     */
    int getIdForItem( const Item& item );

    /* Get a state by it's id
     * @param id The id of the state
     * @return Pointer to state on success, 0 otherwise
     */
    State* getStateById( int id ) const;

    /* Get a id for the state. If the state does not already exist, it will
     * be inserted in the stateMap automatically
     * @param state The state for which to get the id
     * @return The id of the state
     */
    int getIdForState( const State& state );

    /* Get the description string for an item
     * @param item The item to get the description for
     * @return The description string
     */
    BAS::String stringForItem( const Item& item ) const;

    /* Get the description string for a production
     * @param production The production to get the description for
     * @return The description string
     */
    BAS::String stringForProduction( const Production& production ) const;

    /* Get a BAS::String for a symbol string 
     * @return String with symbol names
     */
    BAS::String symbolString( const String& string ) const;

    /* Print a paser state
     * @param os The output stream
     * @param state The state to print
     */
    void printState( std::ostream& os, State& state ) const;

    /* Print the entire grammar
     * @param os The output stream
     */
    void printGrammar( std::ostream& os ) const;

  protected:

    // instance members
    bool                                     isValidM;
    bool                                     isInitializedM;
    SymbolVector                         symbolsM;
    ProductionVector                     productionsM;
    RWTValOrderedVector<FirstSet>        symbolFirstSetsM;
    RWTPtrOrderedVector<Item>            itemVectorM;
    RWTPtrMap<Item,Item,Item>    itemMapM;
    RWTPtrMap<State,State,State> stateMapM;
    RWTPtrOrderedVector<State>           stateVectorM;
    int                                      epsilonIdM;
    int                                      startSymbolIdM;
    BAS::String                               startSymbolM;
    int                                      eofSymbolIdM;
    BAS::String                               eofSymbolM;
    BAS::String                               iScriptSourceM;
    BAS::String                               failureM;
    int                                      numShiftReduceConflictsM;
    int                                      numShiftShiftConflictsM;
    int                                      numReduceReduceConflictsM;
    BAS::String                               debugFileM;
    
    // friends
    friend class DescrParser;

	DescrParser parserM;

  private:
    // Hide copy constructor and assignment operator
    Grammar( const Grammar& other );
    const Grammar& operator=( const Grammar& other );
};

//==============================================================================
// Check if the grammar is valid
//==============================================================================
inline bool 
Grammar::isValid() const
{
  return isValidM;
}

//==============================================================================
// Set the isValid flag
//==============================================================================
inline void
Grammar::isValid( bool flag )
{
  isValidM = flag;
}

//==============================================================================
// Check if the grammar is initialized
//==============================================================================
inline bool 
Grammar::isInitialized() const
{
  return isInitializedM;
}

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
Grammar::failure() const
{
  return failureM;
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
Grammar::failure( const BAS::String& failure )
{
  failureM = failure;
}
}
#endif // GRAMMAR_HPP
