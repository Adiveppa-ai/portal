#ifndef __rw_thread_RWGuardedRunnable_h__
#define __rw_thread_RWGuardedRunnable_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWGuardedRunnable.h#1 $
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

  RWGuardedRunnable - An RWRunnable/RWRunnableGuard pair.

  RWGuardedRunnableQueue - An RWGuardedRunnable  producer-consumer queue.

  RWGuardedRunnableQueue is a producer-consumer queue specialized for
  Runnables. It will only deque an RWRunnable if it has an
  associated guard that evaluates to true, or if there is no associated
  guard.

  These classes are used in the implementation of RWRunnableServer. They
  are not otherwise documented.

******************************************************************************/

#include <rw/thread/RWRunnable.h>
#include <rw/thread/RWRunnableGuard.h>
#include <rw/thread/pkgdefs.h>

#if defined(RW_DISABLE_DEPRECATED)
#  error RWGuardedRunnable and RWGuardedRunnableQueue are deprecated, \
use the RWTPCValQueue heirarchy classes instead.
#endif

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_THREAD_SYMBOLIC RWGuardedRunnable
{

protected:

    RWRunnable runnable_;
    RWRunnableGuard runnableGuard_;
    bool noGuard_;

public:

    // Construct with RWRunnable and RWRunnableGuard
    RWGuardedRunnable(RWRunnable r, RWRunnableGuard g);

    // Construct with RWRunnable, default guard always evaluates to true
    RWGuardedRunnable(RWRunnable r);

    RWGuardedRunnable(const RWGuardedRunnable& second);

    // Construct with no runnable, default guard always evaluates to true
    // This constructor is required for stdlib version of RWTValSlist<>
    // DO NOT USE!
    RWGuardedRunnable(void);

    RWGuardedRunnable&
    operator=(const RWGuardedRunnable& second);

    // Destructor
    ~RWGuardedRunnable(void);

    // Does the guard for this runnable evaluate to true.
    bool
    isRunnable(void) const;

    // Get RWRunnable out of this RWGuardedRunnable.
    operator RWRunnable(void) const;

    // Equality
    bool
    operator==(const RWGuardedRunnable& second) const;

    // Required for stdlib-based collections
    bool
    operator<(const RWGuardedRunnable& second) const;

};

/****************************************************************************/

inline
RWGuardedRunnable::~RWGuardedRunnable(void)
{
}

inline bool
RWGuardedRunnable::isRunnable(void) const
{
    return noGuard_ ? true : runnableGuard_();
}

inline
RWGuardedRunnable::operator RWRunnable(void) const
{
    return runnable_;
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWGuardedRunnable_h__
