#ifndef rw_stream_RWFilteredDataOutputStreamImp_h_
#define rw_stream_RWFilteredDataOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWFilteredDataOutputStreamImp.h#1 $
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

#include <rw/stream/RWDataOutputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the filtered data output stream
 * implementation classes.
 *
 * Abstract base class for all the filtered data output stream
 * implementation classes. A filtered output stream, is a stream that
 * process elements, and then forwards the result to another stream for
 * further processing. Implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWFilteredDataOutputStreamImp : public RWDataOutputStreamImp
{

public:

    /**
     * Destructor. Throws no exceptions.
     */
    virtual ~RWFilteredDataOutputStreamImp();

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
     * Forward writing of a single \c bool value to the next processing
     * stream.
     *
     * \param value
     * The \c bool value to be written.
     */
    virtual void putBool(bool value);

    /**
     * Forward writing of a single \c char value to the next processing
     * stream.
     *
     * \param value
     * The \c char value to be written.
     */
    virtual void putChar(char value);

    /**
     * Forward writing of a single <tt>unsigned char</tt> value to the next
     * processing stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be written.
     */
    virtual void putUnsignedChar(unsigned char value);

    /**
     * Forward writing of a single <tt>signed char</tt> value to the next
     * processing stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be written.
     */
    virtual void putSignedChar(signed char value);

    /**
     * Forward writing of a single \c short value to the next processing
     * stream.
     *
     * \param value
     * The \c short value to be written.
     */
    virtual void putShort(short value);

    /**
     * Forward writing of a single <tt>unsigned short</tt> value to the next
     * processing stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be written.
     */
    virtual void putUnsignedShort(unsigned short value);

    /**
     * Forward writing of a single \c int value to the next processing
     * stream.
     *
     * \param value
     * The \c int value to be written.
     */
    virtual void putInt(int value);

    /**
     * Forward writing of a single <tt>unsigned int</tt> value to the next
     * processing stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be written.
     */
    virtual void putUnsignedInt(unsigned int value);

    /**
     * Forward writing of a single \c long value to the next processing
     * stream.
     *
     * \param value
     * The \c long value to be written.
     */
    virtual void putLong(long value);

    /**
     * Forward writing of a single <tt>unsigned long</tt> value to the next
     * processing stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be written.
     */
    virtual void putUnsignedLong(unsigned long value);

    /**
     * Forward writing of a single \c float value to the next processing
     * stream.
     *
     * \param value
     * The \c float value to be written.
     */
    virtual void putFloat(float value);

    /**
     * Forward writing of a single \c double value to the next processing
     * stream.
     *
     * \param value
     * The \c double value to be written.
     */
    virtual void putDouble(double value);

    /**
     * Forward writing of a single \c wchar_t value to the next processing
     * stream.
     *
     * \param value
     * The \c wchar_t value to be written.
     */
    virtual void putWchar_t(wchar_t value);

#if !defined(RW_NO_LONG_LONG)
    /**
     * Forward writing of a single <tt>long long</tt> value to the next
     * processing stream.
     *
     * \param value
     * The <tt>long long</tt> value to be written.
     */
    virtual void putLongLong(long long value);

    /**
     * Forward writing of a single <tt>unsigned long long</tt> value to the
     * next processing stream.
     *
     * \param value
     * The <tt>unsigned long long</tt> value to be written.
     */
    virtual void putUnsignedLongLong(unsigned long long value);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Forward writing of a single <tt>long double</tt> value to the next
     * processing stream.
     *
     * \param value
     * The <tt>long double</tt> value to be written.
     */
    virtual void putLongDouble(long double value);
#endif

    /**
     * Forwards the writing of a single narrow character to the next
     * processing stream.
     *
     * \param value
     * The narrow character to be written.
     */
    virtual void putCharacter(char value);

    /**
     * Forward writing of a single wide character to the next processing
     * stream.
     *
     * \param value
     * The wide character to be written.
     */
    virtual void putWCharacter(wchar_t value);

    /**
     * Forwards the writing of a single UTF-16 character to the next
     * processing stream.
     *
     * \param value
     * The unicode character to be written.
     */
    virtual void putUCharacter(RWUChar value);

    /**
     * Forwards the writing of a single \c size_t character to the next
     * processing stream.
     *
     * \param value
     * The \c size_t character to be written.
     */
    virtual void putSizeT(size_t value);

    /**
     * Forward writing of an array of \c bool values to the next processing
     * stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putBools(const bool* arrayPt, RWSize count);

    /**
     * Forward writing of an array of \c char values to the next processing
     * stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putChars(const char* arrayPt, RWSize count);

    /**
     * Forward writing of an array of <tt>unsigned char</tt> values to the
     * next processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedChars(const unsigned char* arrayPt, RWSize count);

    /**
     * Forward writing of an array of <tt>signed char</tt> values to the
     * next processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putSignedChars(const signed char* arrayPt, RWSize count);

    /**
     * Forward writing of an array of \c short values to the next processing
     * stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putShorts(const short* arrayPt, RWSize count);

    /**
     * Forward writing of an array of <tt>unsigned short</tt> values to the
     * next processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedShorts(const unsigned short* arrayPt, RWSize count);

    /**
     * Forward writing of an array of \c int values to the next processing
     * stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putInts(const int* arrayPt, RWSize count);

    /**
     * Forward writing of an array of <tt>unsigned int</tt> values to the
     * next processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedInts(const unsigned int* arrayPt, RWSize count);

    /**
     * Forward writing of an array of \c long values to the next processing
     * stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongs(const long* arrayPt, RWSize count);

    /**
     * Forward writing of an array of <tt>unsigned long</tt> values to the
     * next processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedLongs(const unsigned long* arrayPt, RWSize count);

    /**
     * Forward writing of an array of \c float values to the next processing
     * stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putFloats(const float* arrayPt, RWSize count);

    /**
     * Forward writing of an array of \c double values to the next
     * processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putDoubles(const double* arrayPt, RWSize count);

    /**
     * Forward writing of an array of \c wchar_t values to the next
     * processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putWchar_ts(const wchar_t* arrayPt, RWSize count);

#if !defined(RW_NO_LONG_LONG)
    /**
     * Forward writing of an array of <tt>long long</tt> values to the next
     * processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongLongs(const long long* arrayPt, RWSize count);

    /**
     * Forward writing of an array of <tt>unsigned long long</tt> values to
     * the next processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedLongLongs(const unsigned long long* arrayPt, RWSize count);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Forward writing of an array of <tt>long double</tt> values to the
     * next processing stream.
     *
     * \param arrayPt
     * A pointer to the first element of the array.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongDoubles(const long double* arrayPt, RWSize count);
#endif

    /**
     * Forwards the writing of a narrow character string, including embedded
     * nulls, starting at \a string to the next processing stream.
     *
     * \param string
     * A pointer to the narrow string's first character.
     *
     * \param count
     * The number of narrow character(s) to be written to the stream.
     */
    virtual void putString(const char* string, RWSize count);

    /**
     * Forwards the writing of a wide character string, including embedded
     * nulls, starting at \a wstring to the next processing stream.
     *
     * \param wstring
     * A pointer to the string's first wide character.
     *
     * \param count
     * The number of wide character(s) to be written to the stream.
     */
    virtual void putWString(const wchar_t* wstring, RWSize count);

    /**
     * Forwards the writing of a UTF-16 character string, including embedded
     * nulls, starting at \a ustring to the next processing stream.
     *
     * \param ustring
     * A pointer to the string's first unicode character.
     *
     * \param count
     * The number of unicode character(s) to be written to the stream.
     */
    virtual void putUString(const RWUChar* ustring, RWSize count);

protected:

    /**
     * Used by derived classes to initialize the next processing stream.
     * Throws no exceptions.
     *
     * \param sinkStream
     * A handle to the next processing stream.
     */
    RWFilteredDataOutputStreamImp(const RWDataOutputStream& sinkStream)
        : RWDataOutputStreamImp()
        , sinkStream_(sinkStream)
    {
        ;
    }

    /**
     * Returns a handle to the next processing stream. Throws no exceptions.
     */
    RWDataOutputStream& getSinkStream()
    {
        return RW_EXPOSE(sinkStream_);
    }

    /**
     * Returns a handle to the next processing stream. Throws no exceptions.
     */
    const RWDataOutputStream& getSinkStream() const
    {
        return sinkStream_;
    }

private:

    // A handle to the next processing stream.
    RWDataOutputStream sinkStream_;

};

#endif // rw_stream_RWFilteredDataOutputStreamImp_h_
