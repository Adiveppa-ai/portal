#ifndef __rw_trace_fwd_h__
#define __rw_trace_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/fwd.h#1 $
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

class RW_TRACE_SYMBOLIC RWTraceEvent;

class RW_TRACE_GLOBAL RWTraceEventClient;
class RW_TRACE_GLOBAL RWTraceEventClientImp;

class RW_TRACE_GLOBAL RWTraceOstreamClient;
class RW_TRACE_GLOBAL RWTraceOstreamClientImp;

class RW_TRACE_GLOBAL RWTraceEventFilter;
class RW_TRACE_GLOBAL RWTraceEventFilterImp;

class RW_TRACE_GLOBAL RWTraceSingleClientFilter;
class RW_TRACE_GLOBAL RWTraceSingleClientFilterImp;

class RW_TRACE_GLOBAL RWTraceLevelFilter;
class RW_TRACE_GLOBAL RWTraceLevelFilterImp;

class RW_TRACE_GLOBAL RWTraceMultiClientFilter;
class RW_TRACE_GLOBAL RWTraceMultiClientFilterImp;

class RW_TRACE_GLOBAL RWTraceManager;
class RW_TRACE_GLOBAL RWTraceManagerImp;

class RW_TRACE_GLOBAL RWTraceInvalidPointer;
class RW_TRACE_GLOBAL RWTraceClientAlreadyConnected;
class RW_TRACE_GLOBAL RWTraceClientNotConnected;
class RW_TRACE_GLOBAL RWTraceClientAlreadyAdded;
class RW_TRACE_GLOBAL RWTraceInvalidClient;

#endif // __rw_trace_fwd_h__
