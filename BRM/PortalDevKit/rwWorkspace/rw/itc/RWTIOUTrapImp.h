#ifndef __rw_itc_RWTIOUTrapImp_h__
#define __rw_itc_RWTIOUTrapImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTIOUTrapImp.h#1 $
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
#include <rw/itc/RWTPCValQueue.h>
#include <rw/itc/pkgdefs.h>
#include <rw/pointer/RWBodyBase.h>

// Do not use RWTIOUTrapImp<R> directly. Use RWTIOUTrap<R>.

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWIOUTrapImp RWTIOUTrapImp
#endif

template <class Redeemable>
class RWTIOUTrapImp : public RWBodyBase
{

protected:

    RWTPCValQueue< RWTIOUResult<Redeemable> > iouQueue_;

public:

    // Constructor
    RWTIOUTrapImp(void);

    // Destructor
    ~RWTIOUTrapImp(void);

    // Is the queue empty.
    bool
    isEmpty(void) const;

    // Trap the given IOUResult when it is redeemable.
    void
    setTrap(RWTIOUResult<Redeemable>& iou);

    // Get next RWTIOUResult<R> that is redeemable. Blocks if
    // no RWTIOUResult<R> trapped.
    RWTIOUResult<Redeemable>
    getNext(void);

    // Get next RWTIOUResult<R> that is redeemable. Returns with
    // RW_THR_TIMEOUT status if we couldn't get the result in the
    // specified milliseconds, otherwise the returned status is
    // RW_THR_COMPLETED.
    RWWaitStatus
    getNext(RWTIOUResult<Redeemable>& iouResult, unsigned long milliseconds);

    // Get next redeemable RWTIOUResult<R> if one is available.
    // Returns true and sets the iouResult parameter if one
    // could be read, otherwise returns false
    bool
    tryGetNext(RWTIOUResult<Redeemable>& iouResult);

    // Callback function which is called by the IOU when it
    // becomes redeemable. It "trips" the trap.
    void
    trip(RWTIOUResult<Redeemable> iou);

};

/*****************************************************************************/

template <class Redeemable>
inline
RWTIOUTrapImp<Redeemable>::RWTIOUTrapImp(void)
{
}

template <class Redeemable>
inline
RWTIOUTrapImp<Redeemable>::~RWTIOUTrapImp(void)
{
}

template <class Redeemable>
inline bool
RWTIOUTrapImp<Redeemable>::isEmpty(void) const
{
    return !iouQueue_.canRead();
}

template <class Redeemable>
inline RWTIOUResult<Redeemable>
RWTIOUTrapImp<Redeemable>::getNext(void)
{
    return iouQueue_.read();
}

template <class Redeemable>
inline RWWaitStatus
RWTIOUTrapImp<Redeemable>::getNext(RWTIOUResult<Redeemable>& iouResult, unsigned long milliseconds)
{
    return iouQueue_.read(iouResult, milliseconds);
}

template <class Redeemable>
inline bool
RWTIOUTrapImp<Redeemable>::tryGetNext(RWTIOUResult<Redeemable>& iouResult)
{
    return iouQueue_.tryRead(iouResult);
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/itc/RWTIOUTrapImp.cc>
#endif

#endif // __rw_itc_RWTIOUTrapImp_h__
