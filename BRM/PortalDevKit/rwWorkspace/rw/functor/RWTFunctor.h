#ifndef rw_functor_RWTFunctor_h_
#define rw_functor_RWTFunctor_h_
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor.h#1 $
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

/**************************************************************************
 *
 * Description:
 *
 * The handle class for functor bodies that are invoked with two caller
 * arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>
#include <rw/tools/refwrap.h>
#include <rw/tools/traits/RWTEnableIf.h>

#if defined(DOXYGEN)

/**
 * \ingroup functor_module
 *
 * \brief
 * A generic function object.
 *
 * RWTFunctor represents a generic function object that can be called with
 * \c As... parameters and returns \c R.
 *
 * \note
 * RWTFunctor supports calling functions with between 0 and 10 parameters,
 * inclusive.
 *
 * \example
 * \code
 * #include <rw/functor/RWTFunctor.h>
 *
 * void foo(int x) {
 *     std::cout << "x is " << x << std::endl;
 * }
 *
 * int main() {
 *     // Associate the functor with the global function 'foo'
 *     RWTFunctor<void(int)> functor = foo;
 *
 *     // Invoke the functor.
 *     functor(42);
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
template <typename R, typename As...>
class RWTFunctor<R(As...)>
{
public:
    /**
     * Constructs an invalid function object. Self will need to be
     * associated with a function or function object before it can be
     * invoked.
     */
    RWTFunctor();

    /**
     * Constructs an invalid function object. This constructor assumes the
     * object is constructed with static storage duration and does not
     * explicitly initialize any of its members.
     */
    RWTFunctor(RWStaticCtor);

    /**
     * Copy constructor. Binds self to the functor body instance of
     * \a other.
     */
    RWTFunctor(const RWTFunctor<R(As...)>& other);

    /**
     * Constructs a function object associated with \a callable. When
     * operator() is invoked, \a callable will be called.
     */
    template <typename C>
    RWTFunctor(C callable);

    /**
     * Assignment operator. Binds self to the functor body instance of
     * \a other.
     */
    RWTFunctor<R(As...)>&
    operator=(const RWTFunctor<R(As...)>& other);

    /**
     * Assignment operator. When operator() is invoked, \a callable will be
     * called.
     */
    template <typename C>
    RWTFunctor<R(As...)>&
    operator=(C callable);

    /**
     * Invokes the callable associated with self, passing parameters \a a
     * and returning the result. If the underlying callable has not been
     * set, throws RWTHRInvalidPointer.
     */
    R operator()(As&& ... a) const;
};

#else

template <typename T> class RWTFunctor;

template <typename S, typename T>
struct RWTIsFunctor {
    static const bool value = false;
};

template <typename S>
struct RWTIsFunctor<S, RWTFunctor<S> > {
    static const bool value = true;
};

template <typename R>
class RWTFunctorImpBase0 : public RWBodyBase
{
public:
    virtual R run() const = 0;
};

template <typename C, typename R>
class RWTFunctorImp0 : public RWTFunctorImpBase0<R>
{
public:
    RWTFunctorImp0(C callable) : callable_(callable)
    {
    }

    R run() const
    {
        return (R)rwUnwrapReference((C&)callable_)();
    }

    C callable_;
};

template <typename R>
class RWTFunctor<R()> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R()>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp0<C, R>(callable))
    {
    }

    RWTFunctor<R()>&
    operator=(const RWTFunctor<R()>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R()>&
    operator=(C callable)
    {
        RWTFunctor<R()> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()() const
    {
        return body().run();
    }

protected:
    RWTFunctor(RWTFunctorImpBase0<R>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase0<R>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase0<R>&)RWHandleBase::body();
    }
};


template <typename R, typename A1>
class RWTFunctorImpBase1 : public RWBodyBase
{
public:
    virtual R run(A1 a1) const = 0;
};

template <typename C, typename R, typename A1>
class RWTFunctorImp1 : public RWTFunctorImpBase1<R, A1>
{
public:
    RWTFunctorImp1(C callable) : callable_(callable)
    {
    }

    R run(A1 a1) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1);
#endif
    }

    C callable_;
};

template <typename R, typename A1>
class RWTFunctor<R(A1)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp1<C, R, A1>(callable))
    {
    }

    RWTFunctor<R(A1)>&
    operator=(const RWTFunctor<R(A1)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1));
#else
        return body().run(a1);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase1<R, A1>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase1<R, A1>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase1<R, A1>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2>
class RWTFunctorImpBase2 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2) const = 0;
};

template <typename C, typename R, typename A1, typename A2>
class RWTFunctorImp2 : public RWTFunctorImpBase2<R, A1, A2>
{
public:
    RWTFunctorImp2(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2>
class RWTFunctor<R(A1, A2)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp2<C, R, A1, A2>(callable))
    {
    }

    RWTFunctor<R(A1, A2)>&
    operator=(const RWTFunctor<R(A1, A2)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2));
#else
        return body().run(a1, a2);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase2<R, A1, A2>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase2<R, A1, A2>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase2<R, A1, A2>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3>
class RWTFunctorImpBase3 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3>
class RWTFunctorImp3 : public RWTFunctorImpBase3<R, A1, A2, A3>
{
public:
    RWTFunctorImp3(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3>
class RWTFunctor<R(A1, A2, A3)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp3<C, R, A1, A2, A3>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3)>&
    operator=(const RWTFunctor<R(A1, A2, A3)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3));
#else
        return body().run(a1, a2, a3);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase3<R, A1, A2, A3>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase3<R, A1, A2, A3>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase3<R, A1, A2, A3>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3, typename A4>
class RWTFunctorImpBase4 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3, A4 a4) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3, typename A4>
class RWTFunctorImp4 : public RWTFunctorImpBase4<R, A1, A2, A3, A4>
{
public:
    RWTFunctorImp4(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3, A4 a4) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3, a4);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3, typename A4>
class RWTFunctor<R(A1, A2, A3, A4)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3, A4)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3, A4), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp4<C, R, A1, A2, A3, A4>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3, A4)>&
    operator=(const RWTFunctor<R(A1, A2, A3, A4)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3, A4)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3, A4)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3, A4 a4) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4));
#else
        return body().run(a1, a2, a3, a4);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase4<R, A1, A2, A3, A4>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase4<R, A1, A2, A3, A4>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase4<R, A1, A2, A3, A4>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
class RWTFunctorImpBase5 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
class RWTFunctorImp5 : public RWTFunctorImpBase5<R, A1, A2, A3, A4, A5>
{
public:
    RWTFunctorImp5(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3, a4, a5);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
class RWTFunctor<R(A1, A2, A3, A4, A5)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3, A4, A5)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3, A4, A5), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp5<C, R, A1, A2, A3, A4, A5>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3, A4, A5)>&
    operator=(const RWTFunctor<R(A1, A2, A3, A4, A5)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3, A4, A5)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3, A4, A5)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5));
#else
        return body().run(a1, a2, a3, a4, a5);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase5<R, A1, A2, A3, A4, A5>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase5<R, A1, A2, A3, A4, A5>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase5<R, A1, A2, A3, A4, A5>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class RWTFunctorImpBase6 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class RWTFunctorImp6 : public RWTFunctorImpBase6<R, A1, A2, A3, A4, A5, A6>
{
public:
    RWTFunctorImp6(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3, a4, a5, a6);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class RWTFunctor<R(A1, A2, A3, A4, A5, A6)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3, A4, A5, A6)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3, A4, A5, A6), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp6<C, R, A1, A2, A3, A4, A5, A6>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3, A4, A5, A6)>&
    operator=(const RWTFunctor<R(A1, A2, A3, A4, A5, A6)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3, A4, A5, A6)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3, A4, A5, A6)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6));
#else
        return body().run(a1, a2, a3, a4, a5, a6);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase6<R, A1, A2, A3, A4, A5, A6>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase6<R, A1, A2, A3, A4, A5, A6>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase6<R, A1, A2, A3, A4, A5, A6>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class RWTFunctorImpBase7 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class RWTFunctorImp7 : public RWTFunctorImpBase7<R, A1, A2, A3, A4, A5, A6, A7>
{
public:
    RWTFunctorImp7(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3, a4, a5, a6, a7);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3, A4, A5, A6, A7), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp7<C, R, A1, A2, A3, A4, A5, A6, A7>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7)>&
    operator=(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7));
#else
        return body().run(a1, a2, a3, a4, a5, a6, a7);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase7<R, A1, A2, A3, A4, A5, A6, A7>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase7<R, A1, A2, A3, A4, A5, A6, A7>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase7<R, A1, A2, A3, A4, A5, A6, A7>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
class RWTFunctorImpBase8 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
class RWTFunctorImp8 : public RWTFunctorImpBase8<R, A1, A2, A3, A4, A5, A6, A7, A8>
{
public:
    RWTFunctorImp8(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7), rw_forward<A8>(a8));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3, a4, a5, a6, a7, a8);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
class RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp8<C, R, A1, A2, A3, A4, A5, A6, A7, A8>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8)>&
    operator=(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7), rw_forward<A8>(a8));
#else
        return body().run(a1, a2, a3, a4, a5, a6, a7, a8);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase8<R, A1, A2, A3, A4, A5, A6, A7, A8>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase8<R, A1, A2, A3, A4, A5, A6, A7, A8>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase8<R, A1, A2, A3, A4, A5, A6, A7, A8>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
class RWTFunctorImpBase9 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
class RWTFunctorImp9 : public RWTFunctorImpBase9<R, A1, A2, A3, A4, A5, A6, A7, A8, A9>
{
public:
    RWTFunctorImp9(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7), rw_forward<A8>(a8), rw_forward<A9>(a9));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
class RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp9<C, R, A1, A2, A3, A4, A5, A6, A7, A8, A9>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9)>&
    operator=(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7), rw_forward<A8>(a8), rw_forward<A9>(a9));
#else
        return body().run(a1, a2, a3, a4, a5, a6, a7, a8, a9);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase9<R, A1, A2, A3, A4, A5, A6, A7, A8, A9>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase9<R, A1, A2, A3, A4, A5, A6, A7, A8, A9>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase9<R, A1, A2, A3, A4, A5, A6, A7, A8, A9>&)RWHandleBase::body();
    }
};


template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
class RWTFunctorImpBase10 : public RWBodyBase
{
public:
    virtual R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const = 0;
};

template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
class RWTFunctorImp10 : public RWTFunctorImpBase10<R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>
{
public:
    RWTFunctorImp10(C callable) : callable_(callable)
    {
    }

    R run(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return (R)rwUnwrapReference((C&)callable_)(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7), rw_forward<A8>(a8), rw_forward<A9>(a9), rw_forward<A10>(a10));
#else
        return (R)rwUnwrapReference((C&)callable_)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
#endif
    }

    C callable_;
};

template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
class RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)> : public RWHandleBase
{
public:
    typedef R result_type;

    RWTFunctor(void) : RWHandleBase()
    {
    }

    RWTFunctor(RWStaticCtor s) : RWHandleBase(s)
    {
    }

    RWTFunctor(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>& other) : RWHandleBase(other)
    {
    }

    template <typename C>
    RWTFunctor(C callable, typename RWTEnableIf < !RWTIsFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), C>::value >::type* = 0)
        : RWHandleBase(new RWTFunctorImp10<C, R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>(callable))
    {
    }

    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>&
    operator=(const RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>& other)
    {
        if (this != &other) {
            RWHandleBase::operator=(other);
        }
        return *this;
    }

    template <typename C>
    RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>&
    operator=(C callable)
    {
        RWTFunctor<R(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)> functor(callable);
        RWHandleBase::operator=(functor);
        return *this;
    }

    R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const
    {
#if !defined(RW_NO_RVALUE_REFERENCES)
        return body().run(rw_forward<A1>(a1), rw_forward<A2>(a2), rw_forward<A3>(a3), rw_forward<A4>(a4), rw_forward<A5>(a5), rw_forward<A6>(a6), rw_forward<A7>(a7), rw_forward<A8>(a8), rw_forward<A9>(a9), rw_forward<A10>(a10));
#else
        return body().run(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
#endif
    }

protected:
    RWTFunctor(RWTFunctorImpBase10<R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>* imp) : RWHandleBase(imp)
    {
    }

    RWTFunctorImpBase10<R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>& body() const
    {
        // Throws RWTHRInvalidPointer if no imp assigned!
        return (RWTFunctorImpBase10<R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>&)RWHandleBase::body();
    }
};

// Instantiate common functor types for use in downstream products.
template class RW_FUNCTOR_GLOBAL RWTFunctor<void()>;
template class RW_FUNCTOR_GLOBAL RWTFunctorImpBase0<void>;

#endif

#endif // rw_functor_RWTFunctor_h_
