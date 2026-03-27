#ifndef __rw_http_RWHttpRequestBody_h__
#define __rw_http_RWHttpRequestBody_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpRequestBody.h#1 $
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

/**
 * \ingroup http_package
 *
 * \brief
 * Encapsulates reading an HTTP message body.
 *
 * RWHttpRequestBody is an abstract base class from which the methods for
 * handling message bodies are derived.
 */
class RW_HTTP_GLOBAL RWHttpRequestBody
{

public:
    /**
     * Constructs a default RWHttpRequestBody object.
     */
    RWHttpRequestBody();

    /**
     * Virtual destructor.
     */
    virtual
    ~RWHttpRequestBody();

    /**
     * A virtual function that creates a polymorphic copy of the object on
     * the heap.
     */
    virtual RWHttpRequestBody*
    clone() const = 0;

    /**
     * Returns \c true if the body is valid, and returns \c false otherwise.
     * isValid() is virtual, which means that derived classes can define
     * their own isValid() state.
     */
    virtual bool
    isValid() const = 0;

    /**
     * Reads and returns the next \a size bytes from the body as an
     * RWCString. If \a size bytes are not available, the remainder of the
     * string is returned. Returns an empty string when no data is
     * available.
     */
    virtual RWCString
    getNextChunk(size_t size) = 0;

    /**
     * Returns the total length of the body object, if known. Returns \c -1
     * if the \c Content-Length cannot be determined in the derived class.
     *
     * \note
     * An exception is thrown if data without a \c Content-Length is sent to
     * a server with version less than HTTP/1.1.
     */
    virtual int
    getContentLength() const = 0;
};

inline
RWHttpRequestBody::RWHttpRequestBody()
{
}

#endif // __rw_http_RWHttpRequestBody_h__
