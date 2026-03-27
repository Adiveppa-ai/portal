#ifndef EDR_CONTAINER_HPP
#define EDR_CONTAINER_HPP
/* @(#)%Portal Version: Container.hpp:Pipeline7.3PatchInt:1:2006-Nov-22 04:18:45 % */

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
// Block: EDR
//------------------------------------------------------------------------------
// Module Description:
//   Declaration of the class Container.
//------------------------------------------------------------------------------
//
// bug 6379318   Added a new inteface for method "setString" with const char * as
//               parameter
//
// bug 7490974   Added new member variable 'originalDefaultStream'
//               and associated set and get functions
//
// Revision      1.123  01-Aug-2006 ashishk
// PRSF00225670  Add resetSavedValue() to reset the original value of an Index
//
// Revision      1.122  18-Apr-2006 knijhawa
// PRSF00204313  Framework changes for Dropped Call
//
// Revision      1.121  1-Apr-2005 rtang
// PRSF00161772  Platform support for improving pre-suspense performance 
//
// Revision       1.120  11-Mar-2005   ammon
// PRSF00156493   Add access functions for array index.
//
// Revision       1.119  15-Nov-2004   jlan
// PRSF00128145   Add opROCSync
//
// Revision       1.119  19-Oct-2004   ammon
// PRSF00136835   Add timed out flag.
//
// Revision       1.118  07-Jun-2004   ammon
// PRSF00114891   Add containsStream() and getStreamFromList().
//
// Revision       1.117  26-Jan-2004   ammon
// PRSF00086760   Add pcm_context for RTDP
//
// Revision       1.116  10-Mar-2004   6.5_FP3   ammon
// PRSF00098531   Add SaxHandler as a friend
//
// Revision       1.115  30-Jun-2003   6.5_FP3   keshav
// PRSF00045126   Differentiate between MISSING and EMPTY fields
//
// Revision 1.114  2002/03/13 08:52:19  sd
// - ClearCase Transition checkin
//
// Revision 1.113  2002/01/15 09:28:23  sd
// - PETS #36397 - Serialization for EDR Container
//
// Revision 1.112  2001/11/15 10:11:39  sd
// - PETS #41247 Parser error messages insufficient
//
// Revision 1.111  2001/11/15 09:52:50  sd
// - PETS #41247 - Parser: error messages for parse errors not helpful
//
// Revision 1.110  2001/11/09 15:32:33  sd
// - Token cache introduced
//
// Revision 1.109  2001/09/17 22:09:38  sd
// - PETS #39540 Iterator interface not sufficient for duplication
//
// Revision 1.108  2001/09/15 17:49:38  sd
// - PETS #37618 Code Review Check
//
// Revision 1.107  2001/08/07 12:58:46  mwriedt
// - PETS #37618: Code Review.
//
// Revision 1.106  2001/07/18 13:11:25  sd
// - PETS #37117 Stream LOG: Wrong EDR number
//   New function bytePosition() added witch is used to evaluate the
//   starting position of an EDR container inside a stream
//
// Revision 1.105  2001/06/26 11:04:24  sd
// - New function clearErrors() added
//
// Revision 1.104  2001/06/26 10:56:29  sd
// - New get functions with bool return value
//
// Revision 1.103  2001/06/26 09:41:38  sd
// - Doc++ documentation enhanced
//
// Revision 1.102  2001/06/11 11:30:38  sd
// - Parameter for returning the new current vector after datablock
//   duplication added.
//
// Revision 1.101  2001/06/11 10:52:17  sd
// - New function duplicateDatablock() added
//
// Revision 1.100  2001/04/26 15:23:25  sd
// - ContainerIndex introduced
//
// Revision 1.99  2001/04/23 14:53:16  sd
// - Index splitted to IndexBase, Index and BlockIndex
//
// Revision 1.98  2001/04/23 11:42:16  sd
// - Function hasError() added.
//
// Revision 1.97  2001/04/12 12:38:14  sd
// - Update for the new module structure
//
// Revision 1.96  2001/04/11 07:31:06  sd
// - New function factory() added to the EDR container
//
// Revision 1.95  2001/03/30 12:49:44  sd
// - Changes to support duplication of EDR containers
//
// Revision 1.94  2001/03/28 07:59:10  sd
// - Files moved from NEWEDR to EDR
//
// Revision 1.18  2001/03/21 11:01:50  sd
// - New function size_t numDatablocks(Index&,CurrentVector&)
//
// Revision 1.17  2001/03/20 11:29:59  sd
// - New container type BEGIN_TRANSACTION and END_TRANSACTION
//
// Revision 1.16  2001/03/19 12:13:55  sd
// - New function addDatablock() added to iterator
//
// Revision 1.15  2001/03/14 11:42:27  sd
// - Output operator added to Container
//
//==============================================================================

#ifndef   RW_TOOLS_TVORDVEC_H
  #include <rw/tvordvec.h>
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif
#ifndef   EDR_VALUE_HPP
  #include "EDR/Value.hpp"
#endif
#ifndef   EDR_TOKEN_HPP
  #include "EDR/Token.hpp"
#endif
#ifndef   EDR_TOKENHANDLE_HPP
  #include "EDR/TokenHandle.hpp"
#endif
#ifndef   EDR_DATABLOCK_HPP
  #include "EDR/Datablock.hpp"
#endif
#ifndef   EDR_BLOCKINDEX_HPP
  #include "EDR/BlockIndex.hpp"
#endif
#ifndef   EDR_METADATA_H
  #include "EDR/MetaData.hpp"
#endif
#ifndef   _RWSTD_MAP_INCLUDED
  #include "map"
#endif
#ifndef   EDR_ACCESSORIF_H
  #include "EDR/AccessorIf.hpp"
#endif

#ifndef   _Pin_H_
  #include "Pin.h"
#endif
#ifndef   EDR_INDEX_HPP
  #include "EDR/Index.hpp"
#endif
#ifndef   EDR_CHANGELOG_HPP
  #include "EDR/ChangeLog.hpp"
#endif

namespace BAS
{
	class Decimal;
	class DateTime;
}
namespace EDR
{
class Index;
class SaxHandler;

typedef RWTValOrderedVector<size_t>     CurrentVector;
typedef RWTValOrderedVector<BAS::Status> StatusList;
typedef RWTValOrderedVector<size_t>     StreamNumberList;

enum OpType {opRead, opCreate, opUpdate, opDelete, opDelayedDelete, opROCSync, noOp};

/** <tt><b>Container</b></tt> is integRate's internal container for data
 *  processing.
 * 
 *  <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
 *  <tr>
 *  <td><font size=-1>$RCSfile: Container.hpp $</font></td>
 *  <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/1 $</font></td>
 *  <td><font size=-1>$Date: 2012/05/23 01:27:41 $</font></td>
 *  <td><font size=-1>$Author: sknanda $</font></td>
 *  </tr>
 *  </table>                
 */
class Container  D_THREADINFO
{
  D_SINGLETHREADED
  

  public:

    // class members
    EDR_EXPORT static CurrentVector nullCurrentVectorCM;

    /** Enumeration container type
     *  <ul>
     *  <li> DATA
     *  <li> SERVICE
     *  </ul>
     */
    enum containerTypeT 
    {
      DATA    = 1,
      SERVICE
    };

    /** Enumeration content type
     *  <ul>
     *  <li> UNKNOWN_CONT
     *  <li> HEADER
     *  <li> DETAIL
     *  <li> TRAILER
     *  <li> START
     *  <li> STOP
     *  <li> BEGIN
     *  <li> END
     *  <li> BEGIN_TRANSACTION
     *  <li> END_TRANSACTION
	 *  <li> TIMOS_TXN_RESOLUTION_END
	 *  <li> TIMOS_RECOVERY_END
     *  </ul>
     */
    enum contentTypeT 
    {
      UNKNOWN_CONT = 1,
      HEADER,
      DETAIL,
      TRAILER,
      START,
      STOP,
      BEGIN,
      END,
      BEGIN_TRANSACTION,
      END_TRANSACTION,
	  // below two types are for timos backend pipeline only
	  TIMOS_TXN_RESOLUTION_END,
	  TIMOS_RECOVERY_END
    };

    /** Enumeration of input states of EDR values that can be accessed from
     *  IScripts and IRules.
     */
    enum iScriptAccessibleInputStateT
    {
      MISSING = EDR::Value::MISSING,
      EMPTY   = EDR::Value::EMPTY,
      OTHER	// other "uninteresting" input states
    };

    /** Magic numbers for origDefaultStreamNumber
        DEFAULT - No stream
        EDR_DUPLICATE - EDR duplicated
     */
    enum originalStreamIndicatorT
    {
      DEFAULT = 99999,
      EDR_DUPLICATE = 88888
    };

    /**@name Container public methods */
    //@{

    /** Check whether the current EDR container is a valid detail or not
     *  @return <b>true</b> if valid detail, <b>false</b> otherwise
     */
    bool isValidDetail() const;

#ifdef _DEBUG
	/** Check whether or not the isValidDetail has been accessed. 
	 * This function is only present in debug builds
	 * @return true for yes, false for failure.
	 */
	bool isValidDetailChecked() const;

	/** Clear the flag that says whether or not isValidDetail has been 
	 * accessed. This function is only present in debug builds.
	 */
	void clearIsValidDetailChecked();
#endif

    /** Set the isValidDetail flag
     *  @param flag The new flag
     */
    void isValidDetail( bool flag );

    /** Check if there is a error message with severity > warning
     *  @return <b>true</b> if error message > warning, <b>false</b> otherwise
     */
    bool hasError() const;

    /** Duplicate the EDR container. The EDR container should also be released
     *  by the releadEDR() method of the factory.
     *  @return Pointer to the duplicated EDR container
     */
    Container* duplicate() const;

    /** Add a datablock to the edr container
     *  @param index The block index for the datablock to add
     *  @param index The Flist arrayIndexId defaults to 0
     *  @return Pointer to the new Datablock
     */
     Datablock* addDatablock( const BlockIndex& index,
                const int32 arrayIndexId = 0 );

    /** Add a datablock to the edr container
     *  @param index The block index for the datablock to add
     *  @param currentVector Current values for the different levels
     *  @param newCurrentVector Return buffer for the new (duplicated) datablock's
     *                          current vector
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool addDatablock( const BlockIndex&    index,
                       const CurrentVector& currentVector,
                       CurrentVector&       newCurrentVector = nullCurrentVectorCM );

    /** Add a datablock to the edr container
     *  @param index The block index for the datablock to add
     *  @param currentVector Current values for the different levels
     *  @param newCurrentVector Return buffer for the new (duplicated) 
     *                          datablock's current vector
     *  @return Pointer to the new Datablock
     */
    Datablock * addAndGetDatablock( const BlockIndex&    index,
                       const CurrentVector& currentVector,
                       CurrentVector&       newCurrentVector = nullCurrentVectorCM );

    /** Duplicate a single datablock
     *  @param index The block index for the datablock to duplicate
     *  @param currentVector Current values for the different levels
     *  @param newCurrentVector Return buffer for the new (duplicated) datablock's
     *                          current vector
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool duplicateDatablock( 
      const BlockIndex&    index,
      const CurrentVector& currentVector,
      CurrentVector&       newCurrentVector = nullCurrentVectorCM );

    /** Get the number of datablocks 
     *  @param index The block index for the datablock
     *  @return The number of datablocks for that index
     */
    size_t numDatablocks( const BlockIndex& index ) const;

    /** Get the number of datablocks 
     *  @param index The block index for the datablock
     *  @param currentVector Current values for the different levels
     *  @return The number of datablocks for that index
     */
    size_t numDatablocks( const BlockIndex&    index,
                          const CurrentVector& currentVector ) const;
    
    /** Get the Current Plugin Name
     */
    virtual const BAS::String& getCurrentPlugin() const;
    
    /** Set the Current Plugin Name
     * @param pluginName Current Plugin name  
     */
    virtual bool  setCurrentPlugin(const BAS::String& pluginName);

    /** Get the ChangeLog instance
     */ 
    virtual EDR::ChangeLog* getChangeLog() const;

    /** Get a string value from the edr
     *  @param index The index for the edr field
     *  @return Reference to string value
     */
    virtual const BAS::String& getString( const Index& index ) const;

    /** Get a string value from the edr
     *  @param index The index for the edr field
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getString( const Index& index, BAS::String& buffer ) const;

    /** Get a string value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return Reference to string value
     */
    virtual const BAS::String& getString( const Index&         index,
                                 const CurrentVector& currentVector ) const;

    /** Get a string value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getString( const Index&         index,
                    const CurrentVector& currentVector,
                    BAS::String&              buffer ) const;

    /** Get a string value from the edr
     *  @param fld The pin_fld_num value for the edr field
     *  @return Reference to string value
     */
    const BAS::String& getString( pin_fld_num_t fld );

    /** Get a poid value from the edr
     *  @param index The index for the edr field
     *  @return Reference to poid value
     */
    const EDR::CompactPoid& getCompactPoid( const Index& index ) const;

    /** Get a poid value from the edr
     *  @param index The index for the edr field
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getCompactPoid( const Index& index, EDR::CompactPoid& buffer ) const;

    /** Get a poid value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return Reference to poid value
     */
    const EDR::CompactPoid& getCompactPoid( const Index&         index,
                                 const CurrentVector& currentVector ) const;

    /** Get a poid value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getCompactPoid( const Index&         index,
                    const CurrentVector& currentVector,
                    EDR::CompactPoid&              buffer ) const;

    /** Get a poid value from the edr
     *  @param fld The pin_fld_num value for the edr field
     *  @return Reference to poid value
     */
    const EDR::CompactPoid& getCompactPoid( pin_fld_num_t fld ) ;

    /** Get a decimal value from the edr
     *  @param index The index for the edr field
     *  @return Reference to decimal value
     */
    virtual const BAS::Decimal& getDecimal( const Index& index ) const;

    /** Get a decimal value from the edr
     *  @param index The index for the edr field
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDecimal( const Index& index,
                     BAS::Decimal&     buffer ) const;

    /** Get a decimal value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return Reference to decimal value
     */
    virtual const BAS::Decimal& getDecimal( const Index& index,
                                   const CurrentVector& currentVector) const;

    /** Get a decimal value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDecimal( const Index&         index,
                     const CurrentVector& currentVector,
                     BAS::Decimal&             buffer ) const;

    /** Get a decimal value from the edr
     *  @param fld The pin_fld_num value for the edr field
     *  @return Reference to decimal value
     */
    const BAS::Decimal& getDecimal( pin_fld_num_t fld );

    /** Get a date value from the edr
     *  @param index The index for the edr field
     *  @return Reference to date/time value
     */
    virtual const BAS::DateTime& getDate( const Index& index ) const;

    /** Get a date value from the edr
     *  @param index The index for the edr field
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDate( const Index& index,
                  BAS::DateTime&    buffer ) const;

    /** Get a date value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return Reference to date/time value
     */
    virtual const BAS::DateTime& getDate( const Index&         index,
                                 const CurrentVector& currentVector) const;

    /** Get a date value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getDate( const Index&         index,
                  const CurrentVector& currentVector,
                  BAS::DateTime&            buffer ) const;
    
    /** Get a date value from the edr
     *  @param fld The pin_fld_num value for the edr field
     *  @return Reference to date/time value
     */
    const BAS::DateTime& getDate( pin_fld_num_t fld );

    /** Get a long value from the edr
     *  @param index The index for the edr field
     *  @return The long value
     */
    virtual int64 getLong( const Index& index ) const;

    /** Get a long value from the edr
     *  @param index The index for the edr field
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getLong( const Index& index,
                  int64&            buffer ) const;

    /** Get a long value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return The long value
     */
    virtual int64 getLong( const Index&         index,
                  const CurrentVector& currentVector) const;

    /** Get a long value from the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool getLong( const Index&         index,
                  const CurrentVector& currentVector,
                  int64&                    buffer ) const;

    /** Get the input state value of the specified field in the EDR.
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param buffer Return buffer for the result
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool getInputState(const EDR::Index&         index,
                       const EDR::CurrentVector& currentVector,
                       int64&                     buffer) const;

    /** Get a long value from the edr
     *  @param fld The pin_fld_num value for the edr field
     *  @return The long value
     */
    int64 getLong( pin_fld_num_t fld ) ;

    /** Set a string value in the edr
     *  @param index The index for the edr field
     *  @param string The string value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setString( const Index&  index, 
                    const BAS::String& string );

    /** Set a string value in the edr
     *  @param index The index for the edr field
     *  @param string The string value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setString( const Index&  index,
                            const char * string );

    /** Set a string value in the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param string The string value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setString( const Index&         index, 
                    const CurrentVector& currentVector,
                    const BAS::String&        string );

    /** Set a poid value in the edr
     *  @param index The index for the edr field
     *  @param poid The poid value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setCompactPoid( const Index&  index,
                    const EDR::CompactPoid& poid );

    /** Set a poid value in the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param poid The poid value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setCompactPoid( const Index&         index,
                    const CurrentVector& currentVector,
                    const EDR::CompactPoid&        poid );

    /** Set a decimal value in the edr
     *  @param index The index for the edr field
     *  @param value The decimal value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDecimal( const Index&   index, 
                     const BAS::Decimal& value );


    /** Set a decimal value in the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param value The decimal value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDecimal( const Index&         index, 
                     const CurrentVector& currentVector,
                     const BAS::Decimal&       value );

    /** Set a long value in the edr
     *  @param index The index for the edr field
     *  @param value The long value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setLong( const Index& index, int64 value );

    /** Set a long value in the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param value The long value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setLong( const Index&         index, 
                  const CurrentVector& currentVector,
                  int64                     value );

    /** Set a date value in the edr
     *  @param index The index for the edr field
     *  @param value The date value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDate( const Index& index, 
                  const BAS::DateTime& value );

    /** Set a date value in the edr
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param value The date value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    virtual bool setDate( const Index&         index, 
                  const CurrentVector& currentVector,
                  const BAS::DateTime&      value );

    /** Set the input state value of the specified field in the EDR.
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @param value The value to set the input state to
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setInputState(const EDR::Index&         index,
                       const EDR::CurrentVector& currentVector,
                       int64                      value);

    /** Get the content type of the edr container as enum value
     *  @return The content type
     */
    contentTypeT contentType() const;

    /** Get the content type of the edr container as string
     *  @return The content type as string
     */
    BAS::String contentTypeName() const;

    /** Set the content type of the edr container
     *  @param value The new content type
     */
    void contentType( Container::contentTypeT value );

    /** Get the originiator member
     *  @return Reference to the originator name
     */
    const BAS::String& originator() const;

    /** Set the originator member
     *  @param originator The originator
     */
    void originator( const BAS::String& originator );

    /** Get the record number
     *  @return The record number of the EDR container
     */
    size_t recordNumber() const;

	/** Get the file number. The file number is defined as being the sequence
	 * of the file being processed when units per transaction is set to > 1
	 * @return the file number that is being processed. 
	 */
	size_t getFileNumber() const;

	/** Set the file number. The file number is defined as being the sequence
	 * of the file being processed when units per transaction is set to > 1
	 * @param fileNumber the number to be stored
	 */
	void setFileNumber(size_t fileNumber);

    /** Set the record number
     *  @param recordNumber The reocrd number for the EDR container
     */
    void recordNumber( size_t recordNumber );

    /** Get the container type (DATA or SERVICE) as enum value
     *  @return The value
     */
    containerTypeT containerType() const;

    /** Get the container type (DATA or SERVICE) as string
     *  @return The value
     */
    BAS::String containerTypeName() const;

    /** Set the container type (DATA or SERVICE)
     *  @param contType The new container content type
     */
    void containerType( containerTypeT contType );

    /** Get the stream number
     *  @return The output stream number of this container
     */
    size_t streamNumber() const;

    /** Set the stream number
     *  @param streamNum The output stream number for this EDR container
     */
    void streamNumber( size_t streamNum );

    /** Add an supplemental stream to the streamList
     *  @param error The new stream number to add
     */
    void addStream(size_t streamNum );

    /** Get the supplemental Stream  list for the container
     *  @return Reference to the list
     */
    const StreamNumberList& getStreamList() const;

    /** Remove an supplemental stream from the streamList
     *  @param error The stream number to remove
     */
    void removeStream(size_t streamNum );

    /** Search the supplemental Stream list for the container
     *  @return True if the stream is in the supplemental Stream list
     */
    bool containsStream( size_t streamNum );

    /** Get a stream from the supplemental Stream list for the container
     *  @return The stream number stored at the index on success or -1
     */
    int64 getStreamFromList( size_t index );

    /** Clear the supplemental streamList
     */
    void clearStreamList();


    /** Add an error to the edr container
     *  @param error The new error message to add
     */
    void addError( const BAS::Status& error );

    /** Clear the error list of the edr container
     */
    void clearErrors();

    /** Get the maximum serverity of all errors 
     *  @return The maximum severity of all errors of this container
     */
    int maxSeverity() const;

    /** Get the error list for the container
     *  @return Reference to the list wit all errors
     */
    const StatusList& errors() const;

    /** Connect a value of the edr container to an input field
     *  @param index The index for the edr container field
     *  @param token Pointer to the connected input token
     *  @param fieldDescr The field description for the file record field
     *  @param pos The position inside the token
     *  @param len The length inside the token
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool connect( const Index& index,
                  Token*       token, 
                  FieldDescr*  fieldDescr,
                  size_t           pos,
                  size_t           len );

    /** Connect a value of the edr container to an input field
     *  @param index The index for the edr container field
     *  @param currentVector Vector specifying the datablock to use
     *  @param token Pointer to the connected input token
     *  @param fieldDescr The field description for the file record field
     *  @param pos The position inside the token
     *  @param len The length inside the token
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool connect( const Index&         index,
                  const CurrentVector& currentVector,
                  Token*               token, 
                  FieldDescr*          fieldDescr,
                  size_t                   pos,
                  size_t                   len );

    /** Add a token to the EDR container
     *  @param token Pointer to the token to add
     */
    void addToken( Token* token );

    /** Get the number of tokens in the EDR container
     *  @return Number of tokens
     */
    size_t numTokens() const;

    /** Get the byte position of the EDR container's first token
     *  @return byte position >= 0 if there is a token, < 0 otherwise
     */
    size_t bytePosition() const;

    /** Get the n-th token
     *  @param n The number of the token to get
     *  @return Pointer to the token
     */
    Token* token( size_t n ) const;

    /** Get the factory belonging to this EDR container
     *  @return Pointer to the factory
     */
    Factory* factory() const;

    /** Get a token connected to an Value
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return Pointer to token on success, 0 otherwise
     */
    Token* token( const Index&         index, 
                      const CurrentVector& curVector ) const;
    

    /** Get a field description connected to an Value
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return Pointer to the field description on success, 0 otherwise
     */
    FieldDescr* fieldDescr( const Index&         index, 
                                const CurrentVector& curVector ) const;
    

    /** Global output operator
     *  @param edr Edr container to print
     */
    friend std::ostream& operator<<( std::ostream&             os,
                                const Container& edr );

    /** Get the type id of the edr's rootblock
     *  @return Type id of the rootblock
     */
    size_t rootBlockTypeId() const;

    /** Write the EDR container into an output stream
     *  @param out Output stream for the operation
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool serialize( std::ostream& out ) const;

    /** Read the EDR container from an input stream
     *  @param in Input stream for the operation
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool restore( std::istream& in );

    /** Remove a datablock in the edr container(Release to Factory)
     *  @param index The block index for the datablock to add
     *  @param currentVector Current values for the different levels
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool removeDatablock(
      const BlockIndex&    index,
      const CurrentVector& currentVector);

    /** Clear a field Value in the Container
     *  @param index The index for the edr field
     *  @param currentVector Current values for the different levels
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool clearFieldValue( const Index&         index,
                  const CurrentVector& currentVector);

    /* Get an EDR value by it's index
     * @param index The index for the edr field
     * @return Pointer to value on success, 0 otherwise
     */
    Value* valueByIndex( const Index& index ) const;

    /* Get an EDR value by it's index
     * @param index The index for the edr field
     * @param currentVector Vector with current blocks for the levels
     * @return Pointer to value on success, 0 otherwise
     */
    Value* valueByIndex( const Index&         index,
                             const CurrentVector& currentVector ) const;

    /** Setp the current Datablock
     *  @param block  the Datablock to be made current(focus)
     */
   void setCurrentDatablock(Datablock *block );

    /** Get current DataBlock
     */
   Datablock* getCurrentDatablock(); 

   Datablock* getRootBlock() const;

   /** Set the field  specified by the PIN_FLD_XXX type
     *  @param fld The pin_fld_num value for the field in the Flist
     *  @param value The string value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setField( pin_fld_num_t fld, 
                    const BAS::String& value );

   /** Set the field  specified by the PIN_FLD_XXX type
     *  @param fld The pin_fld_num value for the field in the Flist
     *  @param value The long value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setField( pin_fld_num_t fld, int64 value );

   /** Set the field  specified by the PIN_FLD_XXX type
     *  @param fld The pin_fld_num value for the field in the Flist
     *  @param value The decimal value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setField( pin_fld_num_t fld, 
                     const BAS::Decimal& value );

   /** Set the field  specified by the PIN_FLD_XXX type
     *  @param fld The pin_fld_num value for the field in the Flist
     *  @param value The poid value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setField( pin_fld_num_t fld, 
                    const EDR::CompactPoid& poid );

   /** Set the field  specified by the PIN_FLD_XXX type
     *  @param fld The pin_fld_num value for the field in the Flist
     *  @param value The date value to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setField( pin_fld_num_t fld, 
                  const BAS::DateTime& value );

    /** Check whether the current EDR container has timed out
     *  @return <b>true</b> if timed out, <b>false</b> otherwise
     */
    bool getTimedOutFlag() const;

    /** Set the timed out flag
     *  @param value The new value
     */
    void setTimedOutFlag( bool value );
    //@}

    /* Get an EDR datablock by it's index
     * @param index The index for the edr datablock
     * @return Pointer to value on success, 0 otherwise
     */
    Datablock* datablockByIndex( const BlockIndex& index ) const;

    /** Check if the value for this index is set or not
     *  @param index The index for the edr field
     *  @return <b>true</b> if state is SET , <b>false</b> otherwise
     */
    bool isValueSet(const Index& index) const;

    /** Check if the value for this index is set or not
     *  @param fld The pin_fld_num value for the edr field
     *  @return <b>true</b> if state is SET , <b>false</b> otherwise
     */
    bool isValueSet(pin_fld_num_t fld);

	/** Return the factory this container uses
	 * Added because this sometimes saves us from storing too many copies
	 * of the pointer 
	 */
	EDR::Factory* getFactory() const;

	/** Release the container.
	 * This calls releaseEDR on the factory contained within this class
	 */
	void release();

	/** get the operation type (optional). 
	 * This is used in timos to label what we did with the container
	 * @return OpType the operation that this container was used in
	 */
	OpType getOpType() const;

	/** set the operation type (optional).
	 * This is used in timos to label what we did with the container
	 * @param opType the operation being performed on the container
	 */
	void setOpType(OpType optype);
    //@}

	/** Get the input flist associated with the container. This is the same
	 * as is referred to by 'flist'. This flist is owned by the container and
	 * kept until the container is recycled 
	 * @return PinFlistObserver
	 */
	PinFlistObserver getInputFlist() const;

	/** Set the input flist associated with the container.
	 * @param flist flist to store.
	 */
	void setInputFlist(PinFlistOwner& flist);

	/** Get the output flist associated with the container. This flist
	 * is owned by the container and kept until the container is recycled.
	 * @return PinFlistObserver
	 */
	PinFlistObserver getOutputFlist() const;

	/** Set the output flist associated with the container.
	 * @param flist the flist to store.
	 */
	void setOutputFlist(PinFlistOwner& flist);

	/** Get the opcode that the container is expected to call. This will
	 * be altered to be a member of the container.
	 * @return PinOp opcode that will be called
	 */
	PinOp getOpcode() const;

	/** Set the opcode that the container is expected to call. 
	 * @param opcode opcode to call.
	 */
	void setOpcode(PinOp opcode);
	
    /* Get the source flist 
     * Only used by the PCM Input device
     */
    pin_flist_t* flist() const;

    /* Set the source flist
     * Only used by the PCM Input device
     */
    void flist( pin_flist_t* flistp );

    /** Get the pcm context.
     * Used for executing opcode from the RTDP
     * @return Pointer to the pcm context
     */
    pcm_context_t* getPcmContext() const;

    /** Set the pcm context.
     * Used for executing opcode from the RTDP
     * @param Pointer to the pcm context
     */
    void setPcmContext( pcm_context_t* ctxp );

    /* Get an EDR datablock value by it's index
     * @param index The index for the edr datablock
     * @return Pointer to value on success, 0 otherwise
     */
    DatablockValue* datablockValueByIndex( const BlockIndex& index ) 
      const;

    /* Get an EDR datablock value by it's index
     * @param index The index for the edr datablock
     * @param currentVector Vector with current blocks for the levels
     * @return Pointer to value on success, 0 otherwise
     */
    DatablockValue* datablockValueByIndex( 
                          const BlockIndex&    index,
                          const CurrentVector& currentVector ) const;

    /* Get an EDR datablock by it's index using a current vector
     * @param index The index for the edr datablock
     * @param currentVector Vector with current blocks for the levels
     * @return Pointer to value on success, 0 otherwise
     */
    Datablock* datablockByIndex( 
                     const BlockIndex&    index,
                     const CurrentVector& currentVector ) const;

    /** Log record buffer accessor.
	 *	@return Value of the container's log record buffer.
     */
    char* getLogRecordBuffer() const;

    /** Log record buffer mutator.
     *  @param buffer The value to set.
     */
    void setLogRecordBuffer(char* buffer);

    /** Get the array index ID of a datablock
     *  @param index The block index for the datablock
     *  @return The array index ID of the datablock
     */
    int32 getArrayIndexId( const BlockIndex& index ) const;

    /** Get the array index ID of a datablock
     *  @param index The block index for the datablock
     *  @param currentVector Current values for the different levels
     *  @return The array index ID of the datablock
     */
    int32 getArrayIndexId( const BlockIndex&    index,
                           const CurrentVector& currentVector ) const;

    /** Set the array index ID of a datablock
     *  @param index The block index for the datablock
     *  @param currentVector Current values for the different levels
     *  @param value The larray index ID to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setArrayIndexId( const BlockIndex& index,
                          int32             value );

    /** Set the array index ID of a datablock
     *  @param index The block index for the datablock
     *  @param currentVector Current values for the different levels
     *  @param value The array index ID to set
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool setArrayIndexId( const BlockIndex&    index,
                          const CurrentVector& currentVector,
                          int32                value );

   /** Walk through this EDR Container to set a flag in all set/connected/initialized fields and datablocks
     */
    void markSetFields();

    /** Mark the specified EDR field
     *  @param index The index for the EDR field
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool markField( const EDR::Index&         index        );

    /** Mark the specified EDR field
     *  @param index The index for the EDR field
     *  @param currentVector Current values for the different levels
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool markField( const EDR::Index&         index,
                    const EDR::CurrentVector& currentVector);

    /** Reset the original value of the specified EDR field
     *  @param index The index for the EDR field
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool resetSavedValue( const EDR::Index&         index);

    /** Reset the original value of the specified EDR field
     *  @param index The index for the EDR field
     *  @param currentVector Current values for the different levels
     *  @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool resetSavedValue( const EDR::Index&         index,
                          const EDR::CurrentVector& currentVector);

   /** Serialize this EDR Container to XML
     *  @param markedOnly  only dump the marked blocks to xml for recycle.
     *  @return XML XML representation of the EDR if sucessful, BAS::NULL_STRING otherwise.
     */
    BAS::String getEdrXml( bool markedOnly = false );

    /** Accesor to get serialized Buffer assembled for ACE_Messge_blocks
	 *	@return Value of the container's log serialized buffer.
     */
    char* getSerializedBuffer() const;

    /** mutator to set the serialized buffer.
     *  @param buffer The value to set.
     */
    void setSerializedBuffer(char* buffer);

    virtual void clearChangeLog();

    /** Sets the original default stream number value
     */
    void setOrigDefaultStreamNumber ( size_t streamNumber ) ;

    /** Gets the original default stream number value
     */
    size_t getOrigDefaultStreamNumber () const ;

  protected:

    /* Constructor
     * @param factory The factory for this container
     */
    Container( Factory* factory );

    /* Destructor
     */
    virtual ~Container();

    /* Copy the data from another EDR container. This function is used
     * by the factory to duplicate EDR containers.
     */
    virtual void copyData( const Container* );

    /* Clear the container (called by destructor and assignment operator)
     */
    virtual void clear();

  private:

    /* Release the datablocks of the container
     */
    void releaseDatablocks();

    /* Get the EDR containers cache successor
     * @return Pointer to the cache successor (can be 0)
     */
    Container* cacheSucc() const;

    /* Initialize the edr containers root datablock
     * @param index The container index for the root datablock
     * @return <b>true</b> on success, <b>false</b> otherwise
     */
    bool init( const ContainerIndex& index );

    /* Set the EDR containers cache successor
     * @param edr The new cache successor
     */
    void cacheSucc( Container* edr );

    /* Get the root datablock
     * @return Pointer to the root datablock
     */
    Datablock* rootBlock() const;

    // hide the default constructor (not implemented)
    Container();
    Container( const Container& other );
    const Container& operator=( const Container& other );

    // instance members
    Factory*                         factoryM;
    Datablock*                       rootBlockM;
    Container*                       cacheSuccM;
    BAS::String                      currentPluginM;

	PinFlistObserver                 inFlistM;
	PinFlistObserver                 outFlistM;
	PinOp                            opcodeM;

    pcm_context_t*                   ctxpM;
    RWTValOrderedVector<TokenHandle> tokensM;

    // compatibility members
    BAS::String     originatorM;
    StatusList errorsM;
    size_t         recordNumberM;
    size_t         streamNumberM;

    StreamNumberList streamListM;

    int            maxSeverityM;

    contentTypeT   contentTypeM;   
    containerTypeT containerTypeM;
	OpType         opTypeM;

    bool           isValidDetailM;

#ifdef _DEBUG
	/** Flag as to whether the 'isValidDetail' function has been called or
	 * not. Used only in debug builds to verify whether or not the plugin
	 * has checked this, which is part of the plugin API contract.
	 */
	bool           isValidDetailCheckedM;
#endif

	/** @todo Handle to the dynamically allocated log record buffer. This
	 *		is used to delete the buffer when the container is released.
	 */
	char* logRecordBufferM;

	/** This is the serailized buffer assembled from ACE_Message_Blocks
	 *   which can be used to free during release if set	
	 */
	char* serializedBufferM;

	// Static data
	EDR_EXPORT static const BAS::String detailCM;

    // Timed Out Flag - used by AAA GW
    bool           timedOutFlagM;
    RWMutexLock    timedOutMutexM;

    // All setFields are relative to this Datablock
    Datablock*                       currentBlockM;

	// The file number
	size_t fileNumberM;

      /** This stores the original Stream number assoicated with the EDR (as specified
       *  in the registry) . This value remains unchanged even on execution
       *  IScript's edrSetStream function or the execution of
       *  streamNumber ( size_t streamNum ) function
       */
      size_t origDefaultStreamNumberM ;

    // friends
    friend class Factory;
    friend class ContainerCache;
    friend class ValueIterator;
    friend class OutputMapping;
    friend class OutMapFix;
    friend class SaxHandler;
};

std::ostream& operator<<(std::ostream& os, const Container& edr);

//==============================================================================
// Get the cache successor
//==============================================================================
inline Container*
Container::cacheSucc() const
{
  return cacheSuccM;
}

//==============================================================================
// Set the cache successor
//==============================================================================
inline void 
Container::cacheSucc( Container* edr )
{
// CodeReview - 08.2001 - mwriedt - V - 04.08 use RWPRECONDITION
// Checked by CodeReview - 08.2001 - sd - C - edr can be 0 here, when there
//   is no cache successor. So a precondition would be wrong!
  cacheSuccM = edr;
}

//==============================================================================
// Get the pcm context
//==============================================================================
inline pcm_context_t*
Container::getPcmContext() const
{
  return ctxpM;
}

//==============================================================================
// Set the pcm context
//==============================================================================
inline void
Container::setPcmContext( pcm_context_t* ctxp )
{
  ctxpM = ctxp;
}

//==============================================================================
// Get the root datablock
//==============================================================================
inline Datablock*
Container::rootBlock() const
{
  return rootBlockM;
}

inline Datablock*
Container::getRootBlock() const
{
    return rootBlock();
}


//==============================================================================
// Get the type id of the root datablock
//==============================================================================
inline size_t
Container::rootBlockTypeId() const
{
  RWPRECONDITION( rootBlockM != 0 );
  return rootBlockM->blockTypeId();
}

//==============================================================================
// Get the content type of the edr container
//==============================================================================
inline 
Container::contentTypeT Container::contentType() const
{
  return contentTypeM;
}

//==============================================================================
// Set the content type of the edr container
//==============================================================================
inline void 
Container::contentType( Container::contentTypeT value )
{
  contentTypeM = value;
}

//==============================================================================
// Get the originator
//==============================================================================
inline const BAS::String&
Container::originator() const
{
  return originatorM;
}

//==============================================================================
// Set the originator
//==============================================================================
inline void
Container::originator( const BAS::String& originator )
{
  originatorM = originator;
}

//==============================================================================
// Get the record number
//==============================================================================
inline size_t
Container::recordNumber() const
{
  return recordNumberM;
}

//==============================================================================
// Set the record number
//==============================================================================
inline void
Container::recordNumber( size_t recordNumber )
{
  recordNumberM = recordNumber;
}

//==============================================================================
// Get the container type
//==============================================================================
inline Container::containerTypeT
Container::containerType() const
{
  return containerTypeM;
}

//==============================================================================
// Set the container type
//==============================================================================
inline void
Container::containerType( Container::containerTypeT contType )
{
  containerTypeM = contType;
}

//==============================================================================
// Get the stream number
//==============================================================================
inline size_t
Container::streamNumber() const
{
  return streamNumberM;
}

//==============================================================================
// Set the record number
//==============================================================================
inline void
Container::streamNumber( size_t streamNum )
{
  streamNumberM = streamNum;
}

//==============================================================================
// Add stream number to list
//==============================================================================
inline void
Container::addStream(size_t streamNum)
{
  D_ENTER( "EDR::Container::addStream(size_t)" );

  if (streamListM.contains(streamNum) == false)
    streamListM.append( streamNum );

}
//==============================================================================
// Get supplemental stream number list
//==============================================================================
inline const StreamNumberList& 
Container::getStreamList() const
{
  D_ENTER( "EDR::Container::getStreamList() const" );

  return streamListM;
}
//==============================================================================
// Remove supplemental stream number from list
//==============================================================================
inline void 
Container::removeStream(size_t streamNum )
{
  D_ENTER( "EDR::Container::removeStream(size_t)" );

  if (streamListM.contains(streamNum) == true)
    streamListM.remove( streamNum );

}

//==============================================================================
// Search supplemental stream number list
//==============================================================================
inline bool
Container::containsStream( size_t streamNum )
{
  D_ENTER( "EDR::Container::containsStream(size_t)" );

  return streamListM.contains(streamNum);
}

//==============================================================================
// Clear supplemental stream number list
//==============================================================================

inline void 
Container::clearStreamList()
{
  D_ENTER( "EDR::Container::clearStreamList(size_t)" );

  streamListM.clear();
}

//==============================================================================
// Add an error to the edr container
//==============================================================================
inline void 
Container::addError( const BAS::Status& value )
{
  errorsM.append( value );
  if ( value.severity() > maxSeverityM ) 
  {
    maxSeverityM = value.severity();
  }
}

//==============================================================================
// Check if there is a error message with severity > warning
//==============================================================================
inline bool 
Container::hasError() const
{
  return( maxSeverityM > BAS::Status::warning );
}

//==============================================================================
// Get the max severity of all errors
//==============================================================================
inline int
Container::maxSeverity() const
{
  return maxSeverityM;
}

//==============================================================================
// Get the edr container's errors
//==============================================================================
inline const StatusList& 
Container::errors() const
{
  return errorsM; 
}

//==============================================================================
// Add a new token to the EDR container
//==============================================================================
inline void
Container::addToken( Token* token )
{
  // CodeReview - 08.2001 - mwriedt - V - 04.08 use RWPRECONDITION
  // Checked by CodeReview - 08.2001 - sd - C - Why should I check it here?
  //   Nothing is dependend on token != 0 here. There is a precondition in
  //   the constructor of TokenHandle.
  tokensM.append( TokenHandle( factoryM, token ) );
}

//==============================================================================
// Get the number of tokens
//==============================================================================
inline size_t
Container::numTokens() const
{
  return tokensM.entries();
}

//==============================================================================
// Get the n-th token
//==============================================================================
inline Token*
Container::token( size_t n ) const
{
  return tokensM(n).token();
}

#ifdef _DEBUG
inline bool
Container::isValidDetailChecked() const
{
	return isValidDetailCheckedM;
}

inline void
Container::clearIsValidDetailChecked()
{
	isValidDetailCheckedM = false;
}
#endif

//==============================================================================
// Check if EDR is a valid detail
//==============================================================================
inline bool
Container::isValidDetail() const
{
#ifdef _DEBUG
	bool& isValidDetailNonConst = const_cast<bool&>(isValidDetailCheckedM);
	isValidDetailNonConst = true;
#endif
  return isValidDetailM;
}

//==============================================================================
// Set the isValidDetail flag
//==============================================================================
inline void
Container::isValidDetail( bool flag )
{
  isValidDetailM = flag;
}

//==============================================================================
// Get a pointer to the EDR's factory
//==============================================================================
inline Factory*
Container::factory() const
{
  return factoryM;
}

//==============================================================================
// Clear the error list
//==============================================================================
inline void
Container::clearErrors()
{
  maxSeverityM = 0;
  errorsM.clear();
}

//==============================================================================
// Get the byte position of the first token
//==============================================================================
inline size_t
Container::bytePosition() const
{
  if ( numTokens() > 0 )
  {
    return token(0)->bytePosition();
  }
  else
  {
    return 0;
  }
}
//==============================================================================
// Set the Curent Datablock
//==============================================================================
inline void
Container::setCurrentDatablock(Datablock *block)
{
  currentBlockM  = block;
}

inline Datablock*
Container::getCurrentDatablock()
{
  return currentBlockM ;
}

inline OpType
Container::getOpType() const
{
	return opTypeM;
}

inline void
Container::setOpType(OpType op)
{
	opTypeM = op;
}

inline char*
Container::getLogRecordBuffer() const
{
	return logRecordBufferM;
}
inline void
Container::setLogRecordBuffer(char* buffer)
{
	logRecordBufferM = buffer;
}

//==============================================================================
// Get the serialized buffer stored in container while restoring 
//==============================================================================

inline char*
Container::getSerializedBuffer() const
{
	return serializedBufferM;
}

//==============================================================================
// set the serialized buffer used to restore this container
//==============================================================================
inline void
Container::setSerializedBuffer(char* buffer)
{
	if (serializedBufferM == buffer)
	{
		return;
	}
	// If getting reused for serialization later, we have to allow 
	// resetting with null arg and not delete here.
	if (serializedBufferM != 0)
	{
		delete [] serializedBufferM;
	}
	serializedBufferM = buffer;
}

}
#endif // CONTAINER_HPP
