#ifndef __rw_trace_RWTraceOstreamClient_h__
#define __rw_trace_RWTraceOstreamClient_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceOstreamClient.h#1 $
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
 * Trace client that sends all events to an ostream. If no 'ostream' is
 * specified, 'cerr' is used by default.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventClient.h>
#include <rw/trace/pkgdefs.h>
#include <iosfwd>


class RWTraceOstreamClientImp;

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A handle class for a trace event client that sends all events to an
 * \b std::ostream.
 *
 * RWTraceOstreamClient is a trace client that sends all events to an
 * \b std::ostream. If no \b std::ostream is specified, uses \b std::cerr by
 * default.
 *
 * \example
 * \code
 * #include <rw/trace/trace.h>
 * . . .
 * RWTraceOstreamClient myTraceClient(std::cerr);
 * \endcode
 * \endexample
 *
 * \sa
 * RWTraceOstreamClientImp
 */
class RW_TRACE_GLOBAL RWTraceOstreamClient : public RWTraceEventClient
{

public:

    /**
     * Creates a client that outputs trace events to \b std::cerr.
     */
    RWTraceOstreamClient();

    /**
     * Creates a client that outputs trace events to the specified
     * \b std::ostream.
     */
    RWTraceOstreamClient(std::ostream& ostr);

    /**
     * Attaches to and increments the reference count on \a bodyP.
     */
    RWTraceOstreamClient(RWTraceOstreamClientImp* bodyP);

    /**
     * Constructs a global static handle instance (that may be used before
     * being constructed).
     */
    RWTraceOstreamClient(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTraceOstreamClient(const RWTraceOstreamClient& second);

    /**
     * Destructor.
     */
    ~RWTraceOstreamClient(void);

};

#endif // __rw_trace_RWTraceOstreamClient_h__
