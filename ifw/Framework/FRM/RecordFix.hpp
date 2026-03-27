#ifndef FRM_RECORDFIX_HPP
#define FRM_RECORDFIX_HPP
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
//   Declaration of the record description class for records with fix length.
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
// $RCSfile: RecordFix.hpp,v $
// $Revision: 1.2 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: RecordFix.hpp,v $
// Revision 1.2  2001/09/27 12:01:18  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.1  2001/05/03 16:29:24  bt
// Base moved to FRM (Format renamed to Pipeline).
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
// Revision 1.4  2001/03/19 11:16:55  sd
// - Backup version
//
// Revision 1.3  2001/03/16 16:03:13  sd
// - ASN records added
//
// Revision 1.1  2001/03/13 13:46:54  sd
// - Initial revision
//
//==============================================================================

#ifndef   FRM_RECORDDESCR_HPP
  #include "FRM/RecordDescr.hpp"
#endif

namespace FRM
{
/** <b><tt>RecordFix</tt></b> is the record description class for records
 *  with fixed length.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: RecordFix.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:18 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class RecordFix : public RecordDescr
{
  public:
    /**@name RecordFix constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the record
     */
    RecordFix( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~RecordFix();

    //@}


    /**@name RecordFix public methods */
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

    /** Do the setup for the record description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setup();

    /** Get the length of the record
     *  @param value The input data matching the pattern
     *  @return The record length
     */
    virtual size_t recordLength( const BAS::String& value ) const;

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

    /** Create a new input mapping for the record description
     *  @param name The name of the mapping description
     *  @return Pointer to the mapping description on success, 0 otherwise
     */
    virtual InputMapping* createInputMapping( const BAS::String& name );

    /** Create a new output mapping description for the record description
     *  @param name The name of the mapping description
     *  @return Pointer to the mapping description on success, 0 otherwise
     */
    virtual OutputMapping* createOutputMapping( const BAS::String& name );

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

    //@}

  private:
    // instance members
    size_t                      recordLengthM;
    RWTValOrderedVector<size_t> positionsM;

    // class members
    FRM_EXPORT static const BAS::String     typeNameCM;
};
}
#endif // RECORDFIX_HPP
