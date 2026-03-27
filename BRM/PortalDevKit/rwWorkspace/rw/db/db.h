#ifndef __RWDB_DB_H__
#define __RWDB_DB_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/db.h#1 $
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


//////////////////////////////////////////////////////////////////////////
//
// Applications can #include specific header files of interest,
// or, instead, they may simply #include this header.  The latter strategy
// has in impact on compile-time efficiency, but is considerably simpler.
//
//////////////////////////////////////////////////////////////////////////

#include <rw/db/bkins.h>
#include <rw/db/bkread.h>
#include <rw/db/blob.h>
#include <rw/db/cachemgr.h>
#include <rw/db/checkconstr.h>
#include <rw/db/column.h>
#include <rw/db/comsel.h>
#include <rw/db/connect.h>
#include <rw/db/cursor.h>
#include <rw/db/datetime.h>
#include <rw/db/dbase.h>
#include <rw/db/dberr.h>
#include <rw/db/dbmgr.h>
#include <rw/db/defs.h>
#include <rw/db/deleter.h>
#include <rw/db/duration.h>
#include <rw/db/envhandl.h>
#include <rw/db/expr.h>
#include <rw/db/forkey.h>
#include <rw/db/func.h>
#include <rw/db/future.h>
#include <rw/db/identity.h>
#include <rw/db/inserter.h>
#include <rw/db/memcache.h>
#include <rw/db/memtable.h>
#include <rw/db/nullind.h>
#include <rw/db/osql.h>
#include <rw/db/phrase.h>
#include <rw/db/prece.h>
#include <rw/db/primarykey.h>
#include <rw/db/reader.h>
#include <rw/db/result.h>
#include <rw/db/row.h>
#include <rw/db/schema.h>
#include <rw/db/select.h>
#include <rw/db/status.h>
#include <rw/db/stored.h>
#include <rw/db/syshandl.h>
#include <rw/db/table.h>
#include <rw/db/tmtbase.h>
#include <rw/db/tracer.h>
#include <rw/db/uniqueconstr.h>
#include <rw/db/updater.h>
#include <rw/db/value.h>
#include <rw/collect.h>
#include <rw/decport.h>

#endif
