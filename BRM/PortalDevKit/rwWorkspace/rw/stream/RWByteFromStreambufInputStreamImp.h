#ifndef rw_stream_RWByteFromStreambufInputStreamImp_h_
#define rw_stream_RWByteFromStreambufInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWByteFromStreambufInputStreamImp.h#1 $
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
#include <rw/stream/pkgdefs.h>
#include <streambuf>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class that connects a binary stream to an iostreams narrow
 * character buffer.
 *
 * Concrete class connecting a binary stream to an iostreams narrow
 * character buffer. The iostreams buffer is used as the source for the data
 * read from the binary stream. The iostreams buffer must be opened in
 * binary mode. Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWByteFromStreambufInputStreamImp : public RWByteInputStreamImp
{

public:

    typedef std::streambuf::char_type char_type;

    /**
     * Constructs an RWByteFromStreambufInputStreamImp instance that uses
     * \a source as the source of bytes, and returns a handle to it. Throws
     * no exceptions.
     *
     * \param source
     * The iostreams \c std::streambuf that is used as the source of bytes.
     */
    static RWByteInputStream make(std::streambuf& source)
    {
        return RWByteInputStream(new RWByteFromStreambufInputStreamImp(source));
    }

    /**
     * Destructor.
     */
    virtual ~RWByteFromStreambufInputStreamImp();

    /**
     * This function does nothing. The user is responsible for closing the
     * iostreams \c std::streambuf, used as the source of bytes, if
     * necessary.
     */
    virtual void close();

    /**
     * Returns \c true if there is no bytes available from the iostreams
     * \c std::streambuf, used as the source of bytes.
     */
    virtual bool isEof() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \c std::streambuf failed.
     */
    virtual bool isBad() const;

    /**
     * \copydoc isBad()
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \c std::streambuf succeeded.
     */
    virtual bool isGood() const;

    /**
     * Reads a single byte from the iostreams \c std::streambuf, used as the
     * source of bytes.
     *
     * \exception RWExternalStreamException
     * Thrown when the call to the internal iostreams \c std::streambuf
     * object fails or any propagated exceptions from that call occur.
     */
    virtual RWByte read();

    /**
     * Reads an array of bytes from the iostreams \c std::streambuf, used as
     * the source of bytes. The array must be pre-allocated to contain at
     * least \a numBytes elements. The function returns the actual number of
     * bytes extracted from the iostreams \c std::streambuf.
     *
     * \exception RWExternalStreamException
     * Thrown when the call to the internal iostreams \c std::streambuf
     * object fails or any propagated exceptions from that call occur.
     *
     * \param byteArray
     * Pointer to the first element of the array.
     *
     * \param numBytes
     * Number of bytes to be read from the stream.
     */
    virtual RWSize read(RWByte* byteArray, RWSize numBytes);

    /**
     * Reads bytes from the iostreams \c std::streambuf, used as the source
     * of bytes, until the last byte read is equal to \a delim, or
     * \a maxSize bytes have been read, or the end of the input sequence is
     * reached. The bytes read are stored in \a byteArray. The function
     * returns the actual number of bytes inserted into \a byteArray. If the
     * last byte extracted is equal to \a delim, then it is not stored in
     * \a byteArray.
     *
     * \param byteArray
     * Pointer to the array receiving the bytes extracted from the iostreams
     * \c std::streambuf.
     *
     * \param maxSize
     * Maximum number of bytes to be read.
     *
     * \param delim
     * Byte value used as a delimiter.
     */
    virtual RWSize readUntil(RWByte* byteArray, RWSize maxSize, RWByte delim);

    /**
     * Returns the number of bytes that can be read from the iostreams
     * \c std::streambuf (used as the source of bytes), without blocking.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits bytes from the input sequence if possible. The
     * function returns the actual number of bytes skipped, which can be any
     * value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of bytes to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

protected:

    /**
     * Initializes the reference to the iostreams \c std::streambuf, that
     * will be used as the source of bytes. Throws no exceptions.
     *
     * \param sourceBuff
     * The iostreams \c std::streambuf that will serve as the source of
     * bytes.
     */
    RWByteFromStreambufInputStreamImp(std::streambuf& sourceBuff)
        : RWByteInputStreamImp()
        , sourceBuff_(sourceBuff)
        , isFail_(false)
    {
        ;
    }

    /**
     * Returns a reference to the iostreams \c std::streambuf, which is used
     * as the source of bytes.
     */
    std::streambuf& getSourceBuff()
    {
        return sourceBuff_;
    }

    /**
     * Returns a const reference to the iostreams \c std::streambuf, which
     * is used as the source of bytes.
     */
    const std::streambuf& getSourceBuff() const
    {
        return sourceBuff_;
    }

private:

    // A reference to the iostreams 'streambuf' is that is used as the source of bytes.
    std::streambuf& sourceBuff_;

    bool isFail_;

};

#endif // rw_stream_RWByteFromStreambufInputStreamImp_h_
