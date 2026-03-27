#ifndef __rw_network_RWBufferedSendPortal_h__
#define __rw_network_RWBufferedSendPortal_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWBufferedSendPortal.h#1 $
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

/**
 * \ingroup networking_module
 *
 * \brief
 * Provides buffering of send() calls only, possibly improving performance
 * by limiting calls to the underlying RWPortal.
 *
 * RWBufferedSendPortal inherits from RWPortal to provide buffering of
 * send() calls. In cases where calling send() on the underlying RWPortal is
 * expensive, RWBufferedSendPortal may substantially increase efficiency by
 * limiting the number of calls to the underlying RWPortal.
 *
 * \note
 * When buffering send data, requests to send data should be made through
 * the RWBufferedSendPortal object. If you must make calls directly to the
 * underlying RWPortal, be sure to call flush() first. Failure to do so may
 * result in data being transmitted out of order.
 *
 * Buffered data in the RWBufferedSendPortal is sent through the underlying
 * RWPortal when any of the following three conditions are met:
 *
 * - the RWBufferedSendPortal is destroyed
 * - the flush() method is invoked
 * - the buffer becomes full
 *
 * \example
 * \code
 * RWPortal portal = RWSocketPortal();
 * portal = RWBufferedSendPortal(portal, 1024);
 * \endcode
 * \endexample
 */
class RW_NETWORK_SYMBOLIC RWBufferedSendPortal
    : public RWPortal
{
public:

    /**
     * Constructs an invalid RWBufferedSendPortal. Attempts to send or
     * receive on the portal throw an RWNetNoChannelError exception.
     *
     * To use an instance created with this constructor, you must assign to
     * it from a valid RWBufferedSendPortal instance.
     */
    RWBufferedSendPortal(void);

    /*
     * Construct a buffered portal on an existing portal.  bufferSize
     * indicates the amount of space allocated to be used as a buffer.
     *
     * \note
     * If send requests are being buffered, users will need to explicitly
     * invoke the flush method to ensure that data is sent properly.
     * RWBufferedSendPortal will automatically send any buffered data on
     * destruction.
     */
    /**
     * Constructs a buffered portal on an existing portal. \a bufferSize is
     * the requested size for the underlying buffer.
     */
    RWBufferedSendPortal(const RWPortal& portal, size_t bufferSize);

    /**
     * Sends any data in the \c send buffer immediately. This function does
     * not affect data in the \c recv buffer, or a portal that is not
     * buffering \c send data.
     *
     * The parameter \a timeout specifies the maximum amount of time in
     * milliseconds to wait for any single blocking send() call. There may
     * be multiple such calls made in a single call to flush(). If a timeout
     * is not specified, or is 0, this method blocks indefinitely.
     *
     * This function throws a RWNetCantSendError exception if the send()
     * call on the underlying portal returns an error or fails to send any
     * data.
     */
    void
    flush(unsigned long timeout = 0);
};

#endif // __rw_network_RWBufferedSendPortal_h__
