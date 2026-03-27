#ifndef IXT_EDRADDDATABLOCK_HPP
#define IXT_EDRADDDATABLOCK_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrAddDatablock
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
// $RCSfile: EdrAddDatablock.hpp,v $
// $Revision: 1.2 $
// $Author: sd $
// $Date: 2002/01/07 10:47:57 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrAddDatablock.hpp,v $
// Revision 1.2  2002/01/07 10:47:57  sd
// - PETS #42574 - LERG enhancements
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

/**<b><tt>EdrAddDatablock</tt></b> is the function class for adding new
 * datablocks to the edr container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrAddDatablock.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrAddDatablock : public SCR::BoolNode
{
  public:
    /**@name EdrAddDatablock constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrAddDatablock();

    //@

    /**@name EdrAddDatablock public methods */
    //@{

    /** Check if edr field is valid
     */
    bool isValid() const;

    /** Create the datablock
     *  @return The index of new datablock (>=0) on success, < 0 otherwise
     */
    virtual bool result();

    /** Factory for creation of edr field
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    static SCR::Node* otherFactory(SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr);


    //@}
    
  protected:

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrAddDatablock( Integrate* extension ,
		         SCR::StringNode* edrFieldNameNode = NULL,
                         SCR::ArrayNode* indicesArrayNode = NULL,
                         SCR::LongNode* noOfIndicesNode = NULL);
 
    bool flagM;
    SCR::StringNode* edrFieldNameNodeM;
    SCR::ArrayNode* indicesArrayNodeM;
    SCR::LongNode* noOfIndicesNodeM;


    /** Initialize the function node
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const BAS::String&                  blockName,
               RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector );

    bool init( const BAS::String&                  blockName,
	SCR::ArrayNode* indicesArrayNode, SCR::LongNode* noOfIndicesNode );


  private:
    // Hide default and copy constructor
    EdrAddDatablock();
    EdrAddDatablock( const EdrAddDatablock& other );
    const EdrAddDatablock& operator=( const EdrAddDatablock& other );

    // instance members
    IXT::Integrate*                    extensionM;
    EDR::BlockIndex                    blockIdxM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
};
}
#endif // EDRADDDATABLOCK_HPP
