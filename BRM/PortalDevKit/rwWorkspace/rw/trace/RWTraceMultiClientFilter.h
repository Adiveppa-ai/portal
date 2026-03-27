#ifndef __rw_trace_RWTraceMultiClientFilter_h__
#define __rw_trace_RWTraceMultiClientFilter_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceMultiClientFilter.h#1 $
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
 * Filter that accepts multiple clients and forwards trace events to them.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventFilter.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A handle class for a trace event filter that accepts multiple clients.
 *
 * RWTraceMultiClientFilter is a filter that accepts multiple clients to
 * which it forwards trace events.
 *
 * \example
 * This example creates two clients; one displays messages on the screen,
 * and the other saves them to a file. This example can be found in
 * <tt>examples/trace/MultiClient.cpp</tt>.
 *
 * \code
 * #define RW_USER_TRACE_LEVEL 8
 * #include <rw\trace\trace.h>
 *
 * #include <fstream>
 *
 * int main(void)
 * {
 *     // Declare function as traceable with the set name "main"
 *     // this will also generate an entry/exit event
 *     RW_USER_TRACEABLE_FUNCTION("main");                            //1
 *
 *     // Create an output file stream.
 *     std::ofstream traceLog("MultiClient.log");
 *
 *     // Create an Ostream client on the file stream.
 *     RWTraceOstreamClient logClient(traceLog);
 *
 *     // Create an Ostream client on cerr.
 *     RWTraceOstreamClient cerrClient(std::cerr);
 *
 *     // Create a multiclient filter that sends messages to
 *     // multiple clients.
 *     RWTraceMultiClientFilter multiClient;                         //2
 *
 *     // Connect both clients to the multiClient.  This must occur
 *     // before the multiClient is connected to the manager to
 *     // prevent loss of data.
 *     logClient.connect(multiClient);                               //3
 *     cerrClient.connect(multiClient);
 *
 *     // Connect the multiclient to the trace manager.
 *     multiClient.connectToManager();                               //4
 *
 *     // Generate some trace messages; these trace events
 *     // will belong to the sets "rw_user" and "main"
 *     RW_USER_TRACE_DEBUG("Debug");                                 //5
 *     RW_USER_TRACE_TEST("Test");
 *     RW_USER_TRACE_INFO("Info");
 *     RW_USER_TRACE_WARNING("Warning");
 *     RW_USER_TRACE_ERROR("Error");
 *     RW_USER_TRACE_FATAL("Fatal");
 *
 *     return 0;
 * }
 * \endcode
 *
 * \c //1 Declares the function as traceable, so you can use trace event
 * generation macros in this function.
 *
 * \c //2 Instantiates the multi-client filter.
 *
 * \c //3 First connects the two clients to the filter.
 *
 * \c //4 Then connects the filter to the manager to ensure that no trace
 * messages are lost.
 *
 * \c //5 Generates some trace messages.
 * \endexample
 */
class RW_TRACE_GLOBAL RWTraceMultiClientFilter : public RWTraceEventFilter
{

public:

    /**
     * Constructs an RWTraceMultiClientFilter (handle) and its body.
     */
    RWTraceMultiClientFilter(void);

    /**
     * Attaches to and increments the reference count on \a bodyP.
     */
    RWTraceMultiClientFilter(RWTraceMultiClientFilterImp* bodyP);

    /**
     * Constructs a global static handle instance (that may be used before
     * being constructed).
     */
    RWTraceMultiClientFilter(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTraceMultiClientFilter(const RWTraceMultiClientFilter& second);

    /**
     * Destructor.
     */
    ~RWTraceMultiClientFilter(void);

};

#endif // __rw_trace_RWTraceMultiClientFilter_h__
