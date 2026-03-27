/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBase.cc#1 $
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

  RWTPCValBufferBase<Type> - Templatized base class for buffers with producer-
    consumer synchronization semantics whose entries are stored by-value.

******************************************************************************/

#include <rw/itc/RWTHRClosedException.h>
#include <rw/itc/RWTPCValBufferBase.h>
#include <rw/sync/RWTUnlockGuard.h>
#include <rw/timer.h>

template <class Type>
RWTPCValBufferBase<Type>::~RWTPCValBufferBase(void)
{
}

template <class Type>
size_t
RWTPCValBufferBase<Type>::_entries(void) const
{
    return buffer_.entries();
}

template <class Type>
Type
RWTPCValBufferBase<Type>::read(void)
{
    LockGuard lock(monitor());

    // Keep looping until there is something to read or the buffer is closed...
    while (!_canRead() && isOpen_) {

        // Each time we execute within this while-loop, we will either invoke
        // the callback or wait for a write, but cannot do both.

        // We must not do both because the callback may directly or indirectly
        // change the state of the buffer, eliminating the need to wait for
        // a write!

        // Is this the first thread to find the buffer empty since the last
        // write or callback registration? Is there a valid functor to invoke?

        if (!hasInvokedEmptyCallback_ &&
                onEmptyCallback_.isValid()) {

            // Yes, this thread is the first reader thread to find the buffer
            // empty since the last write or callback registration - it will need
            // to invoke the callback functor.
            hasInvokedEmptyCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onEmptyCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();

            // What important state changes might have occurred while the buffer
            // was unlocked, and what are the consequences of these changes?

            //  _canRead() == true:

            //  The buffer may have exited the empty state or an entry may have
            //  become "readable" as a result of write operations, so this thread
            //  will no longer need to wait for a write.

            //  isOpen_ == false && _canRead() == false

            //  The buffer has exited the open state and is now closed, so unless
            //  the buffer contains entries that this thread can read, the thread
            //  must not be allowed to wait for a write, since writes will not be
            //  allowed while the buffer is closed, so this method must exit with
            //  an exception.

            //  hasInvokedEmptyCallback_ == false;

            //  The buffer may have exited and reentered the empty state as a
            //  result of some combination of read and write operations, but the
            //  empty callback has not yet been invoked, so this thread must
            //  re-invoke the callback.

            //  previous != onEmptyCallback_

            //  The callback functor may have been changed, so the thread must
            //  use the new functor if the callback is re-invoked.
        }
        else {

            // The buffer is empty and this is not the first thread to
            // find the buffer is empty, or there is no callback to invoke.
            waitingReaders_++;

            try {
                // Unlock the buffer and wait for a write operation, a new empty
                // callback registration, a close operation, or an interrupt.
#if !defined(RW_THR_CONDITIONS_NOT_ALWAYS_SIGNALED)
                notEmpty_.wait();
#else
                // LinuxThreads don't always signal conditions waiting,
                // so the timeout allows us to break out of the wait and recheck
                // the condition manually.
                notEmpty_.wait(500);
#endif
                waitingReaders_--;
            }
            catch (...) {
                waitingReaders_--;
                throw;
            }
        }
    }

    // we can only reach this point if either there is something to
    // read, or if the buffer has been closed.  If there isn't
    // anything to read, then it must be the latter.
    if (!_canRead()) {
        // Throw an exception to indicate that the buffer is empty and
        // is closed.
        throw RWTHRClosedException();
    }

    Type result = _read();

    if (_entries() < maxEntries_) {
        // Indicate that the queue has exited the full state
        hasInvokedFullCallback_ = false;
        // If there are writers waiting, wake one up so it can write.
        if (waitingWriters_ > 0) {
            notFull_.signal();
        }
    }

    return result;
}

template <class Type>
bool
RWTPCValBufferBase<Type>::tryRead(Type& value)
{
    bool result;

    LockGuard lock(monitor());

    if (_canRead()) {
        value = _read();
        if (_entries() < maxEntries_) {
            // Indicate that the queue has left the full state
            hasInvokedFullCallback_ = false;
            // If there are writers waiting, wake one up so it can write.
            if (waitingWriters_ > 0) {
                notFull_.signal();
            }
        }
        result = true;
    }
    else if (!isOpen_) {
        // Throw an exception to indicate that the buffer is empty and is closed.
        throw RWTHRClosedException();
    }
    else {
        // Is this the first thread to find the buffer empty since the last
        // write or callback registration?  Is there a valid functor to invoke?

        if (!hasInvokedEmptyCallback_ &&
                onEmptyCallback_.isValid()) {

            // Yes, this thread is the first reader thread to find the buffer
            // empty since the last write or callback registration - it will need
            // to invoke the callback functor.
            hasInvokedEmptyCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onEmptyCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();
        }

        result = false;
    }

    return result;
}

template <class Type>
RWWaitStatus
RWTPCValBufferBase<Type>::read(Type& result, unsigned long milliseconds)
{
    RWUserTimer  timer;
    unsigned long elapsedMilliseconds;
    RWWaitStatus waitStatus = RW_THR_COMPLETED;

    LockGuard lock(monitor());

    bool b = _canRead();

    // Keep looping until there is something to read, the buffer is closed,
    // or the operation times-out...

    while (!b && isOpen_ && RW_THR_COMPLETED == waitStatus) {

        // Reset and re-start the timer...
        timer.reset();
        timer.start();

        // Each time we execute within this while-loop, we will either invoke
        // the callback or wait for a write, but cannot do both.

        // We must not do both because the callback may directly or indirectly
        // change the state of the buffer, eliminating the need to wait for
        // a write!

        // Is this the first thread to find the buffer empty since the last
        // write or callback registration?  Is there a valid functor to invoke?

        if (!hasInvokedEmptyCallback_ &&
                onEmptyCallback_.isValid()) {

            // Yes, this thread is the first reader thread to find the buffer
            // empty since the last write or callback registration - it will need
            // to invoke the callback functor.
            hasInvokedEmptyCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onEmptyCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();

            // What important state changes might have occurred while the buffer
            // was unlocked, and what are the consequences of these changes?

            //  _canRead() == true:

            //  The buffer may have exited the empty state as a result of write
            //  operations, so this thread will no longer need to wait for an
            //  entry to be written to the buffer.

            //  isOpen_ == false && _canRead() == false

            //  The buffer has exited the open state and is now closed, so unless
            //  the buffer contains entries that this thread can read, the thread
            //  must not be allowed to wait for a write, since writes will not be
            //  allowed while the buffer is closed.

            //  hasInvokedEmptyCallback_ == false;

            //  The buffer may have exited and re-entered the empty state as a
            //  result of some combination of read and write operations, but the
            //  empty callback has not yet been invoked, so this thread must
            //  re-invoke the callback.

            //  previous != onEmptyCallback_

            //  The callback functor may have been changed, so the thread must
            //  use the new functor if the callback is re-invoked.

            //  elapsed time >= milliseconds

            //  The time-out period may have elapsed.
        }
        else {
            // The buffer is empty and this is not the first thread to
            // find the buffer is empty, or there is no callback to invoke.
            waitingReaders_++;
            try {
                // Unlock the buffer and wait for a write operation, a new empty
                // callback registration, a close operation, or an interrupt.
                waitStatus = notEmpty_.wait(milliseconds);
                waitingReaders_--;
            }
            catch (...) {
                waitingReaders_--;
                throw;
            }
        }
        // Do we need to go back and wait again?
        if (!(b = _canRead()) && isOpen_ && RW_THR_COMPLETED == waitStatus) {

            // Yes, the thread either hasn't waited yet, or the thread did wait
            // and received a signal to indicate that a write has occurred, that a
            // new empty callback functor has been registered, or that the buffer
            // has been closed.

            // Determine how much time has elapsed, and use that to calculate
            // how much time, if any, remains from the original time-out period.
            timer.stop();
            elapsedMilliseconds = (unsigned long)(timer.elapsedTime() / 1000.0);
            if (elapsedMilliseconds < milliseconds) {
                // The operation has not timed-out.
                // Calculate the time remaining before the operation must time-out.
                milliseconds -= elapsedMilliseconds;
            }
            else {
                // The operation has timed-out.
                waitStatus = RW_THR_TIMEOUT;
            }
        }
    }
    if (b) {
        result = _read();
        waitStatus = RW_THR_COMPLETED;
        if (_entries() < maxEntries_) {
            // Indicate that the queue has exited the full state
            hasInvokedFullCallback_ = false;
            // If there are writers waiting, wake one up so it can write.
            if (waitingWriters_ > 0) {
                notFull_.signal();
            }
        }
    }
    else if (!isOpen_) {
        // Throw an exception to indicate that the buffer is empty and is closed.
        throw RWTHRClosedException();
    }
    return waitStatus;
}

template <class Type>
Type
RWTPCValBufferBase<Type>::peek(void)
{
    LockGuard lock(monitor());

    // Keep looping until there is something to read or the buffer is closed...
    while (!_canRead() && isOpen_) {

        // Each time we execute within this while-loop, we will either invoke
        // the callback or wait for a write, but cannot do both.

        // We must not do both because the callback may directly or indirectly
        // change the state of the buffer, eliminating the need to wait for
        // a write!

        // Is this the first thread to find the buffer empty since the last
        // write or callback registration? Is there a valid functor to invoke?

        if (!hasInvokedEmptyCallback_ &&
                onEmptyCallback_.isValid()) {

            // Yes, this thread is the first reader thread to find the buffer
            // empty since the last write or callback registration - it will need
            // to invoke the callback functor.
            hasInvokedEmptyCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onEmptyCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();

            // What important state changes might have occurred while the buffer
            // was unlocked, and what are the consequences of these changes?

            //  _canRead() == true:

            //  The buffer may have exited the empty state as a result of write
            //  operations, so this thread will no longer need to wait for a
            //  write.

            //  isOpen_ == false && _canRead() == false

            //  The buffer has exited the open state and is now closed, so unless
            //  the buffer contains entries that this thread can read, the thread
            //  must not be allowed to wait for a write, since writes will not be
            //  allowed while the buffer is closed, so this method must exit with
            //  an exception.

            //  hasInvokedEmptyCallback_ == false;

            //  The buffer may have exited and reentered the empty state as a
            //  result of some combination of read and write operations, but the
            //  empty callback has not yet been invoked, so this thread must
            //  re-invoke the callback.

            //  previous != onEmptyCallback_

            //  The callback functor may have been changed, so the thread must
            //  use the new functor if the callback is re-invoked.
        }
        else {

            // The buffer is empty and this is not the first thread to
            // find the buffer is empty, or there is no callback to invoke.
            waitingReaders_++;

            try {
                // Unlock the buffer and wait for a write operation, a new empty
                // callback registration, a close operation, or an interrupt.
                notEmpty_.wait();
                waitingReaders_--;
            }
            catch (...) {
                waitingReaders_--;
                throw;
            }
        }
    }

    // we can only reach this point if either there is something to
    // read, or if the buffer has been closed.  If there isn't
    // anything to read, then it must be the latter.
    if (!_canRead()) {
        // Throw an exception to indicate that the buffer is empty and
        // is closed.
        throw RWTHRClosedException();
    }

    return _peek();
}

template <class Type>
bool
RWTPCValBufferBase<Type>::tryPeek(Type& value)
{
    bool result;

    LockGuard lock(monitor());

    if (_canRead()) {
        value = _peek();
        result = true;
    }
    else if (!isOpen_) {
        // Throw an exception to indicate that the buffer is empty and is closed.
        throw RWTHRClosedException();
    }
    else {
        // Is this the first thread to find the buffer empty since the last
        // write or callback registration?  Is there a valid functor to invoke?

        if (!hasInvokedEmptyCallback_ &&
                onEmptyCallback_.isValid()) {
            // Yes, this thread is the first reader thread to find the buffer
            // empty since the last write or callback registration - it will need
            // to invoke the callback functor.
            hasInvokedEmptyCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onEmptyCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();
        }

        result = false;
    }
    return result;
}

template <class Type>
RWWaitStatus
RWTPCValBufferBase<Type>::peek(Type& result, unsigned long milliseconds)
{
    RWUserTimer  timer;
    unsigned long elapsedMilliseconds;
    RWWaitStatus waitStatus = RW_THR_COMPLETED;

    LockGuard lock(monitor());

    bool b = _canRead();

    // Keep looping until there is something to read, the buffer is closed,
    // or the operation times-out...

    while (!b && isOpen_ && RW_THR_COMPLETED == waitStatus) {

        // Reset and re-start the timer...
        timer.reset();
        timer.start();

        // Each time we execute within this while-loop, we will either invoke
        // the callback or wait for a write, but cannot do both.

        // We must not do both because the callback may directly or indirectly
        // change the state of the buffer, eliminating the need to wait for
        // a write!

        // Is this the first thread to find the buffer empty since the last
        // write or callback registration?  Is there a valid functor to invoke?

        if (!hasInvokedEmptyCallback_ &&
                onEmptyCallback_.isValid()) {

            // Yes, this thread is the first reader thread to find the buffer
            // empty since the last write or callback registration - it will need
            // to invoke the callback functor.
            hasInvokedEmptyCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onEmptyCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());


            // Invoke the callback.
            callback();

            // What important state changes might have occurred while the buffer
            // was unlocked, and what are the consequences of these changes?

            //  _canRead() == true:

            //  The buffer may have exited the empty state as a result of write
            //  operations, so this thread will no longer need to wait for an
            //  entry to be written to the buffer.

            //  isOpen_ == false && _canRead() == false

            //  The buffer has exited the open state and is now closed, so unless
            //  the buffer contains entries that this thread can read, the thread
            //  must not be allowed to wait for a write, since writes will not be
            //  allowed while the buffer is closed.

            //  hasInvokedEmptyCallback_ == false;

            //  The buffer may have exited and re-entered the empty state as a
            //  result of some combination of read and write operations, but the
            //  empty callback has not yet been invoked, so this thread must
            //  re-invoke the callback.

            //  previous != onEmptyCallback_

            //  The callback functor may have been changed, so the thread must
            //  use the new functor if the callback is re-invoked.

            //  elapsed time >= milliseconds

            //  The time-out period may have elapsed.
        }
        else {
            // The buffer is empty and this is not the first thread to
            // find the buffer is empty, or there is no callback to invoke.
            waitingReaders_++;
            try {
                // Unlock the buffer and wait for a write operation, a new empty
                // callback registration, a close operation, or an interrupt.
                waitStatus = notEmpty_.wait(milliseconds);
                waitingReaders_--;
            }
            catch (...) {
                waitingReaders_--;
                throw;
            }
        }
        // Do we need to go back and wait again?
        if (!(b = _canRead()) && isOpen_ && RW_THR_COMPLETED == waitStatus) {

            // Yes, the thread either hasn't waited yet, or the thread did wait
            // and received a signal to indicate that a write has occurred, that a
            // new empty callback functor has been registered, or that the buffer
            // has been closed.

            // Determine how much time has elapsed, and use that to calculate
            // how much time, if any, remains from the original time-out period.
            timer.stop();
            elapsedMilliseconds = (unsigned long)(timer.elapsedTime() / 1000.0);
            if (elapsedMilliseconds < milliseconds) {
                // The operation has not timed-out.
                // Calculate the time remaining before the operation must time-out.
                milliseconds -= elapsedMilliseconds;
            }
            else {
                // The operation has timed-out.
                waitStatus = RW_THR_TIMEOUT;
            }
        }
    }
    if (b) {
        result = _peek();
        waitStatus = RW_THR_COMPLETED;
    }
    else if (!isOpen_) {
        // Throw an exception to indicate that the buffer is empty and is closed.
        throw RWTHRClosedException();
    }
    return waitStatus;
}

template <class Type>
void
RWTPCValBufferBase<Type>::write(const Type& value)
{
    LockGuard lock(monitor());

    // Keep looping until there is room to write or the buffer is closed...
    while (!_canWrite() && isOpen_) {

        // Each time we execute within this while-loop, we will either invoke
        // the full callback or wait for room to write, but not both.

        // We must not do both because the callback may directly or indirectly
        // change the state of the buffer, eliminating the need to wait for room!

        // Is this the first thread to find the buffer full since the last read,
        // capacity change, or callback registration?
        // Is there a valid functor to invoke?

        if (!hasInvokedFullCallback_ &&
                onFullCallback_.isValid()) {

            // Yes, this thread is the first writer thread to find the buffer
            // full since the last time the buffer was less than full, or
            // since the last callback registration - it will need to invoke the
            // callback functor.
            hasInvokedFullCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onFullCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();

            // What important state changes might have occurred while the buffer
            // was unlocked, and what are the consequences of these changes?

            //  _canWrite() == true:

            //  The buffer may have exited the full state as a result of read
            //  operations or a capacity change, or the buffer may have been
            //  closed, so this thread will no longer need to wait for any more
            //  reads, and if the buffer has been closed, the method must exit
            //  with an exception.

            //  hasInvokedFullcallback_ == false;

            //  The buffer may have exited and reentered the full state as a
            //  result of some combination of read and write operations, but the
            //  full callback has not yet been invoked, so this thread must
            //  re-invoke the callback.

            //  previous != onFullCallback_

            //  The callback functor may have been changed, so the thread must
            //  use the new functor if the callback is re-invoked.
        }
        else {

            // The buffer is full and this is not the first thread to
            // find the buffer is full, or there is no callback to invoke.

            waitingWriters_++;
            try {
                notFull_.wait();
                waitingWriters_--;
            }
            catch (...) {
                waitingWriters_--;
                throw;
            }
        }
    }
    if (_canWrite()) {
        _write(value);
        // Indicate that the queue has exited the empty state
        hasInvokedEmptyCallback_ = false;
        // If there are readers waiting, wake one up so it can read.
        if (waitingReaders_ > 0) {
            notEmpty_.signal();
        }
    }
    else if (!isOpen_) {
        // Throw an exception to indicate that the buffer is closed.
        throw RWTHRClosedException();
    }
}

template <class Type>
bool
RWTPCValBufferBase<Type>::tryWrite(const Type& value)
{
    bool result;

    LockGuard lock(monitor());

    if (_canWrite() && isOpen_) {
        _write(value);
        // Indicate that the queue has exited the empty state
        hasInvokedEmptyCallback_ = false;
        // If there are readers waiting, wake one up so it can read.
        if (waitingReaders_ > 0) {
            notEmpty_.signal();
        }
        result = true;
    }
    else if (!isOpen_) {
        // Throw an exception to indicate that the buffer is closed.
        throw RWTHRClosedException();
    }
    else {
        if (!hasInvokedFullCallback_ &&
                onFullCallback_.isValid()) {

            // Yes, this thread is the first writer thread to find the buffer
            // full since the last time the buffer was less than full, or
            // since the last callback registration - it will need to invoke the
            // callback functor.
            hasInvokedFullCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onFullCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();
        }

        result = false;
    }
    return result;
}

template <class Type>
RWWaitStatus
RWTPCValBufferBase<Type>::write(const Type& value, unsigned long milliseconds)
{
    RWUserTimer  timer;
    unsigned long elapsedMilliseconds;
    RWWaitStatus waitStatus = RW_THR_COMPLETED;

    LockGuard lock(monitor());

    // Keep looping until there is room, the buffer is closed, or until the
    // operation times out...

    while (!_canWrite() && isOpen_ && RW_THR_COMPLETED == waitStatus) {

        // Reset and restart the timer
        timer.reset();
        timer.start();

        // Each time we execute within this while-loop, we will either invoke
        // the full callback or wait for room to write, but not both.

        // We must not do both because the callback may directly or indirectly
        // change the state of the buffer, eliminating the need to wait for room!

        // Is this the first thread to find the buffer full since the last read,
        // capacity change, or callback registration?
        // Is there a valid functor to invoke?

        if (!hasInvokedFullCallback_ &&
                onFullCallback_.isValid()) {

            // Yes, this thread is the first writer thread to find the buffer
            // full since the last time the buffer was less than full, or
            // since the last callback registration - it will need to invoke the
            // callback functor.
            hasInvokedFullCallback_ = true;

            // Save the callback functor in a local variable
            RWTFunctor<void()> callback = onFullCallback_;

            // Temporarily unlock the buffer so the callback can access the buffer
            UnlockGuard unlock(monitor());

            // Invoke the callback.
            callback();

            // What important state changes might have occurred while the buffer
            // was unlocked, and what are the consequences of these changes?

            //  _canWrite() == true:

            //  The buffer may have exited the full state as a result of read
            //  operations or a capacity change, or the buffer may have been
            //  closed, so this thread will no longer need to wait for any more
            //  reads, and if the buffer has been closed, the method must exit
            //  with an exception.

            //  hasInvokedFullcallback_ == false;

            //  The buffer may have exited and reentered the full state as a
            //  result of some combination of read and write operations, but the
            //  full callback has not yet been invoked, so this thread must
            //  re-invoke the callback.

            //  previous != onFullCallback_

            //  The callback functor may have been changed, so the thread must
            //  use the new functor if the callback is re-invoked.

            //  elapsed time >= milliseconds

            //  The time-out period may have elapsed.
        }
        else {

            // The buffer is full and this is not the first thread to
            // find the buffer is full, or there is no callback to invoke.

            waitingWriters_++;
            try {
                waitStatus = (notFull_).wait(milliseconds);
                waitingWriters_--;
            }
            catch (...) {
                waitingWriters_--;
                throw;
            }
        }
        // Has the operation timed-out?
        if (isOpen_ && RW_THR_COMPLETED == waitStatus) {

            // No, the thread either hasn't waited yet, or the thread did wait
            // and received a signal to indicate that the buffer is no longer full,
            // a new full callback functor has been registered, or that the buffer
            // has been closed.

            // Is the buffer still full and open? Does the thread still need to wait?
            if (!_canWrite()) {

                // The buffer is full and open - the thread still needs to wait.
                // Determine how much time has elapsed, and use that to calculate
                // how much time, if any, remains from the original time-out period.
                timer.stop();
                elapsedMilliseconds = (unsigned long)(timer.elapsedTime() * 1000.0);
                if (elapsedMilliseconds < milliseconds) {
                    // The operation has not timed-out.
                    // Calculate the time remaining before the operation must time-out.
                    milliseconds -= elapsedMilliseconds;
                }
                else {
                    // The operation has timed-out.
                    waitStatus = RW_THR_TIMEOUT;
                }
            }
        }
    }
    // Can we write, or did we time-out?
    if (_canWrite()) {
        _write(value);
        waitStatus = RW_THR_COMPLETED;
        // Indicate that the queue has exited the empty state.
        hasInvokedEmptyCallback_ = false;
        // If there are readers waiting, wake one up so it can read.
        if (waitingReaders_ > 0) {
            notEmpty_.signal();
        }
    }
    else if (!isOpen_) {
        // Throw an exception to indicate that the buffer is closed.
        throw RWTHRClosedException();
    }
    return waitStatus;
}

template <class Type>
void
RWTPCValBufferBase<Type>::_flush(void)
{
    buffer_.clear();
    // Indicate that the queue has exited the full state
    hasInvokedFullCallback_ = false;
    // If there are writers waiting, wake one up so it can write.
    if (waitingWriters_ > 0) {
        notFull_.signal();
    }
}

template <class Type>
Type
RWTPCValBufferBase<Type>::_read(void)
{
    return buffer_.removeFirst();
}

template <class Type>
Type
RWTPCValBufferBase<Type>::_peek(void)
{
    return buffer_.first();
}
