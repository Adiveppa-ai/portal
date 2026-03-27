#ifndef rw_stream_RWWCharOutputStream_h_
#define rw_stream_RWWCharOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWWCharOutputStream.h#1 $
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

#include <rw/stream/RWWCharOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredWCharOutputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all the wide character output stream implementation
 * classes.
 *
 * Handle class for all the wide character output stream implementation
 * classes. Implements the handle idiom from the handle-body pattern.
 */
class RWWCharOutputStream : public RWHandleBase
{

public:

    typedef wchar_t element_type;

    //-- Throws no exceptions.
    /**
     * Constructor.
     */
    explicit RWWCharOutputStream(RWWCharOutputStreamImp* ptr)
        : RWHandleBase(ptr)
    { }

    //-- Throws no exceptions.
    /**
     * Copy constructor.
     *
     * \param handle
     * A wide character stream handle used to initialize the newly created
     * handle.
     */
    RWWCharOutputStream(const RWWCharOutputStream& handle)
        : RWHandleBase(handle)
    { }

    //-- Throws no exceptions.
    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A wide character stream handle used to initialize this handle.
     */
    RWWCharOutputStream& operator=(const RWWCharOutputStream& handle)
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
    RWWCharOutputStream& operator<<(RWWCharOutputStream & (*pf)(RWWCharOutputStream&))
    {
        return pf(*this);
    }

    /**
     * \copydoc operator<<()
     */
    RWWCharOutputStream operator<<(RWWCharOutputStream(*pf)(RWWCharOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Writes a single wide character to the stream.
     *
     * \param wcharValue
     * The wide character to be written to the stream.
     */
    RWWCharOutputStream& operator<<(wchar_t wcharValue)
    {
        this->write(wcharValue);
        return *this;
    }

    /**
     * Writes a single wide character to the stream.
     *
     * \param wcharValue
     * The wide character to be written to the stream.
     */
    void write(wchar_t wcharValue)
    {
        static_cast<RWWCharOutputStreamImp&>(this->body()).write(wcharValue);
    }

    /**
     * Writes an array of wide characters to the stream.
     *
     * \param wcharArray
     * A pointer to the first element of the array.
     *
     * \param numWChars
     * The number of wide characters to be written to the stream.
     */
    void write(const wchar_t* wcharArray, RWSize numWChars)
    {
        static_cast<RWWCharOutputStreamImp&>(this->body()).write(wcharArray, numWChars);
    }

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWWCharOutputStreamImp&>(this->body()).close();
    }

    /**
     * Flushes the stream.
     */
    void flush()
    {
        static_cast<RWWCharOutputStreamImp&>(this->body()).flush();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * output operation. Throws no exceptions.
     */
    bool isBad() const
    {
        return static_cast<RWWCharOutputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an output operation failed to
     * generate the desired data. Throws no exceptions.
     */
    bool isFail() const
    {
        return static_cast<RWWCharOutputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    bool isGood() const
    {
        return static_cast<RWWCharOutputStreamImp&>(this->body()).isGood();
    }

private:

    //-- Acquires the synchronization mechanism provided by a stream concrete
    //-- implementation. The 'acquire()' member function returns a handle to the
    //-- wide character stream that should be used for output operation after acquiring
    //-- the synchronization mechanism. This function is only used by instance of
    //-- class 'RWGuardedWCharOutputStreamImp'.
    RWWCharOutputStream acquire()
    {
        return static_cast<RWWCharOutputStreamImp&>(this->body()).acquire();
    }

    //-- Releases the synchronization mechanism provided by a stream concrete
    //-- implementation. This function is only used by instance of
    //-- class 'RWGuardedWCharOutputStreamImp'.
    void release()
    {
        static_cast<RWWCharOutputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWWCharOutputStream, RWFilteredWCharOutputStreamImp>;
};

/**
 * \relates RWWCharOutputStream
 *
 * Manipulator that flushes a wide character output stream.
 *
 * \param stream
 * The wide character stream to be flushed.
 */
inline RWWCharOutputStream& rwFlush(RWWCharOutputStream& stream)
{
    stream.flush();
    return stream;
}

/**
 * \relates RWWCharOutputStream
 *
 * Manipulator that writes an end-of-line control character to the stream.
 *
 * \param stream
 * A wide character output stream.
 */
inline RWWCharOutputStream& rwEndl(RWWCharOutputStream& stream)
{
    stream.write(L'\n');
    return stream;
}

/**
 * \relates RWWCharOutputStream
 *
 * Manipulator that writes an end-of-string character to the stream.
 *
 * \param stream
 * A wide character output stream.
 */
inline RWWCharOutputStream& rwEnds(RWWCharOutputStream& stream)
{
    stream.write(L'\0');
    return stream;
}

#endif // rw_stream_RWWCharOutputStream_h_
