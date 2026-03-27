#ifndef __RWDB_HANDLEI_H__
#define __RWDB_HANDLEI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/handlei.h#1 $
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
 * Declaration of class RWDBHandleImp
 *
 * Provides an implementation for a vendor-specific handle.
 *
 **************************************************************************/

#include <rw/db/dbsrc/osqli.h>
#include <rw/db/connect.h>
#include <rw/db/cursor.h>
#include <rw/db/dbref.h>
#include <rw/db/schema.h>
#include <rw/db/status.h>
#include <rw/tvordvec.h>

class RWDB_GLOBAL RWDBHandleImp
    : public RWDBReference,
      public RWDBStatus
{
public:

    RWDBHandleImp(const RWDBStatus& status, const RWDBConnection& conn);
    virtual ~RWDBHandleImp();

    virtual   void          execute(RWDBOSqlImp* osql, size_t bulkSize);
    virtual   void          executeNoDescribe(RWDBOSqlImp* osql, size_t bulkSize);
    virtual   void          fetch(RWDBOSqlImp* osql);
    virtual   void          cancel(RWDBOSqlImp* osql, int flag);
    virtual   void          cleanup(RWDBOSqlImp* osql);
    virtual   void          reset();
    virtual   void          fetchReturnParams(RWDBOSqlImp* osql);
    virtual   RWDBValue     returnValue(RWDBOSqlImp* osql);

    virtual   RWDBSchema    schema() const;
    virtual   void          schema(const RWDBSchema& sch);

    // base implementation is used for all access libraries but sybasect
    virtual   long          rowsFetched() const;

    virtual   long          rowCount() const;
    virtual   long          rowsAffected() const;

    RWDBConnection          connection() const;

    void                    status(const RWDBStatus&);
    void                    future(const RWDBFuture&);

    // Errors in the following three functions are not reflected on our
    // status.  Instead, the error is returned in an RWDBStatus, since
    // an error doesn't necessarily mean that the handle imp needs to
    // be reset before a successful call can be made again.

    // vendorPositionFetch: Fetch with a specific position
    virtual RWDBStatus    vendorCursorPositionFetch(RWDBOSqlImp* osql,
            RWDBCursor::CursorPosition position,
            int offset,
            bool first = false);

    // vendorUpdateRow: update the current row for any in bindings on the result set.
    virtual RWDBStatus    vendorCursorUpdateRow(RWDBOSqlImp* osql,
            const RWCString& tableName);

    // vendorDeleteRow: delete the current row
    virtual RWDBStatus    vendorCursorDeleteRow(RWDBOSqlImp* osql,
            const RWCString& tableName);

protected:
    RWDBLocalMutex          statusMutex_;
    long                    rowsFetched_;
    RWDBConnection          connection_;
    RWDBSchema              schema_;
    long                    rowCount_;

    // Schema caching can be used to achieve better performance when the same
    // sql statement is re-executed. It is applied at handle level (by caching
    // result schema for current query statement).
    // The schema caching can be set (on/off) at environment handle.
    // It is in off state by default.
    RWTScopedPointer<RWTValOrderedVector<RWDBSchema> > schemaVec_;
    void                                clearSchemaCache();
    void                                putSchemaIntoCache(RWDBOSqlImp* osql);
    bool                           getSchemaFromCache(RWDBOSqlImp* osql);

private:
    RWDBHandleImp(const RWDBHandleImp& h);
    RWDBHandleImp& operator=(const RWDBHandleImp& h);
};

// Utility functions for handles.
class RWDB_SYMBOLIC RWDBHandleUtils
{
public:
    // Standardized error message functions
    static RWDBStatus& setNotWriteCursorError(RWDBStatus& s);
    static RWDBStatus& setBadTableNameError(RWDBStatus& s);
    static RWDBStatus& setChangedTableNameError(RWDBStatus& s);

    // Creates a SET list for an UPDATE based on the cols that are marked as
    // in parameters.  placeHolderSyntax should be a string that can be
    // sprintf'ed to with a number to make a valid placeholder.
    static RWCString createSetList(const RWDBSchema& schema, const RWCString& placeHolderSyntax);
};


#endif
