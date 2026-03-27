#ifndef EDR_ASNNUMBERSTRING_HPP
#define EDR_ASNNUMBERSTRING_HPP
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
//   Declaration of the class AsnNumberStringType.
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
// $RCSfile: AsnNumberStringType.hpp,v $
// $Revision: 1.2 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnNumberStringType.hpp,v $
// Revision 1.2  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.1  2001/06/28 10:06:09  cdiab
// in replacement to the same, but with TapXxxxxx
//
// Revision 1.0  2001/06/28 13:00:04  cdiab
// this class manages objects corresponding to ASN.1 NumberString objects.
//
//==============================================================================

#ifndef   EDR_ASNOCTETSTRINGTYPE_HPP
  #include "EDR/AsnOctetStringType.hpp"
#endif
namespace EDR
{
/** <b><tt>AsnNumberStringType</tt></b> is the ASN_NumberString datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnNumberStringType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class AsnNumberStringType : public AsnOctetStringType D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{
    
    /** Constructor
     *  @param name The name of the input field
     */
    AsnNumberStringType( const BAS::String& name = BAS::NULL_STRING );
    
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

    /** Get the supported EDR container datatypes
     *  @return long value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const;

    //@}

  private:

    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}
#endif // AsnNumberStringType
