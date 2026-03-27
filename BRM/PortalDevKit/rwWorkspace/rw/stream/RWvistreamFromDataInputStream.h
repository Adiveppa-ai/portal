#ifndef rw_stream_RWvistreamFromDataInputStream_h_
#define rw_stream_RWvistreamFromDataInputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWvistreamFromDataInputStream.h#1 $
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
#include <rw/stream/pkgdefs.h>
#include <rw/vstream.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Adaptor class that adapts the Rogue Wave virtual stream interface to the
 * Rogue Wave data input stream interface.
 *
 * The class RWvistreamFromDataInputStream is an adaptor class that adapts
 * the Rogue Wave virtual stream interface to the new Rogue Wave Data Input
 * Stream interface. Requests made through the Rogue Wave virtual input
 * stream interface are forwarded to the embedded RWDataInputStream handle.
 */
class RW_STREAM_GLOBAL RWvistreamFromDataInputStream : public RWvistream
{

public:

    /**
     * Initializes the reference to the data stream that will be used as the
     * source of data.
     *
     * \param sourceStream
     * The data stream that will serve as the source of data.
     */
    RWvistreamFromDataInputStream(const RWDataInputStream& sourceStream)
        : sourceStream_(sourceStream)
    {
        ;
    }

    /**
     * Destructor.
     */
    virtual ~RWvistreamFromDataInputStream();

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
    virtual int get();

    // Documented in base class.
    virtual RWvistream& get(char& c);

    // Documented in base class.
    virtual RWvistream& getChar(char& c);

    // Documented in base class.
    virtual RWvistream& get(signed char& c);

    // Documented in base class.
    virtual RWvistream& getChar(signed char& c);

    // Documented in base class.
    virtual RWvistream& get(unsigned char& c);

    // Documented in base class.
    virtual RWvistream& getChar(unsigned char& c);

    // Documented in base class.
    virtual RWvistream& get(wchar_t& wc);

    // Documented in base class.
    virtual RWvistream& getChar(wchar_t& wc);

    // Documented in base class.
    virtual RWvistream& get(bool& b);

    // Documented in base class.
    virtual RWvistream& get(short& i);

    // Documented in base class.
    virtual RWvistream& get(unsigned short& i);

    // Documented in base class.
    virtual RWvistream& get(int& i);

    // Documented in base class.
    virtual RWvistream& get(unsigned int& i);

    // Documented in base class.
    virtual RWvistream& get(long& i);

    // Documented in base class.
    virtual RWvistream& get(unsigned long& i);

#if !defined(RW_NO_LONG_LONG)
    // Documented in base class.
    virtual RWvistream& get(long long& i);

    // Documented in base class.
    virtual RWvistream& get(unsigned long long& i);
#endif

    // Documented in base class.
    virtual RWvistream& get(float& f);

    // Documented in base class.
    virtual RWvistream& get(double& d);

#ifndef RW_NO_LONG_DOUBLE
    // Documented in base class.
    virtual RWvistream& get(long double& d);
#endif

    // Documented in base class.
    virtual RWvistream& get(bool* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(char* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(double* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(float* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(int* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(long* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(short* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(wchar_t* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(signed char* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(unsigned char* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(unsigned short* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(unsigned int* v, size_t n);

    // Documented in base class.
    virtual RWvistream& get(unsigned long* v, size_t n);

#ifndef RW_NO_LONG_DOUBLE
    // Documented in base class.
    virtual RWvistream&   get(long double* v, size_t n);
#endif

#if !defined(RW_NO_LONG_LONG)
    // Documented in base class.
    virtual RWvistream&   get(long long* v, size_t n);

    // Documented in base class.
    virtual RWvistream&   get(unsigned long long* v, size_t n);
#endif


    // Documented in base class.
    virtual RWvistream& getString(char* s, size_t n);

    // Documented in base class.
    virtual RWvistream& getChars(char* s, size_t n);

    // Documented in base class.
    virtual RWvistream&   getSizeT(size_t& sz);

protected:

    /**
     * Returns a handle to the embedded Data Input Stream that is used as
     * the source of data. Throws no exceptions.
     */
    RWDataInputStream& getSourceStream()
    {
        return RW_EXPOSE(sourceStream_);
    }


    /**
     * \copydoc getSourceStream()
     */
    const RWDataInputStream& getSourceStream() const
    {
        return sourceStream_;
    }

private:

    // The data input stream used as the sink of data
    RWDataInputStream sourceStream_;

};

#endif // rw_stream_RWvistreamFromDataInputStream_h_
