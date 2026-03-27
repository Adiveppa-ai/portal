/* @(#)%Portal Version: TlvIntegerType.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:44:11 % */
#ifndef EDR_TLVINTEGERTYPE_HPP
#define EDR_TLVINTEGERTYPE_HPP
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
//   Declaration of the class TlvIntegerType.
//
//------------------------------------------------------------------------------
// Revision       1.0  2004/06/16 ammon
// PRSF00116930   Created.
//
//==============================================================================

#ifndef   EDR_TLVFIELDDESCR_HPP
  #include "EDR/TlvFieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>TlvIntegerType</tt></b> is the TLV_Integer datatype used in input files.
 *
 */
class TlvIntegerType : public TlvFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    TlvIntegerType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~TlvIntegerType();

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
     *  @return Long value with bits specifing the supported datatypes
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
#endif // TLVINTEGERTYPE
