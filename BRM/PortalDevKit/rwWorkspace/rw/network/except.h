#ifndef __rw_network_except_h__
#define __rw_network_except_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/except.h#1 $
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

#include <rw/network/RWWinSockInfo.h>
#include <rw/network/pkgdefs.h>
#include <rw/network/util.h>
#include <rw/cstring.h>
#include <rw/rwerr.h>

class RWSockType;

/**
 * \ingroup networking_module
 *
 * \brief
 * Reports that an Internet host address lookup failed.
 *
 * An RWInetHostNotFoundError exception is thrown when an Internet host
 * address lookup fails.
 */
class RW_NETWORK_GLOBAL RWInetHostNotFoundError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with the host name set to \a host.
     */
    RWInetHostNotFoundError(const RWCString& host);

    /**
     */
    RWCString host() const
    {
        return host_;
    }

private:
    RWCString host_;
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports that an internet service name lookup failed.
 *
 * An RWInetServiceNotFoundError exception is thrown when an internet
 * service name lookup fails.
 */
class RW_NETWORK_GLOBAL RWInetServiceNotFoundError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with the service name set to \a service.
     */
    RWInetServiceNotFoundError(const RWCString& service);

    /**
     */
    RWCString service() const
    {
        return service_;
    }

private:
    RWCString service_;
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports an attempt to register multiple socket address factories for a
 * socket address family.
 *
 * An RWNetAlreadyRegisteredError exception is thrown when an attempt is
 * made to register multiple socket address factories for a socket address
 * family.
 */
class RW_NETWORK_GLOBAL RWNetAlreadyRegisteredError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception with the socket family name set to \a family.
     */
    RWNetAlreadyRegisteredError(const RWCString& family);

    /**
     * Constructs an exception with the socket family type set to \a family.
     */
    RWNetAlreadyRegisteredError(int family);

private:
    RWCString familyAsString_;
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the inability to create a portal.
 *
 * An RWNetCantCreatePortalError exception thrown if the library is unable
 * to create a portal.
 */
class RW_NETWORK_GLOBAL RWNetCantCreatePortalError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with the error string set to \a err.
     */
    RWNetCantCreatePortalError(const RWCString& err);
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the failure to receive data on a communication channel.
 *
 * An RWNetCantRecvError exception is thrown when an attempt to receive data
 * on a communications channel fails.
 */
class RW_NETWORK_GLOBAL RWNetCantRecvError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with a default message string.
     */
    RWNetCantRecvError();
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports a failure to send data on a communications channel.
 *
 * An RWNetCantRecvError exception is thrown when an attempt to send data on
 * a communications channel fails.
 */
class RW_NETWORK_GLOBAL RWNetCantSendError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with a default message string.
     */
    RWNetCantSendError();
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports use of an invalid RWSocket with rwSocketSelect().
 *
 * An RWNetInvalidSocketError exception is thrown when an invalid RWSocket
 * is used with rwSocketSelect().
 */
class RW_NETWORK_GLOBAL RWNetInvalidSocketError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception with a default message string.
     */
    RWNetInvalidSocketError();
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports an attempt to send or receive data on an RWPortal that is not
 * bound to a communications channel.
 *
 * An RWNetNoChannelError exception is thrown when an attempts is made to
 * send or receive data on an RWPortal that is not bound to a communications
 * channel.
 */
class RW_NETWORK_GLOBAL RWNetNoChannelError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception with a default message string.
     */
    RWNetNoChannelError();
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports a request to produce a derived RWSockAddr for a socket family or
 * name that is not registered with the factory.
 *
 * An RWNetNoFactoryRegisteredError exception is thrown when a
 * RWSockAddrFactory is asked to produce a derived RWSockAddr for a socket
 * family or name that is not registered with that factory.
 */
class RW_NETWORK_GLOBAL RWNetNoFactoryRegisteredError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with the error string set to \a msg.
     */
    RWNetNoFactoryRegisteredError(const RWCString& msg) : RWExternalErr(msg) {}

private:
    RWCString familyAsString_;
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports a request to produce a derived RWSockAddr for a socket family
 * that is not registered with the factory.
 *
 * An RWNetNoNumberFactoryRegisteredError exception is thrown when a
 * RWSockAddrFactory is asked to produce a derived RWSockAddr for a socket
 * family that is not registered with that factory.
 */
class RW_NETWORK_GLOBAL RWNetNoNumberFactoryRegisteredError
    : public RWNetNoFactoryRegisteredError
{
public:

    /**
     * Constructs an exception with the socket family set to \a family.
     */
    RWNetNoNumberFactoryRegisteredError(int family);

    /**
     * Returns the socket family.
     */
    int family() const
    {
        return family_;
    }

private:
    int family_;
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports a request to produce a derived RWSockAddr for a socket family
 * that is not registered with the factory.
 *
 * An RWNetNoNameFactoryRegisteredError exception is thrown when a
 * RWSockAddrFactory is asked to produce a derived RWSockAddr for a socket
 * family that is not registered with that factory.
 */
class RW_NETWORK_GLOBAL RWNetNoNameFactoryRegisteredError
    : public RWNetNoFactoryRegisteredError
{
public:

    /**
     * Constructs an exception with the socket family name to \a family.
     */
    RWNetNoNameFactoryRegisteredError(const RWCString& family);

    /**
     * Returns the socket family name.
     */
    RWCString family() const
    {
        return family_;
    }

private:
    RWCString family_;
};

#if !defined(RW_DISABLE_DEPRECATED)

/**
 * \ingroup networking_module
 *
 * \deprecated
 * As of SourcePro 11.1, this exception is thrown only by a deprecated
 * RWWinSockInfo constructor.
 *
 * \brief
 * Deprecated. Reports an attempt to pass an unknown blocking hook to the
 * RWWinSockInfo constructor
 *
 * An RWNetNoSuchBlockingHookError exception is thrown when the blocking
 * hook passed to the RWWinSockInfo constructor is not known.
 */
class RW_DEPRECATE_TYPE("") RW_NETWORK_GLOBAL RWNetNoSuchBlockingHookError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception with the blocking hook set to \a ID.
     */
    RWNetNoSuchBlockingHookError(int ID);
};

#endif

/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the failure of a network operation to complete within the
 * specified timeout period.
 *
 * An RWNetOperationTimeoutError exception is thrown when a network
 * operation fails to complete within the specified timeout period.
 */
class RW_NETWORK_GLOBAL RWNetOperationTimeoutError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with a default message string.
     */
    RWNetOperationTimeoutError();

    /**
     * Constructs an exception with the message string \a msg.
     */
    RWNetOperationTimeoutError(const RWCString& msg);
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports an attempt to use an unsupported timed operation.
 *
 * An RWNetTimeoutNotImplementedError exception is thrown when a timed
 * operation is attempted but not supported. This would typically occur when
 * using RWTimedPortal on an RWPortalImp that doesn't support timed send and
 * receive operations.
 */
class RW_NETWORK_GLOBAL RWNetTimeoutNotImplementedError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception with a default message string.
     */
    RWNetTimeoutNotImplementedError();
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the failure to initialize the requested version of the Windows
 * Socket library, or a failure to successfully clean up the library.
 *
 * An RWNetWinsockInitError exception is thrown if requested version of the
 * Windows Socket library could not be initialized, or if there was a
 * problem cleaning up the Windows Socket library.
 */
class RW_NETWORK_GLOBAL RWNetWinsockInitError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with the error number set to \a err.
     */
    RWNetWinsockInitError(int err);
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the inability to parse a string into a valid socket address.
 *
 * An RWSockBadAddressFormatError exception is thrown when a string cannot
 * be parsed into a valid socket address.
 */
class RW_NETWORK_GLOBAL RWSockBadAddressFormatError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with the address string \a s.
     */
    RWSockBadAddressFormatError(const RWCString& s);
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports an error on an RWSocket.
 *
 * An RWSocketError is thrown when an error occurs on a RWSocket.
 */
class RW_NETWORK_GLOBAL RWSocketError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception with the error number \a errorNumber, and the
     * function name \a funcname.
     */
    RWSocketError(int errorNumber, const RWCString& funcname);

    /**
     * Returns the name of the function that generated this exception.
     */
    RWCString where() const
    {
        return funcname_;
    }

    /**
     * Returns a string that describes the error.
     */
    RWCString errDescription() const
    {
        return errNumberToString(errno_);
    }

    /**
     * Returns the error number.
     */
    int errorNumber() const
    {
        return errno_;
    }

    static RWCString errNumberToString(int errorNumber);

private:
    RWCString funcname_;
    int       errno_;
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the attempt to change the type of a valid socket.
 *
 * An RWSockTypeChangeError exception is throw when an operation attempts to
 * change the type of a valid socket.
 */
class RW_NETWORK_GLOBAL RWSockTypeChangeError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception with the current socket type \a socktype and
     * the requested socket type \a addrtype.
     */
    RWSockTypeChangeError(const RWSockType& socktype, const RWSockType& addrtype);
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the attempt to convert one derived RWSockAddr to some other
 * RWSockAddr type.
 *
 * An RWSockWrongAddressTypeError exception is thrown when a operation
 * attempts to convert one derived RWSockAddr to some other RWSockAddr type.
 */
class RW_NETWORK_GLOBAL RWSockWrongAddressTypeError
    : public RWInternalErr
{
public:

    /**
     * Constructs an exception that describes a failed conversion from the
     * type \a from to the type \a to.
     */
    RWSockWrongAddressTypeError(const RWCString& from, const RWCString& to);
};


/**
 * \ingroup networking_module
 *
 * \brief
 * Reports the failure of a call to rwSocketSelect().
 *
 * An RWNetSelectError exception is thrown when a call to rwSocketSelect()
 * fails.
 */
class RW_NETWORK_GLOBAL RWNetSelectError
    : public RWExternalErr
{
public:

    /**
     * Constructs an exception with a default message string.
     */
    RWNetSelectError();

    /**
     * Return the error number.
     */
    int error() const
    {
        return err_;
    }

private:
    int err_;
};


#if defined(RWNET_WINSOCK)

const int RWNETEINTR                   = WSAEINTR;
const int RWNETEBADF                   = WSAEBADF;
const int RWNETEACCES                  = WSAEACCES;
const int RWNETEFAULT                  = WSAEFAULT;
const int RWNETEINVAL                  = WSAEINVAL;
const int RWNETEMFILE                  = WSAEMFILE;
const int RWNETEWOULDBLOCK             = WSAEWOULDBLOCK;
const int RWNETEINPROGRESS             = WSAEINPROGRESS;
const int RWNETEALREADY                = WSAEALREADY;
const int RWNETENOTSOCK                = WSAENOTSOCK;
const int RWNETEDESTADDRREQ            = WSAEDESTADDRREQ;
const int RWNETEMSGSIZE                = WSAEMSGSIZE;
const int RWNETEPROTOTYPE              = WSAEPROTOTYPE;
const int RWNETENOPROTOOPT             = WSAENOPROTOOPT;
const int RWNETEPROTONOSUPPORT         = WSAEPROTONOSUPPORT;
const int RWNETESOCKTNOSUPPORT         = WSAESOCKTNOSUPPORT;
const int RWNETEOPNOTSUPP              = WSAEOPNOTSUPP;
const int RWNETEPFNOSUPPORT            = WSAEPFNOSUPPORT;
const int RWNETEAFNOSUPPORT            = WSAEAFNOSUPPORT;
const int RWNETEADDRINUSE              = WSAEADDRINUSE;
const int RWNETEADDRNOTAVAIL           = WSAEADDRNOTAVAIL;
const int RWNETENETDOWN                = WSAENETDOWN;
const int RWNETENETUNREACH             = WSAENETUNREACH;
const int RWNETENETRESET               = WSAENETRESET;
const int RWNETECONNABORTED            = WSAECONNABORTED;
const int RWNETECONNRESET              = WSAECONNRESET;
const int RWNETENOBUFS                 = WSAENOBUFS;
const int RWNETEISCONN                 = WSAEISCONN;
const int RWNETENOTCONN                = WSAENOTCONN;
const int RWNETESHUTDOWN               = WSAESHUTDOWN;
const int RWNETETOOMANYREFS            = WSAETOOMANYREFS;
const int RWNETETIMEDOUT               = WSAETIMEDOUT;
const int RWNETECONNREFUSED            = WSAECONNREFUSED;
const int RWNETELOOP                   = WSAELOOP;
const int RWNETENAMETOOLONG            = WSAENAMETOOLONG;
const int RWNETEHOSTDOWN               = WSAEHOSTDOWN;
const int RWNETEHOSTUNREACH            = WSAEHOSTUNREACH;
const int RWNETENOTEMPTY               = WSAENOTEMPTY;
const int RWNETEPROCLIM                = WSAEPROCLIM;
const int RWNETEUSERS                  = WSAEUSERS;
const int RWNETEDQUOT                  = WSAEDQUOT;
const int RWNETESTALE                  = WSAESTALE;
const int RWNETEREMOTE                 = WSAEREMOTE;
const int RWNETEPIPE                   = 0;
const int RWNETSYSNOTREADY             = WSASYSNOTREADY;
const int RWNETVERNOTSUPPORTED         = WSAVERNOTSUPPORTED;
const int RWNETNOTINITIALISED          = WSANOTINITIALISED;
const int RWNETHOST_NOT_FOUND          = WSAHOST_NOT_FOUND;
const int RWNETTRY_AGAIN               = WSATRY_AGAIN;
const int RWNETNO_RECOVERY             = WSANO_RECOVERY;
const int RWNETNO_DATA                 = WSANO_DATA;
const int RWNETNO_ADDRESS              = WSANO_ADDRESS;

#else /* UNIX */

/**
 * \relates RWSocketError
 *
 * Socket error code that could be returned from
 * RWSocketError::errorNumber().
 */
//@{
const int RWNETEINTR                   = EINTR;
const int RWNETEBADF                   = EBADF;
const int RWNETEACCES                  = EACCES;
const int RWNETEFAULT                  = EFAULT;
const int RWNETEINVAL                  = EINVAL;
const int RWNETEMFILE                  = EMFILE;
const int RWNETEUSERS                  = EUSERS;
const int RWNETESTALE                  = ESTALE;
const int RWNETEREMOTE                 = EREMOTE;
const int RWNETEWOULDBLOCK             = EWOULDBLOCK;
const int RWNETEINPROGRESS             = EINPROGRESS;
const int RWNETEALREADY                = EALREADY;
const int RWNETENOTSOCK                = ENOTSOCK;
const int RWNETEDESTADDRREQ            = EDESTADDRREQ;
const int RWNETEMSGSIZE                = EMSGSIZE;
const int RWNETEPROTOTYPE              = EPROTOTYPE;
const int RWNETENOPROTOOPT             = ENOPROTOOPT;
const int RWNETEPROTONOSUPPORT         = EPROTONOSUPPORT;
const int RWNETESOCKTNOSUPPORT         = ESOCKTNOSUPPORT;
const int RWNETEOPNOTSUPP              = EOPNOTSUPP;
const int RWNETEPFNOSUPPORT            = EPFNOSUPPORT;
const int RWNETEAFNOSUPPORT            = EAFNOSUPPORT;
const int RWNETEADDRINUSE              = EADDRINUSE;
const int RWNETEADDRNOTAVAIL           = EADDRNOTAVAIL;
const int RWNETENETDOWN                = ENETDOWN;
const int RWNETENETUNREACH             = ENETUNREACH;
const int RWNETENETRESET               = ENETRESET;
const int RWNETECONNABORTED            = ECONNABORTED;
const int RWNETECONNRESET              = ECONNRESET;
const int RWNETENOBUFS                 = ENOBUFS;
const int RWNETEISCONN                 = EISCONN;
const int RWNETENOTCONN                = ENOTCONN;
const int RWNETESHUTDOWN               = ESHUTDOWN;
const int RWNETETOOMANYREFS            = ETOOMANYREFS;
const int RWNETETIMEDOUT               = ETIMEDOUT;
const int RWNETECONNREFUSED            = ECONNREFUSED;
const int RWNETELOOP                   = ELOOP;
const int RWNETENAMETOOLONG            = ENAMETOOLONG;
const int RWNETEHOSTDOWN               = EHOSTDOWN;
const int RWNETEHOSTUNREACH            = EHOSTUNREACH;
const int RWNETENOTEMPTY               = ENOTEMPTY;
const int RWNETEPIPE                   = EPIPE;
const int RWNETEPROCLIM                = 0;  // no such code in unix
const int RWNETEDQUOT                  = 0;  // no such code in unix
const int RWNETSYSNOTREADY             = 0;  // no such code in unix;
const int RWNETVERNOTSUPPORTED         = 0;  // no such code in unix;
const int RWNETNOTINITIALISED          = 0;  // no such code in unix;
const int RWNETHOST_NOT_FOUND          = 0;  // no such code in unix;
const int RWNETTRY_AGAIN               = 0;  // no such code in unix;
const int RWNETNO_RECOVERY             = 0;  // no such code in unix;
const int RWNETNO_DATA                 = 0;  // no such code in unix;
const int RWNETNO_ADDRESS              = 0;  // no such code in unix;
//@}

#endif


#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWInetHostNotFoundError instead") RWInetHostNotFoundError                          RWInetHostNotFound;
typedef RW_DEPRECATE_TYPE("Use RWInetServiceNotFoundError instead") RWInetServiceNotFoundError                    RWInetServiceNotFound;
typedef RW_DEPRECATE_TYPE("Use RWNetAlreadyRegisteredError instead") RWNetAlreadyRegisteredError                  RWNetAlreadyRegistered;
typedef RW_DEPRECATE_TYPE("Use RWNetCantCreatePortalError instead") RWNetCantCreatePortalError                    RWNetCantCreatePortal;
typedef RW_DEPRECATE_TYPE("Use RWNetCantRecvError instead") RWNetCantRecvError                                    RWNetCantRecv;
typedef RW_DEPRECATE_TYPE("Use RWNetCantSendError instead") RWNetCantSendError                                    RWNetCantSend;
typedef RW_DEPRECATE_TYPE("Use RWNetInvalidSocketError instead") RWNetInvalidSocketError                          RWNetInvalidSocket;
typedef RW_DEPRECATE_TYPE("Use RWNetNoChannelError instead") RWNetNoChannelError                                  RWNetNoChannel;
typedef RW_DEPRECATE_TYPE("Use RWNetNoFactoryRegisteredError instead") RWNetNoFactoryRegisteredError              RWNetNoFactoryRegistered;
typedef RW_DEPRECATE_TYPE("Use RWNetNoNameFactoryRegisteredError instead") RWNetNoNameFactoryRegisteredError       RWNetNoNameFactoryRegistered;
typedef RW_DEPRECATE_TYPE("Use RWNetNoNumberFactoryRegisteredError instead") RWNetNoNumberFactoryRegisteredError  RWNetNoNumberFactoryRegistered;
typedef RW_DEPRECATE_TYPE("Use RWNetNoSuchBlockingHookError instead") RWNetNoSuchBlockingHookError                RWNetNoSuchBlockingHook;
typedef RW_DEPRECATE_TYPE("Use RWNetSelectError instead") RWNetSelectError                                        RWNetSelectException;
typedef RW_DEPRECATE_TYPE("Use RWNetWinsockInitError instead") RWNetWinsockInitError                              RWNetWinsockInitErr;
typedef RW_DEPRECATE_TYPE("Use RWSockBadAddressFormatError instead") RWSockBadAddressFormatError                  RWSockBadAddressFormat;
typedef RW_DEPRECATE_TYPE("Use RWSocketError instead") RWSocketError                                              RWSockErr;
typedef RW_DEPRECATE_TYPE("Use RWSockTypeChangeError instead") RWSockTypeChangeError                              RWSockTypeChange;
typedef RW_DEPRECATE_TYPE("Use RWSockWrongAddressTypeError instead") RWSockWrongAddressTypeError                  RWSockWrongAddressType;
#endif

#endif // __rw_network_except_h__
