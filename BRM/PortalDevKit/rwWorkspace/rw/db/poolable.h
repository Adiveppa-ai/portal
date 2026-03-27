#ifndef __RWDB_POOLABLE_H__
#define __RWDB_POOLABLE_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/poolable.h#1 $
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
 * Declaration of the Connection Pooling classes
 *
 **************************************************************************/

#include <rw/db/dbsrc/connecti.h>
#include <rw/db/connect.h>
#include <rw/db/defs.h>
#include <rw/tpdlist.h>

///////////////////////////////////////////////////////////////////////////
//
//  RWDBConnectionPool
//
///////////////////////////////////////////////////////////////////////////
class RWDB_SYMBOLIC RWDBConnectionPool
{
public:
    RWDBConnectionPool(size_t numberToRetain = 1);
    ~RWDBConnectionPool();

    void destroy();
    void destroyIfNeeded();

    RWDBConnectionImp* checkOut(const RWDBConnCallback& conncb,
                                RWDBConnection::ConnectionType,
                                bool useConnPool);
    bool checkIn(RWDBConnectionImp*);
    RWDBConnectionImp* factory(RWDBConnection::ConnectionType) const;

    long   entries() const;
    size_t numberToRetain() const;
    size_t numberToRetain(size_t);

    void parent(RWDBDatabaseImp*);

private:
    RWTPtrDlist<RWDBConnectionImp> pool_;
    RWDBDatabaseImp* parent_;
    size_t numberToRetain_;
    long   onLoan_;
};


#endif
