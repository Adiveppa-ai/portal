/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTMaskedCallbackList2.cc#1 $
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

#include <rw/functor/list/RWTMaskedCallbackList2.h>

template <class S1, class S2>
RWTMaskedCallbackElem2<S1, S2>::RWTMaskedCallbackElem2(void)
{
}

template <class S1, class S2>
RWTMaskedCallbackElem2<S1, S2>::RWTMaskedCallbackElem2(
    const RWTFunctor2<S1, S2>& f, unsigned long m, RWCallbackScope s)
    : RWMaskedCallbackElemBase(m, s),
      functor_(f)
{
}

template <class S1, class S2>
RWTMaskedCallbackElem2<S1, S2>::RWTMaskedCallbackElem2(
    const RWTMaskedCallbackElem2<S1, S2>& s)
    : RWMaskedCallbackElemBase(s),
      functor_(s.functor_)
{
}

template <class S1, class S2>
RWTMaskedCallbackElem2<S1, S2>::~RWTMaskedCallbackElem2(void)
{
}

template <class S1, class S2>
RWTMaskedCallbackElem2<S1, S2>&
RWTMaskedCallbackElem2<S1, S2>::operator=(const RWTMaskedCallbackElem2<S1, S2>& s)
{
    RWMaskedCallbackElemBase::operator=(s);
    functor_ = s.functor_;
    return *this;
}

template <class S1, class S2>
RWTFunctor2<S1, S2>
RWTMaskedCallbackElem2<S1, S2>::functor(void) const
{
    return functor_;
}

template <class Mutex, class S1, class S2>
RWTMaskedCallbackList2<Mutex, S1, S2>::RWTMaskedCallbackList2(Mutex& ref)
    : RWTMaskedCallbackListBase<Mutex>(ref)
{
}

template <class Mutex, class S1, class S2>
RWTMaskedCallbackList2<Mutex, S1, S2>::~RWTMaskedCallbackList2(void)
{
}

template <class Mutex, class S1, class S2>
RWTMaskedCallbackList2<Mutex, S1, S2>&
RWTMaskedCallbackList2<Mutex, S1, S2>::operator=(const RWTMaskedCallbackList2<Mutex, S1, S2>& s)
{
    // USAGE ERROR - Mutex must be locked when this member is called!
    RW_ASSERT((BaseType::mutex()).isAcquired());

    if (&s != this) {
        // prevent updates to second while we are copying
        RWTLockGuard<Mutex> guard(s.mutex());

        RWTMaskedCallbackListBase<Mutex>::operator=(s);

        addList_     = s.addList_;
        removeList_  = s.removeList_;
        currentList_ = s.currentList_;
    }

    return *this;
}

template <class Mutex, class S1, class S2>
void
RWTMaskedCallbackList2<Mutex, S1, S2>::add(
    const RWTFunctor2<S1, S2>& f, unsigned long m, RWCallbackScope s)
{
    // USAGE ERROR - Mutex must be locked when this member is called!
    RW_ASSERT((BaseType::mutex()).isAcquired());

    addList_.append(RWTMaskedCallbackElem2<S1, S2>(f, m, s));
}

template <class Mutex, class S1, class S2>
void
RWTMaskedCallbackList2<Mutex, S1, S2>::operator()(S1 s1, S2 s2, unsigned long cbMask)
{
    // Clients of this class are responsible for providing synchronization
    // for this member - only one thread should execute this function
    // at one time!

    // USAGE ERROR - Mutex must be unlocked when calling this member!
    RW_ASSERT(!(BaseType::mutex()).isAcquired());

    // Update the list first.
    update();

    // Are there *any* callbacks with a mask that matches?
    if (cbMask & BaseType::mask()) {
        unsigned long newMask = 0;
        // Yes there is at least one, so traverse the list...
        typename RWTValSlist<RWTMaskedCallbackElem2<S1, S2> >::iterator iter = currentList_.begin();
        while (iter != currentList_.end()) {
            RWTMaskedCallbackElem2<S1, S2> current = *iter;
            //  Does this callback mask match?
            if (current.mask() & cbMask) {
                // Are we going to use this callback anymore?
                if (RW_CALL_ONCE == current.scope()) {
                    // Nope, so remove it from the list
                    iter = currentList_.erase(iter);
                }
                else {
                    // We're keeping this callback - update the mask...
                    newMask |= current.mask();
                    ++iter;
                }
                // Yes, then invoke it, and let any exceptions fly!
                current(s1, s2);
            }
            else {
                // We're not calling this callback but might later -update the mask.
                newMask |= current.mask();
                ++iter;
            }
        }
        BaseType::mask(newMask);
    }
}

template <class Mutex, class S1, class S2>
void
RWTMaskedCallbackList2<Mutex, S1, S2>::remove(const RWTFunctor2<S1, S2>& functor)
{
    // USAGE ERROR - Mutex must be locked when this member is called!
    RW_ASSERT((BaseType::mutex()).isAcquired());

    removeList_.append(RWTMaskedCallbackElem2<S1, S2>(functor));
}

template <class Mutex, class S1, class S2>
void
RWTMaskedCallbackList2<Mutex, S1, S2>::update(void)
{
    // Lock to prevent changes to the update lists
    RWTLockGuard<Mutex> guard(BaseType::mutex());

    // Do additions first then removals
    // (in case an entry was added and removed since the last update)

    // Additions result in an update of the list mask, but removals do not,
    // because there may be other entries in the list that have the same
    // mask as the entry being removed...

    // Update from add list...
    while (!addList_.isEmpty()) {
        RWTMaskedCallbackElem2<S1, S2> current = addList_.removeFirst();
        // Update mask
        unsigned long newMask = BaseType::mask();
        newMask |= current.mask();
        BaseType::mask(newMask);
        currentList_.append(current);
    }

    // Update from remove list
    while (!removeList_.isEmpty()) {
        // Remove all matching entries from list
        RWTMaskedCallbackElem2<S1, S2> current = removeList_.removeFirst();
        currentList_.removeAll(current);
    }
}
