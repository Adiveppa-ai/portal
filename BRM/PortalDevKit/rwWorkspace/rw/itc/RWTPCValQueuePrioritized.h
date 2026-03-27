#ifndef __rw_itc_RWTPCValQueuePrioritized_h__
#define __rw_itc_RWTPCValQueuePrioritized_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValQueuePrioritized.h#1 $
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

#include <rw/itc/RWTPCValBufferBasePrioritized.h>
#include <rw/itc/RWTPriorityDecorator.h>
#include <rw/itc/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPCValQueuePrioritized RWTPCValQueuePrioritized
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * First-in-first-out (FIFO) queue that provides producer-consumer
 * synchronization semantics for exchanging \e prioritized values between
 * cooperating threads.
 *
 * RWTPCValQueuePrioritized is a first-in-first-out (FIFO) queue that
 * provides producer-consumer synchronization semantics for exchanging
 * \e prioritized values between cooperating threads.
 *
 * In the producer-consumer synchronization model, reader threads
 * (consumers) are blocked while the queue is empty, and writer threads
 * (producers) are blocked while the queue is full. The queue is considered
 * full when the number of unread entries equals or exceeds some
 * user-specified maximum capacity.
 *
 * The write operations inherited by this class bind a priority value to
 * each data value prior to storing that value in an internal buffer. The
 * priority value is used by these write operations to determine a value's
 * insertion point within the queue, such that the set of unread values will
 * be retrieved in priority order when they are eventually read from the
 * queue. A new value is retrieved after any previously inserted values of
 * the same priority.
 *
 * \example
 * \code
 * #include <rw/itc/RWTPCValQueuePrioritized.h>
 * #include <rw/thread/RWThreadFunction.h>
 * #include <rw/cstring.h>
 * #include <iostream>
 *
 * RWTPCValQueuePrioritized<RWCString> pcQueue;
 *
 * void reader(void)
 * {
 *     // Get values from queue and write to stdout.
 *     RWCString message;
 *     while ("Exit" != (message = pcQueue.read())) {
 *         std::cout << message << std::endl;
 *         rwSleep(100); // Let the messages pile up
 *     }
 *     std::cout << "EXIT" << std::endl;
 * }
 *
 * int main()
 * {
 *     RWThread thread = RWThreadFunction::make(reader);
 *     RWCString high("High"), medium("Medium"), low("Low");
 *
 *     thread.start();
 *     pcQueue.write(1, low);
 *     pcQueue.write(1, low);
 *     pcQueue.write(2, medium);
 *     pcQueue.write(1, low);
 *     pcQueue.write(3, high);
 *     pcQueue.write(2, medium);
 *     pcQueue.write(1, low);
 *     pcQueue.write(1, low);
 *     pcQueue.write(3, high);
 *     pcQueue.write(1, low);
 *     pcQueue.write(2, medium);
 *     pcQueue.write(2, medium);
 *     pcQueue.write(0, "Exit");
 *     thread.join();
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * High
 * High
 * Medium
 * Medium
 * Medium
 * Medium
 * Low
 * Low
 * Low
 * Low
 * Low
 * EXIT
 * \endcode
 * \endexample
 */
template <class Type>
class RWTPCValQueuePrioritized :
    public RWTPCValBufferBasePrioritized<Type, RWTPriorityDecorator<Type> >
{

public:
    /**
     * Constructs a value-based, prioritized, producer-consumer queue
     * instance.
     *
     * The queue is open on construction and enforces no limit on the number
     * of items in the queue.
     */
    RWTPCValQueuePrioritized(void);

    /**
     * Constructs a value-based, prioritized, producer-consumer queue
     * instance.
     *
     * The parameter \a maxCapacity specifies the maximum number of unread
     * entries to allow to accumulate within the queue. Once the number of
     * entries in the queue equals this number, any thread attempting to
     * write an additional entry is blocked until an entry is removed by a
     * read() operation, or until the capacity is increased. A capacity of
     * zero is used to indicate that the queue has no size limit other than
     * that imposed by memory limitations, and that all
     * \ref RWTPCValBufferBaseDecorated::write() "write()" operations should
     * complete without blocking.
     *
     * The queue is open on construction.
     */
    RWTPCValQueuePrioritized(size_t maxCapacity);

    /**
     * Constructs a value-based, prioritized, producer-consumer queue
     * instance.
     *
     * The parameter \a maxCapacity specifies the maximum number of unread
     * entries to allow to accumulate within the queue. Once the number of
     * entries in the queue equals this number, any thread attempting to
     * write an additional entry is blocked until an entry is removed by a
     * read() operation, or until the capacity is increased. A capacity of
     * zero is used to indicate that the queue has no size limit other than
     * that imposed by memory limitations, and that all
     * \ref RWTPCValBufferBaseDecorated::write() "write()" operations should
     * complete without blocking.
     *
     * The parameter \a isOpen is a \c bool value that specifies whether the
     * queue should be initialized in the open state, \c true, or the closed
     * state, \c false.
     */
    RWTPCValQueuePrioritized(size_t maxCapacity, bool isOpen);

    /**
     * Destructor.
     */
    ~RWTPCValQueuePrioritized(void);

protected:

    virtual void
    _write(const RWTPriorityDecorator<Type>& value);

};

/*****************************************************************************/

template <class Type>
inline
RWTPCValQueuePrioritized<Type>::RWTPCValQueuePrioritized(void)
    : RWTPCValBufferBaseDecorated<Type, RWTPriorityDecorator<Type> >(),
      RWTPCValBufferBasePrioritized<Type, RWTPriorityDecorator<Type> >()
{
}


template <class Type>
inline
RWTPCValQueuePrioritized<Type>::RWTPCValQueuePrioritized(size_t maxCapacity)
    : RWTPCValBufferBaseDecorated<Type, RWTPriorityDecorator<Type> >(maxCapacity),
      RWTPCValBufferBasePrioritized<Type, RWTPriorityDecorator<Type> >(maxCapacity)
{
}


template <class Type>
inline
RWTPCValQueuePrioritized<Type>::RWTPCValQueuePrioritized(size_t maxCapacity, bool isOpen)
    : RWTPCValBufferBaseDecorated<Type, RWTPriorityDecorator<Type> >(maxCapacity, isOpen),
      RWTPCValBufferBasePrioritized<Type, RWTPriorityDecorator<Type> >(maxCapacity, isOpen)
{
}

template <class Type>
inline
RWTPCValQueuePrioritized<Type>::~RWTPCValQueuePrioritized(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTPCValQueuePrioritized.cc>
#endif

#endif // __rw_itc_RWTPCValQueuePrioritized_h__
