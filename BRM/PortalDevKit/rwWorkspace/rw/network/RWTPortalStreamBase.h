#ifndef __rw_network_RWTPortalStreamBase_h__
#define __rw_network_RWTPortalStreamBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTPortalStreamBase.h#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

#include <rw/network/RWTPortalStreambuf.h>
#include <rw/network/pkgdefs.h>
#include <ios>

class RW_NETWORK_SYMBOLIC RWPortal;

/**
 * \ingroup networking_module
 *
 * \brief
 * Base class that includes functions common to derived portal stream
 * classes.
 *
 * RWTPortalStreamBase includes functions common to derived portal stream
 * classes.
 */
template <class charT, class traits = std::char_traits<charT> >
class RWTPortalStreamBase : virtual public std::basic_ios<charT, traits>
{
public:
    /**
     * Constructs a portal stream.
     */
    RWTPortalStreamBase();

    /**
     * \copydoc RWTPortalStreamBase()
     */
    RWTPortalStreamBase(const RWPortal&);

    /**
     * Sets the stream to use a portal to the same communications channel as
     * \a p. If \a force is \c true, the reattachment is forced, and any
     * exceptions thrown by the underlying RWTPortalStreambuf are caught and
     * ignored.
     */
    void attach(const RWPortal& p, bool force = false); // Onyx #23845

    /**
     * Detaches the stream from the portal channel. If \a force is \c true,
     * the detach is forced, and any exceptions thrown by the underlying
     * RWTPortalStreambuf are caught and ignored. If this is the last portal
     * to this communications channel, then the channel is closed.
     */
    void detach(bool force = false);

protected:
    RWTPortalStreambuf<charT, traits>* getBufPointer()
    {
        return &buf_;
    }

private:
    // The streambuf.
    RWTPortalStreambuf<charT, traits> buf_;
};


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/network/RWTPortalStreamBase.cc>
#endif

#endif  // __rw_network_RWTPortalStreamBase_h__ 
