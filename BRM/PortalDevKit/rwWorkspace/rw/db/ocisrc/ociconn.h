#ifndef __RWDB_OCICONN_H__
#define __RWDB_OCICONN_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ociconn.h#1 $
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
 * Oracle OCI Access Module implementation of RWDBConnectionImp
 *
 **************************************************************************/

#include <rw/db/ocisrc/ocienvh.h>
#include <rw/db/ocisrc/ocisysh.h>
#include <rw/db/dbsrc/connecti.h>

//////////////////////////////////////////////////////////////////////////
//
// Class to allow each connection to have it's own environment handle.
// Instances of this class should only be used to get an OCIEnv*, not to
// set attributes of the environment handle.  To set attributes, use the
// environment handle created in the database.
//
//////////////////////////////////////////////////////////////////////////
class RWDBOCIConnEnvHandle : public RWDBOCIEnvironmentHandle
{
public:

    //we want to use the base class ctors
    RWDBOCIConnEnvHandle(RWDBStatus& status)
        : RWDBOCIEnvironmentHandle(status)
    {}

    virtual
    ~RWDBOCIConnEnvHandle()
    {}

private:
    // not implemented
    RWDBOCIConnEnvHandle();
    RWDBOCIConnEnvHandle(const RWDBOCIConnEnvHandle&);
    RWDBOCIConnEnvHandle& operator=(const RWDBOCIConnEnvHandle&);

};



class RWDB_ACCESS_GLOBAL RWDBOCIConnectionImp : public RWDBConnectionImp
{
public:
    enum TransType           { Begin, Commit, Rollback, Savepoint };
    RWDBOCIConnectionImp(const RWDBStatus&   status,
                         const RWDBDatabase& db,
                         RWDBConnection::ConnectionType connType);
    virtual
    ~RWDBOCIConnectionImp();

    virtual
    void initialize();

    // connection handling methods
    virtual
    void                     open();

    virtual
    RWDBStatus               close();

    // transaction control methods
    virtual
    RWDBStatus               beginTransaction(const RWCString&);
    virtual
    RWDBStatus               commitTransaction(const RWCString&);
    virtual
    RWDBStatus               rollbackTransaction(const RWCString& name);
    virtual
    RWDBStatus               setSavepoint(const RWCString& name);

    virtual
    RWDBStatus               setIsolation(RWDBConnection::IsolationType);
    virtual
    RWDBConnection::IsolationType
    isolation() const;

    // producer methods
    virtual
    RWDBHandleImp*           handleImp();
    virtual
    RWDBHandleImp*           handleImp(RWDBCursor::CursorType type,
                                       RWDBCursor::CursorAccess access);

    virtual
    bool                inTransaction() const;

protected:
    // Constructor for RWDBOCIXAConnectionImp to call.
    RWDBOCIConnectionImp(const RWDBStatus&   status,
                         const RWDBDatabase& db,
                         RWDBConnection::ConnectionType connType,
                         int);

    // Member Variables
    bool                                   inTransaction_;
    RWDBCountedRef<RWDBOCIEnvironmentHandle>    connectionEnvHandle_;

private:
    // not implemented
    RWDBOCIConnectionImp(const RWDBOCIConnectionImp&);
    RWDBOCIConnectionImp& operator=(const RWDBOCIConnectionImp&);
};

#endif
