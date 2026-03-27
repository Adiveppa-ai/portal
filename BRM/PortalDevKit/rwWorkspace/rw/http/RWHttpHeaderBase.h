#ifndef __rw_http_RWHttpHeaderBase_h__
#define __rw_http_RWHttpHeaderBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpHeaderBase.h#1 $
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

#include <rw/http/pkgdefs.h>
#include <rw/cstring.h>

/**
 * \ingroup http_package
 *
 * \headerfileloc{#include <rw/http/RWHttpHeaderBase.h>}
 *
 * Specifies the type of header. You can use this enumerator for ordering
 * the headers when you send them.
 */
enum RWHttpHeaderType {

    /**
     * Header type for headers are not specific to requests or responses,
     * and do not apply to the message body.
     */
    RW_HTTP_GENERAL_HEADER = 0,

    /**
     * Header type that is associated with HTTP requests. Request headers
     * allow the client to pass additional information about the request,
     * and about the client itself, to the server.
     */
    RW_HTTP_REQUEST_HEADER = 1,

    /**
     * Header type that is associated with HTTP responses. Response headers
     * allow the server to pass additional information about the response
     * which cannot be placed in the reply status line.
     */
    RW_HTTP_RESPONSE_HEADER = 2,

    /**
     * Entity headers define information about the resource identified by a
     * request.
     */
    RW_HTTP_ENTITY_HEADER = 3
};

/**
 * \ingroup http_package
 *
 * \brief
 * Abstract base class from which all HTTP header classes derive.
 *
 * RWHttpHeaderBase is an abstract base class for all concrete header
 * classes. These classes are helpers that ease header attachment and
 * formatting to various HTTP requests.
 */
class RW_HTTP_GLOBAL RWHttpHeaderBase
{

protected:

    /**
     * Constructs a default RWHttpHeaderBase as part of a specific HTTP
     * header object. The label of the header is set to an empty string, and
     * the header type is set to #RW_HTTP_ENTITY_HEADER.
     */
    RWHttpHeaderBase(void);

    /**
     * Constructs an RWHttpHeaderBase as part of a specific HTTP header
     * object. The label of the header is set to \a label, and the header
     * type is set to \a type. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWHttpHeaderBase(const RWCString& label,
                     RWHttpHeaderType type = RW_HTTP_ENTITY_HEADER);

    virtual ~RWHttpHeaderBase();

public:

    /**
     * Returns \c true if \a h is equal to self.
     */
    bool
    operator==(const RWHttpHeaderBase& h) const;

    /**
     * Returns \c true if the RWHttpHeaderBase%s are not equivalent.
     */
    bool
    operator!=(const RWHttpHeaderBase&) const;

    /**
     * Returns \c true if \a hdr is less than self. Otherwise returns
     * \c false.
     */
    bool
    operator<(const RWHttpHeaderBase& hdr) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWHttpHeaderBase::getLabel() instead")
    RWCString
    label(void) const;
#endif

    /**
     * Returns the internal label of the header. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getLabel(void) const;

    /**
     * Concatenates the label and the value of the header into the format
     * \c label: \c value and returns the result as an RWCString. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    virtual RWCString
    asString(void) const;

    /**
     * Attempts to append \a str to the header as a new set of values, if
     * the header supports appending of headers. Append returns \c true if
     * it is successful in appending the headers. Otherwise it returns
     * \c false. This function also returns \c false if it is not overridden
     * in a derived class. The RWCString should contain 7-bit US-ASCII data.
     */
    virtual bool
    append(const RWCString& str);

#if !defined(RW_DISABLE_DEPRECATED) && !defined(DOXYGEN)
    RW_DEPRECATE_FUNC("Use RWHttpHeaderBase::getValue() instead")
    virtual RWCString
    value(void) const;

    virtual RWCString
    getValue(void) const;
#else
    /**
     * Returns the value associated with the label of the header. This is a
     * pure virtual function, so it must be overridden by a derived class.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    virtual RWCString
    getValue(void) const = 0;
#endif

    /**
     * Returns the internal type of the header.
     */
    RWHttpHeaderType
    getType() const;

    /**
     * Returns the hash value of \a h.
     */
    static unsigned
    hash(const RWHttpHeaderBase&);

protected:

    RWCString   label_;
    RWHttpHeaderType   type_;
};

inline
RWHttpHeaderBase::RWHttpHeaderBase(void)
    : label_(), type_(RW_HTTP_ENTITY_HEADER)
{
}

inline
RWHttpHeaderBase::RWHttpHeaderBase(const RWCString& s,
                                   RWHttpHeaderType type)
    : label_(s), type_(type)
{
}

inline RWCString
RWHttpHeaderBase::getValue(void) const
{
    return RWCString();
}

inline bool
RWHttpHeaderBase::operator==(const RWHttpHeaderBase& h) const
{
    return label_.compareTo(h.label_, RWCString::ignoreCase) == 0;
}

inline bool
RWHttpHeaderBase::operator!=(const RWHttpHeaderBase& h) const
{
    return label_.compareTo(h.label_, RWCString::ignoreCase) != 0;
}

inline RWCString
RWHttpHeaderBase::getLabel(void) const
{
    return label_;
}

inline RWHttpHeaderType
RWHttpHeaderBase::getType(void) const
{
    return type_;
}

inline unsigned
RWHttpHeaderBase::hash(const RWHttpHeaderBase& h)
{
    return unsigned(h.label_.hash());
}

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWHttpHeaderBase::label(void) const
{
    return getLabel();
}

#  if !defined(DOXYGEN)
inline RWCString
RWHttpHeaderBase::value(void) const
{
    return getValue();
}
#  endif

typedef RW_DEPRECATE_TYPE("Use RWHttpHeaderBase instead") RWHttpHeaderBase RWIHttpHeaderBase;
#endif

#endif // __rw_http_RWHttpHeaderBase_h__
