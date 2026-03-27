#ifndef __rw_trace_RWTraceSingleClientFilterImp_h__
#define __rw_trace_RWTraceSingleClientFilterImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceSingleClientFilterImp.h#1 $
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
 * Filter implementation that accepts one client and forwards trace events
 * to it. This class is intended to be the base class for filters that
 * accept one client. It is not meant to be instantiated as it provides no
 * functionality. If one attempts to add a client and the filter already
 * has one, a 'TraceClientAlreadyAdded exception' is thrown.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventFilterImp.h>
#include <rw/trace/except.h>
#include <rw/trace/fwd.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A body class for a trace level filter that accepts only one client.
 *
 * RWTraceSingleClientFilterImp is a filter implementation that accepts one
 * client to which it forwards trace events. This class is intended to be
 * the base class for filters that accept one client and is not intended to
 * be directly instantiated.
 *
 * Attempting to add a client if the filter already has one throws an
 * RWTraceClientAlreadyAdded exception.
 *
 * \sa
 * RWTraceSingleClientFilter, RWTraceMultiClientFilterImp
 */
class RW_TRACE_GLOBAL RWTraceSingleClientFilterImp : public RWTraceEventFilterImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWTraceSingleClientFilterImp(void);

    /**
     * Creates a new RWTraceSingleClientFilterImp instance.
     */
    static RWTraceSingleClientFilter make(void);

    /**
     * Disconnects the attached client.
     */
    void disconnectClient(void);

#if !defined(RW_DISABLE_DEPRECATED)
    // These exception classes have been deprecated in favor of
    // a RWxmsg derived exceptions in global scope.

    //--Exception class.
    typedef RWTraceClientAlreadyAdded TraceClientAlreadyAdded;

    //--Exception class.
    typedef RWTraceInvalidClient InvalidTraceClient;

#endif

protected:

    /**
     * Default constructor.
     */
    RWTraceSingleClientFilterImp(void);

    /**
     * Attaches a client to the filter. Throws an exception if there already
     * is a client.
     */
    virtual void doAdd(RWTraceEventClientImp* clientP);

    /**
     * Detaches the client.
     */
    virtual void doRemove(RWTraceEventClientImp* clientP);

    /**
     * Forwards the trace event to the attached client.
     */
    virtual void doTrace(const RWTraceEvent& ev);

    /**
     * Disconnects the attached client.
     */
    virtual void doDisconnectClient();

    // Not thread-safe
    /**
     * Returns a pointer to the attached client.
     */
    RWTraceEventClientImp* getClient();

    //--Returns a handle to the attached client. thread-safe
    RWTraceEventClient _getClient();

protected:

    RWTraceEventClientImp* clientP_;

};


inline RWTraceEventClientImp*
RWTraceSingleClientFilterImp::getClient()
{
    return clientP_;
}

inline RWTraceEventClient
RWTraceSingleClientFilterImp::_getClient()
{
    RWGUARD(getMutex());

    return clientP_;
}

#endif // __rw_trace_RWTraceSingleClientFilterImp_h__
