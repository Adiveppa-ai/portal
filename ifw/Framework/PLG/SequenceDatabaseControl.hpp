#ifndef PLG_SEQUENCE_DATABASE_CONTROL_HPP
#define PLG_SEQUENCE_DATABASE_CONTROL_HPP
//==============================================================================
//
// Copyright (c) 1996, 2013, Oracle and/or its affiliates. All rights reserved.
//      
//      This material is the confidential property of Oracle Corporation or its
//      licensors and may be used, reproduced, stored or transmitted only in
//      accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: PLG
//------------------------------------------------------------------------------
// Module Description:
//   Sequence controller with database interface
//
// Open Points:
//   <open points>
//
// Review Status:
//   in-work
//
//------------------------------------------------------------------------------
// Responsible: Giles Douglas
//==============================================================================

#ifndef   PLG_SEQUENCE_CONTROL_HPP
  #include "PLG/SequenceControl.hpp"
#endif

#ifndef   __RWDB_CONNECT_H__
  #include <rw/db/connect.h>
#endif

#ifndef  __RWT_LOCK_GUARD_H__
  #include <rw/sync/RWTLockGuard.h>
#endif

namespace DBC
{
class DatabasePlugIn;
}
namespace PLG
{

/** A sequence controller with database interface. 
    The controller holds all his information in
    the database tables IFW_PIPELINE and IFW_EDRSEQLOG.

    <p><table BORDER CELLSPACING=0 CELLPADDING=2 NOSAVE >
    <tr>
    <td><font size=-1>$RCSfile: SequenceDatabaseControl.hpp $</font></td>
    <td><font size=-1>$Revision: /cgbubrm_7.5.0.pipeline/2 $</font></td>
    <td><font size=-1>$Date: 2013/07/03 20:50:12 $</font></td>
    <td><font size=-1>$Author: vinodrao $</font></td>
    </tr>
    </table>                                                                          

<p><dl>
   <dt><b>Registry entries</b></dt>
         <dd>none</dd>
    <dt><b>Messages send</b></dt>
         <dd>none</dd>
    <dt><b>Messages received</b></dt>
         <dd>none</dd>
    <dt><b>Requests send</b></dt>
         <dd>none</dd>
    <dt><b>Requests received</b></dt>
         <dd>none</dd>
    <dt><b>Errors</b></dt>
         <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
         <dd>ERR_OBJ_NOT_FOUND</dd>
         <dd>ERR_PLUGIN_TYPE_INVALID</dd>
         <dd>ERR_REG_NAME_NOT_FOUND</dd>
         <dd>ERR_DATABASE</dd>
         <dd>ERR_SEQ_ALREADY_PROCESSED</dd>
</dl>
*/
class SequenceDatabaseControl : public SequenceControl
{
  public:

    /**@name SequenceDatabaseControl Constructors and Destructors */
    //@{
    /** Default constructor.<br>
        Creates an unregistered object.
    */
    SequenceDatabaseControl();
                                             
    /** Standard constructor.<br>
        Creates an registered sequence controller.
        @param name The name for the created object.
        @param check True if sequence check is active.
        @param generate True if sequence generation is active.
    */
    SequenceDatabaseControl(const BAS::String& name);

    /** Destructor. */
    virtual ~SequenceDatabaseControl();
    //@}                                   

    /**@name Main methods. */
    //@{

    /** Observer pattern update function.
    */
    void update(const BAS::String& name);

    /** Observer pattern update function.
    */
    bool update(const BAS::Status& status);

    /* Initialise the sequence controller.
    */
    virtual bool init();

    //@}

  protected:
    /** Initialise an instance from the registry.
        @return <tt>False</tt> if the object could not initialise itself successfully,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool readRegistry();         

    /** Initilialise from environment.
        @return <tt>False</tt> if the object could not read the environment information,<br>
                <tt>true</tt> otherwise.
    */
    virtual bool evalEnvironment();

    /** Check the original sequence number.
    */
    virtual bool checkForDouble(const BAS::String & seqCheckKey);

    /** Write the sequence data into the sequence file
    */
    virtual bool writeSequenceInformation(const BAS::String & key, const TAM::TransId & transId);

    /** Log the actual sequence information.
    */
    virtual bool logSequenceInformation(SequencerInformation& seqInfo);

    /** Log the actual sequence information.
    */
    virtual bool logSequenceInformation_In( SequencerInformation_In& seqInfo_In);


    /** Commit the Database operations */
    virtual bool commitToStorage();

    /** Rollback the database operations */
    virtual bool rollbackFromStorage();

    /** Get connection.
    */
    RWDBConnection& connection();

    /** Get database plug in
    */
    const DBC::DatabasePlugIn* dataPlugIn() const;

    // insert new key into the database!
    virtual bool insertIntoDatabase(const BAS::String & key) ;

  private: 

    // not implemented
    SequenceDatabaseControl(SequenceDatabaseControl&);
    void operator=(const SequenceDatabaseControl&);

    void getDBConnection();

    // Database connection
    DBC::DatabasePlugIn* dataPlugInM;

    // Roguewave database connection object
    RWDBConnection dbConnectionM;

    // Lock for DB Connection
    RWMutexLock connectionLockM;

    // registry strings
    PLG_EXPORT static const BAS::String registrySequenceDataPoolCM;
    PLG_EXPORT static const BAS::String registrySequenceDataConnectionCM;

    PLG_EXPORT static const BAS::String defaultEmptyKeyCM;

};

inline const DBC::DatabasePlugIn* SequenceDatabaseControl::dataPlugIn() const
{
  return dataPlugInM;
}
}
#endif 
