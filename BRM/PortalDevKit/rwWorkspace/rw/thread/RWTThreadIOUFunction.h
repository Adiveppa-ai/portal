#ifndef __rw_thread_RWTThreadIOUFunction_h__
#define __rw_thread_RWTThreadIOUFunction_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTThreadIOUFunction.h#1 $
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

#include <rw/thread/RWThread.h>
#include <rw/thread/pkgdefs.h>
#include <rw/itc/fwd.h>
#include <rw/functor/fwd.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWThreadIOUFunction RWTThreadIOUFunction
#endif

/**
 * \ingroup threading_package
 *
 * \brief
 * Handle class for functor-based threaded runnable objects.
 *
 * The RWTThreadIOUFunction class is a handle class for functor-based
 * <em>threaded runnable</em> objects.
 *
 * A runnable object provides the basic mechanisms used to create, control,
 * and monitor the threads of execution within your application. Runnables
 * are used to define the task or activity to be performed by a thread.
 *
 * Each runnable object is reference-counted. A threaded runnable body
 * instance keeps a count of the number of handles that currently reference
 * it. A runnable object is deleted when the last handle that references the
 * body is deleted.
 *
 * A functor-based runnable accepts a functor object for execution. A
 * functor is an object used to encapsulate a function call. Each functor
 * keeps a pointer to the function and copies of the argument values that
 * are to be passed to the function. Invoking a functor produces a call to
 * the function, and in this case, a return value.
 *
 * A functor-based runnable simply redefines the basic \b run() member to
 * invoke a functor instance stored within the runnable. With this
 * capability, you do not have to resort to sub-classing or other intrusive
 * techniques to customize the execution behavior of a runnable. The
 * functor-based runnables allow you to dynamically specify the functions
 * you want to execute when a runnable is started.
 *
 * RWTThreadIOUFunction is used to access a threaded runnable, which creates
 * a new thread to execute the specified functor. The result of the functor
 * is returned in the form of an \e IOU. An IOU may be obtained as soon as
 * the runnable is created. To get the actual result from the IOU you must
 * \e redeem it. If the result has not yet been calculated, the calling
 * thread blocks until it has.
 *
 * \example
 * \code
 * #include <iostream>
 * #include <math.h>
 * #include <rw/functor/rwBind.h>
 * #include <rw/itc/RWTIOUResult.h>
 * #include <rw/thread/RWTThreadIOUFunction.h>
 *
 * int greatestPrime(int limit)
 * {
 *     // The sieve of Eratosthenes:
 *     int i, m;
 *     char* sieve = new char[limit + 1];
 *     if (sieve == 0) {
 *         return -1;    // not enough memory
 *     }
 *
 *     for (i = 0; i <= limit; ++i) {
 *         sieve[i] = 1;
 *     }
 *     for (i = 2; i <= sqrt((double)limit); ++i) {
 *         if (sieve[i] != 0) {
 *             for (m = i + i; m <= limit; m += i) {
 *                 sieve[m] = 0;
 *             }
 *         }
 *     }
 *
 *     // Return the greatest prime less than or equal to limit:
 *     for (i = limit; i >= 2; --i) {
 *         if (sieve[i] != 0) {
 *             return i;
 *         }
 *     }
 *     return 0;
 * }
 *
 * int main()
 * {
 *     RWTThreadIOUFunction<int> lastprime
 *         = RWTThreadIOUFunction<int>::make(rwBind(greatestPrime, 6000000));
 *
 *     lastprime.start();  // spawn thread to calculate big prime
 *     RWTIOUResult<int> answer = lastprime.result();  // get an IOU
 *
 *     // While the thread is busy calculating, print this
 *     // suspenseful message to keep the user entertained:
 *     std::cout << "The greatest prime less than six million is... "
 *               << std::flush;
 *
 *     // Block until the answer has been calculated and
 *     // then print it:
 *     std::cout << answer.redeem() << std::endl;
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * The greatest prime less than six million is... 5999993
 * \endcode
 * \endexample
 *
 * \sa
 * RWTFunctor, RWThread, RWRunnable, RWRunnableHandle, RWThreadAttribute
 */
template <class Return>
class RWTThreadIOUFunction :
    public RWThread
{

public:


    /**
     * Constructs an empty RWTThreadIOUFunction handle instance.
     */
    RWTThreadIOUFunction();


    /**
     * Binds a new handle to the runnable instance, if any, pointed to by
     * the handle \a second.
     */
    RWTThreadIOUFunction(const RWTThreadIOUFunction<Return>& second);


    /**
     * Destructor.
     */
    ~RWTThreadIOUFunction();


    /**
     * Binds \c this to the runnable instance, if any, pointed to by the
     * handle \a second.
     */
    RWTThreadIOUFunction<Return>&
    operator=(const RWTThreadIOUFunction<Return>& second);


    /**
     * Returns the IOU that will receive the result of the function.
     */
    RWTIOUResult<Return>
    operator()() const;


    /**
     * Gets the current functor instance, if any, associated with the
     * runnable. Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    RWTFunctor<Return()>
    getFunctor() const;


    /**
     * Constructs and returns an RWTThreadIOUFunction object with an
     * undefined functor. The setFunctor() member must be used to define a
     * functor prior to starting.
     */
    static
    RWTThreadIOUFunction<Return>
    make();


    /**
     * Constructs and returns an RWTThreadIOUFunction that executes the
     * specified functor when started.
     */
    static
    RWTThreadIOUFunction<Return>
    make(const RWTFunctor<Return()>& functor);


    /**
     * Constructs and returns an RWTThreadIOUFunction that executes the
     * specified functor when started, and places the functor result in
     * \a escrow.
     */
    static
    RWTThreadIOUFunction<Return>
    make(const RWTIOUEscrow<Return>& escrow,
         const RWTFunctor<Return()>& functor);


    /**
     * Constructs and returns an RWTThreadIOUFunction that executes the
     * specified \a functor when started. A new thread is created using the
     * attributes given by \a attr.
     */
    static
    RWTThreadIOUFunction<Return>
    make(const RWTFunctor<Return()>& functor,
         const RWThreadAttribute& attr);


    /**
     * Constructs and returns an RWTThreadIOUFunction that executes the
     * specified functor when started. A new thread is created using the
     * attributes given by \a attr, and the functor result is stored in
     * \a escrow.
     */
    static
    RWTThreadIOUFunction<Return>
    make(const RWTIOUEscrow<Return>& escrow,
         const RWTFunctor<Return()>& functor,
         const RWThreadAttribute& attr);


    /**
     * Returns the IOU that will receive the result of the function.
     */
    RWTIOUResult<Return>
    result() const;


    /**
     * Sets the functor to be executed by this runnable. Possible exceptions
     * include RWTHRInvalidPointer and RWTHRInternalError.
     */
    void
    setFunctor(const RWTFunctor<Return()>& functor);


    /**
     * Specifies an IOU escrow that is to receive the result of the
     * function. The new IOU is not used until the next time start() is
     * called. Each time an RWTThreadIOUFunction object is restarted, it
     * checks its current IOU escrow handle to see if it is valid, and if
     * so, checks to see whether the escrow has already been used to capture
     * a result or exception, or has been aborted. If the escrow object is
     * found to be in any of these "redeemable" states, a new escrow
     * instance is automatically created to capture the next result.
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    void
    setIOUEscrow(const RWTIOUEscrow<Return>& escrow);

protected:

    // Construct an external interface handle to a RWTThreadIOUFunctionImp
    // instance cast as a RWThreadImp* (to avoid a circular dependency between
    // the handle and the body template classes!)
    RWTThreadIOUFunction(RWThreadImp* imp);

};

/*****************************************************************************/

template <class Return>
inline
RWTThreadIOUFunction<Return>::RWTThreadIOUFunction()
{
}

template <class Return>
inline
RWTThreadIOUFunction<Return>::RWTThreadIOUFunction(const RWTThreadIOUFunction<Return>& second)
    :
    RWThread(second)
{
}

template <class Return>
// protected
inline
RWTThreadIOUFunction<Return>::RWTThreadIOUFunction(RWThreadImp* imp)
    :
    RWThread(imp)
{
}

template <class Return>
inline
RWTThreadIOUFunction<Return>::~RWTThreadIOUFunction()
{
}

template <class Return>
inline RWTThreadIOUFunction<Return>&
RWTThreadIOUFunction<Return>::operator=(const RWTThreadIOUFunction<Return>& second)
{
    if (&second != this) {
        RWThread::operator=(second);
    }
    return *this;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/thread/RWTThreadIOUFunction.cc>
#endif

#endif // __rw_thread_RWTThreadIOUFunction_h__
