#ifndef __rw_internet_RWURL_h__
#define __rw_internet_RWURL_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWURL.h#1 $
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

#include <rw/internet/pkgdefs.h>
#include <rw/cstring.h>
#include <iosfwd>

/*
 * RWURL
 *
 * RWURL is a convenience class that encapsulates parsing and component
 * management of URL information.
 *
 * URL's are assumed to be in RFC 1738 format:
 *   <scheme>:<scheme data>
 *
 * RWURL has knowledge of some URL schemes implicitly, specifically URL's
 * supported by the SourcePro Net - Internet Protocols Module as well as
 * some other common URL schemes. Specific URL schemes known to the class
 * include: FTP, HTTP, MAILTO, NEWS, NNTP, and FILE.
 *
 * URL schemes not known to RWURL will return false from the isKnown()
 * method. URL schemes that are known but have basic syntactical errors
 * will return false from the isValid() method.
 *
 */

/**
 * \ingroup internet_basics_package
 *
 * \brief
 * A convenience class that encapsulates parsing and component management of
 * URL information.
 *
 * RWURL is a convenience class that encapsulates parsing and component
 * management of URL information. URLs are assumed to be in RFC1738 format:
 *
 * \code
 * <scheme>:<scheme data>
 * \endcode
 *
 * RWURL has implicit knowledge of common URL schemes, that include \c HTTP,
 * \c FTP, \c MAILTO, \c NEWS, \c NNTP, and \c FILE. URL schemes not known
 * to RWURL return \c false from the isKnown() method. URL schemes that are
 * known but have basic syntactical errors return \c false from the
 * isValid() method.
 *
 * You must properly encode any unsafe characters in the URL. See RFC1738 or
 * subsequent documents for proper encoding methods and syntactical
 * questions.
 *
 * \example
 * \code
 * #include <rw/rstream.h>
 * #include <rw/network/RWWinSockInfo.h>
 * #include <rw/internet/RWURL.h>
 *
 * int
 * main()
 * {
 *     RWWinSockInfo info;
 *     RWURL url("http://www.roguewave.com/tools.txt");
 *
 *     cout << url.getScheme() << endl;
 *     cout << url.getHost() << endl;
 *     cout << url.getPath() << endl;
 *     return 0;
 * }
 * \endcode
 *
 * Program Output
 *
 * \code
 * http
 * www.roguewave.com
 * tools.txt
 * \endcode
 * \endexample
 */
class RW_INTERNET_SYMBOLIC RWURL
{

public:

    /**
     * Constructs a default empty RWURL object. \c Self needs to be
     * initialized using the assignment operator.
     */
    RWURL(void);

    /**
     * Constructs an RWURL from a \c const RWCString reference. The URL is
     * expected to be in RFC1738 form.
     */
    RWURL(const RWCString& urlString);

    /**
     * Returns \c true if self and the input \a url represent the same URL.
     */
    bool
    operator==(const RWURL& url) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getScheme() instead")
    RWCString scheme(void) const;
#endif
    /**
     * Returns the scheme portion of the URL. In the example URL
     * \c "http://www.roguewave.com", it returns \c "http". The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWCString getScheme(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getData() instead")
    RWCString data(void) const;
#endif
    /**
     * Returns the whole URL string used to construct the RWURL object. This
     * method is useful if the isKnown() method returns \c false, indicating
     * it is an unknown URL type. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString getData(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getHost() instead")
    RWCString host(void) const;
#endif
    /**
     * Returns the host portion of the URL, if applicable. In the example
     * URL \c "ftp://ftp.roguewave.com", the method returns
     * \c "ftp.roguewave.com". URLs that do not contain host information,
     * such as \c "mailto:me@roguewave.com", return an empty string. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getHost(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getPath() instead")
    RWCString path(void) const;
#endif
    /**
     * Returns the path portion of the URL, if applicable. In the example
     * URL \c "ftp://ftp.roguewave.com/pub", it returns \c "pub". The single
     * slash (\c /) before \c "pub" in the example is \e not part of the
     * path information. If a leading slash is required for the path
     * information, consult RFC1738 or subsequent documents about proper
     * unsafe character encoding techniques. URLs that do not contain path
     * information, such as \c "mailto:me@roguewave.com", return an empty
     * string. The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getPath(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getPort() instead")
    RWCString port(void) const;
#endif
    /**
     * Returns the port portion of the URL, if applicable. In the example
     * URL \c "ftp://ftp.roguewave.com:21/pub", it returns \c "21". URLs
     * that do not contain explicit port information return an empty string.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getPort(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getUser() instead")
    RWCString user(void) const;
#endif
    /**
     * Returns the user portion of the URL, if applicable. In the example
     * URL \c "ftp://fred:pluto@ftp.roguewave.com:21/pub", it returns
     * \c "fred". URLs that do not contain explicit \c user information
     * return an empty string. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWCString getUser(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getPassword() instead")
    RWCString password(void) const;
#endif
    /**
     * Returns the password portion of the URL, if applicable. In the
     * example URL \c "ftp://fred:pluto@ftp.roguewave.com:21/pub", it
     * returns \c "pluto". URLs that contain no explicit password
     * information return an empty string. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString getPassword(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getMailAddress() instead")
    RWCString mailAddress(void) const;
#endif
    /**
     * Returns the email address portion of the URL, if applicable. In the
     * example URL \c "mailto:me@roguewave.com", the method returns
     * \c "me@roguewave.com". URLs that do not contain email information
     * return an empty string. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWCString getMailAddress(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getNewsGroup() instead")
    RWCString newsGroup(void) const;
#endif
    /**
     * Returns the specified newsgroup portion of the URL, if applicable. In
     * the example URL \c "news:comp.windows", it returns \c "comp.windows".
     * URLs that contain no explicit newsgroup information return an empty
     * string. The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getNewsGroup(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getNewsArticle() instead")
    RWCString newsArticle(void) const;
#endif
    /**
     * Returns the news article portion of the URL, if applicable. In the
     * example URL \c "nntp://comp.windows/4u7lb0$t5s@roguewave.com", it
     * returns \c "4u7lb0$t5s@roguewave.com". URLs that do not contain
     * explicit news article information return an empty string. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getNewsArticle(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getType() instead")
    RWCString type(void) const;
#endif
    /**
     * Returns the transfer type portion of the URL, if applicable. In the
     * example URL \c "ftp://www.roguewave.com/doc.txt;type=a", it returns
     * \c "a". URLs that do not contain explicit type information return an
     * empty string. The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString getType(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getSearch() instead")
    RWCString search(void) const;
#endif
    /**
     * Returns the search string portion of the URL, if applicable. In the
     * example URL \c "http://www.roguewave.com/pub?archive=mswin95", it
     * returns \c "archive=mswin95". URLs that do not contain explicit
     * search information return an empty string. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString getSearch(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWURL::getError() instead")
    RWCString error(void) const;
#endif
    /**
     * Returns a textual explanation of a \c false response from either the
     * isValid() or the isKnown() method.
     */
    RWCString getError(void) const;

    /**
     * Returns \c false if the URL scheme is specifically a recognized
     * format, but a syntactical error exists during parsing. A call to the
     * \c data method returns the \c url string used during attempted
     * construction. A call to the \c error method returns a descriptive
     * text string describing why the input URL string could not be parsed
     * successfully. This method also returns \c false if the URL scheme is
     * not specifically known.
     */
    bool isValid(void) const;
    // Indicates that the URL type is known
    // however an error parsing was encountered.
    // A call to the data() method will return
    // the url string that was used during
    // attempted construction.  A call to the
    // error() method will return a descriptive
    // text string describing why the URL could
    // not be parsed.

    /**
     * Returns \c true for URL schemes specifically recognized by the class.
     */
    bool isKnown(void) const;
    // Indicates that the URL type is unknown
    // and no parsing was performed.  A call to the
    // data() method will return the url string that
    // was used during attempted construction.

private:

    /**
     * Outputs an RWURL object to an \c std::ostream.
     */
    friend RW_INTERNET_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWURL& url);

private:

    void      setInvalid(const RWCString& reason);
    // Sets the url to invalid

    void      setUnrecognized(const RWCString& reason);
    // Sets the url to unrecognized

    void      parse(const RWCString& localURL);
    void      parseHTTP(RWCString& localURL);
    void      parseFTP(RWCString& localURL);
    void      parseMailTo(RWCString& localURL);
    void      parseFile(RWCString& localURL);
    void      parseNNTP(RWCString& localURL);
    void      parseNews(RWCString& localURL);
    void      parseTelnet(RWCString& localURL);

    void      parseHost(RWCString& localURL, size_t pos);
    void      parseUserInfo(RWCString& where, size_t pos);

    void      clear(void);

    bool valid_;       // validity of url
    int       known_;       // whether the scheme is known

    RWCString host_;        // host name
    RWCString port_;        // host port
    RWCString path_;        // file path
    RWCString proto_;       // protocol to use
    RWCString user_;        // user name
    RWCString password_;    // users password
    RWCString search_;      // http search argument
    RWCString type_;        // ftp file transfer type
    RWCString mailAddress_; // mailto: mailAddress
    RWCString reason_;      // why url is invalid
    RWCString newsArticle_; // news article
    RWCString newsGroup_;   // news group
    RWCString data_;        // raw data
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWURL::scheme(void) const
{
    return getScheme();
}

inline RWCString
RWURL::data(void) const
{
    return getData();
}

inline RWCString
RWURL::host(void) const
{
    return getHost();
}

inline RWCString
RWURL::path(void) const
{
    return getPath();
}

inline RWCString
RWURL::port(void) const
{
    return getPort();
}

inline RWCString
RWURL::user(void) const
{
    return getUser();
}

inline RWCString
RWURL::password(void) const
{
    return getPassword();
}

inline RWCString
RWURL::mailAddress(void) const
{
    return getMailAddress();
}

inline RWCString
RWURL::newsGroup(void) const
{
    return getNewsGroup();
}

inline RWCString
RWURL::newsArticle(void) const
{
    return getNewsArticle();
}

inline RWCString
RWURL::type(void) const
{
    return getType();
}

inline RWCString
RWURL::search(void) const
{
    return getSearch();
}

inline RWCString
RWURL::error(void) const
{
    return getError();
}
#endif
#endif // __rw_internet_RWURL_h__
