#ifndef __rw_thread_rwtMakeRunnableCallback_h__
#define __rw_thread_rwtMakeRunnableCallback_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/rwtMakeRunnableCallback.h#1 $
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

#include <rw/thread/RWRunnable.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/functor2.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS
#  define rwMakeRunnableCallback    rwtMakeRunnableCallback
#  define rwMakeRunnableCallbackG   rwtMakeRunnableCallbackG
#  define rwMakeRunnableCallbackGA1 rwtMakeRunnableCallbackGA1
#  define rwMakeRunnableCallbackGA2 rwtMakeRunnableCallbackGA2
#  define rwMakeRunnableCallbackM   rwtMakeRunnableCallbackM
#  define rwMakeRunnableCallbackMA1 rwtMakeRunnableCallbackMA1
#  define rwMakeRunnableCallbackMA2 rwtMakeRunnableCallbackMA2

/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2)"
 * instead.
 *
 * Macro to create a runnable callback functor from a global function that
 * takes a runnable reference and an execution state as arguments.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableCallbackG", "Use rwBind() instead")
#define rwtMakeRunnableCallbackG(function)                \
   RWTFunctor2GImp<const RWRunnable&,       /* S1 */      \
                  RWExecutionState,         /* S2 */      \
                  void,                     /* DR */      \
                  const RWRunnable&,        /* D1 */      \
                  RWExecutionState          /* D2 */      \
                 >::make(function)


/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2)"
 * instead.
 *
 * Template function to create a runnable callback functor from a global
 * function that takes a runnable reference and an execution state as
 * arguments.
 */
inline RWTFunctor2<const RWRunnable&, RWExecutionState>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
rwtMakeRunnableCallback(void (*function)(const RWRunnable&, RWExecutionState))
{
    return rwtMakeRunnableCallbackG(function);
}


/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2, a1)"
 * instead.
 *
 * Macro to create a runnable callback functor from a global function that
 * takes a runnable reference, an execution state, and one additional
 * argument.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableCallbackGA1", "Use rwBind() instead")
#define rwtMakeRunnableCallbackGA1(function,A1,a1)          \
   RWTFunctor2GA1Imp<const RWRunnable&,       /* S1 */      \
                    RWExecutionState,         /* S2 */      \
                    void,                     /* DR */      \
                    const RWRunnable&,        /* D1 */      \
                    RWExecutionState,         /* D2 */      \
                    A1                        /* A1 */      \
                   >::make(function,a1)


/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2, a1)"
 * instead.
 *
 * Template function to create a runnable callback functor from a global
 * function that takes the runnable reference, the execution state, and one
 * additional argument. \a a1 must be convertible to an instance of type
 * \c A1.
 */
template <class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<const RWRunnable&, RWExecutionState>
rwtMakeRunnableCallback(void (*function)(const RWRunnable&, RWExecutionState, A1),
                        AA1 a1)
{
    return rwtMakeRunnableCallbackGA1(function, A1, a1);
}

/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, rw1, rw2, a1, a2)" instead.
 *
 * Macro to create a runnable callback functor from a global function that
 * takes a runnable reference, an execution state, and two additional
 * arguments.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableCallbackGA2", "Use rwBind() instead")
#define rwtMakeRunnableCallbackGA2(function,A1,a1,A2,a2)    \
   RWTFunctor2GA2Imp<const RWRunnable&,       /* S1 */      \
                    RWExecutionState,         /* S2 */      \
                    void,                     /* DR */      \
                    const RWRunnable&,        /* D1 */      \
                    RWExecutionState,         /* D2 */      \
                    A1,                       /* A1 */      \
                    A2                        /* A2 */      \
                   >::make(function,a1,a2)


/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, rw1, rw2, a1, a2)" instead.
 *
 * Template function to create a runnable callback functor from a global
 * function that takes the runnable reference, the execution state, and two
 * additional arguments. \a a1 and \a a2 must be convertible to instances of
 * types \c A1 and \c A2 respectively.
 */
template <class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<const RWRunnable&, RWExecutionState>
rwtMakeRunnableCallback(void (*function)(const RWRunnable&, RWExecutionState, A1, A2),
                        AA1 a1,
                        AA2 a2)
{
    return rwtMakeRunnableCallbackGA2(function, A1, a1, A2, a2);
}

/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2)" instead.
 *
 * Macro to create a runnable callback functor from a member function that
 * takes a runnable reference and an execution state as arguments.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableCallbackM", "Use rwBind() instead")
#define rwtMakeRunnableCallbackM(Callee,callee,function)    \
   RWTFunctor2MImp<const RWRunnable&,       /* S1 */        \
                  RWExecutionState,         /* S2 */        \
                  Callee,                   /* Callee */    \
                  void,                     /* DR */        \
                  const RWRunnable&,        /* D1 */        \
                  RWExecutionState          /* D2 */        \
                 >::make(callee,function)


/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2)" instead.
 *
 * Template function to create a runnable callback functor from a member
 * function that takes a runnable reference and an execution state as
 * arguments.
 */
template <class Callee>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<const RWRunnable&, RWExecutionState>
rwtMakeRunnableCallback(Callee& callee,
                        void (Callee::*function)(const RWRunnable&, RWExecutionState))
{
    return rwtMakeRunnableCallbackM(Callee, callee, function);
}

/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1)" instead.
 *
 * Macro to create a runnable callback functor from a global function that
 * takes a runnable reference, an execution state, and one additional
 * argument.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableCallbackMA1", "Use rwBind() instead")
#define rwtMakeRunnableCallbackMA1(Callee,callee,function,A1,a1)    \
   RWTFunctor2MA1Imp<const RWRunnable&,       /* S1 */              \
                    RWExecutionState,         /* S2 */              \
                    Callee,                   /* Callee */          \
                    void,                     /* DR */              \
                    const RWRunnable&,        /* D1 */              \
                    RWExecutionState,         /* D2 */              \
                    A1                        /* A1 */              \
                   >::make(callee,function,a1)


/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1)" instead.
 *
 * Template function to create a runnable callback functor from a global
 * function that takes the runnable reference, the execution state, and one
 * additional argument. \a a1 must be convertible to an instance of \c A1.
 */
template <class Callee, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<const RWRunnable&, RWExecutionState>
rwtMakeRunnableCallback(Callee& callee,
                        void (Callee::*function)(const RWRunnable&, RWExecutionState, A1),
                        AA1 a1)
{
    return rwtMakeRunnableCallbackMA1(Callee, callee, function, A1, a1);
}

/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1, a2)" instead.
 *
 * Macro to create a runnable callback functor from a global function that
 * takes a runnable reference, an execution state, and two additional
 * arguments.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableCallbackMA2", "Use rwBind() instead")
#define rwtMakeRunnableCallbackMA2(Callee,callee,function,A1,a1,A2,a2)    \
   RWTFunctor2MA2Imp<const RWRunnable&,       /* S1 */                    \
                    RWExecutionState,         /* S2 */                    \
                    Callee,                   /* Callee */                \
                    void,                     /* DR */                    \
                    const RWRunnable&,        /* D1 */                    \
                    RWExecutionState,         /* D2 */                    \
                    A1,                       /* A1 */                    \
                    A2                        /* A2 */                    \
                   >::make(callee,function,a1,a2)



/**
 * \ingroup rwtMakeRunnableCallback
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1, a2)" instead.
 *
 * Template function to create a runnable callback functor from a global
 * function that takes the runnable reference, the execution state, and two
 * additional arguments. \a a1 and \a a2 must be convertible to instances of
 * types \c A1 and \c A2 respectively.
 */
template <class Callee, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<const RWRunnable&, RWExecutionState>
rwtMakeRunnableCallback(Callee& callee,
                        void (Callee::*function)(const RWRunnable&, RWExecutionState, A1, A2),
                        AA1 a1,
                        AA2 a2)
{
    return rwtMakeRunnableCallbackMA2(Callee, callee, function, A1, a1, A2, a2);
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_thread_rwtMakeRunnableCallback_h__
