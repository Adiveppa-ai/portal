#ifndef rw_stream_RWSynchronizedDataInputStreamImp_h_
#define rw_stream_RWSynchronizedDataInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWSynchronizedDataInputStreamImp.h#1 $
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
#include <rw/stream/RWFilteredDataInputStreamImp.h>
#include <rw/stream/pkgdefs.h>
#include <rw/sync/RWMutexLock.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Implementation of a simple lock stream that is used with a data input
 * stream.
 *
 * Class RWSynchronizedDataInputStreamImp implements a simple lock stream
 * that is used with data input stream. The stream locks its internal
 * synchronization mechanism before forwarding input requests to its
 * associated source stream, and then unlocks the internal synchronization
 * mechanism upon completion. The stream's internal synchronization
 * mechanism is locked using a guard object, ensuring its proper release in
 * the event that an exception is thrown.
 */
class RW_STREAM_GLOBAL RWSynchronizedDataInputStreamImp : public RWFilteredDataInputStreamImp
{

public:

    /**
     * Constructs an RWSynchronizedDataInputStreamImp instance that uses
     * \a sourceStream as its source of data, and returns a handle to it.
     * Throws no exceptions.
     *
     * \param sourceStream
     * The output stream that will serve as the source of data.
     */
    static RWDataInputStream make(const RWDataInputStream& sourceStream)
    {
        return RWDataInputStream(new RWSynchronizedDataInputStreamImp(sourceStream));
    }

    //--Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWSynchronizedDataInputStreamImp();

    /**
     * Calls close() on the next processing stream.
     */
    virtual void close();

    /**
     * If no data can be obtained from the input sequence, this function
     * returns \c true, otherwise it returns \c false. Throws no exceptions.
     */
    virtual bool isEof() const;

    /**
     * If the stream is in bad state, then this function returns \c true,
     * otherwise it returns \c false. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * If the stream is in fail state, then this function returns \c true,
     * otherwise it returns \c false. Throws no exceptions.
     */
    virtual bool isFail() const;

    /**
     * If the stream is in fail or bad state, then this function returns
     * \c false, otherwise it returns \c true. Throws no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Returns the number of bytes that can be read from the stream without
     * blocking. Throws no exceptions.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits bytes from the input sequence if possible. The
     * function returns the actual number of bytes skipped, which can be any
     * value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of bytes to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

    /**
     * Acquires the stream's internal synchronization mechanism. The
     * acquire() member function returns a handle to the next processing
     * stream.
     */
    virtual RWDataInputStream acquire();

    /**
     * Releases the stream's internal synchronization mechanism.
     */
    virtual void release();

    //--Forward reading a single 'bool' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'bool' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getBool(bool& value);

    //--Forward reading a single 'char' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'char' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getChar(char& value);

    //--Forward reading a single 'unsigned char' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'unsigned char' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getUnsignedChar(unsigned char& value);

    //--Forward reading a single 'signed char' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'signed char' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getSignedChar(signed char& value);


    //--Forward reading a single 'short' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'short' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getShort(short& value);

    //--Forward reading a single 'unsigned short' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'bool' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getUnsignedShort(unsigned short& value);

    //--Forward reading a single int value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'int' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getInt(int& value);

    //--Forward reading a single 'unsigned int' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'unsigned int' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getUnsignedInt(unsigned int& value);

    //--Forward reading a single 'long' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'long' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getLong(long& value);

    //--Forward reading a single 'unsigned long' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'unsigned long' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getUnsignedLong(unsigned long& value);

    //--Forward reading a single 'float' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'float' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getFloat(float& value);

    //--Forward reading a single 'double' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'double' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getDouble(double& value);

    //--Forward reading a single 'wchar_t' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'wchar_t' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getWchar_t(wchar_t& value);

#if !defined(RW_NO_LONG_LONG)

    //--Forward reading a single 'long long' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The 'long long' value to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getLongLong(long long& value);

    virtual void getUnsignedLongLong(unsigned long long& value);
#endif

#ifndef RW_NO_LONG_DOUBLE

    //--Forward reading a single 'long double' value to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The long 'double value' to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getLongDouble(long double& value);
#endif

    //--Forward reading a narrow character to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The narrow character to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getCharacter(char& value);

    //--Forward reading a wide character to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The wide character to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getWCharacter(wchar_t& value);

    //--Forward reading a unicode character to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The unicode character to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getUCharacter(RWUChar& value);

    //--Forward reading a size_t character to the attached source stream.
    //--
    //--Parameters:
    //--
    //--  'value': The size_t character to be read from the attached
    //--source stream.
    //--
    // Documented in base class.
    virtual void getSizeT(size_t& value);

    //--Forward reading an array of 'bool' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getBools(bool* arrayPt, RWSize count);

    //--Forward reading an array of 'char' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getChars(char* arrayPt, RWSize count);

    //--Forward reading an array of 'unsigned char' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getUnsignedChars(unsigned char* arrayPt, RWSize count);

    //--Forward reading an array of 'signed char' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getSignedChars(signed char* arrayPt, RWSize count);

    //--Forward reading an array of 'short' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getShorts(short* arrayPt, RWSize count);

    //--Forward reading an array of 'unsigned short' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getUnsignedShorts(unsigned short* arrayPt, RWSize count);

    //--Forward reading an array of 'int' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getInts(int* arrayPt, RWSize count);

    //--Forward reading an array of 'unsigned int' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getUnsignedInts(unsigned int* arrayPt, RWSize count);

    //--Forward reading an array of 'long' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getLongs(long* arrayPt, RWSize count);

    //--Forward reading an array of unsigned long element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getUnsignedLongs(unsigned long* arrayPt, RWSize count);

    //--Forward reading an array of 'float' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getFloats(float* arrayPt, RWSize count);

    //--Forward reading an array of 'double' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getDoubles(double* arrayPt, RWSize count);

    //--Forward reading an array of 'wchar_t' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getWchar_ts(wchar_t* arrayPt, RWSize count);

#if !defined(RW_NO_LONG_LONG)

    //--Forward reading an array of 'long long' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getLongLongs(long long* arrayPt, RWSize count);

    virtual RWSize getUnsignedLongLongs(unsigned long long* arrayPt, RWSize count);
#endif

#ifndef RW_NO_LONG_DOUBLE

    //--Forward reading an array of 'long double' element(s) to the attached source stream.
    //--The function returns the number of element(s) read;
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the first element of the array. The
    //--array must have been pre-allocated to contain at least 'count' elements.
    //--
    //--  'count': The number of element(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getLongDoubles(long double* arrayPt, RWSize count);
#endif

    //--Forward reading a string of narrow characters to the attached source stream.
    //--The function returns the number of narrow character(s) read;
    //--
    //--Parameters:
    //--
    //--  'string': A pointer to the first element of the string. The
    //--string must have been pre-allocated to contain at least 'count'
    //--narrow characters.
    //--
    //--  'count': The number of narrow character(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getString(char* string, RWSize count);

    //--Forward reading a string of wide characters to the attached source stream.
    //--The function returns the number of wide character(s) read;
    //--
    //--Parameters:
    //--
    //--  'wstring': A pointer to the first element of the string. The
    //--string must have been pre-allocated to contain at least 'count'
    //--wide characters.
    //--
    //--  'count': The number of wide character(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getWString(wchar_t* wstring, RWSize count);

    //--Forward reading a string of unicode characters to the attached source stream.
    //--The function returns the number of unicode character(s) read;
    //--
    //--Parameters:
    //--
    //--  'ustring': A pointer to the first element of the string. The
    //--string must have been pre-allocated to contain at least 'count'
    //--unicode characters.
    //--
    //--  'count': The number of unicode character(s) to be read from the stream.
    //--
    // Documented in base class.
    virtual RWSize getUString(RWUChar* ustring, RWSize count);

    //--Forward reading narrow character(s) from the stream until the last character read is equal
    //--to 'delim', or 'maxCount' narrow character(s) have been read, or the
    //--end of the input sequence is reached. The narrow character(s) read are stored in
    //--'string'. The function returns the actual number of narrow character(s)
    //--read from the stream.
    //--
    //--Parameters:
    //--
    //--  'string': A pointer to the string receiving the narrow character(s) extracted
    //--from the stream.
    //--
    //--  'maxCount': The maximum number of narrow character(s) to be read.
    //--
    //--  'delim': The narrow character used as a delimiter.
    //--
    // Documented in base class.
    virtual RWSize getDelimitedString(char* string, RWSize maxCount, char delim);

    //--Forward reading wide character(s) from the stream until the last character read is equal
    //--to 'delim', or 'maxCount' wide character(s) have been read, or the
    //--end of the input sequence is reached. The wide character(s) read are stored in
    //--'wstring'. The function returns the actual number of wide character(s)
    //--read from the stream.
    //--
    //--Parameters:
    //--
    //--  'wstring': A pointer to the string receiving the wide character(s) extracted
    //--from the stream.
    //--
    //--  'maxCount': The maximum number of wide character(s) to be read.
    //--
    //--  'delim': The wide character used as a delimiter.
    //--
    // Documented in base class.
    virtual RWSize getDelimitedWString(wchar_t* wstring, RWSize maxCount, wchar_t delim);

    //--Forward reading unicode character(s) from the stream until the last character read is equal
    //--to 'delim', or 'maxCount' unicode character(s) have been read, or the
    //--end of the input sequence is reached. The unicode character(s) read are stored in
    //--'ustring'. The function returns the actual number of unicode character(s)
    //--read from the stream.
    //--
    //--Parameters:
    //--
    //--  'ustring': A pointer to the string receiving the unicode character(s) extracted
    //--  from the stream.
    //--
    //--  'maxCount': The maximum number of unicode character(s) to be read.
    //--
    //--  'delim': The unicode character used as a delimiter.
    //--
    // Documented in base class.
    virtual RWSize getDelimitedUString(RWUChar* ustring, RWSize maxCount, RWUChar delim);

protected:

    //--  Throws no exceptions.
    /**
     * Initializes the reference to the input stream that will be used as
     * the source of data.
     *
     * \param sourceStream
     * The input stream that will serve as the source of data.
     */
    RWSynchronizedDataInputStreamImp(const RWDataInputStream& sourceStream);

    // RWMutexLock should come from the synchronization package
    /**
     * Returns the stream's internal synchronization mechanism. Throws no
     * exception.
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
RWSynchronizedDataInputStreamImp::getStreamMutex()
{
    return RW_EXPOSE(mutex_);
}

inline RWMutexLock&
RWSynchronizedDataInputStreamImp::getStreamMutex() const
{
    return RW_EXPOSE(const_cast<RWMutexLock&>(mutex_));
}

#endif // rw_stream_RWSynchronizedDataInputStreamImp_h_
