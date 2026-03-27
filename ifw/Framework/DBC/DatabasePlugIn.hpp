#ifndef DBC_DATABASEPLUGIN_HPP
#define DBC_DATABASEPLUGIN_HPP 

//==============================================================================
//
// Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
// All rights reserved. 
// 
// This material is the confidential property of Oracle Corporation or its
// licensors and may be used, reproduced, stored or transmitted only in
// accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
// Block: DBC
//------------------------------------------------------------------------------
// Module Description:
//  DatabasePlugIn class implementation.
//
//------------------------------------------------------------------------------
// Revision: 10013 7.3  14-Aug-2006 ageorge
// PRSF00228082  "Pipeline changes for get_new_poid stored proc change..."
//
// Revision: 10008 7.2_Patch 11-Aug-2005 psagar
// PRSF00177605 - WIN+Itanium+SQL:  testnap fails if cm is restarted when pipeline is running.
//
// Revision: 10007 7.2     20-Jun-2005 psagar
// PRSF00172212 - WIN+SQL+Itanum: DAT::ItemAssign Pluging is failing at the 
//                time of Pipeline startup.
//
// Revision: 10006 6.7_FP2 19-Mar-2004 brajan
// PRSF00086920 - [Pipeline] Code Cleanup: Remove Remains from DB Version Check
//
// Revision: 10005  6.7_FP2  05-Feb-2004  kirk
// PRSF00090115 - Providing BAS::IdetifierIdIterator interface for poid ids.
//
// Revision: 10004  6.7_FP1  10-Dec-2003  kirk
// PRSF00081177 - Adding poid id retrieval functions.
//
// Revision: 10003  6.5_SP2  29-Apr-2003  keshav
// PRSF00037803: Log unused semaphores
//
// Revision 1.16  2002/01/30 13:39:06  pengelbr
// Add ansiSql flag.
//
// Revision 1.15  2001/10/09 08:35:16  bt
// PETS #38593 DB2 Port
// - New registry parameter 'ConvertToUpperCase' (modifies password decryption)
// - Workaround for rwdbTrimBoth (DBTools DB2 default does not work)
//
// Revision 1.14  2001/08/01 14:44:57  pengelbr
// PETS #37618 CodeReview 08.2001
//
// Revision 1.13  2001/07/04 13:37:23  bt
// PETS #36559 Changes for Rogue Wave SourcePro migration.
//
// Revision 1.12  2001/05/17 12:47:37  bt
// Disable the version check, if the database table IFW_DBVERSION does not exist.
//
// Revision 1.11  2001/01/11 12:51:52  clohmann
// dbvector.h included.
//
// Revision 1.10  2000/09/08 13:35:15  mwriedt
// Made old connection methods private.
//
// Revision 1.9  2000/08/29 12:44:26  mwriedt
// Made max db version entry optional.
//
// Revision 1.8  2000/07/25 15:06:32  mwriedt
// Readded version check.
//
// Revision 1.7  2000/04/17 09:08:18  bt
// - Database version check removed.
// - Initialize the database version with the contents of table PLI_DBVERSION.
// - Method dbVersion() returns the retrieved database version.
//
// Revision 1.6  2000/03/27 12:32:45  bt
// Database reconnect (registry update) changed.
//
// Revision 1.5  2000/03/24 16:23:47  bt
// Database version check added.
//
// Revision 1.4  2000/03/13 16:59:19  bt
// - Initialize the database version with the contents of table PLI_DBVERSION.
// - Method dbVersion() returns the retrieved database version.
//
// Revision 1.3  2000/01/26 09:24:43  bt
// Method errorMessage() changed to static.
//
// Revision 1.2  1999/10/28 08:06:37  pengelbr
// CodeReview - 10.1999 - pengelbr
//
// Revision 1.1  1999/10/21 07:53:51  bt
// Initial version.
//
//==============================================================================

#if !defined DBC_EXPORT
  #if defined(WINDOWS)
    #if !defined(DBC_INTERNAL)
      #define DBC_EXPORT __declspec(dllimport)
    #else
      #define DBC_EXPORT __declspec(dllexport)
    #endif
  #else
    #define DBC_EXPORT 
  #endif
#endif

#ifndef   BAS_IDENTIFIER_H
  #include "BAS/Identifier.hpp"
#endif
#ifndef   BAS_IDENTIFIERIDITERATOR_HPP
  #include "BAS/IdentifierIdIterator.hpp"
#endif
#ifndef   BAS_STRING_HPP
  #include "BAS/String.hpp"
#endif
#ifndef   BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif
#ifndef   PLG_DATA_PLUG_IN_HPP
  #include "PLG/DataPlugIn.hpp"
#endif

#ifndef   __RWDB_DB_H__
  #include <rw/db/db.h>
#endif
#ifndef   RWDBVECTOR_H
  #include <rw/db/dbvector.h>
#endif
#ifndef   RW_TOOLS_TPMAP_H
  #include <rw/tpmap.h>
#endif
#ifndef   _PIN_PARTITION_MODE_H_
  #include "pin_partition_mode.h"
#endif
namespace DBC
{
	// These are the names of the Oracle PL/SQL stored procedures.
	/* DBC_EXPORT REVISIT */ static const BAS::String SPROC_NAME_GET_NEW_POID_ID(
		"PIN_SEQUENCE.GET_NEW_POID_ID");
	/* DBC_EXPORT REVISIT */ static const BAS::String SPROC_NAME_GET_NEW_POID_ID_RANGE(
		"PIN_SEQUENCE.GET_NEW_POID_ID_RANGE");

        // These are the names for SQL Server
        static const BAS::String SQL_SPROC_NAME_GET_NEW_POID_ID("get_new_poid_id");
        static const BAS::String SQL_SPROC_NAME_GET_NEW_POID_ID_RANGE("get_new_poid_id_range");
         

	// Maximum poid ids retrieved in a single call.
	// If the user requests 1M to 10M, they will only get back 1M.
	// If the user requests more than 10M, they are insane and must be stopped.
	static const size_t MAX_POID_IDS_PER_CALL =      1000000;  // 1M
	static const size_t TOO_MANY_POID_IDS_PER_CALL = 10000000; // 10M

//------------------------------------------------------------------------------
// RWTValHashMap hash object for RWDBConnectionMap
//------------------------------------------------------------------------------

class RWDBConnectionHash
{
  public:

    u_int64 operator()(const u_int64& value) const
    {
      return value;
    }
};

//------------------------------------------------------------------------------
// RWTValHashMap type definition for RWDBConnectionMap
//------------------------------------------------------------------------------

typedef RWTValHashMap< u_int64,
                       RWDBConnection,
                       RWDBConnectionHash,
                       equal_to<u_int64> > RWDBConnectionMap;


//------------------------------------------------------------------------------
/** This class provides database connectivity.

    <p> The default connection should be used only to retrieve data
        (therefore, autocommit is turned off). New connections are
        created with the DBTools.h++ default mode (autocommit is turned on).
        On those connections the RWDBConnection methods beginTransaction(),
        rollbackTransaction() and commitTransaction() must be used to
        manage transactions. A registry update with the registry name
        'Reconnect' closes all open connections and reconnects the database.
        All attached observers will be notified (method update()). The version
        check is based on version files provided by every module that needs a
        database connection. If the database table IFW_DBVERSION does not
        exist, the version check will be disabled.<br><br>

    <dl>
    <dt><b>Registry entries</b></dt>
    <dd>UserName</dd>
    <dd>PassWord (encrypted password with a hexadecimal format)</dd>
    <dd>DatabaseName</dd>
    <dd>Connections (default = 1)</dd>
    <dd>ServerName (default = '')</dd>
    <dd>AccessLib (without prefix 'lib' and suffix 'xxd.so',
                   possible choices = 'or843', 'or943' or 'db243')</dd>
    <dd>UsableCheckTable (default = 'DUAL')</dd>
    <dd>ConvertToUpperCase (default = 'True')</dd>
    <dd>Reconnect</dd>
    <dt><b>Messages send</b></dt>
    <dd>none</dd>
    <dt><b>Messages receive</b></dt>
    <dd>none</dd>
    <dt><b>Errors</b></dt>
    <dd>ERR_DATABASE</dd>
    <dd>ERR_CANNOT_DECRYPT_PASSWORD</dd>
    <dd>ERR_CANNOT_OPEN_DATABASE</dd>
    <dd>ERR_CANNOT_INIT_DB_VERSION</dd>
    <dd>ERR_INVALID_REG_VALUE</dd>
    <dd>ERR_OBJ_NOT_INITIALIZED</dd>
    <dd>ERR_REG_NAME_NOT_FOUND</dd>
    <dd>ERR_REG_SUBTREE_NOT_FOUND</dd>
    <dd>ERR_REG_UPDATE_FAILED</dd>
    <dd>ERR_FILE_OPEN_OS</dd>
    <dd>ERR_NO_DIR</dd>
    <dd>ERR_VERSION_CHECK_FAILED</dd>
    <dd>WRN_NO_VALID_ENTRY</dd>
    <dd>INF_DATABASE_OPENED</dd>
    </dl> 
*/
//------------------------------------------------------------------------------

class DatabasePlugIn : public PLG::DataPlugIn
{
  D_MULTITHREADED

  public :

    /**@name Public Constructors */
    //@{

      /** Default constructor.<br>
          Creates an unregistered object. */
      DatabasePlugIn();

      /** Standard constructor.<br>
          Creates an registered object.
          @param name    Name of the object. 
          @param version Version of the object. */
      DatabasePlugIn(const BAS::String& name,
                         const BAS::String& version);

    //@}

    /**@name Public Destructor */
    //@{

      /// Virtual destructor.
      virtual ~DatabasePlugIn();

    //@}

    /**@name Public Member Functions */
    //@{

      /** Returns a reference to a default connection
          with version check (one per thread).
          @param libName Library name of the calling module. */
      virtual const RWDBConnection& defaultConnection(const BAS::String& libName);

    // Returns a new connection without version check.
      virtual RWDBConnection connection();

       virtual RWDBConnection openConnection();

      /** Returns the number of entries in the connection pool.
       *
       * @return The number of connections.
       */
      virtual size_t connections();

      /** Returns the state of the ANSI-compliance of the AccessLib. */
      virtual bool ansiSql() const;

      /** Produces a new database object.
        * @param userName User name.
        * @param passWord Encrypted password.
        * @param databaseName Database name.
        * @param serverName Server name (default = '').
        * @param accessLib Access library without
        *                  prefix 'lib' and suffix 'xxd.so'.
        * @param connections Number of connection pool entries (default = 1).
        * @param toUpperCase If true, convert to upper-case. (default = true).
        * @return The new database object. */
      virtual RWDBDatabase database(const BAS::String& userName,
                                    const BAS::String& passWord,
                                    const BAS::String& databaseName,
                                    const BAS::String& serverName = "",
                                    const BAS::String& accessLib = "",
                                    const size_t connections = 1,
                                    const bool toUpperCase = true);

      /** Routine to reconnect the default database.
        * @param updateRegistry The registry tree with values to be updated.
	* @param workedOn Reference to set to true if anything was changed.
	*/
      virtual bool registryUpdate(const BAS::RegistryEntry* updateRegistry,
                                  BAS::ProtectedBool&       workedOn);

      /** Check the usability of the module. */
      virtual bool isUsable();

      /** Returns the database version string. */
      virtual BAS::String dbVersion();


      /** Acquire a new poid id value from the database.
       * Currently only supported for Oracle Infranet databases, this method
       * accesses the pin_sequence PL/SQL package to retrieve a new poid id
       * value from the POID_IDS2 sequence.  By default, the returned value is
       * mangled per standard Infranet processing.<p>
       *
       * @param className The name of the storable class for which the poid id
       * is being requested.
       * @param mangle The client can request for the returned poid id to not be
       * mangled (have its last 12 bits reversed).  This should only be set to 
       * false if the caller will be performing the mangling themselves (e.g.
       * for performance reasons or backwards-compatibility).
       *
       * @return An iterator which contains the poid id.  Check the iterator's
       * status to ensure the poid id is valid.
       */
      BAS::IdentifierIdIterator getPoidId(BAS::String className = "", bool mangle = true);

      /** Acquire a new, contiguous range of poid id values from the database.
       * Currently only support for Oracle Infranet databases, this method
       * accesses the pin_sequence PL/SQL package to retrieve a new
       * contiguous range of poid ids.<p>
       *
       * Note that the returned poid ids are not mangled.  If the caller intends
       * to mangle each poid id himself, he can optionally request for the range to
       * not be padded - thereby using 8k less poid ids from the sequence per function
       * call.  (For example, dm_timos performs its own mangling and therefore can
       * help to preserve the poid ids by passing in a false padRange argument;
       * IREL does not mangle the poid ids it retrieves and therefore must pad
       * the range.)
       * 
       * @param quantity The number of poid ids desired.
       * @param className The name of the storable class for which the poid id
       * is being requested.
       * @param padRange Will add a 4k buffer to the beginning and end of the
       * retrieved range to prevent collision with exsting or future poid ids.  This
       * supports a caller who does not want to mangle the poid ids, and simply use
       * them as they are returned.  A caller who will mangle the poid ids before
       * inserting them into the database can optionally not have the range padded
       * simply to omit potential poid id waste.  If you don't know or understand this,
       * just use the default.
       *
       * @return An iterator which contains the poid ids.  Check the iterator's
       * status to ensure the poid ids are valid.  If the requested quantity is > 1M
	   * but less than 10M, the returned quantity is 1M.  If the requested quantity
	   * is > 10M, the returned quantity is zero.
       */
      BAS::IdentifierIdIterator getPoidIds(
		const size_t quantity,
		BAS::String className = "",	
		bool padRange = true);

    //@}

    /**@name Static Public Member Functions */
    //@{

      /** Returns the error message of the given database status.
        * @param errStatus The database error status.
        * @return The database error message. */
      static BAS::String errorMessage(const RWDBStatus& errStatus);

    //@}

  private:

	/** This is in sync with the pin_sequence.get_new_poid_id sproc.
	 */
	enum GetNewPoidIdMangleType
	{
		MANGLE = 0,   // By default the returned value is mangled.
		DO_NOT_MANGLE // Clients can request to not have it mangled.
	};

	/** This is in sync with the pin_sequence.get_new_poid_id_range sproc.
	 */
	enum GetNewPoidIdRangePadType
	{
		PAD_RANGE = 0,   // By default the allocated range is padded.
		DO_NOT_PAD_RANGE // Clients can request to not pad the range.
	};

    // The following private attributes and functions are used internally.

      RWDBDatabase databaseM;

   // updateDatabaseM is a database object which is used only for updating database.
   // In the getNewPoidIdRange and getNewPoidId we are updating the table poid_ids.
   // Then featching the updated values. All the time this feature was working because
   // oracle supports autonomous transactions and with in the stored proc we have 
   // transaction handling. This way even with default connection it used to work fine.
   // Since SqlServer doesn't support this kind of feature, the tables are getting locked
   // When we use default connection and leave transactions open from the default connection.

      RWDBDatabase updateDatabaseM;

      RWMutexLock databaseLockerM;

      RWDBConnectionMap defaultConnectionTableM;

      RWMutexLock defaultConnectionTableLockerM;

      BAS::String userNameM;

      BAS::String passWordM;

      BAS::String databaseNameM;

      BAS::String serverNameM;

      BAS::String accessLibM;

      BAS::String dbVersionM;

      BAS::String usableCheckTableM;

      size_t connectionsM;

      bool toUpperCaseM;

      bool ansiSqlM;

    // Class members.

      DBC_EXPORT static const RWDBConnection invalidConnectionCM;

    // Read the configuration values out of the registry.
      virtual bool readRegistry();

    // Initialize the database with the given values.
      RWDBDatabase initDatabase(const BAS::String& userName, 
                                const BAS::String& passWord, 
                                const BAS::String& databaseName,
                                const BAS::String& serverName, 
                                const BAS::String& accessLib,
                                const size_t connections,
                                const bool toUpperCase);

     // Initialize the database with the given values, there will be no default connection in this object.
     RWDBDatabase initUpdateDatabase(const BAS::String& userName, 
                                const BAS::String& passWord, 
                                const BAS::String& databaseName,
                                const BAS::String& serverName, 
                                const BAS::String& accessLib,
                                const bool toUpperCase);

    // Returns a default connection without version check.
      virtual const RWDBConnection& defaultConnection();


    // Copy constructor and assign operator are not implemented.
    // They are private to prevent unintentionally use.

      DatabasePlugIn(DatabasePlugIn& right);

      const DatabasePlugIn& operator=(DatabasePlugIn& right);

      /** Actual method to acquire a new poid id value from the database.
       * Currently only supported for Oracle Infranet databases, this method
       * accesses the pin_sequence PL/SQL package to retrieve a new poid id
       * value from the POID_IDS2 sequence.  By default, the returned value is
       * mangled per standard Infranet processing.<p>
       *
       * This function could be extended in the near future to support
       * SQL Server or other RDBMS.<p>
       *
       * @param newPoidId This is the returned new poid id value if successful.
       * @param mangle The client can request for the returned poid id to not be
       * mangled (have its last 12 bits reversed).  This should only be set to 
       * DO_NOT_MANGLE if the caller will be performing the mangling themselves (e.g.
       * for performance reasons or backwards-compatibility).
       *
       * @return True if the pin_sequence.get_new_poid_id stored procedure
       * returns a valid poid id, else False.
       */
      bool getNewPoidId(BAS::Identifier::IdentifierId& newPoidId,
			pin_partition_mode_t& partitionMode,
			BAS::String className = "",
                        const enum GetNewPoidIdMangleType mangle = MANGLE);

      /** Actual mehotd to acquire a new, contiguous range of poid id values.
       * Currently only support for Oracle Infranet databases, this method
       * accesses the pin_sequence PL/SQL package to retrieve a new
       * contiguous range of poid ids.<p>
       *
       * This function could be extended in the near future to support
       * SQL Server or other RDBMS.<p>
       *
       * Note that the returned poid ids are not mangled.  If the caller intends
       * to mangle each poid id himself, he can optionally request for the range to
       * not be padded - thereby using 8k less poid ids from the sequence per function
       * call.  (For example, dm_timos performs its own mangling and therefore can
       * help to preserve the poid ids by passing in a DO_NOT_PAD_RANGE argument;
       * IREL does not mangle the poid ids it retrieves and therefore must pad
       * the range.)
       * 
       * @param quantity The number of poid ids desired.
       * @param firstNewPoidId The lowest poid id in the allocated range will be
       * returned using this reference.
       * @param lastNewPoidId The highest poid id in the allocated range will be
       * returned using this reference.
       * @param incrementBy This returned value needs to be used to determine the
       * valid poid ids between the first and last poid ids in the range retrieved.
       * It is illegal to use values in the range which do not comply with this
       * increment.  (For example, in a non-multi-db Infranet environment, the
       * increment_by value will (almost certainly) be '1'.  This means that each
       * value in the retrieved range can (and should) be used by the caller.  In a
       * multi-db environment with 4 databases, this value will (almost certainly) be
       * '4'.  This means that starting with the first poid id you must increment
       * by 4 to get the next poid id, and so on.)
       * @param partitionMode Partition Mode for the class name passed in the next
       * argument is returned in this reference.
       * @param className name of the class for which we are requesting the poids.
       * @param padRange PAD_RANGE will add a 4k buffer to the beginning and end of the
       * retrieved range to prevent collision with exsting or future poid ids.  This
       * supports a caller who does not want to mangle the poid ids, and simply use
       * them as they are returned.  A caller who will mangle the poid ids before
       * inserting them into the database can optionally not have the range padded
       * simply to omit potential poid id waste.  If you don't know or understand this,
       * just use the default.
       *
       * @return True if the pin_sequence.get_new_poid_id_range stored procedure
       * returns a valid first and last poid id and increment by, else False.
       */
      bool getNewPoidIdRange(const size_t quantity,
                             BAS::Identifier::IdentifierId& firstNewPoidId,
                             BAS::Identifier::IdentifierId& lastNewPoidId,
                             size_t& incrementBy, pin_partition_mode_t& partitionMode,
			     BAS::String className = "",
                             const enum GetNewPoidIdRangePadType padRange = PAD_RANGE);
};

//------------------------------------------------------------------------------
// Returns the number of entries in the connection pool
//------------------------------------------------------------------------------

// virtual
inline size_t
DatabasePlugIn::connections()
{
  RWLockGuard<RWMutexLock> dbGuard(databaseLockerM);

  return databaseM.totalConnections();
}

//------------------------------------------------------------------------------
// Returns a new database object
//------------------------------------------------------------------------------

// virtual
inline RWDBDatabase
DatabasePlugIn::database(const BAS::String& userName,
                             const BAS::String& passWord, 
                             const BAS::String& databaseName,
                             const BAS::String& serverName,
                             const BAS::String& accessLib,
                             const size_t connections,
                             const bool toUpperCase)
{
  return initDatabase(userName, passWord,
                      databaseName, serverName,
                      accessLib, connections, toUpperCase);
}

//------------------------------------------------------------------------------
// Returns the database version string
//------------------------------------------------------------------------------

// virtual
inline BAS::String
DatabasePlugIn::dbVersion()
{
  return dbVersionM;
}

//------------------------------------------------------------------------------
// Returns the state of the ANSI-SQL compliance of the AccessLib.
//------------------------------------------------------------------------------

// virtual
inline bool
DatabasePlugIn::ansiSql() const
{
  return ansiSqlM;
}
}
#endif // DATABASEPLUGIN_HPP

