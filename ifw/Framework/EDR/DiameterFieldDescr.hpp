/* @(#)%Portal Version: DiameterFieldDescr.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:43:27 % */
#ifndef EDR_DIAMETERFIELDDESCR_HPP
#define EDR_DIAMETERFIELDDESCR_HPP
//==============================================================================
//
// Copyright (c) 1996, 2008, Oracle and/or its affiliates. All rights reserved. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: Base
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class DiameterFieldDescr
//
//------------------------------------------------------------------------------
// Revision       1.1  2006/04/24 mliu
// PRSF00203103   Added DiameterUnknown basetype.
//
// Revision       1.0  2005/01/30 mliu
// PRSF000152956  Created.
//
//==============================================================================

#ifndef   EDR_TLVFIELDDESCR_HPP
  #include "EDR/TlvFieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>DiameterFieldDescr</tt></b> is the base class for Diameter AVP data types.
 *
 */
class DiameterFieldDescr : public TlvFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    DiameterFieldDescr( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~DiameterFieldDescr();

    //@}
    
    /**@name DiameterFieldDescr public methods */
    //@{
    
    /** Add a new parameter to the datatype
     *  @param parameter The parameter list to add
     *  @param failure Buffer for returning the failure string
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addParameter( const ParameterList& parameter,
                               BAS::String&              failure );

    /** Get the information about this field
     *  @param value Return buffer for the information
     */
    virtual void fieldInfo( BAS::String& value ) const;

    /** Get the length in bytes of the Length field of the corresponding AVP field
     *  @return The length in bytes of the Length field of the AVP field
     */
    int64 getLenLength() const;

    /** Get the length in bytes of the VendorId field of the corresponding AVP field
     *  @return The length in bytes of the Length field of the AVP field
     */
    int64 getVidLength() const;

    /** Get the total length in bytes of the tag, length, and vendor id fields
     *  @return The total length in bytes of the leading fields before value field
     */
    int32 getLeadingLength() const;

    /** Get the AVP datatype size in bytes
     *  @return The size in bytes
     */
    int32 getDatatypeSize() const;

    /** Reads the AVP string, and calculate the length in bytes of the Value 
     *  field of the corresponding Diameter AVP
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Value field of the AVP field
     */
    int64 getValLength(const BAS::String& value, size_t pos) const;

    /** Get the implict length of the input field
     *  @param value The input data from the token
     *  @param pos The starting position inside the buffer
     *  @return The total length of the datatype (>0), 0 on error
     */
    virtual size_t implicitLength( const BAS::String& value, size_t pos );

    /** Builds the tag part of the field in the given buffer. 
     *  @param byteBuffer The output data buffer
     *  @return The length in bytes constructed tag
     */
    int64 buildTag( ByteBuffer& byteBuffer ) const;

    /** Knowing the length of the Value field of the AVP field, builds the 
     *  Length field, in the given buffer. 
     *  @param byteBuffer The output data buffer
     *  @param valLength The length of the Value field in bytes (-1 for undefinite)
     *  @return The length in bytes constructed Length field
     */
    int64 buildLenField(ByteBuffer& byteBuffer,
                      const int64      valLength) const;

    /** Build a regular expression enabeling to read and recognize the Tag+Length
     *  fields of an AVP field
     *  @param outRegExpr The output data buffer containing the regular expression (null terminated)
     *  @param tag The AVP tag (given as a int64) to be recognized
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getTagRegularExpression(BAS::String& outRegExpr,
                                        const int64 tag );

    /** Get the total length of the input field
     *  @param value The input data from the token
     *  @param pos The starting position inside the buffer
     *  @return The total length of the datatype (>0), 0 on error
     */
    int64 getTotalLength( const BAS::String& value, size_t pos = 0 ) const;

    virtual int64 getFullLength( const BAS::String& value, size_t pos = 0 ) const;

    //@}

  protected:
    /**@name DiameterFieldDescr protected methods */
    //@{
    /** Get a 3 byte length from a string
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Length field of the AVP field
     */
    int64 getLen( unsigned char* value ) const;

    /** Writes a 3 byte length to the buffer
     *  @param byteBuffer The output data buffer
     *  @param value The value to write to the buffer
     *  @return The length in bytes constructed Length field
     */
    void buildLen( ByteBuffer& byteBuffer, const int64 value ) const;

    //@}
    
  protected:
    int64	avpCodeM;    	// the AVP length
    int64	avpLengthM;    	// the AVP length
    int64       avpFlagsM;     	// the AVP flags
    int64       avpVendorIdM;   // the AVP Vendor Id
    int32       avpTypeSizeM;   // the AVP data type size in bytes (4 or 8)
    BAS::String avpTimeZoneM;   // the AVP Time Zone
    bool 	avpGroupedM;    // 'true' if DiameterGrouped type
    bool 	avpUnknownM;    // 'true' if DiameterUnknown type

    int64       codeLenM;       // the length of AVP flags
    int64       flagsLenM;      // the length of AVP flags
    int64       vendorIdLenM;   // the length of AVP vendor Id

};

}
#endif // EDR_DIAMETERFIELDDESCR_HPP
