#ifndef EDR_BININTEGERTYPE_HPP
#define EDR_BININTEGERTYPE_HPP
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
//   Declaration of the class BinIntegerType.
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
// $RCSfile: BinIntegerType.hpp,v $
// $Revision: 1.2 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: BinIntegerType.hpp,v $
// Revision 1.2  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.1  2001/04/24 15:36:26  sd
// - New binary integer datatype added
//
//==============================================================================

#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>BinIntegerType</tt></b> is used to read binary stored integer
 *  values from streams.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: BinIntegerType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class BinIntegerType : public FieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

// CodeReview - 08.2001 - mwriedt - C - missing in doc

  public:
    /**@name BinIntegerType constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    BinIntegerType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~BinIntegerType();

    //@}


    /**@name BinIntegerType public methods */
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
     *  @return long value with bits specifing the supported datatypes
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
     */
    virtual bool setLong( ByteBuffer&  buffer,
                          size_t           len,
                          int64             value ) const;

    //@}

  public: // public because of the SUN compiler
    enum ByteOrderT
    {
      UNKNOWN,
      LSB_LO,
      LSB_HI
    };

  protected:
    /* Get the byte order constant by its name
     * @param name The name of the byte order
     * @return The byte order constant, UNKNOWN on failure
     */
// CodeReview - 08.2001 - mwriedt - I - could be static
    ByteOrderT byteOrderByName( const BAS::String& name ) const;

  private:
    // Instance members
    ByteOrderT byteOrderM;

    // Class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}
#endif // BININTEGERTYPE_HPP
