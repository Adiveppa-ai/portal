#ifndef __RWDB_OCIXADB_H__
#define __RWDB_OCIXADB_H__

/***************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocixadb.h#1 $
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
 *  Oracle OCI XA Library implementation of RWDBDatabaseImp
 *
 **************************************************************************/

#include <rw/db/ocisrc/ocidb.h>
#include <rw/db/ocisrc/ocixaenvh.h>


class RWDB_ACCESS_GLOBAL RWDBOCIXADatabaseImp
    : public RWDBOCIDatabaseImp
{

public:
    RWDBOCIXADatabaseImp(const RWCString&,
                         const RWCString&,
                         const RWCString&,
                         const RWCString&,
                         const RWCString& connectString);
    virtual
    ~RWDBOCIXADatabaseImp();

    // producer method for XA enabled database connections.
    virtual
    RWDBConnectionImp*    connectionImp(RWDBConnection::ConnectionType type);

    // Returns the version string of the OCI XA Access Module
    virtual
    RWCString           version() const;

protected:
    static const
    RWCString           xaVersion_;

private:

    // not implemented
    RWDBOCIXADatabaseImp(const RWDBOCIXADatabaseImp&);
    RWDBOCIXADatabaseImp&  operator=(const RWDBOCIXADatabaseImp&);

};

#endif //  __RWDB_OCIXADB_H__
