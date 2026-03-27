/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTCallbackList1.cc#1 $
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

#include <rw/functor/list/RWTCallbackList1.h>

RW_SUPPRESS_DEPRECATED_WARNINGS

template <class S1>
RWTCallbackElem1<S1>::RWTCallbackElem1(void)
{
}

template <class S1>
RWTCallbackElem1<S1>::RWTCallbackElem1(
    const RWTFunctor1<S1>& f, RWCallbackScope s)
    : RWCallbackElemBase(s),
      functor_(f)
{
}

template <class S1>
RWTCallbackElem1<S1>::RWTCallbackElem1(const RWTCallbackElem1<S1>& s)
    : RWCallbackElemBase(s),
      functor_(s.functor_)
{
}

template <class S1>
RWTCallbackElem1<S1>&
RWTCallbackElem1<S1>::operator=(const RWTCallbackElem1<S1>& s)
{
    RWCallbackElemBase::operator=(s);
    functor_ = s.functor_;
    return *this;
}

template <class S1>
RWTCallbackElem1<S1>::~RWTCallbackElem1(void)
{
}

template <class Mutex, class S1>
RWTCallbackList1<Mutex, S1>::RWTCallbackList1(Mutex& m)
    : RWTCallbackListBase<Mutex>(m)
{
}

template <class Mutex, class S1>
RWTCallbackList1<Mutex, S1>&
RWTCallbackList1<Mutex, S1>::operator=(const RWTCallbackList1<Mutex, S1>& s)
{
    // USAGE ERROR - Mutex must be locked when this member is called!
    RW_ASSERT((BaseType::mutex()).isAcquired());

    if (&s != this) {
        // prevent updates to second while we are copying
        RWTLockGuard<Mutex> guard(s.mutex());

        addList_ = s.addList_;
        removeList_ = s.removeList_;
        currentList_ = s.currentList_;
    }

    return *this;
}

template <class Mutex, class S1>
RWTCallbackList1<Mutex, S1>::~RWTCallbackList1(void)
{
}

template <class S1>
RWTFunctor1<S1>
RWTCallbackElem1<S1>::functor(void) const
{
    return functor_;
}

template <class Mutex, class S1>
void
RWTCallbackList1<Mutex, S1>::add(
    const RWTFunctor1<S1>& f, RWCallbackScope s)
{
    // USAGE ERROR - Mutex must be locked when this member is called!
    RW_ASSERT((BaseType::mutex()).isAcquired());

    addList_.append(RWTCallbackElem1<S1>(f, s));
}

template <class Mutex, class S1>
void
RWTCallbackList1<Mutex, S1>::operator()(S1 s1)
{
    // Clients of this class are responsible for providing synchronization
    // for this member - only one thread should execute this function
    // at one time!

    // USAGE ERROR - Mutex must be unlocked when calling this member!
    RW_ASSERT(!(BaseType::mutex()).isAcquired());

    // Update the list first.
    update();

    // For each elem in the list, invoke the functor, and remove
    // the item if the flag is RW_CALL_ONCE.
    typename RWTValSlist<RWTCallbackElem1<S1> >::iterator iter = currentList_.begin();
    while (iter != currentList_.end()) {
        RWTCallbackElem1<S1> current = *iter;

        if (RW_CALL_ONCE == current.scope()) {
            iter = currentList_.erase(iter);
        }
        else {
            ++iter;
        }

        current(s1);
    }
}

template <class Mutex, class S1>
void
RWTCallbackList1<Mutex, S1>::remove(const RWTFunctor1<S1>& f)
{
    // USAGE ERROR - Mutex must be locked when this member is called!
    RW_ASSERT((BaseType::mutex()).isAcquired());

    removeList_.append(RWTCallbackElem1<S1>(f));
}

template <class Mutex, class S1>
void
RWTCallbackList1<Mutex, S1>::update(void)
{
    // Lock to prevent changes to the update lists
    RWTLockGuard<Mutex> guard(BaseType::mutex());

    // Do additions first then removals
    // (in case an entry was added and removed since the last update)

    // Update from add list...
    while (!addList_.isEmpty()) {
        RWTCallbackElem1<S1> current = addList_.removeFirst();
        currentList_.append(current);
    }

    // Update from remove list
    while (!removeList_.isEmpty()) {
        RWTCallbackElem1<S1> current = removeList_.removeFirst();
        currentList_.removeAll(current);
    }
}

RW_RESTORE_DEPRECATED_WARNINGS
