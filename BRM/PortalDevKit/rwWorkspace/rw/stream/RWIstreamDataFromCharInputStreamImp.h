#ifndef rw_stream_RWIstreamDataFromCharInputStreamImp_h_
#define rw_stream_RWIstreamDataFromCharInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWIstreamDataFromCharInputStreamImp.h#1 $
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

#include <rw/stream/RWDataFromCharInputStreamImp.h>
#include <rw/stream/RWDataInputStream.h>
#include <rw/stream/pkgdefs.h>
#include <istream>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

template <class InputStream> class RWTStreambufFromByteCharInputStream;
typedef RWTStreambufFromByteCharInputStream<RWCharInputStream> RWStreambufFromCharInputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Reads data in US-ASCII format from a narrow character stream.
 *
 * The class RWIstreamDataFromCharInputStreamImp reads data in US-ASCII
 * format from a narrow character stream. The
 * RWOstreamDataToCharOutputStreamImp or iostreams \b std::ostream class
 * generates the format being read. Implements the body idiom from the
 * handle-body pattern.
 */
class RW_STREAM_GLOBAL RWIstreamDataFromCharInputStreamImp : public RWDataFromCharInputStreamImp
{

public:

    typedef std::streambuf::traits_type traits_type;
    typedef std::streambuf::int_type    int_type;

    /**
     * Constructs an RWIstreamDataFromCharInputStreamImp instance that uses
     * \a source as its source of narrow characters, and returns a handle to
     * it. Throws no exceptions.
     *
     * \param source
     * The narrow character stream that is used as the source of characters.
     */
    static RWDataInputStream make(const RWCharInputStream& source)
    {
        return RWDataInputStream(new RWIstreamDataFromCharInputStreamImp(source));
    }

    /**
     * Constructs an RWIstreamDataFromCharInputStreamImp instance that uses
     * \a source as its source of narrow characters, and returns a handle to
     * it. Throws no exceptions.
     *
     * \param source
     * The narrow character stream that is used as the source of characters.
     *
     * \param formatter
     * An object that can be used to modify the format recognized by the
     * stream. This object is initialized by the stream and then returned to
     * the caller.
     */
    static RWDataInputStream make(const RWCharInputStream& source, std::ios*& formatter)
    {
        return RWDataInputStream(new RWIstreamDataFromCharInputStreamImp(source, formatter));
    }

    //--Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWIstreamDataFromCharInputStreamImp();

    /**
     * Forwards the close() call to the next processing narrow character
     * input stream.
     */
    virtual void close();

    /**
     * Returns \c true if either one of the embedded iostreams
     * \b std::istream objects, or the next processing narrow character
     * input stream object is in a bad state. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * Returns \c true if either one of the embedded iostreams
     * \b std::istream objects or the next processing narrow character input
     * stream object is in a failed state. Throws no exceptions.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if both the embedded iostreams \b std::istream
     * object, and the next processing narrow character input stream object
     * are in good state. Throws no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Returns \c true if either one of the embedded iostreams
     * \b std::istream objects or the next processing narrow character input
     * stream object is in an eof state. Throws no exceptions.
     */
    virtual bool isEof() const;

    /**
     * Returns the number of narrow characters that can be read from the
     * embedded iostreams \b std::istream object without blocking. Throws no
     * exceptions.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits narrow characters from the embedded iostreams
     * \b std::istream object if possible. The function returns the actual
     * number of narrow characters skipped, which can be any value between 0
     * and \a numUnits.
     *
     * \param numUnits
     * The number of narrow characters to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);

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

    /**
     * \copydoc RWDataInputStreamImp::getBools(bool*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getBools(bool* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getChars(char*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getChars(char* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getUnsignedChars(unsigned char*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getUnsignedChars(unsigned char* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getSignedChars(signed char*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getSignedChars(signed char* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getShorts(short*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getShorts(short* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getUnsignedShorts(unsigned short*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getUnsignedShorts(unsigned short* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getInts(int*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getInts(int* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getUnsignedInts(unsigned int*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getUnsignedInts(unsigned int* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getLongs(long*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getLongs(long* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getUnsignedLongs(unsigned long*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getUnsignedLongs(unsigned long* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getFloats(float*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getFloats(float* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getDoubles(double*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getDoubles(double* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getWchar_ts(wchar_t*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getWchar_ts(wchar_t* arrayPt, RWSize count);

#if !defined(RW_NO_LONG_LONG)
    /**
     * \copydoc RWDataInputStreamImp::getLongLongs(long long*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getLongLongs(long long* arrayPt, RWSize count);

    /**
     * \copydoc RWDataInputStreamImp::getUnsignedLongLongs(unsigned long long*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getUnsignedLongLongs(unsigned long long* arrayPt, RWSize count);
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * \copydoc RWDataInputStreamImp::getLongDoubles(long double*, RWSize)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
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

    /**
     * \copydoc RWDataInputStreamImp::getDelimitedString(char*, RWSize, char)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getDelimitedString(char* string, RWSize maxCount, char delim);

    /**
     * \copydoc RWDataInputStreamImp::getDelimitedWString(wchar_t*, RWSize, wchar_t)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getDelimitedWString(wchar_t* wstring, RWSize maxCount, wchar_t delim);

    /**
     * \copydoc RWDataInputStreamImp::getDelimitedUString(RWUChar*, RWSize, RWUChar)
     *
     * \exception RWIncompleteStreamOperation
     * Thrown when elements from the stream cannot be read.
     */
    virtual RWSize getDelimitedUString(RWUChar* ustring, RWSize maxCount, RWUChar delim);


protected:

    //--Throws no exceptions.
    /**
     * Initializes the reference to the narrow character stream that will be
     * used as the source of characters.
     *
     * \param sourceStream
     * The narrow character stream that will serve as the source of
     * characters.
     */
    RWIstreamDataFromCharInputStreamImp(const RWCharInputStream& sourceStream);

    //--Throws no exceptions.
    /**
     * Initializes the reference to the narrow character stream that will be
     * used as the source of characters.
     *
     * \param sourceStream
     * The narrow character stream that will serve as the source of
     * characters.
     *
     * \param formatter
     * An object that can be used to modify the format recognized by the
     * stream. This object is initialized by the stream and then returned to
     * the caller.
     */
    RWIstreamDataFromCharInputStreamImp(const RWCharInputStream& sourceStream,
                                        std::ios*& formatter);

    /**
     * Returns the embedded iostreams \b std::istream object that is used to
     * format data. Throws no exceptions.
     */
    std::istream& getIstream()
    {
        return RW_EXPOSE(is_);
    }

    /**
     * \copydoc getIstream()
     */
    const std::istream& getIstream() const
    {
        return is_;
    }

    /**
     * Returns the embedded iostreams \b std::istream object that is used to
     * format data.
     *
     * \exception RWExternalStreamException
     * Thrown if the embedded \b std::istream object is in a failed or bad
     * state.
     */
    std::istream& getCheckedIstream();

    /**
     * \copydoc getCheckedIstream()
     */
    const std::istream& getCheckedIstream() const;

    /**
     * Returns a reference to the \b std::ios base class of the embedded
     * \b std::istream object. The \b std::ios reference can then be used to
     * modify the format flags used by the embedded \b std::istream object
     * when decoding formatted US-ASCII representation of the data inserted
     * in this input stream.
     */
    std::ios& getIos()
    {
        return is_;
    }

private:

    RWTScopedPointer<RWStreambufFromCharInputStream> buf_;
    std::istream is_;

    bool fail_;
};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWIstreamDataFromCharInputStreamImp_h_
