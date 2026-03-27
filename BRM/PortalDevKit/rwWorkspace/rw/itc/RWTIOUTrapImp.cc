/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTIOUTrapImp.cc#1 $
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

  RWTIOUTrapImp<Redeemable> - Body class for IOU trap.

******************************************************************************/

#include <rw/itc/RWTIOUTrap.h>
#include <rw/itc/RWTIOUTrapImp.h>
#include <rw/functor/rwBind.h>

template <class Redeemable>
void
RWTIOUTrapImp<Redeemable>::trip(RWTIOUResult<Redeemable> iou)
{
    iouQueue_.write(iou);
}

template <class Redeemable>
void RWTIOUTrapImp<Redeemable>::setTrap(RWTIOUResult<Redeemable>& iou)
{
    RWTFunctor<void(RWTEscrowHandle<Redeemable>)> trapCallback =
        rwBind(&RWTIOUTrap<Redeemable>::trip, rw1, RWTIOUTrap<Redeemable>(this));
    iou.addCallback(trapCallback);
}
