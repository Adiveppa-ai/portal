#ifndef __RWDB_OCIXASYSH_H__
#define __RWDB_OCIXASYSH_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocixasysh.h#1 $
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
 * Oracle OCI XA Access Module of RWDBSystemHandle
 *
 **************************************************************************/

#include <rw/db/ocisrc/ocisysh.h>
#include <rw/db/ocisrc/rwoci.h>
#include <rw/db/connect.h>
#include <rw/cstring.h>


class RWDB_ACCESS_GLOBAL RWDBOCIXASystemHandle
    : public RWDBOCISystemHandle
{

public:
    RWDBOCIXASystemHandle(RWDBEnvironmentHandle* env,
                          RWDBStatus& status,
                          RWDBConnection::ConnectionType connType);
    virtual
    ~RWDBOCIXASystemHandle();

    virtual
    void                       initialize();

    virtual
    void                       rwopen(const RWCString& user,
                                      const RWCString& pass,
                                      const RWCString& db,
                                      const RWCString& server,
                                      RWDBConnection::ConnectionType connType,
                                      RWDBStatus& status);
    virtual
    void                       rwclose(RWDBStatus& status);

    // ** THESE METHODS SHOULD NOT BE CALLED BY AN APPLICATION PROGRAM **,
    // since transaction management in XA connections is handled by the TPM.
    virtual
    void                       commitTransaction(RWDBStatus& status);
    virtual
    void                       rollbackTransaction(RWDBStatus& status);

protected:
    virtual
    sword                      allocateResource();

private:
    RWDBConnection::ConnectionType connType_;

    // not implemented
    RWDBOCIXASystemHandle(const RWDBOCIXASystemHandle&);
    RWDBOCIXASystemHandle& operator=(const RWDBOCIXASystemHandle&);

};

#endif //  __RWDB_OCIXASYSH_H__
