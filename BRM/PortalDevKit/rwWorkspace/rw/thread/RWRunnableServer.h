#ifndef __rw_thread_RWRunnableServer_h__
#define __rw_thread_RWRunnableServer_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableServer.h#1 $
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

#include <rw/thread/RWRunnable.h>
#include <rw/thread/RWRunnableGuard.h>
#include <rw/thread/RWRunnableServerImp.h>
#include <rw/thread/RWThread.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>

/**
 * \ingroup threading_package
 *
 * \brief
 * Represents a runnable server for executing runnable objects.
 *
 * The runnable server may be used alone, or within a class for an active
 * object class implementation. The runnable server object, when started,
 * waits for other threads to enqueue runnable objects for the server thread
 * to execute. Each runnable object that the server finds in its internal
 * queue is dequeued and started. The runnable server does not join with the
 * runnables it starts. The runnable server continues to dequeue runnables
 * and execute them until stopped, interrupted, or canceled.
 *
 * Runnables may be enqueued with a guard functor, or a priority value, or
 * both.
 *
 * The server uses the guard functor to determine whether the associated
 * runnable is currently eligible for retrieval and execution. A guarded
 * runnable is not retrieved by the server until that runnable is the first
 * runnable in the queue whose guard evaluates to \c true. Using guards to
 * block runnable execution is important when implementing active objects;
 * guards can be used to ensure that the active object maintains consistent
 * state and preserves any necessary invariants.
 *
 * The priority value is used during write operations to determine a
 * runnable's insertion point within the server's input queue, so that
 * unprocessed and eligible runnables are retrieved in priority order by the
 * server.
 *
 * The RWRunnable::requestCancellation() function should be used if the
 * server thread is to stop execution as soon as possible without dequeuing
 * and dispatching any additional runnables.
 *
 * The RWRunnable::requestInterrupt() function can be used to temporarily
 * suspend execution of the server thread.
 *
 * An active object implementation using this class defines a client
 * interface with member functions that simply produce "runnable functor"
 * objects (see RWRunnableFunction and RWTRunnableIOUFunction) which, when
 * invoked, execute some corresponding private or local member function
 * within the active object instance. The public members pass the runnable
 * functors to the server thread by calling the enqueue() member, which
 * stores the runnables in a queue. The client interface member function
 * then returns to its caller.
 *
 * Runnables that use IOUs can be used to represent a future return value or
 * result of the asynchronous active object operation. In this situation,
 * the client interface would create the appropriate IOU-capable runnable
 * object, enqueue the runnable for execution, retrieve the runnable's IOU
 * result, and return that IOU to the caller. The caller could then redeem
 * that IOU at some point in the future.
 *
 * \example
 * \code
 * #include <rw/thread/RWRunnable.h>
 * #include <rw/thread/RWRunnableFunction.h>
 * #include <rw/thread/RWRunnableServer.h>
 *
 * void function(void);
 *
 * RWRunnableServer runnableServer(RWRunnableServer::make());
 * RWRunnable runnable = RWRunnableFunction::make(function);
 *
 * runnableServer.start();
 * runnableServer.enqueue(runnable);
 * // ...
 * runnableServer.stop();
 * runnableServer.join();
 * \endcode
 *
 * The following is a skeleton of an active object class implemented using
 * an RWRunnableServer. For a complete active object example, refer to
 * \c activobj.cpp in the \c threxam directory.
 *
 * \code
 * class ActiveObject
 * {
 * public:
 *     // Starts runnable server.
 *     ActiveObject();
 *
 *     // Stops runnable server.
 *     ~ActiveObject(void);
 *
 *     // A function with no return. Creates and enqueues an
 *     // RWRunnableFunction, wrapping _func1();
 *     void func1(int arg1, int arg2, int arg3);
 *
 *     // A function with a return value. Creates and enqueues
 *     // an RWTRunnableIOUFunction, wrapping _func2();
 *     RWTIOUResult<int> func2(int arg1, int arg2, int arg3);
 *
 * private:
 *     // func1()'s better half
 *     void _func1(int arg1, int arg2, int arg3);
 *
 *     // func2()'s better half
 *     int _func2(int arg1, int arg2, int arg3);
 *
 *     // Guard functions called by RWRunnableGuard objects
 *     bool guard1Func();
 *     bool guard2Func();
 *
 *     // Runnable execution guards enqueued on
 *     // RWRunnableServer along with RWRunnable objects.
 *     RWRunnableGuard guard1_;
 *     RWRunnableGuard guard2_;
 *
 *     // The internal runnable server instance.
 *     RWRunnableServer runnableServer_;
 * };
 * \endcode
 * \endexample
 *
 * \sa
 * RWRunnable, RWThread, RWServerPool
 */
class RW_THREAD_GLOBAL RWRunnableServer :
    public RWThread
{

    friend class RWRunnableServerImp;
    friend class RWRunnableServerSelf;

public:


    /**
     * Constructs an empty, invalid, handle instance.
     */
    RWRunnableServer();


    /**
     * Constructs an external interface handle to the thread object pointed
     * to by handle \a second, if any.
     */
    RWRunnableServer(const RWRunnableServer& second);


    /**
     * Destructor.
     */
    ~RWRunnableServer();


    /**
     * Binds this external interface handle to the thread object pointed to
     * by handle \a second, if any.
     */
    RWRunnableServer&
    operator=(const RWRunnableServer& second);


    /**
     * Passes a runnable instance to the server for execution. All runnables
     * are inserted into an internal producer-consumer queue, where the
     * server retrieves them, one at a time, in priority order, and executes
     * them to completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns. If the server is running but its input queue is full, this
     * function blocks the calling thread until the input queue is no longer
     * full (because the server has removed a sufficient number of
     * runnables, or another thread has changed the maximum capacity of the
     * input queue) or until the server is stopped.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * This function takes the parameter \a runnable, which is a \c const
     * reference to an RWRunnable instance of the type used to instantiate
     * this template class.
     *
     * Runnables enqueued with this method are not guarded and are assigned
     * a priority value of zero.
     */
    void
    enqueue(const RWRunnable& runnable);


    /**
     * Passes a runnable instance to the server for execution. All runnables
     * are inserted into an internal producer-consumer queue, where the
     * server retrieves them, one at a time, in priority order, and executes
     * them to completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns #RW_THR_COMPLETED. If the server is running but its input
     * queue is full, this function blocks the calling thread until the
     * input queue is no longer full (because the server has removed a
     * sufficient number of runnables, or another thread has changed the
     * maximum capacity of the input queue), or until the server is stopped,
     * or until the specified amount of time passes. If the runnable cannot
     * be inserted in the input queue within the specified amount of time
     * provided in \a milliseconds, this function returns a value of
     * #RW_THR_TIMEOUT.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Parameters:
     * - The parameter \a runnable is a \c const reference to an RWRunnable
     * instance.
     * - The parameter \a milliseconds is an <tt>unsigned long</tt> value
     * that specifies the maximum number of milliseconds to wait for the
     * operation to complete.
     *
     * Runnables enqueued with this method are not guarded and are assigned
     * a priority value of zero.
     */
    RWWaitStatus
    enqueue(const RWRunnable& runnable, unsigned long milliseconds);


    /**
     * Passes a guarded runnable instance \a runnable to the server for
     * execution. All runnable are inserted into an internal
     * producer-consumer queue, where the server retrieves them, one at a
     * time, in priority order, and executes them to completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns. If the server is running but its input queue is full, this
     * function blocks the calling thread until the input queue is no longer
     * full (because the server has removed a sufficient number of
     * runnables, or another thread has changed the maximum capacity of the
     * input queue) or until the server is stopped.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Parameters:
     * - The parameter \a runnable is a \c const reference to an RWRunnable
     * instance.
     * - The parameter \a guard is a reference to an RWTFunctor<bool()>
     * functor instance that is invoked by the server thread to determine
     * whether the associated runnable is currently eligible for retrieval
     * from the input queue and execution. The server retrieves and executes
     * a runnable if its guard functor evaluates to \c true, and skips any
     * runnable whose guard functor evaluates to \c false, until a runnable
     * is found that can be executed. An empty functor handle indicates that
     * the entry is always eligible for execution. The functor must not
     * attempt to enqueue other runnables on the same server instance, as
     * such access results in deadlock.
     *
     * Runnables enqueued with this method are assigned a priority value of
     * zero.
     */
    void
    enqueue(const RWRunnable& runnable, const RWRunnableGuard& guard);


    /**
     * Passes a guarded runnable instance \a runnable to the server for
     * execution. All runnables are inserted into an internal
     * producer-consumer queue, where the server retrieves them, one at a
     * time, in priority order, and executes them to completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns #RW_THR_COMPLETED. If the server is running but its input
     * queue is full, this function blocks the calling thread until the
     * input queue is no longer full (because the server has removed a
     * sufficient number of runnables, or another thread has changed the
     * maximum capacity of the input queue), or until the server is stopped,
     * or until the specified amount of time passes. If the runnable cannot
     * be inserted in the input queue within the specified amount of time,
     * this function returns a value of #RW_THR_TIMEOUT.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Parameters:
     *
     * - The parameter \a runnable is a \c const reference to an RWRunnable
     * instance.
     *
     * - The parameter \a guard is a reference to an RWTFunctor<bool()>
     * functor instance that is invoked by the server thread to determine
     * whether the associated runnable is currently eligible for retrieval
     * from the input queue and execution. The server retrieves and executes
     * a runnable if its guard functor evaluates to \c true, and skips any
     * runnable whose guard functor evaluates to \c false, until a runnable
     * is found that can be executed. An empty functor handle indicates that
     * the entry is always eligible for execution. The functor must not
     * attempt to enqueue other runnables on the same server instance, as
     * such access results in deadlock.
     *
     * - The parameter \a milliseconds is an <tt>unsigned long</tt> value
     * that specifies the maximum number of milliseconds to wait for the
     * operation to complete.
     *
     * Runnables enqueued with this method are assigned a priority value of
     * zero.
     */
    RWWaitStatus
    enqueue(const RWRunnable& runnable, const RWRunnableGuard& guard, unsigned long milliseconds);


    /**
     * Passes a prioritized runnable instance to the server for execution.
     * All runnables are inserted into an internal producer-consumer queue,
     * where the server retrieves them, one at a time, in priority order,
     * and executes them to completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns. If the server is running but its input queue is full, this
     * function blocks the calling thread until the input queue is no longer
     * full (because the server has removed a sufficient number of
     * runnables, or another thread has changed the maximum capacity of the
     * input queue) or until the server is stopped.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Parameters:
     *
     * - The parameter \a priority is a \c long that is used to determine
     * the insertion point of the runnable within the server's input queue.
     * A runnable with a greater priority value is positioned to be read
     * before a runnable of lower priority. Runnables of equal priority are
     * positioned such that older runnables are executed before newer
     * runnables.
     *
     * - The parameter \a runnable is a \c const reference to an RWRunnable
     * instance.
     *
     * Runnables enqueued with this method are not guarded.
     */
    void
    enqueue(long priority, const RWRunnable& runnable);


    /**
     * Passes a prioritized runnable instance to the server for execution.
     * All runnables are inserted into an internal producer-consumer queue,
     * where the server retrieves them, one at a time, and executes them to
     * completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns #RW_THR_COMPLETED. If the server is running but its input
     * queue is full, this function blocks the calling thread until the
     * input queue is no longer full (because the server has removed a
     * sufficient number of runnables, or another thread has changed the
     * maximum capacity of the input queue), or until the server is stopped,
     * or until the specified amount of time passes. If the runnable cannot
     * inserted in the input queue within the specified amount of time, this
     * function returns a value of #RW_THR_TIMEOUT.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Parameters:
     *
     * - The parameter \a priority is a \c long that is used to determine
     * the insertion point of the runnable within the server's input queue.
     * A runnable with a greater priority value is positioned to be read
     * before a runnable of lower priority. Runnables of equal priority are
     * positioned such that older runnables are executed before newer
     * runnables.
     *
     * - The parameter \a runnable is a \c const reference to an RWRunnable
     * instance.
     *
     * - The parameter \a milliseconds is an <tt>unsigned long</tt> value
     * that specifies the maximum number of milliseconds to wait for the
     * operation to complete.
     *
     * Runnables enqueued with this method are not guarded.
     */
    RWWaitStatus
    enqueue(long priority, const RWRunnable& runnable, unsigned long milliseconds);


    /**
     * Passes a guarded and prioritized runnable instance to the server for
     * execution. All runnables are inserted into an internal
     * producer-consumer queue, where the server retrieves them, one at a
     * time, and executes them to completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns. If the server is running but its input queue is full, this
     * function blocks the calling thread until the input queue is no longer
     * full (because the server has removed a sufficient number of
     * runnables, or another thread has changed the maximum capacity of the
     * input queue) or until the server is stopped.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Parameters:
     *
     * - The parameter \a priority is a \c long that is used to determine
     * the insertion point of the runnable within the server's input queue.
     * A runnable with a greater priority value is positioned to be read
     * before a runnable of lower priority. Runnables of equal priority are
     * positioned such that older runnables are executed before newer
     * runnables.
     *
     * - The parameter \a runnable is a \c const reference to an RWRunnable
     * instance.
     *
     * - The parameter \a guard is a reference to an RWTFunctor<bool()>
     * functor instance that is invoked by the server thread to determine
     * whether the associated runnable is currently eligible for retrieval
     * from the input queue and execution. The server retrieves and executes
     * a runnable if its guard functor evaluates to \c true, and skips any
     * runnable whose guard functor evaluates to \c false, until a runnable
     * is found that can be executed. An empty functor handle indicates that
     * the entry is always eligible for execution. The functor must not
     * attempt to enqueue other runnables on the same server instance, as
     * such access results in deadlock.
     */
    void
    enqueue(long priority, const RWRunnable& runnable, const RWRunnableGuard& guard);


    /**
     * Passes a guarded and prioritized runnable instance to the server for
     * execution. All runnables are inserted into an internal
     * producer-consumer queue, where the server retrieves them, one at a
     * time, and executes them to completion.
     *
     * If the server is running and its input queue has sufficient capacity
     * to hold another runnable, this function inserts the runnable and
     * returns #RW_THR_COMPLETED. If the server is running but its input
     * queue is full, this function blocks the calling thread until the
     * input queue is no longer full (because the server has removed a
     * sufficient number of runnables, or another thread has changed the
     * maximum capacity of the input queue), or until the server is stopped,
     * or until the specified amount of time passes. If the runnable cannot
     * inserted in the input queue within the specified amount of time, this
     * function returns a value of #RW_THR_TIMEOUT.
     *
     * If the server is stopped while the calling thread is blocked and
     * waiting within this function for space in the input queue, the
     * calling thread is unblocked and the function returns by throwing an
     * RWTHRClosedException. If the server is already closed when this
     * function is called, the function immediately returns by throwing an
     * RWTHRClosedException.
     *
     * Parameters:
     *
     * - The parameter \a priority is a \c long that is used to determine
     * the insertion point of the runnable within the server's input queue.
     * A runnable with a greater priority value is positioned to be read
     * before a runnable of lower priority. Runnables of equal priority are
     * positioned such that older runnables are executed before newer
     * runnables.
     *
     * - The parameter \a runnable is a \c const reference to an RWRunnable
     * instance.
     *
     * - The parameter \a guard is a reference to an RWTFunctor<bool()>
     * functor instance that is invoked by the server thread to determine
     * whether the associated runnable is currently eligible for retrieval
     * from the input queue and execution. The server retrieves and executes
     * a runnable if whose guard functor evaluates to \c true, and skips any
     * runnable whose guard functor evaluates to \c false, until a runnable
     * is found that can be executed. An empty functor handle indicates that
     * the entry is always eligible for execution. The functor must not
     * attempt to enqueue other runnables on the same server instance, as
     * such access results in deadlock.
     *
     * - The parameter \a milliseconds is an <tt>unsigned long</tt> value
     * that specifies the maximum number of milliseconds to wait for the
     * operation to complete.
     */
    RWWaitStatus
    enqueue(long priority, const RWRunnable& runnable, const RWRunnableGuard& guard, unsigned long milliseconds);


    /**
     * Notifies all readers that a guard state may have changed, and that
     * all pending requests should be reevaluated.
     */
    void
    checkGuards();


    /**
     * Returns the maximum capacity of the server's input queue. A value of
     * zero indicates that the queue has no capacity limit.
     */
    size_t
    getCapacity() const;


    /**
     * Makes a runnable server.
     */
    static
    RWRunnableServer
    make();


    /**
     * Makes a runnable server instance with the specified thread
     * attributes.
     */
    static
    RWRunnableServer
    make(const RWThreadAttribute& serverThreadAttr);


    /**
     * Makes a runnable server whose input queue has the specified maximum
     * capacity.
     */
    static
    RWRunnableServer
    make(size_t maxCapacity);


    /**
     * Makes a runnable server instance with the specified thread attributes
     * whose input queue has the specified maximum capacity.
     */
    static
    RWRunnableServer
    make(const RWThreadAttribute& serverThreadAttr,
         size_t maxCapacity);


    /**
     * Sets the maximum capacity of the server's input queue. The maximum
     * capacity of the input queue determines the maximum number of
     * unprocessed entries allowed to accumulate within the input queue.
     * Once the number of entries equals or exceeds this number, any thread
     * attempting to enqueue another runnable is blocked until the server
     * removes a sufficient number of runnables from the queue, or until
     * another thread increases the capacity. A value of zero indicates that
     * the queue has no capacity limit. This function returns the maximum
     * capacity value that was in use before the call.
     */
    size_t
    setCapacity(size_t maxCapacity);


    /**
     * Requests that the server stop execution after it executes the
     * runnables that are currently enqueued. Any attempt to enqueue a
     * runnable after the server has been stopped, or before it has been
     * started, results in an RWTHRClosedException.
     */
    void
    stop();

protected:


    /**
     * \internal
     *
     * Constructs an external interface handle to an RWRunnableServerImp
     * instance.
     */
    RWRunnableServer(RWRunnableServerImp* threadImpP);

    // Override the parent class body() function to provide
    // version that casts to this handle's body class
    RWRunnableServerImp&
    body(void) const;
};

/*****************************************************************************/

inline
RWRunnableServer::RWRunnableServer()
{
}

inline
RWRunnableServer::RWRunnableServer(RWRunnableServerImp* imp)
    :
    RWThread((RWThreadImp*)imp)
{
}

inline
RWRunnableServer::RWRunnableServer(const RWRunnableServer& second)
    :
    RWThread(second)
{
}

inline
RWRunnableServer::~RWRunnableServer()
{
}

inline RWRunnableServer&
RWRunnableServer::operator=(const RWRunnableServer& second)
{
    if (&second != this) {
        RWThread::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWRunnableServer_h__
