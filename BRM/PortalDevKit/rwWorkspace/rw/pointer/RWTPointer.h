#ifndef __rw_pointer_RWTPointer_h__
#define __rw_pointer_RWTPointer_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTPointer.h#1 $
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

#include <rw/pointer/pkgdefs.h>
#include <rw/threxcept/RWTHRInvalidPointer.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPointer RWTPointer
#endif

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Base class for smart-pointer classes.
 *
 * Base class for the smart-pointer classes in the Smart Pointer package.
 */
template< class Body >
class RWTPointer
{
public:

    /**
     * The type of the body.
     */
    typedef Body BodyType;

    /**
     * Destructor. Throws no exceptions.
     */
    ~RWTPointer(void);

    /**
     * Check if the pointer is valid. Throws an RWTHRInvalidPointer
     * exception if the pointer is #rwnil.
     */
    void
    validate(void) const;

    /**
     * Returns \c true if the pointer is non-nil (#rwnil), otherwise returns
     * \c false. Throws no exceptions.
     */
    bool
    isValid(void) const;

    /**
     * Tests to see if this instance points to the same body that the
     * \a second instance points to. Throws no exceptions.
     */
    bool
    operator==(const RWTPointer<Body>& second) const;

    /**
     * Tests to see if this instance points to a different body than the
     * \a second instance points to. Throws no exceptions.
     */
    bool
    operator!=(const RWTPointer<Body>& second) const;

    //--Provide dummy less-than operator to allow smart-pointer
    //--classes to be used in 'stdlib'-based collections.
    //--This member compares the body addresses and should
    //--be replaced in derived classes if other behavior is desired.
    //--Throws no exceptions.
    bool
    operator<(const RWTPointer<Body>& second) const;

    /**
     * Tests to see if this instance points to the same body as \a ptr.
     * Throws no exceptions.
     */
    bool
    operator==(const Body* ptr) const;

    /**
     * Tests to see if this instance points to a different body than \a ptr.
     * Throws no exceptions.
     */
    bool
    operator!=(const Body* ptr) const;

    /**
     * Swap bodies, if any, pointed to by this and \a second. Throws no
     * exceptions.
     */
    void
    swapWith(RWTPointer<Body>& second);

protected:

    /**
     * Constructs a handle instance with a pointer value of #rwnil. Throws
     * no exceptions.
     */
    RWTPointer(void);

    /**
     * Constructor for static pointers that may be used before constructed.
     * Throws no exceptions.
     */
    RWTPointer(RWStaticCtor);

    /**
     * Constructs a handle instance that points to the specified body.
     * Throws no exceptions.
     */
    RWTPointer(Body* bodyP);

    /**
     * Constructs a handle instance that points to the same body as
     * \a second. Throws no exceptions.
     */
    RWTPointer(const RWTPointer<Body>& second);

    /**
     * Retrieves the handle's pointer value without validating it. Throws no
     * exceptions.
     */
    Body*
    get(void) const;

    /**
     * Assigns a new pointer value to the handle. The parameter \a ptr is
     * \c Body*. Throws no exceptions.
     */
    RWTPointer<Body>&
    operator=(Body* ptr);

protected:
    Body* bodyP_;

private:
    void throwInvalid() const;
};

template< class Body >
inline bool
RWTPointer<Body>::isValid(void) const
{
    return (rwnil != bodyP_);
}

template< class Body >
void
RWTPointer<Body>::throwInvalid() const
{
    throw RWTHRInvalidPointer();
}

template< class Body >
inline void
RWTPointer<Body>::validate(void) const
{
    if (bodyP_ == rwnil) {
        throwInvalid();
    }
}



#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/pointer/RWTPointer.cc>
#endif

#endif //__rw_pointer_RWTPointer_h__
