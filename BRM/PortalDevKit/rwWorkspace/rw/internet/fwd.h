#ifndef __rw_internet_fwd_h__
#define __rw_internet_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/fwd.h#1 $
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

#include <rw/internet/pkgdefs.h>

class RW_INTERNET_SYMBOLIC RWAgent;
class RW_INTERNET_GLOBAL RWAgentImp;
class RW_INTERNET_SYMBOLIC RWDirEntry;
class RW_INTERNET_GLOBAL RWNumReply;
class RW_INTERNET_GLOBAL RWNumReplyLine;
class RW_INTERNET_GLOBAL RWReply;
class RW_INTERNET_SYMBOLIC RWStreamCoupler;
class RW_INTERNET_SYMBOLIC RWURL;

// Exceptions

class RW_INTERNET_GLOBAL RWProtocolAgentError;
class RW_INTERNET_GLOBAL RWProtocolClientCmdSequenceError;
class RW_INTERNET_GLOBAL RWProtocolClientError;
class RW_INTERNET_GLOBAL RWReplyError;
class RW_INTERNET_GLOBAL RWReplySyntaxError;
class RW_INTERNET_GLOBAL RWURLError;

#endif // __rw_internet_fwd_h__
