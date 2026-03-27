#ifndef rw_stream_RWByteInputStream_h_
#define rw_stream_RWByteInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWByteInputStream.h#1 $
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

#include <rw/stream/RWByteInputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

// forward declaration
template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredByteInputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all binary input stream implementation classes.
 *
 * Handle class for all the binary input stream implementation classes.
 * Implement the handle idiom from the handle-body pattern.
 */
class RWByteInputStream : public RWHandleBase
{

public:

    typedef RWByte element_type;

    /**
     * Constructor.
     */
    explicit RWByteInputStream(RWByteInputStreamImp* ptr)
        : RWHandleBase(ptr)
    { }

    /**
     * Copy constructor. Throws no exceptions.
     *
     * \param handle
     * A binary stream handle used to initialize the newly created handle.
     */
    RWByteInputStream(const RWByteInputStream& handle)
        : RWHandleBase(handle)
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A binary stream handle used to initialize this handle.
     */
    RWByteInputStream& operator=(const RWByteInputStream& handle)
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
    RWByteInputStream& operator>>(RWByteInputStream & (*pf)(RWByteInputStream&))
    {
        return pf(*this);
    }

    /**
     * Extractor executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWByteInputStream operator>>(RWByteInputStream(*pf)(RWByteInputStream&))
    {
        return pf(*this);
    }

    /**
     * Reads a single byte from the stream.
     *
     * \param byteValue
     * The byte to be read from the stream.
     */
    RWByteInputStream& operator>>(RWByte& byteValue)
    {
        byteValue = this->read();
        return *this;
    }

    /**
     * Reads a single byte from the stream.
     */
    RWByte read()
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).read();
    }

    /**
     * Reads an array of bytes from the stream. The array must be
     * pre-allocated to contain at least \a numBytes elements. The function
     * returns the actual number of bytes extracted from the stream.
     *
     * \param byteArray
     * A pointer to the first element of the array.
     *
     * \param numBytes
     * The number of bytes to be read from the stream.
     */
    RWSize read(RWByte* byteArray, RWSize numBytes)
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).read(byteArray, numBytes);
    }

    /**
     * Reads bytes from the stream until the last byte read is equal to
     * \a delim, or \a maxSize bytes have been read, or the end of the input
     * sequence is reached. The bytes read are stored in \a byteArray. The
     * function returns the actual number of bytes read from the stream.
     *
     * \param byteArray
     * A pointer to the array receiving the bytes extracted from the stream.
     *
     * \param maxSize
     * The maximum number of bytes to be read.
     *
     * \param delim
     * The byte value used as a delimiter.
     */
    RWSize readUntil(RWByte* byteArray, RWSize maxSize, RWByte delim)
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).readUntil(byteArray, maxSize, delim);
    }

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWByteInputStreamImp&>(this->body()).close();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * input or output operation, such as an irrecoverable read error from a
     * file.
     */
    bool isBad() const
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).isBad();
    }

    //--Returns 'true' to indicate that an input operation failed to read the expected
    //--data, or that an output operation failed to generate the desired data.
    /**
     * Returns \c true to indicate that an input operation failed to read
     * the expected data.
     */
    bool isFail() const
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state.
     */
    bool isGood() const
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).isGood();
    }

    /**
     * Returns \c true to indicate that an input operation reached the end
     * of an input sequence.
     */
    bool isEof() const
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).isEof();
    }

    /**
     * Returns the number of bytes that can be read from the stream without
     * blocking.
     */
    RWSize available() const
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).available();
    }

    /**
     * Skips \a numUnits bytes from the input sequence if possible. The
     * function returns the actual number of bytes skipped, which can be any
     * value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of bytes to be skipped.
     */
    RWSize skip(RWSize numUnits)
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).skip(numUnits);
    }

private:

    //--Acquires the synchronization mechanism provided by a stream concrete
    //--implementation. The 'acquire()' member function returns a handle to the
    //--binary stream that should be used for input operation after acquiring
    //--the synchronization mechanism. This function is only used by instance of
    //--class 'RWGuardedByteInputStreamImp'.
    RWByteInputStream acquire()
    {
        return static_cast<RWByteInputStreamImp&>(this->body()).acquire();
    }

    //--Releases the synchronization mechanism provided by a stream concrete
    //--implementation. This function is only used by instance of
    //--class 'RWGuardedByteInputStreamImp'.
    void release()
    {
        static_cast<RWByteInputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWByteInputStream, RWFilteredByteInputStreamImp>;
};

/**
 * \relates RWByteInputStream
 *
 * Manipulator that discards a byte from a stream input sequence.
 *
 * \param stream
 * The binary stream.
 */
inline RWByteInputStream& rwDisc(RWByteInputStream& stream)
{
    stream.read();
    return stream;
}

#endif // rw_stream_RWByteInputStream_h_
