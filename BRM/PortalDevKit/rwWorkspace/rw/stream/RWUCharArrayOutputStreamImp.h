#ifndef rw_stream_RWUCharArrayOutputStreamImp_h_
#define rw_stream_RWUCharArrayOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWUCharArrayOutputStreamImp.h#1 $
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

#include <rw/stream/RWUCharOutputStreamImp.h>
#include <rw/stream/pkgdefs.h>

class RWUCharArrayOutputStream;

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for Unicode character output streams that support an
 * extended interface.
 *
 * Abstract base class for Unicode character output streams that support an
 * extended interface. This interface allows retrieval of the output
 * streams' inserted data as a UTF-16 character array. Implements the body
 * idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWUCharArrayOutputStreamImp : public RWUCharOutputStreamImp
{

public:

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWUCharArrayOutputStreamImp()
    {
        ;
    }

    /**
     * Returns a pointer to the array of UTF-16 characters inserted into the
     * stream since its creation. Users are responsible for freeing the
     * memory associated with the array returned by this function using
     * <tt>operator delete[]</tt>.
     */
    virtual RWUChar* getUCharacterArray() = 0;

    /**
     * Returns the size of the UTF-16 character array that would be returned
     * by a call to function getUCharacterArray().
     */
    virtual RWSize getUCharacterArraySize() const = 0;

    /**
     * Reset the underlying buffer.
     */
    virtual void clear() = 0;

protected:

    //-- Constructor.
    //-- Throws no exceptions.
    /**
     * Constructor.
     */
    RWUCharArrayOutputStreamImp()
        : RWUCharOutputStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWUCharArrayOutputStreamImp_h_
