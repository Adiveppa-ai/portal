/* @(#)%Portal Version: Value.hpp:NewPipelineVelocityInt:6:2006-Sep-18 22:53:06 % */
#ifndef EDR_VALUE_HPP
#define EDR_VALUE_HPP
//==============================================================================
//
// Copyright (c) 1996, 2024, Oracle and/or its affiliates. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Value.
//------------------------------------------------------------------------------
// Revision       1.21  2012/05/11 Santanu 
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER 
//
// Revision       1.20  2009/04/28 jlan
// bug8451089     Reset serializedBufferM upon reset call (clear()) to be complete
//
// Revision       1.19  2006/08/10 bertm
// PRSF00224380   Changed ostream to BAS::String to improve performance
//
// Revision       1.18  2005/04/1 rtang
// PRSF00161772   Platform support for improving pre-suspense performance 
//
// Revision       1.17  08-Sep-2004   ammon
// PRSF00124011   Backout PRSF00194975 change
//
// Revision       1.16  27-Apr-2004   6.7_FP1_EBF   ammon
// PRSF00104975   Test for flushRaw was always false
//
// Revision       1.15  10-Mar-2004   6.5_FP3_EBF  ammon
// PRSF00098531   Move String specific XML code to StringValue
//
// Revision       1.14  17-Feb-2004   6.5_FP3_EBF  ammon
// PRSF00092698   More XML serialization performance
//
// Revision       1.13  06-Feb-2004   6.5_FP3_EBF  ammon
// PRSF00090995   More XML performance
//
// Revision       1.12  02-Feb-2004   6.5_FP3_EBF  ammon
// PRSF00090216   XML performance
//
// Revision       1.11  01-Jul-2003   6.5_FP3   keshav
// PRSF00045126   Differentiate between MISSING and EMPTY fields
//
// Log 2002/08/30 cdiab
// - modified the clear() methode to really reinitialise the token fields for
//   the next use
// -:modified token() to always return the tokenM, as now it all fields are
//   initialized from the previous use in clear(), the contained values are
//   always correct
//
// Revision 1.9  2002/03/13 08:52:19  sd
// - ClearCase Transition checkin
//
// Revision 1.8  2002/01/15 09:28:23  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.7  2001/11/09 15:32:33  sd
// - Token cache introduced
//
// Revision 1.6  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.5  2001/08/07 12:58:46  mwriedt
// - PETS #37618: Code Review.
//
// Revision 1.4  2001/07/02 10:51:48  sd
// - PETS #36553/2 Input of AscDate("%H%M%S") failed without error
//
// Revision 1.3  2001/04/12 12:38:14  sd
// - Update for the new module structure
//
// Revision 1.2  2001/03/30 12:49:44  sd
// - Changes to support duplication of EDR containers
//
// Revision 1.1  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.18  2001/03/20 15:01:32  sd
// - ByteBuffer introduced
//
// Revision 1.3  2000/10/20 10:02:01  sd
// - Initial revision.
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   EDR_COMPACTPOID_HPP
  #include "EDR/CompactPoid.hpp"
#endif
#ifndef   EDR_TOKEN_HPP
  #include "EDR/Token.hpp"
#endif
#ifndef   EDR_BYTEBUFFER_HPP
  #include "EDR/ByteBuffer.hpp"
#endif
#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
#ifndef   EDR_METADATA_H
  #include "EDR/MetaData.hpp"
#endif

namespace EDR
{
class Token;
class Datablock;
class MetaData;
class Factory;

/** <b><tt>Value</tt></b> is the base class for all data values used in
 *  Datablocks.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Value.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:47 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>                
 */
class Value D_THREADINFO
{
  D_SINGLETHREADED

  public:

    enum InternalStateT
    {
      CLEARED,
      CONNECTED,
      INITIALIZED,
      SET,
      RESTORED,
      RESTOREDASSET
    };

    // Possible state of represented data in relation to input data.
    // This state starts with UNKNOWN and must move to one of the other
    // three states as input data is examined when populating this EDR value.
    // Business logic may require that a default value be populated into
    // this EDR field if input data was either not supplied or was empty.
    // While it does not make sense for this state to change again until the
    // field is recycled (which only happens when the EDR container is
    // returned to the pool), such a state change is not blocked actively.
    //
    enum InputStateT
    {
                // Meaning                         Examples for input field MName
      UNKNOWN,  // Input data not yet processed.
      MISSING,  // Not supplied in input data.     FName=ABC, LName=GHI
      EMPTY,    // Supplied, but with no value.    FName=ABC, MName=, LName=DEF
      GIVEN     // Supplied with a value.          FName=ABC, MName=DEF, LName=GHI
    };

    /**@name Value constructors and destructor */
    //@{

    /** Constructor
     */
    Value();

    /** Constructor
     */
    Value(const size_t length, const short type);


    /** Destructor
     */
    virtual ~Value();

    //@}

    /**@name Value public methods */
    //@{

    /** Clear the value
     */
    void clear();

    /** Connect the value with a field from an input record
     *  @param token The token representing the input record
     *  @param fieldDescr The input fields description (datatype)
     *  @param pos Position of the field in the input record
     *  @param len Length of the field in the input record
     */
    void connect( Token*      token, 
                  FieldDescr* fieldDescr,
                  size_t          pos,
                  size_t          len );

    /** Get the meta data associated with the class. This performs
     * transactions as neccessary for byte swapping (ie it makes it do
     * useful stuff on windowz.
     */
    virtual EDR::MetaData& getMetaData();

    /** Get the field description connected to this EDR value
     *  @return Pointer to the field descripiton
     */
    FieldDescr* fieldDescr() const;

    /** Get the token connected to this Value
     *  @return Pointer to the token
     */
    Token* token() const;

    /** Get the internal state of the EDR value
     *  @return The internal state
     */
    InternalStateT state() const;

    /** Get the internal input state of the EDR value
     *  @return The internal input state
     */
    InputStateT inputState() const;

    /** Set the internal input state of this EDR value to the passed value */
    void inputState(InputStateT newState);

	/** Get the internal state of the EDR value (new style method
	 * @return the internal state
	 */
	InternalStateT getState() const;

	/** Get the name of the state. Used in output operator
	 * @return name of the internal state
	 */
	const BAS::String getStateName();

	/** Set the internal state of the EDR value
	 * @param state state to store
	 */
	void setState(InternalStateT);

    /** Clone the value
     *  @return Pointer to the cloned value
     */
    virtual Value* clone() const = 0;

    /** Get the datatype of the value
     *  @return Bitvalue specifing the datatype as defined in FieldDescr
     */
    virtual int64 datatype() const = 0;

    /** Serialize the EDR value
     *  @param out Output stream for serialization
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool serialize( std::ostream& out ) const = 0;

    /** Restore the EDR value
     *  @param in Input stream 
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool restore( std::istream& in ) = 0;

    /* Flush the data to the output byte buffer
     * @param buffer Output buffer
     * @param outField The output field description
     * @param len The length for the output data
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool flush( ByteBuffer& buffer,
                FieldDescr* outField,
                size_t          len );

    /* Copy the data from an EDR value of same type. This function is used
     * when Datablocks will by duplicated.
     * @param value The source Value 
     */
    virtual void copyData( Value* value ) = 0;

    /* Copy the data from an EDR value of same type. This function is used
     * when Datablocks will be duplicated - a thread-safe version for Solaris
     * and Linux. For aix, this memebrwise copy seems to be not thread safe and
     * the bit wise copy (copyData) is thread safe. So, for aix, we are still 
     * invoking the function 'copyData' while concurrent EDR duplication is 
     * happening. 
     * @param value The source Value
     */
    virtual void memberWiseCopyData( Value* value ) = 0;

    /** Set the a long value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setLong( int64 value );

    /** Set the a string value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setString( const BAS::String& value );

    /** Set the poid value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setCompactPoid( const EDR::CompactPoid& value );

    /** Set the a decimal value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDecimal( const BAS::Decimal& value );
    
    /** Set the a date/time value
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDate( const BAS::DateTime& value );

   /** Serialize the datablock to XML
     *  @param path   Partial xmlId
     *  @param xmlOut Output string for serialization
     *  @param factory, Edr factory for logging into pipeline log
     *  @param markedOnly , if true, only dump the marked field
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addXmlEdrItem( const char* path,
                                const size_t idx,
                                BAS::String& xmlOut,
                                Factory* factory,
                                bool markedOnly = false);

    /* Return the buffer from which this value was restored
     * @return  restoredBuffer
     */
    const char *getRestoredBuffer() const;

    /* Set the buffer from which this value was restored from
     * @param buffer The buffer to set
     * @param length The length of the buffer
     * @return  nothing
     */
    void setRestoredBuffer(const char *restoredBuffer, int length);

    /* Get the length of the restored Buffer
     * @return  length of restored Buffer
     */
    int64 getRestoredBufferLength( ) const;

    /* Return the serializedBuffer
     * @return  serializedBuffer
     */
    virtual ByteBuffer& getSerializedBuffer();

    /* Get the restoredAsSet state
     * @return  true or false
     */
    bool getRestoredAsSet( ) const;

    /** Set the data In Memory Flag
     * @param data In Memory value
     */
    void setDataInMemory(bool dataInMemory);

    //@}

    /** Get a long value
     *  @return 0
     */
    virtual int64 getLong() const noexcept(false);
    
    /** Get a decimal value
     *  @return BAS::DECIMAL_NULL
     */
    virtual const BAS::Decimal& getDecimal() const noexcept(false);

    /** Get a string value
     *  @return BAS::NULL_STRING
     */
    virtual const BAS::String& getString() const noexcept(false);

    /** Get a poid value
     *  @return NULL_IDENTIFIER
     */
    virtual const EDR::CompactPoid& getCompactPoid() const noexcept(false);

    /** Get a date/time value
     *  @return BAS::INVALID_DATETIME
     */
    virtual const BAS::DateTime& getDate() const noexcept(false);

  protected:
    /** Copy the base class data members
     */
    void copyBase(const Value *);

    /* Flush the raw data to the byte buffer
     * @param buffer Output buffer
     * @return <b>true</b>
     */
    bool flushRaw( ByteBuffer& buffer );

    /* Flush the normal EDR data to the byte buffer
     * @param buffer Output buffer
     * @param outField The output field description
     * @param len The length for the output data
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool flushNormal( ByteBuffer& buffer,
                              FieldDescr* outField,
                              size_t          len ) = 0;

    // instance members
    Token*      tokenM;
    FieldDescr* fieldDescrM;
    size_t          posM;
    size_t          lenM;

    // Allocate buffer used for XML serialization
    BAS::String xmlBufferM;

    /* Indicator of what the state of this variable is in relation to input data.
     * It starts out with a state of UNKNOWN - this is before input is examined.
     * If the input data field is not supplied, the state must move to MISSING.
     * If the input data field is supplied but without a value, the state must
     *   move to EMPTY.
     * If there is a valid input data supplied for this field, the state must
     *   move to GIVEN.
     * The state will be reset to UNKNOWN when the clear() method is invoked.
     * The state of the EDR value can be changed and queried from iScript using
     *   the setMissingInput(), setEmptyInput() and getInputState() functions.
     */
    InputStateT     inputStateM;

    InternalStateT  stateM;

    EDR::MetaData metaDataM;

    char *   restoredBufferM;   // For restoredBufferM Data
    size_t          restoredBufferLengthM;
    bool restoredDataConvertedM; // true means restored Data is converted from serial form
    ByteBuffer     serializedBufferM;
    bool dataInMemoryM; // true means data stored in Memory(timos)
    bool markedM; // true if value is in-use after read in EDR
    bool savedM; // true if the original value is saved
    bool badDataM; // true if the original value is invalid
    BAS::String originalStringM; // used to hold the original value before changing a marked field 

    friend std::ostream& operator<<( std::ostream& os, const Datablock& block );
    friend class Container;
    friend class Datablock;

    /** Get a original string value
     *  @return BAS::NULL_STRING
     */
    const BAS::String& getOriginalString() const;

    /** Set a original string value
     */
    void setOriginalString(BAS::String value);

   /** Set/Get marked flag
     */
    void setMarked(bool marked); 
    bool isMarked() const ; 

   /** Set/Get saved flag
    */
    void setSaved(bool saved); 
    bool isSaved() const ; 
   /** Set/Get bad data flag
    */
    void setBadData(bool saved); 
    bool hasBadData() const ; 


};

//==============================================================================
// Clear the value
//==============================================================================
inline void
Value::clear()
{
  // Fields which are not used will already be in CLEARED state
  //if (stateM != CLEARED)
  {
    stateM      = CLEARED;
    inputStateM = UNKNOWN;
    serializedBufferM.clear();

#ifdef TRACE

    tokenM      = 0;
    fieldDescrM = 0;
    posM        = 0;
    lenM        = 0;
  
    restoredBufferM = 0;
    restoredBufferLengthM = 0;
    restoredDataConvertedM = false;
  
    metaDataM.setFieldLength(0);

    // No need to set originalStringM to BAS::NULL_STRING here
    // as no checking is done for this anywhere. (perf reasons)

#endif

    markedM = false;
    savedM = false;
    badDataM = false;
  }
}

//==============================================================================
// Connect the value with an input field
//==============================================================================
inline void
Value::connect( Token*      token,
                    FieldDescr* fieldDescr,
                    size_t          pos,
                    size_t          len )
{
  RWPRECONDITION( token != 0 );
  RWPRECONDITION( fieldDescr != 0 );

  tokenM      = token;
  fieldDescrM = fieldDescr;
  posM        = pos;
  lenM        = len;
  stateM      = CONNECTED;

  if (lenM > 0)
    inputState(GIVEN);
  else if (lenM == 0)
    inputState(EMPTY);
  else
    inputState(MISSING);
}

//==============================================================================
// Get the field description for this field
//==============================================================================
inline FieldDescr*
Value::fieldDescr() const
{
  RWPRECONDITION( fieldDescrM != 0 );
  return fieldDescrM;
}

//==============================================================================
// Get the token connected to this value
//==============================================================================
inline Token*
Value::token() const
{
  return tokenM;
}

//==============================================================================
// Get the internal state of the EDR value
//==============================================================================
inline Value::InternalStateT
Value::state() const
{
  return stateM;
}

inline Value::InternalStateT
Value::getState() const
{
	return stateM;
}

inline void
Value::setState(InternalStateT state)
{
	stateM = state;
}

//==============================================================================
// Get the internal input state of the EDR value
//==============================================================================
inline Value::InputStateT
Value::inputState() const
{
  return inputStateM;
}

//==============================================================================
// Set the internal input state of this EDR value to the passed value
//==============================================================================
inline void
Value::inputState(Value::InputStateT newState)
{
  inputStateM = newState;
}

//==============================================================================
// Flush the raw data to the output buffer
//==============================================================================
inline bool
Value::flushRaw( ByteBuffer& buffer )
{
  RWPRECONDITION( tokenM != 0 );

  buffer.append( tokenM->value().data() + posM, lenM );

  return true;
}

//==============================================================================
// Flush the value to the output buffer
//==============================================================================
inline bool
Value::flush( ByteBuffer& buffer,
                  FieldDescr* outField,
                  size_t          len )
{
  try
  {
    if ( stateM == Value::CONNECTED || stateM == Value::INITIALIZED )
    {
      if ( fieldDescrM == outField )
      {
        return flushRaw( buffer );
      }
    }

    return flushNormal( buffer, outField, len );
  }
  
  catch ( BAS::StringList errList )
  {
    return false;
  }

  return true;
}

//==============================================================================
// Get the restoredBuffer
//==============================================================================
inline const char *
Value::getRestoredBuffer() const
{
  return (const char *)restoredBufferM;
}
//==============================================================================
// Set the restoredBuffer
//==============================================================================
inline void
Value::setRestoredBuffer(const char *restoredBuffer, int length)
{
  restoredBufferM  = (char *)restoredBuffer;
  restoredBufferLengthM  = length;
  restoredDataConvertedM = false;

}

//==============================================================================
// Get the length of the restored Buffer
//==============================================================================
inline int64
Value::getRestoredBufferLength()  const
{
  return restoredBufferLengthM;
}
//==============================================================================
// Get the serializedBuffer
//==============================================================================
inline EDR::ByteBuffer&
Value::getSerializedBuffer() 
{
  return serializedBufferM;
}

//==============================================================================
// Get the restoredAsStateM value
//==============================================================================
inline bool
Value::getRestoredAsSet()  const
{
  if (stateM == RESTOREDASSET)
    return true;
  else
  return false;
}

//==============================================================================
// Set data in Memory flag
//==============================================================================
inline void
Value::setDataInMemory( bool dataInMemory )
{
  dataInMemoryM = dataInMemory;
}

//==============================================================================
// Set/Get marked flag 
//==============================================================================
inline void
Value::setMarked( bool marked )
{
  markedM = marked;
}
inline bool
Value::isMarked() const
{
  return markedM;
}
//==============================================================================
// Set/Get saved flag 
//==============================================================================
inline void
Value::setSaved(bool saved )
{
  savedM = saved;
}
inline bool
Value::isSaved() const
{
  return savedM;
}
//==============================================================================
// Set/Get bad data flag 
//==============================================================================
inline void
Value::setBadData( bool badData )
{
  badDataM = badData;
}
inline bool
Value::hasBadData() const
{
  return badDataM;
}

//==============================================================================
// Get the original string value
//==============================================================================
inline const BAS::String&
Value::getOriginalString() const
{
  return originalStringM;
}
}
#endif // VALUE_HPP 
