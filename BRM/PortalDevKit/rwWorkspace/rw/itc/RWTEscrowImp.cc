/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTEscrowImp.cc#1 $
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

  RWTEscrowImp<Redeemable> - Escrow implementation base class.

******************************************************************************/

#include <rw/itc/RWTEscrowImp.h>
#include <rw/itc/RWTHREscrowAlreadyClosed.h>
#include <rw/functor/rwBind.h>
#include <rw/sync/RWTLockGuard.h>
#include <rw/threxcept/RWTHROperationAborted.h>

template <class Redeemable>
RWTEscrowImp<Redeemable>::~RWTEscrowImp(void)
{
}

template <class Redeemable>
RWTEscrowImp<Redeemable>::RWTEscrowImp(void)
    :  isRedeemed_(false)
    ,  isAborted_(false)
{
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::abort(void)
{
    LockGuard lock(monitor());

    if (!isRedeemable()) {
        isAborted_ = true;
        _abort();          // child hook.
        lock.release();    // since callbacks will be calling redeem() on this.
        fireAllCallbacks(); // allow anyone waiting to reap status.
    }
    // else ignore... the final state of the Escrow has been set.
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::addCallback(const RWTIOUResultCallback& iouResultCallback)
{
    LockGuard lock(monitor());

    // If the escrow isn't redeemable yet, then store the callback
    // in the callback list.
    if (!isRedeemable()) {
        RWTLockGuard<RWMutexLock> guard(cbListMutex_);
        cbList_.insert(iouResultCallback);
    }
    else {
        // An exception, abort condition, or valid result is already available;
        // immediately fire-off the callback
        lock.release(); // Since callbacks will likely call redeem() on this.
        iouResultCallback(RWTEscrowHandle<Redeemable>(this));
    }
}

template <class Redeemable>
bool
RWTEscrowImp<Redeemable>::aborted(void) const
{
    LockGuard lock(monitor());
    return isAborted();
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::close(const Redeemable& value)
{
    LockGuard lock(monitor());

    if (isAborted()) {
        throwAbort();
    }
    if (isException()) {
        throwStoredException();
    }
    if (!_closed()) {
        _close(value);    // close!
    }
    else {
        throw RWTHREscrowAlreadyClosed();
    }

    if (_closed()) {
        // ensure that it was actually closed.
        lock.release(); // since callbacks will be calling redeem() on this.
        fireAllCallbacks();
    }
}

template <class Redeemable>
bool
RWTEscrowImp<Redeemable>::closeable(void) const
{
    LockGuard lock(monitor());
    return !isRedeemable();
}

template <class Redeemable>
bool
RWTEscrowImp<Redeemable>::closed(void) const
{
    LockGuard lock(monitor());
    return _closed();
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::fireAllCallbacks(void)
{
    RW_ASSERT(!isAcquired()); // mutex must NOT already be acquired

    // We don't guard since callbacks are going to be calling redeem() on
    // this. If we guarded, the call to redeem() would try to acquire the
    // guard resulting in deadlock.

    // Fire the callbacks. They will be removed from the callback list
    // following executing.
    RWTLockGuard<RWMutexLock> guard(cbListMutex_);
    std::for_each(cbList_.begin(), cbList_.end(), rwBind(&RWTIOUResultCallback::operator(), rw1, this));
    cbList_.clear();
}

template <class Redeemable>
bool
RWTEscrowImp<Redeemable>::inError(void) const
{
    LockGuard lock(monitor());
    return isException();
}

template <class Redeemable>
RWTEscrowHandle<Redeemable>
RWTEscrowImp<Redeemable>::newInstance(void) const
{
    LockGuard lock(monitor());
    return _newInstance();
}

template <class Redeemable>
const Redeemable&
RWTEscrowImp<Redeemable>::redeem(void) const
{
    LockGuard lock(monitor());

    if (isException()) {
        throwStoredException();
    }

    if (isAborted()) {
        throwAbort();
    }

    const Redeemable& value = _redeem(); // call concrete implementation

    // If we get here then everything went well. Set isRedeemed_ flag.
    RWTEscrowImp<Redeemable>* self =
        const_cast <RWTEscrowImp<Redeemable>*>(this);
    self->isRedeemed_ = true;

    return value;
}

template <class Redeemable>
bool
RWTEscrowImp<Redeemable>::redeemable(void) const
{
    LockGuard lock(monitor());
    return isRedeemable();
}

template <class Redeemable>
bool
RWTEscrowImp<Redeemable>::redeemed(void) const
{
    LockGuard lock(monitor());
    return isRedeemed_;
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::removeCallback(const RWTIOUResultCallback& iouResultCallback)
{
    LockGuard lockMonitor(monitor());
    RWTLockGuard<RWMutexLock> guard(cbListMutex_);
    cbList_.removeAll(iouResultCallback);
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::setException(const RWTHRxmsg& xmsg)
{
    LockGuard lock(monitor());

    // If the escrow isn't already redeemable then set exception_
    if (!isRedeemable()) {
        exception_ = xmsg.clone();
        _setException(xmsg); // child hook
        lock.release();     // since callbacks will likely call redeem() on this.
        fireAllCallbacks();
    }
    // else ignore... the final state of the Escrow has been set.
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::setException(const RWCString& msg)
{
    LockGuard lock(monitor());

    // If the escrow isn't already redeemable then set exception_
    if (!isRedeemable()) {
        RWTHRxmsg xmsg = RWTHRxmsg(msg);
        exception_ = xmsg.clone();
        _setException(xmsg); // child hook
        lock.release();     // since callbacks will likely call redeem() on this.
        fireAllCallbacks();
    }
    // else ignore... the final state of the Escrow has been set.
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::throwAbort(void) const
{
    RW_ASSERT(isAcquired()); // mutex must already be acquired
    RW_ASSERT(isAborted());  // shouldn't reach here if not aborted
    throw RWTHROperationAborted();
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::throwStoredException(void) const
{
    RW_ASSERT(isAcquired()); // mutex must already be acquired
    RW_ASSERT(isException()); // shouldn't reach here if no exception
    (*exception_).raise();
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::_abort(void)
{
    // Default implementation does nothing.
}

template <class Redeemable>
void
RWTEscrowImp<Redeemable>::_setException(const RWTHRxmsg&)
{
    // Default implementation does nothing.
}
