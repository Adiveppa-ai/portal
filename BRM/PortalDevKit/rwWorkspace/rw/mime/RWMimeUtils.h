#ifndef rw_mime_RWMimeUtils_h
#define rw_mime_RWMimeUtils_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeUtils.h#1 $
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

#include <rw/mime/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tvslist.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Provides utility functions commonly needed by MIME applications.
 *
 * RWMimeUtils provides utility functions commonly needed by MIME
 * applications. There is no need to instantiate this class, since it
 * contains only static functions and static constants.
 */
class RW_MIME_GLOBAL RWMimeUtils
{
public:

    /**
     * Static constant string containing \c "quoted-printable", for use with
     * encode() and decode().
     */
    static const RWCString QuotedPrintable;

    /**
     * Static constant string containing \c "base64", for use with encode()
     * and decode().
     */
    static const RWCString Base64;

    /**
     * Static constant string containing \c "7bit", for use with encode()
     * and decode().
     */
    static const RWCString SevenBit;

    /**
     * Static constant string containing \c "8bit", for use with encode()
     * and decode().
     */
    static const RWCString EightBit;

    /**
     * Static constant string containing \c "binary", for use with encode()
     * and decode().
     */
    static const RWCString Binary;

    /**
     * Encodes the string \a str according to the encoding method
     * \a encoding. Throws RWMimeError if \a encoding is not recognized. See
     * the <em>Internet Protocols Module User's Guide</em> for a discussion
     * of encodings. The RWCString should contain 7-bit US-ASCII data.
     */
    static RWCString
    encode(const RWCString& str, const RWCString& encoding);

    /**
     * Decodes the string \a str according to the encoding method
     * \a encoding. Throws RWMimeError if \a encoding is not recognized. See
     * the <em>Internet Protocols Module User's Guide</em> for a discussion
     * of encodings. The RWCString should contain 7-bit US-ASCII data.
     */
    static RWCString
    decode(const RWCString& str, const RWCString& encoding);

    /**
     * Encodes the string \a str according to the encoding method
     * \a encoding for use as a value in a MIME header. Throws RWMimeError
     * if \a encoding is not recognized. Currently, the recognized encodings
     * are \c "B" and \c "Q" as specified in RFC 2047.
     */
    static RWCString
    headerEncode(const RWCString& str, const RWCString& charset, const RWCString& encoding);

    /**
     * Decodes the header value string \a str. If \a str is not a string
     * encoded for use in an header, this function returns the original
     * string, and the \a charset variable is set to US-ASCII. If the string
     * is encoded, the unencoded string is returned, with the \a charset
     * variable set to the \a charset of the returned string.
     */
    static RWCString
    headerDecode(const RWCString& str, RWCString& charset);

    /**
     * Generates a unique string for use as the value of a boundary
     * parameter. The generated string is of the form
     *
     * \code
     * _=_next_part_<milliseconds>_=_
     * \endcode
     *
     * where \c \<milliseconds\> is the number of milliseconds since
     * 00:00:00:000 January 1, 1901 UTC. The RWCString should contain 7-bit
     * US-ASCII data.
     *
     * \note
     * This function generates unique boundaries suitable for most messages
     * and many applications. However, the function generates duplicate
     * values if called more than once a millisecond.
     */
    static RWCString
    getUniqueBoundary(void);

    /**
     * Translates the format of the text in \a str by replacing all
     * occurrences of \c '\\r', \c '\\n' and \c "\r\n" in \a str with
     * \a delim. By default, the function translates \a str to canonical
     * form for text. Providing a different value for \a delim converts
     * \a str to a platform-specific text format. An application sending a
     * message typically converts a text part body to canonical form before
     * encoding the text or inserting the text into a message. An
     * application receiving a message typically converts a text part body
     * to a platform-specific format after retrieving the body from the
     * message and decoding the body. See RFC 2049, section 4 or the
     * <em>Internet Protocols Module User's Guide</em> for a discussion of
     * canonical form.
     *
     * \note
     * Do not use this function on unencoded binary data.
     */
    static RWCString
    replaceLineDelimiter(const RWCString& str, const RWCString& delim = "\r\n");

    /*
     * @internal
     * Returns the position of the given delimiter character within
     * the given string, or #RW_NPOS if the delimiter does not appear
     * within the string.  Understands quoting, escaping, and commenting
     * rules, as described in RFC 2822 with regard to structured header
     * values.
     */
    static size_t
    findDelimiter(const RWCString& str, char delim);

    /*
     * @internal
     * Strips leading and trailing whitespace, strips comments, and unfolds.
     * Optionally unescapes the escaped characters contained within double-
     * quotes, and strips the double-quote characters.
     *
     * See RFC 2822 for more information regarding comments, header folding,
     * escaping, and quoting.
     */
    static RWCString
    cleanToken(const RWCString& str, bool stripQuotes = true);

    /*
     * @internal
     * "Unfolds" by removing all CRLF sequences followed by whitespace.
     * Trims away leading and trailing whitespace.
     */
    static RWCString
    unfoldAndTrim(const RWCString& str);

    /*
     * @internal
     * Surrounds the given string with double-quote characters.  Escapes
     * double-quote and backslash characters by preceding each of them
     * with a backslash.  Useful in preparing a parameter value for
     * inclusion in a MIME message.
     */
    static RWCString
    quoteAndEscape(const RWCString& str);

    /*
     * @internal
     * Folds the given line in accordance with RFC 2822.  Useful in
     * preparing a header string for inclusion in a MIME message.
     */
    static RWCString
    fold(const RWCString& str);

    /*
     * @internal
     * Returns true if \a str meets the requirements of a token, as
     * defined by RFC 2045.
     */
    static bool
    isToken(const RWCString& str);

    /*
     * @internal
     * Encodes string using the base64 encoding described in
     * RFC 2045.
     */
    static RWCString
    encodeBase64(const RWCString& str);

    /*
     * @internal
     * Decodes string using the base64 encoding described in
     * RFC 2045.
     */
    static RWCString
    decodeBase64(const RWCString& str);

    /*
     * @internal
     * Encodes string using the quoted-printable encoding
     * described in RFC 2045.
     */
    static RWCString
    encodeQuotedPrintable(const RWCString& str);

    /*
     * @internal
     * Decodes string using the quoted-printable encoding
     * described in RFC 2045.
     */
    static RWCString
    decodeQuotedPrintable(const RWCString& str,
                          bool trimTrailingWS = true);

    /*
     * @internal
     * Encodes a string according to the "B" encoding
     * described in RFC 2047 for encoded headers.
     *
     */
    static RWCString
    headerEncodeB(const RWCString& str, size_t maxEncodedLength, size_t& length);

    /*
     * @internal
     * Encodes a string according to the "Q" encoding
     * described in RFC 2047 for encoded headers.
     */
    static RWCString
    headerEncodeQ(const RWCString& str, size_t maxEncodedLength, size_t& length);

    /*
     * @internal
     * Decodes a string according to the "Q" encoding
     * described in RFC 2047 for encoded headers.
     */
    static RWCString
    headerDecodeQ(const RWCString& str);

    /*
     * Given an RWCString representing a header value,
     * returns a list of tokens separating normal US-ASCII
     * strings from encoded words.
     *
     * If the string to be analyzed is from a structured header
     * which contains comments, the structured value should be
     * set to true.
     */
    static RWTValSlist<RWCString>
    tokenizeHeader(const RWCString& str, bool structured = false);
};


#endif // rw_mime_RWMimeUtils_h
