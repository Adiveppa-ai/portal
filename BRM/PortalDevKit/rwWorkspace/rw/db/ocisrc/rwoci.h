#ifndef __RWDB_OCIOCI_H__
#define __RWDB_OCIOCI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/rwoci.h#1 $
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
 * Oracle OCI Access Module inclusion of oracle's header files.
 *
 **************************************************************************/
#if defined(__hpux)
#  include <unistd.h>
#endif

extern "C" {
#ifdef _WIN32
#  include <windows.h>
#endif

#include <oci.h>
}

#undef min
#undef max

#if defined(__hpux)
#  include <limits>
#endif

// Oracle OCI has some methods which take argument(s) of type dvoid**. These
// methods need to be passed pointers to object pointers type-punned as
// dvoid**. This typedef RWDBOCIdvoidp is created to indicate to the gcc
// compiler that objects can be type-punned to this type.
#if ( (__GNUG__ >= 4) || ( (__GNUG__ == 3) && (__GNUC_MINOR__ >= 3) ) )
typedef dvoid* __attribute__((__may_alias__)) RWDBOCIdvoidp;
#else
typedef dvoid* RWDBOCIdvoidp;
#endif

#endif
