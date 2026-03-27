#ifndef __rw_http_RWIHttpAgentImpl_h__
#define __rw_http_RWIHttpAgentImpl_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpAgentImpl.h#1 $
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

#  include <rw/http/RWIHttpClient.h>
#  include <rw/http/pkgdefs.h>
#  include <rw/internet/RWAgentImp.h>
#  include <rw/itc/RWTIOUEscrow.h>

#  define HTTPAI_HTTPPATH_KEY "HttpPath"
#  define HTTPAI_HTTPDATE_KEY "HttpDate"
#  define HTTPAI_POSTDATA_KEY "PostData"
#  define HTTPAI_VERSION_KEY  "Version"

/*
 * RWIHttpAgentImpl
 *
 * RWIHttpAgentImpl is an implementation class of its interface counterpart
 * RWIHttpAgent. The main functionality of RWIHttpAgentImpl is to handle
 * all HTTP agent commands dispatched from RWIHttpAgent.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpAgent instead")
    RW_HTTP_GLOBAL RWIHttpAgentImpl : public RWAgentImp
{

public:

    RWIHttpAgentImpl(int version = 1);
    // Default constructor, set to HTTP 1.0

    virtual ~RWIHttpAgentImpl(void);
    // Destructor

    void
    get(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // performs a get transaction that connects to
    // the server, sends GET information, and opens
    // a data connection to the resulting http object.

    void
    getIfNewer(RWTIOUEscrow<bool> iouEscrow);
    // performs a get transaction that connects to the
    // server, sends GET information, along with an
    // If-Modified-Since header.  If a "not modified"
    // message is return then the escrow is set to false.
    // Otherwise, it is set to true.

    void
    post(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // performs a post transaction that connects to the
    // server, sends POST information, and opens a data
    // connection to the resulting http object.

    virtual void
    setProperty(const RWCString& p, const RWCString& v);
    // Sets property

    void
    setHost(const RWCString& host);

    void
    setTimeout(unsigned long timeout);
    // set network timeout

    unsigned long
    getTimeout(void) const;
    // get network timeout

private: // member functions

    void
    connect(void);
    // connects to HTTP server.

private: // data members

    RWIHttpClient httpClient_;
    // http client class.

    RWCString host_;
    // ip address of http server

    RWMutex threadMutex_;
    // exclusive thread access control.
};

#endif  // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpAgentImpl_h__
