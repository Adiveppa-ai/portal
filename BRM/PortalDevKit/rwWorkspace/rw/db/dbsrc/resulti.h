#ifndef __RWDB_RESULTI_H__
#define __RWDB_RESULTI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/resulti.h#1 $
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

#include <rw/db/connect.h>
#include <rw/db/dbref.h>
#include <rw/db/osql.h>
#include <rw/db/status.h>
#include <rw/db/table.h>


//////////////////////////////////////////////////////////////////////////
//
// RWDBResultImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBResultImp
    : public RWDBReference,
      public RWDBStatus
{
    friend class RWDB_GLOBAL RWDBResult;
public:
    RWDBResultImp(const RWDBStatus& status);
    RWDBResultImp(const RWDBStatus& status,
                  const RWDBConnection& connection);
    RWDBResultImp(const RWDBStatus& status,
                  const RWDBConnection& connection,
                  RWDBOSql& osql);

    virtual                  ~RWDBResultImp();

    virtual RWDBConnection   connection() const;
    virtual RWDBTableImp*    tableImp();
    virtual RWDBStatus       status() const;
    virtual long             rowCount();
    virtual long             rowsAffected() const;

protected:
    RWDBConnection           connection_;
    RWDBOSql                 osql_;
    size_t                   currentResult_;
    RWDBTable                lastProducedTable_;

private:
    // not implemented
    RWDBResultImp(const RWDBResultImp&);
    RWDBResultImp& operator=(const RWDBResultImp&);
};

#endif
