#ifndef __rw_thread_RWRunnableImp_h__
#define __rw_thread_RWRunnableImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableImp.h#1 $
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

  RWRunnableImp - Internal runnable implementation.

  RWRunnableImp is the abstract base class for all runnable objects.
  A "runnable" is an object that is used to control and manage threads,
  and also acts as the abstract representation of the "work" to be done
  by a thread.  A runnable object becomes "active" when its start() member
  is called.  If the runnable object is an instance of a derived class
  with synchronous behavior (such as provided by RWTFunctor<void()>), then
  the thread that calls start() effectively enters the runnable instance
  to become its active thread.  Only one thread may be active within a
  runnable instance at one time - the start() member will throw an
  exception if any thread attempts to call start while a thread is already
  executing "inside" of the runnable.  If the runnable object is an
  instance of a class derived from RWThreadImp (also a derivative of this
  class), then a call to start will result in the creation of a new thread
  of execution within the runnable, freeing the starting thread for other
  activities.  Runnable objects may be directly executed (as described
  above) or queued on a RWRunnableServer or RWServerPool instance
  for start-up and execution in a separate thread.

*****************************************************************************/

#include <rw/thread/RWRunnable.h>
#include <rw/thread/RWRunnableHandle.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/RWCallbackScope.h>
#include <rw/functor/fwd.h>
#include <rw/pointer/RWBodyBase.h>
#include <rw/pointer/RWTOnlyPointer.h>
#include <rw/sync/RWReadersWriterLock.h>
#include <rw/sync/RWSemaphore.h>
#include <rw/sync/RWThreadId.h>
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_THREAD_GLOBAL RWRunnableImp
    : public RWBodyBase // All runnables are reference counted
{

    friend class RWCancellationImp;

    friend class RWRunnableHandle;
    friend class RWRunnable;
    friend class RWRunnableSelf;

protected:

    // Helper class for storing registered callbacks and managing their invocation.
    class CallbackManager
    {
    public:
        // Constructs a callback manager, using the given mutex
        // to protect the callback list's state.
        CallbackManager(RWMutexLock& mutex);

        // Destructor
        ~CallbackManager();

        // Adds an entry to the end of the callback list.
        // The same functor may be added more than once with different
        // masks, but it is more efficient to install the functor once.
        //
        // Actually, adds an entry to the changeList_. currentList_ is
        // modified using entries in the changeList_ the next time the
        // callback list is invoked.
        //
        // NOTE: The mutex passed to the callback list constructor
        //       MUST be LOCKED by the caller when this member is called!
        void addCallback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor,
                         unsigned long mask, RWCallbackScope scope);

        // Removes all entries from the callback list that contain the
        // specified functor.
        //
        // Actually, adds an entry to the changeList_. currentList_ is
        // modified using entries in the changeList_ the next time the
        // callback list is invoked.
        //
        // NOTE: The mutex passed to the callback list constructor
        //       MUST be LOCKED when this member is called!
        void removeCallbacks(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor);

        // Acquires the mutex, updates the list, releases the mutex,
        // and for each callback entry in the list, starting at the front,
        // compares the entry's callback mask to the execution state,
        // and if there are any matching 1's, invokes the callback,
        // passing the specified data, and then deletes the list entry
        // if its scope is found to be RW_CALL_ONCE.
        //
        // NOTE: The mutex passed to the callback list constructor
        //       MUST be UNLOCKED when this member is called!
        void operator()(const RWRunnable& runnable, RWExecutionState exeState);

    private:
        // Helper struct to store all three attributes of a callback - functor, mask and scope.
        struct Callback {

            // Constructs a Callback from its three attributes.
            Callback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor,
                     unsigned long mask, RWCallbackScope scope);

            // Destructor
            ~Callback();

            // Equality operator compares just the functor, as removing
            // callbacks from the callback list is based only on the
            // functor comparison.
            // See RWRunnableImp::CallbackManager::removeCallbacks().
            bool operator==(const Callback& second) const;

            // Functor
            RWTFunctor<void(const RWRunnable&, RWExecutionState)> functor_;

            // Mask
            unsigned long mask_;

            // Scope
            RWCallbackScope scope_;
        };

        // Enumeration Action to indicate the action to be taken while updating
        // the callbacks_ list before next execution.
        enum CallbackChange { add, remove };

        // Acquires the mutex, updates the current list from the
        // add and remove lists, and releases the mutex.
        void updateCurrentList();

        // Mutex of the RWRunnable object
        RWMutexLock& mutex_;

        // List mask. Stores OR'd individual callback masks.
        unsigned long listMask_;

        // List of callbacks after the last execution of callbacks.
        RWTValSlist< Callback > currentList_;

        // List of all changes to be made to the callback list after
        // the last callback invocation.
        RWTValSlist< std::pair<Callback, CallbackChange> > changeList_;
    };

    // Pointer to CallbackManager object used to maintain callbacks
    // that are invoked in response to changes in execution state.  To reduce
    // the construction cost of RWRunnableImp objects, the callback manager is
    // not constructed until a request is made to add or remove a callback
    // from the runnable instance.
    RWTOnlyPointer< CallbackManager > callbackMgr_;

    // The completion status for this runnable (RW_THR_PENDING if still running)
    RWCompletionState completionState_;

    // The exception, if any, that cause this runnable to exit
    RWTOnlyPointer<RWTHRxmsg> exception_;

    // The current execution state of this runnable
    RWExecutionState executionState_;

    // Flag that indicates that this runnable is supposed to cancel
    bool isCanceled_;

    // Number of outstanding interrupt requests
    unsigned interruptCount_;

    // Handle to a nested runnable, if any, that is currently being
    // executed by the same thread that is executing within this runnable.
    // This field is used to link runnable object instances together for
    // purposes of thread control and to support queries for the current
    // runnable object associated with a thread (if any).
    RWRunnable nestedRunnable_;

    // Saved execution state (for temporary state changes)
    RWExecutionState savedExecutionState_;

    // RWReadersWriterLock to protect join() from returning during
    // a change of execution state to RW_THR_INITIAL.  join() acts
    // as a writer while the _setExecutionState() and
    // _restoreExecutionState() methods act as readers.
    RWReadersWriterLock joinLock_;

    // The id of this runnable's thread, if any.
    RWThreadId threadId_;


#if defined(RW_THR_CANT_NEST_PROTECTED_TEMPLATE)
public:
#endif

    // Define a helper class for use in signaling state
    // changes to interested threads.
    class MaskedSemaphore
    {

    private:
        // Semaphore used for signaling
        RWSemaphore       semaphore_;

        // Mask that identifies the desired state(s)

        unsigned long     mask_;
        // The state that matched the mask and resulted in the signal
        RWExecutionState  state_;

    public:
        // Construct a masked semaphore instance with mask
        MaskedSemaphore(unsigned long mask);

        // Do nothing destructor to keep stdlib happy...
        ~MaskedSemaphore(void);

        // Get the current execution state mask value
        unsigned long mask(void) const;

        // Get the execution state that matched the mask
        RWExecutionState state(void) const;

        // Set the execution state
        void state(RWExecutionState state);

        // Decrement (acquire) the semaphore, blocking while zero.
        void acquire(void);

        // Decrement (acquire) the semaphore, blocking while zero,
        // until unblocked when another thread increments (releases)
        // the semaphore or until the specified amount of time passes.
        RWWaitStatus acquire(unsigned long milliseconds);

        // Increment (release) the semaphore and unblock one waiting thread (if any)
        void release(void);

        // Try to decrement (acquire) semaphore without blocking
        // return true for success and false if the semaphore is zero.
        bool tryAcquire(void);
    };


#if defined(RW_THR_CANT_NEST_PROTECTED_TEMPLATE)
protected:
#endif

    // Define a list for threads waiting on execution state changes.
    RWTValSlist<MaskedSemaphore*> waiters_;

public:

    // Destroy runnable object (called by destructor of last handle instance)
    virtual
    ~RWRunnableImp(void);

protected:

    /////////////////////////////////////////////////////////////////////////
    //  The following functions may be accessed by any thread
    /////////////////////////////////////////////////////////////////////////

    // Add a callback to end of state-change callback list.  The mask
    // value is used to choose the runnable state or states for which
    // the callback is to be executed.  The scope argument determines
    // whether the callback is called just once or repeatedly.
    // Callbacks are called in FIFO order!
    void
    addCallback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor,
                unsigned long stateMask,
                RWCallbackScope scope = RW_CALL_REPEATEDLY);

    // Query for an active nested runnable (if any).
    // This function returns a reference to the runnable
    // object this runnable's thread is currently executing within.
    // If thread is only active within the current runnable,
    // then the handle returned will not point to any runnable
    // and will return false if tested by calling the isValid() member.
    RWRunnable
    getNestedRunnable(void) const;

    // Query the completion status of the runnable.
    RWCompletionState
    getCompletionState(void) const;

    // Query the current execution state of the runnable.
    RWExecutionState
    getExecutionState(void) const;

    // Query runnable to determine whether or not the runnable has an
    // outstanding request to interrupt.
    bool
    isInterruptRequested(void) const;

    // Indicates whether calling thread is the same thread that is
    // currently executing within this runnable...
    bool
    isSelf(void) const;

    // Indicates whether specified thread id refers to the thread
    // that is currently executing within this runnable...
    bool
    isSelf(const RWThreadId& id) const;

    // Remove all previously added callback entries that call the specified
    // functor.  This function locks the runnable object while removing the
    // callback and unlocks it when done.
    void
    removeCallback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor);

    // Query for the id of the thread currently active within the runnable.
    // The exception RWTHRThreadNotActive is thrown if there is not a thread
    // executing within the runnable.
    RWThreadId
    threadId(void) const;

    /////////////////////////////////////////////////////////////////////////
    //  The following functions may be accessed by any thread except
    //  the thread currently executing within the runnable instance.
    /////////////////////////////////////////////////////////////////////////

    // Wait for this runnable to complete execution.

    // Returns immediately if the runnable has already
    // been started and has completed and is currently inactive.

    // If the runnable object is going to be restarted, then this function
    // should be used with care by threads other than the thread starting
    // the runnable; user code will need to synchronize the thread(s)
    // starting the runnable with the thread(s) joining the runnable so
    // that joining threads will know which iteration they are joining!
    void
    join(void);

    // Wait for this runnable to complete execution or for the
    // specified time period to elapse.

    // Returns immediately if the runnable has already been started and
    // completed and is currently inactive.  Waits for the runnable to
    // complete if it has never been started, or if it has been started
    // and is currently active.

    // If the runnable object is going to be restarted, then this function
    // should be used with care by threads other than the thread starting
    // the runnable; user code will need to synchronize the thread(s)
    // starting the runnable with the thread(s) joining the runnable so
    // that joining threads will know which iteration they are joining!
    RWWaitStatus
    join(unsigned long milliseconds);

    // Force the exception, if any, produced during the execution of this
    // runnable to be rethrown.  This function simply returns if no
    // exception was produced during the most recently completed execution
    // of this runnable.
    void
    raise(void) const;

    // Release the thread executing with the runnable from an interrupt.
    void
    releaseInterrupt(void);

    // Request and wait for the runnable to cancel itself.
    // Returns:
    // RW_THR_COMPLETED
    //    To indicate that the runnable was canceled or was not active anyway
    // RW_THR_ABORTED
    //    To indicate that cancellation started, but did not complete.
    RWWaitStatus
    requestCancellation(void);

    // Request and wait for the runnable to cancel itself within the
    // specified time period.
    // Returns:
    // RW_THR_COMPLETED
    //    To indicate that the runnable was canceled or was not active anyway
    // RW_THR_ABORTED
    //    To indicate that cancellation started, but did not complete.
    // RW_THR_TIMEOUT
    //    To indicate that the runnable failed to complete cancellation within
    //    the specified time period.  The runnable may have started cancellation
    //    (the execution state may be RW_THR_CANCELING), but did not complete it
    //    within the specified time-out period.
    RWWaitStatus
    requestCancellation(unsigned long milliseconds);

    // Requests the thread executing within the runnable to interrupt and
    // waits until the thread is interrupted. To respond to the request
    // for an interrupt, the thread executing within the runnable must call
    // the serviceInterrupt() member.  If this member is called while there
    // is an outstanding request for an interrupt, the runnable thread is
    // blocked inside the serviceInterrupt() call until some other thread
    // releases the interrupt by calling releaseInterrupt();
    // This function returns:
    //    RW_THR_ACQUIRED - If the runnable *was* interrupted - a return
    //                      value of RW_THR_ACQUIRED does not guarantee
    //                      that the runnable is currently interrupted,
    //                      as any thread may release a runnable from an
    //                      interrupt, and the user may design an
    //                      application in such a manner that another
    //                      thread or callback is able to release the
    //                      interrupt before this function returns.
    //    RW_THR_ABORTED - If the runnable is not active
    RWWaitStatus
    requestInterrupt(void);

    // Same as previous function except the user may limit the time the
    // calling thread will wait for the runnable thread to interrupt.
    // Returns:
    //    RW_THR_ACQUIRED - If the runnable was interrupted (see prior
    //                      discussion above).
    //    RW_THR_TIMEOUT - If the runnable did not interrupt prior to the
    //                     expiration of the time-out interval
    //    RW_THR_ABORTED - If the runnable is not active
    RWWaitStatus
    requestInterrupt(unsigned long milliseconds);

    // Start execution of the runnable object.
    // For RWRunnableImp instances, this causes the calling thread to
    // execute synchronously "within" the runnable object.  For RWThreadImp
    // instances, start() results in the creation of a new thread of
    // execution that will execute "within" the runnable object.
    RWCompletionState
    start(void);

    // Waits until the runnable object enters an execution state referenced
    // by the mask.  It returns the execution state value that satisfied
    // the specified mask.
    RWExecutionState
    wait(unsigned long stateMask);

    // Waits until the runnable object enters a state contained in the
    // mask, or until the time-out period of milliseconds has elapsed.
    // If a masked state is entered prior to the expiration of the
    // time-out period, this member will write the state value that
    // satisfied the wait in the state argument location (if not rwnil),
    // and returns a value of RW_THR_SIGNALED.  If the time-out period
    // elapses without a state change that satisfies the mask, then
    // the function returns RW_THR_TIMEOUT without changing the
    // storage specified by the state argument.
    RWWaitStatus
    wait(unsigned long stateMask,
         RWExecutionState* state,
         unsigned long milliseconds);


    /////////////////////////////////////////////////////////////////////////
    //  The following functions may only be accessed by the thread
    //  currently executing within the runnable instance.
    /////////////////////////////////////////////////////////////////////////

    // Interrupts the calling thread executing within the runnable until
    // the runnable is released by another thread.
    void
    interrupt(void);

    // Checks for cancellation requests, throwing an RWCancellation object
    // if cancellation is requested, and returning if otherwise.
    void
    serviceCancellation(void);

    // Checks for interrupt requests, blocking the calling thread if an
    // interrupt has been requested and returning immediately if no
    // interrupt requests are pending.
    bool
    serviceInterrupt(void);

    // Causes the calling thread, executing within the runnable, to sleep
    // for the specified time period, yielding execution to other threads.
    void
    sleep(unsigned long milliseconds);

    // Causes the calling thread executing within the runnable to yield
    // execution to other threads.
    void
    yield(void);

    /////////////////////////////////////////////////////////////////////////
    //  The following functions are used internally or by derived classes.
    /////////////////////////////////////////////////////////////////////////

    // Construct a new runnable instance
    RWRunnableImp(void);

    // Construct a new runnable instance, but don't copy any members
    RWRunnableImp(const RWRunnableImp& second);

    // Assignment operator that doesn't copy anything
    RWRunnableImp&
    operator=(const RWRunnableImp& second);

    // Virtual method called by requestCancellation() members. Allows
    // derived classes define behavior to support cancellation requests.
    // A typical implementation might take some action to unblock the
    // the derived-class runnable so that it might check for cancellation.
    // The RWRunnable monitor mutex will be LOCKED upon entry.
    virtual
    void
    _checkCancellation(void);

    // Virtual method called by requestInterrupt() members. Allows
    // derived classes define behavior to support interrupt requests.
    // A typical implementation might take some action to unblock the
    // the derived-class runnable so that it might check for interrupt.
    // The RWRunnable monitor mutex will be LOCKED upon entry.
    virtual
    void
    _checkInterrupt(void);

    // Determines execution concurrency mechanism to use for running the
    // exec() member.
    // The RWRunnableImp implementation simply makes a synchronous call to
    // the exec() member.  RWThreadImp overrides this member to create
    // a thread that eventually calls the exec() member.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    virtual
    void
    _dispatchExec(void);

    // Perform setup, execution, and cleanup of the run() member
    // Catches any exceptions produced during execution of run().
    // This member should be called with the monitor mutex UNLOCKED!
    void
    exec(void);

    // Release the thread executing with the runnable from an interrupt.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    void
    _releaseInterrupt(void);

    // Internal version of requestCancellation(void) member.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry.
    virtual
    RWWaitStatus
    _requestCancellation(void);

    // Internal version of requestCancellation(unsigned long) member.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry.
    virtual
    RWWaitStatus
    _requestCancellation(unsigned long milliseconds);

    // Internal version of requestInterrupt(void) member.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex while waiting
    // for the interrupt and is therefore, NOT ATOMIC.
    RWWaitStatus
    _requestInterrupt(void);

    // Restores the execution state to the state that existed
    // prior to the last call to _setExecutionState(), notifying
    // waiting threads that the state has changed, and firing callbacks
    // whose mask matches the restored state.
    // This function expects the RWRunnable monitor mutex to be UNLOCKED
    // upon entry, and will lock and unlock the mutex internally.
    RWExecutionState
    restoreExecutionState(void);

    // Restores the execution state to the state that existed
    // prior to the last call to _setExecutionState(), notifying
    // waiting threads that the state has changed, and firing callbacks
    // whose mask matches the restored state.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    RWExecutionState
    _restoreExecutionState(void);

    // Function representing the work to be done by this runnable.
    // Must be overridden in derived classes (The default implementation
    // will produce an assert!).
    // This member should be called with the monitor mutex UNLOCKED!
    virtual
    void
    run(void);

    // Perform cleanup following execution of the virtual run() member.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    virtual
    void
    _runEpilog(void);

    // Perform setup prior execution of the virtual run() member.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    virtual
    void
    _runProlog(void);

    // Return a handle instance bound to the current RWRunnableImp instance
    RWRunnable
    self(void) const;

    // Checks for interrupt requests, blocking the calling thread if an
    // interrupt has been requested and returning immediately if no
    // interrupt requests are pending.  The function returns true if
    // the calling thread was interrupted, and false if otherwise.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    bool
    _serviceInterrupt(void);

    // Checks for cancellation requests, throwing an RWCancellation object
    // if cancellation is requested, and returning if otherwise.
    void
    _serviceCancellation(void);

    // Sets the execution state to the specified state, notifying
    // waiting threads that the state has changed, and firing callbacks
    // whose mask matches the new state.
    // This function expects the RWRunnable monitor mutex to be UNLOCKED
    // upon entry, and will lock and unlock the mutex internally.
    RWExecutionState
    setExecutionState(RWExecutionState newState);

    // Sets the execution state to the specified state, notifying
    // waiting threads that the state has changed, and firing callbacks
    // whose mask matches the new state.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    RWExecutionState
    _setExecutionState(RWExecutionState newState);

    // Register a single runnable object so that it might be notified
    // and serviced during cancellation.  This is done automatically when
    // a runnable is started by a thread created by a RWThreadImp or
    // derived class instance.
    bool
    setNestedRunnable(const RWRunnable&);

    // Signal any threads that are waiting for this runnable to
    // enter the current execution state.
    void
    _signalWaitingThreads(RWExecutionState newState);

    // Waits until the runnable object enters a state contained in the
    // mask. Returns the execution state value that ended the wait.
    // This function must be called with the monitor mutex LOCKED,
    // and the mutex will be unlocked while waiting for state changes,
    // so this function is NOT ATOMIC.
    RWExecutionState
    _wait(unsigned long stateMask);

    // Waits until the runnable object enters a state contained in the
    // mask, or until the time-out period of milliseconds has elapsed.
    // It returns the actual state value in the state argument, and
    // a return value of RW_THR_SIGNALED if a masked state was entered,
    // or RW_THR_TIMEOUT, if a masked state was not encountered within the
    // specified time period.
    // This function must be called with the monitor mutex LOCKED,
    // and the mutex will be unlocked while waiting for state changes,
    // so this function is NOT ATOMIC.
    RWWaitStatus
    _wait(unsigned long stateMask,
          RWExecutionState* state,
          unsigned long milliseconds);

private:

    // Used by the RWCancellationImp object to indicate that
    // cancellation was aborted (the cancellation object was destroyed).
    void
    abortCancellation(void);

    // Get a reference to the current CallbackManager instance, if there
    // is one, otherwise construct a CallbackManager object and then return
    // its reference.
    // This function must be called with the monitor mutex LOCKED,
    // and it does not unlock the mutex, so this function is ATOMIC.
    CallbackManager&
    _callbackMgr(void);

    // Common initialization for runnable object construction.
    // Locking is not required with this member as access to a runnable
    // under construction is assumed to be synchronized within user code.
    void
    init(void);

    // Called by the RWCancellationImp object to indicate that
    // cancellation has started.
    void
    initiateCancellation(void);

    // Invoke any callbacks associated with an execution state.
    // The runnable object must not be locked when this member is
    // called, as the runnable object will be locked and unlocked
    // as RWRunnable handles are copied during the callback invocation
    // process (and the callback code will probably want to access
    // the runnable object anyway!)
    // This function must be called with the monitor mutex LOCKED,
    // and the mutex will be unlocked and locked while updating the list,
    // then re-locked, so this function is NOT ATOMIC.
    void
    _invokeCallbacks(RWExecutionState state);

    // Test to see if we need to worry about callbacks
    // The CallbackManager object will not get constructed until a request
    // is made to install a callback on the current instance.
    // This function must be called with the monitor mutex LOCKED,
    // and it does not unlock the mutex, so this function is ATOMIC.
    bool
    _iscallbackMgr(void) const;

    // Restores the execution state to the state that existed
    // prior to the last call to _setExecutionState(), notifying
    // waiting threads that the state has changed, and firing callbacks
    // whose mask matches the restored state.
    // This function differs from _restoreExecutionState() in that it
    // does not acquire the joinLock_.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    RWExecutionState
    _restoreExecutionStateNoGuard(void);

    // Sets the execution state to the specified state, notifying
    // waiting threads that the state has changed, and firing callbacks
    // whose mask matches the new state.
    // This function differs from _setExecutionState() in that it does
    // not acquire the joinLock_.
    // This function expects the RWRunnable monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    RWExecutionState
    _setExecutionStateNoGuard(RWExecutionState newState);
};

/*****************************************************************************/

inline
RWRunnableImp::RWRunnableImp(const RWRunnableImp& second)
    : RWBodyBase(second)
{
}

inline RWRunnableImp&
RWRunnableImp::operator=(const RWRunnableImp& second)
{
    if (&second != this) {
        RWBodyBase::operator=(second);
    }
    return *this;
}

// Return a handle instance bound to the current RWRunnableImp instance
inline RWRunnable
RWRunnableImp::self(void) const
{
    return RWRunnable(const_cast <RWRunnableImp*>(this));
}

/*****************************************************************************/

inline
RWRunnableImp::CallbackManager::CallbackManager(RWMutexLock& mutex)
    : mutex_(mutex), listMask_(0)
{
}

inline
RWRunnableImp::CallbackManager::~CallbackManager()
{
}

inline void
RWRunnableImp::CallbackManager::addCallback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor,
        unsigned long mask, RWCallbackScope scope)
{
    RW_ASSERT(mutex_.isAcquired());
    changeList_.append(
        std::pair<Callback, CallbackChange>(Callback(functor, mask, scope), add));
}

inline void
RWRunnableImp::CallbackManager::removeCallbacks(
    const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor)
{
    RW_ASSERT(mutex_.isAcquired());
    changeList_.append(
        std::pair<Callback, CallbackChange>(Callback(functor, 0, RW_CALL_ONCE), remove));
}

/*****************************************************************************/

inline
RWRunnableImp::CallbackManager::Callback::Callback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor,
        unsigned long mask, RWCallbackScope scope)
    : functor_(functor), mask_(mask), scope_(scope)
{
}

inline
RWRunnableImp::CallbackManager::Callback::~Callback()
{
}

inline bool
RWRunnableImp::CallbackManager::Callback::operator==(const Callback& second) const
{
    return functor_ == second.functor_;
}

/*****************************************************************************/

inline
RWRunnableImp::MaskedSemaphore::MaskedSemaphore(unsigned long m)
    :
    semaphore_(0),
    mask_(m)
{
}

inline unsigned long
RWRunnableImp::MaskedSemaphore::mask(void) const
{
    return mask_;
}

inline RWExecutionState
RWRunnableImp::MaskedSemaphore::state(void) const
{
    return state_;
}

inline void
RWRunnableImp::MaskedSemaphore::state(RWExecutionState s)
{
    state_ = s;
}

inline void
RWRunnableImp::MaskedSemaphore::acquire(void)
{
    semaphore_.acquire();
}

inline RWWaitStatus
RWRunnableImp::MaskedSemaphore::acquire(unsigned long milliseconds)
{
    return semaphore_.acquire(milliseconds);
}

inline void
RWRunnableImp::MaskedSemaphore::release(void)
{
    semaphore_.release();
}

inline bool
RWRunnableImp::MaskedSemaphore::tryAcquire(void)
{
    return semaphore_.tryAcquire();
}

inline
RWRunnableImp::MaskedSemaphore::~MaskedSemaphore(void)
{
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWRunnableImp_h__
