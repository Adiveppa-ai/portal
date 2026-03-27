#ifndef rw_stream_RWWCharInputStream_h_
#define rw_stream_RWWCharInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWWCharInputStream.h#1 $
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

#include <rw/stream/RWWCharInputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredWCharInputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all the wide character input stream implementation
 * classes.
 *
 * Handle class for all the wide character input stream implementation
 * classes. Implements the handle idiom from the handle-body pattern.
 */
class RWWCharInputStream : public RWHandleBase
{

public:

    typedef wchar_t element_type;

    //-- Throws no exceptions.
    /**
     * Constructor.
     */
    explicit RWWCharInputStream(RWWCharInputStreamImp* ptr)
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
    RWWCharInputStream(const RWWCharInputStream& handle)
        : RWHandleBase(handle)
    { }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A wide character stream handle used to initialize this handle.
     */
    RWWCharInputStream& operator=(const RWWCharInputStream& handle)
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
    RWWCharInputStream& operator>>(RWWCharInputStream & (*pf)(RWWCharInputStream&))
    {
        return pf(*this);
    }

    /**
     * \copydoc operator>>()
     */
    RWWCharInputStream operator>>(RWWCharInputStream(*pf)(RWWCharInputStream&))
    {
        return pf(*this);
    }

    /**
     * Reads a single wide character from the stream.
     *
     * \param wcharValue
     * The wide character to be read from the stream.
     */
    RWWCharInputStream& operator>>(wchar_t& wcharValue)
    {
        wcharValue = this->read();
        return *this;
    }

    /**
     * Reads a single wide character from the stream.
     */
    wchar_t read()
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).read();
    }

    /**
     * Reads an array of wide characters from the stream. The array must be
     * pre-allocated to contain at least \a numWChars elements. The function
     * returns the actual number of wide characters extracted from the
     * stream.
     *
     * \param wcharArray
     * A pointer to the first element of the array.
     *
     * \param numWChars
     * The number of wide characters to be read from the stream.
     */
    RWSize read(wchar_t* wcharArray, RWSize numWChars)
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).read(wcharArray, numWChars);
    }

    /**
     * Reads wide characters from the stream until the last wide character
     * read is equal to \a delim, or \a maxSize wide characters have been
     * read, or the end of the input sequence is reached. The wide
     * characters read are stored in \a wcharArray. The function returns the
     * actual number of wide characters read from the stream.
     *
     * \param wcharArray
     * A pointer to the array receiving the wide characters extracted from
     * the stream.
     *
     * \param maxSize
     * The maximum number of wide characters to be read.
     *
     * \param delim
     * The wide character used as a delimiter.
     */
    RWSize readUntil(wchar_t* wcharArray, RWSize maxSize, wchar_t delim)
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).readUntil(wcharArray, maxSize, delim);
    }

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWWCharInputStreamImp&>(this->body()).close();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * input operation, such as an irrecoverable read error from a file.
     * Throws no exceptions.
     */
    bool isBad() const
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an input operation failed to read
     * the expected data. Throws no exceptions.
     */
    bool isFail() const
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    bool isGood() const
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).isGood();
    }

    /**
     * Returns \c true to indicate that an input operation reached the end
     * of an input sequence. Throws no exceptions.
     */
    bool isEof() const
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).isEof();
    }

    /**
     * Returns the number of wide characters that can be read from the
     * stream without blocking. Throws no exceptions.
     */
    RWSize available() const
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).available();
    }

    /**
     * Skips \a numUnits wide characters from the input sequence if
     * possible. The function returns the actual number of wide characters
     * skipped, which can be any value between \c 0 and \a numUnits.
     *
     * \param numUnits
     * The number of wide characters to be skipped.
     */
    RWSize skip(RWSize numUnits)
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).skip(numUnits);
    }

private:

    //-- Acquires the synchronization mechanism provided by a stream concrete
    //-- implementation. The 'acquire()' member function returns a handle to the
    //-- wide character stream that should be used for input operation after acquiring
    //-- the synchronization mechanism. This function is only used by instance of
    //-- class 'RWGuardedWCharInputStreamImp'.
    RWWCharInputStream acquire()
    {
        return static_cast<RWWCharInputStreamImp&>(this->body()).acquire();
    }

    //-- Releases the synchronization mechanism provided by a stream concrete
    //-- implementation. This function is only used by instance of
    //-- class 'RWGuardedWCharInputStreamImp'.
    void release()
    {
        static_cast<RWWCharInputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWWCharInputStream, RWFilteredWCharInputStreamImp>;
};

/**
 * \relates RWWCharInputStream
 *
 * Manipulator that discards a narrow character from a stream input
 * sequence.
 *
 * \param stream
 * The wide character stream.
 */
inline RWWCharInputStream& rwDisc(RWWCharInputStream& stream)
{
    stream.read();
    return stream;
}

#endif // rw_stream_RWWCharInputStream_h_
