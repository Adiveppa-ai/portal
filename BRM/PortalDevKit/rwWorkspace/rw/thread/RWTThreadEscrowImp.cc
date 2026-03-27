/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTThreadEscrowImp.cc#1 $
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

  RWTThreadEscrowImp<Redeemable> - Multithreaded escrow implementation.

******************************************************************************/

#include <rw/thread/RWTThreadEscrowImp.h>
#include <rw/itc/RWTIOUEscrow.h>

template <class Redeemable>
RWTThreadEscrowImp<Redeemable>::RWTThreadEscrowImp(void)
    : valid_(false),
      closedCondition_(RWTEscrowImp<Redeemable>::mutex())
{
}

template <class Redeemable>
RWTThreadEscrowImp<Redeemable>::~RWTThreadEscrowImp(void)
{
}

template <class Redeemable>
void
RWTThreadEscrowImp<Redeemable>::_abort(void)
{
    // Signal threads blocked in _redeem().
    closedCondition_.signalAll();
}

template <class Redeemable>
void
RWTThreadEscrowImp<Redeemable>::_close(const Redeemable& value)
{
    RW_ASSERT(!_closed());

    // Make a copy of the value.
    value_ = value;
    valid_ = true;

    // Signal threads blocked in _redeem().
    closedCondition_.signalAll();
}

template <class Redeemable>
bool
RWTThreadEscrowImp<Redeemable>::_closed(void) const
{
    return valid_;
}

template <class Redeemable>
RWTEscrowHandle<Redeemable>
RWTThreadEscrowImp<Redeemable>::_newInstance(void) const
{
    return new RWTThreadEscrowImp<Redeemable>;
}

template <class Redeemable>
const Redeemable&
RWTThreadEscrowImp<Redeemable>::_redeem(void) const
{
    // Cast away constness.
    RWTThreadEscrowImp<Redeemable>* self =
        const_cast<RWTThreadEscrowImp<Redeemable>*>(this);

    while (!RWTEscrowImp<Redeemable>::isRedeemable()) {
        self->closedCondition_.wait();
    }

    if (RWTEscrowImp<Redeemable>::isAborted()) {
        RWTEscrowImp<Redeemable>::throwAbort();
    }

    if (RWTEscrowImp<Redeemable>::isException()) {
        RWTEscrowImp<Redeemable>::throwStoredException();
    }

    RW_ASSERT(valid_);

    return value_;
}

template <class Redeemable>
void
RWTThreadEscrowImp<Redeemable>::_setException(const RWTHRxmsg&)
{
    // Signal threads blocked in _redeem().
    closedCondition_.signalAll();
}

template <class Redeemable>
RWTEscrowHandle<Redeemable>
RWTThreadEscrowImp<Redeemable>::make(void)
{
    return new RWTThreadEscrowImp<Redeemable>;
}

template <class Redeemable>
RWTEscrowHandle<Redeemable>
RWTThreadEscrowImp<Redeemable>::make(const Redeemable& immediateValue)
{
    RWTEscrowHandle<Redeemable> escrowHandle =
        new RWTThreadEscrowImp<Redeemable>;

    // Close escrow with immediateValue
    RWTIOUEscrow<Redeemable> iouEscrow(escrowHandle);
    iouEscrow.close(immediateValue);

    return escrowHandle;
}
