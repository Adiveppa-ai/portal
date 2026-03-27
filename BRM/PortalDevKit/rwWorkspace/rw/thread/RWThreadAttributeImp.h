#ifndef __rw_thread_RWThreadAttributeImp_h__
#define __rw_thread_RWThreadAttributeImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadAttributeImp.h#1 $
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

  RWThreadAttributeImp - Internal RWThreadAttribute implementation

******************************************************************************/

#include <rw/thread/RWThreadAttribute.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/pointer/RWBodyBase.h>

class RW_THREAD_GLOBAL RWThreadAttributeImp
    : public RWBodyBase
{

    friend class RWThreadAttribute;

public:

    // Destructor
    ~RWThreadAttributeImp(void);

protected:

    unsigned                   attributeMask_;

#if defined(RW_THR_HAS_CONCURRENCY_POLICY)
    static const unsigned      CONCURRENCY_POLICY;
    RWConcurrencyPolicy        concurrencyPolicy_;
#endif

#if defined(RW_THR_HAS_CONTENTION_SCOPE)
    static const unsigned      CONTENTION_SCOPE;
    RWContentionScope          contentionScope_;
#endif

#if defined(RW_THR_HAS_INHERITANCE_POLICY)
    static const unsigned      INHERITANCE_POLICY;
    RWInheritancePolicy        inheritancePolicy_;
#endif

#if defined(RW_THR_HAS_PROCESS_SCOPE_PRIORITY)
    static const unsigned      PROCESS_SCOPE_PRIORITY;
    RWPriority                 processScopePriority_;
#endif

#if defined(RW_THR_HAS_SYSTEM_SCOPE_PRIORITY)
    static const unsigned      SYSTEM_SCOPE_PRIORITY;
    RWPriority                 systemScopePriority_;
#endif

#if defined(RW_THR_HAS_SCHEDULING_POLICY)
    static const unsigned      SCHEDULING_POLICY;
    RWSchedulingPolicy         schedulingPolicy_;
#endif

#if defined(RW_THR_HAS_STACK_COMMIT_SIZE)
    static const unsigned      STACK_COMMIT_SIZE;
    size_t                     stackCommitSize_;
#endif

#if defined(RW_THR_HAS_STACK_RESERVE_SIZE)
    static const unsigned      STACK_RESERVE_SIZE;
    size_t                     stackReserveSize_;
#endif

#if defined(RW_THR_HAS_START_POLICY)
    static const unsigned      START_POLICY;
    RWStartPolicy              startPolicy_;
#endif

#if defined(RW_THR_HAS_TIME_SLICE_QUANTUM)
    static const unsigned      TIME_SLICE_QUANTUM;
    unsigned long              timeSliceQuantum_;
#endif

#if defined(RW_THR_HAS_USER_STACK)
    static const unsigned      USER_STACK;
    void*                      userStackAddress_;
    size_t                     userStackSize_;
#endif

#if defined(RW_THR_HAS_STACK_GUARD_SIZE)
    static const unsigned      STACK_GUARD;
    size_t                     stackGuardSize_;
#endif

protected:

    // Prohibit direct construction (must use RWThreadAttribute)
    RWThreadAttributeImp(void);

    // Deadlock safe copy
    RWThreadAttributeImp(const RWThreadAttributeImp& second);

    // Deadlock safe assignment...
    RWThreadAttributeImp&
    operator=(const RWThreadAttributeImp& second);

    // Deadlock safe comparison...
    bool
    isEqual(const RWThreadAttributeImp& second) const;

    /////////////////////////////////////////////////////////////////////////
    // The "can get" test functions below can be used to determine at
    // run-time whether the corresponding attribute value may be read.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the corresponding
    // "get" function CANNOT return a legal value under current circumstances.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the corresponding "get"
    // function CAN return a legal value under current circumstances.
    //
    // If the corresponding attribute value has not yet be "set", then a
    // return value of true indicates that a default value is available and
    // may be read.
    //
    // These functions always return true if the corresponding attribute
    // still has the value previously defined by a call to the matching "set"
    // function.  In this case, the behavior is similar to that provided by
    // the "is set" functions (declared later).
    //
    // Some of these functions will throw the RWTHRInternalError exception if
    // some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    canGetConcurrencyPolicy(void) const;

    bool
    canGetContentionScope(void) const;

    bool
    canGetInheritancePolicy(void) const;

    bool
    canGetPriority(void) const;

    bool
    canGetProcessScopePriority(void) const;

    bool
    canGetSchedulingPolicy(void) const;

    bool
    canGetStackCommitSize(void) const;

    bool
    canGetStackReserveSize(void) const;

    bool
    canGetStartPolicy(void) const;

    bool
    canGetSystemScopePriority(void) const;

    bool
    canGetTimeSliceQuantum(void) const;

    bool
    canGetUserStack(void) const;

    bool
    canGetStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The public "get" functions below can be used to query the default
    // value of an attribute, if the attribute is not "set" and there is a
    // default value available, or the functions can be used to retrieve the
    // last value defined in a call to the matching "set" function.
    //
    // These functions will throw the RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw the RWTHROperationNotAvailable exception if
    // the corresponding attribute is supported, but has not yet been defined
    // by a call the the matching "set" function, and no default value is
    // available under the current circumstances.
    //
    // These functions will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    RWConcurrencyPolicy
    getConcurrencyPolicy(void) const;

    RWContentionScope
    getContentionScope(void) const;

    RWInheritancePolicy
    getInheritancePolicy(void) const;

    RWPriority
    getPriority(void) const;

    RWPriority
    getProcessScopePriority(void) const;

    RWSchedulingPolicy
    getSchedulingPolicy(void) const;

    size_t
    getStackCommitSize(void) const;

    size_t
    getStackReserveSize(void) const;

    RWStartPolicy
    getStartPolicy(void) const;

    RWPriority
    getSystemScopePriority(void) const;

    unsigned long
    getTimeSliceQuantum(void) const;

    void*
    getUserStackAddress(void) const;

    size_t
    getUserStackSize(void) const;

    size_t
    getStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The public "is set" test functions below can be used to determine
    // whether the corresponding attribute still has the value specified in
    // an earlier call the the matching "set" function.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment, has not yet been set, or
    // has been forced to some other default value in response to a change
    // in another related attribute.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment, has been set, has not
    // been reset, and has not forced to a default value as the result of a
    // change in a some related attribute.
    //
    // These functions will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    isConcurrencyPolicySet(void) const;

    bool
    isContentionScopeSet(void) const;

    bool
    isInheritancePolicySet(void) const;

    bool
    isPrioritySet(void) const;

    bool
    isProcessScopePrioritySet(void) const;

    bool
    isSchedulingPolicySet(void) const;

    bool
    isStackCommitSizeSet(void) const;

    bool
    isStackReserveSizeSet(void) const;

    bool
    isStartPolicySet(void) const;

    bool
    isSystemScopePrioritySet(void) const;

    bool
    isTimeSliceQuantumSet(void) const;

    bool
    isUserStackSet(void) const;

    bool
    isStackGuardSizeSet(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The public "can set" test functions below can be used to determine, at
    // run-time, whether the corresponding attribute value may be set.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the specified
    // policy, if any, is not supported under the current circumstances.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the specified policy is legal
    // under the current circumstances.
    //
    // Some of these functions will produce a RWTHRBoundsError exception if
    // the specified value is not a legal policy value for that attribute.
    // This exception can be avoided by making sure that you are using the
    // appropriate value names for enumerated attributes.
    //
    // Some of these functions will throw the RWTHRInternalError exception
    // if some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    canSetConcurrencyPolicy(RWConcurrencyPolicy policy) const;

    bool
    canSetContentionScope(RWContentionScope scope) const;

    bool
    canSetInheritancePolicy(RWInheritancePolicy policy) const;

    bool
    canSetPriority(void) const;

    bool
    canSetProcessScopePriority(void) const;

    bool
    canSetSchedulingPolicy(RWSchedulingPolicy policy) const;

    bool
    canSetStackCommitSize(void) const;

    bool
    canSetStackReserveSize(void) const;

    bool
    canSetStartPolicy(RWStartPolicy policy) const;

    bool
    canSetSystemScopePriority(void) const;

    bool
    canSetTimeSliceQuantum(void) const;

    bool
    canSetUserStack(void) const;

    bool
    canSetStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The public "set" functions below can be used to set the corresponding
    // attribute value.
    //
    // These functions will throw the RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw the RWTHROperationNotAvailable exception if
    // the corresponding attribute is supported, but the specified value is
    // not supported under the current circumstances.
    //
    // These functions will throw the RWTHRBoundsError exception if the
    // specified value is invalid or falls outside the current legal range
    // for that attribute.
    //
    // These functions will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    void
    setConcurrencyPolicy(RWConcurrencyPolicy policy);

    void
    setContentionScope(RWContentionScope scope);

    void
    setInheritancePolicy(RWInheritancePolicy policy);

    void
    setPriority(RWPriority priority);

    void
    setProcessScopePriority(RWPriority priority);

    void
    setSchedulingPolicy(RWSchedulingPolicy policy);

    void
    setStackCommitSize(size_t size);

    void
    setStackReserveSize(size_t size);

    void
    setStartPolicy(RWStartPolicy policy);

    void
    setSystemScopePriority(RWPriority priority);

    void
    setTimeSliceQuantum(unsigned long milliseconds);

    void
    setUserStack(void* address, size_t size);

    void
    setStackGuardSize(size_t size);

    /////////////////////////////////////////////////////////////////////////
    // The "reset" functions below can be used to restore an attribute value
    // to its default setting, if any.
    //
    // These functions will always succeed, even if the target attribute is
    // not supported in the current environment.
    //
    // There are several combinations of attributes and environments where it
    // is not possible to query for a default value of an attribute; using
    // these functions will simply clear any previous setting so that the
    // SourcePro Core - Threads Module will know to rely on the underlying
    // API to determine the appropriate default value.
    /////////////////////////////////////////////////////////////////////////

    void
    resetConcurrencyPolicy(void);

    void
    resetContentionScope(void);

    void
    resetInheritancePolicy(void);

    void
    resetPriority(void);

    void
    resetProcessScopePriority(void);

    void
    resetSchedulingPolicy(void);

    void
    resetStackCommitSize(void);

    void
    resetStackReserveSize(void);

    void
    resetStartPolicy(void);

    void
    resetSystemScopePriority(void);

    void
    resetTimeSliceQuantum(void);

    void
    resetUserStack(void);

    void
    resetStackGuardSize(void);

    /////////////////////////////////////////////////////////////////////////
    // The following functions may be used to determine the legal range
    // of values for various attributes.
    /////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
    // This function returns the maximum priority value supported by the
    // current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if the macro RW_THR_HAS_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not
    // use or support the priority attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetPriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    getMaxPriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This function returns the maximum process-scope priority value
    // supported by the current process-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if RW_THR_HAS_PROCESS_SCOPE_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_SYSTEM_SCOPE and the current
    // environment does not support dual priority values, as indicated by
    // the definition of the macro RW_THR_HAS_DUAL_PRIORITY, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetProcessScopePriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    getMaxProcessScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This function returns the maximum system-scope priority value
    // supported by the current system-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the system-scope priority attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_PROCESS_SCOPE, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetSystemScopePriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    getMaxSystemScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This function returns the maximum time-slice quantum value supported
    // by the current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the time-slice quantum attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_TIME_SLICE_QUANTUM is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not use or
    // support the time-slice quantum attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetTimeSliceQuantum() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    unsigned long
    getMaxTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This function returns the minimum priority value supported by the
    // current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if the macro RW_THR_HAS_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not
    // use or support the priority attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetPriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    getMinPriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This function returns the minimum process-scope priority value
    // supported by the current process-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if RW_THR_HAS_PROCESS_SCOPE_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_SYSTEM_SCOPE and the current
    // environment does not support dual priority values, as indicated by
    // the definition of the macro RW_THR_HAS_DUAL_PRIORITY, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetPriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    getMinProcessScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This static function returns the minimum stack size required to launch
    // a thread that calls a null function.  The Threads Module automatically
    // guarantees that the size of any stack allocated by the system will be
    // larger than this value.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if stack attributes are not supported. This exception can be
    // avoided by testing to see if either of the macros
    // RW_THR_HAS_STACK_RESERVE_SIZE or RW_THR_HAS_USER_STACK are currently
    // defined.
    //
    // These exceptions can be avoided by calling this function only when
    // either of the feature test functions, canSetStackReserveSize() or
    // canSetUserStack() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    static
    size_t
    getMinStackSize(void);

    /////////////////////////////////////////////////////////////////////////
    // This function returns the minimum system-scope priority value
    // supported by the current system-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the system-scope priority attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_PROCESS_SCOPE, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetSystemScopePriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    getMinSystemScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This function returns the minimum time-slice quantum value supported
    // by the current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the time-slice quantum attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_TIME_SLICE_QUANTUM is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not use or
    // support the time-slice quantum attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetTimeSliceQuantum() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    unsigned long
    getMinTimeSliceQuantum(void) const;

private:

    bool
    _isEqual(const RWThreadAttributeImp& second) const;

    void
    _copy(const RWThreadAttributeImp& second);

    /////////////////////////////////////////////////////////////////////////
    // The private "is inherited" functions below are used internally to
    // determine whether or not the corresponding attribute is to be
    // inherited.
    //
    // These functions return true if the corresponding attribute is to be
    // inherited, and false if the attribute is to be explicitly supplied.
    //
    // Some of these functions will throw the RWTHRInternalError exception if
    // some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _isPriorityInherited(void) const;

    bool
    _isProcessScopePriorityInherited(void) const;

    bool
    _isSystemScopePriorityInherited(void) const;

    bool
    _isSchedulingPolicyInherited(void) const;

    bool
    _isTimeSliceQuantumInherited(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "can get default" functions below are used internally to
    // indicate whether or not a default value for the corresponding
    // attribute is available under present circumstances.
    //
    // These functions return true if the default value for the corresponding
    // attribute is defined and available.
    //
    // These functions return false if the default value for the
    // corresponding attribute is not currently defined or available.
    //
    // Some of these functions will throw the RWTHRInternalError exception if
    // some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _canGetDefaultConcurrencyPolicy(void) const;

    bool
    _canGetDefaultContentionScope(void) const;

    bool
    _canGetDefaultInheritancePolicy(void) const;

    bool
    _canGetDefaultPriority(void) const;

    bool
    _canGetDefaultProcessScopePriority(void) const;

    bool
    _canGetDefaultSchedulingPolicy(void) const;

    bool
    _canGetDefaultStackCommitSize(void) const;

    bool
    _canGetDefaultStackReserveSize(void) const;

    bool
    _canGetDefaultStartPolicy(void) const;

    bool
    _canGetDefaultSystemScopePriority(void) const;

    bool
    _canGetDefaultTimeSliceQuantum(void) const;

    bool
    _canGetDefaultUserStack(void) const;

    bool
    _canGetDefaultStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "get default" functions below are used internally to get
    // the current default value of the corresponding attribute.
    //
    // These functions will return the default value for the corresponding
    // attribute.  The current default value for any attribute may depend
    // on the settings of other related attributes.
    // If the default value of that attribute cannot be provided, these
    // functions will fail with an assert in the debug version of the
    // library; these functions should NOT be called unless the corresponding
    // "can get default" function has indicated that a default value is
    // available.
    //
    // Some of these functions will throw the RWTHRInternalError exception if
    // some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    RWConcurrencyPolicy
    _getDefaultConcurrencyPolicy(void) const;

    RWContentionScope
    _getDefaultContentionScope(void) const;

    RWInheritancePolicy
    _getDefaultInheritancePolicy(void) const;

    RWPriority
    _getDefaultPriority(void) const;

    RWPriority
    _getDefaultProcessScopePriority(void) const;

    RWSchedulingPolicy
    _getDefaultSchedulingPolicy(void) const;

    size_t
    _getDefaultStackCommitSize(void) const;

    size_t
    _getDefaultStackReserveSize(void) const;

    RWStartPolicy
    _getDefaultStartPolicy(void) const;

    RWPriority
    _getDefaultSystemScopePriority(void) const;

    unsigned long
    _getDefaultTimeSliceQuantum(void) const;

    void*
    _getDefaultUserStackAddress(void) const;

    size_t
    _getDefaultUserStackSize(void) const;

    size_t
    _getDefaultStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "can get" test functions below are used internally to
    // determine at run-time whether the corresponding attribute value may
    // be read.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the corresponding
    // "get" function CANNOT return a legal value under current circumstances.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the corresponding "get"
    // function CAN return a legal value under current circumstances.
    //
    // If the corresponding attribute value has not yet be "set", then a
    // return value of true indicates that a default value is available and
    // may be read.
    //
    // These functions always return true if the corresponding attribute
    // still has the value previously defined by a call to the matching "set"
    // function.  In this case, the behavior is similar to that provided by
    // the "is set" functions (declared later).
    //
    // Some of these functions will throw the RWTHRInternalError exception if
    // some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _canGetConcurrencyPolicy(void) const;

    bool
    _canGetContentionScope(void) const;

    bool
    _canGetInheritancePolicy(void) const;

    bool
    _canGetPriority(void) const;

    bool
    _canGetProcessScopePriority(void) const;

    bool
    _canGetSchedulingPolicy(void) const;

    bool
    _canGetStackCommitSize(void) const;

    bool
    _canGetStackReserveSize(void) const;

    bool
    _canGetStartPolicy(void) const;

    bool
    _canGetSystemScopePriority(void) const;

    bool
    _canGetTimeSliceQuantum(void) const;

    bool
    _canGetUserStack(void) const;

    bool
    _canGetStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "get" functions below are used internally to get the
    // current value of the corresponding attribute.
    //
    // These functions return the value that was defined by a call to
    // the matching "set" function, if any.  If an attribute value has not
    // yet been set, these functions will return the default value for that
    // attribute. If the default value of that attribute is provided by the
    // underlying threads API, and cannot be queried by the Threads Module,
    // these functions will throw an RWTHROperationNotAvailable exception.
    //
    // These functions will throw the RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    RWConcurrencyPolicy
    _getConcurrencyPolicy(void) const;

    RWContentionScope
    _getContentionScope(void) const;

    RWInheritancePolicy
    _getInheritancePolicy(void) const;

    RWPriority
    _getPriority(void) const;

    RWPriority
    _getProcessScopePriority(void) const;

    RWSchedulingPolicy
    _getSchedulingPolicy(void) const;

    size_t
    _getStackCommitSize(void) const;

    size_t
    _getStackReserveSize(void) const;

    RWStartPolicy
    _getStartPolicy(void) const;

    RWPriority
    _getSystemScopePriority(void) const;

    unsigned long
    _getTimeSliceQuantum(void) const;

    void*
    _getUserStackAddress(void) const;

    size_t
    _getUserStackSize(void) const;

    size_t
    _getStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "is set" test functions below can be used to determine
    // whether the corresponding attribute still has the value specified in
    // an earlier call the the matching "set" function.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment, has not yet been set, or
    // has been forced to some other default value in response to a change
    // in another related attribute.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment, has been set, has not
    // been reset, and has not forced to a default value as the result of a
    // change in a some related attribute.
    /////////////////////////////////////////////////////////////////////////

    bool
    _isConcurrencyPolicySet(void) const;

    bool
    _isContentionScopeSet(void) const;

    bool
    _isInheritancePolicySet(void) const;

    bool
    _isPrioritySet(void) const;

    bool
    _isProcessScopePrioritySet(void) const;

    bool
    _isSchedulingPolicySet(void) const;

    bool
    _isStackCommitSizeSet(void) const;

    bool
    _isStackReserveSizeSet(void) const;

    bool
    _isStartPolicySet(void) const;

    bool
    _isSystemScopePrioritySet(void) const;

    bool
    _isTimeSliceQuantumSet(void) const;

    bool
    _isUserStackSet(void) const;

    bool
    _isStackGuardSizeSet(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "can set" test functions below can be used to determine,
    // at run-time, whether the corresponding attribute value may be set.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the specified
    // policy, if any, is not supported under the current circumstances.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the specified policy is legal
    // under the current circumstances.
    //
    // Some of these functions will produce a RWTHRBoundsError exception if
    // the specified value is not a legal policy value for that attribute.
    // This exception can be avoided by making sure that you are using the
    // appropriate value names for enumerated attributes.
    //
    // Some of these functions will throw the RWTHRInternalError exception
    // if some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _canSetConcurrencyPolicy(RWConcurrencyPolicy policy) const;

    bool
    _canSetContentionScope(RWContentionScope scope) const;

    bool
    _canSetInheritancePolicy(RWInheritancePolicy policy) const;

    bool
    _canSetPriority(void) const;

    bool
    _canSetProcessScopePriority(void) const;

    bool
    _canSetSchedulingPolicy(RWSchedulingPolicy policy) const;

    bool
    _canSetStackCommitSize(void) const;

    bool
    _canSetStackReserveSize(void) const;

    bool
    _canSetStartPolicy(RWStartPolicy policy) const;

    bool
    _canSetSystemScopePriority(void) const;

    bool
    _canSetTimeSliceQuantum(void) const;

    bool
    _canSetUserStack(void) const;

    bool
    _canSetStackGuardSize(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "validate" functions below are used internally to validate
    // a candidate value for the corresponding attribute
    //
    // These functions return true if the attribute is supported, and the
    // value is a legal value for the attribute.
    //
    // These functions return false if the attribute is supported, but the
    // value is not a legal value for the attribute.
    //
    // These functions will throw the RWTHROperationNotAvailable exception
    // if the corresponding attribute is supported, but the specified value
    // is not supported under the current circumstances.
    //
    // These functions will throw the RWTHROperationNotSupported exception
    // if the attribute is not supported in the current environment.
    //
    // Some of these functions will throw the RWTHRInternalError exception
    // if some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _validateConcurrencyPolicy(RWConcurrencyPolicy policy) const;

    bool
    _validateContentionScope(RWContentionScope scope) const;

    bool
    _validateInheritancePolicy(RWInheritancePolicy policy) const;

    bool
    _validatePriority(RWPriority priority) const;

    bool
    _validateProcessScopePriority(RWPriority priority) const;

    bool
    _validateSchedulingPolicy(RWSchedulingPolicy policy) const;

    bool
    _validateStackCommitSize(size_t size) const;

    bool
    _validateStackReserveSize(size_t size) const;

    bool
    _validateStartPolicy(RWStartPolicy policy) const;

    bool
    _validateSystemScopePriority(RWPriority priority) const;

    bool
    _validateTimeSliceQuantum(unsigned long milliseconds) const;

    bool
    _validateUserStack(void* address, size_t size) const;

    bool
    _validateStackGuardSize(size_t size) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "set" functions below are used internally to set the
    // corresponding attribute value.
    //
    // These functions will throw the RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw the RWTHROperationNotAvailable exception if
    // the corresponding attribute is supported, but the specified value is
    // not supported under the current circumstances.
    //
    // These functions will throw the RWTHRBoundsError exception if the
    // specified value is invalid or falls outside the current legal range
    // for that attribute.
    //
    // These functions will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    void
    _setConcurrencyPolicy(RWConcurrencyPolicy policy);

    void
    _setContentionScope(RWContentionScope scope);

    void
    _setInheritancePolicy(RWInheritancePolicy policy);

    void
    _setPriority(RWPriority priority);

    void
    _setProcessScopePriority(RWPriority priority);

    void
    _setSchedulingPolicy(RWSchedulingPolicy policy);

    void
    _setStackCommitSize(size_t size);

    void
    _setStackReserveSize(size_t size);

    void
    _setStartPolicy(RWStartPolicy policy);

    void
    _setSystemScopePriority(RWPriority priority);

    void
    _setTimeSliceQuantum(unsigned long milliseconds);

    void
    _setUserStack(void* address, size_t size);

    void
    _setStackGuardSize(size_t size);

    /////////////////////////////////////////////////////////////////////////
    // The private "reset" functions below can be used to restore an
    // attribute value to its default setting, if any.
    //
    // These functions will always succeed, even if the target attribute is
    // not supported in the current environment.
    //
    // There are several combinations of attributes and environments where it
    // is not possible to query for a default value of an attribute; using
    // these functions will simply clear any previous setting so that the
    // Threads Module will know to rely on the underlying API to determine
    // the appropriate default value.
    /////////////////////////////////////////////////////////////////////////

    void
    _resetConcurrencyPolicy(void);

    void
    _resetContentionScope(void);

    void
    _resetInheritancePolicy(void);

    void
    _resetPriority(void);

    void
    _resetProcessScopePriority(void);

    void
    _resetSchedulingPolicy(void);

    void
    _resetStackCommitSize(void);

    void
    _resetStackReserveSize(void);

    void
    _resetStartPolicy(void);

    void
    _resetSystemScopePriority(void);

    void
    _resetTimeSliceQuantum(void);

    void
    _resetUserStack(void);

    void
    _resetStackGuardSize(void);

    /////////////////////////////////////////////////////////////////////////
    // The following private functions may be used to determine the legal
    // range of values for various attributes.
    /////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the maximum priority value supported by
    // the current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if the macro RW_THR_HAS_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not
    // use or support the priority attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetPriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    _getMaxPriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the maximum process-scope priority value
    // supported by the current process-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if RW_THR_HAS_PROCESS_SCOPE_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_SYSTEM_SCOPE and the current
    // environment does not support dual priority values, as indicated by
    // the definition of the macro RW_THR_HAS_DUAL_PRIORITY, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetProcessScopePriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    _getMaxProcessScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the maximum system-scope priority value
    // supported by the current system-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the system-scope priority attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_PROCESS_SCOPE, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetSystemScopePriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    _getMaxSystemScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the maximum time-slice quantum value
    // supported by the current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the time-slice quantum attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_TIME_SLICE_QUANTUM is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not use or
    // support the time-slice quantum attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetTimeSliceQuantum() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    unsigned long
    _getMaxTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the minimum priority value supported by
    // the current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if the macro RW_THR_HAS_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not
    // use or support the priority attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetPriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    _getMinPriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the minimum process-scope priority value
    // supported by the current process-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the priority attribute is not supported. This exception can be
    // avoided by testing to see if RW_THR_HAS_PROCESS_SCOPE_PRIORITY is
    // currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_SYSTEM_SCOPE and the current
    // environment does not support dual priority values, as indicated by
    // the definition of the macro RW_THR_HAS_DUAL_PRIORITY, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetPriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    _getMinProcessScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the minimum system-scope priority value
    // supported by the current system-scope scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the system-scope priority attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope is RW_THR_PROCESS_SCOPE, of if the
    // current scheduling policy does not use or support the priority
    // attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetSystemScopePriority() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWPriority
    _getMinSystemScopePriority(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This private function returns the minimum time-slice quantum value
    // supported by the current contention scope and scheduling policy.
    //
    // This function will throw an RWTHROperationNotSupported exception
    // if the time-slice quantum attribute is not supported. This
    // exception can be avoided by testing to see if the macro
    // RW_THR_HAS_TIME_SLICE_QUANTUM is currently defined.
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not use or
    // support the time-slice quantum attribute.
    //
    // These exceptions can be avoided by calling this function only when the
    // feature test function, canSetTimeSliceQuantum() returns true.
    //
    // This function will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    unsigned long
    _getMinTimeSliceQuantum(void) const;

};

inline
RWThreadAttributeImp::~RWThreadAttributeImp(void)
{
}

#endif // __rw_thread_RWThreadAttributeImp_h__
