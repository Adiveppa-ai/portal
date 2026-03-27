/* @(#)%Portal Version: FlistFieldDescr.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:44:00 % */
#ifndef EDR_FLISTFIELDDESCR_HPP
#define EDR_FLISTFIELDDESCR_HPP
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
//   Declaration of the class FlistFieldDescr
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

#ifndef   EDR_TLVFIELDDESCR_HPP
  #include "EDR/TlvFieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>LPR_FlistFieldDescr</tt></b> is the base class for Flist types.
 *
 */
class FlistFieldDescr : public TlvFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    FlistFieldDescr( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~FlistFieldDescr();

    //@}
    
    /**@name FlistFieldDescr public methods */
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

    /** Get the length in bytes of the Length field of the corresponding flist field
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Length field of the flist field
     */
    int64 getLenLength(const BAS::String& value, size_t pos) const;

    /** Reads the flist string, and calculate the length in bytes of the Value 
     *  field of the corresponding flist field
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Value field of the flist field
     */
    int64 getValLength(const BAS::String& value, size_t pos) const;

    /** Builds the tag part of the field in the given buffer. 
     *  @param byteBuffer The output data buffer
     *  @return The length in bytes constructed tag
     */
    int64 buildTag( ByteBuffer& byteBuffer ) const;

    /** Knowing the length of the Value field of the flist field, builds the 
     *  Length field, in the given buffer. 
     *  @param byteBuffer The output data buffer
     *  @param valLength The length of the Value field in bytes (-1 for undefinite)
     *  @return The length in bytes constructed Length field
     */
    int64 buildLenField(ByteBuffer& byteBuffer,
                      const int64      valLength) const;

    /** Build a regular expression enabeling to read and recognize the Tag+Length
     *  fields of an flist field
     *  @param outRegExpr The output data buffer containing the regular expression (null terminated)
     *  @param tag The flist tag (given as a int64) to be recognized
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getTagRegularExpression(BAS::String& outRegExpr,
                                        const int64 tag );
    //@}

    // How the length is calculated
    enum LengthTypes
    {
      FIXED,                 // implied by type
      INDEX,                 // special case of FIXED
      VARIABLE,              // length only
      EMPTY_OR_FIXED,        // value present flag only
      EMPTY_OR_VARIABLE,     // value present flag and length
      CONTAINER,             // special case of EMPTY_OR_VARIABLE
      DECIMAL,               // special case of EMPTY_OR_VARIABLE
      POID                   // special case of EMPTY_OR_VARIABLE
    };

  protected:
    /**@name FlistFieldDescr protected methods */
    //@{
    /** Get a 4 byte length from a string
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Length field of the flist field
     */
    int64 getLen( unsigned char* value ) const;

    /** Writes a 4 byte length to the buffer
     *  @param byteBuffer The output data buffer
     *  @param value The value to write to the buffer
     *  @return The length in bytes constructed Length field
     */
    void buildLen( ByteBuffer& byteBuffer, const int64 value ) const;

    //@}
    
    BAS::String   fieldTypeM;     // the flist field name - PIN_FLD_*
    int64          pinFldNumM;     // the flist field number
    int64          pinFldTypeM;    // the flist field type
    LengthTypes   lenTypeM;       // how the field length is calculated


  public:
    int64 getTotalLength( const BAS::String& value, size_t pos = 0 ) const;
};

}
#endif // FLISTFIELDDESCR
