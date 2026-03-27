#ifndef __rw_itc_RWTPCValBufferBaseDecorated_h__
#define __rw_itc_RWTPCValBufferBaseDecorated_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBaseDecorated.h#1 $
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
#  define RWPCValBufferBaseDecorated RWTPCValBufferBaseDecorated
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * Base class that provides buffered producer-consumer synchronization
 * semantics for exchanging \e decorated values between cooperating threads.
 *
 * RWTPCValBufferBaseDecorated is the base class for the family of classes
 * that provides buffered producer-consumer synchronization semantics for
 * exchanging \e decorated values between cooperating threads.
 *
 * In the producer-consumer synchronization model, reader threads
 * (consumers) are blocked while a buffer is empty, and writer threads
 * (producers) are blocked while a buffer is full. A buffer is considered
 * full when the number of unread entries equals or exceeds some
 * user-specified maximum capacity.
 *
 * The write operations provided by this class and its subclasses bind
 * additional data items to each value prior to storing that value in an
 * internal buffer. These additional data items are referred to as
 * \e decorations, and are generally used to control the insertion or
 * extraction process. Some examples of decorations include guard functors,
 * instances, and priority values.
 *
 * The template parameter \c Decorator identifies the class that is used to
 * encapsulate both the value and its decorations as a single object for
 * storage in the internal buffer. The decorator classes used by subclasses
 * to instantiate this class are intended for the Threads Module's internal
 * use and are not documented as part of the public interface.
 */
template <class Type, class Decorator>
class RWTPCValBufferBaseDecorated :
    protected RWTPCValBufferBase<Decorator>
{

public:

    typedef Type     DataType;

    // Adjust access to base class members that we want to expose

    using RWTPCValBufferBase<Decorator>::setCapacity;
    using RWTPCValBufferBase<Decorator>::getCapacity;
    using RWTPCValBufferBase<Decorator>::open;
    using RWTPCValBufferBase<Decorator>::isOpen;
    using RWTPCValBufferBase<Decorator>::close;
    using RWTPCValBufferBase<Decorator>::canRead;
    using RWTPCValBufferBase<Decorator>::canWrite;
    using RWTPCValBufferBase<Decorator>::entries;
    using RWTPCValBufferBase<Decorator>::flush;
    using RWTPCValBufferBase<Decorator>::getEmptyCallback;
    using RWTPCValBufferBase<Decorator>::setEmptyCallback;
    using RWTPCValBufferBase<Decorator>::getFullCallback;
    using RWTPCValBufferBase<Decorator>::setFullCallback;
    using RWTPCValBufferBase<Decorator>::getOpenCallback;
    using RWTPCValBufferBase<Decorator>::setOpenCallback;
    using RWTPCValBufferBase<Decorator>::getCloseCallback;
    using RWTPCValBufferBase<Decorator>::setCloseCallback;

    /**
     * Removes and returns the next available value stored in the buffer,
     * where the availability and ordering of values is determined by the
     * implementation supplied in derived classes. The value is of the type
     * used to instantiate this template class.
     *
     * If the buffer contains a value that is eligible for reading, this
     * function removes and returns that value even if the buffer is closed.
     * If the buffer is open and there are no values that are eligible for
     * reading, or if the buffer is empty, this function blocks the calling
     * thread until a value becomes available or until the buffer is closed.
     *
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for a value to become available, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the buffer is both empty and closed when
     * this function is called, the function immediately returns by throwing
     * an RWTHRClosedException.
     *
     * Calling this function on an empty buffer may result in the invocation
     * of the on-empty callback functor, if a valid one has been registered.
     * The on-empty callback functor is guaranteed to execute only within a
     * reader thread. Calling this function on an empty buffer results in
     * the invocation of an on-empty callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an empty buffer when an on-empty
     * callback is registered.
     * - The calling thread is the first to attempt reading from an empty
     * buffer in which an on-empty callback was previously registered.
     *
     * Repeated attempts to read from an empty buffer does not result in
     * repeated invocations of the callback functor. Once the empty buffer
     * is written to, however, it resets the callback trigger. If the buffer
     * again becomes empty, the first thread to attempt to read from it
     * causes another invocation of the on-empty callback.
     */
    Type
    read(void);

    /**
     * Removes and returns the next immediately available value stored in
     * the buffer, where the availability and ordering of values is
     * determined by the implementation supplied in derived classes.
     *
     * If the buffer contains a value that is eligible for reading, this
     * function removes that value, copies it into the instance passed as a
     * reference, and returns a value of \c true to indicate that the read
     * succeeded. If the buffer is open and there are no values that are
     * eligible for reading, or if the buffer is empty, this function
     * immediately returns a value of \c false to indicate that the read was
     * unsuccessful. If the buffer is both empty and closed, this function
     * immediately returns by throwing an RWTHRClosedException.
     *
     * Calling this function on an empty buffer may result in the invocation
     * of the on-empty callback functor, if a valid one has been registered.
     * The on-empty callback functor is guaranteed to execute only within a
     * reader thread. Calling this function on an empty buffer results in
     * the invocation of an on-empty callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an empty buffer when an on-empty
     * callback is registered.
     * - The calling thread is the first to attempt reading from an empty
     * buffer in which an on-empty callback was previously registered.
     *
     * Repeated attempts to read from an empty buffer does not result in
     * repeated invocations of the callback functor. Once the empty buffer
     * is written to, however, it resets the callback trigger. If the buffer
     * again becomes empty, the first thread to attempt to read from it
     * causes another invocation of the on-empty callback.
     *
     * While this function guarantees not to block the caller if there are
     * no readable entries, it cannot prevent the on-empty callback functor,
     * if executed, from indirectly blocking the caller.
     *
     * This function takes the parameter \a result, which is a reference to
     * an instance of the type used to instantiate this template class. The
     * result, if any, is copied into this instance using its assignment
     * operator.
     */
    bool
    tryRead(Type& result);

    /**
     * Removes and returns the next available value stored in the buffer,
     * where the availability and ordering of values is determined by the
     * implementation supplied in derived classes.
     *
     * If the buffer contains a value that is eligible for reading, this
     * function removes that value, copies it into the instance passed as a
     * reference, and returns a value of #RW_THR_COMPLETED to indicate that
     * the read succeeded. If the buffer is open and there are no values
     * that are eligible for reading, or if the buffer is empty, this
     * function blocks the calling thread until a value becomes available,
     * or until the buffer is closed, or until the specified amount of time
     * passes. If no value becomes available within the specified amount of
     * time, the function returns with value of #RW_THR_TIMEOUT.
     *
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for a value to become available, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the buffer is both empty and closed when
     * this function is called, the function immediately returns by throwing
     * an RWTHRClosedException.
     *
     * Calling this function on an empty buffer may result in the invocation
     * of the on-empty callback functor, if a valid one has been registered.
     * The on-empty callback functor is guaranteed to execute only within a
     * reader thread. Calling this function on an empty buffer results in
     * the invocation of an on-empty callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an empty buffer when an on-empty
     * callback is registered.
     * - The calling thread is the first to attempt reading from an empty
     * buffer in which an on-empty callback was previously registered.
     *
     * Repeated attempts to read from an empty buffer does not result in
     * repeated invocations of the callback functor. Once the empty buffer
     * is written to, however, it resets the callback trigger. If the buffer
     * again becomes empty, the first thread to attempt to read from it
     * causes another invocation of the on-empty callback.
     *
     * While this function guarantees to wait, if necessary, for a period
     * time equal to or greater than the specified number of milliseconds,
     * it cannot guarantee that the thread is actually scheduled for
     * execution at the end of the time-out period. It cannot prevent the
     * on-empty callback functor, if executed, from indirectly blocking the
     * caller for an indefinite period of time.
     *
     * This function takes two parameters. The parameter \a result is a
     * reference to an instance of the type used to instantiate this
     * template class. The result, if any, is copied into this instance
     * using its assignment operator. The parameter \a milliseconds is an
     * <tt>unsigned long</tt> value that specifies the maximum number of
     * milliseconds to wait for the operation to complete.
     */
    RWWaitStatus
    read(Type& result,
         unsigned long milliseconds);

    /**
     * Copies and returns the next available value stored in the buffer,
     * where the availability and ordering of values is determined by the
     * implementation supplied in derived classes. The value is of the type
     * used to instantiate this template class.
     *
     * If the buffer contains a value that is eligible for reading, this
     * function copies and returns that value even if the buffer is closed.
     * If the buffer is open and there are no values that are eligible for
     * reading, or if the buffer is empty, this function blocks the calling
     * thread until a value becomes available or until the buffer is closed.
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for a value to become available, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the buffer is both empty and closed when
     * this function is called, it immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Calling this function on an empty buffer may result in the invocation
     * of the on-empty callback functor, if a valid one has been registered.
     * The on-empty callback functor is guaranteed to execute only within a
     * reader thread. Calling this function on an empty buffer results in
     * the invocation of an on-empty callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an empty buffer when an on-empty
     * callback is registered.
     * - The calling thread is the first to attempt reading from an empty
     * buffer in which an on-empty callback was previously registered.
     *
     * Repeated attempts to read from an empty buffer does not result in
     * repeated invocations of the callback functor. Once the empty buffer
     * is written to, however, it resets the callback trigger. If the buffer
     * again becomes empty, the first thread to attempt to read from it
     * causes another invocation of the on-empty callback.
     */
    Type
    peek(void);

    /**
     * Copies and returns the next immediately available value stored in the
     * buffer, where the availability and ordering of values is determined
     * by the implementation supplied in derived classes.
     *
     * If the buffer contains a value that is eligible for reading, this
     * function copies that value into the instance passed as a reference,
     * and returns a value of \c true to indicate that the read succeeded.
     * If the buffer is open and there are no values that are eligible for
     * reading, or if the buffer is empty, this function immediately returns
     * \c false to indicate that the read was unsuccessful. If the buffer is
     * both empty and closed, this function immediately returns by throwing
     * an RWTHRClosedException.
     *
     * Calling this function on an empty buffer may result in the invocation
     * of the on-empty callback functor, if a valid one has been registered.
     * The on-empty callback functor is guaranteed to execute only within a
     * reader thread. Calling this function on an empty buffer results in
     * the invocation of an on-empty callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an empty buffer when an on-empty
     * callback is registered.
     * - The calling thread is the first to attempt reading from an empty
     * buffer in which an on-empty callback was previously registered.
     *
     * Repeated attempts to read from an empty buffer does not result in
     * repeated invocations of the callback functor. Once the empty buffer
     * is written to, however, it resets the callback trigger. If the buffer
     * again becomes empty, the first thread to attempt to read from it
     * causes another invocation of the on-empty callback.
     *
     * While this function guarantees not to block the caller if there are
     * no readable entries, it cannot prevent the on-empty callback functor,
     * if executed, from indirectly blocking the caller.
     *
     * This function takes the parameter \a result, which is a reference to
     * an instance of the type used to instantiate this template class. The
     * result, if any, is copied into this instance using its assignment
     * operator.
     */
    bool
    tryPeek(Type& result);

    /**
     * Copies and returns the next available value stored in the buffer,
     * where the availability and ordering of values is determined by the
     * implementation supplied in derived classes.
     *
     * If the buffer contains a value that is eligible for reading, this
     * function copies that value into the instance passed as a reference,
     * and returns a value of #RW_THR_COMPLETED to indicate that the read
     * succeeded. If the buffer is open and there are no values that are
     * eligible for reading, or if the buffer is empty, this function blocks
     * the calling thread until a value becomes available, or until the
     * buffer is closed, or until the specified amount of time has passed.
     * If no value becomes available within the specified amount of time,
     * the function returns with a value of #RW_THR_TIMEOUT.
     *
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for a value to become available, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the buffer is both empty and closed when
     * this function is called, it immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Calling this function on an empty buffer may result in the invocation
     * of the on-empty callback functor, if a valid one has been registered.
     * The on-empty callback functor is guaranteed to execute only within a
     * reader thread. Calling this function on an empty buffer results in
     * the invocation of an on-empty callback functor under either of these
     * scenarios:
     *
     * - The calling thread is waiting on an empty buffer when an on-empty
     * callback is registered.
     * - The calling thread is the first to attempt reading from an empty
     * buffer in which an on-empty callback was previously registered.
     *
     * Repeated attempts to read from an empty buffer does not result in
     * repeated invocations of the callback functor. Once the empty buffer
     * is written to, however, it resets the callback trigger. If the buffer
     * again becomes empty, the first thread to attempt to read from it
     * causes another invocation of the on-empty callback.
     *
     * While this function guarantees to wait, if necessary, for a period of
     * time equal to or greater than the specified number of milliseconds,
     * this function cannot guarantee that the thread is actually scheduled
     * for execution at the end of the time-out period. The function cannot
     * prevent the on-empty callback functor, if executed, from indirectly
     * blocking the caller for an indefinite period of time.
     *
     * This function takes two parameters. The parameter \a result is a
     * reference to an instance of the type used to instantiate this
     * template class. The result, if any, is copied into this instance
     * using its assignment operator. The parameter \a milliseconds is an
     * <tt>unsigned long</tt> value that specifies the maximum number of
     * milliseconds to wait for the operation to complete.
     */
    RWWaitStatus
    peek(Type& result,
         unsigned long milliseconds);

    /**
     * Inserts a decorated value into the buffer at a position that is
     * determined by the implementation supplied in derived classes. The
     * value is decorated using the defaults defined by the implementation
     * supplied in derived classes.
     *
     * If the buffer is open and has sufficient capacity to hold another
     * value, this function inserts the value. If the buffer is open and yet
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
     */
    void
    write(const Type& value);

    /**
     * Inserts a decorated value into the buffer at a position that is
     * determined by the implementation supplied in derived classes, but
     * only if the value may be written immediately; in other words, only if
     * there is sufficient free capacity. The value is decorated using the
     * defaults defined by the implementation supplied in derived classes.
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
     * is full, this function cannot prevent the on-full callback functor,
     * if executed, from indirectly blocking the caller.
     *
     * This function takes the parameter \a value, which is a \c const
     * reference to an instance of the type used to instantiate this
     * template class.
     */
    bool
    tryWrite(const Type& value);

    /**
     * Inserts a decorated value into the buffer at a position that is
     * determined by the implementation supplied in derived classes. The
     * value is decorated using the defaults defined by the implementation
     * supplied in derived classes.
     *
     * If the buffer is open and has sufficient capacity to hold another
     * value, this function inserts the value, and returns a value of
     * #RW_THR_COMPLETED to indicate that the write succeeded. If the buffer
     * is open and full, this function blocks the calling thread until the
     * buffer is no longer full (because another thread or threads have read
     * values or have changed the maximum capacity), or until the buffer is
     * closed, or until the specified amount of time has passes. If
     * sufficient space does not become available within the specified
     * amount of time, the function returns a value of #RW_THR_TIMEOUT.
     *
     * If the buffer is closed while the calling thread is blocked and
     * waiting within this function for room to write, the calling thread is
     * unblocked and the function returns by throwing an
     * RWTHRClosedException. If the buffer is already closed when this
     * function is called, the function immediately returns by throwing an
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
     * While this function guarantees to wait, if necessary, for a time
     * equal to or greater than the specified number of milliseconds, it
     * cannot guarantee that the thread is actually scheduled for execution
     * at the end of the time-out period. It cannot prevent the on-full
     * callback functor, if executed, from indirectly blocking the caller
     * for an indefinite period of time.
     *
     * This function takes two parameters. The parameter \a value is a
     * \c const reference to an instance of the type used to instantiate
     * this template class. The parameter \a milliseconds is an
     * <tt>unsigned long</tt> value that specifies the maximum number of
     * milliseconds to wait for the operation to complete.
     */
    RWWaitStatus
    write(const Type& value,
          unsigned long milliseconds);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWTPCValBufferBaseDecorated(void);

protected:

    RWTPCValBufferBaseDecorated(void);

    RWTPCValBufferBaseDecorated(size_t maxCapacity);

    RWTPCValBufferBaseDecorated(size_t maxCapacity, bool isOpen);
};

/*****************************************************************************/

template <class Type, class Decorator>
inline
RWTPCValBufferBaseDecorated<Type, Decorator>::RWTPCValBufferBaseDecorated(void)
{
}

template <class Type, class Decorator>
inline
RWTPCValBufferBaseDecorated<Type, Decorator>::RWTPCValBufferBaseDecorated(
    size_t maxCapacity)
    : RWTPCValBufferBase<Decorator>(maxCapacity)
{
}

template <class Type, class Decorator>
inline
RWTPCValBufferBaseDecorated<Type, Decorator>::RWTPCValBufferBaseDecorated(
    size_t maxCapacity, bool b)
    : RWTPCValBufferBase<Decorator>(maxCapacity, b)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTPCValBufferBaseDecorated.cc>
#endif

#endif // __rw_itc_RWTPCValBufferBaseDecorated_h__
