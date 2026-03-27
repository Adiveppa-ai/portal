#ifndef __rw_trace_RWTraceEventFilter_h__
#define __rw_trace_RWTraceEventFilter_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceEventFilter.h#1 $
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
 * Handle for trace event filter implementation.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventClient.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A handle class for trace event filter implementations.
 *
 * RWTraceEventFilter is the handle for a trace event filter implementation.
 * A trace filter accepts trace information and forwards it to a client.
 *
 * \sa
 * RWTraceEventClient, RWTraceEventFilterImp
 */
class RW_TRACE_GLOBAL RWTraceEventFilter : public RWTraceEventClient
{

    friend class RWTraceEventClientImp;  // give access to add & remove methods

public:

    /**
     * Creates an unattached handle.
     */
    RWTraceEventFilter();

    /**
     * Attaches to and increments the reference count on \a bodyP.
     */
    RWTraceEventFilter(RWTraceEventFilterImp* bodyP);

    /**
     * Constructs a global static handle instance (that may be used before
     * being constructed).
     */
    RWTraceEventFilter(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTraceEventFilter(const RWTraceEventFilter& second);

    /**
     * Destructor.
     */
    ~RWTraceEventFilter(void);

protected:

    void add(RWTraceEventClientImp* clientP);

    void remove(RWTraceEventClientImp* clientP);
};

#endif // __rw_trace_RWTraceEventFilter_h__
