#ifndef IXT_EDRNUMDATABLOCKS_HPP
#define IXT_EDRNUMDATABLOCKS_HPP

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
//   Declaration of the class EdrNumDatablocks.
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
// $RCSfile: EXT_OutFileManager.cpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2001/04/03 14:28:08 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EXT_OutFileManager.cpp,v $
//==============================================================================

#ifndef   SCR_NODE_HPP
  #include "SCR/Node.hpp"
#endif
#ifndef   IXT_EDRBLOCKACCESS_HPP
  #include "IXT/EdrBlockAccess.hpp"
#endif

namespace IXT
{
class Interpreter;
class ParserStack;
class FctDescr;
}
namespace IXT
{

/**<b><tt>EdrNumDatablocks</tt></b> is the function class to determine
 * the number of datablocks for the specified type.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrFunctions.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2002/01/07 10:47:57 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrNumDatablocks : public SCR::LongNode, public EdrBlockAccess
{
  public:
    /**@name EdrNumDatablocks constructors and destructor */
    //@{

    /** Destructor
     */
    virtual ~EdrNumDatablocks();

    //@

    /**@name EdrNumDatablocks public methods */
    //@{

    /** Get the number of datablocks
     *  @return The number of datablocks (>=0) on success, < 0 otherwise
     */
    virtual int64 result();

    /** Factory for creation of edr field
     *  @param interpreter Interpreter for the function
     *  @param stack Stack with parameters etc
     *  @param descr The function description
     *  @return <b>Pointer</b> on success, <b>0</b> otherwise
     */
    static SCR::Node* factory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );
    static SCR::Node* otherFactory( SCR::Interpreter&    interpreter,
                              SCR::ParserStack&    stack,
                              const SCR::FctDescr& descr );

    //@}
    
  protected:

    /* Constructor
     * @param extension Pointer to the integRate iScript extension
     * @param alias Alias name of the edr container field
     */
    //EdrNumDatablocks( Integrate* extension );
    EdrNumDatablocks( Integrate* extension,
                         SCR::StringNode* edrFieldNameNode = NULL,
                         SCR::ArrayNode* indicesArrayNode = NULL,
                         SCR::LongNode* noOfIndicesNode = NULL);

    bool flagM;
    SCR::StringNode* edrFieldNameNodeM;
    SCR::ArrayNode* indicesArrayNodeM;
    SCR::LongNode* noOfIndicesNodeM;

  private:
    // Hide copy and default constructor
    EdrNumDatablocks();
    EdrNumDatablocks( const EdrNumDatablocks& other );
    const EdrNumDatablocks& operator=( const EdrNumDatablocks& other );
};
}
#endif // EDRNUMDATABLOCKS_HPP
