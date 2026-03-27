#ifndef rw_stream_RWStreamImp_h_
#define rw_stream_RWStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWStreamImp.h#1 $
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

#include <rw/stream/pkgdefs.h>
#include <rw/pointer/RWBodyBase.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Abstract base class for all the stream implementation classes.
 *
 * Abstract base class for all the stream implementation classes. Implements
 * the body idiom from the handle-body pattern.
 */
class RW_STREAM_GLOBAL RWStreamImp : public RWBodyBase
{

public:

    //--Destructor.
    //--Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWStreamImp()
    {
        ;
    }

    /**
     * Closes the stream.
     */
    virtual void close() = 0;

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * input or output operation, such as an irrecoverable read error from a
     * file. Throws no exceptions.
     */
    virtual bool isBad() const = 0;

    /**
     * Returns \c true to indicate that an input operation failed to read
     * the expected data, or that an output operation failed to generate the
     * desired data. Throws no exceptions.
     */
    virtual bool isFail() const = 0;

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    virtual bool isGood() const = 0;

protected:

    //--Constructor.
    //--Throws no exceptions.
    /**
     * Constructor.
     */
    RWStreamImp()
        : RWBodyBase()
    {
        ;
    }

private:

    //--Copy construction is not allowed.
    //--Throws no exceptions.
    /**
     * Copy construction is not allowed.
     */
    RWStreamImp(const RWStreamImp&); // {;}

    //--Assignment is not allowed.
    //--Throws no exceptions.
    /**
     * Assignment is not allowed.
     */
    RWStreamImp& operator=(const RWStreamImp&); // {;}
};

#endif // rw_stream_RWStreamImp_h_
