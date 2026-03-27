#ifndef EDR_POIDVALUE_HPP
#define EDR_POIDVALUE_HPP
/* @(#)%Portal Version: PoidValue.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:45:25 % */

//=============================================================================
//
// Copyright (c) 1996, 2024, Oracle and/or its affiliates. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: EDR
//-----------------------------------------------------------------------------
// Module Description:
//  Global Data Container
//  Support for POID in EDR
//
// Current Issues:
//  None
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Shivaram Radhakrishna
// Backup-Responsible:
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 11-May-2012  Santanu             Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
// 24-Sep-2004  ammon               PRSF00132512 - add support for XML Serialize
// DD-Jul-2002  Shivaram            First version
//
//=============================================================================


#ifndef   EDR_VALUE_HPP
  #include "EDR/Value.hpp"
#endif

namespace EDR {

class PoidValue : public Value  D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name PoidValue constructors and destructor */
    //@{

    /** Default constructor
     */
    PoidValue();

    /** Destructor
     */
    virtual ~PoidValue();

    //@}


    /**@name PoidValue public methods */
    //@{

    /** Get the datatype of the value
     *  @return Bitvalue specifing the datatype as defined in FieldDescr
     */
    virtual int64 datatype() const;

    /** Clone the  poid value
     *  @return Pointer to the cloned  poid value
     */
    virtual Value* clone() const;

    /** Set the poid value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setCompactPoid( const EDR::CompactPoid&  value );

    /** Get the Poid value
     *  @return The Poid value
     */
    virtual const EDR::CompactPoid& getCompactPoid() const noexcept(false);

    /** Get the  poid value as string
     *  @return Reference to string value
     */
    virtual const BAS::String& getString() const noexcept(false);

    /** Set the a string value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setString( const BAS::String& value );

    /* Copy the data from another PoidValue. This function is only used
     * when Datablocks will by duplicated. 
     * @param value The source Value 
     */
    virtual void copyData( Value* value );

    /* Copy the data from another PoidValue. This function is only used
     * when Datablocks will by duplicated - a thread-safe version for
     * Solaris and Linux.
     * @param value The source Value
     */
    virtual void memberWiseCopyData( Value* value ) noexcept(false);

    /** Serialize the EDR value
     *  @param out Output stream for serialization
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool serialize( ostream& out ) const;

    /** Restore the integer value
     *  @param in Input stream 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool restore( istream& in );

    /** Get the serialized Buffer
     *  @return the serialized buffer
     */
    virtual EDR::ByteBuffer&  getSerializedBuffer(); 

    //@}
    
  protected:

    /* Flush the data to the output byte buffer
     * @param buffer The output byte buffer
     * @param outField The output field description
     * @param len The length for the output data
     * @return Number of flushed bytes on success, <0 otherwise
     */
    virtual bool flushNormal( ByteBuffer& buffer,
                              FieldDescr* outField,
                              size_t          len );

  private:

    // instance members
    EDR::CompactPoid        dataM;
    BAS::String  stringDataM;
};
}
#endif // EDR_POIDVALUE_HPP
