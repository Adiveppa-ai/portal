/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTThreadIOUFunction.cc#1 $
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

  RWTThreadIOUFunction - Handle for RWTThreadIOUFunctionImp class.

******************************************************************************/

#include <rw/thread/RWTThreadEscrowImp.h>
#include <rw/thread/RWTThreadIOUFunction.h>
#include <rw/thread/RWTThreadIOUFunctionImp.h>

template <class Return>
RWTFunctor<Return()>
RWTThreadIOUFunction<Return>::getFunctor(void) const
{
    return ((RWTThreadIOUFunctionImp<Return>&)body()).getFunctor();
}

template <class Return>
// static
RWTThreadIOUFunction<Return>
RWTThreadIOUFunction<Return>::make(void)
{
    return new RWTThreadIOUFunctionImp<Return>(RWTThreadEscrowImp<Return>::make());
}

template <class Return>
// static
RWTThreadIOUFunction<Return>
RWTThreadIOUFunction<Return>::make(const RWTFunctor<Return()>& functor)
{
    return new RWTThreadIOUFunctionImp<Return>(RWTThreadEscrowImp<Return>::make(), functor);
}

template <class Return>
// static
RWTThreadIOUFunction<Return>
RWTThreadIOUFunction<Return>::make(const RWTIOUEscrow<Return>& escrow,
                                   const RWTFunctor<Return()>& functor)
{
    return new RWTThreadIOUFunctionImp<Return>(escrow, functor);
}

template <class Return>
// static
RWTThreadIOUFunction<Return>
RWTThreadIOUFunction<Return>::make(const RWTFunctor<Return()>& functor,
                                   const RWThreadAttribute& attr)
{
    return new RWTThreadIOUFunctionImp<Return>(RWTThreadEscrowImp<Return>::make(), functor, attr);
}

template <class Return>
// static
RWTThreadIOUFunction<Return>
RWTThreadIOUFunction<Return>::make(const RWTIOUEscrow<Return>& escrow,
                                   const RWTFunctor<Return()>& functor,
                                   const RWThreadAttribute& attr)
{
    return new RWTThreadIOUFunctionImp<Return>(escrow, functor, attr);
}

template <class Return>
RWTIOUResult<Return>
RWTThreadIOUFunction<Return>::operator()(void) const
{
    return ((RWTThreadIOUFunctionImp<Return>&)body()).result();
}

template <class Return>
RWTIOUResult<Return>
RWTThreadIOUFunction<Return>::result(void) const
{
    return ((RWTThreadIOUFunctionImp<Return>&)body()).result();
}

template <class Return>
void
RWTThreadIOUFunction<Return>::setFunctor(const RWTFunctor<Return()>& functor)
{
    ((RWTThreadIOUFunctionImp<Return>&)body()).setFunctor(functor);
}

template <class Return>
void
RWTThreadIOUFunction<Return>::setIOUEscrow(const RWTIOUEscrow<Return>& escrow)
{
    ((RWTThreadIOUFunctionImp<Return>&)body()).setIOUEscrow(escrow);
}
