#ifndef EDR_ASCDATEUNIXTYPE_HPP
#define EDR_ASCDATEUNIXTYPE_HPP
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
//   Declaration of the class AscDateUnixType.
//
// Open Points:
//   <open points>
//
// Review Status:
//   reviewed
//
//------------------------------------------------------------------------------
// Responsible: Cedric Diab
//
// $RCSfile: AscDateUnixType.hpp,v $
// $Revision: 1.3 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.3  2004/11/30 ammon
// PRSF00129273:  Add support for using local timezone instead of UTC.
//
// Revision 1.2  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.1  2001/06/22 08:46:39  cdiab
// date type object for the parser to get/set infranet style dates (in seconds
// since 1970 format). Timezone always defaults to OS timezone.
//
// Revision 1.0  2001/06/21 13:30:28  cdiab
// - creation
//
//==============================================================================

#ifndef   BAS_DATETIME_HPP
  #include "BAS/DateTime.hpp"
#endif
#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>AscDateUnixType</tt></b> is the date datatype used in Unix input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AscDateUnixType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class AscDateUnixType : public FieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name AscDateUnixType constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AscDateUnixType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AscDateUnixType();

    //@}

    /**@name AscDateUnixType public methods */
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
     *  @param parameterList A list with parameters
     *  @param failure Buffer for returning the failure string
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addParameter( const ParameterList& parameterList,
                               BAS::String&              failure );

    /** Check whether the string type is valid or not
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool isValid() const;

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

    /** Set a date/time field in a byte buffer
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param date The output date
     */
    virtual bool setDate( ByteBuffer&     buffer,
                          size_t              len,
                          const BAS::DateTime& date ) const;


    /** Get the information about this field
     *  @param value Return buffer for the information
     */
    virtual void fieldInfo( BAS::String& value ) const;

    //@}

  private:
    // instance members
    BAS::String		outBufferM;
    char                padCharM;
    bool                useLocalZoneM;

    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
    EDR_EXPORT static const BAS::String localZoneCM;
};
}
#endif // ASCDATEUNIXTYPE_HPP
