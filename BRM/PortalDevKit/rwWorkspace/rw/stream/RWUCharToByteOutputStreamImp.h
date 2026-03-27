#ifndef rw_stream_RWUCharToByteOutputStreamImp_h_
#define rw_stream_RWUCharToByteOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharToByteOutputStreamImp.h#1 $
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

#include <rw/stream/RWByteOutputStream.h>
#include <rw/stream/RWUCharOutputStream.h>
#include <rw/stream/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class connecting a UTF-16 character stream to an output binary
 * stream.
 *
 * Concrete class connecting a Unicode character stream to a binary stream.
 * The UTF-16 characters are written as a sequence of bytes using the byte
 * ordering (little endian, or big endian) supported by the system on which
 * the code is executed. The UTF-16 character \c U+FEFF is inserted in the
 * stream as first character to let input streams figure out the byte
 * ordering used when generating the output byte sequence. Implements the
 * body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWUCharToByteOutputStreamImp : public RWUCharOutputStreamImp
{

public:

    /**
     * Constructs an RWUCharToByteOutputStreamImp instance that uses \a sink
     * as its sink of bytes, and returns a handle to it.
     *
     * \param sink
     * The binary stream that is used as the sink of bytes.
     */
    static RWUCharOutputStream make(const RWByteOutputStream& sink)
    {
        return RWUCharOutputStream(new RWUCharToByteOutputStreamImp(sink));
    }

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWUCharToByteOutputStreamImp();

    /**
     * This function is forwarded to the binary stream used as the sink of
     * bytes.
     */
    virtual void close();

    /**
     * This function is forwarded to the binary stream used as the sink of
     * bytes.
     */
    virtual void flush();

    /**
     * This function is forwarded to the binary stream used as the sink of
     * bytes. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * \copydoc isBad()
     */
    virtual bool isFail() const;

    /**
     * \copydoc isBad()
     */
    virtual bool isGood() const;

    /**
     * Writes a single UTF-16 character to the binary stream used as the
     * sink of bytes.
     *
     * \param unicodeValue
     * The UTF-16 character to be written.
     */
    virtual void write(RWUChar unicodeValue);

    /**
     * Writes an array of UTF-16 characters to the stream used as the sink
     * of bytes.
     *
     * \param unicodeArray
     * A pointer to the first element of the array.
     *
     * \param numUChars
     * The number of UTF-16 characters to be written.
     */
    virtual void write(const RWUChar* unicodeArray, RWSize numUChars);

protected:

    /**
     * Initializes the reference to the binary stream that will be used as
     * the sink of bytes, and writes the stream header (\c U+FEFF).
     *
     * \param sinkStream
     * The binary stream that will serve as the sink of bytes.
     */
    RWUCharToByteOutputStreamImp(const RWByteOutputStream& sinkStream);

    /**
     * Returns a reference to the binary stream that is used as the sink of
     * bytes. Throw no exceptions.
     */
    RWByteOutputStream& getSinkStream()
    {
        return RW_EXPOSE(sinkStream_);
    }

    /**
     * \copydoc getSinkStream()
     */
    const RWByteOutputStream& getSinkStream() const
    {
        return sinkStream_;
    }

private:

    // The binary stream used as the sink of bytes.
    RWByteOutputStream sinkStream_;

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWUCharToByteOutputStreamImp_h_
