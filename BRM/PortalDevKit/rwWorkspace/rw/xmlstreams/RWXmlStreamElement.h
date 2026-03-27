#ifndef rw_xmlstreams_RWXmlStreamElement_h_
#define rw_xmlstreams_RWXmlStreamElement_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWXmlStreamElement.h#1 $
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

#include <rw/xmlstreams/pkgdefs.h>
#include <rw/xmlabstractions/RWXmlAttributeSet.h>
#include <rw/xmlabstractions/RWXmlName.h>
#include <rw/xmlabstractions/RWXmlNamespace.h>
#include <rw/serial/StreamTraits.h>
#include <rw/stream/RWDataInputStream.h>
#include <rw/stream/RWDataOutputStream.h>
#include <rw/cstring.h>
#include <list>
#if defined(__linux__)
#  include <iostream>
#else
#  include <ostream>
#endif

// Disabling warning #1744:
// field of class type without a DLL interface used in a class with a DLL
// interface.  The data member data_ (std::vector) is not exported and thusly
// The compiler is concerned it may have to create multiple instances of it.
// This is private data that is never returned so in this scenario the warning
// can be silenced.
#if defined(_MSC_VER)
#  if defined(__INTEL_COMPILER)
#    pragma warning(disable : 1744)
#  else
#    pragma warning(push)
#    pragma warning(disable : 4251)
#  endif
#endif

/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * An XML element abstraction for implementing efficient C++
 * transformations.
 *
 * This class represents an XML element abstraction for implementing
 * efficient C++ transformations.
 */
class  RW_XMLSTREAMS_GLOBAL RWXmlStreamElement
{
public:
    /**
     * A typedef for the type of element.
     */
    typedef char element_type;
    typedef std::list<RWXmlStreamElement*> element_list_type;
    typedef std::list<RWXmlStreamElement*>::iterator iterator;
    typedef std::list<RWXmlStreamElement*>::const_iterator const_iterator;


    RWXmlStreamElement()
        : parent_(0), type_(RW_NESTED_OBJECT), curChild_(elements_.begin())
    {}

    RWXmlStreamElement(RWStreamType type)
        : parent_(0), type_(type), curChild_(elements_.begin())
    {}

    //--
    //-- Constructor takes a set of namespaces valid in the scope
    //-- of this element.
    //--
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //--
    /**
     * This constructor takes a set of namespaces valid in the scope of this
     * element. The parameter \a namespaces holds a set of RWCString /
     * RWXmlNamespace pairs.
     */
    RWXmlStreamElement(const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces)
        : namespaces_(namespaces), parent_(0), type_(RW_NESTED_OBJECT), curChild_(elements_.begin())
    {}

    //--
    //-- Constructor takes a name for the element, a CDATA  value and a list of namespaces
    //--
    //-- Parameter 'name' contains a name for this element
    //-- Parameter 'value' contains CDATA for the content of this element
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //--
    /**
     * This constructor takes a name for the element, a \c CDATA value, and
     * a list of namespaces. The parameter \a name contains a name for this
     * element. The parameter \a value contains \c CDATA for the content of
     * this element. The parameter \a namespaces holds a set of RWCString /
     * RWXmlNamespace pairs.
     */
    RWXmlStreamElement(const RWXmlName& name, const RWCString& value, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces);

    //--
    //-- Constructor takes a name for the element, an element value and a list of namespaces
    //--
    //-- Parameter 'name' contains a name for this element
    //-- Parameter 'element' contains a element for the content of this element
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //--
    RWXmlStreamElement(const RWXmlName& name, const RWXmlStreamElement& element, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces);

    //--
    //-- Constructor takes a set of namespaces valid in the scope
    //-- of this element.
    //--
    //-- Parameter 'parent' contains the parent of this element
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //--
    RWXmlStreamElement(RWXmlStreamElement* parent, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces)
        : namespaces_(namespaces), parent_(parent), type_(RW_NESTED_OBJECT), curChild_(elements_.begin())
    {}

    //--
    //-- Constructor takes a name for the element, a parent pointer and a list of namespaces
    //--
    //-- Parameter 'name' contains a name for this element
    //-- Parameter 'parent' contains the parent of this element
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //--
    /**
     * This constructor takes a name for the element, an element value, and
     * a list of namespaces. The parameter \a name contains a name for this
     * element. The parameter \a element contains an element for the content
     * of this element. The parameter \a namespaces holds a set of RWCString
     * / RWXmlNamespace pairs.
     */
    RWXmlStreamElement(const RWXmlName& name, RWXmlStreamElement* element, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces);

    //--
    //-- Constructor takes a name for the element, a parent pointer and a list of namespaces
    //--
    //-- Parameter 'name' contains a name for this element
    //-- Parameter 'parent' contains the parent of this element
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //-- Parameter 'type' holds the type of the contained object
    //--
    RWXmlStreamElement(const RWXmlName& name, RWXmlStreamElement* parent, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces, RWStreamType type);

    //--
    //-- Constructor takes a name for the element, a CDATA  value and a list of namespaces
    //--
    //-- Parameter 'name' contains a name for this element
    //-- Parameter 'parent' contains the parent of this element
    //-- Parameter 'value' contains CDATA for the content of this element
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //--
    RWXmlStreamElement(const RWXmlName& name, RWXmlStreamElement* parent, const RWCString& value, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces);

    //--
    //-- Constructor takes a name for the element, an element value and a list of namespaces
    //--
    //-- Parameter 'name' contains a name for this element
    //-- Parameter 'parent' contains the parent of this element
    //-- Parameter 'element' contains a element for the content of this element
    //-- Parameter 'namespaces' holds a set of RWCString/RWXmlNamespace pairs.
    //--
    RWXmlStreamElement(const RWXmlName& name, RWXmlStreamElement* parent, const RWXmlStreamElement& element, const std::list<std::pair<RWCString, RWXmlNamespace> >& namespaces);

    /**
     * This is a copy constructor. The parameter \a element contains the
     * element to copy.
     */
    RWXmlStreamElement(const RWXmlStreamElement& element);

    //--
    //-- Assignment operator
    //--
    //-- Parameter 'element' contains the element to copy
    //--
    RWXmlStreamElement& operator=(const RWXmlStreamElement& element);

    virtual ~RWXmlStreamElement();

    //--
    //-- Set a CDATA value for the element
    //--
    //-- Parameter 'value' contains CDATA for the content of this element
    //--
    /**
     * Sets a value for the element.
     */
    void setValue(const RWCString& value)
    {
        value_ = value;
    }

    //--
    //-- Set an element value for the element
    //--
    //-- Parameter 'element' contains an element for the content of this element
    //--
    /**
     * Adds an element to the set contained by this. The parameter element
     * contains the element to add.
     */
    void setValue(const RWXmlStreamElement& element)
    {
        RWXmlStreamElement* tmp = element.make();
        elements_.push_back(tmp);
    }
    //--
    //-- Set the elements name
    //--
    //-- Parameter 'name' contains a name for this element
    //--
    /**
     * Sets the element's name. The parameter \a name contains a name for
     * this element.
     */
    void setName(const RWXmlName& name)
    {
        name_ = name;
    }

    //--
    //-- Get the elements CDATA value
    //--
    //-- Returns the CDATA value for this element
    //--
    /**
     * Gets the element's value. Returns the value for this element.
     */
    RWCString getValue() const
    {
        return value_;
    }

    //--
    //-- Get the type of the element
    //--
    //-- Returns the type contained by this element
    //--
    RWStreamType getType() const
    {
        return type_;
    }

    //--
    //-- Get the set of sub-elements
    //--
    //-- Returns the set of elements contained in this element
    //--
    /**
     * Gets the set of sub-elements. Returns the set of elements contained
     * in this element.
     */
    const std::list<RWXmlStreamElement*>& getElements() const
    {
        return elements_;
    }

    std::list<RWXmlStreamElement*>& getElements()
    {
        return RW_EXPOSE(elements_);
    }

    //--
    //-- Get the elements name
    //--
    //-- Returns the name of this element
    //--
    /**
     * Gets the element's name. Returns the name of this element.
     */
    RWXmlName getName() const
    {
        return name_;
    }

    //--
    //-- Get the elements attributes
    //--
    //-- Returns the set of attributes for this element
    //--
    /**
     * Gets the element's attributes. Returns the set of attributes for this
     * element.
     */
    const RWXmlAttributeSet& getAttributes() const
    {
        return attributes_;
    }

    RWXmlAttributeSet& getAttributes()
    {
        return RW_EXPOSE(attributes_);
    }

    /**
     * Adds an attribute. The parameter \a attribute contains the attribute
     * to add.
     */
    void addAttribute(const RWXmlAttribute& attribute);

    /**
     * Deletes an attribute. The parameter \a name contains the name of the
     * attribute to be deleted.
     */
    void deleteAttribute(const RWXmlName& name);

    //--
    //-- Find an attribute
    //--
    //-- Parameter 'name' contains the name of the attribute to locate
    //-- Returns the value of the attribute (RWCString() if not found)
    //--
    /**
     * Finds an attribute. The parameter \a name contains the name of the
     * attribute to locate. Returns the value of the attribute, or
     * \ref RWCString::RWCString() "RWCString()" if none is found.
     */
    RWCString findAttribute(const RWXmlName& name) const ;


    /**
     * Adds an element to the set contained by this. The parameter
     * \a element contains the element to add.
     */
    void addElement(const RWXmlStreamElement& element);

    //--
    //-- Add an element to the set contained by this
    //--
    //-- Parameter 'element' contains a pointer to the element to add
    //--
    void addElement(RWXmlStreamElement* element);

    //--
    //-- Delete an element from the set contained by this
    //-- Removes the first element with a matching name
    //--
    //-- Parameter 'name' contains the element to delete
    //--
    /**
     * Deletes an element from the set contained by this. Removes the first
     * element with a matching name. The parameter \a name contains the name
     * of the element to be deleted.
     */
    void deleteElement(const RWXmlName& name);

    //--
    //-- Find an element in the set contained by this
    //--
    //-- Parameter 'name' contains the element to find
    //-- Returns the first element with a matching name
    //--
    /**
     * Finds an element in the set contained by this. The parameter \a name
     * contains the name of the element to locate. Returns the first element
     * with a matching name.
     */
    const_iterator findElement(const RWXmlName& name) const ;

    //--
    //-- Find an element in the set contained by this
    //--
    //-- Parameter 'name' contains the element to find
    //-- Returns the first element with a matching name
    //--
    iterator findElement(const RWXmlName& name);

    //--
    //-- Find an element in the set contained by this
    //--
    //-- Parameter 'name' contains the element to find
    //-- Parameter 'start' contains the iterator where the search starts
    //-- Returns the first element after 'start' with a matching name
    //--
    /**
     * Finds an element in the set contained by this. The parameter \a name
     * contains the name of the element to locate. The parameter \a start
     * contains the iterator where the search starts. Returns the first
     * element after \a start with a matching name.
     */
    const_iterator findNextElement(const RWXmlName& name, const_iterator start) const;

    //--
    //-- Find an element in the set contained by this
    //--
    //-- Parameter 'name' contains the element to find
    //-- Parameter 'start' contains the iterator where the search starts
    //-- Returns the first element after 'start' with a matching name
    //--
    iterator findNextElement(const RWXmlName& name, iterator start);

    //--
    //-- Add namespace to the set valid for this element.
    //-- If the namespace is already present this operation will
    //-- replace it.
    //--
    //-- Parameter 'prefix' contains the namespace prefix (synonym)
    //-- Parameter 'fullname' contains the full namespace (prefix and uri)
    //--
    /**
     * Adds a namespace to the set valid for this element. If the namespace
     * is already present, this operation will replace it. The parameter
     * \a prefix contains the namespace prefix (synonym). The parameter
     * \a fullname contains the full namespace (prefix and URI).
     */
    void addNamespace(const RWCString& prefix, const RWXmlNamespace& fullname);

    //--
    //-- Get the elements namespaces
    //--
    //-- Returns the set of namespaces active for this element
    //--
    /**
     * Gets the elements namespaces. Returns the set of namespaces active
     * for this element.
     */
    const std::list<std::pair<RWCString, RWXmlNamespace> >& getNamespaces() const
    {
        return namespaces_;
    }

    std::list<std::pair<RWCString, RWXmlNamespace> >& getNamespaces()
    {
        return RW_EXPOSE(namespaces_);
    }

    //--
    //-- Delete a namespace from the set valid for this element
    //--
    //-- Parameter 'prefix' contains the prefix of the namespace to remove
    //--
    /**
     * Deletes an namespace from the set valid for this element. The
     * parameter \a prefix contains the prefix of the namespace to be
     * deleted.
     */
    bool deleteNamespace(const RWCString& prefix);

    //--
    //-- Find the URI for a namespace
    //--
    //-- Parameter prefix contains the name of the namespace
    //-- Returns the URI for the namespace if present, otherwise
    //--         returns RWCString()
    //--
    /**
     * Finds the URI for a namespace. The parameter \a prefix contains the
     * name of the namespace. Returns the URI for the namespace if present,
     * otherwise returns \ref RWCString::RWCString() "RWCString()".
     */
    const RWXmlNamespace findNamespaceURI(const RWCString& prefix) const;

    /**
     * Resolves the namespace URIs.
     */
    void resolveNamespaces();

    //--
    //-- Set a parent for the element
    //--
    //-- Parameter 'parent' contains a pointer to the parent of this element
    //--
    void setParent(RWXmlStreamElement* parent)
    {
        parent_ = parent;
    }
    //--
    //-- Set a parent for the element
    //--
    //-- Parameter 'parent' contains a pointer to the parent of this element
    //--
    RWXmlStreamElement* getParent()
    {
        return parent_;
    }
    const RWXmlStreamElement* getParent() const
    {
        return parent_;
    }
    //--
    //-- Get the currently selected child in the element list
    //-- Any add or delete operation on the element list (such as addElement)
    //-- resets this to the first element.
    //--
    //-- returns the currently selected child
    //--
    const_iterator& getCurrentChild()
    {
        return RW_EXPOSE(curChild_);
    }

    //--
    //-- Write out to a stream
    //--
    void write(std::ostream& out);
    virtual void write(RWDataOutputStream& out, int indent);

protected:
    void doIndent(RWDataOutputStream& out, int indent);
    void writePrologue(RWDataOutputStream& out, const RWCString& name, int indent);
    void writeEpilogue(RWDataOutputStream& out, const RWCString& name, int indent);
    virtual RWXmlStreamElement* make() const
    {
        return new RWXmlStreamElement(*this);
    }

private:
    RWXmlName name_;
    RWCString value_;   // CDATA value
    std::list<RWXmlStreamElement*> elements_;
    RWXmlAttributeSet attributes_;
    //    std::map<RWCString,RWXmlNamespace> namespaces_;
    std::list<std::pair<RWCString, RWXmlNamespace> > namespaces_;
    RWXmlStreamElement* parent_;
    RWStreamType type_;
    const_iterator curChild_;
};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_xmlstreams_RWXmlStreamElement_h_
