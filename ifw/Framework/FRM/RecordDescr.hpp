#ifndef FRM_RECORDDESCR_HPP
#define FRM_RECORDDESCR_HPP

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
//   Class used to store the information about one file datarecord.
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
// $RCSfile: RecordDescr.hpp,v $
// $Revision: 1.7 $
// $Author: cdiab $
// $Date: 2001/09/27 12:01:18 $
// $Locker:  $
//------------------------------------------------------------------------------
// $Log: RecordDescr.hpp,v $
// Revision 1.7  2001/09/27 12:01:18  cdiab
// PETS #37618: CodeReview CR-08.2001
//
// Revision 1.6  2001/08/03 13:15:02  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration (HP-UX aCC 3.27).
//
// Revision 1.5  2001/07/04 08:10:30  sd
// - PETS #36641 - ASN.1 enhancements (Swisscom)
//
// Revision 1.4  2001/07/03 11:49:58  sd
// - PETS #36641 - ASN.1 enhancements for Swisscom
//
// Revision 1.3  2001/06/21 10:15:09  sd
// - FileDescr renamed to StreamDescr
//
// Revision 1.2  2001/05/21 08:12:26  sd
// - function fullName() introduced
//
// Revision 1.1  2001/05/03 16:29:24  bt
// Base moved to FRM (Format renamed to Pipeline).
//
// Revision 1.1  2001/04/12 09:49:48  sd
// - Creation of module Base
//
// Revision 1.3  2001/04/05 09:28:24  sd
// - Backup version
//
// Revision 1.2  2001/04/02 11:31:52  sd
// - iScript functions for direct token access introduced.
//
// Revision 1.1  2001/04/02 09:13:22  sd
// - BlockDescr renamed to RecordDescr
//
// Revision 1.9  2001/03/19 11:16:55  sd
// - Backup version
//
// Revision 1.1  2000/11/21 12:50:37  sd
// - Initial revision.
//
//==============================================================================

#if !defined FRM_EXPORT
  #if defined(WINDOWS)
    #if !defined(FRM_INTERNAL)
      #define FRM_EXPORT __declspec(dllimport)
    #else
      #define FRM_EXPORT __declspec(dllexport)
    #endif
  #else
    #define FRM_EXPORT 
  #endif
#endif

#ifndef   RW_TOOLS_TPORDVEC_H
  #include <rw/tpordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   EDR_FIELDDESCR_HPP
  #include "EDR/FieldDescr.hpp"
#endif
#ifndef   FRM_STATETRANSITION_HPP
  #include "FRM/StateTransition.hpp"
#endif
#ifndef   FRM_INPUTMAPPING_HPP
  #include "FRM/InputMapping.hpp"
#endif
#ifndef   FRM_OUTPUTMAPPING_HPP
  #include "FRM/OutputMapping.hpp"
#endif

namespace EDR
{
class Token;
class Parameter;
}
namespace FRM
{
class StreamDescr;

/** <b><tt>RecordDescr</tt></b> is used to store the information about one
 *  file datarecord. It contains the description of all fields in the record and
 *  the input and output mapping descriptions for transfering data from file
 *  records to the internal EDR container.
 *
 * <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: RecordDescr.hpp,v $</font></td>
 *  <td><font size=-1>$Revision: 1.7 $</font></td>
 *  <td><font size=-1>$Date: 2001/09/27 12:01:18 $</font></td>
 *  <td><font size=-1>$Author: cdiab $</font></td>
 *  </tr>
 *  </table>
 */
class RecordDescr D_THREADINFO
{
  public:
    /**@name RecordDescr constructors and destructor */
    //@{

    /** Constructor
     *  @param name The name of the record
     */
    RecordDescr( const BAS::String& name = BAS::NULL_STRING );

    /** Destructor
     */
    virtual ~RecordDescr();

    //@}

    /**@name RecordDescr public methods */
    //@{

    /** Get the typename of the record
     *  @return Reference to the typename string
     */
    virtual const BAS::String& typeName() const = 0;

    /** Create a new record description (virtual constructor)
     *  @param name The name of the record description
     *  @return Pointer to the new created record description
     */
    virtual RecordDescr* create( const BAS::String& name ) const = 0;

    /** Add a new field to the record description
     *  @param field The field to add
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool addField( EDR::FieldDescr* field );

    /** Add a record parameter to the record description
     *  @param paramName The name of the info parameter
     *  @param parameter The input paramter itself
     */
    virtual bool addParameter( const BAS::String&    paramName,
                               const EDR::Parameter& parameter );

    /** Do the setup for the record description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setup();

    /** Add a new input mapping description to the record description
     *  @param name The name of the mapping description
     *  @return Pointer to the mapping description on success, 0 otherwise
     */
    virtual InputMapping* createInputMapping( const BAS::String& name ) = 0;

    /** Add a new output mapping description to the record description
     *  @param name The name of the mapping description
     *  @return Pointer to the mapping description on success, 0 otherwise
     */
    virtual OutputMapping* createOutputMapping( const BAS::String& name ) =0;

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
                               size_t&    len ) const = 0;

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

    /** Check if the record needs the data matching its regular expression
     *  to determine the record length
     */
    virtual bool needsTokenForRecordLength() const;

    /** Get the name of the record description
     *  @return Reference to the name string
     */
    const BAS::String& name() const;

    /** Get the full name of the record description (including file name)
     *  @return String with full recrod name
     */
    BAS::String fullName() const;

    /** Get the record's smybol id
     *  @return The symbol id
     */
    size_t symbolId() const;

    /** Set the record's symbol id
     *  @param id The records symbols id
     */
    void symbolId( size_t id );

    /** Get the failure string
     *  @return Reference to the failure string
     */
    const BAS::String& failure() const;

    /** Get a field description by it's name
     *  @param name The name of the field description
     *  @return Pointer to the field description on success, 0 otherwise
     */
    EDR::FieldDescr* fieldDescr( const BAS::String& name ) const;

    /** Get a field description by it's index
     *  @param idx The index of the field description
     *  @return Pointer to the field description
     */
    EDR::FieldDescr* fieldDescr( size_t idx ) const;

    /** Get the number of field descriptions in record
     *  @return The number of fields inside the record
     */
    size_t numFieldDescrs() const;

    /** Set the pattern
     *  @param pattern The pattern for the record
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool pattern( const BAS::String& pattern );

    /** Get the pattern
     *  @return Reference to pattern string
     */
    const BAS::String& pattern() const;

    /** Add a lexer state to the record description
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addState( const BAS::String& stateName );

    /** Set the state transition for the record
     *  @param transType The type of the transition
     *  @param succState The name of the successor state
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool transition( StateTransition::StateTransitionT transitionType,
                     const BAS::String&                     succStateName );

    /** Get the state transition for the record
     *  @return Pointer to the state transition info (can be 0)
     */
    const StateTransition* transition() const;

    /** Get the successor lexer state name
     *  @return Reference to the successor state name
     */
    const BAS::String& succStateName() const;

    /** Set the successor state id
     *  @param id The new successor state id
     */
    void succStateId( int id );

    /** Get an input mapping entry by it's name
     *  @param name The name of the input mapping entry
     *  @return Pointer to mapping entry on success, 0 otherwise
     */
    InputMapping* inputMapping( const BAS::String& name ) const;

    /** Get an output mapping entry by it's name
     *  @param name The name of the output mapping entry
     *  @return Pointer to mapping entry on success, 0 otherwise
     */
    OutputMapping* outputMapping( const BAS::String& name ) const;

    /** Get the file description the record belongs to
     *  @return Pointer to the file description
     */
    StreamDescr* streamDescr() const;

    /** Set the file description the record belongs to
     *  @param fileDescr Pointer to the file description
     */
    void streamDescr( StreamDescr* streamDescr );
    
    /** Get the list of lexer states the record is used in
     *  @return String list with lexer states
     */
    BAS::StringList lexerStates() const;

    /** Check if the record description contains a lexer state
     *  @param stateName The name of the lexer state
     *  @return <b>true</b> if contains state, <b>false</b> otherwise
     */
    bool containsState( const BAS::String& name ) const;

    /** Get the end-of-record record for this description
     *  @return Pointer to the end-of-record record description
     */
    const RecordDescr* endRecord() const;

    /** Set the end-of-record record for this description
     *  @param descr Pointer to the end-of-record record description
     */
    void endRecord( const RecordDescr* descr );

    //@}

  protected:

    /** Set the failure string
     *  @param msg The new failure string
     */
    void failure( const BAS::String& msg );

    /** Add a new input mapping description to the record description
     *  @param mapping Pointer to the mapping description 
     *  @return <b>true</b> if contains state, <b>false</b> otherwise
     */
    bool addInputMapping( InputMapping* mapping );

    /** Add a new output mapping description to the record description
     *  @param mapping Pointer to the mapping description 
     *  @return <b>true</b> if contains state, <b>false</b> otherwise
     */
    bool addOutputMapping( OutputMapping* mapping );

  public:
    // instance members
    BAS::String                             nameM;
    BAS::String                             failureM;
    BAS::StringList                         lexerStatesM;
    BAS::String                             patternM;
    size_t                                 symbolIdM;
    RWTPtrOrderedVector<EDR::FieldDescr>    fieldsM;
    RWTPtrOrderedVector<InputMapping>  inputMappingM;
    RWTPtrOrderedVector<OutputMapping> outputMappingM;
    StreamDescr*                       streamDescrM;
    StateTransition*                   stateTransitionM;
    const RecordDescr*                 endRecordM;
};

//==============================================================================
// Get the name of the record description
//==============================================================================
inline const BAS::String&
RecordDescr::name() const
{
  return nameM;
}

//==============================================================================
// Get the failure string
//==============================================================================
inline const BAS::String&
RecordDescr::failure() const
{
  return failureM;
}

//==============================================================================
// Set the failure string
//==============================================================================
inline void
RecordDescr::failure( const BAS::String& msg )
{
  failureM = msg;
}

//==============================================================================
// Get the pattern string
//==============================================================================
inline const BAS::String&
RecordDescr::pattern() const
{
  return patternM;
}

//==============================================================================
// Get the records symbol id
//==============================================================================
inline size_t
RecordDescr::symbolId() const
{
  return symbolIdM;
}

//==============================================================================
// Set the records symbol id
//==============================================================================
inline void
RecordDescr::symbolId( size_t id)
{
  symbolIdM = id;
}

//==============================================================================
// Get the stream description for this record
//==============================================================================
inline StreamDescr*
RecordDescr::streamDescr() const
{
  RWPRECONDITION( streamDescrM != 0 );
  return streamDescrM;
}

//==============================================================================
// Set the stream description for this record
//==============================================================================
inline void
RecordDescr::streamDescr( StreamDescr* streamDescr ) 
{
  RWPRECONDITION( streamDescrM == 0 );
  streamDescrM = streamDescr;
}

//==============================================================================
// Get the number of field descriptions
//==============================================================================
inline size_t
RecordDescr::numFieldDescrs() const
{
  return fieldsM.entries();
}

//==============================================================================
// Get a field description by it's index
//==============================================================================
inline EDR::FieldDescr*
RecordDescr::fieldDescr( size_t idx ) const
{
  return fieldsM(idx);
}

//==============================================================================
// Get the name of the successor state
//==============================================================================
inline const BAS::String&
RecordDescr::succStateName() const
{
  if ( stateTransitionM == 0 )
  {
    return BAS::NULL_STRING;
  }
  else
  {
    return stateTransitionM->succStateName();
  }
}

//==============================================================================
// Set the successor state id
//==============================================================================
inline void
RecordDescr::succStateId( int id )
{
  if ( stateTransitionM != 0 )
  {
    stateTransitionM->succStateId( id );
  }
}

//==============================================================================
// Get the pointer to the state transition info
//==============================================================================
inline const StateTransition*
RecordDescr::transition() const
{
  return stateTransitionM;
}

//==============================================================================
// Get the end-of-record symbol
//==============================================================================
inline const RecordDescr*
RecordDescr::endRecord() const
{
  return endRecordM;
}

//==============================================================================
// Set the end-of-record symbol
//==============================================================================
inline void
RecordDescr::endRecord( const RecordDescr* descr )
{
  endRecordM = descr;
}
}
#endif // RECORDDESCR::HPP

