#ifndef __rw_itc_RWTIOUTrap_h__
#define __rw_itc_RWTIOUTrap_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTIOUTrap.h#1 $
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

#include <rw/itc/RWTIOUResult.h>
#include <rw/itc/RWTIOUTrapImp.h>
#include <rw/itc/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWIOUTrap RWTIOUTrap
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * Waits for the next IOU in a group of IOUs to become redeemable.
 *
 * RWTIOUTrap allows you to wait for the next IOU in a group of IOUs to
 * become redeemable. For example, it can be used to wait on IOU results
 * from a number of RWTThreadIOUFunction instances. You may either block
 * waiting for the next IOU to become available, wait with a time-out, or
 * poll for the next IOU.
 *
 * RWTIOUTrap assists in the management of a number of RWTIOUResult
 * instances. Without an IOU trap, you would have to poll each of a number
 * of IOUs in turn, testing to see when the next one becomes redeemable.
 * This kind of polling loop, however, is inefficient in a multithreaded
 * environment. With an IOU trap, you merely wait for the trap to provide
 * you with the next redeemable IOU.
 *
 * Each IOU you wish to trap must first be registered using the setTrap()
 * member function. Once an IOU is registered, it automatically notifies the
 * trap when it becomes redeemable. RWTIOUTrap uses a producer-consumer
 * queue to store each IOU as it notifies the trap that it is redeemable. An
 * RWTIOUResult is inserted into the queue by the thread that closed it, and
 * taken off the queue when the trap's getNext() member is called.
 *
 * The IOU trap is implemented as a handle-body object. The RWTIOUTrap is
 * the handle for an IOU trap object. These handles can be passed and shared
 * by value. The actual trap object is deleted when the last handle that
 * references it is destroyed.
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/itc/RWTIOUTrap.h>
 *
 * int main(void)
 * {
 *     RWTIOUTrap<long> iouTrap;
 *
 *     RWTIOUResult<long> result1 = ...;
 *     RWTIOUResult<long> result2 = ...;
 *     RWTIOUResult<long> result3 = ...;
 *
 *     iouTrap.setTrap(result1);
 *     iouTrap.setTrap(result2);
 *     iouTrap.setTrap(result3);
 *
 *     for (int i; i < 3; i++) {
 *         long l = iouTrap.getNext();
 *         std::cout << "next result = " << l << std::endl;
 *     }
 * }
 * \endcode
 * \endexample
 */
template <class Redeemable>
class RWTIOUTrap : public RWHandleBase
{
public:
    /**
     * Constructs an RWTIOUTrap instance bound to a new body instance.
     */
    RWTIOUTrap(void);

    /**
     * Constructs a static RWTIOUTrap handle instance. This constructor does
     * not construct a body instance, and does not change the handle
     * instance.
     */
    RWTIOUTrap(RWStaticCtor);

    /**
     * Copy constructor. Constructs a new handle instance and attaches it to
     * the trap instance, if any, pointed to by \a second, and increments
     * the trap's reference count.
     */
    RWTIOUTrap(const RWTIOUTrap<Redeemable>& second);

    // Binds a new handle instance to a body instance
    RWTIOUTrap(RWTIOUTrapImp<Redeemable>* bodyPtr);

    /**
     * Destroys the handle and decrements the reference count of the current
     * trap instance, if any, deleting the trap if its reference count
     * equals zero.
     */
    ~RWTIOUTrap(void);

    /**
     * Detaches this handle from its current trap instance, if any,
     * decrementing the trap's reference count and deleting the trap if the
     * count equals zero. It then attaches to the trap instance, if any,
     * pointed by \a second, and increments the new trap's reference count.
     */
    RWTIOUTrap<Redeemable>&
    operator=(const RWTIOUTrap<Redeemable>& second);

    /**
     * Returns \c true if the queue is empty, otherwise returns \c false.
     */
    bool
    isEmpty(void) const;

    /**
     * Traps the given IOU when it becomes redeemable.
     */
    void
    setTrap(RWTIOUResult<Redeemable> iou) const;

    /**
     * Gets the next redeemable RWTIOUResult, and if none are ready, waits
     * until one becomes available.
     */
    RWTIOUResult<Redeemable>
    getNext(void);

    /**
     * Gets the next redeemable RWTIOUResult, and if none are ready, waits
     * until one becomes available. Returns with #RW_THR_COMPLETED status if
     * an IOU becomes redeemable within the specified number of
     * \a milliseconds; otherwise the returned status is #RW_THR_TIMEOUT.
     */
    RWWaitStatus
    getNext(RWTIOUResult<Redeemable>& iouResult, unsigned long milliseconds);

    /**
     * Gets next redeemable RWTIOUResult if one is available. If an IOU has
     * already been trapped, returns \c true and assigns the redeemable IOU
     * to the \a iouResult argument, otherwise returns \c false.
     */
    bool
    tryGetNext(RWTIOUResult<Redeemable>& iouResult);

    // Callback function that is called by the IOU when it
    // becomes redeemable. It "trips" the trap.
    static void
    trip(RWTIOUResult<Redeemable> iou, RWTIOUTrap<Redeemable> iouTrap);

protected:

    // Returns a reference to the body
    RWTIOUTrapImp<Redeemable>&
    body(void) const;

};

/*****************************************************************************/

template <class Redeemable>
inline
RWTIOUTrap<Redeemable>::RWTIOUTrap(void)
    : RWHandleBase(new RWTIOUTrapImp<Redeemable>)
{
}

template <class Redeemable>
inline
RWTIOUTrap<Redeemable>::RWTIOUTrap(RWStaticCtor)
    : RWHandleBase(RW_STATIC_CTOR)
{
}

template <class Redeemable>
inline
RWTIOUTrap<Redeemable>::RWTIOUTrap(const RWTIOUTrap<Redeemable>& second)
    : RWHandleBase(second)
{
}

template <class Redeemable>
inline
RWTIOUTrap<Redeemable>::RWTIOUTrap(RWTIOUTrapImp<Redeemable>* bodyPtr)
    : RWHandleBase(bodyPtr)
{
}

template <class Redeemable>
inline
RWTIOUTrap<Redeemable>::~RWTIOUTrap(void)
{
}

template <class Redeemable>
inline RWTIOUTrap<Redeemable>&
RWTIOUTrap<Redeemable>::operator=(const RWTIOUTrap<Redeemable>& second)
{
    if (&second != this) {
        RWHandleBase::operator=(second);
    }
    return *this;
}

template <class Redeemable>
inline RWTIOUTrapImp<Redeemable>&
RWTIOUTrap<Redeemable>::body(void) const
{
    return (RWTIOUTrapImp<Redeemable>&)RWHandleBase::body();
}

template <class Redeemable>
inline bool
RWTIOUTrap<Redeemable>::isEmpty(void) const
{
    return body().isEmpty();
}

template <class Redeemable>
inline RWTIOUResult<Redeemable>
RWTIOUTrap<Redeemable>::getNext(void)
{
    return body().getNext();
}

template <class Redeemable>
inline RWWaitStatus
RWTIOUTrap<Redeemable>::getNext(RWTIOUResult<Redeemable>& iouResult, unsigned long milliseconds)
{
    return body().getNext(iouResult, milliseconds);
}

template <class Redeemable>
inline bool
RWTIOUTrap<Redeemable>::tryGetNext(RWTIOUResult<Redeemable>& iouResult)
{
    return body().tryGetNext(iouResult);
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTIOUTrap.cc>
#endif

#endif // __rw_itc_RWTIOUTrap_h__
