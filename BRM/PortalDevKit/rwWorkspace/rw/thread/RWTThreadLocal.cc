/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTThreadLocal.cc#1 $
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

  RWTThreadLocal<Type> - Declare thread-local storage object.

******************************************************************************/

#include <rw/thread/RWTThreadLocal.h>
#include <rw/thread/RWThreadSelf.h>
#include <rw/tools/pointer.h>

#if defined(RW_THR_THREAD_API_WIN32)
// Add forward declarations of TLS methods to avoid inclusion of windows headers
extern "C" {

    __declspec(dllimport) int __stdcall TlsFree(unsigned long);
    __declspec(dllimport) unsigned long __stdcall TlsAlloc(void);
    __declspec(dllimport) void*  __stdcall TlsGetValue(unsigned long);
    __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);

} // extern "C"

#endif

// Unsafe
template <class Type>
RWTThreadLocal<Type>::RWTThreadLocal(RWStaticCtor)
    : RWTMonitor<RWMutexLock>(RW_STATIC_CTOR)
{
}

// Unsafe
template <class Type>
RWTThreadLocal<Type>::RWTThreadLocal(void)
    : isInitialized_(false)
{
    init();
}

template<class Type>
void
RWTThreadLocal<Type>::init(void)
{
    LockGuard lock(monitor());
    if (!isInitialized_) {
        keyCreated_ = false;
        key_ = 0;
#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
        new(ucleanup_.cleanup_) RWTPtrSlist<RWTLDBase>();
#endif
        isInitialized_ = true;
    }
}

template <class Type>
RWTThreadLocal<Type>::~RWTThreadLocal(void)
{

    // Only one thread may destroy an instance, but other
    // threads may still be attempting to access the instance
    // if the instance is being destroyed as part of the static
    // destruction phase of program termination...

    if (isInitialized_) {

        // Lock the key state so we can cleanup the instance
        LockGuard lock(monitor());

        if (keyCreated_) {

#if defined(RW_THR_THREAD_API_POSIX) || \
    defined(RW_THR_THREAD_API_SOLARIS)

            RWTLDBase* tld;
            if (0 != (tld = (RWTLDBase*)get())) {
                // Instance has been created...
                delete tld;

                // Clear the old thread local instance...
                set(0);
            }

#  if defined(RW_THR_THREAD_API_POSIX)

            if (0 != ::pthread_key_delete(key_)) {
                RW_ASSERT(0); // INTERNAL ERROR - Couldn't delete the key for some reason!
            }

#  endif

#elif defined(RW_THR_THREAD_API_WIN32)

            // Assume other threads have already destroyed their entries
            if (0 == ::TlsFree(key_)) {
                RW_ASSERT(0); // INTERNAL ERROR - Couldn't delete the key for some reason!
            }

#endif

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
            (reinterpret_cast<RWTPtrSlist<RWTLDBase>*>(ucleanup_.cleanup_))
            ->clearAndDestroy();
#endif
            keyCreated_ = false;
        }

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
        (reinterpret_cast<RWTPtrSlist<RWTLDBase>*>(ucleanup_.cleanup_))
        ->~RWTPtrSlist<RWTLDBase>();
#endif
        isInitialized_ = false;
    }
}

template <class Type>
void
RWTThreadLocal<Type>::createKey(void)
{
    static const char msgHeader[] = "RWTThreadLocal<Type>::createKey - ";

    if (!isInitialized_) {
        init();
    }

    // Check once - Has a key been create for this instance?
    if (!keyCreated_) {
        // No, so try to get one...

        // Lock the thread local state
        LockGuard lock(monitor());

        // Check again - Has a key been created for this instance?
        if (!keyCreated_) {

            // Still no, so create one...

#if defined(RW_THR_THREAD_API_POSIX)

            int rv;
            if (0 != (rv =::pthread_key_create(&key_, RWTLDdestroy))) {
                RWCString msg(msgHeader, sizeof(msgHeader) - 1);
                switch (rv) {
                    case EAGAIN:
                        // Not enough memory
                        msg.append(RW_THR_No_Memory);
                        throw RWTHRResourceLimit(msg);
                    case ENOMEM:
                        // Key name space is exhausted (exceeded per process limit)
                        msg.append(RW_THR_No_Resources);
                        throw RWTHRResourceLimit(msg);
                    case EINVAL:
                        RW_ASSERT(0); // INTERNAL ERROR - Invalid argument!
                    default:
                        RW_ASSERT(0); // INTERNAL ERROR - Unexpected or unrecognized error!
                        msg.append("pthread_key_create() - ");
                        msg.append(::rwErrorMsg(rv));
                        throw RWTHRInternalError(msg);
                }
            }

#elif defined(RW_THR_THREAD_API_SOLARIS)

            int rv;
            if (0 != (rv =::thr_keycreate(&key_, RWTLDdestroy))) {
                RWCString msg(msgHeader, sizeof(msgHeader) - 1);
                switch (rv) {
                    case EAGAIN:
                        // Not enough memory
                        msg.append(RW_THR_No_Memory);
                        throw RWTHRResourceLimit(msg);
                    case ENOMEM:
                        // Key name space is exhausted (exceeded per process limit)
                        msg.append(RW_THR_No_Resources);
                        throw RWTHRResourceLimit(msg);
                    case EINVAL:
                        RW_ASSERT(0); // INTERNAL ERROR - Invalid argument!
                    default:
                        RW_ASSERT(0); // INTERNAL ERROR - Unexpected or unrecognized error!
                        msg.append("thr_keycreate() - ");
                        msg.append(::rwErrorMsg(rv));
                        throw RWTHRInternalError(msg);
                }
            }

#elif defined(RW_THR_THREAD_API_WIN32)
            // using an explicit unsigned long instead of DWORD to avoid inclusion
            // of windows.h header
            if ((unsigned long) - 1 == (key_ = ::TlsAlloc())) {
                RWCString msg(msgHeader, sizeof(msgHeader) - 1);
                msg.append("TlsAlloc() - ");
                msg.append(::rwGetLastErrorMsg());
                throw RWTHRInternalError(msg);
            }

#endif
            keyCreated_ = true;
        }
    }
}

template <class Type>
bool
RWTThreadLocal<Type>::reset(void)
{
    // Do nothing if not initialized or used
    if (!isInitialized_ || !keyCreated_) {
        return false;
    }

    RWTLDBase* tld = (RWTLDBase*)get();

    // if there is no pointer set, we have nothing to do
    if (!tld) {
        return false;
    }

    // write a null pointer back to TLS
    set(0);

    // delete after set because it could throw without
    // actually storing the null pointer
    delete tld;

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
    // We have either registered this object with the current thread
    // object, or registered this object with the thread-local object.

    // Either way we will remove the item from the list, and we will
    // delete the value ourselves.

    RWThreadSelf curThread = rwThread();
    if (curThread.isValid()) {
        // de-register from the current thread object
        curThread.removeTLD(tld);
    }
    else {
        // de-register from the current thread local object
        LockGuard guard(monitor());
        (reinterpret_cast<RWTPtrSlist<RWTLDBase>*>(ucleanup_.cleanup_))
        ->remove(tld);
    }
#endif

    return true;
}

template <class Type>
void*
RWTThreadLocal<Type>::get(void) const
{
    static const char msgHeader[] = "RWTThreadLocal<Type>::get - ";

    // init and createKey must have been called first
    RW_ASSERT(keyCreated_ && isInitialized_);

#if defined(RW_THR_THREAD_API_POSIX)

    RW_UNUSED(msgHeader);
    return ::pthread_getspecific(key_);

#elif defined(RW_THR_THREAD_API_SOLARIS)

    int rv;
    void* tld = 0;

    if (0 != (rv = ::thr_getspecific(key_, &tld))) {
        RWCString msg(msgHeader, sizeof(msgHeader) - 1);
        switch (rv) {
            case EINVAL:
                RW_ASSERT(0); // INTERNAL ERROR - Invalid argument!
            default:
                RW_ASSERT(0); // INTERNAL ERROR - Unexpected or unrecognized error!
                msg.append("thr_getspecific() - ");
                msg.append(::rwErrorMsg(rv));
                throw RWTHRInternalError(msg);
        }
    }

    return tld;

#elif defined(RW_THR_THREAD_API_WIN32)

    RW_UNUSED(msgHeader);
    return ::TlsGetValue(key_);

#endif
}

template <class Type>
void
RWTThreadLocal<Type>::set(void* tld)
{
    static const char msgHeader[] = "RWTThreadLocal<Type>::set - ";

    // init and createKey must have been called first
    RW_ASSERT(keyCreated_ && isInitialized_);

    // Set may only be called if the value for this thread has
    // not yet been set, or we are setting it back to NULL. If
    // we are setting it back to NULL, the caller is responsible
    // for releasing the memory associated with this threads
    // local storage.
    RW_ASSERT(!tld || !isSet());

#if defined(RW_THR_THREAD_API_POSIX)

    int rv;
    if (0 != (rv = ::pthread_setspecific(key_, tld))) {
        RWCString msg(msgHeader, sizeof(msgHeader) - 1);
        switch (rv) {
            case ENOMEM:
                // Not enough memory
                msg.append(RW_THR_No_Memory);
                throw RWTHRResourceLimit(msg);
            case EINVAL:
                RW_ASSERT(0); // INTERNAL ERROR - Invalid key!
            default:
                RW_ASSERT(0); // INTERNAL ERROR - Unexpected or unrecognized error!
                msg.append("pthread_setspecific() - ");
                msg.append(::rwErrorMsg(rv));
                throw RWTHRInternalError(msg);
        }
    }

#elif defined(RW_THR_THREAD_API_SOLARIS)

    int rv;
    if (0 != (rv = ::thr_setspecific(key_, tld))) {
        RWCString msg(msgHeader, sizeof(msgHeader) - 1);
        switch (rv) {
            case EINVAL:
                RW_ASSERT(0); // INTERNAL ERROR - Invalid argument!
            default:
                RW_ASSERT(0); // INTERNAL ERROR - Unexpected or unrecognized error!
                msg.append("thr_setspecific() - ");
                msg.append(::rwErrorMsg(rv));
                throw RWTHRInternalError(msg);
        }
    }

#elif defined(RW_THR_THREAD_API_WIN32)

    if (0 == ::TlsSetValue(key_, tld)) {
        RW_ASSERT(0); // INTERNAL ERROR - Unexpected error!
        RWCString msg(msgHeader, sizeof(msgHeader) - 1);
        msg.append("TlsSetValue() - ");
        msg.append(::rwGetLastErrorMsg());
        throw RWTHRInternalError(msg);
    }

#endif

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
    // We will either register this object with the current thread object,
    // if any, or with the thread-local object.

    // The thread object will delete any thread-local objects allocated
    // just prior to thread exit.

    // The thread local object will delete any objects when the
    // thread local object goes out of scope and is destructed.

    RWThreadSelf curThread = rwThread();
    if (curThread.isValid()) {
        // Register with the current thread object for cleanup
        curThread.appendTLD((RWTLDBase*)tld);
    }
    else {
        // Register with the current thread local object
        LockGuard guard(monitor());
        (reinterpret_cast<RWTPtrSlist<RWTLDBase>*>(ucleanup_.cleanup_))
        ->append((RWTLDBase*)tld);
    }
#endif
}

template <class Type>
Type&
RWTThreadLocal<Type>::getValue(void) const
{
    // call setValue first!
    // RW_ASSERT(keyCreated_ && isInitialized_);
    RWTThreadLocal<Type>* self = const_cast <RWTThreadLocal<Type>*>(this);
    self->createKey();

    RWTLDBase* tld = 0;

    if (0 == (tld = (RWTLDBase*)get())) {
        self->setValue(Type()); // not set, set a default Type
        tld = (RWTLDBase*)get();
    }

    return ((RWTLD*)tld)->value();
}

template <class Type>
void
RWTThreadLocal<Type>::setValue(const Type& value)
{
    // Is this the first access?
    createKey();

    RWTLDBase* tld = 0;

    if (0 != (tld = (RWTLDBase*)get())) {
        ((RWTLD*)tld)->value() = value;  // Assign
        return;
    }

    RWTScopedPointer<RWTLD> newTLD(new RWTLD(value));
    set(newTLD.get());
    newTLD.release();
}
