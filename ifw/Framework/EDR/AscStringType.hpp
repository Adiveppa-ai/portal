#ifndef EDR_ASCSTRINGTYPE_HPP
#define EDR_ASCSTRINGTYPE_HPP
//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class AscStringType.
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
// $RCSfile: AscStringType.hpp,v $
// $Revision: 1.2 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AscStringType.hpp,v $
// Log 2002/07/18 cdiab
// modified the type to accept 2 additional optional parameters: 
//  - the character to be used for padding (default=' ')
//  - a boolean indicating that the string is to be Left justified (default=true) 
// changes are necessary for CIBER where we have Right justification with '0' pad
//
// Revision 1.2  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.1  2001/04/24 13:30:28  sd
// - Types renamed to AscXXXXX
//
// Revision 1.10  2001/04/19 14:17:37  sd
// - setXXXX() and getXXXX() functions of the FieldDescr are now const
//   functions.
//
// Revision 1.9  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.8  2001/03/20 15:01:32  sd
// - ByteBuffer introduced
//
// Revision 1.7  2001/03/19 16:12:09  sd
// - Interface for addParameter() changed.
//
// Revision 1.6  2001/03/16 15:52:52  sd
// - ASN types added
//
// Revision 1.1  2000/11/30 17:56:47  sd
// - Creation of Base.
//
//==============================================================================

#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>AscStringType</tt></b> is the string datatype used in input 
 *  files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AscStringType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class AscStringType : public FieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name AscStringType constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AscStringType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AscStringType();

    //@}

    /**@name AscStringType public methods */
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
     */
    virtual bool setString( ByteBuffer&   buffer,
                            size_t            len,
                            const BAS::String& value ) const;

    /** Get the information about this field
     *  @param value Return buffer for the information
     */
    virtual void fieldInfo( BAS::String& value ) const;

    //@}

  private:
    // instance members
    char       padCharM;         // default=' ';
    bool       isLeftJustifiedM; // default=true;

    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}
#endif // ASCSTRINGTYPE_HPP
