#ifndef __rw_pointer_instance_h__
#define  __rw_pointer_instance_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/instance.h#1 $
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

#include <rw/pointer/RWTCountingBody.h>

// Template instantiation inside the library; the RWTMonitor <RWMutexLock>
// instantiation has to happen inside the library to prevent linker errors
// in modules that instantiate these templates *and* link with the pointer
// library, since the template will get instantiated in both. Same for the
// RWTCountingBody<RWMutexLock>

#if defined(RW_POINTER_INSTANTIATE_TEMPLATES)

template class RW_POINTER_SYMBOLIC RWTCountingBody <RWMutexLock>;

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
class RWTCountingBody <RWMutexLock> : public RWTMonitor < RWMutexLock >
{
public:

    ~RWTCountingBody(void);

    unsigned
    references(void) const;

    unsigned
    addReference(void);

    unsigned
    removeReference(void);

protected:

    RWTCountingBody(unsigned initCount = 0);

    RWTCountingBody(RWStaticCtor);

    RWTCountingBody(const RWTCountingBody<RWMutexLock>& second);

    RWTCountingBody<RWMutexLock>&
    operator=(const RWTCountingBody<RWMutexLock>& second);

#    if !defined(RW_DISABLE_DEPRECATED)
    typedef RWTLockGuard   < RWTMonitor<RWMutexLock> >  Guard;
#    endif

    typedef RWTLockGuard   < RWTMonitor<RWMutexLock> >  LockGuard;
    typedef RWTUnlockGuard < RWTMonitor<RWMutexLock> >  UnlockGuard;
    typedef RWTTryLockGuard< RWTMonitor<RWMutexLock> >  TryLockGuard;

protected:
    unsigned refs_;
};

#  else
#    if defined(_RWBUILD_pointer)
extern template class RWTCountingBody <RWMutexLock>;
#    else
extern template class RW_POINTER_SYMBOLIC RWTCountingBody <RWMutexLock>;
#    endif  // _RWBUILD_pointer

#  endif // defined (__SUNPRO_CC) || defined (__IBMCPP__) 

#endif // RW_POINTER_INSTANTIATE

#endif // __rw_pointer_instance_h__
