#ifndef __RWDBMUTEX_H__
#define __RWDBMUTEX_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbmutex.h#1 $
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
 ***************************************************************************
 *
 * This class is a portable implementation of a simple mutex lock
 * to be used for synchronizing multiple threads within a single process.
 * It is not suitable for use among threads of different processes.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/mutex.h>


#ifndef     RWDB_USE_LEGACY_MUTEX
// New mutexes from Tools.
// Use static mutexes for static/global locks as they do not have constructor/
// destructors. Further they are POD structs and are safe for static usage
// without concerns about order of construction or destruction.
typedef     RWStaticFastMutex           RWDBStaticMutex;
typedef     RWStaticRecursiveMutex      RWDBStaticRecursiveMutex;
// The regular plain old mutexing (with atomic ops). Not for static duration
// usage but can be used elsewhere.
typedef     RWLocalFastMutex            RWDBLocalMutex;
typedef     RWLocalRecursiveMutex       RWDBLocalRecursiveMutex;

//=============================================================================
//      USAGE TABLE
//
//  Old Mutex               New Mutex
//                          static/global variable      local/member variable
// ---------------------------------------------------------------------------
// RWDBMutex                RWDBStaticRecursiveMutex   RWDBLocalRecursiveMutex
//
// RWDBLightWeightMutex     RWDBStaticMutex            RWDBLocalMutex
//----------------------------------------------------------------------------
//
// Earlier RWDBMutex was a typedef for RWRecursiveMutex and
// RWDBLightWeightMutex was a typedef for RWMutex.
//=============================================================================

#else   // RWDB_USE_LEGACY_MUTEX
#  include <rw/tools/recursivemutex.h>
//===================================================================
//  NOTE: These are provided only for convenience and in case some
//        of problems the dev team can encounter. These are definitely
//        not safe to use and are not recommended.
//===================================================================
typedef     RWMutex               RWDBStaticMutex;
typedef     RWRecursiveMutex      RWDBStaticRecursiveMutex;
typedef     RWMutex               RWDBLocalMutex;
typedef     RWRecursiveMutex      RWDBLocalRecursiveMutex;

#endif  // RWDB_USE_LEGACY_MUTEX



#ifdef RW_MULTI_THREAD

template<class T>
class RWDBGuard
{
    T&   guard_;
public:
    RWDBGuard(const T& t) : guard_((T&)t)
    {
        guard_.acquire();
    }
    ~RWDBGuard()
    {
        guard_.release();
    }
};

//This guard is for objects that hold an implementation.
template<class T>
class RWDBGuardRef
{
    T   guardImp_;
public:
    RWDBGuardRef(const T& t) : guardImp_(t)
    {
        guardImp_.acquire();
    }
    ~RWDBGuardRef()
    {
        guardImp_.release();
    }
};

#  ifdef RWDB_USE_LEGACY_MUTEX
#    define RWDB_MUTEX_RECURSIVE_INITIALIZER
#    define RWDB_MUTEX_INITIALIZER
#  else
#    define RWDB_MUTEX_RECURSIVE_INITIALIZER \
            = RW_MUTEX_RECURSIVE_INITIALIZER
#    define RWDB_MUTEX_INITIALIZER \
            = RW_MUTEX_INITIALIZER
#  endif

#  define RWDBGUARD(C, O, S)       RWDBGuard<C>  dummyguard(O)
#  define RWDBGUARD2(C, O)         RWDBGUARD(C, O, "")

#  define RWDBGUARD_2(C, O, S)     RWDBGuard<C>  dummyguard2(O)
#  define RWDBGUARD2_2(C, O)       RWDBGUARD_2(C, O, "")

#  define RWDBGUARDREF(C, O, S)    RWDBGuardRef<C>  dummyguard(O)
#  define RWDBGUARD2REF(C, O)      RWDBGUARDREF(C, O, "")

#  define RWDBGUARDREF_2(C, O, S)  RWDBGuardRef<C>  dummyguard2(O)
#  define RWDBGUARD2REF_2(C, O)    RWDBGUARDREF_2(C, O, "")

#else

#  define RWDB_MUTEX_RECURSIVE_INITIALIZER
#  define RWDB_MUTEX_INITIALIZER

#  define RWDBGUARD(C, O, S)
#  define RWDBGUARD2(C, O)
#  define RWDBGUARDREF(C, O, S)
#  define RWDBGUARD2REF(C, O)
#  define RWDBGUARDREF_2(C, O, S)
#  define RWDBGUARD_2(C, O, S)
#  define RWDBGUARD2_2(C, O)
#  define RWDBGUARD2REF_2(C, O)

#endif

#endif  /* __RWDBMUTEX_H__ */
