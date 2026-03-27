#ifndef IXT_EDRVALUEACCESS_HPP
#define IXT_EDRVALUEACCESS_HPP

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
//   EdrValueAccess is the base class for all iScript function nodes that
//   access EDR values.
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
// $RCSfile: EdrValueAccess.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2002/03/13 08:51:02 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrValueAccess.hpp,v $
// Revision 1.1  2002/03/13 08:51:02  sd
// - ClearCase Transition checkin
//
//==============================================================================

#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   IXT_EDRACCESS_HPP
  #include "IXT/EdrAccess.hpp"
#endif

namespace IXT
{
/** <b><tt>EdrValueAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrValueAccess.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2002/03/13 08:51:02 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrValueAccess : public EdrAccess
{
  public:
    /**@name EdrValueAccess constructors and destructor */
    //@{

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrValueAccess( Integrate* extension );

    /** Destructor
     */
    ~EdrValueAccess();

    //@}


    /**@name EdrValueAccess public methods */
    //@{

    /** Get the edr index 
     *  @return The edr index 
     */
    EDR::Index edrIndex() const;

    /* Initialize the function node with edr field name and current vector
     * @param edrField The name of the edr container field to access
     * @param currentNodeVector iScript nodes for the additional indices
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const BAS::String&                  fieldName,
               RWTPtrOrderedVector<SCR::LongNode>& currentNodeVector );

    bool init( const BAS::String&                  fieldName,
               SCR::ArrayNode* indicesArrayNode, SCR::LongNode* noOfIndicesNode);

    //@}

  protected:

    // Instance members
    EDR::Index edrIdxM;
};

//==============================================================================
// Get the edr index
//==============================================================================
inline EDR::Index
EdrValueAccess::edrIndex() const
{
  D_ENTER( "EdrValueAccess::edrIndex() const" );
  return edrIdxM;
}
}
#endif // EDRVALUEACCESS_HPP
