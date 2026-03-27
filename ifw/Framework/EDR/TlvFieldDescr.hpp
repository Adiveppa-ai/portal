/* @(#)%Portal Version: TlvFieldDescr.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:44:20 % */
#ifndef EDR_TLVFIELDDESCR_HPP
#define EDR_TLVFIELDDESCR_HPP
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
//   Declaration of the class TlvFieldDescr
//
//------------------------------------------------------------------------------
// Revision       1.1  2005/02/25 mliu
// PRSF00152956   Moved roundUp() function to TlvFiledDescr class from
//                FlistFieldDescr class so that it can be utilized by others.
//
// Revision       1.0  2004/07/22 ammon
// PRSF00116930   Created.
//
//==============================================================================

#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>LPR_TlvFieldDescr</tt></b> is the base class for ASN.1 types.
 *
 */
class TlvFieldDescr : public FieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    TlvFieldDescr( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~TlvFieldDescr();

    //@}
    
    /**@name TlvFieldDescr public methods */
    //@{
    
     /** Check if the field has an implicit field length
     *  @return <b>true</b> if implicit field lenght, <b>false</b> otherwise
     */
    virtual bool hasImplicitLength() const;

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

    /** Get the tag
     *  @return The tagM
     */
    int64 tag() const;

    /** Get the length in bytes of the tag given as a long
     *  @return The length in bytes of the tag
     */
    int64 getTagLength() const;
    
    /** Get the length in bytes of the Length field of the corresponding TLV field
     *  @return The length in bytes of the Length field of the TLV field
     */
    int64 getLenLength() const;

    /** Reads the TLV string, and calculate the length in bytes of the Value 
     *  field of the corresponding TLV field
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Value field of the TLV field
     */
    int64 getValLength(const BAS::String& value, size_t pos) const;

    /** Knowing the length of the Value field of the TLV field, builds the 
     *  Length field, in the given buffer. 
     *  @param byteBuffer The output data buffer
     *  @param valLength The length of the Value field in bytes (-1 for undefinite)
     *  @return The length in bytes constructed Length field
     */
    int64 buildLenField(ByteBuffer& byteBuffer,
                      const int64      valLength) const;

    /** Build a regular expression enabeling to read and recognize the Tag+Length
     *  fields of an TLV field
     *  @param outRegExpr The output data buffer containing the regular expression (null terminated)
     *  @param tag The TLV tag (given as a long) to be recognized
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getTagRegularExpression(BAS::String& outRegExpr,
                                        const int64 tag );
    
    /** Convert a TLV tag or value byte string to a long.
     *  @param byteStr The output data buffer (must be at least len long)
     *  @param len     The length for the coded string
     */
    virtual int64 bytesToLong(unsigned char* byteStr,
                          const int64 len ) const;

    //@}

  protected:
    /**@name TlvFieldDescr protected methods */
    //@{
 
    /** Build a byte string for a long to use as a TLV tag or length.
     *  @param byteStr The output data buffer must be at least len long)
     *  @param value   The value to be coded
     *  @param len     The length for the coded string
     */
    void longToBytes(unsigned char* byteStr,
                          const int64 value,
                          const int64 len ) const;

    /** Round a number uo to the next 4 byte boundary
     *  @param value The value to round up
     *  @return The corrected length to use to pad to a 4 byte boundary
     */
    int64 roundUp( const int64 value ) const;

    //@}
    
    int64          tagM;       // value of the Number part of the tag
    int64          tagLenM;    // the length of the tag
    int64          lenLenM;    // the length of the length
    int64          valueLenM;  // the length of the value
    
    int64	  sizeMinM;   // min length of String to read/write (def 0)
    int64	  sizeMaxM;   // max length of String to read/write (def -1)

  public:
    int64 getTotalLength(const BAS::String& value,
                       size_t            pos=0 ) const;
    virtual int64 getFullLength(const BAS::String& value,
                       size_t            pos=0 ) const;

};

//==============================================================================
// Get the tag number
//==============================================================================
inline int64
TlvFieldDescr::tag() const
{
  return tagM;
}

}
#endif // TLVFIELDDESCR
