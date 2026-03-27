#ifndef __rw_itc_RWTPCValBufferBasePrioritized_h__
#define __rw_itc_RWTPCValBufferBasePrioritized_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBasePrioritized.h#1 $
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

#include <rw/itc/RWTPCValBufferBaseDecorated.h>
#include <rw/itc/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPCValBufferBasePrioritized RWTPCValBufferBasePrioritized
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * Base class that provides producer-consumer synchronization semantics for
 * exchanging \e prioritized values between cooperating threads.
 *
 * RWTPCValBufferBasePrioritized is the base class for the family of classes
 * that provides producer-consumer synchronization semantics for exchanging
 * \e prioritized values between cooperating threads.
 *
 * In the producer-consumer synchronization model, reader threads
 * (consumers) are blocked while a buffer is empty, and writer threads
 * (producers) are blocked while a buffer is full. A buffer is considered
 * full when the number of unread entries equals or exceeds some
 * user-specified maximum capacity.
 *
 * The write operations provided by this class and its subclasses bind
 * additional data items to each value prior to storing that value in an
 * internal buffer. One of these additional data items, or \e decorations,
 * is a priority value that is used during write operations to determine a
 * value's insertion point within the buffer, such that the set of unread
 * values will be retrieved in priority order when eventually read from the
 * buffer. The template parameter \c PriorityDecorator identifies the class
 * that is used to encapsulate both the data value, priority value, and any
 * other decorations as a single object for storage in the internal buffer.
 * The decorator classes used by subclasses to instantiate this class are
 * intended for the Threads Module's internal use, and are not documented as
 * part of the public interface.
 */
template <class Type, class PriorityDecorator>
class RWTPCValBufferBasePrioritized :
    virtual public RWTPCValBufferBaseDecorated<Type, PriorityDecorator>
{

public:

    typedef Type    DataType;

    void
    write(const Type& value)
    {
        RWTPCValBufferBaseDecorated<Type, PriorityDecorator>::write(value);
    }

    bool
    tryWrite(const Type& value)
    {
        return RWTPCValBufferBaseDecorated<Type, PriorityDecorator>::tryWrite(value);
    }

    RWWaitStatus
    write(const Type& value, unsigned long milliseconds)
    {
        return RWTPCValBufferBaseDecorated<Type, PriorityDecorator>::write(value, milliseconds);
    }

    /**
     * Inserts a value with the specified priority into the buffer at a
     * position determined by the implementation supplied in derived
     * classes.
     *
     * If the buffer is open and has sufficient capacity to hold another
     * value, this function inserts the value. If the buffer is open and
     * full, this function blocks the calling thread until the buffer is no
     * longer full (because another thread or threads have read values or
     * have changed the maximum capacity), or until the buffer is closed.
     *
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for room to write, the calling thread is
     * unblocked and the function returns by throwing an
     * RWTHRClosedException.
     *
     * If the buffer is already closed when this function is called, it
     * immediately returns by throwing an RWTHRClosedException.
     *
     * Calling this function on an full buffer may result in the invocation
     * of the on-full callback functor, if a valid one has been registered.
     * The on-full callback functor is guaranteed to execute only within a
     * writer thread. Calling this function on a full buffer results in the
     * invocation of an on-full callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an full buffer when an on-full
     * callback is registered.
     * - The calling thread is the first to attempt writing to a full buffer
     * in which an on-full callback was previously registered.
     *
     * Repeated attempts to write to a full buffer does not result in
     * repeated invocations of the callback functor. Once the full buffer is
     * read from, however, it resets the callback trigger. If the buffer
     * again becomes full, the first thread to attempt to write to it causes
     * another invocation of the on-full callback.
     *
     * This function takes two parameters. The parameter \a value is a
     * \c const reference to an instance of the type used to instantiate
     * this template class. The parameter \a priority is a \c long that is
     * used to determine the insertion point of the value within the buffer.
     * A value with a greater priority value is positioned to be read before
     * a value of lower priority. Values of equal priority are positioned as
     * determined by the implementation supplied in derived classes.
     */
    void
    write(long priority,
          const Type& value);

    /**
     * Inserts a value with the specified priority into the buffer at a
     * position determined by the implementation supplied in derived
     * classes, but only if the value may be written immediately; in other
     * words, only if there is sufficient free capacity.
     *
     * If the buffer is open and has sufficient capacity to hold another
     * value, this function inserts the value, and returns a value of
     * \c true to indicate that the write succeeded. If the buffer is open
     * and full, this function immediately returns a value of \c false to
     * indicate that the write was unsuccessful. If the buffer is closed,
     * this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Calling this function on an full buffer may result in the invocation
     * of the on-full callback functor, if a valid one has been registered.
     * The on-full callback functor is guaranteed to execute only within a
     * writer thread. Calling this function on a full buffer results in the
     * invocation of an on-full callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an full buffer when an on-full
     * callback is registered.
     * - The calling thread is the first to attempt writing to a full buffer
     * in which an on-full callback was previously registered.
     *
     * Repeated attempts to write to a full buffer does not result in
     * repeated invocations of the callback functor. Once the full buffer is
     * read from, however, it resets the callback trigger. If the buffer
     * again becomes full, the first thread to attempt to write to it causes
     * another invocation of the on-full callback.
     *
     * While this function guarantees not to block the caller if the buffer
     * is full, it cannot prevent the on-full callback functor, if executed,
     * from indirectly blocking the caller.
     *
     * This function takes two parameters. The parameter \a value is a
     * \c const reference to an instance of the type used to instantiate
     * this template class. The parameter \a priority is a \c long that is
     * used to determine the insertion point of the value within the buffer.
     * A value with a greater priority value is positioned to be read before
     * a value of lower priority. Values of equal priority are positioned as
     * determined by the implementation supplied in derived classes.
     */
    bool
    tryWrite(long priority,
             const Type& value);

    /**
     * Inserts a value with the specified priority into the buffer at a
     * position determined by the implementation supplied in derived
     * classes.
     *
     * If the buffer is open and has sufficient capacity to hold another
     * value, this function inserts the value and returns #RW_THR_COMPLETED
     * to indicate that the write succeeded. If the buffer is open and full,
     * this function blocks the calling thread until the buffer is no longer
     * full (because another thread or threads have read values or have
     * changed the maximum capacity), or until the buffer is closed, or
     * until the specified amount of time passes. If sufficient space does
     * not become available within the specified amount of time, the
     * function returns a value of #RW_THR_TIMEOUT.
     *
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for room to write, the calling thread is
     * unblocked and the function returns by throwing an
     * RWTHRClosedException.
     *
     * If the buffer is already closed when this function is called, the
     * function immediately returns by throwing an RWTHRClosedException.
     *
     * Calling this function on an full buffer may result in the invocation
     * of the on-full callback functor, if a valid one has been registered.
     * The on-full callback functor is guaranteed to execute only within a
     * writer thread. Calling this function on a full buffer results in the
     * invocation of an on-full callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an full buffer when an on-full
     * callback is registered.
     * - The calling thread is the first to attempt writing to a full buffer
     * in which an on-full callback was previously registered.
     *
     * Repeated attempts to write to a full buffer does not result in
     * repeated invocations of the callback functor. Once the full buffer is
     * read from, however, it resets the callback trigger. If the buffer
     * again becomes full, the first thread to attempt to write to it causes
     * another invocation of the on-full callback.
     *
     * While this function guarantees to wait, if necessary, for a period
     * time equal to or greater than the specified number of milliseconds,
     * it cannot guarantee that the thread is actually scheduled for
     * execution at the end of the time-out period. It cannot prevent the
     * on-full callback functor from indirectly blocking the caller for an
     * indefinite period of time.
     *
     * This function takes three parameters:
     *
     * - The parameter \a priority is a \c long that is used to determine
     * the insertion point of the value within the buffer. A value with a
     * greater priority value is positioned to be read before a value of
     * lower priority. Values of equal priority are positioned to be read as
     * determined by the implementation supplied in derived classes.
     * - The parameter \a value is a \c const reference to an instance of
     * the type used to instantiate this template class.
     * - The parameter \a milliseconds is an <tt>unsigned long</tt> value
     * that specifies the maximum number of milliseconds to wait for the
     * operation to complete.
     */
    RWWaitStatus
    write(long priority,
          const Type& value,
          unsigned long milliseconds);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWTPCValBufferBasePrioritized(void);

protected:

    RWTPCValBufferBasePrioritized(void);

    RWTPCValBufferBasePrioritized(size_t maxCapacity);

    RWTPCValBufferBasePrioritized(size_t maxCapacity, bool isOpen);

    void
    _writeBack(const PriorityDecorator& value);

    void
    _writeFront(const PriorityDecorator& value);

};

/*****************************************************************************/

template <class Type, class PriorityDecorator>
inline
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::RWTPCValBufferBasePrioritized(void)
    : RWTPCValBufferBaseDecorated<Type, PriorityDecorator>()
{
}

template <class Type, class PriorityDecorator>
inline
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::RWTPCValBufferBasePrioritized(size_t maxCapacity)
    : RWTPCValBufferBaseDecorated<Type, PriorityDecorator>(maxCapacity)
{
}

template <class Type, class PriorityDecorator>
inline
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::RWTPCValBufferBasePrioritized(size_t maxCapacity,
        bool isOpen)
    : RWTPCValBufferBaseDecorated<Type, PriorityDecorator>(maxCapacity, isOpen)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTPCValBufferBasePrioritized.cc>
#endif

#endif // __rw_itc_RWTPCValBufferBasePrioritized_h__
