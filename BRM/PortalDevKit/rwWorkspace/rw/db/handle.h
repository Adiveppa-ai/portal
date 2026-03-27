#ifndef __RWDB_HANDLE_H__
#define __RWDB_HANDLE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/handle.h#1 $
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
 * Declaration of class RWDBHandle
 *
 * Provides an object that represents a handle to a vendor.
 *
 **************************************************************************/
#include <rw/db/connect.h>
#include <rw/db/cursor.h>
#include <rw/db/defs.h>
#include <rw/db/status.h>

class RWDB_SYMBOLIC RWDBHandle
{
public:

    RWDBHandle();
    RWDBHandle(RWDBHandleImp* handle);
    RWDBHandle(const RWDBHandle& handle);

    RWDBHandle& operator=(const RWDBHandle& handle);

    ~RWDBHandle();

    void          execute(const RWDBOSql& osql, size_t blkSz);
    void          executeNoDescribe(const RWDBOSql& osql, size_t blkSz);
    void          fetch(const RWDBOSql& osql);
    void          cancel(const RWDBOSql& osql, int flag);
    void          cleanup(const RWDBOSql& osql);
    void          reset();
    RWDBSchema    schema() const;
    void          schema(const RWDBSchema& sch);
    long          rowCount() const;
    long          rowsAffected() const;
    long          rowsFetched() const;

    bool     isReady() const;
    bool     isValid() const;
    RWDBStatus    status() const;
    void          status(const RWDBStatus& s);
    void          future(const RWDBFuture& f);
    void          setErrorHandler(RWDBStatus::ErrorHandler erh);

    void          fetchReturnParams(const RWDBOSql& osql);
    RWDBValue     returnValue(const RWDBOSql& osql) const;

    RWDBConnection connection() const;

    // For the following three member functions, errors are returned on
    //   the returned RWDBStatus instead of set on the handle itself.
    //   This is because errors on these methods don't indicate that further
    //   work on the handle will fail, only that the said operation failed.

    // vendorPositionFetch: Fetch with a specific position
    RWDBStatus    vendorCursorPositionFetch(
        const RWDBOSql& osql,
        RWDBCursor::CursorPosition position,
        int offset,
        bool first = false);

    // vendorUpdateRow: update the current row for any in bindings on the
    //   result set.
    RWDBStatus    vendorCursorUpdateRow(
        const RWDBOSql& osql,
        const RWCString& tableName);

    // vendorDeleteRow: delete the current row.
    RWDBStatus    vendorCursorDeleteRow(
        const RWDBOSql& osql,
        const RWCString& tableName);


private:
    static RWDBHandle& uninitialized();

    RWDBCountedRef<RWDBHandleImp> impl_;

    friend RWDBHandleImp* getImp(const RWDBHandle& handle)
    {
        return handle.impl_;
    }

    friend bool operator==(const RWDBHandle& lhs, const RWDBHandle& rhs)
    {
        return lhs.impl_ == rhs.impl_;
    }
    friend bool operator!=(const RWDBHandle& lhs, const RWDBHandle& rhs)
    {
        return !(lhs.impl_ == rhs.impl_);
    }
};

#endif
