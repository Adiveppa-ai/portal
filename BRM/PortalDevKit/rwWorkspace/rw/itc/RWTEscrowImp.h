#ifndef __rw_itc_RWTEscrowImp_h__
#define __rw_itc_RWTEscrowImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTEscrowImp.h#1 $
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

#include <rw/itc/RWEscrowImpBase.h>
#include <rw/itc/RWTEscrowHandle.h>
#include <rw/itc/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/functor/fwd.h>
#include <rw/pointer/RWTOnlyPointer.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4284)
#endif

class RWCString;

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWEscrowImp RWTEscrowImp
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * Base class for all concrete IOU escrow implementations. Not intended for
 * direct use.
 *
 * Do not use this class directly. This class is the base class for all
 * concrete IOU escrow implementations, providing basic functionality and
 * allowing for extension via virtual functions.
 *
 * Use this class only through RWTIOUResult and RWTIOUEscrow handles. The
 * interface of RWTEscrowImp is a union of the interfaces provided by
 * RWTIOUResult and RWTIOUEscrow.
 */
template <class Redeemable>
class RWTEscrowImp : public RWEscrowImpBase
{

public:

    /**
     * A synonym for the value type of the IOU, or future, result.
     */
    typedef Redeemable RedeemableType;

    /**
     * A typedef for a callback function object.
     */
    typedef RWTFunctor<void(RWTEscrowHandle<Redeemable>)> RWTIOUResultCallback;

private:

    bool isRedeemed_;
    bool isAborted_;
    RWTOnlyPointer<RWTHRxmsg> exception_;
    RWMutexLock cbListMutex_;
    RWTValSlist< RWTIOUResultCallback > cbList_;

public:

    /**
     * Virtual destructor.
     */
    virtual
    ~RWTEscrowImp(void);

    /**
     * Aborts the operation associated with the escrow, as follows:
     * - Tells the service provider that the result is no longer needed.
     * - Notifies all entities waiting on the IOU, so they can detect the
     * abort and catch an exception.
     * - Sends an exception to all subsequent calls to redeem the IOU,
     * indicating that the operation has been aborted.
     *
     * This method is ignored if the operation has already been aborted.
     */
    void
    abort(void);

    /**
     * Returns \c true if the operation has been aborted, otherwise
     * \c false.
     */
    bool
    aborted(void) const;

    /**
     * Adds a callback. The callback is fired when the escrow is closed.
     */
    void
    addCallback(const RWTIOUResultCallback& iouResultCallback);

    /**
     * Stores the \a value, then closes the escrow. If an exception has been
     * set, that exception is thrown.
     *
     * \exception RWTHREscrowAlreadyClosed
     * Thrown if the escrow has already been closed.
     *
     * \exception RWTHROperationAborted
     * Thrown if the escrow operation has been aborted.
     */
    void
    close(const Redeemable& value);

    /**
     * Returns \c true if the escrow can be closed, i.e. if no value has
     * been stored into the escrow, and the escrow is not in the error or
     * aborted states. Otherwise, returns \c false.
     */
    bool
    closeable(void) const;

    /**
     * Returns true if a value has been stored, and the escrow is closed.
     * Otherwise, returns \c false.
     *
     * \note
     * The methods redeemable() or closeable() are better for polling as
     * they report errors and abortion, in addition to valid closures.
     */
    bool
    closed(void) const;

    /**
     * Returns \c true if the escrow closed with an error, otherwise
     * \c false. If the escrow did close with an error, any subsequent call
     * to redeem receives an exception.
     */
    bool
    inError(void) const;

    /**
     * Creates a new instance of this RWTEscrowImp type.
     */
    RWTEscrowHandle<Redeemable>
    newInstance(void) const;

    /**
     * Gets the result, blocking if the result is not yet available.
     *
     * \exception RWTHROperationAborted
     * Thrown if the escrow (or the associated operation) has been aborted.
     * If an exception is thrown and stored in the escrow, then that
     * exception is re-thrown by this routine.
     */
    const Redeemable&
    redeem(void) const;

    /**
     * Returns \c true if a proper value has been set, if an error has been
     * set, or if the operation has been aborted; otherwise, returns
     * \c false.
     *
     * This function is used primarily by the reader side to poll the escrow
     * for the availability of a result.
     */
    bool
    redeemable(void) const;

    /**
     * Returns \c true if the result has been successfully redeemed;
     * otherwise returns \c false.
     *
     * \note
     * A redemption that results in an exception being thrown is not counted
     * as a success.
     */
    bool
    redeemed(void) const;

    /**
     * Removes the callback if it exists, otherwise does nothing.
     */
    void
    removeCallback(const RWTIOUResultCallback& iouResultCallback);

    /**
     * Sets an error on the escrow so that an exception is stored inside the
     * escrow. Notifies any callers waiting for the escrow to close so that
     * the callers can redeem the IOU and catch the error. If the escrow has
     * already closed, either normally or abnormally (with an error or by
     * being aborted), then the error is ignored.
     */
    void
    setException(const RWTHRxmsg& xmsg);

    // Set the error with a string. The string is packaged into an RWTHRxmsg
    // and stored within the EscrowImp until it is redeemed, at which point
    // it is thrown. If the escrow has already been closed normally, closed
    // with an error, or aborted then the error is ignored.
    void
    setException(const RWCString& msg);

protected:

    /**
     * RWTEscrowImp cannot be explicitly constructed. Rather, construct it
     * implicitly using \b make() functions in concrete derived classes. The
     * derived-class \b make() functions return an RWTEscrowHandle for
     * initializing an RWTIOUEscrow or RWTIOUResult.
     *
     * This type of construction means that a raw RWTEscrowImp pointer will
     * not be visible to your application.
     */
    RWTEscrowImp(void);

    // The following helper functions assume that a guard has already
    // been acquired. They will not acquire the mutex.

    // Has the escrow been aborted?
    bool
    isAborted(void) const;

    // Has an exception been set on the escrow?
    bool
    isException(void) const;

    // Has the escrow been closed, aborted, or put in error
    bool
    isRedeemable(void) const;

    // Throw abort exception.
    void
    throwAbort(void) const;

    // Throw stored exception, if any.
    void
    throwStoredException(void) const;

    // Virtual functions... These are meant to be overloaded by concrete escrow
    // implementations. Pure virtuals must be implemented (of course); other
    // virtuals may optionally be specialized. Note that all virtual functions
    // are called while the mutex "mutex_" is acquired. In order to
    // in a call to a member function) on this instance, mutex_ must
    // be released and then reacquired before returning; the best way
    // to do this is to use an UnlockGuard which is defined in the Monitor<>
    // base class.

    // Hook to catch aborts.
    virtual void
    _abort(void);

    // Implementation of escrow closure. Stores value for later redemption.
    // Must be implemented by derived class.
    virtual void
    _close(const Redeemable& value) = 0;

    // Returns whether the escrow has been successfully closed or not.
    // Must be implemented by derived class.
    virtual bool
    _closed(void) const = 0;

    // Implementation of _newInstance(). Must be implemented by
    // derived types.
    virtual RWTEscrowHandle<Redeemable>
    _newInstance(void) const = 0;

    // Implementation of redeem. Returns stored value. Blocks until
    // the value is available or an exception is thrown. Must be
    // implemented by derived class.
    virtual const Redeemable&
    _redeem(void) const = 0;


    // Hook to intercept errors.
    virtual void
    _setException(const RWTHRxmsg& msg);

private:

    void
    fireAllCallbacks(void);

};

/****************************************************************************/

template <class Redeemable>
inline bool
RWTEscrowImp<Redeemable>::isAborted(void) const
{
    RW_ASSERT(isAcquired()); // mutex must already be acquired
    return isAborted_;
}

template <class Redeemable>
inline bool
RWTEscrowImp<Redeemable>::isException(void) const
{
    RW_ASSERT(isAcquired()); // mutex must already be acquired
    return exception_.isValid();
}

template <class Redeemable>
inline bool
RWTEscrowImp<Redeemable>::isRedeemable(void) const
{
    RW_ASSERT(isAcquired()); // mutex must already be acquired
    return (_closed() || exception_.isValid() || isAborted_);
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTEscrowImp.cc>
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_itc_RWTEscrowImp_h__
