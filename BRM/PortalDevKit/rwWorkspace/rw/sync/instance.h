#ifndef __rw_sync_instance_h__
#define  __rw_sync_instance_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/instance.h#1 $
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

// Hack to prevent the tons of warnings poured by
// GCC when encountering the extern template extension
#if __GNUG__ >= 3
#  pragma GCC system_header
#endif   // gcc >= 3

#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWTMonitor.h>

// Template instantiation inside the library; the RWTMonitor <RWMutexLock>
// instantiation has to happen inside the library to prevent linker errors
// in modules that instantiate these templates *and* link with the pointer
// library, since the template will get instantiated in both.

#if defined(RW_SYNC_INSTANTIATE_TEMPLATES)

template class RW_SYNC_SYMBOLIC RWTMonitor <RWMutexLock>;

#else

#  if defined(_MSC_VER)
#    pragma warning (disable: 4231)
#  endif // _MSC_VER

// Here, depending on the compiler capabilities, we either declare the
// template instantiation "extern" or we define an incomplete specialization
// that will force the linker to lookup the implementation of the member
// functions inside the library

#  if  defined(__SUNPRO_CC) || defined(__IBMCPP__)

template <>
class RWTMonitor <RWMutexLock>
{
public:

    typedef RWMutexLock MutexType;

protected:

    RWMutexLock  mutex_;

protected:

    RWTMonitor(void);

    RWTMonitor(RWStaticCtor);

    RWTMonitor(RWNoInitialization);

    RWTMonitor(const RWTMonitor<RWMutexLock>& second);

    ~RWTMonitor(void);

    RWTMonitor<RWMutexLock>&
    operator=(const RWTMonitor<RWMutexLock>&);

    void
    acquire(void);

#    if defined(RW_SYNC_DEBUG)

    bool
    isAcquired(void) const;

#    endif

    RWTMonitor<RWMutexLock>&
    monitor(void) const;

    RWMutexLock&
    mutex(void);

    void
    release(void);

    bool
    tryAcquire(void);

#    if defined(RW_NO_SELF_REFERENCING_FRIEND_DECLARATIONS)

    typedef RWTLockGuard< RWTMonitor< RWMutexLock > >     LockGuard;
    typedef RWTUnlockGuard< RWTMonitor< RWMutexLock > >   UnlockGuard;
    typedef RWTTryLockGuard< RWTMonitor< RWMutexLock > >  TryLockGuard;

private:

    typedef RWTGuardBase< RWTMonitor< RWMutexLock > >     GuardBase;
    typedef RWTLockGuardBase< RWTMonitor< RWMutexLock > > LockGuardBase;


    friend class GuardBase;
    friend class LockGuardBase;
    friend class LockGuard;
    friend class UnlockGuard;
    friend class TryLockGuard;

#    else

    friend class RWTGuardBase< RWTMonitor< RWMutexLock > >;
    friend class RWTLockGuardBase< RWTMonitor< RWMutexLock > >;
    friend class RWTLockGuard< RWTMonitor< RWMutexLock > >;
    friend class RWTTryLockGuard< RWTMonitor< RWMutexLock > >;
    friend class RWTUnlockGuard< RWTMonitor< RWMutexLock > >;

    typedef RWTLockGuard< RWTMonitor< RWMutexLock > >     LockGuard;
    typedef RWTUnlockGuard< RWTMonitor< RWMutexLock > >   UnlockGuard;
    typedef RWTTryLockGuard< RWTMonitor< RWMutexLock > >  TryLockGuard;
#    endif

};

#  else

extern template class RW_SYNC_SYMBOLIC RWTMonitor <RWMutexLock>;

#  endif // defined (__SUNPRO_CC) || defined (__IBMCPP__) 

#endif // RW_SYNC_INSTANTIATE


#endif // __rw_sync_instance_h__
