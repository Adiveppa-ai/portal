#ifndef __rw_network_RWBufferedPortal_h__
#define __rw_network_RWBufferedPortal_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWBufferedPortal.h#1 $
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
 *************************************************************************/

#include <rw/network/RWPortal.h>
#include <rw/network/pkgdefs.h>

/*
 * RWBufferedPortal is for INTERNAL USE ONLY.  The use of this class in
 * user code is not recommended, and is not supported.  For user code,
 * refer to the RWBufferedRecvPortal and RWBufferedSendPortal classes.
 * This class well be removed in a future revision of SourcePro Net
 *
 * RWBufferedPortal provides buffering of data received or sent to an
 * underlying portal.
 */
class RW_NETWORK_SYMBOLIC RWBufferedPortal
    : public RWPortal
{
public:

    /*
     * Enumeration of buffering options
     */
    enum BufferType {
        /**
         * Receive operations will be buffered.
         */
        buffered_recv = 1,

        /**
         * Send operations will be buffered.
         */
        buffered_send,

        /**
         * Both send and receive operations are buffered.
         */
        buffered_both
    };

    /*
     * Construct a default buffered portal.  This constructor sets
     * an invalid internal buffer, which will throw if any methods
     * are executed on it.
     *
     * In order to use an instance created in this manner, you will
     * need to assign to it from a valid RWBufferedPortal instance.
     */
    RWBufferedPortal(void);

    /*
     * Construct a buffered portal on an existing portal.  bufferSize
     * indicates the amount of space allocated to be used as a buffer.
     * The type indicates whether receiving data, sending data, or both
     * should be buffered.
     *
     * @note
     * If both receive and send requests are buffered, each will receive
     * half of the space specified in \a bufferSize.
     *
     * @note
     * If send requests are being buffered, users will need to explicitly
     * invoke the flush() method to ensure that data is sent properly.
     * RWBufferedPortal will automatically send any buffered data on
     * destruction.
     *
     * @note
     * If receive requires are being buffered, users will need to ensure that all
     * requests for data are made through the RWBufferedPortal interface.
     * Accessing data through the underlying portal directly may result
     * in data being read out of order, or being missed.
     */
    RWBufferedPortal(const RWPortal& portal, size_t bufferSize,
                     BufferType type = RWBufferedPortal::buffered_recv);

    /*
     * If there is any send data buffered, send it immediately.  This function
     * has no effect on buffered receive data, or on a portal that is not buffering
     * send data.
     */
    void
    flush(void);

    void
    flush(unsigned long timeout);
};

#endif // __rw_network_RWBufferedPortal_h__
