/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTCountingPointer.cc#1 $
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

#include <rw/pointer/RWTCountingPointer.h>
#include <rw/tools/pointer.h>

template <class Body, class Counter>
RWTCountingPointer<Body, Counter>::RWTCountingPointer(RWStaticCtor)
    :
    RWTPointer<Body>(RW_STATIC_CTOR)
{
}


template <class Body, class Counter>
RWTCountingPointer<Body, Counter>::RWTCountingPointer(Body* bodyP)
    :
    RWTPointer<Body>(bodyP)
{
    // ensure the body pointer is deleted if we're
    // unable to allocate a counter.
    RWTScopedPointer<Body> guard(bodyP);
    if (bodyP != rwnil) {
        counterP_ = new CounterType(1);
    }
    else {
        counterP_ = rwnil;
    }
    guard.release();
}

template <class Body, class Counter>
RWTCountingPointer<Body, Counter>::RWTCountingPointer(const RWTCountingPointer<Body, Counter>& second)
    :
    RWTPointer<Body>(second.bodyP_)
{
    // it acquires one more reference
    if (rwnil != second.counterP_) {
        (second.counterP_)->addReference();
    }
    counterP_ = second.counterP_;
}

template <class Body, class Counter>
RWTCountingPointer<Body, Counter>::~RWTCountingPointer(void)
{
    free();
}

template <class Body, class Counter>
RWTCountingPointer<Body, Counter>&
RWTCountingPointer<Body, Counter>::operator=(const RWTCountingPointer<Body, Counter>& second)
{
    if (&second != this) {
        // it acquires one more reference
        if (rwnil != second.counterP_) {
            (second.counterP_)->addReference();
        }

        // decrement and test; no one else using it ?
        free();

        // share the resource and counter
        RWTPointer<Body>::operator=(second.bodyP_);
        counterP_ =  second.counterP_;
    }
    return *this;
}

template <class Body, class Counter>
RWTCountingPointer<Body, Counter>&
RWTCountingPointer<Body, Counter>::operator=(Body* bodyP)
{
    if (bodyP != this->bodyP_) {
        free();

        // ensure the body pointer is deleted if we're
        // unable to allocate a counter.
        RWTScopedPointer<Body> guard(bodyP);
        if (bodyP != rwnil) {
            counterP_ = new CounterType(1);
        }
        else {
            counterP_ = rwnil;
        }
        RWTPointer<Body>::operator=(bodyP);
        guard.release();
    }
    return *this;
}

#ifndef RW_NO_NONCLASS_ARROW_RETURN
// Disable this operator if your compiler doesn't allow it
// in a template class where the template type is a non-class type,
// if the operator is not referenced.

template <class Body, class Counter>
Body*
RWTCountingPointer<Body, Counter>::operator->(void) const
{
    RWTPointer<Body>::validate();
    return RWTPointer<Body>::get();
}
#endif

template <class Body, class Counter>
Body&
RWTCountingPointer<Body, Counter>::operator*(void) const
{
    RWTPointer<Body>::validate();
    return *(RWTPointer<Body>::get());
}
