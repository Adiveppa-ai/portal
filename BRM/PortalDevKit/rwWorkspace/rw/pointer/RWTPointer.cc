/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTPointer.cc#1 $
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

#include <rw/pointer/RWTPointer.h>

template< class Body >
RW_CC_INLINE
RWTPointer<Body>::~RWTPointer(void)
{
}

template< class Body >
RW_CC_INLINE Body*
RWTPointer<Body>::get(void) const
{
    return bodyP_;
}

template< class Body >
RW_CC_INLINE bool
RWTPointer<Body>::operator==(const RWTPointer<Body>& second) const
{
    // Note! Pointers are equal if they are both rwnil!
    return bodyP_ == second.bodyP_;
}

template< class Body >
RW_CC_INLINE bool
RWTPointer<Body>::operator!=(const RWTPointer<Body>& second) const
{
    return bodyP_ != second.bodyP_;
}

template< class Body >
RW_CC_INLINE bool
RWTPointer<Body>::operator<(const RWTPointer<Body>& second) const
{
    // Note! Pointers are equal if they are both rwnil!
    return bodyP_ < second.bodyP_;
}

template< class Body >
RW_CC_INLINE bool
RWTPointer<Body>::operator==(const Body* ptr) const
{
    return bodyP_ == ptr;
}

template< class Body >
RW_CC_INLINE bool
RWTPointer<Body>::operator!=(const Body* ptr) const
{
    return bodyP_ != ptr;
}

template< class Body >
RW_CC_INLINE
RWTPointer<Body>::RWTPointer(void)
    : bodyP_(rwnil)
{
}

template< class Body >
RW_CC_INLINE
RWTPointer<Body>::RWTPointer(RWStaticCtor)
{
    // Do nothing to change bodyP_ (it may already have a value)
}

template< class Body >
RW_CC_INLINE
RWTPointer<Body>::RWTPointer(Body* bodyP)
    : bodyP_(bodyP)
{
}

template< class Body >
RW_CC_INLINE
RWTPointer<Body>::RWTPointer(const RWTPointer<Body>& second)
    : bodyP_(second.bodyP_)
{
}

template< class Body >
RW_CC_INLINE RWTPointer<Body>&
RWTPointer<Body>::operator=(Body* ptr)
{
    bodyP_ = ptr;
    return *this;
}

template< class Body >
RW_CC_INLINE void
RWTPointer<Body>::swapWith(RWTPointer<Body>& second)
{
    // Note for derived types:
    // Swapping doesn't require a change to the reference counts!
    Body* temp = second.bodyP_;
    second.bodyP_ = bodyP_;
    bodyP_ = temp;
}
