#ifndef __rw_http_RWIHttpPost_h__
#define __rw_http_RWIHttpPost_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpPost.h#1 $
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

#  include <rw/http/RWIHttpMethod.h>
#  include <rw/http/pkgdefs.h>

/*
 * RWIHttpPost
 *
 * RWIHttpPost provides basic formatting for HTTP POST requests.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpRequest instead")
    RW_HTTP_GLOBAL RWIHttpPost : public RWIHttpMethod
{

public:

    RWIHttpPost(void);
    // default constructor. It constructs an invalid object,
    // use assignment operator to initialize.

    RWIHttpPost(const RWCString& uri);
    // constructor

    void append(const RWCString& str);
    // adds body of post

    void appendLine(const RWCString& str);
    // appends CR/LF

    RWCString headerString(void);
    // adds content-length header and
    // calls RWIHttpMethod::headerString

    RWCString bodyString(void) const;
    // returns contents of body

    RWCString name(void) const;
    // returns the request type (i.e. "POST")

public:

    static const RWCString HTTP_POST;

private:

    RWCString body_;
};

inline
RWIHttpPost::RWIHttpPost(void)
    : RWIHttpMethod("")
{
}

inline
RWIHttpPost::RWIHttpPost(const RWCString& uri)
    : RWIHttpMethod(uri)
{
}

inline void
RWIHttpPost::append(const RWCString& str)
{
    body_.append(str);
}

inline void
RWIHttpPost::appendLine(const RWCString& str)
{
    body_.append(str);
    body_.append("\xD\xA", 2);
}

inline RWCString
RWIHttpPost::bodyString(void) const
{
    return body_;
}

inline RWCString
RWIHttpPost::name(void) const
{
    return HTTP_POST;
}

#endif  // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpPost_h__
