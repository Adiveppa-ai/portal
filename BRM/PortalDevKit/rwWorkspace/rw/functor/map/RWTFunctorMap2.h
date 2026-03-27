#ifndef __rw_functor_map_RWTFunctorMap2_h__
#define __rw_functor_map_RWTFunctorMap2_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/map/RWTFunctorMap2.h#1 $
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

/**************************************************************************
 *
 * Description:
 *
 * The functor map class which takes two arguments at invocation, and
 * returns no value.
 *
 *************************************************************************/

#include <rw/functor/map/pkgdefs.h>
#include <rw/functor/RWTFunctor1.h>
#include <rw/functor/RWTFunctor2.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class Key, class S1> class RWTFunctorMap2Imp;


/**
 * \ingroup functor_map_package
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTValHashMap "RWTValHashMap<Key, RWTFunctor<void(S1)>>" instead.
 *
 * \brief
 * Deprecated. A functor map that takes two arguments at invocation time and
 * returns no value.
 *
 * The RWTFunctorMap2 class represents the functor maps that take two
 * arguments at invocation time and return no value. Since one of these
 * argments is the key into the map, the functors held in the map take only
 * one argument, and are RWTFunctor1 functors.
 *
 * Functor maps allow functors to be grouped together in a key/value table
 * structure. They add functors to the map with a corresponding key of type
 * #key_type, used later to invoke the desired functor.
 *
 * \example
 * \code
 * #include <rw/cstring.h>
 * #include <rw/functor/functor1.h>
 * #include <rw/functor/map/RWTFunctorMap2.h>
 *
 * // Functions that we want to wrap in functors:
 * void okButton(RWCString user_data)
 * {
 *     std::cout << "okButton was pushed, user data is: "
 *               << user_data << std::endl;
 * }
 * void cancelButton(RWCString user_data)
 * {
 *     std::cout << "cancelButton was pushed, user data is: "
 *               << user_data << std::endl;
 * }
 *
 * int main()
 * {
 *     // Create new 'RWTFunctor1<RWCString>s to be the values
 *     // in the map.
 *     RWTFunctor1<RWCString> okFunctor =
 *         rwtMakeFunctor1((void(*)(RWCString))0, okButton);
 *     RWTFunctor1<RWCString> cancelFunctor =
 *         rwtMakeFunctor1((void(*)(RWCString))0, cancelButton);
 *
 *     // Create keys with which to associate the values.
 *     RWCString okKey = "ok";
 *     RWCString cancelKey = "cancel";
 *
 *     // Declare a new map. A complete, but empty, instance
 *     // now exists.
 *     RWTFunctorMap2<RWCString, RWCString>  fmap(RWCString::hash);
 *
 *     // Add something to the map to make it useful.
 *     fmap.add(okKey, okFunctor);
 *     fmap.add(cancelKey, cancelFunctor);
 *
 *     // Invoking the map with the key "ok" calls the okButton
 *     // functor, and passes it the caller data "Fred".
 *     fmap("ok", "Fred");
 *
 *     // Finally, invoking the map with the key "cancel" calls the
 *     // cancelButton functor, and passes it the caller data "Barney".
 *     fmap("cancel", "Barney");
 *
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * okButton was pushed, user data is: Fred
 * cancelButton was pushed, user data is: Barney
 * \endcode
 * \endexample
 */
template <class Key, class S1>
class RW_DEPRECATE_TYPE("Use RWTValHashMap<Key, RWTFunctor<void()>> instead") RWTFunctorMap2
    : public RWTFunctor2<Key, S1>
{

public:

    /**
     * The type of the key.
     */
    typedef Key key_type;

    /**
     * The signature of the hash function.
     */
    typedef unsigned(*hash_function)(const Key&);

    /**
     * Constructs an empty map instance. This creates a complete
     * RWTFunctorMap2 instance, but with no entries. The \a size parameter
     * has a default value of #RW_FUNCTOR_MAP_CAPACITY, defined in
     * \c rw/functor/map/pkgdefs.h.
     */
    RWTFunctorMap2(hash_function hf, size_t size = RW_FUNCTOR_MAP_CAPACITY);

    // Not part of the published interface.
    // Binds a new handle instance to a functor map body instance.
    RWTFunctorMap2(RWTFunctorMap2Imp<Key, S1>* functorImp);

    /**
     * Copy constructor. Constructs a new functor map instance that then
     * shares its representation with the functor map \a second.
     */
    RWTFunctorMap2(const RWTFunctorMap2<Key, S1>& second);

    /**
     * Destructor.
     */
    ~RWTFunctorMap2(void);

    /**
     * Assignment operator. Binds this functor map instance to the
     * representation of the \a second map instance.
     */
    RWTFunctorMap2<Key, S1>&
    operator=(const RWTFunctorMap2<Key, S1>& second);

    /**
     * Invokes the functor in the map that is associated with a key
     * equivalent to the given \a key. If there is no matching key, and a
     * default functor has been set, calls the default. If there is no
     * default and no matching key, throws an RWTHRInternalError exception.
     */
    void
    operator()(Key key, S1 s1) const;

    // Not part of the published interface.
    // Gets a reference to the functor map body instance to which this
    // handle instance points.
    // Documented in base class.
    RWTFunctorMap2Imp<Key, S1>&
    body(void) const;

    /**
     * Adds the specified \a functor to the functor map with the
     * corresponding \a key, and returns \c true. If an entry already exists
     * with an equivalent key, returns \c false, and the addition fails.
     */
    bool
    add(Key key, RWTFunctor1<S1> functor);

    /**
     * Removes the entry, if it exists, with a key equivalent to the given
     * \a key, and returns \c true. If no such entry exists, returns
     * \c false.
     */
    bool
    remove(Key key);

    /**
     * Returns \c true if the functor map contains an entry with key
     * equivalent to the given \a key, otherwise \c false.
     */
    bool
    contains(Key key) const;

    /**
     * Finds the entry in the functor map with a key equivalent to the given
     * \a key, and returns it via the reference parameter \a functor.
     * Returns \c true if the key is found, otherwise \c false. If a
     * matching key is not found but a default functor exists, sets the
     * parameter \a functor to the default functor, and returns \c false. If
     * no match is found and there is no default functor, throws an
     * RWTHRInternalError exception.
     *
     * \sa
     * setDefault().
     */
    bool
    find(Key key, RWTFunctor1<S1>& functor) const;

    /**
     * Changes the size of the map to \a size. This is an expensive
     * operation, since the entire map must be re-created. Size can be set
     * at construction time via the \c size parameter of the
     * \ref RWTFunctorMap2(hash_function, size_t) "constructor".
     */
    void
    resize(size_t size);

    /**
     * Clears the functor map of all entries.
     */
    void
    clear(void);

    /**
     * Returns the number of entries in the functor map.
     */
    size_t
    entries(void) const;

    /**
     * Sets \a functor as the default functor. This functor is used when an
     * invalid key is provided to access the functor map.
     */
    void
    setDefault(RWTFunctor1<S1> functor);

    /**
     * Returns the map's default functor.
     *
     * \sa
     * setDefault().
     */
    RWTFunctor1<S1>
    getDefault(void) const;

};
#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/map/RWTFunctorMap2.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_map_RWTFunctorMap2_h__
