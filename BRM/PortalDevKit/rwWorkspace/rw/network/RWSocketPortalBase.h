#ifndef __rw_network_RWSocketPortalBase_h__
#define __rw_network_RWSocketPortalBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSocketPortalBase.h#1 $
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

#include <rw/network/pkgdefs.h>

/**
 * \ingroup networking_module
 * \class RWSocketPortalBase
 *
 * \brief
 * Base class for all classes that wish to use the #WhoShouldClose
 * enumeration.
 *
 * RWSocketPortalBase serves as the base class for all classes that wish to
 * use the #WhoShouldClose enumeration.
 */
class RW_NETWORK_GLOBAL RWSocketPortalBase
{
public:

    virtual ~RWSocketPortalBase() {};
    // does nothing, but solves a Microsoft bug.

    /**
     * Indicates who should close the socket.
     */
    enum WhoShouldClose {

        /**
         * The socket will be closed automatically when the last portal that
         * references the socket is destructed.
         */
        Portal,

        /**
         * The application is responsible for closing the socket.
         */
        Application
    };

    RWSocketPortalBase() {};
    RWSocketPortalBase(const RWSocketPortalBase&) {};
    // Explicitly null constructors. This is necessary because at least
    // one compiler, that we know of, generates improper copy constructors for
    // classes which only contain an enum.
};

#endif  // __rw_network_RWSocketPortalBase_h__ 
