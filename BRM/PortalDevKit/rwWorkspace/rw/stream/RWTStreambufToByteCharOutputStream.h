#ifndef rw_stream_RWTStreambufToByteCharOutputStream_h_
#define rw_stream_RWTStreambufToByteCharOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTStreambufToByteCharOutputStream.h#1 $
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

#include <rw/stream/RWIncompleteStreamOperation.h>
#include <rw/stream/pkgdefs.h>
#include <streambuf>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Adaptor class to adapt the iostreams \b std::streambuf interface to the
 * Rogue Wave binary and narrow character Output Stream interfaces.
 *
 * The class RWTStreambufToByteCharOutputStream is an adaptor class that
 * adapts the iostreams \b std::streambuf interface to the Rogue Wave binary
 * and narrow character Output Stream interfaces. Requests made through the
 * iostreams \b std::streambuf interface are forwarded to the embedded
 * output stream handle. Calls to the iostreams \b std::streambuf functions
 * dealing with the \b std::streambuf's input sequence will always fail
 * since the underlying output stream only supports output operations. The
 * type of the underlying output stream is provided by the template
 * parameter \c OutputStream, and can be RWByteOutputStream or
 * RWCharOutputStream.
 */
template <class OutputStream>
class RWTStreambufToByteCharOutputStream : public std::streambuf
{

public:

    /**
     * A typedef for the template parameter \c OutputStream which will be
     * used as the sink for elements.
     */
    typedef OutputStream RWOutputStream_type;

    /**
     * A typedef for the type of element to be written to
     * #RWOutputStream_type.
     */
    typedef typename OutputStream::element_type element_type;
    typedef std::streambuf::int_type int_type;
    typedef std::streambuf::pos_type pos_type;

    /**
     * Initializes the reference to the output stream that will be used as
     * the sink of elements.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     */
    RWTStreambufToByteCharOutputStream(const OutputStream& sinkStream);

protected:

    /**
     * Consumes the bytes in the put area, by inserting them in the embedded
     * output stream. If \a c is not \c EOF, it is either consumed or placed
     * in the newly established put area. This function is normally called
     * when the put area is full, but may be called at other times to force
     * the consumption of the bytes in the put area. If an error occurs,
     * overflow() returns \c EOF, otherwise it returns a value other than
     * \c EOF. Throws no exceptions.
     *
     * \param c
     * \c EOF to force consumption of the bytes in the put area, or any
     * other 8 bits value that need to be inserted in the put area.
     */
    virtual int_type overflow(int_type c = traits_type::eof());

    /**
     * This function always returns \c EOF to indicate failure. Throws no
     * exceptions.
     */
    virtual int_type underflow();

    /**
     * This function always returns \c EOF to indicate failure. Throws no
     * exceptions.
     */
    virtual int_type pbackfail(int_type c = traits_type::eof());

    /**
     * This function synchronizes the controlled output sequence with the
     * array. That is, if \b std::streambuf::pbase() is non-null the
     * characters between \b std::streambuf::pbase() and
     * \b std::streambuf::pptr() are written to the controlled output
     * sequence. The pointers may then be reset as appropriate. The function
     * returns \c EOF in case of error; otherwise it returns zero. Throws no
     * exceptions.
     */
    virtual int sync();

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
    virtual std::streamsize xsgetn(char_type*, std::streamsize);

    /**
     * This function stores \a n characters (bytes) pointed to by \a s after
     * the put pointer, and increments the put pointer by \a n. If the
     * function rwUnbuffered() returns \c true, then the characters (bytes)
     * are directly forwarded to the embedded output stream. Throws no
     * exceptions.
     *
     * \param s
     * A pointer to the first element of the character (byte) array.
     *
     * \param n
     * The number of elements to be written.
     */
    virtual std::streamsize xsputn(const char_type* s,
                                   std::streamsize n);

protected:

    /**
     * Returns a handle to the embedded Output Stream that is used as the
     * sink of elements. Throws no exceptions.
     */
    OutputStream& getSinkStream()
    {
        return RW_EXPOSE(sinkStream_);
    }

    /**
     * \copydoc getSinkStream()
     */
    const OutputStream& getSinkStream() const
    {
        return sinkStream_;
    }

private:

    // The output stream used as the sink of elements
    OutputStream sinkStream_;

};


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/stream/RWTStreambufToByteCharOutputStream.cc>
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWTStreambufToByteCharOutputStream_h_
