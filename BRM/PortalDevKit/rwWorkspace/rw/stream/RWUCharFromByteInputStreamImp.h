#ifndef rw_stream_RWUCharFromByteInputStreamImp_h_
#define rw_stream_RWUCharFromByteInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharFromByteInputStreamImp.h#1 $
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

#include <rw/stream/RWByteInputStream.h>
#include <rw/stream/RWUCharInputStream.h>
#include <rw/stream/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class connecting a UTF-16 character stream to an input binary
 * stream.
 *
 * Concrete class connecting a UTF-16 character stream to a binary stream.
 * The UTF-16 characters are read as a sequence of bytes using the byte
 * ordering (little endian or big endian) specified by the stream header.
 * The stream header consists of the UTF-16 character \c U+FEFF that is
 * inserted in the stream when generating the output byte sequence.
 * Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWUCharFromByteInputStreamImp : public RWUCharInputStreamImp
{

public:

    /**
     * Constructs an RWUCharFromByteInputStreamImp instance that uses
     * \a source as the source of bytes, and returns a handle to it.
     *
     * \param source
     * The binary stream that is used as the source of bytes.
     */
    static RWUCharInputStream make(const RWByteInputStream& source)
    {
        return RWUCharInputStream(new RWUCharFromByteInputStreamImp(source));
    }


    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWUCharFromByteInputStreamImp();

    /**
     * This function is forwarded to the binary stream used as the source of
     * bytes. Throws no exceptions.
     */
    virtual void close();

    /**
     * This function forwarded to the binary stream used as the source of
     * bytes. Throws no exceptions.
     */
    virtual bool isEof() const;

    /**
     * \copydoc isEof()
     */
    virtual bool isBad() const;

    /**
     * \copydoc isEof()
     */
    virtual bool isFail() const;

    /**
     * \copydoc isEof()
     */
    virtual bool isGood() const;

    /**
     * \copydoc isEof()
     */
    virtual RWUChar read();

    /**
     * Reads an array of UTF-16 characters from the stream used as the
     * source of bytes. The array must be pre-allocated to contain at least
     * \a numUChars elements. The function returns the actual number of
     * UTF-16 characters extracted from the stream.
     *
     * \param unicodeArray
     * A pointer to the first element of the array.
     *
     * \param numUChars
     * The number of UTF-16 characters to be read from the stream.
     */
    virtual RWSize read(RWUChar* unicodeArray, RWSize numUChars);

    /**
     * Reads UTF-16 characters from the stream used as the source of bytes
     * until the last UTF-16 character read is equal to \a delim, or
     * \a maxSize UTF-16 characters have been read, or the end of the input
     * sequence is reached. The UTF-16 characters read are stored in
     * \a unicodeArray. The function returns the actual number of UTF-16
     * characters inserted into \a unicodeArray. If the last UTF-16
     * character extracted is equal to \a delim, then it is not stored in
     * \a unicodeArray.
     *
     * \param unicodeArray
     * A pointer to the array receiving the UTF-16 characters extracted from
     * the stream.
     *
     * \param maxSize
     * The maximum number of UTF-16 characters to be read.
     *
     * \param delim
     * The UTF-16 character used as a delimiter.
     */
    virtual RWSize readUntil(RWUChar* unicodeArray, RWSize maxSize, RWUChar delim);

    /**
     * Returns the number of UTF-16 characters that can be read from the
     * stream used as the source of bytes without blocking.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits UTF-16 characters from the input sequence if
     * possible. The function returns the actual number of UTF-16 characters
     * skipped, which can be any value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of UTF-16 characters to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

protected:

    /**
     * Initializes the reference to the stream that will be used as the
     * source of bytes.
     *
     * \param sourceStream
     * The binary stream that will serve as the source of bytes.
     */
    RWUCharFromByteInputStreamImp(const RWByteInputStream& sourceStream);

    /**
     * Returns a reference to the stream used as the source of bytes. They
     * throw no exceptions.
     */
    RWByteInputStream& getSourceStream()
    {
        return RW_EXPOSE(sourceStream_);
    }

    /**
     * \copydoc getSourceStream()
     */
    const RWByteInputStream& getSourceStream() const
    {
        return sourceStream_;
    }

private:

    /**
     * Reads a single UTF-16 character from the stream used as the source of
     * bytes.
     *
     * \param uc
     * A reference to a UTF-16 character that will be updated if the
     * function succeeds.
     */
    void getUChar(RWUChar& uc);

    /**
     * Reads an array of \a max UTF-16 characters from the stream used as
     * the source of bytes. The function returns the actual number of UTF-16
     * characters read.
     *
     * \param ucAr
     * A pre-allocated array.
     *
     * \param max
     * The number of UTF-16 characters to be read.
     */
    RWSize getUChars(RWUChar* ucAr, RWSize max)
    {
        return static_cast<RWSize>(this->getSourceStream().read(reinterpret_cast<RWByte*>(ucAr), static_cast<RWSize>(sizeof(RWUChar) * max)) / sizeof(RWUChar));
    }

    /**
     * Swap the \c Hi and \c Lo bytes of a single UTF-16 character. Throws
     * no exceptions.
     *
     * \param uc
     * A reference to a UTF-16 character that will have its bytes swapped.
     */
    static void swap2Bytes(RWUChar& uc)
    {
        uc = RWUChar((uc << 8) | (uc >> 8));
    }

    /**
     * Swap the \c Hi and \c Lo bytes of an array of UTF-16 characters.
     * Throws no exceptions.
     *
     * \param ucAr
     * The UTF-16 character's array address.
     *
     * \param n
     * The number of UTF-16 characters to be processed.
     */
    static void swapnBytes(RWUChar* ucAr, RWSize n);

    // The stream used as the source of bytes.
    RWByteInputStream sourceStream_;

    bool isFail_;
    bool swap_;

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWUCharFromByteInputStreamImp_h_
