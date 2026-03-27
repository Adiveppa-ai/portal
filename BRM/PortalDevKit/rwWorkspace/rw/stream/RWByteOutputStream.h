#ifndef rw_stream_RWByteOutputStream_h_
#define rw_stream_RWByteOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWByteOutputStream.h#1 $
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

#include <rw/stream/RWByteOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

// forward declaration
template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredByteOutputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all binary output stream implementation classes.
 *
 * Handle class for all the binary output stream implementation classes.
 * Implements the handle idiom from the handle-body pattern.
 */
class RWByteOutputStream : public RWHandleBase
{

public:

    typedef RWByte element_type;

    /**
     * Constructor.
     */
    explicit RWByteOutputStream(RWByteOutputStreamImp* ptr)
        : RWHandleBase(ptr)
    { }

    /**
     * Copy constructor.
     *
     * \param handle
     * A binary stream handle used to initialize the newly created handle.
     *
     * Exception none.
     */
    RWByteOutputStream(const RWByteOutputStream& handle)
        : RWHandleBase(handle)
    {
        ;
    }

    /**
     * Assignment operator.
     *
     * \param handle
     * A binary stream handle used to initialize this handle.
     *
     * Exception none.
     */
    RWByteOutputStream& operator=(const RWByteOutputStream& handle)
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
    RWByteOutputStream& operator<<(RWByteOutputStream & (*pf)(RWByteOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Inserter executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWByteOutputStream operator<<(RWByteOutputStream(*pf)(RWByteOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Writes a single byte to the stream.
     *
     * \param byteValue
     * The byte to be written to the stream.
     */
    RWByteOutputStream& operator<<(RWByte byteValue)
    {
        this->write(byteValue);
        return *this;
    }

    /**
     * Writes a single byte to the stream.
     *
     * \param byteValue
     * The byte to be written to the stream.
     */
    void write(RWByte byteValue)
    {
        static_cast<RWByteOutputStreamImp&>(this->body()).write(byteValue);
    }

    /**
     * Writes an array of bytes to the stream.
     *
     * \param byteArray
     * A pointer to the first element of the array.
     *
     * \param numBytes
     * The number of bytes to be written to the stream.
     */
    void write(const RWByte* byteArray, RWSize numBytes)
    {
        static_cast<RWByteOutputStreamImp&>(this->body()).write(byteArray, numBytes);
    }

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWByteOutputStreamImp&>(this->body()).close();
    }

    /**
     * Flushes the stream.
     */
    void flush()
    {
        static_cast<RWByteOutputStreamImp&>(this->body()).flush();
    }

    //--Returns 'true' to indicate a loss of integrity resulting from an input or output
    //--operation, such as an irrecoverable read error from a file.
    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * output operation.
     */
    bool isBad() const
    {
        return static_cast<RWByteOutputStreamImp&>(this->body()).isBad();
    }

    //--Returns 'true' to indicate that an input operation failed to read the expected
    //--data, or that an output operation failed to generate the desired data.
    /**
     * Returns \c true to indicate that an output operation failed to
     * generate the desired data.
     */
    bool isFail() const
    {
        return static_cast<RWByteOutputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state.
     */
    bool isGood() const
    {
        return static_cast<RWByteOutputStreamImp&>(this->body()).isGood();
    }

private:

    //--Acquires the synchronization mechanism provided by a stream concrete
    //--implementation. The 'acquire()' member function returns a handle to the
    //--binary stream that should be used for output operation after acquiring
    //--the synchronization mechanism. This function is only used by instance of
    //--class 'RWGuardedByteOutputStreamImp'.
    RWByteOutputStream acquire()
    {
        return static_cast<RWByteOutputStreamImp&>(this->body()).acquire();
    }

    //--Releases the synchronization mechanism provided by a stream concrete
    //--implementation. This function is only used by instance of
    //--class 'RWGuardedByteOutputStreamImp'.
    void release()
    {
        static_cast<RWByteOutputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWByteOutputStream, RWFilteredByteOutputStreamImp>;
};

/**
 * \relates RWByteOutputStream
 *
 * Manipulator that flushes a binary output stream.
 *
 * \param stream
 * The binary stream to be flushed.
 */
inline RWByteOutputStream& rwFlush(RWByteOutputStream& stream)
{
    stream.flush();
    return stream;
}

#endif // rw_stream_RWByteOutputStream_h_
