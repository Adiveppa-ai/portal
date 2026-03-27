/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR0.cc#1 $
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

#include <rw/functor/RWTFunctorR0.h>

template <class SR>
RWTFunctorR0<SR>::RWTFunctorR0(void)
{
}

template <class SR>
RWTFunctorR0<SR>::RWTFunctorR0(RWStaticCtor)
    : RWTFunctor<SR()>(RW_STATIC_CTOR)
{
}

template <class SR>
RWTFunctorR0<SR>::~RWTFunctorR0(void)
{
}

template <class SR>
RWTFunctorR0<SR>::RWTFunctorR0(RWTFunctorR0Imp<SR>* functorImp)
    : RWTFunctor<SR()>((RWTFunctorImpBase0<SR>*)functorImp)
{
}

template <class SR>
RWTFunctorR0<SR>::RWTFunctorR0(const RWTFunctorR0<SR>& second)
    : RWTFunctor<SR()>(second)
{
}

template <class SR>
RWTFunctorR0<SR>::RWTFunctorR0(const RWTFunctor<SR()>& second)
    : RWTFunctor<SR()>(second)
{
}

template <class SR>
RWTFunctorR0<SR>&
RWTFunctorR0<SR>::operator=(const RWTFunctorR0<SR>& second)
{
    if (&second != this) {
        RWTFunctor<SR()>::operator=(second);
    }
    return *this;
}

template <class SR>
RWTFunctorR0<SR>&
RWTFunctorR0<SR>::operator=(const RWTFunctor<SR()>& second)
{
    RWTFunctor<SR()>::operator=(second);
    return *this;
}
