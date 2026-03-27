#ifndef rw_serial_RWDataToVirtualOutputStreamImp_h_
#define rw_serial_RWDataToVirtualOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWDataToVirtualOutputStreamImp.h#1 $
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


//--Abstract base class for all the data output stream
/**
 * \ingroup serialization_package
 *
 * \brief
 * Adapter class that allows virtual output stream class RWvostream to be
 * used where data output stream class RWDataOutputStream is required.
 *
 * An adapter class that allows an Essential Tools Module virtual output
 * stream (RWvostream) to be used where an RWDataOutputStream is required.
 * Implements the body idiom from the handle-body pattern.
 *
 * \example
 * \code
 * // Write data to a virtual stream.
 *
 * #include <rw/serial/RWDataToVirtualOutputStreamImp.h>
 * #include <rw/pstream.h>
 * #include <iostream.h>
 * #include <fstream.h>
 *
 * int main() {
 *   ofstream of;
 *   of.open("RWDataToVirtualOutputStreamImp.out", ios::out);
 *
 *   RWpostream pstrm(of);
 *
 *   RWDataOutputStream out =
 *     RWDataToVirtualOutputStreamImp::make(pstrm);
 *
 *   int i = 5;
 *   out << i;
 *
 *   return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_SERIAL_SYMBOLIC RWDataToVirtualOutputStreamImp : public RWDataOutputStreamImp
{
protected:
    RWvostream& vstrm_;

    /**
     * Constructs an RWDataToVirtualOutputStreamImp instance that adapts the
     * RW virtual output stream instance \a vstrm to the
     * RWDataOutputStreamImp interface. Throws no exceptions.
     *
     * \param vstrm
     * The virtual output stream being adapted.
     */
    RWDataToVirtualOutputStreamImp(RWvostream& vstrm)
        : vstrm_(vstrm)
    { }

public:

    virtual ~RWDataToVirtualOutputStreamImp()
    {
#if (__SUNPRO_CC == 0x530 || __SUNPRO_CC == 0x540) && defined(__SunOS_5_8)
        // This flush() is needed only for solaris8 64bit builds, when using the
        // SunPro 5.3 or 5.4 compilers.  There is no way to distinguish between
        // 64- and 32-bit builds here, so the 32-bit machines will be burdened
        // with this extra flush as well.
        vstrm_.flush();
#endif
    }

    /**
     * Returns an RWDataToVirtualOutputStreamImp instance that adapts the RW
     * virtual output stream instance \a vstrm to the RWDataOutputStreamImp
     * interface. Throws no exceptions.
     *
     * \param vstrm
     * The virtual output stream being adapted.
     */
    static RWDataOutputStream make(RWvostream& vstrm)
    {
        return RWDataOutputStream(new RWDataToVirtualOutputStreamImp(vstrm));
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
    virtual void          flush()
    {
        /*vstrm_.flush();*/
    }

    /**
     * Writes a \c bool value to the stream.
     *
     * \param value
     * The \c bool value to be written to the stream.
     */
    virtual void putBool(bool value)
    {
        vstrm_.put(value);
    }

    /**
     * Writes a \c char value to the stream.
     *
     * \param value
     * The \c char value to be written to the stream.
     */
    virtual void putChar(char value)
    {
        vstrm_ << value;
    }

    /**
     * Writes an <tt>unsigned char</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned char</tt> value to be written to the stream.
     */
    virtual void putUnsignedChar(unsigned char value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a <tt>signed char</tt> value to the stream.
     *
     * \param value
     * The <tt>signed char</tt> value to be written to the stream.
     */
    virtual void putSignedChar(signed char value)
    {
        vstrm_ << (int)value;
    }

    /**
     * Writes a \c short value to the stream.
     *
     * \param value
     * The \c short value to be written to the stream.
     */
    virtual void putShort(short value)
    {
        vstrm_ << value;
    }

    /**
     * Writes an <tt>unsigned short</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned short</tt> value to be written to the stream.
     */
    virtual void putUnsignedShort(unsigned short value)
    {
        vstrm_ << value;
    }

    /**
     * Writes an \c int value to the stream.
     *
     * \param value
     * The \c int value to be written to the stream.
     */
    virtual void putInt(int value)
    {
        vstrm_ << value;
    }

    /**
     * Writes an <tt>unsigned int</tt> value to the stream.
     *
     * \param value
     * The <tt>unsigned int</tt> value to be written to the stream.
     */
    virtual void putUnsignedInt(unsigned int value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a \c long value to the stream.
     *
     * \param value
     * The \c long value to be written to the stream.
     */
    virtual void putLong(long value)
    {
        vstrm_ << value;
    }

    //--Writes an 'unsigned long' value to the stream.
    //--Parameter 'value' is the 'unsigned long' value to be written to the stream.
    virtual void putUnsignedLong(unsigned long value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a \c float value to the stream.
     *
     * \param value
     * The \c float value to be written to the stream.
     */
    virtual void putFloat(float value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a \c double value to the stream.
     *
     * \param value
     * The \c double value to be written to the stream.
     */
    virtual void putDouble(double value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a \c wchar_t value to the stream.
     *
     * \param value
     * The \c wchar_t value to be written to the stream.
     */
    virtual void putWchar_t(wchar_t value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a \c TinyCharacter value to the stream.
     *
     * \param value
     * The \c TinyCharacter value to be written to the stream.
     */
    virtual void putCharacter(char value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a \c WideCharacter value to the stream.
     *
     * \param value
     * The \c WideCharacter value to be written to the stream.
     */
    virtual void putWCharacter(wchar_t value)
    {
        vstrm_ << value;
    }

    /**
     * Writes a \c UnicodeCharacter value to the stream.
     *
     * \param value
     * The \c UnicodeCharacter value to be written to the stream.
     */
    virtual void putUCharacter(RWUChar value)
    {
        vstrm_ << value;
    }

    //--Writes a 'size_t' value to the stream.
    //--Parameter 'value' is the 'size_t' value to be written to the stream.
    virtual void putSizeT(size_t value)
    {
        vstrm_.putSizeT(value);
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes a <tt>long long</tt> value to the stream.
     *
     * \param value
     * The <tt>long long</tt> value to be written to the stream.
     */
    virtual void putLongLong(long long value)
    {
        vstrm_ << value;
    }
    virtual void putUnsignedLongLong(unsigned long long value)
    {
        vstrm_ << value;
    }
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Writes a <tt>long double</tt> value to the stream.
     *
     * \param value
     * The <tt>long double</tt> value to be written to the stream.
     */
    virtual void putLongDouble(long double value)
    {
        vstrm_ << value;
    }
#endif

    /**
     * Writes an array of \c bool values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putBools(const bool* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c char values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putChars(const char* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of <tt>unsigned char</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putUnsignedChars(const unsigned char* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of <tt>signed char</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putSignedChars(const signed char* arrayPt, RWSize count)
    {
        vstrm_.put(reinterpret_cast<const char*>(arrayPt), count);
    }

    /**
     * Writes an array of \c short values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putShorts(const short* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of <tt>unsigned short</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putUnsignedShorts(const unsigned short* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c int values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putInts(const int* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of <tt>unsigned int</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putUnsignedInts(const unsigned int* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c long values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putLongs(const long* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of <tt>unsigned long</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putUnsignedLongs(const unsigned long* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c float values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putFloats(const float* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c double values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putDoubles(const double* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c wchar_t values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putWchar_ts(const wchar_t* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c char values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putString(const char* arrayPt, RWSize count)
    {
        vstrm_.putString(arrayPt, count);
    }

    /**
     * Writes an array of \c char values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putWString(const wchar_t* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

    /**
     * Writes an array of \c char values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putUString(const unsigned short* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }

#if !defined(RW_NO_LONG_LONG)
    /**
     * Writes an array of <tt>long long</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putLongLongs(const long long* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }
    virtual void putUnsignedLongLongs(const unsigned long long* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }
#endif

#ifndef RW_NO_LONG_DOUBLE
    /**
     * Writes an array of <tt>long double</tt> values to the stream.
     *
     * \param arrayPt
     * A pointer to the array's first element.
     *
     * \param count
     * The number of element(s) to be written to the stream.
     */
    virtual void putLongDoubles(const long double* arrayPt, RWSize count)
    {
        vstrm_.put(arrayPt, count);
    }
#endif


};

#endif // rw_serial_RWDataToVirtualOutputStreamImp_h_
