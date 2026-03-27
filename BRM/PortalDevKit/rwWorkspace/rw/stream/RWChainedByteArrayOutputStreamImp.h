#ifndef rw_stream_RWChainedByteArrayOutputStreamImp_h_
#define rw_stream_RWChainedByteArrayOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWChainedByteArrayOutputStreamImp.h#1 $
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

#include <rw/stream/RWByteArrayOutputStream.h>
#include <rw/stream/RWChainedMemoryStreambuf.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Concrete class implementing the byte array output stream interface.
 *
 * Concrete class implementing the byte array output stream interface. Bytes
 * inserted into an instance of class RWChainedByteArrayOutputStreamImp are
 * stored in memory using an instance of class RWChainedMemoryStreambuf.
 * Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWChainedByteArrayOutputStreamImp : public RWByteArrayOutputStreamImp
{

public:

    typedef std::streambuf::char_type char_type;

    /**
     * Constructs an RWChainedByteArrayOutputStreamImp instance that uses an
     * instance of class RWChainedMemoryStreambuf to store bytes. The
     * function returns a handle to the implementation class.
     */
    static RWByteArrayOutputStream make()
    {
        return RWByteArrayOutputStream(new RWChainedByteArrayOutputStreamImp);
    }

    /**
     * Destructor.
     */
    virtual ~RWChainedByteArrayOutputStreamImp();

    /**
     * Returns a pointer to an array of bytes containing the bytes inserted
     * into the stream since its creation, or since the last invocation of
     * function getByteArray(), or function clear(). Users are responsible
     * for freeing the memory associated with the array returned by this
     * function, by using <tt>operator delete[]</tt>.
     */
    virtual RWByte* getByteArray();

    // Documented in base class.
    virtual RWSize getByteArraySize() const;

    // Documented in base class.
    virtual void clear();

    //--This function calls 'flush()'. The user is responsible for closing the 'IOStreams
    //--streambuf' used as the sink of bytes if necessary.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function.
    /**
     * This function calls flush().
     */
    virtual void close();

    //--Forward the 'flush()' request to the 'IOStreams streambuf'.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function.
    /**
     * Forward the flush() request to the internal RWChainedMemoryStreambuf
     * object.
     */
    virtual void flush();

    /**
     * Returns \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object failed.
     */
    virtual bool isBad() const;

    /**
     * Returns \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object failed.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true if the last operation performed on the internal
     * RWChainedMemoryStreambuf object succeeded.
     */
    virtual bool isGood() const;

    //--Writes a single byte to the 'IOStreams streambuf'.
    //--The parameter 'byteValue' is the byte to be written.
    //--Throws exception 'RWExternalStreamException' and any other propagated by another function.
    /**
     * Writes a single byte to the iostreams \c std::streambuf. Throws
     * exception RWExternalStreamException.
     *
     * \param byteValue
     * The byte to be written.
     */
    virtual void write(RWByte byteValue);

    //--Writes an array of byte(s) to the 'IOStreams streambuf'.
    //--The parameter 'byteArray' is a pointer to the first element of the array.
    //--The parameter 'numBytes' is the number of byte(s) to be written.
    //--Throws exception 'RWIncompleteStreamOperation' and any other propagated by another function.
    /**
     * Writes an array of bytes to the iostreams \c std::streambuf. Throws
     * exception RWIncompleteStreamOperation.
     *
     * \param byteArray
     * A pointer to the first element of the array.
     *
     * \param numBytes
     * The number of bytes to be written.
     */
    virtual void write(const RWByte* byteArray, RWSize numBytes);

protected:

    /**
     * Constructor.
     */
    RWChainedByteArrayOutputStreamImp()
        : RWByteArrayOutputStreamImp()
        , isBad_(false)
    {
        ;
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, used as the sink
     * of bytes.
     */
    RWChainedMemoryStreambuf& getSinkBuff()
    {
        return RW_EXPOSE(sinkBuff_);
    }

    /**
     * Returns a reference to the RWChainedMemoryStreambuf, used as the sink
     * of bytes.
     */
    const RWChainedMemoryStreambuf& getSinkBuff() const
    {
        return sinkBuff_;
    }

private:

    RWChainedMemoryStreambuf sinkBuff_;
    bool isBad_;

};

#endif // rw_stream_RWChainedByteArrayOutputStreamImp_h_
