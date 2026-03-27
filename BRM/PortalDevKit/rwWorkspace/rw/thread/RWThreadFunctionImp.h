#ifndef __rw_thread_RWThreadFunctionImp_h__
#define __rw_thread_RWThreadFunctionImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadFunctionImp.h#1 $
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

  RWThreadFunctionImp - RWTFunctor<void()>-based thread class.

******************************************************************************/

#include <rw/thread/RWThreadImp.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>

class RW_THREAD_GLOBAL RWThreadFunctionImp :
    public RWThreadImp
{

    friend class RWThreadFunction;
    friend class RWThreadFunctionSelf;

public:

    // Destructor
    ~RWThreadFunctionImp(void);

private:

    RWTFunctor<void()> functor_;

protected:

    // Make a RWTFunctor<void()>-based thread with an undefined functor instance.
    static
    RWThreadFunction
    make(void);

    // Make a RWTFunctor<void()>-based thread using the specified functor instance.
    static
    RWThreadFunction
    make(const RWTFunctor<void()>& functor);

    // Make a RWTFunctor<void()>-based thread using the specified functor
    // and specified thread attribute instance.
    static
    RWThreadFunction
    make(const RWTFunctor<void()>& functor,
         const RWThreadAttribute& attr);

    // Make a RWTFunctor<void()>-based thread with an undefined functor instance and
    // using the specified thread attribute instance.
    static
    RWThreadFunction
    make(const RWThreadAttribute& attr);

    // Set or change the functor instance that will execute when this
    // thread runnable is started.
    void
    setFunctor(const RWTFunctor<void()>& functor);

    // Get the current functor instance associated with this thread runnable.
    RWTFunctor<void()>
    getFunctor(void) const;

protected:

    // Protect constructors (only accessible by make functions)

    RWThreadFunctionImp(void);

    RWThreadFunctionImp(const RWTFunctor<void()>& functor);

    RWThreadFunctionImp(const RWTFunctor<void()>& functor,
                        const RWThreadAttribute& attr);

    RWThreadFunctionImp(const RWThreadAttribute& attr);

    // Override the virtual run() member to invoke functor at start-up.
    virtual
    void
    run(void);

private:

    RWThreadFunctionImp(const RWThreadFunctionImp& second);

    RWThreadFunctionImp&
    operator=(const RWThreadFunctionImp& second);

};

/*****************************************************************************/

inline
RWThreadFunctionImp::RWThreadFunctionImp(void)
{
}

inline
RWThreadFunctionImp::RWThreadFunctionImp(const RWTFunctor<void()>& functor)
    :
    functor_(functor)
{
}

inline
RWThreadFunctionImp::RWThreadFunctionImp(const RWTFunctor<void()>& functor,
        const RWThreadAttribute& attr)
    :
    RWThreadImp(attr),
    functor_(functor)
{
}

inline
RWThreadFunctionImp::RWThreadFunctionImp(const RWThreadAttribute& attr)
    :
    RWThreadImp(attr)
{
}

inline
RWThreadFunctionImp::~RWThreadFunctionImp(void)
{
}

#endif // __rw_thread_RWThreadFunctionImp_h__
