#ifndef rw_stream_RWCharFromStreambufInputStreamImp_h_
#define rw_stream_RWCharFromStreambufInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWCharFromStreambufInputStreamImp.h#1 $
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

#include <rw/stream/RWCharInputStream.h>
#include <rw/stream/pkgdefs.h>
#include <iosfwd>

class RWCString;

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class connecting a narrow character stream to an iostreams
 * narrow character buffer.
 *
 * Concrete class connecting a narrow character stream, to an iostreams
 * narrow character buffer. The iostreams buffer is used as the source for
 * the data read from the binary stream. The iostreams buffer must be opened
 * in binary mode. Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWCharFromStreambufInputStreamImp : public RWCharInputStreamImp
{

public:

    /**
     * Constructs an RWCharFromStreambufInputStreamImp instance that uses
     * \a source as its source of narrow characters, and returns a handle to
     * it. Throws no exceptions.
     *
     * \param source
     * The iostreams \b std::streambuf that is used as the source of narrow
     * characters.
     */
    static RWCharInputStream make(std::streambuf& source)
    {
        return RWCharInputStream(new RWCharFromStreambufInputStreamImp(source));
    }

    /**
     * Destructor.
     */
    virtual ~RWCharFromStreambufInputStreamImp();

    /**
     * This function does nothing. The user is responsible for closing the
     * iostreams \b std::streambuf, which is used as the source of narrow
     * characters.
     */
    virtual void close();

    /**
     * Returns \c true if there is no narrow character available from the
     * iostreams \b std::streambuf, used as the source of narrow characters.
     */
    virtual bool isEof() const;

    /**
     * These functions return \c true if the last operation performed on the
     * iostreams \b std::streambuf failed.
     */
    virtual bool isBad() const;

    /**
     * These functions return \c true if the last operation performed on the
     * iostreams \b std::streambuf failed.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \b std::streambuf succeeded.
     */
    virtual bool isGood() const;

    /**
     * Reads a single narrow character from the iostreams \b std::streambuf
     * used as the source of narrow characters. Throws exception
     * RWExternalStreamException and propagates any other exception thrown
     * by the internal iostreams stream buffer object.
     */
    virtual char read();

    /**
     * Reads an array of narrow characters from the iostreams
     * \b std::streambuf used as the source of narrow characters. The array
     * must be pre-allocated to contain at least \a numChars elements. The
     * function returns the actual number of narrow characters extracted
     * from the iostreams \b std::streambuf. Throws exception
     * RWExternalStreamException and propagates any other exception thrown
     * by the internal iostreams stream buffer object.
     *
     * \param charArray
     * A pointer to the first element of the array.
     *
     * \param numChars
     * The number of narrow characters to be read from the stream.
     */
    virtual RWSize read(char* charArray, RWSize numChars);

    /**
     * Reads narrow characters from the iostreams \b std::streambuf used as
     * the source of narrow characters until the last narrow character read
     * is equal to \a delim, or until the end of the input sequence is
     * reached. The narrow characters read are stored in \a string. If the
     * last narrow character extracted is equal to \a delim, then it is not
     * stored in \a string.
     *
     * \param string
     * Reference to the narrow string receiving the narrow characters
     * extracted from the iostreams \b std::streambuf.
     *
     * \param delim
     * Narrow character value used as a delimiter.
     */
    virtual void readStringUntil(RWCString& string, char delim);

    /**
     * Reads narrow character(s) from the iostreams \b std::streambuf, used
     * as its source of narrow characters, until the last narrow character
     * read is equal to \a delim, or \a maxSize narrow character(s) have
     * been read, or the end of the input sequence is reached. The narrow
     * character(s) read are stored in \a charArray. The function returns
     * the actual number of narrow character(s) inserted into \a charArray.
     * If the last narrow character extracted is equal to \a delim, then it
     * is not stored in \a charArray.
     *
     * \param charArray
     * A pointer to the array receiving the narrow characters(s) extracted
     * from the iostreams \b std::streambuf.
     *
     * \param maxSize
     * The maximum number of narrow character(s) to be read.
     *
     * \param delim
     * The narrow character value used as a delimiter.
     */
    virtual RWSize readUntil(char* charArray, RWSize maxSize, char delim);

    /**
     * Returns the number of narrow characters that can be read from the
     * iostreams \b std::streambuf, which is used as the source of narrow
     * characters without blocking.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits narrow characters from the input sequence if
     * possible. The function returns the actual number of narrow characters
     * skipped, which can be any value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of narrow characters to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

protected:

    /**
     * Initializes the reference to the iostreams \b std::streambuf, that
     * will be used as the source of narrow characters. Throws no
     * exceptions.
     *
     * \param sourceBuff
     * The iostreams \b std::streambuf that will serve as the source of
     * narrow characters.
     */
    RWCharFromStreambufInputStreamImp(std::streambuf& sourceBuff)
        : RWCharInputStreamImp()
        , sourceBuff_(sourceBuff)
        , isFail_(false)
    {
        ;
    }

    /**
     * These functions return a reference to the iostreams
     * \b std::streambuf, which is used as the source of narrow characters.
     */
    std::streambuf& getSourceBuff()
    {
        return sourceBuff_;
    }

    /**
     * These functions return a reference to the iostreams
     * \b std::streambuf, which is used as the source of narrow characters.
     */
    const std::streambuf& getSourceBuff() const
    {
        return sourceBuff_;
    }

private:

    // A reference to the iostreams 'streambuf' that is used as the source of narrow characters.
    std::streambuf& sourceBuff_;

    bool isFail_;

};

#endif // rw_stream_RWCharFromStreambufInputStreamImp_h_
