#ifndef rw_stream_RWChainedUCharArrayOutputStreamImp_h_
#define rw_stream_RWChainedUCharArrayOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWChainedUCharArrayOutputStreamImp.h#1 $
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

#include <rw/stream/RWChainedMemoryStreambuf.h>
#include <rw/stream/RWUCharArrayOutputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class implementing the UTF-16 character array output stream
 * interface.
 *
 * Concrete class implementing the UTF-16 character array output stream
 * interface. UTF-16 characters inserted into an instance of class
 * RWChainedUCharArrayOutputStreamImp are stored in memory using an instance
 * of class RWChainedMemoryStreambuf. Implements the body idiom from the
 * handle-body pattern.
 */
class RW_STREAM_GLOBAL RWChainedUCharArrayOutputStreamImp : public RWUCharArrayOutputStreamImp
{

public:

    typedef std::streambuf::char_type char_type;

    /**
     * Constructs an RWChainedUCharArrayOutputStreamImp instance that uses
     * an instance of class RWChainedMemoryStreambuf to store UTF-16
     * characters. The function returns a handle to the implementation
     * class.
     */
    static RWUCharArrayOutputStream make()
    {
        return RWUCharArrayOutputStream(new RWChainedUCharArrayOutputStreamImp);
    }

    /**
     * Destructor.
     */
    virtual ~RWChainedUCharArrayOutputStreamImp();

    /**
     * Returns a pointer to an array of UTF-16 characters containing the
     * UTF-16 characters inserted into the stream since its creation, or
     * since the last invocation of function getUCharacterArray(), or
     * function clear(). Users are responsible for freeing the memory
     * associated with the array returned by this function, by using
     * <tt>operator delete[]</tt>.
     */
    virtual RWUChar* getUCharacterArray();

    // Documented in base class.
    virtual RWSize getUCharacterArraySize() const;

    // Documented in base class.
    virtual void clear();

    //--This function calls 'flush()'. The user is responsible for closing the iostreams
    //--'streambuf', used as the sink of bytes, if necessary.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function.
    /**
     * This function calls flush().
     */
    virtual void close();

    /**
     * Forward the flush() request to the internal RWChainedMemoryStreambuf
     * object.
     */
    virtual void flush();

    /**
     * These functions return \c true if the last operation performed on the
     * internal RWChainedMemoryStreambuf object failed.
     */
    virtual bool isBad() const;

    /**
     * These functions return \c true if the last operation performed on the
     * internal RWChainedMemoryStreambuf object failed.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object succeeded.
     */
    virtual bool isGood() const;

    //--Writes a single unicode character to the iostreams 'streambuf'.
    //--The parameter 'unicodeValue' is the unicode character to be written.
    //--Throws exception 'RWIncompleteStreamOperation' and any other propagated by another function.
    /**
     * Writes a single UTF-16 character to the stream. Throws exception
     * RWIncompleteStreamOperation.
     *
     * \param unicodeValue
     * The UTF-16 character to be written.
     */
    virtual void write(RWUChar unicodeValue);

    //--Writes an array of unicode character(s) to the iostreams 'streambuf'.
    //--The parameter 'unicodeArray' is a pointer to the first element of the array.
    //--The parameter 'numUChars' is the number of unicode character(s) to be written.
    //--Throws exception 'RWIncompleteStreamOperation' and any other propagated by another function.
    /**
     * Writes an array of UTF-16 characters to the stream. Throws exception
     * RWIncompleteStreamOperation.
     *
     * \param unicodeArray
     * A pointer to the first element of the array
     *
     * \param numUChars
     * The number of UTF-16 characters to be written.
     */
    virtual void write(const RWUChar* unicodeArray, RWSize numUChars);

protected:

    /**
     * Constructor.
     */
    RWChainedUCharArrayOutputStreamImp()
        : RWUCharArrayOutputStreamImp()
        , isBad_(false)
    {
        ;
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, which is used as
     * the sink of UTF-16 characters.
     */
    RWChainedMemoryStreambuf& getSinkBuff()
    {
        return RW_EXPOSE(sinkBuff_);
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, which is used as
     * the sink of UTF-16 characters.
     */
    const RWChainedMemoryStreambuf& getSinkBuff() const
    {
        return sinkBuff_;
    }

private:

    RWChainedMemoryStreambuf sinkBuff_;
    bool isBad_;

};

#endif // rw_stream_RWChainedUCharArrayOutputStreamImp_h_
