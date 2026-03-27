/* @(#)%Portal Version: OutputMapping.hpp:NewPipelineVelocityInt:2:2006-Sep-18 22:51:12 % */
#ifndef FRM_OUTPUTMAPPING_HPP
#define FRM_OUTPUTMAPPING_HPP

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
//   Declaration of the class OutputMapping.   
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
// $RCSfile: OutputMapping.hpp,v $
// $Revision: 1.3 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// Revision 1.3  2004/07/26 ammon
// PRSF00116930  Added mapToString
//
// Revision 1.2  2001/09/27 12:01:18  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.1  2001/05/03 16:29:24  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.2  2001/04/24 14:13:14  sd
// - Long renamed to Integer
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.10  2001/04/04 11:54:14  sd
// - Old stream interfaces replaced by new stream managers.
//
// Revision 1.9  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.8  2001/03/22 09:30:07  sd
// - Value iterator improved?
//
// Revision 1.7  2001/03/20 15:01:32  sd
// - EDR::ByteBuffer introduced
//
// Revision 1.3  2001/03/08 12:32:41  sd
// - Output mapping changed
//
//==============================================================================

#ifndef   EDR_PARAMETER_HPP
  #include "EDR/Parameter.hpp"
#endif
#ifndef   EDR_BYTEBUFFER_HPP
  #include "EDR/ByteBuffer.hpp"
#endif
#ifndef   EDR_VALUEITERATOR_HPP
  #include "EDR/ValueIterator.hpp"
#endif
#ifndef   FRM_MAPPING_HPP
  #include "FRM/Mapping.hpp"
#endif
#ifndef   FRM_OUTMAPENTRY_HPP
  #include "FRM/OutMapEntry.hpp"
#endif

namespace EDR
{
	class Container;
}
namespace STR
{
class OutStreamManager;
}
namespace FRM
{

/** <b><tt>OutputMapping</tt></b> is used to transfer the EDR container 
 *  date into an output file record.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: OutputMapping.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.2 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:18 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class OutputMapping : public Mapping
{
  public:
    /**@name OutputMapping constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the mapping description
     *  @param recordDescr The record description for the target record
     */
    OutputMapping( const BAS::String& name,
                       RecordDescr*  recordDescr );

    /** Destructor
     */
    virtual ~OutputMapping();

    //@}


    /**@name OutputMapping public methods */
    //@{

    /** Do the final setup after all mapping entries have been added
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool setup();

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
                      STR::OutStreamManager* outStream ) = 0;

    /** Execute the mapping operation to a String
     *  @param edr Pointer to the current EDR container
     *  @param currentVector Indices for the different EDRC levels
     *  @param outString String for the output operation
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool mapToString( EDR::Container* edr,
                      EDR::CurrentVector&     currentVector,
                      BAS::String&            outString ) = 0;

    /** Get the maximum index depth of all used EDR indices
     *  @return The maximum depth of all EDR indices used
     */
    virtual size_t maxEdrIndexDepth() const;

    //@}

  protected:

    /* Get a mapping entry for a field description
     * @return Pointer to mapping entry on success, 0 otherwise
     */
    OutMapEntry* mapEntry( EDR::FieldDescr* field );

  private:
    // Hide the copy constructor and assignment operator
    OutputMapping( const OutputMapping& other );
    const OutputMapping& operator=( const OutputMapping& rhs );

  protected:
    // Instance members
    RWTValOrderedVector<OutMapEntry> mapEntriesM;
    EDR::ValueIterator                    iteratorM;
    EDR::ByteBuffer                       outputBufferM;
};
}
#endif // OUTPUTMAPPING_HPP
