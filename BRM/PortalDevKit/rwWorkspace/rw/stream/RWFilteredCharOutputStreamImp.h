#ifndef rw_stream_RWFilteredCharOutputStreamImp_h_
#define rw_stream_RWFilteredCharOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWFilteredCharOutputStreamImp.h#1 $
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

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the filtered narrow character output stream
 * implementation classes.
 *
 * Abstract base class for all the filtered narrow character output stream
 * implementation classes. A filtered output stream is a stream that process
 * elements and then forwards the result to another stream for further
 * processing. Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWFilteredCharOutputStreamImp : public RWCharOutputStreamImp
{

public:

    /**
     * Destructor. Throws no exceptions.
     */
    virtual ~RWFilteredCharOutputStreamImp();

    /**
     * Forwards the close() request to the next processing stream.
     */
    virtual void close();

    /**
     * Forwards the flush() request to the next processing stream.
     */
    virtual void flush();

    /**
     * Forwards the isBad() request to the next processing stream. Throws no
     * exceptions.
     */
    virtual bool isBad() const;

    /**
     * Forwards the isFail() request to the next processing stream. Throws
     * no exceptions.
     */
    virtual bool isFail() const;

    /**
     * Forwards the isGood() request to the next processing stream. Throws
     * no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Forwards the writing of a single narrow character to the next
     * processing stream.
     *
     * \param charValue
     * The narrow character to be written.
     */
    virtual void write(char charValue);

    /**
     * Forwards the writing of an array of narrow characters to the next
     * processing stream.
     *
     * \param charArray
     * A pointer to the first element of the array.
     *
     * \param numChars
     * The number of narrow character(s) to be written to the stream.
     */
    virtual void write(const char* charArray, RWSize numChars);


protected:

    /**
     * Used by derived classes to initialize the next processing stream.
     * Throws no exceptions.
     *
     * \param sinkStream
     * A handle to the next processing stream.
     */
    RWFilteredCharOutputStreamImp(const RWCharOutputStream& sinkStream)
        : RWCharOutputStreamImp()
        , sinkStream_(sinkStream)
    {
        ;
    }

    /**
     * Returns a handle to the next processing stream. Throws no exceptions.
     */
    RWCharOutputStream& getSinkStream()
    {
        return RW_EXPOSE(sinkStream_);
    }

    /**
     * Returns a handle to the next processing stream. Throws no exceptions.
     */
    const RWCharOutputStream& getSinkStream() const
    {
        return sinkStream_;
    }

private:

    // A handle to the next processing stream.
    RWCharOutputStream sinkStream_;

};

#endif // rw_stream_RWFilteredCharOutputStreamImp_h_
