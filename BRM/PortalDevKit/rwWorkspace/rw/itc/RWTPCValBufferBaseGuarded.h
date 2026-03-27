#ifndef __rw_itc_RWTPCValBufferBaseGuarded_h__
#define __rw_itc_RWTPCValBufferBaseGuarded_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBaseGuarded.h#1 $
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
#include <rw/functor/RWTFunctor.h>
#include <rw/tvslist.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPCValBufferBaseGuarded RWTPCValBufferBaseGuarded
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * Base class that provides buffered producer-consumer synchronization
 * semantics for exchanging \e guarded values between cooperating threads.
 *
 * RWTPCValBufferBaseGuarded is the base class for the family of classes
 * that provides buffered producer-consumer synchronization semantics for
 * exchanging \e guarded values between cooperating threads.
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
 * is a guard functor that is used during read operations to determine
 * whether the associated value is currently eligible for retrieval from the
 * buffer. The template parameter \c GuardDecorator identifies the class
 * that is used to encapsulate the value, guard function, and any other
 * decorations as a single object for storage in the internal buffer. The
 * decorator classes used by subclasses to instantiate this class are
 * intended for the module's internal use, and are not documented as part of
 * the public interface.
 *
 * \sa
 * RWTPCValBufferBaseDecorated, RWTPCValQueueGuarded, RWTPCValStackGuarded,
 * RWTPCValBufferBaseGuardedPrioritized
 */
template <class Type, class GuardDecorator>
class RWTPCValBufferBaseGuarded :
    virtual public RWTPCValBufferBaseDecorated<Type, GuardDecorator>
{

public:

    typedef Type    DataType;

protected:

    typename RWTValSlist<GuardDecorator>::iterator iter_;

public:

    /*
     * Check if any guards currently evaluate to true.
     */
    void
    checkGuards(void);

    void
    write(const Type& value)
    {
        RWTPCValBufferBaseDecorated<Type, GuardDecorator>::write(value);
    }

    bool
    tryWrite(const Type& value)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::tryWrite(value);
    }

    RWWaitStatus
    write(const Type& value, unsigned long milliseconds)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::write(value, milliseconds);
    }

    /**
     * Traverses the buffer, in an order that is determined by the
     * implementation supplied in derived classes, until it finds a value
     * whose guard functor is undefined or evaluates to \c true, at which
     * point the function copies the value and returns it. If the buffer is
     * open and there are no values whose guard functors evaluate to
     * \c true, or if the buffer is empty, this function blocks the calling
     * thread until another value is inserted into the buffer, or until the
     * buffer is closed. If the buffer is closed, and is empty or contains
     * no readable entries, this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Each time a new value is written into the buffer, \e one waiting
     * reader thread is unblocked to give it a chance to re-evaluate the
     * contents of the buffer, including the new entry. Since a write
     * operation only unblocks a single waiting reader thread, any other
     * threads that are waiting to peek or read remain blocked even if the
     * most recent transfer produces a change in program state that would
     * cause one or more guard functors to evaluate to \c true. This means
     * that developers should use a single thread to read from a guarded
     * buffer; additional threads could potentially be stuck waiting for
     * write operations even when there are entries eligible for reading.
     *
     * If the buffer is closed while a thread is blocked within this
     * function, that thread is unblocked, after which this function
     * re-evaluates the guard functors one last time. If it finds a value
     * whose functor evaluates to \c true, it returns that value, otherwise
     * it returns by throwing an RWTHRClosedException.
     */
    Type
    peek(void)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::peek();
    }

    /**
     * Traverses the buffer, in an order that is determined by the
     * implementation supplied in derived classes, until it finds a value
     * whose guard functor is undefined or evaluates to \c true, at which
     * point the function removes the value and returns it. If the buffer is
     * open and there are no values whose guard functors evaluate to
     * \c true, or if the buffer is empty, this function blocks the calling
     * thread until another value is inserted into the buffer, or until the
     * buffer is closed. If the buffer is closed, and is empty or contains
     * no readable entries, this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Each time a new value is written into the buffer, \e one waiting
     * reader thread is unblocked to give it a chance to re-evaluate the
     * contents of the buffer, including the new entry. Since a write
     * operation only unblocks a single waiting reader thread, any other
     * threads that are waiting to peek or read remain blocked even if the
     * most recent transfer produces a change in program state that would
     * cause one or more guard functors to evaluate to \c true. This means
     * that developers should use a single thread to read from a guarded
     * buffer; additional threads could potentially be stuck waiting for
     * write operations even when there are entries eligible for reading.
     *
     * If the buffer is closed while a thread is blocked within this
     * function, that thread is unblocked, after which this function
     * re-evaluates the guard functors one last time. If it finds a value
     * whose functor evaluates to \c true, it returns that value, otherwise
     * it returns by throwing an RWTHRClosedException.
     */
    Type
    read(void)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::read();
    }

    /**
     * Traverses the buffer, in an order that is determined by the
     * implementation supplied in derived classes, until it finds a value
     * whose guard functor is undefined or evaluates to \c true. At this
     * point the function removes the value and copies it into the instance
     * passed as a reference, and returns #RW_THR_COMPLETED to indicate that
     * the read succeeded. If the buffer is open and there are no values
     * whose guard functors evaluate to \c true, or if the buffer is empty,
     * this function blocks the calling thread until another value is
     * inserted into the buffer, or until the buffer is closed, or until the
     * specified amount of time passes. If no value becomes available within
     * the specified amount of time, the function returns with a value of
     * #RW_THR_TIMEOUT. If the buffer is closed, and is empty or contains no
     * readable entries, this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Each time a new value is written into the buffer, \e one waiting
     * reader thread is unblocked to give it a chance to re-evaluate the
     * contents of the buffer, including the new entry. Since a write
     * operation only unblocks a single waiting reader thread, any other
     * threads that are waiting to peek or read remain blocked even if the
     * most recent transfer produces a change in program state that would
     * cause one or more guard functors to evaluate to \c true. This means
     * that developers should use a single thread to read from a guarded
     * buffer; additional threads could potentially be stuck waiting for
     * write operations even when there are entries eligible for reading.
     *
     * If the buffer is closed while a thread is blocked within this
     * function, that thread is unblocked, after which, this function
     * re-evaluates the guard functors one last time. If it finds a value
     * whose functor evaluates to \c true, it returns that value, otherwise
     * it returns by throwing an RWTHRClosedException.
     *
     * While this function guarantees that it will wait for a period of time
     * equal to or greater than the specified number of milliseconds, it
     * cannot guarantee that the thread will actually be scheduled for
     * execution at the end of the time-out period, and cannot prevent the
     * individual guard functors from blocking the caller for indefinite
     * periods of time.
     */
    RWWaitStatus
    read(Type& result,
         unsigned long milliseconds)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::read(result, milliseconds);
    }

    /**
     * Traverses the buffer, in an order that is determined by the
     * implementation supplied in derived classes, until it finds a value
     * whose guard functor is undefined or evaluates to \c true. At this
     * point the function copies the value into the instance passed as a
     * reference, and returns #RW_THR_COMPLETED to indicate that the read
     * succeeded. If the buffer is open and there are no values whose guard
     * functors evaluate to \c true, or if the buffer is empty, this
     * function blocks the calling thread until another value is inserted
     * into the buffer, or until the buffer is closed, or until the
     * specified amount of time passes. If no value becomes available within
     * the specified amount of time, the function returns with a value of
     * #RW_THR_TIMEOUT. If the buffer is closed, and is empty or contains no
     * readable entries, this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Each time a new value is written into the buffer, \e one waiting
     * reader thread is unblocked to give it a chance to re-evaluate the
     * contents of the buffer, including the new entry. Since a write
     * operation only unblocks a single waiting reader thread, any other
     * threads that are waiting to peek or read remain blocked even if the
     * most recent transfer produces a change in program state that would
     * cause one or more guard functors to evaluate to \c true. This means
     * that developers should use a single thread to read from a guarded
     * buffer; additional threads could potentially be stuck waiting for
     * write operations even when there are entries eligible for reading.
     *
     * If the buffer is closed while a thread is blocked within this
     * function, that thread is unblocked, after which, this function
     * re-evaluates the guard functors one last time. If it finds a value
     * whose functor evaluates to \c true, it returns that value, otherwise
     * it returns by throwing an RWTHRClosedException.
     *
     * While this function guarantees that it will wait for a period of time
     * equal to or greater than the specified number of milliseconds, it
     * cannot guarantee that the thread will actually be scheduled for
     * execution at the end of the time-out period, and cannot prevent the
     * individual guard functors from blocking the caller for indefinite
     * periods of time.
     */
    RWWaitStatus
    peek(Type& result,
         unsigned long milliseconds)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::peek(result, milliseconds);
    }

    /**
     * Traverses the buffer, in an order that is determined by the
     * implementation supplied in derived classes, until it finds a value
     * whose guard functor is undefined or evaluates to \c true. At this
     * point, the function copies the value into the instance passed as a
     * reference, and returns \c true to indicate that the read succeeded.
     * If the buffer is open and there are no values whose guard functors
     * evaluate to \c true, or if the buffer is empty, this function
     * immediately returns \c false to indicate that the read was
     * unsuccessful. If the buffer is closed, and is empty or contains no
     * readable values, this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * While these functions do not directly block the caller if the buffer
     * is empty or contains no readable values, they cannot prevent the
     * individual guard functors from indirectly blocking the caller.
     */
    bool
    tryPeek(Type& value)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::tryPeek(value);
    }

    /**
     * Traverses the buffer, in an order that is determined by the
     * implementation supplied in derived classes, until it finds a value
     * whose guard functor is undefined or evaluates to \c true. At this
     * point, the function removes the value and copies it into the instance
     * passed as a reference, and returns \c true to indicate that the read
     * succeeded. If the buffer is open and there are no values whose guard
     * functors evaluate to \c true, or if the buffer is empty, this
     * function immediately returns \c false to indicate that the read was
     * unsuccessful. If the buffer is closed, and is empty or contains no
     * readable values, this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * While these functions do not directly block the caller if the buffer
     * is empty or contains no readable values, they cannot prevent the
     * individual guard functors from indirectly blocking the caller.
     */
    bool
    tryRead(Type& value)
    {
        return RWTPCValBufferBaseDecorated<Type, GuardDecorator>::tryRead(value);
    }

    /**
     * Inserts a guarded value into the buffer at a position that is
     * determined by the implementation supplied in derived classes.
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
     * If the buffer is already closed when this function is called, the
     * function immediately returns by throwing an RWTHRClosedException.
     *
     * Calling this function on a full buffer may result in the invocation
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
     * this template class. The parameter \a guard is a reference to an
     * RWTFunctor<bool()> functor instance that is invoked during read() and
     * peek() operations to determine whether the associated value is
     * currently eligible for reading. An empty functor handle indicates
     * that the entry is always eligible for reading. The functor must not
     * attempt to access the buffer instance as such access results in
     * deadlock.
     */
    void
    write(const Type& value,
          const RWTFunctor<bool()>& guard);

    /**
     * Inserts a guarded value into the buffer at a position that is
     * determined by the implementation supplied in derived classes, but
     * only if the value may be written immediately; in other words, only if
     * there is sufficient free capacity.
     *
     * If the buffer is open and has sufficient capacity to hold another
     * value, this function inserts the value, and returns a value of
     * \c true to indicate that the write succeeded. If the buffer is open
     * and full, this function immediately returns a value of \c false to
     * indicate that the write was unsuccessful. If the buffer is closed,
     * this function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Calling this function on a full buffer may result in the invocation
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
     * this template class. The parameter \a guard is a reference to an
     * RWTFunctor<bool()> functor instance that is invoked during read() and
     * peek() operations to determine whether the associated value is
     * currently eligible for reading. An empty functor handle indicates
     * that the entry is always eligible for reading. The functor must not
     * attempt to access the buffer instance, as such access results in
     * deadlock.
     */
    bool
    tryWrite(const Type& value,
             const RWTFunctor<bool()>& guard);

    /**
     * Inserts a guarded value into the buffer at a position that is
     * determined by the implementation supplied in derived classes.
     *
     * If the buffer is open and has sufficient capacity to hold another
     * value, this function inserts the value and returns #RW_THR_COMPLETED
     * to indicate that the write succeeded. If the buffer is open and full,
     * this function blocks the calling thread until the buffer is no longer
     * full (because another thread or threads have read values or have
     * changed the maximum capacity), or until the buffer is closed, or
     * until the specified amount of time has passed. If sufficient space
     * does not become available within the specified amount of time, the
     * function returns a value of #RW_THR_TIMEOUT.
     *
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for room to write, the calling thread is
     * unblocked and the function returns by throwing an
     * RWTHRClosedException. If the buffer is already closed when this
     * function is called, it immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Calling this function on a full buffer may result in the invocation
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
     * - The parameter \a value is a \c const reference to an instance of
     * the type used to instantiate this template class.
     * - The parameter \a guard is a reference to an RWTFunctor<bool()>
     * functor instance that is invoked during read() and peek() operations
     * to determine whether the associated value is currently eligible for
     * reading. An empty functor handle indicates that the entry is always
     * eligible for reading. The functor must not attempt to access the
     * buffer instance as such access results in deadlock.
     * - The parameter \a milliseconds is an <tt>unsigned long</tt> value
     * that specifies the maximum number of milliseconds to wait for the
     * operation to complete.
     */
    RWWaitStatus
    write(const Type& value,
          const RWTFunctor<bool()>& guard,
          unsigned long milliseconds);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWTPCValBufferBaseGuarded(void);

protected:

    RWTPCValBufferBaseGuarded(void);

    RWTPCValBufferBaseGuarded(size_t maxCapacity);

    RWTPCValBufferBaseGuarded(size_t maxCapacity, bool isOpen);

    virtual bool
    _canRead(void) const;

    virtual GuardDecorator
    _read(void);

    virtual GuardDecorator
    _peek(void);

};

/*****************************************************************************/

template <class Type, class GuardDecorator>
inline
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::RWTPCValBufferBaseGuarded(void)
    : RWTPCValBufferBaseDecorated<Type, GuardDecorator>(),
      iter_(RWTPCValBufferBase<GuardDecorator>::buffer_.begin())
{
}

template <class Type, class GuardDecorator>
inline
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::RWTPCValBufferBaseGuarded(size_t maxCapacity)
    : RWTPCValBufferBaseDecorated<Type, GuardDecorator>(maxCapacity),
      iter_(RWTPCValBufferBase<GuardDecorator>::buffer_.begin())
{
}

template <class Type, class GuardDecorator>
inline
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::RWTPCValBufferBaseGuarded(size_t maxCapacity,
        bool isOpen)
    : RWTPCValBufferBaseDecorated<Type, GuardDecorator>(maxCapacity, isOpen),
      iter_(RWTPCValBufferBase<GuardDecorator>::buffer_.begin())
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTPCValBufferBaseGuarded.cc>
#endif

#endif // __rw_itc_RWTPCValBufferBaseGuarded_h__
