#ifndef __RWDB_DATACB_H__
#define __RWDB_DATACB_H__
/*************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/datacb.h#1 $
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
#include <rw/db/buffer.h>
#include <rw/db/coretypes.h>
#include <rw/tools/uchar.h>
#include <rw/tvordvec.h>

/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Base class for user-defined callbacks.
 *
 * RWDBDataCallback is an abstract base class for the encapsulation of
 * user-defined data callbacks. Derive from one of the type-specific classes
 * RWDBCharCallback, RWDBUChar16Callback, or RWDBBinaryCallback to implement
 * new callback instances.
 *
 * \synopsis
 * #include <rw/db/datacb.h>
 * \endsynopsis
 *
 * \example
 * In this example, we define a data callback to insert and fetch data. The
 * program will create a test table with one column of a LOB character type.
 * It will then execute an INSERT statement to insert 10 rows of data and
 * then execute a SELECT statement to read the rows that were inserted.
 * \code
 * #include <rw/db/db.h>
 * #include <rw/db/tbuffer.h>
 * #include <rw/db/datacb.h>
 *
 * using namespace std;
 *
 * const size_t LENGTH = 20000;
 * const size_t PIECES = 3;
 *
 * class MyCallback : public RWDBCharCallback
 * {
 * public:
 *   MyCallback(size_t rowsetSize) : RWDBCharCallback(rowsetSize), offset(0)
 *   { }
 *
 *   virtual ~MyCallback() { }
 *
 *   bool onFetch(size_t rownum, const char* theData, size_t length,
 *                RWDBNullIndicator ni, bool& lastPiece)
 *   {
 *     cout << endl << "Row in rowset is: " << rownum << endl;
 *     cout << "Row in result set is: " << (rownum + offset) << endl;
 *
 *     if (ni) {
 *       cout << "Read a null" << endl;
 *     }
 *     else if (lastPiece) {
 *       cout << "Read a piece of data of length " << length << endl;
 *       cout << "Received the last piece of data for row " << rownum << endl;
 *     }
 *     else {
 *       cout << "Read a piece of data of length " << length << endl;
 *     }
 *
 *     return true;
 *   }
 *
 *   bool onSend(size_t rownum, char* theData, size_t& length,
 *               RWDBNullIndicator& ni, bool& lastPiece)
 *   {
 *     static size_t piecesSent = 0;
 *     static RWCString tmp('a', LENGTH);
 *
 *     // populate the array, theData, with the data we're inserting
 *     length = LENGTH;
 *     memcpy((void*)theData, tmp.data(), LENGTH);
 *
 *     // keep track of how many pieces for this row have been sent
 *     ++piecesSent;
 *
 *     // if this is the 3rd piece it will be the last one for this value
 *     if (piecesSent == PIECES) {
 *       lastPiece = true;
 *       piecesSent = 0;
 *     }
 *
 *     return true;
 *   }
 *
 *   // We may or may not need to return the length of the data we're sending.
 *   // This depends on the Access Module in use.
 *   size_t getLength(size_t rownum) const
 *   {
 *     return LENGTH * PIECES;
 *   }
 *
 *   // We keep a row offset when fetching data as some vendors will only
 *   // return 1 row on each call to RWDBOSql::fetch(). We use this to count
 *   // the total number of rows that are fetched from the SELECT query.
 *   void addToRowOffset(size_t rowsFetched)
 *   {
 *     offset += rowsFetched;
 *   }
 *
 *   // Set the row offset value to newValue.
 *   void setOffset(size_t newValue)
 *   {
 *     offset = newValue;
 *   }
 *
 * private:
 *    size_t offset;
 * };
 *
 * int main()
 * {
 *   RWDBDatabase db = RWDBManager::database("msq8015d.dll", "SQL SERVER DB",
 *                                           "username", "password", "DB");
 *
 *   RWDBConnection cn = aDatabase.connection();
 *   RWCString tableName("myTestTable");
 *   RWDBTable tbl = db.table(tableName);
 *   // Create the table if needed. If it already exists delete the rows.
 *   if (!tbl.exists()) {
 *     RWDBSchema sch;
 *     sch.appendColumn("col1", RWDBValue::String, INT_MAX);
 *     db.createTable("myTestTable", sch);
 *   }
 *   else {
 *     RWDBDeleter del = tbl.deleter();
 *     del.execute(cn);
 *   }
 *
 *   // Declare a data callback. Set the entries to 5. This will be
 *   // the maximum number of rows that can be fetched on each call to
 *   // RWDBOSql::fetch() or the maximum number of rows that will be sent
 *   // on the call to RWDBOSql::execute().
 *   MyCallback cbin(5);
 *
 *   RWDBOSql sql("insert into " + tableName + " values(?)");
 *   sql << cbin;
 *
 *   // Execute the insert statement.
 *   // MyCallback::onSend(..) will be called as many times as needed
 *   // to insert 5 rows of data. Note that the method MyCallback::getLength()
 *   // may or may not be needed. If needed, it will be called once for each
 *   // row being sent just before onSend() is called for the row.
 *   sql.execute(cn);
 *
 *   // Check if the insert succeeded or not.
 *   if (sql.isValid()) {
 *     cout << "inserted 5 rows" << endl;
 *   }
 *   else {
 *     cout << "inserting rows failed" << endl;
 *   }
 *
 *   // Insert another 5 rows.
 *   sql.execute(cn);
 *   if (sql.isValid()) {
 *     cout << "inserted another 5 rows" << endl;
 *   }
 *   else {
 *     cout << "inserting another 5 rows failed" << endl;
 *   }
 *
 *   // Declare a callback to fetch data. It can accommodate a maximum
 *   // of 3 rows of data on each call to RWDBOSql::fetch().
 *   MyCallback cbout(3);
 *
 *   sql.statement("select * from " + tableName);
 *   // Execute the statement.
 *   sql.execute(cn);
 *
 *   // Check if execution succeeded or failed.
 *   if (sql.isValid()) {
 *     // Bind the callback buffer to the 0th result set.
 *     sql[0] >> cbout;
 *
 *     // Fetch the rows. Note that each call to sql.fetch() will fetch
 *     // a maximum of 3 rows - the size specified in the constructor
 *     // of RWDBCharCallback.
 *     while (sql.fetch(), sql.rowsFetched() > 0) {
 *       // Use this so the callback can keep track of the total
 *       // number of rows fetched from executing the SELECT statement.
 *       cbout.addToRowOffset(sql.rowsFetched());
 *     }
 *   }
 *
 *   return 0;
 * }
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBDataCallback
{
public:

    /**
     * \internal
     * Constructor. Virtual base class for data callbacks.
     */
    RWDBDataCallback(const RWDBCType& typeInfo, size_t entries = 1)
        : entries_(entries), typeInfo_(typeInfo)
    {
    }

    /**
     * \internal
     * Copy constructor.
     */
    RWDBDataCallback(const RWDBDataCallback& cb)
        : entries_(cb.entries_), typeInfo_(cb.typeInfo_)
    {
    }

    /**
     * \internal
     * Assignment operator.
     */
    RWDBDataCallback& operator=(const RWDBDataCallback& cb)
    {
        if (this == &cb) {
            return *this;
        }

        entries_ = cb.entries_;
        typeInfo_ = cb.typeInfo_;
        return *this;
    }

    /**
     * \internal
     * Virtual destructor.
     */
    virtual ~RWDBDataCallback()
    {
    }

    /**
     * Returns the number of entries. The number of entries refers to the
     * maximum size of the rowset that can be used with this callback. It is
     * equivalent to the entries in RWDBTBuffer. Please see the class
     * reference for RWDBOSql and the section "Using the Open SQL Classes"
     * of the <em>DB Interface Module User's Guide</em> for more
     * information.
     */
    size_t entries() const
    {
        return entries_;
    }

    /**
     * \internal
     * Returns the RWDBCType of this buffer.
     */
    RWDBCType typeInfo() const
    {
        return typeInfo_;
    }

    /**
     * Returns the length of the data that will be sent for the row
     * \a rownum. Whether this value is needed depends on the database
     * vendor. Please see the Access Module User's Guide for your database
     * to make this determination. This method must be overridden in the
     * derived class if the length of the data is needed.
     */
    virtual size_t getLength(size_t rownum) const
    {
        RW_UNUSED(rownum);
        return 0;
    }

    /**
     * \internal
     */
    virtual RWDBValue::ValueType valueType() const = 0;

private:
    size_t entries_;
    RWDBCType typeInfo_;
};


/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Base class for user-defined callback methods that fetch and send
 * character data.
 *
 * RWDBCharCallback is a base class for user-defined callback methods for
 * character data. Derive from this class to implement the callback methods
 * to send and retrieve data.
 *
 * \example
 * Please see the example in the entry for RWDBDataCallback.
 * \endexample
 */
class RWDB_GLOBAL RWDBCharCallback : public RWDBDataCallback
{
public:
    /**
     * Constructs an RWDBCharCallback with entries \a entries. If \a entries
     * is more than one, array binding is in effect. Please see the <em>DB
     * Interface Module User's Guide</em> chapter "Bulk/Array Input", in the
     * section "Using the Open SQL Classes", for more information.
     */
    RWDBCharCallback(size_t entries = 1)
        : RWDBDataCallback(RWDBCType(RWDB_TYPE_CHAR_CALLBACK, sizeof(char)), entries)
    { }

    /**
     * Copy constructor.
     */
    RWDBCharCallback(const RWDBCharCallback& cb)
        : RWDBDataCallback(cb)
    {}

    /**
     * Assignment operator.
     */
    RWDBCharCallback& operator=(const RWDBCharCallback& cb)
    {
        RWDBDataCallback::operator=(cb);
        return *this;
    }

    /**
     * Virtual destructor.
     */
    virtual ~RWDBCharCallback() {}

    /**
     * When data callback classes are bound to a SQL statement and
     * RWDBOSql::fetch() is called to fetch the results, this method is
     * invoked to receive the data.
     *
     * \param rownum
     * The row in the current rowset this data is from (0-based indexing).
     * Each call to RWDBOSql::fetch() retrieves the next rowset from the
     * result set of the SQL statement execution. This method is invoked by
     * the Access Module as many times as needed for each row in the rowset.
     *
     * \param theData
     * A pointer to an array containing the fetched data. The contents of
     * \a theData are undefined if \a ni is true.
     *
     * \param byteLength
     * The length in bytes of the data in \a theData, if any.
     *
     * \param ni
     * The null indicator parameter. \c true if the fetched value is null,
     * \c false otherwise.
     *
     * \param lastPiece
     * \c true if this is the last piece of data for this value, otherwise
     * it is \c false. This parameter can be set to \c true by the callee to
     * stop fetching data for this row's value and to move to the next row.
     *
     * \return
     * Return \c false or throw an exception from this method to stop
     * fetching data and terminate the operation, otherwise return \c true
     * to continue.
     */
    virtual bool onFetch(size_t rownum, const char* theData, size_t byteLength,
                         RWDBNullIndicator ni, bool& lastPiece) = 0;

    /**
     * When data callback classes are bound to a SQL statement and
     * RWDBOSql::execute() is called to execute the statement, this method
     * is invoked as needed to supply the data to send to the database. Note
     * that the method RWDBDataCallback::getLength() may need to be be
     * implemented in the derived class to send data to the database.
     *
     * \param rownum
     * The row for which data is needed (0-based indexing). This will always
     * be 0 unless array binding is used. Array binding is in effect when
     * the callback is constructed with \a entries greater than 1. Please
     * see the <em>DB Interface Module User's Guide</em> chapter "Bulk/Array
     * Input", in the section "Using the Open SQL Classes", for more
     * information.
     *
     * \param theData
     * A pointer to an array where the callee should put the data to be
     * sent. If \a ni is \c true this parameter is ignored.
     *
     * \param byteLength
     * The size of \a theData in bytes and should be set by the callee to
     * the length in bytes written to \a theData. If \a ni is \c true this
     * parameter is ignored.
     *
     * \param ni
     * Set this to \c true to indicate that a null value is being sent to
     * the database. If \a ni is \c true, \a theData, \a lastPiece, and
     * \a byteLength are ignored.
     *
     * \param lastPiece
     * When the last piece of data for \a rownum is being supplied this must
     * be set to \c true. This parameter is ignored if \a ni is \c true.
     *
     * \return
     * Return \c false or throw an exception to stop sending data and
     * terminate the operation, otherwise return \c true.
     */
    virtual bool onSend(size_t rownum, char* theData, size_t& byteLength,
                        RWDBNullIndicator& ni, bool& lastPiece) = 0;

    // overridden from the base class
    RWDBValue::ValueType valueType() const
    {
        return RWDBValue::String;
    }

};


/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Base class for user-defined callback methods that fetch and send binary
 * data.
 *
 * RWDBBinaryCallback is a base class for user-defined callback methods for
 * binary data. Derive from this class to implement the callback methods to
 * send and retrieve binary data.
 *
 * \example
 * Please see the example in the entry for RWDBDataCallback.
 * \endexample
 */
class RWDB_GLOBAL RWDBBinaryCallback : public RWDBDataCallback
{
public:
    /**
     * Constructs an RWDBBinaryCallback with entries \a entries. If
     * \a entries is more than one, array binding is in effect. Please see
     * the <em>DB Interface Module User's Guide</em> chapter "Bulk/Array
     * Input", in the section "Using the Open SQL Classes", for more
     * information.
     */
    RWDBBinaryCallback(size_t entries = 1)
        : RWDBDataCallback(RWDBCType(RWDB_TYPE_BINARY_CALLBACK,
                                     sizeof(unsigned char)), entries)
    { }

    /**
     * Copy constructor.
     */
    RWDBBinaryCallback(const RWDBBinaryCallback& cb)
        : RWDBDataCallback(cb)
    {}

    /**
     * Assignment operator.
     */
    RWDBBinaryCallback& operator=(const RWDBBinaryCallback& cb)
    {
        RWDBDataCallback::operator=(cb);
        return *this;
    }

    /**
     * Virtual destructor.
     */
    virtual ~RWDBBinaryCallback() {}

    /**
     * When data callback classes are bound to a SQL statement and
     * RWDBOSql::fetch() is called to fetch the results, this method is
     * invoked to receive the data.
     *
     * \param rownum
     * The row in the current rowset this data is from (0-based indexing).
     * Each call to RWDBOSql::fetch() retrieves the next rowset from the
     * result set of the SQL statement execution. This method is invoked by
     * the Access Module as many times as needed for each row in the rowset.
     *
     * \param theData
     * A pointer to an array containing the fetched data. The contents of
     * \a theData are undefined if \a ni is true.
     *
     * \param byteLength
     * The length in bytes of the data in \a theData, if any.
     *
     * \param ni
     * The null indicator parameter. \c true if the fetched value is null,
     * \c false otherwise.
     *
     * \param lastPiece
     * \c true if this is the last piece of data for this value, otherwise
     * it is \c false. This parameter can be set to \c true by the callee to
     * stop fetching data for this row's value and to move to the next row.
     *
     * \return
     * Return \c false or throw an exception from this method to stop
     * fetching data and terminate the operation, otherwise return \c true
     * to continue.
     */
    virtual bool onFetch(size_t rownum, const void* theData, size_t byteLength,
                         RWDBNullIndicator ni, bool& lastPiece) = 0;

    /**
     * When data callback classes are bound to a SQL statement and
     * RWDBOSql::execute() is called to execute the statement this method is
     * invoked as needed to supply the data to send to the database. Note
     * that the method RWDBDataCallback::getLength() may need to be be
     * implemented in the derived class to send data to the database.
     *
     * \param rownum
     * The row for which data is needed (0-based indexing). This will always
     * be 0 unless array binding is used. Array binding is in effect when
     * the callback is constructed with \a entries greater than 1. Please
     * see the <em>DB Interface Module User's Guide</em> chapter "Bulk/Array
     * Input", in the section "Using the Open SQL Classes", for more
     * information.
     *
     * \param theData
     * A pointer to an array where the callee should put the data to be
     * sent. If \a ni is \c true this parameter is ignored.
     *
     * \param byteLength
     * The size of \a theData in bytes and should be set by the callee to
     * the length in bytes written to \a theData. If \a ni is \c true this
     * parameter is ignored.
     *
     * \param ni
     * Set this to \c true to indicate that a null value is being sent to
     * the database. If \a ni is \c true, \a theData, \a lastPiece, and
     * \a byteLength are ignored.
     *
     * \param lastPiece
     * When the last piece of data for \a rownum is being supplied this must
     * be set to \c true. This parameter is ignored if \a ni is \c true.
     *
     * \return
     * Return \c false or throw an exception to stop sending data and
     * terminate the operation, otherwise return \c true.
     */
    virtual bool onSend(size_t rownum, void* theData, size_t& byteLength,
                        RWDBNullIndicator& ni, bool& lastPiece) = 0;

    // overridden from the base class
    RWDBValue::ValueType valueType() const
    {
        return RWDBValue::Blob;
    }
};


/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Base class for user-defined callbacks that fetch and send UTF-16
 * character data.
 *
 * RWDBUChar16Callback is a base class for user-defined callback methods for
 * UTF-16 character data. Derive from this class to implement the callback
 * methods to send and retrieve data.
 *
 * \example
 * Please see the example in the entry for RWDBDataCallback.
 * \endexample
 */
class RWDB_GLOBAL RWDBUChar16Callback : public RWDBDataCallback
{
public:
    /**
     * Constructs an RWDBUChar16Callback with entries \a entries. If
     * \a entries is more than one, array binding is in effect. Please see
     * the <em>DB Interface Module User's Guide</em> chapter "Bulk/Array
     * Input", in the section "Using the Open SQL Classes", for more
     * information.
     */
    RWDBUChar16Callback(size_t entries = 1)
        : RWDBDataCallback(RWDBCType(RWDB_TYPE_UCHAR16_CALLBACK, sizeof(RWUChar16)), entries)
    {}

    /**
     * Virtual destructor.
     */
    virtual ~RWDBUChar16Callback() {}

    /**
     * Copy constructor.
     */
    RWDBUChar16Callback(const RWDBUChar16Callback& cb)
        : RWDBDataCallback(cb)
    {}

    /**
     * Assignment operator.
     */
    RWDBUChar16Callback& operator=(const RWDBUChar16Callback& cb)
    {
        RWDBDataCallback::operator=(cb);
        return *this;
    }

    /**
     * When data callback classes are bound to a SQL statement and
     * RWDBOSql::fetch() is called to fetch the results, this method is
     * invoked to receive the data.
     *
     * \param rownum
     * The row in the current rowset this data is from (0-based indexing).
     * Each call to RWDBOSql::fetch() retrieves the next rowset from the
     * result set of the SQL statement execution. This method is invoked by
     * the Access Module as many times as needed for each row in the rowset.
     *
     * \param theData
     * A pointer to an array containing the fetched data. The contents of
     * \a theData are undefined if \a ni is true.
     *
     * \param charLength
     * The length in characters of the data in \a theData, if any.
     *
     * \param ni
     * The null indicator parameter. \c true if the fetched value is null,
     * \c false otherwise.
     *
     * \param lastPiece
     * \c true if this is the last piece of data for this value, otherwise
     * it is \c false. This parameter can be set to \c true by the callee to
     * stop fetching data for this row's value and to move to the next row.
     *
     * \return
     * Return \c false or throw an exception from this method to stop
     * fetching data and terminate the operation, otherwise return \c true
     * to continue.
     */
    virtual bool onFetch(size_t rownum, const RWUChar16* theData, size_t charLength,
                         RWDBNullIndicator ni, bool& lastPiece) = 0;

    /**
     * When data callback classes are bound to a SQL statement and
     * RWDBOSql::execute() is called to execute the statement, this method
     * is invoked as needed to supply the data to send to the database. Note
     * that the method RWDBDataCallback::getLength() may need to be be
     * implemented in the derived class to send data to the database.
     *
     * \param rownum
     * The row for which data is needed (0-based indexing). This will always
     * be 0 unless array binding is used. Array binding is in effect when
     * the callback is constructed with \a entries greater than 1. Please
     * see the <em>DB Interface Module User's Guide</em> chapter "Bulk/Array
     * Input", in the section "Using the Open SQL Classes", for more
     * information.
     *
     * \param theData
     * A pointer to an array where the callee should put the data to be
     * sent. If \a ni is \c true this parameter is ignored.
     *
     * \param charLength
     * The size of \a theData in characters and should be set by the callee
     * to the length in characters written to \a theData. If \a ni is
     * \c true this parameter is ignored.
     *
     * \param ni
     * Set this to \c true to indicate that a null value is being sent to
     * the database. If \a ni is \c true, \a theData, \a charLength, and
     * \a lastPiece are ignored.
     *
     * \param lastPiece
     * When the last piece of data for \a rownum is being supplied this must
     * be set to \c true. This parameter is ignored if \a ni is \c true.
     *
     * \return
     * Return \c false or throw an exception to stop sending data and
     * terminate the operation, otherwise return \c true.
     */
    virtual bool onSend(size_t rownum, RWUChar16* theData, size_t& charLength,
                        RWDBNullIndicator& ni, bool& lastPiece) = 0;

    // overridden from the base class
    RWDBValue::ValueType valueType() const
    {
        return RWDBValue::UString;
    }
};

#endif
