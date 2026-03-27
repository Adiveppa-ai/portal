#ifndef __rw_pointer_RWAtomicCounter_h__
#define __rw_pointer_RWAtomicCounter_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWAtomicCounter.h#1 $
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

#include <rw/pointer/pkgdefs.h>
#include <rw/tools/atomic.h>

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Maintains a reference count safely in a multithreaded environment.
 *
 * RWAtomicCounter maintains a reference count and can safely be used in a
 * multithreaded environment.
 *
 * \example
 * \code
 * #include <rw/pointer/RWAtomicCounter.h>
 * #include <rw/pointer/RWTCountingPointer.h>
 *
 * int main()
 * {
 *   RWTCountingPointer<int, RWAtomicCounter> pointer = new int(10);
 *
 *   return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_POINTER_SYMBOLIC RWAtomicCounter
{
public:

    /**
     * Constructs a default instance that initializes the reference count.
     * Throws no exceptions.
     */
    RWAtomicCounter(unsigned n = 0);

    /**
     * Constructs a static instance that does not initialize the reference
     * count. Throws no exceptions.
     */
    RWAtomicCounter(RWStaticCtor);

    // Defines copy constructor so derived classes can copy-construct,
    // but initializes the reference count; don't copy it.
    // Throws no exceptions.
    /**
     * Default-initializes the internal count to zero.
     */
    RWAtomicCounter(const RWAtomicCounter&);

    // Destructor
    ~RWAtomicCounter(void);

    /**
     * Queries the current reference count. Throws no exceptions.
     */
    unsigned
    references(void) const;

    /**
     * Increments the reference count and then returns the previous value
     * minus one.
     */
    unsigned
    addReference(void);

    /**
     * Decrements the reference count and then returns the previous value
     * minus one.
     */
    unsigned
    removeReference(void);

    // Define an assignment operator so derived classes can do assignments.
    // Don't assign the reference count.
    // Throws no exceptions.
    /**
     * Copy assignment operator that does nothing, allowing derived classes
     * to do assignments. Returns \c *this.
     */
    RWAtomicCounter&
    operator=(const RWAtomicCounter&);


private:

    RWTAtomic<unsigned> counter_;
};


inline
RWAtomicCounter::RWAtomicCounter(unsigned n)
    : counter_()
{
    counter_.store(n, rw_mem_order_relaxed);
}

inline
RWAtomicCounter::RWAtomicCounter(RWStaticCtor)
{
}

inline
RWAtomicCounter::RWAtomicCounter(const RWAtomicCounter&)
    : counter_()
{
}

inline
RWAtomicCounter::~RWAtomicCounter(void)
{
}

inline unsigned
RWAtomicCounter::references(void) const
{
    return counter_.load(rw_mem_order_acquire);
}

inline unsigned
RWAtomicCounter::addReference(void)
{
    return counter_++ - 1;
}

inline unsigned
RWAtomicCounter::removeReference(void)
{
    return counter_-- - 1;
}

inline RWAtomicCounter&
RWAtomicCounter::operator=(const RWAtomicCounter&)
{
    return *this;
}

#endif // __rw_pointer_RWAtomicCounter_h__
