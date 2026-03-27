#ifndef rw_stream_RWDataOutputStream_h_
#define rw_stream_RWDataOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWDataOutputStream.h#1 $
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

#include <rw/stream/RWDataOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

// forward declaration
template <class StreamHandle, class FilteredStreamImp> class RWTStreamGuardImp;
class RWFilteredDataOutputStreamImp;


/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for all the data output stream implementation classes.
 *
 * Handle class for all the data output stream implementation classes.
 * Implements the handle idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWDataOutputStream : public RWHandleBase
{

public:

    /**
     * Constructor.
     */
    explicit RWDataOutputStream(RWDataOutputStreamImp* ptr)
        : RWHandleBase(ptr)
    {}

    /**
     * Copy constructor. Throws no exceptions.
     *
     * \param handle
     * A data stream handle used to initialize this handle.
     */
    RWDataOutputStream(const RWDataOutputStream& handle)
        : RWHandleBase(handle)
    {
        ;
    }

    //--virtual Destructor
    //--Throws no exceptions
    virtual ~RWDataOutputStream()
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A data stream handle used to initialize this handle.
     */
    RWDataOutputStream& operator=(const RWDataOutputStream& handle)
    {
        this->RWHandleBase::operator=(handle);
        return *this;
    }

    /**
     * Insertor executing a manipulator function. Throws no exceptions.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWDataOutputStream& operator<<(RWDataOutputStream & (*pf)(RWDataOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Insertor executing a manipulator function. Throws no exceptions.
     *
     * \param pf
     * The manipulator's function pointer.
     */
    RWDataOutputStream operator<<(RWDataOutputStream(*pf)(RWDataOutputStream&))
    {
        return pf(*this);
    }

    /**
     * Closes the stream.
     */
    void close()
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).close();
    }

    /**
     * Flushes the stream.
     */
    void flush()
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).flush();
    }

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * output operation. Throws no exceptions.
     */
    bool isBad() const
    {
        return static_cast<RWDataOutputStreamImp&>(this->body()).isBad();
    }

    /**
     * Returns \c true to indicate that an output operation failed to
     * generate the desired data. Throws no exceptions.
     */
    bool isFail() const
    {
        return static_cast<RWDataOutputStreamImp&>(this->body()).isFail();
    }

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    bool isGood() const
    {
        return static_cast<RWDataOutputStreamImp&>(this->body()).isGood();
    }

    /**
     * Writes a \c bool value to the stream.
     *
     * \param value
     * The \c bool value to be written to the stream.
     */
    RWDataOutputStream& operator<<(bool value)
    {
        this->putBool(value);
        return *this;
    }

    /**
     * Writes a \c char value to the stream.
     *
     * \param value
     * The \c char value to be written to the stream.
     */
    RWDataOutputStream& operator<<(char value)
    {
        this->putChar(value);
        return *this;
    }

    /**
     * Writes an <tt>unsigned char</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be written to the stream.
     */
    RWDataOutputStream& operator<<(unsigned char value)
    {
        this->putUnsignedChar(value);
        return *this;
    }

    /**
     * Writes a <tt>signed char</tt> value to the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be written to the stream.
     */
    RWDataOutputStream& operator<<(signed char value)
    {
        this->putSignedChar(value);
        return *this;
    }

    /**
     * Writes a \c short value to the stream.
     *
     * \param value
     * The \c short to be written to the stream.
     */
    RWDataOutputStream& operator<<(short value)
    {
        this->putShort(value);
        return *this;
    }

    /**
     * Writes an <tt>unsigned short</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> to be written to the stream.
     */
    RWDataOutputStream& operator<<(unsigned short value)
    {
        this->putUnsignedShort(value);
        return *this;
    }

    /**
     * Writes an \c int value to the stream.
     *
     * \param value
     * The \c int value to be written to the stream.
     */
    RWDataOutputStream& operator<<(int value)
    {
        this->putInt(value);
        return *this;
    }

    /**
     * Writes an <tt>unsigned int</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be written to the stream.
     */
    RWDataOutputStream& operator<<(unsigned int value)
    {
        this->putUnsignedInt(value);
        return *this;
    }

    /**
     * Writes a \c long value to the stream.
     *
     * \param value
     * The \c long value to be written to the stream.
     */
    RWDataOutputStream& operator<<(long value)
    {
        this->putLong(value);
        return *this;
    }

    /**
     * Writes an <tt>unsigned long</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be written to the stream.
     */
    RWDataOutputStream& operator<<(unsigned long value)
    {
        this->putUnsignedLong(value);
        return *this;
    }

    /**
     * Writes a \c float value to the stream.
     *
     * \param value
     * The \c float value to be written to the stream.
     */
    RWDataOutputStream& operator<<(float value)
    {
        this->putFloat(value);
        return *this;
    }

    /**
     * Writes a \c double value to the stream.
     *
     * \param value
     * The \c double value to be written to the stream.
     */
    RWDataOutputStream& operator<<(double value)
    {
        this->putDouble(value);
        return *this;
    }

    /**
     * Writes a \c wchar_t value to the stream.
     *
     * \param value
     * The \c wchar_t value to be written to the stream.
     */
    RWDataOutputStream& operator<<(wchar_t value)
    {
        this->putWchar_t(value);
        return *this;
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes a <tt>long long</tt> value to the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be written to the stream.
     */
    RWDataOutputStream& operator<<(long long value)
    {
        this->putLongLong(value);
        return *this;
    }
    //--Writes a 'unsigned long long' value to the stream.
    //--The parameter 'value' is the 'long long' value to be written to the stream.
    RWDataOutputStream& operator<<(unsigned long long value)
    {
        this->putUnsignedLongLong(value);
        return *this;
    }
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Writes a <tt>long double</tt> value to the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be written to the stream.
     */
    RWDataOutputStream& operator<<(long double value)
    {
        this->putLongDouble(value);
        return *this;
    }
#endif

    /**
     * Writes a \c bool value to the stream.
     *
     * \param value
     * The \c bool value to be written to the stream.
     */
    void putBool(bool value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putBool(value);
    }

    /**
     * Writes a \c char value to the stream.
     *
     * \param value
     * The \c char value to be written to the stream.
     */
    void putChar(char value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putChar(value);
    }

    /**
     * Writes an <tt>unsigned char</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be written to the stream.
     */
    void putUnsignedChar(unsigned char value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedChar(value);
    }

    /**
     * Writes a <tt>signed char</tt> value to the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be written to the stream.
     */
    void putSignedChar(signed char value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putSignedChar(value);
    }

    /**
     * Writes a \c short value to the stream.
     *
     * \param value
     * The \c short value to be written to the stream.
     */
    void putShort(short value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putShort(value);
    }

    /**
     * Writes an <tt>unsigned short</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be written to the stream.
     */
    void putUnsignedShort(unsigned short value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedShort(value);
    }

    /**
     * Writes an \c int value to the stream.
     *
     * \param value
     * The \c int value to be written to the stream.
     */
    void putInt(int value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putInt(value);
    }

    /**
     * Writes an <tt>unsigned int</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be written to the stream.
     */
    void putUnsignedInt(unsigned int value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedInt(value);
    }

    /**
     * Writes a \c long value to the stream.
     *
     * \param value
     * The \c long value to be written to the stream.
     */
    void putLong(long value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putLong(value);
    }

    /**
     * Writes an <tt>unsigned long</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be written to the stream.
     */
    void putUnsignedLong(unsigned long value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedLong(value);
    }

    /**
     * Writes a \c float value to the stream.
     *
     * \param value
     * The \c float value to be written to the stream.
     */
    void putFloat(float value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putFloat(value);
    }

    /**
     * Writes a \c double value to the stream.
     *
     * \param value
     * The \c double value to be written to the stream.
     */
    void putDouble(double value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putDouble(value);
    }

    /**
     * Writes a \c wchar_t value to the stream.
     *
     * \param value
     * The \c wchar_t value to be written to the stream.
     */
    void putWchar_t(wchar_t value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putWchar_t(value);
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes a <tt>long long</tt> value to the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be written to the stream.
     */
    void putLongLong(long long value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putLongLong(value);
    }
    void putUnsignedLongLong(unsigned long long value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedLongLong(value);
    }
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Writes a <tt>long double</tt> value to the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be written to the stream.
     */
    void putLongDouble(long double value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putLongDouble(value);
    }
#endif

    /**
     * Writes a narrow character to the stream.
     *
     * \param value
     * The narrow character to be written to the stream.
     */
    virtual void putCharacter(char value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putCharacter(value);
    }
    /**
     * Writes a wide character to the stream.
     *
     * \param value
     * The wide character to be written to the stream.
     */
    virtual void putWCharacter(wchar_t value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putWCharacter(value);
    }

    /**
     * Writes a UTF-16 character to the stream.
     *
     * \param value
     * The UTF-16 character to be written to the stream.
     */
    virtual void putUCharacter(RWUChar value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUCharacter(value);
    }

    /**
     * Writes a \c size_t value to the stream.
     *
     * \param value
     * The \c size_t value to be written to the stream.
     */
    virtual void putSizeT(size_t value)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putSizeT(value);
    }

    /**
     * Writes an array of \c bool value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putBools(const bool* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putBools(arrayPt, count);
    }

    /**
     * Writes an array of \c char value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putChars(const char* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putChars(arrayPt, count);
    }

    /**
     * Writes an array of \c unsigned \c char value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putUnsignedChars(const unsigned char* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedChars(arrayPt, count);
    }

    /**
     * Writes an array of \c signed \c char value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putSignedChars(const signed char* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putSignedChars(arrayPt, count);
    }

    /**
     * Writes an array of \c short value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putShorts(const short* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putShorts(arrayPt, count);
    }

    /**
     * Writes an array of \c unsigned \c short value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putUnsignedShorts(const unsigned short* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedShorts(arrayPt, count);
    }

    /**
     * Writes an array of \c int value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putInts(const int* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putInts(arrayPt, count);
    }

    /**
     * Writes an array of \c unsigned \c int value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putUnsignedInts(const unsigned int* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedInts(arrayPt, count);
    }

    /**
     * Writes an array of \c long value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putLongs(const long* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putLongs(arrayPt, count);
    }

    /**
     * Writes an array of \c unsigned \c long value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putUnsignedLongs(const unsigned long* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedLongs(arrayPt, count);
    }

    /**
     * Writes an array of \c float value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putFloats(const float* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putFloats(arrayPt, count);
    }

    /**
     * Writes an array of \c double value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putDoubles(const double* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putDoubles(arrayPt, count);
    }

    /**
     * Writes an array of \c wchar_t value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putWchar_ts(const wchar_t* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putWchar_ts(arrayPt, count);
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes an array of <tt>long long</tt> value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putLongLongs(const long long* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putLongLongs(arrayPt, count);
    }
    void putUnsignedLongLongs(const unsigned long long* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUnsignedLongLongs(arrayPt, count);
    }
#endif

#if !defined(RW_NO_LONG_DOUBLE)
    /**
     * Writes an array of \c long \c double value(s) to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    void putLongDoubles(const long double* arrayPt, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putLongDoubles(arrayPt, count);
    }
#endif

    /**
     * Writes a narrow character string, including embedded nulls, starting
     * at \a string to the stream.
     *
     * \param string
     * A pointer to the string's first narrow character.
     *
     * \param count
     * The number of narrow characters to be written to the stream.
     */
    void putString(const char* string, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putString(string, count);
    }

    /**
     * Writes a wide character string, including embedded nulls, starting at
     * \a wstring to the stream.
     *
     * \param wstring
     * A pointer to the string's first narrow character.
     *
     * \param count
     * The number of wide characters to be written to the stream.
     */
    void putWString(const wchar_t* wstring, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putWString(wstring, count);
    }

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
    void putUString(const RWUChar* ustring, RWSize count)
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).putUString(ustring, count);
    }

private:

    //--Acquires the synchronization mechanism provided by a stream concrete
    //--implementation. The 'acquire()' member function returns a handle to the
    //--data stream that should be used for output operation after acquiring
    //--the synchronization mechanism. This function is only used by an instance of
    //--class 'RWGuardedDataOutputStreamImp'.
    RWDataOutputStream acquire()
    {
        return static_cast<RWDataOutputStreamImp&>(this->body()).acquire();
    }

    //--Releases the synchronization mechanism provided by a stream concrete
    //--implementation. This function is only used by instance of
    //--class 'RWGuardedDataOutputStreamImp'.
    void release()
    {
        static_cast<RWDataOutputStreamImp&>(this->body()).release();
    }

    friend class RWTStreamGuardImp<RWDataOutputStream, RWFilteredDataOutputStreamImp>;
};

/**
 * \relates RWDataOutputStream
 *
 * Manipulator that flushes a data output stream.
 *
 * \param stream
 * The data stream to be flushed.
 */
inline RWDataOutputStream& rwFlush(RWDataOutputStream& stream)
{
    stream.flush();
    return stream;
}

/**
 * \relates RWDataOutputStream
 *
 * Manipulator that writes a narrow end-of-line control character to the
 * stream.
 *
 * \param stream
 * The data stream to which the manipulator applies.
 */
inline RWDataOutputStream& rwEndl(RWDataOutputStream& stream)
{
    stream.putCharacter('\n');
    return stream;
}

/**
 * \relates RWDataOutputStream
 *
 * Manipulator that writes a narrow end of string character to the stream.
 * to the stream.
 *
 * \param stream
 * The data stream to which the manipulator applies.
 */
inline RWDataOutputStream& rwEnds(RWDataOutputStream& stream)
{
    stream.putCharacter('\0');
    return stream;
}

/**
 * \relates RWDataOutputStream
 *
 * Manipulator that writes a wide end-of-line control character to the
 * stream.
 *
 * \param stream
 * The data stream to which the manipulator applies.
 */
inline RWDataOutputStream& rwWEndl(RWDataOutputStream& stream)
{
    stream.putWCharacter(L'\n');
    return stream;
}

/**
 * \relates RWDataOutputStream
 *
 * Manipulator that writes a wide end of string character to the stream. to
 * the stream.
 *
 * \param stream
 * The data stream to which the manipulator applies.
 */
inline RWDataOutputStream& rwWEnds(RWDataOutputStream& stream)
{
    stream.putWCharacter(L'\0');
    return stream;
}

#endif // rw_stream_RWDataOutputStream_h_
