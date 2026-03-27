#ifndef __rw_trace_RWTraceOstreamClientImp_h__
#define __rw_trace_RWTraceOstreamClientImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/RWTraceOstreamClientImp.h#1 $
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
 * Implementation (body) for 'RWTraceOstreamClient'.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEventClientImp.h>
#include <rw/trace/pkgdefs.h>
#include <rw/rstream.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * A body class for clients that send all trace events to an
 * \b std::ostream.
 *
 * RWTraceOstreamClientImp is the implementation (body) for
 * RWTraceOstreamClient.
 *
 * \sa
 * RWTraceOstreamClient
 */
class RW_TRACE_GLOBAL RWTraceOstreamClientImp : public RWTraceEventClientImp
{

public:

    /**
     * Destructor.
     */
    ~RWTraceOstreamClientImp(void);

    /**
     * Creates a new RWTraceOstreamClientImp instance that outputs trace
     * events to the specified \b std::ostream. If no \b std::ostream is
     * specified, uses \b std::cerr by default.
     */
    static RWTraceEventClient make(std::ostream& ostr = std::cerr);

protected:
    RW_SUPPRESS_CTOR_ACCESSES_GLOBAL_VAR_WARNING
    /**
     * Constructor that takes an output stream. Default argument sets the
     * output stream to \b std::cerr.
     */
    RWTraceOstreamClientImp(std::ostream& ostr = std::cerr);
    RW_RESTORE_CTOR_ACCESSES_GLOBAL_VAR_WARNING

    /**
     * Sends trace events to the output stream.
     */
    virtual void doTrace(const RWTraceEvent& ev);

    /**
     * Returns the output stream for trace events.
     */
    std::ostream& getOstream() const;

private:

    std::ostream& ostr_;

};

inline std::ostream&
RWTraceOstreamClientImp::getOstream() const
{
    return ostr_;
}

#endif // __rw_trace_RWTraceOstreamClientImp_h__
