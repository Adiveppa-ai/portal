#ifndef FRM_STREAMDESCR_HPP
#define FRM_STREAMDESCR_HPP

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
//   Class used to store the information about all datarecords contained in 
//   a datafile.
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
// $RCSfile: StreamDescr.hpp $
// $Revision: /cgbubrm_7.5.0.pipeline/1 $
// $Author: sknanda $
// $Date: 2012/05/23 01:27:49 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: StreamDescr.hpp,v $
// Revision 1.4 : 2012/05/14 Santanu
// Bug 14051114 - P-9305229 ECR: MULTITHREADED PIPELINE-OUTPUT-CONTROLLER
//
// Revision 1.3  2001/09/27 12:01:18  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.2  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.1  2001/06/21 10:15:09  sd
// - FileDescr renamed to StreamDescr
//
// Revision 1.1  2001/05/03 16:29:23  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.5  2001/04/05 09:28:24  sd
// - Backup version
//
// Revision 1.4  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.3  2001/01/18 13:38:31  sd
// - Backup version
//
// Revision 1.2  2000/11/30 17:56:11  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   FRM_RECORDDESCR_HPP
  #include "FRM/RecordDescr.hpp"
#endif

namespace FRM
{
class DataDescr;

/** <b><tt>StreamDescr</tt></b> is used to store the information about all
 *  datarecords contained in an input file.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: StreamDescr.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:49 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>
 */
class StreamDescr D_THREADINFO
{
  public:
    /**@name StreamDescr constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the file format
     */
    StreamDescr( const BAS::String& name );

    /** Destructor
     */
    ~StreamDescr();

    //@}


    /**@name StreamDescr public methods */
    //@{

    /** Get the name of the file description
     *  @return Reference to the name string
     */
    const BAS::String& name() const;
    
    /** Get the number of records in the file description
     *  @return Number of records
     */
    size_t numRecords() const;

    /** Get a record description by it's name
     *  @param name The name of the record
     *  @return Pointer to record description if existent, 0 otherwise
     */
    RecordDescr* recordDescr( const BAS::String& name ) const;
    
    /** Get a record description by it's index
     *  @param idx The index for the record description
     *  @return Pointer to record description
     */
    RecordDescr* recordDescr( size_t idx ) const;

// CodeReview  - 08.2001 - cdiab - I - 05.02 missing parameter description
    /** Get a list of record descriptions for a parser state
     *  @param list A list for returning the found record descriptions
     */
    void recordDescrsForLexerState( 
      const BAS::String&                    name,
      RWTPtrOrderedVector<RecordDescr>& recordVector );

    /** Get a list of record all record descriptions 
     *  @param list A list for returning the record descriptions
     */
    void recordDescrs( RWTPtrOrderedVector<RecordDescr>& recordVector );

    /** Set the data description pointer
     *  @param dataDescr Pointer to the data description
     */
    void dataDescr( DataDescr* dataDescr );

    /** Get the data description pointer
     *  @return Pointer to the data description
     */
    DataDescr* dataDescr() const;

// CodeReview  - 08.2001 - cdiab - I - 05.02 missing parameter description
    /** Add a new record description to the file description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addRecordDescr( RecordDescr* record );

    /** Get the lexer states used in this file description
     *  @return List with lexer states
     */
    BAS::StringList lexerStates() const;

    /** Return the interpreter(grammar) name associated
     *  @return The interpreter name
     */
    const BAS::String& interpreterName() const;

    /** Store the interpreter(grammar) name associated
     *  @param  The interpreter name
     */
    void interpreterName(const BAS::String & iInterpreterName);

    /**  Modify the stream description file name 
     *   @param newName The new name
     */ 
    void modifyName( const BAS::String& newName );

    /** Set the stream description file name
     *  @param fileName The stream description file name
     */
    void fileName( const BAS::String& fileName );

    /** Get the stream description file name
     *  @return The stream description file name
     */
    const BAS::String & fileName();


    //@}

  private:
    // instance members
    BAS::String                           nameM;
    DataDescr*                       dataDescrM;
    RWTPtrOrderedVector<RecordDescr> recordsM;
    BAS::String interpreterNameM;
    BAS::String fileNameM;
};

//==============================================================================
// Get the name of the file description
//==============================================================================
inline const BAS::String&
StreamDescr::name() const
{
  return nameM;
}

//==============================================================================
// Set the data description pointer
//==============================================================================
inline void
StreamDescr::dataDescr( DataDescr* dataDescr )
{

  RWPRECONDITION( dataDescrM == 0 );
  dataDescrM = dataDescr;
}

//==============================================================================
// Get the data description pointer
//==============================================================================
inline DataDescr*
StreamDescr::dataDescr() const
{
  RWPRECONDITION( dataDescrM != 0 );
  return dataDescrM;
}

//==============================================================================
// Get the number of record descriptions
//==============================================================================
inline size_t
StreamDescr::numRecords() const
{
  return recordsM.entries();
}

//==============================================================================
// Get a record description by it's index
//==============================================================================
inline RecordDescr*
StreamDescr::recordDescr( size_t idx ) const
{
  return recordsM(idx);
}

//==============================================================================
// Get the interpreterName(Grammar)
//==============================================================================
inline const BAS::String&
StreamDescr::interpreterName() const
{
  D_ENTER( "FRM::StreamDescr::interpreterName() const" );
  return interpreterNameM;
}


//==============================================================================
// Set the interpreterName(Grammar)
//==============================================================================
inline void
StreamDescr::interpreterName(const BAS::String & iInterpreterName)
{
  D_ENTER( "FRM::StreamDescr::interpreterName(const BAS::String & iInterpreterName)" );
  interpreterNameM = iInterpreterName;
}

//==============================================================================
// Set the streamDescr name.
//==============================================================================
inline void
StreamDescr::modifyName( const BAS::String& newName )
{
  nameM = newName;
}

//==============================================================================
// Set the streamDescr filename.
//==============================================================================
inline void
StreamDescr::fileName( const BAS::String& fileName )
{
  fileNameM = fileName;
}

//==============================================================================
// Get the streamDescr filename.
//==============================================================================
inline const BAS::String &
StreamDescr::fileName()
{
  return fileNameM;
}

}
#endif // STREAMDESCR::HPP
