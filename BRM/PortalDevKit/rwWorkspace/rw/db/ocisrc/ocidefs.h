#ifndef __RWDB_OCIDEFS_H__
#define __RWDB_OCIDEFS_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocidefs.h#1 $
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
 * Definitions for Oracle OCI Access Module
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/defs.h>

//////////////////////////////////////////////////////////////////////////
//
// defines for tables used to get schema information like default column
// values, check constraints
//
//////////////////////////////////////////////////////////////////////////
#define RWDB_ALL_CONSTRAINTS  "ALL_CONSTRAINTS"
#define RWDB_ALL_CONS_COLUMNS "ALL_CONS_COLUMNS"

//////////////////////////////////////////////////////////////////////////
//
// The DB Interface Module communicates with its access modules via
// a single C routine conventionally named 'newDatabaseImp.'
// This routine returns a pointer to a database implementation
// typed according to the access module in which the routine resides.
//
// Where Dynamic Linking is not in use, the routine has to have a unique
// name, which is known at compile time to its "magic cookie"
// object.
//
// These macros are used to declare and reference the newDatabaseImp
// routine in this access module.
//
//////////////////////////////////////////////////////////////////////////

#if defined(RW_DLL) || defined(RW_SHARED)
#  ifndef RW_TRAILING_RWEXPORT
#    define RWDBNEWDBPROCDECL RWDB_ACCESS_SYMBOLIC RWDBDatabaseImp* RWDBNEWDBPROCNAME
#  else
#    define RWDBNEWDBPROCDECL  RWDBDatabaseImp* RWDB_ACCESS_SYMBOLIC RWDBNEWDBPROCNAME
#  endif
#  define RWDBNEWOCILIBPROCNAME RWDBNEWDBPROCNAME
#else
#  define RWDBNEWOCILIBPROCNAME RWDBNEWOCILIBPROCNAME
#  define RWDBNEWDBPROCDECL RWDBDatabaseImp* rwdbfar RWDBNEWOCILIBPROCNAME
#endif

#define RWDB_OCI_TYPE_XMLTYPE 25

#endif
