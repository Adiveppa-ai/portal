#ifndef __RWDB_BKINS_H__
#define __RWDB_BKINS_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/bkins.h#1 $
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
 *  RWDBBulkInserter
 *
 **************************************************************************/

#include <rw/db/dbref.h>

/**
 * \ingroup db_bulk_operations_group
 *
 * \brief
 * Used to insert an RWDBTBuffer array into a database table. (To insert
 * scalar values, use RWDBInserter.)
 *
 * Like RWDBInserter, RWDBBulkInserter is a class designed to insert data
 * into database tables. The main difference between RWDBBulkInserter and
 * RWDBInserter is that \e arrays of values are shifted into
 * RWDBBulkInserter for each column in the table, while \e scalar values are
 * shifted into RWDBInserter. These arrays are passed by reference and need
 * to stay in scope for the duration of the inserter. The class RWDBTBuffer
 * is used for inserting all types of data, including numeric types, dates,
 * strings and binary data.
 *
 * RWDBBulkInserter is designed around the Interface/Implementation
 * paradigm. An RWDBBulkInserter instance is an interface to a
 * reference-counted implementation; copy constructors and assignment
 * operators produce additional references to a shared implementation. An
 * RWDBBulkInserter implementation is a base class from which a family of
 * database-specific implementations is derived.
 *
 * \synopsis
 * #include <rw/db/bkins.h>
 * #include <rw/db/table.h>
 *
 * RWDBBulkInserter ins = table.bulkInserter(connection);
 * \endsynopsis
 *
 * \example
 * The following example uses an RWDBBulkInserter to insert an array of
 * strings and integers into a table.
 *
 * \code
 * // Define the arrays that will hold the data to be
 * // inserted.
 * const int length = 10;
 * RWDBTBuffer< RWCString > stringBuffer(length);
 * RWDBTBuffer< int > intBuffer(length);
 *
 * // Populate the arrays using a user-defined function.
 * setValues(stringBuffer, intBuffer);
 *
 * // Define the inserter.
 * RWDBBulkInserter ins = tab.bulkInserter(connection);
 *
 * // Shift the arrays into the inserter.
 * ins << stringBuffer << intBuffer;
 *
 * // Insert up to length values at a time.
 * RWDBResult result = ins.execute(length);
 * \endcode
 * \endexample
 */
class RWDB_SYMBOLIC RWDBBulkInserter
{
public:

    /**
     * Default constructor. Creates an RWDBBulkInserter whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience; for example, to declare an array of RWDBBulkInserter
     * instances. Usable RWDBBulkInserter objects are obtained from valid
     * RWDBTable objects.
     */
    RWDBBulkInserter();

    /**
     * Copy constructor. The created RWDBBulkInserter shares an
     * implementation with \a ins.
     */
    RWDBBulkInserter(const RWDBBulkInserter& ins);

    RWDBBulkInserter(RWDBBulkInserterImp* imp);

    /**
     * Assignment operator. Self shares an implementation with \a ins.
     */
    RWDBBulkInserter& operator=(const RWDBBulkInserter& ins);

    ~RWDBBulkInserter();

    /**
     * Causes each of the values associated with each of the arrays shifted
     * into self to be inserted into the table associated with self. Returns
     * an RWDBResult.
     */
    RWDBResult execute();

    /**
     * Causes the first \a iters values associated with each of the arrays
     * shifted into self to be inserted into the table associated with self.
     * Returns an RWDBResult.
     */
    RWDBResult execute(size_t iters);

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise returns
     * \c false.
     */
    bool  isValid() const;

    /**
     * Returns the status of self.
     */
    RWDBStatus status() const;

    /**
     * Changes the current row position to \a index. If \a index is out of
     * range, self's status is set to RWDBStatus::invalidPosition. Returns a
     * reference to self.
     */
    RWDBBulkInserter& operator[](size_t index);

    /**
     * Changes the current row position to \a columnName and sets the column
     * list.
     */
    RWDBBulkInserter& operator[](const RWCString& columnName);

    /**
     * Changes the current row position to \a column and sets the column
     * list.
     */
    RWDBBulkInserter& operator[](const RWDBColumn& column);

    /**
     * Returns the current position, at which the next value will be shifted
     * in using the insertion operator. Returns #RW_NPOS if isValid()
     * returns \c false.
     */
    size_t position() const;

    /**
     * Shifts in the \a val to be associated with the column at the current
     * position. Increments the current position. Returns a reference to
     * self.
     *
     * This operator is capable of taking RWDBTBuffer.
     */
    RWDBBulkInserter& operator<<(const RWDBAbstractBuffer& val);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 6, use
     * RWDBBulkInserter::operator<<(const RWDBAbstractBuffer&), passing in
     * \ref RWDBTBuffer "RWDBTBuffer<RWDateTime>" instead.
     *
     * Shifts in the \a dateVector to be associated with the column at the
     * current position. Increments the current position. Returns a
     * reference to self.
     */
    RW_DEPRECATE_FUNC("Use RWDBBulkInserter::operator<<(const RWDBAbstractBuffer&) instead")
    RWDBBulkInserter& operator<<(const RWDBDateVector& dateVector);
#endif

private:
    RWDBCountedRef<RWDBBulkInserterImp> impl_;
};

#endif
