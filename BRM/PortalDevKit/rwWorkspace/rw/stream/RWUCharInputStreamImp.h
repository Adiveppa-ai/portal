#ifndef rw_stream_RWUCharInputStreamImp_h_
#define rw_stream_RWUCharInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharInputStreamImp.h#1 $
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

class RWUCharInputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the Unicode character input stream
 * implementation classes.
 *
 * Abstract base class for all the Unicode character input stream
 * implementation classes. Implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWUCharInputStreamImp : public RWInputStreamImp
{

public:

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWUCharInputStreamImp()
    {
        ;
    }

    /**
     * Reads a single UTF-16 character from the stream.
     */
    virtual RWUChar read() = 0;

    /**
     * Reads an array of UTF-16 characters from the stream. The array must
     * be pre-allocated to contain at least \a numUChars elements. The
     * function returns the actual number of UTF-16 characters read from the
     * stream.
     *
     * \param unicodeArray
     * A pointer to the first element of the array.
     *
     * \param numUChars
     * The number of UTF-16 characters to be read from the stream.
     */
    virtual RWSize read(RWUChar* unicodeArray, RWSize numUChars) = 0;

    /**
     * Reads UTF-16 characters from the stream until the last UTF-16
     * character read is equal to \a delim, or \a maxSize UTF-16 characters
     * have been read, or the end of the input sequence is reached. The
     * UTF-16 characters read are stored in \a unicodeArray. The function
     * returns the actual number of UTF-16 characters read from the stream.
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
    virtual RWSize readUntil(RWUChar* unicodeArray, RWSize maxSize, RWUChar delim) = 0;

    /**
     * Acquires the synchronization mechanism provided by a stream concrete
     * implementation. The acquire() member function returns a handle to the
     * UTF-16 character stream that should be used for input operation after
     * acquiring the synchronization mechanism.
     */
    virtual RWUCharInputStream acquire();

    /**
     * Releases the synchronization mechanism provided by a stream concrete
     * implementation.
     */
    virtual void release()
    {
        ;
    }

protected:

    //-- Constructor.
    //-- Throws no exceptions.
    /**
     * Constructor.
     */
    RWUCharInputStreamImp()
        : RWInputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWUCharInputStreamImp_h_
