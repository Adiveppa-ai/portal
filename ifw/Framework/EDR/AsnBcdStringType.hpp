#ifndef EDR_ASNBCDSTRINGTYPE_HPP
#define EDR_ASNBCDSTRINGTYPE_HPP
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
//   Declaration of the class AsnBcdStringType.
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
// $RCSfile: AsnBcdStringType.hpp $
// $Revision: /cgbubrm_7.3.2.pipeline/1 $
// $Author: cprabhak $
// $Date: 2009/04/04 07:23:06 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnBcdStringType.hpp,v $
// Revision 1.5  2004/04/14 15:17:15  brajan
// PRSF00109238:(propagation of PRSF00100030): B_NUMBER field is sometimes populated wrongly.
// Removed the usage of instance member conversionBufferM since it could be
// accessed by multiple threads changing the internal state of the object
// and leading to corruption of data in the buffer.
//
// $Log: AsnBcdStringType.hpp,v $
// Revision 1.4  2001/09/28 12:01:47  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
// now using an instance member ByteBuffer to optimize the conversion.
//
// Revision 1.3  2001/09/25 16:02:20  cdiab
// PETS #39832: optimize read/write of Hex Strings in Tap3
//
// Revision 1.2  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.1  2001/06/28 10:06:09  cdiab
// in replacement to the same, but with TapXxxxxx
//
// Revision 1.0  2001/06/28 14:17:37  cdiab
// this class manages objects corresponding to ASN.1 BCDString objects.
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
/** <b><tt>AsnBcdStringType</tt></b> is the ASN_BcdString datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnBcdStringType.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.3.2.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2009/04/04 07:23:06 $</font></td>
 *  <td><font size=-1>$Author: cprabhak $</font></td>
 *  </tr>
 *  </table>
 */
class AsnBcdStringType : public AsnOctetStringType D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{
    
    /** Constructor
     *  @param name The name of the input field
     */
    AsnBcdStringType( const BAS::String& name = BAS::NULL_STRING );
    
    /** Destructor
     */
    virtual ~AsnBcdStringType();

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
			    
    //@}

  private:
    // instance members

    // class members and methodes
    EDR_EXPORT static const BAS::String typeNameCM;

    /** Simple BCD to String conversion method
     */
    static int BCDtoSTR(const char* bcd,u_int64 bcdSize,BAS::String& str);

    /** Simple String to BCD conversion method
     */
    static int STRtoBCD(const BAS::String& strBasString,ByteBuffer& bcd);

};
}
#endif // AsnBcdStringType
