#ifndef EDR_ASNBLOBTYPE_HPP
#define EDR_ASNBLOBTYPE_HPP
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
//   Declaration of the class AsnBlobType.
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
// $RCSfile: AsnBlobType.hpp,v $
// $Revision: 1.3 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnBlobType.hpp,v $
// Revision 1.3  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.2  2001/07/02 11:51:36  cdiab
// PETS #36565 : corrected PETS ticket log (no change over last commit).
//
// Revision 1.1  2001/07/02 10:35:23  cdiab
// PETS #PT36565 : added support for indefinite length objects, and
// added new type ASN_Blob (AsnBlobType.*pp).
//
// Revision 1.0  2001/07/02 14:17:37  cdiab
// this class manages objects corresponding to a complete substrucrture block.
//
//==============================================================================


#ifndef   EDR_ASNFIELDDESCR_HPP
  #include "EDR/AsnFieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>AsnBlobType</tt></b> is the ASN_Blob datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnBlobType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class AsnBlobType : public AsnFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AsnBlobType( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AsnBlobType();

    //@}

    /**@name Classname public methods */
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

    /** Get the implict length of the input field
     *  @param value The input data from the token 
     *  @param pos The starting position inside the buffer
     *  @return The total length of the datatype (>0), 0 on error
     */
    virtual size_t implicitLength( const BAS::String& value,
                                   size_t            pos );
 
    /** Add a new parameter to the datatype
     *  @param parameter The parameter list to add
     *  @param failure Buffer for returning the failure string
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addParameter( const ParameterList& parameter,
                               BAS::String&              failure );

    /** Get the supported EDR container datatypes
     *  @return long value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const;

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
    //@}

  private:

    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
};
}
#endif // AsnBlobType
