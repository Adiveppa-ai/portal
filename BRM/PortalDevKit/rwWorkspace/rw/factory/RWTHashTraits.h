#ifndef rw_factory_RWTHashTraits_h_
#define rw_factory_RWTHashTraits_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/factory/RWTHashTraits.h#1 $
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


//--The static RWTHashTraits::rwtHashTraits() function calls the hash function
//--required to initialize the internal RWTValHashDictionary member of the
//--RWTFactoryRegistry class.
//--By specializing this function, different hash functions can be provided
//--for the RWTValHashDictionary constructor without requiring changes in the
//--RWTFactoryRegistry source code.
//--The 'RWTValHashDictionary<K,V>' constructor requires a pointer to a
//--hash function with the signature:  'unsigned  (*)(const Key&)'.
//--The 'RWTHashTraits<Key>::rwtHashTraits(const Key&)' function calls
//--a hash function for the Key object with the required signature.
//--If the 'Key' object used in the RWTFactoryRegistry, doesn't provide a hash
//--function, then the user must specialize
//--RWTHashTraits<Key>::rwtHashTraits(const Key&) to call, for example, a global
//--hash function.
//--For the Rogue Wave types:'RWCString', 'RWDate', 'RWDateTime', or 'RWWString'
//--this specialization is not necessary.
//--
//--Example:
//--
//--#include <rw/factory/RWTHashTraits.h>
//--
//--//Specializes RWTHashTraits<Key>::rwtHashTraits() for the type Foo.
//--//in this example, userHash() is a user provided hash function that.
//--//returns an unsigned hash value.
//--
//--template<>
//--inline unsigned RWTHashTraits<Foo>::rwtHashTraits(const Foo & ref)
//--{
//--    return userHash(ref);
//--}
//--


template <class Key>
class RWTHashTraits
{
public:
    static inline unsigned rwtHashTraits(const Key& ref)
    {
        return Key::hash(ref);
    }
};

#endif // rw_factory_RWTHashTraits_h_
