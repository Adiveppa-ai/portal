#ifndef __rw_trace_RWTraceEventSeverity_h__
#define __rw_trace_RWTraceEventSeverity_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceEventSeverity.h#1 $
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
 * Tracing severity levels; provides basis for convenience macros.
 *
 *************************************************************************/

#include <rw/trace/pkgdefs.h>
#include <iosfwd>

/**
 * \ingroup execution_tracing_package
 *
 * RWTraceEventSeverity contains tracing severity levels; provides basis for
 * convenience macros.
 */
enum RWTraceEventSeverity {

    /**
     * &nbsp;
     */
    RW_TRACE_LEVEL_NONE = 0,

    /**
     * &nbsp;
     */
    RW_TRACE_LEVEL_UNSPECIFIED  = 1,

    /**
     * unrecoverable error
     */
    RW_TRACE_LEVEL_FATAL = 2,

    /**
     * recoverable error
     */
    RW_TRACE_LEVEL_ERROR = 3,

    /**
     * insignificant or potential error
     */
    RW_TRACE_LEVEL_WARNING = 4,

    /**
     * general status or resource mngmnt
     */
    RW_TRACE_LEVEL_INFO = 5,

    /**
     * used for testing
     */
    RW_TRACE_LEVEL_TEST = 6,

    /**
     * used for debugging
     */
    RW_TRACE_LEVEL_DEBUG = 7,

    /**
     * entry/exit (automatic)
     */
    RW_TRACE_LEVEL_ENTRY = 8
};

/**
 * \ingroup execution_tracing_package
 *
 * Streams an input stream into an RWTraceEventSeverity.
 */
RW_TRACE_SYMBOLIC std::istream& operator>>(std::istream& strm,
        RWTraceEventSeverity& crit);

/**
 * \ingroup execution_tracing_package
 *
 * Streams an RWTraceEventSeverity into an output stream.
 */
RW_TRACE_SYMBOLIC std::ostream& operator<<(std::ostream& strm,
        const RWTraceEventSeverity& crit);


#endif // __rw_trace_RWTraceEventSeverity_h__
