#ifndef __rw_thread_RWRunnableFunction_h__
#define __rw_thread_RWRunnableFunction_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableFunction.h#1 $
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

  RWRunnableFunction - Handle for RWRunnableFunctionImp instances.

******************************************************************************/

#include <rw/thread/RWRunnable.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/fwd.h>

/**
 * \ingroup threading_package
 *
 * \brief
 * Handle class for functor-based, \e runnable objects.
 *
 * The RWRunnableFunction class is a handle class for functor-based
 * \e runnable objects.
 *
 * A runnable object provides the basic mechanisms used to create, control,
 * and monitor the threads of execution within your application. Runnables
 * are used to define the task or activity to be performed by a thread.
 *
 * Each runnable object is reference-counted; a runnable body instance keeps
 * a count of the number of handles that currently reference it. A runnable
 * object is deleted when the last handle that references the body is
 * deleted.
 *
 * A functor-based runnable accepts a functor object for execution. A
 * functor is an object used to encapsulate a function call. Each functor
 * keeps a pointer to the function and copies of the argument values that
 * are to be passed to the function. Invoking a functor produces a call to
 * the function.
 *
 * A functor-based runnable simply redefines the basic \c run() member to
 * invoke a functor instance stored within the runnable. With this
 * capability, you do not have to resort to sub-classing or other intrusive
 * techniques to customize the execution behavior of a runnable. The
 * functor-based runnables allow you to dynamically specify the functions
 * you want to execute when a runnable is started.
 *
 * RWRunnableFunction is used to access a synchronous runnable, which
 * executes the specified functor in the same thread that calls start().
 *
 * \example
 * \code
 * #include <rw/functor/rwBind.h>
 * #include <rw/functor/RWTFunctor.h>
 * #include <rw/thread/RWRunnableFunction.h>
 *
 * void foo(int i)
 * {
 *     std::cout << i << std::endl;
 * }
 *
 * int main()
 * {
 *     // Create an RWRunnableFunction that calls foo.
 *     RWRunnableFunction runnablefunc =
 *         RWRunnableFunction::make(rwBind(foo, 7));
 *
 *     runnablefunc.start();   // prints 7
 *
 *     // Create a functor directly, passing 11 as client data.
 *     RWTFunctor<void()> functor = rwBind(foo, 11);
 *
 *     // Set runnablefunc to use the new functor:
 *     runnablefunc.setFunctor(functor);
 *
 *     runnablefunc.start();   // prints 11
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_THREAD_GLOBAL RWRunnableFunction :
    public RWRunnable
{

    friend class RWRunnableFunctionImp;
    friend class RWRunnableFunctionSelf;

public:


    /**
     * Constructs an empty RWRunnableFunction handle instance.
     */
    RWRunnableFunction();


    /**
     * Constructs a global static handle instance that may be assigned to
     * before construction. The static constructor does not change the
     * instance state.
     */
    RWRunnableFunction(RWStaticCtor);


    /**
     * Binds a new handle to the runnable instance, if any, pointed to by
     * the handle \a second.
     */
    RWRunnableFunction(const RWRunnableFunction& second);


    /**
     * Destructor.
     */
    ~RWRunnableFunction();


    /**
     * Binds \c this to the runnable instance, if any, pointed to by the
     * handle \a second.
     */
    RWRunnableFunction&
    operator=(const RWRunnableFunction& second);

    // Return an internal interface handle to the runnable object
    // pointed-to by an external interface handle (if any).
    RWRunnableFunctionSelf
    getRWRunnableFunctionSelf() const;


    /**
     * Constructs and returns an RWRunnableFunction object with an undefined
     * functor. The setFunctor() member must be used to define a functor
     * prior to starting.
     */
    static
    RWRunnableFunction
    make();


    /**
     * Constructs and returns an RWRunnableFunction that executes the
     * specified functor when started.
     */
    static
    RWRunnableFunction
    make(const RWTFunctor<void()>& functor);


    /**
     * Sets the functor to be executed by this runnable. Possible exceptions
     * include RWTHRInvalidPointer and RWTHRInternalError.
     */
    void
    setFunctor(const RWTFunctor<void()>& functor);


    /**
     * Gets the current functor instance, if any, associated with the
     * runnable. Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    RWTFunctor<void()>
    getFunctor() const;

protected:

    // Bind a new handle instance to a runnable instance
    RWRunnableFunction(RWRunnableFunctionImp* imp);

    // Bind an external interface handle instance to the RWRunnableImp
    // instance, if any, pointed-to by an internal handle instance
    RWRunnableFunction(const RWRunnableFunctionSelf& second);

    // Override the parent class body() function to provide
    // version that casts to this handle's body class
    RWRunnableFunctionImp&
    body(void) const;

};

/*****************************************************************************/

// Create an empty (invalid) external interface handle
inline
RWRunnableFunction::RWRunnableFunction()
{
}

// Create an empty (invalid) external interface handle
inline
RWRunnableFunction::RWRunnableFunction(RWStaticCtor)
    :
    RWRunnable(RW_STATIC_CTOR)
{
}

// Construct an external interface handle to the runnable object (if any)
// pointed-to by another external interface handle
inline
RWRunnableFunction::RWRunnableFunction(const RWRunnableFunction& second)
    :
    RWRunnable(second)
{
}

// Destroy an external interface handle
inline
RWRunnableFunction::~RWRunnableFunction()
{
}

// Bind this external interface handle to the runnable object (if any)
// pointed-to by a second external interface handle.
inline RWRunnableFunction&
RWRunnableFunction::operator=(const RWRunnableFunction& second)
{
    if (&second != this) {
        RWRunnable::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWRunnableFunction_h__
