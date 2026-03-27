#ifndef __RWDB_RESULT_H__
#define __RWDB_RESULT_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/result.h#1 $
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

#include <rw/db/defs.h>
#include <rw/db/status.h>


/**
 * \ingroup db_data_manipulation_group
 *
 * \brief
 * Represents a sequence of zero or more RWDBTable instances.
 *
 * RWDBResult represents a sequence of zero or more RWDBTable instances. An
 * RWDBResult instance is returned whenever a database operation may
 * potentially produce multiple SQL table expressions. This is obviously the
 * case when using the RWDBConnection::executeSql() method to submit
 * arbitrary SQL for execution. However, the DB Interface Module recognizes
 * that some database vendors provide:
 *
 * - Stored procedures that can execute more than one \c SELECT statement.
 *
 * - Triggers that can cause results to be generated as a result of an
 * \c INSERT, \c DELETE, or \c UPDATE statement.
 *
 * For this reason, execute() methods of each of the above operation returns
 * an RWDBResult instance. An application using a database that does not
 * provide these capabilities is not obliged to check for multiple results.
 *
 * Every RWDBResult instance has an RWDBConnection. Passing an
 * RWDBConnection to an execute() method causes the RWDBResult to acquire
 * the passed connection. Calling execute() without an RWDBConnection causes
 * the RWDBResult to acquire a default connection from the caller's
 * RWDBDatabase. In each case, the connection is held by the RWDBResult
 * until the RWDBResult is destroyed.
 *
 * The RWDBTable instances produced by RWDBResult must be processed in
 * order. Each call to RWDBResult::table() causes unprocessed rows from any
 * previous table to be flushed.
 *
 * RWDBResult is designed around the Interface/Implementation paradigm. An
 * RWDBResult instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBResult
 * implementation is a base class from which a family of database-specific
 * result implementations is derived.
 *
 * \synopsis
 * #include <rw/db/result.h>
 *
 * RWDBResult result = myConn.executeSql("someSql");
 * RWDBResult result = mySelector.execute();
 * RWDBResult result = myInserter.execute();
 * RWDBResult result = myDeleter.execute();
 * RWDBResult result = myUpdater.execute();
 * RWDBResult result = myStoredProcedure.execute();
 * \endsynopsis
 *
 * \example
 * Here is a way to process an SQL query that may return more than one table
 * expression. The example assumes that the SQL is contained in the variable
 * \c sqlString.
 *
 * \code
 * RWDBConnection dbConn = myDBase.connection();
 * RWDBResult result = dbConn.executeSql(sqlString);
 * RWDBTable resultTable = result.table();
 * while (resultTable.isValid())
 * {
 *     RWDBReader reader = resultTable.reader();
 *     while (reader())
 *     {
 *         // process a row from table
 *     }
 *     resultTable = result.table(); // get the next table
 * }
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBResult
{

public:

    /**
     * The default constructor creates an RWDBResult whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience, for example, for declaring an array of RWDBResult
     * instances. Usable RWDBResult instances are obtained from execute()
     * methods.
     */
    RWDBResult();

    /**
     * Copy constructor. Self shares an implementation with \a result.
     */
    RWDBResult(const RWDBResult& result);

    RWDBResult(RWDBResultImp* imp);

    virtual           ~RWDBResult();

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
     * Returns \c true if the status of self is RWDBStatus::ok, otherwise
     * returns \c false.
     */
    bool                isValid() const;

    /**
     * Returns \c true if the object is in ready state, indicating that
     * accessing the object will not block. Accessing a nonready object may
     * potentially block.
     */
    bool                isReady() const;

    /**
     * Returns the next RWDBTable in the sequence of tables represented by
     * self. When there are no more tables, the status of self becomes
     * RWDBStatus::endOfFetch. This function can behave asynchronously if
     * executed using an asynchronous connection, or if self uses an
     * asynchronous connection.
     */
    RWDBTable                table();

    /**
     * Returns self's database connection.
     */
    RWDBConnection           connection() const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 7, use
     * \ref RWDBResult::rowsAffected() const "rowsAffected()" instead.
     *
     * Returns the number of rows in the database affected by the most
     * recent activity through self's connection. This method makes a direct
     * call to the implementation. Implementations without such a call
     * return \c -1. Typically, this method returns a valid value only after
     * updating, inserting, or deleting rows. Errors always return \c -1.
     *
     * The following code determines the number of rows updated through an
     * RWDBUpdater.
     *
     * \code
     * RWDBResult myResult = myUpdater.execute();
     * long rowsUpdated = myresult.rowCount();
     * \endcode
     */
    RW_DEPRECATE_FUNC("Use RWDBResult::rowsAffected() instead")
    long                     rowCount() const;
#endif

    /**
     * Returns the number of rows in the database affected by the most
     * recent activity through self's connection. Even if the recent
     * activity has failed, this method would attempt to fetch the number of
     * rows affected in spite of the failure. Returns \c -1 if this
     * information cannot be fetched. Typically, this method returns a valid
     * value only after updating, inserting, or deleting rows.
     *
     * The following code determines the number of rows updated through an
     * RWDBUpdater.
     *
     * \code
     * RWDBResult myResult = myUpdater.execute();
     * long rowsAffected = myResult.rowsAffected();
     * \endcode
     */
    long                     rowsAffected() const;

    /**
     * Assignment operator. Self shares an implementation with \a result.
     */
    RWDBResult&              operator=(const RWDBResult& result);

private:
    RWDBCountedRef<RWDBResultImp>    impl_;
};

#endif
