#ifndef __rw_functor_map_RWTFunctorMapR2Imp_h__
#define __rw_functor_map_RWTFunctorMapR2Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/map/RWTFunctorMapR2Imp.h#1 $
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
 * The body class for functor map bodies that are invoked with two caller
 * arguments (the key, and a caller argument to be passed to the functor),
 * and return a value.
 *
 *************************************************************************/

#include <rw/functor/map/RWTFunctorMapR2.h>
#include <rw/functor/map/pkgdefs.h>
#include <rw/functor/RWTFunctorR2Imp.h>
#include <rw/tvhdict.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class SR, class Key, class S1>
class RWTFunctorMapR2Imp : public RWTFunctorR2Imp<SR, Key, S1>
{

public:

    // The type of the key.
    typedef Key key_type;

    // The signature of the hash function.
    typedef unsigned(*hash_function)(const Key&);

    // Grants access to the private constructor for the corresponding
    // handle class.  This allows the handle to create a body as
    // part of its construction process.
    friend class RWTFunctorMapR2<SR, Key, S1>;

    // Destructor
    ~RWTFunctorMapR2Imp(void);

    // Adds the specified functor to the functor map with the
    // corresponding key. If an entry already exists with
    // an equivalent key, the addition fails and false is returned.
    bool
    add(Key key, RWTFunctorR1<SR, S1> functor);

    // Removes the entry, if it exists, with the equivalent key,
    // and returns true. If there is no such entry, returns false.
    bool
    remove(Key key);

    // Invokes the functor in the map that is associated with
    // the given key.  If there is no matching key, and a
    // default functor has been set, this calls the default.
    // If there is no default, and no matching key, it throws a
    // 'RWTHRInternalError' exception.
    SR
    run(Key key, S1 s1) const;

    // Returns true if the functor map contains an entry
    // with an equivalent key.
    bool
    contains(Key key) const;

    // Finds the entry in the functor map with the equivalent key,
    // and returns it via the 'RWTFunctorR1<SR,S1>' reference parameter.
    // Returns true if the key is found, and otherwise, returns false.
    // In the case where a matching key is not found, but a
    // default functor exists, this sets the reference parameter
    // to the default functor, but returns false.
    // If no match is found, and there is no default functor,
    // it throws a 'RWTHRInternalError' exception.
    bool
    find(Key key, RWTFunctorR1<SR, S1>& functor) const;

    // Changes the size of the map to be 'size'.
    // This is an expensive operation, since the entire map
    // must be re-created.
    // Size can be set at construction time via the 'size'
    // parameter.
    void
    resize(size_t size);

    // Clears the functor map of all entries.
    void
    clear(void);

    // Returns the number of entries in the functor map.
    size_t
    entries(void) const;

    // Sets a functor as the default functor. This functor will be
    // used whenever an invalid key is used to access the functor map.
    void
    setDefault(RWTFunctorR1<SR, S1> functor);

    // Returns the map's default functor.
    RWTFunctorR1<SR, S1>
    getDefault(void) const;

private:

    RWTFunctorMapR2Imp(const RWTFunctorMapR2Imp& second);

    RWTFunctorMapR2Imp&
    operator=(const RWTFunctorMapR2Imp& second);

protected:

    // Constructor is private, forcing users to create maps via the
    // handle class 'RWTFunctorMapR2'.
    RWTFunctorMapR2Imp(hash_function hf, size_t size);

    // The actual map, which stores the associations between
    // keys and functors.
    RWTValHashDictionary<Key, RWTFunctorR1<SR, S1>, RWTHasher<Key> > map_;

    // The default functor.  If set, this is used whenever an invalid
    // key is passed.
    RWTFunctorR1<SR, S1> defaultFunctor;

};


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/map/RWTFunctorMapR2Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_map_RWTFunctorMapR2Imp_h__
