#ifndef __rw_thread_RWThreadFunction_h__
#define __rw_thread_RWThreadFunction_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadFunction.h#1 $
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

  RWThreadFunction - Handle for RWThreadFunctionImp instances.

******************************************************************************/

#include <rw/thread/RWThread.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/fwd.h>

/**
 * \ingroup threading_package
 *
 * \brief
 * Handle class for functor-based threaded runnable objects.
 *
 * The RWThreadFunction class is a handle class for functor-based
 * <em>threaded runnable</em> objects.
 *
 * A runnable object provides the basic mechanisms used to create, control,
 * and monitor the threads of execution within your application. Runnables
 * are used to define the task or activity to be performed by a thread.
 *
 * Each runnable object is reference-counted; a threaded runnable body
 * instance keeps a count of the number of handles that currently reference
 * it. A runnable object is deleted when the last handle that references the
 * body is deleted.
 *
 * A functor-based runnable accepts a functor object for execution. A
 * functor is an object that encapsulates a function call. Each functor
 * keeps a pointer to the function and copies of the argument values that
 * are to be passed to the function. Invoking a functor produces a call to
 * the function.
 *
 * A functor-based runnable simply redefines the basic \b run() member to
 * invoke a functor instance stored within the runnable. With this
 * capability, you do not have to resort to sub-classing or other intrusive
 * techniques to customize the execution behavior of a runnable. The
 * functor-base runnables allow you to dynamically specify the functions you
 * want to execute when a runnable is started.
 *
 * RWThreadFunction is used to access a threaded runnable, which creates a
 * new thread to execute the specified functor.
 *
 * \example
 * \code
 * #include <rw/thread/RWThreadFunction.h>
 * #include <rw/functor/rwBind.h>
 * #include <rw/functor/RWTFunctor.h>
 *
 * void foo(int i)
 * {
 *     std::cout << i << std::endl;
 * }
 *
 * int main()
 * {
 *     // Create an RWThreadFunction that calls foo.
 *     RWThreadFunction threadfunc = RWThreadFunction::make(rwBind(foo, 7));
 *
 *     // Create a functor directly, passing 11 as client data.
 *     RWTFunctor<void()> functor = rwBind(foo, 11);
 *
 *     threadfunc.start();   // spawns a thread that prints 7
 *     threadfunc.join();
 *
 *     // Set threadfunc to use the new functor:
 *     threadfunc.setFunctor(functor);
 *
 *     threadfunc.start();   // spawns a thread that prints 11
 *     threadfunc.join();
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTFunctor, RWThread, rwBind
 */
class RW_THREAD_GLOBAL RWThreadFunction :
    public RWThread
{

    friend class RWThreadFunctionImp;
    friend class RWThreadFunctionSelf;

public:


    /**
     * Constructs an empty RWThreadFunction handle instance.
     */
    RWThreadFunction();


    /**
     * Binds a new handle to the runnable instance, if any, pointed to by
     * the handle \a second.
     */
    RWThreadFunction(const RWThreadFunction& second);


    /**
     * Destructor.
     */
    ~RWThreadFunction();


    /**
     * Binds \c this to the runnable instance, if any, pointed to by the
     * handle \a second.
     */
    RWThreadFunction&
    operator=(const RWThreadFunction& second);

    // Return an internal interface handle to the thread object
    // pointed-to by an external interface handle (if any).
    RWThreadFunctionSelf
    getRWThreadFunctionSelf() const;


    /**
     * Constructs and returns an RWThreadFunction object with an undefined
     * functor. The setFunctor() member must be used to define a functor
     * prior to starting.
     */
    static
    RWThreadFunction
    make();


    /**
     * Constructs and returns an RWRunnableFunction that executes the
     * specified \a functor when started.
     */
    static
    RWThreadFunction
    make(const RWTFunctor<void()>& functor);

    /**
     * Constructs and returns an RWRunnableFunction that executes the
     * specified functor when started. A new thread is created using the
     * thread attributes given by \a attr.
     */
    static
    RWThreadFunction
    make(const RWTFunctor<void()>& functor,
         const RWThreadAttribute& attr);


    /**
     * Constructs and returns an RWThreadFunction object with an undefined
     * functor. The setFunctor() member must be used to define a function
     * prior to starting. A new thread is created using the attributes given
     * by \a attr.
     */
    static
    RWThreadFunction
    make(const RWThreadAttribute& attr);


    /**
     * Sets the functor to be executed by this runnable.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    void
    setFunctor(const RWTFunctor<void()>& functor);


    /**
     * Gets the current functor instance, if any, associated with the
     * runnable.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    RWTFunctor<void()>
    getFunctor() const;

protected:

    // Construct an external interface handle to the RWThreadImp instance
    // pointed-to by a base class handle instance (if any)
    RWThreadFunction(RWThreadFunctionImp* imp);

    // Construct an external interface handle to the RWThreadImp
    // instance (if any) pointed-to by an internal interface handle
    RWThreadFunction(const RWThreadFunctionSelf& second);

    // Override the parent class body() function to provide
    // version that casts to this handle's body class
    RWThreadFunctionImp&
    body(void) const;
};

/*****************************************************************************/

inline
RWThreadFunction::RWThreadFunction()
{
}

inline
RWThreadFunction::RWThreadFunction(const RWThreadFunction& second)
    :
    RWThread(second)
{
}

inline
RWThreadFunction::~RWThreadFunction()
{
}

inline
RWThreadFunction&
RWThreadFunction::operator=(const RWThreadFunction& second)
{
    if (&second != this) {
        RWThread::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWThreadFunction_h__
