#ifndef FRM_INMAPSEPARATED_HPP
#define FRM_INMAPSEPARATED_HPP

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
//   Declaration of the class InMapSeparated. This class is the input
//   mapping for file records with columns separated by special separator 
//   characters.
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
// $RCSfile: InMapSeparated.hpp,v $
// $Revision: 1.4 $
// $Author: sd $
// $Date: 2001/11/13 13:22:09 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: InMapSeparated.hpp,v $
// Revision 1.4  2001/11/13 13:22:09  sd
// - PETS #40026 Integrate does not scale
//
// Revision 1.3  2001/09/27 12:01:17  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.2  2001/05/21 08:12:26  sd
// - function fullName() introduced
//
// Revision 1.1  2001/05/03 16:29:23  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.4  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.2  2001/03/14 09:29:33  sd
// - Constants introduced in input mapping
//
//==============================================================================

#ifndef   EDR_VALUEITERATOR_HPP
  #include "EDR/ValueIterator.hpp"
#endif
#ifndef   FRM_INPUTMAPPING_HPP
  #include "FRM/InputMapping.hpp"
#endif

namespace FRM
{
/** <b><tt>InMapSeparated</tt></b> is the input mapping class for file
 *  data records with columns separated by separator characters
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: InMapSeparated.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.4 $</font></td>
 *  <td><font size=-1>$Date: 2001/11/13 13:22:09 $</font></td>
 *  <td><font size=-1>$Author: sd $</font></td>
 *  </tr>
 *  </table>
 */
class InMapSeparated : public InputMapping
{
  public:
    /**@name InMapSeparated constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the mapping description
     *  @param recordDescr The file record description to map
     *  @param fieldSep The separation character for fields
     *  @param recordSpe The separation character for records
     */
    InMapSeparated( const BAS::String& name,
                        RecordDescr*  recordDescr,
                        char              fieldSep,
                        char              recordSep );

    /** Destructor
     */
    virtual ~InMapSeparated();

    //@}


    /**@name InMapSeparated public methods */
    //@{

    /** Add a new mapping entry 
     *  @param leftSide Left side of mapping rule
     *  @param rightSide Right side of mapping rule
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addMappingEntry( const EDR::Parameter& leftSide,
                                  const EDR::Parameter& rightSide );

    /** Do the final setup for the mapping instance
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool setup();

    /** Execute the mapping function
     *  @param edr The current edr container as mapping target
     *  @param token The current token as mapping source
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool map( EDR::Container* edr, EDR::Token* token );

    //@}

  protected:

    /* Class for storing information about all mapping entries
     */
    class InMapSeparatedMapEntry
    {
      public: 
        InMapSeparatedMapEntry() 
          : fieldDescrM(0)
        {
        }

        InMapSeparatedMapEntry( EDR::Index       edrIndex,
                                    EDR::FieldDescr* fieldDescr )
          : edrIndexM( edrIndex ),
            fieldDescrM( fieldDescr )
        {
        }
        
        EDR::Index       edrIndexM;
        EDR::FieldDescr* fieldDescrM;
    };

    /* Class for storing information about all file record field positions
     */
    class InMapSeparatedPosInfo
    {
      public:
        InMapSeparatedPosInfo()
          : posM(0),lenM(0)
        {
        }
        size_t posM;
        size_t lenM;
    };

  private:
    // instance members
    char                                            fieldSepM;
    char                                            recordSepM;
    InMapSeparatedPosInfo*                      posInfoM;
    RWTValOrderedVector<InMapSeparatedMapEntry> mapEntriesM;
    InMapSeparatedMapEntry*                     cMapEntriesM;
    EDR::ValueIterator                               iteratorM;
};
}
#endif // INMAPSEPARATED_HPP
