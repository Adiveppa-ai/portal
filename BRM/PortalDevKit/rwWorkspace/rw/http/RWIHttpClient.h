#ifndef __rw_http_RWIHttpClient_h__
#define __rw_http_RWIHttpClient_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpClient.h#1 $
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


#if !defined(RW_DISABLE_DEPRECATED)

#  include <rw/http/RWIHttpClientImpl.h>
#  include <rw/http/RWIHttpReply.h>
#  include <rw/http/fwd.h>
#  include <rw/http/pkgdefs.h>
#  include <rw/itc/RWTIOUResult.h>

class RWCString;

#  if defined(_MSC_VER)
#    pragma warning(push)
#    pragma warning(disable : 4251)
#  endif

/*
 * RWIHttpClient
 *
 * RWIHttpClient provides low-level access to the HTTP client-side
 * protocol.  The RWIHttpClient class maintains a finite state
 * machine to enforce correct HTTP protocol action ordering. In the
 * case of mis-ordered method invocation, an RWProtocolClientError
 * exception will be thrown.
 *
 * All client methods return IOUResult's redeemable for the
 * type of RWIHttpReply. RWIHttpReply contains an encapsulation of
 * the standard HTTP protocol reply messages.
 *
 * RWIHttpClient, along with helper RWIHttpMethod and RWHttpHeader
 * classes, provides fine-grained control over HTTP communications.
 *
 * RWIHttpClient object are lightweight. RWIHttpClient is
 * implemented using the interface-implementation pattern. The
 * RWIHttpClient is really a handle to an implementation that
 * performs the protocol interaction.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpClient instead")
    RW_HTTP_SYMBOLIC RWIHttpClient
{

public:

    RWIHttpClient(void);
    // Default Constructor

    RWIHttpClient(const RWIHttpVersion& ver);
    // Constructor that takes version number

    RWIHttpClient(const RWIHttpClient& client);
    // Copy constructor

    RWIHttpClient&
    operator=(const RWIHttpClient& other);
    // Assignment operator

    ~RWIHttpClient(void);
    // Destructor

    void
    setTimeout(unsigned long timeout);
    // set the network timeout in milliseconds

    unsigned long
    getTimeout(void) const;
    // get the network timeout in milliseconds

    RWTIOUResult<bool>
    connect(const RWCString& host, int port = 80);
    // provides a connect method, host is expected to
    // be an IP address or machine domain name

    RWTIOUResult<RWIHttpReply>
    execute(RWIHttpMethod& method);
    // sends method to server and retrieve possible response
    // NOTE:
    // If using HTTP 0.9, be careful that the returned
    // value (an RWIHttpReply object) of the method is invalid,
    // except that you may retrieve data using portal()
    // provided by RWIHttpReply, because there is no response
    // specified in 0.9 version of HTTP.

private:

    RWTNetHandle<RWIHttpClientImpl> impl_;
    // handle to HTTP body

    RWIHttpVersion* version_;
    // http version
};

#  if defined(_MSC_VER)
#    pragma warning(pop)
#  endif

#endif // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpClient_h__
