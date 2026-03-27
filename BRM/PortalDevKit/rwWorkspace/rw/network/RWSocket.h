#ifndef __rw_network_RWSocket_h__
#define __rw_network_RWSocket_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSocket.h#1 $
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

#include <rw/network/RWNetBuf.h>
#include <rw/network/RWSockAddr.h>
#include <rw/network/RWWinSockInfo.h>
#include <rw/network/pkgdefs.h>

#if !defined(RWNET_WINSOCK)
#  if defined(RW_NO_SYS_FILIO_H)
#    include <sys/ioctl.h>
#  else
#    include <sys/filio.h>
#    include <sys/sockio.h>
#  endif // RW_NO_SYS_FILIO_H
#endif // !RWNET_WINSOCK

struct msghdr;

#ifndef RWNET_WINSOCK
// SOCKET is the underlying type of the socket reference.  Winsock uses
// SOCKET automatically, this way unix matches.
// This is done outside of RWSocket so it can be used elsewhere, for example
// in the implementation of select.
// If this ever proves a problem due to namespace pollution we could
// create an RWSocket::SockFD or something which works everywhere.
/**
 * \relates RWSocket
 *
 * \c SOCKET is the type used by the underlying implementation as a
 * reference to the communication channel.
 */
typedef int SOCKET;
#endif

/**
 * \ingroup networking_module
 *
 * \brief
 * Wrapper for the C concept of a socket.
 *
 * RWSocket is a wrapper for the C concept of a socket. Its member functions
 * correspond exactly to the C functions in the Berkeley sockets API.
 * Typically, RWSocket member functions have the same names as the
 * corresponding C API functions, but the arguments and return values may be
 * different to reflect the C++ environment. For example, many member
 * functions have default arguments to handle the most common cases. Some
 * member functions take alternate parameter types that simplify the
 * interface (for example, using the RWSockAddrBase class instead of the
 * \b sockaddr structure). Sometimes, multiple overloads of a member
 * function exist to provide alternate APIs for different occasions.
 *
 * Almost all of the Berkeley sockets calls that use a single socket are
 * encapsulated in this class. Omitted calls include:
 *
 * - The database calls of form \c getXbyY (for example,
 * \b gethostbyname()), and IP address conversion routines (for example,
 * \b inet_ntoa()). These are encapsulated by the RWInetHost and RWInetPort
 * classes.
 * - The host-network conversion calls, such as \b htons(). These calls are
 * not needed -- the C++ API does the conversions automatically.
 * - \b select(). This is encapsulated by the RWSocketAttribute class.
 *
 * In addition to the functions that match the sockets API, some convenience
 * functions are included. They are id(), isValid(), getSocket(),
 * recvAtLeast(), and sendAtLeast().
 *
 * The socket is not shut down by a destructor. It must be explicitly shut
 * down by calling close(), closesocket(), or shutdown(). Use the RWPortal
 * layer for objects that close the portal automatically using a destructor.
 *
 * RWSocket has no state. All state (such as whether the socket blocks) is
 * kept in the communications channel.
 *
 * The Networking package provides a C++ wrapper for the native socket API.
 * As a result, return values from socket API calls are returned to the
 * caller unaltered.
 *
 * \note
 * This can result in different return values and, in some cases, different
 * behavior between calls to the same member functions on different
 * platforms (BSD or Winsock, for instance).
 *
 * For example, a connect call on a non-blocking socket returns with
 * \c EINPROGRESS from BSD, but returns with \c WSAVEWOULDBLOCK from
 * Winsock. You should consult your implementation-specific user's guide to
 * identify expected behavior.
 */
class RW_NETWORK_SYMBOLIC RWSocket
{
public:
    /**
     * The default constructor sets the socket to an invalid state. You must
     * initialize it with a call to
     * \ref socket(const RWSockType&) "socket()", connect(), bind(), or
     * listen() before it can be used.
     */
    RWSocket();

    /**
     * Creates an RWSocket that encapsulates the same C socket as \a s.
     */
    RWSocket(const RWSocket& s);

    /**
     * Creates an unconnected socket of the specified type. The resulting
     * socket must be bound to an address using bind(), connect(), or
     * listen() before it can be used.
     */
    RWSocket(const RWSockType& socketType);

    /**
     * Creates an RWSocket that encapsulates the C socket.
     */
    RWSocket(SOCKET existingSocket);

    /**
     * Accepts a connection that is waiting at this socket. A queue for
     * incoming connections must first be created using listen(). If \a addr
     * is non-null, the peer's address is returned in \a addr. You can also
     * get this information by calling getpeername() on the returned
     * RWSocket.
     *
     * If the socket is set to block (the default), then accept() blocks
     * until a connection request arrives. If the socket is set to be
     * non-blocking, accept() returns right away. If no connections are
     * available, the returned socket is invalid (use isValid() to check)
     * and \a *addr is unchanged.
     */
    RWSocket accept(RWSockAddr* addr = 0) const;

    /**
     * Assigns an address to an as-yet unnamed socket. This function is used
     * primarily by servers that need to specify the port on which they wait
     * for connections.
     *
     * \note
     * When the bind() member function is invoked on an uninitialized
     * socket, the function initializes the socket and sets the
     * \c SO_REUSEADDR option on the socket. If you do not want this option
     * to be set, call the \ref socket(const RWSockType&) "socket()" member
     * function to initialize the socket before you invoke bind(). See
     * section "Socket Security" under Chapter 8, "The Windows Socket
     * Adapter" in the <em>Essential Networking Module User's Guide</em> for
     * more information.
     */
    void bind(const RWSockAddrBase& address);

    /**
     * Terminates the connection and removes the socket. The socket is set
     * to an invalid state. Unless this socket is being shared with another
     * process, the resources used to maintain the socket are deallocated
     * and any unread data is discarded.
     */
    void close();

    /**
     * Alias for close().
     */
    void closesocket();

    // Connect to a remote socket.  If this is a stream socket, the initial
    // handshaking with the remote side is done.  If this is a datagram socket
    // this sets up the target for communication, but nothing is sent out over
    // the wire.
    // If the socket has not been initialized with [[socket()]], then [[connect]]
    // first initializes it.
    /**
     * Connects to a remote socket. If it is a stream socket, connect()
     * performs the initial handshaking with the remote side. If it is a
     * datagram socket, connect() sets up the target for communication, but
     * data is not sent. If the socket has not been initialized with
     * \ref socket(const RWSockType&) "socket()", then connect() initializes
     * it.
     */
    void connect(const RWSockAddrBase& address);

    /**
     * Returns the address of the peer connected to this socket.
     */
    RWSockAddr getpeername() const;

    /**
     * Returns the address of this socket.
     */
    RWSockAddr getsockname() const;

    /**
     * Returns the type information for this socket.
     */
    RWSockType getsocktype() const;

    /**
     * Determines a socket option setting.
     */
    void getsockopt(int level, int option, void* optval,
                    RWSockLenType*  optlen) const;

    /**
     * Determines a socket option setting. Assumes the \c SOL_SOCKET level
     * and an integer \a option, which is the usual case.
     */
    int  getsockopt(int option) const;

    /**
     * Returns a string describing self. The verbosity of the output is
     * controlled by \a level, where \c level=0 is the most basic output,
     * and \c level=9 is the most verbose. If not specified, a default value
     * of 0 is used and is guaranteed not to block.
     *
     * <b>Grammar Definitions</b>
     *
     * <pre>
     * ocal_addr ::= <em>\<the result of getsockname().id(\a level\></em>
     * peer_addr ::= <em>\<the result of getpeername().id(\a level\></em>
     * </pre>
     *
     * <table>
     * <tr>
     * <th>Socket State</th>
     * <th>Output Grammar</th>
     * </tr>
     * <tr>
     * <td>isValid() == \c false</td>
     * <td><tt>"invalid"</tt></td>
     * </tr>
     * <tr>
     * <td>\c bind() call failed</td>
     * <td><tt>"no address"</tt></td>
     * </tr>
     * <tr>
     * <td>connected</td>
     * <td><tt>local_addr "-->" peer_addr</tt></td>
     * </tr>
     * <tr>
     * <td>bound</td>
     * <td><tt>local_addr</tt></td>
     * </tr>
     * </table>
     */
    RWCString id(unsigned level = 0) const;

    /**
     * Prepares a socket to accept incoming connections. The \a backlog
     * parameter specifies the number of incoming connection requests that
     * the protocol software enqueues while a connection is being processed.
     *
     * \note
     * When the listen() member function is invoked on an uninitialized
     * socket, the function initializes the socket and sets the
     * \c SO_REUSEADDR option on the socket. If you do not want this option
     * to be set, call the \ref socket(const RWSockType&) "socket()" member
     * function to initialize the socket before you invoke listen(). See
     * section "Socket Security" under Chapter 8, "The Windows Socket
     * Adapter" in the <em>Essential Networking Module User's Guide</em> for
     * more information.
     */
    void listen(const RWSockAddrBase& addr, int backlog = 5);

    /**
     * Prepares a bound socket to accept incoming connections. The
     * \a backlog parameter specifies the number of incoming connection
     * requests that the protocol software enqueues while a connection is
     * being processed.
     */
    void listen(int backlog = 5) const;

    /**
     * Receives data from the socket. recv() is used to read data from a
     * connected socket. The \a flags parameter is formed by \c ORing one or
     * more of \c MSG_OOB (out of band data), or \c MSG_PEEK (peek at data
     * on the socket but do not consume it). The variant that uses an
     * explicit buffer returns the number of bytes actually received. This
     * may be zero in the case of a non-blocking socket without data
     * waiting. If an error occurs, an RWSocketError exception is thrown.
     */
    RWNetBuf  recv(int flags = 0) const;

    /**
     * \copydoc recv(int) const
     */
    int       recv(char* buf, int len, int flags = 0, RWNetBuf::State* s = 0) const;

    /**
     * Receives data from the socket, and can be used on any socket. The
     * \a flags parameter is formed by \c ORing one or more of \c MSG_OOB
     * (out of band data) or \c MSG_PEEK (peek at data on the socket but do
     * not consume it). \a addr, if it is specified and if the socket is a
     * datagram socket, becomes the address of the originator of the
     * message.
     */
    RWNetBuf  recvfrom(RWSockAddr* addr = 0, int flags = 0) const;

    /**
     * Receives data from the socket, and can be used on any socket. The
     * \a flags parameter is formed by \c ORing one or more of \c MSG_OOB
     * (out of band data) or \c MSG_PEEK (peek at data on the socket but do
     * not consume it). \a addr, if it is specified and if the socket is a
     * datagram socket, becomes the address of the originator of the
     * message. This overload returns the number of bytes actually received.
     * This may be zero in the case of a non-blocking socket without data
     * waiting.
     */
    int       recvfrom(char* buf, int len, RWSockAddr* addr = 0, int flags = 0, RWNetBuf::State* state = 0) const;

#if !defined(RWNET_NO_MSGHDR)
    /**
     * Alias for recvfrom(char*,int,RWSockAddr*,int,RWNetBuf::State*)const.
     *
     * \conditional
     * This method is available only on systems that provide
     * <tt>struct msghdr</tt>.
     */
    int       recvmsg(msghdr* msg, int flags = 0,  RWNetBuf::State* s = 0) const;
#endif

    /**
     * This is guaranteed to either receive \a n characters or throw an
     * exception. The call is only valid for stream sockets. The
     * implementation loops over recv() until all of the data has been
     * received. An RWNetCantRecvError exception is thrown if one of the
     * calls to recv() returns no data. If you call recvAtLeast() on a
     * non-blocking socket, it will probably throw an exception.
     */
    RWNetBuf  recvAtLeast(int n) const;

    /**
     * \copydoc recvAtLeast(int) const
     */
    int       recvAtLeast(char* buf, int len, int n, RWNetBuf::State* s = 0) const;

    /**
     * Sends data from a connected socket. These functions return the number
     * of bytes sent. If an error occurs, an RWSocketError exception is
     * thrown.
     *
     * \note
     * When calling send(), the application must check the number of bytes
     * sent, and resend if necessary. The sendAtLeast() method guarantees
     * the transmission of the number of bytes specified (or the entire
     * buffer if no size is specified).
     *
     * \note
     * Sending data on a closed socket may result in the generation of a
     * SIGPIPE signal from the underlying socket library. Avoid this by
     * checking that the socket's sock_attr_canwrite attribute is true
     * before each call to send(). Refer to RWSocketAttribute for details on
     * checking socket attributes. Alternatively, you can use a signal
     * handler to explicitly handle or ignore SIGPIPE.
     */
    int send(const RWCString& buf, int flags = 0) const;

    /**
     * \copydoc send(const RWCString&, int) const
     */
    int send(const char* buf, int len, int flags = 0) const;

    /**
     * Send data from a socket, and can be used on any socket. The \a to
     * parameter is ignored for a connected socket. These functions return
     * the number of bytes sent. This is zero if the socket is non-blocking
     * and the internal buffer for the socket is full.
     */
    int sendto(const RWCString& buf, const RWSockAddrBase& to, int flags = 0) const;

    /**
     * \copydoc sendto()
     */
    int sendto(const char* buf, int len, const RWSockAddrBase& to, int flags = 0) const;

#if !defined(RWNET_NO_MSGHDR)
    /**
     * Alias for sendto(const char*, int, const RWSockAddrBase&, int) const.
     *
     * \conditional
     * This method is available only on systems that provide
     * <tt>struct msghdr</tt>.
     */
    int sendmsg(msghdr* msg, int flags = 0) const;
#endif

    /**
     * Guaranteed to send at least \a n characters or the entire buffer if
     * \a n is not specified. This call is valid only for stream sockets.
     * The implementation loops over send() to send the data. If any of the
     * calls to \c send cannot send any data, an RWNetCantSendError
     * exception is thrown. If you call sendAtLeast() on a non-blocking
     * socket, it will probably throw an exception if \a n is greater than
     * the amount of unused space in the system's buffer for the socket.
     */
    void sendAtLeast(const RWCString& buf) const;

    /**
     * \copydoc sendAtLeast(const RWCString&) const
     */
    int  sendAtLeast(const RWCString& buf, int n) const;

    /**
     * \copydoc sendAtLeast(const RWCString&) const
     */
    void sendAtLeast(const char* buf, int len) const;

    /**
     * \copydoc sendAtLeast(const RWCString&) const
     */
    int  sendAtLeast(const char* buf, int len, int n) const;

    /**
     * Sets a socket option setting. The second function assumes the
     * \c SOL_SOCKET level and an integer \a option, which is the usual
     * case.
     */
    void setsockopt(int level, int option, void* optval, int optlen) const;

    /**
     * \copydoc setsockopt(int, int, void*, int) const
     */
    void setsockopt(int option, int optval) const;

    // Shut down either the reading side (how=0), the writing side (how=1), or
    // both sides (how=2) of a full duplex connection.  The socket resources
    // are not deallocated.  Use close() or closesocket() for that.
    /**
     * Shuts down either the reading side (\c how=0), the writing side
     * (\c how=1), or both sides (\c how=2) of a full duplex connection. Use
     * close() or closesocket() to deallocate the socket resources.
     */
    void shutdown(int how = 2) const;

    /**
     * Shuts down one side of the connection.
     */
    void shutdownread() const;

    /**
     * Shuts down one side of the connection.
     */
    void shutdownwrite() const;


#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSocket::getSocket() instead")
    SOCKET socket() const;
#endif
    /**
     * Returns the C API socket descriptor encapsulated in RWSocket.
     */
    SOCKET getSocket() const;

    // Creates an unconnected socket of the specified type.  The resulting
    // socket must be bound to an address using bind or connect before
    // it can be used.
    // If this [[RWSocket]] was already associated with a socket, that
    // association is lost.
    /**
     * Creates an unconnected socket of the specified \a type. The resulting
     * socket must be bound to an address using bind(), connect(), or
     * listen() before it can be used.
     */
    void socket(const RWSockType& type);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSocket::isValid() instead")
    bool valid() const;
#endif

    /**
     * Verifies that the socket is ready for use.
     */
    bool isValid() const;

#ifndef RWNET_DONT_INCLUDE_IOCTL
    /**
     * Gets or retrieves socket operating parameters.
     */
    void ioctl(long cmd, void* arg) const;

    /**
     * Gets or retrieves socket operating parameters. This overload is
     * useful for commands that expect an integer argument and return
     * nothing (such as \c FIONBIO).
     *
     * This function is commonly used to set blocking or non-blocking mode
     * on a socket. To set a socket to non-blocking, use
     * \ref ioctl(long, int) const "ioctl(FIONBIO,1)". To set it to
     * blocking, use \ref ioctl(long, int) const "ioctl(FIONBIO,0)".
     *
     * \note
     * You can also use the global functions rwSetBlocking() and
     * rwSetNonBlocking() to set the blocking mode on an RWSocket.
     */
    void ioctl(long cmd, int arg) const;

    /**
     * Gets or retrieves socket operating parameters. This overload is
     * useful for commands that return <tt>int</tt>s (like \c FIONREAD or
     * \c SIOCATMARK).
     */
    int  ioctl(long cmd) const;

    /**
     * Alias for ioctl(long,void*) const
     */
    void ioctlsocket(long cmd, void* arg) const;

    /**
     * Alias for ioctl(long,int) const
     */
    void ioctlsocket(long cmd, int arg) const;

    /**
     * Alias for ioctl(long) const
     */
    int  ioctlsocket(long cmd) const;
#endif

protected:
    /**
     * Contains the socket itself. No other state is stored in this class.
     * All state information related to the socket is kept in the socket.
     */
    SOCKET socket_;

    /**
     * Sets the error code to no error. To make your application portable,
     * use this function instead of the underlying OS specific function
     * calls.
     */
    void clearError() const;

    /**
     * Returns the last error on this socket. To make your application
     * portable, use this function instead of the underlying OS specific
     * function calls.
     */
    int lastError() const;

    /**
     * Throws an RWSocketError exception based on the error code passed in
     * the parameter.
     */
    void raise(const char* funcName, int err) const;

    /**
     * Throws an RWSocketError exception based on the error code passed in
     * the parameter.
     */
    void raiseUnlessWouldBlock(const char* funcName, int err) const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 4, use
     * \ref RWSocket::raise(const char*, int) const "raise(const char*, int)"
     * in conjunction with \ref RWSocket::lastError() "lastError()".
     */
    RW_DEPRECATE_FUNC("Use RWSocket::raise(const char*, int) instead")
    void raise(const char* funcName) const;

    /**
     * \deprecated
     * As of SourcePro 4, use
     * \ref RWSocket::raiseUnlessWouldBlock(const char*, int) const "raiseUnlessWouldBlock(const char*, int)"
     * in conjunction with \ref RWSocket::lastError() "lastError()".
     */
    RW_DEPRECATE_FUNC("Use RWSocket::raiseUnlessWouldBlock(const char*, int) instead")
    void raiseUnlessWouldBlock(const char* funcName) const;

    // this method is deprecated as it does not genericise
    // error handling enough. we already throw several types
    // of exceptions, sometimes calling doRaise, sometimes not...
    /**
     * \deprecated
     * As of SourcePro 4, use
     * \ref RWSocket::raise(const char*, int) const "raise(const char*, int)"
     * instead.
     *
     * Throws an RWSocketError exception based on the value of the parameter
     * \a err.
     */
    RW_DEPRECATE_FUNC("Use RWSocket::raise(const char*, int) instead")
    static void doRaise(int err, const char* funcName);
#endif

};

/**
 * \relates RWSocket
 *
 * Outputs a representation of \a x on \a strm. The representation is
 * generated using the member function x.id() with \c level=0.
 *
 * \note
 * This class does not have an extraction (>>) operator.
 */
RW_NETWORK_SYMBOLIC std::ostream&
operator<<(std::ostream&, const RWSocket& sock);

/**
 * \relates RWSocket
 *
 * Returns \c true if the two sockets refer to the same underlying
 * communications channel.
 */
inline bool operator==(const RWSocket& lhs, const RWSocket& rhs)
{
    return lhs.getSocket() == rhs.getSocket();
}

/**
 * \relates RWSocket
 *
 * Returns \c false if the two sockets refer to the same underlying
 * communications channel.
 */
inline bool operator!=(const RWSocket& lhs, const RWSocket& rhs)
{
    return lhs.getSocket() != rhs.getSocket();
}

inline SOCKET
RWSocket::getSocket() const
{
    return socket_;
}

inline void
RWSocket::shutdownread() const
{
    shutdown(0);
}

inline void
RWSocket::shutdownwrite() const
{
    shutdown(1);
}

#if !defined(RW_DISABLE_DEPRECATED)
inline bool
RWSocket::valid() const
{
    return isValid();
}

inline SOCKET
RWSocket::socket() const
{
    return getSocket();
}
#endif

// for convenience, use these macros instead calling ioctl.
// note that the macro expects an RWSocket, not a socket number.

#ifndef RWNET_DONT_INCLUDE_IOCTL
#  if !defined(RW_DISABLE_DEPRECATED)
/**
 * \relates RWSocket
 *
 * \deprecated
 * As of SourcePro 1, use rwSetBlocking() instead.
 */
RW_DEPRECATE_MACRO("SET_BLOCKING", "Use rwSetBlocking() instead")
#    define SET_BLOCKING(rwsocket)    rwsocket.ioctl(FIONBIO, 0);

/**
 * \relates RWSocket
 *
 * \deprecated
 * As of SourcePro 1, use rwSetNonBlocking() instead.
 */
RW_DEPRECATE_MACRO("SET_NON_BLOCKING", "Use rwSetNonBlocking() instead")
#    define SET_NON_BLOCKING(rwsocket) rwsocket.ioctl(FIONBIO, 1);
#  endif

/**
 * \relates RWSocket
 *
 * Sets an RWSocket into blocking mode.
 */
inline void
rwSetBlocking(RWSocket& s)
{
    s.ioctl(FIONBIO, 0);
}

/**
 * \relates RWSocket
 *
 * Sets an RWSocket into non-blocking mode.
 */
inline void
rwSetNonBlocking(RWSocket& s)
{
    s.ioctl(FIONBIO, 1);
}

#endif /* RWNET_DONT_INCLUDE_IOCTL */

#endif // __rw_network_RWSocket_h__
