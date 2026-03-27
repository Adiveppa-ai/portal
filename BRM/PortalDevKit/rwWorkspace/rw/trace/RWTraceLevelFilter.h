#ifndef __rw_trace_RWTraceLevelFilter_h__
#define __rw_trace_RWTraceLevelFilter_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceLevelFilter.h#1 $
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
 * Single-client filter that lets only events of the supplied severity or
 * higher pass through.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventSeverity.h>
#include <rw/trace/RWTraceSingleClientFilter.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A handle class for a single-client filter that lets events only of the
 * supplied severity level or higher to pass through.
 *
 * RWTraceLevelFilter is a single-client trace filter that accepts events
 * only of the supplied severity level or higher, and forwards them to a
 * client.
 *
 * \example
 * This example is located in your installation directory at
 * <tt>examples/trace/LevelFilter.cpp</tt>.
 *
 * \code
 * #define RW_USER_TRACE_LEVEL 8                                  //1
 *
 * #include <rw/trace/trace.h>
 *
 * int main(void)
 * {
 *     // declare function as traceable with the set name "main"
 *     // this also generates an entry/exit event
 *     RW_USER_TRACEABLE_FUNCTION("main");                        //2
 *
 *     // create trace client that logs messages to cerr
 *     RWTraceOstreamClient client(std::cerr);                    //3
 *
 *     // create filter that lets only INFO and more important
 *     // events pass through
 *     RWTraceLevelFilter levelFilter(RW_TRACE_LEVEL_INFO);       //4
 *
 *     // connect client to level filter
 *     client.connect(levelFilter);                               //5
 *
 *     // connect level filter to manager
 *     levelFilter.connectToManager();                            //6
 *
 *     // generate some trace information; these trace events
 *     // will belong to the sets "rw_user" and "main"
 *     RW_USER_TRACE_DEBUG("Debug (hidden)");
 *     RW_USER_TRACE_TEST("Test (hidden)");
 *     RW_USER_TRACE_INFO("Info");
 *     RW_USER_TRACE_WARNING("Warning");
 *     RW_USER_TRACE_ERROR("Error");
 *     RW_USER_TRACE_FATAL("Fatal");
 *
 *     // change the level
 *     levelFilter.setLevel(RW_TRACE_LEVEL_ERROR);                //7
 *
 *     // generate some more trace information; these trace
 *     // events will belong to the sets "rw_user" and "main"
 *     RW_USER_TRACE_DEBUG("Debug (hidden)");
 *     RW_USER_TRACE_TEST("Test (hidden)");
 *     RW_USER_TRACE_INFO("Info (hidden)");
 *     RW_USER_TRACE_WARNING("Warning (hidden)");
 *     RW_USER_TRACE_ERROR("Error");
 *     RW_USER_TRACE_FATAL("Fatal");
 *
 *     return 0;
 * }
 * \endcode
 *
 * \c //1 Compile in all trace macros by setting the user trace level macro
 * to 8, the maximum (Entry/Exit) level. You can also define the trace level
 * on the command line for your compiler, using the flag
 * \c -DRW_USER_TRACE_LEVEL=8.
 *
 * \c //2 Declare the function as traceable, so you can use trace event
 * generation macros in this function.
 *
 * \c //3 Create a normal \b std::ostream client to display the trace
 * information.
 *
 * \c //4 Instantiate an RWTraceLevelFilter. The constructor takes the
 * minimum severity (i.e. the maximum level) of trace messages to pass
 * through. You can pass an integer level number cast to
 * RWTraceEventSeverity or use one of the symbolic constants, as in this
 * line. Pass RW_TRACE_LEVEL_NONE to filter out all trace messages. See the
 * discussion on trace level filters in the <em>Threads Module User's
 * Guide</em> for a definition of the severity levels.
 *
 * \c //5 Connect the client to the level filter.
 *
 * \c //6 Then connect the filter to the trace manager.
 *
 * \c //7 Change the cutoff level on the level filter, using the setLevel()
 * function.
 *
 * All of these constants map directly to the appropriate severity level.
 * #RW_TRACE_LEVEL_NONE filters out all trace messages. It is equivalent to
 * zero.
 * \endexample
 */
class RW_TRACE_GLOBAL RWTraceLevelFilter : public RWTraceSingleClientFilter
{

public:

    /**
     * Default constructor. The default level is RW_TRACE_LEVEL_NONE; no events
     * are passed on.
     */
    RWTraceLevelFilter();

    /**
     * Constructs an instance with a severity filter level \a level. 
     */
    RWTraceLevelFilter(RWTraceEventSeverity level);

    /**
     * Attaches to and increments the reference count on \a bodyP.
     */
    RWTraceLevelFilter(RWTraceLevelFilterImp* bodyP);

    /**
     * Constructs a global static handle instance (that may be used before
     * being constructed).
     */
    RWTraceLevelFilter(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTraceLevelFilter(const RWTraceLevelFilter& second);

    /**
     * Destructor.
     */
    ~RWTraceLevelFilter(void);

    /**
     * Returns the filter's severity level.
     */
    RWTraceEventSeverity getLevel() const;

    /**
     * Sets the severity level for the filter.
     */
    void setLevel(RWTraceEventSeverity level);

};

#endif // __rw_trace_RWTraceLevelFilter_h__
