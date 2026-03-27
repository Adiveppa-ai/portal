#ifndef rw_stream_RWChainedCharArrayOutputStreamImp_h_
#define rw_stream_RWChainedCharArrayOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWChainedCharArrayOutputStreamImp.h#1 $
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
#include <rw/stream/RWCharArrayOutputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class implementing the narrow character array output stream
 * interface.
 *
 * Concrete class implementing the narrow character array output stream
 * interface. Characters inserted into an instance of class
 * RWChainedCharArrayOutputStreamImp are stored in memory using an instance
 * of class RWChainedMemoryStreambuf. Implements the body idiom from the
 * handle-body pattern.
 */
class RW_STREAM_GLOBAL RWChainedCharArrayOutputStreamImp : public RWCharArrayOutputStreamImp
{

public:

    typedef std::streambuf::char_type char_type;

    /**
     * Constructs an RWChainedCharArrayOutputStreamImp instance that uses an
     * instance of class RWChainedMemoryStreambuf to store narrow
     * characters. The function returns a handle to the implementation
     * class.
     */
    static RWCharArrayOutputStream make()
    {
        return RWCharArrayOutputStream(new RWChainedCharArrayOutputStreamImp);
    }

    /**
     * Destructor.
     */
    virtual ~RWChainedCharArrayOutputStreamImp();

    /**
     * Returns a pointer to an array of narrow characters containing the
     * characters inserted into the stream since its creation, or since the
     * last invocation of function getCharacterArray(), or function clear().
     * Users are responsible for freeing the memory associated with the
     * array returned by this function using <tt>operator delete[]</tt>
     */
    virtual char* getCharacterArray();

    // Documented in base class.
    virtual RWCString getString();

    // Documented in base class.
    virtual RWSize getCharacterArraySize() const;

    // Documented in base class.
    virtual void clear();

    //--This function calls 'flush()'. The user is responsible for closing the iostreams
    //--'streambuf' used as the sink of bytes if necessary.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function.
    /**
     * This function calls flush().
     */
    virtual void close();

    //--Forward the 'flush()' request to the iostreams 'streambuf'.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function..
    /**
     * Forwards the flush() request to the internal RWChainedMemoryStreambuf
     * object.
     */
    virtual void flush();

    /**
     * Returns \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object failed. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * Returns \c true if the last operation performed on the external
     * RWChainedMemoryStreambuf object failed
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object succeeded.
     */
    virtual bool isGood() const;

    //--Writes a single narrow character to the stream.
    //--The parameter 'charValue' The narrow character to be written to the stream.
    // Documented in base class.
    virtual void write(char charValue);

    //--Writes an array of narrow character(s) to the stream.
    //--The parameter 'charArray' is a pointer to the first element of the array.
    //--'numChars' The number of narrow character(s) to be written to the
    //--stream.
    // Documented in base class.
    virtual void write(const char* charArray, RWSize numChars);

protected:

    /**
     * Constructor.
     */
    RWChainedCharArrayOutputStreamImp()
        : RWCharArrayOutputStreamImp()
        , isBad_(false)
    {
        ;
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, which is used as
     * the sink of bytes.
     */
    RWChainedMemoryStreambuf& getSinkBuff()
    {
        return RW_EXPOSE(sinkBuff_);
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, which is used as
     * the sink of bytes.
     */
    const RWChainedMemoryStreambuf& getSinkBuff() const
    {
        return sinkBuff_;
    }

private:

    RWChainedMemoryStreambuf sinkBuff_;
    bool isBad_;

};

#endif // rw_stream_RWChainedCharArrayOutputStreamImp_h_
