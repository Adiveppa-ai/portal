#ifndef __rw_trace_except_h__
#define __rw_trace_except_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/except.h#1 $
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

#include <rw/trace/pkgdefs.h>
#include <rw/rwerr.h>

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * Trace exception thrown when the client is not connected to a valid body.
 *
 * An RWTraceInvalidPointer exception is thrown when the client is not
 * connected to a valid body.
 */
class RW_TRACE_GLOBAL RWTraceInvalidPointer
    : public RWxmsg
{

public:

    RWTraceInvalidPointer();

    RWTraceInvalidPointer(const char* reason);

};

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * Trace exception thrown when an attempt is made to connect to a client
 * that is already connected.
 *
 * An RWTraceClientAlreadyConnected exception is thrown when an attempt is
 * made to connect to a client that is already connected.
 */
class RW_TRACE_GLOBAL RWTraceClientAlreadyConnected
    : public RWxmsg
{

public:

    RWTraceClientAlreadyConnected();

    RWTraceClientAlreadyConnected(const char* reason);

};

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * Trace exception thrown when a trace operation is attempted on a client is
 * not yet connected.
 *
 * An RWTraceClientNotConnected exception is thrown when a trace operation
 * is attempted on a client is not yet connected.
 */
class RW_TRACE_GLOBAL RWTraceClientNotConnected
    : public RWxmsg
{

public:

    RWTraceClientNotConnected();

    RWTraceClientNotConnected(const char* reason);

};

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * Trace exception thrown when an attempt is made to add a client that has
 * already been added.
 *
 * An RWTraceClientAlreadyAdded exception is thrown when an attempt is made
 * to add a client that has already been added.
 */
class RW_TRACE_GLOBAL RWTraceClientAlreadyAdded
    : public RWxmsg
{

public:

    RWTraceClientAlreadyAdded();

    RWTraceClientAlreadyAdded(const char* reason);

};

/**
 * \ingroup execution_tracing_package
 *
 * \brief
 * Trace exception thrown when an operation is attempted on a client that is
 * not valid.
 *
 * An RWTraceInvalidClient exception is thrown when an operation is
 * attempted on a client that is not valid.
 */
class RW_TRACE_GLOBAL RWTraceInvalidClient
    : public RWxmsg
{

public:

    RWTraceInvalidClient();

    RWTraceInvalidClient(const char* reason);

};


#endif // __rw_trace_except_h__
