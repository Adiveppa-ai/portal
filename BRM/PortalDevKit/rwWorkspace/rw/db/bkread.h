#ifndef __RWDB_BKREAD_H__
#define __RWDB_BKREAD_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/bkread.h#1 $
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
 * Interface for RWDBBulkReader
 *
 **************************************************************************/

#include <rw/db/dbref.h>

/**
 * \ingroup db_bulk_operations_group
 *
 * \brief
 * Reads result sets, represented as arrays of RWDBTBuffer or
 * RWDBDateVector, that are associated with an RWDBTable or RWDBSelector.
 * (For reading scalar values, use RWDBReader.)
 *
 * Like RWDBReader, RWDBBulkReader is a class designed to read result sets
 * associated with an RWDBTable or RWDBSelector. The main difference between
 * RWDBBulkReader and RWDBReader is that \e arrays of values are shifted
 * into the RWDBBulkReader for each column in the result set, while
 * \e scalar values are shifted out of the RWDBReader. These arrays are
 * passed by reference and need to stay in scope for the duration of the
 * reader. The class RWDBTBuffer is used for reading all types of data,
 * including numbers, dates, strings, and binary data.
 *
 * RWDBBulkReader is designed around the Interface/Implementation paradigm.
 * An RWDBBulkReader instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBBulkReader
 * implementation is a base class from which a family of database-specific
 * implementations is derived.
 *
 * \synopsis
 * #include <rw/db/bkread.h>
 * #include <rw/db/select.h>
 * #include <rw/db/table.h>
 *
 * RWDBBulkReader reader1 = table.bulkReader(connection);
 * RWDBBulkReader reader2 = selector.bulkReader(connection);
 * \endsynopsis
 *
 * \example
 * The following example uses an RWDBBulkReader to read a result set, where
 * the first column is a date and the second column is an integer.
 *
 * \code
 * // Set up the selector.
 * RWDBSelector selector = db.selector();
 * selector << tab["datecolumn"] << tab["intColumn"];
 *
 * // Define the arrays into which the data will be read.
 * RWDBTBuffer< RWDateTime > dateBuffer(n);
 * RWDBTBuffer< int > intBuffer(n);
 *
 * // Define the reader.
 * RWDBBulkReader rdr = selector.bulkReader(connection);
 *
 * // Shift the arrays into the reader.
 * rdr << dateBuffer << intBuffer;
 *
 * // Read up to n values at a time.
 * int numRead;
 * while ( numRead = rdr( ) ) {
 *    for (int i = 0; i < numRead ; i++)
 *      process( dateBuffer[i], intBuffer[i] );
 * }
 * \endcode
 * \endexample
 */
class RWDB_SYMBOLIC RWDBBulkReader
{
public:

    /**
     * Default constructor. Creates an RWDBBulkReader whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience; for example, for declaring an array of RWDBBulkReader
     * instances. Usable RWDBBulkReader objects are obtained from valid
     * RWDBTable objects.
     */
    RWDBBulkReader();

    RWDBBulkReader(RWDBBulkReaderImp* imp);

    /**
     * Copy constructor. The created RWDBBulkReader shares an implementation
     * with \a rdr.
     */
    RWDBBulkReader(const RWDBBulkReader& rdr);

    /**
     * Assignment operator. Self shares an implementation with \a rdr.
     */
    RWDBBulkReader& operator=(const RWDBBulkReader& rdr);

    ~RWDBBulkReader();

    /**
     * Changes the current row position to \a index. If \a index is out of
     * range, self's status is set to RWDBStatus::invalidPosition. Returns a
     * reference to self.
     */
    RWDBBulkReader& operator[](size_t index);

    /**
     * Returns the current position, at which the next value will be shifted
     * in using the extraction operator. Returns #RW_NPOS if isValid()
     * returns false.
     */
    size_t position() const;

    /**
     * Shifts in the \a val to be associated with the column at the current
     * position. Increments the current position. Returns a reference to
     * self.
     *
     * This operator is capable of taking RWDBTBuffer.
     */
    RWDBBulkReader& operator<<(RWDBAbstractBuffer& val);

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 6, use
     * RWDBBulkReader::operator<<(RWDBAbstractBuffer&), passing in
     * \ref RWDBTBuffer "RWDBTBuffer<RWDateTime>" instead.
     *
     * Shifts in the \a dateVector to be associated with the column at the
     * current position. Increments the current position. Returns a
     * reference to self.
     */
    RW_DEPRECATE_FUNC("Use RWDBBulkReader::operator<<(RWDBAbstractBuffer&) instead")
    RWDBBulkReader& operator<<(RWDBDateVector& dateVector);
#endif

    /**
     * Fetches into the internal array the next set of rows from the result
     * set associated with self. Up to \c n rows are fetched at a time,
     * where \c n is equal to the length of the shortest array being
     * fetched. Returns the number of rows actually fetched. A return value
     * of \c 0 indicates that there is no additional data to fetch.
     */
    size_t    operator()();

    /**
     * Cancels any pending results associated with self. Subsequent calls to
     * operator()() iterate over a fresh result set based on the current
     * values of the set of bound variables associated with the selector
     * that produced self.
     */
    int cancel();

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise
     * \c false.
     */
    bool isValid() const;

    /**
     * Returns the status of self.
     */
    RWDBStatus status() const;

private:
    RWDBCountedRef<RWDBBulkReaderImp> impl_;
};

#endif
