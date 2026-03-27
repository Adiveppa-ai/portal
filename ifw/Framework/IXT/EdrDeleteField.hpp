#ifndef IXT_EDRDELETEFIELD_HPP
#define IXT_EDRDELETEFIELD_HPP

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
//   Declaration of the class EdrDeleteField
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
// Revision 1.1  2003/08/07 ammon
// PRSF00050427: Add Namespaces.
//
// Revision 1.0  2003/06/23 ammon
// PRSF00046970: Add function for deleting fields.
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
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

/**<b><tt>EdrDeleteField</tt></b> is the function class for deleting
 * fields from the edr container.
 */
class EdrDeleteField : public SCR::BoolNode
{
  public:
    /**@name EdrDeleteField constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrDeleteField();

    //@

    /**@name EdrDeleteField public methods */
    //@{

    /** Check if edr field is valid
     */
    bool isValid() const;

    /** Delete the field
     *  @return true on success, false otherwise
     */
    virtual bool result();

    /** Factory for deleting an edr field
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
    EdrDeleteField( Integrate* extension );

    /** Initialize the function node
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const BAS::String&                  fieldName,
               RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector );

  private:
    // Hide default and copy constructor
    EdrDeleteField();
    EdrDeleteField( const EdrDeleteField& other );
    const EdrDeleteField& operator=( const EdrDeleteField& other );

    // instance members
    Integrate*                         extensionM;
    EDR::Index                         fieldIdxM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};
}

#endif // IXT_EDRDELETEFIELD_HPP
