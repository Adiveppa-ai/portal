#ifndef rw_stream_RWChainedWCharArrayOutputStreamImp_h_
#define rw_stream_RWChainedWCharArrayOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWChainedWCharArrayOutputStreamImp.h#1 $
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
#include <rw/stream/RWWCharArrayOutputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class implementing the wide character array output stream
 * interface.
 *
 * Concrete class implementing the wide character array output stream
 * interface. Wide character inserted into an instance of class
 * RWChainedWCharArrayOutputStreamImp are stored in memory using an instance
 * of class RWChainedMemoryStreambuf. Implements the body idiom from the
 * handle-body pattern.
 */
class RW_STREAM_GLOBAL RWChainedWCharArrayOutputStreamImp : public RWWCharArrayOutputStreamImp
{

public:

    typedef std::streambuf::char_type char_type;

    /**
     * Constructs an RWChainedWCharArrayOutputStreamImp instance that uses
     * an instance of class RWChainedMemoryStreambuf to store wide
     * characters. The function returns a handle to the implementation
     * class.
     */
    static RWWCharArrayOutputStream make()
    {
        return RWWCharArrayOutputStream(new RWChainedWCharArrayOutputStreamImp);
    }

    /**
     * Destructor.
     */
    virtual ~RWChainedWCharArrayOutputStreamImp();

    /**
     * Returns a pointer to an array of wide characters containing the wide
     * characters inserted into the stream since its creation, or since the
     * last invocation of function getWCharacterArray(), or function
     * clear(). Users are responsible for freeing the memory associated with
     * the array returned by this function, by using
     * <tt>operator delete[]</tt>.
     */
    virtual wchar_t* getWCharacterArray();

    // Documented in base class.
    virtual RWSize getWCharacterArraySize() const;

    // Documented in base class.
    virtual void clear();

    //--This function calls 'flush()'. The user is responsible for closing the iostreams
    //--'streambuf' used as the sink of bytes if necessary.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function.
    /**
     * This function calls flush().
     */
    virtual void close();

    //--Forward the flush request to the iostreams 'streambuf'.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function.
    /**
     * Forward the flush request to the internal RWChainedMemoryStreambuf
     * object.
     */
    virtual void flush();

    /**
     * Return \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object failed.
     */
    virtual bool isBad() const;

    /**
     * Return \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object failed.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object succeeded.
     */
    virtual bool isGood() const;

    //--Writes a single wide character to the iostreams 'streambuf'.
    //--The parameter 'wcharValue' is the wide character to be written.
    //--Throws exception 'RWIncompleteStreamOperation' and any other propagated by another function.
    /**
     * Writes a single wide character to the stream. Throws exception
     * RWIncompleteStreamOperation.
     *
     * \param wcharValue
     * The wide character to be written.
     */
    virtual void write(wchar_t wcharValue);

    //--Writes an array of wide character(s) to the iostreams 'streambuf'.
    //--The parameter 'wcharArray' is a pointer to the first element of the array.
    //--'numWChars' The number of wide character(s) to be written.
    //--Throws exception 'RWIncompleteStreamOperation' and any other propagated by another function.
    /**
     * Writes an array of wide characters to the stream. Throws exception
     * RWIncompleteStreamOperation.
     *
     * \param wcharArray
     * A pointer to the first element of the array.
     *
     * \param numWChars
     * The number of wide characters to be written.
     */
    virtual void write(const wchar_t* wcharArray, RWSize numWChars);

protected:


    /**
     * Constructor.
     */
    RWChainedWCharArrayOutputStreamImp()
        : RWWCharArrayOutputStreamImp()
        , isBad_(false)
    {
        ;
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, which is used as
     * the sink of wide characters.
     */
    RWChainedMemoryStreambuf& getSinkBuff()
    {
        return RW_EXPOSE(sinkBuff_);
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, which is used as
     * the sink of wide characters.
     */
    const RWChainedMemoryStreambuf& getSinkBuff() const
    {
        return sinkBuff_;
    }

private:

    RWChainedMemoryStreambuf sinkBuff_;
    bool isBad_;

};

#endif // rw_stream_RWChainedWCharArrayOutputStreamImp_h_
