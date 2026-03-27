#ifndef __rw_trace_RWTraceLevelFilterImp_h__
#define __rw_trace_RWTraceLevelFilterImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceLevelFilterImp.h#1 $
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
 * Implementation (body) for 'RWTraceLevelFilter'.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventSeverity.h>
#include <rw/trace/RWTraceSingleClientFilterImp.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A body class for trace level filter implementations.
 *
 * RWTraceLevelFilterImp is the implementation (body) for
 * RWTraceLevelFilter.
 *
 * \sa
 * RWTraceLevelFilter
 */
class RW_TRACE_GLOBAL RWTraceLevelFilterImp : public RWTraceSingleClientFilterImp
{

public:

    /**
     * Destructor.
     */
    ~RWTraceLevelFilterImp(void);

    /**
     * Creates a new RWTraceLevelFilterImp instance that filters based on
     * level. By default, all trace events are filtered out.
     */
    static RWTraceSingleClientFilter make(RWTraceEventSeverity level = RW_TRACE_LEVEL_NONE);

    /**
     * Public interface for getting the filter's severity level. Forwards to
     * the internal protected doGetLevel() member.
     */
    RWTraceEventSeverity getLevel() const;

    /**
     * Public interface for setting the filter's severity level. Forwards to
     * the internal protected doSetLevel() member.
     */
    void setLevel(RWTraceEventSeverity level);

protected:

    /**
     * Default constructor. Trace level is #RW_TRACE_LEVEL_NONE.
     */
    RWTraceLevelFilterImp(void);

    /**
     * Constructor that takes a severity level.
     */
    RWTraceLevelFilterImp(RWTraceEventSeverity level);

    /**
     * Forwards the trace event to the attached client if the event's
     * severity is greater or equal to the filter's severity level.
     */
    virtual void doTrace(const RWTraceEvent& ev);

    /**
     * Returns the filter's severity level.
     */
    virtual RWTraceEventSeverity doGetLevel() const;

    /**
     * Sets the severity level for the filter, overriding any existing
     * level.
     */
    virtual void doSetLevel(RWTraceEventSeverity level);

private:

    RWTraceEventSeverity level_;

};


inline RWTraceEventSeverity
RWTraceLevelFilterImp::getLevel() const
{
    return doGetLevel();
}


inline void
RWTraceLevelFilterImp::setLevel(RWTraceEventSeverity level)
{
    doSetLevel(level);
}

#endif // __rw_trace_RWTraceLevelFilterImp_h__
