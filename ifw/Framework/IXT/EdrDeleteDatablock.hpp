#ifndef IXT_EDRDELETEDATABLOCK_HPP
#define IXT_EDRDELETEDATABLOCK_HPP

//==============================================================================
//
//   Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//   
//   This material is the confidential property of Oracle Corporation or its
//   licensors and may be used, reproduced, stored or transmitted only in
//   accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrDeleteDatablock
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Mike Ammon
//------------------------------------------------------------------------------
// Revision 1.1  2003/08/97 ammon
// PRSF00050427: Add NameSpaces.
//
// Revision 1.0  2003/06/23 ammon
// PRSF00046970: Add function for deleting datablocks.
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
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

/**<b><tt>EdrDeleteDatablock</tt></b> is the function class for deleting
 * datablocks from the edr container.
 */
class EdrDeleteDatablock : public SCR::BoolNode
{
  public:
    /**@name EdrDeleteDatablock constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrDeleteDatablock();

    //@

    /**@name EdrDeleteDatablock public methods */
    //@{

    /** Check if edr field is valid
     */
    bool isValid() const;

    /** Delete the datablock
     *  @return true on success, false otherwise
     */
    virtual bool result();

    /** Factory for deleting an edr datablock
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
    EdrDeleteDatablock( Integrate* extension );

    /** Initialize the function node
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const BAS::String&                  blockName,
               RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector );

  private:
    // Hide default and copy constructor
    EdrDeleteDatablock();
    EdrDeleteDatablock( const EdrDeleteDatablock& other );
    const EdrDeleteDatablock& operator=( const EdrDeleteDatablock& other );

    // instance members
    Integrate*                         extensionM;
    EDR::BlockIndex                    blockIdxM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};
}

#endif // IXT_EDRDELETEDATABLOCK_HPP
