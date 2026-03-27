#ifndef rw_stream_RWDataInputStream_h_
#define rw_stream_RWDataInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWDataInputStream.h#1 $
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

#include <rw/stream/RWDataInputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

// forward declaration
template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredDataInputStreamImp;

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all the data input stream implementation classes.
 *
 * Handle class for all the data input stream implementation classes.
 * Implements the handle idiom from the handle-body pattern.
 */
class RW_STREAM_SYMBOLIC RWDataInputStream : public RWHandleBase
{

public:

    /**
     * Constructor.
     */
    explicit RWDataInputStream(RWDataInputStreamImp* ptr)
        : RWHandleBase(ptr)
    { }

    /**
     * Copy constructor.
     *
     * \param handle
     * A data stream handle used to initialize the newly created handle.
     */
    RWDataInputStream(const RWDataInputStream& handle)
        : RWHandleBase(handle)
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A data stream handle used to initialize this handle.
     */
    RWDataInputStream& operator=(const RWDataInputStream& handle)
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
    RWDataInputStream& operator>>(RWDataInputStream & (*pf)(RWDataInputStream&))
    {
        return pf(*this);
    }

    /**
     * Extractor executing a manipulator function.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWDataInputStream operator>>(RWDataInputStream(*pf)(RWDataInputStream&))
    {
        return pf(*this);
    }

    /**
     * Closes the stream. May throw exceptions.
     */
    void close()
    {
        static_cast<RWDataInputStreamImp&>(this->body()).close();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * input, such as an irrecoverable read error from a file. Throws no
     * exceptions.
     */
    bool isBad() const
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an input operation failed to read
     * the expected data. Throws no exceptions.
     */
    bool isFail() const
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    bool isGood() const
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).isGood();
    }

    /**
     * Returns \c true to indicate that an input operation reached the end
     * of an input sequence. Throws no exceptions.
     */
    bool isEof() const
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).isEof();
    }

    /**
     * Returns the number of available elements that can be read from the
     * stream without blocking. The type of the elements read is specified
     * by implementation classes and can be one of the following: #RWByte,
     * \c char, #RWUChar, or \c wchar_t. Throws no exceptions.
     */
    RWSize available() const
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).available();
    }

    /**
     * Skips \a numUnits elements from the input sequence if possible. The
     * function returns the actual number of elements skipped, which can be
     * any value between \c 0 and \a numUnits. The type of the elements
     * skipped is specified by implementation classes and can be one of the
     * following: #RWByte, \c char, #RWUChar, or \c wchar_t.
     *
     * \param numUnits
     * The number of elements to be skipped.
     */
    RWSize skip(RWSize numUnits)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).skip(numUnits);
    }

    /**
     * Reads a \c char value from the stream.
     *
     * \param value
     * The \c bool value to be read from the stream.
     */
    RWDataInputStream& operator>>(bool& value)
    {
        this->getBool(value);
        return *this;
    }

    /**
     * Reads a \c char value from the stream.
     *
     * \param value
     * The \c char value to be read from the stream.
     */
    RWDataInputStream& operator>>(char& value)
    {
        this->getChar(value);
        return *this;
    }

    /**
     * Reads a <tt>unsigned char</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be read from the stream.
     */
    RWDataInputStream& operator>>(unsigned char& value)
    {
        this->getUnsignedChar(value);
        return *this;
    }

    /**
     * Reads a <tt>signed char</tt> value from the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be read from the stream.
     */
    RWDataInputStream& operator>>(signed char& value)
    {
        this->getSignedChar(value);
        return *this;
    }

    /**
     * Reads a \c short value from the stream.
     *
     * \param value
     * The \c short value to be read from the stream.
     */
    RWDataInputStream& operator>>(short& value)
    {
        this->getShort(value);
        return *this;
    }

    /**
     * Reads a <tt>unsigned short</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be read from the stream.
     */
    RWDataInputStream& operator>>(unsigned short& value)
    {
        this->getUnsignedShort(value);
        return *this;
    }

    /**
     * Reads a \c int value from the stream.
     *
     * \param value
     * The \c int value to be read from the stream.
     */
    RWDataInputStream& operator>>(int& value)
    {
        this->getInt(value);
        return *this;
    }

    /**
     * Reads a <tt>unsigned int</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be read from the stream.
     */
    RWDataInputStream& operator>>(unsigned int& value)
    {
        this->getUnsignedInt(value);
        return *this;
    }

    /**
     * Reads a \c long value from the stream.
     *
     * \param value
     * The \c long value to be read from the stream.
     */
    RWDataInputStream& operator>>(long& value)
    {
        this->getLong(value);
        return *this;
    }

    /**
     * Reads a <tt>unsigned long</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be read from the stream.
     */
    RWDataInputStream& operator>>(unsigned long& value)
    {
        this->getUnsignedLong(value);
        return *this;
    }

    /**
     * Reads a \c float value from the stream.
     *
     * \param value
     * The \c float value to be read from the stream.
     */
    RWDataInputStream& operator>>(float& value)
    {
        this->getFloat(value);
        return *this;
    }

    /**
     * Reads a \c double value from the stream.
     *
     * \param value
     * The \c double value to be read from the stream.
     */
    RWDataInputStream& operator>>(double& value)
    {
        this->getDouble(value);
        return *this;
    }

    /**
     * Reads a \c wchar_t value from the stream.
     *
     * \param value
     * The \c wchar_t value to be read from the stream.
     */
    RWDataInputStream& operator>>(wchar_t& value)
    {
        this->getWchar_t(value);
        return *this;
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Reads a <tt>long long</tt> value from the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be read from the stream.
     */
    RWDataInputStream& operator>>(long long& value)
    {
        this->getLongLong(value);
        return *this;
    }

    RWDataInputStream& operator>>(unsigned long long& value)
    {
        this->getUnsignedLongLong(value);
        return *this;
    }

#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Reads a <tt>long double</tt> value from the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be read from the stream.
     */
    RWDataInputStream& operator>>(long double& value)
    {
        this->getLongDouble(value);
        return *this;
    }
#endif

    /**
     * Reads a \c bool value from the stream.
     *
     * \param value
     * The \c bool to be read from the stream.
     */
    void getBool(bool& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getBool(value);
    }

    /**
     * Reads a \c char value from the stream.
     *
     * \param value
     * The \c char to be read from the stream.
     */
    void getChar(char& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getChar(value);
    }

    /**
     * Reads a <tt>unsigned char</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be read from the stream.
     */
    void getUnsignedChar(unsigned char& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedChar(value);
    }

    /**
     * Reads a <tt>signed char</tt> value from the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be read from the stream.
     */
    void getSignedChar(signed char& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getSignedChar(value);
    }

    /**
     * Reads a \c short value from the stream.
     *
     * \param value
     * The \c short to be read from the stream.
     */
    void getShort(short& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getShort(value);
    }

    /**
     * Reads a <tt>unsigned short</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be read from the stream.
     */
    void getUnsignedShort(unsigned short& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedShort(value);
    }

    /**
     * Reads a \c int value from the stream.
     *
     * \param value
     * The \c int to be read from the stream.
     */
    void getInt(int& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getInt(value);
    }

    /**
     * Reads a <tt>unsigned int</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be read from the stream.
     */
    void getUnsignedInt(unsigned int& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedInt(value);
    }

    /**
     * Reads a \c long value from the stream.
     *
     * \param value
     * The \c long to be read from the stream.
     */
    void getLong(long& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getLong(value);
    }

    /**
     * Reads a <tt>unsigned long</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be read from the stream.
     */
    void getUnsignedLong(unsigned long& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedLong(value);
    }

    /**
     * Reads a \c float value from the stream.
     *
     * \param value
     * The \c float value to be read from the stream.
     */
    void getFloat(float& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getFloat(value);
    }

    /**
     * Reads a \c double value from the stream.
     *
     * \param value
     * The \c double value to be read from the stream.
     */
    void getDouble(double& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getDouble(value);
    }

    /**
     * Reads a \c wchar_t value from the stream.
     *
     * \param value
     * The \c wchar_t value to be read from the stream.
     */
    void getWchar_t(wchar_t& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getWchar_t(value);
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Reads a <tt>long long</tt> value from the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be read from the stream.
     */
    void getLongLong(long long& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getLongLong(value);
    }

    void getUnsignedLongLong(unsigned long long& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedLongLong(value);
    }

#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Reads a <tt>long double</tt> value from the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be read from the stream.
     */
    void getLongDouble(long double& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getLongDouble(value);
    }
#endif

    /**
     * Reads a narrow character from the stream.
     *
     * \param value
     * The narrow character to be read from the stream.
     */
    void getCharacter(char& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getCharacter(value);
    }

    /**
     * Reads a wide character from the stream.
     *
     * \param value
     * The wide character to be read from the stream.
     */
    void getWCharacter(wchar_t& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getWCharacter(value);
    }

    /**
     * Reads a UTF-16 character from the stream.
     *
     * \param value
     * The UTF-16 character to be read from the stream.
     */
    void getUCharacter(RWUChar& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getUCharacter(value);
    }

    /**
     * Reads a size_t character from the stream.
     *
     * \param value
     * The size_t character to be read from the stream.
     */
    void getSizeT(size_t& value)
    {
        static_cast<RWDataInputStreamImp&>(this->body()).getSizeT(value);
    }

    /**
     * Reads an array of \c bool value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getBools(bool* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getBools(arrayPt, count);
    }

    /**
     * Reads an array of \c char value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getChars(char* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getChars(arrayPt, count);
    }

    /**
     * Reads an array of <tt>unsigned char</tt> value(s) from the stream.
     * The array must have been pre-allocated to contain at least count
     * elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getUnsignedChars(unsigned char* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedChars(arrayPt, count);
    }

    /**
     * Reads an array of <tt>signed char</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least count
     * elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getSignedChars(signed char* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getSignedChars(arrayPt, count);
    }

    /**
     * Reads an array of \c short value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getShorts(short* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getShorts(arrayPt, count);
    }

    /**
     * Reads an array of <tt>unsigned short</tt> value(s) from the stream.
     * The array must have been pre-allocated to contain at least count
     * elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getUnsignedShorts(unsigned short* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedShorts(arrayPt, count);
    }

    /**
     * Reads an array of \c int value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getInts(int* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getInts(arrayPt, count);
    }

    /**
     * Reads an array of <tt>unsigned int</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least count
     * elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getUnsignedInts(unsigned int* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedInts(arrayPt, count);
    }

    /**
     * Reads an array of \c long value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getLongs(long* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getLongs(arrayPt, count);
    }

    /**
     * Reads an array of <tt>unsigned long</tt> value(s) from the stream.
     * The array must have been pre-allocated to contain at least count
     * elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getUnsignedLongs(unsigned long* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedLongs(arrayPt, count);
    }

    /**
     * Reads an array of \c float value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getFloats(float* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getFloats(arrayPt, count);
    }

    /**
     * Reads an array of \c double value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getDoubles(double* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getDoubles(arrayPt, count);
    }

    /**
     * Reads an array of \c wchar_t value(s) from the stream. The array must
     * have been pre-allocated to contain at least count elements. The
     * function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getWchar_ts(wchar_t* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getWchar_ts(arrayPt, count);
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Reads an array of <tt>long long</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getLongLongs(long long* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getLongLongs(arrayPt, count);
    }

    /**
     * Reads an array of <tt>unsigned long long</tt> value(s) from the
     * stream. The array must have been pre-allocated to contain at least
     * \a count elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getUnsignedLongLongs(unsigned long long* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getUnsignedLongLongs(arrayPt, count);
    }
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Reads an array of <tt>long double</tt> value(s) from the stream. The
     * array must have been pre-allocated to contain at least count
     * elements. The function returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    RWSize getLongDoubles(long double* arrayPt, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getLongDoubles(arrayPt, count);
    }
#endif

    /**
     * Reads a narrow character string from the stream. The string must have
     * been pre-allocated to contain at least \a count elements. The
     * function returns the number of elements read.
     *
     * \param string
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    RWSize getString(char* string, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getString(string, count);
    }

    /**
     * Reads a wide character string from the stream. The string must have
     * been pre-allocated to contain at least \a count elements. The
     * function returns the number of elements read.
     *
     * \param wstring
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    RWSize getWString(wchar_t* wstring, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getWString(wstring, count);
    }

    /**
     * Reads a UTF-16 character string from the stream. The string must have
     * been pre-allocated to contain at least \a count elements. The
     * function returns the number of elements read.
     *
     * \param ustring
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be read from the stream.
     */
    RWSize getUString(RWUChar* ustring, RWSize count)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getUString(ustring, count);
    }

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
    RWSize getDelimitedString(char* string, RWSize maxCount, char delim = '\0')
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getDelimitedString(string, maxCount, delim);
    }

    /**
     * Reads wide characters from the stream until the last character read
     * is equal to \a delim, or \a maxCount wide characters have been read,
     * or the end of the input sequence is reached. The \a wstring stores
     * the wide characters read. The function returns the actual number of
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
    RWSize getDelimitedWString(wchar_t* wstring, RWSize maxCount, wchar_t delim = L'\0')
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getDelimitedWString(wstring, maxCount, delim);
    }

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
    RWSize getDelimitedUString(RWUChar* ustring, RWSize maxCount, RWUChar delim)
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).getDelimitedUString(ustring, maxCount, delim);
    }

private:

    //--Acquires the synchronization mechanism provided by a stream concrete
    //--implementation. The 'acquire()' member function returns a handle to the
    //--data stream that should be used for input operation after acquiring
    //--the synchronization mechanism. This function is only used by instance of
    //--class 'RWGuardedDataInputStreamImp'.
    RWDataInputStream acquire()
    {
        return static_cast<RWDataInputStreamImp&>(this->body()).acquire();
    }

    //--Releases the synchronization mechanism provided by a stream concrete
    //--implementation. This function is only used by instance of
    //--class 'RWGuardedDataInputStreamImp'.
    void release()
    {
        static_cast<RWDataInputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWDataInputStream, RWFilteredDataInputStreamImp>;
};

#endif // rw_stream_RWDataInputStream_h_
