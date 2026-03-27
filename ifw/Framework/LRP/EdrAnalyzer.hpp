#ifndef LRP_EDRANALYZER_HPP
#define LRP_EDRANALYZER_HPP
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
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrAnalyzer.
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
// $RCSfile: EdrAnalyzer.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2001/03/07 10:13:35 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrAnalyzer.hpp,v $
// Revision 1.2  2001/03/07 10:13:35  sd
// - Backup version
//
// Revision 1.1  2001/02/22 12:04:03  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif

namespace EDR
{
class Container;
}
namespace LRP
{

/** <b><tt>EdrAnalyzer</tt></b>
 */
class EdrAnalyzer D_THREADINFO
{
  D_SINGLETHREADED

  public:

    /**@name EdrAnalyzer constructors and destructor */
    //@{

    /** Constructor
     */
    EdrAnalyzer();

    /** Destructor
     */
    ~EdrAnalyzer();

    //@}

    /**@name EdrAnalyzer public methods */
    //@{

    /** Evaluate the symbol id for an EDR container
     *  @param edr The EDR container to process
     *  @param symbolId Return buffer for the evaluated symbol
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool process( EDR::Container* edr,
                  size_t&        symbolId );

    /** Get a list with all symbol names
     *  @return List with all symbol names
     */
    BAS::StringList symbols() const;

    /** Set the symbol id for a symbol name
     *  @param symbol The name of the symbol
     *  @param id The id for the symbol
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setSymbolId( const BAS::String& name,
                      size_t            id );

    //@}

  private:

    struct SymbolT
    {
        SymbolT() 
        {
          symbolIdM   = 0;
          symbolNameM = "";
        }
        
        SymbolT( const BAS::String& sym )
        {
          symbolIdM   = 0;
          symbolNameM = sym;
        }

        BAS::String symbolNameM;
        size_t     symbolIdM;
    };

    // instance members
    RWTValOrderedVector<SymbolT> symbolsM;
};
}
#endif // EDRANALYZER_HPP
