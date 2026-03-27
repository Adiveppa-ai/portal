#ifndef EDR_ASNINTEGERTYPE_HPP
#define EDR_ASNINTEGERTYPE_HPP
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
//   Declaration of the class AsnIntegerType.
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
// $RCSfile: AsnIntegerType.hpp,v $
// $Revision: 1.8 $
// $Author: cdiab $
// $Date: 2001/09/17 13:07:52 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnIntegerType.hpp,v $
// Revision 1.8  2001/09/17 13:07:52  cdiab
// PETS #38890: Errors writing TAP3 to output.
// Corrected error where positiv long values were written with a leading
// bit set to 1 (ie negativ) when the length was smaller than sizeof(Long).
//
// Revision 1.7  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.6  2001/04/19 14:17:37  sd
// - setXXXX() and getXXXX() functions of the FieldDescr are now const
//   functions.
//
// Revision 1.5  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.4  2001/03/21 08:58:20  cdiab
// Modified type for output buffer of set methodes (now automatic length check).
// + added doc++ type comments in header files.
//
// Revision 1.3  2001/03/20 14:49:26  cdiab
// now used as basic class for TAP3 basic types.
//
// Revision 1.2  2001/03/19 16:56:32  cdiab
// now the basic types can get a tag through the addParameter() methode.
//
// Revision 1.1  2001/03/16 14:37:21  cdiab
// this class manages objects coresponding to ASN.1 INTEGER objects.
//
// Revision 1.0  2001/03/16 14:05:03  cdiab
// processes an ASN.1 INTEGER object.
//
// Revision 1.0  2001/03/16 10:43:40  cd
// - Creation
//==============================================================================

#ifndef   EDR_ASNFIELDDESCR_HPP
  #include "EDR/AsnFieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>AsnIntegerType</tt></b> is the ASN_Integer datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnIntegerType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.8 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/17 13:07:52 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class AsnIntegerType : public AsnFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AsnIntegerType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AsnIntegerType();

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

    /** Get a long value as a string from the input record
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

    /** Set a string value as a long in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setString( ByteBuffer&   buffer,
                            size_t            len,
                            const BAS::String& value ) const;

    /** Get a long value as a decimal from the input record
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

    /** Set a decimal value as a long in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setDecimal( ByteBuffer&    buffer,
                             size_t             len,
                             const BAS::Decimal& value ) const;

     //@}

  private:

    //instance member
    u_int64		sizeOfLongM;
    
    // class members
    EDR_EXPORT static const BAS::String	typeNameCM;
};
}
#endif // AsnIntegerType
