#ifndef RW_CURRENCY_DECDEFS_H
#define RW_CURRENCY_DECDEFS_H

/***************************************************************************
 * Macro definitions removed from decbase, decport and decin
 * but still needed for backward compatibility
 *
 * $Id: //spro/rel2016.1/rw/currency/decdefs.h#1 $
 *
 * Copyright (c) 1993-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

/* for backward compatibility */
#ifndef RW_MONEY_DECDEFS_H
#  define RW_MONEY_DECDEFS_H
#endif

#include <rw/dcmldefs.h>

// Support for new product wide using DLL macro:
#ifdef RWDLL
#  ifndef _RWDCMLDLL
#    define _RWDCMLDLL 1
#  endif
#endif


#if defined(_RWDCMLBUILDDLL) || defined(_RWBUILDDLL) || defined(_RWDBBUILDDLL)
#  ifndef _RWDCMLDLL
#    define _RWDCMLDLL 1
#  endif
#  ifndef _RWTOOLSDLL
#    define _RWTOOLSDLL 1
#  endif
#  ifndef _RWDBDLL
#    define _RWDBDLL 1
#  endif
#endif

#if defined(_RWBUILD_mny)
#  ifndef _RWDCMLBUILDDLL
#    define _RWDCMLBUILDDLL
#  endif
#endif

// The Currency Module DLL related defines.
#if (RW_SHARED)
#  if defined(_RWDCMLBUILDDLL) || defined(_RWBUILDDLL) || defined(_RWDBBUILDDLL)
// Compiling the Currency Module DLL.
#    define RW_DCML_GLOBAL          RW_COMPILER_GLOBAL_EXPORT
#    define RW_DCML_SYMBOLIC        RW_COMPILER_SYMBOLIC_EXPORT
#    define RW_DCML_MEMBER_EXPORT   RW_COMPILER_SYMBOLIC_EXPORT
#  else // Using the Currency Module DLL.
#    define RW_DCML_GLOBAL    RW_COMPILER_GLOBAL_IMPORT
#    define RW_DCML_SYMBOLIC  RW_COMPILER_GLOBAL_IMPORT
#    define RW_DCML_MEMBER_EXPORT
#  endif
#else
// Neither compiling, nor using the Currency Module DLL.
#  define RW_DCML_GLOBAL
#  define RW_DCML_SYMBOLIC
#  define RW_DCML_MEMBER_EXPORT
#endif

#endif //  RW_CURRENCY_DECDEFS_H
