#ifndef rw_stream_RWWCharToWStreambufOutputStreamImp_h_
#define rw_stream_RWWCharToWStreambufOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWWCharToWStreambufOutputStreamImp.h#1 $
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

#include <rw/stream/RWWCharOutputStream.h>
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
 * character buffer. The iostreams buffer is used as the sink for the wide
 * characters written to the wide character stream. Implements the body
 * idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWWCharToWStreambufOutputStreamImp : public RWWCharOutputStreamImp
{

public:

    typedef std::wstreambuf::char_type char_type;

    /**
     * Constructs an RWWCharToWStreambufOutputStreamImp instance that uses
     * \a sink as its sink of wide characters, and returns a handle to it.
     * Throws no exceptions.
     *
     * \param sink
     * The iostreams \b std::wstreambuf that is used as the sink of wide
     * characters.
     */
    static RWWCharOutputStream make(std::wstreambuf& sink)
    {
        return RWWCharOutputStream(new RWWCharToWStreambufOutputStreamImp(sink));
    }

    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWWCharToWStreambufOutputStreamImp();

    /**
     * This function calls flush(). The user is responsible for closing the
     * iostreams \b std::wstreambuf used as the sink of wide characters if
     * necessary.
     */
    virtual void close();

    /**
     * Forward the flush() request to the iostreams \b std::wstreambuf.
     */
    virtual void flush();

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
     * Writes a single wide character to the iostreams \b std::wstreambuf.
     *
     * \param wcharValue
     * The wide character to be written.
     */
    virtual void write(wchar_t wcharValue);

    /**
     * Writes an array of wide characters to the iostreams
     * \b std::wstreambuf.
     *
     * \param wcharArray
     * A pointer to the first element of the array.
     *
     * \param numWChars
     * The number of wide characters to be written.
     */
    virtual void write(const wchar_t* wcharArray, RWSize numWChars);

protected:

    //-- Throws no exceptions.
    /**
     * Initializes the reference to the iostreams \b std::wstreambuf, that
     * will be used as the sink of wide characters.
     *
     * \param sinkBuff
     * The iostreams \b std::wstreambuf that will serve as the sink of wide
     * characters.
     */
    RWWCharToWStreambufOutputStreamImp(std::wstreambuf& sinkBuff)
        : RWWCharOutputStreamImp()
        , sinkBuff_(sinkBuff)
        , isBad_(false)
    {
        ;
    }

    /**
     * Returns a reference to the iostreams \b std::wstreambuf, which is
     * used as the sink of wide characters. Throws no exceptions.
     */
    std::wstreambuf& getSinkBuff()
    {
        return sinkBuff_;
    }

    /**
     * \copydoc getSinkBuff()
     */
    const std::wstreambuf& getSinkBuff() const
    {
        return sinkBuff_;
    }

private:

    // A reference to the iostreams 'wstreambuf' that is used as the sink of
    // wide characters.
    std::wstreambuf& sinkBuff_;

    bool isBad_;

};

#endif // rw_stream_RWWCharToWStreambufOutputStreamImp_h_
