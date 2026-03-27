#ifndef IXT_EDRACCESS_HPP
#define IXT_EDRACCESS_HPP

//==============================================================================
//
//      Copyright (c) 1996 - 2008 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: IXT
//------------------------------------------------------------------------------
// Module Description:
//   EdrAccess is the base class for iScript function nodes that access
//   EDR container fields and datablocks.
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
// $RCSfile: EdrAccess.hpp,v $
// $Revision: 1.1 $
// $Author: sd $
// $Date: 2002/03/13 08:51:02 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: EdrAccess.hpp,v $
// Revision 1.1  2002/03/13 08:51:02  sd
// - ClearCase Transition checkin
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   EDR_CONTAINER_HPP
  #include "EDR/Container.hpp"
#endif

namespace SCR
{
class LongNode;
}
namespace IXT
{
class Integrate;

/** <b><tt>EdrAccess</tt></b>
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: EdrAccess.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.1 $</font></td>
 *  <td><font size=-1>$Date: 2002/03/13 08:51:02 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class EdrAccess D_THREADINFO
{
  public:
    /**@name EdrAccess constructors and destructor */
    //@{

    /** Constructor
     *  @param extension Pointer to the integRate iScript extension
     */
    EdrAccess( Integrate* extension );

    /** Destructor
     */
    virtual ~EdrAccess();

    //@}

  protected:

    /**@name EdrAccess protected methods */
    //@{

    /** Initialize the current vector
     *  @return Pointer to current vector to use on success
     *          0 otherwise
     */
   EDR::CurrentVector* initCurrentVector();

    //@}

  protected:
    // Instance members
    Integrate*                    extensionM;
    RWTPtrOrderedVector<SCR::LongNode> currentNodeVectorM;
    EDR::CurrentVector                 currentVectorM;
    SCR::ArrayNode* currentNodeArrayM;
    int64 currentNodeArrayEntriesM;
};
}
#endif // EDRACCESS_HPP
