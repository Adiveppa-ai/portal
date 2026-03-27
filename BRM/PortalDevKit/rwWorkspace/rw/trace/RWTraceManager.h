#ifndef __rw_trace_RWTraceManager_h__
#define __rw_trace_RWTraceManager_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceManager.h#1 $
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
 * Handle for the singleton trace event manager implementation that accepts
 * and forwards trace information to the connected client.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventSeverity.h>
#include <rw/trace/RWTraceLevelFilter.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * The handle to a singleton trace event manager implementation.
 *
 * RWTraceManager is the handle for the singleton trace event manager
 * implementation, which accepts and forwards trace information to the
 * connected client.
 *
 * Attempts to add a client when there is one present already throw an
 * exception.
 *
 * If no client is connected, the manager buffers events. The maximum number
 * of buffered events defaults to 100. If the maximum number of buffered
 * events is reached, the oldest event is removed from the buffer to make
 * room for the newest one.
 *
 * To specify the buffer's size, use the environment variable
 * \c RW_TRACE_BUFFER_SIZE. Once a client is connected, the manager
 * immediately forwards all buffered trace events, and buffering ceases.
 * Buffering resumes when the client is disconnected.
 *
 * To specify the minimum severity level for event generation, use the
 * environment variable \c RW_TRACE_LEVEL. The default severity level is
 * \c INFO. The environment variable can be set to one of the following:
 * \c FATAL, \c ERROR, \c WARNING, \c INFO, \c TEST, \c DEBUG, \c ENTRY, or
 * \c NONE.
 *
 * The singleton trace event manager implementation is reference-counted to
 * ensure that it will not be destroyed while a client is still connected to
 * it.
 */
class RW_TRACE_GLOBAL RWTraceManager : public RWTraceLevelFilter
{

public:

    /**
     * Default constructor. Always returns a handle whose body is the
     * singleton trace event manager implementation.
     */
    RWTraceManager(void);


    // Attaches to and increments the reference count on \a bodyP 's
    // body.
    RWTraceManager(RWTraceManagerImp* bodyP);

    /**
     * Constructs a global static handle instance (that may be used before
     * being constructed).
     */
    RWTraceManager(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTraceManager(const RWTraceManager& second);

    /**
     * Destructor.
     */
    ~RWTraceManager(void);

    /**
     * Static method that returns a handle to the manager. Initialization is
     * performed, if not already completed. This includes setting the
     * maximum buffer size if the environment variable
     * \c RW_TRACE_BUFFER_SIZE has a positive numeric value.
     */
    static RWTraceManager instance(void);

    /**
     * Disconnects the client from the trace manager singleton.
     */
    static void disconnectClient(void);

    // No ref doc.
    int registerSet(const char* set, int (*const superfn)());

#if !defined(RW_DISABLE_DEPRECATED)
    // these methods have been deprecated in favor of the base class
    // getLevel and setLevel methods.

    /**
     * \deprecated
     * As of SourcePro 11.1, use getLevel() instead.
     *
     * Returns the trace manager's runtime severity level.
     */
    RW_DEPRECATE_FUNC("Use RWTraceLevelFilter::getLevel() instead")
    RWTraceEventSeverity getTraceLevel() const;

    /**
     * \deprecated
     * As of SourcePro 11.1, use setLevel() instead.
     *
     * Sets the trace manager's runtime severity level.
     */
    RW_DEPRECATE_FUNC("Use RWTraceLevelFilter::setLevel(RWTraceEventSeverity) instead")
    void setTraceLevel(RWTraceEventSeverity level);
#endif

};


#if !defined(RW_DISABLE_DEPRECATED)
//--Returns the trace manager's runtime severity level.
inline RWTraceEventSeverity
RWTraceManager::getTraceLevel() const
{
    return RWTraceLevelFilter::getLevel();
}

//--Returns the trace manager's runtime severity level.
inline void
RWTraceManager::setTraceLevel(RWTraceEventSeverity level)
{
    RWTraceLevelFilter::setLevel(level);
}
#endif

#endif // __rw_trace_RWTraceManager_h__
