#ifndef rw_stream_RWNativeDataFromByteInputStreamImp_h_
#define rw_stream_RWNativeDataFromByteInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWNativeDataFromByteInputStreamImp.h#1 $
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

#include <rw/stream/RWDataFromByteInputStreamImp.h>
#include <rw/stream/RWDataInputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Reads data in native format from a binary stream.
 *
 * The class RWNativeDataFromByteInputStreamImp reads data in native format
 * from a binary stream. It implements the body idiom from the handle-body
 * pattern.
 */
class RW_STREAM_GLOBAL RWNativeDataFromByteInputStreamImp : public RWDataFromByteInputStreamImp
{

public:

    /**
     * Constructs an RWNativeDataFromByteInputStreamImp instance that uses
     * \a source as the source of bytes, and returns a handle to it. Throws
     * no exceptions.
     *
     * \param source
     * The binary stream that is used as the source of bytes.
     */
    static RWDataInputStream make(const RWByteInputStream& source)
    {
        return RWDataInputStream(new RWNativeDataFromByteInputStreamImp(source));
    }

    //--Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWNativeDataFromByteInputStreamImp();

    // Documented in base class.
    virtual void getBool(bool& value);

    // Documented in base class.
    virtual void getChar(char& value);

    // Documented in base class.
    virtual void getUnsignedChar(unsigned char& value);

    // Documented in base class.
    virtual void getSignedChar(signed char& value);

    // Documented in base class.
    virtual void getShort(short& value);

    // Documented in base class.
    virtual void getUnsignedShort(unsigned short& value);

    // Documented in base class.
    virtual void getInt(int& value);

    // Documented in base class.
    virtual void getUnsignedInt(unsigned int& value);

    // Documented in base class.
    virtual void getLong(long& value);

    // Documented in base class.
    virtual void getUnsignedLong(unsigned long& value);

    // Documented in base class.
    virtual void getFloat(float& value);

    // Documented in base class.
    virtual void getDouble(double& value);

    // Documented in base class.
    virtual void getWchar_t(wchar_t& value);

#if !defined(RW_NO_LONG_LONG)
    // Documented in base class.
    virtual void getLongLong(long long& value);

    // Documented in base class.
    virtual void getUnsignedLongLong(unsigned long long& value);
#endif

#ifndef RW_NO_LONG_DOUBLE
    // Documented in base class.
    virtual void getLongDouble(long double& value);
#endif

    // Documented in base class.
    virtual void getCharacter(char& value);

    // Documented in base class.
    virtual void getWCharacter(wchar_t& value);

    // Documented in base class.
    virtual void getUCharacter(RWUChar& value);

    // Documented in base class.
    virtual void getSizeT(size_t& value);

    //--Reads an array of 'bool' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getBools(bool* arrayPt, RWSize count);

    //--Reads an array of 'char' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getChars(char* arrayPt, RWSize count);

    //--Reads an array of 'unsigned char' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getUnsignedChars(unsigned char* arrayPt, RWSize count);

    //--Reads an array of 'signed char' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getSignedChars(signed char* arrayPt, RWSize count);

    //--Reads an array of 'short' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getShorts(short* arrayPt, RWSize count);

    //--Reads an array of 'unsigned short' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getUnsignedShorts(unsigned short* arrayPt, RWSize count);

    //--Reads an array of 'int' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getInts(int* arrayPt, RWSize count);

    //--Reads an array of 'unsigned int' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getUnsignedInts(unsigned int* arrayPt, RWSize count);

    //--Reads an array of 'long' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getLongs(long* arrayPt, RWSize count);

    //--Reads an array of 'unsigned long' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getUnsignedLongs(unsigned long* arrayPt, RWSize count);

    //--Reads an array of 'float' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getFloats(float* arrayPt, RWSize count);

    //--Reads an array of 'double' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getDoubles(double* arrayPt, RWSize count);

    //--Reads an array of 'wchar_t' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getWchar_ts(wchar_t* arrayPt, RWSize count);

#if !defined(RW_NO_LONG_LONG)
    //--Reads an array of 'long long' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getLongLongs(long long* arrayPt, RWSize count);

    // Documented in base class.
    virtual RWSize getUnsignedLongLongs(unsigned long long* arrayPt, RWSize count);
#endif

#ifndef RW_NO_LONG_DOUBLE
    //--Reads an array of 'long double' value(s) from the stream. The array must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'arrayPt': A pointer to the array's first element.
    //
    // Documented in base class.
    virtual RWSize getLongDoubles(long double* arrayPt, RWSize count);
#endif

    //--Reads a narrow character string from the stream. The string must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'string': A pointer to the string's first element.
    //
    // Documented in base class.
    virtual RWSize getString(char* string, RWSize count);

    //--Reads a wide character string from the stream. The string must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'wstring': A pointer to the string's first element.
    //
    // Documented in base class.
    virtual RWSize getWString(wchar_t* wstring, RWSize count);

    //--Reads a unicode character string from the stream. The string must have
    //--been pre-allocated to contain at least 'count' elements.
    //--The function returns the number of elements read.
    //--
    //--Parameters:
    //--
    //--  'ustring': A pointer to the string's first element.
    //
    // Documented in base class.
    virtual RWSize getUString(RWUChar* arrayPt, RWSize count);

    //--Reads narrow character(s) from the stream until the last character read is equal
    //--to 'delim', or 'maxCount' narrow character(s) have been read, or the
    //--end of the input sequence is reached. The narrow character(s) read are stored in
    //--'string'. The function returns the actual number of narrow character(s)
    //--read from the stream.
    //--
    //--Parameters:
    //--
    //--  'string': A pointer to the string receiving the narrow character(s) extracted
    //--  from the stream.
    //--
    //--  'maxCount': The maximum number of narrow character(s) to be read.
    //--
    //--  'delim': The narrow character used as a delimiter.
    //
    // Documented in base class.
    virtual RWSize getDelimitedString(char* string, RWSize maxCount, char delim);

    //--Reads wide character(s) from the stream until the last character read is equal
    //--to 'delim', or 'maxCount' wide character(s) have been read, or the
    //--end of the input sequence is reached. The wide character(s) read are stored in
    //--'wstring'. The function returns the actual number of wide character(s)
    //--read from the stream.
    //--
    //--Parameters:
    //--
    //--  'wstring': A pointer to the string receiving the wide character(s) extracted
    //--  from the stream.
    //--
    //--  'maxCount': The maximum number of wide character(s) to be read.
    //--
    //--  'delim': The wide character used as a delimiter.
    //
    // Documented in base class.
    virtual RWSize getDelimitedWString(wchar_t* wstring, RWSize maxCount, wchar_t delim);

    //--Reads unicode character(s) from the stream until the last character read is equal
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
    //
    // Documented in base class.
    virtual RWSize getDelimitedUString(RWUChar* ustring, RWSize maxCount, RWUChar delim);


protected:

    //--Throws no exceptions.
    /**
     * Initializes the reference to the binary stream that will be used as
     * the source of bytes.
     *
     * \param sourceStream
     * The binary stream that will serve as the source of bytes.
     */
    RWNativeDataFromByteInputStreamImp(const RWByteInputStream& sourceStream)
        : RWDataFromByteInputStreamImp(sourceStream)
    {
        ;
    }

private:

    RWByte read()
    {
        return this->getSourceStream().read();
    }

    RWSize read(RWByte* pt, RWSize count)
    {
        return this->getSourceStream().read(pt, count);
    }

    RWSize readUntil(RWByte* pt, RWSize maxSize, RWByte delim)
    {
        return this->getSourceStream().readUntil(pt, maxSize, delim);
    }

};

#endif // rw_stream_RWNativeDataFromByteInputStreamImp_h_
