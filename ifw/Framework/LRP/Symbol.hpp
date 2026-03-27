#ifndef LRP_SYMBOL_HPP
#define LRP_SYMBOL_HPP

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
//   Symbol is the class for symbols used in the grammar.
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
// $RCSfile: Symbol.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/11/21 12:50:37 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Symbol.hpp,v $
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   RW_TOOLS_TVSRTVEC_H
  #include <rw/tvsrtvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace LRP
{
/** <b><tt>Symbol</tt></b> is the class for storing symbols used in the
 *  grammar.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Symbol.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2000/11/21 12:50:37 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class Symbol D_THREADINFO
{
  public:
    /**@name Symbol constructors and destructor */
    //@{

    /** Constructor
     *  @param name The symbol name
     *  @param isTerminal Boolean if symbol is a terminal symbol
     */
    Symbol( const BAS::String& name,
                bool              isTerminal );

    /** Destructor
     */
    virtual ~Symbol();

    //@}

    /**@name Symbol public methods */
    //@{

    /** Get the name of the symbol
     *  @return reference to the symbol name
     */
    const BAS::String& name() const;

    /** Check if the symbol is a terminal symbol
     *  @return <b>true</b> if terminal symbol, <b>false</b> otherwise
     */
    bool isTerminal() const;

    /** Set the isReachable flag
     *  @param flag The new flag
     */
    void isReachable( bool flag );

    /** Get the isReachable flag
     *  @return The isReachable flag
     */
    bool isReachable() const;

    /** Set the derives sentence flag
     *  @param flag The new flag
     */
    void derivesSentence( bool flag );

    /** Get the derives sentence flag
     *  @return The flag if the symbol derives a sentence
     */
    bool derivesSentence() const;

    //@}

#ifdef __aix
    bool operator==( const Symbol& other ) const
    {
      return( this == &other );
    }
    bool operator<( const Symbol& other ) const
    {
      return( this < &other );
    }
#endif

  private:
    BAS::String nameM;
    bool       isTerminalM;
    bool       isReachableM;
    bool       derivesSentenceM;
};

typedef RWTPtrOrderedVector<Symbol>    SymbolVector;
typedef RWTValSortedVector<int,less<int> > SymbolSet;

//==============================================================================
// Get the name of the symbol
//==============================================================================
inline const BAS::String& 
Symbol::name() const
{
  return nameM;
}

//==============================================================================
// Check if the symbol is a terminal symbol
//==============================================================================
inline bool
Symbol::isTerminal() const
{
  return isTerminalM;
}

//==============================================================================
// Set the isReachable flag
//==============================================================================
inline void
Symbol::isReachable( bool flag )
{
  isReachableM = flag;
}

//==============================================================================
// Get the isReachable flag
//==============================================================================
inline bool
Symbol::isReachable() const
{
  return isReachableM;
}

//==============================================================================
// Set the derivesSentence flag
//==============================================================================
inline void
Symbol::derivesSentence( bool flag )
{
  derivesSentenceM = flag;
}

//==============================================================================
// Get the derivesSentence flag
//==============================================================================
inline bool
Symbol::derivesSentence() const
{
  return derivesSentenceM;
}
}
#endif // SYMBOL_HPP
