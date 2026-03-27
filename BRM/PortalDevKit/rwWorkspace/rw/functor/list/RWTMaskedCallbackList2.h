#ifndef __rw_functor_list_RWTMaskedCallbackList2_h__
#define __rw_functor_list_RWTMaskedCallbackList2_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTMaskedCallbackList2.h#1 $
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

#include <rw/functor/list/RWTMaskedCallbackListBase.h>
#include <rw/functor/list/pkgdefs.h>
#include <rw/functor/RWTFunctor2.h>
#include <rw/tvslist.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWMaskedCallback2List RWTMaskedCallbackList2
#  define RWMaskedCallback2Elem RWTMaskedCallbackElem2

RW_SUPPRESS_DEPRECATED_WARNINGS

template <class S1, class S2>
class RWTMaskedCallbackElem2 : public RWMaskedCallbackElemBase
{

public:

    // Creates a new (empty) element instance.
    RWTMaskedCallbackElem2(void);

    // Copy constructor
    RWTMaskedCallbackElem2(const RWTMaskedCallbackElem2<S1, S2>& second);

    // Creates a new element instance, and sets the members.
    RWTMaskedCallbackElem2(const RWTFunctor2<S1, S2>& functor,
                           unsigned long mask = 0, RWCallbackScope scope = RW_CALL_ONCE);

    // Destructor
    ~RWTMaskedCallbackElem2(void);

    // Assignment operator
    RWTMaskedCallbackElem2<S1, S2>&
    operator=(const RWTMaskedCallbackElem2<S1, S2>& second);

    // Returns the functor stored in this element.
    RWTFunctor2<S1, S2>
    functor(void) const;

    // Sets the functor stored in this element.
    void
    functor(const RWTFunctor2<S1, S2>& newFunctor);

    // Invokes the functor with the given argument values.
    void
    operator()(S1 s1, S2 s2);

    // Required for storage in RWTValSlist.
    bool
    operator==(const RWTMaskedCallbackElem2<S1, S2>& second) const;

protected:
    RWTFunctor2<S1, S2>    functor_;

};

template <class Mutex, class S1, class S2>
class RWTMaskedCallbackList2 : public RWTMaskedCallbackListBase<Mutex>
{

    typedef RWTMaskedCallbackListBase<Mutex> BaseType;

public:

    // The type of mutex protecting the lists data.
    typedef  Mutex MutexType;

    // The type of the first caller argument.
    typedef  S1    S1Type;

    // The type of the first caller argument.
    typedef  S2    S2Type;

    // Constructs a callback list, using the given mutex
    // to protect the list's state.
    RWTMaskedCallbackList2(Mutex& mutex);

    // Destructor
    ~RWTMaskedCallbackList2(void);

    // Assignment operator
    //
    // NOTE: The mutex passed to the callback list constructor
    //       MUST be LOCKED by the user when this member is called!
    //
    //       The mutex of second will be locked in this operator to
    //       prevent updates during the assignment
    RWTMaskedCallbackList2<Mutex, S1, S2>&
    operator=(const RWTMaskedCallbackList2<Mutex, S1, S2>& second);

    // Adds an entry to the end of the callback list.
    // The same functor may be added more than once with different
    // masks, but it is more efficient to install the functor once
    // Actually adds  an entry to the add list, whose entries
    // are in turn appended to the current list the next time
    // that either the callback list is invoked, or the update
    // method is explicitly called.
    //
    // NOTE: The mutex passed to the callback list constructor
    //       MUST be LOCKED by the user when this member is called!
    void
    add(const RWTFunctor2<S1, S2>& functor, unsigned long mask, RWCallbackScope scope);

    // Removes all entries from the callback list that contain the
    // specified functor.
    //       Adds an entry to the remove list, whose entries are used
    //       to identify entries to be removed from the current list.
    // NOTE: The mutex passed to the callback list constructor
    //       MUST be LOCKED when this member is called!
    void
    remove(const RWTFunctor2<S1, S2>& functor);

    // Acquires the mutex, updates the list, releases the mutex,
    // and for each callback entry in the list, starting at the front,
    // compares the entry's callback mask to the specified mask,
    // and if there are any matching 1's, invokes the callback,
    // passing the specified data, and then deletes the list entry
    // if its scope is found to be RW_CALL_ONCE.

    // NOTE: The mutex passed to the callback list constructor
    //       MUST be UNLOCKED when this member is called!
    void
    operator()(S1 s1, S2 s2, unsigned long mask);

    // Acquires the mutex, updates the current list from the
    // add and remove lists, and releases the mutex.
    void
    update(void);

private:

    // Copy constructor
    RWTMaskedCallbackList2(const RWTMaskedCallbackList2<Mutex, S1, S2>& second);

protected:

    RWTValSlist< RWTMaskedCallbackElem2<S1, S2> > addList_;
    RWTValSlist< RWTMaskedCallbackElem2<S1, S2> > removeList_;
    RWTValSlist< RWTMaskedCallbackElem2<S1, S2> > currentList_;

};


template <class S1, class S2>
inline void
RWTMaskedCallbackElem2<S1, S2>::functor(const RWTFunctor2<S1, S2>& newFunctor)
{
    functor_ = newFunctor;
}

template <class S1, class S2>
inline void
RWTMaskedCallbackElem2<S1, S2>::operator()(S1 s1, S2 s2)
{
    functor_(s1, s2);
}

template <class S1, class S2>
inline bool
RWTMaskedCallbackElem2<S1, S2>::operator==(const RWTMaskedCallbackElem2<S1, S2>& second) const
{
    return functor_ == second.functor_;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/list/RWTMaskedCallbackList2.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_list_RWTMaskedCallbackList2_h__
