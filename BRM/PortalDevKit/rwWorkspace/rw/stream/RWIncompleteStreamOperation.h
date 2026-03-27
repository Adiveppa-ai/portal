#ifndef rw_stream_RWIncompleteStreamOperation_h_
#define rw_stream_RWIncompleteStreamOperation_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWIncompleteStreamOperation.h#1 $
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

#include <rw/stream/RWExternalStreamException.h>
#include <rw/stream/pkgdefs.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Reports errors due to an incomplete stream operation.
 *
 * Exception class used to report an error due to a stream operation
 * partially fulfilled.
 */
class RW_STREAM_GLOBAL RWIncompleteStreamOperation : public RWExternalStreamException
{

public:

    /**
     * Constructs an empty exception. Throws no exceptions.
     */
    RWIncompleteStreamOperation();

    //--Throws no exceptions.
    /**
     * Constructs an exception, and initializes it with the error message
     * \a msg, the error code \a err, and the partial result \a partial.
     *
     * \param msg
     * Message describing the error.
     *
     * \param err
     * Error code associated with the error.
     *
     * \param partial
     * Number of elements successfully processed.
     */
    RWIncompleteStreamOperation(const char* msg, ErrorCode err, RWSize partial);

    //--Throws no exceptions.
    /**
     * Constructs an exception, and initializes it with the error message
     * \a msg, the error code \a err, and the partial result \a partial.
     *
     * \param msg
     * Message describing the error.
     *
     * \param err
     * Error code associated with the error.
     *
     * \param partial
     * Number of elements successfully processed.
     */
    RWIncompleteStreamOperation(const RWCString& msg, ErrorCode err, RWSize partial);

    //--Throws no exceptions.
    /**
     * Copy constructor.
     *
     * \param x
     * An exception used to initialize the newly created exception.
     */
    RWIncompleteStreamOperation(const RWIncompleteStreamOperation& x);

    /**
     * Returns the number of elements successfully processed before the
     * error occurred. Throws no exceptions.
     */
    RWSize elementsProcessed() const;

private:

    RWSize elementsProcessed_;

};

#endif // rw_stream_RWIncompleteStreamOperation_h_
