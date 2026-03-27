#ifndef __rw_trace_RWTraceManagerImp_h__
#define __rw_trace_RWTraceManagerImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceManagerImp.h#1 $
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

#include <rw/trace/RWTraceEvent.h>
#include <rw/trace/RWTraceLevelFilterImp.h>
#include <rw/trace/RWTraceManager.h>
#include <rw/trace/pkgdefs.h>
#include <rw/once.h>
#include <rw/rwerr.h>
#include <rw/tvslist.h>

#if !defined(RW_MULTI_THREAD)
// no thread local storage needed
#elif defined(RW_THR_THREAD_API_POSIX)
#  include <pthread.h>
#elif defined(RW_THR_THREAD_API_SOLARIS)
#  include <thread.h>
#elif defined(RW_THR_THREAD_API_WIN32)
#else
#  error Thread Local Storage is not supported in this environment!
#endif

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251 )
#endif

class RW_TRACE_GLOBAL RWTraceManagerImp
    : public RWTraceLevelFilterImp
{

public:

    static RWTraceManager
    instance(void);

    int
    registerSet(const char* set, int (*const superfn)());

private:

    RWTraceManagerImp(void);

    RWTraceManagerImp(const RWTraceManagerImp& rhs);

    ~RWTraceManagerImp(void);

    RWTraceManagerImp&
    operator=(const RWTraceManagerImp& rhs);

    static void
    init();

protected:

    virtual void
    doAdd(RWTraceEventClientImp* clientP);

    virtual void
    doTrace(const RWTraceEvent& ev);

private:

    bool
    isTracing(void) const;

    void
    setTracing(bool set);

    friend struct TracingGuard;

#if !defined(RW_MULTI_THREAD)
    bool key_;
#elif defined(RW_THR_THREAD_API_POSIX)
    pthread_key_t key_;
#elif defined(RW_THR_THREAD_API_SOLARIS)
    thread_key_t key_;
#elif defined(RW_THR_THREAD_API_WIN32)
    // use an explicit unsigned long instead of a DWORD
    unsigned long key_;
#endif

    size_t maxBufSize_;

    RWTValSlist<RWTraceEvent> buffer_;

    static RWOnce initInstanceOnce_;
    static RWTraceManagerImp* instance_;

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif


#endif // __rw_trace_RWTraceManagerImp_h__
