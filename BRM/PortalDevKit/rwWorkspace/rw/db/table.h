#ifndef __RWDB_TABLE_H__
#define __RWDB_TABLE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/table.h#1 $
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
 **************************************************************************
 *
 * RWDBTable represents a tabular collection of data whose physical
 * location is unknown.  The data may reside on disk (database table),
 * in memory (memory table), or be an SQL 'table expression' (result table).
 * Data is read from a table using RWDBReader.  Table also offers DDL
 * support (drop(), addColumn(), etc).
 *
 **************************************************************************/

#include <rw/db/bkins.h>
#include <rw/db/bkread.h>
#include <rw/db/column.h>
#include <rw/db/cursor.h>
#include <rw/db/defs.h>
#include <rw/db/forkey.h>
#include <rw/db/primarykey.h>
#include <rw/ordcltn.h>


////////////////////////////////////////////////////////////////////////////
//
// RWDBImpControl:: To facilitate construction of handles without imps.
//     Made it a class to avoid differential treatment of enums by different
//     compilers
//
////////////////////////////////////////////////////////////////////////////
class RWDB_SYMBOLIC RWDBImpControl
{

public :
    enum RWDBImpControlFlag { suppressDefaultImp };

    RWDBImpControl(RWDBImpControlFlag = suppressDefaultImp);
    ~RWDBImpControl();

protected:

private:
};


/**
 * \ingroup db_common_group
 * \class RWDBTable
 *
 * \brief
 * Base class for a family of classes that represent the abstract notion of
 * a database table in a number of different ways.
 *
 * RWDBTable is a base class from which a family of classes derive.
 * RWDBTable represents a table of information whose actual location is
 * transparent. The data may reside in a database table or in program
 * memory, or may be an SQL <em>table expression</em>, that is, a derived
 * table or collection of rows returned from a database query. The types of
 * tables to which RWDBTable provides an interface are:
 *
 * - Database table -- a handle to a table physically stored in the database
 * - Derived table -- representing a SQL query as a table, which can be used
 * in other queries in place of a database table
 * - Result table -- the rows returned as the result of a query
 * - Memory table -- a table stored in program memory
 *
 * RWDBTable is designed around the Interface/Implementation paradigm. An
 * RWDBTable instance is an interface to a reference-counted implementation;
 * copy constructors and assignment operators produce additional references
 * to a shared implementation. An RWDBTable implementation is a base class
 * from which a family of table implementations is derived. Each
 * implementation except that of a derived table and RWDBMemTable is in turn
 * a base class from which a family of database-specific table
 * implementations derive.
 *
 * \synopsis
 * #include <rw/db/table.h>
 *
 * RWDBTable myTable = myDbase.table("tableName");
 * RWDBTable myMemTable = myDbase.memTable("tableName");
 * RWDBResult myResult = mySelector.execute();
 *  //or deleter.execute() or updater.execute() or inserter.execute() or
 *  //storedProc.execute()
 * RWDBTable myResultTable = myResult.table();
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBTable
{
public:

    /**
     * A class-scoped enum containing the cache types.
     */
    enum CacheType {

        /**
         * Clears self's cache. Cached data for an RWDBTable consists of the
         * schema, the state of the exists flag and whether self is a view
         * or not. Note that data about primary keys, foreign keys,
         * referred-to-by keys, check constraints, unique constraints and
         * identity column, if stored in schema, is also cleared.
         */
        Local = 0,

        /**
         * Clears cached data in self and in the cache manager derived from
         * RWDBCacheManager, if there is one. Cached data for an RWDBTable
         * consists of schema, the state of the exists flag and whether self
         * is a view or not. Note that data about primary keys, foreign
         * keys, referred-to-by keys, check constraints, unique constraints
         * and identity column, if stored in schema, is also cleared.
         */
        All
    };


    /**
     * A class-scoped enum containing the metadata types.
     */
    enum Metadata {

        /**
         * No metadata type.
         */
        None = 0,

        /**
         * List of columns of a table including applicable attributes such
         * as column name, type, storage length, native type, precision,
         * scale and null allowed.
         */
        ColumnList = 1,

        /**
         * Default values associated with columns of a database table.
         *
         * \note
         * Applies only to database tables.
         */
        DefaultValues = 2,

        /**
         * Identity constraint on a database table.
         *
         * \note
         * Applies only to database tables.
         */
        IdentityConstraint = 4,

        /**
         * Primary key of a database table.
         *
         * \note
         * Applies only to database tables.
         */
        PrimaryKey = 8
    };


    /**
     * The default constructor creates an RWDBTable whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience, for example, for declaring an array of RWDBTable
     * objects. Usable RWDBTable objects are obtained from RWDBDatabase and
     * RWDBResult.
     */
    RWDBTable();

    /**
     * Copy constructor. Self shares an implementation with \a table.
     */
    RWDBTable(const RWDBTable& table);

    RWDBTable(RWDBTableImp* imp);

    /**
     * Assignment operator. Self shares an implementation with \a table.
     */
    RWDBTable& operator=(const RWDBTable& table);

    virtual ~RWDBTable();

    /**
     * Returns a deep copy of the RWDBColumn in self's schema at the given
     * \a index. The RWDBColumn returned is associated with self, that is,
     * the \ref RWDBColumn::table() "table()" method of the returned
     * RWDBColumn returns this table. A deep copy is made so that
     * applications can modify the returned RWDBColumn without modifying the
     * associated RWDBTable schema. If \a index is out of range, returns an
     * RWDBColumn whose status is RWDBStatus::columnNotFound.
     */
    RWDBColumn   column(size_t index) const;

    /**
     * Returns a deep copy of the first RWDBColumn in self's schema whose
     * name matches the given \a name. The RWDBColumn returned is associated
     * with self, that is, the \ref RWDBColumn::table() "table()" method of
     * the returned RWDBColumn returns this table. If no matching column is
     * found, returns an RWDBColumn whose status is
     * RWDBStatus::columnNotFound. A deep copy is made so that applications
     * can modify the returned RWDBColumn without modifying the associated
     * RWDBTable schema.
     */
    RWDBColumn   column(const RWCString& name) const;

    /**
     * Returns a deep copy of the first RWDBColumn in self's schema whose
     * name matches the given \a name, according to \a caseCompare. The
     * RWDBColumn returned is associated with self, that is, the
     * \ref RWDBColumn::table() "table()" method of the returned RWDBColumn
     * returns this table. If no matching column is found, returns an
     * RWDBColumn whose status is RWDBStatus::columnNotFound. A deep copy is
     * made so that applications can modify the returned RWDBColumn without
     * modifying self's schema.
     */
    RWDBColumn   column(const RWCString& name,
                        RWCString::caseCompare caseCompare) const;

    /**
     * Returns a deep copy of self's identity column. If there is no
     * identity column, returns an RWDBColumn whose RWDBStatus is
     * columnNotFound.
     */
    RWDBColumn   identityColumn() const;

    /**
     * Returns a deep copy of the first RWDBColumn in self's schema whose
     * name matches the given \a name. The RWDBColumn returned is associated
     * with self, that is, the \ref RWDBColumn::table() "table()" method of
     * the returned RWDBColumn returns this table. If no matching column is
     * found, returns a new RWDBColumn instance whose name is set to \a name
     * and status is RWDBStatus::ok. This is used with RWDBSelector to build
     * up selectors and criteria without requiring an application to fetch
     * the schema of a table. For example:
     *
     * \code{.unparsed}
     * myselector << table["name"]
     * \endcode
     *
     * \sa
     * RWDBSelector
     */
    RWDBColumn   operator[](const RWCString& name) const;

    /**
     * Returns a deep copy of the RWDBColumn in self's schema at the given
     * \a position. The RWDBColumn returned is associated with self. If no
     * matching column is found, returns an RWDBColumn whose status is
     * RWDBStatus::columnNotFound. A deep copy is made so that the
     * application can modify the returned RWDBColumn without modifying
     * self's schema.
     */
    RWDBColumn   operator[](size_t      position) const;

    /**
     * Returns the index in self's schema of the first column with the given
     * \a name. Returns #RW_NPOS if there is no such column.
     */
    size_t       index(const RWCString& name) const;

    /**
     * Returns the index in self's schema of the first column which matches
     * the given \a name, according to \a caseCompare. Returns #RW_NPOS if
     * there is no such column.
     */
    size_t       index(const RWCString&  name,
                       RWCString::caseCompare caseCompare) const;

    /**
     * Returns the index in self's schema of the first column whose name
     * matches the name of the given \a column. Returns #RW_NPOS if there is
     * no such column.
     */
    size_t       index(const RWDBColumn& column) const;

    /**
     * Returns the RWDBDatabase that produced this table. If there is no
     * such object, for example, if this table was created by the default
     * constructor, returns an RWDBDatabase with status
     * RWDBStatus::notInitialized. If self is a memory table, this method
     * always returns an RWDBDatabase with a status of
     * RWDBStatus::notInitialized.
     */
    RWDBDatabase database() const;

    /**
     * Returns self's name. Returns an empty string if self is unnamed.
     */
    RWCString    name() const;

    /**
     * Returns self's tag. A table's tag is an alias generated by the DB
     * Interface Module for use in SQL queries.
     */
    RWCString    tag() const;

    /**
     * Returns a shallow copy of self's RWDBSchema.
     */
    RWDBSchema   schema() const;

    /**
     * Returns the number of columns in self's schema.
     */
    size_t       numberOfColumns() const;

    /**
     * Changes the name of self to \a name. Returns a reference to self.
     */
    RWDBTable&   name(const RWCString& name);

    /**
     * Set self's tag to \a newTag. If \a newTag is empty, self's table
     * name, instead of table tag, is used to qualify columns associated
     * with self in SQL statements. Returns a reference to self.
     */
    RWDBTable&   tag(const RWCString& newtag);

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void         acquire(void) const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void         release(void) const;

    /**
     * Calls RWDBCacheManager::getPrimaryKey() const. If successful, updates
     * self's schema with the return value. Otherwise, uses \a conn to fetch
     * the primary key associated with self. If successful, updates self's
     * schema with the return value and calls
     * RWDBCacheManager::setPrimaryKey(const RWDBPrimaryKey&). An empty
     * RWDBPrimaryKey indicates there is no primary key associated with
     * self.
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the primary key.
     */
    RWDBPrimaryKey   primaryKey(const RWDBConnection& conn);

    /**
     * Calls RWDBCacheManager::getPrimaryKey() const. If successful, updates
     * self's schema with the return value. Otherwise, uses a default
     * connection to fetch the primary key associated with self. If
     * successful, updates self's schema with the return value and calls
     * RWDBCacheManager::setPrimaryKey(const RWDBPrimaryKey&). An empty
     * RWDBPrimaryKey indicates there is no primary key associated with
     * self. You can check the status of the returned RWDBPrimaryKey to
     * determine whether the operation succeeded with the method
     * RWDBPrimaryKey::status().\ref RWDBStatus::isValid() "isValid()".
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the primary key.
     */
    RWDBPrimaryKey   primaryKey();

    /**
     * Calls RWDBCacheManager::getReferredToBy() const. If successful,
     * appends to \a keyList all foreign keys that refer to self. Otherwise,
     * uses \a conn to append to \a keyList all foreign keys that refer to
     * self. If successful, calls
     * RWDBCacheManager::setReferredToBy(const RWDBForeignKeyList&). You can
     * check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether the operation succeeded.
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the foreign keys.
     */
    RWDBStatus   referredToBy(const RWDBConnection& conn,
                              RWDBForeignKeyList& keyList);

    /**
     * Calls RWDBCacheManager::getReferredToBy() const. If successful,
     * appends to \a keyList all foreign keys that refer to self. Otherwise,
     * uses a default connection to append to \a keyList all foreign keys
     * that refer to self. If successful, calls
     * RWDBCacheManager::setReferredToBy(const RWDBForeignKeyList&). You can
     * check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether the operation succeeded.
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the foreign keys.
     */
    RWDBStatus   referredToBy(RWDBForeignKeyList& keyList);

    /**
     * Calls RWDBCacheManager::getForeignKeys() const. If successful,
     * appends the foreign keys to \a keyList. Otherwise, uses \a conn to
     * append a list of foreign keys to \a keyList. If \a refName is blank,
     * \a keyList will contain all self's foreign keys. If \a refName is not
     * blank, \a keyList will contain the foreign key of self that refers to
     * \a refName. An empty list indicates there are no foreign keys
     * associated with self referring to \a refName. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded. If successful, calls
     * RWDBCacheManager::setForeignKeys(const RWDBForeignKeyList&).
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the foreign keys.
     */
    RWDBStatus   foreignKeys(const RWDBConnection& conn,
                             const RWCString& refName,
                             RWDBForeignKeyList& keyList);

    /**
     * Calls RWDBCacheManager::getForeignKeys() const. If successful,
     * appends the foreign keys to \a keyList. Otherwise, uses a default
     * connection to append a list of foreign keys to \a keyList. If
     * \a refName is blank, \a keyList will contain all self's foreign keys.
     * If \a refName is not blank, \a keyList will contain the foreign key
     * of self that refers to \a refName. An empty list indicates there are
     * no foreign keys associated with self referring to \a refName. You can
     * check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether the operation succeeded. If successful,
     * calls RWDBCacheManager::setForeignKeys(const RWDBForeignKeyList&).
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the foreign keys.
     */
    RWDBStatus   foreignKeys(const RWCString& refName,
                             RWDBForeignKeyList& keyList);

    /**
     * Calls RWDBCacheManager::getCheckConstraints() const. If successful,
     * appends the check constraints to \a list. Otherwise, uses \a conn to
     * append a list of check constraints to \a list and, if successful,
     * calls
     * RWDBCacheManager::setCheckConstraints(const RWDBCheckConstraintList&).
     * If \a constraintName is blank, \a list will contain all of self's
     * check constraints. If \a constraintName is not blank, \a list will
     * contain the check constraint of self whose name is \a constraintName.
     * A list without appended elements indicates there are no check
     * constraints associated with self. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded.
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the check constraints.
     */
    RWDBStatus   checkConstraints(const RWDBConnection& conn,
                                  const RWCString& constraintName,
                                  RWDBCheckConstraintList& list);

    /**
     * Calls RWDBCacheManager::getCheckConstraints() const. If successful,
     * appends the check constraints to \a list. Otherwise, uses a default
     * connection to append a list of check constraints to \a list and, if
     * successful, calls
     * RWDBCacheManager::setCheckConstraints(const RWDBCheckConstraintList&).
     * If \a constraintName is blank, \a list will contain all of self's
     * check constraints. If \a constraintName is not blank, \a list will
     * contain the check constraint of self whose name is \a constraintName.
     * A list without appended elements indicates there are no check
     * constraints associated with self. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded.
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the check constraints.
     */
    RWDBStatus   checkConstraints(const RWCString& constraintName,
                                  RWDBCheckConstraintList& list);

    /**
     * Calls RWDBCacheManager::getUniqueConstraints() const. If successful,
     * appends the unique constraints to \a list. Otherwise, uses \a conn
     * connection to append a list of unique constraints to \a list and, if
     * successful, calls
     * RWDBCacheManager::setUniqueConstraints(const RWDBUniqueConstraintList&).
     * If \a constraintName is blank, \a list will contain all of self's
     * unique constraints. If \a constraintName is not blank, \a list will
     * contain the unique constraint of self whose name is
     * \a constraintName. A list without appended elements indicates there
     * are no unique constraints associated with self. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded.
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the unique constraints.
     */
    RWDBStatus   uniqueConstraints(const RWDBConnection& conn,
                                   const RWCString& constraintName,
                                   RWDBUniqueConstraintList& list);

    /**
     * Calls RWDBCacheManager::getUniqueConstraints() const. If successful,
     * appends the unique constraints to \a list. Otherwise, uses a default
     * connection to append a list of unique constraints to \a list and, if
     * successful, calls
     * RWDBCacheManager::setUniqueConstraints(const RWDBUniqueConstraintList&).
     * If \a constraintName is blank, \a list will contain all of self's
     * unique constraints. If \a constraintName is not blank, \a list will
     * contain the unique constraint of self whose name is
     * \a constraintName. A list without appended elements indicates there
     * are no unique constraints associated with self. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded.
     *
     * \note
     * This method ensures the schema has already been retrieved before
     * attempting to get the unique constraints.
     */
    RWDBStatus   uniqueConstraints(const RWCString& constraintName,
                                   RWDBUniqueConstraintList& list);

    /**
     * If self is a database table, returns \c true if the table exists in
     * the database, otherwise returns \c false. If self is a derived table,
     * returns \c true if the schema of the result set of the SQL \c SELECT
     * statement that self represents can be fetched, otherwise returns
     * \c false. If self is a memory table, always returns \c false. If self
     * is a result table, returns \c true if an RWDBReader has not yet been
     * obtained to read self, otherwise returns \c false.
     *
     * To determine whether or not a database table exists, the DB Interface
     * Module uses a default connection to query the database. To determine
     * whether or not a derived table exists, the DB Interface Module uses a
     * default connection to fetch the schema of the encapsulated
     * RWDBSelectorBase instance. If no schema can be obtained, returns
     * \c false. Otherwise, self's RWDBSchema is populated with the result
     * of the query, and returns \c true.
     *
     * By default, multiple calls to a database table's or derived table's
     * exists() method always return the same result; the database is only
     * queried on the first call. This behavior can be overridden by
     * \a forceLookup, which, if \c true, forces the database to be queried.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    bool         exists(bool forceLookup = false);

    /**
     * If self is a database table, returns \c true if the table exists in
     * the database, otherwise returns \c false. If self is a derived table,
     * returns \c true if the schema of the result set of the SQL \c SELECT
     * statement that self represents can be fetched, otherwise returns
     * \c false. If self is a memory table, always returns \c false. If self
     * is a result table, returns \c true if an RWDBReader has not yet been
     * obtained to read self, otherwise returns \c false.
     *
     * To determine whether or not a database table exists, the DB Interface
     * Module uses the supplied \a connection to query the database. To
     * determine whether or not a derived table exists, the DB Interface
     * Module uses the supplied \a connection to fetch the schema of the
     * encapsulated RWDBSelectorBase instance. If no schema can be obtained,
     * returns \c false. Otherwise, self's RWDBSchema is populated with the
     * result of the query, and returns \c true.
     *
     * By default, multiple calls to a database table's or derived table's
     * exists() method always return the same result; the database is only
     * queried on the first call. This behavior can be overridden by
     * \a forceLookup, which forces the database to be queried if \c true.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    bool         exists(const RWDBConnection& connection,
                        bool forceLookup = false);
    /**
     * If self is a database table, returns \c true if schema information
     * about the table can be obtained, otherwise returns \c false. If self
     * is a derived table, returns \c true if the schema of the result set
     * of the SQL \c SELECT statement that self represents can be fetched,
     * otherwise returns \c false. If self is a memory table, always returns
     * \c true. If self is a result table, returns \c true if an RWDBReader
     * has not yet been obtained to read self, otherwise returns \c false.
     *
     * To obtain schema information, the DB Interface Module uses a default
     * database connection to query the database. If no schema can be
     * obtained, \c false is returned. Otherwise, self's RWDBSchema is
     * populated with the result of the query and \c true is returned.
     */
    virtual bool fetchSchema();

    /**
     * If self is a database table, returns \c true if the schema
     * information about the table can be obtained, otherwise returns
     * \c false. If self is a derived table, returns \c true if the schema
     * of the result set of the SQL \c SELECT statement that self represents
     * can be fetched, otherwise returns \c false. If self is a memory
     * table, always returns \c true. If self is a result table, returns
     * \c true if an RWDBReader has not yet been obtained to read self,
     * otherwise returns \c false.
     *
     * To obtain schema information, the DB Interface Module uses the
     * supplied \a connection to query the database. If no schema can be
     * obtained, \c false is returned. Otherwise, self's RWDBSchema is
     * populated with the result of the query and \c true is returned.
     */
    virtual bool fetchSchema(const RWDBConnection& connection);

    /**
     * Checks local cache for the metadata types requested in \a md. If the
     * metadata information is not in the local cache, queries the database
     * using an implicit connection. If successful, returns a shallow copy
     * of self's RWDBSchema. On failure, returns an empty RWDBSchema with
     * error information set on it, if any. Argument \a md could be a
     * bit-mask of multiple metadata types.
     *
     * If \a md is passed as None, no metadata is fetched from the database
     * and a shallow copy of the local RWDBSchema is returned.
     *
     * \note
     * RWDBTable::ColumnList will be fetched by all metadata types except
     * RWDBTable::None.
     */
    virtual RWDBSchema describe(Metadata md);

    /**
     * Checks local cache for the metadata types requested in \a md. If the
     * metadata information is not in the local cache, queries the database
     * using the supplied database connection \a conn. If successful,
     * returns a shallow copy of self's RWDBSchema. On failure, returns an
     * empty RWDBSchema with error information set on it, if any. Argument
     * \a md could be a bit-mask of multiple metadata types.
     *
     * If \a md is passed as None, no metadata is fetched from the database
     * and a shallow copy of the local RWDBSchema is returned.
     *
     * \note
     * RWDBTable::ColumnList will be fetched by all metadata types except
     * RWDBTable::None.
     */
    virtual RWDBSchema describe(Metadata md, const RWDBConnection& conn);

    /**
     * Returns \c true if self represents a database view, otherwise returns
     * \c false. More specifically:
     *
     * - If self is not a database table, returns \c false.
     *
     * - If self is a database table: If the view information was cached in
     * self, returns it. Otherwise, if the view information was previously
     * cached in the cache manager installed on the RWDBDatabase that
     * produced self, returns the view information found in the cache
     * manager. If the view information was not in either the local cache or
     * cache manager, queries the database using an implicit connection, and
     * the view information is returned and also stored in the internal
     * cache and the cache manager, if there is one.
     */
    bool         isView() const;

    /**
     * Returns \c true if self represents a database view, otherwise returns
     * \c false. More specifically:
     *
     * - If self is not a database table, returns \c false.
     *
     * - If self is a database table: If the view information was cached in
     * self, returns it. Otherwise, if the view information was previously
     * cached in the cache manager installed on the RWDBDatabase that
     * produced self, returns the view information found in the cache
     * manager. If the information was not in either the local cache or
     * cache manager, queries the database using the supplied database
     * connection \a conn, and the view information is returned and also
     * stored in the internal cache and the cache manager, if there is one.
     */
    bool         isView(const RWDBConnection& conn) const;

    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL:
     *
     * \code{.unparsed}
     * GRANT privilege ON <table> TO user
     * \endcode
     *
     * where \c \<table\> is self's table name. The DB Interface Module does
     * not validate the supplied arguments. You can check the returned
     * object's \ref RWDBStatus::isValid() "isValid()" method to see if the
     * operation succeeded. If self is not a database table, the returned
     * status is RWDBStatus::noPrivilege.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   grant(const RWCString& priv, const RWCString& user);

    /**
     * Uses the supplied database connection \a connection to execute the
     * database-specific equivalent of the SQL:
     *
     * \code{.unparsed}
     * GRANT privilege ON <table> TO user
     * \endcode
     *
     * where \c \<table\> is self's table name. The DB Interface Module does
     * not validate the supplied arguments. You can check the returned
     * object's \ref RWDBStatus::isValid() "isValid()" method to see if the
     * operation succeeded. If self is not a database table, the returned
     * status is RWDBStatus::noPrivilege. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   grant(const RWCString& priv, const RWCString& user,
                       const RWDBConnection& connection);
    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL:
     *
     * \code{.unparsed}
     * GRANT privilege ON <table> (<column-list>) TO user
     * \endcode
     *
     * where \c \<table\> is self's table name, and \c \<column-list\> is a
     * list of column names from self's schema. The DB Interface Module does
     * not validate the supplied arguments. You can check the returned
     * object's \ref RWDBStatus::isValid() "isValid()" method to see if the
     * operation succeeded. If self is not a database table, the returned
     * object is RWDBStatus::noPrivilege.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   grant(const RWCString& priv, const RWDBSchema& colList,
                       const RWCString& user);
    /**
     * Uses the supplied database \a connection to execute the
     * database-specific equivalent of the SQL:
     *
     * \code{.unparsed}
     * GRANT privilege ON <table> (<column-list>) TO user
     * \endcode
     *
     * where \c \<table\> is self's table name, and \c \<column-list\> is a
     * list of column names from self's schema. The DB Interface Module does
     * not validate the supplied arguments. You can check the returned
     * object's \ref RWDBStatus::isValid() "isValid()" method to see if the
     * operation succeeded. If self is not a database table, the returned
     * object is RWDBStatus::noPrivilege. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   grant(const RWCString& priv, const RWDBSchema& colList,
                       const RWCString& user,
                       const RWDBConnection& connection);

    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * REVOKE privilege ON <table> FROM user
     * \endcode
     *
     * where \c \<table\> is self's table name. The DB Interface Module does
     * not validate the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned object is
     * RWDBStatus::noPrivilege.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   revoke(const RWCString& privilege, const RWCString& user);

    /**
     * Uses the supplied database \a connection to execute the
     * database-specific equivalent of the SQL:
     *
     * \code{.unparsed}
     * REVOKE privilege ON <table> FROM user
     * \endcode
     *
     * where \c \<table\> is self's table name. The DB Interface Module does
     * not validate the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned object is
     * RWDBStatus::noPrivilege. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   revoke(const RWCString& privilege, const RWCString& user,
                        const RWDBConnection& connection);

    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL:
     *
     * \code{.unparsed}
     * REVOKE privilege ON <table> (<column-list>) FROM user
     * \endcode
     *
     * where \c \<table\> is self's table name, and \c \<column-list\> is a
     * list of column names from self's schema. The DB Interface Module does
     * not validate the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned object is
     * RWDBStatus::noPrivilege.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   revoke(const RWCString& privilege,
                        const RWDBSchema& columnList,
                        const RWCString& user);

    /**
     * Uses the supplied database \a connection to execute the
     * database-specific equivalent of the SQL:
     *
     * \code{.unparsed}
     * REVOKE privilege ON <table> (<column-list>) FROM user
     * \endcode
     *
     * where \c \<table\> is self's table name, and \c \<column-list\> is a
     * list of column names from self's schema. The DB Interface Module does
     * not validate the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned object is
     * RWDBStatus::noPrivilege. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   revoke(const RWCString& privilege,
                        const RWDBSchema& columnList,
                        const RWCString& user,
                        const RWDBConnection& connection);

    /**
     * Uses a default connection to execute the database-specific equivalent
     * of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> PRIMARY KEY(<column-list>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD PRIMARY KEY(<column-list>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the constraint name if supplied, and \c \<column-list\> is a list of
     * column names in the primary key. The DB Interface Module does not
     * validate the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBPrimaryKey& pk);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> PRIMARY KEY(<column-list>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD PRIMARY KEY(<column-list>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the constraint name if supplied, and \c \<column-list\> is a list of
     * column names in the primary key. The DB Interface Module does not
     * validate the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBPrimaryKey& pk,
                               const RWDBConnection& connection);

    /**
     * Uses a default connection to execute the database-specific equivalent
     * of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> FOREIGN KEY(<column-list>) REFERENCES <ref-table>(<ref-column-list>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD FOREIGN KEY(<column-list>) REFERENCES <ref-table>(<ref-column-list>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the constraint name if supplied, \c \<column-list\> is a list of
     * column names in the foreign key, \c \<ref-table\> is the referenced
     * table, and \c \<ref-column-list\> is a list of column names referred
     * to in the referenced table. The DB Interface Module does not validate
     * the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBForeignKey& fk);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> FOREIGN KEY(<column-list>) REFERENCES <table>(<column-list>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD FOREIGN KEY(<column-list>) REFERENCES <ref-table>(<ref-column-list>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the constraint name if supplied, \c \<column-list\> is a list of
     * column names in the foreign key, \c \<ref-table\> is the referenced
     * table, and \c \<ref-column-list\> is a list of column names referred
     * to in the referenced table. The DB Interface Module does not validate
     * the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBForeignKey& fk,
                               const RWDBConnection& connection);

    /**
     * Uses a default connection to execute the database=specific equivalent
     * of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> CHECK(<check-condition>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CHECK(<check-condition>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the name of the constraint if supplied, and \c \<check-condition\> is
     * the check condition. The DB Interface Module does not validate the
     * supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBCheckConstraint& cc);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> CHECK(<check-condition>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CHECK(<check-condition>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the name of the constraint if supplied, and \c \<check-condition\> is
     * the check condition. The DB Interface Module does not validate the
     * supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBCheckConstraint& cc,
                               const RWDBConnection& connection);

    /**
     * Uses a default connection to execute the database-specific equivalent
     * of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> UNIQUE(<column-list>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD UNIQUE(<column-list>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the name of the constraint if supplied, and \c \<column-list\> is a
     * list of column names in the unique constraint. The DB Interface
     * Module does not validate the supplied arguments. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to see
     * if the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBUniqueConstraint& uc);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD CONSTRAINT <constraint-name> UNIQUE(<column-list>)
     * \endcode
     *
     * or
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD UNIQUE(<column-list>)
     * \endcode
     *
     * where \c \<table\> is self's table name, \c \<constraint-name\> is
     * the name of the constraint if supplied, and \c \<column-list\> is a
     * list of column names in the unique constraint. The DB Interface
     * Module does not validate the supplied arguments. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to see
     * if the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   addConstraint(const RWDBUniqueConstraint& uc,
                               const RWDBConnection& connection);

    /**
     * Uses a default connection to execute the database-specific equivalent
     * of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> DROP CONSTRAINT <constraint-name>
     * \endcode
     *
     * where \c \<table\> is self's table name and \c \<constraint-name\> is
     * the name of the constraint. The DB Interface Module does not validate
     * the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   dropConstraint(const RWCString& constraintName);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> DROP CONSTRAINT <constraint-name>
     * \endcode
     *
     * where \c \<table\> is self's table name and \c \<constraint-name\> is
     * the name of the constraint. The DB Interface Module does not validate
     * the supplied arguments. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If self is not a database table, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBStatus   dropConstraint(const RWCString& constraintName,
                                const RWDBConnection& connection);

    /**
     * \copydoc dropConstraint(const RWCString&)
     */
    RWDBStatus   dropConstraint(const RWDBPrimaryKey& pk);

    /**
     * \copydoc dropConstraint(const RWCString&, const RWDBConnection&)
     */
    RWDBStatus   dropConstraint(const RWDBPrimaryKey& pk,
                                const RWDBConnection& connection);

    /**
     * \copydoc dropConstraint(const RWCString&)
     */
    RWDBStatus   dropConstraint(const RWDBForeignKey& fk);

    /**
     * \copydoc dropConstraint(const RWCString&, const RWDBConnection&)
     */
    RWDBStatus   dropConstraint(const RWDBForeignKey& fk,
                                const RWDBConnection& connection);

    /**
     * \copydoc dropConstraint(const RWCString&)
     */
    RWDBStatus   dropConstraint(const RWDBCheckConstraint& cc);

    /**
     * \copydoc dropConstraint(const RWCString&, const RWDBConnection&)
     */
    RWDBStatus   dropConstraint(const RWDBCheckConstraint& cc, const RWDBConnection& connection);

    /**
     * \copydoc dropConstraint(const RWCString&)
     */
    RWDBStatus   dropConstraint(const RWDBUniqueConstraint& uc);

    /**
     * \copydoc dropConstraint(const RWCString&, const RWDBConnection&)
     */
    RWDBStatus   dropConstraint(const RWDBUniqueConstraint& uc,
                                const RWDBConnection& connection);

    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD COLUMN <column>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, and
     * \c \<column\> is defined by the given \a column. If successful, calls
     * fetchSchema() so that self's schema remains consistent with the
     * database. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   addColumn(const RWDBColumn& column);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD COLUMN <column>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, and
     * \c \<column\> is defined by the given \a column. If successful, calls
     * fetchSchema() so that self's schema remains consistent with the
     * database. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   addColumn(const RWDBColumn& column,
                           const RWDBConnection& connection);

    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD COLUMN <column>
     * \endcode
     * where \c \<table\> is the database table represented by self, and
     * \c \<column\> is defined by the supplied arguments. If successful,
     * calls fetchSchema() so that self's schema remains consistent with the
     * database. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   addColumn(const RWCString& name,
                           RWDBValue::ValueType  type = RWDBValue::NoType,
                           long                  storageLength = 0,
                           int                   nativeType = -1,
                           int                   precision = -1,
                           int                   scale = -1,
                           bool             nullAllowed = true,
                           RWDBColumn::ParamType paramType =
                               RWDBColumn::notAParameter);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> ADD COLUMN <column>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, and
     * \c \<column\> is defined by the supplied arguments. If successful,
     * calls fetchSchema() so that self's schema remains consistent with the
     * database. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   addColumn(const RWCString& name,
                           const RWDBConnection& connection,
                           RWDBValue::ValueType  type = RWDBValue::NoType,
                           long                  storageLength = 0,
                           int                   nativeType = -1,
                           int                   precision = -1,
                           int                   scale = -1,
                           bool             nullAllowed = true,
                           RWDBColumn::ParamType paramType =
                               RWDBColumn::notAParameter);

    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> DROP COLUMN <column>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, and
     * \c \<column\> is the column name of the given \a column. If
     * successful, calls fetchSchema() so that self's schema remains
     * consistent with the database. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   dropColumn(const RWDBColumn& column);

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL:
     *
     * \code{.unparsed}
     * ALTER TABLE <table> DROP COLUMN <column>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, and
     * \c \<column\> is the column name of the given \a column. If
     * successful, calls fetchSchema() so that self's schema remains
     * consistent with the database. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   dropColumn(const RWDBColumn& column,
                            const RWDBConnection& connection);

    /**
     * Uses a default connection to send the database-specific equivalent of
     * the SQL statement:
     *
     * \code{.unparsed}
     * CREATE [unique] [clustered] INDEX name
     * ON <table> (<columns>)
     * \endcode
     *
     * where \a name is the name of the index to be created, \c \<table\> is
     * the database table represented by self, \c \<columns\> is a list of
     * columns defined by \a columns, and the optional keywords \c unique
     * and \c clustered are present or absent according to the supplied
     * values \a unique and \a clustered. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   createIndex(const RWCString& name,
                             const RWDBSchema& columns,
                             bool unique = true,
                             bool clustered = true);

    /**
     * Uses the supplied \a connection to send the database-specific
     * equivalent of the SQL statement:
     *
     * \code{.unparsed}
     * CREATE [unique] [clustered] INDEX name
     * ON <table> (<columns>)
     * \endcode
     *
     * where \a name is the name of the index to be created, \c \<table\> is
     * the database table represented by self, \c \<columns\> is a list of
     * columns defined by \a columns, and the optional keywords \c unique
     * and \c clustered are present or absent according to the supplied
     * values \a unique and \a clustered. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to determine whether
     * the operation succeeded. If self is not a database table, the
     * returned status is RWDBStatus::invalidUsage. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   createIndex(const RWCString& name,
                             const RWDBSchema& columns,
                             const RWDBConnection& connection,
                             bool unique = true,
                             bool clustered = true);

    /**
     * Uses a default database connection to drop the database table or view
     * represented by self. Sends the database-specific equivalent of either
     * the SQL statement:
     *
     * \code{.unparsed}
     * DROP TABLE <table>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, or:
     *
     * \code{.unparsed}
     * DROP VIEW <view>
     * \endcode
     *
     * where \c \<view\> is the database view represented by self. You can
     * check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether the operation succeeded. If self is not a
     * database table or view, the returned status is
     * RWDBStatus::invalidUsage.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   drop();

    /**
     * Uses the supplied \a connection to drop the database table or view
     * represented by self. Sends the database-specific equivalent of either
     * the SQL statement:
     *
     * \code{.unparsed}
     * DROP TABLE <table>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, or:
     *
     * \code{.unparsed}
     * DROP VIEW <view>
     * \endcode
     *
     * where \c \<view\> is the database view represented by self. You can
     * check the return value's \ref RWDBStatus::isValid() "isValid()"
     * method to determine whether the operation succeeded. If self is not a
     * database table or view, the returned status is
     * RWDBStatus::invalidUsage. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   drop(const RWDBConnection& connection);

    /**
     * Uses a default database connection to send the database-specific
     * equivalent of the SQL:
     *
     * \code{.unparsed}
     * DROP INDEX <table>.name
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, and
     * \a name is the name of the index to be dropped. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded. If self is not a database
     * table, the returned status is RWDBStatus::invalidUsage.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   dropIndex(const RWCString& name);

    /**
     * Uses the supplied \a connection to send the database-specific
     * equivalent of the SQL:
     *
     * \code{.unparsed}
     * DROP INDEX <table>.name
     * \endcode
     *
     * where \c \<table\> is the database table represented by self, and
     * \a name is the name of the index to be dropped. You can check the
     * return value's \ref RWDBStatus::isValid() "isValid()" method to
     * determine whether the operation succeeded. If self is not a database
     * table, the returned status is RWDBStatus::invalidUsage. This function
     * can behave asynchronously if executed using an asynchronous
     * connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus   dropIndex(const RWCString& name,
                           const RWDBConnection& connection);

    /**
     * Installs \a errorHandler as self's error handler. The supplied
     * handler is inherited by all objects produced by self. By default an
     * RWDBTable error handler is inherited from the object that produced
     * it. This method overwrites the default.
     */
    void         setErrorHandler(RWDBStatus::ErrorHandler errorHandler);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Returns \c true if the status of self is RWDBStatus::ok, otherwise
     * returns \c false.
     */
    bool         isValid() const;

    /**
     * Returns \c true if the object is in ready state, indicating that
     * accessing the object will not block. Accessing a nonready object may
     * potentially block.
     */
    bool         isReady() const;

    /**
     * Returns the status of self.
     */
    RWDBStatus   status() const;

    // utilities
    operator     void* () const;

    bool         isEquivalent(const RWDBTable& table) const;

    /**
     * Produces an RWDBDeleter that can be used to delete all rows from
     * self. The result is an encapsulation of the SQL statement:
     *
     * \code{.unparsed}
     * DELETE FROM <table>
     * \endcode
     *
     * where \c \<table\> is self's table name. If self is not a database
     * table, returns an RWDBDeleter whose status is RWDBStatus::noDeleter.
     */
    RWDBDeleter  deleter() const;

    /**
     * Produces an RWDBDeleter that can be used to delete rows from self
     * based on \a criterion. An RWDBCriterion is an encapsulated SQL
     * \c WHERE clause. The result is an encapsulation of the SQL statement:
     *
     * \code{.unparsed}
     * DELETE FROM <table> WHERE criterion
     * \endcode
     *
     * where \c \<table\> is self's table name. If self is not a database
     * table, returns an RWDBDeleter whose status is RWDBStatus::noDeleter.
     */
    RWDBDeleter  deleter(const RWDBCriterion& criterion) const;

    /**
     * Produces an RWDBUpdater. The result encapsulates an SQL \c UPDATE
     * statement to update all rows in self. If self is not a database
     * table, returns an RWDBUpdater whose status is RWDBStatus::noUpdater.
     */
    RWDBUpdater  updater() const;

    /**
     * Produces an RWDBUpdater. The result can be augmented with one or more
     * RWDBAssignment objects in order to create an encapsulated SQL
     * \c UPDATE statement to update rows in self specified by \a criterion.
     * If self is not a database table, returns an RWDBUpdater whose status
     * is RWDBStatus::noUpdater.
     */
    RWDBUpdater  updater(const RWDBCriterion& criterion) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * \code{.unparsed}
     * INSERT INTO <table> VALUES
     * \endcode
     *
     * where \c \<table\> is represented by self. The actual values must be
     * added to the inserter later. If self is not a database table, returns
     * an RWDBInserter with a status of RWDBStatus::noInserter.
     *
     * \note
     * Specifying \a cache as \c 0 or \c 1 creates a non-cached inserter
     * (the default), while any larger value creates a cache that collects
     * the specified number of rows before placing them in the table. It is
     * important to understand that using a cache means executing an insert
     * does not necessary immediately place the data in the table. The DB
     * Interface Module User Guide includes a discussion of RWDBInserter
     * caching. You should also check your Access Module documentation for
     * limitations and warnings.
     */
    RWDBInserter inserter(size_t cache = 0) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * \code{.unparsed}
     * INSERT INTO <table> select-statement
     * \endcode
     *
     * where \c \<table\> is represented by self. The select-statement is
     * encapsulated by the given \a selector. This method is equivalent to
     * \ref RWDBDatabase::inserter(const RWDBTable&, const RWDBSelector&) const "database.inserter(*this, selector)".
     * If self is not a database table, returns an RWDBInserter with a
     * status of RWDBStatus::noInserter.
     */
    RWDBInserter inserter(const RWDBSelector& selector) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * \code{.unparsed}
     * INSERT INTO <table> <select-statement>
     * \endcode
     *
     * where \c \<table\> is represented by self. The
     * \c \<select-statement\> is encapsulated by the given \a selector.
     * This method is equivalent to
     * \ref RWDBDatabase::inserter(const RWDBTable&, const RWDBCompoundSelector&) const "database.inserter(*this, selector)".
     * If self is not a database table, returns an RWDBInserter with a
     * status of RWDBStatus::noInserter.
     */
    RWDBInserter inserter(const RWDBCompoundSelector& selector) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * \code{.unparsed}
     * INSERT INTO <table> (col1, ..., coln)
     * VALUES(val1, ..., valn)
     * \endcode
     *
     * where \c \<table\> is represented by self. The names of the column
     * entries in \a columnList are used to build up the column-name list.
     * If self is not a database table, returns an RWDBInserter with a
     * status of RWDBStatus::noInserter.
     *
     * \note
     * Specifying \a cache as \c 0 or \c 1 creates a non-cached inserter
     * (the default), while any larger value creates a cache that collects
     * the specified number of rows before placing them in the table. It is
     * important to understand that using a cache means executing an insert
     * does not necessary immediately place the data in the table. The DB
     * Interface Module User Guide includes a discussion of RWDBInserter
     * caching. You should also check your Access Module documentation for
     * limitations and warnings.
     */
    RWDBInserter inserter(const RWDBSchema& columnList, size_t cache = 0) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * \code{.unparsed}
     * INSERT INTO <table> ( col1, ..., coln) <select-statement>
     * \endcode
     *
     * where \c \<table\> is represented by self. The names of the column
     * entries in \a columnList are used to build up the column-name list.
     * The \c \<select-statement\> is encapsulated by the given \a selector.
     * This method is equivalent to
     * \ref RWDBDatabase::inserter(const RWDBTable&, const RWDBSelector&, const RWDBSchema&) const "database.inserter(*this, selector, columnList)".
     * If self is not a database table, returns an RWDBInserter with a
     * status of RWDBStatus::noInserter.
     */
    RWDBInserter inserter(const RWDBSelector& selector,
                          const RWDBSchema& columnList) const;

    /**
     * Produces an RWDBInserter that encapsulates the SQL statement:
     *
     * \code{.unparsed}
     * INSERT INTO <table> (col1,..., coln) <select-statement>
     * \endcode
     *
     * where \c \<table\> is represented by self. The names of the column
     * entries in \a columnList are used to build up the column-name list.
     * The \c \<select-statement\> is encapsulated by the given \a selector.
     * This method is equivalent to
     * \ref RWDBDatabase::inserter(const RWDBTable&, const RWDBCompoundSelector&, const RWDBSchema&) const "database.inserter(*this, selector, columnList)".
     * If self is not a database table, returns an RWDBInserter with a
     * status of RWDBStatus::noInserter.
     */
    RWDBInserter inserter(const RWDBCompoundSelector& selector,
                          const RWDBSchema& columnList) const;

    /**
     * Produces an RWDBReader that can be used to read data from self one
     * row at a time. If self is a derived table, the RWDBReader produced
     * reads rows of the result set from execution of the SQL self
     * represents. If self is an RWDBTPtrMemTable, returns an RWDBReader
     * with a status of RWDBStatus::noReader. RWDBTPtrMemTable does not
     * support readers.
     *
     * Unless self is a memory table, a query is executed using a default
     * database connection, returning a reader for the contents of the
     * table. The reader holds the connection until the reader is destroyed.
     *
     * \note
     * Specifying \a cacheSize as \c 0 (the default) results in a Rogue
     * Wave-determined acceptable default cache size for a given access
     * module. Specify a positive numeric value to specify your own cache
     * size. The DB Interface Module User Guide includes a discussion of
     * RWDBReader caching. You should also check your Access Module
     * documentation for limitations and warnings.
     */
    RWDBReader   reader(size_t cacheSize = 0) const;

    /**
     * Produces an RWDBReader that can be used to read data from self one
     * row at a time. If self is a derived table, the RWDBReader produced
     * reads rows of the result set from execution of the SQL self
     * represents. If self is an RWDBTPtrMemTable, returns an RWDBReader
     * with a status of RWDBStatus::noReader. RWDBTPtrMemTable does not
     * support readers.
     *
     * Unless self is a memory table, a query is executed using the supplied
     * \a connection, returning an RWDBReader for the contents of the table.
     * The RWDBReader holds the \a connection until the RWDBReader is
     * destroyed. This function can behave asynchronously if executed using
     * an asynchronous connection.
     *
     * \note
     * Specifying \a cacheSize as \c 0 (the default) results in a Rogue
     * Wave-determined acceptable default cache size for a given access
     * module. Specify a positive numeric value to specify your own cache
     * size. The DB Interface Module User Guide includes a discussion of
     * RWDBReader caching. You should also check your Access Module
     * documentation for limitations and warnings.
     */
    RWDBReader   reader(const RWDBConnection& connection, size_t cacheSize = 0) const;

    /**
     * Returns an RWDBBulkReader able to read the result set associated with
     * the rows of self. If self is a derived table, the RWDBBulkReader
     * produced reads rows of the result set from execution of the SQL self
     * represents. The RWDBBulkReader executes using the supplied
     * connection.
     */
    RWDBBulkReader   bulkReader(const RWDBConnection& conn) const;

    /**
     * Returns an RWDBBulkInserter able to insert values into self. The
     * RWDBBulkInserter executes using the supplied connection.
     */
    RWDBBulkInserter bulkInserter(const RWDBConnection& conn) const;

    /**
     * If self is a database table, produces an RWDBCursor for execution of
     * the SQL statement:
     *
     * \code{.unparsed}
     * SELECT * from <table>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self.
     *
     * If self is a derived table, produces an RWDBCursor for execution of
     * the SQL Select statement self represents.
     *
     * The cursor is created on a default database connection, using the
     * \a type and \a access specifications provided. The connection is held
     * by the RWDBCursor until the RWDBCursor is destroyed. If self is a
     * result table or a memory table, the function produces an RWDBCursor
     * whose status is RWDBStatus::noCursor.
     */
    RWDBCursor   cursor(RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    /**
     * If self is a database table, produces an RWDBCursor for execution of
     * the SQL statement:
     *
     * \code{.unparsed}
     * SELECT * from <table>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self.
     *
     * If self is a derived table, produces an RWDBCursor for execution of
     * the SQL Select statement self represents.
     *
     * The cursor is created on the supplied database \a connection, using
     * the \a type and \a access specifications provided. The \a connection
     * is held by the RWDBCursor until the RWDBCursor is destroyed. If self
     * is a result table or a memory table, the function produces an
     * RWDBCursor with status RWDBStatus::noCursor. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBCursor   cursor(const RWDBConnection& connection,
                        RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL statement:
     *
     * \code{.unparsed}
     * SELECT * from <table>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self.
     *
     * If self is a derived table, produces an RWDBCursor for execution of
     * the SQL \c SELECT statement self represents.
     *
     * The argument \a updateCols is used in building a clause:
     *
     * \code{.unparsed}
     * FOR UPDATE OF column-name, column-name,...
     * \endcode
     *
     * Some SQL dialects require this form. The cursor is created on a
     * default database connection, using the \a type and \a access
     * specifications provided. The connection is held by the RWDBCursor
     * until the RWDBCursor is destroyed.
     */
    RWDBCursor   cursor(const RWDBSchema& updateCols,
                        RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    /**
     * Produces an RWDBCursor for execution of the SQL statement:
     *
     * \code{.unparsed}
     * SELECT * from <table>
     * \endcode
     *
     * where \c \<table\> is the database table represented by self.
     *
     * If self is a derived table, produces an RWDBCursor for execution of
     * the SQL \c SELECT statement self represents.
     *
     * The cursor is created on the supplied database \a connection, using
     * the \a type and \a access specifications provided. The \a connection
     * is held by the RWDBCursor until the RWDBCursor is destroyed. Some SQL
     * dialects require this form. The argument \a updateCols is used in
     * building a clause:
     *
     * \code{.unparsed}
     * FOR UPDATE OF column-name, column-name,...
     * \endcode
     *
     * This function can behave asynchronously if executed using an
     * asynchronous connection.
     */
    RWDBCursor   cursor(const RWDBSchema& updateCols,
                        const RWDBConnection& connection,
                        RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    /**
     * Clears cached metadata information. If \a cache is RWDBTable::Local,
     * clears cache in self. If \a cache is RWDBTable::All, clears cache in
     * self and in the global cache derived from RWDBCacheManager, if there
     * is one.
     */
    void clearCache(CacheType cache = RWDBTable::Local);

protected:
    RWDBCountedRef<RWDBTableImp> impl_;

    RWDBTable(const RWDBImpControl&);
    RWDBTable(const RWDBDatabase&, const RWCString&);

    friend RWDBTableImp* getImp(const RWDBTable& table)
    {
        return table.impl_;
    }

    static RWDBTable& uninitialized();
};


/**
 * \relates RWDBTable
 *
 * Inverts the value of the RWDBTable::Metadata \a md using a bitwise not
 * operation, and returns the result.
 */
inline RWDBTable::Metadata operator~(RWDBTable::Metadata md)
{
    return static_cast<RWDBTable::Metadata>(~static_cast<int>(md));
}

/**
 * \relates RWDBTable
 *
 * Combines the RWDBTable::Metadata \a lhs with \a rhs using a bitwise or
 * operation, and returns the result.
 */
inline RWDBTable::Metadata operator|(RWDBTable::Metadata lhs, RWDBTable::Metadata rhs)
{
    return static_cast<RWDBTable::Metadata>(static_cast<int>(lhs) | rhs);
}

/**
 * \relates RWDBTable
 *
 * Combines the RWDBTable::Metadata \a lhs with \a rhs using a bitwise and
 * operation, and returns the result.
 */
inline RWDBTable::Metadata operator&(RWDBTable::Metadata lhs, RWDBTable::Metadata rhs)
{
    return static_cast<RWDBTable::Metadata>(static_cast<int>(lhs) & rhs);
}

/**
 * \relates RWDBTable
 *
 * Combines the RWDBTable::Metadata \a lhs with \a rhs using a bitwise
 * exclusive or operation, and returns the result.
 */
inline RWDBTable::Metadata operator^(RWDBTable::Metadata lhs, RWDBTable::Metadata rhs)
{
    return static_cast<RWDBTable::Metadata>(static_cast<int>(lhs) ^ rhs);
}

/**
 * \relates RWDBTable
 *
 * Combines the RWDBTable::Metadata \a lhs with \a rhs using a bitwise or
 * operation, stores the result into \a lhs, and returns reference to
 * \a lhs.
 */
inline RWDBTable::Metadata& operator|=(RWDBTable::Metadata& lhs, RWDBTable::Metadata rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

/**
 * \relates RWDBTable
 *
 * Combines the RWDBTable::Metadata \a lhs with \a rhs using a bitwise and
 * operation, stores the result into \a lhs, and returns reference to
 * \a lhs.
 */
inline RWDBTable::Metadata& operator&=(RWDBTable::Metadata& lhs, RWDBTable::Metadata rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

/**
 * \relates RWDBTable
 *
 * Combines the RWDBTable::Metadata \a lhs with \a rhs using a bitwise
 * exclusive or operation, stores the result into \a lhs, and returns
 * reference to \a lhs.
 */
inline RWDBTable::Metadata& operator^=(RWDBTable::Metadata& lhs, RWDBTable::Metadata rhs)
{
    lhs = lhs ^ rhs;
    return lhs;
}



#endif
