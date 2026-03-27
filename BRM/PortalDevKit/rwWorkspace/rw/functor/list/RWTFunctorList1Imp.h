#ifndef __rw_functor_list_RWTFunctorList1Imp_h__
#define __rw_functor_list_RWTFunctorList1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTFunctorList1Imp.h#1 $
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
 * The body class for functor lists whose invocation takes one argument.
 *
 *************************************************************************/

#include <rw/functor/list/RWTCallbackList1.h>
#include <rw/functor/list/RWTCallbackListBase.h>
#include <rw/functor/list/RWTFunctorList1.h>
#include <rw/functor/list/pkgdefs.h>
#include <rw/functor/RWTFunctor1Imp.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class S1> class RWTFunctorList;

template <class S1>
class RWTFunctorList1Imp : public RWTFunctor1Imp<S1>
{

    typedef typename RWTFunctor1Imp<S1>::MutexType MutexType;

public:

    // Allows handle class access to the protected constructor,
    // this is necessary for the handle to be able to create
    // the body on the fly in its constructor.
    friend class RWTFunctorList1<S1>;

    // Destructor
    ~RWTFunctorList1Imp(void);

    // Adds functor to the list (actually to an add list
    // which is used to update the actual list at invocation
    // time, or when the update method is explicitly called).
    void
    add(const RWTFunctor1<S1>& functor, RWCallbackScope scope);

    // Removes functor from the list (actually adds it to
    // a remove list, which is used to update the actual
    // list at invocation time, or when the  update method is
    // explicitly called).
    void
    remove(const RWTFunctor1<S1>& functor);

    // Acquire the mutex, update the current list from the
    // add and remove lists, and release the mutex.
    void
    update(void);

    // Updates the actual list from the add and remove lists,
    // invokes all of the functors in the list, and removes
    // any which were added with the RW_CALL_ONCE flag.
    void
    run(S1 s1) const;

    // Creates a new list body instance
    // (ctor is private to force construction through
    // this interface which returns a handle, so that
    // users never deal directly with the body).
    static RWTFunctorList1<S1>
    make(void);

private:

    RWTFunctorList1Imp(const RWTFunctorList1Imp& second);

    RWTFunctorList1Imp&
    operator=(const RWTFunctorList1Imp& second);

protected:

    // Protected constructor not to be used by user.
    // Instead use the static make function above.
    RWTFunctorList1Imp(void);

    // Functors are held in a CallbackList.
    RWTCallbackList1<MutexType, S1>  list_;

    // A flag to catch attempts at re-entrance.
    bool isRunning;
};


template <class S1>
inline
RWTFunctorList1Imp<S1>::RWTFunctorList1Imp(void)
    : list_(RWTFunctor1Imp<S1>::mutex()), isRunning(false)
{
}

template <class S1>
inline
RWTFunctorList1Imp<S1>::~RWTFunctorList1Imp(void)
{
}

template <class S1>
inline RWTFunctorList1<S1>
RWTFunctorList1Imp<S1>::make(void)
{
    return new RWTFunctorList1Imp<S1>();
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/list/RWTFunctorList1Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_list_RWTFunctorList1Imp_h__
