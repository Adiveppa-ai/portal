/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTCountedPointer.cc#1 $
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

#include <rw/pointer/RWTCountedPointer.h>

template< class Body >
RW_CC_INLINE
RWTCountedPointer<Body>::RWTCountedPointer(RWStaticCtor)
    : RWTPointer<Body>(RW_STATIC_CTOR)
{
    // Do nothing to change pointer since it may already have a value!
}

template< class Body >
RW_CC_INLINE
RWTCountedPointer<Body>::RWTCountedPointer(Body* bodyP)
    : RWTPointer<Body>(bodyP)
{
    Body* body = RWTPointer<Body>::get();
    if (rwnil != body) {
        body->addReference();
    }
}

template< class Body >
RW_CC_INLINE
RWTCountedPointer<Body>::RWTCountedPointer(const RWTCountedPointer<Body>& second)
    : RWTPointer<Body>(second.bodyP_)
{
    Body* body = RWTPointer<Body>::get();

    if (rwnil != body) {
        body->addReference();
    }
}

template< class Body >
RW_CC_INLINE
RWTCountedPointer<Body>::~RWTCountedPointer(void)
{
    // Detach and delete if necessary...
    orphan();
}

template< class Body >
RW_CC_INLINE RWTCountedPointer<Body>&
RWTCountedPointer<Body>::operator=(const RWTCountedPointer<Body>& second)
{
    // Detach current and delete if necessary, then attach to second's body.
    if (&second != this) {
        transfer(second.bodyP_);
    }

    return *this;
}

template< class Body >
RW_CC_INLINE RWTCountedPointer<Body>&
RWTCountedPointer<Body>::operator=(Body* ptr)
{
    transfer(ptr);

    return *this;
}

template< class Body >
RW_CC_INLINE Body*
RWTCountedPointer<Body>::operator->(void) const
{
    RWTPointer<Body>::validate();

    return RWTPointer<Body>::get();
}

template< class Body >
RW_CC_INLINE Body&
RWTCountedPointer<Body>::operator*(void) const
{
    RWTPointer<Body>::validate();

    return *(RWTPointer<Body>::get());
}
