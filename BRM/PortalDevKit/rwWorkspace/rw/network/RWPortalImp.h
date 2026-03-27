#ifndef __rw_network_RWPortalImp_h__
#define __rw_network_RWPortalImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWPortalImp.h#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

/*
 * RWPortalImp: implementation class for portals
 *
 * This needs to be specified in the header file and before the
 * declaration of RWPortal because some of the inline members in RWPortal
 * use the member functions of this class.  Also putting it here makes life
 * easier when defining specific types of portals.
 */

#include <rw/network/RWNetBuf.h>
#include <rw/network/pkgdefs.h>

/**
 * \ingroup networking_module
 *
 * \brief
 * Abstract base class from which to create specialized portal types.
 *
 * RWPortalImp is an abstract base class from which to create specialized
 * portal types. This class is the implementation class for RWPortal, and
 * objects deriving from it should not be accessed directly, but rather by
 * the interface RWPortal.
 *
 * Classes derived from RWPortalImp implement the operations defined by the
 * RWPortalImp interface.
 */
class RW_NETWORK_GLOBAL RWPortalImp
{
public:
    /**
     * Default constructor. Creates an empty object.
     */
    RWPortalImp() {};

    /**
     * Destroys this portal implementation.
     */
    virtual ~RWPortalImp();

    /**
     * Receives all available data on the underlying communications channel.
     * Derived classes must provide a definition for this method. This
     * function returns a RWNetBuf that contains all data available on the
     * communications channel at the time of the call. This function may
     * throw an exception to indicate failure.
     */
    virtual RWNetBuf recv() = 0;

    /**
     * Receives data on the underlying communications channel. Derived
     * classes must provide a definition for this method.
     *
     * The \a buf parameter is a pointer to an array of characters to fill
     * with data from the communications channel.This parameter may be
     * \c NULL if the value of the \a len parameter is less than or equal to
     * \c 0. The \a len parameter is the number of characters to read from
     * the communications channel. The \a state parameter is a pointer to a
     * RWNetBuf::State object or \c NULL. If this parameter is non-\c NULL,
     * it should be set to the RWNetBuf::State enumeration that most
     * appropriately describes the state of the underlying communications
     * channel.
     *
     * This function returns the number of characters read from the
     * communications channel. The result may be less than the value of
     * \a len. This function should return a negative value or throw an
     * exception to indicate failure.
     */
    virtual int recv(char* buf, int len, RWNetBuf::State* state) = 0;

    /**
     * Sends the data specified over the underlying communications channel.
     * Derived classes must provide a definition for this method.
     *
     * The \c buf parameter is a pointer to an array of characters to write
     * to the communications channel. This parameter may be \c NULL if the
     * value of the \a len parameter is less than or equal to \c 0. The
     * \a len parameter is the number of characters to read from the
     * communications channel.
     *
     * This function returns the number of characters written to the
     * communications channel. The result may be less than the value of
     * \a len. This function should return a negative value or throw an
     * exception to indicate failure.
     */
    virtual int send(const char* buf, int len) = 0;

    /**
     * Receives all available data on the underlying communications channel
     * under the timeout specified. If the recv() operation times out, a
     * derived class should throw an exception or return a value that
     * indicates failure. The default implementation of this method throws a
     * RWNetTimeoutNotImplementedError exception.
     *
     * The \a timeout parameter is the maximum number of milliseconds that
     * the recv() operation is allowed to take.
     *
     * This function returns a RWNetBuf that contains all data available on
     * the communications channel at the time of the call. This function
     * should throw an exception to indicate failure.
     */
    virtual RWNetBuf recv(unsigned long timeout);

    /**
     * Receives data on the underlying communications channel under the
     * timeout specified. If the recv() operation times out, the derived
     * class should throw an exception or return a value that indicates
     * failure. The default implementation of this method throws a
     * RWNetTimeoutNotImplementedError exception.
     *
     * The \a buf parameter is a pointer to an array of characters to fill
     * with data from the communications channel.This parameter may be
     * \c NULL if the value of the \a len parameter is less than or equal to
     * \c 0. The \a len parameter is the number of characters to read from
     * the communications channel. The \a timeout parameter is the maximum
     * number of milliseconds that the recv() operation is allowed to take.
     *
     * This function returns the number of characters read from the
     * communications channel. The result may be less than the value of
     * \a len. This function should return a negative value or throw an
     * exception to indicate failure.
     */
    virtual int recv(char* buf, int len, RWNetBuf::State* state, unsigned long timeout);

    /**
     * Sends the data specified over the underlying communications channel
     * under the timeout specified. If the send() operation times out, the
     * derived class should throw an exception or return a value that
     * indicates failure. The default implementation of this method throws a
     * RWNetTimeoutNotImplementedError exception.
     *
     * The \a buf parameter is a pointer to an array of characters to write
     * to the communications channel. This parameter may be \c NULL if the
     * value of the \a len parameter is less than or equal to \c 0. The
     * \a len parameter is the number of characters to read from the
     * communications channel. The \a timeout parameter is the maximum
     * number of milliseconds that the send() operation is allowed to take.
     *
     * This function returns the number of characters written to the
     * communications channel. The result may be less than the value of
     * \a len. This function should return a negative value or throw an
     * exception to indicate failure.
     */
    virtual int send(const char* buf, int len, unsigned long timeout);

private:
    // Copy constructor and assignment declared (only) private so they can't
    // be used accidentally
    RWPortalImp(const RWPortalImp&);
    RWPortalImp& operator=(const RWPortalImp&);
};

#endif /* __rw_network_RWPortalImp_h__ */
