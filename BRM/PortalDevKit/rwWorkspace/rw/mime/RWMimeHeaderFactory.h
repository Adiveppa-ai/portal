#ifndef rw_mime_RWMimeHeaderFactory_h
#define rw_mime_RWMimeHeaderFactory_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeHeaderFactory.h#1 $
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

#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/pointer/RWTCountingPointer.h>
#include <rw/pointer/fwd.h>
#include <rw/tvhdict.h>

class RWCString;

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/*
 * @internal
 *
 * The MIME package uses an instance of RWMimeHeaderFactory to construct
 * MIME headers from strings.

 * The factory contains a registry which associates functors with header labels.
 * Each functor creates an instance of RWMimeHeader as a handle to the
 * correct implementation type.  For example, the registry associates the
 * label "Content-Disposition" with a functor that returns an RWMimeHeader
 * object that is a handle to a Content-Disposition header.
 *
 * The factory provides functions for adding and removing header functors. While
 * the factory also provides a public function for creating headers, this
 * function is intended for use by other classes in the package.
 *
 * The MIME package uses a single instance of RWMimeHeaderFactory.
 * There is no need to construct an instance of this class.  Instead, use
 * RWMimeHeaderFactory::instance() to access the instance the package itself
 * uses.
 *
 * For example, code such as
 *
 * @code
 * RWMimeHeaderFactory::instance()->
 *   setHeaderFunctor("X-Extension-Header", xExtensionHeaderFunctor);
 * @endcode
 *
 * correctly accesses the RWMimeHeaderFactory instance used by the MIME package.
 *
 * By default, the factory instance contains functors for each header type in the
 * MIME package and a default functor that creates an RWMimeHeader with no special
 * requirements on the value.
 *
 */

class RW_MIME_GLOBAL RWMimeHeaderFactory
{
public:
    friend class RWTSingleton<RWMimeHeaderFactory>;

    /*
     * Destructor.
     */
    ~RWMimeHeaderFactory(void);

    /*
     * Creates a RWMimeHeader by calling the functor registered
     * for \a label.  Uses a case-insensitive comparison to match
     * \a label. If no registered functor matches, creates the
     * header by calling the default functor.
     * @note This function only constructs a header.  It does not
     * set the label or value of the header.
     */
    RWMimeHeader
    create(const RWCString& label) const;

    /*
     * Returns \c true if a functor is registered for \a label,
     * \c false otherwise.
     */
    bool
    contains(const RWCString& label) const;

    /*
     * Registers \a functor for \a label.  If a functor is already registered
     * for \a label, replaces that functor with \a functor.
     */
    void
    setHeaderFunctor(const RWCString& label, RWTFunctor<RWMimeHeader()> functor);

    /*
     * Removes the functor for \a label from the registry.  If no
     * matching functor is registered, has no effect.
     */
    void
    unsetHeaderFunctor(const RWCString& label);

    /*
     * Sets the default functor to \a functor.
     */
    void
    setDefaultHeaderFunctor(RWTFunctor<RWMimeHeader()> functor);

    /*
     * Returns a single access instance of the RWMimeHeaderFactory
     */
    static RWTCountingPointer<RWMimeHeaderFactory, RWAtomicCounter>
    instance(void);

protected:
    /*
     * Default constructor.
     *
     * @note Provided only for use by RWTSingleton.  There is no need
     * to construct an instance of this class.
     *
     */
    RWMimeHeaderFactory(void);

private:
    /*
     * @internal
     * Copy constructor. Private to prevent copying RWMimeHeaderFactory
     * objects.
     */
    RWMimeHeaderFactory(const RWMimeHeaderFactory& second);

    /*
     * @internal
     * Assignment operator. Private to prevent copying RWMimeHeaderFactory
     * objects.
     */
    RWMimeHeaderFactory&
    operator=(const RWMimeHeaderFactory& second);

    RWTValHashMap<RWCString, RWTFunctor<RWMimeHeader()> > functorMap_;
    RWTFunctor<RWMimeHeader()> default_;
};

// create a static handle to the mime header factory in each
// translation unit to ensure that the factory is around as
// long as it might be used.
static RWTCountingPointer<RWMimeHeaderFactory, RWAtomicCounter> rwMimeHeaderFactory
    = RWMimeHeaderFactory::instance();

#if defined(_MSC_VER)
#  pragma warning(push)
#endif

#endif // rw_mime_RWMimeHeaderFactory_h
