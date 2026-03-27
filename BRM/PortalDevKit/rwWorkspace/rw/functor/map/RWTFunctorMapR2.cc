/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/map/RWTFunctorMapR2.cc#1 $
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

/**************************************************************************
 *
 * Description:
 *
 * Provides definition of class 'RWTFunctorMapR2'.
 *
 *************************************************************************/

#include <rw/functor/map/RWTFunctorMapR2.h>
#include <rw/functor/map/RWTFunctorMapR2Imp.h>

template <class SR, class Key, class S1>
RWTFunctorMapR2<SR, Key, S1>::RWTFunctorMapR2(hash_function hf, size_t size)
    : RWTFunctorR2<SR, Key, S1>(new RWTFunctorMapR2Imp<SR, Key, S1>(hf, size))
{
}

template <class SR, class Key, class S1>
RWTFunctorMapR2<SR, Key, S1>::RWTFunctorMapR2(RWTFunctorMapR2Imp<SR, Key, S1>* functorImp)
    : RWTFunctorR2<SR, Key, S1>(functorImp)
{
}

template <class SR, class Key, class S1>
RWTFunctorMapR2<SR, Key, S1>::RWTFunctorMapR2(const RWTFunctorMapR2<SR, Key, S1>& second)
    : RWTFunctorR2<SR, Key, S1>(second)
{
}

template <class SR, class Key, class S1>
RWTFunctorMapR2<SR, Key, S1>::~RWTFunctorMapR2(void)
{
}

template <class SR, class Key, class S1>
RWTFunctorMapR2<SR, Key, S1>&
RWTFunctorMapR2<SR, Key, S1>::operator=(const RWTFunctorMapR2<SR, Key, S1>& second)
{
    if (&second != this) {
        RWTFunctorR2<SR, Key, S1>::operator=(second);
    }
    return *this;
}

template <class SR, class Key, class S1>
SR
RWTFunctorMapR2<SR, Key, S1>::operator()(Key key, S1 s1) const
{
    return body().run(key, s1);
}

template <class SR, class Key, class S1>
RWTFunctorMapR2Imp<SR, Key, S1>&
RWTFunctorMapR2<SR, Key, S1>::body(void) const
{
    return (RWTFunctorMapR2Imp<SR, Key, S1>&)RWTFunctorR2<SR, Key, S1>::body();
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2<SR, Key, S1>::add(Key key, RWTFunctorR1<SR, S1> functor)
{
    return body().add(key, functor);
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2<SR, Key, S1>::remove(Key key)
{
    return body().remove(key);
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2<SR, Key, S1>::contains(Key key) const
{
    return body().contains(key);
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2<SR, Key, S1>::find(Key key, RWTFunctorR1<SR, S1>& functor) const
{
    return body().find(key, functor);
}

template <class SR, class Key, class S1>
void
RWTFunctorMapR2<SR, Key, S1>::resize(size_t size)
{
    body().resize(size);
}

template <class SR, class Key, class S1>
void
RWTFunctorMapR2<SR, Key, S1>::clear(void)
{
    body().clear();
}

template <class SR, class Key, class S1>
size_t
RWTFunctorMapR2<SR, Key, S1>::entries(void) const
{
    return body().entries();
}

template <class SR, class Key, class S1>
void
RWTFunctorMapR2<SR, Key, S1>::setDefault(RWTFunctorR1<SR, S1> functor)
{
    body().setDefault(functor);
}

template <class SR, class Key, class S1>
RWTFunctorR1<SR, S1>
RWTFunctorMapR2<SR, Key, S1>::getDefault(void) const
{
    return body().getDefault();
}
