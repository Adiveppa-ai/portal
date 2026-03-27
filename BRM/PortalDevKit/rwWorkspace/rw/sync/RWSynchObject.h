#ifndef __rw_sync_RWSynchObject_h__
#define __rw_sync_RWSynchObject_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWSynchObject.h#1 $
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

#include <rw/sync/RWCancellationState.h>
#include <rw/sync/pkgdefs.h>
#include <rw/threxcept/threxcept.h>

/*****************************************************************************/

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Base class for synchronization classes.
 *
 * RWSynchObject is the base class for synchronization classes, RWMutexLock,
 * RWFIFOMutexLock, RWTRecursiveLock, RWSemaphore, RWCondition,
 * RWReadersWriterLock, and RWCriticalSection. The class contains methods
 * that support automatic cancellation detection for runnables containing a
 * thread that is accessing the \b acquire() or \b wait() members of these
 * derived classes.
 *
 * \sa
 * RWMutexLock, RWNullMutexLock, RWFIFOMutexLock, RWTRecursiveLock,
 * RWReadersWriterLock, RWSemaphore, RWCondition, RWCriticalSection
 */
class RW_SYNC_SYMBOLIC RWSynchObject
{

protected:
    RWCancellationState  cancellationState_;

public:

    // Destructor
    ~RWSynchObject();


    /**
     * Turns on automatic cancellation detection.
     */
    void
    enableCancellation(RWCancellationState);


    /**
     * Turns on automatic cancellation detection.
     */
    void
    setCancellation(RWCancellationState);


    /**
     * Turns off automatic cancellation detection.
     */
    void
    disableCancellation();


    /**
     * Returns \c true if automatic cancellation is enabled, otherwise
     * \c false.
     */
    bool
    isCancellationEnabled() const;

protected:


    /**
     * Enforces that this class be used only as a base class.
     */
    RWSynchObject(RWCancellationState state = RW_CANCELLATION_DISABLED);

    /**
     * Constructs a static instance, but does no direct initialization. The
     * RWSynchObject is initialized on first use.
     *
     * This constructor must be used only for static instances. Use of this
     * constructor with an automatically or dynamically allocated instance
     * produces errors or other unpredictable behavior.
     *
     * Static instances are zero initialized, which results in an
     * RWSynchObject with a cancellation state of #RW_CANCELLATION_DISABLED.
     */
    RWSynchObject(RWStaticCtor);

    /**
     * Copy constructor.
     */
    RWSynchObject(const RWSynchObject& second);


    /**
     * Assignment operator.
     */
    RWSynchObject& operator=(const RWSynchObject& second);

    // Test current runnable object (if any) for cancellation if
    // automatic cancellation detection is enabled...
    /**
     * Invokes a cancellation method if one has been registered, otherwise
     * does nothing.
     */
    void
    testCancellation();

private:

    // Test the current runnable object (if any) for cancellation
    void
    serviceCancellation();

};

/*****************************************************************************/

inline
RWSynchObject::RWSynchObject(RWCancellationState state)
    : cancellationState_(state)
{
}

// Constructor for use by derived class constructors taking RWStaticCtor.
// Used to construct global static instance of a derived class. Does not
// explicitly initialize, hence object may be used before constructed.
// Global instances are zero initialized, which will create an
// RWSynchObject with a cancellation state of RW_CANCELLATION_DISABLED.
inline
RWSynchObject::RWSynchObject(RWStaticCtor)
{
}

inline
RWSynchObject::RWSynchObject(const RWSynchObject& second)
    : cancellationState_(second.cancellationState_)
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWSynchObject&
RWSynchObject::operator=(const RWSynchObject& second)
{
    cancellationState_ = second.cancellationState_;
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

inline
RWSynchObject::~RWSynchObject()
{
}

inline void
RWSynchObject::enableCancellation(RWCancellationState state)
{
    cancellationState_ = state;
}

inline void
RWSynchObject::setCancellation(RWCancellationState state)
{
    cancellationState_ = state;
}

inline void
RWSynchObject::disableCancellation()
{
    cancellationState_ = RW_CANCELLATION_DISABLED;
}

inline bool
RWSynchObject::isCancellationEnabled() const
{
    return RW_CANCELLATION_DISABLED != cancellationState_;
}

inline void
RWSynchObject::serviceCancellation()
{
    RWCancellationState state_ = cancellationState_;
    if (RW_CANCELLATION_DISABLED != state_) {
        state_();
    }
}

inline void
RWSynchObject::testCancellation()
{
    if (RW_CANCELLATION_DISABLED != cancellationState_) {
        serviceCancellation();
    }
}

/*****************************************************************************/

#endif  // __rw_sync_RWSynchObject_h__
