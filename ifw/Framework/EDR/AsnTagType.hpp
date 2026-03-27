#ifndef EDR_ASNTAGTYPE_HPP
#define EDR_ASNTAGTYPE_HPP
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
//   Declaration of the class AsnTagType.
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
// $RCSfile: AsnTagType.hpp,v $
// $Revision: 1.14 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnTagType.hpp,v $
// Revision 1.14  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.13  2001/05/03 08:08:30  cdiab
// added setLong() methode to write the Tag/Length fields to output (trick).
//
// Revision 1.12  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.11  2001/03/27 11:03:59  sd
// - Backup version
//
// Revision 1.10  2001/03/23 08:27:09  cdiab
// corrected error in asn tag generation, and removed inline from AsnTagType.
//
// Revision 1.9  2001/03/22 11:21:46  cdiab
// I have forgotten that the name param in the constructor must have a default
// of NULL (necessary for DataDescr.cpp).
//
// Revision 1.8  2001/03/22 11:10:05  cdiab
// constructor methode has a default tag of (-1) ie invalid.
//
// Revision 1.7  2001/03/22 11:07:27  cdiab
// added the possibility to use ASN_Tag as a basic type in the BlockDescription.
//
// Revision 1.6  2001/03/19 16:56:32  cdiab
// now the basic types can get a tag through the addParameter() methode.
//
// Revision 1.5  2001/03/19 12:39:01  cdiab
// set and get functions are written.
//
// Revision 1.4  2001/03/16 15:52:52  sd
// - ASN types added
//
// Revision 1.3  2001/03/16 15:04:40  cdiab
// added an inline function to generate the regular expression without giving
// the value of the tag.
//
// Revision 1.2  2001/03/16 14:25:26  cdiab
// tagM was declared static, and that was an error.
//
// Revision 1.1  2001/03/16 14:05:03  cdiab
// access the TL part of an ASN.1 object and processes it as a whole.
//
// Revision 1.0  2001/03/16 10:43:40  cd
// - Creation
//==============================================================================

#ifndef   EDR_ASNFIELDDESCR_HPP
  #include "EDR/AsnFieldDescr.hpp"
#endif
namespace EDR
{
class ByteBuffer; // from ByteBuffer.hpp

/** <b><tt>ASN_TagType</tt></b> is the AsnTagType datatype used in input files.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnTagType.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.14 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class AsnTagType : public AsnFieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AsnTagType( const BAS::String& name = BAS::NULL_STRING ,
                    int                tag = (-1) ); 

    /** Destructor
     */
    virtual ~AsnTagType();

    //@}

    /**@name AsnTagType public methods */
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

    /** Get the supported EDR container datatypes
     *  @return long value with bits specifing the supported datatypes
     */
    virtual int64 supportedDatatypes() const;

    /** Used as a "trick" to set a the Tag and Len fields in a byte buffer
     *  (Value field is NOT set).
     *  @param buffer Output buffer
     *  @param len The length for the output data
     *  @param valLength The length of the Value field
     */
    virtual bool setLong( ByteBuffer&  buffer,
                          size_t           len,
                          int64             valLength ) const;
			  
    /** This methode is just here for coherence, and should never be used
     *  it always return false, and does nothing.
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
   //@}

  private:
    // class members
    EDR_EXPORT static const BAS::String typeNameCM;
    
};
}
#endif // AsnTagType
