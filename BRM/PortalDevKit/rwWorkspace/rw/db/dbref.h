#ifndef __RWDB_DBREF_H__
#define __RWDB_DBREF_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbref.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **************************************************************************/

#include <rw/db/dbmutex.h>
#include <rw/db/defs.h>
#include <rw/tools/atomic.h>

class RWDBReference
{
public:
    RWDBReference() : refCount_() {}
    virtual ~RWDBReference() {}

    void addReference()
    {
        ++refCount_;
    }

    long removeReference()
    {
        return --refCount_;
    }

    long references() const
    {
        return refCount_.load(rw_mem_order_acquire);
    }

private:
    RWTAtomic<long>  refCount_;

    // unimplemented
    RWDBReference(const RWDBReference&);
    RWDBReference& operator=(const RWDBReference&);
};


/////////////////////////////////////////////////////////////////////
//
//  RWDBCountedRef<T>
//
//  This class is a simple class that manages the lifetimes of objects
//     that inherit from RWDBReference.  The class is responsible for
//     all the reference count management and object ownership sharing
//     and transfer. (Note: For a multithread level II safe version of
//     this class, look at RWDBMTCountedRef.)
//  This class also allows the encapsulated object to have a NULL
//     pointer, which allows users of this class to associate an invalid
//     (or NULL) object state when required. (Plus, sometimes, it's nice
//     to have a default constructor.)
//
/////////////////////////////////////////////////////////////////////
template<class T>
class RWDBCountedRef
{
public:
    RWDBCountedRef(T* impl)
        : impl_(impl)
    {
        if (impl_) {
            static_cast<RWDBReference*>(impl_)->addReference();
        }
    }

    RWDBCountedRef(const RWDBCountedRef<T>& ref)
        : impl_(ref.impl_)   // Always assign, even if NULL
    {
        if (ref.impl_) {
            static_cast<RWDBReference*>(ref.impl_)->addReference();
        }
    }

    ~RWDBCountedRef()
    {
        detach();
    }

    RWDBCountedRef<T>& operator=(const RWDBCountedRef<T>& rhs)
    {
        if (this == &rhs) {
            return *this;
        }

        if (rhs.impl_) {
            static_cast<RWDBReference*>(rhs.impl_)->addReference();
        }
        detach();
        impl_ = rhs.impl_;
        return *this;
    }

    RWDBCountedRef<T>& operator=(T* impl)
    {
        if (impl) {
            static_cast<RWDBReference*>(impl)->addReference();
        }
        detach();
        impl_ = impl;
        return *this;
    }

    operator T* () const
    {
        return impl_;
    }

    T* operator->() const
    {
        RW_ASSERT(impl_);
        return impl_;
    }

    T& operator*() const
    {
        RW_ASSERT(impl_);
        return *impl_;
    }

    bool operator==(const RWDBCountedRef<T>& rhs) const
    {
        return (impl_ && (impl_ == rhs.impl_));
    }
    bool operator!=(const RWDBCountedRef<T>& rhs) const
    {
        return !(impl_ && (impl_ == rhs.impl_));
    }
protected:
    void detach()
    {
        if (impl_ && static_cast<RWDBReference*>(impl_)->removeReference() < 1) {
            //If the following line fails when:
            // (1) It was already deleted?
            // (2) The object was created on the stack
            delete static_cast<RWDBReference*>(impl_);
            impl_ = NULL;
        }
    }
    T* impl_;
};

/////////////////////////////////////////////////////////////////////
//
//  RWDBMTCountedRef<T>
//
//     Multithread Level-II safe version of RWDBCountedRef.
//
/////////////////////////////////////////////////////////////////////
template<class T>
class RWDBMTCountedRef
{
    typedef  RWDBStaticMutex    RWDBMTCRefMutexType;
public:
    // We didn't assign NULL for initialization to avoid threading problems
    RWDBMTCountedRef(T* impl)
    {
        RWDBGUARD2(RWDBMTCRefMutexType, RWDBMTCountedRef::levelIIMutex());
        if (impl) {
            static_cast<RWDBReference*>(impl)->addReference();
        }
        impl_ = impl;
    }

    // We didn't assign NULL for initialization to avoid threading problems
    RWDBMTCountedRef(const RWDBMTCountedRef<T>& ref)
    {
        RWDBGUARD2(RWDBMTCRefMutexType, RWDBMTCountedRef::levelIIMutex());
        if (ref.impl_) {
            static_cast<RWDBReference*>(ref.impl_)->addReference();
        }
        impl_ = ref.impl_;
    }
    virtual ~RWDBMTCountedRef()
    {
        RWDBGUARD2(RWDBMTCRefMutexType, RWDBMTCountedRef::levelIIMutex());
        detach();
    }
    RWDBMTCountedRef<T>& operator=(const RWDBMTCountedRef<T>& rhs)
    {
        if (this == &rhs) {
            return *this;
        }

        RWDBGUARD2(RWDBMTCRefMutexType, levelIIMutex());

        if (rhs.impl_) {
            static_cast<RWDBReference*>(rhs.impl_)->addReference();
        }
        detach();
        impl_ = rhs.impl_;
        return *this;
    }
    RWDBMTCountedRef<T>& operator=(T* impl)
    {
        RWDBGUARD2(RWDBMTCRefMutexType, levelIIMutex());
        if (impl) {
            static_cast<RWDBReference*>(impl)->addReference();
        }
        detach();
        impl_ = impl;
        return *this;
    }
    operator T* () const
    {
        RWDBGUARD2(RWDBMTCRefMutexType, levelIIMutex());
        return impl_;
    }
    T* operator->() const
    {
        RWDBGUARD2(RWDBMTCRefMutexType, levelIIMutex());
        RW_ASSERT(impl_);
        return impl_;
    }
    T& operator*() const
    {
        RWDBGUARD2(RWDBMTCRefMutexType, levelIIMutex());
        RW_ASSERT(impl_);
        return *impl_;
    }
    bool operator==(const RWDBMTCountedRef<T>& rhs) const
    {
        RWDBGUARD2(RWDBMTCRefMutexType, levelIIMutex());
        return (impl_ && (impl_ == rhs.impl_));
    }
    bool operator!=(const RWDBMTCountedRef<T>& rhs) const
    {
        RWDBGUARD2(RWDBMTCRefMutexType, levelIIMutex());
        return !(impl_ && (impl_ == rhs.impl_));
    }
protected:
    /////////////////////////////////////////////////////////////////
    //
    // ::referenceCountingMutex (virtual)
    //   This method returns the mutex to use for MT Level-II safe
    //   reference counting.  Default implementation is to use the
    //   same mutex for all instances of this class, but you can
    //   override this method in a derived class like so to reduce
    //   contention for this mutex:
    //   template <class T>
    //   class RWDBMyLevelIISafeCountedRef : public RWDBMTCountedRef<T> {
    //          //copy of the levelIIMutex() method here.
    //   };
    //
    //   NOTE: If deriving from this class and overriding the
    //   levelIIMutex() virtual method, the constructor and
    //   destructor of this class still uses
    //   RWDBMTCountedRef::levelIIMutex() mutex. Additional code
    //   logic may be needed to circumvent these calls.
    //
    /////////////////////////////////////////////////////////////////
    virtual RWDB_GLOBAL RWDBMTCRefMutexType& levelIIMutex() const;
    void detach()
    {
        //No need for the MT Guard, because we are already heavily
        //  guarded against concurrent access.
        if (impl_ && reinterpret_cast<RWDBReference*>(impl_)->removeReference() < 1) {
            //If the following line fails then:
            // (1) It was already deleted?
            // (2) The object was created on the stack
            delete reinterpret_cast<RWDBReference*>(impl_);
            impl_ = NULL;
        }
    }
private:
    T* impl_;
};

/////////////////////////////////////////////////////////////////////
//
//  RWDBMTCountedRef<T>::levelIIMutex() Specializations
//
/////////////////////////////////////////////////////////////////////
RWDBTEMPLATESPECDECL RWDB_GLOBAL
RWDBStaticMutex&
RWDBMTCountedRef<RWDBDatabaseImp>::levelIIMutex() const;

RWDBTEMPLATESPECDECL RWDB_GLOBAL
RWDBStaticMutex&
RWDBMTCountedRef<RWDBDatabaseCallbackImp>::levelIIMutex() const;

/////////////////////////////////////////////////////////////////////
//
//  RWDBCountedRefWithDeallocator<T, D>
//
//  This class is a simple "garbage collector" for classes
//  that want to take more control over their deallocation.
//  See above for examples of deallocators.
//
/////////////////////////////////////////////////////////////////////
template<class T, class D>
class RWDBCountedRefWithDeallocator
{
public:
    RWDBCountedRefWithDeallocator()
        : impl_(NULL)
    {
    }
    RWDBCountedRefWithDeallocator(T* impl)
        : impl_(impl)
    {
        if (impl_) {
            static_cast<RWDBReference*>(impl_)->addReference();
        }
    }
    RWDBCountedRefWithDeallocator(const RWDBCountedRefWithDeallocator<T, D>& ref)
    {
        if (ref.impl_) {
            static_cast<RWDBReference*>(ref.impl_)->addReference();
            // We don't need to detach because this is a constructor.
            // Nothing to detach!
        }
        // Assignment should always succeed. Even if the ref.impl_ is NULL
        impl_ = ref.impl_;
    }
    ~RWDBCountedRefWithDeallocator()
    {
        detach();
    }
    RWDBCountedRefWithDeallocator<T, D>&
    operator=(const RWDBCountedRefWithDeallocator<T, D>& rhs)
    {
        if (this == &rhs) {
            return *this;
        }

        if (rhs.impl_) {
            static_cast<RWDBReference*>(rhs.impl_)->addReference();
        }
        detach();
        impl_ = rhs.impl_;
        return *this;
    }
    RWDBCountedRefWithDeallocator<T, D>& operator=(T* impl)
    {
        if (impl) {
            static_cast<RWDBReference*>(impl)->addReference();
        }
        detach();
        impl_ = impl;
        return *this;
    }
    operator T* () const
    {
        return impl_;
    }
    T* operator->() const
    {
        RW_ASSERT(impl_);
        return impl_;
    }
    T& operator*() const
    {
        RW_ASSERT(impl_);
        return *impl_;
    }
    bool operator==(const RWDBCountedRefWithDeallocator<T, D>& rhs) const
    {
        return (impl_ && (impl_ == rhs.impl_));
    }
    bool operator!=(const RWDBCountedRefWithDeallocator<T, D>& rhs) const
    {
        return !(impl_ && (impl_ == rhs.impl_));
    }
protected:
    void detach()
    {
        if (impl_ && static_cast<RWDBReference*>(impl_)->removeReference() < 1) {
            //Give the Deallocator a whack at it.  If it decides to delete
            //  the pointer, then it is also responsible for setting it to
            //  NULL.
            D::discard(impl_);

            //If the following line fails when:
            // (1) It was already deleted?
            // (2) The object was created on the stack
            delete static_cast<RWDBReference*>(impl_);
            impl_ = NULL;
        }
    }
    T* impl_;
};

#endif
