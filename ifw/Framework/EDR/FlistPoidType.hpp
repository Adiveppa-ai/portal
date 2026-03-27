/* @(#)%Portal Version: FlistPoidType.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:43:52 % */
#ifndef EDR_FLISTPOIDTYPE_HPP
#define EDR_FLISTPOIDTYPE_HPP
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
//   Declaration of the class FlistPoidType.
//
//------------------------------------------------------------------------------
// Revision       1.1  2004/09/08 ammon
// PRSF00124011   Use CompactPoid instead of BAS::Identifier.
//
// Revision       1.0  2004/07/22 ammon
// PRSF00116930   Created.
//
//==============================================================================

#ifndef   EDR_FLISTFIELDDESCR_HPP
  #include "EDR/FlistFieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>FlistPoidType</tt></b> is the FLIST_Poid datatype used in input files.
 *
 */
class FlistPoidType : public FlistFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    FlistPoidType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~FlistPoidType();

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

     //@}

  private:
    // class members
    EDR_EXPORT static const BAS::String	typeNameCM;
};
}
#endif // FLISTPOIDTYPE
