#ifndef __rw_itc_RWTPCPtrQueue_h__
#define __rw_itc_RWTPCPtrQueue_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCPtrQueue.h#1 $
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

#include <rw/itc/RWTPCPtrBufferBase.h>
#include <rw/itc/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPCPtrQueue RWTPCPtrQueue
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * First-in-first-out (FIFO) queue with producer-consumer synchronization
 * semantics for exchanging pointer values between cooperating threads.
 *
 * RWTPCPtrQueue is a first-in-first-out (FIFO) queue that provides
 * producer-consumer synchronization semantics for exchanging pointer values
 * between cooperating threads.
 *
 * In the producer-consumer synchronization model, reader threads
 * (consumers) are blocked while the queue is empty, and writer threads
 * (producers) are blocked while the queue is full. A buffer is considered
 * full when the number of unread entries equals or exceeds some
 * user-specified maximum capacity.
 *
 * \example
 * See RWTPCValQueue for a producer-consumer queue example.
 * \endexample
 */
template <class Type>
class RWTPCPtrQueue : public RWTPCPtrBufferBase<Type>
{

public:
    /**
     * Constructs a pointer-based producer-consumer queue instance.
     *
     * The queue is open on construction and enforces no limit on the number
     * of items in the queue.
     */
    RWTPCPtrQueue(void);

    /**
     * Constructs a pointer-based producer-consumer queue instance.
     *
     * The parameter \a maxCapacity specifies the maximum number of unread
     * entries allowed to accumulate within the queue. Once the number of
     * entries in the queue equals this number, any thread attempting to
     * write an additional entry is blocked until an entry is removed by a
     * read operation, or until the capacity is increased. A capacity of
     * zero is used to indicate that the queue has no size limit, except as
     * imposed by memory limitations, and that all write operations should
     * complete without blocking.
     *
     * The queue is open on construction.
     */
    RWTPCPtrQueue(size_t maxCapacity);

    /**
     * Constructs a pointer-based producer-consumer queue instance.
     *
     * The parameter \a maxCapacity specifies the maximum number of unread
     * entries allowed to accumulate within the queue. Once the number of
     * entries in the queue equals this number, any thread attempting to
     * write an additional entry is blocked until an entry is removed by a
     * read operation, or until the capacity is increased. A capacity of
     * zero is used to indicate that the queue has no size limit, except as
     * imposed by memory limitations, and that all write operations should
     * complete without blocking.
     *
     * The parameter \a isOpen is a bool value that specifies whether the
     * queue should be initialized in the open state (\c true) or the closed
     * state (\c false).
     */
    RWTPCPtrQueue(size_t maxCapacity, bool isOpen);

    /**
     * Destructor.
     */
    ~RWTPCPtrQueue(void);

protected:

    virtual void
    _write(Type* value);

};

/*****************************************************************************/

template <class Type>
inline
RWTPCPtrQueue<Type>::RWTPCPtrQueue(void)
{
}

template <class Type>
inline
RWTPCPtrQueue<Type>::RWTPCPtrQueue(size_t maxCapacity)
    : RWTPCPtrBufferBase<Type>(maxCapacity)
{
}

template <class Type>
inline
RWTPCPtrQueue<Type>::RWTPCPtrQueue(size_t maxCapacity, bool isOpen)
    : RWTPCPtrBufferBase<Type>(maxCapacity, isOpen)
{
}

template <class Type>
inline
RWTPCPtrQueue<Type>::~RWTPCPtrQueue(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTPCPtrQueue.cc>
#endif

#endif // __rw_itc_RWTPCPtrQueue_h__
