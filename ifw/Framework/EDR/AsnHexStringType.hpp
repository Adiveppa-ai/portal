#ifndef EDR_ASNHEXSTRINGTYPE_HPP
#define EDR_ASNHEXSTRINGTYPE_HPP
//==============================================================================
//
// Copyright (c) 1996, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class AsnHexStringType.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: brajan
//
// $RCSfile: AsnHexStringType.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2009/04/04 07:23:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnHexStringType.hpp,v $
// Revision 1.9  2004/05/07 15:17:15  brajan
// PRSF00109238:(propagation of PRSF00100030): B_NUMBER field is sometimes populated wrongly.
// Removed the usage of instance member conversionBufferM since it could be
// accessed by multiple threads changing the internal state of the object
// and leading to corruption of data in the buffer.
//
// $Log: AsnHexStringType.hpp,v $
// Revision 1.8  2001/10/08 16:11:34  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
// use a lookup table for converting Hex characters in Ascii format.
// + added a getDecimal() and setDecimal() method to AsnHexStringType.
//
// Revision 1.7  2001/09/28 12:01:47  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
// now using an instance member ByteBuffer to optimize the conversion.
//
// Revision 1.6  2001/09/25 16:02:20  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
//
// Revision 1.5  2001/09/17 13:07:52  cdiab
// PETS #38890: Errors writing TAP3 to output.
// Corrected error where positiv long values were written with a leading
// bit set to 1 (ie negativ) when the length was smaller than sizeof(Long).
//
// Revision 1.4  2001/09/06 10:18:22  cdiab
// PETS #38890: Errors writing TAP3 to output.
// added a setLong() and getLong() methode for compatibility with ASN_Integer.
//
// Revision 1.3  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.2  2001/07/24 10:41:55  cdiab
// PETS #37417 : need ability to read Hex byte string in an Ascii string
// implemented for ASN_HexString.
//
// Revision 1.1  2001/06/28 10:06:09  cdiab
// in replacement to the same, but with TapXxxxxx
//
// Revision 1.0  2001/06/28 13:00:04  cdiab
// this class manages objects corresponding to ASN.1 HexString objects.
//
//==============================================================================

#ifndef   EDR_BYTEBUFFER_HPP
  #include "EDR/ByteBuffer.hpp"
#endif
#ifndef   EDR_ASNOCTETSTRINGTYPE_HPP
  #include "EDR/AsnOctetStringType.hpp"
#endif
namespace EDR
{
/** <b><tt>AsnHexStringType</tt></b> is the ASN_HexString datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnHexStringType.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2009/04/04 07:23:06 $</font></td>
 *  <td><font size=-1>$Author: cprabhak $</font></td>
 *  </tr>
 *  </table>
 */
class AsnHexStringType : public AsnOctetStringType D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{
    
    /** Constructor
     *  @param name The name of the input field
     */
    AsnHexStringType( const BAS::String& name = BAS::NULL_STRING );
    
    /** Destructor
     */
    virtual ~AsnHexStringType();

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

    /** Get a decimal value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDecimal( const BAS::String& value,
                             size_t            pos,
                             size_t            len,
                             BAS::Decimal&      buffer ) const;

    /** Set a decimal field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setDecimal( ByteBuffer&    buffer,
                             size_t             len,
                             const BAS::Decimal& value ) const;

    //@}

  private:
    // instance members
    u_int64   sizeOfLongM;

    // class members and methodes
    EDR_EXPORT static const BAS::String typeNameCM;
    
    /** Simple HEX to String conversion method
     */
    static int HEXtoSTR(const char* hex,u_int64 hexSize,BAS::String& str);
    
    /** Simple String to HEX conversion method
     */
    static int STRtoHEX(const BAS::String& strBasString, ByteBuffer& hex);
};
}
#endif // AsnHexStringType
