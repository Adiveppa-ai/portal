/* @(#)%Portal Version: AscPoidType.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:43:32 % */
#ifndef EDR_ASCPOIDTYPE_HPP
#define EDR_ASCPOIDTYPE_HPP
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
//   Declaration of the class AscPoidType.
//
//------------------------------------------------------------------------------
// Revision       1.0  2005/02/08 ammon
// PRSF00136889   Created.
//
//==============================================================================

#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>AscPoidType</tt></b> is the Poid datatype used in input files.
 *
 */
class AscPoidType : public FieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AscPoidType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AscPoidType();

    //@}

    /**@name Classname public methods */
    //@{

    /** Get the name of the datatype
     *  @return Reference to the name
     */
    virtual const BAS::String& typeName() const;

    /** Check if the field has a fixed field length
     *  @return <b>true</b> if implicit field lenght, <b>false</b> otherwise
     */
    virtual bool hasFixedLength() const;

    /** Get the supported EDR container datatypes
     *  @return Long value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const;

    /** Create a new string instance
     *  @param name The name of the input field inside the input record
     *  @return Pointer to the created instance
     */
    virtual FieldDescr* create( const BAS::String& name ) const;

    /** Add a new parameter to the datatype
     *  @param parameter The parameter list to add
     *  @param failure Buffer for returning the failure string
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addParameter( const ParameterList& parameter,
                               BAS::String&              failure );

    /** Check whether the string type is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool isValid() const;

    /** Get a CompactPoid from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getCompactPoid( const BAS::String&  value,
                                 size_t              pos,
                                 size_t              len,
                                 EDR::CompactPoid&   buffer ) const;

    /** Set a CompactPoid value in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setCompactPoid( ByteBuffer&             buffer,
                                 size_t                  len,
                                 const EDR::CompactPoid& value ) const;

    /** Get the information about this field
     *  @param value Return buffer for the information
     */
    virtual void fieldInfo( BAS::String& value ) const;

     //@}

  private:
    // instance members
    char            padCharM;
    bool            isLeftJustifiedM;
    BAS::String     inBufferM;
    BAS::String     outBufferM;
    BAS::String     outNumBufferM;

    // class members
    EDR_EXPORT static const BAS::String	typeNameCM;
    EDR_EXPORT static const char	separatorCM;
};
}
#endif // ASCPOIDTYPE
