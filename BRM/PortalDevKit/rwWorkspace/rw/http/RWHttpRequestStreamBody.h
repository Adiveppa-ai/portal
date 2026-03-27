#ifndef __rw_http_RWHttpRequestStreamBody_h__
#define __rw_http_RWHttpRequestStreamBody_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpRequestStreamBody.h#1 $
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
#include <rw/http/except.h>
#include <rw/http/pkgdefs.h>
#include <istream>

/**
 * \ingroup http_package
 *
 * \brief
 * Encapsulates reading an HTTP message body from an \b std::istream.
 *
 * RWHttpRequestStreamBody defines how to read a streamed message body.
 */
class RW_HTTP_GLOBAL RWHttpRequestStreamBody
    : public RWHttpRequestBody
{
public:
    /**
     * Constructs a default RWHttpRequestStreamBody object.
     */
    RWHttpRequestStreamBody();

    /**
     * Copy constructor.
     */
    RWHttpRequestStreamBody(const RWHttpRequestStreamBody& streamBody);

    /**
     * Constructs an RWHttpRequestStreamBody from a stream, where \a length
     * is the length of the stream. If the length is not set, the stream is
     * invalid.
     */
    RWHttpRequestStreamBody(std::istream* istr, int length = -1);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWHttpRequestStreamBody();

    /**
     * Creates a copy of the RWHttpRequestStreamBody on the heap and returns
     * a pointer to the newly allocated memory.
     */
    virtual RWHttpRequestBody*
    clone() const;

    /**
     * Returns \c true if the pointer to the stream is not null and the
     * associated stream object's \c std::istream::good() returns true.
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
     * Assigns the underlying stream to \a istrm.
     */
    void
    setStream(std::istream* istrm, int length = -1);

    /**
     * Returns the underlying stream.
     */
    std::istream*
    getStream(void) const;

private:

    std::istream* istrm_;
    std::streamsize length_;
    std::streamsize bytesRead_;
};

inline
RWHttpRequestStreamBody::RWHttpRequestStreamBody()
    : istrm_(rwnil),
      length_(-1),
      bytesRead_(0)
{
}

inline
RWHttpRequestStreamBody::RWHttpRequestStreamBody(std::istream* istr, int length)
    : istrm_(istr),
      length_(length),
      bytesRead_(0)
{
}

inline
RWHttpRequestStreamBody::RWHttpRequestStreamBody(const RWHttpRequestStreamBody& streamBody)
    : RWHttpRequestBody(), // explicitly initialize base class
      istrm_(streamBody.istrm_),
      length_(streamBody.length_),
      bytesRead_(0)
{
}

inline void
RWHttpRequestStreamBody::setStream(std::istream* istr, int length)
{
    istrm_ = istr;
    length_ = length;
    bytesRead_ = 0;
}

inline std::istream*
RWHttpRequestStreamBody::getStream() const
{
    // Check and make sure we have a valid pointer, if we don't throw
    if (istrm_ == rwnil) {
        throw RWHttpInvalidBodyError("No stream associated with body");
    }

    return istrm_;
}

#endif // __rw_http_RWHttpRequestStreamBody_h__
