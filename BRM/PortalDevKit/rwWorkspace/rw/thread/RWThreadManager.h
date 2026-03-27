#ifndef __rw_thread_RWThreadManager_h__
#define __rw_thread_RWThreadManager_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadManager.h#1 $
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

  RWThreadManager - Counted pointer handle for RWThreadManagerImp instance.

  rwThreadManager - Returns a pointer to singleton RWThreadManagerImp.  A
                    call to this function may result in the construction of
                    the thread manager if it has not yet been created.

******************************************************************************/

#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/tvhdict.h>

/**
 * \ingroup threading_package
 *
 * \brief
 * Attempts orderly thread shutdown at process exit.
 *
 * RWThreadManager attempts orderly thread shutdown at process exit.
 *
 * \note
 * This class uses reference semantics in which an instance of this class
 * represents a reference to an implementation class.
 */
class RW_THREAD_GLOBAL RWThreadManager
    : public RWHandleBase
{
    // Give RWThreadImp access to protected handle members
    friend class RWThreadImp;

public:

    /**
     * Constructs an empty, invalid handle instance.
     */
    RWThreadManager();


    /**
     * Constructor that creates a global static RWThreadManager handle
     * object that may be assigned to before it is constructed. This
     * constructor does not change the static instance.
     */
    RWThreadManager(RWStaticCtor);


    /**
     * Binds a new handle to the runnable instance, if any, pointed to by
     * the handle \a second.
     */
    RWThreadManager(const RWThreadManager& second);


    /**
     * Public destructor.
     */
    ~RWThreadManager();


    /**
     * Assignment operator. Binds the handle to the same threaded runnable,
     * if any, pointed to by \a second.
     */
    RWThreadManager&
    operator=(const RWThreadManager& second);

    // Delegated functions...


    /**
     * Allows the thread manager to clean up threads at program exit, but
     * before destruction of objects with static storage duration.
     */
    void
    enableEarlyShutdown();


    /**
     * Retrieves the number of milliseconds to wait for a thread to service
     * a cancellation request.
     */
    unsigned long
    getCancelTimeOut() const;

    // not documented
    RWThreadSelf
    getCurrentThread(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

#if defined(RW_THR_THREAD_API_SOLARIS) || defined(DOXYGEN)
    /**
     * \deprecated
     * As of SourcePro 13, thread termination is deprecated.
     *
     * Retrieves the signal to use to terminate a thread.
     *
     * \conditional
     * This function is available only when using Solaris threads.
     */
    RW_DEPRECATE_FUNC("")
    int
    getTerminationSignal() const;
#endif

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * Retrieves the value of the shutdown-enabled flag. If the flag is set,
     * the thread manager attempts to cancell all threads before the program
     * terminates.
     */
    bool
    getShutdownEnabled() const;


    /**
     * Creates and/or gets the current singleton thread manager instance.
     */
    static
    RWThreadManager
    instance();


    /**
     * Sets the number of milliseconds to wait for a thread to service a
     * cancellation request.
     */
    void
    setCancelTimeOut(unsigned long milliseconds);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

#if defined(RW_THR_THREAD_API_SOLARIS) || defined(DOXYGEN)
    /**
     * \deprecated
     * As of SourcePro 13, thread termination is deprecated.
     *
     * Sets the signal used to terminate threads.
     *
     * \conditional
     * This function is available only when using Solaris threads.
     */
    RW_DEPRECATE_FUNC("")
    void
    setTerminationSignal(int termSignal);
#endif

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * Sets the value of the shutdown-enabled flag. If the flag is set, the
     * thread manager attempts to cancel all threads before the program
     * terminates.
     */
    void
    setShutdownEnabled(bool shutdownEnabled);

    // not documented
    void
    shutdown(void);

protected:

    // Bind a new handle instance to a thread manager instance
    RWThreadManager(RWThreadManagerImp* imp);

    // Get a reference to the thread manager instance, if any,
    // pointed-to by this handle instance
    RWThreadManagerImp&
    body(void) const;

    // Deregister thread runnable instance (called by RWThreadImp)
    void
    deregisterThread(const RWThreadId& threadID);

    // Register thread runnable instance (called by RWThreadImp)
    void
    registerThread(const RWThreadId& threadID, RWThreadImp* imp);

protected:

    static RWMutexLock mutex_;
    static RWThreadManager instance_;
};


inline
RWThreadManager::~RWThreadManager()
{
}

/**
 * \relates RWThreadManager
 *
 * Creates and/or gets the current singleton thread manager instance. A call
 * to this function may result in the construction of the thread manager if
 * it has not yet been created.
 *
 * \sa
 * RWThreadManager, RWThreadManager::instance()
 */
extern RW_THREAD_SYMBOLIC
RWThreadManager
rwThreadManager();

#endif // __rw_thread_RWThreadManager_h__
