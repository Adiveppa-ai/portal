#ifndef __rw_trace_RWTraceEventClientImp_h__
#define __rw_trace_RWTraceEventClientImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceEventClientImp.h#1 $
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
 * Body for trace event clients. Provides interface for clients.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventFilter.h>
#include <rw/trace/except.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>
#include <rw/mutex.h>
#include <rw/ref.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A body class for trace event client implementations.
 *
 * RWTraceEventClientImp is a body class that provides an interface for
 * trace event clients. Derived clients are required to implement this
 * interface.
 *
 * \sa
 * RWTraceEventClient, RWTraceEventFilter, RWTraceManager
 */
class RW_TRACE_GLOBAL RWTraceEventClientImp : public RWReference
{

public:

    /**
     * Destructor.
     */
    virtual ~RWTraceEventClientImp(void);

    /**
     * Connects the client with the global singleton trace event manager.
     * The manager allows a single client connection at a time.
     *
     * If the client is already connected, throws the exception
     * RWTraceClientAlreadyConnected. If the manager already has a client
     * connected, throws the exception RWTraceClientAlreadyAdded.
     */
    void connectToManager(void);

    /**
     * Connects the client with the \a filter.
     *
     * If the client is already connected, throws the exception
     * RWTraceClientAlreadyConnected.
     */
    void connect(RWTraceEventFilter& filter);

    /**
     * Disconnects the client from the filter it is currently attached to.
     *
     * If the client is not connected, throws the exception
     * RWTraceClientNotConnected.
     */
    void disconnect(void);

    /**
     * Forwards trace information to the doTrace() member.
     */
    void trace(const RWTraceEvent& ev);

#if !defined(RW_DISABLE_DEPRECATED)
    // These exception classes have been deprecated in favor of
    // RWxmsg derived exceptions which are in global scope.

    //--Exception class.
    typedef RWTraceClientAlreadyConnected TraceClientAlreadyConnected;

    //--Exception class.
    typedef RWTraceClientNotConnected TraceClientNotConnected;
#endif

    /**
     * Increments the reference count.
     */
    void addReference(void);

    /**
     * Decrements the reference count.
     */
    unsigned removeReference(void);

protected:

    /**
     * Default constructor.
     */
    RWTraceEventClientImp(void);

    /**
     * Processes a trace event. This method must be overridden by derived
     * clients to provide a way to handle the trace event, perhaps by
     * printing it to standard output or storing it in a file. See the
     * discussion on the <b><em>TraceEventClient</em></b> in the <em>Threads
     * Module User's Guide</em>.
     */
    virtual void doTrace(const RWTraceEvent& ev) = 0;

    /**
     * Returns the mutex used for thread safety. The mutex can be used by
     * derived clients.
     */
    RWMutex& getMutex(void);

private:

    RWTraceEventFilter filter_;

    RWMutex mutex_;
};

inline RWMutex&
RWTraceEventClientImp::getMutex(void)
{
    return RW_EXPOSE(mutex_);
}

inline void
RWTraceEventClientImp::addReference(void)
{
    RWReference::addReference();
}

inline unsigned
RWTraceEventClientImp::removeReference(void)
{
    return unsigned(RWReference::removeReference());
}

#endif // __rw_trace_RWTraceEventClientImp_h__
