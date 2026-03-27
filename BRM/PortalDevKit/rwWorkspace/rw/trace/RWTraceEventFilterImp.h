#ifndef __rw_trace_RWTraceEventFilterImp_h__
#define __rw_trace_RWTraceEventFilterImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceEventFilterImp.h#1 $
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
 * Body for trace event filters. Provides interface for adding and removing
 * clients. Derived filters are required to implement this interface.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventClientImp.h>
#include <rw/trace/pkgdefs.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A body class for trace event filter implementations.
 *
 * RWTraceEventFilterImp is the body for trace event filters. This class
 * provides the interface for adding and removing clients. Derived filters
 * are required to implement this interface.
 *
 * \sa
 * RWTraceEventFilter
 */
class RW_TRACE_GLOBAL RWTraceEventFilterImp : public RWTraceEventClientImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWTraceEventFilterImp(void);

    /**
     * Public interface for adding a client. This member forwards the call
     * to the internal protected doAdd() member. This method is called by
     * the client implementation's connect() member.
     */
    void add(RWTraceEventClientImp* clientP);

    /**
     * Public interface for removing a client. This member forwards the call
     * to the internal protected doRemove() member. This method is called by
     * the client implementation's disconnect() member.
     */
    void remove(RWTraceEventClientImp* clientP);

protected:

    /**
     * Default constructor.
     */
    RWTraceEventFilterImp(void);

    /**
     * Attaches a client to the filter. Derived filters must define this
     * method.
     */
    virtual void doAdd(RWTraceEventClientImp* clientP) = 0;

    /**
     * Detaches a client from the filter. Derived filters must define this
     * method.
     */
    virtual void doRemove(RWTraceEventClientImp* clientP) = 0;

};


#endif // __rw_trace_RWTraceEventFilterImp_h__
