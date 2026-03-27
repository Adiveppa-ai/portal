#ifndef __rw_itc_RWTPCValQueueGuardedPrioritized_h__
#define __rw_itc_RWTPCValQueueGuardedPrioritized_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValQueueGuardedPrioritized.h#1 $
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

#include <rw/itc/RWTGuardAndPriorityDecorator.h>
#include <rw/itc/RWTPCValBufferBaseGuardedPrioritized.h>
#include <rw/itc/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4250)
#endif

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPCValQueueGuardedPrioritized RWTPCValQueueGuardedPrioritized
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * First-in-first-out (FIFO) queue that provides producer-consumer
 * synchronization semantics for exchanging \e guarded and \e prioritized
 * values between cooperating threads.
 *
 * RWTPCValQueueGuardedPrioritized is a first-in-first-out (FIFO) queue that
 * provides producer-consumer synchronization semantics for exchanging
 * \e guarded and \e prioritized values between cooperating threads.
 *
 * In the producer-consumer synchronization model, reader threads
 * (consumers) are blocked while the queue is empty, and writer threads
 * (producers) are blocked while the queue is full. The queue is considered
 * full when the number of unread entries equals or exceeds some
 * user-specified maximum capacity.
 *
 * The write operations inherited by this class bind a guard functor and
 * priority value to each data value prior to storing that value in an
 * internal buffer. The guard functor is used during read operations to
 * determine whether the associated value is currently eligible for
 * retrieval from the buffer. The priority value is used during write
 * operations to determine a value's insertion point within the queue, such
 * that the set of unread values will be retrieved in priority order when
 * they are eventually read from the queue. A new value is retrieved after
 * any previously inserted values of the same priority, except when the
 * retrieval of the older values is prohibited by their guard functors.
 *
 * \example
 * \code
 * #include <rw/functor/RWTFunctor.h>
 * #include <rw/itc/RWTPCValQueueGuardedPrioritized.h>
 * #include <rw/thread/RWThreadFunction.h>
 * #include <iostream>
 *
 * enum Command {
 *     RUN, STOP, PROCESS_HIGH, PROCESS_MED, PROCESS_LOW, EXIT
 * };
 *
 * RWTPCValQueueGuardedPrioritized<Command>  pcQueue;
 * bool isRunning = false;
 *
 * // The guard function
 * bool canProcess()
 * {
 *     return isRunning;
 * }
 *
 * void reader(void)
 * {
 *     // Get commands from queue, update state,
 *     // and write to stdout.
 *     Command command;
 *     while (EXIT != (command = pcQueue.read())) {
 *         switch (command) {
 *             case RUN:
 *                 std::cout << "RUN" << std::endl;
 *                 isRunning = true;
 *                 break;
 *             case STOP:
 *                 std::cout << "STOP" << std::endl;
 *                 isRunning = false;
 *                 break;
 *             case PROCESS_HIGH:
 *                 std::cout << "PROCESS_HIGH" << std::endl;
 *                 break;
 *             case PROCESS_MED:
 *                 std::cout << "PROCESS_MED" << std::endl;
 *                 break;
 *             case PROCESS_LOW:
 *                 std::cout << "PROCESS_LOW" << std::endl;
 *                 break;
 *         }
 *     }
 *     std::cout << "EXIT" << std::endl;
 * }
 *
 * int main()
 * {
 *     RWThread thread = RWThreadFunction::make(reader);
 *     RWTFunctor<bool()> guard = canProcess;
 *
 *     thread.start();
 *     pcQueue.write(1, PROCESS_LOW, guard);
 *     pcQueue.write(2, PROCESS_MED, guard);
 *     pcQueue.write(1, PROCESS_LOW, guard);
 *     pcQueue.write(1, PROCESS_LOW, guard);
 *     pcQueue.write(3, PROCESS_HIGH, guard);
 *     pcQueue.write(4, RUN);
 *     pcQueue.write(2, PROCESS_MED, guard);
 *     pcQueue.write(1, PROCESS_LOW, guard);
 *     pcQueue.write(1, PROCESS_LOW, guard);
 *     pcQueue.write(1, PROCESS_LOW, guard);
 *     pcQueue.write(3, PROCESS_HIGH, guard);
 *     pcQueue.write(4, STOP);
 *     pcQueue.write(3, PROCESS_HIGH, guard);
 *     pcQueue.write(1, PROCESS_LOW, guard);
 *     pcQueue.write(4, RUN);
 *     pcQueue.write(0, EXIT);
 *     thread.join();
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * RUN
 * PROCESS_HIGH
 * PROCESS_MED
 * PROCESS_MED
 * PROCESS_LOW
 * PROCESS_LOW
 * PROCESS_LOW
 * PROCESS_LOW
 * PROCESS_LOW
 * PROCESS_LOW
 * STOP
 * RUN
 * PROCESS_HIGH
 * PROCESS_HIGH
 * PROCESS_LOW
 * EXIT
 * \endcode
 * \endexample
 */
template <class Type>
class RWTPCValQueueGuardedPrioritized :
    public RWTPCValBufferBaseGuardedPrioritized<Type, RWTGuardAndPriorityDecorator<Type> >
{

public:
    /**
     * Constructs a value-based, guarded, prioritized, producer-consumer
     * queue instance.
     *
     * The queue is open on construction and enforces no limit on the number
     * of items in the queue.
     */
    RWTPCValQueueGuardedPrioritized(void);

    /**
     * Constructs a value-based, guarded, prioritized, producer-consumer
     * queue instance.
     *
     * The parameter \a maxCapacity specifies the maximum number of unread
     * entries to allow to accumulate within the queue. Once the number of
     * entries in the queue equals this number, any thread attempting to
     * write an additional entry is blocked until an entry is removed by a
     * read() operation, or until the capacity is increased. A capacity of
     * zero is used to indicate that the queue has no size limit other than
     * that imposed by memory limitations, and that all write() operations
     * should complete without blocking.
     *
     * The queue is open on construction.
     */
    RWTPCValQueueGuardedPrioritized(size_t maxCapacity);

    /**
     * Constructs a value-based, guarded, prioritized, producer-consumer
     * queue instance.
     *
     * The parameter \a maxCapacity specifies the maximum number of unread
     * entries to allow to accumulate within the queue. Once the number of
     * entries in the queue equals this number, any thread attempting to
     * write an additional entry is blocked until an entry is removed by a
     * read() operation, or until the capacity is increased. A capacity of
     * zero is used to indicate that the queue has no size limit other than
     * that imposed by memory limitations, and that all write() operations
     * should complete without blocking.
     *
     * The parameter \a isOpen is a \c bool value that specifies whether the
     * queue should be initialized in the open state, \c true, or the closed
     * state, \c false.
     */
    RWTPCValQueueGuardedPrioritized(size_t maxCapacity, bool isOpen);

    /**
     * Destructor.
     */
    ~RWTPCValQueueGuardedPrioritized(void);

protected:

    virtual void
    _write(const RWTGuardAndPriorityDecorator<Type>& value);

};

/*****************************************************************************/

template <class Type>
inline
RWTPCValQueueGuardedPrioritized<Type>::RWTPCValQueueGuardedPrioritized(void)
    : RWTPCValBufferBaseDecorated<Type, RWTGuardAndPriorityDecorator<Type> >(),
      RWTPCValBufferBaseGuardedPrioritized<Type, RWTGuardAndPriorityDecorator<Type> >()

{
}


template <class Type>
inline
RWTPCValQueueGuardedPrioritized<Type>::RWTPCValQueueGuardedPrioritized(
    size_t maxCapacity)
    : RWTPCValBufferBaseDecorated<Type, RWTGuardAndPriorityDecorator<Type> >(
          maxCapacity),
      RWTPCValBufferBaseGuardedPrioritized<Type, RWTGuardAndPriorityDecorator<Type> >(
          maxCapacity)

{
}


template <class Type>
inline
RWTPCValQueueGuardedPrioritized<Type>::RWTPCValQueueGuardedPrioritized(
    size_t maxCapacity, bool b)
    : RWTPCValBufferBaseDecorated<Type, RWTGuardAndPriorityDecorator<Type> >(
          maxCapacity, b),
      RWTPCValBufferBaseGuardedPrioritized<Type, RWTGuardAndPriorityDecorator<Type> >(
          maxCapacity, b)

{
}

template <class Type>
inline
RWTPCValQueueGuardedPrioritized<Type>::~RWTPCValQueueGuardedPrioritized(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTPCValQueueGuardedPrioritized.cc>
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_itc_RWTPCValQueueGuardedPrioritized_h__
