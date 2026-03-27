#ifndef __rw_thread_RWCancellationImp_h__
#define __rw_thread_RWCancellationImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWCancellationImp.h#1 $
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

  RWCancellationImp - Body class for thread cancellation object.

*****************************************************************************/

#include <rw/thread/pkgdefs.h>
#include <rw/pointer/RWBodyBase.h>

class RW_THREAD_GLOBAL RWRunnableImp;

class RW_THREAD_GLOBAL RWCancellationImp :
    public RWBodyBase
{


protected:

    bool         isAcknowledged_;
    RWRunnableImp*    runnableImpP_;

public:

    // Construct a cancellation object and notify the target runnable
    // that cancellation has started.
    RWCancellationImp(RWRunnableImp* runnableImpP);

    RWCancellationImp(const RWCancellationImp& second);

    RWCancellationImp&
    operator=(const RWCancellationImp& second);

    // If this instance has not been acknowledged, notify the target
    // runnable that this cancellation instance is being destroyed so
    // it will know that the cancellation attempt was unsuccessful.
    ~RWCancellationImp(void);

    // Acknowledge receipt of cancellation to turn-off
    // automated cancellation abort processing.
    void
    acknowledge(void);

    // Runnable target for cancellation
    RWRunnableImp*
    target(void) const;

};

/*****************************************************************************/

inline void
RWCancellationImp::acknowledge(void)
{
    isAcknowledged_ = true;
}

inline RWRunnableImp*
RWCancellationImp::target(void) const
{
    return runnableImpP_;
}

#endif // __rw_thread_RWCancellationImp_h__
