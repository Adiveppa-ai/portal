/* @(#)%Portal Version: DiameterTimeType.hpp:NewPipelineVelocityInt:3:2006-Sep-18 22:43:17 % */
#ifndef EDR_DIAMETERTIMETYPE_HPP
#define EDR_DIAMETERTIMETYPE_HPP
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
//   Declaration of the class DiameterTimeType
//
//------------------------------------------------------------------------------
// Revision       1.0  2005/01/30 mliu
// PRSF000152956  Created.
//
//==============================================================================

#ifndef   EDR_DIAMETERFIELDDESCR_HPP
  #include "EDR/DiameterFieldDescr.hpp"
#endif

namespace EDR
{
/** <b><tt>DiameterTimeType</tt></b> is the DiameterTime datatype used in input files.
 *
 */
class DiameterTimeType : public DiameterFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    DiameterTimeType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~DiameterTimeType();

    //@}
    
    /**@name DiameterTimeType public methods */
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

    /** Get the supported EDR container datatypes
     *  @return int64 value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const;

    /** Convert a DiameterTime tag or value byte string to a long.
     *  @param byteStr The output data buffer (must be at least len long)
     *  @param len     The length for the coded string
     */
    int64 bytesToLong(unsigned char* byteStr,
                          const int64 len ) const;

   /** Get a date value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDate( const BAS::String& value,
                          size_t             pos,
                          size_t             len,
                          BAS::DateTime&     buffer ) const;

    /** Set a date field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The value to set
     */
    virtual bool setDate( ByteBuffer&           buffer,
                          size_t                len,
                          const BAS::DateTime&  value ) const;

    //@}

  private:

    // class members
    EDR_EXPORT static const BAS::String typeNameCM;

};
}
#endif // EDR_DIAMETERTIMETYPE_HPP
