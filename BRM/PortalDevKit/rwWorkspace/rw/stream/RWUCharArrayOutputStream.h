#ifndef rw_stream_RWUCharArrayOutputStream_h_
#define rw_stream_RWUCharArrayOutputStream_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharArrayOutputStream.h#1 $
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

#include <rw/stream/RWUCharArrayOutputStreamImp.h>
#include <rw/stream/RWUCharOutputStream.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Handle class for Unicode character output streams that support an
 * extended interface.
 *
 * Handle class for Unicode character output streams that support an
 * extended interface. This interface allows retrieval of the output
 * stream's inserted data as a UTF-16 character array. Implements the handle
 * idiom from the handle-body pattern.
 *
 * \note
 * All Unicode-named variables, such as \c UChar or \c unicodeArray refer to
 * the Unicode form UTF-16.
 */
class RWUCharArrayOutputStream : public RWUCharOutputStream
{

public:

    //-- Constructor.
    //--
    //-- Parameters:
    //--
    //--   'body': A pointer to an implementation class supporting the
    //-- abstract interface 'RWUCharArrayOutputStreamImp'.
    //-- Throws no exceptions.
    //--
    /**
     * Constructor.
     *
     * \param body
     * A pointer to an implementation class supporting the abstract
     * interface RWUCharArrayOutputStreamImp.
     */
    explicit RWUCharArrayOutputStream(RWUCharArrayOutputStreamImp* body)
        : RWUCharOutputStream(body)
    { }

    //-- Copy constructor.
    //--
    //-- Parameters:
    //--
    //--   'handle': A unicode character array stream handle used to initialize the
    //--   newly created handle.
    //--   Throws no exceptions.
    //--
    /**
     * Copy constructor.
     *
     * \param handle
     * A UTF-16 character array stream handle used to initialize the newly
     * created handle.
     */
    RWUCharArrayOutputStream(const RWUCharArrayOutputStream& handle)
        : RWUCharOutputStream(handle)
    {
        ;
    }

    /**
     * Assignment operator. Throws no exceptions.
     *
     * \param handle
     * A UTF-16 character array stream handle used to initialize this
     * handle.
     */
    RWUCharArrayOutputStream& operator=(const RWUCharArrayOutputStream& handle)
    {
        static_cast<RWUCharOutputStream*>(this)->operator=(static_cast<const RWUCharOutputStream&>(handle));
        return *this;
    }

    /**
     * Returns a pointer to the array of UTF-16 characters inserted into the
     * stream since its creation. Users are responsible for freeing the
     * memory associated with the array returned by this function using
     * <tt>operator delete[]</tt>.
     */
    RWUChar* getUCharacterArray()
    {
        return static_cast<RWUCharArrayOutputStreamImp&>(this->body()).getUCharacterArray();
    }

    /**
     * Returns the size of the UTF-16 character array that would be returned
     * by a call to function getUCharacterArray().
     */
    RWSize getUCharacterArraySize() const
    {
        return static_cast<RWUCharArrayOutputStreamImp&>(this->body()).getUCharacterArraySize();
    }

    /**
     * Resets the underlying buffer.
     */
    void clear()
    {
        static_cast<RWUCharArrayOutputStreamImp&>(this->body()).clear();
    }

};

#endif // rw_stream_RWUCharArrayOutputStream_h_
