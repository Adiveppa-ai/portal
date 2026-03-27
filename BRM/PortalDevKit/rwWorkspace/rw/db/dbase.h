#ifndef __RWDB_DBASE_H__
#define __RWDB_DBASE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbase.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
 * 
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software, Inc.
 * pursuant to a written license agreement and may be used, copied, transmitted,
 * and stored only in accordance with the terms of such license agreement and
 * with the inclusion of the above copyright notice.  This computer software or
 * any other copies thereof may not be provided or otherwise made available to
 * any other person.
 * 
 * U.S. Government Restricted Rights.  This computer software: (a) was
 * developed at private expense and is in all respects the proprietary
 * information of Rogue Wave Software, Inc.; (b) was not developed with
 * government funds; (c) is a trade secret of Rogue Wave Software, Inc. for all
 * purposes of the Freedom of Information Act; and (d) is a commercial item and
 * thus, pursuant to Section 12.212 of the Federal Acquisition Regulations (FAR)
 * and DFAR Supplement Section 227.7202, Government's use, duplication or
 * disclosure of the computer software is subject to the restrictions set forth
 * by Rogue Wave Software, Inc.
 *
 **************************************************************************/

#include    <rw/db/column.h>
#include    <rw/db/connect.h>
#include    <rw/db/cursor.h>
#include    <rw/db/dbdatevec.h>
#include    <rw/db/defs.h>
#include    <rw/db/envhandl.h>
#include    <rw/db/property.h>
#include    <rw/db/status.h>

class RWDBCacheManager;

//  This macro is used in preference to a static const member, owing
//  to difficulties some compilers have with static initialization
//  in shared libraries and DLL's. It is used as a default argument
//  for RWDBDatabase::dbTables
/**
 * The default value for the \c type argument to dbTables().
 * \relates RWDBDatabase
 */
#define     rwdbAllTypes    SystemTable | UserTable | View | Synonym

/**
 * \ingroup db_common_group
 * \class RWDBDatabase
 *
 * \brief
 * Manages connections with database servers.
 *
 * RWDBDatabase manages connections with database servers. A database object
 * represents a server, a user on that server, and a database opened for
 * that user. Database objects are produced by the RWDBManager. Class
 * RWDBDatabase provides an interface for obtaining database-specific
 * objects and data definition language (DDL) concepts.
 *
 * RWDBDatabase is designed around the Interface/Implementation paradigm. An
 * RWDBDatabase instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBDatabase
 * implementation is a base class from which a family of database-specific
 * implementations is derived.
 *
 * Every valid RWDBDatabase implementation has a database type. For example,
 * the database type might be Sybase or Oracle. Applications request
 * RWDBDatabase objects of a particular type by specifying the type to the
 * RWDBManager; once a valid RWDBDatabase instance is obtained, its
 * implementation type is transparent to the application. Objects produced
 * by an RWDBDatabase instance automatically have the same implementation
 * type as the producer. For example, a Sybase type RWDBDatabase
 * automatically produces Sybase type RWDBTable objects.
 *
 * \synopsis
 * #include <rw/db/dbase.h>
 * #include <rw/db/dbmgr.h>
 *
 * RWDBDatabase dBase =
 *   RWDBManager::database("accessLib", "Servername",
 *                         "Username", "Password",
 *                         "DatabaseName");
 * \endsynopsis
 *
 * <h4>DB XA Module</h4>
 * In the DB Interface Module, database objects are produced by calling
 * RWDBManager::database() and defining the \c propertyString parameter with
 * key \c XA=xaParameter. Class RWDBDatabase provides an interface for
 * obtaining XA-enabled database-specific objects. For database-specific
 * values of \c xaParameter, see the DB XA Module User's Guide.
 *
 * \note
 * In an XA environment, use of DDL calls may result in a server error. DDL
 * calls can be used before XA connectivity is established.
 *
 * In the XA environment, you would create an RWDBDatabase instance like
 * this:
 *
 * \code
 * RWDBDatabase dBase =
 *   RWDBManager::database("accessLib", "","","","","XA=xaParameter");
 * \endcode
 */
class RWDB_GLOBAL RWDBDatabase
{
public:

    /**
     * These enumeration values are used in dbTables() to make up the type
     * argument.
     */
    enum {

        /**
         * User table
         */
        UserTable = 1,

        /**
         * System table
         */
        SystemTable = 2,

        /**
         * Views
         */
        View = 4,

        /**
         * Synonyms
         */
        Synonym = 8
    };

    /**
     * These enumeration values are used in dbTables() and
     * dbStoredProcedures() calls to indicate whether or not the case of the
     * search parameters should be normalized for the database.
     */
    enum AdjustCaseType {

        /**
         * Exact value; search parameters are not normalized.
         */
        Exact = 0,

        /**
         * Normalized value; search parameters are converted to the default
         * case of the database.
         */
        Normalize = 1
    };

    // Constructors, destructor, operators

    /**
     * Default constructor that creates a database with a status of
     * RWDBStatus::notInitialized. This constructor is provided for
     * convenience; usable RWDBDatabase objects must be obtained from the
     * RWDBManager.
     */
    RWDBDatabase();

    /**
     * Copy constructor. The object created shares an implementation with
     * \a dbase.
     */
    RWDBDatabase(const RWDBDatabase& dbase);

    // internal
    RWDBDatabase(RWDBDatabaseImp*  imp);

    virtual ~RWDBDatabase();

    /**
     * Assignment operator. Self shares an implementation with \a dbase.
     * Returns a reference to self.
     */
    RWDBDatabase&      operator=(const RWDBDatabase& dbase);

    /**
     * Returns \c true if self and \a dbase share the same implementation,
     * otherwise \c false.
     */
    bool               operator==(const RWDBDatabase& dbase) const;

    /**
     * Returns \c true if self and \a dbase do not share the same
     * implementation, otherwise \c false.
     */
    bool               operator!=(const RWDBDatabase& dbase) const;

    // Accessors

    /**
     * Returns the total number of connections an application is using or
     * has retained in the connection pool.
     *
     * \sa
     * defaultConnections().
     */
    size_t             totalConnections() const;

    /**
     * Returns the number of default connections retained in self's
     * connection pool. Initially, the number of default connections is set
     * to \c 1. Each database maintains a pool of connections from which all
     * requests for explicit and implicit connections are satisfied.
     * Optimizing the number of default connections can significantly boost
     * performance when using implicit connections.
     *
     * \sa
     * totalConnections().
     *
     * <b>DB XA Module:</b> The number of default connections is always
     * \c 1, except with the DB Access Module for Sybase, where the
     * connection pool is disabled and this method always returns \c 0.
     */
    size_t             defaultConnections() const;

    /**
     * Produces an RWDBConnection that provides a connection to self. On
     * return, the connection is either open and ready for use, or
     * RWDBConnection::isValid() of the produced RWDBConnection object
     * returns \c false.
     *
     * <b>DB XA Module:</b> With the exception of Sybase, this method
     * produces a RWDBStatus::notSupported error if used to create more than
     * one connection.
     */
    RWDBConnection     connection(
        RWDBConnection::ConnectionType type =
            RWDBConnection::Synchronous) const;

    /**
     * Produces an RWDBConnection that provides a connection to self. On
     * return, the connection is either open and ready for use, or
     * RWDBConnection::isValid() of the produced RWDBConnection object
     * returns \c false. The argument \a conncb provides an instance of the
     * RWDBConnCallback to be associated with the produced RWDBConnection
     * object. The connection produced is not fetched from the connection
     * pool nor is it returned to the connection pool.
     *
     * <b>DB XA Module:</b> With the exception of Sybase, this method
     * produces a RWDBStatus::notSupported error if used to create more than
     * one connection.
     */
    RWDBConnection     connection(
        const RWDBConnCallback& conncb,
        RWDBConnection::ConnectionType type =
            RWDBConnection::Synchronous) const;

    /**
     * Returns a reference to self's RWDBPhraseBook.
     */
    const RWDBPhraseBook& phraseBook() const;

    /**
     * Returns a reference to self's RWDBTracer. The result can be used to
     * control trace output from this RWDBDatabase. See RWDBTracer for an
     * explanation of tracing capabilities.
     */
    RWDBTracer&        tracer();

    /**
     * Returns the current value of self's case comparison setting. If it is
     * set to RWCString::exact, objects produced by self use case sensitive
     * search when looking for objects by name; if it is set to
     * RWCString::ignoreCase, objects use case-insensitive search. The
     * default for any particular implementation is set to mirror the
     * behavior of the underlying database. RWDBTable uses the case
     * comparison setting when accessing columns by name.
     */
    RWCString::caseCompare caseCompare() const;

    /**
     * Returns the user name passed in when constructing self. See
     * RWDBManager for more information.
     *
     * <b>DB XA Module:</b> Returns an empty string.
     */
    RWCString          userName() const;

    /**
     * Returns the password of the user passed in when constructing self.
     * See RWDBManager for more information.
     *
     * <b>DB XA Module:</b> Returns an empty string.
     */
    RWCString          passWord() const;

    /**
     * Returns the name of the database used when constructing self. See
     * RWDBManager for more information.
     *
     * <b>DB XA Module:</b> Returns an empty string.
     */
    RWCString          dbName() const;

    /**
     * Returns the name of the server used when constructing self. See
     * RWDBManager for more information.
     *
     * <b>DB XA Module:</b> Returns an empty string.
     */
    RWCString          serverName() const;

    /**
     * Returns a mnemonic based on the Access Module you are using. This is
     * the same as the string you use for the \c accessLib parameter of
     * RWDBManager::database() for static libraries, as described in your DB
     * Access Module guide. Specifically, it is \e not the same as the
     * \c accessLib parameter for dynamic libraries.
     */
    RWCString          serverType() const;

    RWDBProperties     properties() const;

    /**
     * Returns a string that identifies the version number of the DB
     * Interface Module and the DB Access Module being used.
     */
    RWCString          version() const;

    // If true, "" == NULL. If false, "" != NULL.
    // This will not affect Oracle as Oracle always treats empty strings as null
    /**
     * Retrieves the setting of this flag for this instance of RWDBDatabase.
     * See RWDBManager::emptyStringIsNull(bool) for details.
     */
    bool               emptyStringIsNull() const;

    /**
     * Accessor function that returns self's \c verboseAsString setting.
     *
     * The value of this member affects the SQL returned by the asString()
     * methods of the RWDBInserter, RWDBUpdater, RWDBDeleter, RWDBSelector,
     * and RWDBCompoundSelector instances produced by this RWDBDatabase.
     *
     * - If the \c verboseAsString setting is set to \c false, the
     * asString() methods of the above classes return the SQL as sent to the
     * database for execution, meaning that it may include placeholders.
     *
     * - If the \c verboseAsString setting is set to \c true, the asString()
     * methods of the above classes return the SQL with the placeholders
     * replaced by their bound values.
     */
    bool               verboseAsString() const;

    /**
     * Returns a pointer to the currently installed cache manager. If a
     * cache manager is not installed, returns \c NULL.
     */
    RWDBCacheManager*  cacheManager() const;

    /**
     * Sets the cache manager to \a mgr. Returns a pointer to the previous
     * cache manager. Pass \c NULL to unset the cache manager.
     *
     * \note
     * It is the application's responsibility to ensure that \a mgr has a
     * lifetime greater than self or any object produced from self.
     */
    RWDBCacheManager*  cacheManager(RWDBCacheManager* mgr);

    /**
     * Returns a reference to the time zone set on self. If the time zone is
     * not set, returns RWZone::local().
     *
     * \sa
     * timeZone(const RWZone*) for setting the time zone.
     *
     * \sa
     * RWDBConnection::timeZone(const RWZone*) for information on how the
     * time zone setting is used.
     *
     * \note
     * This method does not fetch the time zone set on the database server
     * or the database client.
     */
    const RWZone&      timeZone() const;

    /**
     * Returns the current status of self.
     */
    RWDBStatus         status() const;

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise
     * \c false.
     */
    bool               isValid() const;

    /**
     * Returns \c true if the object is in ready state, indicating that
     * accessing the object will not block. Accessing a nonready object may
     * potentially block.
     */
    bool               isReady() const;

    /**
     * Returns the currently-installed error handler, if any.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Installs \a handler as the error handler for self. The supplied
     * \a handler is called whenever the status of self changes to anything
     * except RWDBStatus::ok. By default, the error handler of self is
     * inherited from the RWDBManager; this method overrides the default.
     */
    void               setErrorHandler(RWDBStatus::ErrorHandler handler);

    // multithreading support

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void               acquire(void) const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void               release(void) const;

    // Mutators

    /**
     * Updates self's password to \a pwd. Database connections obtained
     * after this call will use the new password. Returns the old password.
     */
    RWCString          passWord(const RWCString& pwd);

    /**
     * Sets the number of default connections retained in self's connection
     * pool to \a size. Each database maintains a pool of connections from
     * which all requests for explicit and implicit connections are
     * satisfied. This method allows applications to change the number of
     * default connections to retain as they are returned to the connection
     * pool.
     *
     * Increasing or decreasing the number of default connections does not
     * immediately enlarge or shrink the connection pool, but affects only
     * the number of default connections. The total size of the connection
     * pool changes as connections are created and destroyed, and the
     * requested number of default connections are retained.
     *
     * This method returns the previous number of default connections
     * retained. Initially, the number of default connections is set to
     * \c 1. Optimizing the number of default connections can significantly
     * boost performance when using implicit connections. Also see
     * totalConnections().
     *
     * <b>DB XA Module:</b> The number of default connections is restricted
     * to \c 1, so using this method to set a higher number does nothing.
     * The exception is the DB Access Module for Sybase, where the
     * connection pool is disabled so use of this method results in an
     * RWDBStatus::notSupported error.
     */
    size_t             defaultConnections(size_t size);

    /**
     * Sets self's case comparison setting to \a cmp, and returns its
     * previous value.
     */
    RWCString::caseCompare caseCompare(RWCString::caseCompare cmp);

    /**
     * Sets self's \c verboseAsString setting to \a verbose and returns its
     * previous value. The default value is \c false.
     *
     * The value of this member affects the SQL returned by the asString()
     * methods of the RWDBInserter, RWDBUpdater, RWDBDeleter, RWDBSelector,
     * and RWDBCompoundSelector instances produced by this RWDBDatabase.
     *
     * - If the \c verboseAsString setting is set to \c false, the
     * asString() methods of the above classes return the SQL as sent to the
     * database for execution, meaning that it may include placeholders.
     *
     * - If the \c verboseAsString setting is set to \c true, the asString()
     * methods of the above classes will return the SQL with the
     * placeholders replaced by their bound values.
     *
     * \note
     * Setting the \c verboseAsString setting to \c true enables the
     * asString() methods to return SQL in which placeholders are replaced
     * by their bound values, but it does \e not affect the SQL passed to
     * the database for execution.
     */
    bool               verboseAsString(bool verbose);

    /**
     * Sets self's time zone to \a zone. All explicit and implicit
     * RWDBConnection objects produced from self inherit the time zone
     * setting at the time they are produced.
     *
     * \param zone
     * The time zone to be set on self. Pass \c NULL to unset the time zone
     * setting.
     *
     * \return
     * The previous time zone set on self. Returns \c NULL when the time
     * zone was not set.
     *
     * \sa
     * RWDBConnection::timeZone(const RWZone*) for information on how the
     * time zone setting is used.
     *
     * \note
     * Self retains a reference to \a zone. It is the application's
     * responsibility to ensure that \a zone has a lifetime greater than
     * self or any object produced from self.
     *
     * \note
     * This method does not set the time zone on the database server or the
     * database client.
     */
    const RWZone*      timeZone(const RWZone* zone);

    // Producers

    /**
     * Produces an RWDBTable with the given \a name. The returned object is
     * an instance of a database table, which applications are likely to
     * need most often. See RWDBTable for an explanation of the different
     * kinds of RWDBTable objects.
     *
     * Each RWDBTable that is produced has a unique alias. When producing a
     * \c table that will be used for self-joins, this may or may not be
     * desirable. Exact copies of a \c table and associated tags should be
     * produced by RWDBTable::operator=() or copy constructor.
     */
    RWDBTable          table(const RWCString& name) const;

    /**
     * Produces an RWDBTable with the given \a name. The returned object is
     * an instance of a database table. The supplied \a schema is used as
     * the table's schema. If \a isView is \c true, it is assumed that the
     * table represents a database view. If a cache manager is present,
     * \a schema and \a isView are stored in the cache, replacing any
     * existing schema and isView information stored in the cache. See
     * RWDBTable for an explanation of the different kinds of RWDBTable
     * objects.
     *
     * Each RWDBTable that is produced has a unique alias. When producing a
     * \c table that will be used for self-joins, this may or may not be
     * desirable. Exact copies of a \c table and associated tags should be
     * produced by RWDBTable::operator=() or copy constructor. It is assumed
     * that the contents of the supplied \a schema are correct for the named
     * RWDBTable. If not, the program may produce unexpected results.
     *
     * \note
     * The schema \a schema passed to construct an RWDBTable object is
     * assumed to be complete with pertinent metadata information.
     */
    RWDBTable          table(const RWCString& name, const RWDBSchema& schema,
                             bool isView = false) const;
    /**
     * Produces an RWDBTable representing the SQL query encapsulated by
     * \a selector. The returned object is an instance of a derived table.
     * See RWDBTable for an explanation of the different kinds of RWDBTable
     * objects. The returned RWDBTable has a unique alias.
     */
    RWDBTable          table(const RWDBSelectorBase& selector) const;

    /**
     * Produces an RWDBMemTable with the given \a name. A default connection
     * is used to query the database for a table matching \a name. If one is
     * found, the RWDBMemTable is populated with rows of data from the
     * database. If \a capacity is zero, all rows are fetched into the
     * RWDBMemTable, otherwise a maximum of \a capacity rows is fetched.
     */
    RWDBMemTable       memTable(const RWCString& name,
                                size_t capacity = 0) const;

    /**
     * Produces an RWDBMemTable with the given \a name. The given
     * \a connection is used to query the database for a table matching
     * \a name. If one is found, the RWDBMemTable is populated with rows of
     * data from the database. If \a capacity is zero, all rows are fetched
     * into the RWDBMemTable. Otherwise a maximum of \a capacity rows is
     * fetched.
     */
    RWDBMemTable       memTable(const RWCString& name,
                                const RWDBConnection& connection,
                                size_t capacity = 0) const;

    /**
     * Produces an empty RWDBSelector appropriate for this database. The
     * result can be used to build an encapsulated SQL \c SELECT statement.
     * See RWDBSelector for details.
     */
    RWDBSelector       selector() const;

    /**
     * Produces an RWDBSelector whose \c criterion, or \c WHERE clause, is
     * initialized with the given \a criterion. The result can be used to
     * build an encapsulated SQL \c SELECT statement. See RWDBSelector for
     * details. Note that a subsequent call to RWDBSelector::where() on the
     * produced RWDBSelector object replaces \c criterion, rather than adds
     * to it.
     */
    RWDBSelector       selector(const RWDBCriterion& criterion) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * <tt>INSERT INTO \a table VALUES ...</tt>
     *
     * where the actual values must be added to the inserter later. When
     * \a cache is passed in as \c 0, it is interpreted as \c 1.
     *
     * \note
     * When using Access Modules that support an inserter cache, increasing
     * the \a cache value can greatly improve performance. However, setting
     * the \a cache parameter greater than one may adversely affect
     * transactions. Check your Access Module documentation for limitations
     * and warnings.
     */
    RWDBInserter       inserter(const RWDBTable& table, size_t cache = 1) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * <tt>INSERT INTO \a table <em>select-statement</em></tt>
     *
     * where the <em>select-statement</em> is encapsulated by the given
     * \a selector.
     */
    RWDBInserter       inserter(const RWDBTable& table,
                                const RWDBSelector& selector) const;

    /**
     * Produces an RWDBInserter which encapsulates the SQL statement:
     *
     * <tt>INSERT INTO \a table <em>select-statement</em></tt>
     *
     * where the <em>select-statement</em> is encapsulated by the given
     * \a selector.
     */
    RWDBInserter       inserter(const RWDBTable& table,
                                const RWDBCompoundSelector& selector) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * <tt>INSERT INTO \a table(col1, ..., coln) VALUES(val1, ..., valn)</tt>
     *
     * The names of the column entries in schema are used to build up the
     * column-name list. When \a cache is passed in as \c 0, it is
     * interpreted as \c 1.
     *
     * \note
     * When using Access Modules that support an inserter cache, increasing
     * the \a cache value can greatly improve performance. However, setting
     * the \a cache parameter greater than one may adversely affect
     * transactions. Check your Access Module documentation for limitations
     * and warnings.
     */
    RWDBInserter       inserter(const RWDBTable& table,
                                const RWDBSchema& columnList, size_t cache = 1) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * <tt>INSERT INTO \a table(col1, ..., coln) <em>select-statement</em></tt>
     *
     * The names of the column entries in schema are used to build up the
     * column-name list. The <em>select-statement</em> is encapsulated by
     * the given \a selector.
     */
    RWDBInserter       inserter(const RWDBTable& table,
                                const RWDBSelector& selector,
                                const RWDBSchema& columnList) const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 6, use class
     * \ref RWDBTBuffer "RWDBTBuffer<RWDateTime>" instead of RWDBDateVector.
     *
     * Produces an RWDBDateVector of size \a n with RWDBVendorDate objects
     * appropriate for use with self's underlying implementation.
     */
    RW_DEPRECATE_FUNC("Use RWDBTBuffer<RWDateTime> instead")
    RWDBDateVector     dateVector(size_t n) const;
#endif

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * <tt>INSERT INTO \a table(col1, ..., coln) <em>select-statement</em></tt>
     *
     * The names of the column entries in schema are used to build up the
     * column-name list. The <em>select-statement</em> is encapsulated by
     * the given \a selector.
     */
    RWDBInserter       inserter(const RWDBTable& table,
                                const RWDBCompoundSelector& selector,
                                const RWDBSchema& columnList) const;

    /**
     * Produces an RWDBDeleter which encapsulates the SQL statement:
     *
     * <tt>DELETE FROM \a table</tt>
     *
     * The deleter can be used to delete all the data from the database
     * table represented by \a table, or can be augmented with an
     * RWDBCriterion representing an SQL \c WHERE clause in order to delete
     * data selectively.
     */
    RWDBDeleter        deleter(const RWDBTable& table) const;

    /**
     * Produces an RWDBDeleter that encapsulates the SQL statement:
     *
     * <tt>DELETE FROM \a table WHERE \a criterion</tt>
     *
     * The deleter can be used to delete rows that meet the given
     * \a criterion representing an SQL \c WHERE clause, from the database
     * table represented by \a table. Note that a subsequent call to
     * RWDBDeleter::where() on the produced RWDBDeleter object replaces the
     * \a criterion, rather than adding to it.
     */
    RWDBDeleter        deleter(const RWDBTable& table,
                               const RWDBCriterion& criterion) const;

    /**
     * Produces an RWDBUpdater. The result can be used to create an
     * encapsulated SQL \c UPDATE statement to update rows in the database
     * table represented by \a table.
     */
    RWDBUpdater        updater(const RWDBTable& table) const;

    /**
     * Produces an RWDBUpdater whose \c criterion (\c WHERE clause) is
     * initialized with the given \a criterion. The result can be used to
     * create an encapsulated SQL \c UPDATE statement to update rows in the
     * database table represented by \a table. Note that a subsequent call
     * to RWDBUpdater::where() on the produced RWDBUpdater object replaces
     * \a criterion, rather than adds to it.
     */
    RWDBUpdater        updater(const RWDBTable& table,
                               const RWDBCriterion& criterion) const;

    // cursor variants w/o schema

    /**
     * Produces an RWDBCursor for execution of the given \a sql. The
     * \a cursorType may be either RWDBCursor::Sequential or
     * RWDBCursor::Scrolling. The \a cursorAccess may be either
     * RWDBCursor::Read or RWDBCursor::Write. The cursor is created on the
     * \a connection provided. The DB Interface Module does not check the
     * contents of \a sql for validity. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBCursor         cursor(const RWCString& sql,
                              const RWDBConnection& connection,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the given \a sql. The
     * \a cursorType may be either RWDBCursor::Sequential or
     * RWDBCursor::Scrolling. The \a cursorAccess may be either
     * RWDBCursor::Read or RWDBCursor::Write. The cursor is created on a
     * default connection. The DB Interface Module does not check the
     * contents of \a sql for validity.
     */
    RWDBCursor         cursor(const RWCString& sql,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType can be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * can be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on the supplied \a connection. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBCursor         cursor(const RWDBSelector& select,
                              const RWDBConnection& connection,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType can be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * can be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on a default connection.
     */
    RWDBCursor         cursor(const RWDBSelector& select,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType may be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * may be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on the supplied \a connection. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBCursor         cursor(const RWDBCompoundSelector& select,
                              const RWDBConnection& connection,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType can be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * can be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on a default connection.
     */
    RWDBCursor         cursor(const RWDBCompoundSelector& select,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;


    // cursor variants w schema

    /**
     * Produces an RWDBCursor for execution of the given SQL \c SELECT
     * statement. The \a cursorType may be RWDBCursor::Sequential, or
     * RWDBCursor::Scrolling. The \a cursorAccess may be either
     * RWDBCursor::Read or RWDBCursor::Write. The cursor is created on the
     * supplied \a connection. The argument \a updateCols is used in
     * building a clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBCursor         cursor(const RWCString& select,
                              const RWDBSchema& updateCols,
                              const RWDBConnection& connection,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the given SQL \c SELECT
     * statement. The \a cursorType may be either RWDBCursor::Sequential or
     * RWDBCursor::Scrolling. The \a cursorAccess may be either
     * RWDBCursor::Read or RWDBCursor::Write. The cursor is created on the
     * default connection. The argument \a updateCols is used in building a
     * clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form.
     */
    RWDBCursor         cursor(const RWCString& select,
                              const RWDBSchema& updateCols,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType can be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * can be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on the supplied \a connection. The argument \a updateCols is
     * used in building a clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBCursor         cursor(const RWDBSelector& select,
                              const RWDBSchema& updateCols,
                              const RWDBConnection& connection,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType can be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * can be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on a default connection. The argument \a updateCols is used
     * in building a clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form.
     */
    RWDBCursor         cursor(const RWDBSelector& select,
                              const RWDBSchema& updateCols,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType can be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * can be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on the supplied \a connection. The argument \a updateCols is
     * used in building a clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBCursor         cursor(const RWDBCompoundSelector& select,
                              const RWDBSchema& updateCols,
                              const RWDBConnection& connection,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL \c SELECT statement
     * encapsulated in \a select. The \a cursorType can be either
     * RWDBCursor::Sequential or RWDBCursor::Scrolling. The \a cursorAccess
     * can be either RWDBCursor::Read or RWDBCursor::Write. The cursor is
     * created on a default connection. The argument \a updateCols is used
     * in building a clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form.
     */
    RWDBCursor         cursor(const RWDBCompoundSelector& select,
                              const RWDBSchema& updateCols,
                              RWDBCursor::CursorType cursorType =
                                  RWDBCursor::Sequential,
                              RWDBCursor::CursorAccess cursorAccess =
                                  RWDBCursor::Read) const;

    /**
     * Produces an RWDBStoredProc. The result represents the stored
     * procedure with the given \a name in the database. If a cache manager
     * is present, this method checks the cache for a schema. If it isn't
     * found or a cache manager isn't present, uses a default connection to
     * retrieve information about the stored procedure's parameters. If a
     * cache manager is present, the stored procedure metadata fetched from
     * the database is stored in the cache.
     */
    RWDBStoredProc     storedProc(const RWCString& name) const;

    /**
     * Produces an RWDBStoredProc. The result represents the stored
     * procedure with the given \a name in the database. If a cache manager
     * is present, this method checks the cache for a schema. If it isn't
     * found or a cache manager isn't present, uses the supplied
     * \a connection to retrieve information about the stored procedure's
     * parameters. If a cache manager is present, the stored procedure
     * metadata fetched from the database is stored in the cache.
     */
    RWDBStoredProc     storedProc(const RWCString& name,
                                  const RWDBConnection& connection) const;

    /**
     * Produces an RWDBStoredProc. The result represents the stored
     * procedure with the given \a name in the database. Uses the supplied
     * RWDBSchema to determine the parameters in the stored procedure, the
     * supplied column to determine the return value, if any, and the
     * supplied RWCString to determine the text. If \a text is an empty
     * string, the next call to RWDBStoredProc::text() will attempt to fetch
     * the text. This means that the call does not have to query the
     * database for the parameters needed or the return value, so the
     * \a connection is not used. If a cache manager is present, the schema
     * and column are stored in the cache, replacing any existing metadata
     * present in the cache. If the text is not empty, it too is stored in
     * the cache.
     *
     * \note
     * The return value definition \a col must have a valid
     * RWDBValue::type() and any appropriate RWDBColumn::storageLength(),
     * RWDBColumn::scale() and RWDBColumn::precision() information.
     *
     * \note
     * The \a connection parameter is currently not used.
     */
    RWDBStoredProc     storedProc(const RWCString& name,
                                  const RWDBConnection& connection,
                                  const RWDBSchema& sch,
                                  const RWDBColumn& col = RWDBColumn(),
                                  const RWCString& text = RWCString()) const;

    /**
     * Produces an RWDBStoredProc. The result represents the stored
     * procedure with the given \a name in the database. Uses the supplied
     * RWDBSchema to determine the parameters in the stored procedure, the
     * supplied column to determine the return value, if any, and the
     * supplied RWCString to determine the text. If \a text is an empty
     * string, the next call to RWDBStoredProc::text() will attempt to fetch
     * the text. This means that the call does not have to query the
     * database for the parameters needed or the return value. If a cache
     * manager is present, the schema and column are stored in the cache,
     * replacing any existing metadata present in the cache. If the text is
     * not empty, it too is stored in the cache.
     *
     * \note
     * The return value definition \a col must have a valid
     * RWDBValue::type() and any appropriate RWDBColumn::storageLength(),
     * RWDBColumn::scale() and RWDBColumn::precision() information.
     */
    RWDBStoredProc     storedProc(const RWCString& name,
                                  const RWDBSchema& sch,
                                  const RWDBColumn& col = RWDBColumn(),
                                  const RWCString& text = RWCString()) const;

    // Direct DDL Support

    /**
     * Uses a default connection to create a new table in the database.
     * Creates the table with the same name and schema as the given
     * \a table. The new table has no data in it. You can check the return
     * value's \ref RWDBStatus::isValid() "isValid()" method to determine
     * whether the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createTable(const RWDBTable& table) const;

    /**
     * Uses the supplied \a connection to create a new table in the
     * database. Creates the table with the same name and schema as the
     * given \a table. The new table has no data in it. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createTable(const RWDBTable& table,
                                   const RWDBConnection& connection) const;

    /**
     * Uses a default connection to create a new table in the database.
     * Creates the table with the given \a name and \a schema. The new table
     * has no data in it. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createTable(const RWCString& name,
                                   const RWDBSchema& schema) const;

    /**
     * Uses the supplied \a connection to create a new table in the
     * database. Creates the table with the given \a name and \a schema. The
     * new table has no data in it. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createTable(const RWCString& name,
                                   const RWDBSchema& schema,
                                   const RWDBConnection& connection) const;

    /**
     * Uses a default connection to create \a viewName in the database. The
     * SQL \c SELECT statement encapsulated in \a select is used as the body
     * of the new view. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWDBSelectorBase& select) const;

    /**
     * Uses a default connection to create \a viewName in the database. The
     * SQL \c SELECT statement encapsulated in \a select is used as the body
     * of the new view. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. The resulting columns from the \c SELECT
     * statement are named according to the \a columnList provided.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWDBSchema& columnList,
                                  const RWDBSelectorBase& select) const;

    /**
     * Uses the supplied \a connection to create \a viewName in the
     * database. The SQL \c SELECT statement encapsulated in \a select is
     * used as the body of the new view. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWDBSelectorBase& select,
                                  const RWDBConnection& connection) const;

    /**
     * Uses the supplied \a connection to create \a viewName in the
     * database. The SQL \c SELECT statement encapsulated in \a select is
     * used as the body of the new view. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. The resulting columns from the \c SELECT
     * statement are named according to the \a columnList provided. This
     * function can behave asynchronously if executed using an asynchronous
     * connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWDBSchema& columnList,
                                  const RWDBSelectorBase& select,
                                  const RWDBConnection& connection) const;

    /**
     * Uses a default connection to create \a viewName in the database. The
     * supplied \a sql is used as the body of the new view. You can check
     * the return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWCString& sql) const;

    /**
     * Uses a default connection to create \a viewName in the database. The
     * supplied \a sql is used as the body of the new view. You can check
     * the return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded. The resulting columns from
     * the \c SELECT statement are named according to the \a columnList
     * provided.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWDBSchema& columnList,
                                  const RWCString& sql) const;

    /**
     * Uses the supplied \a connection to create \a viewName in the
     * database. The supplied \a sql is used as the body of the new view.
     * You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWCString& sql,
                                  const RWDBConnection& connection) const;

    /**
     * Uses the supplied \a connection to create \a viewName in the
     * database. The supplied \a sql is used as the body of the new view.
     * You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. The resulting columns from the \c SELECT
     * statement are named according to the \a columnList provided. This
     * function can behave asynchronously if executed using an asynchronous
     * connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createView(const RWCString& viewName,
                                  const RWDBSchema& columnList,
                                  const RWCString& sql,
                                  const RWDBConnection& connection) const;

    /**
     * Uses a default connection to create a stored procedure with the given
     * \a name in the database. The supplied \a sql is used as the body of
     * the new procedure. The new procedure takes no parameters. You can
     * check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createProcedure(const RWCString& name,
                                       const RWCString& sql) const;

    /**
     * Uses the supplied \a connection to create a stored procedure with the
     * given \a name in the database. The supplied \a sql is used as the
     * body of the new procedure. The new procedure takes no parameters. You
     * can check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether the operation succeeded. This function
     * can behave asynchronously if executed using an asynchronous
     * connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createProcedure(const RWCString& name,
                                       const RWCString& sql,
                                       const RWDBConnection& connection) const;

    /**
     * Uses a default connection to create a stored procedure with the given
     * \a name in the database. The supplied \a sql is used as the body of
     * the new procedure. The new procedure's parameters are specified by
     * \a params. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createProcedure(const RWCString& name,
                                       const RWCString& sql,
                                       const RWDBSchema& params) const;

    /**
     * Uses the supplied \a connection to create a stored procedure with the
     * given \a name in the database. The supplied \a sql is used as the
     * body of the new procedure. The new procedure's parameters are
     * specified by \a params. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createProcedure(const RWCString& name,
                                       const RWCString& sql,
                                       const RWDBSchema& params,
                                       const RWDBConnection& connection) const;

    /**
     * Uses a default connection to create a stored procedure in the
     * database. Also opens a connection to the database of \a proc. The new
     * procedure's name, parameter definitions, and body are copied from the
     * supplied \a proc. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createProcedure(const RWDBStoredProc& proc) const;

    /**
     * Uses the supplied \a connection to create a stored procedure in the
     * database. Also opens a connection to the database of \a proc. The new
     * procedure's name, parameter definitions and SQL body are copied from
     * the supplied \a proc. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         createProcedure(const RWDBStoredProc& proc,
                                       const RWDBConnection& connection) const;

    /**
     * Uses a default connection to drop \a viewName from the database. You
     * can check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether or not the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         dropView(const RWCString& viewName);

    /**
     * Uses the supplied \a connection to drop \a viewName from the
     * database. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether or
     * not the operation succeeded. This function can behave asynchronously
     * if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus         dropView(const RWCString& viewName,
                                const RWDBConnection& connection);
    //
    // Not all compilers support default values for "complicated"
    // arguments. These overloads mimic default values for CStrings.
    //

    /**
     * Like an RWDBTable, returns a list of tables stored in the database
     * encapsulated by self. The table contains three columns, \c name,
     * \c owner, and \c type, whose data types are
     * \ref RWDBValue::String "String", \ref RWDBValue::String "String", and
     * \ref RWDBValue::Int "Int", respectively.
     *
     * Each row in the returned table contains information about a single
     * database object. The search is restricted to tables of those types
     * that make up \a type. If the default argument is used, this method
     * returns all tables encapsulated by self.
     *
     * \param type
     * Consists of the bitwise <tt>OR</tt>ed combination of the enumerated
     * values #UserTable, #SystemTable, #View, and #Synonym.
     */
    RWDBTable          dbTables(int type = rwdbAllTypes) const;

    /**
     * Like an RWDBTable, returns a list of tables stored in the database
     * encapsulated by self. The table contains three columns, \c name,
     * \c owner, and \c type, whose data types are
     * \ref RWDBValue::String "String", \ref RWDBValue::String "String", and
     * \ref RWDBValue::Int "Int", respectively.
     *
     * Each row in the returned table contains information about a single
     * database object. The search is restricted to tables of those types
     * that make up \a type. If the default argument
     *
     * is used, this method returns all tables encapsulated by self.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param type
     * Consists of the bitwise <tt>OR</tt>ed combination of the enumerated
     * values #UserTable, #SystemTable, #View, and #Synonym.
     *
     * \param adjustCase
     * Specifies whether the search value \a name should be normalized.
     */
    RWDBTable          dbTables(const RWCString& name,
                                int type = rwdbAllTypes,
                                AdjustCaseType adjustCase = Normalize) const;

    /**
     * Like an RWDBTable, returns a list of tables stored in the database
     * encapsulated by self. The table contains three columns, \c name,
     * \c owner, and \c type, whose data types are
     * \ref RWDBValue::String "String", \ref RWDBValue::String "String", and
     * \ref RWDBValue::Int "Int", respectively.
     *
     * Each row in the returned table contains information about a single
     * database object. The search is restricted to tables of those types
     * that make up \a type. If the default argument is used, this method
     * returns all tables encapsulated by self.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param owner
     * Restricts the search to tables with matching owners, according to the
     * SQL \c LIKE operator. A blank \a owner places no restrictions on the
     * search.
     *
     * \param type
     * Consists of the bitwise <tt>OR</tt>ed combination of the enumerated
     * values #UserTable, #SystemTable, #View, and #Synonym.
     *
     * \param adjustCase
     * Specifies whether the search values \a name and \a owner should be
     * normalized.
     */
    RWDBTable          dbTables(const RWCString& name, const RWCString& owner,
                                int type = rwdbAllTypes,
                                AdjustCaseType adjustCase = Normalize) const;

    /**
     * Like an RWDBTable, returns a list of tables stored in the database
     * encapsulated by self. The table contains three columns, \c name,
     * \c owner, and \c type, whose data types are
     * \ref RWDBValue::String "String", \ref RWDBValue::String "String", and
     * \ref RWDBValue::Int "Int", respectively. Each row in the returned
     * table contains information about a single database object.
     *
     * The search is restricted to tables of those types that make up
     * \a type. If the default argument is used, this method returns all
     * tables encapsulated by self. The query is issued through the supplied
     * \a conn. This function can behave asynchronously if executed using an
     * asynchronous connection.
     *
     * \param conn
     * Database connection to be used for this query.
     *
     * \param type
     * Consists of the bitwise <tt>OR</tt>ed combination of the enumerated
     * values #UserTable, #SystemTable, #View, and #Synonym.
     */
    RWDBTable          dbTables(const RWDBConnection& conn,
                                int type = rwdbAllTypes) const;

    /**
     * Like an RWDBTable, returns a list of tables stored in the database
     * encapsulated by self. The table contains three columns, \c name,
     * \c owner, and \c type, whose data types are
     * \ref RWDBValue::String "String", \ref RWDBValue::String "String", and
     * \ref RWDBValue::Int "Int", respectively.
     *
     * Each row in the returned table contains information about a single
     * database object. The search is restricted to tables of those types
     * that make up \a type. If the default argument is used, this method
     * returns all tables encapsulated by self. The query is issued through
     * the supplied \a conn. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * \param conn
     * Database connection to be used for this query.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param type
     * Consists of the bitwise <tt>OR</tt>ed combination of the enumerated
     * values #UserTable, #SystemTable, #View, and #Synonym.
     *
     * \param adjustCase
     * Specifies whether the search value \a name should be normalized.
     */
    RWDBTable          dbTables(const RWDBConnection& conn,
                                const RWCString& name,
                                int type = rwdbAllTypes,
                                AdjustCaseType adjustCase = Normalize) const;

    /**
     * Like an RWDBTable, returns a list of tables stored in the database
     * encapsulated by self. The table contains three columns, \c name,
     * \c owner, and \c type, whose data types are
     * \ref RWDBValue::String "String", \ref RWDBValue::String "String", and
     * \ref RWDBValue::Int "Int", respectively.
     *
     * Each row in the returned table contains information about a single
     * database object. The search is restricted to tables of those types
     * that make up \a type. If the default argument is used, this method
     * returns all tables encapsulated by self. The query is issued through
     * the supplied \a conn. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * \param conn
     * Database connection to be used for this query.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param owner
     * Restricts the search to tables with matching owners, according to the
     * SQL \c LIKE operator. A blank \a owner places no restrictions on the
     * search.
     *
     * \param type
     * Consists of the bitwise <tt>OR</tt>ed combination of the enumerated
     * values #UserTable, #SystemTable, #View, and #Synonym.
     *
     * \param adjustCase
     * Specifies whether the search values \a name and \a owner should be
     * normalized.
     */
    RWDBTable          dbTables(const RWDBConnection& conn,
                                const RWCString& name, const RWCString& owner,
                                int type = rwdbAllTypes,
                                AdjustCaseType adjustCase = Normalize) const;

    /**
     * Returns, as an RWDBTable, a list of stored procedures available in
     * the database encapsulated by self. The table contains two columns,
     * \c name and \c owner, whose data type is
     * \ref RWDBValue::String "String". Each row in the returned table
     * contains information about a single database object.
     */
    RWDBTable          dbStoredProcedures() const;

    /**
     * Returns, as an RWDBTable, a list of stored procedures available in
     * the database encapsulated by self. The table contains two columns,
     * \c name and \c owner, whose data type is
     * \ref RWDBValue::String "String". Each row in the returned table
     * contains information about a single database object.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param adjustCase
     * Specifies whether the search value \a name should be normalized.
     */
    RWDBTable          dbStoredProcedures(const RWCString& name,
                                          AdjustCaseType adjustCase = Normalize) const;

    /**
     * Returns, as an RWDBTable, a list of stored procedures available in
     * the database encapsulated by self. The table contains two columns,
     * \c name and \c owner, whose data type is
     * \ref RWDBValue::String "String". Each row in the returned table
     * contains information about a single database object.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param owner
     * Restricts the search to tables with matching owners, according to the
     * SQL \c LIKE operator. A blank \a owner places no restrictions on the
     * search.
     *
     * \param adjustCase
     * Specifies whether the search values \a name and \a owner should be
     * normalized.
     */
    RWDBTable          dbStoredProcedures(const RWCString& name,
                                          const RWCString& owner,
                                          AdjustCaseType adjustCase = Normalize) const;

    /**
     * Returns, as an RWDBTable, a list of stored procedures available in
     * the database encapsulated by self. The table contains two columns,
     * \c name and \c owner, whose data type is
     * \ref RWDBValue::String "String". Each row in the returned table
     * contains information about a single database object. The query is
     * issued through the supplied \a conn. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * \param conn
     * Database connection to be used for this query.
     */
    RWDBTable          dbStoredProcedures(const RWDBConnection& conn) const;

    /**
     * Returns, as an RWDBTable, a list of stored procedures available in
     * the database encapsulated by self. The table contains two columns,
     * \c name and \c owner, whose data type is
     * \ref RWDBValue::String "String". Each row in the returned table
     * contains information about a single database object. The query is
     * issued through the supplied \a conn. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * \param conn
     * Database connection to be used for this query.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param adjustCase
     * Specifies whether the search value \a name should be normalized.
     */
    RWDBTable          dbStoredProcedures(const RWDBConnection& conn,
                                          const RWCString& name,
                                          AdjustCaseType adjustCase = Normalize) const;

    /**
     * Returns, as an RWDBTable, a list of stored procedures available in
     * the database encapsulated by self. The table contains two columns,
     * \c name and \c owner, whose data type is
     * \ref RWDBValue::String "String". Each row in the returned table
     * contains information about a single database object. The query is
     * issued through the supplied \a conn. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * \param conn
     * Database connection to be used for this query.
     *
     * \param name
     * Restricts the search to tables with matching names, according to the
     * SQL \c LIKE operator. A blank \a name places no restrictions on the
     * search.
     *
     * \param owner
     * Restricts the search to tables with matching owners, according to the
     * SQL \c LIKE operator. A blank \a owner places no restrictions on the
     * search.
     *
     * \param adjustCase
     * Specifies whether the search values \a name and \a owner should be
     * normalized.
     */
    RWDBTable          dbStoredProcedures(const RWDBConnection& conn,
                                          const RWCString& name,
                                          const RWCString& owner,
                                          AdjustCaseType adjustCase = Normalize) const;

    /**
     * Returns the handle to the environment. Through the environment
     * handle, the user can set environment-specific values. Should be used
     * before a connection is established. See RWDBEnvironmentHandle for
     * more information.
     */
    RWDBEnvironmentHandle* environmentHandle() const;

    // Connect to the server when producing this db object

    /**
     * Allows an application to specify whether the call to
     * RWDBManager::database() should result in a database that establishes
     * a physical connection to the server. By default, the DB Interface
     * Module establishes a default connection to the server when an
     * RWDBDatabase object is produced. To change this behavior, an
     * application calls RWDBDatabase::connect() with \a enable set to
     * \c false. In this case, a connection to the server is established
     * only when a statement is to be executed against the server, or when a
     * connection is explicitly created by the application.
     *
     * A side effect of disabling the initial connection is that the
     * RWDBDatabase is always valid. If the subsequent first connection attempt 
     * fails, the status of the RWDBDatabase object will remain unchanged and
     * the RWDBConnection should be inspected to determine the connection
     * status.
     *
     * This method is a static method and affects the creation of all
     * databases within an application. For related topics, see
     * RWDBEnvironmentHandle.
     *
     * <b>DB XA Module:</b> The default behavior is to obtain the XA
     * connection from the server. Alternatively, the connection is obtained
     * only when a statement is to be executed, or when a connection is
     * explicitly created by the application.
     */
    static void        connect(bool enable);

    /**
     * Accessor function that returns the connection policy set by the
     * \ref connect(bool) "mutator".
     */
    static bool        connect();

    static RWDBDatabase& uninitialized();

private:
    RWDBMTCountedRef<RWDBDatabaseImp> impl_;

    friend RWDBDatabaseImp* getImp(const RWDBDatabase& dbase)
    {
        return dbase.impl_;
    }
    static bool   connect_;
};


#endif
