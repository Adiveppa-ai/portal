#ifndef __RWDB_MEMTABLE_H__
#define __RWDB_MEMTABLE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/memtable.h#1 $
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
 * RWDBMemTable represents tabular data stored in program memory.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/table.h>

/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * Represents a table of data that resides in program memory.
 *
 * RWDBMemTable is a table of data that resides in program memory. After
 * construction, an RWDBMemTable is no longer associated with a table in the
 * database. An application can modify the data in an RWDBMemTable, but the
 * changes are not propagated back to the database.
 *
 * RWDBMemTable is designed around the Interface/Implementation paradigm. An
 * RWDBMemTable instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation.
 *
 * Because an RWDBMemTable resides in memory, it is possible to provide
 * random access to its data. The DB Interface Module provides
 * \ref operator[](size_t) "operator[]" for indexing on RWDBMemTable, the
 * result of which is a reference to RWDBRow. RWDBRow inherits indexing
 * operator \ref RWDBRow::operator[](size_t)const "operator[]" from the
 * Essential Tools Module class RWOrdered. The net result is the ability to
 * access RWDBMemTable data with double indexing, as if it were a
 * two-dimensional C++ array.
 *
 * There are limitations to using RWDBMemTable, as it lacks some of the
 * functionality of an RWDBTable. The differences in functionality come from
 * the lack of a server in memory for selecting, deleting, inserting, and
 * updating memory tables through SQL constructs. This means that selectors,
 * cursors, deleters, inserters, and updaters cannot be created using memory
 * tables. Instead, the actual table in the database must be referenced.
 *
 * However, an RWDBReader may be produced from RWDBMemTable, allowing access
 * to each row within the memory table, rather than using the overloaded
 * operator \ref operator[](size_t) "operator[]" for indexing.
 *
 * It should also be noted that since memory tables exist within memory, the
 * normal data definition language (DDL) constructs that are associated with
 * tables are also dysfunctional and return invalid results. These include
 * grant(), revoke(), addColumn(), dropColumn(), and so on.
 *
 * \synopsis
 * #include <rw/db/memtable.h>
 *
 * RWDBMemTable myTable = myDbase.memTable("myTable");
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBMemTable
    : public RWDBTable
{
public:

    /**
     * Constructs an empty RWDBMemTable with given \a capacity. A
     * \a capacity of zero means there is no limit on the number of rows to
     * be stored.
     */
    RWDBMemTable(size_t capacity = 0);

    /**
     * Uses a default database connection to construct an RWDBMemTable and
     * populate it with a maximum of \a capacity rows from \a table. A
     * capacity of zero means there is no limit on the number of rows to be
     * stored.
     */
    RWDBMemTable(const RWDBTable& table, size_t capacity = 0);

    /**
     * Uses the supplied \a connection to construct an RWDBMemTable and
     * populate it with a maximum of \a capacity rows from \a table. A
     * \a capacity of zero means there is no limit on the number of rows to
     * be stored.
     */
    RWDBMemTable(const RWDBTable& table, const RWDBConnection& connection,
                 size_t capacity = 0);

    /**
     * Uses a default connection to construct an RWDBMemTable and populate
     * it with the maximum of \a capacity rows from \a sel. A \a capacity of
     * zero means there is no limit on the number of rows to be stored.
     */
    RWDBMemTable(const RWDBSelectorBase& sel, size_t capacity = 0);

    /**
     * Uses the supplied \a connection to construct an RWDBMemTable and to
     * populate it with the maximum of \a capacity rows from \a sel. A
     * \a capacity of zero means there is no limit on the number of rows to
     * be stored.
     */
    RWDBMemTable(const RWDBSelectorBase& sel,
                 const RWDBConnection& connection,
                 size_t capacity = 0);

    /**
     * Uses the supplied \a reader to construct an RWDBMemTable, populating
     * it with a maximum of \a capacity rows copied from \a reader. A
     * \a capacity of zero means there is no limit on the number of rows to
     * be stored.
     */
    RWDBMemTable(RWDBReader& reader, size_t capacity = 0);

    /**
     * Copy constructor. Self shares an implementation with \a table.
     */
    RWDBMemTable(const RWDBMemTable& table);

    virtual ~RWDBMemTable();

    /**
     * Assignment operator. Self shares an implementation with \a table.
     */
    RWDBMemTable&       operator=(const RWDBMemTable& table);

    /**
     * Returns the number of rows in self.
     */
    size_t              entries() const;

    /**
     * Returns a reference to the RWDBRow in self at position \a index. No
     * bounds checking is done.
     */
    RWDBRow&            operator[](size_t index);

    /**
     * Fills self to capacity, with rows fetched from \a reader. Rows
     * existing in self before this call are discarded.
     */
    bool           populate(RWDBReader& reader);

    /**
     * Fills self to capacity, with rows fetched from \a table. Rows
     * existing in self before this call are discarded.
     */
    bool           populate(const RWDBTable& table);

protected:

    // Documented in base class.
    RWDBColumn operator[](const RWCString& name) const;

    // Documented in base class.
    RWDBColumn operator[](size_t           idx) const;
};

#endif
