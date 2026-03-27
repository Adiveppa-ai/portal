/* @(#)%Portal Version: DiameterDecimalType.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:43:30 % */
#ifndef EDR_DIAMETERDECIMALTYPE_HPP
#define EDR_DIAMETERDECIMALTYPE_HPP
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
//   Declaration of the class DiameterDecimalType
//
//------------------------------------------------------------------------------
// Revision        1.0  2005/01/30 mliu
// PRSF000152956   Created.
//
//==============================================================================

#ifndef   EDR_DIAMETERFIELDDESCR_HPP
  #include "EDR/DiameterFieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>DiameterDecimalType</tt></b> is the DiameterDecimal datatype used in input files.
 *
 */
class DiameterDecimalType : public DiameterFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    DiameterDecimalType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~DiameterDecimalType();

    //@}
    
    /**@name DiameterDecimalType public methods */
    //@{
    
    /** Create a new instance
     *  @param name The name of the input field inside the input record
     *  @return Pointer to the created instance
     */
    virtual FieldDescr* create( const BAS::String& name ) const;

    /** Get the name of the datatype
     *  @return Reference to the name
     */
    virtual const BAS::String& typeName() const;

    /** Check whether the type is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool isValid() const;

    /** Get the supported EDR container datatypes
     *  @return int64 value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const;

    /** Get a floating point value as a decimal from the input record
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

    /** Set a decimal value as a floating point data in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setDecimal( ByteBuffer&    buffer,
                             size_t             len,
                             const BAS::Decimal& value ) const;

    //@}

  private:

    // class member
    EDR_EXPORT static const BAS::String typeNameCM;

};
}
#endif // DIAMETERDECIMALTYPE
