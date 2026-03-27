#ifndef __RWDB_OCIXADEFS_H__
#define __RWDB_OCIXADEFS_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocixadefs.h#1 $
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
 * Definitions for Oracle OCI XA Access Module
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/defs.h>


//////////////////////////////////////////////////////////////////////////
//
// The DB Interface Module communicates with its XA access modules via
// a single C routine conventionally named 'newXADatabaseImp.'
// This routine returns a pointer to a XA database implementation
// typed according to the access module in which the routine resides.
//
// Where Dynamic Linking is not in use, the routine has to have a unique
// name, which is known at compile time to its "magic cookie"
// object.
//
// These macros are used to declare and reference the newXADatabaseImp
// routine in this access module.
//
// Besides declaring Vendor specific database implementation, following
// definitions are also used to declare a function which returns Vendor
// specific XA switch.
//
//////////////////////////////////////////////////////////////////////////

#if defined(RW_DLL) || defined(RW_SHARED)
#  ifndef RW_TRAILING_RWEXPORT
#    define RWDBNEWOCIXAPROCDECL RWDB_ACCESS_SYMBOLIC RWDBDatabaseImp* rwdbfar RWDBNEWDBXAPROCNAME
#    define RWDBOCIXASWITCHFUNCDECL RWDB_ACCESS_SYMBOLIC void* rwdbfar RWDBXASWITCHFUNCNAME
#  else
#    define RWDBNEWOCIXAPROCDECL RWDBDatabaseImp* RWDB_ACCESS_SYMBOLIC rwdbfar RWDBNEWDBXAPROCNAME
#    define RWDBOCIXASWITCHFUNCDECL void* RWDB_ACCESS_SYMBOLIC rwdbfar RWDBXASWITCHFUNCNAME
#  endif
#  define RWDBNEWOCIXAPROCNAME            RWDBNEWDBXAPROCNAME
#  define RWDBOCIXASWITCHFUNCNAME         RWDBXASWITCHFUNCNAME
#else
#  define RWDBNEWOCIXAPROCNAME        newOciXADatabaseImp
#  define RWDBOCIXASWITCHFUNCNAME     rwdbOciXaSwitch
#  define RWDBNEWOCIXAPROCDECL RWDBDatabaseImp* rwdbfar RWDBNEWOCIXAPROCNAME
#  define RWDBOCIXASWITCHFUNCDECL   void*  rwdbfar RWDBOCIXASWITCHFUNCNAME
#endif


#endif //  __RWDB_OCIXADEFS_H__
