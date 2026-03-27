#ifndef __rw_http_RWHttpRequestStringBody_h__
#define __rw_http_RWHttpRequestStringBody_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpRequestStringBody.h#1 $
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

#include <rw/http/RWHttpRequestBody.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Encapsulates reading an HTTP message body from an RWCString.
 *
 * RWHttpRequestStringBody defines how to read a standard message body.
 */
class RW_HTTP_GLOBAL RWHttpRequestStringBody
    : public RWHttpRequestBody
{
public:
    /**
     * Constructs a default RWHttpRequestStringBody object.
     */
    RWHttpRequestStringBody();

    /**
     * Copy constructor.
     */
    RWHttpRequestStringBody(const RWHttpRequestStringBody& body);

    /**
     * Constructs an RWHttpRequestStringBody from a string.
     */
    RWHttpRequestStringBody(const RWCString& body);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWHttpRequestStringBody();

    /**
     * Creates a copy of the RWHttpRequestStringBody on the heap and returns
     * a pointer to the newly allocated memory.
     */
    virtual RWHttpRequestBody*
    clone() const;

    /**
     * Always returns \c true for this derived class.
     */
    virtual bool
    isValid() const;

    /**
     * Reads and returns the next \a size bytes from the body as an
     * RWCString. If \a size bytes are not available, the remainder of the
     * string is returned. Returns an empty string when no more data can be
     * read.
     */
    virtual RWCString
    getNextChunk(size_t size);

    /**
     * Returns the total length of the body object, if known. Returns \c -1
     * if the \c Content-Length cannot be determined.
     *
     * \note
     * An RWHttpRequestError exception is thrown if data without a
     * \c Content-Length is sent to a server with version less than
     * HTTP/1.1.
     */
    virtual int
    getContentLength() const;

    /**
     * Returns the internal body representation as an RWCString.
     */
    RWCString
    getString() const;

    /**
     * Stores the RWCString \a str as the internal body of the object.
     */
    void
    setString(const RWCString& str);

private:

    RWCString body_;
    size_t    index_;
};

inline
RWHttpRequestStringBody::RWHttpRequestStringBody()
    : index_(0)
{
}

inline
RWHttpRequestStringBody::RWHttpRequestStringBody(const RWCString& body)
    : body_(body),
      index_(0)
{
}

inline
RWHttpRequestStringBody::RWHttpRequestStringBody(const RWHttpRequestStringBody& strBody)
    : RWHttpRequestBody(), // explicitly initialize base class
      body_(strBody.body_),
      index_(0)
{
}

inline RWCString
RWHttpRequestStringBody::getString() const
{
    return body_;
}

inline void
RWHttpRequestStringBody::setString(const RWCString& str)
{
    body_ = str;
}

#endif // __rw_http_RWHttpRequestStringBody_h__
