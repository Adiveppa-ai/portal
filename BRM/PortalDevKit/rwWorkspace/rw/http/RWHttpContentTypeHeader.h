#ifndef __rw_http_RWHttpContentTypeHeader_h__
#define __rw_http_RWHttpContentTypeHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpContentTypeHeader.h#1 $
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

#include <rw/http/RWHttpHeaderBase.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines an HTTP Content-Type header.
 *
 * RWHttpContentTypeHeader is a specialization class of RWHttpHeaderBase. It
 * is a helper class that formats its contents as \c Content-Type:
 * \c header_value, where \c header_value is the media type and sub type of
 * the message, as well as any parameters describing the content.
 *
 * \example
 * \code
 * RWHttpContentTypeHeader hdr("text", "plain");
 * hdr.addParameter("charset", "iso-2022-jp");
 * \endcode
 * \endexample
 */
class RW_HTTP_GLOBAL RWHttpContentTypeHeader : public RWHttpHeaderBase
{

public:

    /**
     * Constructs a default RWHttpContentTypeHeader object with the label
     * \c Content-Type and the value \c text/plain.
     */
    RWHttpContentTypeHeader(void);

    /**
     * Constructs an RWHttpContentTypeHeader with the label \c Content-Type
     * and the value \a mediaType / \a subType.
     */
    RWHttpContentTypeHeader(const RWCString& mediaType, const RWCString& subType);

    /**
     * Constructs an RWHttpContentTypeHeader object from an
     * RWHttpGenericHeader that represents a \c Content-Type header. If the
     * RWHttpGenericHeader does not represent a \c Content-Type header or if
     * the value of the RWHttpGenericHeader does not conform to the
     * formatting of a \c Content-Type value, an RWHttpHeaderParseError
     * exception is thrown.
     */
    RWHttpContentTypeHeader(const RWHttpGenericHeader& hdr);

    /**
     * Sets the \a mediaType and \a subType of this instance.
     */
    void
    setContentType(const RWCString& mediaType, const RWCString& subType);

    /**
     * Returns the media type of this instance.
     */
    RWCString
    getMediaType(void) const;

    /**
     * Returns the sub type of this instance.
     */
    RWCString
    getSubType(void) const;

    /**
     * Returns the value of this header as an RWCString. This includes the
     * media and sub types, as well as any parameters associated with the
     * header, formatted according the HTTP specification's requirements.
     */
    RWCString
    getValue(void) const;

    /**
     * Add a parameter to this header. If the parameter is not currently
     * associated with this instance, the parameter will be added, and
     * \c true will be returned, \c false otherwise.
     */
    bool
    addParameter(const RWCString& name, const RWCString& value);

    /**
     * Removes the parameter associated with name from the parameter list.
     * If the parameter is not present, \c false is returned.
     */
    bool
    removeParameter(const RWCString& name);

    /**
     * Returns the value associated with a parameter associated with this
     * instance. If the name does not match a parameter in the list, an
     * empty string is returned.
     */
    RWCString
    getParameterValue(const RWCString& name) const;

    /**
     * Returns a list of parameter names associated with this instance. The
     * values associated with these parameter names can be retrieved with
     * the getParameterValue() method.
     */
    RWTValSlist<RWCString>
    getParameterNames(void) const;


    // This structure is used internally to represent
    // a key:value pair.  It is not intended for
    // external use.
    struct ParameterPair {
        RWCString name;
        RWCString value;
    };

private:

    RWCString                   mediaType_;
    RWCString                   subType_;
    RWTValSlist<ParameterPair>  parameters_;
};

inline
RWHttpContentTypeHeader::RWHttpContentTypeHeader(void)
    : RWHttpHeaderBase("Content-Type", RW_HTTP_ENTITY_HEADER),
      mediaType_("text"),
      subType_("plain")
{
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpContentTypeHeader_h__
