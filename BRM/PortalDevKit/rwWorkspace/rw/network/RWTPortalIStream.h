#ifndef __rw_network_RWTPortalIStream_h__
#define __rw_network_RWTPortalIStream_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTPortalIStream.h#1 $
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

#include <rw/network/RWTPortalStreamBase.h>
#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>
#include <istream>

// See SP-14202 for more information on why this is necessary
#if defined(_MSC_VER) && _MSC_VER >= 1700
#  pragma warning(push)
#  pragma warning(disable : 4250)
#endif

/**
 * \ingroup networking_module
 *
 * \brief
 * Provides a \b std::basic_istream that uses an RWPortal as its source of
 * bytes.
 *
 * RWTPortalIStream provides a \b std::basic_istream that uses an RWPortal
 * as its source of bytes. The RWPortal associated with this class can be
 * attached to any of the communications channels supported by SourcePro
 * Net.
 */
template <class charT, class traits>
class RWTPortalIStream : public RWTPortalStreamBase<charT, traits>, public std::basic_istream<charT, traits>
{
public:
    /**
     * Constructs a portal input stream from a portal.
     *
     * \note
     * RWTPortalIStream should not be used with a non-blocking
     * communications channel. The implementation of this class uses the
     * \ref RWPortal::recvAtLeast() "recvAtLeast()" and
     * \ref RWPortal::sendAtLeast() "sendAtLeast()" member functions of the
     * underlying RWPortal. These functions will likely throw exceptions if
     * called on a non-blocking communications channel.
     */
    RWTPortalIStream();

    /**
     * \copydoc RWTPortalIStream()
     */
    RWTPortalIStream(const RWPortal&);
};


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/network/RWTPortalIStream.cc>
#endif

#if defined(_MSC_VER)
#  if(_MSC_VER >= 1700)
#    pragma warning(pop)
#  endif
#endif

#endif  // __rw_network_RWTPortalIStream_h__ 
