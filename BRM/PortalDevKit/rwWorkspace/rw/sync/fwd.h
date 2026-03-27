#ifndef __rw_sync_fwd_h__
#define __rw_sync_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/fwd.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 *************************************************************************/

#include <rw/sync/pkgdefs.h>

class RW_SYNC_SYMBOLIC RWBarrier;
class RW_SYNC_SYMBOLIC RWCondition;
class RW_SYNC_SYMBOLIC RWCriticalSection;
class RW_SYNC_SYMBOLIC RWFIFOMutexLock;
class RW_SYNC_SYMBOLIC RWMutexLock;
class RW_SYNC_SYMBOLIC RWNullMutexLock;
class RW_SYNC_SYMBOLIC RWReadersWriterLock;
class RW_SYNC_SYMBOLIC RWSemaphore;
class RW_SYNC_SYMBOLIC RWSynchObject;
class RW_SYNC_SYMBOLIC RWThreadId;
template <class T> class RWTRecursiveLock;
template <class T> class RWTGuardBase;
template <class T> class RWTLockGuardBase;
template <class T> class RWTReadGuardBase;
template <class T> class RWTReadLockGuardBase;
template <class T> class RWTWriteGuardBase;
template <class T> class RWTWriteLockGuardBase;
template <class T> class RWTLockGuard;
template <class T> class RWTMonitor;
template <class T> class RWTReadLockGuard;
template <class T> class RWTReadUnlockGuard;
template <class T> class RWTTryLockGuard;
template <class T> class RWTTryReadLockGuard;
template <class T> class RWTTryWriteLockGuard;
template <class T> class RWTUnlockGuard;
template <class T> class RWTWriteLockGuard;
template <class T> class RWTWriteUnlockGuard;

#endif // __rw_sync_fwd_h__
