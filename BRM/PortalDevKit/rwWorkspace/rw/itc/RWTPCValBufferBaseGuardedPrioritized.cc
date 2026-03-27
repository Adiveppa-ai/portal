/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBaseGuardedPrioritized.cc#1 $
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


/*****************************************************************************

  RWTPCValBufferBaseGuardedPrioritized<Type,GuardAndPriorityDecorator> -
    Templatized base class for buffers with guarded, producer-consumer
    synchronization semantics whose entries are stored by-value and ordered
    according to a priority value.

******************************************************************************/

#include <rw/itc/RWTPCValBufferBaseGuardedPrioritized.h>

template <class Type, class GuardAndPriorityDecorator>
RWTPCValBufferBaseGuardedPrioritized<Type, GuardAndPriorityDecorator>::~RWTPCValBufferBaseGuardedPrioritized(void)
{
}

template <class Type, class GuardAndPriorityDecorator>
void
RWTPCValBufferBaseGuardedPrioritized<Type, GuardAndPriorityDecorator>::write(long priority, const Type& value, const RWTFunctor<bool()>& guard)
{
    RWTPCValBufferBase<GuardAndPriorityDecorator>::write(GuardAndPriorityDecorator(value, guard, priority));
}

template <class Type, class GuardAndPriorityDecorator>
bool
RWTPCValBufferBaseGuardedPrioritized<Type, GuardAndPriorityDecorator>::tryWrite(long priority, const Type& value, const RWTFunctor<bool()>& guard)
{
    return RWTPCValBufferBase<GuardAndPriorityDecorator>::tryWrite(GuardAndPriorityDecorator(value, guard, priority));
}

template <class Type, class GuardAndPriorityDecorator>
RWWaitStatus
RWTPCValBufferBaseGuardedPrioritized<Type, GuardAndPriorityDecorator>::write(long priority, const Type& value, const RWTFunctor<bool()>& guard, unsigned long milliseconds)
{
    return RWTPCValBufferBase<GuardAndPriorityDecorator>::write(GuardAndPriorityDecorator(value, guard, priority), milliseconds);
}
