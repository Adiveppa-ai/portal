#ifndef rw_stream_RWCharInputStreamImp_h_
#define rw_stream_RWCharInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWCharInputStreamImp.h#1 $
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
class RWCString;
class RWCharInputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all narrow character input stream implementation
 * classes.
 *
 * Abstract base class for all the narrow character input stream
 * implementation classes. Implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWCharInputStreamImp : public RWInputStreamImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWCharInputStreamImp()
    {
        ;
    }

    /**
     * Reads a single narrow character from the stream.
     */
    virtual char read() = 0;

    /**
     * Reads an array of narrow characters from the stream. The array must
     * be pre-allocated to contain at least \a numChars elements. The
     * function returns the actual number of narrow characters read from the
     * stream.
     *
     * \param charArray
     * A pointer to the first element of the array.
     *
     * \param numChars
     * The number of narrow characters to be read from the stream.
     */
    virtual RWSize read(char* charArray, RWSize numChars) = 0;

    /**
     * Reads narrow character(s) from the attached source stream until the
     * last character read is equal to \a delim, or the end of the input
     * sequence is reached. The narrow character(s) read are stored in a
     * narrow \a string object.
     *
     * \param string
     * A string object receiving the narrow character(s) extracted from the
     * stream.
     *
     * \param delim
     * The narrow character used as a delimiter.
     */
    virtual void readStringUntil(RWCString& string, char delim) = 0;

    /**
     * Reads narrow character(s) from the attached source stream until the
     * last narrow character read is equal to \a delim, or \a maxSize narrow
     * character(s) have been read, or the end of the input sequence is
     * reached. The narrow character(s) read are stored in \a charArray. The
     * function returns the actual number of narrow character(s) read from
     * the stream.
     *
     * \param charArray
     * A pointer to the array receiving the narrow character(s) extracted
     * from the stream.
     *
     * \param maxSize
     * The maximum number of narrow character(s) to be read.
     *
     * \param delim
     * The narrow character value used as a delimiter.
     */
    virtual RWSize readUntil(char* charArray, RWSize maxSize, char delim) = 0;

    /**
     * Acquires the synchronization mechanism provided by a stream concrete
     * implementation. The acquire() member function returns a handle to the
     * narrow character stream that should be used for input operation after
     * acquiring the synchronization mechanism.
     */
    virtual RWCharInputStream acquire();

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
    RWCharInputStreamImp()
        : RWInputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWCharInputStreamImp_h_
