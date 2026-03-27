#ifndef __RWDB_SQL_H__
#define __RWDB_SQL_H__

/*************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/osql.h#1 $
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
 * Declaration of class RWDBOSqlImp
 *
 * Provides an object that represents a bindable sql.
 *
 *************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/status.h>
#include <rw/cstring.h>
#include <rw/tpslist.h>
#include <limits.h>

/**
 * \ingroup db_open_sql_group
 * \class RWDBOSql
 *
 * \brief
 * Encapsulates a database-specific SQL statement with all its input and
 * output bindings.
 *
 * Class RWDBOSql is an encapsulation of a database-specific SQL statement
 * with all its input and output bindings. Program variables may be bound to
 * placeholders in your statement using operator<<() and shifting in
 * RWDBAbstractBuffer objects, such as RWDBTBuffer instances, which describe
 * input data. Class RWDBOSql also contains a vector of RWDBMultiRow
 * instances, each of which specifies the output bindings for a single
 * result set. You can use the RWDBOSql operator[]() to obtain a reference
 * to an RWDBMultiRow, and then use the RWDBMultiRow
 * \ref RWDBMultiRow::operator>>() "operator>>()" to provide output bindings
 * for the RWDBMultiRow.
 *
 * When executing an RWDBOSql that produces results, there are two options
 * for specifying the output RWDBAbstractBuffer objects for those results:
 *
 * - <b>If the format of the results is known</b> when creating the query,
 * RWDBOSql may gain performance if output RWDBAbstractBuffer instances are
 * bound to the result set before invoking execute(). However, binding
 * output RWDBAbstractBuffer instances before invoking execute() is not
 * required.
 * - <b>If the existence or format of the results is unknown</b> -- for
 * example, if you are entering ad hoc queries -- you would do the
 * following:
 *    - Execute the RWDBOSql, and use methods such as hasResult() and
 *    schema() to discover the number and size of the result sets.
 *    - Bind RWDBAbstractBuffer instances, such as a RWDBTBuffer object, to
 *    the result sets using the RWDBOSql operator[]() and the RWDBMultiRow
 *    \ref RWDBMultiRow::operator>>() "operator>>()".
 *    - Invoke fetch() to begin fetching results.
 *
 * RWDBOSql is designed around the Interface/Implementation paradigm. An
 * RWDBOSql instance is an interface to a reference-counted implementation.
 * Copy constructors and assignment operators produce additional references
 * to a shared implementation.
 *
 * \synopsis
 * #include <rw/db/osql.h>
 *
 * RWDBOSql aQuery;
 * RWDBOSql aQuery("select * from myTable");
 * \endsynopsis
 *
 * \example
 * <b>Example 1</b>
 *
 * In this example, we use an RWDBOSql to execute a query with a
 * placeholder. The input value and output storage are both specified using
 * RWDBTBuffer. Please note that Oracle-specific placeholder syntax is used
 * here; check your access module guide or vendor documentation for
 * appropriate SQL and placeholder syntax.
 *
 * \code
 * // Grab a connection from our database
 * RWDBConnection aConn = aDB.connection();
 *
 * // Create the statement
 * RWDBOSql myQuery("SELECT TITLE,
 *                 TEMPO FROM SONGS WHERE KEY=:phKey");
 *
 * // Bind in data
 * RWCString key;
 * RWDBTBuffer<RWCString> keyBinding(&key, 1);
 * myQuery << keyBinding;
 *
 * // Set the query data; we're looking for songs in Bb
 * key = "Bb";
 *
 * // Execute the query
 * myQuery.execute(aConn);
 *
 * // Fetch and print results
 * if( myQuery.isValid() ) {
 *   RWDBTBuffer<RWCString> titles(10);
 *   RWDBTBuffer<unsigned>  tempos(10);
 *   // Bind result buffers to 0th result set
 *   myQuery[0] >> titles >> tempos;
 *   // Fetch data
 *   while(myQuery.fetch(), myQuery.rowsFetched() > 0) {
 *       // Print the rows that were fetched
 *       for(int i=0; i<myQuery.rowsFetched(); i++ ) {
 *           cout << "Song Title: " << titles[i]
 *                << " Tempo: " << tempos[i] << endl;
 *       }
 *   }
 * }
 * else
 * {
 *   // An error
 *   cout << "Error occurred: "
 *        << myQuery.status().message()
 *        << endl;
 * }
 * \endcode
 *
 * <b>Example 2</b>
 *
 * In this example, we use an RWDBOSql to execute a user-supplied ad hoc
 * query. We then use an RWDBMultiRow to fetch the results.
 *
 * \code
 * // Utility function to print an RWDBRow
 * void outputRow(ostream &o, RWDBRow &r)
 * {
 *    for(int i = 0; i < r.entries(); i++) {
 *        if(i>0) cout << `\t';
 *        RWDBValue theField = r[i];
 *        cout << theField.asString();
 *    }
 *    cout << endl;
 * }
 *
 * // This function is called by the user interface
 * void executeAndDisplayResults(RWDBConnection &c,
 *                              const RWCString &query)
 * {
 *    // Create an RWDBOSql for the query
 *    RWDBOSql osql(query);
 *
 *    // Execute the RWDBOSql
 *    // No error checking performed here for simplicity
 *    osql.execute(c);
 *
 *    // We'll use RWDBMultiRow to automatically create
 *    // RWDBTBuffers for us from the schema of the results.
 *    // The `1' indicates a one-row MultiRow  --  each
 *    // RWDBTBuffer created will have one entry.
 *    RWDBMultiRow outputBuffers( osql.schema(), 1 );
 *
 *    // Bind the MultiRow to the 0th result set
 *    osql[0] = outputBuffers;
 *
 *    // Fetch and output the results
 *    while( osql.fetch(), osql.rowsFetched() > 0 ) {
 *        // Create an RWDBRow from the 0th row in the
 *        // output buffers. Since we fetch only one row
 *        // at a time,the row is always placed
 *        // in the 0th row of the RWDBMultiRow.
 *        RWDBRow aRow = outputBuffers[0];
 *
 *        // Print out the row we fetched
 *        outputRow(cout, aRow);
 *    }
 * }
 * \endcode
 *
 * <b>Example 3</b>
 *
 * In this example, we use an RWDBOSql to execute a stored procedure that
 * has one input and output parameter each. The input value and output
 * storage are both specified using RWDBTBuffer. Please note that Oracle-
 * specific placeholder syntax is used here; check your access module guide
 * or vendor-specific documentation for appropriate SQL and placeholder
 * syntax.
 *
 * \code
 * // Grab a connection from our database
 * RWDBConnection aConn = aDB.connection();
 *
 * // Create an RWDBOSql for the query
 * RWDBOSql osql("BEGIN testProc( :ph1, :ph2 ); END;",
 *                RWDBOSql::Procedure);
 *
 * // create a buffer for the input parameter
 * RWCString str = "aStringValue";
 * RWDBTBuffer<RWCString> input(1);
 * input[0] = str;
 *
 * // create a buffer for the output parameter
 * // and set the parameter type
 * RWDBTBuffer<RWCString> output(1);
 * output.paramType(RWDBColumn::outParameter);
 *
 * // Bind the buffers
 * osql << input << output;
 *
 * // execute and fetch the output parameter
 * osql.execute(aConn);
 * osql.fetchReturnParams();
 * cout << "output parameter value is: " << output[0] << endl;
 * \endcode
 * \endexample
 */
class RWDB_SYMBOLIC RWDBOSql
{
public:

    /**
     * A class-scoped enum containing all the statement identifications
     * understood by open SQL.
     */
    enum StatementType {

        /**
         * Statement is non query type.
         */
        NonQuery = 0,

        /**
         * Statement is a query.
         */
        Query,

        /**
         * Statement is a stored procedure.
         */
        Procedure
    };

    /**
     * A class-scoped enum containing the statement cancel types understood
     * by RWDBOSql. Please refer to the method RWDBOSql::cancel() for usage
     * information.
     */
    enum CancelType {

        /**
         * Current.
         */
        Current = 0,

        /**
         * All.
         */
        All
    };

    /**
     * Default constructor. Creates an RWDBOSql object with statement type
     * RWDBOSql::NonQuery and no statement set. Its error handler is set to
     * the error handler of the static RWDBManager.
     */
    RWDBOSql();

    /**
     * Creates an RWDBOSql with SQL statement set to \a sql, and statement
     * type set to \a type. The statement type communicates to the access
     * module the kind of query inside the statement. This information is
     * used to help optimize binding and performance. The error handler for
     * the created object is set to the error handler of the static
     * RWDBManager, as in the default constructor.
     */
    RWDBOSql(const RWCString& sql, StatementType type = NonQuery);

    RWDBOSql(RWDBOSqlImp* imp);

    /**
     * Creates an RWDBOSql whose implementation is shared with \a osql. All
     * attributes are shared, including statement, status, and bindings.
     */
    RWDBOSql(const RWDBOSql& osql);

    /**
     * Assignment operator. Causes self's current implementation to be
     * discarded, including its SQL statement, bindings, state, status, and
     * any other attributes. Self then shares \a osql's implementation.
     */
    RWDBOSql&           operator=(const RWDBOSql& osql);

    /**
     * Cleans up the RWDBOSql implementation if it is the last RWDBOSql to
     * reference that implementation, consistent with standard
     * Interface/Implementation destructor behavior. Blocks if an
     * asynchronous operation has not completed. If blocking is \e not
     * desired, call to cancel the asynchronous operation before the
     * RWDBOSql is destroyed.
     */
    ~RWDBOSql();

    /**
     * Sets the statement to \a sql, and the statement type to \a type. All
     * pending queries are canceled. All bindings are cleared. Any error set
     * on the RWDBOSql is cleared.
     */
    RWDBOSql&           statement(const RWCString& sql, StatementType type = NonQuery);

    /**
     * Returns the current SQL statement by value. If no statement is set,
     * returns an empty string (\c "").
     */
    RWCString           statement() const;

    /**
     * Returns the statement type of the RWDBOSql. #StatementType is a
     * class-scoped enum containing all the statement identifications
     * understood by open SQL.
     */
    StatementType       type() const;

    //Binding related methods:

    /**
     * Sets an input binding on the current binding location. Advances the
     * current binding location internally by one, so that the next call to
     * operator<<() binds the next binding location. Returns a reference to
     * self.
     */
    RWDBOSql&           operator<<(RWDBAbstractBuffer& input);

    /**
     * \copydoc operator<<(RWDBAbstractBuffer&)
     */
    RWDBOSql&           operator<<(RWDBDataCallback& input);

    /**
     * Returns a reference to the RWDBMultiRow that stores all the output
     * bindings for the \a index <sup>th</sup> result set.
     */
    RWDBMultiRow&       operator[](size_t index);

    //Execution related methods:

    /**
     * Executes the SQL statement on \a cn. If \a blkSz is nonzero, \a blkSz
     * rows are sent to the server from the input bindings. If \a blkSz is
     * zero, the number of rows sent is determined by the minimum of the
     * lengths of all input-bound buffers.
     */
    void                execute(const RWDBConnection& cn, size_t blkSz = 0);

    void                execute(const RWDBHandle& cn, size_t blkSz = 0);
    void                executeNoDescribe(const RWDBConnection& cn, size_t blkSz = 0);
    void                executeNoDescribe(const RWDBHandle& cn, size_t blkSz = 0);

    /**
     * Returns \c true if there is data waiting to be fetched. Also returns
     * \c true if all the data has been fetched, but the end-of-fetch has
     * not yet been encountered. If no attempt is made to read past the end
     * of the result set that was fetched, hasResult() still returns
     * \c true.
     */
    bool                hasResult() const;

    /**
     * Returns the schema for the current result set, if the statement has
     * been executed and has results. Returns an empty schema otherwise.
     * This method is useful when the format of results are unknown, as is
     * the case when using ad hoc queries.
     */
    RWDBSchema          schema() const;

    /**
     * Fetches the current result set into the output bindings for that
     * result set, and returns a reference to self. If the current result
     * set has been completely fetched no rows are fetched, and the next
     * call to fetch() moves to the next result set and fetches. The member
     * function fetch() returns at most \c n rows at a time, where \c n is
     * the minimum of the lengths of the output-bound RWDBTBuffer instances
     * for the current result set. After calling fetch(), use rowsFetched()
     * to determine how many rows were fetched.
     *
     * \note
     * This call is valid only after the RWDBOSql is executed. Calling
     * fetch() before execute() invalidates the RWDBOSql, setting an
     * RWDBStatus::invalidUsage error, and calling any associated error
     * handler.
     */
    RWDBOSql&           fetch();

    /**
     * Attempts to cancel the pending result set, or current statement
     * execution. The exact definition is vendor-dependent; see your access
     * module guide for details.
     *
     * \note
     * This call is valid only after the RWDBOSql is executed. Calling
     * cancel() before execute() invalidates the RWDBOSql, setting an
     * RWDBStatus::invalidUsage error, and calling any associated error
     * handler.
     */
    RWDBOSql&           cancel(CancelType tp);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 7, use
     * \ref RWDBOSql::rowsAffected() const "rowsAffected()" instead.
     *
     * Returns the number of rows affected by the last execute(), if
     * available. Returns \c -1 if this information is unavailable.
     */
    RW_DEPRECATE_FUNC("Use RWDBOsql::rowsAffected() instead")
    long                rowCount() const;
#endif

    /**
     * Returns the number of rows in the database affected by the most
     * recent activity on self. Even if the recent activity has failed, this
     * method would attempt to fetch the number of rows affected in spite of
     * the failure. Returns \c -1 if this information cannot be fetched.
     * Typically, this method only returns a valid value after updating,
     * inserting, or deleting rows.
     */
    long                rowsAffected() const;

    /**
     * Returns the number of rows fetched in the last fetch() operation.
     * Blocks if the fetch() was asynchronous and has not yet completed.
     * Returns \c -1 if no fetch was performed.
     */
    long                rowsFetched() const;

    /**
     * Fetches any in/out or out-type stored procedure parameters into the
     * bound buffers for those parameters. Returns a reference to self.
     */
    RWDBOSql&           fetchReturnParams();

    /**
     * Obtains and returns the stored procedure return value, if one exists.
     * If no return value exists, or a stored procedure has \e not been
     * executed, returns an RWDBValue whose type is RWDBValue::NoType.
     */
    RWDBValue           returnValue() const;

    //Status related methods:

    /**
     * Returns \c true if the object is in ready state, indicating that
     * accessing the object will not block. Accessing a nonready object may
     * potentially block.
     */
    bool                isReady() const;

    /**
     * Returns \c true if the RWDBOSql is not in an error condition. This
     * call blocks if the last operation on this RWDBOSql is not yet
     * completed.
     */
    bool                isValid() const;

    /**
     * Returns the status of self.
     */
    RWDBStatus          status() const;

    void                status(const RWDBStatus& s);

    /**
     * Installs \a err as self's error handler.
     */
    void                setErrorHandler(RWDBStatus::ErrorHandler err);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    static RWDBOSql&    uninitialized();

private:
    RWDBCountedRef<RWDBOSqlImp> impl_;

    friend RWDBOSqlImp* getImp(const RWDBOSql& osql)
    {
        return osql.impl_;
    }
};


#endif
