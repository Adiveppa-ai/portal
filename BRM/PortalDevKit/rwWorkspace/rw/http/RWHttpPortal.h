#ifndef __rw_http_RWHttpPortal_h__
#define __rw_http_RWHttpPortal_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpPortal.h#1 $
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

#include <rw/http/RWHttpPortalImp.h>  // get the RWHttpTransferEncoding enum
#include <rw/http/pkgdefs.h>
#include <rw/network/RWPortal.h>

class RW_HTTP_SYMBOLIC RWHttpPortal : public RWPortal
{
public:
    RWHttpPortal();
    // Construct a default RWHttpPortal

    RWHttpPortal(const RWPortal& portal, size_t length, RWHttpTransferEncoding te = RW_HTTP_NONE);
    // Construct a RWHttpPortal on a socket portal

    void
    setPortal(const RWPortal& portal, size_t length, RWHttpTransferEncoding te = RW_HTTP_NONE);
    // Set the portal for use

    bool
    isEOF() const;
    // Returns true if the portal is EOF
};

inline
void
RWHttpPortal::setPortal(const RWPortal& portal, size_t length, RWHttpTransferEncoding te)
{
    RWHttpPortalImp* const imp =
        static_cast<RWHttpPortalImp*>(implementation());
    RW_ASSERT(0 != imp);

    imp->setPortal(portal, length, te);
}

inline
bool
RWHttpPortal::isEOF() const
{
    const RWHttpPortalImp* const imp =
        static_cast<const RWHttpPortalImp*>(implementation());
    RW_ASSERT(0 != imp);

    return imp->isEOF();
}

#endif // __rw_http_RWHttpPortal_h__
