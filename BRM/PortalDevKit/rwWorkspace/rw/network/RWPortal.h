#ifndef __rw_network_RWPortal_h__
#define __rw_network_RWPortal_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWPortal.h#1 $
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
 * RWPortal: An access point to stream oriented communication channel
 *
 * A portal is an access point of a reliable byte stream communication
 * channel.  It is possible for more than one portal to access the
 * communications channel.  This happens, for example, when using the
 * copy constructor and assignment operator.  Most portal classes are
 * designed so that when the last portal disappears, the communications
 * channel is closed.
 *
 * Portals are lightweight objects.  Since copying and assignment copy
 * only the portal, and not the underlying communications channel, these
 * operations are inexpensive.  As a result, portals are suitable for
 * returning from functions and using by value in objects.
 *
 * Portals are implemented using the interface-implementation design pattern.
 * The portal itself is really a handle to an implementation that represents
 * the communication channel.
 */

#include <rw/network/RWNetBuf.h>
#include <rw/network/RWNoPortalImp.h>
#include <rw/network/RWPortalImp.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/network/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup networking_module
 *
 * \brief
 * An access point to a reliable byte stream communication channel.
 *
 * RWPortal is an access point to a reliable byte stream communication
 * channel. It is possible for more than one RWPortal to access the same
 * communications channel. This happens, for example, when using the copy
 * constructor and assignment operator. Unless explicitly constructed
 * otherwise, portal classes are designed so that when the last portal into
 * a channel disappears, the communications channel is closed.
 *
 * RWPortal is a lightweight object. In addition, the copy constructor and
 * the assignment operator copy only the RWPortal and not the underlying
 * communications channel, which means that those operations are
 * inexpensive. As a result, RWPortal%s can be returned by value from
 * functions and used as member data in objects.
 *
 * RWPortal is implemented using the interface/implementation design pattern
 * as described in the <em>Essential Networking Module User's Guide</em>.
 * The RWPortal itself is really a handle to an implementation that
 * represents the communication channel.
 */
class RW_NETWORK_SYMBOLIC RWPortal
{
public:
    /**
     * Creates a portal that cannot send or receive. Trying to send or
     * receive throws an RWNetNoChannelError exception.
     */
    RWPortal();

    /**
     * Copy constructor.
     */
    RWPortal(const RWPortal& x);

    /**
     * Destroys this portal. If other portals were created from this one by
     * assignment or copying, they are unaffected.
     */
    ~RWPortal();

    /**
     * Assignment operator. Makes self a portal to the same channel as \a x.
     * Disconnects from the current channel, if any.
     */
    RWPortal&
    operator=(const RWPortal& x);

    /**
     * Receives a buffer of data. The version returning an \c int returns
     * the number of characters actually received. recv() makes only one
     * call to the communications channel.
     */
    RWNetBuf recv() const;

    /**
     * \copydoc RWPortal::recv() const
     */
    int recv(char* buf, int bufLen, RWNetBuf::State* state = 0) const;

    /**
     * Receives at least \a n characters into the buffer. The second version
     * returns the number of bytes actually received. The implementation
     * loops over recv() until either all the data is received or, for some
     * reason, no data is returned. If no data is returned by recv(), an
     * RWNetCantRecvError exception is thrown. If you call recvAtLeast() on
     * a non-blocking channel, it will probably throw this same exception.
     */
    RWNetBuf recvAtLeast(int n) const;

    /**
     * \copydoc RWPortal::recvAtLeast(int) const
     */
    int recvAtLeast(char* buf, int bufLen, int n, RWNetBuf::State* state = 0) const;

    /**
     * Sends a buffer of data. Returns the number of bytes actually sent.
     * send() makes only one call to the communications channel.
     */
    int send(const RWCString& s) const;

    /**
     * \copydoc RWPortal::send(const RWCString&) const
     */
    int send(const char* buf, int buflen) const;

    /**
     * Sends at least \a n characters into the communications channel. If
     * \a n is omitted, all of the data is sent where appropriate, and the
     * number of bytes actually sent is returned. The implementation loops
     * over send() to send the data. If any of the calls to send() cannot
     * send any data, an RWNetCantSendError exception is thrown. If
     * sendAtLeast() is called on a non-blocking channel, it will probably
     * throw this same exception.
     */
    int  sendAtLeast(const char* buf, int bufLen, int n) const;

    /**
     * \copydoc RWPortal::sendAtLeast(const char*, int, int) const
     */
    void sendAtLeast(const char* buf, int bufLen) const;

    /**
     * \copydoc RWPortal::sendAtLeast(const char*, int, int) const
     */
    int  sendAtLeast(const RWCString& s, int n) const;

    /**
     * \copydoc RWPortal::sendAtLeast(const char*, int, int) const
     */
    void sendAtLeast(const RWCString& s) const;

protected:
    /**
     * Specifies the portal implementation. This constructor is used by
     * derived classes that create specific types of portals by passing in
     * specific types of portal implementations. The argument, like all
     * RWPortalImp instances, must live on the heap.
     */
    RWPortal(RWPortalImp* impl);

    // Derived classes may need to do things to the implementation. This
    // prevents the caller from modifying the impl_ handle that is maintained
    // by this class.
    /**
     * Provides derived classes access to the underlying implementation.
     */
    const RWPortalImp* implementation() const
    {
        return impl_;
    }

    /**
     * \copydoc implementation() const
     */
    RWPortalImp* implementation()
    {
        return impl_;
    }

private:
    RWTNetHandle<RWPortalImp> impl_;

public:
    /**
     * Returns \c true if \a p and \a q both use the same underlying portal
     * implementation object.
     */
    friend RW_NETWORK_SYMBOLIC bool operator==(const RWPortal& p, const RWPortal& q);

};

inline
RWPortal::RWPortal(RWPortalImp* imp)
    : impl_(imp)
{
}

inline
RWPortal::RWPortal()
    : impl_(new RWNoPortalImp)
{
}

inline
RWPortal::RWPortal(const RWPortal& x)
    : impl_(x.impl_)
{
}

inline
RWPortal::~RWPortal()
{
}

inline
RWPortal&
RWPortal::operator=(const RWPortal& x)
{
    if (this != &x) {
        impl_ = x.impl_;
    }
    return *this;
}

inline RWNetBuf
RWPortal::recv() const
{
    return impl_->recv();
}

inline void
RWPortal::sendAtLeast(const char* buf, int bufLen) const
{
    sendAtLeast(buf, bufLen, bufLen);
}

inline int
RWPortal::sendAtLeast(const RWCString& s, int n) const
{
    size_t bufLen = s.length();
    int maxBytes = bufLen > INT_MAX ? INT_MAX : (int)bufLen;
    return sendAtLeast(s.data(), maxBytes, n);
}

inline int
RWPortal::send(const RWCString& s) const
{
    size_t bufLen = s.length();
    int maxBytes = bufLen > INT_MAX ? INT_MAX : (int)bufLen;
    return impl_->send(s.data(), maxBytes);
}

inline int
RWPortal::send(const char* buf, int buflen) const
{
    return impl_->send(buf, buflen);
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif  // __rw_network_RWPortal_h__
