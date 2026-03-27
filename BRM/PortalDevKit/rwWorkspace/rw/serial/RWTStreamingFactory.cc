/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWTStreamingFactory.cc#1 $
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
 ********************************************************************/

#include <rw/serial/RWTStreamingFactory.h>
#include <new>

template <class Base>
/* static */ RWOnce
RWTStreamingFactory<Base>::initInstanceOnce_ = RW_ONCE_INITIALIZER;

template <class Base>
typename RWTStreamingFactory<Base>::factory_type_ptr
RWTStreamingFactory<Base>::ptr_ /* = 0 */;

template <class Base>
/* static */ void
RWTStreamingFactory<Base>::init()
{
    ptr_ = new(std::nothrow) RWTFactory0<Base, RWSymbol> (DefaultMethod());
    RW_ASSERT(ptr_);
}

template <class Base>
typename RWTStreamingFactory<Base>::factory_type_ptr
RWTStreamingFactory<Base>::getFactory()
{
    initInstanceOnce_((void(*)())RWTStreamingFactory<Base>::init);
    return ptr_;
}


template <class Base>
void*
RWTStreamingFactory<Base>::operator()(RWSymbol typeName) const
{
    return getFactory()->create(typeName);
}
