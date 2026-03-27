#ifndef DAT_PREFIXSEARCH_HPP
#define DAT_PREFIXSEARCH_HPP

//==============================================================================
//
//      @(#)%Portal Version: PrefixSearch.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:39:31 %
//      
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: DAT::PrefixDesc
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the function node for the function prefixSearch().
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
// $RCSfile: PrefixSearch.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2000/09/19 10:50:32 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: PrefixSearch.hpp,v $
// Revision 1.1  2000/09/19 10:50:32  sd
// - Initial revision of the iScript extension.
//
//==============================================================================

#include "SCR/Node.hpp"

// Forward declaration
namespace SCR {
  class FctDescr;
  class Interpreter;
  class ParserStack;
  class StringDataNode;
}

namespace DAT
{
namespace PrefixDesc
{

class PrefixIScriptExt;

/** <b><tt>PrefixSearch</tt></b> is the iScript function node for 
 *  searching prefix data.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: PrefixSearch.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2000/09/19 10:50:32 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class PrefixSearch : public SCR::BoolNode
{
  public:
    /**@name PrefixSearch constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~PrefixSearch();

    //@}

    /**@name PrefixSearch public methods */
    //@{

    /** Execute the prefixSearch() function
     */
    virtual bool result();
    
    /** Create a prefixSearch() function 
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
    PrefixSearch( PrefixIScriptExt* prefixExtension,
                  SCR::StringNode*       cliNode,
                  SCR::StringDataNode*   prefixDataNode,
                  SCR::StringDataNode*   descripitionDataNode );

  private:
    // hide default and copy constructor
    PrefixSearch();
    PrefixSearch( const PrefixSearch& other );
    const PrefixSearch& operator=( const PrefixSearch& other );

    // instance members
    PrefixIScriptExt* prefixExtensionM;
    SCR::StringNode*       cliNodeM;
    SCR::StringDataNode*   prefixDataNodeM;
    SCR::StringDataNode*   descriptionDataNodeM;

    BAS::String            prefixM;
    BAS::String            descriptionM;
};

} // namespace PrefixDesc
} // namespace DAT

#endif // DAT_PREFIXSEARCH_HPP
