#ifndef __rw_network_RWTNetHandle_h__
#define __rw_network_RWTNetHandle_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTNetHandle.h#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

/*
 * RWTNetHandle<C>: Reference counted handle to a C on the free store
 *
 * A Handle would be called a "smart pointer" in some C++ circles.  It
 * has the same semantics as a pointer, except that the thing it points
 * to is reference counted.  When the last handle referencing it is
 * destructed, the referencee gets deleted.
 *
 * This class is used in the implementation of some of the SourcePro
 * Net - Essential Networking Module classes.  It is not part of the
 * supported customer interface of the Essential Networking Module.  It
 * may change without notice in future revisions.
 *
 * This simple Handle class does not have any of the smarts needed to convert
 * from one type of Handle to another, for example, to convert from a
 * Handle<Derived> to a Handle<Base>.  To do this requires member function
 * templates, and not all compilers support those yet.
 *
 * Since these classes contain only a single pointer, a reasonable
 * compiler ought to stick them in a register just like a regular pointer.
 *
 * It is possible (and very useful) to use this class to point to objects
 * that are derived from C, rather than being exactly of type C.  For this
 * to work properly, be sure that C has a virtual destructor.  Otherwise, the
 * call to delete the object when all pointers to it are gone will not likely
 * do the right thing.
 *
 * There is a const hole that I'm not sure how to plug.
 * It is the same one present in the SourcePro Core - Essential Tools Module
 * collection classes, and the SourcePro Analysis - Essential Math Module
 * The problem is due to the definition of op=.  You can do this:
 * <pre>
 *   const Handle p(o);  // If Handle has pointer semantics, I can't change p
 *   Handle q;
 *   Handle q=p;         // Oh-oh, q is not const
 *   q->nonConstFn();
 * </pre>
 *
 **
 ** It seems that making the copy ctor/assignment op take non-const refs
 ** would fix this problem. Creating a handle to a const would not be allowed.
 **
 *
 * If the preprocessor symbol RW_NETWORK_DEBUG is set, then a test for
 * nil pointers is done before any operation involving a dereference, except
 * for the conversion to a pointer.  The conversion to a pointer is not
 * tested, because often this is called explicitly to test if we are referring
 * to a nil pointer.
 */

#include <rw/network/pkgdefs.h>
#include <rw/rwerr.h>
#include <rw/tools/atomic.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_DEPRECATE_MACRO("RWNetHandle", "Use RWTNetHandle instead")
#  define RWNetHandle RWTNetHandle
#endif

template< class C >
class RWTNetHandle
{
public:
    enum StaticCtor { staticCtor };

    RWTNetHandle(typename RWTNetHandle<C>::StaticCtor);
    // Statically initialized handle. Does nothing because the handle could
    // already be in use.

    RWTNetHandle(C* object = 0);
    // Initialize the handle to point to obj.  obj must be an object allocated
    // on the heap.  It will be deleted automatically when no more Handles
    // reference it.

    RWTNetHandle(const RWTNetHandle<C>& other);
    // Construct a handle to the same data that x points to.

    ~RWTNetHandle();
    // Deletes the object being referenced if no more Handles are pointing to it.

    RWTNetHandle<C>&
    operator=(const RWTNetHandle<C>& other);
    // Set this pointer to point to the same thing as x.  The object currently
    // being pointed to is deleted if this was the last pointer to it.

    bool
    operator==(const RWTNetHandle<C>& other) const;

    bool
    operator!=(const RWTNetHandle<C>& other) const;

    C& operator*() const;
    C* operator->() const;
    // Dereference operators.  These return the object pointed to.  If either
    // of the RW_NETWORK_DEBUG or RWHANDLE_CHECK macros is set, then an exception
    // is thrown if the pointer being dereferenced is the null pointer.

    operator C* () const;
    // Obtain a native C++ pointer to the object pointed to.
    // Unlike the dereference operators, this does not check first if the
    // pointer is nil. Often this function is called specifically to check
    // if the reference is nil.

    bool
    isValid() const;
    // Returns true if this handle refers to an object

private:
    RWTAtomic<size_t>* counter_;
    // This is a shared pointer to the reference count

    C* object_;
    // This is a wrapper for the object being reference counted.

    void attach();
    void detach();
    // Increment/Decrement reference count as appropriate.

    void validate() const;
    // Test for nil pointer when dereferencing.  If RW_NETWORK_DEBUG
    // is set, and if this is a nil pointer, then validate will call
    // RWThrow
};


template< class C >
inline
RWTNetHandle<C>::RWTNetHandle(typename RWTNetHandle<C>::StaticCtor)
{
    // initialize nothing, may be in use!
}

template< class C >
inline bool
RWTNetHandle<C>::isValid() const
{
    return (0 != object_);
}

template< class C >
inline void
RWTNetHandle<C>::validate() const
{
#if defined(RW_NETWORK_DEBUG)
    if (0 == object_) {
        RWTHROW(RWInternalErr("attempt to dereference a nil handle"));
    }
#endif
}

template< class C >
inline bool
RWTNetHandle<C>::operator==(const RWTNetHandle<C>& other) const
{
    return object_ == other.object_;
}

template< class C >
inline bool
RWTNetHandle<C>::operator!=(const RWTNetHandle<C>& other) const
{
    return object_ != other.object_;
}

template< class C >
inline C&
RWTNetHandle<C>::operator*() const
{
    validate();
    return *object_;
}

template< class C >
inline C*
RWTNetHandle<C>::operator->() const
{
    validate();
    return object_;
}

template< class C >
inline RWTNetHandle<C>::operator C* () const
{
    return object_;
}

#ifdef RW_NO_IMPLICIT_INCLUSION
#  include <rw/network/RWTNetHandle.cc>
#endif

#endif // __rw_network_RWTNetHandle_h__
