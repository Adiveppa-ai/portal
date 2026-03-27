/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/map/RWTFunctorMap1.cc#1 $
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
 * Provides definition of class 'RWTFunctorMap1'.
 *
 *************************************************************************/

#include <rw/functor/map/RWTFunctorMap1.h>
#include <rw/functor/map/RWTFunctorMap1Imp.h>

template <class Key>
RWTFunctorMap1<Key>::RWTFunctorMap1(hash_function hf, size_t size)
    : RWTFunctor1<Key>(new RWTFunctorMap1Imp<Key>(hf, size))
{
}

template <class Key>
RWTFunctorMap1<Key>::RWTFunctorMap1(RWTFunctorMap1Imp<Key>* functorImp)
    : RWTFunctor1<Key>(functorImp)
{
}

template <class Key>
RWTFunctorMap1<Key>::RWTFunctorMap1(const RWTFunctorMap1<Key>& second)
    : RWTFunctor1<Key>(second)
{
}

template <class Key>
RWTFunctorMap1<Key>::~RWTFunctorMap1(void)
{
}

template <class Key>
RWTFunctorMap1<Key>&
RWTFunctorMap1<Key>::operator=(const RWTFunctorMap1<Key>& second)
{
    if (&second != this) {
        RWTFunctor1<Key>::operator=(second);
    }
    return *this;
}

template <class Key>
void
RWTFunctorMap1<Key>::operator()(Key key) const
{
    body().run(key);
}

template <class Key>
RWTFunctorMap1Imp<Key>&
RWTFunctorMap1<Key>::body(void) const
{
    return (RWTFunctorMap1Imp<Key>&)RWTFunctor1<Key>::body();
}

template <class Key>
bool
RWTFunctorMap1<Key>::add(Key key, RWFunctor0 functor)
{
    return body().add(key, functor);
}

template <class Key>
bool
RWTFunctorMap1<Key>::remove(Key key)
{
    return body().remove(key);
}

template <class Key>
bool
RWTFunctorMap1<Key>::contains(Key key) const
{
    return body().contains(key);
}

template <class Key>
bool
RWTFunctorMap1<Key>::find(Key key, RWFunctor0& functor) const
{
    return body().find(key, functor);
}

template <class Key>
void
RWTFunctorMap1<Key>::resize(size_t size)
{
    body().resize(size);
}

template <class Key>
void
RWTFunctorMap1<Key>::clear(void)
{
    body().clear();
}

template <class Key>
size_t
RWTFunctorMap1<Key>::entries(void) const
{
    return body().entries();
}

template <class Key>
void
RWTFunctorMap1<Key>::setDefault(RWFunctor0 functor)
{
    body().setDefault(functor);
}

template <class Key>
RWFunctor0
RWTFunctorMap1<Key>::getDefault(void) const
{
    return body().getDefault();
}
