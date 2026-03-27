#ifndef rw_stream_RWNativeDataToByteOutputStreamImp_h_
#define rw_stream_RWNativeDataToByteOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWNativeDataToByteOutputStreamImp.h#1 $
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
#include <rw/stream/RWDataToByteOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Writes data in native format to a binary stream.
 *
 * The class RWNativeDataToByteOutputStreamImp writes data in native format
 * to a binary stream. Implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWNativeDataToByteOutputStreamImp : public RWDataToByteOutputStreamImp
{

public:

    /**
     * Constructs an RWNativeDataToByteOutputStreamImp instance that uses
     * \a sink as its byte sink, and returns a handle to it. Throws no
     * exceptions.
     *
     * \param sink
     * The binary stream that is used as the byte sink.
     */
    static RWDataOutputStream make(const RWByteOutputStream& sink)
    {
        return RWDataOutputStream(new RWNativeDataToByteOutputStreamImp(sink));
    }

    //--Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWNativeDataToByteOutputStreamImp();

    /**
     * Writes a \c bool value to the binary stream, used as the data sink.
     *
     * \param value
     * The \c bool value to be written to the stream.
     */
    virtual void putBool(bool value);

    /**
     * Writes a \c char value to the binary stream, used as the data sink.
     *
     * \param value
     * The \c char value to be written to the stream.
     */
    virtual void putChar(char value);

    /**
     * Writes a <tt>unsigned char</tt> value to the binary stream, used as
     * the data sink.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be written to the stream.
     */
    virtual void putUnsignedChar(unsigned char value);

    /**
     * Writes a <tt>signed char</tt> value to the binary stream, used as the
     * data sink.
     *
     * \param value
     * The <tt>signed char</tt> value to be written to the stream.
     */
    virtual void putSignedChar(signed char value);

    /**
     * Writes a \c short value to the binary stream, used as the data sink.
     *
     * \param value
     * The \c short value to be written to the stream.
     */
    virtual void putShort(short value);

    /**
     * Writes a <tt>unsigned short</tt> value to the binary stream, used as
     * the data sink.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be written to the stream.
     */
    virtual void putUnsignedShort(unsigned short value);

    /**
     * Writes a \c int value to the binary stream, used as the data sink.
     *
     * \param value
     * The \c int value to be written to the stream.
     */
    virtual void putInt(int value);

    /**
     * Writes a <tt>unsigned int</tt> value to the binary stream, used as
     * the data sink.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be written to the stream.
     */
    virtual void putUnsignedInt(unsigned int value);

    /**
     * Writes a \c long value to the binary stream, used as the data sink.
     *
     * \param value
     * The \c long value to be written to the stream.
     */
    virtual void putLong(long value);

    /**
     * Writes a <tt>unsigned long</tt> value to the binary stream, used as
     * the data sink.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be written to the stream.
     */
    virtual void putUnsignedLong(unsigned long value);

    /**
     * Writes a \c float value to the binary stream, used as the data sink.
     *
     * \param value
     * The \c float value to be written to the stream.
     */
    virtual void putFloat(float value);

    /**
     * Writes a \c double value to the binary stream, used as the data sink.
     *
     * \param value
     * The \c double value to be written to the stream.
     */
    virtual void putDouble(double value);

    /**
     * Writes a \c wchar_t value to the binary stream, used as the data
     * sink.
     *
     * \param value
     * The \c wchar_t value to be written to the stream.
     */
    virtual void putWchar_t(wchar_t value);

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes a <tt>long long</tt> value to the binary stream, used as the
     * data sink.
     *
     * \param value
     * The <tt>long long</tt> value to be written to the stream.
     */
    virtual void putLongLong(long long value);

    /**
     * Writes an <tt>unsigned long long</tt> value to the binary stream,
     * used as the data sink.
     *
     * \param value
     * The <tt>unsigned long long</tt> value to be written to the stream.
     */
    virtual void putUnsignedLongLong(unsigned long long value);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Writes a <tt>long double</tt> value to the binary stream, used as the
     * data sink.
     *
     * \param value
     * The <tt>long double</tt> value to be written to the stream.
     */
    virtual void putLongDouble(long double value);
#endif

    /**
     * Writes a narrow character to the binary stream that is used as the
     * data sink.
     *
     * \param value
     * The narrow character to be written to the stream.
     */
    virtual void putCharacter(char value);

    /**
     * Writes a wide character to the binary stream that is used as the data
     * sink.
     *
     * \param value
     * The wide character to be written to the stream.
     */
    virtual void putWCharacter(wchar_t value);

    /**
     * Writes a UTF-16 character to the binary stream that is used as the
     * data sink.
     *
     * \param value
     * The UTF-16 character to be written to the stream.
     */
    virtual void putUCharacter(RWUChar value);

    /**
     * Writes a \c size_t character to the binary stream that is used as the
     * data sink.
     *
     * \param value
     * The \c size_t character to be written to the stream.
     */
    virtual void putSizeT(size_t value);

    /**
     * Writes an array of \c bool values to the binary stream, used as the
     * data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putBools(const bool* arrayPt, RWSize count);

    /**
     * Writes an array of \c char values to the binary stream, used as the
     * data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putChars(const char* arrayPt, RWSize count);

    /**
     * Writes an array of <tt>unsigned char</tt> values to the binary
     * stream, used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedChars(const unsigned char* arrayPt, RWSize count);

    /**
     * Writes an array of <tt>signed char</tt> values to the binary stream,
     * used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putSignedChars(const signed char* arrayPt, RWSize count);

    /**
     * Writes an array of \c short values to the binary stream, used as the
     * data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putShorts(const short* arrayPt, RWSize count);

    /**
     * Writes an array of <tt>unsigned short</tt> values to the binary
     * stream, used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedShorts(const unsigned short* arrayPt, RWSize count);

    /**
     * Writes an array of \c int values to the binary stream, used as the
     * data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putInts(const int* arrayPt, RWSize count);

    /**
     * Writes an array of <tt>unsigned int</tt> values to the binary stream,
     * used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedInts(const unsigned int* arrayPt, RWSize count);

    /**
     * Writes an array of \c long values to the binary stream, used as the
     * data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongs(const long* arrayPt, RWSize count);

    /**
     * Writes an array of <tt>unsigned long</tt> values to the binary
     * stream, used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedLongs(const unsigned long* arrayPt, RWSize count);

    /**
     * Writes an array of \c float values to the binary stream, used as the
     * data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putFloats(const float* arrayPt, RWSize count);

    /**
     * Writes an array of \c double values to the binary stream, used as the
     * data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putDoubles(const double* arrayPt, RWSize count);

    /**
     * Writes an array of \c wchar_t values to the binary stream, used as
     * the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putWchar_ts(const wchar_t* arrayPt, RWSize count);

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes an array of <tt>long long</tt> values to the binary stream,
     * used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongLongs(const long long* arrayPt, RWSize count);

    /**
     * Writes an array of <tt>unsigned long long</tt> values to the binary
     * stream, used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUnsignedLongLongs(const unsigned long long* arrayPt, RWSize count);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Writes an array of <tt>long double</tt> values to the binary stream,
     * used as the data sink.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putLongDoubles(const long double* arrayPt, RWSize count);
#endif

    /**
     * Writes a narrow character string to the binary stream that is used as
     * the data sink.
     *
     * \param string
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putString(const char* string, RWSize count);

    /**
     * Writes a wide character string to the binary stream that is used as
     * the data sink.
     *
     * \param wstring
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putWString(const wchar_t* wstring, RWSize count);

    /**
     * Writes a UTF-16 character string to the binary stream that is used as
     * the data sink.
     *
     * \param ustring
     * A pointer to the string's first element.
     *
     * \param count
     * The number of elements to be written to the stream.
     */
    virtual void putUString(const RWUChar* ustring, RWSize count);

protected:

    //--Throws no exceptions.
    /**
     * Initializes the reference to the binary stream that will be used as
     * the byte sink.
     *
     * \param sinkStream
     * The binary stream that will serve as the byte sink.
     */
    RWNativeDataToByteOutputStreamImp(const RWByteOutputStream& sinkStream)
        : RWDataToByteOutputStreamImp(sinkStream)
    {
        ;
    }

private:

    void write(RWByte pt)
    {
        this->getSinkStream().write(pt);
    }

    void write(const RWByte* pt, RWSize count)
    {
        this->getSinkStream().write(pt, count);
    }

};

#endif // rw_stream_RWNativeDataToByteOutputStreamImp_h_
