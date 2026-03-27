#ifndef rw_stream_RWDataInputStreamImp_h_
#define rw_stream_RWDataInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWDataInputStreamImp.h#1 $
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

#include <rw/stream/RWInputStreamImp.h>
#include <rw/stream/pkgdefs.h>

// forward declaration
class RWDataInputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class from which all data input stream implementation
 * classes must derive.
 *
 * Abstract base class for all the data input stream implementation classes.
 * Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWDataInputStreamImp : public RWInputStreamImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWDataInputStreamImp()
    {
        ;
    }

    /**
     * Reads a \c bool value from the stream.
     *
     * \param value
     * The \c bool value to be read from the stream.
     */
    virtual void getBool(bool& value) = 0;

    /**
     * Reads a \c char value from the stream.
     *
     * \param value
     * The \c char value to be read from the stream.
     */
    virtual void getChar(char& value) = 0;

    /**
     * Reads a <tt>unsigned char</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be read from the stream.
     */
    virtual void getUnsignedChar(unsigned char& value) = 0;

    /**
     * Reads a <tt>signed char</tt> value from the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be read from the stream.
     */
    virtual void getSignedChar(signed char& value) = 0;

    /**
     * Reads a \c short value from the stream.
     *
     * \param value
     * The \c short value to be read from the stream.
     */
    virtual void getShort(short& value) = 0;

    /**
     * Reads a <tt>unsigned short</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be read from the stream.
     */
    virtual void getUnsignedShort(unsigned short& value) = 0;

    /**
     * Reads a \c int value from the stream.
     *
     * \param value
     * The \c int value to be read from the stream.
     */
    virtual void getInt(int& value) = 0;

    /**
     * Reads a <tt>unsigned int</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be read from the stream.
     */
    virtual void getUnsignedInt(unsigned int& value) = 0;

    /**
     * Reads a \c long value from the stream.
     *
     * \param value
     * The \c long value to be read from the stream.
     */
    virtual void getLong(long& value) = 0;

    /**
     * Reads a <tt>unsigned long</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be read from the stream.
     */
    virtual void getUnsignedLong(unsigned long& value) = 0;

    /**
     * Reads a \c float value from the stream.
     *
     * \param value
     * The \c float value to be read from the stream.
     */
    virtual void getFloat(float& value) = 0;

    /**
     * Reads a \c double value from the stream.
     *
     * \param value
     * The \c double value to be read from the stream.
     */
    virtual void getDouble(double& value) = 0;

    /**
     * Reads a \c wchar_t value from the stream.
     *
     * \param value
     * The \c wchar_t value to be read from the stream.
     */
    virtual void getWchar_t(wchar_t& value) = 0;

#if !defined(RW_NO_LONG_LONG)
    /**
     * Reads a <tt>long long</tt> value from the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be read from the stream.
     */
    virtual void getLongLong(long long& value) = 0;

    /**
     * Reads a <tt>unsigned long long</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned long long</tt> value to be read from the stream.
     */
    virtual void getUnsignedLongLong(unsigned long long& value) = 0;
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Reads a <tt>long double</tt> value from the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be read from the stream.
     */
    virtual void getLongDouble(long double& value) = 0;
#endif

    /**
     * Reads a \c char value from the stream.
     *
     * \param value
     * The \c char value to be read from the stream.
     */
    virtual void getCharacter(char& value) = 0;

    /**
     * Reads a \c wchar_t value from the stream.
     *
     * \param value
     * The \c wchar_t value to be read from the stream.
     */
    virtual void getWCharacter(wchar_t& value) = 0;

    /**
     * Reads a \c UTF-16 character from the stream.
     *
     * \param value
     * The \c UTF-16 value to be read from the stream.
     */
    virtual void getUCharacter(RWUChar& value) = 0;

    /**
     * Reads a \c size_t value from the stream.
     *
     * \param value
     * The \c size_t value to be read from the stream.
     */
    virtual void getSizeT(size_t& value) = 0;

    /**
     * Reads an array of \c bool value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getBools(bool* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of \c char value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getChars(char* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of <tt>unsigned char</tt> value(s) from the stream.
     * The array must have been pre-allocated to contain at least \a count
     * elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedChars(unsigned char* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of <tt>signed char</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getSignedChars(signed char* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of \c short value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getShorts(short* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of <tt>unsigned short</tt> value(s) from the stream.
     * The array must have been pre-allocated to contain at least \a count
     * elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedShorts(unsigned short* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of \c int value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getInts(int* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of <tt>unsigned int</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedInts(unsigned int* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of \c long value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getLongs(long* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of <tt>unsigned long</tt> value(s) from the stream.
     * The array must have been pre-allocated to contain at least \a count
     * elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedLongs(unsigned long* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of \c float value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getFloats(float* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of \c double value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getDoubles(double* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of \c wchar_t value(s) from the stream. The array must
     * have been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getWchar_ts(wchar_t* arrayPt, RWSize count) = 0;

#if !defined(RW_NO_LONG_LONG)
    /**
     * Reads an array of <tt>long long</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getLongLongs(long long* arrayPt, RWSize count) = 0;

    /**
     * Reads an array of <tt>unsigned long long</tt> value(s) from the
     * stream. The array must have been pre-allocated to contain at least
     * \a count elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUnsignedLongLongs(unsigned long long* arrayPt, RWSize count) = 0;
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Reads an array of <tt>long double</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements. The functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getLongDoubles(long double* arrayPt, RWSize count) = 0;
#endif

    /**
     * Reads a narrow character string from the stream. The string must have
     * been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param string
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getString(char* string, RWSize count) = 0;

    /**
     * Reads a wide character string from the stream. The string must have
     * been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param wstring
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getWString(wchar_t* wstring, RWSize count) = 0;

    /**
     * Reads a UTF-16 character string from the stream. The string must have
     * been pre-allocated to contain at least \a count elements. The
     * functions return the number of elements read.
     *
     * \param arrayPt
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    virtual RWSize getUString(RWUChar* arrayPt, RWSize count) = 0;

    /**
     * Reads narrow characters from the stream until the last character read
     * is equal to \a delim, or \a maxCount narrow characters have been
     * read, or the end of the input sequence is reached. The narrow
     * characters read are stored in \a string. The function returns the
     * actual number of narrow characters read from the stream.
     *
     * \param string
     * A pointer to the string receiving the narrow characters extracted
     * from the stream.
     *
     * \param maxCount
     * The maximum number of narrow characters to be read.
     *
     * \param delim
     * The narrow character used as a delimiter.
     */
    virtual RWSize getDelimitedString(char* string, RWSize maxCount, char delim) = 0;

    /**
     * Reads wide characters from the stream until the last character read
     * is equal to \a delim, or \a maxCount wide characters have been read,
     * or the end of the input sequence is reached. The wide characters read
     * are stored in \a wstring. The function returns the actual number of
     * wide characters read from the stream.
     *
     * \param wstring
     * A pointer to the string receiving the wide characters extracted from
     * the stream.
     *
     * \param maxCount
     * The maximum number of wide characters to be read.
     *
     * \param delim
     * The wide character used as a delimiter.
     */
    virtual RWSize getDelimitedWString(wchar_t* wstring, RWSize maxCount, wchar_t delim) = 0;

    /**
     * Reads UTF-16 characters from the stream until the last character read
     * is equal to \a delim, or \a maxCount UTF-16 characters have been
     * read, or the end of the input sequence is reached. The UTF-16
     * characters read are stored in \a ustring. The function returns the
     * actual number of UTF-16 characters read from the stream.
     *
     * \param ustring
     * A pointer to the string receiving the UTF-16 characters extracted
     * from the stream.
     *
     * \param maxCount
     * The maximum number of UTF-16 characters to be read.
     *
     * \param delim
     * The UTF-16 character used as a delimiter.
     */
    virtual RWSize getDelimitedUString(RWUChar* ustring, RWSize maxCount, RWUChar delim) = 0;

    //--Acquires the synchronization mechanism provided by a stream concrete
    //--implementation. The 'acquire()' member function returns a handle to the data
    //--stream that should be used for input operation after acquiring
    //--the synchronization mechanism.
    virtual RWDataInputStream acquire();

    //--Releases the synchronization mechanism provided by a stream concrete
    //--implementation.
    virtual void release()
    {
        ;
    }

protected:

    /**
     * Constructor. Throws no exceptions.
     */
    RWDataInputStreamImp()
        : RWInputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWDataInputStreamImp_h_
