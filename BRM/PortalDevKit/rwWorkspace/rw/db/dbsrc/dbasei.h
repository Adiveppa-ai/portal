#ifndef __RWDB_DBASEI_H__
#define __RWDB_DBASEI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/dbasei.h#1 $
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

#ifdef _MSC_VER
#  pragma warning( disable : 4251)
#endif

#include <rw/db/dbsrc/connecti.h>
#include <rw/db/dbsrc/dbentry.h>
#include <rw/db/cachemgr.h>
#include <rw/db/connect.h>
#include <rw/db/cursor.h>
#include <rw/db/dbref.h>
#include <rw/db/poolable.h>
#include <rw/db/property.h>
#include <rw/db/status.h>
#include <rw/tools/atomic.h>

//////////////////////////////////////////////////////////////////////////
//
// Externs
//
//////////////////////////////////////////////////////////////////////////
extern "C" {
#ifndef RW_TRAILING_RWEXPORT
    RWDB_SYMBOLIC RWDBDatabaseImp*
#else
    RWDBDatabaseImp* RWDB_SYMBOLIC
#endif
    newNotFounddbDatabaseImp(
        const RWCString&,
        const RWCString&,
        const RWCString&,
        const RWCString&
    );
}

class RWDB_GLOBAL RWDBDateVectorImp;

//////////////////////////////////////////////////////////////////////////
//
// RWDBDatabaseImp
//
//    A DatabaseImp is a base class for a family of database
//    implementations. Services requested from a database are forwarded
//    to its implementation, which may either provide them directly
//    or through its derived class.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBDatabaseImp
    : public RWDBReference, public RWDBStatus
{
    friend class RWDB_GLOBAL RWDBDatabase;
    friend class RWDBManagerProxy;
public:
    RWDBDatabaseImp(const RWDBStatus& status);
    RWDBDatabaseImp(const RWDBStatus& status,
                    const RWCString& serverType,
                    const RWCString& serverName,
                    const RWCString& userName,
                    const RWCString& passWord,
                    const RWCString& dbName);
    RWDBDatabaseImp(const RWDBStatus& status,
                    const RWCString& serverType,
                    const RWCString& serverName,
                    const RWCString& userName,
                    const RWCString& passWord,
                    const RWCString& dbName,
                    const RWCString& connectString);

    virtual ~RWDBDatabaseImp();

    virtual void              initialize();
    virtual void              cleanup();


    // connection management
    virtual
    RWDBConnectionImp*        getFromConnectionPool(
        const RWDBConnCallback& conncb,
        RWDBConnection::ConnectionType connType,
        bool useConnPool);

    // accessor methods
    virtual size_t            totalConnections() const;
    virtual size_t            defaultConnections() const;
    virtual
    RWCString::caseCompare    caseCompare() const;
    RWDBEnvironmentHandle*    environmentHandle() const;
    virtual
    const RWDBPhraseBook&     phraseBook() const;
    virtual RWDBStatus        status() const;
    virtual RWCString         version() const;

    virtual RWCString         serverType() const;
    virtual RWCString         serverName() const;
    virtual RWCString         userName() const;
    virtual RWCString         passWord() const;
    virtual RWCString         dbName() const;
    virtual RWDBTracer&       tracer();
    virtual RWDBProperties    properties() const;

    virtual bool              emptyStringIsNull() const;
    virtual bool              verboseAsString() const;
    const RWZone&             timeZone() const;
    // Returns raw pointer. To be used only by RWDBConnectionImp::checkOut()
    // for inheriting the time zone setting.
    const RWZone*             timeZonePtr() const;
    RWDBCacheManager*         cacheManager() const;

    // mutator methods
    RWCString                 passWord(const RWCString& pwd);
    virtual size_t            defaultConnections(size_t size);
    virtual
    RWCString::caseCompare    caseCompare(RWCString::caseCompare);
    virtual bool              verboseAsString(bool verbose);
    const RWZone*             timeZone(const RWZone* zone);
    RWDBCacheManager*         cacheManager(RWDBCacheManager* cacheMgr);

    // multithreading methods
    void                      acquire() const;
    void                      release() const;

    // producer methods
    virtual
    RWDBConnectionImp*       connectionImp(RWDBConnection::ConnectionType type);

    virtual RWDBTableImp*    tableImp(const RWDBDatabase& dbase,
                                      const RWCString& name);
    virtual RWDBTableImp*    tableImp(const RWDBDatabase& dbase,
                                      const RWCString& name,
                                      const RWDBSchema& sch,
                                      bool isView);
    virtual RWDBTableImp*    tableImp(const RWDBSelectorBase& sel) const;
    virtual RWDBSelectorImp* selectorImp(const RWDBDatabase& dbase,
                                         const RWDBCriterion& criterion);
    virtual RWDBCursorImp*   cursorImp(RWDBCursor::CursorType type,
                                       RWDBCursor::CursorAccess access,
                                       const RWCString& select,
                                       const RWDBConnection& connection);
    virtual RWDBCursorImp*   cursorImp(RWDBCursor::CursorType type,
                                       RWDBCursor::CursorAccess access,
                                       const RWCString& select,
                                       const RWDBSchema& updateCols,
                                       const RWDBConnection& connection);
    virtual RWDBCursorImp*   cursorImp(RWDBCursor::CursorType type,
                                       RWDBCursor::CursorAccess access,
                                       const RWCString& select,
                                       const RWDBMultiRow& inboundBuffers,
                                       const RWDBConnection& connection);
    virtual RWDBCursorImp*   cursorImp(RWDBCursor::CursorType type,
                                       RWDBCursor::CursorAccess access,
                                       const RWCString& select,
                                       const RWDBMultiRow& inboundBuffers,
                                       const RWDBSchema& updateCols,
                                       const RWDBConnection& connection);
    virtual
    RWDBStoredProcImp*       storedProcImp(const RWDBDatabase& dbase,
                                           const RWCString& name,
                                           const RWDBStatus& status,
                                           const RWDBConnection& conn);
    virtual
    RWDBStoredProcImp*       storedProcImp(const RWDBDatabase& dbase,
                                           const RWCString& name,
                                           const RWDBStatus& status,
                                           const RWDBSchema&,
                                           const RWDBColumn&,
                                           const RWCString& text);

    // DDL methods
    virtual RWDBStatus   createTable(const RWCString& name,
                                     const RWDBSchema& updateCols,
                                     const RWDBConnection& connection);
    virtual RWDBStatus   createView(const RWCString& name,
                                    const RWDBSelectorBase& select,
                                    const RWDBConnection& connection);
    virtual RWDBStatus   createView(const RWCString& name,
                                    const RWDBSchema& columnList,
                                    const RWDBSelectorBase& select,
                                    const RWDBConnection& connection);
    virtual RWDBStatus   createView(const RWCString& name,
                                    const RWCString& sql,
                                    const RWDBConnection& connection);
    virtual RWDBStatus   createView(const RWCString& name,
                                    const RWDBSchema& columnList,
                                    const RWCString& sql,
                                    const RWDBConnection& connection);
    virtual RWDBStatus   createProcedure(const RWCString& name,
                                         const RWCString& sql,
                                         const RWDBSchema& params,
                                         const RWDBConnection& conn);
    virtual RWDBStatus   createProcedure(const RWDBStoredProc& proc,
                                         const RWDBConnection& conn);

    virtual RWDBStatus   dropView(const RWCString& name,
                                  const RWDBConnection& connection);


    virtual RWDBTable    dbTables(const RWDBConnection& conn,
                                  const RWCString& name,
                                  const RWCString& owner,
                                  int type,
                                  int adjustCase);

    virtual RWDBTable    dbStoredProcedures(const RWDBConnection& conn,
                                            const RWCString& name,
                                            const RWCString& owner,
                                            int adjustCase);

    void                 dbEntry(const RWDBEntry& e);
    RWDBEntry            dbEntry() const;

protected:

    RWDBLocalRecursiveMutex mutex_;

    RWDBConnectionPool      connectionPool_;
    RWDBProperties          connProperties_;
    RWCString::caseCompare  caseCompare_;
    RWCString               serverType_;
    RWCString               serverName_;
    RWCString               userName_;
    RWCString               passWord_;
    RWCString               dbName_;
    RWDBTracer              tracer_;
    size_t                  defaultConnections_;
    RWDBEntry               entry_;
    bool                    emptyStringIsNull_;
    bool                    verboseAsString_;
    // Time zone to be used for datetime data sent and received from database.
    const RWZone*           timeZone_;

    RWDBCountedRef<RWDBEnvironmentHandle> environmentHandle_;

    RWTAtomic<RWDBCacheManager*> cacheMgr_;

    friend
    RWDBConnectionPool&    rwdbExtractConnectionPool(RWDBDatabaseImp* imp)
    {
        return imp->connectionPool_;
    }

    friend class RWDBManager;

private:
    // not implemented:
    RWDBDatabaseImp(const RWDBDatabaseImp&);
    RWDBDatabaseImp&  operator=(const RWDBDatabaseImp&);

    RWCString                 encode(const RWCString&) const;
};


#endif
