#ifndef __RWDB_OSQLI_H__
#define __RWDB_OSQLI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/osqli.h#1 $
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
 * The prototype of class RWDBOSqlImp
 *
 * Provides an object that represents a sql
 *
 **************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/handle.h>
#include <rw/db/multirow.h>
#include <rw/db/osql.h>
#include <rw/db/status.h>
#include <rw/ordcltn.h>
#include <rw/tvdlist.h>

class RWDB_GLOBAL RWDBOSqlImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    RWDBOSqlImp(const RWDBStatus& status);
    RWDBOSqlImp(const RWDBStatus& status,
                const RWCString& sql,
                RWDBOSql::StatementType type);
    virtual ~RWDBOSqlImp();
    void                operator << (RWDBAbstractBuffer& input);
    void                operator << (RWDBDataCallback& prm);
    RWDBMultiRow&       operator [](size_t index);

    void                statement(const RWCString& sql, RWDBOSql::StatementType type);
    RWCString           statement() const
    {
        return sql_;
    }

    void                initStatement(const RWCString& sql, RWDBOSql::StatementType type);

    void                execute(const RWDBConnection& cn,
                                size_t blkSz, size_t maxCachedResults);
    void                execute(const RWDBConnection& cn, size_t blkSz);
    void                execute(const RWDBHandle& hdl, size_t blkSz);
    void                executeNoDescribe(const RWDBConnection& cn, size_t blkSz);
    void                executeNoDescribe(const RWDBHandle& hdl, size_t blkSz);

    bool           hasResult() const
    {
        return anyResult_;
    }

    void                increaseResultsetIndex()
    {
        results_.incrementResultIndex();
        columnInfoUsed_ = false;
    }

    bool           columnInfoUsed() const
    {
        return columnInfoUsed_;
    }
    void                columnInfoUsed(bool used)
    {
        columnInfoUsed_ = used;
    }

    RWDBSchema          schema() const;
    void                status(const RWDBStatus& s);
    void                future(const RWDBFuture& s);
    void                fetch();
    void                cancel(int tp);
    long                rowCount() const;
    long                rowsAffected() const;
    long                rowsFetched() const;
    void                fetchReturnParams();
    RWDBValue           returnValue() const;

    void                hasResult(bool t);
    void                cleanup();
    void                preCleanup();

    RWDBOSql::StatementType type() const;
    void                type(RWDBOSql::StatementType newValue);

    size_t                 getParamBulkSize() const;
    size_t                 getParamBulkSize(size_t idx) const;
    size_t                 getColBulkSize() const;
    size_t                 getColBulkSize(size_t idx) const;
    RWDBMultiRow&       getResult() const;
    RWDBMultiRow&       getResult(size_t idx) const;
    RWDBMultiRow&       getParams() const;
    bool           anyParams() const;
    size_t              currentResult() const
    {
        return results_.currentResultIndex();
    }
    bool           isReady() const;

    void                transferInserterEntries(RWOrdered& scalarList);

private:

    //////////////////////////////////////////////////////////////////
    // class RWDBOSqlResults
    //
    // Embedded class to handle the result sets of the execution.
    // The class provides controlled caching of the result sets giving
    // performance improvement for multiple executions of the same SQL.
    //////////////////////////////////////////////////////////////////
    class RWDB_SYMBOLIC RWDBOSqlResults
    {
    public:
        RWDBOSqlResults(size_t maxCachedResults)
            : maxCachedResults_(maxCachedResults)
            , currentResultIndex_(0)
            , currentResult_((RWDBMultiRowImp*)0)
        {
        }

        // Fetches the current result set.
        RWDBMultiRow& getResult() const;
        // Fetches the requested result set.
        RWDBMultiRow& getResult(size_t idx) const;

        // Returns the index of the current result set.
        size_t currentResultIndex() const
        {
            return currentResultIndex_;
        }

        // Indicates next result set is being processed.
        void incrementResultIndex();

        // Prepares for re-execution of the statement.
        // Resets the current result without purging the cached result sets.
        void reset();

        // Prepares for re-execution of the statement with a new limit on the
        // number of cached results.
        // Resets the current result. Trims the cached result sets to adjust
        // to the new limit, if necessary.
        void reset(size_t maxCachedResults);

        // Prepares for executing a new query.
        // Clears the current result and the cached results.
        void clear();

    private:
        // Maximum number of results that can be cached in the resultList_.
        // NOTE: When RWDBOSql is used directly by the user, the user is free
        //       to access any result set any time using RWDBOSql::operator[].
        //       Hence all results must be cached by keeping maxCachedResults_
        //       as RW_SIZE_MAX.
        size_t maxCachedResults_;
        // The result index of the currentResult_.
        size_t currentResultIndex_;
        // The result currently being processed by the handle_.
        // NOTE: The currentResult_ may be pointing to a NULL
        //       RWDBMultiRowImp if the current result is not yet accessed.
        mutable
        RWDBMultiRow currentResult_;
        // The list caching results from the execution.
        mutable
        RWTValDlist<RWDBMultiRow> resultList_;

        // Fetches the current result from cache, if present, else creates a
        // new result set.
        RWDBMultiRow& fetchCurrentResult() const;

        // Stores the currentResult_ back in the cache, if needed.
        // NOTE: This method should be called every time value of
        //       currentResultIndex_ changes.
        void storeCurrentResult();

        // Not implemented: forbidden.
        RWDBOSqlResults(const RWDBOSqlResults&);
        RWDBOSqlResults& operator=(const RWDBOSqlResults&);

    }; // RWDBOSqlResults


    // Database handle to execute the SQL.
    RWDBHandle                  handle_;

    // SQL and its type.
    RWCString                   sql_;
    RWDBOSql::StatementType     type_;

    // Bind parameters.
    RWDBMultiRow                params_;

    // Result sets.
    RWDBOSqlResults             results_;

    bool                   columnInfoUsed_;
    bool                   anyResult_;
    bool                   executed_;

    // to hold inserter entries when the stored proc goes
    // out of scope to prevent the buffers being deleted
    // when they might still be in use
    RWOrdered                   procScalarList_;

    // not implemented: forbidden.
    RWDBOSqlImp(const RWDBOSqlImp&);
    RWDBOSqlImp& operator=(const RWDBOSqlImp&);
};

#endif
