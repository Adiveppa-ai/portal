#ifndef rw_stream_RWCharOutputStream_h_
#define rw_stream_RWCharOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWCharOutputStream.h#1 $
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

#include <rw/stream/RWCharOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

// forward declaration
class RWCString;
template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredCharOutputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all narrow character output stream implementation
 * classes.
 *
 * Handle class for all the narrow character output stream implementation
 * classes. Implements the handle idiom from the handle-body pattern.
 */
class RW_STREAM_SYMBOLIC RWCharOutputStream : public RWHandleBase
{

public:

    typedef char element_type;

    /**
     * Constructor.
     */
    explicit RWCharOutputStream(RWCharOutputStreamImp* ptr)
        : RWHandleBase(ptr)
    { }

    /**
     * Copy constructor.
     *
     * \param handle
     * A narrow stream handle used to initialize the newly created handle.
     */
    RWCharOutputStream(const RWCharOutputStream& handle)
        : RWHandleBase(handle)
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A narrow stream handle used to initialize this handle.
     */
    RWCharOutputStream& operator=(const RWCharOutputStream& handle)
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
    RWCharOutputStream& operator<<(RWCharOutputStream & (*pf)(RWCharOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Inserter executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWCharOutputStream operator<<(RWCharOutputStream(*pf)(RWCharOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Writes a single narrow character to the stream.
     *
     * \param charValue
     * The narrow character to be written to the stream.
     */
    RWCharOutputStream& operator<<(char charValue)
    {
        this->write(charValue);
        return *this;
    }

    /**
     * Writes a narrow string to the stream.
     *
     * \param string
     * The narrow string object to be written to the stream.
     */
    RWCharOutputStream& operator<<(const RWCString& string)
    {
        this->write(string);
        return *this;
    }

    /**
     * Writes a single narrow character to the stream.
     *
     * \param charValue
     * The narrow character to be written to the stream.
     */
    void write(char charValue)
    {
        static_cast<RWCharOutputStreamImp&>(this->body()).write(charValue);
    }

    /**
     * Writes an array of narrow characters to the stream.
     *
     * \param charArray
     * A pointer to the first element of the array.
     *
     * \param numChars
     * The number of narrow characters to be written to the stream.
     */
    void write(const char* charArray, RWSize numChars)
    {
        static_cast<RWCharOutputStreamImp&>(this->body()).write(charArray, numChars);
    }

    /**
     * Writes a single narrow string to the stream.
     *
     * \param string
     * The narrow string object to be written to the stream.
     */
    void write(const RWCString& string);

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWCharOutputStreamImp&>(this->body()).close();
    }

    /**
     * Flushes the stream.
     */
    void flush()
    {
        static_cast<RWCharOutputStreamImp&>(this->body()).flush();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * output operation.
     */
    bool isBad() const
    {
        return static_cast<RWCharOutputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an output operation failed to
     * generate the desired data.
     */
    bool isFail() const
    {
        return static_cast<RWCharOutputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state.
     */
    bool isGood() const
    {
        return static_cast<RWCharOutputStreamImp&>(this->body()).isGood();
    }

private:

    //--Acquires the synchronization mechanism provided by a stream concrete
    //--implementation. The acquire member function returns a handle to the narrow
    //--character stream that should be used for output operation after acquiring
    //--the synchronization mechanism. This function is only used by instance of
    //--class 'RWGuardedCharOutputStreamImp'.
    RWCharOutputStream acquire()
    {
        return static_cast<RWCharOutputStreamImp&>(this->body()).acquire();
    }

    //--Releases the synchronization mechanism provided by a stream concrete
    //--implementation. This function is only used by instance of
    //--class 'RWGuardedCharOutputStreamImp'.
    void release()
    {
        static_cast<RWCharOutputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWCharOutputStream, RWFilteredCharOutputStreamImp>;
};

/**
 * \relates RWCharOutputStream
 * Manipulator that flushes a narrow character output stream.
 *
 * \param stream
 * The narrow stream to be flushed.
 */
inline RWCharOutputStream& rwFlush(RWCharOutputStream& stream)
{
    stream.flush();
    return stream;
}

/**
 * \relates RWCharOutputStream
 * Manipulator that writes an end of line control character to the stream.
 *
 * \param stream
 * A narrow character output stream.
 */
inline RWCharOutputStream& rwEndl(RWCharOutputStream& stream)
{
    stream.write('\n');
    return stream;
}

/**
 * \relates RWCharOutputStream
 * Manipulator that writes an end of string character to the stream.
 *
 * \param stream
 * A narrow character output stream.
 */
inline RWCharOutputStream& rwEnds(RWCharOutputStream& stream)
{
    stream.write('\0');
    return stream;
}

#endif // rw_stream_RWCharOutputStream_h_
