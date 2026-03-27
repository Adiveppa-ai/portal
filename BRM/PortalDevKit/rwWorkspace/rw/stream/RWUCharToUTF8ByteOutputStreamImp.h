#ifndef rw_stream_RWUCharToUTF8ByteOutputStreamImp_h_
#define rw_stream_RWUCharToUTF8ByteOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharToUTF8ByteOutputStreamImp.h#1 $
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
 * Concrete class connecting a UTF-16 character stream to a UTF-8 output
 * binary stream.
 *
 * Concrete class connecting a UTF-16 character stream to a UTF-8 binary
 * stream. The UTF-16 characters are transformed as a sequence of UTF-8
 * bytes. UTF-8 is a variable length encoding of the Unicode Standard using
 * 8-bit sequences, where the high bits indicate which part of the sequence
 * a byte belongs to. Implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWUCharToUTF8ByteOutputStreamImp : public RWUCharOutputStreamImp
{

public:

    /**
     * Constructs an RWUCharToUTF8ByteOutputStreamImp instance that uses
     * \a sink as its sink of bytes, and returns a handle to it. Throws no
     * exceptions.
     *
     * \param sink
     * The binary stream that is used as the sink of bytes.
     */
    static RWUCharOutputStream make(const RWByteOutputStream& sink)
    {
        return RWUCharOutputStream(new RWUCharToUTF8ByteOutputStreamImp(sink));
    }

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWUCharToUTF8ByteOutputStreamImp();

    //-- This function is forwarded to the binary stream used as the sink of bytes.
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
     * Encodes, and writes a single UTF-16 character to the binary stream
     * used as the sink of bytes.
     *
     * \param unicodeValue
     * The UTF-16 character to be encoded.
     */
    virtual void write(RWUChar unicodeValue);

    /**
     * Encodes, and writes an array of UTF-16 characters to the stream used
     * as the sink of bytes.
     *
     * \param unicodeArray
     * A pointer to the first element of the array.
     *
     * \param numUChars
     * The number of UTF-16 characters to be encoded.
     */
    virtual void write(const RWUChar* unicodeArray, RWSize numUChars);

protected:

    /**
     * Initializes the reference to the binary stream that will be used as
     * the sink of bytes.
     *
     * \param sinkStream
     * The binary stream that will serve as the sink of bytes.
     */
    RWUCharToUTF8ByteOutputStreamImp(const RWByteOutputStream& sinkStream);

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
    // used for surrogate encoding
    RWUChar previous_;
    RWByte  res_[4];
    // fail bit
    bool isFail_;

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWUCharToUTF8ByteOutputStreamImp_h_
