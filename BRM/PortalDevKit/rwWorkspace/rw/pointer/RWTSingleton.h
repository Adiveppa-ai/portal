#ifndef __rw_pointer_RWTSingleton_h__
#define __rw_pointer_RWTSingleton_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTSingleton.h#1 $
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

#include <rw/pointer/RWTCountingPointer.h>
#include <rw/pointer/pkgdefs.h>
#include <rw/once.h>
#include <new>

#ifdef _WIN32
#  pragma warning(push)
#  pragma warning(disable:4345)
#endif

//forward declaration
class RWMutexLock;

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Ensures that a class has only one instance and provides a global point of
 * access to it.
 *
 * RWTSingleton ensures that a class has only one instance, and provides a
 * global point of access to it. This is an Object Creational pattern. For
 * more information, see <em>Design Patterns</em> by Gamma, Helm, Johnson,
 * and Vlissides.
 *
 * \example
 * \code
 * #include <rw/pointer/RWTSingleton.h>
 * #include <iostream>
 *
 * class Foo
 * {
 * public:
 *     void function() {
 *         std::cout << "I'm a foo example" << std::endl;
 *     }
 * };
 *
 * RWTCountingPointer<Foo> singleFooPtr = RWTSingleton<Foo>::instance();
 *
 * int main(void)
 * {
 *     singleFooPtr->function();
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
template <class T>
class RWTSingleton
{

public:

    /**
     * Creates and returns the instance of \c T, if it has not already been
     * created.
     */
    static RWTCountingPointer<T, RWAtomicCounter>&
    instance()
    {
        initInstanceOnce_((void(*)())RWTSingleton< T >::initInstance);
        return ptr_;
    }

protected:

    /**
     * The constructor is protected to ensure that only one instance can
     * ever get created.
     */
    RWTSingleton() {}

    /**
     * Protected accessor function that gives access to the class state.
     * Inherited classes use this function.
     */
    static RWTCountingPointer<T, RWAtomicCounter>&
    get()
    {
        return ptr_;
    }

private:

    static void
    initInstance()
    {
        ptr_ = new(std::nothrow) T();
        RW_ASSERT(ptr_.isValid());
    }

private:

    //--Encapsulated refcounted pointer
    static RWTCountingPointer<T, RWAtomicCounter> ptr_;

    static RWOnce initInstanceOnce_;
};

// Initialize static member
#if defined(_WIN32)
template <class T>
/* static */ RWTCountingPointer<T, RWAtomicCounter>
RWTSingleton<T>::ptr_ = RWStaticCtor();
#else
template <class T>
/* static */ RWTCountingPointer<T, RWAtomicCounter>
RWTSingleton<T>::ptr_(RW_STATIC_CTOR);
#endif

// Initialize static member
template <class T>
/* static */ RWOnce
RWTSingleton<T>::initInstanceOnce_ = RW_ONCE_INITIALIZER;

#ifdef _WIN32
#  pragma warning(pop)
#endif  // pragma warning(disable:4345)

#endif // __rw_pointer_RWTSingleton_h__
