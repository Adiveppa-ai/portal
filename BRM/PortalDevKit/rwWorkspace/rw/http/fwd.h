#ifndef __rw_http_fwd_h__
#define __rw_http_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/fwd.h#1 $
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

#include <rw/http/pkgdefs.h>

class RW_HTTP_SYMBOLIC RWHttpAgent;
class RW_HTTP_GLOBAL RWHttpAuthorizationHeaderBase;
class RW_HTTP_GLOBAL RWHttpBasicAuthorizationHeader;
class RW_HTTP_GLOBAL RWHttpRequestBody;
class RW_HTTP_GLOBAL RWHttpClient;
class RW_HTTP_GLOBAL RWHttpClientImp;
class RW_HTTP_SYMBOLIC RWHttpClientManager;
class RW_HTTP_GLOBAL RWHttpContentLengthHeader;
class RW_HTTP_GLOBAL RWHttpContentTypeHeader;
class RW_HTTP_GLOBAL RWHttpDate;
class RW_HTTP_GLOBAL RWHttpDateHeader;
class RW_HTTP_SYMBOLIC RWHttpEntityTag;
class RW_HTTP_GLOBAL RWHttpEntityTagHeaderBase;
class RW_HTTP_GLOBAL RWHttpFromHeader;
class RW_HTTP_GLOBAL RWHttpGenericHeader;
class RW_HTTP_GLOBAL RWHttpHeaderBase;
class RW_HTTP_SYMBOLIC RWHttpHeaderList;
class RW_HTTP_GLOBAL RWHttpHostHeader;
class RW_HTTP_GLOBAL RWHttpIfDateRangeHeader;
class RW_HTTP_GLOBAL RWHttpIfEntityTagRangeHeader;
class RW_HTTP_GLOBAL RWHttpIfModifiedSinceHeader;
class RW_HTTP_SYMBOLIC RWHttpPortal;
class RW_HTTP_GLOBAL RWHttpPortalImp;
class RW_HTTP_SYMBOLIC RWHttpRange;
class RW_HTTP_GLOBAL RWHttpRangeHeader;
class RW_HTTP_GLOBAL RWHttpReply;
class RW_HTTP_GLOBAL RWHttpRequest;
class RW_HTTP_GLOBAL RWHttpSocketClient;
class RW_HTTP_GLOBAL RWHttpSocketClientImp;
class RW_HTTP_GLOBAL RWHttpRequestStreamBody;
class RW_HTTP_GLOBAL RWHttpRequestStringBody;
class RW_HTTP_GLOBAL RWHttpUserAgentHeader;

class RW_HTTP_SYMBOLIC RWIHttpAgent;
class RW_HTTP_GLOBAL RWIHttpAgentImpl;
class RW_HTTP_SYMBOLIC RWIHttpClient;
class RW_HTTP_SYMBOLIC RWIHttpClientImpl;
class RW_HTTP_GLOBAL RWIHttpReply;
class RW_HTTP_GLOBAL RWIHttpGet;
class RW_HTTP_GLOBAL RWIHttpHead;
class RW_HTTP_GLOBAL RWIHttpMethod;
class RW_HTTP_GLOBAL RWIHttpPost;
class RW_HTTP_GLOBAL RWIHttpVersion;
class RW_HTTP_GLOBAL RWIHttpVersion_0_9;
class RW_HTTP_GLOBAL RWIHttpVersion_1_0;

// Exceptions

class RW_HTTP_GLOBAL RWHttpConnectionError;
class RW_HTTP_GLOBAL RWHttpHandlerError;
class RW_HTTP_GLOBAL RWHttpHeaderParseError;
class RW_HTTP_GLOBAL RWHttpInvalidBodyError;
class RW_HTTP_GLOBAL RWHttpNoPendingRepliesError;
class RW_HTTP_GLOBAL RWHttpRecursiveRedirectError;
class RW_HTTP_GLOBAL RWHttpRequestError;
class RW_HTTP_GLOBAL RWHttpReplyError;


#endif // __rw_http_fwd_h__
