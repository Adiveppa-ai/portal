#ifndef __rw_http_RWIHttpVersion_1_0_h__
#define __rw_http_RWIHttpVersion_1_0_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpVersion_1_0.h#1 $
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


#if !defined(RW_DISABLE_DEPRECATED)

#  include <rw/http/RWIHttpVersion.h>
#  include <rw/http/pkgdefs.h>

// forward declarations
class RWIHttpMethod;

/*
 * RWIHttpVersion_1_0
 *
 * RWIHttpVersion_1_0 is a specialization class of RWIHttpVersion. It
 * provides all version 1.0 related information.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpRequest instead")
    RW_HTTP_GLOBAL RWIHttpVersion_1_0 : public RWIHttpVersion
{

public:

    RWIHttpVersion_1_0(void);
    // default constructor

    virtual ~RWIHttpVersion_1_0() { }

    bool canPersist(void) const;

    bool methodIsValid(const RWCString& methodName) const;

    RWCString makeMethodAsString(RWIHttpMethod& pMethod);

    int majorVersionNumber(void) const;

    int minorVersionNumber(void) const;

    RWIHttpVersion* clone(void) const;
};

inline
RWIHttpVersion_1_0::RWIHttpVersion_1_0(void)
{
}

inline bool
RWIHttpVersion_1_0::canPersist(void) const
{
    return false;
}

inline int
RWIHttpVersion_1_0::majorVersionNumber(void) const
{
    return 1;
}

inline int
RWIHttpVersion_1_0::minorVersionNumber(void) const
{
    return 0;
}

inline RWIHttpVersion*
RWIHttpVersion_1_0::clone(void) const
{
    return new RWIHttpVersion_1_0(*this);
}

#endif // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpVersion_1_0_h__
