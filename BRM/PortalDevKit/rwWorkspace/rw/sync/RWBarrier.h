#ifndef __rw_sync_RWBarrier_h__
#define __rw_sync_RWBarrier_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWBarrier.h#1 $
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

#include <rw/sync/RWCondition.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Synchronizes a number of concurrent threads at a specific point in their
 * processing.
 *
 * RWBarrier synchronizes a number of concurrent threads at a specific point
 * in their processing. Each thread indicates that it has reached the
 * "barrier" by calling the wait() member function. Each thread is blocked
 * by the call to wait() until the number of threads specified in the
 * RWBarrier constructor have all called wait(). When the last thread calls
 * wait(), all threads waiting at the barrier are unblocked, making them
 * eligible for execution.
 *
 * Initializing an RWBarrier with a zero count is not legal, and causes an
 * assertion to be triggered in debug mode. Using an RWBarrier with a count
 * different than the number of threads able to perform a wait() on that
 * RWBarrier is outside the intended use of the class. There is no
 * diagnostic available to detect this condition.
 *
 * The count of an RWBarrier may be changed after initialization by using
 * the setCount(int) function. When calling this function, make sure that no
 * threads are blocked in wait(). If threads are blocked in wait(), an
 * assertion is triggered in debug mode; in release mode, an exception is
 * thrown.
 *
 * When an RWBarrier is destroyed, no threads should be blocked in the
 * wait() function. When the module is built in debug mode, an assertion is
 * raised if there are threads waiting when the RWBarrier is destructed.
 *
 * \example
 * \code
 * #include <rw/sync/RWBarrier.h>
 * #include <rw/functor/rwBind.h>
 * #include <rw/thread/RWThreadFunction.h>
 *
 * void func(RWBarrier* barrier)
 * {
 *     // do initialization ...
 *
 *     // wait for all threads to complete initialization
 *     barrier->wait();
 * }
 *
 * int main()
 * {
 *     RWBarrier barrier(3);
 *     RWThread t1 = RWThreadFunction::make(rwBind(func, &barrier));
 *     RWThread t2 = RWThreadFunction::make(rwBind(func, &barrier));
 *     t1.start();
 *     t2.start();
 *
 *     barrier.wait(); // Wait for t1 and t2 to complete
 *     // initialization.
 *     t1.join();
 *     t2.join();
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_SYNC_SYMBOLIC RWBarrier
{

#if defined(RW_MULTI_THREAD)

private:

    RWMutexLock mutex_;
    RWCondition barrier_;
    int         count_;
    int         countTotal_;
    int         group_;

#endif

public:

    /**
     * Constructs a barrier for synchronizing \a count threads, where
     * \a count must be greater than 0. A default \a count of 1 is provided
     * for default construction. This can be changed following construction
     * using the setCount() method.
     *
     * \note
     * Constructing a barrier with \a count not equal to 1 causes a debug
     * assertion in single-threaded debug mode builds.
     */
    RWBarrier(int count = 1);


    /**
     * Destructor. Triggers an assertion failure in debug mode if there are
     * any threads blocked in wait().
     */
    ~RWBarrier();


    /**
     * Sets the barrier count to \a count. The \a count must be greater than
     * or equal to 1. There must be no threads blocked in wait() when this
     * function is called.
     *
     * \note
     * Passing \a count not equal to 1 causes an assertion in
     * single-threaded debug mode builds.
     */
    void
    setCount(int count);


    /**
     * Each thread calls wait() when it reaches its synchronization point.
     * The threads \e block in wait() until \c count threads have called
     * wait(). When the last thread enters wait(), all threads are released.
     *
     * \note
     * This function is a no-op in single-threaded builds because there are
     * no other threads with which to synchronize.
     */
    void
    wait();
    //used to throw any exception

private:

    /**
     * Copy construction prohibited.
     */
    RWBarrier(const RWBarrier& second);

    /**
     * Assignment prohibited.
     */
    RWBarrier& operator=(const RWBarrier& second);

};

#endif // __rw_sync_RWBarrier_h__
