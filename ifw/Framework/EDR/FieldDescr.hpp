#ifndef EDR_FIELDDESCR_HPP
#define EDR_FIELDDESCR_HPP
/* @(#)%Portal Version: FieldDescr.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:52:45 % */
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: LRP
//------------------------------------------------------------------------------
// Module Description:
//   Definition of the class FieldDescr.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Stefan Deigmueller
//
// $RCSfile: FieldDescr.hpp,v $
// $Revision: 1.13 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.14  2004/09/08  ammon
// PRSF00124011  Add get/setCompactPoid
//
// Revision 1.13  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.12  2001/04/24 14:13:14  sd
// - Long renamed to Integer
//
// Revision 1.11  2001/04/19 14:17:37  sd
// - setXXXX() and getXXXX() functions of the FieldDescr are now const
//   functions.
//
// Revision 1.10  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.9  2001/04/11 10:49:50  sd
// - Member numParametersM removed.
//
// Revision 1.8  2001/03/20 15:01:32  sd
// - ByteBuffer introduced
//
// Revision 1.7  2001/03/19 16:12:09  sd
// - Interface for addParameter() changed.
//
// Revision 1.6  2001/03/16 11:21:36  sd
// - New function implicitLength() in interface
//
// Revision 1.5  2001/03/15 15:15:43  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#if !defined EDR_EXPORT
  #if defined(WINDOWS)
    #if !defined(EDR_INTERNAL)
      #define EDR_EXPORT __declspec(dllimport)
    #else
      #define EDR_EXPORT __declspec(dllexport)
    #endif
  #else
    #define EDR_EXPORT 
  #endif
#endif

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif
#ifndef   BAS_IDENTIFIER_H
  #include "BAS/Identifier.hpp"
#endif
#ifndef   EDR_PARAMETER_HPP
  #include "EDR/Parameter.hpp"
#endif
#ifndef   EDR_COMPACTPOID_HPP
  #include "EDR/CompactPoid.hpp"
#endif
#ifndef   _PCM_H
  #include "pcm.h"
#endif

namespace EDR
{
class Token;
class ByteBuffer;

/** <b><tt>FieldDescr</tt></b> is used to store the information about a 
 *  single field of a datablock. It is a base class for all datatypes used
 *  in file descriptions.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: FieldDescr.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.13 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class FieldDescr D_THREADINFO
{
  D_SINGLETHREADED

  public:

    enum DatatypeT
    {
      TYPE_STRING    = 0x0001,
      TYPE_INTEGER   = 0x0002,
      TYPE_DATE      = 0x0004,
      TYPE_DECIMAL   = 0x0008,
      TYPE_BLOB      = 0x0010,
      TYPE_DATABLOCK = 0x0020,
      TYPE_POID      = 0x0040
    };

    /**@name FieldDescr constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the field
     */
    FieldDescr( const BAS::String& name = BAS::NULL_STRING  ); 

    /** Destructor
     */
    virtual ~FieldDescr();

    //@}

    /**@name FieldDescr public methods */
    //@{

    /** Get the name of the field description
     *  @return Reference to the name string
     */
    const BAS::String& name() const;

    /** Get the typename of the datatype
     *  @return Reference to the name
     */
    virtual const BAS::String& typeName() const = 0;

    /** Get the Infranet PCM equivalent of the stored field
     * @return long value with the correct field
     */
    static short GetPCMDataType(int64 datatype);

    /** Get the supported EDR container datatypes
     *  @return long value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const = 0;

    /** Create a new instance of this datatype
     *  @param name The name of the field in input record
     *  @return Pointer to the created instance
     */
    virtual FieldDescr* create( const BAS::String& name ) const = 0;
    
    /** Add a new parameter to the datatype
     *  @param parameterList The list with parameters
     *  @param failure Buffer for returning the failure string
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addParameter( const ParameterList& paramterList,
                               BAS::String&              failure );

    /** Check whether the string type is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool isValid() const = 0;

    /** Get a string value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getString( const BAS::String& value,
                            size_t            pos,
                            size_t            len,
                            BAS::String&       buffer ) const;

    /** Set a string field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setString( ByteBuffer&   buffer,
                            size_t            len,
                            const BAS::String& value ) const;
    
    /** Get a long value from the input record
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

    /** Set a long field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setLong( ByteBuffer& buffer,
                          size_t          len,
                          int64            value ) const;

    /** Get a date/time value from the input record
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer
     *  @param len The length of the field
     *  @param buffer Buffer for returning the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDate( const BAS::String& value,
                          size_t            pos,
                          size_t            len,
                          BAS::DateTime&     buffer ) const;

    /** Set a date field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param date The output date
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDate( ByteBuffer&     buffer,
                          size_t              len,
                          const BAS::DateTime& date ) const;

    /** Get a decimal value from the input record
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

    /** Set a decimal field in a output buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDecimal( ByteBuffer&    buffer,
                             size_t             len,
                             const BAS::Decimal& value ) const;

    /** Get a CompactPoid value from the input record
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

    /** Set a CompactPoid field in a output buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setCompactPoid( ByteBuffer&             buffer,
                                 size_t                  len,
                                 const EDR::CompactPoid& value ) const;

	virtual bool getPoid(const BAS::String& value,
						 size_t pos,
						 size_t len,
						 BAS::Identifier& buffer) const;

	virtual bool setPoid(ByteBuffer& buffer,
						 size_t len,
						 const BAS::Identifier& value) const;

    /** Check if the field has an implicit field length
     *  @return <b>true</b> if implicit field lenght, <b>false</b> otherwise
     */
    virtual bool hasImplicitLength() const;

    /** Check if the field has a fixed field length
     *  @return <b>true</b> if implicit field lenght, <b>false</b> otherwise
     */
    virtual bool hasFixedLength() const;

    /** Get the implict length of the input field
     *  @param value The input data from the token 
     *  @param pos The starting position inside the buffer
     *  @return The total length of the datatype (>0), 0 on error
     */

// CodeReview - 08.2001 - mwriedt - V - 01.23 const method?
    virtual size_t implicitLength( const BAS::String& value,
                                   size_t            pos );

    /** Get the information about this field
     *  @param value Return buffer for the information
     */
    virtual void fieldInfo( BAS::String& value ) const;

    /** Get the length of the field
     *  @return The length of the field
     */ 
    size_t len() const;

    /** Get the maximum length of the field
     *  @return The maximum length of the field
     */
    size_t getMaxLen() const;


    /** Get the rank of the field
     *  @return The rank of the field
     */ 
    size_t rank() const;

    /** Set the rank of the field
     *  @param rank The new rank of the field
     */ 
    void rank( size_t rank );

    /** Set the maximum length  of the field
     *  @param rank The new length of the field
     */
    void setMaxLen( size_t len );


    //@}

  protected:

    // instance members
    BAS::String    nameM;
    size_t        rankM;
    size_t        lenM;
    size_t        maxLenM;   // Maximum allowed length for this field

};

//==============================================================================
// Get the name of the field description
//==============================================================================
inline const BAS::String&
FieldDescr::name() const
{
  return nameM;
}

//==============================================================================
// Get the length of the field
//==============================================================================
inline size_t
FieldDescr::len() const
{
  return lenM;
}

//==============================================================================
// Get the rank of the field
//==============================================================================
inline size_t
FieldDescr::rank() const
{
  return rankM;
}

//==============================================================================
// Set the rank of the field
//==============================================================================
inline void
FieldDescr::rank( size_t rank )
{
  rankM = rank;
}

//==============================================================================
// Get the maximum length of the field
//==============================================================================
inline size_t
FieldDescr::getMaxLen() const
{
  return maxLenM;
}

//==============================================================================
// Set the maximum length  of the field
//==============================================================================
inline void
FieldDescr::setMaxLen( size_t len )
{
  maxLenM = len;
}

}
#endif // FIELDDESCR_HPP
