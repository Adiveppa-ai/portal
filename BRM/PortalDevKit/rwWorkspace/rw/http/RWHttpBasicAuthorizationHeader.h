#ifndef __rw_http_RWHttpBasicAuthorizationHeader_h__
#define __rw_http_RWHttpBasicAuthorizationHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpBasicAuthorizationHeader.h#1 $
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

#include <rw/http/RWHttpAuthorizationHeaderBase.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines an Authorization header for Basic Access
 * Authentication.
 *
 * RWHttpBasicAuthorizationHeader is a specialization class of
 * RWHttpAuthorizationHeaderBase. It is a helper class that formats and
 * encodes its contents as \c Authorization: \c basic \c header_value, where
 * \c header_value is the username and password used for basic
 * authentication.
 */
class RW_HTTP_GLOBAL RWHttpBasicAuthorizationHeader
    : public RWHttpAuthorizationHeaderBase
{
public:

    /**
     * Constructs a default RWHttpBasicAuthorizationHeader object with the
     * label \c Authorization and the username and password set to empty
     * strings.
     */
    RWHttpBasicAuthorizationHeader();

    /**
     * Constructs a RWHttpBasicAuthorizationHeader object with the label
     * \c Authorization, a username of \a username, and a password of
     * \a password.
     */
    RWHttpBasicAuthorizationHeader(const RWCString& username,
                                   const RWCString& password,
                                   bool        padding = false);

    /**
     * Constructs an RWHttpBasicAuthorizationHeader object from an
     * RWHttpGenericHeader representing a basic Authorization HTTP header.
     * If the RWHttpGenericHeader does not represent a basic Authorization
     * HTTP header or if the value of the RWHttpGenericHeader does not
     * conform to the formatting of a basic Authorization value, an
     * RWHttpHeaderParseError exception is thrown.
     */
    RWHttpBasicAuthorizationHeader(const RWHttpGenericHeader& hdr);

    /**
     * Assigns \a username to the internal username.
     */
    void
    setUsername(const RWCString& username);

    /**
     * Assigns \a password to the internal password.
     */
    void
    setPassword(const RWCString& password);

    /**
     * Returns the internal value of username as a RWCString.
     */
    RWCString
    getUsername() const;
    // returns the internal username

    /**
     * Returns the internal value of password as a RWCString.
     */
    RWCString
    getPassword() const;

    void
    setPadding(bool);
    // sets the padding behavior

    bool
    getPadding() const;
    // retrieves the padding setting

    /**
     * Returns a RWCString consisting of the word \c Basic followed by a
     * base64 encoded string representing \c username:password.
     */
    virtual RWCString
    getValue() const;

protected:

    /**
     * Returns a RWCString representing the base64 encoded version of
     * \a str. The RWCString should contain 7-bit US-ASCII data.
     */
    static RWCString
    encodeString(const RWCString& str, bool padding) ;
    // encodes a string using BASE64 encoding as specified in RFC 2045 [6.8]

    /**
     * Returns a RWCString representing the plain text version of the base64
     * encoded string \a str. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    static RWCString
    decodeString(const RWCString& str) ;
    // decodes a string using BASE64 encoding as specified in RFC 2045 [6.8]

private:

    RWCString username_;
    RWCString password_;

    bool padding_;
};

inline
RWHttpBasicAuthorizationHeader::RWHttpBasicAuthorizationHeader()
    : padding_(false)
{
}

inline
RWHttpBasicAuthorizationHeader::RWHttpBasicAuthorizationHeader(
    const RWCString& username,
    const RWCString& password,
    bool padding)
    : username_(username),
      password_(password),
      padding_(padding)
{
}

inline void
RWHttpBasicAuthorizationHeader::setUsername(const RWCString& username)
{
    username_ = username;
}

inline void
RWHttpBasicAuthorizationHeader::setPassword(const RWCString& password)
{
    password_ = password;
}

inline RWCString
RWHttpBasicAuthorizationHeader::getUsername(void) const
{
    return username_;
}

inline RWCString
RWHttpBasicAuthorizationHeader::getPassword(void) const
{
    return password_;
}



inline void
RWHttpBasicAuthorizationHeader::setPadding(bool padding)
{
    padding_ = padding;
}

inline bool
RWHttpBasicAuthorizationHeader::getPadding(void) const
{
    return padding_;
}



#endif // __rw_http_RWHttpBasicAuthorizationHeader_h__
