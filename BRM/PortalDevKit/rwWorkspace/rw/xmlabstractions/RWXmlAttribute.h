#ifndef rw_xmlabstractions_RWXmlAttribute_h_
#define rw_xmlabstractions_RWXmlAttribute_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlAttribute.h#1 $
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

#include <rw/xmlabstractions/RWXmlName.h>
#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>
#include <utility>  //for pair
#include <string.h>

// Implementation note:
// RWXmlAttributeSet is still a std::pair<RWXmlName,RWCString>. If we ever
// change RWXmlAttributeSet to wrap a list, for instance, we'll get the same
// behavior from its iterators that we get this way.

/**************************************************************************
 * RWXmlAttribute class wraps the idea of an XML attribute. Consists
 * of two parts, wrapped in std::pair --
 *  An attribute name, using RWXmlName
 *  An attribute value, using RWCString
 * or, in programmatic style:
 *   std::pair<RWXmlName,RWCString>
 **************************************************************************/

// Disabling warning #1744:
// field of class type without a DLL interface used in a class with a DLL
// interface.  The data member attr_ (std::pair) is not exported and thusly
// The compiler is concerned it may have to create multiple instances of it.
// This is private data that is never returned so in this scenario the warning
// can be silenced.
#if defined(_MSC_VER)
#  pragma warning(push)
#  if defined(__INTEL_COMPILER)
#    pragma warning(disable : 1744)
#  else
#    pragma warning(disable : 4251)
#  endif
#endif

class RW_XMLABSTRACTIONS_SYMBOLIC RWXmlAttribute
{
public:
    /**
     * AttributeName is a convenient typedef here
     */
    typedef RWXmlName   AttributeName;
    /**
     * AttributeType is the value type of an attributeSet: It is the type
     * returned by dereferencing an iterator over that set. It is also the
     * underlying data format of RWXmlAttribute itself.
     */
    typedef std::pair<RWXmlName, RWCString>  AttributeType;
    //  typedef std::pair<const RWXmlName,RWCString>  AttributeType;
    /**
     * default constructor: empty, empty, and null
     */
    RWXmlAttribute();

    /**
     * The canonical constructor takes name, value arguments
     */
    RWXmlAttribute(const RWXmlName& name, const RWCString& value);

    /**
     * Another constructor takes the name, value pair, as strings, and an
     * optional namespace, defaulting to the empty one.
     */
    RWXmlAttribute(const RWCString& name, const RWCString& value, const RWXmlNamespace& ns = RWXmlNamespace::getEmptyNamespace());

    /**
     * copy constructor does a full copy
     */
    RWXmlAttribute(const RWXmlAttribute&);

    ~RWXmlAttribute();

    /**
     * expected assignment semantics
     */
    inline RWXmlAttribute&           operator=(const RWXmlAttribute&);

    /**
     * non-const version allows getName().mutate() code: a convenience.
     */
    RWXmlName&                       getName();

    /**
     * The RWXmlName encapsulates the idea of name and namespace
     */
    const RWXmlName&                 getName() const;

    /**
     * Change the name
     */
    inline void                      setName(const RWXmlName& name);

    /**
     * Get the string "value" associated with this attribute
     */
    inline const RWCString&          getValue() const;

    /**
     * Change the value of this attribute
     */
    inline void                      setValue(const RWCString&);

    /*
     * Returns getName().compareTo(other.getName(): Each attribute in an
     * attribute set has a unique (within that set) name, by definition.
     *
     * public to make operators ==, < and != easy; but no need to document.
     */
    inline int                       compareTo(const RWXmlAttribute&) const;

private:
    std::pair<RWXmlName, RWCString> attr_;
}; // end of class declaration for RWXmlAttribute

// inline method implementations:

inline int
RWXmlAttribute::compareTo(const RWXmlAttribute& other) const
{
    return getName().compareTo(other.getName());
}

inline bool
operator<(const RWXmlAttribute& lhs, const RWXmlAttribute& rhs)
{
    return lhs.compareTo(rhs) < 0;
}

inline bool
operator==(const RWXmlAttribute& lhs, const RWXmlAttribute& rhs)
{
    return lhs.getName() == rhs.getName();
}

inline bool
operator!=(const RWXmlAttribute& lhs, const RWXmlAttribute& rhs)
{
    return lhs.getName() != rhs.getName();
}

inline void
RWXmlAttribute::setName(const RWXmlName& name)
{
    attr_.first = name;
}

inline const RWCString&
RWXmlAttribute::getValue() const
{
    return attr_.second;
}

inline void
RWXmlAttribute::setValue(const RWCString& value)
{
    attr_.second = value;
}

inline RWXmlAttribute&
RWXmlAttribute::operator=(const RWXmlAttribute& other)
{
    attr_ = other.attr_;
    return *this;
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_xmlabstractions_RWXmlAttribute_h_
