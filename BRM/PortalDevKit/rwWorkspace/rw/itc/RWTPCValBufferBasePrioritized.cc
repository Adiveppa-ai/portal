/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBasePrioritized.cc#1 $
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

  RWTPCValBufferBasePrioritized<Type,PriorityDecorator> - Templatized base
    class for buffers with producer-consumer synchronization semantics whose
    entries are stored by-value and ordered according to a priority value.

******************************************************************************/

#include <rw/itc/RWTPCValBufferBasePrioritized.h>

template <class Type, class PriorityDecorator>
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::~RWTPCValBufferBasePrioritized(void)
{
}

template <class Type, class PriorityDecorator>
void
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::write(long priority, const Type& value)
{
    RWTPCValBufferBase<PriorityDecorator>::write(PriorityDecorator(value, priority));
}

template <class Type, class PriorityDecorator>
bool
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::tryWrite(long priority, const Type& value)
{
    return RWTPCValBufferBase<PriorityDecorator>::tryWrite(PriorityDecorator(value, priority));
}

template <class Type, class PriorityDecorator>
RWWaitStatus
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::write(long priority, const Type& value, unsigned long milliseconds)
{
    return RWTPCValBufferBase<PriorityDecorator>::write(PriorityDecorator(value, priority), milliseconds);
}

template <class Type, class PriorityDecorator>
void
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::_writeBack(const PriorityDecorator& value)
{
    // Write at end of list of equal priorities for queue implementation
    if (RWTPCValBufferBase<PriorityDecorator>::buffer_.isEmpty() ||
            RWTPCValBufferBase<PriorityDecorator>::buffer_.last().priority_ >= value.priority_) {
        // The queue is empty or the new priority is less than that of the last entry
        // Insert at the end of the list
        RWTPCValBufferBase<PriorityDecorator>::buffer_.append(value);
    }
    else if (RWTPCValBufferBase<PriorityDecorator>::buffer_.first().priority_ < value.priority_) {
        // The new priority is greater than that of the first entry.
        // Insert at the beginning of the list
        RWTPCValBufferBase<PriorityDecorator>::buffer_.prepend(value);
    }
    else {
        // Start at the beginning of the queue and search for the first
        // entry whose priority is less-than the new priority
        // We want to insert the new element BEFORE the element with the
        // lesser priority.
        typename RWTValSlist<PriorityDecorator>::iterator
        iter = RWTPCValBufferBase<PriorityDecorator>::buffer_.begin();

        // Keep going till we find an entry
        // We don't need to worry about iterating past the end of the list
        // as the first two tests above ensure that we will find an entry
        // between the first and last entry...
        while ((*iter).priority_ >= value.priority_) {
            ++iter;
        }
        RWTPCValBufferBase<PriorityDecorator>::buffer_.insert(iter, value);
    }
}

template <class Type, class PriorityDecorator>
void
RWTPCValBufferBasePrioritized<Type, PriorityDecorator>::_writeFront(const PriorityDecorator& value)
{
    // Write at beginning of list of equal priorities for stack implementation
    if (RWTPCValBufferBase<PriorityDecorator>::buffer_.isEmpty() ||
            RWTPCValBufferBase<PriorityDecorator>::buffer_.last().priority_ > value.priority_) {
        // The  is empty or the new priority is less than that of the last entry
        // Insert at the end of the list
        RWTPCValBufferBase<PriorityDecorator>::buffer_.append(value);
    }
    else if (RWTPCValBufferBase<PriorityDecorator>::buffer_.first().priority_ <= value.priority_) {
        // The new priority is greater than that of the first entry.
        // Insert at the beginning of the list
        RWTPCValBufferBase<PriorityDecorator>::buffer_.prepend(value);
    }
    else {
        // Start at the beginning of the stack and search for the first
        // entry whose priority is equal to the new priority
        // We want to insert the new element BEFORE the element with the
        // equal or lesser priority.
        typename RWTValSlist<PriorityDecorator>::iterator
        iter = RWTPCValBufferBase<PriorityDecorator>::buffer_.begin();

        // Keep going till we find an entry
        // We don't need to worry about iterating past the end of the list
        // as the first two tests above ensure that we will find an entry
        // between the first and last entry...
        while ((*iter).priority_ > value.priority_) {
            ++iter;
        }
        RWTPCValBufferBase<PriorityDecorator>::buffer_.insert(iter, value);
    }
}
