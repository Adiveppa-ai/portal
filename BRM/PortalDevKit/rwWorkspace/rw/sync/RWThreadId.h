#ifndef __rw_sync_RWThreadId_h__
#define __rw_sync_RWThreadId_h__


/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWThreadId.h#1 $
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

#include <rw/sync/pkgdefs.h>
#include <rw/tools/hash.h>

#if !defined(RW_MULTI_THREAD)
/**
 * \relates RWThreadId
 *
 * The internal thread id representation.
 *
 * \conditional
 * This type is used for single-threaded build configurations.
 */
typedef unsigned RWThreadIdRep;
#endif

#if defined(RW_THR_THREAD_API_POSIX) || defined(DOXYGEN)
#  include <pthread.h>
/**
 * \relates RWThreadId
 *
 * The internal thread id representation.
 *
 * \conditional
 * This type is used for build configurations based on POSIX threads.
 */
typedef pthread_t RWThreadIdRep;
#endif

#if defined(RW_THR_THREAD_API_SOLARIS) || defined(DOXYGEN)
#  include <thread.h>
/**
 * \relates RWThreadId
 *
 * The internal thread id representation.
 *
 * \conditional
 * This type is used for build configurations based on Solaris threads.
 */
typedef thread_t RWThreadIdRep;
#endif

#if  defined(RW_THR_THREAD_API_WIN32) || defined(DOXYGEN)
#  include <rw/mutex.h>
#  include <process.h>
/**
 * \relates RWThreadId
 *
 * The internal thread id representation.
 *
 * \conditional
 * This type is used for build configurations based on Win32 threads.
 */
typedef unsigned RWThreadIdRep;
#endif

#if  defined(RW_MULTI_THREAD) && !defined(RW_THR_THREAD_API_POSIX) \
      && !defined(RW_THR_THREAD_API_SOLARIS) && !defined(RW_THR_THREAD_API_WIN32)
#  error RWThreadIdRep declaration missing!
#endif

// The valid flag is not used with MT builds on Solaris and AIX:
#if defined(RW_MULTI_THREAD)
#  if defined(_AIX) && defined(__IBMCPP__) || \
      defined (__sun) && defined (__SUNPRO_CC)
#    define RW_THR_NO_VALID_FLAG
#  endif // AIX && VACPP || Solaris && SUNPro
#endif // RW_MULTI_THREAD

// POSIX implementations based on CMA threads use a structure
// for thread ids.  Cfront-based compiler's skip this file when doing
// template instantiation, so we can't define a global comparison
// operator for pthread_t, a requirement if we are going to use
// pthread_t in SourcePro Core - Essential Tools Module templatized
// collections.  To solve this problem, we've had to wrap the native
// thread id structures with another class.  Now we can define a
// comparison operator that can be used by Essential Tools Module
// template collections under all APIs.

/**
 * \ingroup synchronization_package
 *
 * \brief
 * A wrapper for platform-specific thread IDs.
 *
 * RWThreadId is a wrapper for platform-specific thread IDs. An RWThreadId
 * represents the identification given by the underlying thread API to a
 * specific thread of execution. The native thread IDs are used to identify
 * and control these threads in the native thread API, but are not
 * necessarily related to any Threads Module objects. You can get an
 * instance of RWThreadId directly from a runnable object using the
 * RWRunnableHandle::threadId() member function, or you can call the global
 * function rwThreadId() to get an RWThreadId associated with the current
 * thread. A thread ID is valid only while the separate thread of execution
 * exists.
 *
 * The global rwThread() function may be used to determine the threaded
 * runnable object, if any, associated with the current thread of execution.
 * Use the rwThreadHash() function to retrieve an integer associated with a
 * thread id for output or debugging purposes. Do not attempt to stream an
 * RWThreadId instance directly, as the native thread ID type that this class
 * represents may be a structure and not a simple scalar.
 *
 * \example
 * \code
 * #include <rw/thread/RWThreadFunction.h>
 * #include <rw/sync/RWThreadId.h>
 *
 * void whoamiReally()
 * {
 *     RWThreadId myID = rwThreadId();
 *     std::cout << "My thread ID is " << rwThreadHash(myID) << std::endl;
 * }
 *
 * int main()
 * {
 *     RWThread t1, t2, t3;
 *
 *     (t1 = RWThreadFunction::make(whoamiReally)).start();
 *     (t2 = RWThreadFunction::make(whoamiReally)).start();
 *     (t3 = RWThreadFunction::make(whoamiReally)).start();
 *
 *     t1.join();
 *     t2.join();
 *     t3.join();
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * My thread ID is  4
 * My thread ID is  5
 * My thread ID is  6
 * \endcode
 * \endexample
 *
 * \sa
 * rwThreadId(), rwThreadHash(), rwThread(), RWRunnableHandle
 */
class RW_SYNC_SYMBOLIC RWThreadId
{

protected:

    RWThreadIdRep tid_;

#if !defined(RW_THR_NO_VALID_FLAG)
    bool valid_;
#endif

public:
    // Default constructor gives an invalid thread id
    /**
     * Creates an RWThreadId object not associated with any thread.
     */
    RWThreadId();

    // Does not explicitly initialize, hence may be used before constructed.
    /**
     * Constructs a static instance, but does no direct initialization.
     * Static instances are zero initialized, resulting in an RWThreadId
     * with an invalid state.
     *
     * \note
     * This constructor must be used only for static instances. Use of this
     * constructor with an automatically or dynamically allocated instance
     * may produce unpredictable behavior.
     */
    RWThreadId(RWStaticCtor);

    // Constructor from a native api thread id that is assumed valid
    /**
     * Creates an RWThreadId object directly from a native thread ID.
     */
    RWThreadId(const RWThreadIdRep& threadIdRep);

    // Do nothing destructor to keep stdlib happy!
    /**
     * Destructor.
     */
    ~RWThreadId();


    /**
     * Clears the native thread ID so it won't match other native IDs.
     */
    void
    clear();


    /**
     * Returns a hash of the thread ID.
     */
    unsigned
    hash() const;

    /**
     * Returns \c true if this thread ID was constructed or assigned from a
     * native thread instance, otherwise \c false.
     */
    bool
    isValid() const;


    /**
     * Assignment operator.
     */
    RWThreadId&
    operator=(const RWThreadId& second);


    /**
     * Returns a reference to the native thread ID.
     */
    operator RWThreadIdRep& () const;


    /**
     * Returns the address of the native thread ID member.
     */
    RWThreadIdRep*
    getRep() const;


    /**
     * Compares native thread IDs for equality.
     */
    bool
    operator==(const RWThreadId& second) const;


    /**
     * Compares native thread IDs for inequality.
     */
    bool
    operator!=(const RWThreadId& second) const;

    // Compare native thread ids for inequality
    // (Required for C++ Standard Library collections)
    bool
    operator<(const RWThreadId& second) const;

    /**
     * Returns \c true if \a id matches the thread ID of the currently
     * running thread; otherwise, returns \c false.
     */
    static bool  isSelf(const RWThreadId& id);


    /**
     * Returns an RWThreadId for the current thread.
     */
    static RWThreadId self();

};

/*****************************************************************************/

// Create an invalid RWThreadId object
inline
RWThreadId::RWThreadId()
    :
    tid_(0)
#if !defined(RW_THR_NO_VALID_FLAG)
    , valid_(false)
#endif // RW_THR_NO_VALID_FLAG
{
}

// Constructor for global static instances. Does not explicitly initialize
// any data members, hence it could be used before construction. Global
// objects are always zero-initialized creating an invalid RWThreadId object.
inline
RWThreadId::RWThreadId(RWStaticCtor)
{
}

// Create a valid RWThreadId object from a native thread id
// threadIdRep is assumed to be valid
inline
RWThreadId::RWThreadId(const RWThreadIdRep& threadIdRep)
    :
    tid_(threadIdRep)
#if !defined(RW_THR_NO_VALID_FLAG)
    , valid_(true)
#endif // RW_THR_NO_VALID_FLAG
{
}

// Destruct a RWThreadId object
inline
RWThreadId::~RWThreadId()
{
}

// Clear the thread id so it won't match other valid ids
inline void
RWThreadId::clear()
{
#if !defined(RW_THR_NO_VALID_FLAG)
    valid_ = false;
#endif

    tid_ = 0;

}

// Reports whether or not this thread id is valid or not
inline bool
RWThreadId::isValid() const
{
    return
#if defined(RW_THR_NO_VALID_FLAG)
        tid_ != 0
#else
        valid_
#endif // RW_THR_NO_VALID_FLAG
        ;
}

inline unsigned
RWThreadId::hash() const
{
    // hash for an invalid thread id is always 0...
    if (!isValid()) {
        return 0;
    }

    return (unsigned)tid_;
}

// Assign one id to another
inline RWThreadId&
RWThreadId::operator=(const RWThreadId& second)
{
    // this assignment sequence is not holding on PSO and
    // should not hold on TSO either

    tid_ = second.tid_;

#if !defined(RW_THR_NO_VALID_FLAG)
    valid_     = second.isValid();
#endif // !RW_THR_NO_VALID_FLAG

    return *this;
}

// Return a pointer to the native thread id structure
// which may or may not be initialized yet.
inline RWThreadIdRep*
RWThreadId::getRep() const
{
    return const_cast<RWThreadIdRep*>(&RW_EXPOSE(tid_));
}

// Return a reference to the native thread id structure
inline
RWThreadId::operator RWThreadIdRep& () const
{
    return const_cast< RWThreadIdRep& >(tid_);
}

// Compare native thread ids
inline bool
RWThreadId::operator==(const RWThreadId& second) const
{
    // first check to see if the LHS is valid.  If the LHS is not
    // valid, return the state of the RHS as the RWThreadIds are
    // equal if they are both
    // invalid and not equal if one side is valid and the other side is not.
    if (!isValid()) {
        return !second.isValid();
    }
    else {
        // if the the LHS is valid, check the RHS.  If the RHS is not
        // valid, return false as both valid_ flags must be equal to
        // be considered the same.  Finally, if both sides are equal,
        // compare the actual native thread ids.
#if defined(RW_THR_THREAD_API_POSIX)
        return
            second.isValid() &&
            pthread_equal(tid_, second.tid_);
#else
        return
            second.isValid() && (second.tid_ == tid_);
#endif
    }
}

inline bool
RWThreadId::operator!=(const RWThreadId& second) const
{
    return !(second == *this);
}

// Compare native thread ids for inequality
inline bool
RWThreadId::operator<(const RWThreadId& second) const
{
    // first check to see if the LHS is valid.  If the LHS is not valid,
    // return the state of the RHS as the RWThreadIds are equal if they
    // are both invalid and less than if LHS side is invalid and the RHS
    // is not.
    if (!isValid()) {
        return second.isValid();
    }
    else {
        // if the the LHS is valid, check the RHS.  If the RHS is not
        // valid, return false.  Finally, if both sides are valid, compare
        // the actual native thread ids.
        return second.isValid() && (tid_ < second.tid_);
    }
}

inline RWThreadId
RWThreadId::self()
{
#if !defined(RW_MULTI_THREAD)
    return 0;
#elif defined(RW_THR_THREAD_API_POSIX)
    return pthread_self();
#elif defined(RW_THR_THREAD_API_SOLARIS)
    return thr_self();
#elif defined(RW_THR_THREAD_API_WIN32)
    return GetCurrentThreadId();
#endif
}

inline bool
RWThreadId::isSelf(const RWThreadId& id)
{
    return id == RWThreadId::self();
}

/*****************************************************************************/

inline bool
rwIsSelf(const RWThreadId& id)
{
    return id == RWThreadId::self();
}


/**
 * \relates RWThreadId
 *
 * Use this function when an integer is required to identify a particular thread
 * for hashing and trace/debug output purposes. The thread id value stored
 * inside an RWThreadId instance should not be used directly, since some
 * environments use a structure to represent a thread id.
 *
 * \sa
 * RWThreadId
 */
inline unsigned
rwThreadHash(const RWThreadId& id)
{
    return id.hash();
}


/**
 * \relates RWThreadId
 *
 * The rwThreadId() function returns an RWThreadId instance containing the
 * thread id value associated with the calling thread. This id value is
 * assigned by the underlying threads system. You may query for the thread
 * id of any thread, regardless of its method of creation.
 *
 * \sa
 * RWThreadId, rwThreadHash()
 */
inline RWThreadId
rwThreadId()
{
    return RWThreadId::self();
}

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Function object for hashing an RWThreadId.
 *
 * Provides a C++ Standard Library-compliant hash function object suitable
 * for use with hash or unordered containers.
 */
template <>
struct RWTHash<RWThreadId> : public std::unary_function<RWThreadId, size_t> {
    /**
     * Returns a hash of \a obj. This function is the equivalent of calling
     *
     * \code
     * obj.hash();
     * \endcode
     */
    size_t operator()(const RWThreadId& obj) const
    {
        return obj.hash();
    }
};

#endif // __rw_sync_RWThreadId_h__
