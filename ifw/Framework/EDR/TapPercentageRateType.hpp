#ifndef EDR_TAPPERCENTAGERATETYPE_HPP
#define EDR_TAPPERCENTAGERATETYPE_HPP
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class TapPercentageRateType.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Cedric Diab
//
// $RCSfile: TapPercentageRateType.hpp,v $
// $Revision: 1.4 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: TapPercentageRateType.hpp,v $
// Revision 1.4  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.3  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.2  2001/03/21 09:57:17  cdiab
// the typeName() methode was missing.
//
// Revision 1.1  2001/03/20 14:46:28  cdiab
// creation of the TAP3 basic types
//
// Revision 1.2  2001/03/19 16:56:32  cdiab
// this class manages objects corresponding to TAP3 PercentageRate Type
//
//==============================================================================

#ifndef   EDR_ASNINTEGERTYPE_HPP
  #include "EDR/AsnIntegerType.hpp"
#endif
namespace EDR
{
/** <b><tt>TapPercentageRateType</tt></b> is the TAP_PercentageRate datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: TapPercentageRateType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class TapPercentageRateType : public AsnIntegerType D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{
    
    /** Constructor
     *  @param name The name of the input field
     */
    TapPercentageRateType( const BAS::String& name = BAS::NULL_STRING );

    //@}

    /**@name Classname public methods */
    //@{
    
    /** Create a new string instance
     *  @param name The name of the input field inside the input record
     *  @return Pointer to the created instance
     */
    virtual FieldDescr* create( const BAS::String& name ) const;

    /** Get the name of the datatype
     *  @return Reference to the name
     */
    virtual const BAS::String& typeName() const;
    
    //@}


  private:

    // class members
    EDR_EXPORT static const BAS::String typeNameCM;

};
}
#endif // TapPercentageRateType
