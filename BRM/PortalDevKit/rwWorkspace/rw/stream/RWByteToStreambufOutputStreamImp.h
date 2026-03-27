#ifndef rw_stream_RWByteToStreambufOutputStreamImp_h_
#define rw_stream_RWByteToStreambufOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWByteToStreambufOutputStreamImp.h#1 $
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

#include <rw/stream/RWByteOutputStream.h>
#include <rw/stream/pkgdefs.h>
#include <streambuf>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class connecting a binary stream to an iostreams narrow
 * character buffer.
 *
 * Concrete class connecting a binary stream to an iostreams narrow
 * character buffer. The iostreams buffer is used as the sink for the data
 * written to the binary stream. The iostreams buffer must be opened in
 * binary mode. Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWByteToStreambufOutputStreamImp : public RWByteOutputStreamImp
{

public:

    typedef std::streambuf::char_type char_type;

    /**
     * Constructs an RWByteToStreambufOutputStreamImp instance that uses
     * \a sink as its sink of bytes, and returns a handle to it. Throws no
     * exceptions.
     *
     * \param sink
     * The iostreams \c std::streambuf that is used as the sink of bytes.
     */
    static RWByteOutputStream make(std::streambuf& sink)
    {
        return RWByteOutputStream(new RWByteToStreambufOutputStreamImp(sink));
    }

    /**
     * Destructor.
     */
    virtual ~RWByteToStreambufOutputStreamImp();

    /**
     * This function calls flush(). The user is responsible for closing the
     * iostreams \c std::streambuf used as the sink of bytes, if necessary.
     * Throws RWExternalStreamException and propagates any other exception
     * thrown by the internal \c std::iostreams streambuf object.
     */
    virtual void close();

    /**
     * Forward the flush request to the iostreams \c std::streambuf. Throws
     * RWExternalStreamException and propagates any other exception thrown
     * by the internal iostreams \c std::streambuf object.
     */
    virtual void flush();

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
     * Writes a single byte to the iostreams \c std::streambuf. Throws
     * exception RWExternalStreamException and propagates any other
     * exception thrown by the internal iostreams \c std::streambuf object.
     *
     * \param byteValue
     * The byte to be written.
     */
    virtual void write(RWByte byteValue);

    /**
     * Writes an array of bytes to the iostreams \c std::streambuf. Throws
     * exception RWIncompleteStreamOperation and propagates any other
     * exception thrown by the internal iostreams \c std::streambuf object.
     *
     * \param byteArray
     * A pointer to the first element of the array.
     *
     * \param numBytes
     * The number of bytes to be written.
     */
    virtual void write(const RWByte* byteArray, RWSize numBytes);

protected:

    /**
     * Initializes the reference to the iostreams \c std::streambuf, used as
     * the sink of bytes.
     *
     * \param sinkBuff
     * The iostreams \c std::streambuf that will serve as the sink of bytes.
     */
    RWByteToStreambufOutputStreamImp(std::streambuf& sinkBuff)
        : RWByteOutputStreamImp()
        , sinkBuff_(sinkBuff)
        , isBad_(false)
    {
        ;
    }

    /**
     * Returns a reference to the iostreams \c std::streambuf, which is used
     * as the sink of bytes.
     */
    std::streambuf& getSinkBuff()
    {
        return sinkBuff_;
    }

    /**
     * Returns a const reference to the iostreams \c std::streambuf, which
     * is used as the sink of bytes.
     */
    const std::streambuf& getSinkBuff() const
    {
        return sinkBuff_;
    }

private:

    // A reference to the iostreams 'streambuf' that is used as the sink of bytes.
    std::streambuf& sinkBuff_;

    bool isBad_;

};

#endif // rw_stream_RWByteToStreambufOutputStreamImp_h_
