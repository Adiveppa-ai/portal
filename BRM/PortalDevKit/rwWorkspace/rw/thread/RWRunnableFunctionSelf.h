#ifndef __rw_thread_RWRunnableFunctionSelf_h__
#define __rw_thread_RWRunnableFunctionSelf_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableFunctionSelf.h#1 $
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

  RWRunnableFunctionSelf - Handle class that provides an interface to the thread
                           running inside of the currently executing runnable.

******************************************************************************/

#include <rw/thread/RWRunnableFunctionImp.h>
#include <rw/thread/RWRunnableSelf.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>

class RW_THREAD_GLOBAL RWRunnableFunctionSelf :
    public RWRunnableSelf
{

    friend class RWRunnableFunctionImp;
    friend class RWRunnableFunction;

public:

    // Construct an empty, invalid, handle instance
    RWRunnableFunctionSelf(void);

    // Construct a global static handle instance
    // (may be used before constructed)
    RWRunnableFunctionSelf(RWStaticCtor);

    // Bind a new handle instance to the runnable instance, if any,
    // pointed-to by another handle instance
    RWRunnableFunctionSelf(const RWRunnableFunctionSelf& second);

    // Destructor
    ~RWRunnableFunctionSelf(void);

    // Bind this handle instance to the runnable instance, if any,
    // pointed-to by another handle instance
    RWRunnableFunctionSelf&
    operator=(const RWRunnableFunctionSelf& second);

    // Return an internal interface handle to the runnable object
    // pointed-to by an external interface handle (if any).
    RWRunnableFunction
    getRWRunnableFunction(void) const;

protected:

    // Bind an internal interface handle instance to the RWRunnableImp
    // instance, if any, pointed-to by an external handle instance
    RWRunnableFunctionSelf(const RWRunnableFunction& second);

    // Override the parent class body() function to provide
    // a version that casts to this handle's body class
    RWRunnableFunctionImp&
    body(void) const;

};

/*****************************************************************************/

inline
RWRunnableFunctionSelf::RWRunnableFunctionSelf(void)
{
}

inline
RWRunnableFunctionSelf::RWRunnableFunctionSelf(RWStaticCtor)
    :
    RWRunnableSelf(RW_STATIC_CTOR)
{
}

inline
RWRunnableFunctionSelf::RWRunnableFunctionSelf(const RWRunnableFunctionSelf& second)
    :
    RWRunnableSelf(second)
{
}

inline
RWRunnableFunctionSelf::~RWRunnableFunctionSelf(void)
{
}

inline RWRunnableFunctionSelf&
RWRunnableFunctionSelf::operator=(const RWRunnableFunctionSelf& second)
{
    if (&second != this) {
        RWRunnableSelf::operator=(second);
    }
    return *this;
}

inline RWRunnableFunctionImp&
RWRunnableFunctionSelf::body(void) const
{
    return (RWRunnableFunctionImp&)RWRunnableSelf::body();
}

#endif // __rw_thread_RWRunnableFunctionSelf_h__
