/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTNetHandle.cc#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

/*
 * defs for Handle classes
 */

#include <rw/network/RWTNetHandle.h>


template< class C >
RWTNetHandle<C>::RWTNetHandle(C* object)
    : counter_(object ? new RWTAtomic<size_t>() : 0), object_(object)
{
    /* if object_ is null, then counter is null */
    attach();
}

template< class C >
RWTNetHandle<C>::RWTNetHandle(const RWTNetHandle<C>& other)
    : counter_(other.counter_), object_(other.object_)
{
    attach();
}

template< class C >
RWTNetHandle<C>::~RWTNetHandle()
{
    detach();
}

template< class C >
RWTNetHandle<C>& RWTNetHandle<C>::operator=(const RWTNetHandle<C>& other)
{
    if (&other != this) {
        detach();
        counter_ = other.counter_;
        object_ = other.object_;
        attach();
    }
    return *this;
}

template< class C >
void RWTNetHandle<C>::attach()
{
    if (counter_) {
        ++(*counter_);
    }
}

template< class C >
void RWTNetHandle<C>::detach()
{
    if (counter_ && 0 == --(*counter_)) {
        delete object_;
        object_ = 0;
        delete counter_;
        counter_ = 0;
    }
}
