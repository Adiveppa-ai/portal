#ifndef __rw_thread_RWThreadManagerImp_h__
#define __rw_thread_RWThreadManagerImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadManagerImp.h#1 $
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


/*****************************************************************************

  RWThreadManagerImp - Maintains dictionary of current thread object and
                       attempts orderly shutdown of threads at process exit.

******************************************************************************/

#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/pointer/RWBodyBase.h>
#include <rw/sync/RWReadersWriterLock.h>
#include <rw/sync/RWThreadId.h>
#include <rw/tvhdict.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

#define RW_THR_DEFAULT_CANCEL_TIME_OUT 5000 /* Milliseconds */

class RW_THREAD_GLOBAL RWThreadManagerImp
    : public RWBodyBase
{

    friend class RWThreadManager;

protected:

    unsigned long cancelTimeOut_;
    bool isEarlyShutdownEnabled_;
    bool isShutdownEnabled_;
    bool shuttingDown_;
    RWReadersWriterLock threadsLock_;

    RWTValHashDictionary<RWThreadId, RWThreadImp*> threads_;

#if defined(RW_THR_HAS_SET_TERMINATE_PER_PROCESS)
    void (*prevTerminate_)(void);
#endif

#if !defined(RW_DISABLE_DEPRECATED)
#  if defined(RW_THR_THREAD_API_SOLARIS)
    int termSignal_;
    struct sigaction oldSigAction_;
#  endif
#endif

protected:

    // Protect constructor so that only instance can get to it
    RWThreadManagerImp(void);

    ~RWThreadManagerImp(void);

    void
    deregisterThread(const RWThreadId& threadID);

    void
    enableEarlyShutdown(void);

    unsigned long
    getCancelTimeOut(void) const;

    RWThreadSelf
    getCurrentThread(void);

#if !defined(RW_DISABLE_DEPRECATED)
#  if defined(RW_THR_THREAD_API_SOLARIS)
    // Get the signal the SourcePro Core - Threads Module uses for
    // termination
    RW_DEPRECATE_FUNC("")
    int
    getTerminationSignal(void) const;
#  endif
#endif

    bool
    getShutdownEnabled() const;

    void
    registerThread(const RWThreadId& threadID, RWThreadImp* imp);

    void
    setCancelTimeOut(unsigned long milliseconds);

#if !defined(RW_DISABLE_DEPRECATED)
#  if defined(RW_THR_THREAD_API_SOLARIS)
    // Change the signal the Threads Module uses for termination
    RW_DEPRECATE_FUNC("")
    void
    setTerminationSignal(int termSignal);
#  endif
#endif

    void
    setShutdownEnabled(bool shutdownEnabled);

    void
    shutdown(void);

private:

    RWThreadManagerImp(const RWThreadManagerImp& second);

    RWThreadManagerImp&
    operator=(const RWThreadManagerImp& second);

};


#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWThreadManagerImp_h__
