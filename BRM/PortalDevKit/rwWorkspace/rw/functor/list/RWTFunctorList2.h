#ifndef __rw_functor_list_RWTFunctorList2_h__
#define __rw_functor_list_RWTFunctorList2_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTFunctorList2.h#1 $
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
 * The handle class for functor list bodies which are invoked with two
 * caller arguments
 *
 *************************************************************************/

#include <rw/functor/list/RWTCallbackListBase.h>
#include <rw/functor/list/pkgdefs.h>
#include <rw/functor/RWTFunctor2.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class S1, class S2> class RWTFunctorList2Imp;

/**
 * \ingroup functor_list
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTValSlist "RWTValSlist<RWTFunctor<void(S1, S2)>>" instead.
 *
 * \brief
 * Deprecated. A sequence of functors whose invocation takes two arguments.
 *
 * The RWTFunctorList2 class is a sequence of functors whose invocation
 * takes two arguments.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * function. When a functor is invoked, it calls the associated function.
 *
 * A functor list is a sequence of such functors. The list's invocation
 * results in the invocation of all functors contained in the list. This is
 * useful when you wish to connect more that one invocation to a particular
 * action.
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/functor/rwtMakeFunctor2.h>
 * #include <rw/functor/list/RWTFunctorList2.h>
 *
 * void foo(int x, short y)
 * {
 *     std::cout << "x is " << x << " and y is " << y << std::endl;
 * }
 *
 * void bar(int a, short b)
 * {
 *     std::cout << "a is " << a << " and b is " << b << std::endl;
 * }
 *
 * int main()
 * {
 *     // create new functors
 *     RWTFunctor2<int, short> fooFunctor =
 *             rwtMakeFunctor2((void(*)(int, short))0, foo);
 *     RWTFunctor2<int, short> barFunctor =
 *             rwtMakeFunctor2((void(*)(int, short))0, bar);
 *
 *     // create a new functor list
 *     RWTFunctorList2<int, short> flist;
 *
 *     // add the functors to the list
 *     flist.add(fooFunctor, RW_CALL_REPEATEDLY);
 *     flist.add(barFunctor, RW_CALL_REPEATEDLY);
 *
 *     // invoke the list and see that both the functors are called
 *     flist(3, 45);
 *
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * x is 3 and y is 45
 * a is 3 and b is 45
 * \endcode
 * \endexample
 */
template <class S1, class S2 >
class RW_DEPRECATE_TYPE("Use RWTValSlist<RWTFunctor<void(S1, S2)> instead") RWTFunctorList2
    : public RWTFunctor2<S1, S2>
{

public:

    /**
     * Constructs an empty list instance.
     */
    RWTFunctorList2(void);

    // Not part of the published interface.
    // Creates a new list instance from another list's representation.
    RWTFunctorList2(RWTFunctorList2Imp<S1, S2>* functorImp);

    /**
     * Copy constructor. Creates a new list instance that shares its list
     * representation with \a second.
     */
    RWTFunctorList2(const RWTFunctorList2<S1, S2>& second);

    /**
     * Destructor.
     */
    ~RWTFunctorList2(void);

    /**
     * Assignment operator. Binds this list instance to representation of
     * list \a second.
     */
    RWTFunctorList2<S1, S2>&
    operator=(const RWTFunctorList2<S1, S2>& second);

    /**
     * Invokes the functor list. This includes updating the list with any
     * stored adds or removes, invoking each functor in the list, and
     * removing any functors that were added with the #RW_CALL_ONCE flag.
     *
     * If more than one thread attempts to invoke the list at any one time,
     * throws an RWTHRInternalError exception.
     */
    void
    operator()(S1 s1, S2 s2) const;

    /**
     * Adds the specified \a functor to the list. Duplicates are allowed, in
     * which case the functor is run each time it appears.
     *
     * The add request is stored until either the list is invoked, or the
     * update() method is called.
     */
    void
    add(const RWTFunctor2<S1, S2>& functor, RWCallbackScope scope);

    /**
     * Removes all entries from the list for the specified \a functor.
     *
     * The remove request is stored until either the list is invoked, or the
     * update() method is called.
     */
    void
    remove(const RWTFunctor2<S1, S2>& functor);

    /**
     * Updates the list with any add() or remove() requests that have
     * occurred since the last invocation.
     */
    void
    update(void);

    // Not part of the published interface.
    // Gets a reference to the list body instance
    // pointed-to by this handle instance.
    // Documented in base class.
    RWTFunctorList2Imp<S1, S2>&
    body(void) const;

};

template <class S1, class S2>
inline
RWTFunctorList2<S1, S2>::RWTFunctorList2(RWTFunctorList2Imp<S1, S2>* functorImp)
    : RWTFunctor2<S1, S2>(functorImp)
{
}

template <class S1, class S2>
inline
RWTFunctorList2<S1, S2>::RWTFunctorList2(const RWTFunctorList2<S1, S2>& second)
    : RWTFunctor2<S1, S2>(second)
{
}

template <class S1, class S2>
inline
RWTFunctorList2<S1, S2>::~RWTFunctorList2(void)
{
}

template <class S1, class S2>
inline RWTFunctorList2<S1, S2>&
RWTFunctorList2<S1, S2>::operator=(const RWTFunctorList2<S1, S2>& second)
{
    if (&second != this) {
        RWTFunctor2<S1, S2>::operator=(second);
    }
    return *this;
}

template <class S1, class S2>
inline RWTFunctorList2Imp<S1, S2>&
RWTFunctorList2<S1, S2>::body(void) const
{
    return (RWTFunctorList2Imp<S1, S2>&)RWTFunctor2<S1, S2>::body();
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/list/RWTFunctorList2.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_list_RWTFunctorList2_h__
