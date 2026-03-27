#ifndef LRP_PRODUCTION_HPP
#define LRP_PRODUCTION_HPP

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
//   Declaration of the class Production. This class is used to store the
//   production rules in the grammar.
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
// $RCSfile: Production.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/11/21 12:50:37 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Production.hpp,v $
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace LRP
{
typedef RWTValOrderedVector<int> String;

/** <b><tt>Production</tt></b> is used to store the production rules in
 *  the grammar.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Production.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2000/11/21 12:50:37 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class Production D_THREADINFO
{
  public:
    /**@name Production constructors and destructor */
    //@{

    /** Constructor
     *  @param leftSide The Id of the production's left side symbol
     *  @param action The action to execute on reduce
     */
    Production( int               leftSide,
                    const BAS::String& reduceAction );

    /** Destructor
     */
    ~Production();

    //@}


    /**@name Production public methods */
    //@{

    /** Set the production id
     *  @param The id
     */
    void productionId( int id );

    /** Get the production id
     *  @return The id
     */
    int productionId() const;

    /** Append a new id to the right side of the production
     *  @param rightSideId The id to append
     *  @param action The action to execute 
     */
    void append( int rightSide );

    /** Get the number of symbols on the right side of the production
     *  @return The number of symbols on the right side of the rule
     */
    size_t numRightSideSymbols() const;

    /** Get a right side symbol id
     *  @return The symbol id on success, -1 otherwise
     */
    int rightSide( size_t pos ) const;

    /** Get the action for a right side symbol
     *  @param pos The index of the action
     *  @return The action to execute
     */
    const BAS::String& action( size_t pos ) const;

    /** Get the left side symbol id
     *  @return The symbol id 
     */
    int leftSide() const;

    /** Get the right side string
     *  @return The string on the right side of the production
     */
    const String& rightSideString() const;

    /** Get the right side partstring starting at specified index
     *  @param index The startindex for the partstring
     *  @return The partstring
     */
    String rightSideStringFrom( int index ) const;

    /** Get the action to execute if the production is reduced
     *  @return Reference to instance member
     */
    const BAS::String& reduceAction() const;

    /** Check if the right side of the production contains symbol
     *  @param symbolId The id of the symbol to search for
     *  @param startIdx The start index for the search
     *  @return The symbol index if found, -1 otherwise
     */
    int rightSideIndex( int symbolId,
                        int startIdx ) const;

    //@}

#ifdef __aix
    bool operator==( const Production& other ) const
    {
      return( this == &other );
    }
    bool operator<( const Production& other ) const
    {
      return( this < &other );
    }
#endif

  private:

    // instance members
    int            leftSideM;
    int            productionIdM;
    String     rightSideM;
    BAS::String     reduceActionM;
};

typedef RWTPtrOrderedVector<Production> ProductionVector;

//==============================================================================
// Get the production id
//==============================================================================
inline int
Production::productionId() const
{
  return productionIdM;
}

//==============================================================================
// Set the production id
//==============================================================================
inline void
Production::productionId( int id )
{
  productionIdM = id;
}

//==============================================================================
// Get the reduct action
//==============================================================================
inline const BAS::String&
Production::reduceAction() const
{
  return reduceActionM;
}
}
#endif // PRODUCTION_HPP
