#ifndef EDR_ASNFIELDDESCR_HPP
#define EDR_ASNFIELDDESCR_HPP
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
//   Declaration of the class AsnFieldDescr
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
// $RCSfile: AsnFieldDescr.hpp,v $
// $Revision: 1.15 $
// $Author: mwriedt $
// $Date: 2001/08/07 13:12:24 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: AsnFieldDescr.hpp,v $
// Revision 1.15  2001/08/07 13:12:24  mwriedt
// PETS #37618: Code Review.
//
// Revision 1.14  2001/07/04 07:52:49  sd
// - Return type of getTotalLength() corrected
//
// Revision 1.13  2001/07/02 12:29:33  cdiab
// modified formatting for doc++.
//
// Revision 1.12  2001/07/02 11:51:36  cdiab
// PETS #36565 : corrected PETS ticket log (no change over last commit).
//
// Revision 1.11  2001/07/02 10:35:23  cdiab
// PETS #PT36565 : added support for indefinite length objects, and
// added new type ASN_Blob (AsnBlobType.*pp).
//
// Revision 1.10  2001/06/11 12:49:13  cdiab
// it is now possible to give min and max size for ASN string objects, but the
// value are not yet used.
//
// Revision 1.9  2001/06/07 16:21:15  cdiab
// now tag class can be other than just Application
//
// Revision 1.8  2001/04/19 14:17:37  sd
// - setXXXX() and getXXXX() functions of the FieldDescr are now const
//   functions.
//
// Revision 1.7  2001/04/11 13:00:04  sd
// - LRP_Base renamed to Base
//
// Revision 1.6  2001/03/27 11:03:59  sd
// - Backup version
//
// Revision 1.5  2001/03/21 08:58:20  cdiab
// Modified type for output buffer of set methodes (now automatic length check).
// + added doc++ type comments in header files.
//
// Revision 1.4  2001/03/19 16:56:32  cdiab
// now the basic types can get a tag through the addParameter() methode.
//
// Revision 1.3  2001/03/19 12:39:01  cdiab
// set and get functions are written.
//
// Revision 1.2  2001/03/16 14:08:00  cdiab
// removed calculation of implicitlength from this level.
//
// Revision 1.0  2001/03/16 10:43:40  cd
// - Creation
//==============================================================================

#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
namespace EDR
{
/** <b><tt>LPR_AsnFieldDescr</tt></b> is the base class for ASN.1 types.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: AsnFieldDescr.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.15 $</font></td>
 *  <td><font size=-1>$Date: 2001/08/07 13:12:24 $</font></td>
 *  <td><font size=-1>$Author: mwriedt $</font></td>
 *  </tr>
 *  </table>
 */
class AsnFieldDescr : public FieldDescr D_THREADINFO_M
{
  D_SINGLETHREADED

  public:
    /**@name Classname constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the input field
     */
    AsnFieldDescr( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~AsnFieldDescr();

    //@}
    
    /**@name AsnFieldDescr public methods */
    //@{
    
     /** Check if the field has an implicit field length
     *  @return <b>true</b> if implicit field lenght, <b>false</b> otherwise
     */
    virtual bool hasImplicitLength() const;

    /** Add a new parameter to the datatype
     *  @param parameter The parameter list to add
     *  @param failure Buffer for returning the failure string
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addParameter( const ParameterList& parameter,
                               BAS::String&              failure );

    /** Get the information about this field
     *  @param value Return buffer for the information
     */
    virtual void fieldInfo( BAS::String& value ) const;

    /** Get the tag
     *  @return The tagM
     */
    int tag() const;

    /** Get the Class value of the tag
     *  @return The classM
     */
    unsigned char classType() const;

    /** Get the Form value of the tag
     *  @return The formM
     */
    unsigned char formType() const;
    
    /** Calculate the length in bytes of the ASN.1 tag given as an integer
     *  @param Tag The ASN.1 tag given as an integer
     *  @return The length in bytes of the ASN.1 tag
     */
// CodeReview - 08.2001 - mwriedt - V - 01.13 lowercase letter for variables
    static int getTagLength(const int Tag);
    
    /** Read the ASN.1 string, and calculate the length in bytes of the Length 
     *  field of the corresponding ASN.1 object
     *  @param tagLength The length of the Tag field in bytes (must be known)
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Length field of the ASN.1 object
     */
    int getLenLength(const int tagLength, const BAS::String& value, size_t pos) const;

    /** Reads the ASN.1 string, and calculate the length in bytes of the Value 
     *  field of the corresponding ASN.1 object
     *  @param tagLength The length of the Tag field in bytes (must be known)
     *  @param value The input data buffer
     *  @param pos The starting position inside the buffer (where the Tag field starts)
     *  @return The length in bytes of the Value field of the ASN.1 object
     */
    int64 getValLength(const int tagLength, const BAS::String& value, size_t pos) const;

    /** Knowing the length of the Value field of the ASN.1 object, builds the 
     *  Length field, in the given buffer. 
     *  @param byteBuffer The output data buffer
     *  @param valLength The length of the Value field in bytes (-1 for undefinite)
     *  @return The length in bytes constructed Length field
     */
    int buildLenField(ByteBuffer& byteBuffer,
                      const int64      valLength) const;

    /** Build a regular expression enabeling to read and recognize the Tag+Length
     *  fields of an ASN.1 String
     *  @param outRegExpr The output data buffer containing the regular expression (null terminated)
     *  @param Tag The ASN.1 tag (given as an integer) to be recognized
     *  @param Class The Class of the ASN.1 object (bits 7,6 of the first ASN.1 Tag byte)
     *  @param Form The Form of the ASN.1 object (bit 5 of the first ASN.1 Tag byte)
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */

// CodeReview - 08.2001 - mwriedt - V - 01.13 lowercase letter for constants
    static bool getTagRegularExpression(BAS::String& outRegExpr,
                                        const int Tag,
                                        const unsigned char Class=ASN1_APPLICATION, 
                                        const unsigned char Form=ASN1_CONSTRUCTED );
    //@}

    /**@name AsnFieldDescr public constants */
        
    // ASN.1 constants representing the possibilities for the Class part 
    // of the ASN.1 Tag field
    EDR_EXPORT static const unsigned char	ASN1_UNIVERSAL;
    EDR_EXPORT static const unsigned char	ASN1_APPLICATION;
    EDR_EXPORT static const unsigned char	ASN1_CONTEXT;
    EDR_EXPORT static const unsigned char	ASN1_PRIVATE;
    EDR_EXPORT static const BAS::String	STR_UNIVERSAL;	// the string name to identify it
    EDR_EXPORT static const BAS::String	STR_APPLICATION;// the string name to identify it
    EDR_EXPORT static const BAS::String	STR_CONTEXT;	// the string name to identify it
    EDR_EXPORT static const BAS::String	STR_PRIVATE;	// the string name to identify it

    // ASN.1 constants representing the possibilities for the Form part
    // of the ASN.1 Tag field
    EDR_EXPORT static const unsigned char	ASN1_PRIMITIVE;
    EDR_EXPORT static const unsigned char	ASN1_CONSTRUCTED; 
    EDR_EXPORT static const BAS::String	STR_PRIMITIVE;	// the string name to identify it
    EDR_EXPORT static const BAS::String	STR_CONSTRUCTED;// the string name to identify it
    
  protected:
    /**@name AsnFieldDescr protected methods */
    //@{
 
    /** Build a ASN.1 byte string corresponding to the Tag field of an ASN.1 object
     *  @param ByteTag The output data buffer (must be at least 3 bytes Long)
     *  @param Tag The ASN.1 tag (given as an integer) to be coded
     *  @param Class The Class of the ASN.1 object (bits 7,6 of the first ASN.1 Tag byte)
     *  @param Form The Form of the ASN.1 object (bit 5 of the first ASN.1 Tag byte)
     *  @return The number of bytes used to encode the Tag field
     */

// CodeReview - 08.2001 - mwriedt - V - 01.13 lowercase letter for variables & constants
    static int getByteTag(unsigned char* ByteTag,
                          const int Tag,
                          const unsigned char Class=ASN1_APPLICATION, 
                          const unsigned char Form=ASN1_CONSTRUCTED);

    //@}
    
    unsigned char classM;     // binary mask for the Class part of the tag
    unsigned char formM;      // binary mask for the Form part of the tag
    int           tagM;       // value of the Number part of the tag
    
    unsigned char asnTagM[4]; // binary asn.1 presentation of the tag
    int           asnTagLenM; // length of asnTagM in bytes

    int64	  sizeMinM;   // min length of String to read/write (def 0)
    int64	  sizeMaxM;   // max length of String to read/write (def -1)

// CodeReview - 08.2001 - mwriedt - V - 01.20 declare public section first
  public:
    int getTotalLength(const BAS::String& value,
                       size_t            pos=0 );
};

//==============================================================================
// Get the tag number
//==============================================================================
inline int
AsnFieldDescr::tag() const
{
  return tagM;
}

inline unsigned char
AsnFieldDescr::classType() const
{
  return classM;
}

inline unsigned char
AsnFieldDescr::formType() const
{
  return formM;
}
}
#endif // AsnFieldDescr
