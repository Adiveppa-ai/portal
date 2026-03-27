#ifndef __rw_thread_RWTThreadEscrowImp_h__
#define __rw_thread_RWTThreadEscrowImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWTThreadEscrowImp.h#1 $
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

#include <rw/thread/pkgdefs.h>
#include <rw/itc/RWTEscrowHandle.h>
#include <rw/itc/fwd.h>
#include <rw/sync/RWCondition.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWThreadEscrowImp RWTThreadEscrowImp
#endif

/**
 * \ingroup threading_package
 *
 * \brief
 * Multithread-safe implementation of RWTEscrowImp.
 *
 * This is a concrete implementation of the RWTEscrowImp class. It is
 * multithread-safe and uses condition variables to communicate between
 * threads.
 *
 * This class should not be used directly. It is intended to be used through
 * the RWTIOUResult and RWTIOUEscrow interfaces. However, you may wish to
 * use the static make() functions provided by this class to construct an
 * escrow instance.
 *
 * \example
 * \code
 * #include <rw/thread/RWTThreadEscrowImp.h>
 * #include <rw/itc/RWTIOUResult.h>
 * #include <rw/itc/RWTIOUEscrow.h>
 *
 * // Create a new RWTThreadEscrowImp<int> impl.,
 * // and use it to initialize RWTIOUResult<int>.
 * RWTIOUResult<int> intRes = RWTThreadEscrowImp<int>::make();
 *
 * // Make an RWTIOUEscrow<int> handle that points
 * // to same RWTThreadEscrowImp<int> as intRes.
 * RWTIOUEscrow<int> intEsc = intRes;
 *
 * // Create a new RWTThreadEscrowImp<RWCString>, and
 * // use it to initialize an RWTIOUEscrow<RWCString>
 * RWTIOUEscrow<RWCString> strEsc =
 *     RWTThreadEscrowImp<RWCString>::make();
 *
 * // Just for the sake of demonstration, make an
 * // RWTIOUResult<RWCString> that points to same
 * // RWTThreadEscrowImp<RWCString> as strEsc.
 * RWTIOUResult<RWCString> strRes = strEsc;
 * \endcode
 * \endexample
 *
 * \sa
 * RWTIOUResult, RWTIOUEscrow, RWTEscrowImp
 */
template <class Redeemable>
class RWTThreadEscrowImp :
    public RWTEscrowImp<Redeemable>
{

    // Member Variables
public:

    /**
     * Public typedef.
     */
    typedef Redeemable RedeemableType;

protected:

    bool   valid_;
    Redeemable  value_;
    RWCondition closedCondition_;

    // Member Functions
public:


    /**
     * Virtual destructor.
     */
    virtual
    ~RWTThreadEscrowImp();


    /**
     * Creates a new RWTThreadEscrowImp. Returns an RWTEscrowHandle handle
     * that can be used to create an RWTIOUResult or RWTIOUEscrow handle to
     * the newly-created escrow implementation.
     */
    static RWTEscrowHandle<Redeemable>
    make();


    /**
     * Creates an RWTThreadEscrowImp and assigns it to an RWTEscrowHandle.
     * The escrow is closed immediately with \a immediateValue. The returned
     * RWTEscrowHandle can be used to initialize an RWTIOUEscrow or
     * RWTIOUResult. Once the escrow is created it is immediately
     * redeemable.
     */
    static RWTEscrowHandle<Redeemable>
    make(const Redeemable& immediateValue);

    // The following virtual functions are called by the base class
    // RWTEscrowImp<Redeemable>. It is assumed that a guard (mutex_) has been
    // acquired before these functions are called, so access to instance
    // members is safe.

    // Escrow operation aborted. Release threads blocked on redeem
    // so they can reap the status.
    virtual void
    _abort(void);

    // Implementation of pure virtual function _close defined in
    // RWTEscrowImp<Redeemable>. Makes a local copy of the value for
    // later redemption. Unblocks any threads blocked in _redeem.
    virtual void
    _close(const Redeemable& value);

    // Implementation of pure virtual function _closed defined in
    // RWTEscrowImp<Redeemable>. Returns true if a value has been stored.
    virtual bool
    _closed(void) const;

    // Returns new copy of this RWTEscrowImp<R> implementation.
    virtual RWTEscrowHandle<Redeemable>
    _newInstance(void) const;

    // Implementation of pure virtual function _redeem defined in
    // RWTEscrowImp<Redeemable>. Returns the internally stored value
    // if available. Otherwise blocks until the value is available.
    virtual const Redeemable&
    _redeem(void) const;

    // Escrow in error. Release threads blocked on redeem so they
    // can reap the status.
    virtual void
    _setException(const RWTHRxmsg& msg);

protected:


    /**
     * The constructor for this class is protected. You must use the static
     * make() members to create instances.
     */
    RWTThreadEscrowImp();

private:

    /**
     * Copy construction prohibited.
     */
    RWTThreadEscrowImp(const RWTThreadEscrowImp& second);

    /**
     * Assignment prohibited.
     */
    RWTThreadEscrowImp&
    operator=(const RWTThreadEscrowImp& second);

};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/thread/RWTThreadEscrowImp.cc>
#endif

#endif // __rw_thread_RWTThreadEscrowImp_h__
