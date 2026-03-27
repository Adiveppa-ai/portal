/* @(#)%Portal Version: TlvTagType.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:44:06 % */
#ifndef EDR_TLVTAGTYPE_HPP
#define EDR_TLVTAGTYPE_HPP
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
//   Declaration of the class TlvTagType.
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
class ByteBuffer; // from ByteBuffer.hpp

/** <b><tt>TLV_TagType</tt></b> is the TlvTagType datatype used in input files.
 *
 */
class TlvTagType : public TlvFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    TlvTagType( const BAS::String& name = BAS::NULL_STRING ,
                    int                tag = (-1) ); 

    /** Destructor
     */
    virtual ~TlvTagType();

    //@}

    /**@name TlvTagType public methods */
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

    /** Used as a "trick" to set a the Tag and Len fields in a byte buffer
     *  (Value field is NOT set).
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param valLength The length of the Value field
     */
    virtual bool setLong( ByteBuffer&  buffer,
                          size_t           len,
                          int64             valLength ) const;
			  
    /** This methode is just here for coherence, and should never be used
     *  it always return false, and does nothing.
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
   //@}

  private:
    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
    
};
}
#endif // TLVTAGTYPE
