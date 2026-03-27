#ifndef __rw_network_RWTSocketAttribute_h__
#define __rw_network_RWTSocketAttribute_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTSocketAttribute.h#1 $
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
 * RWTSocketAttribute:  Socket events and an interface to detect socket events
 *
 * The [[RWTSocketAttribute]] class encapsulates conditions that may be
 * true for a socket.
 *
 * The [[RWTSocketAttribute]] class is used by the global function [[select]]
 * to do asynchronous I/O.
 *
 * This class could have been implemented using inheritance to represent
 * the various possible types of attributes: a RWSocketReadAtt for a read
 * attribute, for example.  There are two downsides to this approach.  First,
 * it would be impossible to use one object to represent multiple attributes
 * (ok, at least not easily, you could invent composite event objects).
 * More importantly, the chosen design is lightweight and simple, and
 * allows us to pass attributes around by value.  This makes management of
 * event collections much simpler.  The downside to the chosen approach
 * is that it tends to encourage "switch statement" style coding, and
 * clients cannot add new attribute types.
 */

#include <rw/network/RWSocket.h>
#include <rw/tvordvec.h>

/**
 * \ingroup networking_module
 * \class RWTSocketAttribute
 *
 * \brief
 * Represents a set of attributes on a socket.
 *
 * RWTSocketAttribute encapsulates conditions that may be true for a socket.
 * An RWTSocketAttribute serves two purposes: it is used to represent a set
 * of attributes on a socket, and it is used to indicate that a particular
 * attribute is \c true. It consists of two parts: the socket and the
 * attribute.
 */
template <class Socket>
class RWTSocketAttribute
{
public:
    /**
     * The #Attribute type indicates the condition(s) on the socket.
     * Attributes are used to indicate conditions of interest and to
     * indicate what has happened on the socket. Attributes can be
     * aggregated by \c ORing them together. For example, the attribute
     * #sock_attr_canread|#sock_attr_canwrite on a socket indicates that the
     * socket can either read or write.
     *
     * The later enum values (\c NIL, \c CANREAD, \c CANWRITE,
     * \c RWEXCEPTION, \c ISEXCEPTION, \c EXCEPTION, \c ISCONNECTED,
     * \c CANACCEPT, \c ANY) have been retained, but are deprecated. You can
     * refuse support for these values by defining the macro
     * \c RW_DISABLE_DEPRECATED.
     */
    enum Attribute {

#if !defined(RW_DISABLE_DEPRECATED)

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_nil "sock_attr_nil" instead.
         *
         * No attributes.
         */
        RW_DEPRECATE_ENUMERATOR(NIL, "Use RWTSocketAttribute::sock_attr_nil instead") = 0,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_canread "sock_attr_canread"
         * instead.
         *
         * Data is available for reading.
         */
        RW_DEPRECATE_ENUMERATOR(CANREAD, "Use RWTSocketAttribute::sock_attr_canread instead") = 1,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_canwrite "sock_attr_canwrite"
         * instead.
         *
         * Data is available for writing.
         */
        RW_DEPRECATE_ENUMERATOR(CANWRITE, "Use RWTSocketAttribute::sock_attr_canwrite instead") = 2,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_exception "sock_attr_exception"
         * instead.
         *
         * An exception, such as an error or out-of-band data.
         */
        RW_DEPRECATE_ENUMERATOR(RWEXCEPTION, "Use RWTSocketAttribute::sock_attr_exception instead") = 4,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_exception "sock_attr_exception"
         * instead.
         *
         * An exception, such as an error or out-of-band data.
         */
        RW_DEPRECATE_ENUMERATOR(ISEXCEPTION, "Use RWTSocketAttribute::sock_attr_exception instead") = 4,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_exception "sock_attr_exception"
         * instead.
         *
         * An exception, such as an error or out-of-band data.
         */
        RW_DEPRECATE_ENUMERATOR(EXCEPTION, "Use RWTSocketAttribute::sock_attr_exception instead") = 4,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_isconnected "sock_attr_isconnected"
         * instead.
         *
         * Connect has completed.
         */
        RW_DEPRECATE_ENUMERATOR(ISCONNECTED, "Use RWTSocketAttribute::sock_attr_isconnected instead") = 8,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_canaccept "sock_attr_canaccept"
         * instead.
         *
         * A new connection is ready to be accepted.
         */
        RW_DEPRECATE_ENUMERATOR(CANACCEPT, "Use RWTSocketAttribute::sock_attr_canaccept instead") = 32,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWTSocketAttribute::sock_attr_any "sock_attr_any" instead.
         *
         * Any Attribute
         */
        RW_DEPRECATE_ENUMERATOR(ANY, "Use RWTSocketAttribute::sock_attr_any instead") = ~0,

#endif /* RW_DISABLE_DEPRECATED */

        /**
         * No attributes.
         */
        sock_attr_nil = 0,

        /**
         * Data is available for reading.
         */
        sock_attr_canread = 1,

        /**
         * Data is available for writing.
         */
        sock_attr_canwrite = 2,

        /**
         * An exception, such as an error or out-of-band data.
         */
        sock_attr_exception = 4,

        /**
         * Connect has completed.
         */
        sock_attr_isconnected = 8,

#if 0
        // sock_attr_isclosed not supported for this release of the
        // Essential Networking Module.

        /**
         * The socket has been closed.
         */
        sock_atter_isclosed = 16,
#endif

        /**
         * A new connection is ready to be accepted.
         */
        sock_attr_canaccept = 32,

        /**
         * Any Attribute
         */
        sock_attr_any = ~0

    };

    /**
     * Inverts the value of the attribute \a rhs using a bitwise not
     * operation, and returns the result.
     */
    friend Attribute operator~(Attribute rhs)
    {
        return static_cast<Attribute>(~static_cast<int>(rhs));
    }

    /**
     * Combines the attribute \a lhs with \a rhs using a bitwise or
     * operation, and returns the result.
     */
    friend Attribute operator|(Attribute lhs, Attribute rhs)
    {
        return static_cast<Attribute>(static_cast<int>(lhs) | rhs);
    }

    /**
     * Combines the attribute \a lhs with \a rhs using a bitwise or
     * operation, and returns the result.
     */
    friend Attribute operator&(Attribute lhs, Attribute rhs)
    {
        return static_cast<Attribute>(static_cast<int>(lhs) & rhs);
    }

    /**
     * Combines the attribute \a lhs with \a rhs using a bitwise exclusive
     * or operation, and returns the result.
     */
    friend Attribute operator^(Attribute lhs, Attribute rhs)
    {
        return static_cast<Attribute>(static_cast<int>(lhs) ^ rhs);
    }

    /**
     * Combines the attribute \a lhs with \a rhs using a bitwise or
     * operation, stores the result into \a lhs, and returns the result.
     */
    friend Attribute& operator|=(Attribute& lhs, Attribute rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    /**
     * Combines the attribute \a lhs with \a rhs using a bitwise and
     * operation, stores the result into \a lhs, and returns the result.
     */
    friend Attribute& operator&=(Attribute& lhs, Attribute rhs)
    {
        lhs = lhs & rhs;
        return lhs;
    }

    /**
     * Combines the attribute \a lhs with \a rhs using a bitwise exclusive
     * or operation, stores the result into \a lhs, and returns the result.
     */
    friend Attribute& operator^=(Attribute& lhs, Attribute rhs)
    {
        lhs = lhs ^ rhs;
        return lhs;
    }

    /**
     * Constructs a null attribute on the undefined socket.
     */
    RWTSocketAttribute();

    /**
     * Constructs an attribute for a particular socket.
     */
    RWTSocketAttribute(const Socket& socket, Attribute attribute = sock_attr_nil);

    /**
     * Copy constructor.
     */
    RWTSocketAttribute(const RWTSocketAttribute& rhs);

    /**
     * Destructor.
     */
    ~RWTSocketAttribute(void);

    /**
     * Assignment operator.
     */
    RWTSocketAttribute&
    operator=(const RWTSocketAttribute& rhs);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWTSocketAttribute::getSocket() instead")
    Socket socket() const;
#endif

    /**
     * The socket with which the attribute is associated.
     */
    Socket getSocket() const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWTSocketAttribute::getAttribute() instead")
    Attribute attribute() const;
#endif

    /**
     * The attribute with which \c this is associated. The attribute may be
     * a set of several #Attribute values \c ORed together.
     */
    Attribute getAttribute() const;

private:
    Socket     socket_;
    Attribute  attribute_;
};

/**
 * \relates RWTSocketAttribute
 *
 * Returns \c true if \a x and \a y refer to the same attribute(s) on the
 * same socket. Requires that \c Socket provide an equality operator.
 */
template <class Socket>
inline bool
operator==(const RWTSocketAttribute<Socket>& x, const RWTSocketAttribute<Socket>& y)
{
    return x.getSocket() == y.getSocket() && x.getAttribute() == y.getAttribute();
}

#if defined(_AIX)

template <class Socket>
inline bool
operator<(const RWTSocketAttribute<Socket>&, const RWTSocketAttribute<Socket>&)
{
    RWTHROW(RWInternalErr("RWTSocketAttribute<Socket>::operator< should not have been used explicitly."));
    return false;
}

#endif

template <class Socket>
inline
RWTSocketAttribute<Socket>::RWTSocketAttribute()
    : socket_()
    , attribute_(sock_attr_nil)
{
}

template <class Socket>
inline
RWTSocketAttribute<Socket>::RWTSocketAttribute(const Socket& s, Attribute a)
    : socket_(s)
    , attribute_(a)
{
}

template <class Socket>
inline
RWTSocketAttribute<Socket>::RWTSocketAttribute(const RWTSocketAttribute& rhs)
    : socket_(rhs.socket_)
    , attribute_(rhs.attribute_)
{
}

template <class Socket>
inline
RWTSocketAttribute<Socket>::~RWTSocketAttribute(void)
{
}

template <class Socket>
inline RWTSocketAttribute<Socket>&
RWTSocketAttribute<Socket>::operator=(const RWTSocketAttribute<Socket>& rhs)
{
    if (&rhs != this) {
        socket_ = rhs.socket_;
        attribute_ = rhs.attribute_;
    }

    return *this;
}

template <class Socket>
inline Socket
RWTSocketAttribute<Socket>::getSocket() const
{
    return socket_;
}

template <class Socket>
inline typename RWTSocketAttribute<Socket>::Attribute
RWTSocketAttribute<Socket>::getAttribute() const
{
    return attribute_;
}

#if !defined(RW_DISABLE_DEPRECATED)

template <class Socket>
inline Socket
RWTSocketAttribute<Socket>::socket() const
{
    return getSocket();
}

template <class Socket>
inline typename RWTSocketAttribute<Socket>::Attribute
RWTSocketAttribute<Socket>::attribute() const
{
    return getAttribute();
}

#endif

#endif   // __rw_network_RWTSocketAttribute_h__ 
