#ifndef rw_stream_RWInputStreamImp_h_
#define rw_stream_RWInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWInputStreamImp.h#1 $
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

#include <rw/stream/RWStreamImp.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the input stream implementation classes.
 *
 * Abstract base class for all the input stream implementation classes.
 * Implements the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWInputStreamImp : public RWStreamImp
{

public:

    //--Destructor.
    //--Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWInputStreamImp()
    {
        ;
    }

    /**
     * Returns \c true to indicate that an input operation reached the end
     * of an input sequence. Throws no exceptions.
     */
    virtual bool isEof() const = 0;

    /**
     * Returns the number of available elements that can be read from the
     * stream without blocking. The type of the elements read is specified
     * by derived classes and can be one of the following: #RWByte, \c char,
     * #RWUChar, or \c wchar_t. Throws no exceptions.
     */
    virtual RWSize available() const = 0;

    /**
     * Skips \a numUnits elements from the input sequence if possible. The
     * function returns the actual number of elements skipped, which can be
     * any value between 0 and \a numUnits. The type of the elements skipped
     * is specified by derived classes and can be one of the following:
     * #RWByte, \c char, #RWUChar, or \c wchar_t.
     *
     * \param numUnits
     * The number of elements to be skipped.
     */
    virtual RWSize skip(RWSize numUnits) = 0;

protected:

    //--Constructor.
    //--
    //--Throws no exceptions.
    /**
     * Constructor.
     */
    RWInputStreamImp()
        : RWStreamImp()
    {
        ;
    }

};

#endif // rw_stream_RWInputStreamImp_h_
