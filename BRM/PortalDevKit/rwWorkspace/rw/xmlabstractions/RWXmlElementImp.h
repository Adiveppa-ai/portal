#ifndef rw_xmlabstractions_RWXmlElementImp_h_
#define rw_xmlabstractions_RWXmlElementImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlElementImp.h#1 $
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

#include <rw/xmlabstractions/RWXmlAttributeSet.h> // The collection of attributes

/**************************************************************************
 *
 * RWXmlElementImp is a core set of data and methods that will be used by all
 * the "body" parts of the handle-body hierarchy comprising a putative XML
 * (but for now, only Soap) document. Almost all the methods may be inline,
 * non-virtual because almost all the things that any child needs can be
 * handled with our own data.
 *
 * The standard handle/body pattern would make all the impl methods protected,
 * with the handle as friend. Because we are providing direct access to the
 * impl for efficiency reasons, we will not do that. Methods that are present
 * purely as an implementation detail will be either protected or private, but
 * all other methods will be public.
 *
 **************************************************************************/
class RW_XMLABSTRACTIONS_GLOBAL RWXmlElementImp
{
protected:
    RWXmlName         name_;         // RWXmlName has a name and a space
    RWXmlAttributeSet attributes_;   // map of key->value attribute pairs

private: // unimplemented
    RWXmlElementImp& operator=(const RWXmlElementImp&);
protected:
    // constructors protected to prevent the wrong folks using us.
    RWXmlElementImp();
    RWXmlElementImp(const RWXmlName& name);
    // beware: copy constructor does deep copy
    RWXmlElementImp(const RWXmlElementImp&);
    virtual ~RWXmlElementImp();
public:
    // iterator typedefs
    typedef RWXmlAttributeSet::iterator attribute_iterator;
    typedef RWXmlAttributeSet::const_iterator const_attribute_iterator;

    // accessors for full name
    virtual inline void               setName(const RWXmlName&);
    virtual inline const RWXmlName&   getName() const;
    virtual inline RWXmlName&         getName();
    // accessors for (local) name
    inline void                       setLocalName(const RWCString&);
    inline const RWCString&           getLocalName() const;
    // helpers for namespace-modified names
    inline RWCString                  getQualifiedName() const; // return copy
    inline RWCString                  getUniqueName() const; // return copy

    // accessors for this element's one namespace
    inline void                       setNamespace(const RWXmlNamespace&);
    const RWXmlNamespace&             getNamespace() const;
    RWXmlNamespace&                   getNamespace();
    inline void                       setAndAddNamespace(const RWXmlNamespace&);
    // true if there was a namespace to unset
    inline void                       unsetNamespace();

    // accessors for namespace attributes (any number)
    virtual inline void               addNamespaceAttribute(const RWXmlNamespace&);
    virtual inline const_attribute_iterator findNamespaceAttribute(const RWCString&) const;
    virtual inline attribute_iterator findNamespaceAttribute(const RWCString&);
    virtual inline const_attribute_iterator findNamespaceAttribute(const RWXmlNamespace&) const;
    virtual inline attribute_iterator findNamespaceAttribute(const RWXmlNamespace&);
    // true if there was something to remove
    virtual inline void               removeNamespaceAttribute(const RWXmlNamespace&);
    // true if there was something to remove
    virtual inline void               removeNamespaceAttribute(const RWCString&);

    // accessors for default namespace attribute (each element has at most one)
    virtual inline void               setDefaultNamespaceAttribute(const RWXmlNamespace&);
    // see above
    virtual inline void               setDefaultNamespaceAttribute(const RWCString&);
    // true if there is something to unset
    virtual inline void               unsetDefaultNamespaceAttribute();
    virtual inline const RWCString&   getDefaultNamespaceAttribute() const;

    // generic attributes: iterator stuff

    virtual inline attribute_iterator attributesBegin()
    {
        return attributes_.begin();
    }

    virtual inline const_attribute_iterator attributesBegin() const
    {
        return attributes_.begin();
    }

    virtual inline attribute_iterator attributesEnd()
    {
        return attributes_.end();
    }


    virtual inline const_attribute_iterator attributesEnd() const
    {
        return attributes_.end();
    }

    // accessors and other  generic attributes methods
    virtual inline RWXmlAttributeSet::size_type attributeCount() const
    {
        return attributes_.size();
    }

    virtual inline void               clearAttributes();

    virtual void                      addAttribute(const RWXmlName&, const RWCString&);

    virtual void                      addAttribute(const RWXmlAttribute&);

    virtual void                      removeAttribute(const RWXmlName& name);

    virtual void                      removeAttribute(const RWXmlAttribute&);

    virtual attribute_iterator        removeAttribute(attribute_iterator loc);

    virtual inline const_attribute_iterator findAttribute(const RWXmlName& name) const
    {
        return attributes_.find(name);
    }

    virtual inline attribute_iterator findAttribute(const RWXmlName& name)
    {
        return attributes_.find(name);
    }

    virtual inline const_attribute_iterator findAttribute(const RWXmlAttribute& a) const
    {
        return attributes_.find(a);
    }

    virtual inline attribute_iterator findAttribute(const RWXmlAttribute& a)
    {
        return attributes_.find(a);
    }

    virtual inline bool               hasAttribute(const RWXmlName&) const;
    virtual inline bool               hasAttribute(const RWXmlAttribute&) const;
    virtual inline const RWXmlAttributeSet& getAttributes() const;
    virtual inline RWXmlAttributeSet&   getAttributes(); // not const: allows setting

    //Replaces self's attribute set with the given attrSet
    inline void                       setAttributes(const RWXmlAttributeSet& attrSet);

};

inline void
RWXmlElementImp::setName(const RWXmlName& n)
{
    name_ = n;
}

inline const RWXmlName&
RWXmlElementImp::getName() const
{
    return name_;
}

inline RWXmlName&
RWXmlElementImp::getName()
{
    return RW_EXPOSE(name_);
}

inline const RWCString&
RWXmlElementImp::getLocalName() const
{
    return name_.getLocalName();
}

inline void
RWXmlElementImp::setLocalName(const RWCString& n)
{
    name_.setLocalName(n);
}
inline RWCString
RWXmlElementImp::getQualifiedName() const
{
    return name_.getQualifiedName();
}

inline RWCString
RWXmlElementImp::getUniqueName() const
{
    return name_.getUniqueName();
}

inline void
RWXmlElementImp::setNamespace(const RWXmlNamespace& ns)
{
    name_.setNamespace(ns);
}

inline void
RWXmlElementImp::setAndAddNamespace(const RWXmlNamespace& ns)
{
    name_.setNamespace(ns);
    attributes_.addNamespaceAttribute(ns);
}

inline void
RWXmlElementImp::unsetNamespace()
{
    name_.setNamespace(RWXmlNamespace::getEmptyNamespace());
}

inline void
RWXmlElementImp::addNamespaceAttribute(const RWXmlNamespace& ns)
{
    attributes_.addNamespaceAttribute(ns);
}

inline RWXmlElementImp::const_attribute_iterator
RWXmlElementImp::findNamespaceAttribute(const RWCString& name) const
{
    return attributes_.findNamespaceAttribute(name);
}

inline RWXmlElementImp::attribute_iterator
RWXmlElementImp::findNamespaceAttribute(const RWCString& name)
{
    return attributes_.findNamespaceAttribute(name);
}

inline RWXmlElementImp::const_attribute_iterator
RWXmlElementImp::findNamespaceAttribute(const RWXmlNamespace& ns) const
{
    return attributes_.findNamespaceAttribute(ns);
}

inline RWXmlElementImp::attribute_iterator
RWXmlElementImp::findNamespaceAttribute(const RWXmlNamespace& ns)
{
    return attributes_.findNamespaceAttribute(ns);
}

inline void
RWXmlElementImp::removeNamespaceAttribute(const RWCString& name)
{
    attributes_.removeNamespaceAttribute(name);
}

inline void
RWXmlElementImp::removeNamespaceAttribute(const RWXmlNamespace& ns)
{
    attributes_.removeNamespaceAttribute(ns);
}

inline void
RWXmlElementImp::setDefaultNamespaceAttribute(const RWXmlNamespace& dns)
{
    attributes_.setDefaultNamespaceAttribute(dns.getURI());
}

inline void
RWXmlElementImp::setDefaultNamespaceAttribute(const RWCString& uri)
{
    attributes_.setDefaultNamespaceAttribute(uri);
}

inline void
RWXmlElementImp::unsetDefaultNamespaceAttribute()
{
    attributes_.unsetDefaultNamespaceAttribute();
}

inline const RWCString&
RWXmlElementImp::getDefaultNamespaceAttribute() const
{
    return attributes_.getDefaultNamespaceAttribute();
}

inline void
RWXmlElementImp::clearAttributes()
{
    attributes_.clear();
}

inline bool
RWXmlElementImp::hasAttribute(const RWXmlName& name) const
{
    const_attribute_iterator iter = attributes_.find(name);
    return iter != attributes_.end();
}

inline bool
RWXmlElementImp::hasAttribute(const RWXmlAttribute& attr) const
{
    const_attribute_iterator iter = attributes_.find(attr);
    return iter != attributes_.end();
}

inline const RWXmlAttributeSet&
RWXmlElementImp::getAttributes() const
{
    return attributes_;
}

inline RWXmlAttributeSet&
RWXmlElementImp::getAttributes()
{
    return RW_EXPOSE(attributes_);
}

//Replaces self's attribute set with the given attrSet
inline void
RWXmlElementImp::setAttributes(const RWXmlAttributeSet& attrSet)
{
    attributes_ = attrSet;
}

#endif // rw_xmlabstractions_RWXmlElementImp_h_
