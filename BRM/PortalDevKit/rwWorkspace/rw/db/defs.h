#ifndef __RWDB_DEFS_H__
#define __RWDB_DEFS_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/defs.h#1 $
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

#include <rw/config/rwconfig_dbt.h>  // RW_MULTI_THREAD
#include <rw/compiler.h>
#include <rw/defs.h>

// Define compatibility macro
#define RWDBTOOLS    RW_DBCORE_VERSION

// Set the DB Interface Module build macro _RWDBTBUILDDLL if appropriate.
#if (defined(RW_DLL) || defined(RW_SHARED)) && defined(_RWBUILD_dbt)
#  define _RWDBTBUILDDLL
#endif

// Following Block is to resolve definitions for Access Module Builds
// It includes Access Module specific header files and also defines
//    the _RWDBTACCESSBUILDDLL macro if appropriate.
#if defined(_RWBUILD_ora)
#  include <rw/config/rwconfig_ora.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_oci)
#  include <rw/config/rwconfig_oci.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_ctl)
#  include <rw/config/rwconfig_ctl.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_odb)
#  include <rw/config/rwconfig_odb.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_inf)
#  include <rw/config/rwconfig_inf.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_msq)
#  include <rw/config/rwconfig_msq.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_db2)
#  include <rw/config/rwconfig_db2.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_mys)
#  include <rw/config/rwconfig_mys.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#elif defined(_RWBUILD_pgs)
#  include <rw/config/rwconfig_pgs.h>
#  if defined(RW_DLL) || defined(RW_SHARED)
#    define _RWDBTACCESSBUILDDLL
#  endif
#endif

#ifdef RW_MULTI_THREAD
#  ifdef _WIN32
#    include <windows.h>
#  endif
#endif

// The following two preprocessing blocks are provided for backward compatibility for our old shared library and
// DLL macros
#ifndef RW_DLL
#  if defined(_RWDBDLL) || defined(_RWDBTBUILDDLL) || defined(_RWDBDYNLINK) || defined(_RWDBTACCESSBUILDDLL)
#    define RW_DLL 1
#  endif
#endif

#include <rw/defs.h>    /* Get compiler-specific flags and Tools.h++ defines */

/*
 * Export specific
 */
#include <rw/db/rwdbwind.h>

/*
 * This macro remains to exist entirely for customers that depend on it.
 * It was conditionally #defined it to _CLASSTYPE for the Borland Turbo
 * C++ compiler.
 */
#define _RWDBCLASSTYPE


//////////////////////////////////////////////////////////////////////////
// Public Collectable Class IDs
//////////////////////////////////////////////////////////////////////////
#define __RWDBVALUE  0x8DB0
#define __RWDBBLOB   0x8DB1
#define __RWDBROW    0x8DB2
#define __RWDBCHECKCONSTRAINT  0x8DB3
#define __RWDBUNIQUECONSTRAINT 0x8DB4
#define __RWDBFOREIGNKEY       0x8DB5
#define __RWDBFOREIGNKEYLIST   0x8DB6
#define __RWDBCOLLECTABLEEXPR  0x8DB7
#define __RWDBCOLLECTABLECOLUMN   0x8DB8

//////////////////////////////////////////////////////////////////////////
// Classes
//////////////////////////////////////////////////////////////////////////

class RWDB_SYMBOLIC RWDBAbstractNullIndicator;
class RWDB_GLOBAL RWDBAssignment;
class RWDB_GLOBAL RWDBBlob;
class RWDB_GLOBAL RWDBBuffer;
typedef RWDBBuffer RWDBAbstractBuffer;
class RWDB_GLOBAL RWDBBufferFactory;
class RWDB_GLOBAL RWDBCacheManager;
class RWDB_GLOBAL RWDBCallbackBuffer;
class RWDB_GLOBAL RWDBCheckConstraint;
class RWDB_GLOBAL RWDBCheckConstraintList;
class RWDB_GLOBAL RWDBColumn;
class RWDB_GLOBAL RWDBCompoundSelector;
class RWDB_SYMBOLIC RWDBConnection;
class RWDB_SYMBOLIC RWDBConnCallback;
class RWDB_GLOBAL RWDBCriterion;
class RWDB_GLOBAL RWDBCursor;
class RWDB_GLOBAL RWDBDatabase;
class RWDB_SYMBOLIC RWDBDatabaseCallback;
class RWDB_GLOBAL RWDBDataCallback;
#if !defined(RW_DISABLE_DEPRECATED)
class RWDB_GLOBAL RWDBDateTime;
class RWDB_SYMBOLIC RWDBDateVector;
#endif
class RWDB_GLOBAL RWDBDeleter;
class RWDB_GLOBAL RWDBDuration;
class RWDB_SYMBOLIC RWDBEntry;
class RWDB_GLOBAL RWDBEnvironmentHandle;
class RWDB_GLOBAL RWDBExpr;
class RWDB_GLOBAL RWDBJoinExpr;
class RWDB_GLOBAL RWDBForeignKey;
class RWDB_GLOBAL RWDBForeignKeyList;
class RWDB_GLOBAL RWDBFuture;
class RWDB_GLOBAL RWDBGenericBufferFactory;
class RWDB_SYMBOLIC RWDBHandle;
class RWDB_SYMBOLIC RWDBIdentityConstraint;
class RWDB_SYMBOLIC RWDBInserter;
class RWDB_GLOBAL RWDBInMemoryCacheManager;
class RWDB_GLOBAL RWDBManager;
class RWDB_GLOBAL RWDBMemTable;
class RWDB_SYMBOLIC RWDBMultiRow;
class RWDB_GLOBAL RWDBReference;
class RWDB_SYMBOLIC RWDBNullIndicator;
class RWDB_SYMBOLIC RWDBOSql;
class RWDB_SYMBOLIC RWDBPhraseBook;
class RWDB_SYMBOLIC RWDBPrecedence;
class RWDB_SYMBOLIC RWDBPrimaryKey;
class RWDB_SYMBOLIC RWDBReader;
class RWDB_GLOBAL RWDBReference;
class RWDB_GLOBAL RWDBResult;
class RWDB_GLOBAL RWDBRow;
class RWDB_GLOBAL RWDBSchema;
class RWDB_GLOBAL RWDBSelector;
class RWDB_GLOBAL RWDBSelectorBase;
class RWDB_GLOBAL RWDBShiftableRow;
class RWDB_GLOBAL RWDBStatus;
class RWDB_GLOBAL RWDBStoredProc;
class RWDB_SYMBOLIC RWDBStoredProcEntry;
class RWDB_GLOBAL RWDBSystemHandle;
class RWDB_GLOBAL RWDBTable;
class RWDB_SYMBOLIC RWDBTableEntry;
class RWDB_SYMBOLIC RWDBTracer;
class RWDB_GLOBAL RWDBUniqueConstraint;
class RWDB_GLOBAL RWDBUniqueConstraintList;
class RWDB_SYMBOLIC RWDBUpdater;
class RWDB_GLOBAL RWDBValue;

class RWDB_GLOBAL RWDBBulkInserterImp;
class RWDB_GLOBAL RWDBBulkReaderImp;
class RWDB_GLOBAL RWDBCheckConstraintImp;
class RWDB_GLOBAL RWDBColumnImp;
class RWDB_GLOBAL RWDBCompoundSelectorImp;
class RWDB_GLOBAL RWDBConnectionImp;
class RWDB_GLOBAL RWDBConnCallbackImp;
class RWDB_GLOBAL RWDBCursorImp;
class RWDB_GLOBAL RWDBDatabaseImp;
class RWDB_GLOBAL RWDBDatabaseCallbackImp;
class RWDB_GLOBAL RWDBDatabaseTableImp;
#if !defined(RW_DISABLE_DEPRECATED)
class RWDB_GLOBAL RWDBDateVectorImp;
#endif
class RWDB_GLOBAL RWDBDeleterImp;
class RWDB_GLOBAL RWDBDerivedTableImp;
class RWDB_GLOBAL RWDBExprImp;
class RWDB_GLOBAL RWDBForeignKeyImp;
class RWDB_GLOBAL RWDBFutureImp;
class RWDB_GLOBAL RWDBHandleImp;
class RWDB_GLOBAL RWDBIdentityConstraintImp;
class RWDB_GLOBAL RWDBInserterImp;
class RWDB_GLOBAL RWDBMultiRowImp;
class RWDB_GLOBAL RWDBOSqlImp;
class RWDB_GLOBAL RWDBPrimaryKeyImp;
class RWDB_GLOBAL RWDBReaderImp;
class RWDB_GLOBAL RWDBResultImp;
class RWDB_GLOBAL RWDBResultTableImp;
class RWDB_GLOBAL RWDBRowImp;
class RWDB_GLOBAL RWDBSchemaImp;
class RWDB_GLOBAL RWDBSelectorBaseImp;
class RWDB_GLOBAL RWDBSelectorImp;
class RWDB_GLOBAL RWDBStatusImp;
class RWDB_GLOBAL RWDBStatementImp;
class RWDB_GLOBAL RWDBStoredProcImp;
class RWDB_GLOBAL RWDBTableImp;
class RWDB_GLOBAL RWDBUniqueConstraintImp;
class RWDB_GLOBAL RWDBUpdaterImp;


//////////////////////////////////////////////////////////////////////////
// Borrowed Classes
//////////////////////////////////////////////////////////////////////////

class RWExport RWDecimalPortable;

class RWExport RWCString;
class RWExport RWDate;
class RWExport RWTime;
class RWExport RWSet;

//////////////////////////////////////////////////////////////////////////
// Macros
//////////////////////////////////////////////////////////////////////////

#define RWDBNEWDBPROCNAME            newDatabaseImp
#define RWDBNEWDBXAPROCNAME          newXADatabaseImp

#define RWDBNEWDLLPROCNAME           newDatabaseImp
#define RWDBNEWDLLXAPROCNAME         newXADatabaseImp

#define RWDBXASWITCHFUNCNAME         newXASwitch

#define RWDBNEWIMPARGS  const RWCString&, const RWCString&, const RWCString&,\
                        const RWCString&, const RWCString&, const RWCString&

extern "C"
{
    typedef RWDBDatabaseImp* (rwdbfar* RWDBNewImpFunc)(RWDBNEWIMPARGS);
    typedef void*            (*RWDBXASwitchFunc)();
}

#define RWDBENQUOTE(name)            # name
#define RWDBQUOTE(name)              RWDBENQUOTE(name)

#include <float.h>            // floating point limits are defined in this file.
#include <limits.h>
/**
 * \ingroup db_common_group
 *
 * Sentinel to indicate an unknown value.
 */
#define RWDB_NO_TRAIT                -INT_MAX

#ifndef DBL_DIG
#  define DBL_DIG     15        /* not defined, use SUN's DBL_DIG */
#endif

////////////////////////////////////////////////////////////////////////
//
//  RWDB_MEMBER_MAX and RWDB_MEMBER_MIN macro
//      These macros are required if NOMINMAX is not defined.
//      MSVC defines min() and max() as macros and the precompiler
//      uses the macro magic on any methods that use these names.
//      Even for calling these methods, one needs to use:
//          (obj.max)(values...)  instead of obj.max(values...)
////////////////////////////////////////////////////////////////////////
#if defined(_WIN32)
#  define RWDB_MEMBER_MAX (max)
#  define RWDB_MEMBER_MIN (min)
#else
#  define RWDB_MEMBER_MAX max
#  define RWDB_MEMBER_MIN min
#endif


#if defined(RW_NO_NEW_TEMPLATE_SYNTAX)
#  define RWDBTEMPLATESPECDECL
#else
#  define RWDBTEMPLATESPECDECL template<>
#endif

// Template min-max functions
template<class T>
T rwdbmax(const T& a, const T& b)
{
    if (a < b) {
        return b;
    }
    else {
        return a;
    }
}
template<class T>
T rwdbmin(const T& a, const T& b)
{
    if (b < a) {
        return b;
    }
    else {
        return a;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// This template function converts a void* pointer to a pointer to a function
//
////////////////////////////////////////////////////////////////////////////////
template <class T>
T rwdbtConvertToFunctionPointer(void* vptr)
{
    union {
        T p;
        void* vp;
    } u;

    RW_ASSERT(sizeof(u.p) == sizeof(u.vp));

    u.vp = vptr;
    return u.p;
}

////////////////////////////////////////////////////////////////////////////////
//
// This template function converts a function to a void* pointer
//
////////////////////////////////////////////////////////////////////////////////
template <class T>
void* rwdbtConvertFunctionToVoidPointer(T funcToBeVoid)
{
    union {
        T p;
        void* vp;
    } u;

    RW_ASSERT(sizeof(u.p) == sizeof(u.vp));

    u.p = funcToBeVoid;
    return u.vp;
}


#endif
