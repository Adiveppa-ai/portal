#ifndef __rw_network_RWBufferedRecvPortal_h__
#define __rw_network_RWBufferedRecvPortal_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWBufferedRecvPortal.h#1 $
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
 * Provides buffering of recv() calls only, possibly improving performance
 * by limiting calls to the underlying RWPortal.
 *
 * RWBufferedRecvPortal inherits from RWPortal to provide buffering of
 * recv() calls. When calling recv() on the underlying RWPortal is
 * expensive, RWBufferedRecvPortal may substantially increase efficiency by
 * limiting the number of calls to the underlying RWPortal.
 *
 * \note
 * When buffering receive data, all requests for data must be made through
 * the RWBufferedRecvPortal object; do not make calls directly to the
 * underlying RWPortal. Doing so may lose data that is currently buffered.
 *
 * \example
 * \code
 * RWPortal portal = RWSocketPortal();
 * portal = RWBufferedRecvPortal(portal, 1024);
 * \endcode
 * \endexample
 */
class RW_NETWORK_SYMBOLIC RWBufferedRecvPortal
    : public RWPortal
{
public:
    /**
     * Constructs an invalid RWBufferedRecvPortal. Attempts to send or
     * receive on the portal throw an RWNetNoChannelError exception.
     *
     * To use an instance created with this constructor, you must assign to
     * it from a valid RWBufferedRecvPortal instance.
     */
    RWBufferedRecvPortal(void);

    /*
     * Construct a buffered portal on an existing portal. \a bufferSize
     * indicates the amount of space allocated to be used as a buffer.
     *
     * \note
     * If receive requires are being buffered, users will need to ensure
     * that all requests for data are made through the
     * RWBufferedRecvPortal interface.  Accessing data through the
     * underlying portal directly may result in data being read out of
     * order, or being missed.
     */
    /**
     * Constructs a buffered portal on an existing portal. \a bufferSize is
     * the requested size for the underlying buffer.
     */
    RWBufferedRecvPortal(const RWPortal& portal, size_t bufferSize);
};

#endif // __rw_network_RWBufferedRecvPortal_h__
