#ifndef __rw_functor_list_RWTCallbackList0_h__
#define __rw_functor_list_RWTCallbackList0_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTCallbackList0.h#1 $
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

#include <rw/functor/list/RWTCallbackListBase.h>
#include <rw/functor/list/pkgdefs.h>
#include <rw/functor/RWFunctor0.h>
#include <rw/tvslist.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

class RW_FUNCTOR_LIST_SYMBOLIC RWCallbackElem0 : public RWCallbackElemBase
{

public:

    // Creates a new (empty) element instance.
    RWCallbackElem0(void);


    // Creates a new element instance, and sets the members.
    RWCallbackElem0(const RWFunctor0& functor,
                    RWCallbackScope scope = RW_CALL_ONCE);

    // Copy constructor
    RWCallbackElem0(const RWCallbackElem0& second);

    // Destructor
    ~RWCallbackElem0(void);

    // Assignment operator
    RWCallbackElem0&
    operator=(const RWCallbackElem0& second);

    // Returns the functor stored in this element.
    RWFunctor0
    functor(void) const;

    // Sets the functor stored in this element.
    void
    functor(const RWFunctor0& newFunctor);

    // Invokes the functor with the given argument values.
    void
    operator()(void);

    // Required for storage in RWTValSlist.
    bool
    operator==(const RWCallbackElem0& second) const;

protected:

    RWFunctor0    functor_;

};


template <class Mutex>
class RWTCallbackList0 : public RWTCallbackListBase<Mutex>
{

    typedef  RWTCallbackListBase<Mutex> BaseType;

public:
    // The type of mutex protecting the lists data.
    typedef  Mutex MutexType;

    // Constructs a callback list, using the given mutex
    // to protect the list's state.
    RWTCallbackList0(Mutex& mutex);

    // Destructor
    ~RWTCallbackList0(void);

    // Assignment operator
    //
    // NOTE: The mutex passed to the callback list constructor
    //       MUST be LOCKED by the user when this member is called!
    //
    //       The mutex of second will be locked in this operator to
    //       prevent updates during the assignment
    RWTCallbackList0<Mutex>&
    operator=(const RWTCallbackList0<Mutex>& second);

    // Adds an entry to the end of the callback list
    // Actually adds  an entry to the add list, whose entries
    // are in turn appended to the current list the next time
    // that either the callback list is invoked, or the update
    // method is explicitly called.
    //
    // NOTE: The mutex passed to the callback list constructor
    //       MUST be LOCKED by the user when this member is called!
    void
    add(const RWFunctor0& functor, RWCallbackScope scope);

    // Removes all entries from the callback list that contain the
    // specified functor.
    //       Adds an entry to the remove list, whose entries are used
    //       to identify entries to be removed from the current list.
    // NOTE: The mutex passed to the callback list constructor
    //       MUST be LOCKED when this member is called!
    void
    remove(const RWFunctor0& functor);

    // Acquires the mutex, updates the list, releases the mutex,
    // and for each callback entry in the list, starting at the front,
    // invokes the functor passing the specified data, and then
    // deletes the list entry if its scope is found to be RW_CALL_ONCE.
    //
    // NOTE: The mutex passed to the callback list constructor
    //       MUST be UNLOCKED when this member is called!
    void
    operator()(void);

    // Acquires the mutex, updates the current list from the
    // add and remove lists, and releases the mutex.
    void
    update(void);

private:

    // Copy constructor
    RWTCallbackList0(const RWTCallbackList0<Mutex>& second);

protected:

    RWTValSlist<RWCallbackElem0> addList_;
    RWTValSlist<RWCallbackElem0> removeList_;
    RWTValSlist<RWCallbackElem0> currentList_;

};


inline void
RWCallbackElem0::functor(const RWFunctor0& newFunctor)
{
    functor_ = newFunctor;
}

inline RWFunctor0
RWCallbackElem0::functor(void) const
{
    return functor_;
}

inline void
RWCallbackElem0::operator()(void)
{
    functor_();
}

inline bool
RWCallbackElem0::operator==(const RWCallbackElem0& second) const
{
    // Only compare functors and ignore the rest.
    return functor_ == second.functor_;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/list/RWTCallbackList0.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_list_RWTCallbackList0_h__
