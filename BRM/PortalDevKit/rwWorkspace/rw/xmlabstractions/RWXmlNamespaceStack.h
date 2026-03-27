#ifndef rw_xmlabstractions_RWXmlNamespaceStack_h_
#define rw_xmlabstractions_RWXmlNamespaceStack_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlNamespaceStack.h#1 $
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

#include <rw/xmlabstractions/RWXmlAttributeSet.h>
#include <rw/xmlabstractions/RWXmlNamespace.h>
#include <rw/xmlabstractions/pkgdefs.h>         // everybody needs this
#include <vector>

// Disabling warning #1744:
// field of class type without a DLL interface used in a class with a DLL
// interface.  The data member data_ (std::vector) is not exported and thusly
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

/****************************************************************************
 * RWXmlNamespaceStack is a undocumented utility class that provides the
 * capability to keep track of namespaces in scope.
 *
 * Each time a new element is to be processed and new namespace
 * declarations need to be visible within that element, the pushScope
 * method should be called to create the new scope.  The addNamespace
 * method can then be called any number of times for that particular
 * scope.
 *
 * Scopes nest inside out; that is, any namespace declaration added
 * into a scope is visible from any scopes that are pushed later.
 *
 * To see whether a namespace declaration has already been made for a
 * certain URI, you can call the getPrefixForURI method.
 *
 ****************************************************************************/

class RW_XMLABSTRACTIONS_SYMBOLIC RWXmlNamespaceStack
{
public:
    /**
     * Default constructor. Not much use, really.
     */
    RWXmlNamespaceStack();

    /**
     * Copy constructor has the usual semantics
     */
    RWXmlNamespaceStack(const RWXmlNamespaceStack&);

    /**
     * Always good to have a place to hang some destruction, if needed
     */
    ~RWXmlNamespaceStack();

    /**
     * Create a new scope for which namespaces can be added.
     */
    void pushScope();

    /**
     * Removes the last scope entered and removes any of the namespaces that
     * belonged to it.
     */
    void popScope();

    /**
     * Adds a namespace to the current scope.
     */
    void addNamespace(const RWXmlNamespace& nameSpace);

    /**
     * Gets the prefix for the namespace associated with the specified URI.
     *
     * If a prefix is not found, RWXmlAttributeSet::EmptyString will be
     * returned.
     */
    const RWCString&   getPrefixForURI(const RWCString& uri) const;

    /**
     * Gets the uri for the namespace with the specified prefix
     *
     * If a uri is not found, RWXmlAttributeSet::EmptyString will be
     * returned.
     */
    const RWCString&   getURIForPrefix(const RWCString& prefix) const;

    /**
     * The iterator typedef for iterating through all namespaces in the
     * current scope. This does not include namespaces defined in outer
     * scopes.
     */
    typedef std::vector<RWXmlNamespace>::const_iterator  const_namespace_iterator;

    /**
     * returns stl type iterator for collection of namespaces.
     */
    inline const_namespace_iterator  namespacesBegin() const;

    /**
     * One may iterate over the namespaces in the current scope.
     */
    inline const_namespace_iterator  namespacesEnd() const;

protected:
    std::vector<std::vector<RWXmlNamespace> *> data_;

}; // end of class declaration for RWXmlNamespaceStack

inline RWXmlNamespaceStack::const_namespace_iterator
RWXmlNamespaceStack::namespacesBegin() const
{
    return data_.back()->begin();
}

inline RWXmlNamespaceStack::const_namespace_iterator
RWXmlNamespaceStack::namespacesEnd() const
{
    return data_.back()->end();
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_xmlabstractions_RWXmlNamespaceStack_h_
