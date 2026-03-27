#ifndef FRM_MAPPINGCONSTANT_HPP
#define FRM_MAPPINGCONSTANT_HPP

//==============================================================================
//
//          Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//          
//          This material is the confidential property of Oracle Corporation or its
//          licensors and may be used, reproduced, stored or transmitted only in
//          accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FRM
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class MappingConstant. This class is used to store
//   the constant values that are copied to the EDR container and the file
//   records when the mapping is executed.
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
// $RCSfile: MappingConstant.hpp,v $
// $Revision: 1.4 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:17 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: MappingConstant.hpp,v $
// Revision 1.4  2001/09/27 12:01:17  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.3  2001/05/17 06:50:37  sd
// - Error messages for constant mapping improved
//
// Revision 1.2  2001/05/11 07:23:23  sd
// - Types of output constants are checked now
//
// Revision 1.1  2001/05/03 16:29:24  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.2  2001/03/20 15:01:32  sd
// - EDR::ByteBuffer introduced
//
// Revision 1.1  2001/03/14 09:29:33  sd
// - Constants introduced in input mapping
//
//==============================================================================

#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   BAS_DECIMAL_HPP
  #include "BAS/Decimal.hpp"
#endif
#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif

namespace EDR
{
class Value;
class ByteBuffer;
}
namespace FRM
{
/** <b><tt>MappingConstant</tt></b> is used to store the constants that are
 *  used to initialize EDR container and file record fields when the mapping is 
 *  executed.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MappingConstant.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:17 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class MappingConstant D_THREADINFO
{
  public:
    /**@name MappingConstant constructors and destructor */
    //@{

    /** Constructor
     */
    MappingConstant();
    
    /** Destructor
     */
    virtual ~MappingConstant();

    //@}


    /**@name MappingConstant public methods */
    //@{

    /** Transfer the constant value to an EDR value
     *  @param value The target EDR value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool transfer( EDR::Value* value ) = 0;

    /** Transfer the constant value to a byte buffer
     *  @param buffer The output byte buffer
     *  @param descr The target field description
     *  @param len The length of the output field
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool flush( EDR::ByteBuffer& buffer,
                        EDR::FieldDescr* descr,
                        size_t          len ) = 0;

    /** Get the datatype of the mapping constant
     *  @return The datatype of the constant
     */
    virtual EDR::FieldDescr::DatatypeT datatype() const = 0;

    /** Get the mapping constants value as string
     *  @return Value as string
     */
    virtual BAS::String value() const = 0;

    //@}

  protected:
};

/** <b><tt>StringMappingConstant</tt></b> is the mapping constant for string
 *  values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MappingConstant.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:17 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class StringMappingConstant : public MappingConstant
{
  public:
    /**@name StringMappingConstant constructors and destructor */
    //@{

    /** Constructor
     *  @param value The string value
     */
    StringMappingConstant( const BAS::String& value );
    
    //@}


    /**@name StringMappingConstant public methods */
    //@{

    /** Transfer the constant value to an EDR value
     *  @param value The target EDR value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool transfer( EDR::Value* value );

    /** Transfer the constant value to a byte buffer
     *  @param buffer The output byte buffer
     *  @param descr The target field description
     *  @param len The length of the output field
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool flush( EDR::ByteBuffer& buffer,
                        EDR::FieldDescr* descr,                           
                        size_t          len );

    /** Get the datatype of the mapping constant
     *  @return The datatype of the constant
     */
    virtual EDR::FieldDescr::DatatypeT datatype() const;

    /** Get the mapping constants value as string
     *  @return Value as string
     */
    virtual BAS::String value() const ;

    //@}

  private:
    // Instance members
    BAS::String dataM;
};

/** <b><tt>DecimalMappingConstant</tt></b> is the mapping constant for
 *  decimal values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MappingConstant.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:17 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class DecimalMappingConstant : public MappingConstant
{
  public:
    /**@name DecimalMappingConstant constructors and destructor */
    //@{

    /** Constructor
     *  @param value The constant value
     */
    DecimalMappingConstant( const BAS::Decimal& value );
    
    //@}


    /**@name DecimalMappingConstant public methods */
    //@{

    /** Transfer the constant value to an EDR value
     *  @param value The target EDR value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool transfer( EDR::Value* value );

    /** Transfer the constant value to a byte buffer
     *  @param buffer The output byte buffer
     *  @param descr The target field description
     *  @param len The length of the output field
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool flush( EDR::ByteBuffer& buffer,
                        EDR::FieldDescr* descr,
                        size_t          len );

    /** Get the datatype of the mapping constant
     *  @return The datatype of the constant
     */
    virtual EDR::FieldDescr::DatatypeT datatype() const;

    /** Get the mapping constants value as string
     *  @return Value as string
     */
    virtual BAS::String value() const ;

    //@}

  private:
    // Instance members
    BAS::Decimal dataM;
};

/** <b><tt>LongMappingConstant</tt></b> is the mapping constant for long
 *  values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MappingConstant.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:17 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class LongMappingConstant : public MappingConstant
{
  public:
    /**@name LongMappingConstant constructors and destructor */
    //@{

    /** Constructor
     *  @param value The constant value
     */
    LongMappingConstant( int64 value );
    
    //@}

    /**@name LongMappingConstant public methods */
    //@{

    /** Transfer the constant value to an EDR value
     *  @param value The target EDR value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool transfer( EDR::Value* value );

    /** Transfer the constant value to a byte buffer
     *  @param buffer The output byte buffer
     *  @param descr The target field description
     *  @param len The length of the output field
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool flush( EDR::ByteBuffer& buffer,
                        EDR::FieldDescr* descr,
                        size_t          len );

    /** Get the datatype of the mapping constant
     *  @return The datatype of the constant
     */
    virtual EDR::FieldDescr::DatatypeT datatype() const;

    /** Get the mapping constants value as string
     *  @return Value as string
     */
    virtual BAS::String value() const ;

    //@}

  private:
    // Instance members
    int64 dataM;
};

/** <b><tt>DateMappingConstant</tt></b> is the mapping constant for DateTime
 *  values.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: MappingConstant.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:17 $</font></td>
# *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class DateMappingConstant : public MappingConstant
{
  public:
    /**@name DateMappingConstant constructors and destructor */
    //@{

    /** Constructor
     *  @param value The constant value
     */
    DateMappingConstant( const BAS::DateTime& value );
    
    //@}


    /**@name DateMappingConstant public methods */
    //@{

    /** Transfer the constant value to an EDR value
     *  @param value The target EDR value
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool transfer( EDR::Value* value );

    /** Transfer the constant value to a byte buffer
     *  @param buffer The output byte buffer
     *  @param descr The target field description
     *  @param len The length of the output field
     *  @return <b>true</b> on success <b>false</b> otherwise
     */
    virtual bool flush( EDR::ByteBuffer& buffer,
                        EDR::FieldDescr* descr,
                        size_t          len );

    /** Get the datatype of the mapping constant
     *  @return The datatype of the constant
     */
    virtual EDR::FieldDescr::DatatypeT datatype() const;

    /** Get the mapping constants value as string
     *  @return Value as string
     */
    virtual BAS::String value() const ;

    //@}

  private:
    // Instance members
    BAS::DateTime dataM;
};
}
#endif // MAPPINGCONSTANT_HPP
