#ifndef __rw_itc_RWTPCValQueue_h__
#define __rw_itc_RWTPCValQueue_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValQueue.h#1 $
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

#include <rw/itc/RWTPCValBufferBase.h>
#include <rw/itc/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPCValQueue RWTPCValQueue
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * First-in-first-out (FIFO) queue that provides producer-consumer
 * synchronization semantics for exchanging values between cooperating
 * threads.
 *
 * RWTPCValQueue is a first-in-first-out (FIFO) queue that provides
 * producer-consumer synchronization semantics for exchanging values between
 * cooperating threads.
 *
 * In the producer-consumer synchronization model, reader threads
 * (consumers) are blocked while the queue is empty, and writer threads
 * (producers) are blocked while the queue is full. A queue is considered
 * full when the number of unread entries equals or exceeds some
 * user-specified maximum capacity.
 *
 * \example
 * \code
 * // This program uses reader and writer threads to
 * // copy text from standard input to standard output
 * // via a producer-consumer queue:
 *
 * #include <iostream>
 * #include <rw/itc/RWTPCValQueue.h>
 * #include <rw/thread/RWThread.h>
 * #include <rw/thread/RWThreadFunction.h>
 *
 * // A producer-consumer queue with buffer size of 10:
 * RWTPCValQueue<char> pcQueue(10);
 *
 * void readerThread()
 * {
 *     // Read chars from queue and send to stdout. Quit when
 *     // sentinel NULL char is received:
 *     char c;
 *     while ((c = pcQueue.read()) != '\0') {
 *         std::cout << c << std::flush;
 *     }
 * }
 *
 * void writerThread()
 * {
 *     // Get chars from stdin and write to queue. Send the NULL
 *     // char and quit when stream error or EOF occurs:
 *     char c;
 *     do {
 *         std::cin.get(c);
 *         pcQueue.write(std::cin.good() ? c : '\0');
 *     }
 *     while (std::cin.good());
 * }
 *
 * int main()
 * {
 *     RWThread reader = RWThreadFunction::make(readerThread);
 *     RWThread writer = RWThreadFunction::make(writerThread);
 *     reader.start();
 *     writer.start();
 *     reader.join();
 *     writer.join();
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
template <class Type>
class RWTPCValQueue : public RWTPCValBufferBase<Type>
{

public:
    /**
     * Constructs a value-based producer-consumer queue instance.
     *
     * The queue is open on construction and enforces no limit on the number
     * of items in the queue.
     */
    RWTPCValQueue(void);

    /**
     * Constructs a value-based producer-consumer queue instance.
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
    RWTPCValQueue(size_t maxCapacity);

    /**
     * Constructs a value-based producer-consumer queue instance.
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
    RWTPCValQueue(size_t maxCapacity, bool isOpen);

    /**
     * Destructor.
     */
    ~RWTPCValQueue(void);

protected:

    virtual void
    _write(const Type& value);

};

/*****************************************************************************/

template <class Type>
inline
RWTPCValQueue<Type>::RWTPCValQueue(void)
{
}

template <class Type>
inline
RWTPCValQueue<Type>::RWTPCValQueue(size_t maxCapacity)
    : RWTPCValBufferBase<Type>(maxCapacity)
{
}

template <class Type>
inline
RWTPCValQueue<Type>::RWTPCValQueue(size_t maxCapacity, bool b)
    : RWTPCValBufferBase<Type>(maxCapacity, b)
{
}

template <class Type>
inline
RWTPCValQueue<Type>::~RWTPCValQueue(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTPCValQueue.cc>
#endif

#endif // __rw_itc_RWTPCValQueue_h__
