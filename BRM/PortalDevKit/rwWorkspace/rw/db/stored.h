#ifndef __RWDB_STORED_H__
#define __RWDB_STORED_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/stored.h#1 $
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
 * Definition of class RWDBStoredProc
 *
 * This class provides a standard interface to the specific database
 * implementation of "stored procedures", i.e. the method used to manipulate
 * data in the database via procedure like calls.
 *
 * The schema of the parameters is fetched from the database whenever the
 * stored procedure is first created. From that point on, the schema is kept
 * as part of the stored procedure to check parameter types, positioning, etc.
 * For more information about the specific implementation,
 * see the header files for the specific database.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/expr.h>
#include <rw/db/status.h>
#include <rw/db/value.h>
#include <rw/tools/bustring.h>

/**
 * \ingroup db_common_group
 * \class RWDBStoredProc
 *
 * \brief
 * Encapsulates a database stored procedure, providing a uniform API to the
 * common operations related to them.
 *
 * Many modern RDBMS implementations include a mechanism to enforce database
 * policy through stored procedures. Applications may be required to do much
 * of their data manipulation through stored procedures. Unfortunately, the
 * standards bodies have had little to say about stored procedures, so
 * implementations vary widely among RDBMS vendors. If an RWDBStoredProc
 * feature is not supported by the underlying database, <b><em>The DB
 * Interface Module</em></b> reports an RWDBStatus::notSupported error. The
 * remainder of this section assumes that all features are supported. Check
 * the DB Access Module guide for information about what features are
 * supported by a particular database.
 *
 * RWDBStoredProc is an encapsulation of a database stored procedure.
 * RWDBStoredProc supports creating and deleting stored procedures,
 * retrieving stored procedures definitions, executing stored procedures,
 * and processing results returned from stored procedure execution.
 * Parameters may be passed to an RWDBStoredProc prior to execution, and the
 * values of output parameters may be retrieved. If a database vendor's
 * stored procedure may return multiple sets of results, RWDBStoredProc can
 * access each result set in turn.
 *
 * RWDBStoredProc uses an RWDBSchema to store information about its formal
 * parameters. Use the insertion operator operator<<() to pass actual
 * parameters to an RWDBStoredProc. Insert values if the stored procedure
 * expects \c IN parameters; insert pointers if the stored procedure expects
 * \c OUT or \c IN/OUT parameters and your application needs to obtain
 * results through the parameters. Insert
 * \ref RWDBValue::rwdbNull "rwdbNull" to pass a literal \c NULL by value.
 *
 * \note
 * It is an error to insert a NULL pointer; if this occurs, the status of
 * the RWDBStoredProc changes to RWDBStatus::nullReference.
 *
 * RWDBStoredProc maintains a notion of the current position in its
 * parameter list. The current position is set to zero when the
 * RWDBStoredProc is created, and reset to zero whenever the RWDBStoredProc
 * is executed. Each insertion of an actual parameter increments the current
 * position by one. The indexing operator operator[]() can be used to access
 * a particular parameter position by number or by name. Given a stored
 * procedure \c myStoredProc that expects the parameters \c number and
 * \c name in that order, these notations are equivalent:
 *
 * \code
 * RWCString  hello("Hello  World");
 *
 * myStoredProc  <<  1  <<  hello;
 *
 * myStoredProc[0]  <<  1;
 * myStoredProc[1]  <<  hello;
 *
 * myStoredProc["name"]  <<  hello;
 * myStoredProc["number"]  <<  1;
 * \endcode
 *
 * RWDBStoredProc does not check actual parameters for type; it allows the
 * database to do type conversion. If there is a type incompatibility, the
 * DB Interface Module passes along whatever the database reports to the
 * application. The DB Interface Module produces an
 * RWDBStatus::invalidPosition error if too many arguments are inserted into
 * an RWDBStoredProc. No check is made for too few arguments. The database
 * may supply defaults; if not, the DB Interface Module passes along
 * whatever the database reports to the application.
 *
 * In order to support parameter passing, <b><em>The DB Interface
 * Module</em></b> uses a connection to query the database for schema
 * information whenever an RWDBStoredProc is produced by an RWDBDatabase.
 *
 * RWDBStoredProc is designed around the Interface/Implementation paradigm.
 * An RWDBStoredProc instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBStoredProc
 * implementation is a base class from which a family of database-specific
 * stored procedure implementations is derived.
 *
 * \synopsis
 * #include <rw/db/stored.h>
 *
 * RWDBStoredProc myProc = myDbase.storedProc("myProcName");
 * \endsynopsis
 *
 * \example
 * In this example, suppose there is a database procedure \c getId, which
 * expects two parameters: \c name, an input string representing a
 * customer's name, and \c id, an output integer parameter representing the
 * customer's id. The procedure is supposed to look up the customer id for
 * the given customer name. If successful, it places the id in its \c id
 * parameter and returns \c 0. Otherwise it returns \c -1 and does not
 * change \c id.
 *
 * \code
 * RWDBStoredProc getId = myDbase.storedProc("getId");
 * RWCString name("John Doe");
 * int id;
 * getId << name << &id;
 * getId.execute();
 * RWDBValue retValue = getId.returnValue();
 * if (retValue.asInt() == 0)
 * {
 *     cout << "John Doe's id is " << id << endl;
 * }
 * else
 * {
 *     cout << "Can't find John Doe's id" << endl;
 * }
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBStoredProc
{
public:
    /**
     * A class-scoped enum containing the cache types.
     */
    enum CacheType {

        /**
         * Clears self's cache. Cached data for an RWDBStoredProc consists
         * of the parameter list, the state of the exists flag, and the
         * text.
         */
        Local = 0,

        /**
         * Clears cached data in self and in the cache manager, if there is
         * one. Cached data for an RWDBStoredProc consists of the parameter
         * list, the state of the exists flag, and the text.
         */
        All
    };

    /**
     * The default constructor creates an RWDBStoredProc whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience, for example, for declaring an array of RWDBStoredProc
     * objects. Usable RWDBStoredProc objects are obtained from RWDBDatabase
     * instances.
     */
    RWDBStoredProc();

    /**
     * Copy constructor. Self shares an implementation with \a proc.
     */
    RWDBStoredProc(const RWDBStoredProc& proc);

    RWDBStoredProc(RWDBStoredProcImp* impl);
    virtual ~RWDBStoredProc();

    /**
     * Assignment operator. Self shares an implementation with \a proc.
     */
    RWDBStoredProc& operator=(const RWDBStoredProc& proc);

    // Accessors

    /**
     * Returns the RWDBDatabase that produced self. Returns an RWDBDatabase
     * whose status is RWDBStatus::notInitialized, if self was created with
     * the default constructor.
     */
    RWDBDatabase        database() const;

    /**
     * Returns self's name.
     */
    RWCString           name() const;

    // Mutators

    /**
     * Clears all internal state.
     */
    RWDBStatus          clear();

    /**
     * Clears cached metadata information. If \a cache is
     * RWDBStoredProc::Local, clears cache in self. If \a cache is
     * RWDBStoredProc::All, clears cached data in self and in the global
     * cache derived from RWDBCacheManager, if there is one.
     */
    void          clearCache(CacheType cache = RWDBStoredProc::Local);

    // multithreading support

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                acquire() const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                release() const;

    // Error Handling

    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, an
     * RWDBStatus::ErrorHandler is inherited from the object which produced
     * self; this method overrides the default.
     */
    void                     setErrorHandler(RWDBStatus::ErrorHandler handler);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Returns the current status of self.
     */
    RWDBStatus               status() const;

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise returns
     * \c false.
     */
    bool                isValid() const;

    /**
     * This function returns \c true if the object is in ready state,
     * indicating that accessing the object will not block. Accessing a
     * nonready object may potentially block.
     */
    bool                isReady() const;

    // Execution

    /**
     * Uses a default database connection to execute the stored procedure
     * encapsulated by self. The connection is held by the RWDBResult until
     * the RWDBResult is destroyed. The connection is also held by self
     * until either fetchReturnParams() or returnValue() is called, or the
     * RWDBStoredProc is destroyed.
     */
    RWDBResult          execute();

    /**
     * Uses the supplied \a connection to execute the stored procedure
     * encapsulated by self. The connection is held by the RWDBResult until
     * the RWDBResult is destroyed. The connection is also held by self
     * until either fetchReturnParams() or returnValue() is called, or the
     * RWDBStoredProc is destroyed. This function can behave asynchronously
     * if executed using an asynchronous connection.
     */
    RWDBResult          execute(const RWDBConnection& connection);

    /**
     * The connection used by the last call to execute() is used to obtain
     * any output parameters returned by the database stored procedure. If
     * execute() has not yet been successfully invoked, sets self's status
     * and returns RWDBStatus::notConnected. Some databases do not support
     * return parameters, in this case RWDBStatus::notSupported is returned.
     * This function behaves asynchronously if the stored procedure was
     * created using an asynchronous connection.
     */
    RWDBStatus          fetchReturnParams();

    /**
     * Calls fetchReturnParams(), then, if no error has occurred, obtains
     * the return value of the most recent execution of self in the database
     * and returns it. If there is no return value, or if an error has
     * occurred, returns a \c NULL RWDBValue. In the latter case sets self's
     * status to reflect the error.
     */
    RWDBValue           returnValue() const;

    /**
     * Returns a deep copy of the RWDBColumn representing the datatype of
     * self's return value. If there is no return value, returns an
     * RWDBColumn whose status is RWDBStatus::columnNotFound.
     */
    RWDBColumn          returnValueColumn() const;

    // DDL

    /**
     * Uses a default database connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * <tt>DROP PROCEDURE</tt> \e \<name\>
     *
     * where \e \<name\> is the name of the database stored procedure
     * encapsulated by self. You can check the
     * \ref RWDBStatus::isValid() "isValid()" method of the return value to
     * see if the operation succeeded.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus          drop();

    /**
     * Uses the supplied \a connection to execute the database-specific
     * equivalent of the SQL statement:
     *
     * <tt>DROP PROCEDURE</tt> \e \<name\>
     *
     * where \e \<name\> is the name of the database stored procedure
     * encapsulated by self. You can check the
     * \ref RWDBStatus::isValid() "isValid()" method of the return value to
     * see if the operation succeeded. This function can behave
     * asynchronously if executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> May generate a server error. This method can
     * still be used \b before XA connectivity is established.
     */
    RWDBStatus          drop(const RWDBConnection& connection);

    /**
     * Returns the SQL text used to define the stored procedure encapsulated
     * by self. If the text was cached in self, returns the cached text.
     * Otherwise, if the text was previously cached in the cache manager
     * installed on the RWDBDatabase that produced self, returns the text
     * found in the cache manager. If the text was not in either the local
     * cache or cache manager, the database is queried, using a default
     * database connection, and the retrieved text is returned and also
     * stored in the local cache and the cache manager, if there is one.
     *
     * By setting \a forceLookup to \c true, this method necessarily queries
     * the database.
     *
     * If for some reason the text cannot be obtained from either the caches
     * or the database, this method returns an empty string and sets self's
     * status to reflect the error.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    RWCString           text(bool forceLookup = false) const;

    /**
     * Returns the SQL text used to define the stored procedure encapsulated
     * by self. If the text was cached in self, returns the cached text.
     * Otherwise, if the text was previously cached in the cache manager
     * installed on the RWDBDatabase that produced self, returns the text
     * found in the cache manager. If the text was not in either the local
     * cache or cache manager, the database is queried, using the supplied
     * \a connection, and the retrieved text is returned and also stored in
     * the local cache and the cache manager, if there is one.
     *
     * By setting \a forceLookup to \c true, this method necessarily queries
     * the database.
     *
     * If for some reason the text cannot be obtained from either the caches
     * or the database, this method returns an empty string and sets self's
     * status to reflect the error.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    RWCString           text(const RWDBConnection& connection,
                             bool forceLookup = false) const;

    /**
     * Returns an RWDBSchema which represents self's formal parameter list.
     * If the schema was cached in self, returns the cached schema.
     * Otherwise, if the schema was previously cached in the cache manager
     * installed on the RWDBDatabase that produced self, returns the schema
     * found in the cache manager. If the schema was not in either the local
     * cache or cache manager, the database is queried, using a default
     * database connection, and the retrieved schema is returned and also
     * stored in the local cache and the cache manager, if there is one.
     *
     * By setting \a forceLookup to \c true, this method necessarily queries
     * the database.
     *
     * If for some reason the schema cannot be obtained from either the
     * caches or the database, this method returns an empty schema and sets
     * self's status to reflect the error.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    RWDBSchema          params(bool forceLookup = false) const;

    /**
     * Returns an RWDBSchema which represents self's formal parameter list.
     * If the schema was cached in self, returns the cached schema.
     * Otherwise, if the schema was previously cached in the cache manager
     * installed on the RWDBDatabase that produced self, returns the schema
     * found in the cache manager. If the schema was not in either the local
     * cache or cache manager, the database is queried, using the supplied
     * \a connection, and the retrieved schema is returned and also stored
     * in the local cache and the cache manager, if there is one.
     *
     * By setting \a forceLookup to \c true, this method necessarily queries
     * the database.
     *
     * If for some reason the schema cannot be obtained from either the
     * caches or the database, this method returns an empty schema and sets
     * self's status to reflect the error.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    RWDBSchema          params(const RWDBConnection& connection,
                               bool forceLookup = false) const;

    /**
     * Returns \c true if the stored procedure encapsulated by self exists
     * in the database. If the result was cached in self, returns the cached
     * result. Otherwise, if the result was previously cached in the cache
     * manager installed on the RWDBDatabase that produced self, returns the
     * result found in the cache manager. If the result was not in either
     * the local cache or cache manager, the database is queried, using a
     * default database connection, and the retrieved result is returned and
     * also stored in the local cache and the cache manager, if there is
     * one.
     *
     * By setting \a forceLookup to \c true, this method necessarily queries
     * the database.
     *
     * If for some reason the result cannot be obtained from either the
     * caches or the database, this method returns \c false.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    bool           exists(bool forceLookup = false) const;

    /**
     * Returns \c true if the stored procedure encapsulated by self exists
     * in the database. If the result was cached in self, returns the cached
     * result. Otherwise, if the result was previously cached in the cache
     * manager installed on the RWDBDatabase that produced self, returns the
     * result found in the cache manager. If the result was not in either
     * the local cache or cache manager, the database is queried, using the
     * supplied \a connection, and the retrieved result is returned and also
     * stored in the local cache and the cache manager, if there is one.
     *
     * By setting \a forceLookup to \c true, this method necessarily queries
     * the database.
     *
     * If for some reason the result cannot be obtained from either the
     * caches or the database, this method returns \c false.
     *
     * \note
     * The \a forceLookup parameter is deprecated. Use clearCache() to clear
     * the metadata from the cache before calling this method.
     */
    bool           exists(const RWDBConnection& connection,
                          bool forceLookup = false) const;

    /**
     * Passes \a value as the \c n<sup>th</sup> parameter to self, where
     * \c n is the current position in self's formal parameter list, and
     * increments the current position by one. The parameter is passed by
     * value.
     */
    RWDBStoredProc&     operator<<(RWDBValueManip value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWDBValue& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(char value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(unsigned char value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(short value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(unsigned short value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(int value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(unsigned int value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(long value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(unsigned long value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(long long value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(unsigned long long value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(float value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(double value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(long double value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWDecimalPortable& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWDate& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWDateTime& value);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 12.5, use
     * RWDBStoredProc::operator<<(const RWDateTime&) instead.
     *
     * \copydoc operator<<(RWDBValueManip)
     */
    RW_DEPRECATE_FUNC("Use RWDBStoredProc::operator<<(const RWDateTime&) instead")
    RWDBStoredProc&     operator<<(const RWDBDateTime& value);
#endif

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWDBDuration& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWCString& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWDBMBString& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWBasicUString& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWWString& value);

    /**
     * \copydoc operator<<(RWDBValueManip)
     */
    RWDBStoredProc&     operator<<(const RWDBBlob& value);

    /**
     * Inserts a placeholder and performs binding for in-type parameters.
     * Here <em>in-type binding</em> includes <em>in/out binding</em>. The
     * meaning of shifting in an RWDBBoundExpr with entries greater than
     * \c 1 is vendor-dependent.
     */
    RWDBStoredProc&     operator<<(const RWDBBoundExpr& value);

    /**
     * Passes \a valPtr as the \c n<sup>th</sup> parameter to self, where
     * \c n is the current position in self's formal parameter list, and
     * increments the current position by \c 1. The parameter is passed by
     * reference. After executing the stored procedure, the variable
     * addressed by \a valPtr is updated by calling either
     * fetchReturnParams() or returnValue().
     */
    RWDBStoredProc&     operator<<(short* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(unsigned short* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(int* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(unsigned int* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(long* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(unsigned long* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(long long* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(unsigned long long* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(float* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(double* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(long double* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWDecimalPortable* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWDate* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWDateTime* valPtr);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 12.5, use RWDBStoredProc::operator<<(RWDateTime*)
     * instead.
     *
     * \copydoc operator<<(short*)
     */
    RW_DEPRECATE_FUNC("Use RWDBStoredProc::operator<<(RWDateTime*) instead")
    RWDBStoredProc&     operator<<(RWDBDateTime* valPtr);
#endif

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWDBDuration* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWDBBlob* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWCString* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWDBMBString* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWBasicUString* valPtr);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBStoredProc&     operator<<(RWWString* valPtr);

    /**
     * Self's current row position is set to the index in self's schema of
     * the first parameter whose name matches that of \a paramColumn. If
     * there is no such parameter, self's status changes to
     * RWDBStatus::invalidPosition. Returns reference to self.
     */
    RWDBStoredProc&     operator[](const RWDBColumn& paramColumn);

    /**
     * Self's current row position is set to the index in self's schema of
     * the first parameter whose name is \a paramName. If there is no such
     * parameter, self's status changes to RWDBStatus::invalidPosition.
     * Returns a reference to self.
     */
    RWDBStoredProc&     operator[](const RWCString& paramName);

    /**
     * Self's current row position is set to \a index. If \a index is
     * greater than or equal to the number of parameters expected by self,
     * self's status is changed to RWDBStatus::invalidPosition. Returns a
     * reference to self.
     */
    RWDBStoredProc&     operator[](size_t index);

    /**
     * Returns \c true if the last value fetched into the output parameter
     * with the same name as \a column was \c NULL. Otherwise returns
     * \c false. If there is no such output parameter with the same name,
     * self's status changes to RWDBStatus::invalidPosition.
     */
    bool           isNull(const RWDBColumn& column) const;

    /**
     * Returns \c true if the last value fetched into the output parameter
     * with the given \a name was \c NULL. Otherwise returns \c false. If
     * there is no such output parameter with that given \a name, self's
     * status changes to RWDBStatus::invalidPosition.
     */
    bool           isNull(const RWCString& name) const;

    /**
     * Returns \c true if the last value fetched into the output parameter
     * at position \a index was \c NULL. Otherwise returns \c false. If
     * there is no such output parameter at \a index, self's status changes
     * to RWDBStatus::invalidPosition.
     */
    bool           isNull(size_t index) const;

    /**
     * Returns the current position, at which the next value will be shifted
     * in using the insertion operator. Returns #RW_NPOS if isValid()
     * returns false.
     */
    size_t         position() const;

private:
    RWDBCountedRef<RWDBStoredProcImp>  impl_;
    friend RWDBStoredProcImp* getImp(const RWDBStoredProc& sproc)
    {
        return sproc.impl_;
    }
};

#endif
