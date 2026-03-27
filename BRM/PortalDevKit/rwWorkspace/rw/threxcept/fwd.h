#ifndef __rw_threxcept_fwd_h__
#define __rw_threxcept_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/threxcept/fwd.h#1 $
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

#include <rw/threxcept/pkgdefs.h>

class RW_THREXCEPT_GLOBAL RWTHRBoundsError;
class RW_THREXCEPT_GLOBAL RWTHRExternalError;
class RW_THREXCEPT_GLOBAL RWTHRIllegalAccess;
class RW_THREXCEPT_GLOBAL RWTHRIllegalUsage;
class RW_THREXCEPT_GLOBAL RWTHRInternalError;
class RW_THREXCEPT_GLOBAL RWTHRInvalidPointer;
class RW_THREXCEPT_GLOBAL RWTHROperationAborted;
class RW_THREXCEPT_GLOBAL RWTHROperationCanceled;
class RW_THREXCEPT_GLOBAL RWTHROperationNotAvailable;
class RW_THREXCEPT_GLOBAL RWTHROperationNotImplemented;
class RW_THREXCEPT_GLOBAL RWTHROperationNotSupported;
class RW_THREXCEPT_GLOBAL RWTHROperationTerminated;
class RW_THREXCEPT_GLOBAL RWTHRPermissionError;
class RW_THREXCEPT_GLOBAL RWTHRResourceLimit;
class RW_THREXCEPT_GLOBAL RWTHRThreadActive;
class RW_THREXCEPT_GLOBAL RWTHRThreadNotActive;
class RW_THREXCEPT_GLOBAL RWTHRxmsg;

template <class Exception> class RWTTHRCompatibleException;

#endif // __rw_threxcept_fwd_h__
