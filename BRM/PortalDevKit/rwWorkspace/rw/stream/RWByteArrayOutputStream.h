#ifndef rw_stream_RWByteArrayOutputStream_h_
#define rw_stream_RWByteArrayOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWByteArrayOutputStream.h#1 $
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

#include <rw/stream/RWByteArrayOutputStreamImp.h>
#include <rw/stream/RWByteOutputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for binary output streams, allowing retrieval of inserted
 * data as a byte array.
 *
 * The handle class for binary output streams supporting an extended
 * interface that allows retrieval of their inserted data as a byte array.
 * Implements the handle idiom from the handle-body pattern.
 */
class RWByteArrayOutputStream : public RWByteOutputStream
{

public:

    /**
     * Constructor.
     *
     * \param body
     * A pointer to an implementation class supporting the abstract
     * interface RWByteArrayOutputStreamImp.
     */
    explicit RWByteArrayOutputStream(RWByteArrayOutputStreamImp* body)
        : RWByteOutputStream(body)
    { }

    /**
     * Copy constructor.
     *
     * \param handle
     * A binary array stream handle used to initialize the newly created
     * handle.
     */
    RWByteArrayOutputStream(const RWByteArrayOutputStream& handle)
        : RWByteOutputStream(handle)
    {
        ;
    }

    /**
     * Assignment operator.
     *
     * \param handle
     * A binary array stream handle used to initialize this handle.
     */
    RWByteArrayOutputStream& operator=(const RWByteArrayOutputStream& handle)
    {
        static_cast<RWByteOutputStream*>(this)->operator=(static_cast<const RWByteOutputStream&>(handle));
        return *this;
    }

    /**
     * Returns a pointer to an array of bytes containing the bytes inserted
     * into the stream since its creation. Users are responsible for freeing
     * the memory associated with the array returned by this function, by
     * using <tt>operator delete[]</tt>.
     */
    RWByte* getByteArray()
    {
        return static_cast<RWByteArrayOutputStreamImp&>(this->body()).getByteArray();
    }

    /**
     * Returns the size of the byte array that would be returned by a call
     * to function getByteArray().
     */
    RWSize getByteArraySize() const
    {
        return static_cast<RWByteArrayOutputStreamImp&>(this->body()).getByteArraySize();
    }

    /**
     * Resets the underlying buffer.
     */
    void clear()
    {
        static_cast<RWByteArrayOutputStreamImp&>(this->body()).clear();
    }

};

#endif // rw_stream_RWByteArrayOutputStream_h_
