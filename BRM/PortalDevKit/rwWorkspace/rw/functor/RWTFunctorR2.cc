/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR2.cc#1 $
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

   RWTFunctorR2<SR,S1,S2> - Handle class for RWTFunctorR2Imp functor family

******************************************************************************/

#include <rw/functor/RWTFunctorR2.h>

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>::RWTFunctorR2(void)
{
}

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>::RWTFunctorR2(RWStaticCtor)
    : RWTFunctor<SR(S1, S2)>(RW_STATIC_CTOR)
{
}

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>::RWTFunctorR2(RWTFunctorR2Imp<SR, S1, S2>* functorImp)
    : RWTFunctor<SR(S1, S2)>((RWTFunctorImpBase2<SR, S1, S2>*)functorImp)
{
}

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>::RWTFunctorR2(const RWTFunctorR2<SR, S1, S2>& second)
    : RWTFunctor<SR(S1, S2)>(second)
{
}

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>::RWTFunctorR2(const RWTFunctor<SR(S1, S2)>& second)
    : RWTFunctor<SR(S1, S2)>(second)
{
}

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>::~RWTFunctorR2(void)
{
}

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>&
RWTFunctorR2<SR, S1, S2>::operator=(const RWTFunctorR2<SR, S1, S2>& second)
{
    if (&second != this) {
        RWTFunctor<SR(S1, S2)>::operator=(second);
    }
    return *this;
}

template <class SR, class S1, class S2>
RWTFunctorR2<SR, S1, S2>&
RWTFunctorR2<SR, S1, S2>::operator=(const RWTFunctor<SR(S1, S2)>& second)
{
    RWTFunctor<SR(S1, S2)>::operator=(second);
    return *this;
}
