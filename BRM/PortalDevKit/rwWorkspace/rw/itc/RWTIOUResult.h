#ifndef __rw_itc_RWTIOUResult_h__
#define __rw_itc_RWTIOUResult_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTIOUResult.h#1 $
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

#include <rw/itc/RWTEscrowHandle.h>
#include <rw/itc/RWTEscrowImp.h>
#include <rw/pointer/RWHandleBase.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWIOUResult RWTIOUResult
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * A readable IOU handle.
 *
 * An RWTIOUResult is a readable IOU handle. An IOU, sometimes known as a
 * \e future, is a promise for a value that is forthcoming, and is a
 * placeholder for that value. Usually the writer of an IOU and the reader
 * (or readers) of an IOU are in different threads of control. In this
 * sense, IOUs are a mechanism for interthread communication.
 *
 * The template parameter \c Redeemable is the value type of the IOU result.
 * This type must provide a public copy-constructor and must allow dynamic
 * allocation using <tt>operator new</tt>.
 *
 * An IOU is a <em>write once/read many</em> structure. It may only be
 * written to once, but may be read any number of times.
 *
 * The RWTIOUResult handle is a reference counted handle to an RWTEscrowImp.
 * It can be copied and passed by value. When the last handle to a given
 * RWTEscrowImp is destroyed, the internal RWTEscrowImp is destroyed.
 *
 * An RWTIOUResult can be initialized by or assigned to an RWTIOUEscrow, and
 * vice versa. Both are interfaces to the same underlying RWTEscrowImp.
 * RWTIOUResult is a read interface, and RWTIOUEscrow is a write interface.
 *
 * The holder of the RWTIOUResult decides how and when to \e redeem the
 * value held by the IOU. IOU redemption is the process of getting the
 * result from the IOU when it is available. There are 3 ways to redeem an
 * RWTIOUResult :
 *
 * - \b Blocking. A call to RWTIOUResult::redeem() blocks the caller until
 * the result is available.
 * - \b Polling. Calls to RWTIOUResult::redeemable() tell whether the IOU is
 * redeemable. An IOU is redeemable if a value has been set, an exception
 * has been set, or the IOU has been aborted.
 * - \b Callback. A callback function may be registered with the IOU using
 * RWTIOUResult::addCallback(). The callback is called and passed an
 * RWTIOUResult when the IOU is redeemable.
 *
 * An IOU may be aborted by the holder of an RWTIOUResult. This will cause
 * an exception to be thrown if an attempt is made to redeem the IOU or to
 * set its value.
 *
 * Similarly an exception may be set on an IOU by the holder of an
 * RWTIOUEscrow. This causes the exception to be thrown when an attempt is
 * made to redeem the IOU.
 *
 * An RWTIOUResult is \e redeemable if a value has been set, if it has been
 * aborted, or if an exception has been set.
 *
 * \example
 * \code
 * #include <rw/itc/RWTIOUResult.h>
 * #include <rw/thread/RWRunnableSelf.h>
 * #include <rw/thread/RWTThreadIOUFunction.h>
 *
 * int sixteen(void)
 * {
 *     ::rwSleep(500); // simulate useful activity
 *     return 16;
 * }
 *
 * void callback(RWTIOUResult<int> intIOUResult)
 * {
 *     try {
 *         int val = intIOUResult;  // redeem value
 *         std::cout << "callback received value of " << val << std::endl;
 *     }
 *     catch (...) {
 *         std::cout << "something bad happened" << std::endl;
 *     }
 * }
 *
 * int main()
 * {
 *     try {
 *         RWTThreadIOUFunction<int> thread =
 *             RWTThreadIOUFunction<int>::make(sixteen);
 *
 *         // get RWTIOUResult
 *         RWTIOUResult<int> iouRes = thread.result();
 *
 *         // register callback
 *         iouRes.addCallback(callback);
 *
 *         thread.start();
 *
 *         // poll until redeemable
 *         while (!iouRes.redeemable()) {
 *             ::rwSleep(50);
 *         }
 *
 *         // redeem RWTIOUResult
 *         std::cout << "redeemed " << iouRes.redeem() << std::endl;
 *     }
 *     catch (...) {
 *         std::cout << "something bad happened" << std::endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
template <class Redeemable>
class RWTIOUResult : public RWTEscrowHandle<Redeemable>
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

    /**
     * Destroys the handle and decrements the reference count of the current
     * escrow instance, if any, deleting the escrow if its reference count
     * reaches zero.
     */
    ~RWTIOUResult(void);

    /**
     * Creates an empty, invalid handle. Use of an instance created by the
     * default constructor results in an RWTHRInvalidPointer exception being
     * thrown. You can determine if an RWTIOUResult handle is valid by
     * calling the isValid() member function, which is inherited from the
     * RWHandleBase base class.
     */
    RWTIOUResult(void);

    /**
     * Constructs a new handle instance and attaches it to the escrow
     * instance, if any, pointed to by \c escrowHandle, and increments the
     * escrow's reference count. This constructor allows an RWTIOUEscrow to
     * be constructed from an RWTIOUResult.
     */
    RWTIOUResult(const RWTEscrowHandle<Redeemable>& escrowHandle);

    /**
     * Copy constructor. Constructs a new handle instance and attaches it to
     * the escrow instance, if any, pointed to by \a second, and increments
     * the escrow's reference count.
     */
    RWTIOUResult(const RWTIOUResult<Redeemable>& second);

    /**
     * Detaches this handle from its current escrow instance, if any,
     * decrementing the escrow's reference count and deleting the escrow if
     * the count reaches zero. It then attaches to the escrow instance, if
     * any, pointed by \a second, and increments the new escrow's reference
     * count.
     */
    RWTIOUResult<Redeemable>&
    operator=(const RWTIOUResult<Redeemable>& second);

    /**
     * Tells the writer of an IOU that a result is no longer needed.
     * Notifies anyone waiting to redeem the IOU so they can detect, abort,
     * and catch an exception. Subsequent calls to redeem the IOU
     * immediately receive an exception indicating that the operation
     * associated with the IOU has already been aborted. This method is
     * ignored if the operation has already been aborted. Possible
     * exceptions include RWTHRInvalidPointer.
     */
    void
    abort(void) const;

    /**
     * Returns \c true if the operation has been aborted, otherwise returns
     * \c false. Possible exceptions include RWTHRInvalidPointer.
     */
    bool
    aborted(void) const;

    /**
     * Adds a callback. The callback is called when the IOU is closed.
     */
    void
    addCallback(const RWTIOUResultCallback& callback);

    /**
     * Returns \c true if the IOU was closed with an error, otherwise
     * returns \c false. Possible exceptions include RWTHRInvalidPointer.
     */
    bool
    inError(void) const;

    /**
     * Equivalent to redeem().
     */
    Redeemable
    operator()(void) const;

    /**
     * Equivalent to redeem().
     */
    operator
    Redeemable(void) const;

    /**
     * Gets the result, blocking if the result is not yet available.
     *
     * Throws RWTHROperationAborted if the IOU (or the associated operation)
     * has been aborted. If an exception has been thrown and stored in the
     * IOU, that exception is re-thrown.
     */
    Redeemable
    redeem(void) const;

    /**
     * Returns \c true if the IOU has been closed, closed with an error, or
     * aborted, otherwise returns \c false. This function is used to poll an
     * IOU for the availability of a result. Possible exceptions include
     * RWTHRInvalidPointer.
     */
    bool
    redeemable(void) const;

    /**
     * Returns \c true if the IOU has been redeemed at least once, otherwise
     * returns \c false. Possible exceptions include RWTHRInvalidPointer.
     */
    bool
    redeemed(void) const;

    /**
     * Removes the callback represented by \a callback. If \a callback does
     * not exist, does nothing.
     */
    void
    removeCallback(const RWTIOUResultCallback& callback);

protected:

    // Return reference to RWTEscrowImp<Redeemable> body.
    RWTEscrowImp<Redeemable>&
    body(void) const;

};

/****************************************************************************/

template <class Redeemable>
inline
RWTIOUResult<Redeemable>::RWTIOUResult(void)
{
}

template <class Redeemable>
inline
RWTIOUResult<Redeemable>::RWTIOUResult(const RWTEscrowHandle<Redeemable>& escrowHandle)
    : RWTEscrowHandle<Redeemable>(escrowHandle)
{
}

template <class Redeemable>
inline
RWTIOUResult<Redeemable>::RWTIOUResult(const RWTIOUResult<Redeemable>& second)
    : RWTEscrowHandle<Redeemable>(second)
{
}

template <class Redeemable>
inline
RWTIOUResult<Redeemable>::~RWTIOUResult(void)
{
}

template <class Redeemable>
inline RWTIOUResult<Redeemable>&
RWTIOUResult<Redeemable>::operator=(const RWTIOUResult<Redeemable>& second)
{
    if (&second != this) {
        RWTEscrowHandle<Redeemable>::operator=(second);
    }
    return *this;
}

template <class Redeemable>
inline void
RWTIOUResult<Redeemable>::abort(void) const
{
    body().abort();
}

template <class Redeemable>
inline bool
RWTIOUResult<Redeemable>::aborted(void) const
{
    return body().aborted();
}

template <class Redeemable>
inline void
RWTIOUResult<Redeemable>::addCallback(const RWTIOUResultCallback& callback)
{
    body().addCallback(callback);
}

template <class Redeemable>
inline RWTEscrowImp<Redeemable>&
RWTIOUResult<Redeemable>::body(void) const
{
    // The following cast is safe since an RWTEscrowHandle<Redeemable>
    // is ultimately initialized by an RWTEscrowImp<Redeemable>.
    return (RWTEscrowImp<Redeemable>&)RWHandleBase::body();
}

template <class Redeemable>
inline bool
RWTIOUResult<Redeemable>::inError(void) const
{
    return body().inError();
}

template <class Redeemable>
inline Redeemable
RWTIOUResult<Redeemable>::operator()(void) const
{
    return body().redeem();
}

template <class Redeemable>
inline
RWTIOUResult<Redeemable>::operator Redeemable() const
{
    return body().redeem();
}

template <class Redeemable>
inline Redeemable
RWTIOUResult<Redeemable>::redeem(void) const
{
    return body().redeem();
}

template <class Redeemable>
inline bool
RWTIOUResult<Redeemable>::redeemable(void) const
{
    return body().redeemable();
}

template <class Redeemable>
inline bool
RWTIOUResult<Redeemable>::redeemed(void) const
{
    return body().redeemed();
}

template <class Redeemable>
inline void
RWTIOUResult<Redeemable>::removeCallback(const RWTIOUResultCallback& callback)
{
    body().removeCallback(callback);
}

#endif // __rw_itc_RWTIOUResult_h__
