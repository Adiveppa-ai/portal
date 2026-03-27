#ifndef FRM_INPUTMAPPING_HPP
#define FRM_INPUTMAPPING_HPP

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
//   Declaration of the class InputMapping.
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
// $RCSfile: InputMapping.hpp,v $
// $Revision: 1.3 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:17 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: InputMapping.hpp,v $
// Revision 1.3  2001/09/27 12:01:17  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.2  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
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
// Revision 1.12  2001/04/02 11:31:52  sd
// - iScript functions for direct token access introduced.
//
// Revision 1.11  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.10  2001/03/15 15:15:43  sd
// - Backup version
//
// Revision 1.9  2001/03/14 09:29:33  sd
// - Constants introduced in input mapping
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_VALUEITERATOR_HPP
  #include "EDR/ValueIterator.hpp"
#endif
#ifndef   EDR_PARAMETER_HPP
  #include "EDR/Parameter.hpp"
#endif
#ifndef   FRM_MAPPING_HPP
  #include "FRM/Mapping.hpp"
#endif
#ifndef   FRM_MAPPINGCONSTANT_HPP
  #include "FRM/MappingConstant.hpp"
#endif

namespace EDR
{
class Container;
class Token;
class FieldDescr;
}
namespace FRM
{
class RecordDescr;

/** <b><tt>InputMapping</tt></b> is used to transfer the data read from file
 *  record into the EDR container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: InputMapping.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.3 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:17 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class InputMapping : public Mapping
{
  public:
    /**@name InputMapping constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the mapping description
     *  @param recordDescr The file record description to map
     */
    InputMapping( const BAS::String& name,
                      RecordDescr*  recordDescr );

    /** Destructor
     */
    virtual ~InputMapping();

    //@}

    /**@name InputMapping public methods */
    //@{

    /** Finish the setup after all mapping entries have been added
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setup();

    /** Execute the mapping function
     *  @param edr The current edr container as mapping target
     *  @param token The current token as mapping source
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool map( EDR::Container* edr, EDR::Token* token ) = 0;

    /** Get the maximum index depth of all used EDR indices
     *  @return The maximum depth of all EDR indices used
     */
    virtual size_t maxEdrIndexDepth() const;

    //@}

  protected:

    /* Add a mapping constant to the mapping entry
     * @param constant The constant
     * @param index The EDR index for the destination field
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addMappingConstant( const EDR::Parameter& constant,
                             const EDR::Index&     index );

    /* Execute the mapping of the constants
     * @param edr The destination EDR container
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool mapConstants( EDR::Container* edr );
                             
  protected:
    // instance members
    RWTPtrOrderedVector<MappingConstant> constantsM;
    EDR::ValueIterator                        constantIteratorM;

  private:
    // Hide copy constructor and assignment operator
    InputMapping( const InputMapping& rhs );
    const InputMapping& operator=( const InputMapping& rhs );
};
}
#endif // INPUTMAPPING_HPP
