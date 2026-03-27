/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTFunctorList1Imp.cc#1 $
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

#include <rw/functor/list/RWTFunctorList1Imp.h>

template <class S1>
void
RWTFunctorList1Imp<S1>::run(S1 s1) const
{
    RWTFunctorList1Imp<S1>* self = const_cast<RWTFunctorList1Imp<S1>*>(this);

#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1200 && __INTEL_COMPILER <= 1300)
    // work around for intel compiler bug #683230
    do
#endif
    {
        RWTLockGuard<MutexType> guard(self->RWTFunctor1Imp<S1>::mutex());
        if (self->isRunning) {
            throw RWTHRInternalError("Only one thread can call RWTFunctorList1::operator(S1) at a time");
        }
        else {
            self->isRunning = true;
        }
    }
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1200 && __INTEL_COMPILER <= 1300)
    // work around for intel compiler bug #683230
    while (false);
#endif

    try {
        self->list_(s1);
        self->isRunning = false;
    }
    catch (...) {
        self->isRunning = false;
        throw;
    }
}

template <class S1>
void
RWTFunctorList1Imp<S1>::add(const RWTFunctor1<S1>& functor, RWCallbackScope scope)
{
    RWTLockGuard<MutexType> guard(RWTFunctor1Imp<S1>::mutex());
    list_.add(functor, scope);
}

template <class S1>
void
RWTFunctorList1Imp<S1>::remove(const RWTFunctor1<S1>& functor)
{
    RWTLockGuard<MutexType> guard(RWTFunctor1Imp<S1>::mutex());
    list_.remove(functor);
}

template <class S1>
void
RWTFunctorList1Imp<S1>::update(void)
{
    list_.update();
}
