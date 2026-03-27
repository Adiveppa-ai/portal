#ifndef __rw_itc_RWTIOUEscrow_h__
#define __rw_itc_RWTIOUEscrow_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTIOUEscrow.h#1 $
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
#include <rw/itc/pkgdefs.h>
#include <rw/cstring.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWIOUEscrow RWTIOUEscrow
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * A writable IOU handle.
 *
 * An RWTIOUEscrow is a writable IOU handle. An IOU, also known as a
 * \e future, is a promise for a value that is forthcoming -- a placeholder
 * for that value. Usually the writer of an IOU and the reader (or readers)
 * of an IOU are in different threads of control. In this sense IOUs are a
 * mechanism for interthread communication.
 *
 * An IOU is a <em>write once/read many</em> structure. It may only be
 * written to once, but may be read any number of times.
 *
 * The template parameter \c Redeemable is the value type of IOU result.
 * This type must provide a public copy constructor, and must allow dynamic
 * allocation using <tt>operator new</tt>.
 *
 * The RWTIOUEscrow is the handle through which a value is eventually
 * written to an underlying \e escrow object. One or more readers may redeem
 * that value once it is available by using any RWTIOUResult handle that is
 * bound to the same escrow instance.
 *
 * An RWTIOUEscrow is a reference counted handle to an RWTEscrowImp. It can
 * be copied and passed by value. When the last handle to a given
 * RWTEscrowImp is destroyed, the internal RWTEscrowImp is destroyed.
 *
 * An RWTIOUEscrow can be initialized by or assigned to an RWTIOUResult, and
 * vice versa. Both are interfaces to the same underlying RWTEscrowImp.
 * RWTIOUEscrow is a write interface, and RWTIOUResult is a read interface.
 *
 * An exception may be set on an IOU by the holder of an RWTIOUEscrow. This
 * will cause the exception to be thrown when an attempt is made to redeem
 * it.
 *
 * Similarly, an IOU may be aborted by the holder of an RWTIOUResult. This
 * will cause an exception to be thrown if an attempt is made to redeem the
 * IOU or to set its value.
 *
 * An RWTIOUEscrow is \e closeable if a value has not been set, it has not
 * been aborted, and no exception has been set.
 *
 * \example
 * \code
 * #include <rw/functor/rwBind.h>
 * #include <rw/itc/RWTIOUEscrow.h>
 * #include <rw/itc/RWTIOUResult.h>
 * #include <rw/thread/RWRunnableSelf.h>
 * #include <rw/thread/RWThreadFunction.h>
 * #include <rw/thread/RWTThreadEscrowImp.h>
 *
 * // This function is started in a thread and is passed an
 * // RWTIOUEscrow<int>.
 * // It is expected to close the escrow.
 * void sixteen(RWTIOUEscrow<int> iouInt)
 * {
 *     ::rwSleep(500); // simulate useful activity
 *     iouInt = 16;    // close escrow
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
 *         // Create a thread-safe IOU with a redeemable type of int.
 *         RWTIOUResult<int> intResult = RWTThreadEscrowImp<int>::make();
 *
 *         // create thread, pass in RWTIOUResult<int> as additional
 *         // arg. intResult will be converted into an
 *         // RWTIOUEscrow<int> in sixteen()
 *         RWThreadFunction thread =
 *             RWThreadFunction::make(rwBind(sixteen, intResult));
 *
 *         // register callback
 *         intResult.addCallback(callback);
 *
 *         thread.start();
 *
 *         // block, wait for result
 *         int val = intResult;
 *         std::cout << "redeemed " << val << std::endl;
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
class RWTIOUEscrow : public RWTEscrowHandle<Redeemable>
{
public:
    /**
     * A synonym for the value type of the IOU, or future, result.
     */
    typedef Redeemable RedeemableType;

    /**
     * Destroys the handle and decrements the reference count of the current
     * escrow instance, if any, deleting the escrow if its reference count
     * reaches zero.
     */
    ~RWTIOUEscrow(void);

    /**
     * Creates an empty, invalid handle. Use of an instance created by the
     * default constructor results in an RWTHRInvalidPointer exception being
     * thrown. You can determine if an RWTIOUEscrow handle is valid by
     * calling the isValid() member function, which is inherited from the
     * RWHandleBase base class.
     */
    RWTIOUEscrow(void);

    /**
     * Constructs a new handle instance and attaches it to the escrow
     * instance, if any, pointed to by \a escrowHandle, and increments the
     * escrow's reference count. This constructor allows an RWTIOUEscrow to
     * be constructed from an RWTIOUResult.
     */
    RWTIOUEscrow(const RWTEscrowHandle<Redeemable>& escrowHandle);

    /**
     * Copy constructor. Constructs a new handle instance and attaches it to
     * the escrow instance, if any, pointed to by \a second, and increments
     * the escrow's reference count.
     */
    RWTIOUEscrow(const RWTIOUEscrow<Redeemable>& second);

    /**
     * Detaches this handle from its current escrow instance, if any,
     * decrementing the escrow's reference count and deleting the escrow if
     * the count reaches zero. It then attaches to the escrow instance, if
     * any, pointed to by \a second, and increments the new escrow's
     * reference count.
     */
    RWTIOUEscrow<Redeemable>&
    operator=(const RWTIOUEscrow<Redeemable>& second);

    /**
     * Returns \c true if the IOU has been aborted, otherwise returns
     * \c false. Possible exceptions include \c RWTHRInvalidPointer.
     */
    bool
    aborted(void) const;

    /**
     * Stores a value into the underlying escrow. If the IOU has already
     * been closed, the function throws an RWTHREscrowAlreadyClosed
     * exception. If the escrow operation has been aborted, the function
     * throws an RWTHROperationAborted exception. If an exception has been
     * set, that exception is thrown.
     */
    void
    close(const Redeemable& value);

    // Can a value be written into the Escrow? True if no value has
    // been written and the escrow isn't in error or aborted.
    /**
     * Returns \c true if the IOU has not been closed, and is not in an
     * error condition or aborted; otherwise returns \c false. Possible
     * exceptions include RWTHRInvalidPointer.
     */
    bool
    closeable(void) const;

    // Has a value been successfully written into the IOU?
    /**
     * Returns \c true if the IOU has been closed, otherwise returns
     * \c false. Possible exceptions include RWTHRInvalidPointer.
     */
    bool
    closed(void);

    // Was the IOU closed with an error? If true then, if the IOU is
    // redeemed, an exception will be thrown.
    /**
     * Returns \c true if the IOU has been closed with an error, otherwise
     * returns \c false. Possible exceptions include RWTHRInvalidPointer.
     */
    bool
    inError(void);

    /**
     * Creates a new instance of the same class as the current concrete
     * RWTEscrowImp body. Returns a new RWTIOUEscrow handle that points to
     * the new body.
     */
    RWTIOUEscrow<Redeemable>
    newInstance(void) const;

    /**
     * Equivalent to close().
     */
    void
    operator()(const Redeemable& value);

    /**
     * Equivalent to close().
     */
    void
    operator=(const Redeemable& value);

    /**
     * Returns \c true if the IOU has been successfully redeemed at least
     * once, otherwise returns \c false. Possible exceptions include
     * RWTHRInvalidPointer.
     */
    bool
    redeemed(void) const;

    // Set an error on the Escrow. Causes an exception to be stored inside
    // the Escrow. Notifies callers waiting for the Escrow to be closed.
    // so that they can redeem IOU and catch the error. If the Escrow has
    // already been closed normally, closed with an error, or aborted then
    // the error is ignored.
    /**
     * Used to indicate that IOU result could not be produced because an
     * exception occurred. Causes a copy of the specified exception to be
     * stored inside the IOU escrow object. The stored exception is rethrown
     * in response to any attempt to redeem the IOU. If the IOU has already
     * either been closed normally, closed with an error, or aborted, the
     * error is ignored.
     */
    void
    setException(const RWTHRxmsg& xmsg);

    // Set the error with a string. The string is packaged into an RWTHRxmsg
    // and stored within the EscrowImp until it is redeemed, at which point
    // it is thrown. If the Escrow has already been closed normally, closed
    // with an error, or aborted then the error is ignored.
    /**
     * Used to indicate that IOU result could not be produced because an
     * exception occurred. The string message is packaged in an RWTHRxmsg
     * and stored inside the IOU escrow object. The stored exception is
     * thrown in response to any attempt to redeem the IOU. If the IOU has
     * already either been closed normally, closed with an error, or
     * aborted, the error is ignored.
     */
    void
    setException(const RWCString& msg);

protected:

    // Return reference to RWTEscrowImp<Redeemable> body.
    RWTEscrowImp<Redeemable>&
    body(void) const;

};

/*****************************************************************************/

template <class Redeemable>
inline
RWTIOUEscrow<Redeemable>::RWTIOUEscrow(void)
{
}

template <class Redeemable>
inline
RWTIOUEscrow<Redeemable>::RWTIOUEscrow(const RWTEscrowHandle<Redeemable>& escrowHandle)
    : RWTEscrowHandle<Redeemable>(escrowHandle)
{
}

template <class Redeemable>
inline
RWTIOUEscrow<Redeemable>::RWTIOUEscrow(const RWTIOUEscrow<Redeemable>& second)
    : RWTEscrowHandle<Redeemable>(second)
{
}

template <class Redeemable>
inline
RWTIOUEscrow<Redeemable>::~RWTIOUEscrow(void)
{
}

template <class Redeemable>
inline RWTIOUEscrow<Redeemable>&
RWTIOUEscrow<Redeemable>::operator=(const RWTIOUEscrow<Redeemable>& second)
{
    if (&second != this) {
        RWTEscrowHandle<Redeemable>::operator=(second);
    }
    return *this;
}

template <class Redeemable>
inline bool
RWTIOUEscrow<Redeemable>::aborted(void) const
{
    return body().aborted();
}

template <class Redeemable>
inline RWTEscrowImp<Redeemable>&
RWTIOUEscrow<Redeemable>::body(void) const
{
    // The following cast is safe since an RWTEscrowHandle<Redeemable>
    // is ultimately initialized by an RWTEscrowImp<Redeemable>.
    return (RWTEscrowImp<Redeemable>&)RWHandleBase::body();
}

template <class Redeemable>
inline void
RWTIOUEscrow<Redeemable>::close(const Redeemable& value)
{
    body().close(value);
}

template <class Redeemable>
inline bool
RWTIOUEscrow<Redeemable>::closeable(void) const
{
    return body().closeable();
}

template <class Redeemable>
inline bool
RWTIOUEscrow<Redeemable>::closed(void)
{
    return body().closed();
}

template <class Redeemable>
inline bool
RWTIOUEscrow<Redeemable>::inError(void)
{
    return body().inError();
}

template <class Redeemable>
inline RWTIOUEscrow<Redeemable>
RWTIOUEscrow<Redeemable>::newInstance(void) const
{
    return body().newInstance();
}

template <class Redeemable>
inline void
RWTIOUEscrow<Redeemable>::operator()(const Redeemable& value)
{
    body().close(value);
}

template <class Redeemable>
inline void
RWTIOUEscrow<Redeemable>::operator=(const Redeemable& value)
{
    body().close(value);

    // operator= normally returns a reference to self,
    // so that operator chaining can occur (a = b = c;),
    // however in this case only IOU "b" would get closed
    // with the value of "c".  IOU "a" would be associated
    // with the body of "b", but the body of "a" would be
    // lost and never closed.  To prevent this situation,
    // we prevent operator chaining.
}

template <class Redeemable>
inline bool
RWTIOUEscrow<Redeemable>::redeemed(void) const
{
    return body().redeemed();
}

template <class Redeemable>
inline void
RWTIOUEscrow<Redeemable>::setException(const RWCString& msg)
{
    body().setException(msg);
}

template <class Redeemable>
inline void
RWTIOUEscrow<Redeemable>::setException(const RWTHRxmsg& xmsg)
{
    body().setException(xmsg);
}

#endif // __rw_itc_RWTIOUEscrow_h__
