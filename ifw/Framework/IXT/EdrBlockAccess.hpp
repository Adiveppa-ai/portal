#ifndef IXT_EDRBLOCKACCESS_HPP
#define IXT_EDRBLOCKACCESS_HPP

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
//   Declaration of the class EdrBlockAccess.
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

#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   IXT_EDRACCESS_HPP
  #include "IXT/EdrAccess.hpp"
#endif
namespace IXT
{

/** <b><tt>EdrBlockAccess</tt></b> is the base class for all iScript
 *  function nodes accessing datablocks.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: SCR::Interpreter.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.27 $</font></td>
 *  <td><font size=-1>$Date: 2000/09/08 15:35:06 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrBlockAccess : public EdrAccess
{
  public:
    /**@name EdrBlockAccess constructors and destructor */
    //@{

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrBlockAccess( Integrate* extension );

    /** Destructor
     */
    ~EdrBlockAccess();

    //@}

    /**@name EdrBlockAccess public methods */
    //@{

    /** Get the edr block index 
     *  @return The edr index 
     */
    EDR::BlockIndex edrBlockIndex() const;

    /* Initialize the function node with edr field name and current vector
     * @param edrField The name of the edr container field to access
     * @param currentNodeVector iScript nodes for the additional indices
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool initBlockAccess( const BAS::String&                  fieldName,
                          RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector );
    bool initBlockAccess( const BAS::String&                  fieldName,
			SCR::ArrayNode* indicesArrayNode, SCR::LongNode* noOfIndicesNode );


    //@}

  protected:
    // Instance members
    EDR::BlockIndex blockIdxM;
};
}
#endif // EDRBLOCKACCESS_HPP
