#ifndef rw_xmlabstractions_RWXmlName_h_
#define rw_xmlabstractions_RWXmlName_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlName.h#1 $
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

#include <rw/xmlabstractions/RWXmlNamespace.h>  // we hold an RWXmlNamespace
#include <rw/xmlabstractions/pkgdefs.h>         // everybody needs this
#include <rw/cstring.h>                 // we hold a string

/****************************************************************************
 *
 * Class RWXmlName represents a name in an XML document.  Such a name lives
 * in a namespace so an RWXmlName contains a string for the name and an
 * RWXmlNamespace for the namespace.
 *
 ****************************************************************************/

class RW_XMLABSTRACTIONS_SYMBOLIC RWXmlName
{
public:
    /**
     * Default constructor. Not much use, really.
     */
    RWXmlName();

    /**
     * Constructor sets name, namespace is set to the empty namespace
     */
    RWXmlName(const RWCString& localName);

    /**
     * Constructor sets name and namespace
     */
    RWXmlName(const RWCString& localName, const RWXmlNamespace& ns);

    /**
     * Copy constructor has the usual semantics
     */
    RWXmlName(const RWXmlName&);

    /**
     * always good to have a place to hang some destruction, if needed
     */
    ~RWXmlName();

    /**
     * Assignment has copy semantics (not copy-on-write)
     */
    inline RWXmlName&            operator=(const RWXmlName& n);

    /**
     * Return the local name of this XML name
     */
    inline const RWCString&      getLocalName() const;

    /**
     * Save a new local name for this XML name
     */
    inline void                  setLocalName(const RWCString& localName);

    /**
     * Return getNamespace().qualifiedName(getLocalName())
     */
    RWCString                    getQualifiedName() const;

    /**
     * return getNamespace().uniqueName(getLocalName())
     */
    RWCString                    getUniqueName() const;

    /**
     * Get the namespace as an RWXmlNamespace
     */
    inline const RWXmlNamespace& getNamespace() const;

    inline RWXmlNamespace&       getNamespace();

    /**
     * Set the namespace with an RWXmlNamespace
     */
    inline void                  setNamespace(const RWXmlNamespace& ns);

    /**
     * You may find that you need to unset this particular element's
     * namespace.
     */
    inline void                  unsetNamespace();

    /**
     * synonym for getQualifiedName()
     */
    RWCString                    asString() const;

    /**
     * Compare self to another RWXmlName. If self is less, return int less
     * than 0, if self is greater, return int greater, and if equal, return 0.
     */
    int                          compareTo(const RWXmlName& other) const;
private:
    RWCString name_;
    RWXmlNamespace ns_;
}; // end of class declaration for RWXmlName

/**
 * operator == returns true if the names and namespace uris are both equal
 */
RW_XMLABSTRACTIONS_GLOBAL bool operator==(const RWXmlName&, const RWXmlName&);

/**
 * operator != returns true if == returns false.
 */
RW_XMLABSTRACTIONS_GLOBAL bool operator!=(const RWXmlName& lhs, const RWXmlName& rhs);

/**
 * operator < returns true if the l.name_ < r.name_. If equal then it
 * returns true if l.namespace_.uri_ < r.namespace_.uri_ is true.
 */
RW_XMLABSTRACTIONS_GLOBAL bool operator<(const RWXmlName&, const RWXmlName&);

// inline implementations
inline const
RWCString& RWXmlName::getLocalName() const
{
    return name_;
}

inline void
RWXmlName::setLocalName(const RWCString& localName)
{
    name_ = localName;
}

inline const RWXmlNamespace&
RWXmlName::getNamespace() const
{
    return ns_;
}

inline RWXmlNamespace&
RWXmlName::getNamespace()
{
    return RW_EXPOSE(ns_);
}

inline void
RWXmlName::setNamespace(const RWXmlNamespace& ns)
{
    ns_ = ns;
}

inline void
RWXmlName::unsetNamespace()
{
    ns_ = RWXmlNamespace::getEmptyNamespace();
}

inline RWXmlName&
RWXmlName::operator=(const RWXmlName& other)
{
    name_ = other.name_;
    ns_ = other.ns_;
    return *this;
}

#endif // rw_xmlabstractions_RWXmlName_h_
