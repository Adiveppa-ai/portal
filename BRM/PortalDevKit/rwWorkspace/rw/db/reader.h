#ifndef __RWDB_READER_H__
#define __RWDB_READER_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/reader.h#1 $
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
 * Definition  of class RWDBReader
 *
 * A reader is an object used to obtain rows of data from a table.
 * Sequential access to the next row is through operator(), whereas
 * random access within the current row is through operator[].
 * Like an iterator, a reader needs to be advanced to the first row,
 * using operator() before any data can be obtained through operator>>.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/inserter.h>
#include <rw/db/mbstring.h>
#include <rw/tools/bustring.h>
#include <rw/wstring.h>

/**
 * \ingroup db_data_manipulation_group
 *
 * \brief
 * Provides row-by-row access to tabular data.
 *
 * Class RWDBReader provides row-by-row access to tabular data. RWDBReader
 * objects are produced by RWDBTable objects. When instantiated, an
 * RWDBReader is positioned before the first row of the table that produced
 * it. Subsequently, it can repeatedly advance to the next row, but can
 * never retreat. The contents of each row, however, may be accessed at
 * random. The function call operator is used to advance an RWDBReader one
 * row. Within a row, the indexing or extraction operators may be used to
 * access data.
 *
 * The RWDBReader extraction operator is used to transfer data from the
 * current row into program variables. The DB Interface Module has defined
 * extraction operator variants for all native C++ types, as well as for
 * RWCString, RWDateTime, RWDecimalPortable, and RWDBBlob. Programmers are
 * encouraged to define variants for classes in their application domain.
 *
 * RWDBReader has a notion of the current position within the current row.
 * Each time the reader is advanced to a new row, the position is set to
 * \c 0. Each extraction increments the position by \c 1. The indexing
 * operators set the position to a specified index, column, or column name;
 * they return a reference to self, so that any of the following notations
 * may be used:
 *
 * \code
 * rdr  >>  x;
 * rdr[i]  >>  x;
 * rdr["columnName"]  >>  x;
 * rdr[table["columnName"]]  >>  x;
 * \endcode
 *
 * RWDBReader is designed around the Interface/Implementation paradigm. An
 * RWDBReader instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBReader
 * implementation is a base class from which a family of database-specific
 * reader implementations is derived.
 *
 * \synopsis
 * #include <rw/db/reader.h>
 *
 * RWDBReader rdr = myTable.reader();
 * RWDBReader rdr = mySelector.reader();
 * RWDBReader rdr = myMemTable.reader();
 * \endsynopsis
 *
 * \sa
 * \parblock
 * The DB Interface Module stores the data from the database in RWDBValue
 * objects. See RWDBValue for information about conversions from table to
 * C++ types. For information about the conversion from database-specific
 * data types to RWDBValue, see <em>The DB Access Module User's Guide</em>
 * for each database.
 *
 * Applications that need to detect \c NULL values explicitly can use an
 * RWDBNullIndicator to test whether or not the next data item to be
 * extracted is \c NULL. Extracting into an RWDBNullIndicator sets the
 * indicator to \c true if the data item at the current row position is
 * \c NULL, otherwise sets it to \c false. The current row position is left
 * unchanged.
 * \endparblock
 *
 * \example
 * In this example, assume that there is a database table \c Employees, with
 * a unique integer key field \c id, text field \c name, and date field
 * \c dateOfBirth. We define an employee class, along with an operator to
 * extract an employee record from an RWDBReader, and include a constructor
 * to retrieve an employee record given an \c id.
 *
 * \code
 * class Employee
 * {
 * public:
 *     friend RWDBReader& operator>>(RWDBReader&, Employee&);
 *     Employee(const RWDBDatabase& db, int id);
 *     // etc.
 * private:
 *     int id_;
 *     RWCString name_;
 *     RWDateTime dateOfBirth_;
 * };
 *
 * RWDBReader&
 * operator>>(RWDBReader& rdr, Employee& employee)
 * {
 *     rdr >> employee.id_ >> employee.name_ >> employee.dateOfBirth_;
 *     return rdr;
 * }
 *
 * Employee::Employee(const RWDBDatabase& db, int id)
 * {
 *     RWDBSelector select = db.selector;
 *     RWDBTable employees = db.table("Employees");
 *     select << employees["id"] << employees["name"]
 *            << employees["dateOfBirth"];
 *     select.where(employees["id"] == id);
 *
 *     RWDBReader rdr = select.reader();
 *     if (!rdr()) //advance to first row and check for valid id
 *         throw("no such employee");
 *     rdr >> *this;
 * }
 * \endcode
 * \endexample
 */
class RWDB_SYMBOLIC RWDBReader
{
public:

    /**
     * The default constructor creates an RWDBReader whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience, for example, for declaring an array of RWDBReader
     * instances. Usable RWDBReader instances are obtained from a
     * RWDBSelector or RWDBTable.
     */
    RWDBReader();

    /**
     * Copy constructor. Self shares an implementation with \a reader.
     */
    RWDBReader(const RWDBReader& reader);

    RWDBReader(RWDBReaderImp* imp);

    /**
     * Assignment operator. Self shares an implementation with \a reader.
     */
    RWDBReader&         operator=(const RWDBReader& reader);

    ~RWDBReader();

    // accessors

    /**
     * Returns the result table that produced self. See RWDBResult. Each
     * result table is associated with a single reader, so multiple readers
     * cannot be obtained from the returned result table.
     */
    RWDBTable           table() const;

    /**
     * Returns the database connection used by self. An RWDBReader holds an
     * RWDBConnection until the RWDBReader is destroyed.
     */
    RWDBConnection      connection() const;

    // error handling functions

    /**
     * Installs \a errorHandler as self's error handler. The supplied
     * handler is inherited by all objects produced by self. By default an
     * RWDBReader object inherits error handler from the object that
     * produced it. This method overwrites the default.
     */
    void                     setErrorHandler(RWDBStatus::ErrorHandler errorHandler);

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

    // indexing

    /**
     * Changes the current row position to \a index. If \a index is out of
     * range, self's status is set to RWDBStatus::invalidPosition. Returns a
     * reference to self.
     */
    RWDBReader&         operator[](size_t index);

    /**
     * Interrogates self's table() for the index of the first column with
     * given \a colName, and changes the current row position to the result.
     * If there is no such column, sets self's status to
     * RWDBStatus::invalidPosition. Returns a reference to self.
     */
    RWDBReader&         operator[](const RWCString& colName);

    /**
     * Interrogates self's table() for the index of the first column whose
     * name matches the name of the given \a column, and changes the current
     * row position to the result. If there is no such column, sets self's
     * status to RWDBStatus::invalidPosition. Returns a reference to self.
     */
    RWDBReader&         operator[](const RWDBColumn& column);

    /**
     * Returns the current position, at which the next value will be shifted
     * in using the extraction operator. Returns #RW_NPOS if isValid()
     * returns false.
     */
    size_t position() const;

    // execution

    /**
     * Advances self to next row. Returns \c 0 if already at the last row,
     * otherwise returns nonzero. This function must be called once to
     * advance to the first entry in the result set. This function can
     * behave asynchronously if self is using an asynchronous connection.
     *
     * \note
     * In asynchronous mode, you must check the validity of the reader prior
     * to shifting out values from the reader.
     *
     * For example:
     *
     * \code
     * while (reader()) {
     *     if (reader.isValid()) {
     *         reader >> myint >> mychar;
     *         cout << "MyInt: " << myint
     *              << "; MyChar: " << mychar << endl;
     *     }
     * }
     * \endcode
     */
    void*               operator()();

    /**
     * If self is valid, sets \a nullIndicator to \c true if the data at the
     * current row position represents a \c NULL value, or \c false
     * otherwise. The current row position is unchanged. If self is not
     * valid, \a nullIndicator is unchanged. Returns a reference to self.
     */
    RWDBReader&         operator>>(RWDBNullIndicator& nullIndicator);

    /**
     * If self is valid and self's current row position is zero, copies each
     * value in self to the corresponding position in \a row. If self is not
     * valid, \a row is unchanged. If self's position is not zero, self's
     * status is set to RWDBStatus::invalidUsage and \a row is unchanged.
     * Returns a reference to self.
     */
    RWDBReader&         operator>>(RWDBRow& row);

    /**
     * If self is valid, deposits data from the current row position into
     * \a value and increments the current row position by one. If the data
     * at the current row position cannot be converted to the given
     * \a value's data type, changes self's status to
     * RWDBStatus::typeConversion without changing \a value. If self is not
     * valid, \a value is unchanged. Returns a reference to self.
     */
    RWDBReader&         operator>>(char& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(unsigned char& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(short& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(unsigned short& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(int& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(unsigned int& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(long& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(unsigned long& value);

    RWDBReader&         operator>>(long long& value);
    RWDBReader&         operator>>(unsigned long long& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(float& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(double& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(long double& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWDecimalPortable& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWDate& value);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWTime& value);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWDateTime& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWTimeTuple& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWTimeTupleOffset& value);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 12.5, use
     * \ref RWDBReader::operator>>(RWDateTime&) "operator>>(RWDateTime&)"
     * instead.
     *
     * \copydoc operator>>(char&)
     */
    RW_DEPRECATE_FUNC("Use RWDBReader::operator>>(RWDateTime&) instead")
    RWDBReader&         operator>>(RWDBDateTime& value);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWDBDuration& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWCString& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWDBBlob& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWDBMBString& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWBasicUString& value);

    /**
     * \copydoc operator>>(char&)
     */
    RWDBReader&         operator>>(RWWString& value);

    /**
     * If self is valid, copies data from the current row position into
     * \a value and increments the current row position by one. Otherwise
     * does not change \a value. Returns a reference to self.
     */
    RWDBReader&         operator>>(RWDBValue& value);

#if !defined(RW_TRAILING_RWEXPORT)
    /**
     * Adds the contents of the current row in \a rdr to inserter.
     */
    friend RWDB_SYMBOLIC RWDBInserter& RWDBInserter::operator<<(RWDBReader& rdr);
#else
    friend RWDBInserter& RWDB_SYMBOLIC RWDBInserter::operator<<(RWDBReader&);
#endif

private:
    RWDBCountedRef<RWDBReaderImp>      impl_;
    RWDBShiftableRow&   currentRow();
};

#endif
