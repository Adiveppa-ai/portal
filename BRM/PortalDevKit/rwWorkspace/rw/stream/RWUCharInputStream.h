#ifndef rw_stream_RWUCharInputStream_h_
#define rw_stream_RWUCharInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharInputStream.h#1 $
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

#include <rw/stream/RWUCharInputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredUCharInputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all the UTF-16 character input stream implementation
 * classes.
 *
 * Handle class for all the UTF-16 character input stream implementation
 * classes. Implements the handle idiom from the handle-body pattern.
 */
class RWUCharInputStream : public RWHandleBase
{

public:

    typedef RWUChar element_type;

    //-- Constructor.
    //-- Throws no exceptions.
    /**
     * Constructor.
     */
    explicit RWUCharInputStream(RWUCharInputStreamImp* body)
        : RWHandleBase(body)
    { }

    //-- Copy constructor.
    //--
    //-- Parameters:
    //--
    //--   'handle': A unicode character stream handle used to initialize the
    //-- newly created handle.
    //-- Throws no exceptions.
    //--
    /**
     * Copy constructor.
     *
     * \param handle
     * A UTF-16 character stream handle used to initialize the newly created
     * handle.
     */
    RWUCharInputStream(const RWUCharInputStream& handle)
        : RWHandleBase(handle)
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A UTF-16 character stream handle used to initialize this handle.
     */
    RWUCharInputStream& operator=(const RWUCharInputStream& handle)
    {
        this->RWHandleBase::operator=(handle);
        return *this;
    }

    /**
     * Extractor executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWUCharInputStream& operator>>(RWUCharInputStream & (*pf)(RWUCharInputStream&))
    {
        return pf(*this);
    }

    /**
     * Extractor executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWUCharInputStream operator>>(RWUCharInputStream(*pf)(RWUCharInputStream&))
    {
        return pf(*this);
    }

    /**
     * Reads a single UTF-16 character from the stream.
     *
     * \param unicodeValue
     * The UTF-16 character to be read from the stream.
     */
    RWUCharInputStream& operator>>(RWUChar& unicodeValue)
    {
        unicodeValue = this->read();
        return *this;
    }

    /**
     * Reads a single UTF-16 character from the stream.
     */
    RWUChar read()
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).read();
    }

    /**
     * Reads an array of UTF-16 characters from the stream. The array must
     * be pre-allocated to contain at least \a numUChars elements. The
     * function returns the actual number of UTF-16 characters extracted
     * from the stream.
     *
     * \param unicodeArray
     * A pointer to the first element of the array.
     *
     * \param numUChars
     * The number of UTF-16 characters to be read from the stream.
     */
    RWSize read(RWUChar* unicodeArray, RWSize numUChars)
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).read(unicodeArray, numUChars);
    }

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
    RWSize readUntil(RWUChar* unicodeArray, RWSize maxSize, RWUChar delim)
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).readUntil(unicodeArray, maxSize, delim);
    }

    /**
     * Close the stream.
     */
    void close()
    {
        static_cast<RWUCharInputStreamImp&>(this->body()).close();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * input operation, such as an irrecoverable read error from a file.
     * Throws no exceptions.
     */
    bool isBad() const
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an input operation failed to read
     * the expected data. Throws no exceptions.
     */
    bool isFail() const
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    bool isGood() const
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).isGood();
    }

    /**
     * Returns \c true to indicate that an input operation reached the end
     * of an input sequence. Throws no exceptions.
     */
    bool isEof() const
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).isEof();
    }

    /**
     * Returns the number of UTF-16 characters that can be read from the
     * stream without blocking. Throws no exceptions.
     */
    RWSize available() const
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).available();
    }

    /**
     * Skips \a numUnits UTF-16 characters from the input sequence if
     * possible. The function returns the actual number of UTF-16 characters
     * skipped, which can be any value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of UTF-16 characters to be skipped.
     */
    RWSize skip(RWSize numUnits)
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).skip(numUnits);
    }

private:

    //-- Acquires the synchronization mechanism provided by a stream concrete
    //-- implementation. The 'acquire()' member function returns a handle to the
    //-- unicode character stream that should be used for input operation after acquiring
    //-- the synchronization mechanism. This function is only used by instance of
    //-- class 'RWGuardedUCharInputStreamImp'.
    RWUCharInputStream acquire()
    {
        return static_cast<RWUCharInputStreamImp&>(this->body()).acquire();
    }

    //-- Releases the synchronization mechanism provided by a stream concrete
    //-- implementation. This function is only used by instance of
    //-- class 'RWGuardedUCharInputStreamImp'.
    void release()
    {
        static_cast<RWUCharInputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWUCharInputStream, RWFilteredUCharInputStreamImp>;
};

/**
 * \relates RWUCharInputStream
 *
 * Manipulator that discards a UTF-16 character from a stream input
 * sequence.
 *
 * \param stream
 * The UTF-16 character stream.
 */
inline RWUCharInputStream& rwDisc(RWUCharInputStream& stream)
{
    stream.read();
    return stream;
}

#endif // rw_stream_RWUCharInputStream_h_
