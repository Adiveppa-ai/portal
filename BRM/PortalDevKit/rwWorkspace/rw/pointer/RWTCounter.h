#ifndef __rw_pointer_RWTCounter_h__
#define __rw_pointer_RWTCounter_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTCounter.h#1 $
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

#include <rw/pointer/RWTCountingBody.h>
#include <rw/pointer/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
/**
 * \ingroup smart_pointer_package
 *
 * \deprecated
 * As of SourcePro 11.1, use RWAtomicCounter.
 *
 * \brief
 * Deprecated. Maintains a reference count.
 *
 * A class for maintaining a reference count that uses the template type as
 * a lock for atomicity.
 *
 * Generally, applications will use one of two typedefs provided by the
 * Smart Pointer package. #RWSafeCounter is a typedef for
 * \ref RWTCounter "RWTCounter<RWMutexLock>" and provides thread-safe
 * reference counting. #RWUnsafeCounter is a typedef for
 * \ref RWTCounter "RWTCounter<RWNullMutexLock>" and can be used for greater
 * efficiency when thread safety is not required.
 *
 * \sa
 * RWSafeCounter, RWUnsafeCounter, RWTCountingPointer
 */
template <class Mutex >
class RW_DEPRECATE_TYPE("Use RWAtomicCounter instead") RWTCounter : public RWTCountingBody<Mutex>
{
public:

    typedef Mutex MutexType;

    /**
     * Constructs a default instance (initializes the reference count).
     * Throws no exceptions.
     */
    RWTCounter(unsigned initCount = 0);

    /**
     * Constructs a static instance (does not initialize the reference
     * count). Throws no exceptions.
     */
    RWTCounter(RWStaticCtor);

    //--Defines copy constructor so derived classes can copy-construct,
    //--but initializes the reference count; don't copy it.
    //--Throws no exceptions.
    /**
     * Does not copy the internal count. This method is provided as a
     * convenience to derived classes.
     */
    RWTCounter(const RWTCounter<Mutex>& second);

    // Destructor
    ~RWTCounter(void);

    //--Define an assignment operator so derived classes can do assignments.
    //--Don't assign the reference count.
    //--Throws no exceptions.
    /**
     * Does not assign the internal count. This method is provided as a
     * convenience to derived classes.
     */
    RWTCounter<Mutex>&
    operator=(const RWTCounter<Mutex>& second);
};

///////////////////////////////////////////////////////////////////////////////

template <class Mutex>
inline
RWTCounter<Mutex>::RWTCounter(unsigned initCount)
    :
    RWTCountingBody<Mutex>(initCount)
{
}

template <class Mutex>
inline
RWTCounter<Mutex>::RWTCounter(RWStaticCtor)
    :
    RWTCountingBody<Mutex>(RW_STATIC_CTOR)
{
}

template <class Mutex>
inline
RWTCounter<Mutex>::RWTCounter(const RWTCounter<Mutex>&)
    : RWTCountingBody<Mutex>()
{
    // Don't copy anything
}

template <class Mutex>
inline
RWTCounter<Mutex>::~RWTCounter(void)
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
template <class Mutex>
inline RWTCounter<Mutex>&
RWTCounter<Mutex>::operator=(const RWTCounter<Mutex>&)
{
    // Don't assign anything
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

#endif


#endif // __rw_pointer_RWTCounter_h__
