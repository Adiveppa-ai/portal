#ifndef EDR_ASNOCTETSTRINGTYPE_HPP
#define EDR_ASNOCTETSTRINGTYPE_HPP
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
//   Declaration of the class AsnOctetStringType.
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
// $RCSfile: AsnOctetStringType.hpp,v $
// $Revision: 1.9 $
// $Author: cdiab $
// $Date: 2001/10/08 16:11:34 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnOctetStringType.hpp,v $
// Revision 1.9  2001/10/08 16:11:34  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
// use a lookup table for converting Hex characters in Ascii format.
// + added a getDecimal() and setDecimal() method to AsnHexStringType.
//
// Revision 1.8  2001/09/25 16:02:20  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
//
// Revision 1.7  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.6  2001/04/19 14:17:37  sd
// - setXXXX() and getXXXX() functions of the FieldDescr are now const
//   functions.
//
// Revision 1.5  2001/04/11 14:08:21  cdiab
// added getLong() and setLong() methodes to AsnOctetString, and activated
// them for TapNumberString.
//
// Revision 1.4  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.3  2001/03/30 14:22:05  cdiab
// added the getDate() and setDate() methode to AsnOctetStringType,
// and activated this type for TAP_NumericString.
//
// Revision 1.2  2001/03/21 08:58:20  cdiab
// Modified type for output buffer of set methodes (now automatic length check).
// + added doc++ type comments in header files.
//
// Revision 1.1  2001/03/20 14:48:20  cdiab
// Creation of the ASN.1 basic Type OCTET STRING, used for TAP3 strings.
//
// Revision 1.0  2001/03/19 16:56:32  cdiab
// this class manages objects corresponding to ASN.1 OCTETSTRING objects.
//
//==============================================================================

#ifndef   EDR_ASNFIELDDESCR_HPP
  #include "EDR/AsnFieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>AsnOctetStringType</tt></b> is the ASN_OctetString datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnOctetStringType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.9 $</font></td>
 *  <td><font size=-1>$Date: 2001/10/08 16:11:34 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class AsnOctetStringType : public AsnFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AsnOctetStringType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AsnOctetStringType();

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

    /** Check whether the string type is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool isValid() const;

    /** Get the implict length of the input field
     *  @param value The input data from the token 
     *  @param pos The starting position inside the buffer
     *  @return The total length of the datatype (>0), 0 on error
     */
    virtual size_t implicitLength( const BAS::String& value,
                                   size_t            pos );
 
    /** Get the supported EDR container datatypes
     *  @return long value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const;


    /** Get a string value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getString( const BAS::String& value,
                            size_t            pos,
                            size_t            len,
                            BAS::String&       buffer ) const;

    /** Set a string field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setString( ByteBuffer&   buffer,
                            size_t            len,
                            const BAS::String& value ) const;

    /** Get a date/time value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDate( const BAS::String& value,
                          size_t            pos,
                          size_t            len,
                          BAS::DateTime&     buffer ) const;

    /** Set a date/time field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param date The output date
     */
    virtual bool setDate( ByteBuffer&     buffer,
                          size_t              len,
                          const BAS::DateTime& date ) const;

    /** Get a long value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getLong( const BAS::String& value,
                          size_t            pos,
                          size_t            len,
                          int64&             buffer ) const;

    /** Set a long field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The value to set
     */
    virtual bool setLong( ByteBuffer&  buffer,
                          size_t           len,
                          int64             value ) const;
    //@}

  protected:
    // Arrays to quickly convert long values into their hex representation
    EDR_EXPORT static const char hexbyte2str[256][3];
    EDR_EXPORT static const char hexdigit2char[16];
    EDR_EXPORT static const int  hexchar2int[120];

  private:
    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}
#endif // AsnOctetStringType
