#ifndef __RWDB_ociHandle_H__
#define __RWDB_ociHandle_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocihandle.h#1 $
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
 * Oracle OCI Access Module implementation of RWDBHandle
 *
 **************************************************************************/

#include <rw/db/ocisrc/ocidefs.h>
#include <rw/db/ocisrc/ocisysh.h>
#include <rw/db/ocisrc/rwocitypes.h>
#include <rw/db/dbsrc/futurei.h>
#include <rw/db/dbsrc/handlei.h>
#include <rw/db/dbsrc/osqli.h>
#include <rw/db/cursor.h>
#include <rw/db/osql.h>
#include <rw/db/poolable.h>
#include <rw/tpdlist.h>
#include <rw/tpordvec.h>

class RWDB_ACCESS_GLOBAL RWDBOCIHandleImp: public RWDBHandleImp
{
public:
    RWDBOCIHandleImp(const RWDBConnection& conn);
    virtual ~RWDBOCIHandleImp();
    virtual void   execute(RWDBOSqlImp* osql, size_t numberOfExecutions);
    virtual void   executeNoDescribe(RWDBOSqlImp* osql, size_t numberOfExecutions);
    virtual void   fetch(RWDBOSqlImp* osql);
    virtual void   cancel(RWDBOSqlImp* osql, int flag);
    virtual void   cleanup(RWDBOSqlImp* osql);
    virtual void   defineSchema(RWDBOSqlImp* osql);
    virtual void   fetchReturnParams(RWDBOSqlImp* osql);
    virtual void   vendorParse(RWDBOSqlImp* osql, bool needsRowId = false);
    virtual void   vendorBind(RWDBOSqlImp* osql);
    virtual void   vendorExec(RWDBOSqlImp* osql, size_t numberOfExecutions,
                              bool describeResultSchema = true);

    void           bindParam(RWDBOSqlImp* osql);
    void           bindCol(RWDBOSqlImp* osql, OCIStmt* stmt);
    void           currentFetchDone(bool t)
    {
        currentFetchDone_ = t;
    }
    bool           currentFetchDone()
    {
        return currentFetchDone_;
    }
    bool           asyncDone()
    {
        return asyncDone_;
    }

    OCIStmt*         ociStmt()
    {
        return stmt_;
    }
    OCIStmt*         ociFetchingStmt()
    {
        return fetchingStmt_;
    }
    OCIError*        ociErr()
    {
        return sysHandle_->errorHandle();
    }
    OCISvcCtx*       ociCtx()
    {
        return sysHandle_->ociServerContext();
    }
    OCIEnv*          ociEnvh()
    {
        return sysHandle_->ociEnvh();
    }
    size_t          piecewiseSize()
    {
        return sysHandle_->piecewiseSize();
    }
    ub4             lobPrefetchSize()
    {
        return sysHandle_->lobPrefetchSize();
    }
    void            check(sword ret)
    {
        sysHandle_->check(*(RWDBStatus*)this, ret);
    }
    void            check(RWDBStatus& st, sword ret)
    {
        sysHandle_->check(st, ret);
    }

protected:
    enum StateType { Start = 0, Prepared, Executed, Fetched };

    // result sets for pl/sql cursor parameters
    RWTPtrOrderedVector<OCIStmt> rSet_;

    RWDBOCIAdapterFactory factory_;

    RWCString       sqlStmt_; //hold SQL statement(might not necessary for OCI)
    size_t          rSetIdx_;       // indexing current position of rSet_
    OCIStmt*         stmt_;          // base associated with sql string.

    // current statement for fetching.
    OCIStmt*         fetchingStmt_;

    // accumulated rows fetched for current fetch statement
    long            totalRowsFetched_;
    bool            currentFetchDone_;  // flag for current fetch statement
    bool            asyncDone_;      // flag for non-blocking.

    // for ocilib, uses ocirowsFetched_ internally (ub4 vs. long)
    virtual long    rowsFetched() const;

    inline bool plsql(RWDBOSqlImp* osql)
    {
        return (osql->type() == RWDBOSql::Procedure);
    }

    // These functions are for scrolling cursor.
    ub4             getExecutionMode() const;
    void            setExecutionMode(ub4);
    ub2             getFetchMode() const;
    void            setFetchMode(RWDBCursor::CursorPosition);
    sb4             getFetchOffset() const;
    void            setFetchOffset(sb4);

private:
    void            sendData(RWDBOSqlImp* osql);
    void            prepareResultAfterVendorExecute(RWDBOSqlImp*, bool);
    bool            prepareFetch(RWDBOSqlImp* osql);
    void            cancelFetch(RWDBOSqlImp* osql);
    void            finishPollingExecute();
    // Fetches number of rows affected by the operation.
    long            fetchRowsAffected();

    RWDBCountedRef<RWDBOCISystemHandle> sysHandle_;

    OCIError*        errorHandle_; // cached locally for performance.
    bool            paramsFetched_;
    size_t          bksize_;
    StateType       state_;
    ub4             executionMode_;
    ub4             ocirowsFetched_;
    sb4             fetchOffset_;
    ub2             fetchMode_;
};

// This is the handle used that can perform cursor operations.
class RWDB_ACCESS_GLOBAL RWDBOCICursorHandleImp: public RWDBOCIHandleImp
{
public:
    RWDBOCICursorHandleImp(const RWDBConnection& conn,
                           RWDBCursor::CursorType type,
                           RWDBCursor::CursorAccess access);
    virtual ~RWDBOCICursorHandleImp();

    virtual void vendorParse(RWDBOSqlImp* osql, bool needsRowId = false);
    virtual void vendorExec(RWDBOSqlImp* osql,
                            size_t numberOfExecutions,
                            bool);

    virtual void defineSchema(RWDBOSqlImp* osql);

    virtual void cleanup(RWDBOSqlImp* osql);

    virtual RWDBStatus vendorCursorPositionFetch(RWDBOSqlImp* osql,
            RWDBCursor::CursorPosition position,
            int offset,
            bool first = false);

    virtual RWDBStatus vendorCursorUpdateRow(RWDBOSqlImp* osql,
            const RWCString& tableName);

    virtual RWDBStatus vendorCursorDeleteRow(RWDBOSqlImp* osql,
            const RWCString& tableName);

protected:
    RWDBCursor::CursorAccess access_;
    RWDBCursor::CursorType type_;
    RWDBOSql updater_, deleter_;  // For updateRow, deleteRow.
    RWCString oldTableName_;
};


class RWDBOCIVendorExecuteFutureImp : public RWDBFutureImp
{
public:
    RWDBOCIVendorExecuteFutureImp(RWDBOSqlImp* osql,
                                  RWDBOCIHandleImp* handle,
                                  ub4 bulkSz,
                                  bool describeResultSchema)
        : RWDBFutureImp(false),
          describeResultSchema_(describeResultSchema),
          osql_(osql),
          handle_(handle),
          bulkSz_(bulkSz)
    {
    }

    virtual ~RWDBOCIVendorExecuteFutureImp()
    {
    }

    bool isDbReady();
    void finishDbAsync();
protected:
    bool describeResultSchema_;
    RWDBOSqlImp*                            osql_;
    RWDBOCIHandleImp*                   handle_;
    ub4                                     bulkSz_;
};

class RWDBOCIVendorFetchFutureImp : public RWDBFutureImp
{
public:
    RWDBOCIVendorFetchFutureImp(RWDBOSqlImp* osql,
                                RWDBOCIHandleImp* handle)
        : RWDBFutureImp(false),
          osql_(osql),
          handle_(handle)
    {
    }

    virtual ~RWDBOCIVendorFetchFutureImp()
    {
    }

    bool isDbReady();
    void finishDbAsync();
protected:
    RWDBOSqlImp*             osql_;
    RWDBOCIHandleImp*    handle_;
};

#endif
