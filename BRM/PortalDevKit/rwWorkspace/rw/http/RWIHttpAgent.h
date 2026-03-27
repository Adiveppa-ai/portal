#ifndef __rw_http_RWIHttpAgent_h__
#define __rw_http_RWIHttpAgent_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpAgent.h#1 $
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
RW_SUPPRESS_DEPRECATED_WARNINGS

#  include <rw/http/RWIHttpAgentImpl.h>
#  include <rw/http/pkgdefs.h>
#  include <rw/internet/RWAgent.h>
#  include <rw/network/RWSocketPortal.h>
#  include <rw/itc/RWTIOUResult.h>
#  include <rw/cstring.h>

class RWTime;

/*
 * RWIHttpAgent
 *
 * RWIHttpAgent is an easy-to-use SourcePro Net - Internet
 * Protocols Module class that does basic HTTP access and posting.
 * It handles more of the details of the HTTP protocol than the
 * RWIHttpClient class. However, it doesn't provide the flexibility
 * of the RWIHttpClient class.
 *
 * The constructor stores connection information. The methods
 * perform interaction with the server by connecting, perform-
 * ing the requested action, and disconnecting with the server.
 * Multiple transactions may be performed before an RWIHttpAgent
 * object gets destroyed.
 *
 * An RWIHttpAgent object is lightweight. It is implemented
 * using interface-implementation pattern. The RWIHttpAgent
 * itself is really a handle to an implementation that performs
 * the protocol interaction.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpAgent instead")
    RW_HTTP_SYMBOLIC RWIHttpAgent : public RWAgent
{

public:

    RWIHttpAgent(void);
    // Default constructor, builds an invalid object.  Use the
    // assignment operator to initialize.

    RWIHttpAgent(const RWCString& host, const RWIHttpVersion& ver);
    // Constructs a valid object ready use.  Host is domain name of
    // the http server of interest. Ver specifies which HTTP
    // version to use.

    RWTIOUResult<RWSocketPortal>
    get(const RWCString& httpPath = "/");
    // sends a GET request to the server requesting the object
    // specified in httpPath.  No header information will be
    // sent to the server.

    RWTIOUResult<bool>
    isNewer(const RWCString& httpPath, const RWTime& time);
    // sends a GET request to the server requesting the object
    // specified in httpPath.  An If-Modified-Since header will
    // be attached to the request.  If the object has been modified
    // more recently than the passed in time t then the IOU is populated
    // with a value of true. Otherwise it will be false.

    RWTIOUResult<RWSocketPortal>
    post(const RWCString& httpPath, const RWCString& postData = "");
    // sends a POST request to the server.  The passed-in postData will
    // be attached to the request along with a Content-Length header
    // specifying the size of the body, if postData is not null. The
    // POST request will be given to the object specified in the
    // httpPath.

    void
    setTimeout(unsigned long timeout);
    // set network timeout in milliseconds

    unsigned long
    getTimeout(void) const;
    // get network timeout in milliseconds

private:

    RWIHttpAgentImpl* httpImpl(void) const;
};

RW_RESTORE_DEPRECATED_WARNINGS
#endif  // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpAgent_h__
