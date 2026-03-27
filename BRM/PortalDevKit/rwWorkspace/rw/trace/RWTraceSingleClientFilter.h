#ifndef __rw_trace_RWTraceSingleClientFilter_h__
#define __rw_trace_RWTraceSingleClientFilter_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceSingleClientFilter.h#1 $
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

/**************************************************************************
 *
 * Description:
 *
 * Handle for filter implementation that accepts one client to which it
 * forwards trace events.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventFilter.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A handle class for a trace event filter that accepts only one client.
 *
 * RWTraceSingleClientFilter is the handle for a filter implementation that
 * accepts one client and forwards trace events to it.
 *
 * \sa
 * RWTraceSingleClientFilterImp, RWTraceMultiClientFilter
 */
class RW_TRACE_GLOBAL RWTraceSingleClientFilter : public RWTraceEventFilter
{

public:

    /**
     * Constructs a handle with no body.
     */
    RWTraceSingleClientFilter(void);

    /**
     * Attaches to and increments the reference count on \a bodyP.
     */
    RWTraceSingleClientFilter(RWTraceSingleClientFilterImp* bodyP);

    /**
     * Constructs a global static handle instance (that may be used before
     * being constructed).
     */
    RWTraceSingleClientFilter(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTraceSingleClientFilter(const RWTraceSingleClientFilter& second);

    /**
     * Destructor.
     */
    ~RWTraceSingleClientFilter(void);

    /**
     * Disconnects the attached client.
     */
    void disconnectClient(void);

};

#endif // __rw_trace_RWTraceSingleClientFilter_h__
