#ifndef rw_stream_RWDataOutputStreamImp_h_
#define rw_stream_RWDataOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWDataOutputStreamImp.h#1 $
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

#include <rw/stream/RWOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>

// forward declaration
class RWDataOutputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class from which all data output stream implementation
 * classes must derive.
 *
 * Abstract base class for all the data output stream implementation
 * classes. Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWDataOutputStreamImp : public RWOutputStreamImp
{

public:

    /**
     * Destructor.
     */
    virtual ~RWDataOutputStreamImp()
    {
        ;
    }

    /**
     * Writes a \c bool value to the stream.
     *
     * \param value
     * The \c bool value to be written to the stream.
     */
    virtual void putBool(bool value) = 0;

    /**
     * Writes a \c char value to the stream.
     *
     * \param value
     * The \c char value to be written to the stream.
     */
    virtual void putChar(char value) = 0;

    /**
     * Writes an <tt>unsigned char</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be written to the stream.
     */
    virtual void putUnsignedChar(unsigned char value) = 0;

    /**
     * Writes a <tt>signed char</tt> value to the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be written to the stream.
     */
    virtual void putSignedChar(signed char value) = 0;


    /**
     * Writes a \c short value to the stream.
     *
     * \param value
     * The \c short value to be written to the stream.
     */
    virtual void putShort(short value) = 0;

    /**
     * Writes an <tt>unsigned short</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be written to the stream.
     */
    virtual void putUnsignedShort(unsigned short value) = 0;

    /**
     * Writes an \c int value to the stream.
     *
     * \param value
     * The \c int value to be written to the stream.
     */
    virtual void putInt(int value) = 0;

    /**
     * Writes an <tt>unsigned int</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be written to the stream.
     */
    virtual void putUnsignedInt(unsigned int value) = 0;

    /**
     * Writes a \c long value to the stream.
     *
     * \param value
     * The \c long value to be written to the stream.
     */
    virtual void putLong(long value) = 0;

    /**
     * Writes an <tt>unsigned long</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be written to the stream.
     */
    virtual void putUnsignedLong(unsigned long value) = 0;

    /**
     * Writes a \c float value to the stream.
     *
     * \param value
     * The \c float value to be written to the stream.
     */
    virtual void putFloat(float value) = 0;

    /**
     * Writes a \c double value to the stream.
     *
     * \param value
     * The \c double value to be written to the stream.
     */
    virtual void putDouble(double value) = 0;

    /**
     * Writes a \c wchar_t value to the stream.
     *
     * \param value
     * The \c wchar_t value to be written to the stream.
     */
    virtual void putWchar_t(wchar_t value) = 0;

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes a <tt>long long</tt> value to the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be written to the stream.
     */
    virtual void putLongLong(long long value) = 0;
    virtual void putUnsignedLongLong(unsigned long long value) = 0;
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Writes a <tt>long double</tt> value to the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be written to the stream.
     */
    virtual void putLongDouble(long double value) = 0;
#endif

    /**
     * Writes a narrow character to the stream.
     *
     * \param value
     * The narrow character to be written to the stream.
     */
    virtual void putCharacter(char value) = 0;

    /**
     * Writes a wide character to the stream.
     *
     * \param value
     * The wide character to be written to the stream.
     */
    virtual void putWCharacter(wchar_t value) = 0;

    /**
     * Writes a UTF-16 character to the stream.
     *
     * \param value
     * The UTF-16 character to be written to the stream.
     */
    virtual void putUCharacter(RWUChar value) = 0;

    //--Writes a size_t character to the stream.
    //--The parameter 'value' is the unicode character to be written to the stream.
    virtual void putSizeT(size_t value) = 0;

    /**
     * Writes an array of \c bool values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putBools(const bool* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of \c char values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putChars(const char* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of <tt>unsigned char</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedChars(const unsigned char* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of <tt>signed char</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putSignedChars(const signed char* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of \c short values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putShorts(const short* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of <tt>unsigned short</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedShorts(const unsigned short* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of \c int values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putInts(const int* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of <tt>unsigned int</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedInts(const unsigned int* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of \c long values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongs(const long* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of <tt>unsigned long</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedLongs(const unsigned long* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of \c float values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putFloats(const float* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of \c double values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putDoubles(const double* arrayPt, RWSize count) = 0;

    /**
     * Writes an array of \c wchar_t values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putWchar_ts(const wchar_t* arrayPt, RWSize count) = 0;

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes an array of <tt>long long</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongLongs(const long long* arrayPt, RWSize count) = 0;
    virtual void putUnsignedLongLongs(const unsigned long long* arrayPt, RWSize count) = 0;
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Writes an array of <tt>long double</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongDoubles(const long double* arrayPt, RWSize count) = 0;
#endif

    /**
     * Writes a narrow character string, including embedded nulls, starting
     * at \a string to the stream.
     *
     * \param string
     * A pointer to the narrow string's first character.
     *
     * \param count
     * The number of narrow characters to be written to the stream.
     */
    virtual void putString(const char* string, RWSize count) = 0;

    /**
     * Writes a wide character string, including embedded nulls, starting at
     * \a wstring to the stream.
     *
     * \param wstring
     * A pointer to the string's first wide character.
     *
     * \param count
     * The number of wide characters to be written to the stream.
     */
    virtual void putWString(const wchar_t* wstring, RWSize count) = 0;

    /**
     * Writes a UTF-16 character string, including embedded nulls, starting
     * at \a ustring to the stream.
     *
     * \param ustring
     * A pointer to the string's first UTF-16 character.
     *
     * \param count
     * The number of UTF-16 characters to be written to the stream.
     */
    virtual void putUString(const RWUChar* ustring, RWSize count) = 0;

    /**
     * Acquires the synchronization mechanism provided by a stream concrete
     * implementation. The acquire member function returns a handle to the
     * data stream that should be used for output operation after acquiring
     * the synchronization mechanism.
     */
    virtual RWDataOutputStream acquire();

    /**
     * Releases the synchronization mechanism provided by a stream concrete
     * implementation.
     */
    virtual void release()
    {
        ;
    }

protected:

    /**
     * Constructor. Throws no exceptions.
     */
    RWDataOutputStreamImp()
        : RWOutputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWDataOutputStreamImp_h_
