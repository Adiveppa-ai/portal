#ifndef rw_stream_RWWCharFromWStreambufInputStreamImp_h_
#define rw_stream_RWWCharFromWStreambufInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWWCharFromWStreambufInputStreamImp.h#1 $
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

#include <rw/stream/RWWCharInputStream.h>
#include <rw/stream/pkgdefs.h>
#include <streambuf>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class connecting a wide character stream to an iostreams wide
 * character buffer.
 *
 * Concrete class connecting a wide character stream to an iostreams wide
 * character buffer. The iostreams buffer is used as the source for the wide
 * characters read from the wide character stream. Implements the body idiom
 * from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWWCharFromWStreambufInputStreamImp : public RWWCharInputStreamImp
{

public:

    typedef std::wstreambuf::char_type char_type;

    /**
     * Constructs an RWWCharFromWStreambufInputStreamImp instance that uses
     * \a source as its source of wide characters, and returns a handle to
     * it. Throws no exceptions.
     *
     * \param source
     * The iostreams \b std::wstreambuf that is used as the source of wide
     * characters.
     */
    static RWWCharInputStream make(std::wstreambuf& source)
    {
        return RWWCharInputStream(new RWWCharFromWStreambufInputStreamImp(source));
    }

    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWWCharFromWStreambufInputStreamImp();

    /**
     * This function does nothing. The user is responsible for closing the
     * iostreams \b std::wstreambuf used as the source of wide characters if
     * necessary. Throws no exceptions.
     */
    virtual void close();

    /**
     * Returns \c true if there are no wide characters available from the
     * iostreams \b std::wstreambuf used as the source of wide characters.
     * Throws no exceptions.
     */
    virtual bool isEof() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \b std::wstreambuf failed. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \b std::wstreambuf failed. Throws no exceptions.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \b std::wstreambuf succeeded. Throws no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Reads a single wide character from the iostreams \b std::wstreambuf
     * used as the source of wide characters.
     */
    virtual wchar_t read();

    /**
     * Reads an array of wide characters from the iostreams
     * \b std::wstreambuf used as the source of wide characters. The array
     * must be pre-allocated to contain at least \a numWChars elements. The
     * function returns the actual number of wide characters extracted from
     * the iostreams \b std::wstreambuf.
     *
     * \param wcharArray
     * A pointer to the first element of the array.
     *
     * \param numWChars
     * The number of wide characters to be read from the stream.
     */
    virtual RWSize read(wchar_t* wcharArray, RWSize numWChars);

    /**
     * Reads wide characters from the iostreams \b std::wstreambuf used as
     * the source of wide characters until the last wide character read is
     * equal to \a delim, or \a maxSize wide characters have been read, or
     * the end of the input sequence is reached. The wide characters read
     * are stored in \a wcharArray. The function returns the actual number
     * of wide characters inserted into \a wcharArray. If the last wide
     * character extracted is equal to \a delim, then it is not stored in
     * \a wcharArray.
     *
     * \param wcharArray
     * A pointer to the array receiving the wide characters extracted from
     * the iostreams \b std::wstreambuf.
     *
     * \param maxSize
     * The maximum number of wide characters to be read.
     *
     * \param delim
     * The wide character used as a delimiter.
     */
    virtual RWSize readUntil(wchar_t* wcharArray, RWSize maxSize, wchar_t delim);

    /**
     * Returns the number of wide characters that can be read from the
     * iostreams \b std::wstreambuf used as the source of wide characters
     * without blocking.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits wide characters from the input sequence if
     * possible. The function returns the actual number of wide characters
     * skipped, which can be any value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of wide characters to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

protected:

    //-- Throws no exceptions.
    /**
     * Initializes the reference to the iostreams \b std::wstreambuf, that
     * will be used as the source of wide characters.
     *
     * \param sourceBuff
     * The iostreams \b std::wstreambuf that will serve as the source of
     * wide characters.
     */
    RWWCharFromWStreambufInputStreamImp(std::wstreambuf& sourceBuff)
        : RWWCharInputStreamImp()
        , sourceBuff_(sourceBuff)
        , isFail_(false)
    {
        ;
    }

    /**
     * Returns a reference to the iostreams \b std::wstreambuf, which is
     * used as the source of wide characters. Throws no exceptions.
     */
    std::wstreambuf& getSourceBuff()
    {
        return sourceBuff_;
    }

    /**
     * \copydoc getSourceBuff()
     */
    const std::wstreambuf& getSourceBuff() const
    {
        return sourceBuff_;
    }

private:

    // A reference to the iostreams wstreambuf that is used as the source of wide characters.
    std::wstreambuf& sourceBuff_;

    bool isFail_;

};

#endif // rw_stream_RWWCharFromWStreambufInputStreamImp_h_
