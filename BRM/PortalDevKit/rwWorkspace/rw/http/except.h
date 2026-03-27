#ifndef __rw_http_except_h__
#define __rw_http_except_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/except.h#1 $
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
#include <rw/cstring.h>
#include <rw/rwerr.h>

// Exceptions

/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown when the requested HTTP connection could not be
 * established.
 *
 * An RWHttpConnectionError is thrown when the requested HTTP connection
 * could not be established.
 */
class RW_HTTP_GLOBAL RWHttpConnectionError
    : public RWInternalErr
{
public:
    RWHttpConnectionError(const RWCString& error);
};


/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown when the handler function fails to process the
 * entire body of a message passed to it.
 *
 * An RWHttpHandlerError is thrown when the handler function fails to
 * process the entire body of a message passed to it.
 *
 * \sa
 * RWHttpClient::getReply()
 */
class RW_HTTP_GLOBAL RWHttpHandlerError
    : public RWInternalErr
{
public:
    RWHttpHandlerError(const RWCString& s);
};


/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown when any portion of the HTTP header cannot be
 * parsed due to non-conformance with the HTTP specification.
 *
 * An RWHttpHeaderParseError is thrown when any portion of the HTTP header
 * cannot be parsed due to non-conformance with the HTTP specification.
 */
class RW_HTTP_GLOBAL RWHttpHeaderParseError
    : public RWInternalErr
{
public:
    RWHttpHeaderParseError(const RWCString& s);
};


/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown when an invalid body is associated with a handle
 * or the information provided to the body cannot be processed.
 *
 * An RWHttpInvalidBodyError is thrown when an invalid body is associated
 * with a handle or the information provided to the body cannot be
 * processed.
 *
 * \sa
 * RWHttpRequestStreamBody
 */
class RW_HTTP_GLOBAL RWHttpInvalidBodyError
    : public RWExternalErr
{
public:
    RWHttpInvalidBodyError(const RWCString& s);
};


/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown when a reply is requested but there are no pending
 * RWHttpRequest%s.
 *
 * An RWHttpNoPendingRepliesError is thrown when a reply is requested but
 * there are no pending RWHttpRequest%s.
 *
 * \sa
 * RWHttpClient::getReply()
 */
class RW_HTTP_GLOBAL RWHttpNoPendingRepliesError
    : public RWInternalErr
{
public:
    RWHttpNoPendingRepliesError();
};


/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown if a redirect location is already in the list of
 * visited locations.
 *
 * An RWHttpRecursiveRedirectError is thrown if a redirect location is
 * already in the list of visited locations.
 *
 * \sa
 * RWHttpClientManager::execute(const RWHttpRequest&, const RWHttpRequestInfo&)
 */
class RW_HTTP_GLOBAL RWHttpRecursiveRedirectError
    : public RWInternalErr
{
public:
    RWHttpRecursiveRedirectError(const RWCString& s);
};


/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown if data without a \c Content-Length is sent to a
 * server with version less than HTTP/1.1.
 *
 * An RWHttpRequestError exception is thrown if data without a
 * \c Content-Length is sent to a server with version less than HTTP/1.1.
 */
class RW_HTTP_GLOBAL RWHttpRequestError
    : public RWInternalErr
{
public:
    RWHttpRequestError(const RWCString& s);
};


/**
 * \ingroup http_package
 *
 * \brief
 * Exception class thrown if unexpected data is found in the reply to and
 * HTTP request.
 *
 * An RWHttpReplyError is thrown if unexpected data is found in the reply to
 * and HTTP request.
 */
class RW_HTTP_GLOBAL RWHttpReplyError
    : public RWInternalErr
{
public:
    RWHttpReplyError(const RWCString& s);
};


#endif // __rw_http_except_h__
