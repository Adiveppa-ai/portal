#ifndef __rw_functor_list_RWTFunctorList2Imp_h__
#define __rw_functor_list_RWTFunctorList2Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTFunctorList2Imp.h#1 $
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

/**************************************************************************
 *
 * Description:
 *
 * The body class for functor lists whose invocation takes two arguments.
 *
 *************************************************************************/

#include <rw/functor/list/RWTCallbackList2.h>
#include <rw/functor/list/RWTCallbackListBase.h>
#include <rw/functor/list/RWTFunctorList2.h>
#include <rw/functor/list/pkgdefs.h>
#include <rw/functor/RWTFunctor2Imp.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class S1, class S2>
class RWTFunctorList2Imp : public RWTFunctor2Imp<S1, S2>
{

    typedef typename RWTFunctor2Imp<S1, S2>::MutexType MutexType;

public:

    // Allows handle class access to the protected constructor,
    // this is necessary for the handle to be able to create
    // the body on the fly in its constructor.
    friend class RWTFunctorList2<S1, S2>;

    // Destructor
    ~RWTFunctorList2Imp(void);

    // Adds functor to the list (actually to an add list
    // which is used to update the actual list at invocation
    // time, or when the update method is explicitly called).
    void
    add(const RWTFunctor2<S1, S2>& functor, RWCallbackScope scope);

    // Removes functor from the list (actually adds it to
    // a remove list, which is used to update the actual
    // list at invocation time, or when the  update method is
    // explicitly called).
    void
    remove(const RWTFunctor2<S1, S2>& functor);

    // Acquire the mutex, update the current list from the
    // add and remove lists, and release the mutex.
    void
    update(void);

    // Updates the actual list from the add and remove lists,
    // invokes all of the functors in the list, and removes
    // any which were added with the RW_CALL_ONCE flag.
    void
    run(S1 s1, S2 s2) const;

    // Creates a new list body instance
    // (ctor is private to force construction through
    // this interface which returns a handle, so that
    // users never deal directly with the body).
    static RWTFunctorList2<S1, S2> make(void);

private:

    RWTFunctorList2Imp(const RWTFunctorList2Imp& second);

    RWTFunctorList2Imp&
    operator=(const RWTFunctorList2Imp& second);

protected:

    // Protected constructor not to be used by user.
    // Instead use the static make function above.
    RWTFunctorList2Imp(void);

    // Functors are held in a CallbackList.
    RWTCallbackList2<MutexType, S1, S2>  list_;

    // A flag to catch attempts at re-entrance.
    bool isRunning;

};


template <class S1, class S2>
inline
RWTFunctorList2Imp<S1, S2>::RWTFunctorList2Imp(void)
    : list_(RWTFunctor2Imp<S1, S2>::mutex()), isRunning(false)
{
}

template <class S1, class S2>
inline RWTFunctorList2<S1, S2>
RWTFunctorList2Imp<S1, S2>::make(void)
{
    return new RWTFunctorList2Imp<S1, S2>();
}

template <class S1, class S2>
inline
RWTFunctorList2Imp<S1, S2>::~RWTFunctorList2Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/list/RWTFunctorList2Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_list_RWTFunctorList2Imp_h__
