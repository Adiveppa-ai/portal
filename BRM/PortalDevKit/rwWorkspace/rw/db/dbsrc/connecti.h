#ifndef __RWDB_CONNECTI_H__
#define __RWDB_CONNECTI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/connecti.h#1 $
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
 * Definition of RWDBConnectionImp
 *
 **************************************************************************/

#include <rw/db/cursor.h>
#include <rw/db/dbase.h>
#include <rw/db/dbref.h>

class RWDB_SYMBOLIC RWDBConnectionPool;

//////////////////////////////////////////////////////////////////////////
//
// RWDBConnectionImp
//
//    Base Class for Connection Implementations
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBConnectionImp : public RWDBReference,
    public RWDBStatus
{
    friend class RWDB_GLOBAL RWDBDatabaseImp;
public:
    RWDBConnectionImp(const RWDBStatus&      status,
                      const RWDBDatabase&    dbase,
                      RWDBConnection::ConnectionType connType);
    virtual ~RWDBConnectionImp();
    virtual void              initialize();

    virtual void              open();
    virtual RWDBStatus        close();

    virtual RWDBStatus        beginTransaction(const RWCString& name);
    virtual RWDBStatus        commitTransaction(const RWCString& name);
    virtual RWDBStatus        rollbackTransaction(const RWCString& name);
    virtual RWDBStatus        setSavepoint(const RWCString& name);
    virtual RWDBStatus        setIsolation(RWDBConnection::IsolationType level);
    virtual RWDBConnection::IsolationType isolation() const;

    //virtual RWDBResultImp*    executeSql( const RWCString& sql,
    RWDBResultImp*    executeSql(const RWCString& sql,
                                 RWDBStatus& status);

    RWDBStatus                executeSqlNoResult(const RWCString& sql,
            RWDBStatus& status);

    // producers
    virtual RWDBHandleImp*  getFromHandlePool();
    virtual RWDBHandleImp*  getFromHandlePool(RWDBCursor::CursorType type,
            RWDBCursor::CursorAccess access);
    virtual RWDBHandleImp*  handleImp();
    virtual RWDBHandleImp*  handleImp(RWDBCursor::CursorType type,
                                      RWDBCursor::CursorAccess access);

    // accessors
    virtual bool         isOpen() const;
    virtual RWDBConnection::ConnectionType connectionType() const;
    virtual RWDBDatabase      database() const;
    RWDBDatabase&             database();
    RWDBSystemHandle*         systemHandle() const;

    // time zone functions
    const RWZone&         timeZone() const;
    const RWZone*         timeZone(const RWZone* zone);

    // multithreading functions
    void              acquire() const;
    void              release() const;

    virtual void      checkOut();
    void              checkOut(RWDBConnectionPool* origin);
    virtual bool checkIn();

    void              useConnPool(bool useConnectionPool);
    bool         useConnPool() const;

    bool operator==(const RWDBConnectionImp& rhs) const
    {
        return this == &rhs;
    }

    bool operator<(const RWDBConnectionImp& /*rhs*/) const
    {
        // This code should never be reached, and only exists to
        // satisfy a select few compilers that need this operator.
        // If this assertion is reached, this object has been placed
        // in an inappropriate collection.
        RW_ASSERT(false);
        return false;
    }

protected:
    // System handle object.
    RWDBCountedRef<RWDBSystemHandle>   systemHandle_;

    // multithreading data
    RWDBLocalRecursiveMutex         mutex_;

    RWDBDatabase                   dbase_;
    RWDBConnection::ConnectionType connType_;
    bool                      isOpen_; // derived classes should set this

    // connection pool that self is from (if any.)
    RWDBConnectionPool*            origin_;

    // Whether the connection should be stored back in connection pool.
    bool                      useConnPool_;

    // Time zone to be used for datetime data sent and received from database.
    const RWZone*                  timeZone_;

private:
    // not implemented
    RWDBConnectionImp(const RWDBConnectionImp&);
    RWDBConnectionImp& operator=(const RWDBConnectionImp&);
};


#endif
