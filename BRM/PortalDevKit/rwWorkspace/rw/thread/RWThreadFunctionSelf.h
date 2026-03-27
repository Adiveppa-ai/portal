#ifndef __rw_thread_RWThreadFunctionSelf_h__
#define __rw_thread_RWThreadFunctionSelf_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadFunctionSelf.h#1 $
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

  RWThreadFunctionSelf - Handle class that provides an interface to the thread
                         running inside of the currently executing threaded
                         runnable.

******************************************************************************/

#include <rw/thread/RWThreadFunctionImp.h>
#include <rw/thread/RWThreadSelf.h>
#include <rw/thread/pkgdefs.h>

// Forward declarations...
class RW_THREAD_GLOBAL RWThreadFunction;
class RW_THREAD_GLOBAL RWThreadFunctionImp;

class RW_THREAD_GLOBAL RWThreadFunctionSelf :
    public RWThreadSelf
{

    friend class RWThreadFunctionImp;
    friend class RWThreadFunction;

public:

    // Construct an empty (invalid) handle
    RWThreadFunctionSelf(void);

    // Construct an external interface handle to the thread object
    // pointed-to by a second handle (if any).
    RWThreadFunctionSelf(const RWThreadFunctionSelf& second);

    // Destructor
    ~RWThreadFunctionSelf(void);

    // Bind this external interface handle to the thread object
    // pointed-to by a second handle (if any)
    RWThreadFunctionSelf&
    operator=(const RWThreadFunctionSelf& second);

    // Return an internal interface handle to the thread object
    // pointed-to by an external interface handle (if any).
    RWThreadFunction
    getRWThreadFunction(void) const;

protected:

    // Construct an internal interface handle to the RWThreadImp
    // instance (if any) pointed-to by an external interface handle
    RWThreadFunctionSelf(const RWThreadFunction& second);

    // Override the parent class body() function to provide
    // a version that casts to this handle's body class
    RWThreadFunctionImp&
    body(void) const;

};

/*****************************************************************************/

inline
RWThreadFunctionSelf::RWThreadFunctionSelf(void)
{
}

inline
RWThreadFunctionSelf::RWThreadFunctionSelf(const RWThreadFunctionSelf& second)
    :
    RWThreadSelf(second)
{
}

inline
RWThreadFunctionSelf::~RWThreadFunctionSelf(void)
{
}

inline
RWThreadFunctionSelf&
RWThreadFunctionSelf::operator=(const RWThreadFunctionSelf& second)
{
    if (&second != this) {
        RWThreadSelf::operator=(second);
    }
    return *this;
}

inline
RWThreadFunctionImp&
RWThreadFunctionSelf::body(void) const
{
    return (RWThreadFunctionImp&)RWThreadSelf::body();
}

#endif // __rw_thread_RWThreadFunctionSelf_h__
