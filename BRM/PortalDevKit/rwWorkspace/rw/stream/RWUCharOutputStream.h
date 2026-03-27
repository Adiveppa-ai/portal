#ifndef rw_stream_RWUCharOutputStream_h_
#define rw_stream_RWUCharOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharOutputStream.h#1 $
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

#include <rw/stream/RWUCharOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredUCharOutputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for the Unicode character output stream implementation
 * classes.
 *
 * Handle class for all the Unicode character output stream implementation
 * classes. Implements the handle idiom from the handle-body pattern.
 */
class RWUCharOutputStream : public RWHandleBase
{

public:

    typedef RWUChar element_type;

    //-- Constructor.
    //-- Throws no exceptions.
    /**
     * Constructor.
     */
    explicit RWUCharOutputStream(RWUCharOutputStreamImp* body)
        : RWHandleBase(body)
    {
        ;
    }

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
    RWUCharOutputStream(const RWUCharOutputStream& handle)
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
    RWUCharOutputStream& operator=(const RWUCharOutputStream& handle)
    {
        this->RWHandleBase::operator=(handle);
        return *this;
    }

    /**
     * Inserter executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWUCharOutputStream& operator<<(RWUCharOutputStream & (*pf)(RWUCharOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Inserter executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWUCharOutputStream operator<<(RWUCharOutputStream(*pf)(RWUCharOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Writes a single UTF-16 character to the stream.
     *
     * \param unicodeValue
     * The UTF-16 character to be written to the stream.
     */
    RWUCharOutputStream& operator<<(RWUChar unicodeValue)
    {
        this->write(unicodeValue);
        return *this;
    }

    /**
     * Writes a single UTF-16 character to the stream.
     *
     * \param unicodeValue
     * The UTF-16 character to be written to the stream.
     */
    void write(RWUChar unicodeValue)
    {
        static_cast<RWUCharOutputStreamImp&>(this->body()).write(unicodeValue);
    }

    /**
     * Writes an array of UTF-16 characters to the stream.
     *
     * \param unicodeArray
     * A pointer to the first element of the array.
     *
     * \param numUChars
     * The number of UTF-16 characters to be written to the stream.
     */
    void write(const RWUChar* unicodeArray, RWSize numUChars)
    {
        static_cast<RWUCharOutputStreamImp&>(this->body()).write(unicodeArray, numUChars);
    }

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWUCharOutputStreamImp&>(this->body()).close();
    }

    /**
     * Flushes the stream.
     */
    void flush()
    {
        static_cast<RWUCharOutputStreamImp&>(this->body()).flush();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * output operation. Throws no exceptions.
     */
    bool isBad() const
    {
        return static_cast<RWUCharOutputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an output operation failed to
     * generate the desired data. Throws no exceptions.
     */
    bool isFail() const
    {
        return static_cast<RWUCharOutputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    bool isGood() const
    {
        return static_cast<RWUCharOutputStreamImp&>(this->body()).isGood();
    }

private:

    //-- Acquires the synchronization mechanism provided by a stream concrete
    //-- implementation. The 'acquire()' member function returns a handle to the
    //-- unicode character stream that should be used for output operation after acquiring
    //-- the synchronization mechanism. This function is only used by instance of
    //-- class 'RWGuardedUCharOutputStreamImp'.
    RWUCharOutputStream acquire()
    {
        return static_cast<RWUCharOutputStreamImp&>(this->body()).acquire();
    }

    //-- Releases the synchronization mechanism provided by a stream concrete
    //-- implementation. This function is only used by instance of
    //-- class 'RWGuardedUCharOutputStreamImp'.
    void release()
    {
        static_cast<RWUCharOutputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWUCharOutputStream, RWFilteredUCharOutputStreamImp>;
};

/**
 * \relates RWUCharOutputStream
 *
 * Manipulator that flushes a UTF-16 character output stream.
 *
 * \param stream
 * The UTF-16 character stream to be flushed.
 */
inline RWUCharOutputStream& rwFlush(RWUCharOutputStream& stream)
{
    stream.flush();
    return stream;
}

/**
 * \relates RWUCharOutputStream
 *
 * Manipulator that writes an end-of-line UTF-16 control character to the
 * stream.
 *
 * \param stream
 * A UTF-16 character output stream.
 */
inline RWUCharOutputStream& rwEndl(RWUCharOutputStream& stream)
{
    stream.write(static_cast<RWUChar>('\n'));
    return stream;
}

/**
 * \relates RWUCharOutputStream
 *
 * Manipulator that writes an end-of-string UTF-16 character to the stream.
 *
 * \param stream
 * A UTF-16 character output stream.
 */
inline RWUCharOutputStream& rwEnds(RWUCharOutputStream& stream)
{
    stream.write(static_cast<RWUChar>('\0'));
    return stream;
}

#endif // rw_stream_RWUCharOutputStream_h_
