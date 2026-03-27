#ifndef rw_stream_RWTStreambufFromByteCharInputStream_h_
#define rw_stream_RWTStreambufFromByteCharInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTStreambufFromByteCharInputStream.h#1 $
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
 ********************************************************************/

#include <rw/stream/RWExternalStreamException.h>
#include <rw/stream/pkgdefs.h>
#include <streambuf>

#ifndef RW_STREAM_STREAMBUF_BUFFER_SIZE
#  define RW_STREAM_STREAMBUF_BUFFER_SIZE 128
#endif

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Adaptor class to adapt the iostreams \b std::streambuf interface to the
 * Rogue Wave binary and narrow character Input Stream interfaces.
 *
 * The class RWTStreambufFromByteCharInputStream is an adaptor class that
 * adapts the iostreams \b std::streambuf interface to the Rogue Wave binary
 * and narrow character Input Stream interfaces. Requests made through the
 * iostreams \b std::streambuf interface are forwarded to the embedded input
 * stream handle. Calls to the iostreams \b std::streambuf functions dealing
 * with the \b std::streambuf's output sequence will always fail since the
 * underlying output stream only supports input operations. The type of the
 * underlying input stream is provided by the template parameter
 * \c InputStream, and can be RWByteInputStream or RWCharInputStream.
 */
template <class InputStream>
class RWTStreambufFromByteCharInputStream : public std::streambuf
{

public:

    /**
     * A typedef for the template parameter \c InputStream which will be
     * used as the source of elements.
     */
    typedef InputStream RWInputStream_type;

    /**
     * A typedef for the type of element to be read from
     * #RWInputStream_type.
     */
    typedef typename InputStream::element_type element_type;
    typedef std::streambuf::int_type int_type;
    typedef std::streambuf::pos_type pos_type;

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of elements.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements.
     */
    RWTStreambufFromByteCharInputStream(const InputStream& sourceStream);

protected:

    /**
     * This function always returns EOF to indicate failure. Throws no
     * exceptions.
     */
    virtual int_type overflow(int_type c = traits_type::eof());

    /**
     * This function returns the first character in the get area if called
     * when there are characters in the get area. If the get area is empty,
     * then the function returns the next character that would be read from
     * the input sequence. Throws no exceptions.
     */
    virtual int_type underflow();

    /**
     * This function always returns zero. Throws no exceptions.
     */
    virtual int sync();

    /**
     * This function always returns 0. Throws no exceptions.
     */
    virtual std::streamsize showmanyc();

    /**
     * This function always returns \c EOF to indicate failure. Throws no
     * exceptions.
     */
    virtual int_type pbackfail(int_type c = traits_type::eof());

    /**
     * This function always returns \c EOF to indicate failure. Throws no
     * exceptions.
     */
    virtual pos_type seekoff(off_type off, std::ios_base::seekdir way,
                             std::ios_base::openmode which =
                                 std::ios_base::in | std::ios_base::out);

    /**
     * This function always returns \c EOF to indicate failure. Throws no
     * exceptions.
     */
    virtual pos_type seekpos(pos_type sp,
                             std::ios_base::openmode which =
                                 std::ios_base::in | std::ios_base::out);

    /**
     * This function always returns \c EOF to indicate failure. Throws no
     * exceptions.
     */
    virtual std::streamsize xsputn(const char_type*, std::streamsize);

protected:

    /**
     * Returns a handle to the embedded \c InputStream that is used as the
     * source of elements. Throw no exceptions.
     */
    InputStream& getSourceStream()
    {
        return RW_EXPOSE(sourceStream_);
    }

    /**
     * \copydoc getSourceStream()
     */
    const InputStream& getSourceStream() const
    {
        return sourceStream_;
    }

private:

    // The input stream used as the source of elements
    InputStream sourceStream_;

    // if unbuffered operation are not supported, then
    // we use a small fixe size internal buffer
    char_type buf_[RW_STREAM_STREAMBUF_BUFFER_SIZE];
};


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/stream/RWTStreambufFromByteCharInputStream.cc>
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWTStreambufFromByteCharInputStream_h_
