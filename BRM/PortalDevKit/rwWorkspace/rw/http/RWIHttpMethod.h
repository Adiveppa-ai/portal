#ifndef __rw_http_RWIHttpMethod_h__
#define __rw_http_RWIHttpMethod_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpMethod.h#1 $
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

#  include <rw/http/RWHttpHeaderBase.h>
#  include <rw/http/pkgdefs.h>
#  include <rw/tvslist.h>

#  if defined(_MSC_VER)
#    pragma warning(push)
#    pragma warning(disable : 4251)
#  endif

/*
 * RWIHttpMethod
 *
 * RWIHttpMethod is an abstract base class used to define HTTP request
 * methods, which are defined by the HTTP protocol specifications. For
 * HTTP 0.9, GET is supported. For HTTP 1.0, GET, HEAD, and POST are
 * supported.
 *
 * RWIHttpMethod accommodates adding header information to the request,
 * and provides methods to construct a full request.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpRequest instead")
    RW_HTTP_GLOBAL RWIHttpMethod
{

public:

    RWIHttpMethod(const RWCString& uri) : uri_(uri)
    {}
    // constructor

    virtual
    ~RWIHttpMethod() { }
    // destructor

    void addHeader(const RWHttpHeaderBase& hdr);
    void addHeader(const RWCString& label, const RWCString& value);
    // adds header information

    void persistConnection(const bool bVal)
    {
        persistConn_ = bVal;
    }
    // may be used by future RWIHttpVersion classes
    // to keep a connection open

    virtual RWCString requestString(void) const;
    // returns request line in the form of
    // "request request-URI"

    virtual RWCString headerString(void);
    // iterates through header list concatenating
    // each header + newline to return string

    virtual RWCString bodyString(void) const;
    // returns contents of body, which is null in the
    // superclass. Subclasses with bodies should
    // override this function

    virtual RWCString name(void) const = 0;
    // returns the request type (e.g. "GET") by
    // a concrete subclass

private:

    RWTValSlist<RWCString>  headerList_;
    bool               persistConn_;
    RWCString               uri_;
};

inline RWCString
RWIHttpMethod::bodyString(void) const
{
    return RWCString();
}

#  if defined(_MSC_VER)
#    pragma warning(pop)
#  endif

#endif // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpMethod_h__
