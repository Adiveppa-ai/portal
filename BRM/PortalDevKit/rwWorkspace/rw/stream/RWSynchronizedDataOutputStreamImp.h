#ifndef rw_stream_RWSynchronizedDataOutputStreamImp_h_
#define rw_stream_RWSynchronizedDataOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWSynchronizedDataOutputStreamImp.h#1 $
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

#include <rw/stream/RWExternalStreamException.h>
#include <rw/stream/RWFilteredDataOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/sync/RWMutexLock.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Implementation of a simple lock stream that can be used with a data
 * output stream.
 *
 * The class RWSynchronizedDataOutputStreamImp implements a simple lock
 * stream that can be used with data output stream. The stream locks its
 * internal synchronization mechanism before forwarding output requests to
 * its associated sink stream, and then unlocks the internal synchronization
 * mechanism upon completion. The stream's internal synchronization
 * mechanism is locked using a guard object, ensuring its proper release in
 * the event an exception is thrown.
 */
class RW_STREAM_GLOBAL RWSynchronizedDataOutputStreamImp : public RWFilteredDataOutputStreamImp
{

public:

    /**
     * Constructs an RWSynchronizedDataOutputStreamImp instance that uses
     * \a sinkStream as its sink of data, and returns a handle to it. Throws
     * no exceptions.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of data.
     */
    static RWDataOutputStream make(const RWDataOutputStream& sinkStream)
    {
        return RWDataOutputStream(new RWSynchronizedDataOutputStreamImp(sinkStream));
    }

    //--Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWSynchronizedDataOutputStreamImp();

    //--Calls 'close()' on the next processing stream.
    // Documented in base class.
    virtual void close();

    //--Calls 'flush()' on the next processing stream.
    // Documented in base class.
    virtual void flush();

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * output operation. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * Returns \c true to indicate that an output operation failed to
     * generate the desired data. Throws no exceptions.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    virtual bool isGood() const;

    /**
     * Acquires the stream's internal synchronization mechanism. The
     * acquire() member function returns a handle to the next processing
     * stream.
     */
    virtual RWDataOutputStream acquire();

    /**
     * Releases the stream's internal synchronization mechanism.
     */
    virtual void release();

    //--Forward writing a single 'bool' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'bool' to be written.
    //--
    // Documented in base class.
    virtual void putBool(bool value);

    //--Forward writing a single 'char' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'char' to be written.
    //--
    // Documented in base class.
    virtual void putChar(char value);

    //--Forward writing a single 'unsigned char' value to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'unsigned char' to be written.
    //--
    // Documented in base class.
    virtual void putUnsignedChar(unsigned char value);

    //--Forward writing a single 'signed char' value to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'signed char' to be written.
    //--
    // Documented in base class.
    virtual void putSignedChar(signed char value);

    //--Forward writing a single 'short' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'short' to be written.
    //--
    // Documented in base class.
    virtual void putShort(short value);

    //--Forward writing a single 'unsigned short' value to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'unsigned short' to be written.
    //--
    // Documented in base class.
    virtual void putUnsignedShort(unsigned short value);

    //--Forward writing a single 'int' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'int' to be written.
    //--
    // Documented in base class.
    virtual void putInt(int value);

    //--Forward writing a single 'unsigned int' value to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'unsigned int' to be written.
    //--
    // Documented in base class.
    virtual void putUnsignedInt(unsigned int value);

    //--Forward writing a single 'long' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'long' to be written.
    //--
    // Documented in base class.
    virtual void putLong(long value);

    //--Forward writing a single 'unsigned long' value to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'unsigned long' to be written.
    //--
    // Documented in base class.
    virtual void putUnsignedLong(unsigned long value);

    //--Forward writing a single 'float' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'float' to be written.
    //--
    // Documented in base class.
    virtual void putFloat(float value);

    //--Forward writing a single 'double' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'double' to be written.
    //--
    // Documented in base class.
    virtual void putDouble(double value);

    //--Forward writing a single 'wchar_t' value to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'wchar_t' to be written.
    //--
    // Documented in base class.
    virtual void putWchar_t(wchar_t value);

#if !defined(RW_NO_LONG_LONG)

    // Documented in base class
    virtual void putUnsignedLongLong(unsigned long long value);

    //--Forward writing a single 'long long' value to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'long long' to be written.
    //--
    // Documented in base class.
    virtual void putLongLong(long long value);
#endif

#ifndef RW_NO_LONG_DOUBLE

    //--Forward writing a single 'long double' value to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'long double' to be written.
    //--
    // Documented in base class.
    virtual void putLongDouble(long double value);
#endif

    //--Forward writing a single narrow character to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The narrow character to be written.
    //--
    // Documented in base class.
    virtual void putCharacter(char value);

    //--Forward writing a single wide character to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The wide character to be written.
    //--
    // Documented in base class.
    virtual void putWCharacter(wchar_t value);

    //--Forward writing a single unicode character to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The unicode character to be written.
    //--
    // Documented in base class.
    virtual void putUCharacter(RWUChar value);

    //--Forward writing a single size_t character to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'value': The size_t character to be written.
    //--
    // Documented in base class
    virtual void putSizeT(size_t value);

    //--Forward writing an array of 'bool' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putBools(const bool* arrayPt, RWSize count);

    //--Forward writing an array of 'char' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putChars(const char* arrayPt, RWSize count);

    //--Forward writing an array of 'unsigned char' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putUnsignedChars(const unsigned char* arrayPt, RWSize count);

    //--Forward writing an array of 'signed char' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putSignedChars(const signed char* arrayPt, RWSize count);

    //--Forward writing an array of 'short' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putShorts(const short* arrayPt, RWSize count);

    //--Forward writing an array of 'unsigned short' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putUnsignedShorts(const unsigned short* arrayPt, RWSize count);

    //--Forward writing an array of 'int' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putInts(const int* arrayPt, RWSize count);

    //--Forward writing an array of 'unsigned int' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putUnsignedInts(const unsigned int* arrayPt, RWSize count);

    //--Forward writing an array of 'long' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putLongs(const long* arrayPt, RWSize count);

    //--Forward writing an array of 'unsigned long' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putUnsignedLongs(const unsigned long* arrayPt, RWSize count);

    //--Forward writing an array of 'float' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putFloats(const float* arrayPt, RWSize count);

    //--Forward writing an array of 'double' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putDoubles(const double* arrayPt, RWSize count);

    //--Forward writing an array of wchar_t value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putWchar_ts(const wchar_t* arrayPt, RWSize count);

#if !defined(RW_NO_LONG_LONG)

    //--Forward writing an array of 'long long' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putLongLongs(const long long* arrayPt, RWSize count);

    virtual void putUnsignedLongLongs(const unsigned long long* arrayPt, RWSize count);
#endif

#ifndef RW_NO_LONG_DOUBLE

    //--Forward writing an array of 'long double' value(s) to the next
    //-- processing stream.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array.
    //--
    //--  'count': The number of elements(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putLongDoubles(const long double* arrayPt, RWSize count);
#endif

    //--Forward writing a narrow character string, including embedded nulls,
    //--starting at 'string' to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'string': A pointer to the narrow string's first character.
    //--
    //--  'count': The number of narrow character(s) to be written
    //--   to the stream.
    //--
    // Documented in base class.
    virtual void putString(const char* string, RWSize count);

    //--Forward writing a wide character string, including embedded nulls,
    //--starting at 'wstring' to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'wstring': A pointer to the string's first wide character.
    //--
    //--  'count': The number of wide character(s) to be written to the stream.
    //--
    // Documented in base class.
    virtual void putWString(const wchar_t* wstring, RWSize count);

    //--Forward writing a unicode character string, including embedded nulls,
    //--starting at 'ustring' to the next processing stream.
    //--
    //--Parameters:
    //--
    //--  'ustring': A pointer to the string's first unicode character.
    //--
    //--  'count': The number of unicode character(s) to be written
    //--   to the stream.
    //--
    // Documented in base class.
    virtual void putUString(const RWUChar* ustring, RWSize count);

protected:

    //--  Throws no exceptions.
    /**
     * Initializes the reference to the data output stream that will be used
     * as the sink of data.
     *
     * \param sinkStream
     * The data output stream that will serve as the sink of elements.
     */
    RWSynchronizedDataOutputStreamImp(const RWDataOutputStream& sinkStream);

    // RWMutexLock should come from the synchronization package
    /**
     * Returns the stream's internal synchronization mechanism. Throws no
     * exceptions.
     */
    inline RWMutexLock& getStreamMutex();

    // RWMutexLock should come from the synchronization package
    /**
     * \copydoc getStreamMutex()
     */
    inline RWMutexLock& getStreamMutex() const;

private:

    // this should come from the synchronization package
    RWMutexLock mutex_;

};

inline RWMutexLock&
RWSynchronizedDataOutputStreamImp::getStreamMutex()
{
    return RW_EXPOSE(mutex_);
}

inline RWMutexLock&
RWSynchronizedDataOutputStreamImp::getStreamMutex() const
{
    return RW_EXPOSE(const_cast<RWMutexLock&>(mutex_));
}

#endif // rw_stream_RWSynchronizedDataOutputStreamImp_h_
