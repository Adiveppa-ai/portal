#ifndef rw_xmlabstractions_RWXmlNamespace_h_
#define rw_xmlabstractions_RWXmlNamespace_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlNamespace.h#1 $
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
 ********************************************************************/

#include <rw/xmlabstractions/pkgdefs.h>      // everyone needs this
#include <rw/cstring.h>              // we hold two strings

/****************************************************************************
 * Class RWXmlNamespace encapsulates the XML namespace specification. As an
 * implementation detail, this is a pair of strings:
 *  the "prefix" used to explicitly scope names,
 *  the "URI" by which one namespace is distinguished from another
 *
 * RWXmlNamespace uses the URI portion of itself for all comparison purposes,
 * as described in REC-xml-names-19990114.
 *
 ****************************************************************************/
class RW_XMLABSTRACTIONS_SYMBOLIC RWXmlNamespace
{
public:
    /**
     * default constructor is fine: both URI and prefix are empty
     */
    RWXmlNamespace();

    /**
     * the namespace is created with the specified values
     */
    RWXmlNamespace(const RWCString& prefix, const RWCString& URI);

    /**
     * copy constructor is public, acts as expected
     */
    RWXmlNamespace(const RWXmlNamespace&);

    /**
     * Non- virtual destructor. Who could ever need a derive Xml Namespace?
     */
    ~RWXmlNamespace();

    /**
     * assignment acts as expected
     */
    inline RWXmlNamespace& operator=(const RWXmlNamespace&);

    /**
     * it is perfectly legal to change the prefix
     */
    inline void                setPrefix(const RWCString& pfx)
    {
        this->prefix_ = pfx;
    }

    /**
     * it is odd to change the URI, but makes sense if the namespace was
     * default constructed, or copied prior to the change.
     */
    inline void                setURI(const RWCString& uri)
    {
        this->URI_ = uri;
    }

    /**
     * You may examine the prefix
     */
    inline const RWCString&    getPrefix() const
    {
        return this->prefix_;
    }

    /**
     * You may examine the URI
     */
    const RWCString&           getURI() const
    {
        return this->URI_;
    }

    /**
     * Returns getURI().compare(other.getURI())
     */
    inline int                 compareTo(const RWXmlNamespace& other) const;

    /**
     * Convenience function for debugging or logging
     */
    inline RWCString           infoString() const;

public: // static 'constant' namespace information
    /**
     * http://www.w3.org/TR/REC-xml-names/ Section 4 "Namespace Constraint:
     * Prefix Declared" says this: The prefix xmlns is used only for
     * namespace bindings and is not itself bound to any namespace name. For
     * our purposes, we will provide "xmlns" --> ""
     */
    static const RWXmlNamespace&    getXmlns();     // "xmlns", ""
    static bool                     matchXmlns(const RWXmlNamespace& ns);

    /**
     * Per the XML Schemas document, part 1 "xsi" -->
     * "http://www.w3.org/2001/XMLSchema-instance"
     */
    static RWXmlNamespace&          getXsi();
    static bool                     matchXsi(const RWXmlNamespace& ns);

    /**
     * Per the XML Schemas document, part 2 "xsd" -->
     * "http://www.w3.org/2001/XMLSchema"
     */
    static RWXmlNamespace&          getXsd();
    static bool                     matchXsd(const RWXmlNamespace& ns);

    /**
     * "Empty" is often very useful
     */
    static const RWXmlNamespace&    getEmptyNamespace();

private: // data
    RWCString                  prefix_;
    RWCString                  URI_;
}; // class RWXmlNamespace

// global equality operators
/**
 * Equality is based entirely on the URI. The prefix is a meaningless token
 * according to the XML specification
 */
inline bool    operator==(const RWXmlNamespace& lhs, const RWXmlNamespace& rhs)
{
    return lhs.getURI() == rhs.getURI();
}

/**
 * Inequality is based entirely on the URI. The prefix is a meaningless
 * token according to the XML specification
 */
inline bool    operator!=(const RWXmlNamespace& lhs, const RWXmlNamespace& rhs)
{
    return lhs.getURI() != rhs.getURI();
}

/**
 * Provide operator < for stl
 */
inline bool    operator<(const RWXmlNamespace& lhs, const RWXmlNamespace& rhs)
{
    return lhs.getURI() < rhs.getURI();
}

// inline implementations

inline RWXmlNamespace&
RWXmlNamespace::operator=(const RWXmlNamespace& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    setPrefix(rhs.getPrefix());
    setURI(rhs.getURI());
    return *this;
}

inline int
RWXmlNamespace::compareTo(const RWXmlNamespace& other) const
{
    return URI_.compareTo(other.getURI());
}

inline RWCString
RWXmlNamespace::infoString() const
{
    RWSize_T len(prefix_.length() + URI_.length() + 7);
    RWCString info(len);
    info.append("\"");
    info.append(prefix_);
    info.append("\"-->\"");
    info.append(URI_).append("\"");
    return info;
}

#endif // rw_xmlabstractions_RWXmlNamespace_h_
