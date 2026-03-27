#ifndef rw_stream_RWvostreamToDataOutputStream_h_
#define rw_stream_RWvostreamToDataOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWvostreamToDataOutputStream.h#1 $
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
#include <rw/stream/pkgdefs.h>
#include <rw/vstream.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Adaptor class that adapts the Rogue Wave virtual stream interface to the
 * Rogue Wave data output stream interface.
 *
 * The class RWvostreamToDataOutputStream is an adaptor class that adapts
 * the Rogue Wave virtual stream interface to the new Rogue Wave data output
 * stream interface. Requests made through the Rogue Wave virtual output
 * stream interface are forwarded to the embedded RWDataOutputStream handle.
 */
class RW_STREAM_GLOBAL RWvostreamToDataOutputStream : public RWvostream
{

public:

    /**
     * Initializes the reference to the data stream that will be used as the
     * sink of data.
     *
     * \param sinkStream
     * The data stream that will serve as the sink of data.
     */
    RWvostreamToDataOutputStream(const RWDataOutputStream& sinkStream)
        : sinkStream_(sinkStream)
    {
        ;
    }

    /**
     * Destructor.
     */
    virtual ~RWvostreamToDataOutputStream();

    // Documented in base class.
    virtual int eof();

    // Documented in base class.
    virtual int fail();

    // Documented in base class.
    virtual int bad();

    // Documented in base class.
    virtual int good();

    // Documented in base class.
    virtual int rdstate();

    /**
     * Not supported. RWDataOutputStream does not provide a mechanism for
     * setting/clearing the underlying state. Calls to this function are
     * ignored.
     */
    virtual void clear(int v = 0);

    // Documented in base class.
    virtual RWvostream& putString(const char* s, size_t n);

    // Documented in base class.
    virtual RWvostream& putChars(const char* s, size_t n);

    // Documented in base class.
    virtual RWvostream& put(char c);

    // Documented in base class.
    virtual RWvostream& putChar(char c);

    // Documented in base class.
    virtual RWvostream& put(signed char c);

    // Documented in base class.
    virtual RWvostream& putChar(signed char c);

    // Documented in base class.
    virtual RWvostream& put(unsigned char c);

    // Documented in base class.
    virtual RWvostream& putChar(unsigned char c);

    // Documented in base class.
    virtual RWvostream& put(wchar_t wc);

    // Documented in base class.
    virtual RWvostream& putChar(wchar_t wc);

    // Documented in base class.
    virtual RWvostream& put(bool b);

    // Documented in base class.
    virtual RWvostream& put(int i);

    // Documented in base class.
    virtual RWvostream& put(unsigned int i);

    // Documented in base class.
    virtual RWvostream& put(short i);

    // Documented in base class.
    virtual RWvostream& put(unsigned short i);

    // Documented in base class.
    virtual RWvostream& put(long i);

    // Documented in base class.
    virtual RWvostream& put(unsigned long i);

#if !defined(RW_NO_LONG_LONG)
    // Documented in base class.
    virtual RWvostream& put(long long i);

    // Documented in base class.
    virtual RWvostream& put(unsigned long long i);
#endif

    // Documented in base class.
    virtual RWvostream& put(float f);

    // Documented in base class.
    virtual RWvostream& put(double d);


#ifndef RW_NO_LONG_DOUBLE
    // Documented in base class.
    virtual RWvostream& put(long double d);
#endif

    // Documented in base class.
    virtual RWvostream& flush();

    // Documented in base class.
    virtual RWvostream& put(const char* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const bool* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const wchar_t* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const signed char* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const unsigned char* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const short* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const unsigned short* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const int* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const unsigned int* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const long* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const unsigned long* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const float* v, size_t n);

    // Documented in base class.
    virtual RWvostream& put(const double* v, size_t n);

#ifndef RW_NO_LONG_DOUBLE
    // Documented in base class.
    virtual RWvostream&   put(const long double* v, size_t n);
#endif

#if !defined(RW_NO_LONG_LONG)
    // Documented in base class.
    virtual RWvostream&   put(const long long* v, size_t n);

    // Documented in base class.
    virtual RWvostream&   put(const unsigned long long* v, size_t n);
#endif

    // Documented in base class.
    virtual RWvostream&   putSizeT(size_t sz);

protected:

    /**
     * Returns a handle to the embedded data output stream that is used as
     * the sink of data. Throws no exceptions.
     */
    RWDataOutputStream& getSinkStream()
    {
        return RW_EXPOSE(sinkStream_);
    }

    /**
     * \copydoc getSinkStream()
     */
    const RWDataOutputStream& getSinkStream() const
    {
        return sinkStream_;
    }

private:

    // The data output stream used as the sink of data
    RWDataOutputStream sinkStream_;

};

#endif // rw_stream_RWvostreamToDataOutputStream_h_
