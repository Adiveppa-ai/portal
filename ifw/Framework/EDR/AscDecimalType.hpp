#ifndef EDR_ASCDECIMALTYPE_HPP
#define EDR_ASCDECIMALTYPE_HPP
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
//   Declaration of the class AscDecimalType.
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
// $RCSfile: AscDecimalType.hpp,v $
// $Revision: 1.5 $
// $Author: sd $
// $Date: 2001/12/18 16:03:22 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AscDecimalType.hpp,v $
// Revision 1.5  2001/12/18 16:03:22  sd
// - PETS #42574 - Enhancements for LERG support
//
// Revision 1.4  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.3  2001/06/21 14:37:34  sd
// - Write on reject
//
// Revision 1.2  2001/05/02 14:01:03  sd
// - New parameters for the decimal type added.
//
// Revision 1.1  2001/04/24 13:30:28  sd
// - Types renamed to AscXXXXX
//
// Revision 1.10  2001/04/19 14:21:25  sd
// - Doc++ bugs fixed
//
// Revision 1.9  2001/04/19 14:17:37  sd
// - setXXXX() and getXXXX() functions of the FieldDescr are now const
//   functions.
//
// Revision 1.8  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.7  2001/03/20 15:01:32  sd
// - ByteBuffer introduced
//
// Revision 1.6  2001/03/19 16:12:09  sd
// - Interface for addParameter() changed.
//
// Revision 1.2  2000/12/06 09:33:41  sd
// - Backup version
//
//==============================================================================

#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>AscDecimalType</tt></b> is the decimal datatype used in input
 *  files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AscDecimalType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.5 $</font></td>
 *  <td><font size=-1>$Date: 2001/12/18 16:03:22 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class AscDecimalType : public FieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name AscDecimalType constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AscDecimalType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AscDecimalType();

    //@}

    /**@name AscDecimalType public methods */
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

    /** Set a decimal field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param value The output value
     */
    virtual bool setDecimal( ByteBuffer&    buffer,
                             size_t             len,
                             const BAS::Decimal& value ) const;

    /** Get the information about this field
     *  @param value Return buffer for the information
     */
    virtual void fieldInfo( BAS::String& value ) const;

    //@}

  private:

    // instance members
    BAS::String                  outBufferM;
    bool                        withPointM;
    int                         precisionM;
    char                        padCharM;
    char                        pointCharM;
    bool                        roundM;
    BAS::Decimal::RoundingMethod roundingMethodM;

    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}
#endif // ASCDECIMALTYPE_HPP
