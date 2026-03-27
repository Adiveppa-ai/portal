#ifndef rw_stream_RWCharInputStream_h_
#define rw_stream_RWCharInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWCharInputStream.h#1 $
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

#include <rw/stream/RWCharInputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

// forward declaration
class RWCString;
template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredCharInputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all narrow character input stream implementation
 * classes.
 *
 * Handle class for all the narrow character input stream implementation
 * classes. Implements the handle idiom from the handle-body pattern.
 */
class RWCharInputStream : public RWHandleBase
{

public:

    typedef char element_type;

    /**
     * Constructor.
     */
    explicit RWCharInputStream(RWCharInputStreamImp* ptr)
        : RWHandleBase(ptr)
    { }

    /**
     * Copy constructor.
     *
     * \param handle
     * A narrow stream handle used to initialize the newly created handle.
     */
    RWCharInputStream(const RWCharInputStream& handle)
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
    RWCharInputStream& operator=(const RWCharInputStream& handle)
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
    RWCharInputStream& operator>>(RWCharInputStream & (*pf)(RWCharInputStream&))
    {
        return pf(*this);
    }

    /**
     * Extractor executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWCharInputStream operator>>(RWCharInputStream(*pf)(RWCharInputStream&))
    {
        return pf(*this);
    }

    /**
     * Reads a single narrow character from the stream.
     *
     * \param charValue
     * The narrow character to be read from the stream.
     */
    RWCharInputStream& operator>>(char& charValue)
    {
        charValue = this->read();
        return *this;
    }

    /**
     * Reads a single narrow character from the stream.
     */
    char read()
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).read();
    }

    /**
     * Reads an array of narrow characters from the stream. The array must
     * be pre-allocated to contain at list \a numChars elements. The
     * function returns the actual number of narrow characters read from the
     * stream.
     *
     * \param charArray
     * A pointer to the first element of the array.
     *
     * \param numChars
     * The number of narrow characters to be read from the stream.
     */
    RWSize read(char* charArray, RWSize numChars)
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).read(charArray, numChars);
    }

    /**
     * Reads narrow character(s) from the attached source stream until the
     * last character read is equal to \a delim, or the end of the input
     * sequence is reached. The narrow character(s) read are stored in a
     * narrow string object.
     *
     * \param string
     * A string object receiving the narrow character(s) extracted from the
     * stream.
     *
     * \param delim
     * The narrow character used as a delimiter.
     */
    void readStringUntil(RWCString& string, char delim = ' ')
    {
        static_cast<RWCharInputStreamImp&>(this->body()).readStringUntil(string, delim);
    }

    /**
     * Reads narrow character(s) from the attached source stream until the
     * last narrow character read is equal to \a delim, or \a maxSize narrow
     * character(s) have been read, or the end of the input sequence is
     * reached. The narrow character(s) read are stored in \a charArray. The
     * function returns the actual number of narrow character(s) read from
     * the stream.
     *
     * \param charArray
     * A pointer to the array receiving the narrow character(s) extracted
     * from the stream.
     *
     * \param maxSize
     * The maximum number of narrow character(s) to be read.
     *
     * \param delim
     * The narrow character value used as a delimiter.
     */
    RWSize readUntil(char* charArray, RWSize maxSize, char delim)
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).readUntil(charArray, maxSize, delim);
    }

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWCharInputStreamImp&>(this->body()).close();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * input, such as an irrecoverable read error from a file.
     */
    bool isBad() const
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an input operation failed to read
     * the expected data.
     */
    bool isFail() const
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state.
     */
    bool isGood() const
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).isGood();
    }

    /**
     * Returns \c true to indicate that an input operation reached the end
     * of an input sequence.
     */
    bool isEof() const
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).isEof();
    }

    /**
     * Returns the number of narrow characters that can be read from the
     * attached source stream without blocking. Throws no exceptions.
     */
    RWSize available() const
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).available();
    }

    /**
     * Skips \a numUnits narrow characters from the input sequence if
     * possible. The function returns the actual number of narrow characters
     * skipped, which can be any value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of narrow characters to be skipped.
     */
    RWSize skip(RWSize numUnits)
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).skip(numUnits);
    }

private:

    //--Acquires the synchronization mechanism provided by a stream concrete
    //--implementation. The 'acquire()' member function returns a handle to the narrow
    //--character stream that should be used for input operation after acquiring
    //--the synchronization mechanism. This function is only used by instance of
    //--class 'RWGuardedCharInputStreamImp'.
    RWCharInputStream acquire()
    {
        return static_cast<RWCharInputStreamImp&>(this->body()).acquire();
    }

    //--Releases the synchronization mechanism provided by a stream concrete
    //--implementation. This function is only used by instance of
    //--class 'RWGuardedCharInputStreamImp'.
    void release()
    {
        static_cast<RWCharInputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWCharInputStream, RWFilteredCharInputStreamImp>;
};

/**
 * \relates RWCharInputStream
 * Manipulator that discards a narrow character from a stream input
 * sequence.
 *
 * \param stream
 * The narrow character stream.
 */
inline RWCharInputStream& rwDisc(RWCharInputStream& stream)
{
    stream.read();
    return stream;
}

#endif // rw_stream_RWCharInputStream_h_
