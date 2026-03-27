#ifndef rw_serial_RWDataFromVirtualInputStreamImp_h_
#define rw_serial_RWDataFromVirtualInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWDataFromVirtualInputStreamImp.h#1 $
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

#include <rw/serial/pkgdefs.h>
#include <rw/stream/stream.h>
#include <rw/vstream.h>


/**
 * \ingroup serialization_package
 *
 * \brief
 * Adapter class that allows virtual input stream class RWvistream to be
 * used where data input stream class RWDataInputStream is required.
 *
 * An adapter class that allows an Essential Tools Module virtual input
 * stream (RWvistream) to be used where an RWDataInputStream is required.
 * Implements the body idiom from the handle-body pattern.
 *
 * \example
 * \code
 * // Read data in using virtual streams.
 *
 * #include <rw/serial/RWDataFromVirtualInputStreamImp.h>
 * #include <rw/pstream.h>
 * #include <iostream.h>
 * #include <fstream.h>
 *
 * int main() {
 *   ifstream ifstrm;
 *   ifstrm.open("RWDataToVirtualOutputStreamImp.out",
 *     ios::in | ios::nocreate);
 *
 *   if (!ifstrm) {
 *     cout << "The input file does not exist."<< endl;
 *   }
 *
 *   else {
 *     RWpistream pstrm(ifstrm);
 *
 *     RWDataInputStream in =
 *       RWDataFromVirtualInputStreamImp::make(pstrm);
 *
 *     int j;
 *     in >> j;
 *     cout << j;
 *   }
 *   return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_SERIAL_SYMBOLIC RWDataFromVirtualInputStreamImp : public RWDataInputStreamImp
{
protected:
    RWvistream& vstrm_;

    /**
     * Constructs an RWDataFromVirtualInputStreamImp instance that adapts
     * the RW virtual input stream instance \a vstrm to the
     * RWDataInputStreamImp interface. Throws no exceptions.
     *
     * \param vstrm
     * The virtual input stream being adapted.
     */
    RWDataFromVirtualInputStreamImp(RWvistream& vstrm)
        : vstrm_(vstrm)
    { }

public:
    /**
     * Returns an RWDataFromVirtualInputStreamImp instance that adapts the
     * RW virtual input stream instance \a vstrm to the RWDataInputStreamImp
     * interface. Throws no exceptions.
     *
     * \param vstrm
     * The virtual input stream being adapted.
     */
    static RWDataInputStream make(RWvistream& vstrm)
    {
        return RWDataInputStream(new RWDataFromVirtualInputStreamImp(vstrm));
    }
    virtual int           eof()
    {
        return vstrm_.eof();
    }
    virtual bool     isFail() const
    {
        return vstrm_.fail() != 0;
    }
    virtual bool     isBad() const
    {
        return vstrm_.bad() != 0;
    }
    virtual bool     isGood() const
    {
        return vstrm_.good() != 0;
    }
    virtual int           rdstate()
    {
        return vstrm_.rdstate();
    }
    virtual void          clear(int v = 0)
    {
        vstrm_.clear(v);
    }

    /**
     * Closes the stream.
     */
    virtual void close()
    {
        /*vstrm_.close();*/
    }

    /**
     * Returns \c true to indicate that an input operation reached the end
     * of an input sequence. Throws no exceptions.
     */
    virtual bool isEof() const
    {
        return vstrm_.eof() != 0;
    }

    /**
     * Returns the number of available elements that can be read from the
     * stream without blocking. The type of the elements read is specified
     * by derived classes and can be one of the following: #RWByte, \c char,
     * #RWUChar, or \c wchar_t. Throws no exceptions.
     */
    virtual RWSize available() const
    {
        return 1;
    }

    /**
     * Skips \a numUnits elements from the input sequence, if possible. The
     * function returns the actual number of elements skipped, which can be
     * any value between \c 0 and \a numUnits. The type of the elements
     * skipped is specified by derived classes and can be one of the
     * following: #RWByte, \c char, #RWUChar, or \c wchar_t.
     *
     * \param numUnits
     * The number of elements to be skipped.
     */
    virtual RWSize skip(RWSize numUnits)
    {
        RW_UNUSED(numUnits);
        return 0;
    }

    /**
     * Reads a \c bool value from the stream.
     *
     * \param value
     * The \c bool value to be read from the stream.
     */
    virtual void getBool(bool& value)
    {
        vstrm_.get(value);
    }

    /**
     * Reads a \c char value from the stream.
     *
     * \param value
     * The \c char value to be read from the stream.
     */
    virtual void getChar(char& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads an <tt>unsigned char</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be read from the stream.
     */
    virtual void getUnsignedChar(unsigned char& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a <tt>signed char</tt> value from the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be read from the stream.
     */
    virtual void getSignedChar(signed char& value)
    {
        int valAsInt;
        vstrm_ >> valAsInt;
        value = (signed char)valAsInt;
    }

    /**
     * Reads a \c short value from the stream.
     *
     * \param value
     * The \c short value to be read from the stream.
     */
    virtual void getShort(short& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads an <tt>unsigned short</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be read from the stream.
     */
    virtual void getUnsignedShort(unsigned short& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads an \c int value from the stream.
     *
     * \param value
     * The \c int value to be read from the stream.
     */
    virtual void getInt(int& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads an <tt>unsigned int</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be read from the stream.
     */
    virtual void getUnsignedInt(unsigned int& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a \c long value from the stream.
     *
     * \param value
     * The \c long value to be read from the stream.
     */
    virtual void getLong(long& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads an <tt>unsigned long</tt> value from the stream.
     *
     * \param value
     * The <tt>unsigned long</tt> value to be read from the stream.
     */
    virtual void getUnsignedLong(unsigned long& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a \c float value from the stream.
     *
     * \param value
     * The \c float value to be read from the stream.
     */
    virtual void getFloat(float& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a \c double value from the stream.
     *
     * \param value
     * The \c double value to be read from the stream.
     */
    virtual void getDouble(double& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a \c wchar_t value from the stream.
     *
     * \param value
     * The \c wchar_t value to be read from the stream.
     */
    virtual void getWchar_t(wchar_t& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a \c TinyCharacter value from the stream.
     *
     * \param value
     * The \c TinyCharacter value to be read from the stream.
     */
    virtual void getCharacter(char& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a \c WideCharacter value from the stream.
     *
     * \param value
     * The \c WideCharacter value to be read from the stream.
     */
    virtual void getWCharacter(wchar_t& value)
    {
        vstrm_ >> value;
    }

    /**
     * Reads a \c UTF-16 Character value from the stream.
     *
     * \param value
     * The \c UnicodeCharacter value to be read from the stream.
     */
    virtual void getUCharacter(RWUChar& value)
    {
        vstrm_ >> value;
    }

    virtual void getSizeT(size_t& value)
    {
        vstrm_.getSizeT(value);
    };

#if !defined(RW_NO_LONG_LONG)
    /**
     * Reads a <tt>long long</tt> value from the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be read from the stream.
     */
    virtual void getLongLong(long long& value)
    {
        vstrm_ >> value;
    }

    virtual void getUnsignedLongLong(unsigned long long& value)
    {
        vstrm_ >> value;
    }
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Reads a <tt>long double</tt> value from the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be read from the stream.
     */
    virtual void getLongDouble(long double& value)
    {
        vstrm_ >> value;
    }
#endif

    /**
     * Reads an array of \c bool values from the stream. The array must have
     * been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getBools(bool* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of \c char values from the stream. The array must have
     * been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getChars(char* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of <tt>unsigned char</tt> values from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getUnsignedChars(unsigned char* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of <tt>signed char</tt> values from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements. Returns the number of elements read.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getSignedChars(signed char* arrayPt, RWSize count)
    {
        vstrm_.get((char*)arrayPt, count);
        return count;
    }

    /**
     * Reads an array of \c short values from the stream. The array must
     * have been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getShorts(short* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of <tt>unsigned short</tt> values from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getUnsignedShorts(unsigned short* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of \c int values from the stream. The array must have
     * been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getInts(int* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of <tt>unsigned int</tt> values from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getUnsignedInts(unsigned int* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of \c long values from the stream. The array must have
     * been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getLongs(long* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of <tt>unsigned long</tt> values from the stream. The
     * array must have been pre-allocated to contain at least \a count
     * elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getUnsignedLongs(unsigned long* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of \c float values from the stream. The array must
     * have been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getFloats(float* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of \c double values from the stream. The array must
     * have been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getDoubles(double* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads an array of \c wchar_t values from the stream. The array must
     * have been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getWchar_ts(wchar_t* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads a \c String value from the stream. The array must have been
     * pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getString(char* arrayPt, RWSize count)
    {
        vstrm_.getString(arrayPt, count + 1);
        return count;
    }

    /**
     * Reads a wide string value from the stream. The array must have been
     * pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getWString(wchar_t* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads a UTF-16 string value from the stream. The array must have been
     * pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getUString(RWUChar* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads a \c String value from the stream. The array must have been
     * pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     *
     * \param delim
     * The narrow character used as a delimiter.
     */
    virtual RWSize getDelimitedString(char* arrayPt, RWSize count, char delim = '\0')
    {
        RW_UNUSED(delim);
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads a wide string value from the stream. The array must have been
     * pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     *
     * \param delim
     * The wide character used as a delimiter.
     */
    virtual RWSize getDelimitedWString(wchar_t* arrayPt, RWSize count, wchar_t delim = L'\0')
    {
        RW_UNUSED(delim);
        vstrm_.get(arrayPt, count);
        return count;
    }

    /**
     * Reads a UTF-16 string value from the stream. The array must have been
     * pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     *
     * \param delim
     * The UTF-16 character used as a delimiter.
     */
    virtual RWSize getDelimitedUString(RWUChar* arrayPt, RWSize count, unsigned short delim)
    {
        RW_UNUSED(delim);
        vstrm_.get(arrayPt, count);
        return count;
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Reads an array of \c long \c long values from the stream. The array
     * must have been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getLongLongs(long long* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }
    virtual RWSize getUnsignedLongLongs(unsigned long long* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Reads an array of \c long \c double values from the stream. The array
     * must have been pre-allocated to contain at least \a count elements.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be read from the stream.
     */
    virtual RWSize getLongDoubles(long double* arrayPt, RWSize count)
    {
        vstrm_.get(arrayPt, count);
        return count;
    }
#endif

};

#endif // rw_serial_RWDataFromVirtualInputStreamImp_h_
