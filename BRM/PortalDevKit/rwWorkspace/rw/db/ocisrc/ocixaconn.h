#ifndef __RWDB_OCIXACONN_H__
#define __RWDB_OCIXACONN_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocixaconn.h#1 $
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
 * Oracle OCI XA Access Module implementation of RWDBConnectionImp
 *
 **************************************************************************/

#include <rw/db/ocisrc/ociconn.h>
#include <rw/db/ocisrc/ocixaenvh.h>

//////////////////////////////////////////////////////////////////////////
//
// Class to allow each XA connection to have it's own XA environment
// handle.
// Instances of this class should only be used to get an OCIEnv*, not to
// set attributes of the environment handle.  To set attributes, use the
// XA environment handle created in the database.
//
//////////////////////////////////////////////////////////////////////////
class RWDBOCIXAConnEnvHandle : public RWDBOCIXAEnvironmentHandle
{

public:

    // Constructor.
    // Takes the OCIEnv fetched by the OCIXAEnvironmentHandle.
    RWDBOCIXAConnEnvHandle(RWDBStatus& status, RWCString& dbName)
        : RWDBOCIXAEnvironmentHandle(status, dbName)
    {}

    virtual
    ~RWDBOCIXAConnEnvHandle()
    {}

private:
    // not implemented
    RWDBOCIXAConnEnvHandle();
    RWDBOCIXAConnEnvHandle(const RWDBOCIXAConnEnvHandle&);
    RWDBOCIXAConnEnvHandle& operator=(const RWDBOCIXAConnEnvHandle&);

};




class RWDB_ACCESS_GLOBAL RWDBOCIXAConnectionImp
    : public RWDBOCIConnectionImp
{

public:
    RWDBOCIXAConnectionImp(const RWDBStatus&              status,
                           const RWDBDatabase&            db,
                           RWDBConnection::ConnectionType connType);
    virtual
    ~RWDBOCIXAConnectionImp();


    // ** THESE METHODS SHOULD NOT BE CALLED BY AN APPLICATION PROGRAM **,
    // since opening and closing of connections and transaction management
    // in XA connections is handled by the TPM.
    // Use of these methods may result in RWDB_NOTSUPPORTED error.

    // connection handling methods
    virtual
    void                       open();
    virtual
    RWDBStatus                 close();

    // transaction control methods
    virtual
    RWDBStatus                 beginTransaction(const RWCString&);
    virtual
    RWDBStatus                 commitTransaction(const RWCString&);
    virtual
    RWDBStatus                 rollbackTransaction(const RWCString& name);

    virtual
    bool                  inTransaction() const;

private:
    // not implemented
    RWDBOCIXAConnectionImp(const RWDBOCIXAConnectionImp&);
    RWDBOCIXAConnectionImp& operator=(const RWDBOCIXAConnectionImp&);

};

#endif //  __RWDB_OCIXACONN_H__
