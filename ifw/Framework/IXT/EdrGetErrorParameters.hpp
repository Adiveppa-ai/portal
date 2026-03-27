#ifndef IXT_EDRGETERRORPARAMETERS_HPP
#define IXT_EDRGETERRORPARAMETERS_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: SCR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class EdrGetErrorParameters. This class is the
//   iScript function node for the function edrGetErrorParameters() which 
//   returns the StringList parameter list associated with an error .
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Cedric Diab
//
// $RCSfile: EdrGetErrorParameters.hpp,v $
// $Revision: 1.0 $
// $Author: cdiab $
// $Date: 2002/04/24 16:01:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrGetErrorParameters.hpp,v $
// Revision 1.0  2002/04/24 16:01:18  cdiab
// - Creation of: nbParams = edrGetErrorParameters(errorIdx, stringArray)
//
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif

class Interpreter;
class ParserStack;
class FctDescr;
namespace IXT
{

/** <b><tt>EdrGetErrorParameters</tt></b> is the iScript function which
 *  returns the StringList parameter list associated with an error.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrGetErrorParameters.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.0 $</font></td>
 *  <td><font size=-1>$Date: 2002/04/24 16:01:18 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class EdrGetErrorParameters : public SCR::LongNode
{
  public:
    /**@name EdrGetErrorParameters constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrGetErrorParameters();

    //@}

    /**@name EdrGetErrorParameters public methods */
    //@{

    /** Fills in the array with the parameter associated to the error
     *  coresponding to the given index
     *  @return The number of elements in the resulting array
     */
    virtual int64 result();

    /** Create a EdrGetErrorParameters() function node
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr Function description
     *  @return <b>Pointer</b> to function node on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}

  protected:

    /* Constructor
     * @param extension Pointer to the integRate iScript extension
     * @param indexNode node containing the index of the error to retrieve
     * @param arrayNode node containing the Array to fill
     */
    EdrGetErrorParameters(	Integrate* extension,
				SCR::LongNode*  indexNode,
				SCR::ArrayNode* arrayNode);
  private:

    // Hide the copy constructor and assignment operator (not implemented)
    EdrGetErrorParameters( const EdrGetErrorParameters& other );
    const EdrGetErrorParameters& operator=( const EdrGetErrorParameters& other );

    // instance members
    Integrate*  extensionM;
    SCR::LongNode*   indexNodeM;
    SCR::ArrayNode*  arrayNodeM;
};
}
#endif // EDRGETERRORPARAMETERS_HPP
