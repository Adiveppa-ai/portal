#ifndef __rw_trace_RWTraceEventClient_h__
#define __rw_trace_RWTraceEventClient_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceEventClient.h#1 $
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
 * Handle for trace event client implementations.
 *
 *************************************************************************/

#include <rw/trace/except.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A handle class for trace event client implementations.
 *
 * RWTraceEventClient is the handle for trace event client implementations,
 * forwarding messages to its body for processing. A client must be
 * connected to a filter (or the global trace manager) to receive trace
 * messages. The filter calls the trace() method each time a trace event is
 * generated.
 *
 * \sa
 * RWTraceEventFilter, RWTraceEventClientImp
 */
class RW_TRACE_GLOBAL RWTraceEventClient
{

public:

#if !defined(RW_DISABLE_DEPRECATED)
    // This exception class have been deprecated in favor of
    // a RWxmsg derived exception in global scope.

    //--Exception class.
    typedef RWTraceInvalidPointer InvalidPointer;
#endif

    /**
     * Creates an unattached handle.
     */
    RWTraceEventClient();

    /**
     * Attaches to and increments the reference count on \a bodyP.
     */
    RWTraceEventClient(RWTraceEventClientImp* bodyP);

    /**
     * Constructs a global static handle instance (that may be used before
     * being constructed).
     */
    RWTraceEventClient(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTraceEventClient(const RWTraceEventClient& second);

    /**
     * Destructor.
     */
    virtual ~RWTraceEventClient(void);

    /**
     * Detaches from the current body (if any), decrements its reference
     * count, deletes it if there are no other references, and then attaches
     * to the body of \a second and increments its reference count.
     */
    RWTraceEventClient& operator=(const RWTraceEventClient& second);

    /**
     * Detaches from the current body (if any), decrements its reference
     * count, deletes it if there are no other references, and then attaches
     * to the body \a ptr and increments its reference count.
     */
    RWTraceEventClient& operator=(RWTraceEventClientImp* ptr);

    /**
     * Tests that this handle is associated with a body. If not, throws
     * RWTraceInvalidPointer.
     */
    void validate(void) const;

    /**
     * Returns \c true if this handle is connected to a body, otherwise
     * \c false.
     */
    bool isValid(void) const;

    /**
     * Returns \c true if this instance points to the same body as the
     * \a second instance.
     */
    bool operator==(const RWTraceEventClient& second) const;

    /**
     * Returns \c true if this instance points to a body other than the
     * \a second instance.
     */
    bool operator!=(const RWTraceEventClient& second) const;

    /**
     * Detaches from the current body (if any), decrements its reference
     * count, and deletes it if there are no other references.
     */
    void orphan(void);

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
     * Accepts a trace event.
     */
    void trace(const RWTraceEvent& ev);

protected:

    /**
     * Associates this handle with the body pointed to by \a bodyP and
     * increments its reference count.
     *
     * If this handle is already associated with a body, detaches from that
     * body, decrements its reference count, and deletes it if there are no
     * other references.
     */
    void transfer(RWTraceEventClientImp* bodyP = 0);

    /**
     * Returns a pointer to the associated body.
     *
     * If the pointer is not associated with a body, throws
     * RWTraceInvalidPointer.
     */
    RWTraceEventClientImp* getBody(void) const;

private:

    RWTraceEventClientImp* bodyP_;

};


#endif // __rw_trace_RWTraceEventClient_h__
