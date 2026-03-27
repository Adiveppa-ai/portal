/* @(#)%Portal Version: OutMapSeparated.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:51:15 % */
#ifndef FRM_OUTMAPSEPARATED_HPP
#define FRM_OUTMAPSEPARATED_HPP

//==============================================================================
//
// Copyright (c) 1996 - 2006 Oracle. All rights reserved.
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FRM
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the output mapping class for records with separated fields.
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
// $RCSfile: OutMapSeparated.hpp,v $
// $Revision: 1.5 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.5  2004/12/03 ammon
// PRSF00143648  Made mapToString work.
//
// Revision 1.4  2004/07/26 ammon
// PRSF00116930  Added mapToString.
//
// Revision 1.3  2001/09/27 12:01:18  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.2  2001/05/17 06:50:37  sd
// - Error messages for constant mapping improved
//
// Revision 1.1  2001/05/03 16:29:24  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.6  2001/04/04 11:54:14  sd
// - Old stream interfaces replaced by new stream managers.
//
// Revision 1.5  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.4  2001/03/22 09:30:07  sd
// - Value iterator improved?
//
// Revision 1.3  2001/03/19 16:12:31  sd
// - Backup version
//
// Revision 1.2  2001/03/14 09:29:33  sd
// - Constants introduced in input mapping
//
// Revision 1.1  2001/03/13 13:46:32  sd
// - Initial revision
//
//==============================================================================

#ifndef   FRM_OUTPUTMAPPING_HPP
  #include "FRM/OutputMapping.hpp"
#endif

namespace FRM
{
/** <b><tt>OutMapSeparated</tt></b> is the output mapping class for records
 *  with separated fields.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: OutMapSeparated.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:18 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class OutMapSeparated : public OutputMapping
{
  public:
    /**@name OutMapSeparated constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the mapping description
     *  @param recordDescr The description for the output file record
     *  @param fieldSep The field separation character
     *  @param recordSep The record separation character
     *  @param hasRecordSep Boolean if the record has a record separator
     */
    OutMapSeparated( const BAS::String& name,
                         RecordDescr*  recordDescr,
                         char              fieldSep,
                         char              recordSep,
                         bool              hasRecordSep );

    /** Destructor
     */
    virtual ~OutMapSeparated();

    //@}


    /**@name OutMapSeparated public methods */
    //@{

    /** Add a new mapping entry 
     *  @param leftSide Left side of mapping rule
     *  @param rightSide Right side of mapping rule
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addMappingEntry( const EDR::Parameter& leftSide,
                                  const EDR::Parameter& rightSide );

    /** Execute the mapping operation
     *  @param edr Pointer to the current EDR container
     *  @param currentVector Indices for the different EDRC levels
     *  @param outStream Stream for the output operation
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool map( EDR::Container*        edr,
                      EDR::CurrentVector&    currentVector,
                      STR::OutStreamManager* outStream );

    /** Execute the mapping operation to a String
     *  @param edr Pointer to the current EDR container
     *  @param currentVector Indices for the different EDRC levels
     *  @param outString String for the output operation
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool mapToString( EDR::Container* edr,
                      EDR::CurrentVector&     currentVector,
                      BAS::String&            outString );

    /** Execute the mapping operation to a buffer
     *  @param edr Pointer to the current EDR container
     *  @param currentVector Indices for the different EDRC levels
     *  @param outBuffer Buffer for the output operation
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool mapToBuffer( EDR::Container*      edr,
                              EDR::CurrentVector&  currentVector,
                              EDR::ByteBuffer&     outBuffer );

    //@}

  private:
    // Hide copy constructor and assignment operator
    OutMapSeparated( const OutMapSeparated& rhs );
    const OutMapSeparated& operator=( const OutMapSeparated& rhs );

    // Instance members
    char fieldSepM;
    char recordSepM;
    bool hasRecordSepM;
};

}
#endif // OUTMAPSEPARATED_HPP
