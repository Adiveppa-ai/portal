#ifndef rw_stream_RWFilteredByteInputStreamImp_h_
#define rw_stream_RWFilteredByteInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWFilteredByteInputStreamImp.h#1 $
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

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the filtered binary input stream
 * implementation classes.
 *
 * Abstract base class for all the filtered binary input stream
 * implementation classes. A filtered input stream is a stream that uses its
 * attached input stream as the source of elements to its own functions.
 * Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWFilteredByteInputStreamImp
    : public RWByteInputStreamImp
{

public:
    /**
     * Destructor. Throws no exceptions.
     */
    virtual ~RWFilteredByteInputStreamImp();

    /**
     * Forwards the close() request to the attached source stream.
     */
    virtual void close();

    /**
     * Forwards the isBad() request to the attached source stream. Throws no
     * exceptions.
     */
    virtual bool isBad() const;

    /**
     * Forwards the isFail() request to the attached source stream. Throws
     * no exceptions.
     */
    virtual bool isFail() const;

    /**
     * Forwards the isEof() request to the attached source stream. Throws no
     * exceptions.
     */
    virtual bool isEof() const;

    /**
     * Forwards the isGood() request to the attached source stream. Throws
     * no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Forwards the reading of a single byte to the attached source stream.
     */
    virtual RWByte read();

    /**
     * Forwards the reading of an array of bytes from the attached source
     * stream. The function returns the actual number of bytes read.
     *
     * \param byteArray
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least \a numBytes elements.
     *
     * \param numBytes
     * The number of byte(s) to be read from the stream.
     */
    virtual RWSize read(RWByte* byteArray, RWSize numBytes);

    /**
     * Reads bytes from the attached source stream until the last byte read
     * is equal to \a delim, or \a maxSize bytes have been read, or the end
     * of the input sequence is reached. The bytes read are stored in
     * \a byteArray. The function returns the actual number of bytes read
     * from the stream.
     *
     * \param byteArray
     * A pointer to the array receiving the byte(s) extracted from the
     * stream.
     *
     * \param maxSize
     * The maximum number of byte(s) to be read.
     *
     * \param delim
     * The byte value used as a delimiter.
     */
    virtual RWSize readUntil(RWByte* byteArray, RWSize maxSize, RWByte delim);

    /**
     * Returns the number of bytes that can be read from the attached source
     * stream without blocking. Throws no exceptions.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits bytes from the input sequence of the attached
     * source stream if possible. The function returns the actual number of
     * bytes skipped, which can be any value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of byte(s) to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

protected:

    /**
     * Used by derived classes to initialize the attached source stream.
     * Throws no exceptions.
     *
     * \param sourceStream
     * A handle to the attached source stream.
     */
    RWFilteredByteInputStreamImp(const RWByteInputStream& sourceStream)
        : RWByteInputStreamImp()
        , sourceStream_(sourceStream)
    {
        ;
    }

    /**
     * Returns a handle to the attached source stream. Throws no exceptions.
     */
    RWByteInputStream& getSourceStream()
    {
        return RW_EXPOSE(sourceStream_);
    }

    /**
     * Returns a handle to the attached source stream. Throws no exceptions.
     */
    const RWByteInputStream& getSourceStream() const
    {
        return sourceStream_;
    }

private:

    // A handle to the attached source stream.
    RWByteInputStream sourceStream_;

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWFilteredByteInputStreamImp_h_
