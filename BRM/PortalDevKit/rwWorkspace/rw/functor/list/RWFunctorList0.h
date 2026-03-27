#ifndef __rw_functor_list_RWFunctorList0_h__
#define __rw_functor_list_RWFunctorList0_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWFunctorList0.h#1 $
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
 * The functor list class which is invoked with no caller arguments.
 *
 *************************************************************************/

#include <rw/functor/list/RWFunctorList0Imp.h>
#include <rw/functor/list/pkgdefs.h>
#include <rw/functor/RWFunctor0.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

/**
 * \ingroup functor_list
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTValSlist "RWTValSlist<RWTFunctor<void()>>" instead.
 *
 * \brief
 * Deprecated. A sequence of functors whose invocation takes no arguments.
 *
 * The RWFunctorList0 class is a sequence of functors whose invocation takes
 * no arguments.
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
 * #include <rw/functor/functor0.h>
 * #include <rw/functor/list/RWFunctorList0.h>
 *
 * void foo(int x)
 * {
 *     std::cout << "foo was called with " << x << std::endl;
 * }
 *
 * void bar()
 * {
 *     std::cout << "bar was called" << std::endl;
 * }
 *
 * int main()
 * {
 *     // create new functors
 *     RWFunctor0 fooFunctor = rwtMakeFunctor0(0, foo, 4);
 *     RWFunctor0 barFunctor = rwtMakeFunctor0(0, bar);
 *
 *     // create a new functor list
 *     RWFunctorList0 flist;
 *
 *     // add the functors to the list
 *     flist.add(fooFunctor, RW_CALL_REPEATEDLY);
 *     flist.add(barFunctor, RW_CALL_REPEATEDLY);
 *
 *     // invoke the list and see that both the functors are called
 *     flist();
 *
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * foo was called with 4
 * bar was called
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWTValSlist<RWTFunctor<void()> instead") RW_FUNCTOR_LIST_SYMBOLIC RWFunctorList0
    : public RWFunctor0
{

public:

    /**
     * Constructs an empty list instance.
     */
    RWFunctorList0(void);

    // Not part of the published interface.
    // Creates a new list instance from another list's representation.
    RWFunctorList0(RWFunctorList0Imp* functorImp);

    /**
     * Copy constructor. Creates a new list instance that shares its list
     * representation with \a second.
     */
    RWFunctorList0(const RWFunctorList0& second);

    /**
     * Destructor.
     */
    ~RWFunctorList0(void);

    /**
     * Assignment operator. Binds this list instance to representation of
     * list \a second.
     */
    RWFunctorList0&
    operator=(const RWFunctorList0& second);

    /**
     * Invokes the functor list. This includes updating the list with any
     * stored adds or removes, invoking each functor in the list, and
     * removing any functors that were added with the #RW_CALL_ONCE flag.
     *
     * \exception RWTHRInternalError
     * Thrown if more than one thread attempts to invoke the list at a time.
     */
    void
    operator()(void) const;

    /**
     * Adds the specified \a functor to the list. Duplicates are allowed in
     * the list. In such cases the functor is run once for each time it
     * appears in the list.
     *
     * The add request is stored until either the list is invoked, or the
     * update() method is called.
     */
    void
    add(const RWFunctor0& functor, RWCallbackScope scope);

    /**
     * Removes all entries from the list that contain the specified
     * \a functor.
     *
     * The remove request is stored until either the list is invoked, or the
     * update() method is called.
     */
    void
    remove(const RWFunctor0& functor);

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
    RWFunctorList0Imp&
    body(void) const;

};


inline RWFunctorList0Imp&
RWFunctorList0::body(void) const
{
    return (RWFunctorList0Imp&)RWFunctor0::body();
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_list_RWFunctorList0_h__
