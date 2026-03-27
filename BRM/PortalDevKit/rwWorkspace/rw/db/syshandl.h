#ifndef __RWDB_SYSHANDL_H__
#define __RWDB_SYSHANDL_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/syshandl.h#1 $
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
 * RWDBSystemHandle is a base class for database-specific "handles."
 * Each DB Access Module defines a system handle for its
 * own database. The nature system handles can be expected to vary
 * widely among access libraries. Applications that wish to access
 * an underlying API directly can do so by obtaining a system handle pointer
 * from a database connection (RWDBConnection) and downcasting the result
 * to the known type.
 *
 **************************************************************************/

#include <rw/db/conncb.h>
#include <rw/db/dbref.h>
#include <rw/db/defs.h>


/**
 * \ingroup db_common_group
 *
 * \brief
 * Base class for database-specific classes that provide direct access to
 * the database API.
 *
 * RWDBSystemHandle is a base class for system handles that are Access
 * Module-specific. Each DB Access Module defines a system handle for its
 * own database that encapsulates database vendor-specific handles. These
 * handles provide access to the underlying database functionality, and vary
 * widely among Access Modules.
 *
 * To access your database-specific handle, obtain the RWDBSystemHandle
 * pointer from an RWDBConnection, and then downcast it to the Access
 * Module-specific system handle type. For more information, see your DB
 * Access Module guide.
 *
 * <b>DB XA Module:</b> Also see the chapter on using access modules with DB
 * XA functionality in the <em>DB XA Module User's Guide</em>.
 *
 * \note
 * To use this class, link the appropriate SourcePro DB Access Module
 * directly with your application. Using this class reduces the portability
 * of your application.
 *
 * \synopsis
 * #include<rw/db/syshandl.h>
 *
 * RWDBConnection connection = myDbase.connection();
 * RWDBSystemHandle* sysh = connection.systemHandle();
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBSystemHandle
    : public RWDBReference
{
public:
    RWDBSystemHandle(RWDBEnvironmentHandle* env);
    virtual ~RWDBSystemHandle();

    size_t defaultReaderCache() const;
    size_t defaultReaderCache(size_t);

    //For internal use only:
    virtual void initialize();
    void connCallback(const RWDBConnCallback& callback);
    RWDBConnCallback connCallback() const;

protected:
    RWDBCountedRef<RWDBEnvironmentHandle>   environmentHandle_;
    RWDBConnCallback conncb_;
    size_t defaultReaderCache_;

private:
    //Unimplemented:
    RWDBSystemHandle(const RWDBSystemHandle& handle);
    RWDBSystemHandle& operator=(const RWDBSystemHandle& handle);
};

#endif
