#ifndef FRM_RECORDASN_HPP
#define FRM_RECORDASN_HPP
//==============================================================================
//
//      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FRM
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the record description class for ASN record types encoded
//   with the Basic Encoding Rules (BER).
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
// $RCSfile: RecordASN.hpp,v $
// $Revision: 1.6 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: RecordASN.hpp,v $
// Revision 1.6  2001/09/27 12:01:18  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.5  2001/07/04 08:10:30  sd
// - PETS #36641 - ASN.1 enhancements (Swisscom)
//
// Revision 1.4  2001/07/03 11:49:58  sd
// - PETS #36641 - ASN.1 enhancements for Swisscom
//
// Revision 1.3  2001/06/07 16:28:09  cdiab
// - renaming of method applicationTag() to asnTag() for coherence.
//
// Revision 1.2  2001/06/07 16:20:05  cdiab
// - now the record can identify more than just Application class of tags.
//
// Revision 1.1  2001/05/03 16:29:24  bt
// - Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.2  2001/04/27 10:06:16  sd
// - New functions (needed by the ASN iScript extension) added
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.2  2001/04/02 11:31:52  sd
// - iScript functions for direct token access introduced.
//
// Revision 1.1  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.4  2001/03/27 09:13:42  sd
// - Backup version
//
// Revision 1.3  2001/03/19 11:16:55  sd
// - Backup version
//
// Revision 1.2  2001/03/16 16:03:13  sd
// - ASN records added
//
// Revision 1.1  2001/03/15 15:53:48  sd
// - Initial revision
//
//==============================================================================

#ifndef   FRM_RECORDDESCR_HPP
  #include "FRM/RecordDescr.hpp"
#endif

namespace EDR
{
class AsnFieldDescr;
}

namespace FRM
{
/** <b><tt>RecordASN</tt></b> is the record description class for ASN file
 *  records, encoded using the basic encoding rules.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: RecordASN.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.6 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:18 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class RecordASN : public RecordDescr
{
  public:
    /**@name RecordASN constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the record
     */
    RecordASN( const BAS::String& name  = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~RecordASN();

    //@}


    /**@name RecordASN public methods */
    //@{

    /** Get the typename of the record
     *  @return Reference to the typename string
     */
    virtual const BAS::String& typeName() const;

    /** Create a new record description (virtual constructor)
     *  @param name The name of the record description
     *  @return Pointer to the new created record description
     */
    virtual RecordDescr* create( const BAS::String& name ) const;

    /** Add a new field to the record description
     *  @param field The field to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addField( EDR::FieldDescr* field );

    /** Add a info parameter to the record description
     *  @param paramName The name of the info parameter
     *  @param parameter The input paramter itself
     */
    virtual bool addParameter( const BAS::String&    paramName,
                               const EDR::Parameter& parameter );

    /** Do the setup for the record description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setup();

    /** Create a new input mapping description to the record description
     *  @param name The name of the mapping description
     *  @return Pointer to the mapping description on success, 0 otherwise
     */
    virtual InputMapping* createInputMapping( const BAS::String& name );

    /** Create a new output mapping description to the record description
     *  @param name The name of the mapping description
     *  @return Pointer to the mapping description on success, 0 otherwise
     */
    virtual OutputMapping* createOutputMapping( const BAS::String& name );

    /** Check if the record needs the data matching its regular expression
     *  to determine the record length
     */
    virtual bool needsTokenForRecordLength() const;

    /** Get the length of the record
     *  @param value The input data matching the pattern
     *  @return The record length
     */
    virtual size_t recordLength( const BAS::String& value ) const;

    /** Get the distance to the end-of-record symbol
     *  @param value The input data matching the pattern
     *  @return Distance (>=0) if end-of-record symbol, < 0 otherwise
     */
    virtual int endRecordDistance( const BAS::String& value ) const;

    /** Calculate the position and the length for an input field
     *  @param token Pointer to the token containing the record data
     *  @param fielIdx The index of the input field
     *  @param pos Return buffer for the position of the field
     *  @param lne Return buffer for the length of the field
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool calcFieldPos( EDR::Token* token,
                               size_t     fieldIdx,
                               size_t&    pos,
                               size_t&    len ) const;

    /** Get the asn tag object if present
     *  @return Pointer to the asn tag if present, 0 otherwise
     */
    EDR::AsnFieldDescr* asnTag() const;

    //@}

  private:
    // instance members
    EDR::AsnFieldDescr*        asnTagM;
    BAS::String                endRecordNameM;

    // class members
    FRM_EXPORT static const BAS::String   typeNameCM;
};

//==============================================================================
// Get the application tag
//==============================================================================
inline EDR::AsnFieldDescr* 
RecordASN::asnTag() const
{
  return asnTagM;
}
}
#endif // RECORDASN_HPP
