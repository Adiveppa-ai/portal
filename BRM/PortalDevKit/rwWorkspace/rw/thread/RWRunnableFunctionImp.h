#ifndef __rw_thread_RWRunnableFunctionImp_h__
#define __rw_thread_RWRunnableFunctionImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableFunctionImp.h#1 $
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

  RWRunnableFunctionImp - RWTFunctor<void()>-based runnable class.

******************************************************************************/

#include <rw/thread/RWRunnableImp.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>

class RW_THREAD_GLOBAL RWRunnableFunctionImp :
    public RWRunnableImp
{

    friend class RWRunnableFunction;
    friend class RWRunnableFunctionSelf;

public:

    // Destructor
    ~RWRunnableFunctionImp(void);

private:

    RWTFunctor<void()> functor_;

protected:

    // Make a RWTFunctor<void()>-based runnable with an undefined functor instance.
    static
    RWRunnableFunction
    make(void);

    // Make a RWTFunctor<void()>-based runnable using the specified functor instance.
    static
    RWRunnableFunction
    make(const RWTFunctor<void()>& functor);

    // Set or change the functor instance that will execute when this
    // runnable runnable is started.
    void
    setFunctor(const RWTFunctor<void()>& functor);

    // Get the current functor instance associated with this runnable runnable.
    RWTFunctor<void()>
    getFunctor(void) const;

protected:

    // Protect constructors (only accessible by make functions)

    RWRunnableFunctionImp(void);

    RWRunnableFunctionImp(const RWTFunctor<void()>& functor);

    // Override the virtual run() member to invoke functor at start-up.
    virtual
    void
    run(void);


private:

    RWRunnableFunctionImp(const RWRunnableFunctionImp& second);

    RWRunnableFunctionImp&
    operator=(const RWRunnableFunctionImp& second);

};

/*****************************************************************************/

// protected
inline
RWRunnableFunctionImp::RWRunnableFunctionImp(void)
{
}

// protected
inline
RWRunnableFunctionImp::RWRunnableFunctionImp(const RWTFunctor<void()>& functor)
    :
    functor_(functor)
{
}

inline
RWRunnableFunctionImp::~RWRunnableFunctionImp(void)
{
}

#endif // __rw_thread_RWRunnableFunctionImp_h__
