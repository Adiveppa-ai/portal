#ifndef rw_stream_RWByteInputStreamImp_h_
#define rw_stream_RWByteInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWByteInputStreamImp.h#1 $
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

#include <rw/stream/RWInputStreamImp.h>
#include <rw/stream/pkgdefs.h>

// forward declaration
class RWByteInputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all binary input stream implementation classes.
 *
 * Abstract base class for all the binary input stream implementation
 * classes. Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWByteInputStreamImp : public RWInputStreamImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWByteInputStreamImp()
    {
        ;
    }

    /**
     * Reads a single byte from the stream.
     */
    virtual RWByte read() = 0;

    /**
     * Reads an array of bytes from the stream. The array must be
     * pre-allocated to contain at least of \a numBytes elements. The
     * function returns the actual number of bytes read from the stream.
     *
     * \param byteArray
     * A pointer to the first element of the array.
     *
     * \param numBytes
     * The number of bytes to be read from the stream.
     */
    virtual RWSize read(RWByte* byteArray, RWSize numBytes) = 0;

    /**
     * Reads bytes from the stream until the last byte read is equal to
     * \a delim, or \a maxSize bytes have been read, or the end of the input
     * sequence is reached. The bytes read are stored in \a byteArray. The
     * function returns the actual number of bytes read from the stream.
     *
     * \param byteArray
     * A pointer to the array receiving the bytes extracted from the stream.
     *
     * \param maxSize
     * The maximum number of bytes to be read.
     *
     * \param delim
     * The byte value used as a delimiter.
     */
    virtual RWSize readUntil(RWByte* byteArray, RWSize maxSize, RWByte delim) = 0;

    /**
     * Acquires the synchronization mechanism provided by a stream concrete
     * implementation. The acquire() member function returns a handle to the
     * binary stream that should be used for input operation after acquiring
     * the synchronization mechanism.
     */
    virtual RWByteInputStream acquire();

    /**
     * Releases the synchronization mechanism provided by a stream concrete
     * implementation.
     */
    virtual void release()
    {
        ;
    }

protected:

    /**
     * Constructor.
     */
    RWByteInputStreamImp()
        : RWInputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWByteInputStreamImp_h_
