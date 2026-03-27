#ifndef __rw_thread_RWTThreadLocal_h__
#define __rw_thread_RWTThreadLocal_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTThreadLocal.h#1 $
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

  The RWTThreadLocal class provide a thread-local storage class with simple
  value semantics.  Each thread local instance may be shared between multiple
  threads, but each thread accessing the thread-local object is actually
  manipulating its own distinct instances of the template parameter class.

  Thread local variables are especially useful in situations where a global
  scope variable is desired, but each thread needs to maintain its own value
  within that variable (the global variable 'errno' is a common example).

  The types used in instantiating this class template must be:

  - DefaultConstructible
  - CopyConstructible
  - Assignable

  The value or instance associated with each thread is created the first time
  a thread-local instance is accessed.  A thread-local value is stored in
  an instance using the assignment operator.  A value is retrieved from an
  instance by using the instance as the right-hand term in an expression
  requiring a value of the template parameter Type:

  RWTThreadLocal<int>   myInt(RW_STATIC_CTOR);

  void func()
  {
    ...
    // Write a value...
    myInt = 5;

    // Read a value...
    int anotherInt = myInt;
  }

  If a thread-local instance is evaluated without first assigning it value,
  then the value retrieved will be that produced by the default constructor
  for the Type-parameter class.

  Assignment does not actually result in assignment from the right-hand Type-
  instance to the internal Type-instance; instead, the internal Type-instance
  is deleted, and a new instance is copy-constructed from the right-hand
  Type-instance.

  Thread-local objects may be allocated as static instances, such as global
  variables or a static class-members, or may be allocated as automatic or
  dynamic instances.  Static instances must be constructed using a special
  static constructor that is selected by passing the RW_STATIC_CTOR value from
  the enumerated type RWStaticCtor.  Automatically and dynamically allocated
  instances must use the default constructor to properly initialize the
  thread-local instance.

  There is probably little need for automatic allocation of a thread-local
  storage object on the stack, since this instance can only be accessed by
  the allocating thread (unless a reference or pointer to the object is
  passed to other threads, which is arguably, a dangerous thing to do!).

  The initialization of global and static class member instances is not
  multithread-safe.  One thread must complete construction or an access
  operation on an instance before other threads may safely access that same
  instance.

******************************************************************************/

#include <rw/thread/pkgdefs.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWTMonitor.h>

#if defined(RW_THR_THREAD_API_POSIX)
typedef pthread_key_t   RWThreadLocalRep;
#elif defined(RW_THR_THREAD_API_SOLARIS)
#  include <thread.h>
typedef thread_key_t    RWThreadLocalRep;
#elif defined(RW_THR_THREAD_API_WIN32)
#  include <rw/tpslist.h>
// Use explicit unsigned long instead of windows.h
typedef unsigned long   RWThreadLocalRep;
#else
#  error Class RWTThreadLocal<Type> is not supported in this environment!
#endif

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWThreadLocal RWTThreadLocal
#endif

// Base class for Thread Local Data. Has a virtual
// destructor so that we can call delete on a base
// pointer and have it destroy the derived
// RWThreadLocal<T>::RWTLD.
struct RWTLDBase {
    virtual ~RWTLDBase(void) { }
};

// Operator== compares addresses intentionally.  A
// RWTPtrSlist needs it to allow comparison of two
// RWTLDBase objects, which are not the same unless
// they refer to two objects at the same address.
inline bool operator==(const RWTLDBase& first, const RWTLDBase& second)
{
    return &first == &second;
}

#if defined(RW_THR_THREAD_API_POSIX) || \
    defined(RW_THR_THREAD_API_SOLARIS)
#  include <errno.h>

extern "C" {
    // Function needed to get cleanup of thread local data
    // when threads exit. Passed to pthread_key_create or
    // thr_keycreate.
    inline void
    RWTLDdestroy(void* ptld)
    {
        RWTLDBase* tld = (RWTLDBase*)ptld;
        delete tld; // invoke virtual dtor!!!
    }
}
#endif



/**
 * \ingroup threading_package
 *
 * \brief
 * Provides thread-local storage with simple by-value semantics.
 *
 * The RWTThreadLocal class provides thread-local storage with simple
 * by-value semantics. An RWTThreadLocal instance may be shared between
 * multiple threads. Doing so creates one instance of typed data per thread.
 * Each thread accesses its own private instance of the typed data whenever
 * it uses the shared RWTThreadLocal instance.
 *
 * \example
 * \code
 * #include <rw/sync/RWSemaphore.h>
 * #include <rw/thread/RWThreadFunction.h>
 * #include <rw/thread/RWTThreadLocal.h>
 * #include <rw/cstring.h>
 *
 * RWTThreadLocal<int> threadLocalVal;
 * RWCString nonThreadLocalString;
 *
 * RWSemaphore sema1;    //Used to synchronize
 * RWSemaphore sema2;
 *
 * void multiThreadFunc()
 * {
 *     sema1.acquire();  //Wait for main thread to set values
 *
 *     //Set global variables to our own values
 *     threadLocalVal = 5;
 *     nonThreadLocalString = "Ha Ha I overwrote Main's string";
 *
 *     sema2.release(); //Tell main thread to print out its values
 *     sema1.acquire(); //Wait for main thread to print
 *
 *     //Print out our values
 *     std::cout << "Thread's val: " << threadLocalVal << std::endl;
 *     std::cout << "Thread's string: " << nonThreadLocalString << std::endl;
 * }
 *
 * int main()
 * {
 *     RWThreadFunction myThread = RWThreadFunction::make(multiThreadFunc);
 *
 *     myThread.start();
 *
 *     //Set main thread's values
 *     threadLocalVal = 10;
 *     nonThreadLocalString = "Main's String";
 *
 *     sema1.release();  //Tell other thread to set values
 *     sema2.acquire();  //Wait for other thread to set values
 *
 *     //Print out main thread's values
 *     std::cout << "Main's val: " << threadLocalVal << std::endl;
 *     std::cout << "Main's string: " << nonThreadLocalString << std::endl;
 *
 *     sema1.release(); //Tell other thread to print values
 *
 *     myThread.join(); //Wait for other thread to end
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
template <class Type>
class RWTThreadLocal :
    public RWTMonitor<RWMutexLock>
{

public:

    typedef RWTLockGuard< RWTMonitor< RWMutexLock > >     LockGuard;
    typedef RWTUnlockGuard< RWTMonitor< RWMutexLock > >   UnlockGuard;
    typedef RWTTryLockGuard< RWTMonitor< RWMutexLock > >  TryLockGuard;

protected:

    RWThreadLocalRep key_;
    bool isInitialized_;
    bool keyCreated_;

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
    // RWTPtrSlist<RWTLDBase> will be constructed in the init() method as
    // part of delayed initialization and destructed in the destructor.
    union {
        long long align_;
        char cleanup_[sizeof(RWTPtrSlist< RWTLDBase >)];
    } ucleanup_;
#endif

public:

    /**
     * Constructs an RWTThreadLocal instance, which is initialized when
     * first used, unlike an instance created by the default constructor,
     * which is initialized when constructed.
     */
    RWTThreadLocal(RWStaticCtor);


    /**
     * Constructs and initializes a thread-local storage object. The first
     * time a thread accesses this object, a new instance of \c Type is
     * created specifically for that thread. Each subsequent access by the
     * same thread references the same \c Type instance.
     */
    RWTThreadLocal();


    /**
     * Destroys the thread-local storage object. Since thread-local storage
     * objects are often declared at global scope, they necessarily are
     * destroyed during the program termination process. Any threads that
     * may still be running during program termination must guard against
     * trying to access these storage objects.
     */
    ~RWTThreadLocal();


    /**
     * Assigns a \c Type value to self. The value assigned is available only
     * to the current thread. Access of self by other threads manipulate the
     * values stored specifically for those threads.
     */
    RWTThreadLocal<Type>&
    operator=(const Type& value);


    /**
     * Retrieves and returns the value previously stored by the current
     * thread.
     */
    operator Type() const;


    /**
     * Returns \c true if this variable has been set in the current thread,
     * otherwise returns \c false.
     */
    bool
    isSet() const;


    /**
     * Retrieves a reference to the current value of this variable.
     */
    Type&
    getValue() const;


    /**
     * Sets the value of this object.
     */
    void
    setValue(const Type& value);


    /**
     * Resets the value of this object.
     */
    bool
    reset(void);

private:

    /**
     * Copy construction prohibited.
     */
    RWTThreadLocal(const RWTThreadLocal& second);


    /**
     * Assignment prohibited.
     */
    RWTThreadLocal&
    operator=(const RWTThreadLocal& second);

private:

    void
    createKey(void);

    void*
    get(void) const;

    void
    set(void*);

    void
    init(void);

#ifdef RW_THR_NO_NESTED_CLASS_FRIEND_ACCESS
    static void initTLD(void* buf, const Type& t);

    static void destroyTLD(void* buf);
#endif

    class RWTLD;

};

#ifndef RW_THR_NO_NESTED_CLASS_FRIEND_ACCESS
// A Thread Local Data type. Wraps any data Type T.
// Destructor simply destroys value_.
template <class Type>
class RWTThreadLocal<Type>::RWTLD : public RWTLDBase
{
public:
    RWTLD(const Type& value) : value_(value) { }
    ~RWTLD(void) { }

    Type& value()
    {
        return value_;
    }

private:
    RWTLD(const RWTLD&);
    RWTLD& operator=(const RWTLD&);

    Type value_;
};

#else
// RWTThreadLocal<T>::RWTLD will not have access to private members of classes
// that declare RWTThreadLocal<T> a friend. In order to allow RWTLD to hold
// a T instance, we delegate responsibility for constructing/destroying the
// instance back to RWTThreadLocal<T>
template <class Type>
inline void RWTThreadLocal<Type>::initTLD(void* buf, const Type& t)
{
    new(buf) Type(t);
}

template <class Type>
inline void RWTThreadLocal<Type>::destroyTLD(void* buf)
{
    reinterpret_cast<Type*>(buf)->~Type();
}

template <class Type>
class RWTThreadLocal<Type>::RWTLD : public RWTLDBase
{
public:
    RWTLD(const Type& value)
    {
        RWTThreadLocal<Type>::initTLD(value_.data_, value);
    }

    ~RWTLD(void)
    {
        RWTThreadLocal<Type>::destroyTLD(value_.data_);
    }

    Type& value()
    {
        return *reinterpret_cast<Type*>(value_.data_);
    }

private:
    RWTLD(const RWTLD&);
    RWTLD& operator=(const RWTLD&);

    union {
        long long align_;
        char data_[sizeof(Type)];
    } value_;
};

#endif



/*****************************************************************************/

template <class Type>
inline RWTThreadLocal<Type>&
RWTThreadLocal<Type>::operator=(const Type& value)
{
    setValue(value);
    return *this;
}

template <class Type>
inline bool
RWTThreadLocal<Type>::isSet() const
{
    const_cast< RWTThreadLocal< Type >* >(this)->createKey();
    return 0 != get();
}

template <class Type>
inline
RWTThreadLocal<Type>::operator Type() const
{
    return getValue();
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/thread/RWTThreadLocal.cc>
#endif

#endif // __rw_thread_RWTThreadLocal_h__
