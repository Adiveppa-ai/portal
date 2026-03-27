#ifndef rw_stream_RWWCharArrayOutputStream_h_
#define rw_stream_RWWCharArrayOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWWCharArrayOutputStream.h#1 $
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

#include <rw/stream/RWWCharArrayOutputStreamImp.h>
#include <rw/stream/RWWCharOutputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for wide character output streams that support an extended
 * interface, allowing retrieval of inserted data as a wide character array.
 *
 * Handle class for wide character output streams that support an extended
 * interface that allows retrieval of their inserted data as a wide
 * character array. Implements the handle idiom from the handle-body
 * pattern.
 */
class RWWCharArrayOutputStream : public RWWCharOutputStream
{

public:

    //-- Throws no exceptions.
    /**
     * Constructor.
     *
     * \param body
     * A pointer to an implementation class supporting the abstract
     * interface RWWCharArrayOutputStreamImp.
     */
    explicit RWWCharArrayOutputStream(RWWCharArrayOutputStreamImp* body)
        : RWWCharOutputStream(body)
    { }

    //-- Throws no exceptions.
    /**
     * Copy constructor.
     *
     * \param handle
     * A wide character array stream handle used to initialize the newly
     * created handle.
     */
    RWWCharArrayOutputStream(const RWWCharArrayOutputStream& handle)
        : RWWCharOutputStream(handle)
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A wide character array stream handle used to initialize this handle.
     */
    RWWCharArrayOutputStream& operator=(const RWWCharArrayOutputStream& handle)
    {
        static_cast<RWWCharOutputStream*>(this)->operator=(static_cast<const RWWCharOutputStream&>(handle));
        return *this;
    }

    /**
     * Returns a pointer to an array of wide characters containing the wide
     * characters inserted into the stream since its creation. Users are
     * responsible for freeing the memory associated with the array returned
     * by this function using <tt>operator delete[]</tt>.
     */
    wchar_t* getWCharacterArray()
    {
        return static_cast<RWWCharArrayOutputStreamImp&>(this->body()).getWCharacterArray();
    }

    /**
     * Returns the size of the wide character array that would be returned
     * by a call to function getWCharacterArray().
     */
    RWSize getWCharacterArraySize() const
    {
        return static_cast<RWWCharArrayOutputStreamImp&>(this->body()).getWCharacterArraySize();
    }

    /**
     * Resets the underlying buffer.
     */
    void clear()
    {
        static_cast<RWWCharArrayOutputStreamImp&>(this->body()).clear();
    }

};

#endif // rw_stream_RWWCharArrayOutputStream_h_
