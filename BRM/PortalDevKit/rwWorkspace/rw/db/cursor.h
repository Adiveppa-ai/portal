#ifndef __RWDB_CURSOR_H__
#define __RWDB_CURSOR_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/cursor.h#1 $
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
#include <rw/db/value.h>
#include <rw/tools/bustring.h>


/**
 * \ingroup db_data_manipulation_group
 * \class RWDBCursor
 *
 * \brief
 * Encapsulates a database cursor.
 *
 * RWDBCursor is an encapsulation of a database cursor. It is a relatively
 * low-level construct that maps directly onto a database cursor.
 *
 * Despite the efforts of various standards bodies, cursor capabilities vary
 * widely among database vendors. The DB Interface Module does not attempt
 * to emulate functionality that is not supported by the underlying database
 * engine. For example, if a database vendor's implementation does not
 * support scrollable cursors, an application requesting a scrollable
 * RWDBCursor from that RWDBDatabase receives an RWDBCursor with a status of
 * RWDBStatus::notSupported. The remainder of this section assumes that all
 * features are supported. See your DB Access Module guide for details
 * concerning RWDBCursor restrictions for a particular database.
 *
 * RWDBCursor captures common features of database cursors.
 *
 * Specifically:
 *
 * - There can be multiple RWDBCursor instances open on a single connection.
 * - RWDBCursor provides row-by-row access to data.
 * - RWDBCursor supports index entry and positioned deletes.
 * - RWDBCursor may be read-only or read-write.
 * - RWDBCursor may be scrollable or sequential.
 * - RWDBCursor operates on application-supplied buffers. It is
 * pointer-based rather than value-based.
 *
 * The insertion operator is used to supply an RWDBCursor with pointers to
 * application variables. When possible, RWDBCursor performs a cursor bind
 * operation directly on the pointer provided. This is always possible for
 * pointers to primitive C++ types. Otherwise, the RWDBCursor allocates
 * enough space internally to do the required type conversion, binds to its
 * internal buffers, and arranges for results to be copied into the buffers
 * supplied by the application.
 *
 * An application continues to own the memory supplied to an RWDBCursor, and
 * it is the application's responsibility to ensure that a pointer remains
 * valid for as long as the RWDBCursor requires it. The unbind() method can
 * be used to dissociate program memory from the RWDBCursor.
 *
 * RWDBCursor has a notion of the current column position within the current
 * row. Each time the cursor is advanced to a new row, the column position
 * is set to \c 0. Each insertion increments the column position by \c 1.
 * The indexing operators set the position to a specified index, column, or
 * column name. They return a reference to self, so that any of the
 * following notations may be used:
 *
 * \code
 * cursor  <<  &x;
 * cursor[i]  <<  &x;
 * cursor["columnName"]  <<  &x;
 * cursor[table["columnName"]]  <<  &x;
 * \endcode
 *
 * RWDBCursor is designed around the Interface/Implementation paradigm. An
 * RWDBCursor instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. RWDBCursor
 * implementations are base classes from which a family of database-specific
 * cursor implementations are derived.
 *
 * \synopsis
 * #include <rw/db/cursor.h>
 *
 * RWDBCursor cursor = myDbase.cursor(mySelector);
 * RWDBCursor cursor = myDbase.cursor("SQL String");
 * RWDBCursor cursor = myTable.cursor();
 * \endsynopsis
 *
 * \example
 * Assume there are database tables \c Inventory and \c Suppliers. The
 * \c Inventory table has \c partNumber, \c Supplier, and \c onHand columns;
 * the \c Suppliers table has \c Supplier and \c toOrder columns. This
 * example uses two RWDBCursor instances to examine the \c Inventory table
 * for any parts that have fewer than 10 on hand, and increment the \c order
 * column in the \c Suppliers table for each such part.
 *
 * \code
 * RWDBConnection session = myDbase.connection();
 * RWDBTable inventory = myDbase.table("Inventory");
 * RWDBTable suppliers = myDbase.table("Suppliers");
 * RWDBSelector shortage = myDbase.selector();
 * shortage << inventory;
 * RWDBSelector order = myDbase.selector();
 * order << suppliers;
 * shortage.where(inventory["onHand"] < 10);
 * RWDBCursor invCsr = shortage.cursor(session);
 *
 * int partNumber;
 * RWCString supplier;
 * int onHand;
 * int toOrder;
 * invCsr << &partNumber << &supplier << &onHand;
 * while (invCsr.fetchRow().isValid()) {
 *    order.where(suppliers["Supplier"] == supplier);
 *    session.beginTransaction();
 *    RWDBCursor ordCsr = order.cursor(session,
 *       RWDBCursor::Sequential, RWDBCursor::Write);
 *    ordCsr << &supplier << &toOrder;
 *    while (ordCsr.fetchRow().isValid()) {
 *       ++toOrder;
 *       ordCsr.updateRow(suppliers.name());
 *    }
 *    session.commitTransaction();
 * }
 * \endcode
 *
 * Assume a database table \c Parts. The \c Parts table has columns \c id,
 * \c partName, \c cost with the types \c int, \c varchar, and \c int
 * respectively. Assume an entry in the table with an \c id number and a
 * \c partName, but the \c cost was inserted as \c NULL. This example uses
 * one RWDBCursor to demonstrate how to update a row with a \c NULL value in
 * a column and set a value for that column. Note that the column being
 * updated must be \c UNSET from \c NULL for the new value to be updated in
 * the table.
 *
 * \code
 * int newCost = 0;
 * RWDBSelector select = aDB.selector();
 * select << parts["cost"];
 * select.where(parts["partName"] == "Steering Wheel");
 * select.fetchSchema(conn);
 * RWDBSchema schema = select.schema();
 * RWDBCursor cursor = select.cursor(schema, conn, RWDBCursor::Sequential, RWDBCursor::Write);
 * cursor["cost"] << &newCost;
 * if (cursor.fetchRow().isValid())
 * {
 *   newCost = 30;
 *   if(cursor.isNull(0)) {
 *     cursor.unsetNull(0);
 *   }
 *   RWDBStatus status = cursor.updateRow(parts.name());
 * }
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBCursor
{
public:

    /**
     * This \c enum holds values for cursor type.
     */
    enum CursorType {

        /**
         * A Sequential cursor can only advance to the #Next row.
         */
        Sequential,

        /**
         * A Scrolling cursor can move to the #First, #Last, #Next, or
         * #Previous row; to a row number #Relative to the current row; or
         * to an #Absolute row number.
         */
        Scrolling
    };

    /**
     * This \c enum holds values for cursor access.
     */
    enum CursorAccess {

        /**
         * A Read cursor can only be used to select data.
         */
        Read,

        /**
         * A Write cursor can also be used for updates, inserts, and
         * deletes.
         */
        Write
    };

    /**
     * The #CursorPosition is used by the fetchRow() method to identify the
     * row to be fetched. A #Scrolling cursor can fetch any row in a set of
     * result rows. A #Sequential cursor can fetch only the #Next row.
     */
    enum CursorPosition {

        /**
         * Fetches first row
         */
        First,

        /**
         * Fetches last row
         */
        Last,

        /**
         * Fetches next row
         */
        Next,

        /**
         * Fetches previous row
         */
        Previous,

        /**
         * Fetches absolute row
         */
        Absolute,

        /**
         * Fetches relative row
         */
        Relative
    };

    /**
     * The default constructor creates an RWDBCursor whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience, for example, for declaring an array of RWDBCursor
     * objects. Usable RWDBCursor objects are obtained from instances of
     * RWDBDatabase, RWDBTable, and RWDBSelector.
     */
    RWDBCursor();

    /**
     * Copy constructor. Self shares an implementation with \a csr.
     */
    RWDBCursor(const RWDBCursor& csr);

    RWDBCursor(RWDBCursorImp* impl);

    virtual ~RWDBCursor();

    // access functions

    /**
     * Returns self's name. The DB Interface Module generates a unique name
     * for every RWDBCursor. The name is used if the underlying database
     * requires cursors to be named.
     */
    RWCString       name() const;

    /**
     * Returns self's cursor type. The cursor type is specified when an
     * RWDBCursor is first obtained. The default is RWDBCursor::Sequential.
     */
    CursorType      type() const;

    /**
     * Returns self's cursor access. The cursor access is specified when an
     * RWDBCursor is first obtained. The default is RWDBCursor::Read.
     */
    CursorAccess    access() const;

    /**
     * Returns the database connection used by self. An RWDBCursor holds an
     * RWDBConnection until the RWDBCursor is destroyed. There may be more
     * than one RWDBCursor opened using the same RWDBConnection.
     */
    RWDBConnection  connection() const;

    /**
     * Returns a deep copy of self's RWDBSchema containing all column
     * information. The copy is made so that an application can modify the
     * returned RWDBSchema without changing self's schema.
     */
    RWDBSchema      schema() const;

    // error handling functions

    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, the
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
     * Returns \c true if the object is in ready state, indicating that
     * accessing the object will not block. Accessing a nonready object may
     * potentially block.
     */
    bool                isReady() const;

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                     acquire() const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                     release() const;

    // cursor functions

    /**
     * Fetches a row into self. Returns RWDBStatus::endOfFetch if there are
     * no more rows. If the cursor is associated with an asynchronous
     * connection, this function behaves asynchronously.
     *
     * If self is a #Sequential cursor, the only allowable value for
     * \a position is #Next; \a offset is ignored and the next row is
     * fetched. Returns a status of RWDBStatus::invalidUsage if position is
     * not #Next.
     *
     * If self is a #Scrolling cursor and \a position is #First, #Last,
     * #Next, or #Previous, \a offset is ignored and the specified row is
     * fetched. If self is a #Scrolling cursor and \a position is #Relative,
     * the row at the current position + \a offset is fetched. If self is a
     * #Scrolling cursor and \a position is #Absolute, the row number
     * identified by \a offset is fetched. Returns a database-specific error
     * if the specified row does not exist.
     */
    RWDBStatus      fetchRow(CursorPosition position = Next, int offset = 1);


    /**
     * Encapsulates the database-specific equivalent of:
     *
     * \c UPDATE \a tableName \c SET \e <set-clause>
     * <tt>WHERE CURRENT OF CURSOR</tt>
     *
     * where \e <set-clause> refers to the values in self that belong to
     * \a tableName. You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If the cursor is associated with an asynchronous
     * connection, this function behaves asynchronously.
     */
    RWDBStatus      updateRow(const RWCString& tableName);

    /**
     * Encapsulates the database-specific equivalent of the SQL statement:
     *
     * \c DELETE \a tableName <tt>WHERE CURRENT OF CURSOR</tt>
     *
     * You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If the cursor is associated with an asynchronous
     * connection, this function behaves asynchronously.
     */
    RWDBStatus      deleteRow(const RWCString& tableName);

    /**
     * Encapsulates the database-specific equivalent of the SQL statement:
     *
     * \c INSERT \a tableName <tt>WHERE CURRENT OF CURSOR</tt>
     *
     * You can check the return value's
     * \ref RWDBStatus::isValid() "isValid()" method to see if the operation
     * succeeded. If the cursor is associated with an asynchronous
     * connection, this function behaves asynchronously.
     */
    RWDBStatus      insertRow(const RWCString& tableName);

    /**
     * Releases all pointers to external buffers that self holds. If the
     * cursor is associated with an asynchronous connection, this function
     * behaves asynchronously.
     */
    RWDBStatus      unbind();

    /**
     * Returns \c true if the last value fetched into self at column
     * position \a index was \c NULL, otherwise returns \c false.
     */
    bool       isNull(size_t index) const;

    /**
     * Sets the value at column \a colPosition to \c NULL, so that the next
     * update or insert will make the corresponding field \c NULL.
     */
    void            setNull(size_t colPosition);

    /**
     * Unsets \c NULL from the value at column \a colPosition, so that the
     * bound-in value for this column is used on the next update or insert.
     */
    void            unsetNull(size_t colPosition);

    /**
     * The insertion operator is used to bind application variables to an
     * RWDBCursor. Each call to fetchRow() populates the application
     * variables with data from the fetch. Each call to insertRow() inserts
     * the current contents of the relevant application variables into a
     * database table. Each call to updateRow() updates a database table
     * with the current contents of the relevant application variables.
     * Returns a reference to self.
     */
    RWDBCursor&     operator<<(short* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(unsigned short* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(int* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(unsigned int* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(long* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(unsigned long* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(long long* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(unsigned long long* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(float* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(double* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(long double* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWDecimalPortable* val);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWDate* val);

    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWDateTime* val);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 13, use operator<<(RWDateTime*) instead.
     *
     * \copydoc operator<<(short*)
     */
    RW_DEPRECATE_FUNC("Use RWDBCursor::operator<<(RWDateTime*) instead")
    RWDBCursor&     operator<<(RWDBDateTime* val);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWDBDuration* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWCString* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWDBMBString* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWWString* val);
    /**
     * \copydoc operator<<(short*)
     */
    RWDBCursor&     operator<<(RWDBBlob* val);
    /**
     * \copydoc operator<<(short*)
     *
     * \note
     * This function accepts Unicode strings. For more information, see the
     * entry for RWBasicUString in <em>The Essential Tools Module Reference
     * Guide</em>. For more information on internationalization, see Chapter
     * "Internationalization" in the <em>The DB Interface Module User's
     * Guide</em>.
     */
    RWDBCursor&     operator<<(RWBasicUString* val);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 1, use
     * \ref RWDBCursor::setNull(size_t) "setNull(size_t)" instead.
     *
     * Uses the #RWDBValueManip \ref RWDBValue::rwdbNull "rwdbNull" to
     * insert a \c NULL value into a database table. Returns a reference to
     * self.
     */
    RW_DEPRECATE_FUNC("Use RWDBCursor::setNull(size_t) instead")
    RWDBCursor&     operator<<(RWDBValueManip);
#endif

    /**
     * Returns the current position, at which the next value will be shifted
     * in using the insertion operators. Returns #RW_NPOS if isValid()
     * returns \c false.
     */
    size_t position() const;

    /**
     * Changes the current row position to \a index. If \a index is out of
     * range, self's status is set to RWDBStatus::invalidPosition. Returns a
     * reference to self.
     */
    RWDBCursor&     operator[](size_t            index);

    /**
     * Changes the current row position to the index of the first column in
     * self's result set whose name matches \a colName. If there is no such
     * column, sets self's status to RWDBStatus::invalidPosition. Returns a
     * reference to self.
     */
    RWDBCursor&     operator[](const RWCString&  colName);

    /**
     * Changes the current row position to the index of the first column in
     * self's result set whose name matches the name of the given \a column.
     * If there is no such column, sets self's status to
     * RWDBStatus::invalidPosition. Returns a reference to self.
     */
    RWDBCursor&     operator[](const RWDBColumn& column);

    /**
     * Assignment operator. Self shares an implementation with \a csr.
     */
    RWDBCursor&     operator=(const RWDBCursor& csr);
private:
    RWDBCountedRef<RWDBCursorImp>  impl_;
};
#endif
