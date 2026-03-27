/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPCValBufferBaseGuarded.cc#1 $
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

  RWTPCValBufferBaseGuarded<Type,GuardDecorator> - Templatized base class for
    buffers with guarded, producer-consumer synchronization semantics whose
    entries are stored by-value.

******************************************************************************/

#include <rw/itc/RWTPCValBufferBaseGuarded.h>

template <class Type, class GuardDecorator>
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::~RWTPCValBufferBaseGuarded(void)
{
}

template <class Type, class GuardDecorator>
void
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::checkGuards(void)
{
    // check if any readers are waiting for data.
    // If there aren't any, there's no reason to
    // acquire the lock or signal.
    if (this->RWPCBufferBase::waitingReaders_) {
        // Some platforms mistakenly see RWPCBufferBase::LockGuard
        // as protected (and unavailable) from this function.  We
        // use RWTLockGuard directly here to avoid this issue.
        RWTLockGuard<RWTMonitor<RWMutexLock> > lock(RWPCBufferBase::monitor());

        // Double-check - if there are still readers
        // waiting after getting the lock, we'll signal.
        if (this->RWPCBufferBase::waitingReaders_) {
            // Threads that are blocked in read calls are
            // waiting for this condition to be signalled.
            // Signaling all waiting threads will allow them
            // to determine
            this->RWPCBufferBase::notEmpty_.signalAll();
        }
    }
}

template <class Type, class GuardDecorator>
void
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::write(const Type& value, const RWTFunctor<bool()>& guard)
{
    RWTPCValBufferBase<GuardDecorator>::write(GuardDecorator(value, guard));
}

template <class Type, class GuardDecorator>
bool
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::tryWrite(const Type& value, const RWTFunctor<bool()>& guard)
{
    return RWTPCValBufferBase<GuardDecorator>::tryWrite(GuardDecorator(value, guard));
}

template <class Type, class GuardDecorator>
RWWaitStatus
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::write(const Type& value, const RWTFunctor<bool()>& guard, unsigned long milliseconds)
{
    return RWTPCValBufferBase<GuardDecorator>::write(GuardDecorator(value, guard), milliseconds);
}

template <class Type, class GuardDecorator>
bool
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::_canRead(void) const
{
    bool b = false;
    // Is there anything in the buffer?
    if (RWTPCValBufferBase<GuardDecorator>::_entries() > 0) {
        // Yes, there are entries in the buffer - now check to see if any are readable...
        // Reset iterator to leave it pointing at the beginning of the list
        RWTPCValBufferBaseGuarded<Type, GuardDecorator>* self =
            const_cast<RWTPCValBufferBaseGuarded<Type, GuardDecorator>*>(this);

        // Iterate until we find an entry whose guard evaluates
        // to true or until we run out of entries.
        self->iter_ = self->buffer_.begin();
        for (; self->iter_ != self->buffer_.end(); ++(self->iter_)) {
            RWTFunctor<bool()> guard = (*(self->iter_)).guard_;
            b = !guard.isValid() || guard();
            if (b) {
                break;
            }
        }
    }
    return b;
}

template <class Type, class GuardDecorator>
GuardDecorator
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::_read(void)
{
    // Use the value whose location was cached by an earlier call to _canRead()
    GuardDecorator decorator = (*(this->iter_));
    this->iter_ = this->buffer_.erase(this->iter_);
    return decorator;
}

template <class Type, class GuardDecorator>
GuardDecorator
RWTPCValBufferBaseGuarded<Type, GuardDecorator>::_peek(void)
{
    // Use the value whose location was cached by an earlier call to _canRead()
    return *(this->iter_);
}
