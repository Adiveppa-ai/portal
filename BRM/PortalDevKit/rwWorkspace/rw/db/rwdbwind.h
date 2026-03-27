#ifndef __RWDB_WIND_H__
#define __RWDB_WIND_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/rwdbwind.h#1 $
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

/*
 * Check for Microsoft C/C++ and massage as necessary.
 */
#if defined(_MSC_VER)
#  if defined(_WINDLL) && !defined(__DLL__)
#    define __DLL__ 1
#  endif
#  if !defined(_export)
#    define _export __export
#  endif
#endif


/*
 * Check for DLL builds / usage
 */
#if defined(RW_DLL) || defined(RW_SHARED)
// Compiling the DB Interface Module DLL.
#  if defined(_RWDBTBUILDDLL)
#    define RWDB_GLOBAL         RW_COMPILER_GLOBAL_EXPORT
#    define RWDB_SYMBOLIC       RW_COMPILER_SYMBOLIC_EXPORT
#  else
// Using the DB Interface Module DLL.
#    define RWDB_GLOBAL         RW_COMPILER_GLOBAL_IMPORT
#    define RWDB_SYMBOLIC       RW_COMPILER_GLOBAL_IMPORT
#  endif

// Compiling the DB Access Module DLL.
#  if defined(_RWDBTACCESSBUILDDLL)
#    define RWDB_ACCESS_GLOBAL      RW_COMPILER_GLOBAL_EXPORT
#    define RWDB_ACCESS_SYMBOLIC    RW_COMPILER_SYMBOLIC_EXPORT
#  else
// Using the DB Access Module DLL.
#    define RWDB_ACCESS_GLOBAL      RW_COMPILER_GLOBAL_IMPORT
#    define RWDB_ACCESS_SYMBOLIC    RW_COMPILER_GLOBAL_IMPORT
#  endif

#else
// Neither compiling, nor using the DLLs
#  define RWDB_GLOBAL
#  define RWDB_SYMBOLIC
#  define RWDB_ACCESS_GLOBAL
#  define RWDB_ACCESS_SYMBOLIC
#endif

/*
 * Disable near/far pointers and pascal calling convention
 * if they are still present in our code.
 */
#define rwdbnear
#define rwdbfar
#define rwdbhuge
#define rwdbpascal

#endif
