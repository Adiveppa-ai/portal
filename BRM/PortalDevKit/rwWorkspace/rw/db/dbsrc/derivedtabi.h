#ifndef __RWDB_DERIVEDTABI_H__
#define __RWDB_DERIVEDTABI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/derivedtabi.h#1 $
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
 * Definition of RWDBDerivedTableImp
 *
 *    RWDBDerivedTableImp represents a derived table produced from a query.
 *
 **************************************************************************/

#include <rw/db/dbsrc/tablei.h>
#include <rw/db/cursor.h>
#include <rw/db/select.h>
#include <rw/db/table.h>

class RWDB_GLOBAL RWDBDerivedTableImp
    : public RWDBTableImp
{
public:
    RWDBDerivedTableImp(const RWDBStatus& status,
                        const RWDBSelectorBase& sel);
    virtual ~RWDBDerivedTableImp();

    // Defining self in the SQL statement
    virtual RWCString asString(RWDBStatementImp* stmt,
                               const RWZone& timeZone,
                               bool verbose) const;

    // Fetches schema
    virtual bool existsAllocateConnection(
        bool forceLookup = false);
    virtual bool exists(const RWDBConnection& connection,
                        bool forceLookup = false);

    RWDBSchema describe(RWDBTable::Metadata md, const RWDBConnection* connection);

    // Producers
    virtual RWDBReaderImp* readerImp(const RWDBTable& t, size_t cacheSize);
    virtual RWDBReaderImp* readerImp(const RWDBTable&,
                                     const RWDBConnection& conn,
                                     size_t cacheSize);
    virtual RWDBBulkReaderImp* bulkReaderImp(const RWDBTable&,
            const RWDBConnection& conn);
    virtual RWDBCursorImp* cursorImp(const RWDBConnection& connection,
                                     RWDBCursor::CursorType type,
                                     RWDBCursor::CursorAccess access);
    virtual RWDBCursorImp* cursorImp(const RWDBSchema& updateCols,
                                     const RWDBConnection& connection,
                                     RWDBCursor::CursorType type,
                                     RWDBCursor::CursorAccess access);
protected:
    RWDBSelectorBase sel_;
    bool schemaFetched_;

private:
    // Not implemented: forbidden.
    RWDBDerivedTableImp(const RWDBDerivedTableImp&);
    RWDBDerivedTableImp& operator=(const RWDBDerivedTableImp&);
};

#endif // __RWDB_DERIVEDTABI_H__
