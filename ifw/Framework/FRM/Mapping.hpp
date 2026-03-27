#ifndef FRM_MAPPING_HPP
#define FRM_MAPPING_HPP

//==============================================================================
//
// Copyright (c) 1996, 2012, Oracle and/or its affiliates. 
// All rights reserved. 
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: FRM
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Mapping. This class is the base class for
//   the classes InputMapping and OutputMapping.
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
// $RCSfile: Mapping.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:48 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: Mapping.hpp,v $
// Revision 1.4  2012/05/14 Santanu
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER
//
// Revision 1.3  2001/09/27 12:01:17  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.2  2001/05/21 08:12:26  sd
// - function fullName() introduced
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
// Revision 1.6  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.5  2001/03/15 15:15:43  sd
// - Backup version
//
// Revision 1.4  2001/03/13 13:45:35  sd
// - Backup version
//
// Revision 1.3  2001/03/08 12:32:41  sd
// - Output mapping changed
//
// Revision 1.2  2001/03/07 10:13:35  sd
// - Backup version
//
// Revision 1.1  2001/01/18 13:38:31  sd
// - Backup version
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

namespace EDR
{
class FieldDescr;
}
namespace FRM
{
class RecordDescr;
class MappingConstant;

/** <b><tt>Mapping</tt></b> is the base class for the two classes
 *  InputMapping and OutputMapping. This classes are used to exchange
 *  the data between the file records and the EDR container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Mapping.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:48 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>
 */
class Mapping D_THREADINFO
{
  public:
    /**@name Mapping constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the mapping description
     *  @param recordDescr The file record description to map
     */
    Mapping( const BAS::String& name,
                 RecordDescr*   recordDescr );

    /** Destructor
     */
    virtual ~Mapping();

    //@}

    /**@name Mapping public methods */
    //@{

    /** Do the final setup for the mapping entry
     *  @return <b>true</b> if valid, <b>false</b> otherwise
     */
    virtual bool setup() = 0;

    /** Add a new mapping entry 
     *  @param leftSide Left side of mapping rule
     *  @param rightSide Right side of mapping rule
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addMappingEntry( const EDR::Parameter& leftSide,
                                  const EDR::Parameter& rightSide ) = 0;

    /** Get the maximum index depth of all used EDR indices
     *  @return The maximum depth of all EDR indices used
     */
    virtual size_t maxEdrIndexDepth() const = 0;

    /** Get the name of the mapping description
     *  @return Reference for the name string
     */
    const BAS::String& name() const;

    /** Get the full name of the mapping description (including file and
     *  record name).
     *  @return The full name of the mapping description
     */
    BAS::String fullName() const;

    /** Get the failure string
     *  @return Reference for the failure string
     */
    const BAS::String& failure() const;

    /** Create a mapping constant for a parameter
     *  @param parameter The parameter for which to get a constant
     *  @return Pointer to new mapping constant on success, 0 otherwise
     */
    MappingConstant* createMappingConstant(const EDR::Parameter& parameter);

    /** Get the pointer to the associated record description
     *  @return Pointer to the record description
     */
    RecordDescr* recordDescr() const;

    /** get the name of the mapping file
     *  @return the file name
     */
    const BAS::String& fileName();

    /** Set the name of the mapping file
     *  @param name the file name
     */
    void fileName ( const BAS::String & name );


    //@}

  protected:

    /* Set the failure string
     * @param msg The failure message
     */
    void failure( const BAS::String& msg );

  private:
    // Hide copy constructor and assignment operator
    Mapping( const Mapping& other );
    const Mapping& operator=( const Mapping& rhs );


  protected:
    // instance members
    BAS::String                            nameM;
    BAS::String                            failureM;
    BAS::String                            fileNameM;
    RecordDescr*                      recordDescrM;
};

//==============================================================================
// Get the name of the mapping entry
//==============================================================================
inline const BAS::String&
Mapping::name() const
{
  return nameM;
}

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
Mapping::failure() const
{
  return failureM;
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
Mapping::failure( const BAS::String& msg )
{
  failureM = msg;
}

//==============================================================================
// Get the associated record description
//==============================================================================
inline RecordDescr*
Mapping::recordDescr() const
{
  return recordDescrM;
}
}
#endif // MAPPING_HPP
