/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/map/RWTFunctorMapR2Imp.cc#1 $
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
 * Provides definition of class 'RWTFunctorMapR2Imp'.
 *
 *************************************************************************/

#include <rw/functor/map/RWTFunctorMapR2.h>
#include <rw/functor/map/RWTFunctorMapR2Imp.h>

template <class SR, class Key, class S1>
RWTFunctorMapR2Imp<SR, Key, S1>::RWTFunctorMapR2Imp(hash_function hf, size_t size)
    : map_(hf, size)
{
}

template <class SR, class Key, class S1>
RWTFunctorMapR2Imp<SR, Key, S1>::~RWTFunctorMapR2Imp(void)
{
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2Imp<SR, Key, S1>::add(Key key, RWTFunctorR1<SR, S1> functor)
{
    // This construction takes into account that the non-stdlib version
    // not only returns no value; but that it also behaves differently
    // when there is already an entry in the map with a matching key.

    if (map_.contains(key)) {
        return false;
    }

    map_.insertKeyAndValue(key, functor);
    return true;
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2Imp<SR, Key, S1>::remove(Key key)
{
    return map_.remove(key);
}

template <class SR, class Key, class S1>
SR
RWTFunctorMapR2Imp<SR, Key, S1>::run(Key key, S1 s1) const
{
    RWTFunctorR1<SR, S1> functor;

    if (!map_.findValue(key, functor)) {
        functor = getDefault();
    }

    return functor(s1);
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2Imp<SR, Key, S1>::contains(Key key) const
{
    return map_.contains(key);
}

template <class SR, class Key, class S1>
bool
RWTFunctorMapR2Imp<SR, Key, S1>::find(Key key, RWTFunctorR1<SR, S1>& functor) const
{
    if (map_.findValue(key, functor)) {
        return true;
    }

    functor = getDefault();
    return false;
}

template <class SR, class Key, class S1>
void
RWTFunctorMapR2Imp<SR, Key, S1>::resize(size_t size)
{
    map_.resize(size);
}

template <class SR, class Key, class S1>
void
RWTFunctorMapR2Imp<SR, Key, S1>::clear(void)
{
    map_.clear();
}

template <class SR, class Key, class S1>
size_t
RWTFunctorMapR2Imp<SR, Key, S1>::entries(void) const
{
    return map_.entries();
}

template <class SR, class Key, class S1>
void
RWTFunctorMapR2Imp<SR, Key, S1>::setDefault(RWTFunctorR1<SR, S1> functor)
{
    defaultFunctor = functor;
}

template <class SR, class Key, class S1>
RWTFunctorR1<SR, S1>
RWTFunctorMapR2Imp<SR, Key, S1>::getDefault(void) const
{
    try {
        defaultFunctor.body();
    }
    catch (const RWTHRInvalidPointer&) {
        throw;
    }

    return defaultFunctor;
}
