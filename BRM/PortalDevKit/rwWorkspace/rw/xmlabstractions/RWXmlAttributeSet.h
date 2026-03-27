#ifndef rw_xmlabstractions_RWXmlAttributeSet_h_
#define rw_xmlabstractions_RWXmlAttributeSet_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlAttributeSet.h#1 $
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

#include <rw/xmlabstractions/RWXmlAttribute.h>
#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/cstring.h>
#include <set>


// Disabling warning #1744:
// field of class type without a DLL interface used in a class with a DLL
// interface.  The data member attributes_ (std::set) is not exported and thusly
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

/**************************************************************************
 * RWXmlAttributeSet class provides STL collection semantics for adding, looking
 * up, iterating and removing attributes, with "spell-checker" methods for
 * manipulating namespace and default namespace attributes. Many of the API
 * classes' implementations hold an instance of (a child of) this class.
 **************************************************************************/
class RW_XMLABSTRACTIONS_GLOBAL RWXmlAttributeSet
{
public:
    /**
     * typedefs make it easy to use the iterators
     */
    typedef RWXmlName                        AttributeName;
    typedef std::set<RWXmlAttribute>         AttributeTable;
    typedef AttributeTable::iterator         iterator;
    typedef AttributeTable::const_iterator   const_iterator;
    typedef AttributeTable::size_type        size_type;
    typedef AttributeTable::key_type         key_type;
    typedef AttributeTable::value_type       value_type; // == key_type

    /**
     * Default constructor: Empty set
     */
    RWXmlAttributeSet();

    /**
     * copy constructor: deep copy of the set
     */
    RWXmlAttributeSet(const RWXmlAttributeSet& a);

    /**
     * This class is intended as a base: needs virtual destructor
     */
    virtual ~RWXmlAttributeSet();

    /**
     * assignment: deep copy of the set
     */
    RWXmlAttributeSet&          operator=(const RWXmlAttributeSet& a);

    /**
     * Forward set's size()
     */
    inline size_type                           size() const;

    /**
     * Forward set's begin
     */
    inline RWXmlAttributeSet::iterator          begin();

    /**
     * Forward set's begin
     */
    inline RWXmlAttributeSet::const_iterator    begin() const;

    /**
     * Forward set's end
     */
    inline RWXmlAttributeSet::iterator          end();

    /**
     * Forward set's end
     */
    inline RWXmlAttributeSet::const_iterator    end() const;

    /**
     * Add an attribute.
     */
    void                      add(const RWXmlAttribute& attr);

    /**
     * Add a name, value pair
     */
    void                      add(const RWXmlName&, const RWCString&);

    /**
     * Erase all the name value pairs
     */
    inline void               clear();

    /**
     * Return true if there is an attribute with this RWXmlName.
     */
    bool                      contains(const RWXmlName& name) const;

    /**
     * Return true if there is a match for this attribute's RWXmlName
     */
    inline bool               contains(const RWXmlAttribute& attr) const;

    /**
     * Remove the attribute with this RWXmlName, (if any).
     */
    inline void               remove(const RWXmlName& name);

    /**
     * Remove the attribute that matches this attribute (if any)
     */
    inline void               remove(const RWXmlAttribute& attr);

    /**
     * Remove the attribute referenced by this iterator.
     */
    inline iterator           remove(iterator loc);

    /**
     * Return a const iterator referencing attribute with this RWXmlName, if
     * there is such an attribute. Return end() if there is not.
     */
    inline const_iterator     find(const RWXmlName& name) const;

    /**
     * Return a const iterator referencing attribute that matches this
     * attribute's RWXmlName, if there is such an attribute. Return end() if
     * there is not.
     */
    inline const_iterator     find(const RWXmlAttribute& attr) const;

    /**
     * Return an iterator referencing attribute with this name, if there is
     * such an attribute. Return end() if there is not.
     */
    inline iterator           find(const RWXmlName& name);

    /**
     * Return an iterator referencing attribute that matches this
     * attribute's RWXmlName, if there is such an attribute. Return end() if
     * there is not.
     */
    inline iterator           find(const RWXmlAttribute& attr);

    /**
     * Add the attribute "xmlns:prefix", "URI" for the namespace consisting
     * of the pair "prefix", "URI".
     */
    void                      addNamespaceAttribute(const RWXmlNamespace&);

    /**
     * Return a const iterator referencing attribute with name "xmlns:s", if
     * any otherwise return end().
     */
    const_iterator            findNamespaceAttribute(const RWCString& s) const;

    /**
     * Return an iterator referencing attribute with name "xmlns:s", if any
     * otherwise return end().
     */
    iterator                  findNamespaceAttribute(const RWCString& s);

    /**
     * Return a const iterator referencing attribute with name "xmlns:s", if
     * any otherwise return end().
     */
    const_iterator            findNamespaceAttribute(const RWXmlNamespace& ns) const;

    /**
     * Return an iterator referencing attribute with name "xmlns:s", if any
     * otherwise return end().
     */
    iterator                  findNamespaceAttribute(const RWXmlNamespace& s);

    /**
     * Remove the attribute with the name "xmlns:prefix", if any. Return
     * false if there was no such attribute.
     */
    inline void               removeNamespaceAttribute(const RWXmlNamespace&);

    /**
     * Remove the attribute with name "xmlns:s", if any, and return true if
     * there was such an attribute, else false.
     */
    void                      removeNamespaceAttribute(const RWCString& s);

    /**
     * Add (or replace) the attribute with name "xmlns" and value s.
     */
    void                      setDefaultNamespaceAttribute(const RWCString& s);

    /**
     * Add (or replace) the attribute with name "xmlns" and value ns.
     */
    void                      setDefaultNamespaceAttribute(const RWXmlNamespace& ns);

    /**
     * Return the (uri) string associated with the attribute name "xmlns" if
     * any, otherwise return the empty string.
     */
    const RWCString&          getDefaultNamespaceAttribute() const;

    /**
     * Remove the attribute with name "xmlns" if any, and return true if
     * there was such an attribute, else false.
     */
    void                      removeDefaultNamespaceAttribute();

    /**
     * Add or replace the attribute with name "xmlns" and value "".
     */
    inline void               unsetDefaultNamespaceAttribute();

    /**
     * Return true if the number of attributes is the same, and the
     * RWXmlName of each attribute in this set is the same as an RWXmlName
     * of the other set, and for each name, the value is the same. (Note:
     * RWXmlNames are unique in each set).
     */
    int                       compareTo(const RWXmlAttributeSet& other) const;

    // Known attribute names per XML spec, empty string to return by reference
    static const RWCString    EmptyString;
    static const RWCString    DefaultNamespaceAttributeTag;
private:
    AttributeTable               attributes_;

    //methods
    iterator                  findNamespaceByPrefix(const RWCString& prefix);
    const_iterator            findNamespaceByPrefix(const RWCString& prefix) const;


}; // end of class RWXmlAttributeSet declaration

// global (in) equality ops are NOT defined

inline RWXmlAttributeSet::size_type
RWXmlAttributeSet::size() const
{
    return attributes_.size();
}

inline RWXmlAttributeSet::iterator
RWXmlAttributeSet::begin()
{
    return attributes_.begin();
}

inline RWXmlAttributeSet::const_iterator
RWXmlAttributeSet::begin() const
{
    return attributes_.begin();
}

inline RWXmlAttributeSet::iterator
RWXmlAttributeSet::end()
{
    return attributes_.end();
}

inline RWXmlAttributeSet::const_iterator
RWXmlAttributeSet::end() const
{
    return attributes_.end();
}

inline void
RWXmlAttributeSet::clear()
{
    attributes_.clear();
}

inline RWXmlAttributeSet::iterator
RWXmlAttributeSet::find(const RWXmlName& name)
{
    return attributes_.find(RWXmlAttribute(name, RWXmlAttributeSet::EmptyString));
}

inline RWXmlAttributeSet::iterator
RWXmlAttributeSet::find(const RWXmlAttribute& attr)
{
    return attributes_.find(attr);
}

inline RWXmlAttributeSet::const_iterator
RWXmlAttributeSet::find(const RWXmlName& name) const
{
    return attributes_.find(RWXmlAttribute(name, RWXmlAttributeSet::EmptyString));
}

inline RWXmlAttributeSet::const_iterator
RWXmlAttributeSet::find(const RWXmlAttribute& attr) const
{
    return attributes_.find(attr);
}

inline void
RWXmlAttributeSet::remove(const RWXmlName& name)
{
    iterator iter = find(name);
    remove(iter);
}

inline void
RWXmlAttributeSet::remove(const RWXmlAttribute& attr)
{
    attributes_.erase(attr);
}

inline RWXmlAttributeSet::iterator
RWXmlAttributeSet::remove(iterator loc)
{
    iterator ret = loc;
    if (loc != end()) {
        ++ret;
        attributes_.erase(loc);
    }
    return ret;
}

inline bool
RWXmlAttributeSet::contains(const RWXmlAttribute& attr) const
{
    return (static_cast<const_iterator>(attributes_.find(attr)) != attributes_.end());
}

inline void
RWXmlAttributeSet::unsetDefaultNamespaceAttribute()
{
    setDefaultNamespaceAttribute(RWXmlAttributeSet::EmptyString);
}

inline void
RWXmlAttributeSet::removeNamespaceAttribute(const RWXmlNamespace& ns)
{
    removeNamespaceAttribute(ns.getPrefix());
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_xmlabstractions_RWXmlAttributeSet_h_
