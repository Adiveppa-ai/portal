#ifndef __rw_http_RWIHttpReply_h__
#define __rw_http_RWIHttpReply_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpReply.h#1 $
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

#  include <rw/http/RWHttpGenericHeader.h>
#  include <rw/http/pkgdefs.h>
#  include <rw/internet/RWNumReply.h>
#  include <rw/network/RWSocketPortal.h>
#  include <rw/tvordvec.h>

#  if defined(_MSC_VER)
#    pragma warning(push)
#    pragma warning(disable : 4251)
#  endif

/*
 * RWIHttpReply
 *
 * RWIHttpReply is a specialization class of RWNumReply. It
 * provides additional methods for retrieving returned HTTP
 * header information.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpReply instead")
    RW_HTTP_GLOBAL RWIHttpReply : public RWNumReply
{

public:

    RWIHttpReply(void);
    // default constructor

    RWIHttpReply(const RWIHttpReply& r);
    // copy constructor

    RWIHttpReply& operator=(const RWIHttpReply& rs);
    // assignment operator

    RWIHttpReply(const RWSocketPortal& portal, int majorVerNum);
    // constructs an RWIHttpReply with data from a portal,
    // the reply data will be read until a complete reply
    // is obtained

    RWSocketPortal portal(void) const;
    // returns a copy of the internal portal

    bool containsHeader(const RWCString& label) const;
    // looks up label in header collection and returns
    // whether it exists or not

    RWCString headerValue(const RWCString& label) const;
    // looks up label in header collection and if found
    // returns its corresponding value

    size_t headerEntries(void) const;
    // returns the total number of headers in the
    // returned reply

    RWHttpGenericHeader header(size_t i) const;
    // returns the header found at the passed in index
    // if the index is invalid an exception of type
    // RWBoundsErr will be thrown

    RWCString versionAsString(void) const;
    // returns the HTTP version number passed back
    // by the HTTP server

    void clearAndDestroy(void);
    // clears all headers by calling headerMap_.clear() and the base class
    // clearAndDestroy

private:

    void setPortal(const RWSocketPortal& portal);
    // assigns the internal portal and, if dependent upon the
    // major version number passed in

    virtual void readFromPortal(const RWPortal& portal);
    // reads return code and header info from the portal
    // and morphs it into a more readable form

    RWCString getline(const RWPortal& portal);
    // reads a line of data from the portal

    RWTValOrderedVector<RWHttpGenericHeader>   headerMap_;
    RWCString                                  sVersion_;
    RWSocketPortal                             portal_;

    // friends
    friend class RWHttpFSM;

    friend RW_HTTP_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWIHttpReply& r);
    // outputs an RWIHttpReply to an ostream
};

inline size_t
RWIHttpReply::headerEntries(void) const
{
    return headerMap_.entries();
}

inline RWCString
RWIHttpReply::versionAsString(void) const
{
    return sVersion_;
}

inline RWSocketPortal
RWIHttpReply::portal(void) const
{
    return portal_;
}

#  if defined(_MSC_VER)
#    pragma warning(pop)
#  endif

#endif // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpReply_h__
