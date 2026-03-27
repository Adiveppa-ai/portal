#ifndef __rw_thread_RWThreadAttribute_h__
#define __rw_thread_RWThreadAttribute_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadAttribute.h#1 $
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

  RWConcurrencyPolicy - enumerated thread concurrency generation policies.
  RWContentionScope - enumerated thread scheduling contention scope policies.
  RWInheritancePolicy - enumerated thread scheduling inheritance policies.
  RWPriority - typedef of platform-specific type used to represent priorities.
  RWSchedulingPolicy - enumerated thread scheduling policies.
  RWStartPolicy - enumerated thread start-up policies.

  RWThreadAttribute - Handle class of thread attributes object.

******************************************************************************/

#include <rw/thread/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

#if defined(RW_THR_THREAD_API_POSIX) || defined(DOXYGEN)
/**
 * \relates RWThreadAttribute
 *
 * The internal thread priority representation.
 *
 * \conditional
 * This type is used for build configurations based on POSIX threads.
 */
typedef int    RWPriority;
#endif

#if defined(RW_THR_THREAD_API_SOLARIS) || defined(DOXYGEN)
#  include <sys/types.h>
/**
 * \relates RWThreadAttribute
 *
 * The internal thread priority representation.
 *
 * \conditional
 * This type is used for build configurations based on Solaris threads.
 */
typedef pri_t  RWPriority;
#endif

#if defined(RW_THR_THREAD_API_WIN32) || defined(DOXYGEN)
/**
 * \relates RWThreadAttribute
 *
 * The internal thread priority representation.
 *
 * \conditional
 * This type is used for build configurations based on Win32 threads.
 */
typedef int    RWPriority;
#endif

/**
 * \ingroup threading_package
 *
 * #RWConcurrencyPolicy values describe whether new kernel threads are
 * created at each new thread creation.
 *
 * \sa
 * RWThreadAttribute
 */
enum RWConcurrencyPolicy {

    /**
     * The creation of a new thread does not force an increase in the
     * effective concurrency supplied by the threads system (no new kernel
     * threads are created).
     */
    RW_THR_NO_CHANGE,

    /**
     * The creation of a new thread does result in the creation of a new
     * kernel thread to support increased concurrency of execution for the
     * new thread.
     */
    RW_THR_INCREASE
};


/**
 * \ingroup threading_package
 *
 * #RWContentionScope values describe whether threads contend for processing
 * resources with other threads in the same process or other threads in the
 * system.
 *
 * \sa
 * RWThreadAttribute
 */
enum RWContentionScope {

    /**
     * Thread contends for processing resources with other threads in the
     * same process.
     */
    RW_THR_PROCESS_SCOPE,

    /**
     * Thread contends for processing resources with other processes in the
     * system.
     */
    RW_THR_SYSTEM_SCOPE
};


/**
 * \ingroup threading_package
 *
 * #RWInheritancePolicy values indicate whether default settings are
 * provided by the creating thread or the thread attribute.
 *
 * \sa
 * RWThreadAttribute
 */
enum RWInheritancePolicy {

    /**
     * The default scheduling policy, priority, and time-slice quantum are
     * inherited from the creating thread.
     */
    RW_THR_INHERIT,

    /**
     * The default scheduling policy, priority, and time-slice quantum are
     * provided by the thread attribute instance.
     */
    RW_THR_EXPLICIT
};


/**
 * \ingroup threading_package
 *
 * #RWSchedulingPolicy values determine the scheduling policy.
 *
 * \sa
 * RWThreadAttribute
 */
enum RWSchedulingPolicy {

    /**
     * A scheduling policy other than those listed below.
     */
    RW_THR_OTHER,


    /**
     * Time-sliced with unspecified adjustments.
     */
    RW_THR_TIME_SLICED,

    /**
     * Time-sliced with fixed priorities.
     */
    RW_THR_TIME_SLICED_FIXED,

    /**
     * Time-sliced with dynamic priorities and/or time-slice quantums.
     */
    RW_THR_TIME_SLICED_DYNAMIC,

    /**
     * No time slicing and fixed priorities.
     */
    RW_THR_PREEMPTIVE
};


/**
 * \ingroup threading_package
 *
 * Determines whether a thread is in an interrupted state or is ready to run
 * after the RWThread::start() operation is complete.
 *
 * \sa
 * RWThreadAttribute
 */
enum RWStartPolicy {

    /**
     * A newly created thread may run as soon as the RWThread::start()
     * operation is complete.
     */
    RW_THR_START_RUNNING,

    /**
     * A newly created thread is left in an interrupted state upon return
     * from the RWThread::start() invocation that created it. The thread
     * must be explicitly released from the interrupt before it will execute
     * the RWRunnable::run() method.
     */
    RW_THR_START_INTERRUPTED
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Forward references
class RW_THREAD_GLOBAL RWThreadAttributeImp;
class RW_THREAD_GLOBAL RWThreadAttribute;

/**
 * \ingroup threading_package
 *
 * \brief
 * Encapsulates a set of attributes that define or control thread scheduling
 * and stack allocation.
 *
 * Class RWThreadAttribute encapsulates a set of attributes that define or
 * control thread scheduling and stack allocation. By supplying an instance
 * of this class to a thread object such as an RWThread, you can configure
 * the behavior of each new thread that you create. You can also use an
 * RWThreadAttribute to retrieve the default values for the current
 * environment and query the current environment as to which attributes may
 * be legally retrieved and set under the current circumstances.
 *
 * This class also provides functions that query the minimum and maximum
 * allowable values for the various attributes. Please see the <em>Threads
 * Module User's Guide</em> and the <em>Threads Module Platform User's
 * Guide</em> for a complete discussion of thread attributes.
 *
 * <h4>Public Member Functions (by group)</h4>
 * The bulk of the public member functions for this class are divided into
 * six groups:
 *   - The \c "canGetXxx" functions determine whether an attribute value can
 *   be read.
 *
 *   - The \c "canSetXxx" functions determine whether an attribute value can
 *   be set.
 *
 *   - The \c "getXxx" functions return an attribute value.
 *
 *   - The \c "isXxxSet" functions determine whether an attribute has
 *   maintained its previously set value.
 *
 *   - The \c "resetXxx" functions restore an attribute to its default
 *   setting.
 *
 *   - The \c "setXxx" functions set an attribute value.
 *
 * <h4>Feature Test Macros</h4>
 * The following macros, defined in \c rw/thread/RWThreadAttribute.h,
 * indicate whether the corresponding attribute is supported in the current
 * environment. If the macro is \e not defined, attempts to get or set the
 * corresponding attribute produce exceptions. If the macro \e is defined,
 * the current environment has some level of support for the attribute, and
 * \e may allow you to get or set the attribute value.
 *
 * - \b RW_THR_HAS_CONTENTION_SCOPE
 * - \b RW_THR_HAS_INHERITANCE_POLICY
 * - \b RW_THR_HAS_PRIORITY
 * - \b RW_THR_HAS_PROCESS_SCOPE_PRIORITY
 * - \b RW_THR_HAS_SCHEDULING_POLICY
 * - \b RW_THR_HAS_STACK_COMMIT_SIZE
 * - \b RW_THR_HAS_STACK_RESERVE_SIZE
 * - \b RW_THR_HAS_START_POLICY
 * - \b RW_THR_HAS_SYSTEM_SCOPE_PRIORITY
 * - \b RW_THR_HAS_TIME_SLICE_QUANTUM
 * - \b RW_THR_HAS_USER_STACK
 * - \b RW_THR_HAS_DUAL_PRIORITY -- This macro indicates when the underlying
 * system requires two priorities for threads with system contention scope:
 * one priority value for resolving system-level scheduling conflicts, and a
 * second priority value for resolving contention for synchronization
 * resources that are shared between threads in a process.
 *
 * - \b RW_THR_HAS_PARTIAL_STACK_COMMITMENT -- This macro indicates that the
 * underlying system allows partial stack commitment, meaning the stack
 * commit size may be set to a value less than the stack reserve size. If
 * this macro is not defined, then the stack reserve size and stack commit
 * size attributes are mutually exclusive and only one or the other may be
 * set.
 *
 * \example
 * \code
 * #include <rw/thread/RWRunnableSelf.h>
 * #include <rw/thread/RWThreadAttribute.h>
 * #include <rw/thread/RWThreadFunction.h>
 * #include <rw/thread/RWThreadSelf.h>
 *
 * void checkContentionScope(void)
 * {
 *     RWThreadSelf me = rwThread();
 *     // Was this thread created by a Threading package class?
 *     if (me.isValid()) {
 *
 *         // Get the attribute instance used to create the thread
 *         RWThreadAttribute attr = me.getActiveAttribute();
 *
 *         // Is the contention scope attribute available?
 *         if (attr.canGetContentionScope()) {
 *             // Yes, then get the scope used to create the thread
 *             RWContentionScope cscope = attr.getContentionScope();
 *
 *             switch (cscope) {
 *                 case RW_THR_PROCESS_SCOPE:
 *                     std::cout << "Process Scope" << std::endl;
 *                     break;
 *                 case RW_THR_SYSTEM_SCOPE:
 *                     std::cout << "System Scope" << std::endl;
 *                     break;
 *                 default:
 *                     std::cout << "Unexpected value for contention scope"
 *                               << std::endl;
 *             }
 *         }
 *         else {
 *             std::cout << "Contention scope is not supported" << std::endl;
 *         }
 *     }
 * }
 *
 * int main()
 * {
 *     RWThread t1 = RWThreadFunction::make(checkContentionScope);
 *     std::cout << "Default: " << std::flush;
 *     t1.start();
 *     t1.join();
 *
 *     RWThreadAttribute attr;
 *     // Is the desired contention scope policy supported?
 *     if (attr.canSetContentionScope(RW_THR_SYSTEM_SCOPE)) {
 *         attr.setContentionScope(RW_THR_SYSTEM_SCOPE);
 *     }
 *     else
 *         std::cout << "Unable to set contention scope to \"System\""
 *                   << std::endl;
 *     t1.setAttribute(attr);
 *     std::cout << "Set: " << std::flush;
 *     t1.start();
 *     t1.join();
 *
 *     attr.resetContentionScope();
 *     t1.setAttribute(attr);
 *     std::cout << "Reset: " << std::flush;
 *     t1.start();
 *     t1.join();
 *
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT (Solaris):
 * \code
 * Default: Process Scope
 * Set: System Scope
 * Reset: Process Scope
 * \endcode
 * \endexample
 *
 * \sa
 * RWThread, RWThreadSelf
 */
class RW_THREAD_GLOBAL RWThreadAttribute :
    public RWHandleBase
{

public:


    /**
     * Default constructor.
     */
    RWThreadAttribute();


    /**
     * Constructs a global static instance that is initialized upon first
     * use. If the object is used before this constructor is called, any set
     * values are not overridden.
     */
    RWThreadAttribute(RWStaticCtor);


    /**
     * Copy constructor.
     */
    RWThreadAttribute(const RWThreadAttribute& second);


    /**
     * Destructor.
     */
    ~RWThreadAttribute();


    /**
     * Assignment operator.
     */
    RWThreadAttribute&
    operator=(const RWThreadAttribute& second);


    /**
     * Copies the thread attribute values from \a second.
     */
    void
    copy(const RWThreadAttribute& second);


    /**
     * Tests the equality of self against \a second on a value by value
     * basis.
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    isEqual(const RWThreadAttribute& second) const;


    /**
     * Determines at runtime whether the value of the concurrency attribute
     * may be read. Returns \c false if the attribute is not supported in
     * the current environment, or if the function getConcurrencyPolicy()
     * cannot return a legal value under current circumstances.
     *
     * Returns \c true if the value of the concurrency attribute has not yet
     * been set using the function setConcurrencyPolicy(), indicating that a
     * default value is available and may be read.
     *
     * Always returns \c true if the concurrency attribute retains the value
     * defined by a previous call to setConcurrencyPolicy(). In this case,
     * the behavior is similar to that provided by the function
     * isConcurrencyPolicySet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetConcurrencyPolicy() const;

    /**
     * Determines at runtime whether the value of contention scope attribute
     * may be read. Returns \c false if the attribute is not supported in
     * the current environment, or if the function getContentionScope()
     * cannot return a legal value under current circumstances.
     *
     * Returns \c true if the value of the contention scope attribute has
     * not yet been set using the function setContentionScope(), indicating
     * that a default value is available and may be read.
     *
     * Always returns \c true if contention scope attribute retains the
     * value defined by a previous call to setContentionScope(). In this
     * case, the behavior is similar to that provided by the function
     * isContentionScopeSet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetContentionScope() const;

    /**
     * Determines at runtime whether the value of the inheritance attribute
     * may be read. Returns \c false if the attribute is not supported in
     * the current environment, or if the function getInheritancePolicy()
     * cannot return a legal value under current circumstances.
     *
     * Returns \c true if the value of the inheritance attribute has not yet
     * been set using the function setInheritancePolicy(), indicating that a
     * default value is available and may be read.
     *
     * Always returns \c true if the inheritance attribute retains the value
     * defined by a previous call to setInheritancePolicy(). In this case,
     * the behavior is similar to that provided by the function
     * isInheritancePolicySet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetInheritancePolicy() const;

    /**
     * Determines at runtime whether the value of the priority attribute may
     * be read. Returns \c false if the attribute is not supported in the
     * current environment, or if the function getPriority() cannot return a
     * legal value under current circumstances.
     *
     * Returns \c true if the value of the priority attribute has not yet
     * been set using the function setPriority(), indicating that a default
     * value is available and may be read.
     *
     * Always returns \c true if the priority attribute retains the value
     * defined by a previous call to setPriority(). In this case, the
     * behavior is similar to that provided by the function isPrioritySet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetPriority() const;

    /**
     * Determines at runtime whether the value of process scope attribute
     * may be read. Returns \c false if the attribute is not supported in
     * the current environment, or if the function getProcessScopePriority()
     * cannot return a legal value under current circumstances.
     *
     * Returns \c true if the value of the process scope attribute has not
     * yet been set using the function setProcessScopePriority(), indicating
     * that a default value is available and may be read.
     *
     * Always returns \c true if the process scope attribute retains the
     * value defined by a previous call to setProcessScopePriority(). In
     * this case, the behavior is similar to that provided by the function
     * isProcessScopePrioritySet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetProcessScopePriority() const;

    /**
     * Determines at runtime whether the value of the scheduling attribute
     * may be read. Returns \c false if the attribute is not supported in
     * the current environment, or if the function getSchedulingPolicy()
     * cannot return a legal value under current circumstances.
     *
     * Returns \c true if the value of the scheduling attribute has not yet
     * been set using the function setSchedulingPolicy(), indicating that a
     * default value is available and may be read.
     *
     * Always returns \c true if the scheduling attribute retains the value
     * defined by a previous call to setSchedulingPolicy(). In this case,
     * the behavior is similar to that provided by the function
     * isSchedulingPolicySet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetSchedulingPolicy() const;

    /**
     * Determines at runtime whether the value of the stack commit size
     * attribute may be read. Returns \c false if the attribute is not
     * supported in the current environment, or if the function
     * getStackCommitSize() cannot return a legal value under current
     * circumstances.
     *
     * Returns \c true if the value of the stack commit size attribute has
     * not yet been set using the function setStackCommitSize(), indicating
     * that a default value is available and may be read.
     *
     * Always returns \c true if the stack commit size attribute retains the
     * value defined by a previous call to setStackCommitSize(). In this
     * case, the behavior is similar to that provided by the function
     * isStackCommitSizeSet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetStackCommitSize() const;

    /**
     * Determines at runtime whether the value of the stack reserve size
     * attribute may be read. Returns \c false if the attribute is not
     * supported in the current environment, or if the function
     * getStackReserveSize() cannot return a legal value under current
     * circumstances.
     *
     * Returns \c true if the value of the stack reserve size attribute has
     * not yet been set using the function setStackReserveSize(), indicating
     * that a default value is available and may be read.
     *
     * Always returns \c true if stack reserve size attribute retains the
     * value defined by a previous call to the function
     * setStackReserveSize(). In this case, the behavior is similar to that
     * provided by the function isStackReserveSizeSet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetStackReserveSize() const;

    /**
     * Determines at runtime whether the value of the start attribute may be
     * read. Returns \c false if the attribute is not supported in the
     * current environment, or if the function getStartPolicy() cannot
     * return a legal value under current circumstances.
     *
     * Returns \c true if the value of the start attribute has not yet been
     * set using the function setStartPolicy(), indicating that a default
     * value is available and may be read.
     *
     * Always returns \c true if the start attribute retains the value
     * defined by a previous call to setStartPolicy(). In this case, the
     * behavior is similar to that provided by the function
     * isStartPolicySet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetStartPolicy() const;

    /**
     * Determines at runtime whether the value of the system scope priority
     * attribute may be read. Returns \c false if the attribute is not
     * supported in the current environment, or if the function
     * getSystemScopePriority() cannot return a legal value under current
     * circumstances.
     *
     * Returns \c true if the value of the system scope priority attribute
     * has not yet been set using the function setSystemScopePriority(),
     * indicating that a default value is available and may be read.
     *
     * Always returns \c true if the system scope priority attribute retains
     * the value defined by a previous call to the function
     * setSystemScopePriority(). In this case, the behavior is similar to
     * that provided by the function isSystemScopePrioritySet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetSystemScopePriority() const;

    /**
     * Determines at runtime whether the value of the time slice quantum
     * attribute may be read. Returns \c false if the attribute is not
     * supported in the current environment, or if the function
     * getTimeSliceQuantum() cannot return a legal value under current
     * circumstances.
     *
     * Returns \c true if the value of the time slice quantum attribute has
     * not yet been set using the function setTimeSliceQuantum(), indicating
     * that a default value is available and may be read.
     *
     * Always returns \c true if the time slice quantum attribute retains
     * the value defined by a previous call to setTimeSliceQuantum(). In
     * this case, the behavior is similar to that provided by the function
     * isTimeSliceQuantumSet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetTimeSliceQuantum() const;

    /**
     * Determines at runtime whether the value of the user stack attribute
     * may be read. Returns \c false if the attribute is not supported in
     * the current environment, or if the function getUserStackSize() cannot
     * return a legal value under current circumstances.
     *
     * Returns \c true if the value of the user stack attribute has not yet
     * been set using the function setUserStack(), indicating that a default
     * value is available and may be read.
     *
     * Always returns \c true if the user stack attribute retains the value
     * defined by a previous call to setUserStack(). In this case, the
     * behavior is similar to that provided by the function
     * isUserStackSet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetUserStack() const;

    /**
     * Determines at runtime whether the value of the stack guard size
     * attribute may be read. Returns \c false if the attribute is not
     * supported in the current environment, or if the function
     * getStackGuardSize() cannot return a legal value under current
     * circumstances.
     *
     * Returns \c true if the value of the stack guard size attribute has
     * not yet been set using the function setStackGuardSize(), indicating
     * that a default value is available and may be read.
     *
     * Always returns \c true if the stack guard size attribute retains the
     * value defined by a previous call to setStackGuardSize(). In this
     * case, the behavior is similar to that provided by the function
     * isStackGuardSizeSet().
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    canGetStackGuardSize() const;


    /**
     * Use the \c "getXxx()" functions to query the default value of an
     * attribute, if available, or the last value defined in a call to the
     * matching \c "setXxx()" function.
     *
     * These functions throw an RWTHROperationNotSupported exception if the
     * attribute is not supported in the current environment. They throw an
     * RWTHROperationNotAvailable exception if the corresponding attribute
     * is supported but has not yet been defined by a call to the matching
     * \c "setXxx()" function, and no default value is available under the
     * current circumstances. Other possible exceptions include
     * RWTHRInternalError.
     */
    RWConcurrencyPolicy
    getConcurrencyPolicy() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    RWContentionScope
    getContentionScope() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    RWInheritancePolicy
    getInheritancePolicy() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    RWPriority
    getPriority() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    RWPriority
    getProcessScopePriority() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    RWSchedulingPolicy
    getSchedulingPolicy() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    size_t
    getStackCommitSize() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    size_t
    getStackReserveSize() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    RWStartPolicy
    getStartPolicy() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    RWPriority
    getSystemScopePriority() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    unsigned long
    getTimeSliceQuantum() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    void*
    getUserStackAddress() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    size_t
    getUserStackSize() const;

    /**
     * \copydoc RWThreadAttribute::getConcurrencyPolicy() const
     */
    size_t
    getStackGuardSize() const;


    /**
     * The \c "isXxxSet()" functions determine whether the corresponding
     * attribute still has the value specified in an earlier call to the
     * matching \c "setXxx()" function.
     *
     * Each of these functions returns \c false if the corresponding
     * attribute is not supported in the current environment, has not yet
     * been set, or has been forced to another default value in response to
     * a change in a related attribute. Otherwise, returns \c true.
     *
     * Possible exceptions include RWTHRInternalError.
     */
    bool
    isConcurrencyPolicySet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isContentionScopeSet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isInheritancePolicySet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isPrioritySet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isProcessScopePrioritySet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isSchedulingPolicySet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isStackCommitSizeSet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isStackReserveSizeSet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isStartPolicySet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isSystemScopePrioritySet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isTimeSliceQuantumSet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isUserStackSet() const;

    /**
     * \copydoc RWThreadAttribute::isConcurrencyPolicySet() const
     */
    bool
    isStackGuardSizeSet() const;


    /**
     * The \c "canSetXxx()" functions determine, at runtime, whether the
     * corresponding attribute value may be set. Each of these functions
     * returns \c false if the corresponding attribute is not supported in
     * the current environment or if the specified policy, if any, is not
     * supported under the current circumstances. Otherwise, the function
     * returns \c true.
     *
     * All of these functions can throw an RWTHRInternalError exception. In
     * addition, those that take an argument can throw RWTHRBoundsError.
     */
    bool
    canSetConcurrencyPolicy(RWConcurrencyPolicy policy) const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetContentionScope(RWContentionScope scope) const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetInheritancePolicy(RWInheritancePolicy policy) const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetPriority() const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetProcessScopePriority() const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetSchedulingPolicy(RWSchedulingPolicy policy) const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetStackCommitSize() const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetStackReserveSize() const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetStartPolicy(RWStartPolicy policy) const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetSystemScopePriority() const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetTimeSliceQuantum() const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetUserStack() const;

    /**
     * \copydoc RWThreadAttribute::canSetConcurrencyPolicy()
     */
    bool
    canSetStackGuardSize() const;


    /**
     * Use the \c "setXxx()" functions to set the corresponding attribute.
     *
     * These functions throw the RWTHROperationNotSupported exception if the
     * attribute is not supported in the current environment. They throw the
     * RWTHROperationNotAvailable exception if the corresponding attribute
     * is supported, but the specified value is not supported under the
     * current circumstances. Other possible exceptions include
     * RWTHRBoundsError, RWTHROperationNotAvailable,
     * RWTHROperationNotSupported, and RWTHRInternalError.
     */
    void
    setConcurrencyPolicy(RWConcurrencyPolicy policy);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setContentionScope(RWContentionScope scope);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setInheritancePolicy(RWInheritancePolicy policy);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setPriority(RWPriority priority);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setProcessScopePriority(RWPriority priority);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setSchedulingPolicy(RWSchedulingPolicy policy);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setStackCommitSize(size_t size);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setStackReserveSize(size_t size);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setStartPolicy(RWStartPolicy policy);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setSystemScopePriority(RWPriority priority);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setTimeSliceQuantum(unsigned long milliseconds);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setUserStack(void* address, size_t size);

    /**
     * \copydoc RWThreadAttribute::setConcurrencyPolicy(RWConcurrencyPolicy)
     */
    void
    setStackGuardSize(size_t size);


    /**
     * The \c "resetXxx()" functions restore an attribute value to its
     * default setting, if any. These functions always succeed, even if the
     * target attribute is not supported in the current environment. Several
     * combinations of attributes and environments exist in which it is not
     * possible to query for a default value of an attribute. In these
     * cases, the functions simply clear any previous setting so that the
     * Threads Module relies instead on the underlying API to determine the
     * appropriate default value.
     *
     * Possible exceptions include RWTHRInternalError and
     * RWTHROperationNotSupported.
     */
    void
    resetConcurrencyPolicy();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetContentionScope();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetInheritancePolicy();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetPriority();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetProcessScopePriority();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetSchedulingPolicy();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetStackCommitSize();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetStackReserveSize();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetStartPolicy();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetSystemScopePriority();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetTimeSliceQuantum();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetUserStack();

    /**
     * \copydoc RWThreadAttribute::resetConcurrencyPolicy()
     */
    void
    resetStackGuardSize();

    /////////////////////////////////////////////////////////////////////////
    // The following functions may be used to determine the legal range
    // of values for various attributes.
    /////////////////////////////////////////////////////////////////////////

    /**
     * Use the \c "getXxx"() functions to determine the legal range of
     * values for various attributes.
     *
     * Can throw exceptions RWTHROperationNotSupported, RWTHRInternalError
     * and RWTHROperationNotAvailable.
     */
    RWPriority
    getMaxPriority() const;

    /**
     * \copydoc RWThreadAttribute::getMaxPriority() const
     */
    RWPriority
    getMaxProcessScopePriority() const;

    /**
     * \copydoc RWThreadAttribute::getMaxPriority() const
     */
    RWPriority
    getMaxSystemScopePriority() const;

    /**
     * \copydoc RWThreadAttribute::getMaxPriority() const
     */
    unsigned long
    getMaxTimeSliceQuantum() const;

    /**
     * \copydoc RWThreadAttribute::getMaxPriority() const
     */
    RWPriority
    getMinPriority() const;

    /**
     * \copydoc RWThreadAttribute::getMaxPriority() const
     */
    RWPriority
    getMinProcessScopePriority() const;

    /**
     * Use the \c "getXxx"() functions to determine the legal range of
     * values for various attributes.
     *
     * Can throw exceptions RWTHROperationNotSupported, RWTHRInternalError.
     */
    static
    size_t
    getMinStackSize();

    /**
     * \copydoc RWThreadAttribute::getMaxPriority() const
     */
    RWPriority
    getMinSystemScopePriority() const;

    /**
     * \copydoc RWThreadAttribute::getMaxPriority() const
     */
    unsigned long
    getMinTimeSliceQuantum() const;

protected:

    // Bind a new handle instance to a thread attribute instance
    RWThreadAttribute(RWThreadAttributeImp* imp);

    // Get a reference to the thread attribute instance, if any,
    // pointed-to by this handle instance, and if the handle is
    // undefined (because it was a static instance) then bind
    // this handle instance to a new default thread attribute instance
    // (this member was declared const even though it may change the
    //  handle instance - this eliminates the need to cast away const
    //  on the this pointer in all const interface members...)
    RWThreadAttributeImp&
    body(void) const;

};

/*****************************************************************************/

inline
RWThreadAttribute::RWThreadAttribute(RWStaticCtor)
    :
    RWHandleBase(RW_STATIC_CTOR)
{
}

inline
RWThreadAttribute::RWThreadAttribute(const RWThreadAttribute& second)
    :
    RWHandleBase(second)
{
}

inline
RWThreadAttribute::~RWThreadAttribute()
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWThreadAttribute&
RWThreadAttribute::operator=(const RWThreadAttribute& second)
{
    RWHandleBase::operator=(second);
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

#endif // __rw_thread_RWThreadAttribute_h__
