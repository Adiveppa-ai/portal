#ifndef EDR_ASNLEGACYOCTETSTRINGTYPE_HPP
#define EDR_ASNLEGACYOCTETSTRINGTYPE_HPP

/* @(#)%Portal Version: AsnLegacyOctetStringType.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:45:48 % */
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
//   Declaration of the class AsnLegacyOctetStringType. This was
//   introduced for Vodaphone to support a legacy switch
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Joe Ponepinto
//

#ifndef   EDR_ASNFIELDDESCR_HPP
  #include "EDR/AsnFieldDescr.hpp"
#endif
#ifndef   EDR_ASNOCTETSTRINGTYPE_HPP
  #include "EDR/AsnOctetStringType.hpp"
#endif
namespace EDR
{
/** <b><tt>AsnLegacyOctetStringType</tt></b> is the ASN_LegacyOctetString datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnLegacyOctetStringType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.0 $</font></td>
 *  <td><font size=-1>$Date: 2002/10/10 $</font></td>
 *  <td><font size=-1>$Author: pinto $</font></td>
 *  </tr>
 *  </table>
 */
class AsnLegacyOctetStringType : public AsnOctetStringType D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AsnLegacyOctetStringType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AsnLegacyOctetStringType();

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

    /** Set a string field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setString( ByteBuffer&   buffer,
                            size_t            len,
                            const BAS::String& value ) const;

  private:
    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}
#endif // AsnLegacyOctetStringType
