#ifndef __rw_thread_RWTRunnableIOUFunctionImp_h__
#define __rw_thread_RWTRunnableIOUFunctionImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTRunnableIOUFunctionImp.h#1 $
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

  RWTRunnableIOUFunctionImp<Return> - RWTFunctor<R()>-based runnable class that
                                      uses IOUs to capture return values.

******************************************************************************/

#include <rw/thread/RWRunnableImp.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWRunnableIOUFunctionImp RWTRunnableIOUFunctionImp
#endif

template <class Return>
class RWTRunnableIOUFunctionImp :
    public RWRunnableImp
{

    friend class RWTRunnableIOUFunction<Return>;

public:

    // Destructor
    ~RWTRunnableIOUFunctionImp(void);

private:

    // Handle for functor instance
    RWTFunctor<Return()>  functor_;

    // Handle for escrow instance
    RWTIOUEscrow<Return>  escrow_;

protected:

    RWTRunnableIOUFunctionImp(const RWTIOUEscrow<Return>& escrow);

    RWTRunnableIOUFunctionImp(const RWTIOUEscrow<Return>& escrow,
                              const RWTFunctor<Return()>& functor);

    // Get a handle bound to the RWTFunctor instance, if any, currently
    // associated with this RWTRunnableIOUFunction instance.
    RWTFunctor<Return()>
    getFunctor(void) const;

    // Get an RWTIOUResult handle bound to the
    // current escrow instance (if any!)
    RWTIOUResult<Return>
    result(void) const;

    // Bind the functor handle to the functor
    // instance pointed-to by another handle.
    void
    setFunctor(const RWTFunctor<Return()>& functor);

    // Use this member to specify a new escrow instance for the runnable to
    // use in capturing the results of a functor invocation.  Changing the
    // escrow instance will not have any affect until the next time the
    // runnable is started.  Each time a RWThread runnable is restarted,
    // it checks its current escrow instance to see if it is valid, and if
    // so, then checks to see whether or not it  has already been used to
    // capture a result, an exception, or has been aborted.  If the escrow
    // is found to be in any of these "redeemable" states, then a new escrow
    // instance is automatically created to capture the next result.
    void
    setIOUEscrow(const RWTIOUEscrow<Return>& escrow);

    // Override RWRunnableImp run() member to call the specified functor, if
    // any, and use the specified escrow, if any, to capture the results of
    // the functor invocation.
    virtual
    void
    run(void);

private:

    RWTRunnableIOUFunctionImp(const RWTRunnableIOUFunctionImp& second);

    RWTRunnableIOUFunctionImp&
    operator=(const RWTRunnableIOUFunctionImp& second);

};

/*****************************************************************************/

template <class Return>
inline
RWTRunnableIOUFunctionImp<Return>::~RWTRunnableIOUFunctionImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/thread/RWTRunnableIOUFunctionImp.cc>
#endif

#endif // __rw_thread_RWTRunnableIOUFunctionImp_h__
