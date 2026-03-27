#ifndef __rw_http_RWHttpRequestInfo_h__
#define __rw_http_RWHttpRequestInfo_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpRequestInfo.h#1 $
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

class RW_HTTP_SYMBOLIC RWHttpRequestInfo
{
public:
    RWHttpRequestInfo(void);

    void
    setFollowRedirects(bool follow);

    bool
    getFollowRedirects(void) const;

    void
    setMaxWait(unsigned long wait);

    unsigned long
    getMaxWait(void) const;

    void
    setPort(const RWCString& port);

    RWCString
    getPort(void) const;

    void
    setHost(const RWCString& host);

    RWCString
    getHost(void) const;

    void
    setScheme(const RWCString& scheme);

    RWCString
    getScheme(void) const;

private:
    bool redirects_;
    unsigned long maxwait_;
    RWCString port_;
    RWCString host_;
    RWCString scheme_;
};

inline
RWHttpRequestInfo::RWHttpRequestInfo(void)
    : redirects_(true), maxwait_(0)
{
}

inline void
RWHttpRequestInfo::setFollowRedirects(bool follow)
{
    redirects_ = follow;
}

inline bool
RWHttpRequestInfo::getFollowRedirects(void) const
{
    return redirects_;
}

inline void
RWHttpRequestInfo::setMaxWait(unsigned long wait)
{
    maxwait_ = wait;
}

inline unsigned long
RWHttpRequestInfo::getMaxWait(void) const
{
    return maxwait_;
}

inline void
RWHttpRequestInfo::setPort(const RWCString& port)
{
    port_ = port;
}

inline RWCString
RWHttpRequestInfo::getPort(void) const
{
    return port_;
}

inline void
RWHttpRequestInfo::setHost(const RWCString& host)
{
    host_ = host;
}

inline RWCString
RWHttpRequestInfo::getHost(void) const
{
    return host_;
}

inline void
RWHttpRequestInfo::setScheme(const RWCString& scheme)
{
    scheme_ = scheme;
}

inline RWCString
RWHttpRequestInfo::getScheme(void) const
{
    return scheme_;
}

#endif // __rw_http_RWHttpRequestInfo_h__
