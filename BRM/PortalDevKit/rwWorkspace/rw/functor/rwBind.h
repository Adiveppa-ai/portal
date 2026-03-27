#ifndef rw_functor_rwBind_h_
#define rw_functor_rwBind_h_
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/rwBind.h#1 $
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

#include <rw/functor/RWTPlaceholder.h>
#include <rw/functor/pkgdefs.h>
#include <rw/edefs.h>
#include <rw/tools/refwrap.h>
#include <rw/tools/traits/RWTEnableIf.h>
#include <rw/tools/traits/RWTIdentity.h>
#include <rw/tools/traits/RWTIsBaseOf.h>
#include <rw/tools/traits/RWTRemoveCV.h>
#include <rw/tools/traits/RWTRemoveReference.h>
#include <rw/tools/traits/RWTResultOf.h>

#if defined(DOXYGEN)

/**
 * \ingroup functor_module
 *
 * \brief
 * Binds a callable and arguments into a callable object
 *
 * Constructs and returns a callable object of an unspecified type that
 * invokes \a c, passing arguments \a args, and returns the result.
 *
 * Assuming a bind invocation of the form
 * <tt>rwBind(f, t1, t2, ..., tN)</tt>, the callable will be invoked as
 * follows:
 *
 * - If \c f is a pointer to a member function of type \c T, and \c t1 is
 * either an object of type \c T, a reference to an object of type \c T, or
 * a reference to an object of a type derived from \c T:
 * \code
 * (t1.*f)(t2, ..., tN)
 * \endcode
 *
 * - If \c f is a pointer to a member function of type \c T and \c t1 is not
 * one of the types described above:
 * \code
 * ((*t1).*f)(t2, ..., tN)
 * \endcode
 *
 * - Otherwise:
 * \code
 * f(t1, t2, ..., tN)
 * \endcode
 *
 * Arguments to rwBind can be specified as placeholder values (\c rw1,
 * \c rw2, ..., \c rw10), allowing the arguments to be provided when the
 * returned callable object is invoked.
 *
 * \example
 * \code
 * int add(int x, int y) {
 *     return x + y;
 * }
 *
 * // Bind the function. The first parameter will be provided when f is
 * // invoked, the second parameter is specified when the function is bound.
 * RWTFunctor<int(int)> f = rwBind(add, rw1, 5);
 *
 * // When f is invoked, the first parameter to add must be specified
 * int z = f(10); // returns 15
 * \endcode
 * \endexample
 *
 * \note
 * This function allows specifying a maximum of 10 arguments.
 */
template <typename C, typename... As>
unspecified_type rwBind(C&& c, As&& ... args);

/**
 * \ingroup functor_module
 *
 * \brief
 * Binds a callable and arguments into a callable object that returns \c R
 *
 * Constructs and returns a callable object of an unspecified type that
 * invokes \a c, passing arguments \a args, and returns the result as type
 * \c R.
 *
 * Assuming a bind invocation of the form
 * <tt>rwBind<R>(f, t1, t2, ..., tN)</tt>, the callable will be invoked as
 * follows:
 *
 * - If \c f is a pointer to a member function of type \c T, and \c t1 is
 * either an object of type \c T, a reference to an object of type \c T, or
 * a reference to an object of a type derived from \c T:
 * \code
 * (t1.*f)(t2, ..., tN)
 * \endcode
 *
 * - If \c f is a pointer to a member function of type \c T and \c t1 is not
 * one of the types described above:
 * \code
 * ((*t1).*f)(t2, ..., tN)
 * \endcode
 *
 * - Otherwise:
 * \code
 * f(t1, t2, ..., tN)
 * \endcode
 *
 * Arguments to rwBind can be specified as placeholder values (\c rw1,
 * \c rw2, ..., \c rw10), allowing the arguments to be provided when the
 * returned callable object is invoked.
 *
 * \example
 * \code
 * int add(int x, int y) {
 *     return x + y;
 * }
 *
 * // Bind the function. The first parameter will be provided when f is
 * // invoked, the second parameter is specified when the function is bound.
 * RWTFunctor<long(int)> f = rwBind<long>(add, rw1, 5);
 *
 * // When f is invoked, the first parameter to add must be specified
 * long z = f(10); // returns 15 as a long
 * \endcode
 * \endexample
 *
 * \note
 * This function allows specifying a maximum of 10 arguments.
 */
template <typename R, typename C, typename... As>
unspecified_type rwBind<R>(C&& c, As&& ... args);

#else



#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_ARG_1(A, P1, a, p1)                                  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1>(  \
            rw_forward<A>(a), rw_forward<P1>(p1))

#  define RW_BIND_ARG_2(A, P1, P2, a, p1, p2)                              \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2))

#  define RW_BIND_ARG_3(A, P1, P2, P3, a, p1, p2, p3)                          \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2),          \
            rw_forward<P3>(p3))

#  define RW_BIND_ARG_4(A, P1, P2, P3, P4, a, p1, p2, p3, p4)                      \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2),              \
            rw_forward<P3>(p3), rw_forward<P4>(p4))

#  define RW_BIND_ARG_5(A, P1, P2, P3, P4, P5, a, p1, p2, p3, p4, p5)                  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2),                  \
            rw_forward<P3>(p3), rw_forward<P4>(p4), rw_forward<P5>(p5))

#  define RW_BIND_ARG_6(A, P1, P2, P3, P4, P5, P6, a, p1, p2, p3, p4, p5, p6)              \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2), rw_forward<P3>(p3),  \
            rw_forward<P4>(p4), rw_forward<P5>(p5), rw_forward<P6>(p6))

#  define RW_BIND_ARG_7(A, P1, P2, P3, P4, P5, P6, P7, a, p1, p2, p3, p4, p5, p6, p7)          \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2), rw_forward<P3>(p3),      \
            rw_forward<P4>(p4), rw_forward<P5>(p5), rw_forward<P6>(p6), rw_forward<P7>(p7))

#  define RW_BIND_ARG_8(A, P1, P2, P3, P4, P5, P6, P7, P8, a, p1, p2, p3, p4, p5, p6, p7, p8)      \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7, P8>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2), rw_forward<P3>(p3),          \
            rw_forward<P4>(p4), rw_forward<P5>(p5), rw_forward<P6>(p6), rw_forward<P7>(p7),        \
            rw_forward<P8>(p8))

#  define RW_BIND_ARG_9(A, P1, P2, P3, P4, P5, P6, P7, P8, P9, a, p1, p2, p3, p4, p5, p6, p7, p8, p9)  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7, P8, P9>(  \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2), rw_forward<P3>(p3),              \
            rw_forward<P4>(p4), rw_forward<P5>(p5), rw_forward<P6>(p6), rw_forward<P7>(p7),            \
            rw_forward<P8>(p8), rw_forward<P9>(p9))

#  define RW_BIND_ARG_10(A, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, a, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>(        \
            rw_forward<A>(a), rw_forward<P1>(p1), rw_forward<P2>(p2), rw_forward<P3>(p3), rw_forward<P4>(p4),     \
            rw_forward<P5>(p5), rw_forward<P6>(p6), rw_forward<P7>(p7), rw_forward<P8>(p8), rw_forward<P9>(p9),   \
            rw_forward<P10>(p10))

#else
#  define RW_BIND_ARG_1(A, P1, a, p1)                                  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1>(  \
            a, p1)

#  define RW_BIND_ARG_2(A, P1, P2, a, p1, p2)                              \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2>(  \
            a, p1, p2)

#  define RW_BIND_ARG_3(A, P1, P2, P3, a, p1, p2, p3)                          \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3>(  \
            a, p1, p2, p3)

#  define RW_BIND_ARG_4(A, P1, P2, P3, P4, a, p1, p2, p3, p4)                      \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4>(  \
            a, p1, p2, p3, p4)

#  define RW_BIND_ARG_5(A, P1, P2, P3, P4, P5, a, p1, p2, p3, p4, p5)                  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5>(  \
            a, p1, p2, p3, p4, p5)

#  define RW_BIND_ARG_6(A, P1, P2, P3, P4, P5, P6, a, p1, p2, p3, p4, p5, p6)              \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6>(  \
            a, p1, p2, p3, p4, p5, p6)

#  define RW_BIND_ARG_7(A, P1, P2, P3, P4, P5, P6, P7, a, p1, p2, p3, p4, p5, p6, p7)          \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7>(  \
            a, p1, p2, p3, p4, p5, p6, p7)

#  define RW_BIND_ARG_8(A, P1, P2, P3, P4, P5, P6, P7, P8, a, p1, p2, p3, p4, p5, p6, p7, p8)      \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7, P8>(  \
            a, p1, p2, p3, p4, p5, p6, p7, p8)

#  define RW_BIND_ARG_9(A, P1, P2, P3, P4, P5, P6, P7, P8, P9, a, p1, p2, p3, p4, p5, p6, p7, p8, p9)  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7, P8, P9>(  \
            a, p1, p2, p3, p4, p5, p6, p7, p8, p9)

#  define RW_BIND_ARG_10(A, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, a, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)  \
        RWTBindArg<RWTIsPlaceholder<A>::value>::template bind<A, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>(        \
            a, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#endif

#define RW_BIND_ARG_TYPE_1(A, P1) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1>::type

#define RW_BIND_ARG_TYPE_2(A, P1, P2) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2>::type

#define RW_BIND_ARG_TYPE_3(A, P1, P2, P3) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3>::type

#define RW_BIND_ARG_TYPE_4(A, P1, P2, P3, P4) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3, P4>::type

#define RW_BIND_ARG_TYPE_5(A, P1, P2, P3, P4, P5) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3, P4, P5>::type

#define RW_BIND_ARG_TYPE_6(A, P1, P2, P3, P4, P5, P6) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3, P4, P5, P6>::type

#define RW_BIND_ARG_TYPE_7(A, P1, P2, P3, P4, P5, P6, P7) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3, P4, P5, P6, P7>::type

#define RW_BIND_ARG_TYPE_8(A, P1, P2, P3, P4, P5, P6, P7, P8) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3, P4, P5, P6, P7, P8>::type

#define RW_BIND_ARG_TYPE_9(A, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3, P4, P5, P6, P7, P8, P9>::type

#define RW_BIND_ARG_TYPE_10(A, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
        typename RWTBindArgType<RWTIsPlaceholder<A>::value, A, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>::type

template <typename A1, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, typename A6 = void, typename A7 = void, typename A8 = void, typename A9 = void, typename A10 = void>
struct RWTAnyPlaceholder {
    static const bool value =
        RWTIsPlaceholder<A1>::value ||
        RWTIsPlaceholder<A2>::value ||
        RWTIsPlaceholder<A3>::value ||
        RWTIsPlaceholder<A4>::value ||
        RWTIsPlaceholder<A5>::value ||
        RWTIsPlaceholder<A6>::value ||
        RWTIsPlaceholder<A7>::value ||
        RWTIsPlaceholder<A8>::value ||
        RWTIsPlaceholder<A9>::value ||
        RWTIsPlaceholder<A10>::value;
};

template <typename T>
struct RWTBindArrayAsPointer {
    typedef T type;
};

template <typename T>
struct RWTBindArrayAsPointer<T[]> {
    typedef T* type;
};

template <typename T, size_t N>
struct RWTBindArrayAsPointer<T[N]> {
    typedef T* type;
};

struct RWDeducedType;

template <typename R, typename>
struct RWTBindResult {
    typedef R type;
};

template <typename T>
struct RWTBindResult<RWDeducedType, T> {
    typedef typename RWTResultOf<T>::type type;
};



#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type()>::type
rwInvoke(C&& c, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type()>::type)
           c();
}
#else
template <typename R, typename C>
typename RWTBindResult<R, C()>::type
rwInvoke(C& c, long)
{
    return (typename RWTBindResult<R, C()>::type)
           c();
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1)>::type
rwInvoke(C&& c, A1&& a1, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1)>::type)
           c(rw_forward<A1>(a1));
}
#else
template <typename R, typename C, typename A1>
typename RWTBindResult<R, C(A1&)>::type
rwInvoke(C& c, A1& a1, long)
{
    return (typename RWTBindResult<R, C(A1&)>::type)
           c(a1);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2)>::type)c(rw_forward<A1>(a1),
            rw_forward<A2>(a2));
}
#else
template <typename R, typename C, typename A1, typename A2>
typename RWTBindResult<R, C(A1&, A2&)>::type
rwInvoke(C& c, A1& a1, A2& a2, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&)>::type)
           c(a1, a2);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3>
typename RWTBindResult<R, C(A1&, A2&, A3&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&)>::type)
           c(a1, a2, a3);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, A4&& a4, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3),
             rw_forward<A4>(a4));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
typename RWTBindResult<R, C(A1&, A2&, A3&, A4&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, A4& a4, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&, A4&)>::type)c(a1, a2, a3, a4);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3),
             rw_forward<A4>(a4),
             rw_forward<A5>(a5));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&)>::type)
           c(a1, a2, a3, a4, a5);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3),
             rw_forward<A4>(a4),
             rw_forward<A5>(a5),
             rw_forward<A6>(a6));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&)>::type)
           c(a1, a2, a3, a4, a5, a6);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3),
             rw_forward<A4>(a4),
             rw_forward<A5>(a5),
             rw_forward<A6>(a6),
             rw_forward<A7>(a7));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&)>::type)
           c(a1, a2, a3, a4, a5, a6, a7);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7, A8)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7, A8)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3),
             rw_forward<A4>(a4),
             rw_forward<A5>(a5),
             rw_forward<A6>(a6),
             rw_forward<A7>(a7),
             rw_forward<A8>(a8));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&)>::type)
           c(a1, a2, a3, a4, a5, a6, a7, a8);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7, A8, A9)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7, A8, A9)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3),
             rw_forward<A4>(a4),
             rw_forward<A5>(a5),
             rw_forward<A6>(a6),
             rw_forward<A7>(a7),
             rw_forward<A8>(a8),
             rw_forward<A9>(a9));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&)>::type)
           c(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>::type
rwInvoke(C&& c, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9, A10&& a10, long)
{
    return (typename RWTBindResult<R, typename RWTRemoveReference<C>::type(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>::type)
           c(rw_forward<A1>(a1),
             rw_forward<A2>(a2),
             rw_forward<A3>(a3),
             rw_forward<A4>(a4),
             rw_forward<A5>(a5),
             rw_forward<A6>(a6),
             rw_forward<A7>(a7),
             rw_forward<A8>(a8),
             rw_forward<A9>(a9),
             rw_forward<A10>(a10));
}
#else
template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&, A10&)>::type
rwInvoke(C& c, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, A10& a10, long)
{
    return (typename RWTBindResult<R, C(A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&, A10&)>::type)
           c(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type
rwInvoke(CR(MT::*f)(), T&& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type
rwInvoke(CR(MT::*f)(), T&& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#else
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type
rwInvoke(CR(MT::*f)(), T& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type
rwInvoke(CR(MT::*f)(), T& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)()>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type
rwInvoke(CR(MT::*f)() const, T&& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type
rwInvoke(CR(MT::*f)() const, T&& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#else
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type
rwInvoke(CR(MT::*f)() const, T& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type
rwInvoke(CR(MT::*f)() const, T& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type
rwInvoke(CR(MT::*f)() volatile, T&& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type
rwInvoke(CR(MT::*f)() volatile, T&& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#else
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type
rwInvoke(CR(MT::*f)() volatile, T& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type
rwInvoke(CR(MT::*f)() volatile, T& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type
rwInvoke(CR(MT::*f)() const volatile, T&& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type
rwInvoke(CR(MT::*f)() const volatile, T&& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#else
template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type
rwInvoke(CR(MT::*f)() const volatile, T& t,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)();
}

template <typename R, typename CR, typename MT, typename T>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type
rwInvoke(CR(MT::*f)() const volatile, T& t,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)() const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)();
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type
rwInvoke(CR(MT::*f)(MA1), T&& t, A1&& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type
rwInvoke(CR(MT::*f)(MA1), T&& t, A1&& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type
rwInvoke(CR(MT::*f)(MA1), T& t, A1& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type
rwInvoke(CR(MT::*f)(MA1), T& t, A1& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const, T&& t, A1&& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const, T&& t, A1&& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const, T& t, A1& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const, T& t, A1& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) volatile, T&& t, A1&& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) volatile, T&& t, A1&& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) volatile, T& t, A1& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) volatile, T& t, A1& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const volatile, T&& t, A1&& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const volatile, T&& t, A1&& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const volatile, T& t, A1& a1,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1) const volatile, T& t, A1& a1,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2), T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2), T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2), T& t, A1& a1, A2& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2), T& t, A1& a1, A2& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const, T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const, T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const, T& t, A1& a1, A2& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const, T& t, A1& a1, A2& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) volatile, T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) volatile, T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) volatile, T& t, A1& a1, A2& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) volatile, T& t, A1& a1, A2& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const volatile, T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const volatile, T&& t, A1&& a1, A2&& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const volatile, T& t, A1& a1, A2& a2,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2) const volatile, T& t, A1& a1, A2& a2,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3), T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3), T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3), T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3), T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const, T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const, T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const, T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const, T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) volatile, T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) volatile, T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const volatile, T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3) const volatile, T& t, A1& a1, A2& a2, A3& a3,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4), T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4), T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8),
                                     rw_forward<A9>(a9));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9), T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8),
                                          rw_forward<A9>(a9));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9), T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9)>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8),
                                     rw_forward<A9>(a9));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8),
                                          rw_forward<A9>(a9));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8),
                                     rw_forward<A9>(a9));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8),
                                          rw_forward<A9>(a9));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif


#if !defined(RW_NO_RVALUE_REFERENCES)
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(rw_forward<A1>(a1),
                                     rw_forward<A2>(a2),
                                     rw_forward<A3>(a3),
                                     rw_forward<A4>(a4),
                                     rw_forward<A5>(a5),
                                     rw_forward<A6>(a6),
                                     rw_forward<A7>(a7),
                                     rw_forward<A8>(a8),
                                     rw_forward<A9>(a9));
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile, T&& t, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(rw_forward<A1>(a1),
                                          rw_forward<A2>(a2),
                                          rw_forward<A3>(a3),
                                          rw_forward<A4>(a4),
                                          rw_forward<A5>(a5),
                                          rw_forward<A6>(a6),
                                          rw_forward<A7>(a7),
                                          rw_forward<A8>(a8),
                                          rw_forward<A9>(a9));
}
#else
template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf<RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int>::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type)
           (rwUnwrapReference(t).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template <typename R, typename CR, typename MT, typename T, typename MA1, typename A1, typename MA2, typename A2, typename MA3, typename A3, typename MA4, typename A4, typename MA5, typename A5, typename MA6, typename A6, typename MA7, typename A7, typename MA8, typename A8, typename MA9, typename A9>
typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type
rwInvoke(CR(MT::*f)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile, T& t, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9,
         typename RWTEnableIf < !RWTIsBaseOf<MT, typename RWTUnwrapType<typename RWTRemoveReference<T>::type>::type>::value, int >::type)
{
    return (typename RWTBindResult<R, typename RWTIdentity<CR(MT::*)(MA1, MA2, MA3, MA4, MA5, MA6, MA7, MA8, MA9) const volatile>::type()>::type)
           ((*(rwUnwrapReference(t))).*f)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif


template <size_t P, typename A0, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, typename A6 = void, typename A7 = void, typename A8 = void, typename A9 = void, typename A10 = void>
struct RWTBindArgType {
    typedef typename RWTBindArgType < P - 1, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 >::type type;
};

template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct RWTBindArgType<0, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> {
    typedef A0 type;
};


#if defined(RW_GCC_VERSION) && (RW_GCC_VERSION < 40500)
#  define RW_AVOID_FORWARD_STATIC_CAST
#endif

template <size_t P>
struct RWTBindArg;

template <>
struct RWTBindArg<0> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A0>::type&&
    bind(typename RWTIdentity<A0>::type&& a0,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A0>(a0);
#  else
        return a0;
#  endif
    }

#else

    template <typename A0, typename A1>
    static A0&
    bind(A0& a0, A1&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2>
    static A0&
    bind(A0& a0, A1&, A2&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3>
    static A0&
    bind(A0& a0, A1&, A2&, A3&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static A0&
    bind(A0& a0, A1&, A2&, A3&, A4&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static A0&
    bind(A0& a0, A1&, A2&, A3&, A4&, A5&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static A0&
    bind(A0& a0, A1&, A2&, A3&, A4&, A5&, A6&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A0&
    bind(A0& a0, A1&, A2&, A3&, A4&, A5&, A6&, A7&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A0&
    bind(A0& a0, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A0&
    bind(A0& a0, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&)
    {
        return a0;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A0&
    bind(A0& a0, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&, A10&)
    {
        return a0;
    }

#endif
};

template <>
struct RWTBindArg<1> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A1>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&& a1,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A1>(a1);
#  else
        return a1;
#  endif
    }

#else

    template <typename A0, typename A1>
    static A1&
    bind(A0&, A1& a1)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2>
    static A1&
    bind(A0&, A1& a1, A2&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3>
    static A1&
    bind(A0&, A1& a1, A2&, A3&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static A1&
    bind(A0&, A1& a1, A2&, A3&, A4&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static A1&
    bind(A0&, A1& a1, A2&, A3&, A4&, A5&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static A1&
    bind(A0&, A1& a1, A2&, A3&, A4&, A5&, A6&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A1&
    bind(A0&, A1& a1, A2&, A3&, A4&, A5&, A6&, A7&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A1&
    bind(A0&, A1& a1, A2&, A3&, A4&, A5&, A6&, A7&, A8&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A1&
    bind(A0&, A1& a1, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&)
    {
        return a1;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A1&
    bind(A0&, A1& a1, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&, A10&)
    {
        return a1;
    }

#endif
};

template <>
struct RWTBindArg<2> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A2>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&& a2,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A2>(a2);
#  else
        return a2;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2>
    static A2&
    bind(A0&, A1&, A2& a2)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3>
    static A2&
    bind(A0&, A1&, A2& a2, A3&)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static A2&
    bind(A0&, A1&, A2& a2, A3&, A4&)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static A2&
    bind(A0&, A1&, A2& a2, A3&, A4&, A5&)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static A2&
    bind(A0&, A1&, A2& a2, A3&, A4&, A5&, A6&)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A2&
    bind(A0&, A1&, A2& a2, A3&, A4&, A5&, A6&, A7&)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A2&
    bind(A0&, A1&, A2& a2, A3&, A4&, A5&, A6&, A7&, A8&)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A2&
    bind(A0&, A1&, A2& a2, A3&, A4&, A5&, A6&, A7&, A8&, A9&)
    {
        return a2;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A2&
    bind(A0&, A1&, A2& a2, A3&, A4&, A5&, A6&, A7&, A8&, A9&, A10&)
    {
        return a2;
    }

#endif
};

template <>
struct RWTBindArg<3> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3,
         typename RWTIdentity<A4>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A3>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&& a3,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A3>(a3);
#  else
        return a3;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3>
    static A3&
    bind(A0&, A1&, A2&, A3& a3)
    {
        return a3;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static A3&
    bind(A0&, A1&, A2&, A3& a3, A4&)
    {
        return a3;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static A3&
    bind(A0&, A1&, A2&, A3& a3, A4&, A5&)
    {
        return a3;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static A3&
    bind(A0&, A1&, A2&, A3& a3, A4&, A5&, A6&)
    {
        return a3;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A3&
    bind(A0&, A1&, A2&, A3& a3, A4&, A5&, A6&, A7&)
    {
        return a3;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A3&
    bind(A0&, A1&, A2&, A3& a3, A4&, A5&, A6&, A7&, A8&)
    {
        return a3;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A3&
    bind(A0&, A1&, A2&, A3& a3, A4&, A5&, A6&, A7&, A8&, A9&)
    {
        return a3;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A3&
    bind(A0&, A1&, A2&, A3& a3, A4&, A5&, A6&, A7&, A8&, A9&, A10&)
    {
        return a3;
    }

#endif
};

template <>
struct RWTBindArg<4> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static typename RWTIdentity<A4>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&& a4)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A4>(a4);
#  else
        return a4;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static typename RWTIdentity<A4>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&& a4,
         typename RWTIdentity<A5>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A4>(a4);
#  else
        return a4;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static typename RWTIdentity<A4>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&& a4,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A4>(a4);
#  else
        return a4;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A4>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&& a4,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A4>(a4);
#  else
        return a4;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A4>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&& a4,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A4>(a4);
#  else
        return a4;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A4>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&& a4,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A4>(a4);
#  else
        return a4;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A4>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&& a4,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A4>(a4);
#  else
        return a4;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    static A4&
    bind(A0&, A1&, A2&, A3&, A4& a4)
    {
        return a4;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static A4&
    bind(A0&, A1&, A2&, A3&, A4& a4, A5&)
    {
        return a4;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static A4&
    bind(A0&, A1&, A2&, A3&, A4& a4, A5&, A6&)
    {
        return a4;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A4&
    bind(A0&, A1&, A2&, A3&, A4& a4, A5&, A6&, A7&)
    {
        return a4;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A4&
    bind(A0&, A1&, A2&, A3&, A4& a4, A5&, A6&, A7&, A8&)
    {
        return a4;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A4&
    bind(A0&, A1&, A2&, A3&, A4& a4, A5&, A6&, A7&, A8&, A9&)
    {
        return a4;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A4&
    bind(A0&, A1&, A2&, A3&, A4& a4, A5&, A6&, A7&, A8&, A9&, A10&)
    {
        return a4;
    }

#endif
};

template <>
struct RWTBindArg<5> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static typename RWTIdentity<A5>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&& a5)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A5>(a5);
#  else
        return a5;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static typename RWTIdentity<A5>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&& a5,
         typename RWTIdentity<A6>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A5>(a5);
#  else
        return a5;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A5>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&& a5,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A5>(a5);
#  else
        return a5;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A5>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&& a5,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A5>(a5);
#  else
        return a5;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A5>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&& a5,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A5>(a5);
#  else
        return a5;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A5>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&& a5,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A5>(a5);
#  else
        return a5;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    static A5&
    bind(A0&, A1&, A2&, A3&, A4&, A5& a5)
    {
        return a5;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static A5&
    bind(A0&, A1&, A2&, A3&, A4&, A5& a5, A6&)
    {
        return a5;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A5&
    bind(A0&, A1&, A2&, A3&, A4&, A5& a5, A6&, A7&)
    {
        return a5;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A5&
    bind(A0&, A1&, A2&, A3&, A4&, A5& a5, A6&, A7&, A8&)
    {
        return a5;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A5&
    bind(A0&, A1&, A2&, A3&, A4&, A5& a5, A6&, A7&, A8&, A9&)
    {
        return a5;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A5&
    bind(A0&, A1&, A2&, A3&, A4&, A5& a5, A6&, A7&, A8&, A9&, A10&)
    {
        return a5;
    }

#endif
};

template <>
struct RWTBindArg<6> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static typename RWTIdentity<A6>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&& a6)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A6>(a6);
#  else
        return a6;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A6>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&& a6,
         typename RWTIdentity<A7>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A6>(a6);
#  else
        return a6;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A6>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&& a6,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A6>(a6);
#  else
        return a6;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A6>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&& a6,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A6>(a6);
#  else
        return a6;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A6>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&& a6,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A6>(a6);
#  else
        return a6;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static A6&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6& a6)
    {
        return a6;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A6&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6& a6, A7&)
    {
        return a6;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A6&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6& a6, A7&, A8&)
    {
        return a6;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A6&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6& a6, A7&, A8&, A9&)
    {
        return a6;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A6&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6& a6, A7&, A8&, A9&, A10&)
    {
        return a6;
    }

#endif
};

template <>
struct RWTBindArg<7> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static typename RWTIdentity<A7>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&& a7)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A7>(a7);
#  else
        return a7;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A7>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&& a7,
         typename RWTIdentity<A8>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A7>(a7);
#  else
        return a7;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A7>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&& a7,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A7>(a7);
#  else
        return a7;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A7>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&& a7,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A7>(a7);
#  else
        return a7;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    static A7&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7& a7)
    {
        return a7;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A7&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7& a7, A8&)
    {
        return a7;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A7&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7& a7, A8&, A9&)
    {
        return a7;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A7&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7& a7, A8&, A9&, A10&)
    {
        return a7;
    }

#endif
};

template <>
struct RWTBindArg<8> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static typename RWTIdentity<A8>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&& a8)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A8>(a8);
#  else
        return a8;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A8>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&& a8,
         typename RWTIdentity<A9>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A8>(a8);
#  else
        return a8;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A8>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&& a8,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A8>(a8);
#  else
        return a8;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    static A8&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8& a8)
    {
        return a8;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A8&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8& a8, A9&)
    {
        return a8;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A8&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8& a8, A9&, A10&)
    {
        return a8;
    }

#endif
};

template <>
struct RWTBindArg<9> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static typename RWTIdentity<A9>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&& a9)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A9>(a9);
#  else
        return a9;
#  endif
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A9>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&& a9,
         typename RWTIdentity<A10>::type&&)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A9>(a9);
#  else
        return a9;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    static A9&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9& a9)
    {
        return a9;
    }


    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A9&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9& a9, A10&)
    {
        return a9;
    }

#endif
};

template <>
struct RWTBindArg<10> {
#if !defined(RW_NO_RVALUE_REFERENCES)

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static typename RWTIdentity<A10>::type&&
    bind(typename RWTIdentity<A0>::type&&,
         typename RWTIdentity<A1>::type&&,
         typename RWTIdentity<A2>::type&&,
         typename RWTIdentity<A3>::type&&,
         typename RWTIdentity<A4>::type&&,
         typename RWTIdentity<A5>::type&&,
         typename RWTIdentity<A6>::type&&,
         typename RWTIdentity<A7>::type&&,
         typename RWTIdentity<A8>::type&&,
         typename RWTIdentity<A9>::type&&,
         typename RWTIdentity<A10>::type&& a10)
    {
#  if !defined(RW_AVOID_FORWARD_STATIC_CAST)
        return rw_forward<A10>(a10);
#  else
        return a10;
#  endif
    }

#else

    template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    static A10&
    bind(A0&, A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&, A10& a10)
    {
        return a10;
    }

#endif
};


#if defined(RW_AVOID_FORWARD_STATIC_CAST)
#  undef RW_AVOID_FORWARD_STATIC_CAST
#endif

template <typename R, typename C>
struct RWTPlaceholderBinder0 {
    RWTPlaceholderBinder0(C callable)
        : callable_(callable) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&, CA4&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&, CA4&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&, CA4&&, CA5&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&, CA4&, CA5&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&, CA4&&, CA5&&, CA6&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&, CA4&&, CA5&&, CA6&&, CA7&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&, CA4&&, CA5&&, CA6&&, CA7&&, CA8&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&, CA4&&, CA5&&, CA6&&, CA7&&, CA8&&, CA9&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&&, CA2&&, CA3&&, CA4&&, CA5&&, CA6&&, CA7&&, CA8&&, CA9&&, CA10&&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
    ) >::type
    operator()(CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_), 0);
    }
#endif

protected:
    C callable_;

};

template <typename R, typename C>
struct RWTBinder0 : public RWTPlaceholderBinder0<R, C> {
    RWTBinder0(C callable)
        : RWTPlaceholderBinder0<R, C>(callable) {}

    using RWTPlaceholderBinder0<R, C>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type()>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_), 0);
    }
};

template <typename R, typename C, bool = false>
struct RWTBindType0 {
    typedef RWTBinder0<R, C> type;
};

template <typename R, typename C>
struct RWTBindType0<R, C, true> {
    typedef RWTPlaceholderBinder0<R, C> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_0(R, C) \
        typename RWTBindType0<R, typename RWTRemoveReference<C>::type>::type

template <typename R, typename C>
RW_BIND_TYPE_0(R, C)
rwBind(C&& callable)
{
    return RW_BIND_TYPE_0(R, C)(rw_forward<C>(callable));
}

template <typename C>
RW_BIND_TYPE_0(RWDeducedType, C)
rwBind(C&& callable)
{
    return RW_BIND_TYPE_0(RWDeducedType, C)(rw_forward<C>(callable));
}

template <typename R, typename C>
RW_BIND_TYPE_0(R, C*)
rwBind(C* callable)
{
    return RW_BIND_TYPE_0(R, C*)(callable);
}

template <typename C>
RW_BIND_TYPE_0(RWDeducedType, C*)
rwBind(C* callable)
{
    return RW_BIND_TYPE_0(RWDeducedType, C*)(callable);
}
#else
#  define RW_BIND_TYPE_0(R, C) \
        typename RWTBindType0<R, C>::type

template <typename R, typename C>
RW_BIND_TYPE_0(R, C)
rwBind(C c)
{
    return RW_BIND_TYPE_0(R, C)(c);
}

template <typename C>
RW_BIND_TYPE_0(RWDeducedType, C)
rwBind(C c)
{
    return RW_BIND_TYPE_0(RWDeducedType, C)(c);
}
#endif
#undef RW_BIND_TYPE_0


template <typename R, typename C, typename A1>
struct RWTPlaceholderBinder1 {
    RWTPlaceholderBinder1(C callable, A1 a1)
        : callable_(callable), a1_(a1) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
};

template <typename R, typename C, typename A1>
struct RWTBinder1 : public RWTPlaceholderBinder1<R, C, A1> {
    RWTBinder1(C callable, A1 a1)
        : RWTPlaceholderBinder1<R, C, A1>(callable, a1) {}

    using RWTPlaceholderBinder1<R, C, A1>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_), 0);
    }
};

template <typename R, typename C, typename A1, bool = RWTAnyPlaceholder<A1>::value>
struct RWTBindType1 {
    typedef RWTBinder1<R, C, A1> type;
};

template <typename R, typename C, typename A1>
struct RWTBindType1<R, C, A1, true> {
    typedef RWTPlaceholderBinder1<R, C, A1> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_1(R, C, A1) \
        typename RWTBindType1<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type>::type

template <typename R, typename C, typename A1>
RW_BIND_TYPE_1(R, C, A1)
rwBind(C&& callable, A1&& a1)
{
    return RW_BIND_TYPE_1(R, C, A1)(rw_forward<C>(callable),
                                    rw_forward<A1>(a1));
}

template <typename C, typename A1>
RW_BIND_TYPE_1(RWDeducedType, C, A1)
rwBind(C&& callable, A1&& a1)
{
    return RW_BIND_TYPE_1(RWDeducedType, C, A1)(rw_forward<C>(callable),
            rw_forward<A1>(a1));
}

template <typename R, typename C, typename A1>
RW_BIND_TYPE_1(R, C*, A1)
rwBind(C* callable, A1&& a1)
{
    return RW_BIND_TYPE_1(R, C*, A1)(callable,
                                     rw_forward<A1>(a1));
}

template <typename C, typename A1>
RW_BIND_TYPE_1(RWDeducedType, C*, A1)
rwBind(C* callable, A1&& a1)
{
    return RW_BIND_TYPE_1(RWDeducedType, C*, A1)(callable,
            rw_forward<A1>(a1));
}
#else
#  define RW_BIND_TYPE_1(R, C, A1) \
        typename RWTBindType1<R, C, A1>::type

template <typename R, typename C, typename A1>
RW_BIND_TYPE_1(R, C, A1)
rwBind(C c, A1 a1)
{
    return RW_BIND_TYPE_1(R, C, A1)(c, a1);
}

template <typename C, typename A1>
RW_BIND_TYPE_1(RWDeducedType, C, A1)
rwBind(C c, A1 a1)
{
    return RW_BIND_TYPE_1(RWDeducedType, C, A1)(c, a1);
}
#endif
#undef RW_BIND_TYPE_1


template <typename R, typename C, typename A1, typename A2>
struct RWTPlaceholderBinder2 {
    RWTPlaceholderBinder2(C callable, A1 a1, A2 a2)
        : callable_(callable), a1_(a1), a2_(a2) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
};

template <typename R, typename C, typename A1, typename A2>
struct RWTBinder2 : public RWTPlaceholderBinder2<R, C, A1, A2> {
    RWTBinder2(C callable, A1 a1, A2 a2)
        : RWTPlaceholderBinder2<R, C, A1, A2>(callable, a1, a2) {}

    using RWTPlaceholderBinder2<R, C, A1, A2>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, bool = RWTAnyPlaceholder<A1, A2>::value>
struct RWTBindType2 {
    typedef RWTBinder2<R, C, A1, A2> type;
};

template <typename R, typename C, typename A1, typename A2>
struct RWTBindType2<R, C, A1, A2, true> {
    typedef RWTPlaceholderBinder2<R, C, A1, A2> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_2(R, C, A1, A2) \
        typename RWTBindType2<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type>::type

template <typename R, typename C, typename A1, typename A2>
RW_BIND_TYPE_2(R, C, A1, A2)
rwBind(C&& callable, A1&& a1, A2&& a2)
{
    return RW_BIND_TYPE_2(R, C, A1, A2)(rw_forward<C>(callable),
                                        rw_forward<A1>(a1),
                                        rw_forward<A2>(a2));
}

template <typename C, typename A1, typename A2>
RW_BIND_TYPE_2(RWDeducedType, C, A1, A2)
rwBind(C&& callable, A1&& a1, A2&& a2)
{
    return RW_BIND_TYPE_2(RWDeducedType, C, A1, A2)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2));
}

template <typename R, typename C, typename A1, typename A2>
RW_BIND_TYPE_2(R, C*, A1, A2)
rwBind(C* callable, A1&& a1, A2&& a2)
{
    return RW_BIND_TYPE_2(R, C*, A1, A2)(callable,
                                         rw_forward<A1>(a1),
                                         rw_forward<A2>(a2));
}

template <typename C, typename A1, typename A2>
RW_BIND_TYPE_2(RWDeducedType, C*, A1, A2)
rwBind(C* callable, A1&& a1, A2&& a2)
{
    return RW_BIND_TYPE_2(RWDeducedType, C*, A1, A2)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2));
}
#else
#  define RW_BIND_TYPE_2(R, C, A1, A2) \
        typename RWTBindType2<R, C, A1, A2>::type

template <typename R, typename C, typename A1, typename A2>
RW_BIND_TYPE_2(R, C, A1, A2)
rwBind(C c, A1 a1, A2 a2)
{
    return RW_BIND_TYPE_2(R, C, A1, A2)(c, a1, a2);
}

template <typename C, typename A1, typename A2>
RW_BIND_TYPE_2(RWDeducedType, C, A1, A2)
rwBind(C c, A1 a1, A2 a2)
{
    return RW_BIND_TYPE_2(RWDeducedType, C, A1, A2)(c, a1, a2);
}
#endif
#undef RW_BIND_TYPE_2


template <typename R, typename C, typename A1, typename A2, typename A3>
struct RWTPlaceholderBinder3 {
    RWTPlaceholderBinder3(C callable, A1 a1, A2 a2, A3 a3)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
};

template <typename R, typename C, typename A1, typename A2, typename A3>
struct RWTBinder3 : public RWTPlaceholderBinder3<R, C, A1, A2, A3> {
    RWTBinder3(C callable, A1 a1, A2 a2, A3 a3)
        : RWTPlaceholderBinder3<R, C, A1, A2, A3>(callable, a1, a2, a3) {}

    using RWTPlaceholderBinder3<R, C, A1, A2, A3>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, bool = RWTAnyPlaceholder<A1, A2, A3>::value>
struct RWTBindType3 {
    typedef RWTBinder3<R, C, A1, A2, A3> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3>
struct RWTBindType3<R, C, A1, A2, A3, true> {
    typedef RWTPlaceholderBinder3<R, C, A1, A2, A3> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_3(R, C, A1, A2, A3) \
        typename RWTBindType3<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3>
RW_BIND_TYPE_3(R, C, A1, A2, A3)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3)
{
    return RW_BIND_TYPE_3(R, C, A1, A2, A3)(rw_forward<C>(callable),
                                            rw_forward<A1>(a1),
                                            rw_forward<A2>(a2),
                                            rw_forward<A3>(a3));
}

template <typename C, typename A1, typename A2, typename A3>
RW_BIND_TYPE_3(RWDeducedType, C, A1, A2, A3)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3)
{
    return RW_BIND_TYPE_3(RWDeducedType, C, A1, A2, A3)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3));
}

template <typename R, typename C, typename A1, typename A2, typename A3>
RW_BIND_TYPE_3(R, C*, A1, A2, A3)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3)
{
    return RW_BIND_TYPE_3(R, C*, A1, A2, A3)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3));
}

template <typename C, typename A1, typename A2, typename A3>
RW_BIND_TYPE_3(RWDeducedType, C*, A1, A2, A3)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3)
{
    return RW_BIND_TYPE_3(RWDeducedType, C*, A1, A2, A3)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3));
}
#else
#  define RW_BIND_TYPE_3(R, C, A1, A2, A3) \
        typename RWTBindType3<R, C, A1, A2, A3>::type

template <typename R, typename C, typename A1, typename A2, typename A3>
RW_BIND_TYPE_3(R, C, A1, A2, A3)
rwBind(C c, A1 a1, A2 a2, A3 a3)
{
    return RW_BIND_TYPE_3(R, C, A1, A2, A3)(c, a1, a2, a3);
}

template <typename C, typename A1, typename A2, typename A3>
RW_BIND_TYPE_3(RWDeducedType, C, A1, A2, A3)
rwBind(C c, A1 a1, A2 a2, A3 a3)
{
    return RW_BIND_TYPE_3(RWDeducedType, C, A1, A2, A3)(c, a1, a2, a3);
}
#endif
#undef RW_BIND_TYPE_3


template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
struct RWTPlaceholderBinder4 {
    RWTPlaceholderBinder4(C callable, A1 a1, A2 a2, A3 a3, A4 a4)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3), a4_(a4) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1),
        RW_BIND_ARG_TYPE_1(A4, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&),
        RW_BIND_ARG_TYPE_1(A4, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A4, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A4, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A4, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A4, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A4, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A4, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A4, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A4, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A4, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
struct RWTBinder4 : public RWTPlaceholderBinder4<R, C, A1, A2, A3, A4> {
    RWTBinder4(C callable, A1 a1, A2 a2, A3 a3, A4 a4)
        : RWTPlaceholderBinder4<R, C, A1, A2, A3, A4>(callable, a1, a2, a3, a4) {}

    using RWTPlaceholderBinder4<R, C, A1, A2, A3, A4>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3, A4)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_),
                           rwUnwrapReference(this->a4_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, bool = RWTAnyPlaceholder<A1, A2, A3, A4>::value>
struct RWTBindType4 {
    typedef RWTBinder4<R, C, A1, A2, A3, A4> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
struct RWTBindType4<R, C, A1, A2, A3, A4, true> {
    typedef RWTPlaceholderBinder4<R, C, A1, A2, A3, A4> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_4(R, C, A1, A2, A3, A4) \
        typename RWTBindType4<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A4>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
RW_BIND_TYPE_4(R, C, A1, A2, A3, A4)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4)
{
    return RW_BIND_TYPE_4(R, C, A1, A2, A3, A4)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4));
}

template <typename C, typename A1, typename A2, typename A3, typename A4>
RW_BIND_TYPE_4(RWDeducedType, C, A1, A2, A3, A4)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4)
{
    return RW_BIND_TYPE_4(RWDeducedType, C, A1, A2, A3, A4)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4));
}

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
RW_BIND_TYPE_4(R, C*, A1, A2, A3, A4)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4)
{
    return RW_BIND_TYPE_4(R, C*, A1, A2, A3, A4)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4));
}

template <typename C, typename A1, typename A2, typename A3, typename A4>
RW_BIND_TYPE_4(RWDeducedType, C*, A1, A2, A3, A4)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4)
{
    return RW_BIND_TYPE_4(RWDeducedType, C*, A1, A2, A3, A4)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4));
}
#else
#  define RW_BIND_TYPE_4(R, C, A1, A2, A3, A4) \
        typename RWTBindType4<R, C, A1, A2, A3, A4>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4>
RW_BIND_TYPE_4(R, C, A1, A2, A3, A4)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4)
{
    return RW_BIND_TYPE_4(R, C, A1, A2, A3, A4)(c, a1, a2, a3, a4);
}

template <typename C, typename A1, typename A2, typename A3, typename A4>
RW_BIND_TYPE_4(RWDeducedType, C, A1, A2, A3, A4)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4)
{
    return RW_BIND_TYPE_4(RWDeducedType, C, A1, A2, A3, A4)(c, a1, a2, a3, a4);
}
#endif
#undef RW_BIND_TYPE_4


template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
struct RWTPlaceholderBinder5 {
    RWTPlaceholderBinder5(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1),
        RW_BIND_ARG_TYPE_1(A4, CA1),
        RW_BIND_ARG_TYPE_1(A5, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&),
        RW_BIND_ARG_TYPE_1(A4, CA1&),
        RW_BIND_ARG_TYPE_1(A5, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A4, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A5, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A4, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A5, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A4, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A5, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A4, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A5, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A4, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A5, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A4, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A5, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A4, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A5, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A4, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A5, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A4, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A5, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
struct RWTBinder5 : public RWTPlaceholderBinder5<R, C, A1, A2, A3, A4, A5> {
    RWTBinder5(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
        : RWTPlaceholderBinder5<R, C, A1, A2, A3, A4, A5>(callable, a1, a2, a3, a4, a5) {}

    using RWTPlaceholderBinder5<R, C, A1, A2, A3, A4, A5>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3, A4, A5)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_),
                           rwUnwrapReference(this->a4_),
                           rwUnwrapReference(this->a5_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, bool = RWTAnyPlaceholder<A1, A2, A3, A4, A5>::value>
struct RWTBindType5 {
    typedef RWTBinder5<R, C, A1, A2, A3, A4, A5> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
struct RWTBindType5<R, C, A1, A2, A3, A4, A5, true> {
    typedef RWTPlaceholderBinder5<R, C, A1, A2, A3, A4, A5> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_5(R, C, A1, A2, A3, A4, A5) \
        typename RWTBindType5<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A4>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A5>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
RW_BIND_TYPE_5(R, C, A1, A2, A3, A4, A5)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5)
{
    return RW_BIND_TYPE_5(R, C, A1, A2, A3, A4, A5)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
RW_BIND_TYPE_5(RWDeducedType, C, A1, A2, A3, A4, A5)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5)
{
    return RW_BIND_TYPE_5(RWDeducedType, C, A1, A2, A3, A4, A5)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5));
}

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
RW_BIND_TYPE_5(R, C*, A1, A2, A3, A4, A5)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5)
{
    return RW_BIND_TYPE_5(R, C*, A1, A2, A3, A4, A5)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
RW_BIND_TYPE_5(RWDeducedType, C*, A1, A2, A3, A4, A5)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5)
{
    return RW_BIND_TYPE_5(RWDeducedType, C*, A1, A2, A3, A4, A5)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5));
}
#else
#  define RW_BIND_TYPE_5(R, C, A1, A2, A3, A4, A5) \
        typename RWTBindType5<R, C, A1, A2, A3, A4, A5>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
RW_BIND_TYPE_5(R, C, A1, A2, A3, A4, A5)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    return RW_BIND_TYPE_5(R, C, A1, A2, A3, A4, A5)(c, a1, a2, a3, a4, a5);
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
RW_BIND_TYPE_5(RWDeducedType, C, A1, A2, A3, A4, A5)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    return RW_BIND_TYPE_5(RWDeducedType, C, A1, A2, A3, A4, A5)(c, a1, a2, a3, a4, a5);
}
#endif
#undef RW_BIND_TYPE_5


template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct RWTPlaceholderBinder6 {
    RWTPlaceholderBinder6(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1),
        RW_BIND_ARG_TYPE_1(A4, CA1),
        RW_BIND_ARG_TYPE_1(A5, CA1),
        RW_BIND_ARG_TYPE_1(A6, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&),
        RW_BIND_ARG_TYPE_1(A4, CA1&),
        RW_BIND_ARG_TYPE_1(A5, CA1&),
        RW_BIND_ARG_TYPE_1(A6, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A4, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A5, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A6, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A4, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A5, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A6, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A4, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A5, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A6, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A4, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A5, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A6, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A4, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A5, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A6, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A4, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A5, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A6, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A4, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A5, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A6, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A4, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A5, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A6, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A4, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A5, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A6, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct RWTBinder6 : public RWTPlaceholderBinder6<R, C, A1, A2, A3, A4, A5, A6> {
    RWTBinder6(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
        : RWTPlaceholderBinder6<R, C, A1, A2, A3, A4, A5, A6>(callable, a1, a2, a3, a4, a5, a6) {}

    using RWTPlaceholderBinder6<R, C, A1, A2, A3, A4, A5, A6>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3, A4, A5, A6)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_),
                           rwUnwrapReference(this->a4_),
                           rwUnwrapReference(this->a5_),
                           rwUnwrapReference(this->a6_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, bool = RWTAnyPlaceholder<A1, A2, A3, A4, A5, A6>::value>
struct RWTBindType6 {
    typedef RWTBinder6<R, C, A1, A2, A3, A4, A5, A6> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct RWTBindType6<R, C, A1, A2, A3, A4, A5, A6, true> {
    typedef RWTPlaceholderBinder6<R, C, A1, A2, A3, A4, A5, A6> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_6(R, C, A1, A2, A3, A4, A5, A6) \
        typename RWTBindType6<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A4>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A5>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A6>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
RW_BIND_TYPE_6(R, C, A1, A2, A3, A4, A5, A6)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6)
{
    return RW_BIND_TYPE_6(R, C, A1, A2, A3, A4, A5, A6)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
RW_BIND_TYPE_6(RWDeducedType, C, A1, A2, A3, A4, A5, A6)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6)
{
    return RW_BIND_TYPE_6(RWDeducedType, C, A1, A2, A3, A4, A5, A6)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6));
}

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
RW_BIND_TYPE_6(R, C*, A1, A2, A3, A4, A5, A6)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6)
{
    return RW_BIND_TYPE_6(R, C*, A1, A2, A3, A4, A5, A6)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
RW_BIND_TYPE_6(RWDeducedType, C*, A1, A2, A3, A4, A5, A6)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6)
{
    return RW_BIND_TYPE_6(RWDeducedType, C*, A1, A2, A3, A4, A5, A6)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6));
}
#else
#  define RW_BIND_TYPE_6(R, C, A1, A2, A3, A4, A5, A6) \
        typename RWTBindType6<R, C, A1, A2, A3, A4, A5, A6>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
RW_BIND_TYPE_6(R, C, A1, A2, A3, A4, A5, A6)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    return RW_BIND_TYPE_6(R, C, A1, A2, A3, A4, A5, A6)(c, a1, a2, a3, a4, a5, a6);
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
RW_BIND_TYPE_6(RWDeducedType, C, A1, A2, A3, A4, A5, A6)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    return RW_BIND_TYPE_6(RWDeducedType, C, A1, A2, A3, A4, A5, A6)(c, a1, a2, a3, a4, a5, a6);
}
#endif
#undef RW_BIND_TYPE_6


template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct RWTPlaceholderBinder7 {
    RWTPlaceholderBinder7(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1),
        RW_BIND_ARG_TYPE_1(A4, CA1),
        RW_BIND_ARG_TYPE_1(A5, CA1),
        RW_BIND_ARG_TYPE_1(A6, CA1),
        RW_BIND_ARG_TYPE_1(A7, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&),
        RW_BIND_ARG_TYPE_1(A4, CA1&),
        RW_BIND_ARG_TYPE_1(A5, CA1&),
        RW_BIND_ARG_TYPE_1(A6, CA1&),
        RW_BIND_ARG_TYPE_1(A7, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A4, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A5, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A6, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A7, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A4, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A5, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A6, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A7, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A4, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A5, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A6, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A7, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A4, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A5, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A6, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A7, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A4, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A5, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A6, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A7, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A4, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A5, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A6, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A7, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A4, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A5, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A6, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A7, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A4, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A5, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A6, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A7, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A4, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A5, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A6, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A7, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct RWTBinder7 : public RWTPlaceholderBinder7<R, C, A1, A2, A3, A4, A5, A6, A7> {
    RWTBinder7(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
        : RWTPlaceholderBinder7<R, C, A1, A2, A3, A4, A5, A6, A7>(callable, a1, a2, a3, a4, a5, a6, a7) {}

    using RWTPlaceholderBinder7<R, C, A1, A2, A3, A4, A5, A6, A7>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3, A4, A5, A6, A7)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_),
                           rwUnwrapReference(this->a4_),
                           rwUnwrapReference(this->a5_),
                           rwUnwrapReference(this->a6_),
                           rwUnwrapReference(this->a7_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, bool = RWTAnyPlaceholder<A1, A2, A3, A4, A5, A6, A7>::value>
struct RWTBindType7 {
    typedef RWTBinder7<R, C, A1, A2, A3, A4, A5, A6, A7> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct RWTBindType7<R, C, A1, A2, A3, A4, A5, A6, A7, true> {
    typedef RWTPlaceholderBinder7<R, C, A1, A2, A3, A4, A5, A6, A7> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_7(R, C, A1, A2, A3, A4, A5, A6, A7) \
        typename RWTBindType7<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A4>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A5>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A6>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A7>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
RW_BIND_TYPE_7(R, C, A1, A2, A3, A4, A5, A6, A7)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7)
{
    return RW_BIND_TYPE_7(R, C, A1, A2, A3, A4, A5, A6, A7)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
RW_BIND_TYPE_7(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7)
{
    return RW_BIND_TYPE_7(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7));
}

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
RW_BIND_TYPE_7(R, C*, A1, A2, A3, A4, A5, A6, A7)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7)
{
    return RW_BIND_TYPE_7(R, C*, A1, A2, A3, A4, A5, A6, A7)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
RW_BIND_TYPE_7(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7)
{
    return RW_BIND_TYPE_7(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7));
}
#else
#  define RW_BIND_TYPE_7(R, C, A1, A2, A3, A4, A5, A6, A7) \
        typename RWTBindType7<R, C, A1, A2, A3, A4, A5, A6, A7>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
RW_BIND_TYPE_7(R, C, A1, A2, A3, A4, A5, A6, A7)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    return RW_BIND_TYPE_7(R, C, A1, A2, A3, A4, A5, A6, A7)(c, a1, a2, a3, a4, a5, a6, a7);
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
RW_BIND_TYPE_7(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    return RW_BIND_TYPE_7(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7)(c, a1, a2, a3, a4, a5, a6, a7);
}
#endif
#undef RW_BIND_TYPE_7


template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct RWTPlaceholderBinder8 {
    RWTPlaceholderBinder8(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7), a8_(a8) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1),
        RW_BIND_ARG_TYPE_1(A4, CA1),
        RW_BIND_ARG_TYPE_1(A5, CA1),
        RW_BIND_ARG_TYPE_1(A6, CA1),
        RW_BIND_ARG_TYPE_1(A7, CA1),
        RW_BIND_ARG_TYPE_1(A8, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1),
                           RW_BIND_ARG_1(A8, CA1, a8_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&),
        RW_BIND_ARG_TYPE_1(A4, CA1&),
        RW_BIND_ARG_TYPE_1(A5, CA1&),
        RW_BIND_ARG_TYPE_1(A6, CA1&),
        RW_BIND_ARG_TYPE_1(A7, CA1&),
        RW_BIND_ARG_TYPE_1(A8, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1),
                           RW_BIND_ARG_1(A8, CA1, a8_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A4, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A5, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A6, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A7, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A8, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2),
                           RW_BIND_ARG_2(A8, CA1, CA2, a8_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A4, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A5, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A6, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A7, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A8, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2),
                           RW_BIND_ARG_2(A8, CA1, CA2, a8_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A4, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A5, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A6, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A7, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A8, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3),
                           RW_BIND_ARG_3(A8, CA1, CA2, CA3, a8_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A4, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A5, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A6, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A7, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A8, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3),
                           RW_BIND_ARG_3(A8, CA1, CA2, CA3, a8_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A4, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A5, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A6, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A7, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A8, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A8, CA1, CA2, CA3, CA4, a8_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A4, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A5, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A6, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A7, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A8, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A8, CA1, CA2, CA3, CA4, a8_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A4, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A5, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A6, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A7, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A8, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A8, CA1, CA2, CA3, CA4, CA5, a8_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A4, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A5, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A6, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A7, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A8, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A8, CA1, CA2, CA3, CA4, CA5, a8_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A4, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A5, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A6, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A7, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A8, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A8, CA1, CA2, CA3, CA4, CA5, CA6, a8_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A8, CA1, CA2, CA3, CA4, CA5, CA6, a8_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a8_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a8_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a8_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a8_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
    A8 a8_;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct RWTBinder8 : public RWTPlaceholderBinder8<R, C, A1, A2, A3, A4, A5, A6, A7, A8> {
    RWTBinder8(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
        : RWTPlaceholderBinder8<R, C, A1, A2, A3, A4, A5, A6, A7, A8>(callable, a1, a2, a3, a4, a5, a6, a7, a8) {}

    using RWTPlaceholderBinder8<R, C, A1, A2, A3, A4, A5, A6, A7, A8>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3, A4, A5, A6, A7, A8)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_),
                           rwUnwrapReference(this->a4_),
                           rwUnwrapReference(this->a5_),
                           rwUnwrapReference(this->a6_),
                           rwUnwrapReference(this->a7_),
                           rwUnwrapReference(this->a8_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, bool = RWTAnyPlaceholder<A1, A2, A3, A4, A5, A6, A7, A8>::value>
struct RWTBindType8 {
    typedef RWTBinder8<R, C, A1, A2, A3, A4, A5, A6, A7, A8> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct RWTBindType8<R, C, A1, A2, A3, A4, A5, A6, A7, A8, true> {
    typedef RWTPlaceholderBinder8<R, C, A1, A2, A3, A4, A5, A6, A7, A8> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_8(R, C, A1, A2, A3, A4, A5, A6, A7, A8) \
        typename RWTBindType8<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A4>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A5>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A6>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A7>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A8>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
RW_BIND_TYPE_8(R, C, A1, A2, A3, A4, A5, A6, A7, A8)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8)
{
    return RW_BIND_TYPE_8(R, C, A1, A2, A3, A4, A5, A6, A7, A8)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
RW_BIND_TYPE_8(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8)
{
    return RW_BIND_TYPE_8(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8));
}

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
RW_BIND_TYPE_8(R, C*, A1, A2, A3, A4, A5, A6, A7, A8)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8)
{
    return RW_BIND_TYPE_8(R, C*, A1, A2, A3, A4, A5, A6, A7, A8)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
RW_BIND_TYPE_8(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7, A8)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8)
{
    return RW_BIND_TYPE_8(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7, A8)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8));
}
#else
#  define RW_BIND_TYPE_8(R, C, A1, A2, A3, A4, A5, A6, A7, A8) \
        typename RWTBindType8<R, C, A1, A2, A3, A4, A5, A6, A7, A8>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
RW_BIND_TYPE_8(R, C, A1, A2, A3, A4, A5, A6, A7, A8)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    return RW_BIND_TYPE_8(R, C, A1, A2, A3, A4, A5, A6, A7, A8)(c, a1, a2, a3, a4, a5, a6, a7, a8);
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
RW_BIND_TYPE_8(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    return RW_BIND_TYPE_8(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8)(c, a1, a2, a3, a4, a5, a6, a7, a8);
}
#endif
#undef RW_BIND_TYPE_8


template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct RWTPlaceholderBinder9 {
    RWTPlaceholderBinder9(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7), a8_(a8), a9_(a9) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1),
        RW_BIND_ARG_TYPE_1(A4, CA1),
        RW_BIND_ARG_TYPE_1(A5, CA1),
        RW_BIND_ARG_TYPE_1(A6, CA1),
        RW_BIND_ARG_TYPE_1(A7, CA1),
        RW_BIND_ARG_TYPE_1(A8, CA1),
        RW_BIND_ARG_TYPE_1(A9, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1),
                           RW_BIND_ARG_1(A8, CA1, a8_, a1),
                           RW_BIND_ARG_1(A9, CA1, a9_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&),
        RW_BIND_ARG_TYPE_1(A4, CA1&),
        RW_BIND_ARG_TYPE_1(A5, CA1&),
        RW_BIND_ARG_TYPE_1(A6, CA1&),
        RW_BIND_ARG_TYPE_1(A7, CA1&),
        RW_BIND_ARG_TYPE_1(A8, CA1&),
        RW_BIND_ARG_TYPE_1(A9, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1),
                           RW_BIND_ARG_1(A8, CA1, a8_, a1),
                           RW_BIND_ARG_1(A9, CA1, a9_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A4, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A5, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A6, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A7, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A8, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A9, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2),
                           RW_BIND_ARG_2(A8, CA1, CA2, a8_, a1, a2),
                           RW_BIND_ARG_2(A9, CA1, CA2, a9_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A4, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A5, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A6, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A7, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A8, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A9, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2),
                           RW_BIND_ARG_2(A8, CA1, CA2, a8_, a1, a2),
                           RW_BIND_ARG_2(A9, CA1, CA2, a9_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A4, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A5, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A6, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A7, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A8, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A9, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3),
                           RW_BIND_ARG_3(A8, CA1, CA2, CA3, a8_, a1, a2, a3),
                           RW_BIND_ARG_3(A9, CA1, CA2, CA3, a9_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A4, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A5, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A6, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A7, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A8, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A9, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3),
                           RW_BIND_ARG_3(A8, CA1, CA2, CA3, a8_, a1, a2, a3),
                           RW_BIND_ARG_3(A9, CA1, CA2, CA3, a9_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A4, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A5, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A6, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A7, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A8, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A9, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A8, CA1, CA2, CA3, CA4, a8_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A9, CA1, CA2, CA3, CA4, a9_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A4, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A5, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A6, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A7, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A8, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A9, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A8, CA1, CA2, CA3, CA4, a8_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A9, CA1, CA2, CA3, CA4, a9_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A4, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A5, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A6, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A7, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A8, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A9, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A8, CA1, CA2, CA3, CA4, CA5, a8_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A9, CA1, CA2, CA3, CA4, CA5, a9_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A4, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A5, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A6, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A7, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A8, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A9, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A8, CA1, CA2, CA3, CA4, CA5, a8_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A9, CA1, CA2, CA3, CA4, CA5, a9_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A4, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A5, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A6, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A7, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A8, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A9, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A8, CA1, CA2, CA3, CA4, CA5, CA6, a8_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A9, CA1, CA2, CA3, CA4, CA5, CA6, a9_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A8, CA1, CA2, CA3, CA4, CA5, CA6, a8_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A9, CA1, CA2, CA3, CA4, CA5, CA6, a9_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a8_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a9_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a8_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a9_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a8_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a9_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a8_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a9_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A4&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A5&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A6&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A7&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A8&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A9&, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
    A8 a8_;
    A9 a9_;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct RWTBinder9 : public RWTPlaceholderBinder9<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9> {
    RWTBinder9(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
        : RWTPlaceholderBinder9<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9>(callable, a1, a2, a3, a4, a5, a6, a7, a8, a9) {}

    using RWTPlaceholderBinder9<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3, A4, A5, A6, A7, A8, A9)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_),
                           rwUnwrapReference(this->a4_),
                           rwUnwrapReference(this->a5_),
                           rwUnwrapReference(this->a6_),
                           rwUnwrapReference(this->a7_),
                           rwUnwrapReference(this->a8_),
                           rwUnwrapReference(this->a9_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, bool = RWTAnyPlaceholder<A1, A2, A3, A4, A5, A6, A7, A8, A9>::value>
struct RWTBindType9 {
    typedef RWTBinder9<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct RWTBindType9<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, true> {
    typedef RWTPlaceholderBinder9<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_9(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9) \
        typename RWTBindType9<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A4>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A5>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A6>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A7>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A8>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A9>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
RW_BIND_TYPE_9(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9)
{
    return RW_BIND_TYPE_9(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
RW_BIND_TYPE_9(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9)
{
    return RW_BIND_TYPE_9(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9));
}

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
RW_BIND_TYPE_9(R, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9)
{
    return RW_BIND_TYPE_9(R, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
RW_BIND_TYPE_9(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9)
{
    return RW_BIND_TYPE_9(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9));
}
#else
#  define RW_BIND_TYPE_9(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9) \
        typename RWTBindType9<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
RW_BIND_TYPE_9(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    return RW_BIND_TYPE_9(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)(c, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
RW_BIND_TYPE_9(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    return RW_BIND_TYPE_9(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9)(c, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif
#undef RW_BIND_TYPE_9


template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct RWTPlaceholderBinder10 {
    RWTPlaceholderBinder10(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
        : callable_(callable), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7), a8_(a8), a9_(a9), a10_(a10) {}

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1),
        RW_BIND_ARG_TYPE_1(A2, CA1),
        RW_BIND_ARG_TYPE_1(A3, CA1),
        RW_BIND_ARG_TYPE_1(A4, CA1),
        RW_BIND_ARG_TYPE_1(A5, CA1),
        RW_BIND_ARG_TYPE_1(A6, CA1),
        RW_BIND_ARG_TYPE_1(A7, CA1),
        RW_BIND_ARG_TYPE_1(A8, CA1),
        RW_BIND_ARG_TYPE_1(A9, CA1),
        RW_BIND_ARG_TYPE_1(A10, CA1)) >::type
    operator()(CA1&& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1),
                           RW_BIND_ARG_1(A8, CA1, a8_, a1),
                           RW_BIND_ARG_1(A9, CA1, a9_, a1),
                           RW_BIND_ARG_1(A10, CA1, a10_, a1), 0);
    }
#else
    template <typename CA1>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_1(A1, CA1&),
        RW_BIND_ARG_TYPE_1(A2, CA1&),
        RW_BIND_ARG_TYPE_1(A3, CA1&),
        RW_BIND_ARG_TYPE_1(A4, CA1&),
        RW_BIND_ARG_TYPE_1(A5, CA1&),
        RW_BIND_ARG_TYPE_1(A6, CA1&),
        RW_BIND_ARG_TYPE_1(A7, CA1&),
        RW_BIND_ARG_TYPE_1(A8, CA1&),
        RW_BIND_ARG_TYPE_1(A9, CA1&),
        RW_BIND_ARG_TYPE_1(A10, CA1&)) >::type
    operator()(CA1& a1)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_1(A1, CA1, a1_, a1),
                           RW_BIND_ARG_1(A2, CA1, a2_, a1),
                           RW_BIND_ARG_1(A3, CA1, a3_, a1),
                           RW_BIND_ARG_1(A4, CA1, a4_, a1),
                           RW_BIND_ARG_1(A5, CA1, a5_, a1),
                           RW_BIND_ARG_1(A6, CA1, a6_, a1),
                           RW_BIND_ARG_1(A7, CA1, a7_, a1),
                           RW_BIND_ARG_1(A8, CA1, a8_, a1),
                           RW_BIND_ARG_1(A9, CA1, a9_, a1),
                           RW_BIND_ARG_1(A10, CA1, a10_, a1), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A2, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A3, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A4, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A5, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A6, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A7, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A8, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A9, CA1, CA2),
        RW_BIND_ARG_TYPE_2(A10, CA1, CA2)) >::type
    operator()(CA1&& a1, CA2&& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2),
                           RW_BIND_ARG_2(A8, CA1, CA2, a8_, a1, a2),
                           RW_BIND_ARG_2(A9, CA1, CA2, a9_, a1, a2),
                           RW_BIND_ARG_2(A10, CA1, CA2, a10_, a1, a2), 0);
    }
#else
    template <typename CA1, typename CA2>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_2(A1, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A2, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A3, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A4, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A5, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A6, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A7, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A8, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A9, CA1&, CA2&),
        RW_BIND_ARG_TYPE_2(A10, CA1&, CA2&)) >::type
    operator()(CA1& a1, CA2& a2)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_2(A1, CA1, CA2, a1_, a1, a2),
                           RW_BIND_ARG_2(A2, CA1, CA2, a2_, a1, a2),
                           RW_BIND_ARG_2(A3, CA1, CA2, a3_, a1, a2),
                           RW_BIND_ARG_2(A4, CA1, CA2, a4_, a1, a2),
                           RW_BIND_ARG_2(A5, CA1, CA2, a5_, a1, a2),
                           RW_BIND_ARG_2(A6, CA1, CA2, a6_, a1, a2),
                           RW_BIND_ARG_2(A7, CA1, CA2, a7_, a1, a2),
                           RW_BIND_ARG_2(A8, CA1, CA2, a8_, a1, a2),
                           RW_BIND_ARG_2(A9, CA1, CA2, a9_, a1, a2),
                           RW_BIND_ARG_2(A10, CA1, CA2, a10_, a1, a2), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A2, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A3, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A4, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A5, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A6, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A7, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A8, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A9, CA1, CA2, CA3),
        RW_BIND_ARG_TYPE_3(A10, CA1, CA2, CA3)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3),
                           RW_BIND_ARG_3(A8, CA1, CA2, CA3, a8_, a1, a2, a3),
                           RW_BIND_ARG_3(A9, CA1, CA2, CA3, a9_, a1, a2, a3),
                           RW_BIND_ARG_3(A10, CA1, CA2, CA3, a10_, a1, a2, a3), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_3(A1, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A2, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A3, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A4, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A5, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A6, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A7, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A8, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A9, CA1&, CA2&, CA3&),
        RW_BIND_ARG_TYPE_3(A10, CA1&, CA2&, CA3&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_3(A1, CA1, CA2, CA3, a1_, a1, a2, a3),
                           RW_BIND_ARG_3(A2, CA1, CA2, CA3, a2_, a1, a2, a3),
                           RW_BIND_ARG_3(A3, CA1, CA2, CA3, a3_, a1, a2, a3),
                           RW_BIND_ARG_3(A4, CA1, CA2, CA3, a4_, a1, a2, a3),
                           RW_BIND_ARG_3(A5, CA1, CA2, CA3, a5_, a1, a2, a3),
                           RW_BIND_ARG_3(A6, CA1, CA2, CA3, a6_, a1, a2, a3),
                           RW_BIND_ARG_3(A7, CA1, CA2, CA3, a7_, a1, a2, a3),
                           RW_BIND_ARG_3(A8, CA1, CA2, CA3, a8_, a1, a2, a3),
                           RW_BIND_ARG_3(A9, CA1, CA2, CA3, a9_, a1, a2, a3),
                           RW_BIND_ARG_3(A10, CA1, CA2, CA3, a10_, a1, a2, a3), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A2, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A3, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A4, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A5, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A6, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A7, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A8, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A9, CA1, CA2, CA3, CA4),
        RW_BIND_ARG_TYPE_4(A10, CA1, CA2, CA3, CA4)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A8, CA1, CA2, CA3, CA4, a8_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A9, CA1, CA2, CA3, CA4, a9_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A10, CA1, CA2, CA3, CA4, a10_, a1, a2, a3, a4), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_4(A1, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A2, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A3, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A4, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A5, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A6, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A7, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A8, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A9, CA1&, CA2&, CA3&, CA4&),
        RW_BIND_ARG_TYPE_4(A10, CA1&, CA2&, CA3&, CA4&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_4(A1, CA1, CA2, CA3, CA4, a1_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A2, CA1, CA2, CA3, CA4, a2_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A3, CA1, CA2, CA3, CA4, a3_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A4, CA1, CA2, CA3, CA4, a4_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A5, CA1, CA2, CA3, CA4, a5_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A6, CA1, CA2, CA3, CA4, a6_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A7, CA1, CA2, CA3, CA4, a7_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A8, CA1, CA2, CA3, CA4, a8_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A9, CA1, CA2, CA3, CA4, a9_, a1, a2, a3, a4),
                           RW_BIND_ARG_4(A10, CA1, CA2, CA3, CA4, a10_, a1, a2, a3, a4), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A2, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A3, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A4, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A5, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A6, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A7, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A8, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A9, CA1, CA2, CA3, CA4, CA5),
        RW_BIND_ARG_TYPE_5(A10, CA1, CA2, CA3, CA4, CA5)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A8, CA1, CA2, CA3, CA4, CA5, a8_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A9, CA1, CA2, CA3, CA4, CA5, a9_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A10, CA1, CA2, CA3, CA4, CA5, a10_, a1, a2, a3, a4, a5), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_5(A1, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A2, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A3, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A4, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A5, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A6, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A7, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A8, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A9, CA1&, CA2&, CA3&, CA4&, CA5&),
        RW_BIND_ARG_TYPE_5(A10, CA1&, CA2&, CA3&, CA4&, CA5&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_5(A1, CA1, CA2, CA3, CA4, CA5, a1_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A2, CA1, CA2, CA3, CA4, CA5, a2_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A3, CA1, CA2, CA3, CA4, CA5, a3_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A4, CA1, CA2, CA3, CA4, CA5, a4_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A5, CA1, CA2, CA3, CA4, CA5, a5_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A6, CA1, CA2, CA3, CA4, CA5, a6_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A7, CA1, CA2, CA3, CA4, CA5, a7_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A8, CA1, CA2, CA3, CA4, CA5, a8_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A9, CA1, CA2, CA3, CA4, CA5, a9_, a1, a2, a3, a4, a5),
                           RW_BIND_ARG_5(A10, CA1, CA2, CA3, CA4, CA5, a10_, a1, a2, a3, a4, a5), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A2, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A3, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A4, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A5, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A6, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A7, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A8, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A9, CA1, CA2, CA3, CA4, CA5, CA6),
        RW_BIND_ARG_TYPE_6(A10, CA1, CA2, CA3, CA4, CA5, CA6)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A8, CA1, CA2, CA3, CA4, CA5, CA6, a8_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A9, CA1, CA2, CA3, CA4, CA5, CA6, a9_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A10, CA1, CA2, CA3, CA4, CA5, CA6, a10_, a1, a2, a3, a4, a5, a6), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_6(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&),
        RW_BIND_ARG_TYPE_6(A10, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_6(A1, CA1, CA2, CA3, CA4, CA5, CA6, a1_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A2, CA1, CA2, CA3, CA4, CA5, CA6, a2_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A3, CA1, CA2, CA3, CA4, CA5, CA6, a3_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A4, CA1, CA2, CA3, CA4, CA5, CA6, a4_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A5, CA1, CA2, CA3, CA4, CA5, CA6, a5_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A6, CA1, CA2, CA3, CA4, CA5, CA6, a6_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A7, CA1, CA2, CA3, CA4, CA5, CA6, a7_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A8, CA1, CA2, CA3, CA4, CA5, CA6, a8_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A9, CA1, CA2, CA3, CA4, CA5, CA6, a9_, a1, a2, a3, a4, a5, a6),
                           RW_BIND_ARG_6(A10, CA1, CA2, CA3, CA4, CA5, CA6, a10_, a1, a2, a3, a4, a5, a6), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7),
        RW_BIND_ARG_TYPE_7(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a8_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a9_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a10_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_7(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&),
        RW_BIND_ARG_TYPE_7(A10, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_7(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a1_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a2_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a3_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a4_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a5_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a6_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a7_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a8_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a9_, a1, a2, a3, a4, a5, a6, a7),
                           RW_BIND_ARG_7(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, a10_, a1, a2, a3, a4, a5, a6, a7), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8),
        RW_BIND_ARG_TYPE_8(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a8_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a9_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a10_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_8(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&),
        RW_BIND_ARG_TYPE_8(A10, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_8(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a1_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a2_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a3_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a4_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a5_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a6_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a7_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a8_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a9_, a1, a2, a3, a4, a5, a6, a7, a8),
                           RW_BIND_ARG_8(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, a10_, a1, a2, a3, a4, a5, a6, a7, a8), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9),
        RW_BIND_ARG_TYPE_9(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a10_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_9(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&),
        RW_BIND_ARG_TYPE_9(A10, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_9(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9),
                           RW_BIND_ARG_9(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, a10_, a1, a2, a3, a4, a5, a6, a7, a8, a9), 0);
    }
#endif

#if !defined(RW_NO_RVALUE_REFERENCES)
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10),
        RW_BIND_ARG_TYPE_10(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10)) >::type
    operator()(CA1&& a1, CA2&& a2, CA3&& a3, CA4&& a4, CA5&& a5, CA6&& a6, CA7&& a7, CA8&& a8, CA9&& a9, CA10&& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a10_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#else
    template <typename CA1, typename CA2, typename CA3, typename CA4, typename CA5, typename CA6, typename CA7, typename CA8, typename CA9, typename CA10>
    typename RWTBindResult < R, typename RWTUnwrapType<C>::type(
        RW_BIND_ARG_TYPE_10(A1, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A2, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A3, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A4, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A5, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A6, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A7, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A8, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A9, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&),
        RW_BIND_ARG_TYPE_10(A10, CA1&, CA2&, CA3&, CA4&, CA5&, CA6&, CA7&, CA8&, CA9&, CA10&)) >::type
    operator()(CA1& a1, CA2& a2, CA3& a3, CA4& a4, CA5& a5, CA6& a6, CA7& a7, CA8& a8, CA9& a9, CA10& a10)
    {
        return rwInvoke<R>(rwUnwrapReference((C&)callable_),
                           RW_BIND_ARG_10(A1, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a1_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A2, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a2_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A3, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a3_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A4, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a4_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A5, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a5_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A6, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a6_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A7, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a7_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A8, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a8_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A9, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a9_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),
                           RW_BIND_ARG_10(A10, CA1, CA2, CA3, CA4, CA5, CA6, CA7, CA8, CA9, CA10, a10_, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), 0);
    }
#endif

protected:
    C callable_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
    A8 a8_;
    A9 a9_;
    A10 a10_;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct RWTBinder10 : public RWTPlaceholderBinder10<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> {
    RWTBinder10(C callable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
        : RWTPlaceholderBinder10<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>(callable, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) {}

    using RWTPlaceholderBinder10<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::operator();

    typename RWTBindResult<R, typename RWTUnwrapType<C>::type(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>::type
    operator()()
    {
        return rwInvoke<R>(rwUnwrapReference((C&)this->callable_),
                           rwUnwrapReference(this->a1_),
                           rwUnwrapReference(this->a2_),
                           rwUnwrapReference(this->a3_),
                           rwUnwrapReference(this->a4_),
                           rwUnwrapReference(this->a5_),
                           rwUnwrapReference(this->a6_),
                           rwUnwrapReference(this->a7_),
                           rwUnwrapReference(this->a8_),
                           rwUnwrapReference(this->a9_),
                           rwUnwrapReference(this->a10_), 0);
    }
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, bool = RWTAnyPlaceholder<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::value>
struct RWTBindType10 {
    typedef RWTBinder10<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> type;
};

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct RWTBindType10<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, true> {
    typedef RWTPlaceholderBinder10<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> type;
};

#if !defined(RW_NO_RVALUE_REFERENCES)
#  define RW_BIND_TYPE_10(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) \
        typename RWTBindType10<R, typename RWTRemoveReference<C>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A1>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A2>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A3>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A4>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A5>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A6>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A7>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A8>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A9>::type>::type,  \
            typename RWTBindArrayAsPointer<typename RWTRemoveReference<A10>::type>::type>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
RW_BIND_TYPE_10(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9, A10&& a10)
{
    return RW_BIND_TYPE_10(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9),
            rw_forward<A10>(a10));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
RW_BIND_TYPE_10(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
rwBind(C&& callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9, A10&& a10)
{
    return RW_BIND_TYPE_10(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)(rw_forward<C>(callable),
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9),
            rw_forward<A10>(a10));
}

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
RW_BIND_TYPE_10(R, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9, A10&& a10)
{
    return RW_BIND_TYPE_10(R, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9),
            rw_forward<A10>(a10));
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
RW_BIND_TYPE_10(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
rwBind(C* callable, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9, A10&& a10)
{
    return RW_BIND_TYPE_10(RWDeducedType, C*, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)(callable,
            rw_forward<A1>(a1),
            rw_forward<A2>(a2),
            rw_forward<A3>(a3),
            rw_forward<A4>(a4),
            rw_forward<A5>(a5),
            rw_forward<A6>(a6),
            rw_forward<A7>(a7),
            rw_forward<A8>(a8),
            rw_forward<A9>(a9),
            rw_forward<A10>(a10));
}
#else
#  define RW_BIND_TYPE_10(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) \
        typename RWTBindType10<R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::type

template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
RW_BIND_TYPE_10(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
{
    return RW_BIND_TYPE_10(R, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)(c, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
RW_BIND_TYPE_10(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
rwBind(C c, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
{
    return RW_BIND_TYPE_10(RWDeducedType, C, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)(c, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
#endif
#undef RW_BIND_TYPE_10

#undef RW_BIND_ARG_1
#undef RW_BIND_ARG_2
#undef RW_BIND_ARG_3
#undef RW_BIND_ARG_4
#undef RW_BIND_ARG_5
#undef RW_BIND_ARG_6
#undef RW_BIND_ARG_7
#undef RW_BIND_ARG_8
#undef RW_BIND_ARG_9
#undef RW_BIND_ARG_10

#undef RW_BIND_ARG_TYPE_1
#undef RW_BIND_ARG_TYPE_2
#undef RW_BIND_ARG_TYPE_3
#undef RW_BIND_ARG_TYPE_4
#undef RW_BIND_ARG_TYPE_5
#undef RW_BIND_ARG_TYPE_6
#undef RW_BIND_ARG_TYPE_7
#undef RW_BIND_ARG_TYPE_8
#undef RW_BIND_ARG_TYPE_9
#undef RW_BIND_ARG_TYPE_10

#endif // DOXYGEN

#endif // rw_functor_rwBind_h_
