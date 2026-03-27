#ifndef rw_stream_RWFilteredDataInputStreamImp_h_
#define rw_stream_RWFilteredDataInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWFilteredDataInputStreamImp.h#1 $
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

#include <rw/stream/RWDataInputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the filtered data input stream implementation
 * classes.
 *
 * Abstract base class for all the filtered data input stream implementation
 * classes. A filtered input stream is a stream that uses its attached input
 * stream as the source of elements to its own functions. Implements the
 * body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWFilteredDataInputStreamImp : public RWDataInputStreamImp
{

public:

    /**
     * Destructor. Throws no exceptions.
     */
    virtual ~RWFilteredDataInputStreamImp();

    /**
     * Forward the close() request to the attached source stream.
     */
    virtual void close();

    /**
     * Forward the isBad() request to the attached source stream. Throws no
     * exceptions.
     */
    virtual bool isBad() const;

    /**
     * Forward the isFail() request to the attached source stream. Throws no
     * exceptions.
     */
    virtual bool isFail() const;

    /**
     * Forward the isEof() request to the attached source stream. Throws no
     * exceptions.
     */
    virtual bool isEof() const;

    /**
     * Forward the isGood() request to the attached source stream. Throws no
     * exceptions.
     */
    virtual bool isGood() const;

    /**
     * Forward reading of a single \c bool value from the attached source
     * stream.
     *
     * \param value
     * The value to be read from the attached source stream.
     */
    virtual void getBool(bool& value);

    /**
     * Forward reading of a single \c char value from the attached source
     * stream.
     *
     * \param value
     * The \c char value to be read from the attached source stream.
     */
    virtual void getChar(char& value);

    /**
     * Forward reading of a single <tt>unsigned char</tt> value from the
     * attached source stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be read from the attached source
     * stream.
     */
    virtual void getUnsignedChar(unsigned char& value);

    /**
     * Forward reading of a single <tt>signed char</tt> value from the
     * attached source stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be read from the attached source
     * stream.
     */
    virtual void getSignedChar(signed char& value);

    /**
     * Forward reading of a single \c short value from the attached source
     * stream.
     *
     * \param value
     * The \c short value to be read from the attached source stream.
     */
    virtual void getShort(short& value);

    /**
     * Forward reading of a single <tt>unsigned short</tt> value from the
     * attached source stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be read from the attached source
     * stream.
     */
    virtual void getUnsignedShort(unsigned short& value);

    /**
     * Forward reading of a single \c int value from the attached source
     * stream.
     *
     * \param value
     * The \c int value to be read from the attached source stream.
     */
    virtual void getInt(int& value);

    /**
     * Forward reading of a single <tt>unsigned int</tt> value from the
     * attached source stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be read from the attached source
     * stream.
     */
    virtual void getUnsignedInt(unsigned int& value);

    /**
     * Forward reading of a single \c long value from the attached source
     * stream.
     *
     * \param value
     * The \c long value to be read from the attached source stream.
     */
    virtual void getLong(long& value);

    /**
     * Forward reading of a single <tt>unsigned long</tt> value from the
     * attached source stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be read from the attached source
     * stream.
     */
    virtual void getUnsignedLong(unsigned long& value);

    /**
     * Forward reading of a single \c float value from the attached source
     * stream.
     *
     * \param value
     * The \c float value to be read from the attached source stream.
     */
    virtual void getFloat(float& value);

    /**
     * Forward reading of a single \c double value from the attached source
     * stream.
     *
     * \param value
     * The \c double value to be read from the attached source stream.
     */
    virtual void getDouble(double& value);

    /**
     * Forward reading of a single \c wchar_t value from the attached source
     * stream.
     *
     * \param value
     * The \c wchar_t value to be read from the attached source stream.
     */
    virtual void getWchar_t(wchar_t& value);

#if !defined(RW_NO_LONG_LONG)
    /**
     * Forward reading of a single <tt>long long</tt> value from the
     * attached source stream.
     *
     * \param value
     * The <tt>long long</tt> value to be read from the attached source
     * stream.
     */
    virtual void getLongLong(long long& value);

    /**
     * Forward reading of a single <tt>unsigned long long</tt> value from
     * the attached source stream.
     *
     * \param value
     * The <tt>unsigned long long</tt> value to be read from the attached
     * source stream.
     */
    virtual void getUnsignedLongLong(unsigned long long& value);
#endif

#ifndef RW_NO_LONG_DOUBLE
    //--Forward reading of a single 'long double' value from the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The long double value to be read from the attached
    //--  source stream.
    /**
     * Forward reading of a single <tt>long double</tt> value from the
     * attached source stream.
     *
     * \param value
     * The <tt>long double</tt> value to be read from the attached source
     * stream.
     */
    virtual void getLongDouble(long double& value);
#endif

    /**
     * Forward the reading of a narrow character from the attached source
     * stream.
     *
     * \param value
     * The narrow character to be read from the attached source stream.
     */
    virtual void getCharacter(char& value);

    /**
     * Forward the reading of a wide character from the attached source
     * stream.
     *
     * \param value
     * The wide character to be read from the attached source stream.
     */
    virtual void getWCharacter(wchar_t& value);

    /**
     * Forward the reading of a UTF-16 character from the attached source
     * stream.
     *
     * \param value
     * The unicode character to be read from the attached source stream.
     */
    virtual void getUCharacter(RWUChar& value);

    //--Reads a 'size_t' character from the stream.
    virtual void getSizeT(size_t& value);

    /**
     * Forward the reading of an array of \c bool elements from the attached
     * source stream. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getBools(bool* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of \c char elements from the attached
     * source stream. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getChars(char* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of <tt>unsigned char</tt> elements
     * from the attached source stream. The function returns the number of
     * elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedChars(unsigned char* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of <tt>signed char</tt> elements from
     * the attached source stream. The function returns the number of
     * elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getSignedChars(signed char* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of \c short elements from the
     * attached source stream. The function returns the number of elements
     * read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getShorts(short* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of <tt>unsigned short</tt> elements
     * from the attached source stream. The function returns the number of
     * elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedShorts(unsigned short* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of \c int elements from the attached
     * source stream. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getInts(int* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of <tt>unsigned int</tt> elements
     * from the attached source stream. The function returns the number of
     * elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedInts(unsigned int* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of \c long elements from the attached
     * source stream. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getLongs(long* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of <tt>unsigned long</tt> elements
     * from the attached source stream. The function returns the number of
     * elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedLongs(unsigned long* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of \c float elements from the
     * attached source stream. The function returns the number of elements
     * read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getFloats(float* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of \c double elements from the
     * attached source stream. The function returns the number of elements
     * read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getDoubles(double* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of \c wchar_t elements from the
     * attached source stream. The function returns the number of elements
     * read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getWchar_ts(wchar_t* arrayPt, RWSize count);

#if !defined(RW_NO_LONG_LONG)
    /**
     * Forward the reading of an array of <tt>long long</tt> elements from
     * the attached source stream. The function returns the number of
     * elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getLongLongs(long long* arrayPt, RWSize count);

    /**
     * Forward the reading of an array of <tt>unsigned long long</tt>
     * elements from the attached source stream. The function returns the
     * number of elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedLongLongs(unsigned long long* arrayPt, RWSize count);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Forward the reading of an array of <tt>long double</tt> elements from
     * the attached source stream. The function returns the number of
     * elements read.
     *
     * \param arrayPt
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least count elements.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getLongDoubles(long double* arrayPt, RWSize count);
#endif

    /**
     * Forward the reading of a string of narrow characters from the
     * attached source stream. The function returns the number of narrow
     * characters read.
     *
     * \param string
     * A pointer to the first element of the string. The string must have
     * been pre-allocated to contain at least \a count narrow characters.
     *
     * \param count
     * The number of narrow character(s) to be read from the stream.
     */
    virtual RWSize getString(char* string, RWSize count);

    /**
     * Forward the reading of a string of wide characters from the attached
     * source stream. The function returns the number of wide characters
     * read.
     *
     * \param wstring
     * A pointer to the first element of the string. The string must have
     * been pre-allocated to contain at least \a count wide characters.
     *
     * \param count
     * The number of wide character(s) to be read from the stream.
     */
    virtual RWSize getWString(wchar_t* wstring, RWSize count);

    /**
     * Forward the reading of a string of UTF-16 characters from the
     * attached source stream. The function returns the number of UTF-16
     * characters read.
     *
     * \param ustring
     * A pointer to the first element of the string. The string must have
     * been pre-allocated to contain at least \a count unicode characters.
     *
     * \param count
     * The number of unicode character(s) to be read from the stream.
     */
    virtual RWSize getUString(RWUChar* ustring, RWSize count);

    /**
     * Forward the reading of narrow characters from the stream until the
     * last character read is equal to \a delim, or \a maxCount narrow
     * characters have been read, or the end of the input sequence is
     * reached. The narrow characters read are stored in \a string. The
     * function returns the actual number of narrow characters read from the
     * stream.
     *
     * \param string
     * A pointer to the string receiving the narrow character(s) extracted
     * from the stream.
     *
     * \param maxCount
     * The maximum number of narrow character(s) to be read.
     *
     * \param delim
     * The narrow character used as a delimiter.
     */
    virtual RWSize getDelimitedString(char* string, RWSize maxCount, char delim);

    /**
     * Forward the reading of wide characters from the stream until the last
     * character read is equal to \a delim, or \a maxCount wide characters
     * have been read, or the end of the input sequence is reached. The wide
     * characters read are stored in \a wstring. The function returns the
     * actual number of wide characters read from the stream.
     *
     * \param wstring
     * A pointer to the string receiving the wide character(s) extracted
     * from the stream.
     *
     * \param maxCount
     * The maximum number of wide character(s) to be read.
     *
     * \param delim
     * The wide character used as a delimiter.
     */
    virtual RWSize getDelimitedWString(wchar_t* wstring, RWSize maxCount, wchar_t delim);

    /**
     * Forward the reading of UTF-16 characters from the stream until the
     * last character read is equal to \a delim, or \a maxCount UTF-16
     * characters have been read, or the end of the input sequence is
     * reached. The UTF-16 characters read are stored in \a ustring. The
     * function returns the actual number of UTF-16 characters read from the
     * stream.
     *
     * \param ustring
     * A pointer to the string receiving the unicode character(s) extracted
     * from the stream.
     *
     * \param maxCount
     * The maximum number of unicode character(s) to be read.
     *
     * \param delim
     * The unicode character used as a delimiter.
     */
    virtual RWSize getDelimitedUString(RWUChar* ustring, RWSize maxCount, RWUChar delim);

    /**
     * Returns the number of elements that can be read from the attached
     * source stream without blocking. The elements can be of type #RWByte,
     * \c char, #RWUChar, or \c wchar_t depending on the type of the
     * attached source stream. Throws no exceptions.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits elements from the input sequence of the attached
     * source stream if possible. The function returns the actual number of
     * elements skipped, which can be any value between 0 and \a numUnits.
     * The elements can be of type #RWByte, \c char, #RWUChar, or \c wchar_t
     * depending on the type of the attached source stream.
     *
     * \param numUnits
     * The number of element(s) to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

protected:

    /**
     * Used by derived classes to initialize the attached source stream.
     * Throws no exceptions.
     *
     * \param sourceStream
     * A handle to the attached source stream.
     */
    RWFilteredDataInputStreamImp(const RWDataInputStream& sourceStream)
        : RWDataInputStreamImp()
        , sourceStream_(sourceStream)
    {
        ;
    }

    /**
     * Returns a handle to the attached source stream. Throws no exceptions.
     */
    RWDataInputStream& getSourceStream()
    {
        return RW_EXPOSE(sourceStream_);
    }

    /**
     * Returns a handle to the attached source stream. Throws no exceptions.
     */
    const RWDataInputStream& getSourceStream() const
    {
        return sourceStream_;
    }

private:

    // A handle to the attached source stream.
    RWDataInputStream sourceStream_;

};

#endif // rw_stream_RWFilteredDataInputStreamImp_h_
