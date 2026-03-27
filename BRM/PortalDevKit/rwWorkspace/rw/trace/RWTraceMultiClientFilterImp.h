#ifndef __rw_trace_RWTraceMultiClientFilterImp_h__
#define __rw_trace_RWTraceMultiClientFilterImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceMultiClientFilterImp.h#1 $
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
 * Filter implementation that accepts multiple clients and forwards trace
 * events to them. Objects of this class should be instantiated through the
 * corresponding handle class 'RWTraceMultiClientFilter'.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventFilterImp.h>
#include <rw/trace/pkgdefs.h>
#include <rw/tvordvec.h> //for RWTValOrderedVector, used for table of clients

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A body class for trace event filters that accept multiple clients.
 *
 * RWTraceMultiClientFilterImp is a filter implementation that accepts
 * multiple clients to which it forwards trace events. Objects of this class
 * should be instantiated through the corresponding handle class
 * RWTraceMultiClientFilter.
 *
 * \sa
 * RWTraceMultiClientFilter
 */
class RW_TRACE_GLOBAL RWTraceMultiClientFilterImp : public RWTraceEventFilterImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWTraceMultiClientFilterImp(void);

    /**
     * Creates a new RWTraceMultiClientFilterImp instance.
     */
    static RWTraceEventFilter make(void);

protected:

    /**
     * Default constructor.
     */
    RWTraceMultiClientFilterImp(void);

    /**
     * Attaches a client to the filter.
     */
    virtual void doAdd(RWTraceEventClientImp* clientP);

    /**
     * Detaches the specified client.
     */
    virtual void doRemove(RWTraceEventClientImp* clientP);

    /**
     * Forwards the trace events to all attached clients.
     */
    virtual void doTrace(const RWTraceEvent& ev);

    // Not thread-safe
    /**
     * Returns a vector containing pointers to the attached clients.
     */
    RWTValOrderedVector<RWTraceEventClientImp*> getClients(void);

    //--Returns a vector of handles to attached clients. thread-safe
    RWTValOrderedVector<RWTraceEventClient> _getClients(void);

protected:

    RWTValOrderedVector<RWTraceEventClientImp*> clientPs_;

};


inline
RWTValOrderedVector<RWTraceEventClientImp*>
RWTraceMultiClientFilterImp::getClients(void)
{
    return clientPs_;
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_trace_RWTraceMultiClientFilterImp_h__
