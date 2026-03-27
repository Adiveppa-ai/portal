/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/map/RWTFunctorMap2.cc#1 $
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
 * Provides definition of class 'RWTFunctorMap2'.
 *
 *************************************************************************/

#include <rw/functor/map/RWTFunctorMap2.h>
#include <rw/functor/map/RWTFunctorMap2Imp.h>

template <class Key, class S1>
RWTFunctorMap2<Key, S1>::RWTFunctorMap2(hash_function hf, size_t size)
    : RWTFunctor2<Key, S1>(new RWTFunctorMap2Imp<Key, S1>(hf, size))
{
}

template <class Key, class S1>
RWTFunctorMap2<Key, S1>::RWTFunctorMap2(RWTFunctorMap2Imp<Key, S1>* functorImp)
    : RWTFunctor2<Key, S1>(functorImp)
{
}

template <class Key, class S1>
RWTFunctorMap2<Key, S1>::RWTFunctorMap2(const RWTFunctorMap2<Key, S1>& second)
    : RWTFunctor2<Key, S1>(second)
{
}

template <class Key, class S1>
RWTFunctorMap2<Key, S1>::~RWTFunctorMap2(void)
{
}

template <class Key, class S1>
RWTFunctorMap2<Key, S1>&
RWTFunctorMap2<Key, S1>::operator=(const RWTFunctorMap2<Key, S1>& second)
{
    if (&second != this) {
        RWTFunctor2<Key, S1>::operator=(second);
    }
    return *this;
}

template <class Key, class S1>
void
RWTFunctorMap2<Key, S1>::operator()(Key key, S1 s1) const
{
    body().run(key, s1);
}

template <class Key, class S1>
RWTFunctorMap2Imp<Key, S1>&
RWTFunctorMap2<Key, S1>::body(void) const
{
    return (RWTFunctorMap2Imp<Key, S1>&)RWTFunctor2<Key, S1>::body();
}

template <class Key, class S1>
bool RWTFunctorMap2<Key, S1>::add(Key key, RWTFunctor1<S1> functor)
{
    return body().add(key, functor);
}

template <class Key, class S1>
bool
RWTFunctorMap2<Key, S1>::remove(Key key)
{
    return body().remove(key);
}

template <class Key, class S1>
bool
RWTFunctorMap2<Key, S1>::contains(Key key) const
{
    return body().contains(key);
}

template <class Key, class S1>
bool
RWTFunctorMap2<Key, S1>::find(Key key, RWTFunctor1<S1>& functor) const
{
    return body().find(key, functor);
}

template <class Key, class S1>
void
RWTFunctorMap2<Key, S1>::resize(size_t size)
{
    body().resize(size);
}

template <class Key, class S1>
void
RWTFunctorMap2<Key, S1>::clear(void)
{
    body().clear();
}

template <class Key, class S1>
size_t
RWTFunctorMap2<Key, S1>::entries(void) const
{
    return body().entries();
}

template <class Key, class S1>
void
RWTFunctorMap2<Key, S1>::setDefault(RWTFunctor1<S1> functor)
{
    body().setDefault(functor);
}

template <class Key, class S1>
RWTFunctor1<S1>
RWTFunctorMap2<Key, S1>::getDefault(void) const
{
    return body().getDefault();
}
