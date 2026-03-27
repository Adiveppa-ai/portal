#ifndef rw_stream_RWCharToStreambufOutputStreamImp_h_
#define rw_stream_RWCharToStreambufOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWCharToStreambufOutputStreamImp.h#1 $
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

#include <rw/stream/RWCharOutputStream.h>
#include <rw/stream/pkgdefs.h>
#include <iosfwd>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class connecting a narrow character stream to an iostreams
 * narrow character buffer.
 *
 * Concrete class connecting a narrow character stream, to an iostreams
 * narrow character buffer. The iostreams buffer is used as the sink for the
 * data written to the narrow character stream. Implements the body idiom
 * from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWCharToStreambufOutputStreamImp : public RWCharOutputStreamImp
{

public:

    /**
     * Constructs an RWCharToStreambufOutputStreamImp instance that uses
     * \a sink as its sink of narrow characters, and returns a handle to it.
     * Throws no exceptions.
     *
     * \param sink
     * The iostreams \c std::streambuf that is used as the sink of narrow
     * characters.
     */
    static RWCharOutputStream make(std::streambuf& sink)
    {
        return RWCharOutputStream(new RWCharToStreambufOutputStreamImp(sink));
    }

    /**
     * Destructor.
     */
    virtual ~RWCharToStreambufOutputStreamImp();

    /**
     * This function calls flush(). The user is responsible for closing the
     * iostreams \c std::streambuf used as the sink of narrow characters if
     * necessary.
     *
     * \exception RWExternalStreamException
     * Thrown when the call to the internal iostreams \c std::streambuf
     * object fails or any propagated exceptions from that call occur.
     */
    virtual void close();

    /**
     * Forward the flush request to the iostreams \c std::streambuf.
     *
     * \exception RWExternalStreamException
     * Thrown when the call to the internal iostreams \c std::streambuf
     * object fails or any propagated exceptions from that call occur.
     */
    virtual void flush();

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \c std::streambuf failed. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \c std::streambuf failed. Throws no exceptions.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the iostreams
     * \c std::streambuf succeeded. Throws no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Writes a single narrow character to the iostreams \c std::streambuf.
     *
     * \exception RWExternalStreamException
     * Thrown when the call to the internal iostreams \c std::streambuf
     * object fails or any propagated exceptions from that call occur.
     *
     * \param charValue
     * The narrow character to be written.
     */
    virtual void write(char charValue);

    //--Writes an array of narrow character(s) to the iostreams 'streambuf'.
    //--The parameter 'charArray' is a pointer to the first element of the array.
    //--The parameter 'numChars' is the number of narrow character(s) to be written.
    //--Throws exception 'RWIncompleteStreamOperation' and any other exception propagated by another function.
    /**
     * Writes an array of narrow characters to the iostreams
     * \c std::streambuf.
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when the call to the internal iostreams \c std::streambuf
     * object fails or any propagated exceptions from that call occur.
     *
     * \param charArray
     * A pointer to the first element of the array.
     *
     * \param numChars
     * The number of narrow characters to be written.
     */
    virtual void write(const char* charArray, RWSize numChars);

protected:

    /**
     * Initializes the reference to the iostreams \c std::streambuf, that
     * will be used as the sink of narrow characters.
     *
     * \param sinkBuff
     * The iostreams \c std::streambuf that will serve as the sink of narrow
     * characters.
     */
    RWCharToStreambufOutputStreamImp(std::streambuf& sinkBuff)
        : RWCharOutputStreamImp()
        , sinkBuff_(sinkBuff)
        , isBad_(false)
    {
        ;
    }

    /**
     * Returns a reference to the iostreams \c std::streambuf, which is used
     * as the sink of narrow characters. Throws no exceptions.
     */
    std::streambuf& getSinkBuff()
    {
        return sinkBuff_;
    }

    /**
     * Returns a reference to the iostreams \c std::streambuf, which is used
     * as the sink of narrow characters. Throws no exceptions.
     */
    const std::streambuf& getSinkBuff() const
    {
        return sinkBuff_;
    }

private:

    // A reference to the iostreams streambuf that is used as the sink of narrow characters.
    std::streambuf& sinkBuff_;

    bool isBad_;

};

#endif // rw_stream_RWCharToStreambufOutputStreamImp_h_
