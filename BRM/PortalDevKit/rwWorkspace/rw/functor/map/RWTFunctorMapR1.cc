/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/map/RWTFunctorMapR1.cc#1 $
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
 * Provides definition of class 'RWTFunctorMapR1'.
 *
 *************************************************************************/

#include <rw/functor/map/RWTFunctorMapR1.h>
#include <rw/functor/map/RWTFunctorMapR1Imp.h>

template <class SR, class Key>
RWTFunctorMapR1<SR, Key>::RWTFunctorMapR1(hash_function hf, size_t size)
    : RWTFunctorR1<SR, Key>(new RWTFunctorMapR1Imp<SR, Key>(hf, size))
{
}

template <class SR, class Key>
RWTFunctorMapR1<SR, Key>::RWTFunctorMapR1(RWTFunctorMapR1Imp<SR, Key>* functorImp)
    : RWTFunctorR1<SR, Key>(functorImp)
{
}

template <class SR, class Key>
RWTFunctorMapR1<SR, Key>::RWTFunctorMapR1(const RWTFunctorMapR1<SR, Key>& second)
    : RWTFunctorR1<SR, Key>(second)
{
}

template <class SR, class Key>
RWTFunctorMapR1<SR, Key>::~RWTFunctorMapR1(void)
{
}

template <class SR, class Key>
RWTFunctorMapR1<SR, Key>&
RWTFunctorMapR1<SR, Key>::operator=(const RWTFunctorMapR1<SR, Key>& second)
{
    if (&second != this) {
        RWTFunctorR1<SR, Key>::operator=(second);
    }
    return *this;
}

template <class SR, class Key>
SR
RWTFunctorMapR1<SR, Key>::operator()(Key key) const
{
    return body().run(key);
}

template <class SR, class Key>
RWTFunctorMapR1Imp<SR, Key>&
RWTFunctorMapR1<SR, Key>::body(void) const
{
    return (RWTFunctorMapR1Imp<SR, Key>&)RWTFunctorR1<SR, Key>::body();
}

template <class SR, class Key>
bool
RWTFunctorMapR1<SR, Key>::add(Key key, RWTFunctorR0<SR> functor)
{
    return body().add(key, functor);
}

template <class SR, class Key>
bool
RWTFunctorMapR1<SR, Key>::remove(Key key)
{
    return body().remove(key);
}

template <class SR, class Key>
bool
RWTFunctorMapR1<SR, Key>::contains(Key key) const
{
    return body().contains(key);
}

template <class SR, class Key>
bool
RWTFunctorMapR1<SR, Key>::find(Key key, RWTFunctorR0<SR>& functor) const
{
    return body().find(key, functor);
}

template <class SR, class Key>
void
RWTFunctorMapR1<SR, Key>::resize(size_t size)
{
    body().resize(size);
}

template <class SR, class Key>
void
RWTFunctorMapR1<SR, Key>::clear(void)
{
    body().clear();
}

template <class SR, class Key>
size_t
RWTFunctorMapR1<SR, Key>::entries(void) const
{
    return body().entries();
}

template <class SR, class Key>
void
RWTFunctorMapR1<SR, Key>::setDefault(RWTFunctorR0<SR> functor)
{
    body().setDefault(functor);
}

template <class SR, class Key>
RWTFunctorR0<SR>
RWTFunctorMapR1<SR, Key>::getDefault(void) const
{
    return body().getDefault();
}
